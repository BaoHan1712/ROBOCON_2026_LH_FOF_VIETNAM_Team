#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_i2c.h"
#include "stm32f4xx_rcc.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
vu8 DATA_SPEED[80]={255,1,0,0,				// 1- ID = 1, DIRECT = 0, SPEED = 0
										255,2,0,0,			// 1- ID = 2, DIRECT = 0, SPEED = 0
										255,3,0,0,			// 1- ID = 3, DIRECT = 0, SPEED = 0
										255,4,0,0,			// 1- ID = 4, DIRECT = 0, SPEED = 0
										255,5,0,0,			// 1- ID = 5, DIRECT = 0, SPEED = 0
										255,6,0,0,			// 1- ID = 6, DIRECT = 0, SPEED = 0
										255,7,0,0,			// 1- ID = 7, DIRECT = 0, SPEED = 0
										255,8,0,0,			// 1- ID = 8, DIRECT = 0, SPEED = 0
										255,9,0,0,			// 1- ID = 9, DIRECT = 0, SPEED = 0
										255,10,0,0,			// 1- ID = 10, DIRECT = 0, SPEED = 0
										255,11,0,0,			// 1- ID = 11, DIRECT = 0, SPEED = 0
										255,12,0,0,			// 1- ID = 12, DIRECT = 0, SPEED = 0
										255,13,0,0,			// 1- ID = 13, DIRECT = 0, SPEED = 0	
										255,14,0,0,			// 1- ID = 14, DIRECT = 0, SPEED = 0
										255,15,0,0,			// 1- ID = 15, DIRECT = 0, SPEED = 0
										255,16,0,0,			// 1- ID = 16, DIRECT = 0, SPEED = 0
										255,17,0,0,			// 1- ID = 17, DIRECT = 0, SPEED = 0
										255,18,0,0,			// 1- ID = 18, DIRECT = 0, SPEED = 0
										255,19,0,0,			// 1- ID = 19, DIRECT = 0, SPEED = 0
										255,20,0,0,			// 1- ID = 20, DIRECT = 0, SPEED = 0	
};

/*----------- bit loc trong byte ---------------*/
#define bit_0_H        0x01
#define bit_1_H        0x02
#define bit_2_H        0x04
#define bit_3_H        0x08
#define bit_4_H        0x10
#define bit_5_H        0x20
#define bit_6_H        0x40
#define bit_7_H        0x80

#define bit_0_L        0xFE
#define bit_1_L        0xFD
#define bit_2_L        0xFB
#define bit_3_L        0xF7
#define bit_4_L        0xEF
#define bit_5_L        0xDF
#define bit_6_L        0xBF
#define bit_7_L        0x7F
/*##############################################*/

#define 	ADC1_DR_ADDRESS    ((uint32_t)0x4001204C)

////////////////////// --KHAI BAO DINH NGHIA PWM 4 BANH XE-- /////////////////////////////////////
#define	DIA_CHI_START1 												DATA_SPEED[0]=255
#define	ID1 		 															DATA_SPEED[1]=1
#define Mor_FrontLeft_thuan  					 				DATA_SPEED[2]=0
#define Mor_FrontLeft_nghich 									DATA_SPEED[2]=1
#define	Mor_FrontLeft							 		 				DATA_SPEED[3]

#define	DIA_CHI_START2 												DATA_SPEED[4]=255
#define	ID2 		 															DATA_SPEED[5]=2
#define Mor_FrontRight_thuan 									DATA_SPEED[6]=1
#define Mor_FrontRight_nghich									DATA_SPEED[6]=0
#define	Mor_FrontRight												DATA_SPEED[7]


#define	DIA_CHI_START3 												DATA_SPEED[8]=255
#define	ID3 		 															DATA_SPEED[9]=3
#define Mor_RearLeft_thuan				 						DATA_SPEED[10]=1
#define Mor_RearLeft_nghich										DATA_SPEED[10]=0
#define	Mor_RearLeft					 								DATA_SPEED[11]

#define	DIA_CHI_START4												DATA_SPEED[12]=255
#define	ID4	 																	DATA_SPEED[13]=4
#define Mor_RearRight_thuan							 			DATA_SPEED[14]=1
#define Mor_RearRight_nghich									DATA_SPEED[14]=0
#define	Mor_RearRight		 											DATA_SPEED[15]

#define	DIA_CHI_START5 												DATA_SPEED[16]=255
#define	ID5	 		 															DATA_SPEED[17]=5
#define mor_lift_rear_up											DATA_SPEED[18]=1
#define mor_lift_rear_down					 					DATA_SPEED[18]=0
#define	mor_lift_rear					 								DATA_SPEED[19]

#define	DIA_CHI_START6											  DATA_SPEED[20]=255
#define	ID6																    DATA_SPEED[21]=6
#define mor_lift_front_up					 						DATA_SPEED[22]=0
#define mor_lift_front_down										DATA_SPEED[22]=1
#define	mor_lift_front		 										DATA_SPEED[23]



#define	DIA_CHI_START7											  DATA_SPEED[24]=255 // -- OK
#define	ID7																    DATA_SPEED[25]=7 
#define Gat_tay1_len				 									DATA_SPEED[26]=1
#define Gat_tay1_xuong												DATA_SPEED[26]=0
#define	Gat_tay1							 								DATA_SPEED[27]

#define	DIA_CHI_START8											  DATA_SPEED[28]=255 // -- OK
#define	ID8																    DATA_SPEED[29]=8
#define Cylinder2_next					 							DATA_SPEED[30]=1
#define Cylinder2_back												DATA_SPEED[30]=0
#define	Cylinder_ID8	 												DATA_SPEED[31]

//==============================Co cau ====================================================================
#define	DIA_CHI_START9						DATA_SPEED[32]=255
#define	ID9												DATA_SPEED[33]=9
#define Cylinder_next							DATA_SPEED[34]=1
#define Cylinder_back							DATA_SPEED[34]=0
#define	Cylinder_ID9							DATA_SPEED[35]

#define	DIA_CHI_START10						DATA_SPEED[36]=255 // -- OK
#define	ID10									 		DATA_SPEED[37]=10
#define tay_xoay_thuan 					  DATA_SPEED[38]=1
#define tay_xoay_nghich			      DATA_SPEED[38]=0
#define	tay_xoay									DATA_SPEED[39]

#define	DIA_CHI_START11						DATA_SPEED[40]=255 // -- OK
#define	ID11											DATA_SPEED[41]=11 
#define Gat_tay2_len				 			DATA_SPEED[42]=0
#define Gat_tay2_xuong						DATA_SPEED[42]=1
#define	Gat_tay2									DATA_SPEED[43]


//#define	DIA_CHI_START12						DATA_SPEED[44]=255 // -- OK
//#define	ID12											DATA_SPEED[45]=12 
//#define XI_LANH_HA_KEP				 		DATA_SPEED[46]=1
//#define XI_LANH_NANG_KEP					DATA_SPEED[46]=0
//#define	Nang_Ha_Kep								DATA_SPEED[47]


//#define	DIA_CHI_START13						DATA_SPEED[48]=255 // -- OK
//#define	ID13											DATA_SPEED[49]=13 
//#define XI_LANH_KEP_MO						DATA_SPEED[50]=0
//#define XI_LANH_KEP_DONG					DATA_SPEED[50]=1
//#define	Kep					  						DATA_SPEED[51]


//==========================================================================================

//3 PHA
#define	DIA_CHI_START14 														   DATA_SPEED[52]=255
#define	DIA_CHI_P14														         DATA_SPEED[53]=0
#define	ID14 		 															  	   	 DATA_SPEED[54]=14
#define	dong_co_ban_1(A)										           ((DATA_SPEED[56]=A&0xFF)| (DATA_SPEED[55]=(A>>8)&0xFF))



#define	DIA_CHI_START15 														   DATA_SPEED[57]=255
#define	DIA_CHI_P15														         DATA_SPEED[58]=0
#define	ID15 		 															  	  	 DATA_SPEED[59]=15
#define	dong_co_ban_2(A)										           ((DATA_SPEED[61]=A&0xFF)| (DATA_SPEED[60]=(A>>8)&0xFF))

//=============================================================================================

 //Cylnder 
//#define	DIA_CHI_START16						DATA_SPEED[62]=255
//#define	ID16											DATA_SPEED[63]=16 
//#define Cylinder_next							DATA_SPEED[64]=1
//#define Cylinder_back							DATA_SPEED[64]=0
//#define	Cylinder									DATA_SPEED[66]




//=============================ADC DMI======================================//

#define bien_tro_gat1												 _ADC1_Value[0]//pinA2
#define bien_tro_gat2												 _ADC1_Value[1]//pinA3

#define bien_tro_chan_truoc									 _ADC1_Value[2]//A4	
#define bien_tro_chan_sau								 	 	 _ADC1_Value[3]//AA5	 
#define bien_tro_xoay_tay								 		 _ADC1_Value[4]//A6
#define Quang_tro								 	 	 				 _ADC1_Value[5]//
#define Quang_tro2								 	 	 				_ADC1_Value[8]//
#define Quang_tro3								 	 	 				_ADC1_Value[7]//


#define cam_bien_laze_phai			       			 _ADC1_Value[10]//ok
#define cam_bien_laze_trai			       			 _ADC1_Value[11]

#define cam_bien_laze_truoc							 		 _ADC1_Value[12]  //OK
#define cam_bien_laze_sau							 		   _ADC1_Value[13]  //OK 


 
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx OUTPUT xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx//
//CO CAU LAY BONG


#define   XI_LANH_DAY_BONG_RA								GPIO_WriteBit(GPIOA,GPIO_Pin_12,0) // -- OK
#define   XI_LANH_DAY_BONG_VAO							GPIO_WriteBit(GPIOA,GPIO_Pin_12,1)

////////////////////////////////////////////////////////////////////////////////////////////////////////

//#define   XI_LANH_BAN_BONG_ON								GPIO_WriteBit(GPIOB,GPIO_Pin_0,1) // -- OK
//#define   XI_LANH_BAN_BONG_OFF							GPIO_WriteBit(GPIOB,GPIO_Pin_0,0)


//////////////////////////////////////////////////////////////////////////////////////////////////////

//#define   XI_LANH_NANG_KEP									GPIO_WriteBit(GPIOB,GPIO_Pin_10,0) 
//#define   XI_LANH_HA_KEP										GPIO_WriteBit(GPIOB,GPIO_Pin_10,1)
 
//#define   XI_LANH_KEP_DONG									GPIO_WriteBit(GPIOB,GPIO_Pin_11,0) // -- OK
//#define   XI_LANH_KEP_MO										GPIO_WriteBit(GPIOB,GPIO_Pin_11,1)

#define   XI_LANH_TAY1_LEN										GPIO_WriteBit(GPIOB,GPIO_Pin_7,1) 
#define 	XI_LANH_TAY1_XUONG									GPIO_WriteBit(GPIOB,GPIO_Pin_7,0)

#define   XI_LANH_TAY1_RA										GPIO_WriteBit(GPIOB,GPIO_Pin_6,1) // -- OK
#define   XI_LANH_TAY1_VAO										GPIO_WriteBit(GPIOB,GPIO_Pin_6,0)

#define   XI_LANH_TAY2_LEN											GPIO_WriteBit(GPIOB,GPIO_Pin_0,1) // -- OK
#define   XI_LANH_TAY2_XUONG										GPIO_WriteBit(GPIOB,GPIO_Pin_0,0)

#define   XI_LANH_TAY2_RA											GPIO_WriteBit(GPIOD,GPIO_Pin_15,1) // -- OK
#define   XI_LANH_TAY2_VAO										GPIO_WriteBit(GPIOD,GPIO_Pin_15,0)

#define   XI_LANH_TAY3_LEN											GPIO_WriteBit(GPIOD,GPIA_Pin_12,1) // -- OK
#define   XI_LANH_TAY3_XUONG										GPIO_WriteBit(GPIOD,GPIA_Pin_12,0)

#define   XI_LANH_TAY3_RA											GPIO_WriteBit(GPIOA,GPIO_Pin_11,1) // -- OK
#define   XI_LANH_TAY3_VAO										GPIO_WriteBit(GPIOA,GPIO_Pin_11,0)
//                                    GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_11), OK
//                                    GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_11),
//                                    GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_10),
//                                    GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_12),
//                                    GPIO_ReadOutputDataBit(GPIOD, GPIO_Pin_15), OK
//                                    GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_6), OK
//                                    GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_0), OK
//                                    GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_7)


// SAN    
#define  DO																	GPIO_WriteBit(GPIOC,GPIO_Pin_15,1)
#define  XANH																GPIO_WriteBit(GPIOC,GPIO_Pin_15,0)

//================================INPUT==================================//
//CAM BIEN TREN ROBOT 1
#define  CB_Ha_Dau													GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)//ok
#define  CB_Ha_Sau													GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8)//ok
#define  CB_tay_kep_vk_T										GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_15)//ok
#define  CB_tay_kep_vk_P										GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)//ok
#define  CB_ROI_3														GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_12)//ok
#define  CB_ROI_2													GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)//ok
#define  CB_kep													    GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_1)//ok
#define  CB_ROI_1														GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0)//ok
#define  CB_ROI_4														GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_11)//ok
#define  CB_bung											    	GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_13)//ok
#define  CB_bung_duoi												GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_0)//ok
#define  CB_kep_1_1											GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_15)//okT
#define  CB_kep_1_2											GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_10)//okP
#define  CB_kep_2_1											GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_12)//okT
#define  CB_kep_2_2											GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_10)//okP
#define  CB_kep_3_1											GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_14)//okT
#define  CB_kep_3_2											GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_14)//okP
#define  CB_kep_4_1											GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_13)//OKT
#define  CB_kep_4_2											GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_11)//OKP
#define  CB_vtri_leo										GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_6)

#define  CB_xilanh_tay_1								GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_15)//OK nhan la 0, khong nhan la 1
#define  CB_xilanh_tay_2								GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11)//OK

#define  CB_vtri_leo_dau								GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_14)//OK KO NHAN = 1,NHAN = 0
#define  CB_Cap_Thanh_Sau								GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_7)//OK  k nhan la 0, nhan la 1

#define  CB_Nang_trai										GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_11)
#define  CB_Nang_phai										GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_9)

//================================INPUT==================================//


#define  HT_1																GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_12)//ok
#define  HT_2																GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_10)//ok
#define  HT_3																GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_8)//ok
#define  HT_4																GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_7)//ok
#define  HT_qua_1														GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_12)//ok
#define  HT_qua_2														GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_15)//ok
#define  HT_qua_3														GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_10)//ok
//#define  CB_XL_NANG_LUA_3										GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_18)
//#define  CB_XL_NANG_LUA_2										GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_6)
//																		GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_8)ok,
//                                    GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_7)ok,
//                                    GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_10),
//                                    GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_4),
//                                    GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_12),
//                                    GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_3),
//                                    GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_13),
//                                    GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_4)ok,
//                              
//                                    GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_14),
//                                    GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_3),
//                                    GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_15)ok,
//                                    GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_2)ok,
//                                    GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_14),
//                                    GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_1)ok,
//                                    GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_13),
//                                    GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_0)ok
//NUT BAM
#define		CHON_SAN												 	GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)
#define  	NUT_START													GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_14)

//****************************** Khai bao cam bien do line ******************************//
#define GP_MASK_0					0x01
#define GP_MASK_1					0x02
#define GP_MASK_2					0x04
#define GP_MASK_3					0x08
#define GP_MASK_4					0x10
#define GP_MASK_5					0x20
#define GP_MASK_6					0x40
#define GP_MASK_7					0x80

#define CB_Line_P1				(CB_DO_LINE[0] & GP_MASK_0)
#define CB_Line_P2				(CB_DO_LINE[0] & GP_MASK_1)
#define CB_Line_P3				(CB_DO_LINE[0] & GP_MASK_2)
#define CB_Line_P4				(CB_DO_LINE[0] & GP_MASK_3)

#define CB_Line_T1				(CB_DO_LINE[0] & GP_MASK_4)
#define CB_Line_T2				(CB_DO_LINE[0] & GP_MASK_5)
#define CB_Line_T3				(CB_DO_LINE[0] & GP_MASK_6)
#define CB_Line_T4				(CB_DO_LINE[0] & GP_MASK_7)

//=============================ENCODER======================================
#define Encoder_Xoay		(vs32)((num_over_t1<<16) | TIM_GetCounter(TIM1))/61.3
//#define Encoder_4h			(vs32)((num_over_t5<<16) | TIM_GetCounter(TIM5))/61.3 
//#define Encoder_8h			(vs32)((num_over_t3<<16) | TIM_GetCounter(TIM3))/61.3 //TRONG78.32306
//#define Encoder_0h			(vs32)((num_over_t2<<16) | TIM_GetCounter(TIM2))/61.3
#define Encoder_Front_Left	(vs32)((num_over_t2<<16) | TIM_GetCounter(TIM2))/12
#define Encoder_Front_Right	(vs32)((num_over_t3<<16) | TIM_GetCounter(TIM3))/12
#define Encoder_Rear_Left		(vs32)((num_over_t4<<16) | TIM_GetCounter(TIM4))/12
#define Encoder_Rear_Right	(vs32)((num_over_t5<<16) | TIM_GetCounter(TIM5))/12

//#define Encoder_Run_Right		(vs32)((num_over_t1<<16) | TIM_GetCounter(TIM1))/10

///////////////////////KET THUC KHAI BAO  NHUNG CHAN MAC DINH/////////////////////////////////////////

/* -------------------------KHAI BAO VAN THEO DRIVER KICH VAN---------------------------*/
// Chu y: Chi sua ten Van khong sua dinh nghia phia sau

// Khai Bao van don cho Driver Cylinder ID 9
#define Tay_kep_mo					Cylinder_ID9 |= bit_0_H
#define Tay_kep_dong				Cylinder_ID9 &= bit_0_L

#define Tay_kep_xuong				Cylinder_ID9 |= bit_1_H
#define Tay_kep_len				Cylinder_ID9 &= bit_1_L

#define phai_4_ra						Cylinder_ID9 |= bit_2_H
#define phai_4_vao					Cylinder_ID9 &= bit_2_L

#define Tay3_xa_on					Cylinder_ID9 |= bit_3_H
#define Tay3_xa_off					Cylinder_ID9 &= bit_3_L

#define Bom1_off						Cylinder_ID9 |= bit_4_H
#define Bom1_on							Cylinder_ID9 &= bit_4_L
	
#define Bom3_off						Cylinder_ID9 |= bit_5_H
#define Bom3_on							Cylinder_ID9 &= bit_5_L

#define Bom2_off						Cylinder_ID9 |= bit_6_H
#define Bom2_on							Cylinder_ID9 &= bit_6_L

#define XI_LANH2						Cylinder_ID9 |= bit_7_H
#define XI_LANH3						Cylinder_ID9 &= bit_7_L

// Khai Bao van don cho Driver Cylinder ID 8
#define Tay1_len_on						Cylinder_ID8 |= bit_0_H//ko ok
#define Tay1_len_off					Cylinder_ID8 &= bit_0_L

#define	Tay1_xuong_on				Cylinder_ID8 |= bit_1_H
#define Tay1_xuong_off			Cylinder_ID8 &= bit_1_L

#define Kep_phai_4_ra					Cylinder_ID8 |= bit_2_H
#define Kep_phai_4_vao				Cylinder_ID8 &= bit_2_L

#define Kep_phai_1_ra					Cylinder_ID8 |= bit_3_H
#define Kep_phai_1_vao				Cylinder_ID8 &= bit_3_L

#define Kep_phai_3_ra					Cylinder_ID8 |= bit_4_H
#define Kep_phai_3_vao				Cylinder_ID8 &= bit_4_L

#define Tay1_len						Cylinder_ID8 |= bit_5_H
#define Tay1_xuong					Cylinder_ID8 &= bit_5_L

#define Kep_phai_2_ra					Cylinder_ID8 |= bit_6_H
#define Kep_phai_2_vao				Cylinder_ID8 &= bit_6_L

#define Tay2_len					Cylinder_ID8 |= bit_7_H
#define Tay2_xuong					Cylinder_ID8 &= bit_7_L

//Bien ham reset banh xe
int bienBuTruRR = 900, bienBuTruRL = 0, bienBuTruFR = 0 , bienBuTruFL = 0;
int bitVeHome = 1;
extern int _RRRO, _RLRO, _FFRO, _FLRO , _speed0h;


//End
vs32 	sieu_am,num_over_t1=0,num_over_t2=0, num_over_t3=0,num_over_t5=0, num_over_t9=0,CCR2_Val,HMI_LOOP, num_over_t4;;
vs16 	IMU,IMUxoay;
vu8 	data_tx_gyro,en_gyro,dataTxGyro,enGyro, CB_DO_LINE[1], Home = 0; 
int 	lazeSauValue,lazeTruocValue,lazeTraiValue,lazePhaiValue,quangTroValue,lazeTruocNhoValue;	
int		bientroxoaytayValue, bientronangtayValue,bientrochantruocValue,bientrochansauValue,bientrodaytay1Value,bientrodaytay2Value;
vu16 _ADC1_Value[14];
vu8   RX_USART1[15], RX_USART2[15],DATA_COLOR[20];

uint8_t MANG_GAME[15];		
uint8_t GP_BTN [15];
vs32 HUONG_GAME,HUONG_GAME_CT ;

extern unsigned char GP_BTN [15];
extern int laybong;
extern int Rear_Left_Wheel_Angle, Rear_Right_Wheel_Angle, Front_Left_Wheel_Angle, Front_Right_Wheel_Angle;
extern float _robotRunFL, _robotRunFR, _robotRunRL, _robotRunRR;
float _robotDirFL, _robotDirFR, _robotDirRL, _robotDirRR;
extern float _robotRotateFL, _robotRotateFR, _robotRotateRL, _robotRotateRR, Vy10, Vx10;;
extern int Rear_Left_Wheel_Angle_dir, Rear_Right_Wheel_Angle_dir, Front_Left_Wheel_Angle_dir, Front_Right_Wheel_Angle_dir, dir;
extern int _robotIMUAngle, _wheelRotateAngle;

int da_lay_vk = 0;

extern int final_force;
extern int force_F;
float degree_F;

int TinHieu_ChuanBi_GapThang = 0;
int TinHieu_ChuanBi_GapTrai = 0;
int TinHieu_ChuanBi_GapPhai = 0;

int bai_db = 0;

extern int _robotIMUAngle;
int Vi_tri;
int coVong = 0;
int Vitri_tru = 0;
int g0,g1,g2,g3,g4,g5,g6;
int bit_khoa_ham_thay_tuan = 0;
int dang_Ban = 0;

int robotIsRun_cc = 0;
int vi_tri_bong, vi_tri_ma_xoay = 0;
int sang_phai = 0;
int sang_trai = 0;
int di_xuong = 0;
int di_len = 0;

int target_BT_Xoay = 1020;
int Min_BT_Xoay =  300;
int Max_BT_Xoay = 800;


int taget_BT_Nong_Ban = 760;
int Min_BT_Nong_Ban = 350;
int Max_BT_Nong_Ban = 530;
int goc_ban = 440;//

int cho_phep_chay = 0;

/// **************** GIA TRI VI TRI DAT HOP ********************

int vi_tri_dat_hop_1_2 = 404;
int vi_tri_dat_hop_3_4 = 600;
int tin_hieu_dat_hop_3_4 = 0;
int tin_hieu_dat_hop_1_2 = 0;

int vi_tri_tay_3_dat_hop = 505;
int vi_tri_tay_4_dat_hop = 505;


/// **************** GIA TRI VI TRI TAY ********************

int vi_tri_tay_43 = 505;
int vi_tri_tay_12 = 698;

// VI TRI MAM XOAY LAY BEN PHAI 200 TREN
int vi_tri_tay_4_phai_tren = 610;
int vi_tri_tay_1_phai_tren = 420;
int vi_tri_tay_2_phai_tren = 410;
int vi_tri_tay_3_phai_tren = 600;

int vi_tri_tay_4_phai_duoi = 607;
int vi_tri_tay_3_phai_duoi = 600;


/// VI TRI MAM XOAY LAY TRAI 200 
int vi_tri_tay_4_trai_tren = 406;
int vi_tri_tay_1_trai_tren = 602;
int vi_tri_tay_2_trai_tren = 600;
int vi_tri_tay_3_trai_tren = 407;

int vi_tri_tay_4_trai_duoi = 413;
int vi_tri_tay_3_trai_duoi = 405;

/// VI TRI LAZER LAY QUA THANG
int vitri_tay41_laser_trai_GapQua = 153;
int vitri_tay23_laser_trai_GapQua = 224;
int vitri_tay23_phai_laser_GapQua = 151;


int vitri_tay1home = 445;
int vitri_tay2home = 445;

int vi_tri_gap_ngang_43 = 602;
//// ******** VI TRI LAZER CUA RUNG XANH *********************

int vi_tri_cua_rung_xanh_1_lazer_phai_tay_41 = 308;
int vi_tri_cua_rung_xanh_1_lazer_phai_tay_23 = 261;

int vi_tri_cua_rung_xanh_2_lazer_phai_tay_41 = 406;
int vi_tri_cua_rung_xanh_2_lazer_trai_tay_41 = 428;
int vi_tri_cua_rung_xanh_2_lazer_phai_tay_23 = 399;

int vi_tri_cua_rung_xanh_3_lazer_trai_tay_41 = 305;
int vi_tri_cua_rung_xanh_3_lazer_trai_tay_23 = 370;
int vi_tri_cua_rung_xanh_3_lazer_phai_tay_23 = 446;
int vi_tri_cua_rung_xanh_3_lazer_phai_tay_41 = 474;

//// ******** VI TRI LAZER CUA RUNG DO *********************
int vi_tri_cua_rung_do_3_lazer_phai_tay_41 = 306;
int vi_tri_cua_rung_do_3_lazer_phai_tay_23 = 262;

int vi_tri_cua_rung_do_2_lazer_phai_tay_41 = 403;
int vi_tri_cua_rung_do_2_lazer_phai_tay_23 = 363;

int vi_tri_cua_rung_do_1_lazer_phai_tay_41 = 481;
int vi_tri_cua_rung_do_1_lazer_phai_tay_23 = 451;

int vi_tri_cua_rung_do_1_lazer_trai_tay_41 = 308;
int vi_tri_cua_rung_do_1_lazer_trai_tay_23 = 370;

///*********************************************************


int target_Nang_Ha = 600;
int Min_Nang_Ha = 160 ;
int Max_Nang_Ha = 610;
static bool on_off_nang = true;


extern int state_nang;

int Max_BT_Nang_Lua = 730;
int taget_BT_Nang_Lua = 715;
int Min_BT_Nang_Lua = 470;

int Max_BT_Nang_Bong = 540;
int taget_BT_Nang_Bong = 435;//
int Min_BT_Nang_Bong = 270 ;//
int BT_Nang_Tha_Bong = 280;
int BT_Bat_Bong_giua =420;
int BT_Bat_Bong_sau =530;

extern int part;
vs8 CB_line_trai, CB_line_phai, Nho_trai_truoc, Nho_trai_sau, Nho_phai_truoc, Nho_phai_sau;

char Do_Xanh;
//////////////////////////chong nhieu encoder////////////////////
vs32 ENCODER_FL()
{
	vs32 en, enOld = Encoder_Front_Left;
	int i=0;
	while( i < 2)
	{
		en = Encoder_Front_Left;
		if(abs(en - enOld) < 5) i++;
		enOld = en;
	}
	return -en;
}

vs32 ENCODER_FR()
{
	vs32 en, enOld = Encoder_Front_Right;
	int i=0;
	while( i < 2)
	{
		en = Encoder_Front_Right;
		if(abs(en - enOld) < 5) i++;
		enOld = en;
	}
	return en;
}

vs32 ENCODER_RL()
{
	vs32 en, enOld = Encoder_Rear_Left;
	int i=0;
	while( i < 2)
	{
		en = Encoder_Rear_Left;
		if(abs(en - enOld) < 5) i++;
		enOld = en;
	}
	return en;
}

//////////////////////////chong nhieu encoder////////////////////
vs32 ENCODER_RR()
{
	vs32 en, enOld = Encoder_Rear_Right;
	int i=0;
	while( i < 2)
	{
		en = Encoder_Rear_Right;
		if(abs(en - enOld) < 5) i++;
		enOld = en;
	}
	return en;
}

//vs32 ENCODER_XOAY()
//{
//	//return (vs32)((num_over_t2<<16)|TIM_GetCounter(TIM2))/100;
//	vs32 en, enOld = Encoder_Xoay;
//	int i=0;
//	while( i < 2)
//	{
//		en = Encoder_Xoay;
//		if(abs(en - enOld) < 50) i++;
//		enOld = en;
//	}
//	return en;
//}

//////////////////////////chong nhieu encoder////////////////////
//vs32 Encoder_RunRight()
//{
//	vs32 en, enOld = Encoder_Run_Right;
//	int i=0;
//	while( i < 2)
//	{
//		en = Encoder_Run_Right;
//		if(abs(en - enOld) < 5) i++;
//		enOld = en;
//	}
//	return abs(en);
//}


//vs32 ENCODER_TONG()
//{
//	return	Encoder_RunRight();
//}

//------------------------------------ DELAY MICROSECOND--------------------------------------------
void delay_us(vu32 num)
{
	__IO uint32_t index = 0;
	/* default system clock is 180MHz */
	for(index = (18 * num); index != 0; index--);
}
//------------------------------------ DELAY MILISECOND--------------------------------------------
void delay_ms(vu32 num)
{
	__IO uint32_t index = 0;
	/* default system clock is 180MHz */
	for(index = (18000 * num); index != 0; index--);
}

//---------------------------- config out mode -----------------------------
void Config_out_mode(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD|RCC_AHB1Periph_GPIOB|RCC_AHB1Periph_GPIOA|RCC_AHB1Periph_GPIOE|RCC_AHB1Periph_GPIOC, ENABLE);

	GPIO_InitStructure.GPIO_Pin = 0xffff;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = 0xffff;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = 0xffff;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOD, &GPIO_InitStructure);

}
//---------------------------- config in mode -----------------------------
void Config_in_mode(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB | RCC_AHB1Periph_GPIOC | RCC_AHB1Periph_GPIOD | RCC_AHB1Periph_GPIOE | RCC_AHB1Periph_GPIOF | RCC_AHB1Periph_GPIOG, ENABLE);
	/////////////////////////////////////line
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7| GPIO_Pin_8| GPIO_Pin_11| GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = 	GPIO_Pin_2 | GPIO_Pin_1| GPIO_Pin_6| GPIO_Pin_7| GPIO_Pin_15| GPIO_Pin_14| GPIO_Pin_13| GPIO_Pin_12| GPIO_Pin_11| GPIO_Pin_10| GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11| GPIO_Pin_14| GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	
}

	//============================ config timer6 1ms ===================================
void Config_int_time6(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	NVIC_InitStructure.NVIC_IRQChannel = TIM6_DAC_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);
	TIM_TimeBaseInitStructure.TIM_Prescaler=50;//50
	TIM_TimeBaseInitStructure.TIM_Period=999;//999;//1ms
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;//
	TIM_TimeBaseInit(TIM6, &TIM_TimeBaseInitStructure);

	TIM_ClearITPendingBit(TIM6, TIM_IT_Update);
	TIM_ITConfig(TIM6, TIM_IT_Update, ENABLE);
	TIM_SetCounter(TIM6, 0); 
	TIM_Cmd(TIM6,ENABLE);
}
	//================================= config timer7 1ms ================================
void Config_int_time7(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	NVIC_InitStructure.NVIC_IRQChannel = TIM7_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE);
	TIM_TimeBaseInitStructure.TIM_Prescaler=50;//500;
	TIM_TimeBaseInitStructure.TIM_Period=999;//999;//1ms
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;//
	TIM_TimeBaseInit(TIM7, &TIM_TimeBaseInitStructure);

	TIM_ClearITPendingBit(TIM7, TIM_IT_Update);
	TIM_ITConfig(TIM7, TIM_IT_Update, ENABLE);
	TIM_SetCounter(TIM7, 0); 
	TIM_Cmd(TIM7,ENABLE);
}

//===================================PWM===========================================
void Config_pwm_time_t8(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	GPIO_InitTypeDef  GPIO_InitStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC|RCC_AHB1Periph_GPIOD, ENABLE);

	GPIO_PinAFConfig(GPIOC, GPIO_PinSource6, GPIO_AF_TIM8);// ch1
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource7, GPIO_AF_TIM8);// ch2
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource8, GPIO_AF_TIM8);// ch3
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource9, GPIO_AF_TIM8);// ch4

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode =GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType =GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOC, &GPIO_InitStructure);	

	//Fpwm=84000000/(TIM_Period*TIM_Prescaler);
	//50=84000000/(40*TIM_Prescaler);
	TIM_TimeBaseInitStructure.TIM_Prescaler=84000000/(2000*255); // fpwm=2khz
	TIM_TimeBaseInitStructure.TIM_Period=3000;
	//  TIM_TimeBaseInitStructure.TIM_Prescaler=186; // fpwm=4khz
	//  TIM_TimeBaseInitStructure.TIM_Period=10000;
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV2;//TIM_CKD_DIV2;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;//
	TIM_TimeBaseInit(TIM8, &TIM_TimeBaseInitStructure); 

	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

	TIM_Cmd(TIM8,ENABLE);
	TIM_SetCounter(TIM8, 0);
	//////////////	
	TIM_OC1Init(TIM8, &TIM_OCInitStructure);
	TIM_OC2Init(TIM8, &TIM_OCInitStructure);
	TIM_OC3Init(TIM8, &TIM_OCInitStructure);
	TIM_OC4Init(TIM8, &TIM_OCInitStructure);	  
	TIM_CtrlPWMOutputs(TIM8,ENABLE);

}

//===================================PWM TIME 5===========================================
void Config_pwm_time_t5(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	GPIO_InitTypeDef  GPIO_InitStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA|RCC_AHB1Periph_GPIOA, ENABLE);

	GPIO_PinAFConfig(GPIOA, GPIO_PinSource0, GPIO_AF_TIM5);// ch1
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource1, GPIO_AF_TIM5);// ch2
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_TIM5);// ch3
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_TIM5);// ch4

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode =GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType =GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);	

//	//Fpwm=84000000/(TIM_Period*TIM_Prescaler);
//	//50=84000000/(40*TIM_Prescaler);
	//TIM_TimeBaseInitStructure.TIM_Prescaler=84000000/(1000*255); // fpwm=2khz
	//TIM_TimeBaseInitStructure.TIM_Period=255;
	TIM_TimeBaseInitStructure.TIM_Prescaler=186; 
	TIM_TimeBaseInitStructure.TIM_Period=10000;
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;//
	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseInitStructure); 

	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

	TIM_Cmd(TIM5,ENABLE);
	TIM_SetCounter(TIM5, 0);
	//////////////	
	TIM_OC1Init(TIM5, &TIM_OCInitStructure);
	TIM_OC2Init(TIM5, &TIM_OCInitStructure);
	TIM_OC3Init(TIM5, &TIM_OCInitStructure);
	TIM_OC4Init(TIM5, &TIM_OCInitStructure);	  
	TIM_CtrlPWMOutputs(TIM5,ENABLE);

}



//============================ config pwm timer4 ================================
void Config_pwm_time_t4(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	GPIO_InitTypeDef  GPIO_InitStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD|RCC_AHB1Periph_GPIOA|RCC_AHB1Periph_GPIOC, ENABLE);

	GPIO_PinAFConfig(GPIOD, GPIO_PinSource12, GPIO_AF_TIM4); // ch1
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource13, GPIO_AF_TIM4);// ch2
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource14, GPIO_AF_TIM4);// ch3
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource15, GPIO_AF_TIM4);  //ch4

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_15|GPIO_Pin_13|GPIO_Pin_14;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	TIM_TimeBaseInitStructure.TIM_Prescaler=84000000/(2000*255); // fpwm=2khz
	TIM_TimeBaseInitStructure.TIM_Period=3000;
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV2;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;//
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseInitStructure);

	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_Cmd(TIM4,ENABLE);
	TIM_SetCounter(TIM4, 0);

	TIM_OC1Init(TIM4, &TIM_OCInitStructure);
	TIM_OC2Init(TIM4, &TIM_OCInitStructure);
	TIM_OC3Init(TIM4, &TIM_OCInitStructure);
	TIM_OC4Init(TIM4, &TIM_OCInitStructure);

}

//===========================PWM RC SECVOR==================================
void Config_pwm_time_t9(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_ICInitTypeDef TIM_ICInitStructure;
	GPIO_InitTypeDef  GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM9, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_TIM9);// ch2
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_TIM9);// ch1
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode =GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType =GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	TIM_TimeBaseInitStructure.TIM_Prescaler=0;
	TIM_TimeBaseInitStructure.TIM_Period=65535;
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;//
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseInitStructure);

	TIM_ICInitStructure.TIM_Channel=TIM_Channel_1|TIM_Channel_2;
	TIM_ICInitStructure.TIM_ICPolarity=TIM_ICPolarity_Rising;
	TIM_ICInitStructure.TIM_ICFilter=200;
	TIM_ICInitStructure.TIM_ICSelection=TIM_ICSelection_DirectTI;
	TIM_ICInit(TIM1, &TIM_ICInitStructure);	
	TIM_EncoderInterfaceConfig(TIM9, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
	TIM_ClearITPendingBit(TIM9, TIM_IT_Update);
	TIM_ITConfig(TIM9, TIM_IT_Update, ENABLE);
	TIM_Cmd(TIM1,ENABLE); 	
	TIM_SetCounter(TIM9, 0); 
}

//============================ config encoder timer2 && timer3 ===========================
void Config_encoder_timer2_timer3(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_ICInitTypeDef TIM_ICInitStructure;
	GPIO_InitTypeDef  GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOB, ENABLE);

	GPIO_PinAFConfig(GPIOA, GPIO_PinSource15, GPIO_AF_TIM2); // tim2
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource3, GPIO_AF_TIM2);

	GPIO_PinAFConfig(GPIOB, GPIO_PinSource4, GPIO_AF_TIM3); // tim3
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource5, GPIO_AF_TIM3);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;	
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	//  GPIO_InitStructure.GPIO_Pin = ;
	//  GPIO_Init(GPIOB, &GPIO_InitStructure);

	TIM_TimeBaseInitStructure.TIM_Prescaler=0;
	TIM_TimeBaseInitStructure.TIM_Period=65535;
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;//
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStructure);

	TIM_ICInitStructure.TIM_Channel=TIM_Channel_1|TIM_Channel_2;
	TIM_ICInitStructure.TIM_ICPolarity=TIM_ICPolarity_Falling;
	TIM_ICInitStructure.TIM_ICFilter=20;
	TIM_ICInitStructure.TIM_ICSelection=TIM_ICSelection_DirectTI;
	TIM_ICInit(TIM2, &TIM_ICInitStructure);
	TIM_ICInit(TIM3, &TIM_ICInitStructure);

	TIM_EncoderInterfaceConfig(TIM2, TIM_EncoderMode_TI12, TIM_ICPolarity_Falling, TIM_ICPolarity_Falling);
	TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12, TIM_ICPolarity_Falling, TIM_ICPolarity_Falling);

	TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);

	TIM_Cmd(TIM2,ENABLE); 
	TIM_Cmd(TIM3,ENABLE);

	TIM_SetCounter(TIM2, 0); 
	TIM_SetCounter(TIM3, 0);

	////////////
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	/* Enable the TIM3 gloabal Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 4;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}


//========================== config encoder timer 1 ================================
//========================== config encoder timer2 && timer3 ================================
void Config_encoder_timer1(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_ICInitTypeDef TIM_ICInitStructure;
	GPIO_InitTypeDef  GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE , ENABLE);


	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9|GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;	
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource9, GPIO_AF_TIM1); // tim5
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource11, GPIO_AF_TIM1);
	
	
	TIM_TimeBaseInitStructure.TIM_Prescaler=0;
	TIM_TimeBaseInitStructure.TIM_Period=65535;
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;//
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseInitStructure);

	TIM_ICInitStructure.TIM_Channel=TIM_Channel_1|TIM_Channel_2;
	TIM_ICInitStructure.TIM_ICPolarity=TIM_ICPolarity_Rising;
	TIM_ICInitStructure.TIM_ICFilter=10;
	TIM_ICInitStructure.TIM_ICSelection=TIM_ICSelection_DirectTI;
	TIM_ICInit(TIM1, &TIM_ICInitStructure);	
	TIM_EncoderInterfaceConfig(TIM1, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising, TIM_ICPolarity_Rising);
	TIM_ClearITPendingBit(TIM1, TIM_IT_Update);
	TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE);
	
		TIM_ClearITPendingBit(TIM1, TIM_IT_Update);

	TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE);
	
	TIM_Cmd(TIM1,ENABLE); 	
	TIM_SetCounter(TIM1, 0); 

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_TIM10_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

//---------------------------- KHAI BAO ENCODER TIMER 1-----------------------------
void Config_encoder_timer4(void)
{
 	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_ICInitTypeDef TIM_ICInitStructure;
  GPIO_InitTypeDef  GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD , ENABLE);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_13;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;	
  GPIO_Init(GPIOD, &GPIO_InitStructure);

	TIM_TimeBaseInitStructure.TIM_Prescaler=0;
  TIM_TimeBaseInitStructure.TIM_Period=65535;
  TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;//
  TIM_TimeBaseInit(TIM4, &TIM_TimeBaseInitStructure);
  
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource12, GPIO_AF_TIM4); // tim5
  GPIO_PinAFConfig(GPIOD, GPIO_PinSource13, GPIO_AF_TIM4);
	
  TIM_ICInitStructure.TIM_Channel=TIM_Channel_1|TIM_Channel_2;
  TIM_ICInitStructure.TIM_ICPolarity=TIM_ICPolarity_Falling;
  TIM_ICInitStructure.TIM_ICFilter=200;
  TIM_ICInitStructure.TIM_ICSelection=TIM_ICSelection_DirectTI;
  TIM_ICInit(TIM4, &TIM_ICInitStructure);	
  TIM_EncoderInterfaceConfig(TIM4, TIM_EncoderMode_TI12, TIM_ICPolarity_Falling, TIM_ICPolarity_Falling);
  TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
  TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);
  TIM_Cmd(TIM4,ENABLE); 	
  TIM_SetCounter(TIM4,0); 
   ///////////////////////////
		TIM4->EGR = 0;           // Generate an update event
    TIM4->CR1 = 1;           // Enable the counter
   /////////////////
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
  NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 4;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

//========================== config encoder timer2 && timer3 ================================
//---------------------- config encoder timer2 && timer3 ---------------------
//---------------------------- KHAI BAO ENCODER TIMER 1-----------------------------
void Config_encoder_timer5(void)
{
 	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_ICInitTypeDef TIM_ICInitStructure;
  GPIO_InitTypeDef  GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA , ENABLE);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;	
  GPIO_Init(GPIOA, &GPIO_InitStructure);

	TIM_TimeBaseInitStructure.TIM_Prescaler=0;
  TIM_TimeBaseInitStructure.TIM_Period=65535;
  TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;//
  TIM_TimeBaseInit(TIM5, &TIM_TimeBaseInitStructure);
  
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource0, GPIO_AF_TIM5); // tim5
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource1, GPIO_AF_TIM5);

		
  TIM_ICInitStructure.TIM_Channel=TIM_Channel_1|TIM_Channel_2;
  TIM_ICInitStructure.TIM_ICPolarity=TIM_ICPolarity_Falling;
  TIM_ICInitStructure.TIM_ICFilter=200;
  TIM_ICInitStructure.TIM_ICSelection=TIM_ICSelection_DirectTI;
  TIM_ICInit(TIM5, &TIM_ICInitStructure);	
  TIM_EncoderInterfaceConfig(TIM5, TIM_EncoderMode_TI12, TIM_ICPolarity_Falling, TIM_ICPolarity_Falling);
  TIM_ClearITPendingBit(TIM5, TIM_IT_Update);
  TIM_ITConfig(TIM5, TIM_IT_Update, ENABLE);
  TIM_Cmd(TIM5,ENABLE); 	
  TIM_SetCounter(TIM5,0); 
   ///////////////////////////
		TIM5->EGR = 0;           // Generate an update event
    TIM5->CR1 = 1;           // Enable the counter
   /////////////////
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
  NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 4;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}
//------------------------------------ config ADC DMA ----------------------------- 

//---------------------------- KHAI BAO ADC DMA----------------------------- 
void Config_ADC1_DMA(void)
{
  ADC_InitTypeDef       ADC_InitStructure;
  ADC_CommonInitTypeDef ADC_CommonInitStructure;
  DMA_InitTypeDef       DMA_InitStructure;
  GPIO_InitTypeDef      GPIO_InitStructure;

  /* Enable ADC3, DMA2 and GPIO clocks ****************************************/
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2 | RCC_AHB1Periph_GPIOA |RCC_AHB1Periph_GPIOB | RCC_AHB1Periph_GPIOC, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

  /* DMA2 Stream0 channel0 configuration **************************************/
  DMA_InitStructure.DMA_Channel = DMA_Channel_0;  
  DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)ADC1_DR_ADDRESS;
  DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)&_ADC1_Value;
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
  DMA_InitStructure.DMA_BufferSize = 14;
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;
  DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;         
  DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;
  DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
  DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
  DMA_Init(DMA2_Stream0, &DMA_InitStructure);
  DMA_Cmd(DMA2_Stream0, ENABLE);
// config_ngat_dma();// cau hinh ngat dma phai dat sau lenh enable kenh dma.

  /* Configure ADC1 Channel7 pin as analog input ******************************/
 
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
 
 
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
 
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
 
  /* ADC Common Init **********************************************************/
  ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;
  ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div8;
  ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;//ADC_DMAAccessMode_1;//
  ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;
  ADC_CommonInit(&ADC_CommonInitStructure);

  /* ADC3 Init ****************************************************************/
ADC_InitStructure.ADC_Resolution = ADC_Resolution_10b;//CH?NH DO PHAN GIAI
  ADC_InitStructure.ADC_ScanConvMode = ENABLE;
  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
  ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
  ADC_InitStructure.ADC_ExternalTrigConv =ADC_ExternalTrigConv_T1_CC1;
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
  ADC_InitStructure.ADC_NbrOfConversion = 14;
  ADC_Init(ADC1, &ADC_InitStructure);

  /* ADC3 regular channel7 configuration *************************************/ 
 ADC_RegularChannelConfig(ADC1, ADC_Channel_2, 1, ADC_SampleTime_480Cycles);	//A2
 ADC_RegularChannelConfig(ADC1, ADC_Channel_3, 2, ADC_SampleTime_480Cycles);	//A3
 ADC_RegularChannelConfig(ADC1, ADC_Channel_4, 3, ADC_SampleTime_480Cycles);	//A4
 ADC_RegularChannelConfig(ADC1, ADC_Channel_5, 4, ADC_SampleTime_480Cycles);	//A5
  ADC_RegularChannelConfig(ADC1, ADC_Channel_6, 5, ADC_SampleTime_480Cycles);	//A6
 ADC_RegularChannelConfig(ADC1, ADC_Channel_7, 6, ADC_SampleTime_480Cycles);	//A7
 
 ADC_RegularChannelConfig(ADC1, ADC_Channel_8, 7, ADC_SampleTime_480Cycles);	
 ADC_RegularChannelConfig(ADC1, ADC_Channel_9, 8, ADC_SampleTime_480Cycles);
 ADC_RegularChannelConfig(ADC1, ADC_Channel_10, 9, ADC_SampleTime_480Cycles);
 ADC_RegularChannelConfig(ADC1, ADC_Channel_11, 10, ADC_SampleTime_480Cycles);
 
  ADC_RegularChannelConfig(ADC1, ADC_Channel_12, 11, ADC_SampleTime_480Cycles);
 ADC_RegularChannelConfig(ADC1, ADC_Channel_13, 12, ADC_SampleTime_480Cycles);
 ADC_RegularChannelConfig(ADC1, ADC_Channel_14, 13, ADC_SampleTime_480Cycles);
 ADC_RegularChannelConfig(ADC1, ADC_Channel_15, 14, ADC_SampleTime_480Cycles); // cac so rank la so thu tu chuyen doi adc 

 /* Enable DMA request after last transfer (Single-ADC mode) */
  ADC_DMARequestAfterLastTransferCmd(ADC1, ENABLE);
//ADC_MultiModeDMARequestAfterLastTransferCmd(ENABLE);
  /* Enable ADC1 DMA */
  ADC_DMACmd(ADC1, ENABLE);

  /* Enable ADC1 */
  ADC_Cmd(ADC1, ENABLE);
 ADC_SoftwareStartConv(ADC1);
}

	//----------------------------------- config int uart1 ------------------------------
	void Config_int_uart1_rx(void)
	{
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;// 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; // muc do uu tien ngat thu 15
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;// cho phep su dung ngat
	NVIC_Init(&NVIC_InitStructure);  	// cau hinh cho bang vector ngat

}

//////////////////////////////////////////////////////////////////////////////////////////////////////
void UART1_DMA_RX(u32 baudrate)
{		
	DMA_InitTypeDef DMA_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);
	/*-------------------------- GPIO Configuration ----------------------------*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	/* Connect USART pins to AF */
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1);

	USART_InitStructure.USART_BaudRate = baudrate;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; 
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; 
	USART_Init(USART1, &USART_InitStructure); 
	USART_Cmd(USART1, ENABLE);

	/* Configure the Priority Group to 2 bits */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	/* Enable the UART4 RX DMA Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = DMA2_Stream2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	DMA_DeInit(DMA2_Stream2);
	DMA_InitStructure.DMA_Channel = DMA_Channel_4;
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory; // Receive
	DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)RX_USART1;
	DMA_InitStructure.DMA_BufferSize = 10;//(uint16_t)sizeof(Buffer);
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&USART1->DR;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Enable;
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single; 
	DMA_Init(DMA2_Stream2, &DMA_InitStructure); 
	/* Enable DMA Stream Half Transfer and Transfer Complete interrupt */
	USART_DMACmd(USART1, USART_DMAReq_Rx, ENABLE); // Enable USART Rx DMA Request
	DMA_ITConfig(DMA2_Stream2, DMA_IT_TC, ENABLE);  
	/* Enable the DMA RX Stream */
	DMA_Cmd(DMA2_Stream2, ENABLE);


}

//---------------------------- KHAI BAO UART 2-----------------------------
void UART2_DMA_TX(u32 baudrate)
{		
		DMA_InitTypeDef DMA_InitStructure;
		NVIC_InitTypeDef NVIC_InitStructure;
    USART_InitTypeDef USART_InitStructure;
		GPIO_InitTypeDef GPIO_InitStructure;
	 RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
   /*-------------------------- GPIO Configuration ----------------------------*/
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_6;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
   GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
   GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_Init(GPIOD, &GPIO_InitStructure);

   /* Connect USART pins to AF */
   GPIO_PinAFConfig(GPIOD, GPIO_PinSource5, GPIO_AF_USART2);
   GPIO_PinAFConfig(GPIOD, GPIO_PinSource6, GPIO_AF_USART2);
	

   USART_InitStructure.USART_BaudRate = baudrate;
   USART_InitStructure.USART_WordLength = USART_WordLength_8b;
   USART_InitStructure.USART_StopBits = USART_StopBits_1;
   USART_InitStructure.USART_Parity = USART_Parity_No;
   USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; 
   USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; 
   USART_Init(USART2, &USART_InitStructure); 
   USART_Cmd(USART2, ENABLE);


/////////////////////////////////
 /* Configure the Priority Group to 2 bits */
   NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
   /* Enable the UART4 RX DMA Interrupt */
   NVIC_InitStructure.NVIC_IRQChannel = DMA1_Stream6_IRQn;
   NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
   NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
   NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
   NVIC_Init(&NVIC_InitStructure);
	
	 DMA_DeInit(DMA1_Stream6);
   DMA_InitStructure.DMA_Channel = DMA_Channel_4;
   DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral; // Receive
   DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)DATA_SPEED;
   DMA_InitStructure.DMA_BufferSize =(uint16_t)sizeof(DATA_SPEED);//(uint16_t)sizeof(Buffer_SPEED)-1 ;
   DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&USART2->DR;
   DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
   DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
   DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
   DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
   DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
   DMA_InitStructure.DMA_Priority = DMA_Priority_High;
   DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Enable;
   DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
   DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
   DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single; 
   DMA_Init(DMA1_Stream6, &DMA_InitStructure); 
   /* Enable the USART Rx DMA request */
   USART_DMACmd(USART2, USART_DMAReq_Tx, ENABLE); 
   /* Enable DMA Stream Half Transfer and Transfer Complete interrupt */
   USART_DMACmd(USART2, USART_DMAReq_Tx, ENABLE); // Enable USART Rx DMA Request
	 DMA_ITConfig(DMA1_Stream6, DMA_IT_TC, ENABLE);  
   /* Enable the DMA RX Stream */
   DMA_Cmd(DMA1_Stream6, ENABLE);	

}

//============================================
void UART3_DMA_RX(u32 baudrate)
{		
		DMA_InitTypeDef DMA_InitStructure;
		NVIC_InitTypeDef NVIC_InitStructure;
    USART_InitTypeDef USART_InitStructure;
		GPIO_InitTypeDef GPIO_InitStructure;
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);
   /*-------------------------- GPIO Configuration ----------------------------*/
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
   GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
   GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_Init(GPIOD, &GPIO_InitStructure);
   /* Connect USART pins to AF */
   GPIO_PinAFConfig(GPIOD, GPIO_PinSource8, GPIO_AF_USART3);
   GPIO_PinAFConfig(GPIOD, GPIO_PinSource9, GPIO_AF_USART3);

   USART_InitStructure.USART_BaudRate = baudrate;
   USART_InitStructure.USART_WordLength = USART_WordLength_8b;
   USART_InitStructure.USART_StopBits = USART_StopBits_1;
   USART_InitStructure.USART_Parity = USART_Parity_No;
   USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; 
   USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; 
   USART_Init(USART3, &USART_InitStructure); 
   USART_Cmd(USART3, ENABLE);

/////////////////////////////////////////////	   
   
   /* Configure the Priority Group to 2 bits */
   NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
   /* Enable the UART4 RX DMA Interrupt */
   NVIC_InitStructure.NVIC_IRQChannel = DMA1_Stream1_IRQn;
   NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
   NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
   NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
   NVIC_Init(&NVIC_InitStructure);
	
	 DMA_DeInit(DMA1_Stream1);
   DMA_InitStructure.DMA_Channel = DMA_Channel_4;
   DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory; // Receive
   DMA_InitStructure.DMA_Memory0BaseAddr =  (uint32_t) rx_buf;
   DMA_InitStructure.DMA_BufferSize = 10;//(uint16_t)sizeof(Buffer);
   DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&USART3->DR;
   DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
   DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
   DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
   DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
   DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
   DMA_InitStructure.DMA_Priority = DMA_Priority_High;
   DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Enable;
   DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
   DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
   DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single; 
   DMA_Init(DMA1_Stream1, &DMA_InitStructure); 
   /* Enable the USART Rx DMA request */
   USART_DMACmd(USART3, USART_DMAReq_Rx, ENABLE); 
   /* Enable DMA Stream Half Transfer and Transfer Complete interrupt */
   USART_DMACmd(USART3, USART_DMAReq_Rx, ENABLE); // Enable USART Rx DMA Request
	 DMA_ITConfig(DMA1_Stream1, DMA_IT_TC, ENABLE);  
   /* Enable the DMA RX Stream */
   DMA_Cmd(DMA1_Stream1, ENABLE);	
}

//====================	========UART4=======================================
#define UART4_BUFFER_SIZE 8
vu8 RX_UART4[UART4_BUFFER_SIZE];

void UART4_DMA_RX(u32 baudrate)
{		
    DMA_InitTypeDef DMA_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    
    // C?u h?nh clock cho c?c ngo?i vi
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);

    // C?u h?nh GPIO gi? nguy?n
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    GPIO_PinAFConfig(GPIOC, GPIO_PinSource10, GPIO_AF_UART4);
    GPIO_PinAFConfig(GPIOC, GPIO_PinSource11, GPIO_AF_UART4);

    // C?u h?nh UART gi? nguy?n 
    USART_InitStructure.USART_BaudRate = baudrate;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(UART4, &USART_InitStructure);
    USART_Cmd(UART4, ENABLE);

    // C?u h?nh ng?t DMA
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    NVIC_InitStructure.NVIC_IRQChannel = DMA1_Stream2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3; 
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    // C?u h?nh DMA 
    DMA_DeInit(DMA1_Stream2);
    DMA_InitStructure.DMA_Channel = DMA_Channel_4;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
    DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)RX_UART4;
    DMA_InitStructure.DMA_BufferSize = UART4_BUFFER_SIZE;
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&UART4->DR;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal; // Thay d?i t? Circular sang Normal
    DMA_InitStructure.DMA_Priority = DMA_Priority_High;
    DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable; // Disable FIFO mode
    DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
    DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
    DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
    DMA_Init(DMA1_Stream2, &DMA_InitStructure);

    USART_DMACmd(UART4, USART_DMAReq_Rx, ENABLE);
	USART_DMACmd(UART4, USART_DMAReq_Tx, ENABLE);
DMA_ITConfig(DMA1_Stream2, DMA_IT_TC, ENABLE);
    DMA_Cmd(DMA1_Stream2, ENABLE);
}


uint8_t id_rb = 0;
uint8_t state_rb = 0;
uint8_t move = 0;
uint8_t action = 0;
uint8_t id_block = 0;

//------------------ Ðém data gui vê rôi thuc thi----------
int count_data_uart4 = 0;

#include <stdint.h>

#define QUEUE_SIZE 100   // tùy b?n ch?nh

typedef struct {
    uint8_t id_rb;
    uint8_t state_rb;
    uint8_t move;
    uint8_t action;
    uint8_t id_block;
} Packet_t;


// Hàng d?i FIFO
Packet_t packet_queue[QUEUE_SIZE];
uint16_t head = 0;   // v? trí thêm
uint16_t tail = 0;   // v? trí lay

uint8_t take_data_block = 0;   // block dang duoc thuc thi
uint8_t has_active_block = 0;  // 0: chua lay, 1: dang xu lý

// ham them data vao hang doi
void Queue_Push(uint8_t state, uint8_t move, uint8_t action, uint8_t id_block)
{
    if (count_data_uart4 >= QUEUE_SIZE) return;

    packet_queue[head].state_rb = state;
    packet_queue[head].move     = move;
    packet_queue[head].action   = action;
    packet_queue[head].id_block = id_block;

    head = (head + 1) % QUEUE_SIZE;
    count_data_uart4++;
}


int Queue_Peek(Packet_t *out)
{
    if (count_data_uart4 == 0)
        return 0;

    *out = packet_queue[tail];   // KHÔNG tang tail
    return 1;
}


/// ham xoa 1 data trong hang doi
int Queue_Pop(Packet_t *out)
{
    if (count_data_uart4 == 0)
        return 0;

    *out = packet_queue[tail];
    tail = (tail + 1) % QUEUE_SIZE;
    count_data_uart4--;

    return 1;
}


// ham hoan thanh data
void Finish_Current_Block(void)
{
    Packet_t dummy;
    Queue_Pop(&dummy);   // ? pop khi dã xong
    has_active_block = 0;
}


int block_pha = 0;
int co_vat_can = 1;
int id_dat_hop = 0;

//// nhat hop
int do_lech = 0;
int khoangcach = 0;
int nhat_dat_hop = 0;
	
void pha_khoi_r1(void); // ham gui data toi rb1


void ProcessReceivedData_2(void)
{
	uint8_t calc_checksum =
        (RX_UART4[0] +   // start
         RX_UART4[1] +   // id_rb
         RX_UART4[2] +   // state
         RX_UART4[3] +   // move
         RX_UART4[4] +   // action
         RX_UART4[5]) & 0xFF; // id_block
	
	
    // Check start & end
    if (RX_UART4[0] != 0x02) return;
    if (RX_UART4[7] != 0x03) return;

    // Tính checksum
    if (calc_checksum == RX_UART4[6])
    {
        id_rb    = RX_UART4[1];
        state_rb    = RX_UART4[2];
        move     = RX_UART4[3];
        action   = RX_UART4[4];
        id_block = RX_UART4[5];
			
			// trang thai ghep vu khi
			if (id_rb == 1 && state_rb == 2) {
					block_pha = id_block;
					pha_khoi_r1();
			}
			else if (id_rb == 2 && state_rb == 1) {
							co_vat_can = 0;
					}
			
			// trang thai vuot rung
			else if (id_rb == 2 && state_rb == 2 ) {
				 // Push vào FIFO
        Queue_Push(state_rb, move, action, id_block);
			}
			
			// trang lai len zone 3 dat hop
			else if (id_rb == 2 && state_rb == 3 ) {
						id_dat_hop = id_block;
			}
			
			// trang thai nhat hop tren zone 3
			else if (id_rb == 2 && state_rb == 4 ) {
						do_lech = move;
						khoangcach = action;
						nhat_dat_hop = id_block;
			}

			
    }
    else
    {
        // checksum sai ? dánh d?u l?i
				state_rb     = 0xFF;
        move     = 0xFF;
        action   = 0xFF;
        id_block = 0xFF;
    }
}

//========================================================================
//---------------------------- KHAI BAO UART 5-----------------------------
#define UART_BUFFER_SIZE 10
vu8 RX_USART5[UART_BUFFER_SIZE];


void UART5_DMA_TX(u32 baudrate)
{		
		DMA_InitTypeDef DMA_InitStructure;
		NVIC_InitTypeDef NVIC_InitStructure;
    USART_InitTypeDef USART_InitStructure;
		GPIO_InitTypeDef GPIO_InitStructure;
	 RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5, ENABLE);
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD|RCC_AHB1Periph_GPIOC, ENABLE);
   /*-------------------------- GPIO Configuration ----------------------------*/
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
   GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
   GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_Init(GPIOD, &GPIO_InitStructure);
	
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
   GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
   GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_Init(GPIOC, &GPIO_InitStructure);
	
   /* Connect USART pins to AF */
   GPIO_PinAFConfig(GPIOD, GPIO_PinSource2, GPIO_AF_UART5);
   GPIO_PinAFConfig(GPIOC, GPIO_PinSource12, GPIO_AF_UART5);
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

  /* Enable the UART5 TX DMA Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = DMA1_Stream7_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 5;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 5;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
	
	/* Enable the UART5 RX DMA Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = DMA1_Stream0_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 5;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 5;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);



   USART_InitStructure.USART_BaudRate = baudrate;
   USART_InitStructure.USART_WordLength = USART_WordLength_8b;
   USART_InitStructure.USART_StopBits = USART_StopBits_1;
   USART_InitStructure.USART_Parity = USART_Parity_No;
   USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; 
   USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; 
   USART_Init(UART5, &USART_InitStructure); 
   USART_Cmd(UART5, ENABLE);
	 


/////////////////////////////////////////////	   

  DMA_DeInit(DMA1_Stream7);

  DMA_InitStructure.DMA_Channel = DMA_Channel_4;
  DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral; // Transmit
  DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)Buffer_HMI;
  DMA_InitStructure.DMA_BufferSize =10 ;//(uint16_t)sizeof(Buffer_HMI)-1 ;
  DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&UART5->DR;
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;//DMA_Mode_Circular
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;//DMA_Priority_High;
  DMA_InitStructure.DMA_FIFOMode =DMA_FIFOMode_Disable;// DMA_FIFOMode_Enable;
  DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
  DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
  DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;

  DMA_Init(DMA1_Stream7, &DMA_InitStructure);
	
	/////////////////////////////////////////////	   

  DMA_DeInit(DMA1_Stream0);

  DMA_InitStructure.DMA_Channel = DMA_Channel_4;
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory; // Transmit
  DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)RX_USART5;
  DMA_InitStructure.DMA_BufferSize = 5 ;//(uint16_t)sizeof(Buffer_HMI)-1 ;
  DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&UART5->DR;
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;//DMA_Mode_Circular
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;//DMA_Priority_High;
  DMA_InitStructure.DMA_FIFOMode =DMA_FIFOMode_Disable;// DMA_FIFOMode_Enable;
  DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
  DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
  DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;

  DMA_Init(DMA1_Stream0, &DMA_InitStructure);

  /* Enable the USART Tx Rx DMA request */
  USART_DMACmd(UART5, USART_DMAReq_Tx, ENABLE);
	USART_DMACmd(UART5, USART_DMAReq_Rx, ENABLE);

  /* Enable DMA Stream Transfer Complete interrupt */
  DMA_ITConfig(DMA1_Stream7, DMA_IT_TC, ENABLE);
	DMA_ITConfig(DMA1_Stream0, DMA_IT_TC, ENABLE);

  /* Enable the DMA TX Stream */

	DMA_Cmd(DMA1_Stream7, ENABLE);
	DMA_Cmd(DMA1_Stream0, ENABLE);

}

/////////////////
////////////////////////////////////////////////////////////
#define UART_BUFFER_SIZE 8
vu8 RX_USART6[UART_BUFFER_SIZE];


void UART6_DMA_RX(u32 baudrate)
{		
		DMA_InitTypeDef DMA_InitStructure;
		NVIC_InitTypeDef NVIC_InitStructure;
    USART_InitTypeDef USART_InitStructure;
		GPIO_InitTypeDef GPIO_InitStructure;
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART6, ENABLE);
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);
   /*-------------------------- GPIO Configuration ----------------------------*/
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
   GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
   GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_Init(GPIOC, &GPIO_InitStructure);
   /* Connect USART pins to AF */
   GPIO_PinAFConfig(GPIOC, GPIO_PinSource6, GPIO_AF_USART6);
   GPIO_PinAFConfig(GPIOC, GPIO_PinSource7, GPIO_AF_USART6);

   USART_InitStructure.USART_BaudRate = baudrate;
   USART_InitStructure.USART_WordLength = USART_WordLength_8b;
   USART_InitStructure.USART_StopBits = USART_StopBits_1;
   USART_InitStructure.USART_Parity = USART_Parity_No;
   USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; 
   USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; 
   USART_Init(USART6, &USART_InitStructure); 
   USART_Cmd(USART6, ENABLE);

   /* Configure the Priority Group to 2 bits */
   NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
   /* Enable the UART4 RX DMA Interrupt */
   NVIC_InitStructure.NVIC_IRQChannel = DMA2_Stream1_IRQn;
   NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
   NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
   NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
   NVIC_Init(&NVIC_InitStructure);
	
    DMA_DeInit(DMA2_Stream1); 
   DMA_InitStructure.DMA_Channel = DMA_Channel_5;
   DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory; // Receive
   DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)RX_USART6;;
   DMA_InitStructure.DMA_BufferSize =UART_BUFFER_SIZE;//(uint16_t)sizeof(DATA_COLOR);
   DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&USART6->DR;
   DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
   DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
   DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
   DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	 
   DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;//DMA_Mode_Circular
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;//DMA_Priority_High;
  DMA_InitStructure.DMA_FIFOMode =DMA_FIFOMode_Disable;
   DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
   DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
   DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single; 
   DMA_Init(DMA2_Stream1, &DMA_InitStructure); 
   /* Enable DMA Stream Half Transfer and Transfer Complete interrupt */
   USART_DMACmd(USART6, USART_DMAReq_Rx, ENABLE); // Enable USART Rx DMA Request
	 USART_DMACmd(USART6, USART_DMAReq_Tx, ENABLE); // CONFIG TRUYEN LEN
	 
	 
	 DMA_ITConfig(DMA2_Stream1, DMA_IT_TC, ENABLE);
/* Enable the DMA RX Stream */
   DMA_Cmd(DMA2_Stream1, ENABLE);
	 

}

uint8_t id_rb_2 = 0;
uint8_t state_rb_2 = 0;
uint8_t move_2 = 0;
uint8_t action_2 = 0;
uint8_t id_block_2 = 0;
uint8_t do_lech_px_2 = 0;

void ProcessReceivedData(void)
{
	uint8_t calc_checksum =
        (RX_USART6[0] +   // start
         RX_USART6[1] +   // id_rb
         RX_USART6[2] +   // state
         RX_USART6[3] +   // move
         RX_USART6[4] +   // action
         RX_USART6[5]) & 0xFF; // id_block
	
	
    // Check start & end
    if (RX_USART6[0] != 0x02) return;
    if (RX_USART6[7] != 0x03) return;

    // Tính checksum
    

    if (calc_checksum == RX_USART6[6])
    {
        id_rb_2    = RX_USART6[1];
        state_rb_2    = RX_USART6[2];
        move_2     = RX_USART6[3];
        action_2   = RX_USART6[4];
        id_block_2 = RX_USART6[5];

//        // Push vào FIFO
//        Queue_Push(move, action, id_block);
			
					do_lech_px_2 = action_2;
			
    }
    else
    {
        // checksum sai ? dánh d?u l?i
        move_2     = 0xFF;
        action_2   = 0xFF;
        id_block_2 = 0xFF;
    }
}

//================================INT=========================================
void ngat_ngoai(void)   
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	NVIC_InitTypeDef  NVIC_InitStructure;
	EXTI_InitTypeDef  EXTI_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE); 
	/* Enable SYSCFG clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

	/* Configure PB5 PB6 pin as input floating */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_Init(GPIOD, &GPIO_InitStructure);

	/* Connect EXTI Line5, Line6 to PB5,PB6 pin */
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOD, EXTI_PinSource2);
	//   SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOD, EXTI_PinSource3);

	/* Configure EXTI Line5, Line6 */
	EXTI_InitStructure.EXTI_Line = EXTI_Line2 ;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;  
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);

	/* Enable and set EXTI Line5, Line6 Interrupt to the lowest priority */
	NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn  ;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

//------------------------------ send uart1 ------------------------

void SEND_UART(u8 _UART,u8 _GIA_TRI)
{
	if(_UART==1) 	  {  USART_SendData(USART1, (uint8_t) _GIA_TRI); 	while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET){} }
	else if(_UART==3) {  USART_SendData(USART3, (uint8_t) _GIA_TRI); 	while (USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET){} }
	else if(_UART==4) {  USART_SendData(UART4, (uint8_t) _GIA_TRI); 	while (USART_GetFlagStatus(UART4, USART_FLAG_TC) == RESET){} }
	else if(_UART==5) {  USART_SendData(UART5, (uint8_t) _GIA_TRI); 	while (USART_GetFlagStatus(UART5, USART_FLAG_TC) == RESET){} }
	else if(_UART==6) {  USART_SendData(USART6, (uint8_t) _GIA_TRI); 	while (USART_GetFlagStatus(USART6, USART_FLAG_TC) == RESET){} }
}

void pha_khoi_r1(void)
{
    uint8_t start    = 0x02;
    uint8_t id_rb    = 1;
    uint8_t state    = 2;
    uint8_t move     = 0;
    uint8_t action   = 0;
		uint8_t end_byte = 0x03;

    uint8_t checksum = (start + id_rb + state + move + action + block_pha) & 0xFF;

    SEND_UART(6, start);
    SEND_UART(6, id_rb);
    SEND_UART(6, state);
    SEND_UART(6, move);
    SEND_UART(6, action);
    SEND_UART(6, block_pha);
    SEND_UART(6, checksum);
    SEND_UART(6, end_byte);
}



//--------------------------- reset encoder doc -------------------------

void RESET_ENCODER_CHAY(void)
{
	TIM1->CNT = 0;num_over_t1 = 0;
	TIM4->CNT = 0;num_over_t4 = 0;
}
void RESET_ENCODER(void)
{
	TIM1->CNT = 0;num_over_t1 = 0;
	TIM2->CNT = 0;num_over_t2 = 0;
	TIM3->CNT = 0;num_over_t3 = 0;
	TIM4->CNT = 0;num_over_t4 = 0;
	TIM5->CNT = 0;num_over_t5 = 0;
}
void RESET_ENCODER_XOAY(void)
{
	TIM2->CNT = 0;num_over_t2 = 0;
}

void RESET_ENCODER_BAN(void)
{
	TIM3->CNT = 0;num_over_t3 = 0;
}

//-------------------------------- reset uart-----------------------------------------
void run_read_gyro_uart1(void)
{ 
	u32 i;
	en_gyro=0;
	for(i=0;i<2;i++)
	{
		SEND_UART(1,'a');
		delay_ms(50);
	}
	en_gyro=1;
	data_tx_gyro='z';
}

void run_read_gyro_uart3(void)
{ 
	u32 i;
	enGyro=0;
	for(i=0;i<2;i++)
	{
		SEND_UART(3,'a');
		delay_ms(50);
	}
	enGyro=1;
	dataTxGyro='z';
}

int da_lay_tay1 = 0;
int da_lay_tay2 = 0;
int da_lay_tay3 = 0;
int da_lay_tay4 = 0;
int da_lay_tay4_duoi = 0;
int hoan_thanh_chay_rung = 0;

extern int Xoay_ok;
int	KT_Ha_Tay;
int	KT_Ha_Tay_phai;
int KT_Ha_Tay_trai;
int nhay_den_lan_1 = 0;
int so_qua_tren_tay = 0;
uint8_t tay_1_co_qua = 0;
uint8_t tay_2_co_qua = 0;
uint8_t tay_3_co_qua = 0;
uint8_t tay_4_co_qua = 0;

uint8_t robot_position = 0;  // vi tri robot dat hop
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//---------------------------- TRUYEN DU LIEU VAO MANG-----------------------------
void HMI_TRAN(vs32 _so_dong)
{
		char*camera="11111111111111111111110111111111";
									vs32 _i,_chua_cac_bit=0;
									char _ghep_bit[40];
									char _chu_cac_bit[40];
									_ghep_bit[0]=0;
									_chu_cac_bit[0]=0;
							switch (_so_dong) {
										case 0:
										if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)){
											GPIO_WriteBit(GPIOC,GPIO_Pin_15,0);
											HMI_DMI("ROBOT 2 DANG CHAY SAN XANH:   ",	GPIO_ReadOutputDataBit(GPIOC,GPIO_Pin_15),0);
										}
										else{
											GPIO_WriteBit(GPIOC,GPIO_Pin_15,1);
											HMI_DMI("ROBOT 2 DANG CHAY SAN DO:   ",	GPIO_ReadOutputDataBit(GPIOC,GPIO_Pin_15),0);
										}		
										
										break;
									case 1:
										HMI_DMI("IMU:", -IMU,1);
										break;

									case 2:
										HMI_DMI("Tro chan Truoc: ",	bientrochantruocValue,2);
										break;
									case 3:
										HMI_DMI("Tro chan Sau:  ",bientrochansauValue,3);
										break;
									case 4:
										HMI_DMI("Tro xoay tay ",bientroxoaytayValue,4);
										break;

									case 5:
										HMI_DMI("Tro day tay 1 ",bientrodaytay1Value,5);
										break;
									case 6:
										HMI_DMI("Tro day tay 2 ",bientrodaytay2Value,6); 
										break;
									case 7:
										HMI_DMI("Lazer phai",lazePhaiValue,7); 
										break;
									case 8:
										HMI_DMI("Lazer trai ",lazeTraiValue,8);									
										break;
									case 9:
										HMI_DMI("Lazer sau",lazeSauValue,9); 
										break;
									case 10:
										HMI_DMI("Lazer truoc ",lazeTruocValue,10);  
										break;
									case 11:
										HMI_DMI("count_data_uart4 ",count_data_uart4,11);  
										break;
									case 12:
										HMI_DMI("ENCODER_FL ",ENCODER_FL(),12);
										break;
									case 13:
										HMI_DMI("ENCODER_FR ",ENCODER_FR(),13);
										break;
									case 14:
										HMI_DMI("tay_2_co_qua ",tay_2_co_qua,14);
										break;		
									case 15:
										HMI_DMI("Quang_tro_2 ",Quang_tro2,15);
										break;	
//									case 14:
//										HMI_DMI("Quang_tro_2 ",Quang_tro2,14);
//										break;		
//									case 15:
//										HMI_DMI("Quang_tro_3 ",Quang_tro3,15);
//										break;	
								  case 16:
									//	hien thi phan ngo vao

                                 snprintf(_ghep_bit, sizeof(_ghep_bit), "%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d",
                                    GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_8),
                                    GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_7),
                                    GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_10),
                                    GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_4),
                                    GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_12),
                                    GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_3),
                                    GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_13),
                                    GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_4),
                              
                                    GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_14),
                                    GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_3),
                                    GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_15),
                                    GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_2),
                                    GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_14),
                                    GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_1),
                                    GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_13),
                                    GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_0)

                              ); 
                                 

										HMI_PUTS("I:",_ghep_bit,16);
										break;
									case 17:
										// hien thi phan ngo ra

                              snprintf(_ghep_bit, sizeof(_ghep_bit), "%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d",
                                    GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_15),
                                    GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_8),
                                    GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_14),
                                    GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_14),
                                    GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_13),
                                    GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_11),
                                    GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_12),
                                    GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_10),
                              
                                    GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11),
                                    GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_11),
                                    GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_10),
                                    GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_12),
                                    GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_15),
                                    GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_6),
                                    GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0),
                                    GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_7)

                              ); 
										HMI_PUTS("in2:",_ghep_bit,17);
										break;	
									case 18:
										HMI_DMI("Quang_tro : ",Quang_tro,18); 
//										HMI_DMI("TinHieu_GapThang: ",TinHieu_ChuanBi_GapThang,18);  
										break;	
									case 19:
										HMI_DMI("co_vat_can ",co_vat_can,19);  
										break;	
									case 20:
										HMI_DMI("Lazer truoc ",lazeTruocValue,20);  
										break;	
//									case 19:
//										HMI_DMI("Quang_tro_2 ",Quang_tro2,19);  
//										break;	
//									case 20:
//										HMI_DMI("Quang_tro_3 ",Quang_tro3,20); 
//										break;	
//							
						}
}

//////////////////////////
void DATA_SPEED_RUN_LOOP()///TOC DO <254
	{int _k,_i;

	DMA_Cmd(DMA1_Stream6,ENABLE);
						
		}
	////////////////////////////////

void HMI_RUN_LOOP(vs32 _cause)
{
	if(HMI_LOOP>_cause)HMI_LOOP=0;
	else HMI_LOOP++;
	HMI_TRAN(HMI_LOOP);
}