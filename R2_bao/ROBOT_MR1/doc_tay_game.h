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



//    *************    khai bao bien toan cuc     ***********
extern   vs32 HUONG_GAME,HUONG_GAME_CT ;
extern   uint8_t GP_BTN [15];
extern   uint8_t MANG_GAME [15];

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
	const float PI = 3.141592653589793238462643;
    float CANH_A,CANH_B;

              if (tac_chien_dien_tu == GP_BTN[9] && ((GP_BTN[8]&GP_MODE_NONE)==13) ){
                
                  //////////////////////////////////////////////
                              CANH_A=-(GP_BTN[2]-127); CANH_B=(GP_BTN[3]-129);
                                 if(CANH_A==0)CANH_A=1;
                                 if(CANH_B==0)CANH_B=1; 
                                 HUONG_GAME_CT= (abs(CANH_A)+abs(CANH_B))/2;
                              if ((abs(CANH_B)<50)&&(abs(CANH_A)<50)) HUONG_GAME=0;   
                              //else if ((CANH_B>0)&&(CANH_A<0)) HUONG_GAME=(atan(CANH_A/CANH_B)*(1800/3.1415))+1800;  
                              //else if ((CANH_B>0)&&(CANH_A>0)) HUONG_GAME=-1800+(atan(CANH_A/CANH_B)*(1800/3.1415));  
                            //  else HUONG_GAME=(atan(CANH_A/CANH_B)*(1800/3.1415)); 
                             
               else HUONG_GAME = atan2(CANH_A, CANH_B) * (1800 / PI) ; // Tính góc 
    

             
       }
              
      else  {
                  if( b!= 13) {
                     USART_Cmd(USART3, DISABLE);
                    
                  }
               }           
            
 }
///////////////////////////////



// Ham lay che do UART hien tai
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
	if(DOWN)      	return 0; 
  else           	return 1;
}