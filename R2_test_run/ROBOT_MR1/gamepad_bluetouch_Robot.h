//=====================================================================
//=====================================================================
//                  HUYNH CAO TUAN - 03/2017
//=====================================================================
//=====================================================================
//--------- Mat na Bit ----------------------
#define GP_MASK_BIT0         0x01
#define GP_MASK_BIT1         0x02
#define GP_MASK_BIT2         0x04
#define GP_MASK_BIT3         0x08

#define GP_MASK_BIT4    		 0x10
#define GP_MASK_BIT5         0x20
#define GP_MASK_BIT6         0x40
#define GP_MASK_BIT7      	 0x80

#define GP_MASK_BIT_ANALOGUE_ON   0xfc
#define GP_MASK_BIT_ANALOGUE_OFF  0xf4

//---------- byte 6 -----------------------------
#define GP_MODE_DIGITAL               0x41
#define GP_MODE_NEGCON                0x23
#define GP_MODE_ANALOGUE_RED_LED      0x73 // bat analog
#define GP_MODE_ANALOGUE_GREEN_LED    0x53 // tat analog
#define GP_MODE_NONE                  0xff
//---------------------------------------

#define SELECT        (GP_BTN[0] & GP_MASK_BIT0)
#define LJOY        	(GP_BTN[0] & GP_MASK_BIT1)
#define RJOY        	(GP_BTN[0] & GP_MASK_BIT2)
#define START        	(GP_BTN[0] & GP_MASK_BIT3)

#define UP            (GP_BTN[0] & GP_MASK_BIT4)
#define RIGHT        	(GP_BTN[0] & GP_MASK_BIT5)
#define DOWN        	(GP_BTN[0] & GP_MASK_BIT6)
#define LEFT        	(GP_BTN[0] & GP_MASK_BIT7)

#define L2            (GP_BTN[1] & GP_MASK_BIT0)
#define R2            (GP_BTN[1] & GP_MASK_BIT1)
#define L1            (GP_BTN[1] & GP_MASK_BIT2)
#define R1            (GP_BTN[1] & GP_MASK_BIT3)

#define TRIANGLE    	(GP_BTN[1] & GP_MASK_BIT4)
#define O            	(GP_BTN[1] & GP_MASK_BIT5)
#define X            	(GP_BTN[1] & GP_MASK_BIT6)
#define SQUARE        (GP_BTN[1] & GP_MASK_BIT7)

//------------------------------------------------
#define RJOY_LEFT 		(GP_BTN[2] & GP_MASK_BIT0)
#define RJOY_RIGHT 		(GP_BTN[2] & GP_MASK_BIT1)
#define RJOY_UP 			(GP_BTN[2] & GP_MASK_BIT2)
#define RJOY_DOWN 		(GP_BTN[2] & GP_MASK_BIT3)
#define LJOY_LEFT 		(GP_BTN[2] & GP_MASK_BIT4)
#define LJOY_RIGHT 		(GP_BTN[2] & GP_MASK_BIT5)
#define LJOY_UP 			(GP_BTN[2] & GP_MASK_BIT6)
#define LJOY_DOWN 		(GP_BTN[2] & GP_MASK_BIT7)

#define ANALOG_ON   	(GP_BTN[3] == GP_MASK_BIT_ANALOGUE_ON)

//    *************    khai bao bien toan cuc     ***********

unsigned char GP_BTN[4]={255,255,255,255};
int errorFixCouter=0;	

//===================================================
int get_Gamepad_Bluetouch(vu8 *GP_Arr)
{
		errorFixCouter = 0;

		if(GP_Arr[3] != GP_MASK_BIT_ANALOGUE_ON && GP_Arr[3] != GP_MASK_BIT_ANALOGUE_OFF){
			GP_BTN[0] = 255; //SLCT JOYR JOYL STRT UP   RGHT DOWN LEFT
			GP_BTN[1] = 255; //L2   R2   L1   R1   /\   O    X    |_|
			GP_BTN[2] = 255; //2 Joy
			return 0;
		}else{
			GP_BTN[0] = GP_Arr[0]; //SLCT JOYR JOYL STRT UP   RGHT DOWN LEFT
			GP_BTN[1] = GP_Arr[1]; //L2   R2   L1   R1   /\   O    X    |_|
			GP_BTN[2] = GP_Arr[2]; //2 Joy
			GP_BTN[3] = GP_Arr[3]; // Analogue - Check Sum
		}
		return 1;
}
//====================================================
void fixError_Gamepad_Bluetouch()
{
		if(GP_BTN[0] != 255 || GP_BTN[1] != 255 || GP_BTN[2] != 255){
			if(errorFixCouter++ > 200){
				GP_BTN[0] = 255;
				GP_BTN[1] = 255;
				GP_BTN[2] = 255;
			}
		}else errorFixCouter=0;
}
