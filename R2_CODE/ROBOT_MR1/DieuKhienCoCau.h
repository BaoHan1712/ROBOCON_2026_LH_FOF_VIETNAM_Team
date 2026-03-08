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

extern int TinHieu_ChuanBi_GapThang;
extern int TinHieu_ChuanBi_GapTrai ;
extern int TinHieu_ChuanBi_GapPhai;


// *************** thong so tay gap ************
int	Min_chan_truoc = 215, Max_chan_truoc = 702, target_chan_truoc;
int	Min_chan_sau = 215, Max_chan_sau = 702, target_chan_sau;
int	Min_xoay_tay = 250, Max_xoay_tay = 700, target_xoay_tay;
int	Min_tay_gat1 = 43, Max_tay_gat1 = 215, target_tay_gat1;
int	Min_tay_gat2 = 43, Max_tay_gat2 = 208, target_tay_gat2;

int	speed_chan_sau, speed_chan_truoc,speed_tay_xoay,speed_tay_gat1,speed_tay_gat2;
int home_trc,home_sau;

int force_F;
int final_force;
float result;

extern int Man_xoay_tay;
extern int Man_gat1;
extern int Man_gat2;

extern int da_lay_tay1;
extern int da_lay_tay2;
extern int da_lay_tay3;
extern int da_lay_tay4;


void robotLineRunLeft(vu8 speed);
void robotLineRunRight(vu8 speed);
void kiem_tra_huong_quay_tay_gap_phia_truoc (void);

	
void Bam_thanh_laser_trai(int speed, int runangle, int AngleHead, int lazer_stable_phai, int num_change_stable, int fix_max,int rat);
void Bam_thanh_laser_phai(int speed, int runangle, int AngleHead, int lazer_stable_phai, int num_change_stable, int fix_max,int rat);


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
	static unsigned int bientrodaytay1Couter = 0, bientrodaytay1_SUM = 0;
	static unsigned int bientrodaytay2Couter = 0, bientrodaytay2_SUM = 0;
	////----------------TINH TOAN LAZER---------------
	if (lazeSauCouter++ < 70)
	{
		lazeSau_SUM += cam_bien_laze_sau;
	}
	else
	{
		lazeSauValue = lazeSau_SUM / 70;
		lazeSauCouter = 0;
		lazeSau_SUM = 0;
	}
	//-------------------------------------------
	if (lazeTruocCouter++ < 70)
	{
		lazeTruoc_SUM += cam_bien_laze_truoc;
	}
	else
	{
		lazeTruocValue = lazeTruoc_SUM / 70;
		lazeTruocCouter = 0;
		lazeTruoc_SUM = 0;
	}
	//------------------------------ laze phai --------------
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
//	//------------------------------ laze truoc nho --------------
//	if (lazeTruocNhoCouter++ < 70)
//	{
//		lazeTruocNho_SUM += cam_bien_laze_truoc_nho;
//	}
//	else
//	{
//		lazeTruocNhoValue = lazeTruocNho_SUM / 70;
//		lazeTruocNhoCouter = 0;
//		lazeTruocNho_SUM = 0;
//	}
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

	//-----------------------------
	if (bientrodaytay1Couter++ < 50)
	{
		bientrodaytay1_SUM += bien_tro_gat1;
	}
	else
	{
		bientrodaytay1Value = bientrodaytay1_SUM / 50;
		bientrodaytay1Couter = 0;
		bientrodaytay1_SUM = 0;
	}

//-----------------------------
	if (bientrodaytay2Couter++ < 50)
	{
		bientrodaytay2_SUM += bien_tro_gat2;
	}
	else
	{
		bientrodaytay2Value = bientrodaytay2_SUM / 50;
		bientrodaytay2Couter = 0;
		bientrodaytay2_SUM = 0;
	}

}



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
//************************************** gat1 **************************************
void Gat_1()
{
	if (target_tay_gat1 < Min_tay_gat1)
		target_tay_gat1 = Min_tay_gat1;
	if (target_tay_gat1 > Max_tay_gat1)
		target_tay_gat1 = Max_tay_gat1;

	if (abs(bientrodaytay1Value - target_tay_gat1) > 2)
	{
		if (bientrodaytay1Value > target_tay_gat1)			Gat_tay1_xuong;
		else																						Gat_tay1_len;

		speed_temp = abs(bientrodaytay1Value - target_tay_gat1)*7;
		if (speed_temp > speed_tay_gat1)
				speed_temp = speed_tay_gat1;
		if (speed_temp < 20)
				speed_temp = 20;
		
		Gat_tay1 = speed_temp;
	}
	else Gat_tay1 = 0;
}
//************************************** gat2 **************************************
void Gat_2()
{
	if (target_tay_gat2 < Min_tay_gat2)
		target_tay_gat2 = Min_tay_gat2;
	if (target_tay_gat2 > Max_tay_gat2)
		target_tay_gat2 = Max_tay_gat2;

	if (abs(bientrodaytay2Value - target_tay_gat2) > 2)
	{
		if (bientrodaytay2Value > target_tay_gat2)			Gat_tay2_len;
		else																						Gat_tay2_xuong;

		speed_temp = abs(bientrodaytay2Value - target_tay_gat2)*10;
		if (speed_temp > speed_tay_gat2)
				speed_temp = speed_tay_gat2;
		if (speed_temp < 150)
				speed_temp = 150;
		
		Gat_tay2 = speed_temp;
	}
	else Gat_tay2 = 0;
}
//************************************** xoay tay kep auto **************************************
	void Xoay_tay_kep()
{
	if (target_xoay_tay < Min_xoay_tay)
		target_xoay_tay = Min_xoay_tay;
	if (target_xoay_tay > Max_xoay_tay)
		target_xoay_tay = Max_xoay_tay;

	if ((abs(bientroxoaytayValue - target_xoay_tay) > 2) && (abs(bientrodaytay1Value - 117) < 15) && (abs(bientrodaytay2Value - 115) < 15))
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


//********************************Speed nang ****************************
void Nang_cham	(void) {
	speed_chan_sau = 37;
	speed_chan_truoc = 48;
}

void Nang_thuong	(void) {
	speed_chan_sau = 46;
	speed_chan_truoc = 62;
}

void Nang_nhanh	(void) {
	speed_chan_sau = 59;
	speed_chan_truoc = 81;
}

void Nang_cuc_nhanh	(void) {
	speed_chan_sau = 104;
	speed_chan_truoc = 140;
}


void su_dung_chan (int value_chan) {
	Nang_cuc_nhanh();

	target_chan_truoc = value_chan;
	target_chan_sau = value_chan;
}


//******************************** leo bac 200 ****************************
void Leo_bac_200(void)
{	
		int i;
			// nâng bánh trc lên 
	speed_chan_sau = 115;
	speed_chan_truoc = 140;
	
	target_chan_truoc = 465;
	target_chan_sau = 465;
	
 	for(i=0;i<50;i++)		
	{
		while(abs(bientrochansauValue - target_chan_sau) > 4)	{vTaskDelay(1); if(!wantExit())	break;}
	}

	
	for(i=0;i<250;i++)	
	{	
		while(CB_Ha_Sau == 1)	{vTaskDelay(1); if(!wantExit())	break;}
	}
////	
//	RESET_ENCODER(); 
//	
//	while(abs(ENCODER_FR()) + abs(ENCODER_FL()) < 200)	{vTaskDelay (1); if(!wantExit())	break;}
//	
//	robotStop(0);
////////	
	target_chan_sau = 223;
	for(i=0;i<50;i++)		
	{
		while(bientrochansauValue > 228)	{vTaskDelay(1); if(!wantExit())	break;}
	}
//	
////	// nâng bánh sau lên 
	target_chan_truoc = 480;
	robotRunAngle(-900,12,900,0.2);
	
	for(i=0;i<550;i++)	
	{	
		while(CB_bung_duoi == 1)	{vTaskDelay(2); if(!wantExit())	break;}
	}

	speed_chan_sau = 50;
	target_chan_sau = 240;

for(i=0;i<550;i++)	
	{	
		while(CB_bung == 1)	{vTaskDelay(1); if(!wantExit())	break;}
	}

  robotStop(0);
	target_chan_truoc = 223;

	for(i=0;i<250;i++)	
	{
		while(bientrochantruocValue > 228)	{vTaskDelay(1); if(!wantExit())	break;}
	}
//	
	RESET_ENCODER();
	robotRunAngle(-900,7,900,0.2);
for(i=0;i<250;i++)	
	{
	while(abs(ENCODER_RR()) + abs(ENCODER_RL()) < 1600)	{vTaskDelay (1); if(!wantExit())	break;}
	}

	speed_chan_truoc = 50;
	target_chan_truoc = 240;
	for(i=0;i<150;i++) 
	{
		while(CB_Ha_Dau == 1)		{vTaskDelay(1); if(!wantExit())	break;}
	
}
	
	
	robotStop(0);
	speed_chan_sau = 100;
	speed_chan_truoc = 140;
	
	target_chan_truoc = 350, target_chan_sau = 350;

			if ( TinHieu_ChuanBi_GapThang == 1 ) {
					kiem_tra_huong_quay_tay_gap_phia_truoc();
					TinHieu_ChuanBi_GapThang = 0;
				}
		else {TinHieu_ChuanBi_GapThang = 0 ;}
}

//***************** leo bac 200 bam thanh laser phai va laser truoc *************

void Leo_bac_200_bam_thanh_phai(void)
{	
	Leo_bac_200();
// **** leo xong bam thanh phai
	
	for(i=0;i<1000;i++)	
	{
		while(lazeTruocValue > 35)	
			{	
					Bam_thanh_laser_phai(7,-900,900,154,2,550,50);
						if(!wantExit())	break;
			}
	}
	
		for(i=0;i<1000;i++)	
	{
		while(lazeTruocValue > 10)	
			{	
					Bam_thanh_laser_phai(7,-900,900,154,2,550,50);
						if(!wantExit())	break;
			}
	}
	
	su_dung_chan (615);
	robotRunAngle(-900,15,900,0.2);
	RESET_ENCODER(); 
		
	while(abs(ENCODER_FR()) + abs(ENCODER_FL()) < 1650)	{vTaskDelay (1); if(!wantExit())	break;}
			robotStop(0);
	
	
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
					Bam_thanh_laser_phai(7,-900,-880,154,2,550,50);
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
					Bam_thanh_laser_trai(7,-900,-880,154,2,550,50);
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
					Bam_thanh_laser_trai(7,-900,-880,154,2,550,50);
						if(!wantExit())	break;
			}
	}
	
		for(i=0;i<1000;i++)	
	{
		while(lazeTruocNhoValue > 148)	
			{	
					Bam_thanh_laser_trai(7,-900,-880,154,2,550,50);
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
	
	speed_chan_sau = 90;
	speed_chan_truoc = 130;
	
	target_chan_truoc = 690, target_chan_sau = 690;
	
	for(i=0;i<250;i++)	
	{
		while(abs(bientrochansauValue - target_chan_sau) > 4)	{vTaskDelay(1); if(!wantExit())	break;}
	}
	robotStop(0);
	robotRunAngle(-900,10,900,0.2);
	
	for(i=0;i<550;i++)	
	{	
		while(CB_Ha_Sau == 1)	{vTaskDelay(1); if(!wantExit())	break;}
	}

	RESET_ENCODER(); 
	
	while(abs(ENCODER_FR()) + abs(ENCODER_FL()) < 300)	{vTaskDelay (5); if(!wantExit())	break;}
	
	robotStop(15); 
////////	
	target_chan_sau = 223;
//	
	for(i=0;i<50;i++)		
	{
		while(bientrochansauValue > 228)	{vTaskDelay(5); if(!wantExit())	break;}
	}
	
	target_chan_truoc = 702;
	
	robotRunAngle(-900,12,900,0.2);
	
	for(i=0;i<550;i++)	
	{	
		while(CB_bung_duoi == 1)	{vTaskDelay(2); if(!wantExit())	break;}
	}

	speed_chan_sau = 50;
	target_chan_sau = 240;
	
	for(i=0;i<550;i++)	
	{	
		while(CB_bung == 1)	{vTaskDelay(1); if(!wantExit())	break;}
	}

  robotStop(0);
 target_chan_truoc = 223;

	for(i=0;i<250;i++)	
	{
		while(bientrochantruocValue > 228)	{vTaskDelay(1); if(!wantExit())	break;}
	}
	
	robotRunAngle(-900,7,900,0.2);
	for(i=0;i<250;i++)	
	{
	while(CB_ROI_1	== 1)	{vTaskDelay (1); if(!wantExit())	break;}
	}
	speed_chan_truoc = 50;
	target_chan_truoc = 240;
//	
	robotRunAngle(-900,7,900,0.2);

	for(i=0;i<150;i++) 
	{
		while(CB_Ha_Dau == 1)		{vTaskDelay(1); if(!wantExit())	break;}
//		
//		if ( TinHieu_ChuanBi_GapThang == 1 ) {
//					kiem_tra_huong_quay_tay_gap_phia_truoc();
//					TinHieu_ChuanBi_GapThang = 0;
//				}
//		else {TinHieu_ChuanBi_GapThang =0 ;}
			
	
}
//	
	
	robotStop(0);
  speed_chan_sau = 100;
	speed_chan_truoc = 140;
	
	target_chan_truoc = 350, target_chan_sau = 350;
}

////******************************** xuong bac 200 ****************************88
void Xuong_bac_200(void)
{	
	int i;
	speed_chan_sau = 100;
	speed_chan_truoc = 130;
	
	target_chan_truoc = 242, target_chan_sau = 242;
	
	speed_tay_gat1 = 150;
	target_tay_gat1 = 148;

	speed_tay_gat2 = 250;
	target_tay_gat2 = 148;
	
	for(i=0;i<250;i++)	
	{
		while(CB_Ha_Sau == 1)	{vTaskDelay(5); if(!wantExit())	break;}
	}
	
	for(i=0;i<250;i++)	
	{
		while(bientrodaytay1Value <  145 )	{vTaskDelay(5); if(!wantExit())	break;}
	}
	robotRunAngle(-900,7,900,-0.2);

	for(i=0;i<250;i++)
	{	
		while(CB_Ha_Sau == 0)	{vTaskDelay(5); if(!wantExit())	break;}
	}

	RESET_ENCODER();
	
	while(abs(ENCODER_FR()) + abs(ENCODER_FL()) < 1300)	{vTaskDelay (1); if(!wantExit())	break;}
	
	robotStop(0);

	target_chan_sau = 460;
	
		for(i=0;i<250;i++)	
	{
		while(bientrochansauValue < 455)	{vTaskDelay(5); if(!wantExit())	break;}
	}
		robotStop(0);

	robotRunAngle(-900,7,900,-0.2);
	
	for(i=0;i<550;i++)	
	{	
		while(CB_bung == 0)	{vTaskDelay(1); if(!wantExit())	break;}
	}

	for(i=0;i<550;i++)	
	{	
		while( CB_ROI_1 == 0)	{vTaskDelay(1); if(!wantExit())	break;}
	}
		robotStop(0);
	target_chan_truoc = 460;
	
	for(i=0;i<250;i++)	
	{
		while(bientrochantruocValue < 455)	{vTaskDelay(5); if(!wantExit())	break;}
	}
	robotStop(0);

	robotRunAngle(-900,10,900,-0.2);
	
	for(i=0;i<150;i++) 
	{
		while(CB_Ha_Dau == 0)		{vTaskDelay(1); if(!wantExit())	break;}
	}
	
	robotStop(0);
	
				if ( TinHieu_ChuanBi_GapThang == 1 ) {
					kiem_tra_huong_quay_tay_gap_phia_truoc();
					TinHieu_ChuanBi_GapThang = 0;
				}
		else {TinHieu_ChuanBi_GapThang = 0 ;}
}
	
//**************** Xuong_bac_200 bam thanh phai ********
void Xuong_bac_200_bam_thanh_phai(void)
{	
	Xuong_bac_200();		
	
	for(i=0;i<1000;i++)	
	{
		while(lazeTruocValue > 25)	
			{	
					Bam_thanh_laser_phai(7,-900,900,12,2,550,50);
						if(!wantExit())	break;
			}
	}
	
		for(i=0;i<1000;i++)	
	{
		while(lazeTruocNhoValue > 148)	
			{	
					Bam_thanh_laser_phai(7,-900,900,12,2,550,50);
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
	
	target_chan_truoc = 240, target_chan_sau = 240;
	
	speed_tay_gat1 = 150;
	target_tay_gat1 = 148;

	speed_tay_gat2 = 250;
	target_tay_gat2 = 148;
	
	for(i=0;i<250;i++)	
	{
		while(CB_Ha_Sau == 1 )	{vTaskDelay(5); if(!wantExit())	break;}
	}
	
	for(i=0;i<250;i++)	
	{
		while(bientrodaytay1Value <  145 )	{vTaskDelay(5); if(!wantExit())	break;}
	}
	
	robotRunAngle(-900,7,900,-0.2);

	for(i=0;i<250;i++)
	{	
		while(CB_Ha_Sau == 0)	{vTaskDelay(5); if(!wantExit())	break;}
	}

	RESET_ENCODER();
	
	while(abs(ENCODER_FR()) + abs(ENCODER_FL()) < 1250)	{vTaskDelay (1); if(!wantExit())	break;}
	
	robotStop(0);
	target_chan_sau = 683;
//	
		for(i=0;i<250;i++)	
	{
		while(bientrochansauValue < 679)	{vTaskDelay(5); if(!wantExit())	break;}
	}
		robotStop(0);
	robotRunAngle(-900,7,900,-0.2);
	
	for(i=0;i<550;i++)	
	{	
		while(CB_bung == 0)	{vTaskDelay(1); if(!wantExit())	break;}
	}
	
	for(i=0;i<550;i++)	
	{	
		while( CB_ROI_1 == 0)	{vTaskDelay(1); if(!wantExit())	break;}
	}
		robotStop(0);

	target_chan_truoc = 683;
	
	for(i=0;i<250;i++)	
	{
		while(bientrochantruocValue < 679)	{vTaskDelay(5); if(!wantExit())	break;}
	}
	robotStop(0);

	robotRunAngle(-900,10,900,0.2);
	
	for(i=0;i<150;i++) 
	{
		while(CB_Ha_Dau == 0)		{vTaskDelay(1); if(!wantExit())	break;}
	}
////////	

	robotStop(0);
}

// ********* hanh dong qua trái phai  ***************

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

void Bam_thanh_laser_phai_cua_vao(int speed, int runangle, int AngleHead, int lazer_stable_phai, int num_change_stable, int fix_max,int rat)
{
	int fix;

	fix = abs(lazePhaiValue - lazer_stable_phai) * rat;

	if (fix > fix_max)
	fix = fix_max;

	if (lazePhaiValue - lazer_stable_phai < num_change_stable)
	{
		robotRunAngle(runangle + fix, speed, AngleHead, 0.3);
	}
	else if (lazePhaiValue - lazer_stable_phai > num_change_stable)
	{
		robotRunAngle(runangle - fix, speed, AngleHead, 0.3);
	}
	else
		robotRunAngle(runangle, speed, AngleHead, 0.3);
}


//********************************************* bam thanh laser trai ********************************************
void Bam_thanh_laser_trai(int speed, int runangle, int AngleHead, int lazer_stable_phai, int num_change_stable, int fix_max,int rat)
{
	int fix;

	fix = abs(lazeTraiValue - lazer_stable_phai) * rat;

	if (fix > fix_max)
	fix = fix_max;

	if (lazeTraiValue - lazer_stable_phai < num_change_stable)
	{
		robotRunAngle(runangle - fix, speed, AngleHead, 0.3);
	}
	else if (lazeTraiValue - lazer_stable_phai > num_change_stable)
	{
		robotRunAngle(runangle + fix, speed, AngleHead, 0.3);
	}
	else
		robotRunAngle(runangle, speed, AngleHead, 0.3);
}

void Bam_thanh_laser_trai_cua_vao(int speed, int runangle, int AngleHead, int lazer_stable_phai, int num_change_stable, int fix_max,int rat)
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

}
void Tay_2_gap_kfs_xuong(void)
{
	
}
void Tay_2_gap_kfs_dung(void)
{

}
void Tay_len_all(void)
{

}

//******************************* XOAY bang tayu **************************
void Xoay_tay_Manual(void)
{
	if (SQUARE && !R1 && !R2 && !L2 && bientroxoaytayValue > Min_xoay_tay ) 				
	{
		if(L1 && bientroxoaytayValue < Max_xoay_tay - 20)	tay_xoay = 100;
		else		tay_xoay = 40;
		tay_xoay_thuan;
		target_xoay_tay = bientroxoaytayValue;
		Man_xoay_tay = 1;
	}
	else	if (O && !R1 && !R2 && !L2 && bientroxoaytayValue < Max_xoay_tay) 	
				{
					if(L1 && bientroxoaytayValue > Min_xoay_tay + 20)	tay_xoay = 100;
					else		tay_xoay = 40;
					tay_xoay_nghich;
					target_xoay_tay = bientroxoaytayValue;
					Man_xoay_tay = 1;
				}
	else Man_xoay_tay = 0;
}
//******************************* nang ha 1 bang tay **************************
void Nang_Ha_tay1_Manual(void)
{
	if (LJOY && !R1 && !R2 && !L2 && bientrodaytay1Value < Max_tay_gat1) 				
	{
		if(L1 && bientrodaytay1Value > Min_tay_gat1 + 20)	Gat_tay1 = 150;
		else		Gat_tay1 = 70;
		Gat_tay1_len;
		target_tay_gat1 = bientrodaytay1Value;
		Man_gat1 = 1;
	}
	else	if (RJOY && !R1 && !R2 && !L2 && bientrodaytay1Value > Min_tay_gat1) 	
				{
		if(L1 && bientrodaytay1Value < Max_tay_gat1 - 20)	Gat_tay1 = 150;
	 	else		Gat_tay1 = 70;
		Gat_tay1_xuong;
		target_tay_gat1 = bientrodaytay1Value;
		Man_gat1 = 1;
				}
	else Man_gat1 = 0;
}
//******************************* nang ha 2 bang tay **************************
void Nang_Ha_tay2_Manual(void)
{
	if (TRIANGLE && !R1 && !R2 && !L2 && bientrodaytay2Value > Min_tay_gat2 ) 				
	{
		if(L1 && bientrodaytay2Value < Max_tay_gat2 - 20)	Gat_tay2 = 250;
	 	else		Gat_tay2 = 100;
		Gat_tay2_len;
		target_tay_gat2 = bientrodaytay2Value;
		Man_gat2 = 1;
	}
	else	if (X && !R1 && !R2 && !L2 && bientrodaytay2Value < Max_tay_gat2) 	
				{
		if(L1 && bientrodaytay2Value > Min_tay_gat2 + 20)	Gat_tay2 = 250;
		else	Gat_tay2 = 100;
		Gat_tay2_xuong;
		target_tay_gat2 = bientrodaytay2Value;
		Man_gat2 = 1;
				}
	else Man_gat2 = 0;
}
// **** ham kiem tra tay gap *********
void kiem_tra_tay_gap1( int giatri_xoay) {
		Tay_1_gap_kfs_xuong();

		Bom1_on;
			
		vTaskDelay (15000);
	
		Tay_1_gap_kfs_len();

	
		vTaskDelay (7000);
		
		if(HT_qua_1 == 1)	
		{
			
			target_xoay_tay = giatri_xoay + 5;
			vTaskDelay (3000);
			
			Tay_1_gap_kfs_xuong();

			Bom1_on;
			
			vTaskDelay (15000);
	
			Tay_1_gap_kfs_len();

			
			vTaskDelay (7000);

		if(HT_qua_1 == 1)	
		{
			target_xoay_tay = giatri_xoay - 5;
			vTaskDelay (3000);
			
			Tay_1_gap_kfs_xuong();

			Bom1_on;
			
			vTaskDelay (15000);
	
			Tay_1_gap_kfs_len();

			
			vTaskDelay (7000);
		}
		
	}		
		
	target_xoay_tay = giatri_xoay - 20;
		
}	


// ************* roi khoi dung thi tay ve home ***************
void vuot_rung_ve_homeTay_bac_400 (void) {
	Xuong_bac_400();
	
		speed_tay_xoay = 100;
	target_xoay_tay = 503;
		robotStop(30);
	hoan_thanh_chay_rung = 1;

}

void vuot_rung_ve_homeTay_bac_200 (void) {
	Xuong_bac_200();
	
		speed_tay_xoay = 100;
	target_xoay_tay = 503;
		robotStop(30);
	hoan_thanh_chay_rung = 1;

}
// ******************Home***************************
void vehome(void)
{
	robotResetIMU();
	speed_chan_sau = 40;
	speed_chan_truoc = 60;

	target_chan_truoc = 242;
	target_chan_sau = 240;
	su_dung_chan(350);

//	target_chan_truoc = 235;
//	target_chan_sau = 235;
	
//	speed_tay_gat1 = 150;
//	target_tay_gat1 = 151;
//	
//	speed_tay_gat2 = 250;
//	target_tay_gat2 = 151;
	
	speed_tay_gat1 = 150;
	target_tay_gat1 = 117;
	
	speed_tay_gat2 = 250;
	target_tay_gat2 = 115;
	
	Tay2_xuong;
	Tay1_xuong;
}



// su dung mam xoay toi vi tri mong muon
void su_dung_mam_xoay (int value_mucTieu_MamXoay) {
	int value_mamXoay_HienTai = bientroxoaytayValue;
	
	if (value_mamXoay_HienTai < value_mucTieu_MamXoay) {
			speed_tay_xoay = 100;
			target_xoay_tay = value_mucTieu_MamXoay;
		for(i=0;i<50;i++)	{ 
			while(bientroxoaytayValue < value_mucTieu_MamXoay - 3)	{vTaskDelay(1); if(!wantExit())	break;}
					}
	}
	
	else if (value_mamXoay_HienTai > value_mucTieu_MamXoay) {
			speed_tay_xoay = 100;
			target_xoay_tay = value_mucTieu_MamXoay;
		for(i=0;i<50;i++)	{ 
			while(bientroxoaytayValue > value_mucTieu_MamXoay + 3)	{vTaskDelay(1); if(!wantExit())	break;}
					}
	}
}

//// *** ham chuan bi tay gap phia truoc ********
void chuanbi_taygap_phiatruoc ( int tay_kep ) {
		
	// tay dau tien, dung tay 4
	if (tay_kep == 4 ) {
			speed_tay_gat2 = 250;
			target_tay_gat2 = 75;	
	
		}
				
		// tay se lay lan 2, dung tay 1
	else if ( tay_kep == 1) {
			speed_tay_xoay = 100;
			target_xoay_tay = 692;
			for(i=0;i<50;i++)	{ 
			while(bientroxoaytayValue < 690 )	{vTaskDelay(1); if(!wantExit())	break;}
					}
			speed_tay_gat1 = 250;
			target_tay_gat1 = 205;		
		}
	
	// tay se lay lan 3, dung tay 2
	else if ( tay_kep == 2 ) {
//			su_dung_mam_xoay(692);
			speed_tay_gat1 = 250;
			target_tay_gat1 = 205;		
		
	}

	// tay se lay lan 4, dung tay 3
	else if (tay_kep == 3 ) {
			speed_tay_xoay = 100;
			target_xoay_tay = 503;
			for(i=0;i<50;i++)	{ 
			while(bientroxoaytayValue > 508 )	{vTaskDelay(1); if(!wantExit())	break;}
					}
			speed_tay_gat1 = 250;
			target_tay_gat1 = 75;		
		
	}
}


// ********************* HAM LAY PHIA TRUOC ****************

// ********** gap lan 1 **********
void gap_tay4(void) 
{	
			Kep_phai_4_ra;
			Tay2_len;
			
			speed_tay_gat2 = 250;
			target_tay_gat2 = (Min_tay_gat2 + 5);
			for(i=0;i<50;i++)	{ 
					while(bientrodaytay2Value > (Min_tay_gat2 + 7) )	{vTaskDelay(1); if(!wantExit())	break;}
				}
			vTaskDelay (5000);
			Kep_phai_4_vao;
			vTaskDelay (5000);
			Tay2_xuong;	
			
			speed_tay_gat2 = 250;
			target_tay_gat2 = 145;
			for(i=0;i<50;i++)	{ 
					while(bientrodaytay2Value < 92)	{vTaskDelay(1); if(!wantExit())	break;}
				}
		
			
}

void gap_tay4_bac_400(void) 
{	
			Kep_phai_4_ra;
			Tay2_len;
			
			speed_tay_gat2 = 250;
			target_tay_gat2 = (Min_tay_gat2 + 12);
			for(i=0;i<50;i++)	{ 
					while(bientrodaytay2Value > (Min_tay_gat2 + 15) )	{vTaskDelay(1); if(!wantExit())	break;}
				}
			vTaskDelay (5000);
			Kep_phai_4_vao;
			vTaskDelay (5000);
			Tay2_xuong;	
			
			speed_tay_gat2 = 250;
			target_tay_gat2 = 145;
			for(i=0;i<50;i++)	{ 
					while(bientrodaytay2Value < 92)	{vTaskDelay(1); if(!wantExit())	break;}
				}
		
			
}


// ********** gap lan 2 **********
void gap_tay1(void) 
{			
		Tay1_len;
		speed_tay_gat1 = 250;
		target_tay_gat1 = (Max_tay_gat1- 5);
		for(i=0;i<50;i++)	{ 
					while(bientrodaytay1Value < (Max_tay_gat1 - 7) )	{vTaskDelay(1); if(!wantExit())	break;}
				}
		vTaskDelay (5000);
		Kep_phai_1_vao;
		vTaskDelay (5000);
		Tay1_xuong;
				
		speed_tay_gat1 = 150;
		target_tay_gat1 = 117;
		for(i=0;i<50;i++)	{ 
				while(bientrodaytay1Value > 120)	{vTaskDelay(1); if(!wantExit())	break;}
				}

}

// ********** gap lan 3 **********
void gap_tay2(void) 
{	
		Tay2_len;
	
		speed_tay_xoay = 100;
		target_xoay_tay = 692;
		for(i=0;i<50;i++)	{ 
		while(bientroxoaytayValue < 690 )	{vTaskDelay(1); if(!wantExit())	break;}
				}
				
		speed_tay_gat2 = 250;
		target_tay_gat2 = (Max_tay_gat2- 5);
		for(i=0;i<50;i++)	{ 
					while(bientrodaytay2Value < (Max_tay_gat2 - 7) )	{vTaskDelay(1); if(!wantExit())	break;}
				}
		vTaskDelay (5000);
		Kep_phai_2_vao;
		vTaskDelay (5000);
		Tay2_xuong;
	
		speed_tay_gat2 = 150;
		target_tay_gat2 = 115;
		for(i=0;i<50;i++)	{ 
				while(bientrodaytay2Value > 117)	{vTaskDelay(1); if(!wantExit())	break;}
				}
}

// GAP LAN 4
void gap_tay3(void)
{	
		Tay1_len;
		Kep_phai_3_ra;
		
		
		speed_tay_gat1 = 250;
		target_tay_gat1 = (Min_tay_gat1+ 5);
		for(i=0;i<50;i++)	{ 
					while(bientrodaytay1Value < (Min_tay_gat1 + 7) )	{vTaskDelay(1); if(!wantExit())	break;}
				}
		vTaskDelay (5000);
		Kep_phai_3_vao;
		vTaskDelay (5000);
		Tay1_xuong;
	
		speed_tay_gat1 = 150;
		target_tay_gat1 = 117;
		for(i=0;i<50;i++)	{ 
				while(bientrodaytay1Value < 114)	{vTaskDelay(1); if(!wantExit())	break;}
				}
		
}


// ********** xoay toi goc tay tiep theo + mo kep
void kiem_tra_huong_quay_tay_gap_phia_truoc (void) {
	
		if (da_lay_tay1 == 0 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
			
				Kep_phai_4_ra;
	
		}
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
			
					// quay mam sang tay 2
						speed_tay_xoay = 100;
						target_xoay_tay = 692;
						Kep_phai_1_ra;

//					// quay tay xuong truoc
//						speed_tay_gat1 = 250;
//						target_tay_gat1 = (Max_tay_gat1- 15);
//						for(i=0;i<50;i++)	{ 
//									while(bientrodaytay1Value < (Max_tay_gat1 - 18) )	{vTaskDelay(1); if(!wantExit())	break;}
//								}
						
						}
		
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
						speed_tay_xoay = 100;
						target_xoay_tay = 692;
						Kep_phai_2_ra;

//						// xoay tay xuong chuan bi
//						speed_tay_gat2 = 250;
//						target_tay_gat2 = (Max_tay_gat2- 15);
//						for(i=0;i<50;i++)	{ 
//									while(bientrodaytay2Value < (Max_tay_gat2 - 16) )	{vTaskDelay(1); if(!wantExit())	break;}
//								}
						}
		
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 0) {
					speed_tay_xoay = 100;
					target_xoay_tay = 503;	
					Kep_phai_3_ra;
			
//					speed_tay_gat1 = 250;
//					target_tay_gat1 = (Min_tay_gat1+ 15);
//					for(i=0;i<50;i++)	{ 
//								while(bientrodaytay1Value < (Min_tay_gat1 + 18) )	{vTaskDelay(1); if(!wantExit())	break;}
//							}
						}										
}


/// ****** gap ben trai tay 1
void kiem_tra_huong_quay_tay_trai (void) { 
			speed_tay_xoay = 100;
			target_xoay_tay = 603;
			for(i=0;i<50;i++)	{ 
			while(bientroxoaytayValue < 606 )	{vTaskDelay(1); if(!wantExit())	break;}
												}
			
			// xoay tay xuong chuan bi
			speed_tay_gat2 = 250;
			target_tay_gat2 = (Max_tay_gat2- 23);
			for(i=0;i<50;i++)	{ 
						while(bientrodaytay2Value < (Max_tay_gat2 - 26) )	{vTaskDelay(1); if(!wantExit())	break;}
					}
			}

/// ****** gap ben trai tay 3
void kiem_tra_huong_quay_tay_phai (void) { 
			speed_tay_xoay = 100;
			target_xoay_tay = 603;
			for(i=0;i<50;i++)	{ 
			while(bientroxoaytayValue < 606 )	{vTaskDelay(1); if(!wantExit())	break;}
												}
			
			// xoay tay xuong chuan bi
			speed_tay_gat2 = 250;
			target_tay_gat2 = (Max_tay_gat2- 23);
			for(i=0;i<50;i++)	{ 
						while(bientrodaytay2Value < (Max_tay_gat2 - 26) )	{vTaskDelay(1); if(!wantExit())	break;}
					}
			}

		
void Lay_phia_truoc_bac_400_tren (void) {
		
			if (da_lay_tay1 == 0 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
					gap_tay4_bac_400();
					da_lay_tay1 = 1;
					}			
			
				}

void Lay_phia_truoc_bac_200_tren (void) {
		
			if (da_lay_tay1 == 0 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
					gap_tay4();
					da_lay_tay1 = 1;
					}
			
					// dung tay lan 2
			else if (da_lay_tay1 == 1 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
					gap_tay1();
					
					da_lay_tay2 = 1;
			}
			
			// dung tay lan 3 
			else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
					gap_tay2();
			
					da_lay_tay3 = 1;
			}
			
			// dung tay lan 4
			else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 0) {
					gap_tay3();
					
					da_lay_tay4 = 1;
			}
			
}



void go_qua (void) {
	if (R2 && O) {
				Kep_phai_4_ra;
				Kep_phai_1_ra;
				Kep_phai_2_ra;
				Kep_phai_3_ra;
	
	}

}
// ****************** CAMERA DETECT TÂM *******************

#include <stdint.h>
#include <math.h>

#define A 4.64f 
#define B 207.5f  

//void can_tam_robot(int do_lech_px)
//{
//		
//    int delta = abs(do_lech_px - 100);   // chuy?n byte v? pixel l?ch
//    int kc_chay = (int)(A * delta - B);
//		
//		
//    if (do_lech_px == 100)
//    {
//        robotStop(0);
//    }
//    else if (do_lech_px > 100)   // chay phai
//    {
//				RESET_ENCODER_CHAY();
//        robotRunAngle(-900,25,0,0.1);
//				
//        while(abs(ENCODER_CHAY()) < kc_chay)
//        {
//            vTaskDelay(5);
//            if(wantExit()) break;
//        }
//    }
//    else if (do_lech_px < 100)             // chay trai
//    {
//        RESET_ENCODER_CHAY();
//        robotRunAngle(900,25,0,0.1);
//        while(abs(ENCODER_CHAY()) < kc_chay)
//        {
//            vTaskDelay(5);
//            if(wantExit()) break;
//        }
//    }
//}