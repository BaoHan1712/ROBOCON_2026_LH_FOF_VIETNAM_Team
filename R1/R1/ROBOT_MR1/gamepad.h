#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "lcd.h"

//---------------------------------	khai bao bit giao tiep SPI ---------------------------------
/* ket noi gamepad ps2
	MISO->A11
	MOSI->C8
	CS->C9
	SCK->A12
*/
#define SPI_MISO        GPIOA->IDR&(1<<12)//GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_11)

#define SPI_MOSI_0      GPIOC->BSRRH=1<<9//GPIO_WriteBit(GPIOD,GPIO_Pin_10,0)//GPIOB->BRR = 1<<0
#define SPI_MOSI_1      GPIOC->BSRRL=1<<9//GPIO_WriteBit(GPIOD,GPIO_Pin_10,1)//GPIOB->BSRR = 1<<0//GPIO_WriteBit(GPIOA,GPIO_Pin_12,1)

#define SPI_CS_0        GPIOA->BSRRH=1<<11//GPIO_WriteBit(GPIOD,GPIO_Pin_7,0)//GPIOB->BRR = 1<<2//GPIO_WriteBit(GPIOA,GPIO_Pin_14,0) 
#define SPI_CS_1        GPIOA->BSRRL=1<<11//GPIO_WriteBit(GPIOD,GPIO_Pin_7,1)//GPIOB->BSRR = 1<<2//GPIO_WriteBit(GPIOA,GPIO_Pin_14,1)

#define SPI_SCK_0       GPIOC->BSRRH=1<<8//GPIO_WriteBit(GPIOD,GPIO_Pin_8,0)//GPIOB->BRR = 1<<3//GPIO_WriteBit(GPIOA,GPIO_Pin_15,0) 
#define SPI_SCK_1       GPIOC->BSRRL=1<<8//GPIO_WriteBit(GPIOD,GPIO_Pin_8,1)//GPIOB->BSRR = 1<<3//GPIO_WriteBit(GPIOA,GPIO_Pin_15,1)

//-------------------------------------- Dat bien nut nhan -------------------------------------
#define GP_MASK_SELECT 			0x01
#define GP_MASK_START				0x08
#define GP_MASK_UP					0x10
#define GP_MASK_RIGHT				0x20
#define GP_MASK_DOWN				0x40
#define GP_MASK_LEFT				0x80
#define GP_MASK_L2					0x01
#define GP_MASK_R2					0x02
#define GP_MASK_L1					0x04
#define GP_MASK_R1					0x08
#define GP_MASK_TRIANGLE    0x10
#define GP_MASK_O           0x20
#define GP_MASK_X           0x40
#define GP_MASK_SQUARE      0x80
#define GP_MASK_RJOY        0x02
#define GP_MASK_LJOY        0x04

#define GP_MODE_DIGITAL               0x41
#define GP_MODE_NEGCON                0x23
#define GP_MODE_ANALOGUE_RED_LED      0x73
#define GP_MODE_ANALOGUE_GREEN_LED    0x53
#define GP_MODE_NONE                  0xff

#define SELECT        (GP_BTN[0] & GP_MASK_SELECT)
#define START        	(GP_BTN[0] & GP_MASK_START)

#define DOWN        	(GP_BTN[0] & GP_MASK_DOWN)
#define UP            (GP_BTN[0] & GP_MASK_UP)
#define RIGHT        	(GP_BTN[0] & GP_MASK_RIGHT)
#define LEFT        	(GP_BTN[0] & GP_MASK_LEFT)

#define LJOY        	(GP_BTN[0] & GP_MASK_RJOY)
#define RJOY        	(GP_BTN[0] & GP_MASK_LJOY)


#define L2            (GP_BTN[1] & GP_MASK_L2)
#define R2            (GP_BTN[1] & GP_MASK_R2)
#define L1            (GP_BTN[1] & GP_MASK_L1)
#define R1            (GP_BTN[1] & GP_MASK_R1)

#define TRIANGLE    	(GP_BTN[1] & GP_MASK_TRIANGLE)
#define O            	(GP_BTN[1] & GP_MASK_O)
#define X            	(GP_BTN[1] & GP_MASK_X)
#define SQUARE        (GP_BTN[1] & GP_MASK_SQUARE)

#define RJOY_LR       (GP_BTN[2])
#define RJOY_UD       (GP_BTN[3])
#define LJOY_LR       (GP_BTN[4])
#define LJOY_UD       (GP_BTN[5])

void delay_us(vu32 num);

//----------------------- khai bao bien toan cuc ------------------

unsigned char GP_BTN [6];

//----------------------- chuong trinh con ------------------------
unsigned char SPIxmit (unsigned char dta)
{
	unsigned char tmp = 0;
	unsigned char i;
	
	for (i = 0x01; i > 0; i <<= 1)
	{
		 SPI_SCK_0;
     delay_us(5);
		
     if(dta & i) 	SPI_MOSI_1;
		 else					SPI_MOSI_0;
		
     SPI_SCK_1;
     delay_us(15);						// nhanh se anh huong den R2
     if (SPI_MISO) tmp |= i;
	}
	return tmp;
}

void gp_update_btn (void)
{
    SPI_CS_0;
    delay_us(5);
    SPIxmit(0x01);    //start command
    SPIxmit(0x42); // request data
    SPIxmit(0xff); //rx 0x5A
    GP_BTN[0] = SPIxmit(0xff); //SLCT JOYR JOYL STRT UP   RGHT DOWN LEFT
    GP_BTN[1] = SPIxmit(0xff); //L2   R2   L1   R1   /\   O    X    |_|
    GP_BTN[2] = SPIxmit(0xff); //Right Joy 0x00 = Left  0xFF = Right
    GP_BTN[3] = SPIxmit(0xff); //Right Joy 0x00 = Up    0xFF = Down
    GP_BTN[4] = SPIxmit(0xff); //Left Joy  0x00 = Left  0xFF = Right
    GP_BTN[5] = SPIxmit(0xff); //Left Joy  0x00 = Up    0xFF = Down
    delay_us(5);
    SPI_CS_1;
	
}

unsigned char gp_get_mode (void)
{
    unsigned char ret = 0;
    SPI_CS_0;
    delay_us(5);
    SPIxmit(0x01);
    ret = SPIxmit(0x42);
    SPI_CS_1;
    delay_us(5);
    return ret;
}  

//---------------------------- config gamepad PS2 --------------------------
void Config_gamepad_PS2(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOC, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
//  GPIO_InitStructure.GPIO_OType = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
}


