#include <stdlib.h>
#include <math.h>
char SS_RL = 0, SS_RR = 0, SS_FR = 0, SS_FL = 0;

extern int Rear_Left_Wheel_Angle, Rear_Right_Wheel_Angle, Front_Left_Wheel_Angle, Front_Right_Wheel_Angle;
extern float _robotDirFL, _robotDirFR, _robotDirRL, _robotDirRR;
extern int Vi_tri;
int speed_temp = 0, speed, i;

int Home_Encoder_RL = 374, Home_Encoder_RR = 3402 , Home_Encoder_FL = 1248 , Home_Encoder_FR = 1290;
int	current_RL_Angle, current_RR_Angle, current_FL_Angle, current_FR_Angle;
//void veHome(){
//		int bien1 = 0, bien2 = 0, bien3 = 0, bien4 = 0;
//		int bienBuTruRR = 840, bienBuTruRL = 900, bienBuTruFR = 930, bienBuTruFL = 930 ;
//		while(!bien1 || !bien2 || !bien3 || !bien4){
//			mor_rotate_rear_left_back;
//			mor_rotate_rear_right_back;
//			mor_rotate_front_right_back;
//			mor_rotate_front_left_back
//			if(Home_Rear_Right) mor_rotate_rear_right_next = 20;
//			else Home_Rear_Right = 2, bien1 = 1;
//			
//			if(Home_Front_Left) mor_rotate_front_left = 20;
//			else mor_4hRo = 2, bien2 = 1;
//			
//			if(CB_8h) mor_8hRo = 20;
//			else mor_8hRo = 2, bien3 = 1;
//			
//			vTaskDelay(3);
//		}
//		for(i = 2; i<10; i++) RESET_ENCODER();
//		vTaskDelay(10);
//		bien1 = 0, bien2 = 0, bien3 = 0;
//		while(!bien1 || !bien2 || !bien3){
//			quayGoc0h(bienBuTru0h);
//			quayGoc4h(bienBuTru4h);
//			quayGoc8h(bienBuTru8h);
//			if(abs(ENCODER_0H() - bienBuTru0h) < 1) mor_0hRo = 2, bien1 = 1;
//			if(abs(ENCODER_4H() - bienBuTru4h) < 1) mor_4hRo = 2, bien2 = 1;
//			if(abs(ENCODER_8H() - bienBuTru8h) < 1) mor_8hRo = 2, bien3 = 1;
//			vTaskDelay(3);
//		}
//		mor_0hRo = 0;
//		mor_4hRo = 0;
//		mor_8hRo = 0;
//		for(i = 2; i<10; i++) RESET_ENCODER();
//		vTaskDelay(10);
//		bitVeHome = 0;
//	}

//************************************** dieu khien robot dung gamepad **************************************8
void robotGamePadControl(vu8 speedMin , vu8 speedMax)
{
	int tocdo = 20, td_x = 5;
	float tocdoXoay = 0;
	int rJoy_LR = (RJOY_LR >= 50 && RJOY_LR <= 200) ? 1 : 0;
//	int lJoy_LR = (LJOY_LR >= 5 && LJOY_LR <= 250) ? 1 : 0;

	if (!UP && !DOWN && !RIGHT && !LEFT && rJoy_LR && !LJOY)
	{				  // Khong dieu khien
		robotStop(0); // truot banh
		
		return;
	}
	/*_____________________________//___________________________*/

	/********************** TOC DO ****************************/
	/*_____________________________//___________________________*/
//	if (L1)
//		tocdo = speedMax, tocdoXoay = 1.2;
	 if(L1)
		tocdo = speedMax, tocdoXoay = 0.9;
	else
		tocdo = speedMin, tocdoXoay = 0.7;

	//--------- chay cac huong -----------
	if (UP && !DOWN && !RIGHT && !LEFT && !R1 && !R2)
		robotRun(0, tocdo);
	else if (!UP && DOWN && !RIGHT && !LEFT)
		robotRun(1800, tocdo);
	else if (!UP && !DOWN && RIGHT && !LEFT && !R1 && !R2)
		robotRun(900, tocdo);
	else if (!UP && !DOWN && !RIGHT && LEFT && !R1 && !R2)
		robotRun(-900, tocdo);

	else if (UP && !DOWN && RIGHT && !LEFT)
		robotRun(450, tocdo);
	else if (UP && !DOWN && !RIGHT && LEFT)
		robotRun(-450, tocdo);
	else if (!UP && DOWN && RIGHT && !LEFT)
		robotRun(1350, tocdo);
	else if (!UP && DOWN && !RIGHT && LEFT)
		robotRun(-1350, tocdo);

	//-------------- Dang chay va Khong chay nua, chi xoay ----------------
	if (!UP && !DOWN && !RIGHT && !LEFT && rJoy_LR  && robotIsRun() && !LJOY)
		robotStop(0);

	//-------------- Xoay ----------------
	if (rJoy_LR)
		robotRotateStop();
	else if (RJOY_LR < 50) 
	{
		if (robotIsRun())
			robotRotateFree(-tocdoXoay, 0);
		else		
			robotRotateFree(-tocdoXoay, 0);
	}
	else if (RJOY_LR > 200)
	{
		if (robotIsRun())
			robotRotateFree(tocdoXoay, 0);
		else
			robotRotateFree(tocdoXoay, 0);
		//			robotLineRunLeft(20);//
	}
	else
		robotRotateStop();
	
}



//************************************** home wheels ****************************************
vu8 Home_wheel_RL_Out(void)
{
	mor_rotate_rear_left_next;
	
	if(Home_Rear_Left == 1){	mor_rotate_rear_left = 2; return 1;}
	else										{	mor_rotate_rear_left = 100; return 0;}

}

vu8 Home_wheel_RL(void)
{
	mor_rotate_rear_left_next;
 	if(Home_Rear_Left == 1 && SS_RL == 0){
		mor_rotate_rear_left = 100; TIM3->CNT = 0; num_over_t3 = 0;return 0;
	}
	else if((abs(ENCODER_RL()) > Home_Encoder_RL) && SS_RL == 1){	
		mor_rotate_rear_left = 2 ;return 1;
	}
	else{
		mor_rotate_rear_left = 50; SS_RL = 1; return 0;
	}			
	
}

//************************************** home wheels ****************************************
vu8 Home_wheel_RR_Out(void)
{
	mor_rotate_rear_right_next;
	
	if(Home_Rear_Right == 1){	mor_rotate_rear_right = 2; return 1;}
	else										{	mor_rotate_rear_right = 100; return 0;}

}

vu8 Home_wheel_RR(void)
{
	
	if(Home_Rear_Right == 1 && SS_RR == 0)																{	mor_rotate_rear_right = 100; TIM4->CNT = 0; num_over_t4 = 0;return 0;}
	else if((abs(ENCODER_RR()) > Home_Encoder_RR) && SS_RR == 1)					{	mor_rotate_rear_right = 2 ;return 1;}
	else 																																	{	mor_rotate_rear_right = 50; SS_RR = 1; return 0;}	
	
}
//************************************** home wheels ****************************************
vu8 Home_wheel_FL_Out(void)
{
	mor_rotate_front_left_next;
	
	if(Home_Front_Left == 1){	mor_rotate_front_left = 2; return 1;}
	else										{	mor_rotate_front_left = 100; return 0;}

}

vu8 Home_wheel_FL(void)
{
	mor_rotate_front_left_next;
	if(Home_Front_Left == 1 && SS_FL == 0)															{	mor_rotate_front_left = 100; TIM2->CNT = 0; num_over_t2 = 0;return 0;}
	else if((abs(ENCODER_FL()) > Home_Encoder_FL) && SS_FL == 1)				{	mor_rotate_front_left = 2 ;return 1;}
	else 																																{	mor_rotate_front_left = 50; SS_FL = 1; return 0;}			
	
}

//************************************** home wheels ****************************************
vu8 Home_wheel_FR_Out(void)
{
	mor_rotate_front_right_next;
	
	if(Home_Front_Right == 1){	mor_rotate_front_right = 2; return 1;}
	else										{	mor_rotate_front_right = 100; return 0;}

}

vu8 Home_wheel_FR(void)
{
	
	if(Home_Front_Right == 1 && SS_FR == 0)																{	mor_rotate_front_right = 100; TIM5->CNT = 0; num_over_t5 = 0;return 0;}
	else if((abs(ENCODER_FR()) > Home_Encoder_FR) && SS_FR == 1)					{	mor_rotate_front_right = 2 ;return 1;}
	else 																																	{	mor_rotate_front_right = 50; SS_FR = 1; return 0;}	
	
}

//**************************************************** giu goc banh xe sau trai ***************************************************************************
void Rear_Left_Angle()
{
		if (abs(ENCODER_RL() - Rear_Left_Wheel_Angle) > 20)
	{
		if (ENCODER_RL() > Rear_Left_Wheel_Angle)
			mor_rotate_rear_left_back;
		else
			mor_rotate_rear_left_next;

		speed_temp = (abs(ENCODER_RL() - Rear_Left_Wheel_Angle) * 4);
		if (speed_temp > 250)
			speed_temp = 250;
		if (speed_temp < 150)
			speed_temp = 150;
		mor_rotate_rear_left = speed_temp;
	}
	else
		mor_rotate_rear_left = 2;
}

//**************************************************** giu goc banh xe sau phai ***************************************************************************
void Rear_Right_Angle()
{
		if (abs(ENCODER_RR() - Rear_Right_Wheel_Angle) > 20)
	{
		if (ENCODER_RR() > Rear_Right_Wheel_Angle)
			mor_rotate_rear_right_back;
		else
			mor_rotate_rear_right_next;

		speed_temp = (abs(ENCODER_RR() - Rear_Right_Wheel_Angle) * 4);
		if (speed_temp > 250)
			speed_temp = 250;
		if (speed_temp < 150)
			speed_temp = 150;
		mor_rotate_rear_right = speed_temp;
	}
	else
		mor_rotate_rear_right = 2;
}

//**************************************************** giu goc banh xe truoc trai ***************************************************************************
void Front_Left_Angle()
{
		if (abs(ENCODER_FL() - Front_Left_Wheel_Angle) > 20)
	{
		if (ENCODER_FL() > Front_Left_Wheel_Angle)
			mor_rotate_front_left_back;
		else
			mor_rotate_front_left_next;

		speed_temp = (abs(ENCODER_FL() - Front_Left_Wheel_Angle) * 4);
		if (speed_temp > 250)
			speed_temp = 250;
		if (speed_temp < 150)
			speed_temp = 150;
		mor_rotate_front_left = speed_temp;
	}
	else
		mor_rotate_front_left = 2;
}

//**************************************************** giu goc banh xe ***************************************************************************
void Front_Right_Angle()
{
		if (abs(ENCODER_FR() - Front_Right_Wheel_Angle) > 20)
	{
		if (ENCODER_FR() > Front_Right_Wheel_Angle)
			mor_rotate_front_right_back;
		else
			mor_rotate_front_right_next;

		speed_temp = (abs(ENCODER_FR() - Front_Right_Wheel_Angle) * 4);
		if (speed_temp > 250)
			speed_temp = 250;
		if (speed_temp < 150)
			speed_temp = 150;
		mor_rotate_front_right = speed_temp;
	}
	else
		mor_rotate_front_right = 2;
}