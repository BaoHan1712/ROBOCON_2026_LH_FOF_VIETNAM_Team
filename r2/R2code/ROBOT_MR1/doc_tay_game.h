 
//// ***************    khai bao bit giao tiep SPI     ******************
////
//#include "stm32f4xx.h"
//#include "stm32f4xx_gpio.h"
//#include "stm32f4xx_rcc.h"
//#include <stdio.h>
//#include <stdlib.h>
//#include <math.h>
////#include "lcd.h"
//#define SPI_MISO        (GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_12))

//#define SPI_MOSI_0      GPIO_WriteBit(GPIOD, GPIO_Pin_13, (BitAction)(0))
//#define SPI_MOSI_1      GPIO_WriteBit(GPIOD, GPIO_Pin_13, (BitAction)(1))

//#define SPI_CS_0        GPIO_WriteBit(GPIOD, GPIO_Pin_15, (BitAction)(0))
//#define SPI_CS_1        GPIO_WriteBit(GPIOD, GPIO_Pin_15, (BitAction)(1))

//#define SPI_SCK_0       GPIO_WriteBit(GPIOD, GPIO_Pin_14, (BitAction)(0))
//#define SPI_SCK_1       GPIO_WriteBit(GPIOD, GPIO_Pin_14, (BitAction)(1))

////#define SPI_MISO    PINA.7
////#define SPI_MOSI    PORTA.6
////#define SPI_CS        PORTA.5
////#define SPI_SCK        PORTA.4

////-------------------------------------- Dat bien nut nhan -------------------------------------
//#define GP_MASK_SELECT 			0x01
//#define GP_MASK_START				0x08
//#define GP_MASK_UP					0x10
//#define GP_MASK_RIGHT				0x20
//#define GP_MASK_DOWN				0x40
//#define GP_MASK_LEFT				0x80
//#define GP_MASK_L2					0x01
//#define GP_MASK_R2					0x02
//#define GP_MASK_L1					0x04
//#define GP_MASK_R1					0x08
//#define GP_MASK_TRIANGLE    0x10
//#define GP_MASK_O           0x20
//#define GP_MASK_X           0x40
//#define GP_MASK_SQUARE      0x80
//#define GP_MASK_RJOY        0x02
//#define GP_MASK_LJOY        0x04

//#define GP_MODE_DIGITAL               0x41
//#define GP_MODE_NEGCON                0x23
//#define GP_MODE_ANALOGUE_RED_LED      0x73
//#define GP_MODE_ANALOGUE_GREEN_LED    0x53
//#define GP_MODE_NONE                  0xff

//#define SELECT        (GP_BTN[0] & GP_MASK_SELECT)
//#define START        	(GP_BTN[0] & GP_MASK_START)
//#define LJOY        	(GP_BTN[0] & GP_MASK_RJOY)
//#define RJOY        	(GP_BTN[0] & GP_MASK_LJOY)

//#define UP            (GP_BTN[0] & GP_MASK_UP)
//#define RIGHT        	(GP_BTN[0] & GP_MASK_RIGHT)
//#define DOWN        	(GP_BTN[0] & GP_MASK_DOWN)
//#define LEFT        	(GP_BTN[0] & GP_MASK_LEFT)

//#define L2            (GP_BTN[1] & GP_MASK_L2)
//#define R2            (GP_BTN[1] & GP_MASK_R2)
//#define L1            (GP_BTN[1] & GP_MASK_L1)
//#define R1            (GP_BTN[1] & GP_MASK_R1)

//#define TRIANGLE    	(GP_BTN[1] & GP_MASK_TRIANGLE)
//#define O            	(GP_BTN[1] & GP_MASK_O)
//#define X            	(GP_BTN[1] & GP_MASK_X)
//#define SQUARE        (GP_BTN[1] & GP_MASK_SQUARE)

//#define RJOY_LR       (GP_BTN[2])
//#define RJOY_UD       (GP_BTN[3])
//#define LJOY_LR       (GP_BTN[4])
//#define LJOY_UD       (GP_BTN[5])

//// *************    khai bao bien toan cuc     ***********

//unsigned char GP_BTN [15]={255,255,255,255,255,255,255,255,255,255};
//int errorFixCouter=0;	

////    ******************    chuong trinh con    **************


//unsigned char SPIxmit (unsigned char dta)
//{
//    unsigned char tmp = 0;
//    unsigned char i;
//   // #asm ("WDR")
//    for (i = 0x01; i > 0; i <<= 1)
//    {
//        SPI_SCK_0;
//        delay_us(16);
//        if(dta & i) SPI_MOSI_1;
//        if((dta & i)==0) SPI_MOSI_0;
//        //SPI_MOSI = dta & i;
//        SPI_SCK_1;
//        delay_us(16);
//        if (SPI_MISO) tmp |= i;
//    }
//    return tmp;
//}

//void gp_update_btn (void)
//{
//    SPI_CS_0;
//    delay_us(16);
//    SPIxmit(0x01);    //start command
//    SPIxmit(0x42); // request data
//    SPIxmit(0xff); //rx 0x5A
//    GP_BTN[0] = SPIxmit(0xff); //SLCT JOYR JOYL STRT UP   RGHT DOWN LEFT
//    GP_BTN[1] = SPIxmit(0xff); //L2   R2   L1   R1   /\   O    X    |_|
//    GP_BTN[2] = SPIxmit(0xff); //Right Joy 0x00 = Left  0xFF = Right
//    GP_BTN[3] = SPIxmit(0xff); //Right Joy 0x00 = Up    0xFF = Down
//    GP_BTN[4] = SPIxmit(0xff); //Left Joy  0x00 = Left  0xFF = Right
//    GP_BTN[5] = SPIxmit(0xff); //Left Joy  0x00 = Up    0xFF = Down
////    delay_us(20);
//    SPI_CS_1;
//}

//unsigned char gp_get_mode (void)
//{
//    unsigned char ret = 0;
//    SPI_CS_0;
//    delay_us(16);
//    SPIxmit(0x01);
//    ret = SPIxmit(0x42);
//    SPI_CS_1;
//    delay_us(16);
//    return ret;
//} 

//int get_Gamepad_Bluetouch(vu8 *GP_Arr)
//{
//		errorFixCouter = 0;

//		if(GP_Arr[7] != 13){
//			GP_BTN[0] = 239; //SLCT JOYR JOYL STRT UP   RGHT DOWN LEFT
//			GP_BTN[1] = 255; //L2   R2   L1   R1   /\   O    X    |_|
//			GP_BTN[2] = 255; //2 Joy
//			GP_BTN[3] = 255; //2 Joy
//			GP_BTN[4] = 255; //2 Joy
//			GP_BTN[5] = 255; //2 Joy
//			GP_BTN[6] = 255; //2 Joy
//			return 0;
//		}else{
//			GP_BTN[0] = GP_Arr[0]; //SLCT JOYR JOYL STRT UP   RGHT DOWN LEFT
//			GP_BTN[1] = GP_Arr[1]; //L2   R2   L1   R1   /\   O    X    |_|
//			GP_BTN[2] = GP_Arr[2]; //2 Joy
//			GP_BTN[3] = GP_Arr[3]; 
//			GP_BTN[4] = GP_Arr[4]; 
//			GP_BTN[5] = GP_Arr[5]; 
//			GP_BTN[6] = GP_Arr[6]; 
//		}
//		return 1;
//}
////====================================================
//void fixError_Gamepad_Bluetouch()
//{
//		if(GP_BTN[0] != 255 || GP_BTN[1] != 255 || GP_BTN[2] != 255){
//			if(errorFixCouter++ > 200){
//				GP_BTN[0] = 255;
//				GP_BTN[1] = 255;
//				GP_BTN[2] = 255;
//			}
//		}else errorFixCouter=0;
//}

////void gp_update_uart (void)
////{
////   if(MANG_GAME[0] ==0){
////		GP_BTN[0] = 255; //SLCT JOYR JOYL STRT UP   RGHT DOWN LEFT
////    GP_BTN[1] = 255; //L2   R2   L1   R1   /\   O    X    |_|
////	 }
////	 else{
////    GP_BTN[0] = MANG_GAME[0]; //SLCT JOYR JOYL STRT UP   RGHT DOWN LEFT
////    GP_BTN[1] = MANG_GAME[1]; //L2   R2   L1   R1   /\   O    X    |_|
////    GP_BTN[2] = MANG_GAME[2]; //Right Joy 0x00 = Left  0xFF = Right
////    GP_BTN[3] = MANG_GAME[3]; //Right Joy 0x00 = Up    0xFF = Down
////    GP_BTN[4] = MANG_GAME[4]; //Left Joy  0x00 = Left  0xFF = Right
////    GP_BTN[5] = MANG_GAME[5]; //Left Joy  0x00 = Up    0xFF = Down
////	 }
////}
//unsigned char gp_get_mode_uart (void)
//{
//    return GP_BTN[6];
//} 



//vu8 choBanTay(void)
//{
//	//gp_update_uart();	
//	if(!LJOY)      return 1; 
//  else           return 0;
//}


// ***************    khai bao bit giao tiep SPI     ******************
//
#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


//  ************ Dat bien nut nhan  *****************

#define GP_MASK_SHARE         0x01
#define GP_MASK_OPTIONS       0x02
#define GP_MASK_HOME          0x04
#define GP_MASK_UP            0x08
#define GP_MASK_DOWN        	0x10
#define GP_MASK_RIGHT         0x20
#define GP_MASK_LEFT 	        0x40
#define GP_MASK_TOUCHPAD 	    0x80


#define GP_MASK_L1            0x01
#define GP_MASK_R1            0x02
#define GP_MASK_TRIANGLE   	  0x20
#define GP_MASK_O           	0x08
#define GP_MASK_X           	0x04
#define GP_MASK_SQUARE      	0x10
#define GP_MASK_RJOY        	0x80
#define GP_MASK_LJOY        	0x40

//#define GP_MASK_SELECT 			0x01
//#define GP_MASK_START				0x08
//#define GP_MASK_UP					0x10
//#define GP_MASK_RIGHT				0x20
//#define GP_MASK_DOWN				0x40
//#define GP_MASK_LEFT				0x80
//#define GP_MASK_L2					0x01
//#define GP_MASK_R2					0x02
//#define GP_MASK_L1					0x04
//#define GP_MASK_R1					0x08
//#define GP_MASK_TRIANGLE    0x10
//#define GP_MASK_O           0x20
//#define GP_MASK_X           0x40
//#define GP_MASK_SQUARE      0x80
//#define GP_MASK_RJOY        0x02
//#define GP_MASK_LJOY        0x04

////////////////////////// 

#define GP_MODE_ANALOGUE_RED_LED      0x0D // bat analog 0x73
#define GP_MODE_NONE                  0x0F // 
///////////////////////////////

#define SHARE         (GP_BTN[0] & GP_MASK_SHARE)     //  DEC 1  
#define OPTIONS      	(GP_BTN[0] & GP_MASK_OPTIONS)   //  DEC 2
#define HOME        	(GP_BTN[0] & GP_MASK_HOME)     //   		4
#define TOUCHPAD      (GP_BTN[0] & GP_MASK_TOUCHPAD)     //   128


#define UP           	(GP_BTN[0] & GP_MASK_UP)			// 8
#define RIGHT        	(GP_BTN[0] & GP_MASK_RIGHT)		// 32
#define DOWN        	(GP_BTN[0] & GP_MASK_DOWN)		// 16
#define LEFT        	(GP_BTN[0] & GP_MASK_LEFT)		// 64 


#define LJOY          (GP_BTN[1] & GP_MASK_LJOY)			// 64
#define RJOY          (GP_BTN[1] & GP_MASK_RJOY)			// 128
#define L1            (GP_BTN[1] & GP_MASK_L1)				//	1
#define R1            (GP_BTN[1] & GP_MASK_R1)				//	2
#define TRIANGLE    	(GP_BTN[1] & GP_MASK_TRIANGLE)	// 32
#define O            	(GP_BTN[1] & GP_MASK_O)					//	8
#define X            	(GP_BTN[1] & GP_MASK_X)					// 	4
#define SQUARE        (GP_BTN[1] & GP_MASK_SQUARE)		//	16
#define R2            (GP_BTN[7])				      //	0 =>> 255
#define L2            (GP_BTN[6])				      //	0 =>> 255

#define LJOY_LR       	(GP_BTN[2]) //=0 la Left, 255 la Right
#define LJOY_UD        	(GP_BTN[3]) //=0 la Up, 255 la Down
#define RJOY_LR         	(GP_BTN[4]) //=0 la Left, 255 la Right
#define RJOY_UD         	(GP_BTN[5]) //=0 la Up, 255 la Down

#define BAT										    				(GP_BTN[8] >>4) // gia tri pin tu 0 =.> 10  



///////////////////
/*

//#define GP_MODE_DIGITAL               0x41
//#define GP_MODE_NEGCON                0x23
//#define GP_MODE_ANALOGUE_RED_LED      0x73
//#define GP_MODE_ANALOGUE_GREEN_LED    0x53
//#define GP_MODE_NONE                  0xff

//#define SELECT        (GP_BTN[0] & GP_MASK_SELECT)
//#define START        	(GP_BTN[0] & GP_MASK_START)
//#define LJOY        	(GP_BTN[0] & GP_MASK_RJOY)

//#define RJOY        	(GP_BTN[0] & GP_MASK_LJOY)

//#define UP            (GP_BTN[0] & GP_MASK_UP)
//#define RIGHT        	(GP_BTN[0] & GP_MASK_RIGHT)
//#define DOWN        	(GP_BTN[0] & GP_MASK_DOWN)
//#define LEFT        	(GP_BTN[0] & GP_MASK_LEFT)

//#define L2            (GP_BTN[1] & GP_MASK_L2)
//#define R2            (GP_BTN[1] & GP_MASK_R2)
//#define L1            (GP_BTN[1] & GP_MASK_L1)
//#define R1            (GP_BTN[1] & GP_MASK_R1)

//#define TRIANGLE    	(GP_BTN[1] & GP_MASK_TRIANGLE)
//#define O            	(GP_BTN[1] & GP_MASK_O)
//#define X            	(GP_BTN[1] & GP_MASK_X)
//#define SQUARE        (GP_BTN[1] & GP_MASK_SQUARE)

//#define RJOY_LR       (GP_BTN[2])
//#define RJOY_UD       (GP_BTN[3])
//#define LJOY_LR       (GP_BTN[4])
//#define LJOY_UD       (GP_BTN[5])



2
*/


//    *************    khai bao bien toan cuc     ***********

extern   uint8_t GP_BTN [15];
//extern   uint8_t MANG_GAME [15];

//    ******************    chuong trinh con    **************
////////////////////////////
/*
MANG_GAME[0]=0000 1000& 0x08nut toi
						=0001 0000& 0x10 nut lui



*/
/////////////////////////////////
void gp_update_uart (void)
{
	vs32 tac_chien_dien_tu=((GP_BTN[0]+GP_BTN[1]+GP_BTN[2]+GP_BTN[3]+GP_BTN[4]+GP_BTN[5]+GP_BTN[6]+GP_BTN[7]+GP_BTN[8])&0xFF);   
	vu8 b = GP_BTN[8]&GP_MODE_NONE;

	   float CANH_A,CANH_B;
                  if( b!= 13) {
                     USART_Cmd(USART3, DISABLE);
                  }      
 }
///////////////////////////////

unsigned char gp_get_mode_uart() {
    if (((GP_BTN[8] & GP_MODE_NONE) == GP_MODE_ANALOGUE_RED_LED) && ((GP_BTN[0] & GP_MASK_SHARE) == GP_MASK_SHARE)) {
        return GP_MODE_ANALOGUE_RED_LED;
    } else {
			
        return 0;  
    }
}

vu8 wantExit(void)
{
	//gp_update_uart();	
	if(DOWN)      return 1; 
  else           return 0;
}
