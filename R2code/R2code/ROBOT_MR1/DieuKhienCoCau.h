//*****************************8 bien toan cuc *************************************
char xl_truot_lua, xl_kep_lua_tren, xl_kep_lua_duoi, xl_nang_lua,gt_kep_bong;
int vi_tri = 0, Cbcc = 0, Cbnv = 0, Cbnn = 0,vt_xl_nang_lua = 0;
char	On_Off_Ban = 0;
int xl_ban_bong = 0;
int Nang_vong_max = 322, Nang_vong_min = 105, i;
int Nang_goc_max = 540, Nang_goc_min = 300;
int touchpad_press =0;
int laybong =0;
int en_tru = 60;
int max_speed = 10;
int speed_tay_lua = 100;
int speed_xoay = 200;

int xl_kepbong_state = 0;
int xl_nangkep_state = 0;
int ban_bong_state=0 ;

//extern vu8 update;
extern speed_temp;
extern vu8	Cam;
extern float	JTL;
int state_nang = 1;
int state_ha = 1;

int	Min_chan_truoc = 215, Max_chan_truoc = 692, target_chan_truoc;
int	Min_chan_sau = 215, Max_chan_sau = 702, target_chan_sau;
int	Min_xoay_tay = 332, Max_xoay_tay = 710, target_xoay_tay;

int	speed_chan_sau, speed_chan_truoc,speed_tay_xoay;
int home_trc,home_sau;

int force_F;
int final_force;
float result;

extern int Man_xoay_tay;

void robotLineRunLeft(vu8 speed);
void robotLineRunRight(vu8 speed);

	
void Bam_thanh_laser_trai(int speed, int runangle, int AngleHead, int lazer_stable_phai, int num_change_stable, int fix_max,int rat);
void Bam_thanh_laser_phai(int speed, int runangle, int AngleHead, int lazer_stable_phai, int num_change_stable, int fix_max,int rat);




//**********************************************************************
//void banxoay(void)
//{	int tocdo;
//	if(L2) tocdo = 20;
//	else	tocdo = 7;
//	
//	 if (SQUARE)													  Mor_CamRotate = tocdo, Mor_CamRotate_next;
//	 else if (O) 	                          Mor_CamRotate = tocdo, Mor_CamRotate_back;
//	 else	                                        Mor_CamRotate = 2;
//}


//void nangcam(void)
// {

//	if (!R1&&TRIANGLE)													state_nang = 1, state_ha = 0, target_Nang_Ha = 165;
//	if (!R1&&X)
//	{ 					 
//				target_Nang_Ha = 610 ;
//	 }
//	 else if(state_ha == 0&& target_Nang_Ha == 610 && BienTroNongBanValue > 595) 
//			{
//				state_nang = 0;
//				state_ha = 1;
//			 }	 
// }

//void Nang_Ha_Nong_Ban(void)
//{
//	if (R1 && X && (taget_BT_Xoay < Max_BT_Xoay))
//		taget_BT_Xoay++, vTaskDelay(300);
//	else if (R1 && TRIANGLE && (taget_BT_Xoay > Min_BT_Xoay))
//		taget_BT_Xoay--, vTaskDelay(400);
//}


//====================================================================================


// char CB_line_trai, CB_line_phai, Nho_trai_truoc, Nho_trai_sau, Nho_phai_truoc, Nho_phai_truoc;
//void robotGamePadControl(vu8 speedMin, vu8 speedMax)
//{
//	int tocdo = 20, td_x = 5;
//	float tocdoXoay = 0;
//	int rJoy_LR = (RJOY_LR >= 5 && RJOY_LR <= 250) ? 1 : 0;
//	int lJoy_LR = (LJOY_LR >= 5 && LJOY_LR <= 250) ? 1 : 0;

//	if (UP && DOWN && RIGHT && LEFT && rJoy_LR)
//	{				  // Khong dieu khien
//		robotStop(0); // truot banh

//		return;
//	}
//	/*_____________________________//___________________________*/

//	/********************** TOC DO ****************************/
//	/*_____________________________//___________________________*/
//	if (!L1)
//		tocdo = speedMax, tocdoXoay = 0.5;
//	else
//		tocdo = speedMin, tocdoXoay = 0.3;

//	//--------- chay cac huong -----------
//	if (!UP && DOWN && RIGHT && LEFT && L2)
//		robotRun(0, tocdo);
//	else if (UP && !DOWN && RIGHT && LEFT && L2)
//		robotRun(1800, tocdo);
//	else if (UP && DOWN && !RIGHT && LEFT && L2)
//		robotRun(900, tocdo);
//	else if (UP && DOWN && RIGHT && !LEFT && L2)
//		robotRun(-900, tocdo);

//	else if (!UP && DOWN && !RIGHT && LEFT && L2)
//		robotRun(450, tocdo);
//	else if (!UP && DOWN && RIGHT && !LEFT && L2)
//		robotRun(-450, tocdo);
//	else if (UP && !DOWN && !RIGHT && LEFT && L2)
//		robotRun(1350, tocdo);
//	else if (UP && !DOWN && RIGHT && !LEFT && L2)
//		robotRun(-1350, tocdo);

//	//-------------- Dang chay va Khong chay nua, chi xoay ----------------
//	if (UP && DOWN && RIGHT && LEFT && !rJoy_LR && lJoy_LR && robotIsRun())
//		robotStop(0);

//	//-------------- Xoay ----------------
//	if (rJoy_LR)
//		robotRotateStop();
//	else if (RJOY_LR < 5) 
//	{
//		if (robotIsRun())
//			robotRotateFree(tocdoXoay, 0);
//		else
//			robotRotateFree(tocdoXoay, 0);
//	}
//	else if (RJOY_LR > 250)
//	{
//		if (robotIsRun())
//			robotRotateFree(-tocdoXoay, 0);
//		else
//			robotRotateFree(-tocdoXoay, 0);
//		//			robotLineRunLeft(20);//
//	}

//	else
//		robotRotateStop();
//}

//////-------------------------------------------------------------
void ADCValue_Control(void)
{
	// khai bao lazer
	static unsigned int lazeSauCouter = 0, lazeSau_SUM = 0;
	static unsigned int lazeTruocCouter = 0, lazeTruoc_SUM = 0;
	static unsigned int lazePhaiCouter = 0, lazePhai_SUM = 0;
	static unsigned int lazeTraiCouter = 0, lazeTrai_SUM = 0;
	static unsigned int QuangtroCouter = 0, Quangtro_SUM = 0;
	static unsigned int lazeTruocNhoCouter = 0, lazeTruocNho_SUM = 0;

	// Bien tro vi tri co cau
	static unsigned int bientromamxoayCouter = 0, bientromamxoay_SUM = 0;
	static unsigned int bientrochansauCouter = 0, bientrochansau_SUM = 0;
	static unsigned int bientrochantruocCouter = 0, bientrochantruoc_SUM = 0;
	static unsigned int bientroxoaytayCouter = 0, bientroxoaytay_SUM = 0;
	static unsigned int bientrodaytayCouter = 0, bientrodaytay_SUM = 0;
	static unsigned int bientronangtayCouter = 0, bientronangtay_SUM = 0;
	
	int cam_bien_laze_truoc_mapping = 0;
	////----------------TINH TOAN LAZER---------------
//	if (lazeSauCouter++ < 100)
//	{
//		lazeSau_SUM += cam_bien_laze_sau;
//	}
//	else
//	{
//		lazeSauValue = lazeSau_SUM / 100;
//		lazeSauCouter = 0;
//		lazeSau_SUM = 0;
//	}
	//------------------------------ laze truoc --------------
	if (lazeTruocCouter++ < 70)
	{
//		cam_bien_laze_truoc_mapping = (int)(10.02023 * cam_bien_laze_truoc + 183.290118);
//		lazeTruoc_SUM += cam_bien_laze_truoc_mapping;
			lazeTruoc_SUM += cam_bien_laze_truoc;
	}
	else
	{
		lazeTruocValue = lazeTruoc_SUM / 70;

		lazeTruocCouter = 0;
		lazeTruoc_SUM = 0;
	}


	//------------------------------ laze phai--------------
	if (lazePhaiCouter++ < 70)
	{
		lazePhai_SUM += cam_bien_laze_phai;
	}
	else
	{
		lazePhaiValue = lazePhai_SUM / 70;
		lazePhaiCouter = 0;
		lazePhai_SUM = 0;
	}
	//------------------------------ laze truoc nho --------------
	if (lazeTruocNhoCouter++ < 70)
	{
		lazeTruocNho_SUM += cam_bien_laze_truoc_nho;
	}
	else
	{
		lazeTruocNhoValue = lazeTruocNho_SUM / 70;
		lazeTruocNhoCouter = 0;
		lazeTruocNho_SUM = 0;
	}
	//----------------------------------------- laze trai -------------
	if (lazeTraiCouter++ < 70)
	{
		lazeTrai_SUM += cam_bien_laze_trai;
	}
	else
	{
		lazeTraiValue = lazeTrai_SUM / 70;
		lazeTraiCouter = 0;
		lazeTrai_SUM = 0;
	}
	//----------------------------------------- laze sau-------------
	if (QuangtroCouter++ < 50)
	{
		Quangtro_SUM += Quang_tro;
	}
	else
	{
		quangTroValue = Quangtro_SUM / 50;
		QuangtroCouter = 0;
		Quangtro_SUM = 0;
	}
	//-----------------TINH TOAN BIEN TRO---------------

//	if (bientromamxoayCouter++ < 10)
//	{
//		bientromamxoay_SUM += bien_tro_nong_ban;
//	}
//	else
//	{
//		BienTroNongBanValue = bientromamxoay_SUM / 10;
//		bientromamxoayCouter = 0;
//		bientromamxoay_SUM = 0;
//	}
	//-----------------------------------
	if (bientrochansauCouter++ < 50)
	{
		bientrochansau_SUM += bien_tro_chan_sau;
	}
	else
	{
		bientrochansauValue = bientrochansau_SUM / 50;
		bientrochansauCouter = 0;
		bientrochansau_SUM = 0;
	}
	//-----------------------------
	if (bientrochantruocCouter++ < 50)
	{
		bientrochantruoc_SUM += bien_tro_chan_truoc;
	}
	else
	{
		bientrochantruocValue = bientrochantruoc_SUM / 50;
		bientrochantruocCouter = 0;
		bientrochantruoc_SUM = 0;
	}


	//-----------------------------
	if (bientroxoaytayCouter++ < 50)
	{
		bientroxoaytay_SUM += bien_tro_xoay_tay;
	}
	else
	{
		bientroxoaytayValue = bientroxoaytay_SUM / 50;
		bientroxoaytayCouter = 0;
		bientroxoaytay_SUM = 0;
	}

}


//	if (taget_BT_Nong_Ban < Min_BT_Nong_Ban)
//		taget_BT_Nong_Ban = Min_BT_Nong_Ban;
//	if (taget_BT_Nong_Ban > Max_BT_Nong_Ban)
//		taget_BT_Nong_Ban = Max_BT_Nong_Ban;

//	if (abs(BienTroNongBanValue - taget_BT_Nong_Ban) > 1)
//	{
//		if (BienTroNongBanValue > taget_BT_Nong_Ban)
//			Cylinder_back;
//		else
//			Cylinder_next;

//		speed_temp = abs(BienTroNongBanValue - taget_BT_Nong_Ban)*10;
//		if (speed_temp > 250) // 50
//			speed_temp = 250;
//		if (speed_temp < 50) 
//			speed_temp = 50;

//		Cylinder = speed_temp;
//	}
//	else
//		Cylinder = 0;
//}



//void Xoay_Nong_Ban()
//{
//	if (target_BT_Xoay < Min_BT_Xoay )
//		target_BT_Xoay = Min_BT_Xoay;
//	if (target_BT_Xoay > Max_BT_Xoay)
//		target_BT_Xoay = Max_BT_Xoay;

//	if (abs(BienTroXoayValue - target_BT_Xoay) > 2)
//	{
//		if (BienTroXoayValue > target_BT_Xoay)
//			Mor_CamRotate_back;
//		else
//			Mor_CamRotate_next;

//		speed_temp = abs(BienTroXoayValue - target_BT_Xoay);
//		if (speed_temp > 70) // 50
//			speed_temp = 70;
//		if (speed_temp < 8) 							
//			speed_temp = 8;
//		Mor_CamRotate = speed_temp;
//	}
//	else
//		Mor_CamRotate = 0;
//}

//void Nang_Ha_Nong_Ban_abs(void)
//{
//	if (R1 && X && (taget_BT_Nong_Ban < Max_BT_Nong_Ban))
//		taget_BT_Nong_Ban++, vTaskDelay(300);
//	else if (R1 && TRIANGLE && (taget_BT_Nong_Ban > Min_BT_Nong_Ban))
//		taget_BT_Nong_Ban--, vTaskDelay(300);
//}

////***************************** xoay nong ban bang tay **************************************
////void Xoay_nong_ban(vu8 speed)
////{
////	if(R1 && SQUARE)					Mor_CamRotate = speed, Mor_CamRotate_next;
////	else	if(R1 && O)					Mor_CamRotate = speed, Mor_CamRotate_back;
////	else											Mor_CamRotate = 2;
////}
//void Xoay_nong (void)
//{
//	if (R1 && O && (target_BT_Xoay < Max_BT_Xoay))
//		target_BT_Xoay++, vTaskDelay(500);
//	else if (R1 && SQUARE && (target_BT_Xoay > Min_BT_Xoay))
//		target_BT_Xoay--, vTaskDelay(500);
//}


void Chan_truoc()
{
//		if(BienTroNongBanValue < taget_BT_Xoay - 5 ){
//			Cylinder = 0;
//			return;
//		}
	
	if (target_chan_truoc < Min_chan_truoc)
		target_chan_truoc = Min_chan_truoc;
	if (target_chan_truoc > Max_chan_truoc)
		target_chan_truoc = Max_chan_truoc;

	if (abs(bientrochantruocValue - target_chan_truoc) > 5)
	{
		if (bientrochantruocValue > target_chan_truoc)	mor_lift_front_down;
		else																						mor_lift_front_up;

		speed_temp = abs(bientrochantruocValue - target_chan_truoc)*3;
//		if (speed_temp > 170)
//				speed_temp = 170;
		if (speed_temp > speed_chan_truoc)
				speed_temp = speed_chan_truoc;
		if (speed_temp < 30)
				speed_temp = 30;
		
		mor_lift_front = speed_temp;
	}
	else mor_lift_front = 0;
}


void Chan_sau()
{
	if (target_chan_sau < Min_chan_sau)
		target_chan_sau = Min_chan_sau;
	if (target_chan_sau > Max_chan_sau)
		target_chan_sau = Max_chan_sau;

	if (abs(bientrochansauValue - target_chan_sau) > 5)
	{
		if (bientrochansauValue > target_chan_sau)			mor_lift_rear_down;
		else																						mor_lift_rear_up;

		speed_temp = abs(bientrochansauValue - target_chan_sau)*3;
		if (speed_temp > speed_chan_sau)
				speed_temp = speed_chan_sau;
		if (speed_temp < 20)
				speed_temp = 20;
		
		mor_lift_rear = speed_temp;
	}
	else mor_lift_rear = 0;
}

//************************************** xoay tay kep auto **************************************
	void Xoay_tay_kep()
{
	if (target_xoay_tay < Min_xoay_tay)
		target_xoay_tay = Min_xoay_tay;
	if (target_xoay_tay > Max_xoay_tay)
		target_xoay_tay = Max_xoay_tay;

	if ((abs(bientroxoaytayValue - target_xoay_tay) > 2) && CB_tay1_giua == 0 && CB_tay2_giua == 0 && CB_tay3_giua == 0)
	{
		if (bientroxoaytayValue > target_xoay_tay)			tay_xoay_thuan;
		else																						tay_xoay_nghich;

		speed_temp = abs(bientroxoaytayValue - target_xoay_tay);
		if (speed_temp > speed_tay_xoay)
				speed_temp = speed_tay_xoay;
		if (speed_temp < 50)
				speed_temp = 50;
	
		tay_xoay = speed_temp;
	}
	else tay_xoay = 0;
}

//******************************** leo bac 200 ****************************
void Leo_bac_200(void)
{	
		int i;
			// nâng bánh trc lên 
	speed_chan_sau = 115;
	speed_chan_truoc = 140;
	
	target_chan_truoc = 468;
	target_chan_sau = 468;
	
 	for(i=0;i<50;i++)		
	{
		while(bientrochantruocValue < 464)	{vTaskDelay(1); if(!wantExit())	break;}
	}
	
		for(i=0;i<250;i++)	
	{	
		while(CB_Ha_Dau == 0)	{vTaskDelay(1); if(!wantExit())	break;} 
	}
	
//	robotRun(0,10);
	robotRunAngle(-900,15,-900,0.2);
	
	for(i=0;i<250;i++)	
	{	
		while(CB_Ha_Dau == 1)	{vTaskDelay(1); if(!wantExit())	break;}
	}
//	
	RESET_ENCODER(); 
	
	while(ENCODER_RR() + ENCODER_RL() < 237)	{vTaskDelay (1); if(!wantExit())	break;}
	
	robotStop(0);
//////	
	target_chan_truoc = 223;
	for(i=0;i<50;i++)		
	{
		while(bientrochantruocValue > 228)	{vTaskDelay(1); if(!wantExit())	break;}
	}
	
//	// nâng bánh sau lên 
	target_chan_sau = 505;
	robotRunAngle(-900,12,-900,0.2);
	
	for(i=0;i<550;i++)	
	{	
		while(CB_bung == 1)	{vTaskDelay(1); if(!wantExit())	break;}
	}
	speed_chan_truoc = 40;
	target_chan_truoc = 250;
	RESET_ENCODER(); 
	
	while(ENCODER_FR() + ENCODER_FL() < 390)	{vTaskDelay (1); if(!wantExit())	break;}

	robotStop(0);
//////	
	target_chan_sau = 232;

	for(i=0;i<250;i++)	
	{
		while(bientrochansauValue > 240)	{vTaskDelay(1); if(!wantExit())	break;}
	}
	
	robotRunAngle(-900,7,-900,0.2);
	RESET_ENCODER(); 
	
	while(ENCODER_FR() + ENCODER_FL() < 950)	{vTaskDelay (5); if(!wantExit())	break;}
	
	speed_chan_sau = 40;
	target_chan_sau = 280;
	
		for(i=0;i<250;i++)	
	{
		while(bientrochansauValue < 273)	{vTaskDelay(1); if(!wantExit())	break;}
	}
	
	robotRunAngle(-900,7,-900,0.2);
	for(i=0;i<150;i++) 
	{
		while(CB_Ha_Sau == 1)		{vTaskDelay(1); if(!wantExit())	break;}
	
}
	
	
	robotStop(0);
	speed_chan_sau = 100;
	speed_chan_truoc = 140;
	
	target_chan_truoc = 260, target_chan_sau = 260;
}

//***************** leo bac 200 bam thanh laser phai va laser truoc *************

void Leo_bac_200_bam_thanh_phai(void)
{	

//////	
Leo_bac_200();
// **** leo xong bam thanh phai
	
	for(i=0;i<1000;i++)	
	{
		while(lazeTruocValue > 25)	
			{	
					Bam_thanh_laser_phai(7,-900,-880,12,2,550,50);
						if(!wantExit())	break;
			}
	}
	
		for(i=0;i<1000;i++)	
	{
		while(lazeTruocNhoValue > 148)	
			{	
					Bam_thanh_laser_phai(7,-900,-880,12,2,550,50);
						if(!wantExit())	break;
			}
	}
	robotStop(0);
	speed_chan_sau = 100;
	speed_chan_truoc = 140;
	target_chan_truoc = 300, target_chan_sau = 300;
}

// ************* leo bac 200 bam thanh phai encoder *************
void Leo_bac_200_bam_thanh_phai_encoder(void)
{	
	Leo_bac_200();
		
// **** leo xong bam thanh phai dua vao encoder
	
	for(i=0;i<1000;i++)	
	{
		while(CB_Ha_Dau == 0 )	
			{	
					Bam_thanh_laser_phai(7,-900,-880,12,2,550,50);
					vTaskDelay(1);
					if(!wantExit())	break;
			}
	}
	
	robotStop(0);
	
	robotRunAngle(900,5,-900,0.2);
	
	RESET_ENCODER();
	
	while(abs(ENCODER_RR()) + abs(ENCODER_RL()) < 150)	
	{	
		//Bam_thanh_laser_phai(7,-900,-880,10,2,650,30);
		vTaskDelay (1); if(!wantExit())	break;
	}
	robotStop(0);

}

/// ***************leo xong bam thanh trai encoder ****************

void Leo_bac_200_bam_thanh_trai_encoder(void)
{	
	Leo_bac_200();
		
// **** leo xong bam thanh phai dua vao encoder
	
	for(i=0;i<1000;i++)	
	{
		while(CB_Ha_Dau == 0 )	
			{	
					Bam_thanh_laser_trai(7,-900,-880,42,2,550,50);
					vTaskDelay(1);
					if(!wantExit())	break;
			}
	}
	
	robotStop(0);
	
	robotRunAngle(900,5,-900,0.2);
	
	RESET_ENCODER();
	
	while(abs(ENCODER_RR()) + abs(ENCODER_RL()) < 150)	
	{	
		//Bam_thanh_laser_phai(7,-900,-880,10,2,650,30);
		vTaskDelay (1); if(!wantExit())	break;
	}
	robotStop(0);

}

//***************** leo bac 200 bam thanh laser trai + laser truoc *************

void Leo_bac_200_bam_thanh_trai(void)
{	
Leo_bac_200();
// **** leo xong bam thanh trai
	
	for(i=0;i<1000;i++)	
	{
		while(lazeTruocValue > 25)	
			{	
					Bam_thanh_laser_trai(7,-900,-880,42,2,550,50);
						if(!wantExit())	break;
			}
	}
	
		for(i=0;i<1000;i++)	
	{
		while(lazeTruocNhoValue > 148)	
			{	
					Bam_thanh_laser_trai(7,-900,-880,42,2,550,50);
						if(!wantExit())	break;
			}
	}
	robotStop(0);
	speed_chan_sau = 100;
	speed_chan_truoc = 140;
	target_chan_truoc = 300, target_chan_sau = 300;
}

//******************************** leo bac 400 ****************************
void Leo_bac_400(void)
{	
	int i;
	
	speed_chan_sau = 100;
	speed_chan_truoc = 140;
	
	target_chan_truoc = 690, target_chan_sau = 690;
	
	for(i=0;i<250;i++)	
	{
		while(bientrochantruocValue < 680)	{vTaskDelay(5); if(!wantExit())	break;}
	}
	robotStop(0);
	robotRunAngle(-900,10,-900,0.2);
	
	for(i=0;i<550;i++)	
	{	
		while(CB_Ha_Dau == 1)	{vTaskDelay(1); if(!wantExit())	break;}
	}

	RESET_ENCODER(); 
	
	while(ENCODER_RR() + ENCODER_RL() < 450)	{vTaskDelay (5); if(!wantExit())	break;}
	
	robotStop(0); 
//////	
	target_chan_truoc = 223;
	
	for(i=0;i<50;i++)		
	{
		while(bientrochantruocValue > 228)	{vTaskDelay(5); if(!wantExit())	break;}
	}
	
	robotStop(0);
	target_chan_sau = 703;
	robotRunAngle(-900,10,-900,0.2);
	RESET_ENCODER(); 
	
	while(ENCODER_FR() + ENCODER_FL() < 1200)	{vTaskDelay (5); if(!wantExit())	break;}

	robotStop(0);
	robotRunAngle(-900,15,-900,0.2);
	
	for(i=0;i<550;i++)	
	{	
		while(CB_bung == 1)	{vTaskDelay(1); if(!wantExit())	break;}
	}
	speed_chan_truoc = 30;
	target_chan_truoc = 270;

	RESET_ENCODER(); 
	while(ENCODER_RR() + ENCODER_RL() < 460)	{vTaskDelay (5); if(!wantExit())	break;}

	robotStop(0);
//////	
	target_chan_sau = 232;
	for(i=0;i<250;i++)	
	{
		while(bientrochansauValue > 235)	{vTaskDelay(5); if(!wantExit())	break;}
	}
	robotStop(0);
	
	robotRunAngle(-900,7,-900,0.2);
	RESET_ENCODER(); 
	
	while(ENCODER_FL() + ENCODER_FR() < 950)	{vTaskDelay (5); if(!wantExit())	break;}
	
	speed_chan_sau = 40;
	target_chan_sau = 290;
	
	for(i=0;i<250;i++)	
	{
		while(bientrochansauValue < 277)	{vTaskDelay(1); if(!wantExit())	break;}
	}
	
	
	robotRunAngle(-900,7,-900,0.2);
//	robotRun(0,20);
	
	for(i=0;i<150;i++) 
	{
		while(CB_Ha_Sau == 1)		{vTaskDelay(1); if(!wantExit())	break;}
	}

////	
	robotStop(0);
	speed_chan_sau = 50;
	speed_chan_truoc = 50;
	
	target_chan_truoc = 300, target_chan_sau = 300;
}

////******************************** xuong bac 200 ****************************88
void Xuong_bac_200(void)
{	
	int i;
	speed_chan_sau = 100;
	speed_chan_truoc = 130;
	
	target_chan_truoc = 245, target_chan_sau = 245;
	
	for(i=0;i<250;i++)	
	{
		while(CB_Ha_Dau == 1)	{vTaskDelay(5); if(!wantExit())	break;}
	}
	
	robotRunAngle(-900,7,-880,-0.2);

	for(i=0;i<250;i++)
	{	
		while(CB_Ha_Dau == 0)	{vTaskDelay(5); if(!wantExit())	break;}
	}

	RESET_ENCODER();
	
	while(abs(ENCODER_RR()) + abs(ENCODER_RL()) < 1400)	{vTaskDelay (1); if(!wantExit())	break;}
	
	robotStop(0);

	target_chan_truoc = 475;
	
		for(i=0;i<250;i++)	
	{
		while(bientrochantruocValue < 470)	{vTaskDelay(5); if(!wantExit())	break;}
	}
		robotStop(0);

	robotRunAngle(-900,7,-880,-0.2);
	
	for(i=0;i<550;i++)	
	{	
		while(CB_bung == 0)	{vTaskDelay(1); if(!wantExit())	break;}
	}
	RESET_ENCODER(); 
	
	while(ENCODER_FR() + ENCODER_FL() < 2150)	{vTaskDelay (1); if(!wantExit())	break;}
	
	robotStop(0);

	target_chan_sau = 475;
	
	for(i=0;i<250;i++)	
	{
		while(bientrochansauValue < 470)	{vTaskDelay(5); if(!wantExit())	break;}
	}
	robotStop(0);

	robotRunAngle(-900,10,-880,-0.2);
	
	for(i=0;i<150;i++) 
	{
		while(CB_Ha_Sau == 0)		{vTaskDelay(1); if(!wantExit())	break;}
	}
	
	RESET_ENCODER(); 
	
	while(ENCODER_FR() + ENCODER_FL() < 300)	{vTaskDelay (1); if(!wantExit())	break;}
	
	robotStop(0);
	speed_chan_sau = 50;
	speed_chan_truoc = 90;
	
	target_chan_truoc = 260, target_chan_sau = 260;
	
		for(i=0;i<250;i++)	
	{
		while(bientrochantruocValue > 265)	{vTaskDelay(5); if(!wantExit())	break;}
	}
}
	
//**************** Xuong_bac_200 bam thanh phai + laser truoc ********
void Xuong_bac_200_bam_thanh_phai(void)
{	
	Xuong_bac_200();		
	
	for(i=0;i<1000;i++)	
	{
		while(lazeTruocValue > 25)	
			{	
					Bam_thanh_laser_phai(7,-900,-880,12,2,550,50);
						if(!wantExit())	break;
			}
	}
	
		for(i=0;i<1000;i++)	
	{
		while(lazeTruocNhoValue > 148)	
			{	
					Bam_thanh_laser_phai(7,-900,-880,12,2,550,50);
						if(!wantExit())	break;
			}
	}
	robotStop(0);
	speed_chan_sau = 120;
	speed_chan_truoc = 140;
	
	target_chan_truoc = 260, target_chan_sau = 260;
	
}
	

//**************** Xuong_bac_200 bam thanh trai + laser truoc ********
void Xuong_bac_200_bam_thanh_trai(void)
{	
	Xuong_bac_200();

	
	for(i=0;i<1000;i++)	
	{
		while(lazeTruocValue > 25)	
			{	
					Bam_thanh_laser_trai(7,-900,-880,42,2,550,50);
						if(!wantExit())	break;
			}
	}
	
		for(i=0;i<1000;i++)	
	{
		while(lazeTruocNhoValue > 148)	
			{	
					Bam_thanh_laser_trai(7,-900,-880,42,2,550,50);
						if(!wantExit())	break;
			}
	}
	robotStop(0);
	speed_chan_sau = 120;
	speed_chan_truoc = 140;
	
	target_chan_truoc = 260, target_chan_sau = 260;
}
	
//************************* xuong bac 200 encoder ********************************
// xuong bac 200 bam thanh phai
void Xuong_bac_200_encoder_bam_thanh_phai(void)
{	
		Xuong_bac_200();
		
// **** leo xong bam thanh phai dua vao encoder
	for(i=0;i<1000;i++)	
	{
		while(CB_Ha_Dau == 0 )	
			{	
					Bam_thanh_laser_phai(7,-900,-880,12,2,550,50);
					vTaskDelay(1);
					if(!wantExit())	break;
			}
	}
	
	robotStop(0);
	
	robotRunAngle(900,5,-900,0.2);
	
	RESET_ENCODER();
	
	while(abs(ENCODER_RR()) + abs(ENCODER_RL()) < 150)	
	{	
		//Bam_thanh_laser_phai(7,-900,-880,10,2,650,30);
		vTaskDelay (1); if(!wantExit())	break;
	}
	robotStop(0);
}


//**************** Xuong_bac_200 bam thanh trai ********
void Xuong_bac_200_encoder_bam_thanh_trai(void)
{	
		Xuong_bac_200();
		
// **** leo xong bam thanh phai dua vao encoder
	for(i=0;i<1000;i++)	
	{
		while(CB_Ha_Dau == 0 )	
			{	
					Bam_thanh_laser_trai(7,-900,-880,42,2,550,50);
					vTaskDelay(1);
					if(!wantExit())	break;
			}
	}
	
	robotStop(0);
	
	robotRunAngle(900,5,-900,0.2);
	
	RESET_ENCODER();
	
	while(abs(ENCODER_RR()) + abs(ENCODER_RL()) < 150)	
	{	
		//Bam_thanh_laser_phai(7,-900,-880,10,2,650,30);
		vTaskDelay (1); if(!wantExit())	break;
	}
	robotStop(0);	
	
}
	

////******************************** xuong bac 400 ****************************88
	void Xuong_bac_400 (void)
{	
	int i;
	speed_chan_sau = 100;
	speed_chan_truoc = 140;
	
	target_chan_truoc = 250, target_chan_sau = 250;
	
	for(i=0;i<250;i++)	
	{
		while(CB_Ha_Dau == 1)	{vTaskDelay(5); if(!wantExit())	break;}
	}
	
	robotRunAngle(-900,7,-900,0.2);

	for(i=0;i<250;i++)
	{	
		while(CB_Ha_Dau == 0)	{vTaskDelay(5); if(!wantExit())	break;}
	}

	RESET_ENCODER();
	
	while(abs(ENCODER_RR()) + abs(ENCODER_RL()) < 1325)	{vTaskDelay (1); if(!wantExit())	break;}
	
	robotStop(0);
	target_chan_truoc = 700;
	
		for(i=0;i<250;i++)	
	{
		while(bientrochantruocValue < 692)	{vTaskDelay(5); if(!wantExit())	break;}
	}
		robotStop(0);
//////	
	robotRunAngle(-900,7,-900,0.2);
//	robotRun(0,20);
//	
	for(i=0;i<550;i++)	
	{	
		while(CB_bung == 0)	{vTaskDelay(1); if(!wantExit())	break;}
	}
	
	RESET_ENCODER(); 
	
	while(abs(ENCODER_FR()) + abs(ENCODER_FL()) < 2000)	{vTaskDelay (1); if(!wantExit())	break;}
	
	robotStop(0);

	target_chan_sau = 700;
	
	for(i=0;i<250;i++)	
	{
		while(bientrochansauValue < 692)	{vTaskDelay(5); if(!wantExit())	break;}
	}
	robotStop(0);

	robotRunAngle(-900,10,-900,0.2);
	
	for(i=0;i<150;i++) 
	{
		while(CB_Ha_Sau == 0)		{vTaskDelay(1); if(!wantExit())	break;}
	}
////////	

	robotStop(30);
}

//============== Sang trái lên bac 200 ===================

void qua_trai_len_bac(void) {
	for(i=0;i<250;i++)
				{
					while(_robotIMUAngle < 1950)	
					{	
						robotRotateFree(-1.5, 0);
						if(!wantExit())	break;
					}
				}
}

//============== Sang trái xuong bac 200 ===================

void qua_trai_xuong_bac(void) {
 robotRotate(1800,-1.5, 0);
}

//============== Sang phai lên bac 200 ===================

void qua_phai_len_bac(void) {
	for(i=0;i<250;i++)
				{
					while(_robotIMUAngle < 10)	
					{	
						robotRotateFree(1.5, 0);
						if(!wantExit())	break;
					}
				}
}

//============== Sang phai xuong bac 200 ===================

void qua_phai_xuong_bac(void) {
 robotRotate(0,1.5, 0);

}

//********************************************* bam thanh laser phai ********************************************
void Bam_thanh_laser_phai(int speed, int runangle, int AngleHead, int lazer_stable_phai, int num_change_stable, int fix_max,int rat)
{
	int fix;

	fix = abs(lazePhaiValue - lazer_stable_phai) * rat;

	if (fix > fix_max)
	fix = fix_max;

	if (lazePhaiValue - lazer_stable_phai < num_change_stable)
	{
		robotRunAngle(runangle - fix, speed, AngleHead, 0.3);
	}
	else if (lazePhaiValue - lazer_stable_phai > num_change_stable)
	{
		robotRunAngle(runangle + fix, speed, AngleHead, 0.3);
	}
	else
		robotRunAngle(runangle, speed, AngleHead, 0.3);
}

//********************************************* bam thanh laser phai ********************************************
void Bam_thanh_laser_trai(int speed, int runangle, int AngleHead, int lazer_stable_phai, int num_change_stable, int fix_max,int rat)
{
	int fix;

	fix = abs(lazeTraiValue - lazer_stable_phai) * rat;

	if (fix > fix_max)
	fix = fix_max;

	if (lazeTraiValue - lazer_stable_phai < num_change_stable)
	{
		robotRunAngle(runangle + fix, speed, AngleHead, 0.3);
	}
	else if (lazeTraiValue - lazer_stable_phai > num_change_stable)
	{
		robotRunAngle(runangle - fix, speed, AngleHead, 0.3);
	}
	else
		robotRunAngle(runangle, speed, AngleHead, 0.3);
}


//********************************************* bam thanh laser truoc ********************************************
void Bam_laser_truoc(int speed, int runangle, int AngleHead, int lazer_stable_truoc, int num_change_stable, int fix_max,int rat)
{
	int fix;

	fix = abs(lazeTruocValue - lazer_stable_truoc) * rat;

	if (fix > fix_max)
	fix = fix_max;

	if (lazeTruocValue - lazer_stable_truoc < num_change_stable)
	{
		robotRunAngle(runangle - fix, speed, AngleHead, 0.7);
	}
	else if (lazeTruocValue - lazer_stable_truoc > num_change_stable)
	{
		robotRunAngle(runangle + fix, speed, AngleHead, 0.7);
	}
	else
		robotRunAngle(runangle, speed, AngleHead, 0.77);
}
/////////////////////////////leodoc/////////////////////////////////////////
	void leodoc1(void)
{	
	int i;
	
	speed_chan_sau = 100;
	speed_chan_truoc = 160;
	
	target_chan_truoc = 270, target_chan_sau = 280;
	
	robotRun(0,30);
	for(i=0;i<550;i++)	
	{	
			while(lazeTruocValue > 40)	{vTaskDelay(5); if(wantExit())	break;}
	}
	
	robotRun(0,30);
	for(i=0;i<550;i++)	
	{	
			while(lazeTruocValue < 70)	{vTaskDelay(5); if(wantExit())	break;}
	}	
	
	robotRun(0,30);
	
	for(i=0;i<550;i++)	
	{	
			while(lazeTruocValue > 50)	{vTaskDelay(5); if(wantExit())	break;}
	}			
	
	
	robotStop(0);
	
	for(i=0;i<550;i++)	
	{	
			while(lazeTraiValue > 100)	
			{	
				Bam_laser_truoc(60,-900,0,32,2,200,30);
				vTaskDelay(5); 
				if(wantExit())	break;
			}
		
	}	
	
	for(i=0;i<550;i++)	
	{	
			while(lazeTraiValue > 15)	
			{	
				Bam_laser_truoc(20,-900,0,32,2,200,30);
				vTaskDelay(5); 
				if(wantExit())	break;
			}
		
	}	
	robotStop(0);
}

void leodoc2(void)
{	
	int i;
	
	speed_chan_sau = 100;
	speed_chan_truoc = 160;
	
	target_chan_truoc = 270, target_chan_sau = 280;
	
	robotRun(0,30);
	for(i=0;i<550;i++)	
	{	
			while(lazeTruocValue > 40)	{vTaskDelay(5); if(wantExit())	break;}
	}
	
	robotRun(0,30);
	for(i=0;i<550;i++)	
	{	
			while(lazeTruocValue < 70)	{vTaskDelay(5); if(wantExit())	break;}
	}	
	
	robotRun(0,30);
	
	for(i=0;i<550;i++)	
	{	
			while(lazeTruocValue > 50)	{vTaskDelay(5); if(wantExit())	break;}
	}			
	
	
	robotStop(0);
	
	for(i=0;i<550;i++)	
	{	
			while(lazeTraiValue > 100)	
			{	
				Bam_laser_truoc(60,-900,0,32,2,200,30);
				vTaskDelay(5); 
				if(wantExit())	break;
			}
		
	}	
	
	for(i=0;i<550;i++)	
	{	
			while(lazeTraiValue > 15)	
			{	
				Bam_laser_truoc(20,-900,0,32,2,200,30);
				vTaskDelay(5); 
				if(wantExit())	break;
			}
		
	}	
	robotStop(0);
}

//****************************** tay gap kfs 1 ********************************
void Tay_3_gap_kfs_len(void)
{
	Tay3_len_on;
	Tay3_xuong_off;
}
void Tay_3_gap_kfs_xuong(void)
{
	Tay3_xuong_on;
	Tay3_len_off;
}
void Tay_3_gap_kfs_dung(void)
{
	Tay3_xuong_off;
	Tay3_len_off;
}

//****************************** tay gap kfs 1 ********************************
void Tay_1_gap_kfs_len(void)
{
	Tay1_len_on;
	Tay1_xuong_off;
}
void Tay_1_gap_kfs_xuong(void)
{
	Tay1_xuong_on;
	Tay1_len_off;
}
void Tay_1_gap_kfs_dung(void)
{
	Tay1_xuong_off;
	Tay1_len_off;
}

//****************************** tay gap kfs 1 ********************************
void Tay_2_gap_kfs_len(void)
{
	Tay2_len_on;
	Tay2_xuong_off;
}
void Tay_2_gap_kfs_xuong(void)
{
	Tay2_xuong_on;
	Tay2_len_off;
}
void Tay_2_gap_kfs_dung(void)
{
	Tay2_xuong_off;
	Tay2_len_off;
}
void Tay_len_all(void)
{
	Tay1_len_on;
	Tay1_xuong_off;
	Tay2_len_on;
	Tay2_xuong_off;
	Tay3_len_on;
	Tay3_xuong_off;
}

//******************************* nang ha bang tayu **************************
void Xoay_tay_Manual(void)
{
	if (SQUARE && !R1 && !R2 && !L2 && bientroxoaytayValue < Max_xoay_tay ) 				
	{
		if(L1 && bientroxoaytayValue < Max_xoay_tay - 20)	tay_xoay = 100;
		else		tay_xoay = 40;
		tay_xoay_thuan;
		target_xoay_tay = bientroxoaytayValue;
		Man_xoay_tay = 1;
	}
	else	if (O && !R1 && !R2 && !L2 && bientroxoaytayValue > Min_xoay_tay) 	
				{
					if(L1 && bientroxoaytayValue > Min_xoay_tay + 20)	tay_xoay = 100;
					else		tay_xoay = 40;
					tay_xoay_nghich;
					target_xoay_tay = bientroxoaytayValue;
					Man_xoay_tay = 1;
				}
	else Man_xoay_tay = 0;
}

// **** ham kiem tra tay gap *********
void kiem_tra_tay_gap1( int giatri_xoay) {
		Tay_1_gap_kfs_xuong();
		Tay1_day_ra;
		Bom1_on;
			
		vTaskDelay (15000);
	
		Tay_1_gap_kfs_len();
		Tay1_day_vao;
	
		vTaskDelay (7000);
		
		if(HT_qua_1 == 1)	
		{
			
			target_xoay_tay = giatri_xoay + 5;
			vTaskDelay (3000);
			
			Tay_1_gap_kfs_xuong();
			Tay1_day_ra;
			Bom1_on;
			
			vTaskDelay (15000);
	
			Tay_1_gap_kfs_len();
			Tay1_day_vao;
			
			vTaskDelay (7000);

		if(HT_qua_1 == 1)	
		{
			target_xoay_tay = giatri_xoay - 5;
			vTaskDelay (3000);
			
			Tay_1_gap_kfs_xuong();
			Tay1_day_ra;
			Bom1_on;
			
			vTaskDelay (15000);
	
			Tay_1_gap_kfs_len();
			Tay1_day_vao;
			
			vTaskDelay (7000);
		}
		
	}		
		
	target_xoay_tay = giatri_xoay - 20;
		
}	

//*********** ham kiem tra tay gap 2 **********
void kiem_tra_tay_gap2( int giatri_xoay) {
		Tay_2_gap_kfs_xuong();
		Tay2_day_ra;
		Bom2_on;
			
		vTaskDelay (15000);
	
		Tay_2_gap_kfs_len();
		Tay2_day_vao;
	
		vTaskDelay (7000);
		
		if(HT_qua_2 == 1)	
		{
			target_xoay_tay = giatri_xoay + 8;
			vTaskDelay (3000);
			
			Tay_2_gap_kfs_xuong();
			Tay2_day_ra;
			Bom2_on;
			
			vTaskDelay (15000);
	
			Tay_2_gap_kfs_len();
			Tay2_day_vao;
	
			vTaskDelay (7000);
			
		if(HT_qua_2 == 1)	
		{
			target_xoay_tay = giatri_xoay - 8;
			vTaskDelay (3000);
			
			Tay_2_gap_kfs_xuong();
			Tay2_day_ra;
			Bom2_on;
			
			vTaskDelay (15000);
	
			Tay_2_gap_kfs_len();
			Tay2_day_vao;
	
			vTaskDelay (7000);
		}		
	}			
		
	target_xoay_tay = giatri_xoay - 20;
}	


// ********* ham kiem tra tay gap 3 **********
void kiem_tra_tay_gap3( int giatri_xoay) {
		Tay_3_gap_kfs_xuong();
		Tay3_day_ra;
		Bom3_on;
			
		vTaskDelay (15000);
	
		Tay_3_gap_kfs_len();
		Tay3_day_vao;
	
		vTaskDelay (7000);
		
		if(HT_qua_3 == 1)	
		{
			target_xoay_tay = giatri_xoay + 8;
			vTaskDelay (3000);
			
			Tay_3_gap_kfs_xuong();
			Tay3_day_ra;
			Bom3_on;
			
			vTaskDelay (15000);
	
			Tay_3_gap_kfs_len();
			Tay3_day_vao;
	
			vTaskDelay (7000);
			
		if(HT_qua_3 == 1)	
		{
			target_xoay_tay = giatri_xoay - 8;
			vTaskDelay (3000);
			
			Tay_3_gap_kfs_xuong();
			Tay3_day_ra;
			Bom3_on;
			
			vTaskDelay (15000);
	
			Tay_3_gap_kfs_len();
			Tay3_day_vao;
	
			vTaskDelay (7000);
		}		
	}			
		target_xoay_tay = giatri_xoay - 20;
}	


/// ******************** Ham lay tay phia truoc  *****************
extern int da_lay_tay1;
extern int da_lay_tay2 ;
extern int da_lay_tay3 ;
extern int da_lay_tay4 ;

void Lay_phia_truoc_bac_200_tren(void) {
	
	////******************* di len phia truoc ******************
	speed_chan_sau = 140;
	speed_chan_truoc = 180;

	target_chan_truoc = 475;
	target_chan_sau = 475;	
	
				
	for(i=0;i<250;i++)	
	{
		while(bientrochantruocValue < 470)	{vTaskDelay(5); if(!wantExit())	break;}
	}			
				

	for(i=0;i<250;i++)	
	{
		while(CB_Ha_Dau == 1)	
			{	
//					Bam_thanh_laser_trai(7,-900,-880,271,2,150,15);
						robotRunAngle(-900,7,-900,0.2);
						if(!wantExit())	break;
			}
	}
	
	RESET_ENCODER();
	
	while(abs(ENCODER_RR()) + abs(ENCODER_RL()) < 540)	
	{	
//		Bam_thanh_laser_trai(7,-900,-900,271,2,150,15);
			robotRunAngle(-900,7,-900,0.2);

		if(!wantExit())	break;
	}
	
	robotStop(30);
	
	// ******************Neu canh tay 1 chua co gap***************************
	if (da_lay_tay1 == 0) {
	
	// xoay tay 1
		
	speed_tay_xoay = 150;
	target_xoay_tay = 618;
		
	for(i=0;i<250;i++)	
	{
		while(bientroxoaytayValue < 613)	{vTaskDelay(5); if(!wantExit())	break;}
	}	
		robotStop(30);
		kiem_tra_tay_gap1(target_xoay_tay);

	
	robotRunAngle(900,10,-900,0.2);
	
	for(i=0;i<250;i++)	
	{
		while(CB_Ha_Dau == 0)	
			{	
							vTaskDelay (2);
						if(!wantExit())	break;
			}
	}
	
	RESET_ENCODER();
	
	while(abs(ENCODER_RR()) + abs(ENCODER_RL()) < 450)	// lùi ve
	{	
		vTaskDelay (2);
		if(!wantExit())	break;
	}
	
	speed_chan_sau = 100;
	speed_chan_truoc = 180;

	target_chan_truoc = 300;
	target_chan_sau = 300;
	
	robotStop(30);
	
	for(i=0;i<250;i++)	
	{
		while(bientrochantruocValue > 310)	{vTaskDelay(5); if(!wantExit())	break;}
	}
	for(i=0;i<250;i++)	
{
	while(CB_tay1_giua == 1 )	
	{	
		vTaskDelay (2);
		if(!wantExit())	break;
	}
}
	robotStop(30);
	da_lay_tay1 = 1;
	
// *************lay xong thi quay tay sang tay 2*******************

		// nhac len ty cho tay 2
	speed_chan_sau = 100;
	speed_chan_truoc = 180;

	target_chan_truoc = 485;
	target_chan_sau = 485;

		for(i=0;i<250;i++)	
	{
		while(bientrochantruocValue < 482)	{vTaskDelay(5); if(!wantExit())	break;}
	}	

	// nang chan roi xoay
	speed_tay_xoay = 100;
	target_xoay_tay = 517;

	for(i=0;i<250;i++)	
	{
		while(bientroxoaytayValue > 519)	{vTaskDelay(1); if(!wantExit())	break;}
	}	
		robotStop(30);
	
	}
	
	//********************* da dung tay 1 chuyen sang tay 2**************
	else if (da_lay_tay1 == 1 && da_lay_tay2 == 0 ) {

		kiem_tra_tay_gap2(target_xoay_tay);

	
	robotRunAngle(900,10,-900,0.2);
	
	for(i=0;i<250;i++)	
	{
		while(CB_Ha_Dau == 0)	
			{	
							vTaskDelay (2);
						if(!wantExit())	break;
			}
	}
	
	RESET_ENCODER();
	
	while(abs(ENCODER_RR()) + abs(ENCODER_RL()) < 450)	// lùi ve
	{	
		vTaskDelay (2);
		if(!wantExit())	break;
	}
	
	speed_chan_sau = 100;
	speed_chan_truoc = 180;

	target_chan_truoc = 300;
	target_chan_sau = 300;
	
	robotStop(30);
	
	for(i=0;i<250;i++)	
	{
		while(bientrochantruocValue > 310)	{vTaskDelay(5); if(!wantExit())	break;}
	}
	for(i=0;i<250;i++)	
{
	while(CB_tay2_giua == 1 )	
	{	
		vTaskDelay (2);
		if(!wantExit())	break;
	}
	} 
	robotStop(30);
	da_lay_tay2 = 1;
	
	//********** quay tay sang tay 3 ************
	
	// nhac len ty cho tay 3
		speed_chan_sau = 100;
		speed_chan_truoc = 180;

		target_chan_truoc = 485;
		target_chan_sau = 485;	
	
		for(i=0;i<250;i++)	
	{
		while(bientrochantruocValue < 482)	{vTaskDelay(5); if(!wantExit())	break;}
	}			
	
		speed_tay_xoay = 100;
		target_xoay_tay = 423;
	
		for(i=0;i<250;i++)	
	{
		while(bientroxoaytayValue > 427)	{vTaskDelay(5); if(!wantExit())	break;}
	}	
		
		robotStop(30);
	
		
}
	///************ tay 1 tay 2 dung roi thi dung tay 3 *********
	else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 ) {

		kiem_tra_tay_gap3(target_xoay_tay);
	
	robotRunAngle(900,10,-900,0.2);
	
	for(i=0;i<250;i++)	
	{
		while(CB_Ha_Dau == 0)	
			{	
							vTaskDelay (2);
						if(!wantExit())	break;
			}
	}
	
	RESET_ENCODER();
	
	while(abs(ENCODER_RR()) + abs(ENCODER_RL()) < 450)	// lùi ve
	{	
		vTaskDelay (2);
		if(!wantExit())	break;
	}
	
	speed_chan_sau = 100;
	speed_chan_truoc = 180;

	target_chan_truoc = 300;
	target_chan_sau = 300;
	
	robotStop(30);
	
	for(i=0;i<250;i++)	
	{
		while(bientrochantruocValue > 310)	{vTaskDelay(5); if(!wantExit())	break;}
	}
	for(i=0;i<250;i++)	
{
	while(CB_tay3_giua == 1 )	
	{	
		vTaskDelay (2);
		if(!wantExit())	break;
	}
	} 
	robotStop(30);
	da_lay_tay3 = 1;
	
			}
	}



//***************Gap phia truoc leo bac 400******************
void Lay_phia_truoc_bac_400(void) {	
	
	// chay len phia truoc bac 400
				
	speed_chan_sau = 100;
	speed_chan_truoc = 110;

	target_chan_truoc = 690;
	target_chan_sau = 690;
				
	for(i=0;i<250;i++)	
	{
		while(bientrochantruocValue < 685)	{vTaskDelay(5); if(!wantExit())	break;}
	}			
				

	for(i=0;i<250;i++)	
	{
		while(CB_Ha_Dau == 1)	
			{	
						Bam_thanh_laser_trai(7,-900,-880,152,2,150,15);//robotRun(-450,10);
						if(!wantExit())	break;
			}
	}
	
	RESET_ENCODER();
	
	while(abs(ENCODER_RR()) + abs(ENCODER_RL()) < 540)	
	{	
		Bam_thanh_laser_trai(7,-900,-880,152,2,150,15);//robotRun(-450,10);
		if(!wantExit())	break;
	}
	
	robotStop(30);
	
	/// xoay sang de tay 1 lay
	
	speed_tay_xoay = 150;
	target_xoay_tay = 620;
	for(i=0;i<250;i++)	
	{
		while(bientroxoaytayValue < 620)	{vTaskDelay(5); if(!wantExit())	break;}
	}	
	
	kiem_tra_tay_gap1(target_xoay_tay);
	
	robotRunAngle(900,10,-900,0.2);
	
	for(i=0;i<250;i++)	
	{
		while(CB_Ha_Dau == 0)	
			{	
							vTaskDelay (2);
						if(!wantExit())	break;
			}
	}
	
	RESET_ENCODER();
	
	while(abs(ENCODER_RR()) + abs(ENCODER_RL()) < 300)	
	{	
		vTaskDelay (2);
		if(!wantExit())	break;
	}
	
	
	speed_chan_sau = 100;
	speed_chan_truoc = 120;

	target_chan_truoc = 400;
	target_chan_sau = 400;
	robotStop(30);
	

	
	for(i=0;i<250;i++)	
{
	while(CB_tay1_giua == 1 )	
	{	
		vTaskDelay (2);
		if(!wantExit())	break;
	}
}
	da_lay_tay1 = 1;
	// lay xong roi thi xoay sang tay 2
	
	speed_tay_xoay = 100;
	target_xoay_tay = 517;

	for(i=0;i<250;i++)	
	{
		while(bientroxoaytayValue > 519)	{vTaskDelay(1); if(!wantExit())	break;}
	}	
		robotStop(30);
}

// ********** Hàm lây tay phia truoc bac duoi 200 **********

void Lay_phia_truoc_bac_200_duoi(void) {
	// ********* di len phia truoc, cb dau cham thi dung lai  ******************
	int i;
	speed_chan_sau = 100;
	speed_chan_truoc = 180;
	
	target_chan_truoc = 238, target_chan_sau = 238;
	
	for(i=0;i<250;i++)	
	{
		while(CB_Ha_Dau == 1)	{vTaskDelay(5); if(!wantExit())	break;}
	}
	
	robotRunAngle(-900,7,-900,0.2);

	for(i=0;i<250;i++)
	{	
		while(CB_Ha_Dau == 0)	{vTaskDelay(5); if(!wantExit())	break;}
	}

	RESET_ENCODER();
	
	while(abs(ENCODER_RR()) + abs(ENCODER_RL()) < 500)	{vTaskDelay (1); if(!wantExit())	break;}
	
	robotStop(0);
//	
//	// gap tay duoi bac 200 duoi
//	// ******************Neu canh tay 1 chua co gap***************************
	if (da_lay_tay2 == 0) {
	
	// xoay tay 2, 3 gap qua duoi
		
	speed_tay_xoay = 150;
	target_xoay_tay = 522;
	

		robotStop(30);
		
	for(i=0;i<250;i++)	
	{
		while(bientroxoaytayValue > 520)	{vTaskDelay(5); if(!wantExit())	break;}
	}	
		robotStop(0);
		kiem_tra_tay_gap2(target_xoay_tay);
	
	speed_chan_sau = 50;
	target_chan_sau = 500;
//	for(i=0;i<250;i++)	
//	{
//		while(bientrochansauValue > 240)	{vTaskDelay(5); if(!wantExit())	break;}
//	}
	
	for(i=0;i<1050;i++)
	{	
		while(CB_tay2_giua == 1)	{vTaskDelay(5); if(!wantExit())	break;}
	}
	robotStop(0);
	
	speed_chan_sau = 50;
	target_chan_sau = 238;
	
		for(i=0;i<250;i++)	
	{
		while(bientrochansauValue > 240)	{vTaskDelay(5); if(!wantExit())	break;}
	}
	
	//	// gap xong thì lùi ve sau nhón chan sau len de lay luc keo hop len
	robotRunAngle(900,10,-900,0.2);
	
	for(i=0;i<250;i++)	
	{
		while(CB_Ha_Dau == 1)	
			{	
							vTaskDelay (2);
						if(!wantExit())	break;
			}
	}
	
	RESET_ENCODER();
	
	while(abs(ENCODER_RR()) + abs(ENCODER_RL()) < 450)	// lùi ve
	{	
		vTaskDelay (2);
		if(!wantExit())	break;
	}
	robotStop(0);
	
	da_lay_tay2 = 1; //da lay tay 2 xoay sang tay 3
	
	speed_tay_xoay = 100;
	target_xoay_tay = 410;
	
		for(i=0;i<250;i++)	
	{
		while(bientroxoaytayValue > 418)	{vTaskDelay(5); if(!wantExit())	break;}
	}	
		
		robotStop(30);

		}
	//******* lay xong tay 2 , chuyen sang tay 3 *************
	else if (da_lay_tay2 == 1) {
		
	kiem_tra_tay_gap3(target_xoay_tay);
		
		
	
	speed_chan_sau = 50;
	target_chan_sau = 500;

		for(i=0;i<1050;i++)
	{	
		while(CB_tay3_giua == 1)	{vTaskDelay(5); if(!wantExit())	break;}
	}

	speed_chan_sau = 50;
	target_chan_sau = 238;
	for(i=0;i<250;i++)	
	{
		while(bientrochansauValue > 240)	{vTaskDelay(5); if(!wantExit())	break;}
	}
		
	
	
	//	// gap xong thì lùi ve sau nhón chan sau len de lay luc keo hop len
	robotRunAngle(900,10,-900,0.2);
	
	for(i=0;i<250;i++)	
	{
		while(CB_Ha_Dau == 1)	
			{	
							vTaskDelay (2);
						if(!wantExit())	break;
			}
	}
	
	RESET_ENCODER();
	
	while(abs(ENCODER_RR()) + abs(ENCODER_RL()) < 450)	// lùi ve
	{	
		vTaskDelay (2);
		if(!wantExit())	break;
	}
	robotStop(0);
	da_lay_tay3 = 1;
			
		
		}

}

// ************* roi khoi dung thi tay ve home ***************
void vuot_rung_ve_homeTay_bac_400 (void) {
	Xuong_bac_400();
	
	speed_tay_xoay = 100;
	target_xoay_tay = 520;
		robotStop(30);
	hoan_thanh_chay_rung = 1;

}

void vuot_rung_ve_homeTay_bac_200 (void) {
	Xuong_bac_200();
	
	speed_tay_xoay = 100;
	target_xoay_tay = 520;
		robotStop(30);
	hoan_thanh_chay_rung = 1;

}
// ******************Home***************************
void vehome(void)
{
	robotResetIMU();
	speed_chan_sau = 40;
	speed_chan_truoc = 70;
	target_chan_truoc = 300;
	target_chan_sau = 300;
	Tay_len_all();
	Bom3_off;
	Bom2_off;
	Bom1_off;
	Tay1_xa_on;
	Tay2_xa_on;
	Tay3_xa_on;	
	XI_LANH_KEP_MO;
	XI_LANH_NANG_KEP;
	speed_tay_xoay = 100;
	target_xoay_tay = 520;
}
//////////CODETEST//////////////
void Test(void)
{	
int i;
	speed_chan_sau = 100;
	speed_chan_truoc = 130;
	
	target_chan_truoc = 245, target_chan_sau = 245;
	
	for(i=0;i<250;i++)	
	{
		while(CB_Ha_Dau == 1)	{vTaskDelay(5); if(!wantExit())	break;}
	}
	
	robotRunAngle(0,7,0,-0.2);

	for(i=0;i<250;i++)
	{	
		while(CB_Ha_Dau == 0)	{vTaskDelay(5); if(!wantExit())	break;}
	}

	RESET_ENCODER();
	
	while(abs(ENCODER_RR()) + abs(ENCODER_RL()) < 1400)	{vTaskDelay (1); if(!wantExit())	break;}
	
	robotStop(0);

	target_chan_truoc = 470;
	
		for(i=0;i<250;i++)	
	{
		while(bientrochantruocValue < 462)	{vTaskDelay(5); if(!wantExit())	break;}
	}
		robotStop(0);

	robotRunAngle(0,7,0,-0.2);
	
	for(i=0;i<550;i++)	
	{	
		while(CB_bung == 0)	{vTaskDelay(1); if(!wantExit())	break;}
	}
	target_chan_sau = 260;
	RESET_ENCODER(); 
	
	while(abs(ENCODER_FR()) + abs(ENCODER_FL()) < 2100)	{vTaskDelay (1); if(!wantExit())	break;}
	
	robotStop(0);

	target_chan_sau = 470;
	
	for(i=0;i<250;i++)	
	{
		while(bientrochansauValue < 460)	{vTaskDelay(5); if(!wantExit())	break;}
	}
	robotStop(0);

	robotRunAngle(0,10,0,-0.2);
	
	for(i=0;i<150;i++) 
	{
		while(CB_Ha_Sau == 0)		{vTaskDelay(1); if(!wantExit())	break;}
	}
//	
	robotStop(30);

}