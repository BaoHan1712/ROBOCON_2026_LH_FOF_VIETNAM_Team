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
#include "BasicFunction.h"
#include "San_Xanh.h"
#include "San_Do.h"
#include "module_san_Do.h"

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
		HMI_RUN_LOOP(40);
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

		vTaskDelay(3);
	}
}

static void taskDieuKhienCoCau(void *pvParameters)
{

	while (1)
	{
		if(KT_Ha_Tay == 1)							kiem_tra_huong_ha_tay_gap_phia_truoc(); // thang 200 tren
		if(KT_Ha_Tay_Trc_200_Duoi == 1)	kiem_tra_huong_ha_tay_gap_phia_truoc_duoi(); // thang 200 duoi
		if(KT_Ha_Tay_Trc_400 == 1)			kiem_tra_huong_ha_tay_gap_phia_truoc_400(); // thang 400 tren
		
		if(KT_Ha_Tay_phai == 1)					kiem_tra_huong_ha_tay_gap_ben_phai();
		if(KT_Ha_Tay_trai == 1)					kiem_tra_huong_ha_tay_gap_ben_trai();
		
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
	//Config_encoder_timer1();
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
//	UART6_DMA_RX(115200);
	
	//Config_ADC1_DMA(); // su dung  khi doc tin hieu laze hay cac t�n hieu ADC<3,3v
	
	// reset lai laban
	robotResetIMU();
	Vi_tri = 0;
	RESET_ENCODER(); 

	
//	//-----------------------------------
	xTaskCreate(taskRobotAnalytics, (signed char *)"taskRobotAnalytics", 256, NULL, 0, NULL);
	xTaskCreate(taskDieuKhienCoCau, (signed char *)"taskDieuKhienCoCau", 256, NULL, 0, NULL);
	xTaskCreate(taskDieuKhienCoCau1, (signed char *)"taskDieuKhienCoCau1", 256, NULL, 0, NULL);

vTaskDelay(1000);
	
	Nang_thuong();

	target_chan_truoc = bientrochantruocValue;
	target_chan_sau = bientrochansauValue;
	
	target_tay_gat1 = bientrodaytay1Value;
	target_tay_gat2 = bientrodaytay2Value;

	speed_tay_xoay = 120;
	target_xoay_tay = vi_tri_tay_43;
	
	speed_tay_gat1 = 120;
	target_tay_gat1 = vitri_tay1home;
	
	speed_tay_gat2 = 120;
	target_tay_gat2 = vitri_tay2home;
	
	RESET_ENCODER();
	vehome_xuat_phat();
	
	
	while (1)
	{ 

		while(SHARE) 
		{	
//			
			robotGamePadControl(8,40);
			Nang_Ha_tay1_Manual(); 
			Nang_Ha_tay2_Manual();
			Xoay_tay_Manual();
			go_qua();
		
			if(OPTIONS) vehome();
		
			
			if(quangTroValue < 120)					Tay_kep_mo;
			if(CHON_SAN == 0)									//SAN DO
			{
				
				Init_Action_Table_san_do(); 
				bat_dau_chay_do();
				
////			if(TRIANGLE && L2 && !R2 )												Xuat_Phat_Lay_Vu_Khi_Do(152,1350,210);
//				if(TRIANGLE && L2 && !R2 )												bieu_dien();
				
//////				
					if(TRIANGLE && L2 && !R2 )												su_dung_chan(720);
					if(SQUARE && L2 && !R2) 													RESET_ENCODER(); 
					if(X && L2 && !R2) 																Tay2_len;
//					if(O && L2 && !R2 ) 																Kep_phai_3_ra;
				
				
//					if(TRIANGLE && L2 && !R2 )											tu_dong_dat_tang2_do();
//					if(SQUARE && L2 && !R2) 												Leo_bac_200(900, -900);
//					if(X && L2 && !R2) 															Xuong_bac_200(900, -900);
//					if(O && L2 && !R2 ) 														Xuong_bac_400(900, -900);


	
			}
			else															//SAN XANH
			{
				Init_Action_Table_san_xanh(); 
				bat_dau_chay_xanh();
				
//			if(O && L2 && !R2)															Xuat_Phat_Lay_Vu_Khi_Xanh(163, -1700, 205); chon_o_retry3();

					if(TRIANGLE && L2 && !R2 )												nhat_hop_zone3_xanh();
					if(SQUARE && L2 && !R2) 													chon_o_retry3();
//					if(X && L2 && !R2) 																su_dung_chan(490);
//					if(O && L2 && !R2 ) 															Tay1_len;

		
				
//					if(TRIANGLE && L2 && !R2) 											tu_dong_dat_tang2_xanh();
////					if(SQUARE && L2 && !R2) 											test_vitri_3();
//					if ( X && L2 && !R2 ) 																test_xoay();
//					if(O && L2 && !R2) 																		tu_dong_dat_tang2_xanh();
		
////Leo_bac_400
//Xuong_bac_200	(-900, 900)	
////Xuong_bac_400	
 ///auto_vao_rung_xanh_cua1(); tay 41, 262 tay 23
//Vao_rung_mai_2_xanh(460);  phai 410
// Vao_rung_mai_3_xanh(308); tay 41, 371 tay  23
////  VI TRI LAZER CUA RUNG (note)
// chuan_bi_gap_phai_200_tren
// kiem_tra_so_qua_tren_tay();
		}
			
}


		robotStop(0);
	}
}
	
int main(void)
{
    xTaskCreate(taskMain, (signed char *)"taskMain", 256, NULL, 0, NULL);
    xTaskCreate(taskGyro, (signed char *)"taskGyro", 256, NULL, 0, NULL);

    vTaskStartScheduler(); 
}
