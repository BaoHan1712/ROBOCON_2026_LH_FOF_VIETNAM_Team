// #include "cmsis_os.h"

// 19h42 18 03 2023

#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include "LID_HMI.h"
#include "doc_tay_game.h"
#include "config.h"

//#include "3SwerveWheel_Vu.h"
#include "4OmniControler.h"
#include "FreeRTOS.h"
#include "task.h"
#include "DieuKhienCoCau.h"
 //#include "ROBOTRUN.h"
#include "BasicFunction.h"
#include "San_Xanh.h"
#include "San_Do.h"

int Vi_tri = 0;
int Man_xoay_tay = 0;
int Man_gat1 = 0;
int Man_gat2 = 0;

void USART1_SendChar(char c) {
    while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
    USART_SendData(USART1, c);
}
 
void USART1_SendHex(uint8_t v) {
    char buf[4];
    char *p;                     // khai báo p ở trên cùng
    sprintf(buf, "%02X ", v);
     p = buf;                     // gán sau
    for (; *p; p++) {
        USART1_SendChar(*p);
    }
}

static void taskGyro(void *pvParameters)
{
	while (1)
	{
		//-------------------------------------------------------------

		//-----------------------------------------------------------------
		HMI_RUN_LOOP(17);
		USART_Cmd(USART3, ENABLE);
		vTaskDelay(15);
	 }
} 
 
static void taskDieuKhienCoCau1(void *pvParameters)
{
 
	while (1)
	{
		ADCValue_Control();	
		Chan_truoc();
		Chan_sau();
		if(Man_xoay_tay == 0) Xoay_tay_kep(); 
		if(Man_gat1 == 0) Gat_1(); 
		if(Man_gat2 == 0) Gat_2(); 
//		Nang_ha_tay_kep();
//		Day_tay_kep();
		vTaskDelay(3);
	}
}

static void taskDieuKhienCoCau(void *pvParameters)
{

	while (1)
	{
		
		vTaskDelay(3);
	}
}

static void taskRobotAnalytics(void *pvParameters)
{
	while (1)
	{
		robotAnalytics();
		vTaskDelay(3);
	}
}
static void taskMain(void *pvParameters)
{
	Config_out_mode(); // khai b�o ngo ra cua mot chan bat ky
	Config_in_mode();  // khai bao ngo v�o cua mot chan bat ky
	// Config_pwm_time_t8();//cai dat timer8 o che do dieu xung
	//Config_pwm_time_t4(); // cai dat timer4 o che do dieu xung
	// Config_pwm_time_t9();//cai dat timer9 o che do RC SEVOR
	Config_encoder_timer2_timer3(); // doc encoder  timer 2, timer 3, timer 5 ,timer 9
	Config_encoder_timer1();
	Config_encoder_timer5();
	Config_encoder_timer4();
	// ngat_ngoai();			//chuy�n dung de doc sieu am ket hop timer7, hoac co the dung lam nut nh�n
	Config_ADC1_DMA(); // su dung  khi doc tin hieu laze hay cac t�n hieu ADC<3,3v
	// Config_int_time6();		//phuc vu cho chuong trinh hoat dong song song voi he thong v?i chu ky 1ms
	Config_int_time7();	  // su dung de doc sieu am, tang giam bien, ch�ng nhieu, v� c�c chuong tr�nh hoat dong khong song song voi he thong
	UART1_DMA_RX(115200); // usart giao tiep voi laban
	UART2_DMA_TX(115200); /// DIEU KHIEN DONG CO
	UART3_DMA_RX(115200); // usart giao tiep de doc gamepad
	UART4_DMA_RX(115200);	//SU DUNG DE GIAO TRUYEN UART
	UART5_DMA_TX(921600); // GIAO TIEP MAN HINH HMI
 
	// if (SysTick_Config(SystemCoreClock / 1000))while (1);// 1ms truyen du lieu usart den cac slever
	//UART6_DMA_RX(115200);
	
	// reset lai laban
	robotResetIMU();
	Vi_tri = 0;
	RESET_ENCODER(); 

////	target_kep = 610;
//	speed_tay_xoay = 100;
	//
	
//	target_day_kep = 500;
	

//	target_chan_truoc = 230;
//	target_chan_sau = 230;
	
//	tay_gat = 50,target_kep = 500;
//	for(i=0;i<250;i++)	
//	{
//		while(bientronangtayValue < 495)	{vTaskDelay(5); if(wantExit())	break;}
//	}
//	tay_xoay = 50,target_tay_kep = 500;
//	//-----------------------------------
	xTaskCreate(taskRobotAnalytics, (signed char *)"taskRobotAnalytics", 256, NULL, 0, NULL);
	xTaskCreate(taskDieuKhienCoCau, (signed char *)"taskDieuKhienCoCau", 256, NULL, 0, NULL);
	xTaskCreate(taskDieuKhienCoCau1, (signed char *)"taskDieuKhienCoCau1", 256, NULL, 0, NULL);

vTaskDelay(1000);
	
//	Tay1_len_on;
//	Tay1_xuong_on;
//	Kep_phai_4_ra;
//	Tay1_len;
//	Tay2_len;
//	Kep_phai_3_ra;
//	Kep_phai_2_ra;
//	Kep_phai_1_ra;

	
//	XI_LANH_KEP_MO;
//	XI_LANH_HA_KEP;
//	0
//	
	speed_chan_sau = 40;
	speed_chan_truoc = 60;

	target_chan_truoc = bientrochantruocValue;
	target_chan_sau = bientrochansauValue;

	speed_tay_xoay = 100;
	target_xoay_tay = vi_tri_tay_43;
	
	speed_tay_gat1 = 250;
	target_tay_gat1 = vitri_tay1home;
	
	speed_tay_gat2 = 250;
	target_tay_gat2 = vitri_tay2home;
	
	RESET_ENCODER(); 
	
	
	while (1)
	{ 
	
		while(SHARE) 
		{	
			
			robotGamePadControl(5,30);
			Nang_Ha_tay1_Manual(); 
			Nang_Ha_tay2_Manual();
			Xoay_tay_Manual();
			go_qua();
			
//			if(quangTroValue < 30)					Kep = 250;
			if(OPTIONS) vehome();
			if(CHON_SAN == 0)									//SAN DO
			{
				
				//Init_Action_Table_san_do(); 
//				if(O && L2 && !R2 && Vi_tri == 0)								Xuat_Phat_Lay_Vu_Khi_Do(31,1800),Vi_tri = 1 ;
//				if(TRIANGLE && L2 && !R2 && Vi_tri == 0)				Xuat_Phat_Lay_Vu_Khi_Do(52,1800),Vi_tri = 1;
//				if(SQUARE && L2 && !R2 && Vi_tri == 0)					Xuat_Phat_Lay_Vu_Khi_Do(71,-1750),Vi_tri = 1;
//				if(O && L2 && !R2 && Vi_tri == 1)								Vao_rung_mai_1_san_Do();

			
			}
			else															//SAN XANH
			{
					Init_Action_Table_san_xanh(); 
//				if(X && L2 && !R2)							Ktra_vtri_kep3();
//				if(SQUARE && L2 && !R2)					su_dung_chan(580);
//				if(O && L2 && !R2)								Tay1_len;
//				if(TRIANGLE&& L2 && !R2)					Test_gap();
//			if(O && L2 && !R2 && Vi_tri == 0)								Xuat_Phat_Lay_Vu_Khi_Xanh(171,-1700),Vi_tri = 1 ;
//			if(TRIANGLE && L2 && !R2 && Vi_tri == 0)				Xuat_Phat_Lay_Vu_Khi_Xanh(205,1800),Vi_tri = 1;
//			if(SQUARE && L2 && !R2 && Vi_tri == 0)					Xuat_Phat_Lay_Vu_Khi_Xanh(229,1700),Vi_tri = 1;
//			if(TRIANGLE && !L2 && R2) 								
//			{		speed_chan_sau = 40;
//				speed_chan_truoc = 60;

//				target_chan_truoc = 350;
//				target_chan_sau = 350;
////			}
//				if(TRIANGLE && L2 && !R2) 												Run_All_Blocks_From_Queue_san_xanh();
//				if(SQUARE && L2 && !R2) 													qua_trai_len_bac_400();
//				if ( X && L2 && !R2 ) 														qua_phai_len_bac_200_cua_vao();	
//				if ( O && L2 && !R2 ) 														qua_phai_len_bac_400();	
////Leo_bac_200
//Leo_bac_400		
//Xuong_bac_400		
			if(TRIANGLE && L2 && !R2) 													tudonghoantoan();
//			if(SQUARE && L2 && !R2) 														dat_qua_tay_1_2_xanh();
//			if ( X && L2 && !R2 ) 														chinh_lai_vi_tri_laser_sau(50, 50);
//			if ( O && L2 && !R2 ) 														test_tay_duoi();
// Vao_rung_mai_1_xanh(310); tay 41, 262 tay 23
//Vao_rung_mai_2_xanh(460);  phai 410
// Vao_rung_mai_3_xanh(308); tay 41, 371 tay  23
////  VI TRI LAZER CUA RUNG (note)
// chuan_bi_gap_phai_200_tren
		}
			
		// tay 1 : 365, tay 2 : 365,mam : 603, lz trai 165, lz sau 52, 
		}
			
//		if(quangTroValue < 30)					Kep = 250;
		//else														XI_LANH_KEP_DONG;
		robotStop(0);
	}
}
int main(void)
{
    xTaskCreate(taskMain, (signed char *)"taskMain", 256, NULL, 0, NULL);
    xTaskCreate(taskGyro, (signed char *)"taskGyro", 256, NULL, 0, NULL);

    vTaskStartScheduler(); 
}
