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

#include "3SwerveWheel_HanBao.h"
//#include "3SwerveWheel_Vu.h"
//#include "4OmniControler.h"
#include "FreeRTOS.h"
#include "task.h"
#include "DieuKhienCoCau.h"
 //#include "ROBOTRUN.h"
#include "BasicFunction.h"
#include "San_Xanh.h"
#include "San_Do.h"


int Vi_tri, Man_ra_vao = 0, Man_nang_ha = 0;

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
		if(Man_nang_ha == 0)	Nang();
		if(Man_ra_vao == 0)		Taykfs();
		
		
		vTaskDelay(3);
	}
}

static void taskDieuKhienCoCau(void *pvParameters)
{

	while (1)
	{
		
//		Rear_Left_Angle();
//		Rear_Right_Angle();
//		Front_Left_Angle();
//		Front_Right_Angle();
		
		Angle_0h();
		Angle_4h();
		Angle_8h();
//		
		vTaskDelay(3);
	}
}

static void taskRobotAnalytics(void *pvParameters)
{
	while (1)
	{
		Curent_angle_4_wheel();
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
	//Config_encoder_timer8();
	// ngat_ngoai();			//chuy�n6 dung de doc sieu am ket hop timer7, hoac co the dung lam nut nh�n
	Config_ADC1_DMA(); // su dung  khi doc tin hieu laze hay cac t�n hieu ADC<3,3v
	// Config_int_time6();		//phuc vu cho chuong trinh hoat dong song song voi he thong v?i chu ky 1ms
	Config_int_time7();	  // su dung de doc sieu am, tang giam bien, ch�ng nhieu, v� c�c chuong tr�nh hoat dong khong song song voi he thong
	UART1_DMA_RX(115200); // usart giao tiep voi laban
	UART2_DMA_TX(115200); /// DIEU KHIEN DONG CO
	UART3_DMA_RX(115200); // usart giao tiep de doc gamepad
	UART4_DMA_RX(115200);	//SU DUNG DE GIAO TIEP MACH DO LAI
	UART5_DMA_TX(921600); // GIAO TIEP MAN HINH HMI
	// if (SysTick_Config(SystemCoreClock / 1000))while (1);// 1ms truyen du lieu usart den cac slever
	UART6_DMA_RX(115200);
	
	// reset lai laban
	robotResetIMU();
	
//	//---- reset he thong ve vi tri ban dau

while(!Home_wheel_0h_Out() | !Home_wheel_4h_Out() | !Home_wheel_8h_Out());
while(!Home_wheel_0h()| !Home_wheel_4h() | !Home_wheel_8h());

//while(!Home_wheel_4h_Out());
//while(!Home_wheel_4h());

//	while(!Home_wheel_RL_Out() | !Home_wheel_RR_Out() | !Home_wheel_FR_Out() | !Home_wheel_FL_Out());
//	while(!Home_wheel_RL() | !Home_wheel_RR() | !Home_wheel_FR() | !Home_wheel_FL());
//////	
//	while(!Home_wheel_FR_Out());
//	while(!Home_wheel_FR());
//	while(!Home_wheel_FL_Out());
//	while(!Home_wheel_FL());
	Vi_tri = 0;
	RESET_ENCODER(); 


	//-----------------------------------
	xTaskCreate(taskRobotAnalytics, (signed char *)"taskRobotAnalytics", 256, NULL, 0, NULL);
	xTaskCreate(taskDieuKhienCoCau, (signed char *)"taskDieuKhienCoCau", 256, NULL, 0, NULL);
	xTaskCreate(taskDieuKhienCoCau1, (signed char *)"taskDieuKhienCoCau1", 256, NULL, 0, NULL);
	
	
	vTaskDelay(1503);

target_taykfs = BienTroTaykfsValue;
target_nang = BienTroNangValue;

//nang = 70;
//	

	while (1)
	{ 
		while(SHARE) 
		{			
			robotGamePadControl(30,45);		
			//Take_Next_Block_From_Queue();
			if (!R1 && !L2 && SQUARE && CB_Dau == 0) 
				{ if(L1)	Chot_gay = 150,Chot_gay_vao;
					else Chot_gay = 40,Chot_gay_vao;
				}
			else if (!R1 && !L2 && O && CB_Lay_Gay == 0 )			
				{ if(L1)	Chot_gay = 150,Chot_gay_ra;
					else Chot_gay = 40,Chot_gay_ra;
				}
			else	Chot_gay = 0;
			
			Ra_vao_tay_lay_KFS();
			Nang_Ha_Manual();
	
			if (LJOY && !L1 && !L2) Quang_tro = 250,Quang_tro_off;
			else			Quang_tro = 0,Quang_tro_off;
//			if (LJOY && !L1 && !L2) leodocdo();
			Cylinder_Tay_Day();
			Cylinder_Tay_Kep();
			Cylinder_Xoay_Kep();
			Hut_nha_KFS();
			Lay_KFS_Tu_Dong();
			if(LEFT && R1)		Bac_kfs(553,161);
			if(UP && R1)			Bac_kfs(725,150);
			if(RIGHT && R1)		Bac_kfs(955,166);

			if(O && !R1 && R2)	speed_nang = 250,target_nang = 785;
				
			if(O && L2 && !R2)		can_tam_robot(do_lech_px_2);
				
			if(OPTIONS)	Ve_home();
			if(CHON_SAN == 1)
			{
//			if (LJOY && L1)	Cua_goc_xanh_1();
			if (RJOY && Vi_tri == 0)	Xuat_Phat_Lay_Gay_vtr1_Xanh(38), Vi_tri = 1;
			if (RJOY && Vi_tri == 1)	Xuat_Phat_Lay_Gay_vtr2_Xanh(38);
//				if (RJOY)  testxanh();
//			if(SQUARE && L2 && !R2)					DatKFS_Xanh(16,150,150);
//			if(TRIANGLE && L2 && !R2)				DatKFS_Xanh(82,100,200);
//			if(O && L2 && !R2)							DatKFS_Xanh(148,100,300);
//			if(UP && R2)				chaytudong_esp_now_san_xanh(); //// chay tu dong san xanh
//			if(LEFT && R2)			vtri1vs2xanh(438,389,725,150);;

			}
			else
			{
				if (RJOY && Vi_tri == 0)				Xuat_Phat_Lay_Gay_vtri1_Do(39), Vi_tri = 1; 
				if (RJOY && Vi_tri == 1)				Xuat_Phat_Lay_Gay_vtri2_Do(39); 
//				if(SQUARE && L2 && !R2)					DatKFSDo(15,150,120);
//				if(TRIANGLE && L2 && !R2)				DatKFSDo(80,100,150);
//				if(O && L2 && !R2)							DatKFSDo(145,100,220);
//				if (RJOY)  testdo();				
//				if(UP && R2)				chaytudong_esp_now_san1(); //// chay tu dong san red			
////				if(LEFT && R2)			vtri11do(725,150);
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