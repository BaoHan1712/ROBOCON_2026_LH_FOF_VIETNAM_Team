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
		//tinhLucBan(lazeTraiValue);
		//luu_bien_laze();
		//updateLazeValue();
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
	// UART4_DMA_RX(115200);	//SU DUNG DE GIAO TIEP MACH DO LAI
	UART5_DMA_TX(921600); // GIAO TIEP MAN HINH HMI
	// if (SysTick_Config(SystemCoreClock / 1000))while (1);// 1ms truyen du lieu usart den cac slever
//	UART6_DMA_RX(115200);
	
	// reset lai laban
	robotResetIMU();
	Vi_tri = 0;
	RESET_ENCODER(); 

	target_chan_truoc = 320;
	target_chan_sau = 320;
	//-----------------------------------
	xTaskCreate(taskRobotAnalytics, (signed char *)"taskRobotAnalytics", 256, NULL, 0, NULL);
	xTaskCreate(taskDieuKhienCoCau, (signed char *)"taskDieuKhienCoCau", 256, NULL, 0, NULL);
	xTaskCreate(taskDieuKhienCoCau1, (signed char *)"taskDieuKhienCoCau1", 256, NULL, 0, NULL);

	//target_chan_truoc = 220;
	//target_chan_sau = 795;

	while (1)
	{ 
		while(SHARE) 
		{	

				robotGamePadControl(7,40);
		
			//if(O)	target_chan_truoc = 220, target_chan_sau = 800;
			//if(O)					target_chan_truoc = 720, target_chan_sau = 300;
			
			
//			if(X &&R2) target_chan_truoc = 220, target_chan_sau = 805;
//				
//				if(TRIANGLE && !L2) target_chan_truoc = 700;
//				if(O && !L2) target_chan_truoc = 460;
//				if(X && !L2) target_chan_truoc = 220;
//			
//				if(TRIANGLE && L2) target_chan_sau = 330;
//				if(O && L2) target_chan_sau = 560;
//				if(X && L2) target_chan_sau = 805;
			//if(SQUARE && R2 && !L2) 		target_chan_truoc = 685, target_chan_sau = 685;
			if(SQUARE && R2) 		target_chan_truoc = 618, target_chan_sau = 640; // tay_kep
			if(O && R2) 				target_chan_truoc = 460, target_chan_sau = 460;
			if(TRIANGLE && R2 && !L2)	target_chan_truoc = 230, target_chan_sau = 230;
			
			if(TRIANGLE && !R2 && !L2)
			{
				//Leo_bac_200();	
				lane_trai();
				//XI_LANH_KEP_DONG;
			}
			if(X && !R2 && !L2)
			{
				//Leo_bac_400();
				lane_giua();
				//XI_LANH_KEP_MO;
			}
			if(SQUARE && !R2 && !L2)
			{
				//Xuong_bac_200();
				lane_phai();
				//XI_LANH_NANG_KEP;
			}
			if(O && !R2 && !L2)
			{
				//Xuong_bac_400();
				XI_LANH_HA_KEP;
			}
			if(TRIANGLE && L2 && !R2)
			{
				Xuat_Phat_Lay_Vu_Khi_1();
				//XI_LANH_NANG_KEP;
			}  
			if(SQUARE && L2 && !R2)
			{
				Xuat_Phat_Lay_Vu_Khi_2();
				//XI_LANH_HA_KEP;
			} 
			if(X && L2 && !R2)
			{
				Xuat_Phat_Lay_Vu_Khi_3();
				
			} 
			if(O && L2 && !R2)
			{
				Xuat_Phat_Lay_Vu_Khi_4();
				
			} 
			
			
		
//			if(TRIANGLE && !X)		
//			{
//				mor_lift_front = 150; mor_lift_front_up;
//				mor_lift_rear = 250; mor_lift_rear_up;
//			}
//			else	if(!TRIANGLE && X)		
//			{
//				mor_lift_front = 150; mor_lift_front_down;
//				mor_lift_rear = 250; mor_lift_rear_down;
//			}
//			else
//			{
//				mor_lift_front = 0;
//				mor_lift_rear = 0;	
//			}
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