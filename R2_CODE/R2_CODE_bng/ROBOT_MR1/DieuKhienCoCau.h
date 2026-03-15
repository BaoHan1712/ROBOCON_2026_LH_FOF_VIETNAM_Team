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
extern int vitri_tay41_laser_trai_GapQua;
extern int vitri_tay23_laser_trai_GapQua;


// *************** thong so tay gap ************
int	Min_chan_truoc = 238, Max_chan_truoc = 712, target_chan_truoc;
int	Min_chan_sau = 238, Max_chan_sau = 712, target_chan_sau;
int	Min_xoay_tay = 250, Max_xoay_tay = 710, target_xoay_tay;
int	Min_tay_gat1 = 160, Max_tay_gat1 = 810, target_tay_gat1;
int	Min_tay_gat2 = 240, Max_tay_gat2 = 687, target_tay_gat2;

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
void chinh_lai_vi_tri_laser_trai(int vitri, int gia_tri_lap);
void chinh_lai_vi_tri_laser_phai(int vitri, int gia_tri_lap);
void Ktra_vtri_kep4 (void);
void Ktra_vtri_kep1 (void);
void Ktra_vtri_kep2 (void);
void Ktra_vtri_kep3 (void);
void di_vao_giua (void);

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
	if (bientroxoaytayCouter++ < 70)
	{
		bientroxoaytay_SUM += bien_tro_xoay_tay;
	}
	else
	{
		bientroxoaytayValue = bientroxoaytay_SUM / 70;
		bientroxoaytayCouter = 0;
		bientroxoaytay_SUM = 0;
	}

	//-----------------------------
	if (bientrodaytay1Couter++ < 70)
	{
		bientrodaytay1_SUM += bien_tro_gat1;
	}
	else
	{
		bientrodaytay1Value = bientrodaytay1_SUM / 70;
		bientrodaytay1Couter = 0;
		bientrodaytay1_SUM = 0;
	}

//-----------------------------
	if (bientrodaytay2Couter++ < 70)
	{
		bientrodaytay2_SUM += bien_tro_gat2;
	}
	else
	{
		bientrodaytay2Value = bientrodaytay2_SUM / 70;
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

	if (abs(bientrochantruocValue - target_chan_truoc) > 2)
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

	if (abs(bientrochansauValue - target_chan_sau) > 2)
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

	if (abs(bientrodaytay1Value - target_tay_gat1) > 4)
	{
		if (bientrodaytay1Value > target_tay_gat1)			Gat_tay1_xuong;
		else																						Gat_tay1_len;

		speed_temp = abs(bientrodaytay1Value - target_tay_gat1)*20;
		if (speed_temp > speed_tay_gat1)
				speed_temp = speed_tay_gat1;
		if (speed_temp < 200)
				speed_temp = 200;
		
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

	if (abs(bientrodaytay2Value - target_tay_gat2) > 4)
	{
		if (bientrodaytay2Value > target_tay_gat2)			Gat_tay2_len;
		else																						Gat_tay2_xuong;

		speed_temp = abs(bientrodaytay2Value - target_tay_gat2)*20;
		if (speed_temp > speed_tay_gat2)
				speed_temp = speed_tay_gat2;
		if (speed_temp < 200)
				speed_temp = 200;
		
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

	if ((abs(bientroxoaytayValue - target_xoay_tay) > 1) && (abs(bientrodaytay1Value - vitri_tay1home) < 20) && (abs(bientrodaytay2Value - vitri_tay2home) < 20))
	{
		if (bientroxoaytayValue > target_xoay_tay)			tay_xoay_thuan;
		else																						tay_xoay_nghich;

		speed_temp = abs(bientroxoaytayValue - target_xoay_tay);
		if (speed_temp > speed_tay_xoay)
				speed_temp = speed_tay_xoay;
		if (speed_temp < 70)
				speed_temp = 70;
	
		tay_xoay = speed_temp;
	}
	else tay_xoay = 0;
}

void dau_di_sat_tuong (void) { 
				robotRunAngle(0,5,900,0.3);
				RESET_ENCODER();
				while(abs(ENCODER_FR()) + abs(ENCODER_FL()) < 700)	{vTaskDelay (1); if(!wantExit())	break;}
					robotStop(0);
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

	target_chan_truoc = value_chan + 3;
	target_chan_sau = value_chan;
}


void di_tren_buc_khong_thanh_2_ben (void) {	
		if (da_lay_tay1 == 0 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
			
				//// qua phai cho den khi cb roi phai  mat
					robotRunAngle(0,5,900,0.5);
								
					for(i=0;i<150;i++)
					{
						while(CB_ROI_3 == 0)	
						{	
							vTaskDelay (1);
							if(!wantExit())	break;
						}
					}
						robotStop(0);	
	
		}
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
			
					robotRunAngle(0,5,900,0.5);
								
					for(i=0;i<150;i++)
					{
						while(CB_ROI_3 == 0)	
						{	
							vTaskDelay (1);
							if(!wantExit())	break;
						}
					}
						robotStop(0);	
				}

		// quay mam sang tay 2
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
					robotRunAngle(1800,5,900,0.5);
					for(i=0;i<150;i++)
					{
						while(CB_ROI_2 == 0)	
						{	
							vTaskDelay (1);
							if(!wantExit())	break;
						}
					}
						robotStop(0);	
				}
		// quay mam sang tay 3
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 0) {
					robotRunAngle(1800,5,900,0.5);
					for(i=0;i<150;i++)
					{
						while(CB_ROI_2 == 0)	
						{	
							vTaskDelay (1);
							if(!wantExit())	break;
						}
					}
						robotStop(0);	
			
						}										


}

//******************************** leo bac 200 ****************************
void Leo_bac_200(void)
{	
		int i;
			// nâng bánh trc lên 
	speed_chan_sau = 115;
	speed_chan_truoc = 140;
	
	target_chan_truoc = Min_chan_truoc + 250;
	target_chan_sau = Min_chan_sau + 245;
	
 	for(i=0;i<50;i++)		
	{
		while(abs(bientrochansauValue - target_chan_sau) > 10)	{vTaskDelay(1); if(!wantExit())	break;}
	}
	
	robotRunAngle(-900,8,900,0.5);
	for(i=0;i<250;i++)	
	{	
		while(CB_Ha_Sau == 1)	{vTaskDelay(1); if(!wantExit())	break;}
	}
	robotStop(60);
	////	// nâng bánh sau lên 
	speed_chan_sau = 250;
	target_chan_sau = Min_chan_sau - 3;
	for(i=0;i<50;i++)		
	{
			while(abs(bientrochansauValue - target_chan_sau) > 10)	{vTaskDelay(1); if(!wantExit())	break;}
	}
	
	vTaskDelay(3000);
	
	robotRunAngle(-900,12,900,0.2);
	
	for(i=0;i<550;i++)	
	{	
		while(CB_bung_duoi == 1)	{vTaskDelay(2); if(!wantExit())	break;}
	}

	speed_chan_sau = 30;
	target_chan_sau = Min_chan_sau + 10;
	
	
	
	
		for(i=0;i<550;i++)	
	{	
		while(CB_bung == 1)	{vTaskDelay(1); if(!wantExit())	break;}
	}

  robotStop(0);
	speed_chan_truoc = 250;
	target_chan_truoc = Min_chan_truoc + 3;

	for(i=0;i<250;i++)	
	{
		while(abs(bientrochantruocValue - target_chan_truoc) > 10)	{vTaskDelay(1); if(!wantExit())	break;}
	}
	
	vTaskDelay(3000);
	
	
	
	robotRunAngle(-900,7,900,0.2);
	for(i=0;i<250;i++)	
	{
	while(CB_ROI_1	== 1 )	{vTaskDelay (1); if(!wantExit())	break;}
	}

	RESET_ENCODER(); 
	while(abs(ENCODER_FR()) + abs(ENCODER_FL()) < 400)	{vTaskDelay (5); if(!wantExit())	break;}

  speed_chan_sau = 100;
	speed_chan_truoc = 140;
	target_chan_truoc = 260, target_chan_sau = 260;
	
	robotRunAngle(-900,6,900,0.2);

	for(i=0;i<100;i++) 
		{
		while(CB_Ha_Dau == 1)		{vTaskDelay(1); if(!wantExit())	break;}
		}
	
	robotStop(0);

	// len xong roi quay tay chuan bi
	kiem_tra_huong_quay_tay_gap_phia_truoc();

}

//***************** leo bac 200 bam thanh laser phai va laser truoc *************

void Leo_bac_200_bam_thanh_phai(void)
{	
	int vitri = 153;
	int vitri_tay41 = vitri_tay41_laser_trai_GapQua;
	int vitri_tay23 = vitri_tay23_laser_trai_GapQua;
	
	Leo_bac_200();
	su_dung_chan(510);
		
		// chay toi khi laser sau cham 
		for(i=0;i<150;i++)		
				{
					while(bientrochansauValue < 500)	
					{
						if(!wantExit())	break;
						vTaskDelay (1);
					}
				}		
		robotRunAngle(-900,8,900,0.5);
	
		for(i=0;i<1550;i++)
				{
					while( CB_vtri_leo == 0)	
					{	
						if(!wantExit())	break;
						vTaskDelay (1);
					}
				}
				
		
	robotStop(0); 
	if (TinHieu_ChuanBi_GapThang == 1) {
		
	// chinh lai vi tri cho tay gap
		if (da_lay_tay1 == 0 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
					chinh_lai_vi_tri_laser_trai(vitri_tay41, 1000);
					robotStop(0);
					dau_di_sat_tuong();
			}
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
					chinh_lai_vi_tri_laser_trai(vitri_tay41, 1000);	
					robotStop(0);
					dau_di_sat_tuong();
			}

		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
						chinh_lai_vi_tri_laser_trai(vitri_tay23, 1000);	
						robotStop(0);
						dau_di_sat_tuong();
						}
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 0) {
						chinh_lai_vi_tri_laser_trai(vitri_tay23, 1000);	
						robotStop(0);
						dau_di_sat_tuong();
						}			
		}
		su_dung_chan(565);
		
		robotStop(0); 			
		
	
}

///// ********* leo bac 200 khong thanh **************
void Leo_bac_200_ko_thanh(void)
{	
		Leo_bac_200();
		su_dung_chan(265);
		// chay toi khi mat cam bien sau
		robotRunAngle(-900,8,900,0.1);
		for(i=0;i<250;i++)
				{
					while(CB_vtri_leo == 0)	
					{	
						vTaskDelay (1);
						if(!wantExit())	break;
					}
				}
				
		robotStop(0);
		vTaskDelay (2000);
		if (TinHieu_ChuanBi_GapThang == 1) {
		di_tren_buc_khong_thanh_2_ben();
		}
}



// ************* leo bac 200 bam thanh phai encoder *************

void Leo_bac_200_bam_thanh_phai_encoder(void)
{	
		int vitri_tay41 = vitri_tay41_laser_trai_GapQua;
		int vitri_tay23 = vitri_tay23_laser_trai_GapQua;

		Leo_bac_200();
	
		su_dung_chan(265);
		// chay toi khi mat cam bien sau
		robotRunAngle(-900,8,900,0.3);
		for(i=0;i<250;i++)
				{
					while(CB_vtri_leo == 0)	
					{	
						vTaskDelay (1);
						if(!wantExit())	break;
					}
				}
				
		robotStop(0);
		vTaskDelay (2000);	
	
	if (TinHieu_ChuanBi_GapThang == 1) {
	// chinh lai vi tri cho tay gap
		if (da_lay_tay1 == 0 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
					chinh_lai_vi_tri_laser_trai(vitri_tay41, 1000);
			}
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
					chinh_lai_vi_tri_laser_trai(vitri_tay41, 1000);	
			}

		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
					robotRunAngle(1800,5,900,0.5);
					for(i=0;i<150;i++)
						{
						while(CB_ROI_4 == 0)	
							{	
							vTaskDelay (1);
							if(!wantExit())	break;
							}
						}
						robotStop(0);	
				}
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 0) {
					robotRunAngle(1800,5,900,0.5);
					for(i=0;i<150;i++)
					{
						while(CB_ROI_4 == 0)	
						{	
							vTaskDelay (1);
							if(!wantExit())	break;
						}
					}
						robotStop(0);	
						}

		}

}
/// ***************leo xong bam thanh trai encoder ****************

void Leo_bac_200_bam_thanh_trai_encoder(void)
{	
	int vitri = 154;
	Leo_bac_200();
		
// **** leo xong bam thanh phai dua vao encoder
	
	for(i=0;i<1000;i++)	
	{
		while(CB_Ha_Dau == 0 )	
			{	
					Bam_thanh_laser_trai(7,-900,-880,vitri,2,550,50);
					vTaskDelay(1);
					if(!wantExit())	break;
			}
	}
	
	robotStop(0);
	
	robotRunAngle(900,5,-900,0.2);
	
	RESET_ENCODER();
	
	while(abs(ENCODER_RR()) + abs(ENCODER_RL()) < 150)	
	{	
		vTaskDelay (1); if(!wantExit())	break;
	}
	robotStop(0);

}


//***************** leo bac 200 bam thanh laser trai + laser truoc *************

void Leo_bac_200_bam_thanh_trai(void)
{	
	int vitri = 154;
	Leo_bac_200();
	
// **** leo xong bam thanh trai
	
	for(i=0;i<1000;i++)	
	{
		while(lazeTruocValue > 25)	
			{	
					Bam_thanh_laser_trai(7,-900,-880,vitri,2,550,50);
						if(!wantExit())	break;
			}
	}
	
		for(i=0;i<1000;i++)	
	{
		while(lazeTruocNhoValue > 148)	
			{	
					Bam_thanh_laser_trai(7,-900,-880,vitri,2,550,50);
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
	
	Man_gat2 = 1;
	Gat_tay2 = 0;
	
	speed_chan_sau = 90;
	speed_chan_truoc = 130;
	
	target_chan_truoc = Max_chan_truoc - 4, target_chan_sau = Max_chan_sau - 4;
	
	for(i=0;i<250;i++)	
	{
		while(abs(bientrochansauValue - target_chan_sau) > 10)	{vTaskDelay(1); if(!wantExit())	break;}
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
	
	speed_chan_sau = 220;
	target_chan_sau = Min_chan_sau - 3;

	for(i=0;i<50;i++)		
	{
		while(abs(bientrochansauValue - target_chan_sau) > 10)	{vTaskDelay(5); if(!wantExit())	break;}
	}
	
	vTaskDelay(3000);
	
//	target_chan_truoc = 702;
	
	robotRunAngle(-900,12,900,0.2);
	
	for(i=0;i<550;i++)	
	{	
		while(CB_bung_duoi == 1)	{vTaskDelay(2); if(!wantExit())	break;}
	}

	speed_chan_sau = 30;
	target_chan_sau = Min_chan_sau + 10;
	
	for(i=0;i<550;i++)	
	{	
		while(CB_bung == 1)	{vTaskDelay(1); if(!wantExit())	break;}
	}

  robotStop(0);
	speed_chan_truoc = 250;
	target_chan_truoc = Min_chan_truoc + 3;

	for(i=0;i<250;i++)	
	{
		while(abs(bientrochantruocValue - target_chan_truoc) > 10)	{vTaskDelay(1); if(!wantExit())	break;}
	}
	
	vTaskDelay(3000);
	
	robotRunAngle(-900,7,900,0.2);
	for(i=0;i<250;i++)	
	{
	while(CB_ROI_1	== 1 )	{vTaskDelay (1); if(!wantExit())	break;}
	}

	RESET_ENCODER(); 
	while(abs(ENCODER_FR()) + abs(ENCODER_FL()) < 400)	{vTaskDelay (5); if(!wantExit())	break;}

  speed_chan_sau = 100;
	speed_chan_truoc = 140;
	target_chan_truoc = 260, target_chan_sau = 260;
	
	robotRunAngle(-900,6,900,0.2);

	for(i=0;i<100;i++) 
		{
		while(CB_Ha_Dau == 1)		{vTaskDelay(1); if(!wantExit())	break;}
		}
	Man_gat2 = 0;
	robotStop(0);
	kiem_tra_huong_quay_tay_gap_phia_truoc();
}

void Leo_bac_400_ko_thanh(void)
{		
		Leo_bac_400();
//		kiem_tra_huong_quay_tay_gap_phia_truoc();
		su_dung_chan(265);
		// chay toi khi mat cam bien sau
		robotRunAngle(-900,8,900,0.1);
		for(i=0;i<250;i++)
				{
					while(CB_vtri_leo == 0)	
					{	
						vTaskDelay (1);
						if(!wantExit())	break;
					}
				}
				
		robotStop(0);
		vTaskDelay (2000);
		if (TinHieu_ChuanBi_GapThang == 1 ) {
		di_tren_buc_khong_thanh_2_ben();
		TinHieu_ChuanBi_GapThang == 0;
		}

}

void Leo_bac_400_co_thanh(void) {
		Leo_bac_400();
		su_dung_chan(510);
		
		// chay toi khi laser sau cham 1
		robotRunAngle(-900,8,900,0.1);
		for(i=0;i<150;i++)		
				{
					while(bientrochansauValue < 500)	
					{
						if(!wantExit())	break;
						vTaskDelay (1);
					}
				}		
	
		for(i=0;i<1550;i++)
				{
					while( CB_vtri_leo == 1)	
					{	
						vTaskDelay (1);
						if(!wantExit())	break;
						vTaskDelay (1);
					}
				}
				
		robotStop(0);
		vTaskDelay (2000);
		if (TinHieu_ChuanBi_GapThang == 1) {
		di_tren_buc_khong_thanh_2_ben();
			
		}
	//	do Chan len
	su_dung_chan(580);
		
	robotStop(0); 

}

////******************************** xuong bac 200 ****************************88
void Xuong_bac_200(void)
{	
	int i;
	speed_chan_sau = 100;
	speed_chan_truoc = 130;
	
	target_chan_truoc = Min_chan_truoc + 10, target_chan_sau = Min_chan_sau + 10;
	for(i=0;i<50;i++)		
	{
		while(abs(bientrochansauValue - target_chan_sau) > 8)	{vTaskDelay(1); if(!wantExit())	break;}
	}
	
	robotRunAngle(-900,7,900,-0.2);

	for(i=0;i<250;i++)
	{	
		while(CB_vtri_leo == 0)	{vTaskDelay(5); if(!wantExit())	break;}
	}
	
	vTaskDelay(2000);
	
	target_chan_sau = Min_chan_sau + 5;
	
	robotRunAngle(-900,7,900,-0.2);
	RESET_ENCODER();
	
	while(abs(ENCODER_FR()) + abs(ENCODER_FL()) < 800)	{vTaskDelay (1); if(!wantExit())	break;}
	
	robotStop(0);
		
	speed_chan_sau = 150;
	target_chan_sau = Min_chan_sau + 240;
	
	for(i=0;i<50;i++)		
	{
		while(abs(bientrochansauValue - target_chan_sau) > 60)	{vTaskDelay(1); if(!wantExit())	break;}
	}
	
	speed_chan_sau = 30;
	
	for(i=0;i<50;i++)		
	{
		while(abs(bientrochansauValue - target_chan_sau) > 6)	{vTaskDelay(1); if(!wantExit())	break;}
	}
	
	vTaskDelay(2000);

	robotRunAngle(-900,7,900,-0.2);
	
	for(i=0;i<550;i++)	
	{	
		while(CB_bung == 0)	{vTaskDelay(1); if(!wantExit())	break;}
	}
	
	target_chan_truoc = Min_chan_truoc + 5;

	
	for(i=0;i<1000;i++)	
	{	
		while( CB_ROI_1 == 0 &&  CB_ROI_2 == 0)	{vTaskDelay(1); if(!wantExit())	break;}
	}
	
	vTaskDelay(4000);
	
	robotStop(0);
	
//	
	speed_chan_truoc = 150;
	target_chan_truoc = Min_chan_truoc + 240;
	
	for(i=0;i<50;i++)		
	{
		while(abs(bientrochantruocValue - target_chan_truoc) > 60)	{vTaskDelay(1); if(!wantExit())	break;}
	}
	
	speed_chan_truoc = 20;
	
	for(i=0;i<50;i++)		
	{
		while(abs(bientrochantruocValue - target_chan_truoc) > 6)	{vTaskDelay(1); if(!wantExit())	break;}
	}
	
	robotRunAngle(-900,10,900,-0.2);
	
	for(i=0;i<150;i++) 
	{
		while(CB_Ha_Dau == 0)		{vTaskDelay(1); if(!wantExit())	break;}
	}
	
	robotStop(0);
	kiem_tra_huong_quay_tay_gap_phia_truoc();

}
	
void xuong_bac_200_end (void) {
	Xuong_bac_200();

}
//**************** Xuong_bac_200 bam thanh phai + laser ********
void Xuong_bac_200_bam_thanh_phai(void)
{	
	int vitri = 154;
	int vitri_tay41 = 161;
	int vitri_tay23 = 226;
	
	Xuong_bac_200();		
	
	su_dung_chan(510);
		// chay toi khi laser sau cham 1
		robotRunAngle(-900,8,900,0.5);
		for(i=0;i<150;i++)		
				{
					while(bientrochansauValue < 500)	
					{
						if(!wantExit())	break;
						vTaskDelay (1);
					}
				}		
	
	for(i=0;i<1550;i++)
				{
					while( CB_vtri_leo == 1)	
					{	
						if(!wantExit())	break;
						vTaskDelay (1);
					}
				}
				
		robotStop(0); 
		if (TinHieu_ChuanBi_GapThang == 1 ) {
	// chinh lai vi tri cho tay gap
		if (da_lay_tay1 == 0 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
					chinh_lai_vi_tri_laser_trai(vitri_tay41, 1000);
						robotRunAngle(-900,5,900,0.3);
						RESET_ENCODER();
						while(abs(ENCODER_FR()) + abs(ENCODER_FL()) < 700)	{vTaskDelay (1); if(!wantExit())	break;}
							robotStop(0);
						
			}
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
					chinh_lai_vi_tri_laser_trai(vitri_tay41, 1000);	
			
						robotRunAngle(-900,5,900,0.3);
						RESET_ENCODER();
						while(abs(ENCODER_FR()) + abs(ENCODER_FL()) < 700)	{vTaskDelay (1); if(!wantExit())	break;}
							robotStop(0);
						
			}

		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
						robotRunAngle(1800,5,900,0.5);
					for(i=0;i<150;i++)
					{
						while(CB_ROI_2 == 0)	
						{	
							vTaskDelay (1);
							if(!wantExit())	break;
						}
					}
						robotStop(0);
						
						}
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 0) {
						robotRunAngle(1800,5,900,0.5);
					for(i=0;i<150;i++)
					{
						while(CB_ROI_2 == 0)	
						{	
							vTaskDelay (1);
							if(!wantExit())	break;
						}
					}
						robotStop(0);
						
					}
				}		
		su_dung_chan(565);
		
		robotStop(0); 	
	
	
	
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
		int vitri_tay23 = vitri_tay23_phai_laser_GapQua;
		Xuong_bac_200();
		su_dung_chan(265);
		// chay toi khi mat cam bien sau
		robotRunAngle(-900,8,900,0.3);
		for(i=0;i<250;i++)
				{
					while(CB_vtri_leo == 0)	
					{	
						vTaskDelay (1);
						if(!wantExit())	break;
					}
				}
				
		robotStop(0);
		vTaskDelay (2000);	
	
	if (TinHieu_ChuanBi_GapThang == 1) {
	// chinh lai vi tri cho tay gap
		if (da_lay_tay1 == 0 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
					robotRunAngle(0,5,900,0.5);
					for(i=0;i<150;i++)
						{
						while(CB_ROI_3 == 0)	
							{	
							vTaskDelay (1);
							if(!wantExit())	break;
							}
						}
						robotStop(0);	
			}
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
					robotRunAngle(0,5,900,0.5);
					for(i=0;i<150;i++)
						{
						while(CB_ROI_3 == 0)	
							{	
							vTaskDelay (1);
							if(!wantExit())	break;
							}
						}
						robotStop(0);
			}

		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
					chinh_lai_vi_tri_laser_phai(vitri_tay23, 1000);
					
				}
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 0) {
					chinh_lai_vi_tri_laser_phai(vitri_tay23, 1000);
						}
			}

}

// ********* hanh dong qua trái phai  ***************


// qua trai len 400 o cua vao rung

void qua_trai_len_bac_400(void) {
	su_dung_chan(695);
	
	for(i=0;i<250;i++)	
	{
		while(bientrochansauValue < 690)
								{	
		vTaskDelay (1);
		if(!wantExit())	break;
					}
	}
	
	kiem_tra_huong_quay_tay_gap_phia_truoc();
	
	robotRunAngle(1800,15,900,0.2);
	for(i=0;i<250;i++)
				{
					while(lazePhaiValue > 380)	
					{	
						vTaskDelay (1);
						if(!wantExit())	break;
					}
				}
				
	robotRunAngle(1800,7,900,0.2);
	for(i=0;i<250;i++)
				{
					while(lazePhaiValue > 330)	
					{	
						vTaskDelay (1);
						if(!wantExit())	break;
					}
				}
		
	robotRunAngle(-900,6,900,0.2);
	RESET_ENCODER(); 
				
	while(abs(ENCODER_FR()) + abs(ENCODER_FL()) < 1000)	
		{	
				vTaskDelay (1);
				if(!wantExit())	break;
		}		
		robotStop(0);
		
		if (da_lay_tay1 == 1 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
					chinh_lai_vi_tri_laser_phai(307, 1000);
					}
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
					chinh_lai_vi_tri_laser_phai(267, 1000);
					}
		
}

//============== Sang phai lên bac 400 o ria rung ===================

void qua_phai_len_bac_400(void) {
	su_dung_chan(695);
	
	for(i=0;i<250;i++)	
	{
		while(bientrochansauValue < 690)
								{	
		vTaskDelay (1);
		if(!wantExit())	break;
					}
	}
	
	kiem_tra_huong_quay_tay_gap_phia_truoc();
	
	robotRunAngle(0,15,900,0.2);
	for(i=0;i<250;i++)
				{
					while(lazeTraiValue > 400)	
					{	
						vTaskDelay (1);
						if(!wantExit())	break;
					}
				}
				
	robotRunAngle(0,7,900,0.2);
	for(i=0;i<250;i++)
				{
					while(lazeTraiValue > 307)	
					{	
						vTaskDelay (1);
						if(!wantExit())	break;
					}
				}
		
	robotRunAngle(-900,6,900,0.2);
	RESET_ENCODER(); 
				

	
	while(abs(ENCODER_FR()) + abs(ENCODER_FL()) < 500)	
		{	
				vTaskDelay (5);
				if(!wantExit())	break;
		}		
		robotStop(0);
		if (da_lay_tay1 == 1 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
					chinh_lai_vi_tri_laser_trai(307, 1000);
					}
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
					chinh_lai_vi_tri_laser_trai(262, 1000);
					}
		
		
}
//============== Sang trai lên bac 200 o ria ===================
void qua_trai_len_bac_200_cua_vao(void) {

	
	kiem_tra_huong_quay_tay_gap_phia_truoc();
	
	robotRunAngle(1800,15,900,0.2);
	for(i=0;i<250;i++)
				{
					while(lazeTraiValue < 430)	
					{	
						vTaskDelay (1);
						if(!wantExit())	break;
					}
				}
				
	robotRunAngle(1800,7,900,0.2);
	for(i=0;i<250;i++)
				{
					while(lazeTraiValue < 460)	
					{	
						vTaskDelay (1);
						if(!wantExit())	break;
					}
				}
	su_dung_chan(580);
	RESET_ENCODER(); 
				
	while(abs(ENCODER_FR()) + abs(ENCODER_FL()) < 1700)	
		{	
				Bam_thanh_laser_trai(8,-900,900,460,2,50,30);
				if(!wantExit())	break;
		}
		
	robotStop(0); 
	chinh_lai_vi_tri_laser_trai(460, 1000);
}

//============== Sang phai lên bac 200 o ria ===================
void qua_phai_len_bac_200_cua_vao(void) {

	// kiem tra tay gap
	kiem_tra_huong_quay_tay_gap_phia_truoc();
	
	robotRunAngle(0,15,900,0.2);
	for(i=0;i<250;i++)
				{
					while(lazePhaiValue < 380)	
					{	
						vTaskDelay (1);
						if(!wantExit())	break;
					}
				}
				
	robotRunAngle(0,7,900,0.2);
	for(i=0;i<250;i++)
				{
					while(lazePhaiValue < 410)	
					{	
						vTaskDelay (1);
						if(!wantExit())	break;
					}
				}
				
		su_dung_chan(575);
		
	robotRunAngle(-900,6,900,0.2);
	RESET_ENCODER(); 
				
	while(abs(ENCODER_FR()) + abs(ENCODER_FL()) < 1000)	
		{	
				vTaskDelay (5);
				if(!wantExit())	break;
		}		
		robotStop(0);
		chinh_lai_vi_tri_laser_phai(410, 50);
		
}


	void Xuong_bac_400 (void)
{	
	int i;
	speed_chan_sau = 100;
	speed_chan_truoc = 130;
	
	target_chan_truoc = Min_chan_truoc + 10, target_chan_sau = Min_chan_sau + 10;
	for(i=0;i<50;i++)		
	{
		while(abs(bientrochansauValue - target_chan_sau) > 8)	{vTaskDelay(1); if(!wantExit())	break;}
	}
	
	robotRunAngle(-900,7,900,-0.2);

	for(i=0;i<250;i++)
	{	
		while(CB_vtri_leo == 0)	{vTaskDelay(5); if(!wantExit())	break;}
	}
	
	vTaskDelay(2000);
	
	target_chan_sau = Min_chan_sau + 5;
	
	robotRunAngle(-900,7,900,-0.2);
	RESET_ENCODER();
	
	while(abs(ENCODER_FR()) + abs(ENCODER_FL()) < 800)	{vTaskDelay (1); if(!wantExit())	break;}
	
	robotStop(0);
		
	speed_chan_sau = 250;
	target_chan_sau = Max_chan_sau - 10;
	
	for(i=0;i<50;i++)		
	{
		while(abs(bientrochansauValue - target_chan_sau) > 100)	{vTaskDelay(1); if(!wantExit())	break;}
	}
	
	speed_chan_sau = 20;
	
	for(i=0;i<50;i++)		
	{
		while(abs(bientrochansauValue - target_chan_sau) > 6)	{vTaskDelay(1); if(!wantExit())	break;}
	}
	
	vTaskDelay(2000);

	robotRunAngle(-900,7,900,-0.2);
	
	for(i=0;i<550;i++)	
	{	
		while(CB_bung == 0)	{vTaskDelay(1); if(!wantExit())	break;}
	}
	
	target_chan_truoc = Min_chan_truoc + 5;

	
	for(i=0;i<1000;i++)	
	{	
		while( CB_ROI_1 == 0 ||  CB_ROI_2 == 0)	{vTaskDelay(1); if(!wantExit())	break;}
	}
	
	vTaskDelay(4000);
	
	robotStop(0);
	
	
	
//	robotRunAngle(-900,7,900,-0.2);
//	RESET_ENCODER();
//	
//	while(abs(ENCODER_RR()) + abs(ENCODER_RL()) < 680)	{vTaskDelay (1); if(!wantExit())	break;}
//	
//	robotStop(0);
//	
	speed_chan_truoc = 250;
	target_chan_truoc = Max_chan_truoc - 10;
	
	for(i=0;i<50;i++)		
	{
		while(abs(bientrochantruocValue - target_chan_truoc) > 100)	{vTaskDelay(1); if(!wantExit())	break;}
	}
	
	speed_chan_truoc = 20;
	
	for(i=0;i<50;i++)		
	{
		while(abs(bientrochantruocValue - target_chan_truoc) > 6)	{vTaskDelay(1); if(!wantExit())	break;}
	}
	
	robotRunAngle(-900,10,900,-0.2);
	
	for(i=0;i<150;i++) 
	{
		while(CB_Ha_Dau == 0)		{vTaskDelay(1); if(!wantExit())	break;}
	}
	
	robotStop(0);
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


//******************************* XOAY bang tayu **************************
void Xoay_tay_Manual(void)
{
	if (SQUARE && !R1 && !R2 && !L2 && bientroxoaytayValue > Min_xoay_tay ) 				
	{
		if(L1 && bientroxoaytayValue < Max_xoay_tay - 20)	tay_xoay = 50;
		else		tay_xoay = 20;
		tay_xoay_thuan;
		target_xoay_tay = bientroxoaytayValue;
		Man_xoay_tay = 1;
	}
	else	if (O && !R1 && !R2 && !L2 && bientroxoaytayValue < Max_xoay_tay) 	
				{
					if(L1 && bientroxoaytayValue > Min_xoay_tay + 20)	tay_xoay = 50;
					else		tay_xoay = 20;
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
	else Man_gat1 = 0, Gat_tay1 = 0;
}
//******************************* nang ha 2 bang tay **************************
void Nang_Ha_tay2_Manual(void)
{
	if (TRIANGLE && !R1 && !R2 && !L2 && bientrodaytay2Value > Min_tay_gat2 ) 				
	{
		if(L1 && bientrodaytay2Value < Max_tay_gat2 - 20)	Gat_tay2 = 150;
	 	else		Gat_tay2 = 100;
		Gat_tay2_len;
		target_tay_gat2 = bientrodaytay2Value;
		Man_gat2 = 1;
	}
	else	if (X && !R1 && !R2 && !L2 && bientrodaytay2Value < Max_tay_gat2) 	
				{
		if(L1 && bientrodaytay2Value > Min_tay_gat2 + 20)	Gat_tay2 = 150;
		else	Gat_tay2 = 100;
		Gat_tay2_xuong;
		target_tay_gat2 = bientrodaytay2Value;
		Man_gat2 = 1;
				}
	else Man_gat2 = 0, Gat_tay2 = 0;
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
	target_xoay_tay = vi_tri_tay_43;
		robotStop(30);
	hoan_thanh_chay_rung = 1;

}

void vuot_rung_ve_homeTay_bac_200 (void) {
	Xuong_bac_200();
	
		speed_tay_xoay = 100;
	target_xoay_tay = 507;
		robotStop(30);
	hoan_thanh_chay_rung = 1;

}
// ******************Home***************************
void vehome(void)
{
	robotResetIMU();

		Nang_nhanh();

	target_chan_truoc = 350;
	target_chan_sau = 350;

	speed_tay_gat2 = 250;
	target_tay_gat2 = 470;
	
	speed_tay_gat1 = 250;
	target_tay_gat1 = 470;
	
		speed_tay_xoay = 100;
	target_xoay_tay = vi_tri_tay_43;
	
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


/// *************  MODULE GAP TUNG TAY BAC 400 *************************

void gap_tay4_bac_400(void) 
{	
			Kep_phai_4_ra;
			Tay2_len;
	
			speed_tay_gat2 = 250;
			target_tay_gat2 = Min_tay_gat2 + 85;
			for(i=0;i<50;i++)	{ 
							while(abs(bientrodaytay2Value - target_tay_gat2)> 10 )	{vTaskDelay(1); if(!wantExit())	break;}
					}
			Ktra_vtri_kep4(); // kiem tra hop 
			vTaskDelay (1000);
			
			speed_tay_gat2 = 250;
			target_tay_gat2 = (Min_tay_gat2 + 7);
			for(i=0;i<50;i++)	{ 
				while(abs(bientrodaytay2Value - target_tay_gat2)> 10 )	{vTaskDelay(1); if(!wantExit())	break;}
				}
			vTaskDelay (7000);
			Kep_phai_4_vao;
			vTaskDelay (5000);
			Tay2_xuong;	
			
			speed_tay_gat2 = 250;
			target_tay_gat2 = vitri_tay2home;
			for(i=0;i<50;i++)	{ 
					while(abs(bientrodaytay2Value - target_tay_gat2)> 10 )	
			{vTaskDelay(1); if(!wantExit())	break;}
				}
			robotStop(0);
			
}

// ********** gap lan 2 **********
void gap_tay1_bac_400(void) 
{		
		Kep_phai_1_ra;
		Tay1_len;
	
		speed_tay_gat1 = 250;
		target_tay_gat1 = (Max_tay_gat1- 88);
		for(i=0;i<50;i++)	{ 
						while(abs(bientrodaytay1Value - target_tay_gat1)> 10 )	{vTaskDelay(1); if(!wantExit())	break;}
				}
		Ktra_vtri_kep1(); // kiem tra hop tay 1
		vTaskDelay (1000);
		
				speed_tay_gat1 = 250;
		target_tay_gat1 = (Max_tay_gat1- 7);
		for(i=0;i<50;i++)	{ 
						while(abs(bientrodaytay1Value - target_tay_gat1)> 10 )	{vTaskDelay(1); if(!wantExit())	break;}
				}
		vTaskDelay (7000);
		Kep_phai_1_vao;
		vTaskDelay (1000);
		Tay1_xuong;
				
		speed_tay_gat1 = 150;
		target_tay_gat1 = vitri_tay1home;
		for(i=0;i<50;i++)	{ 
					while(abs(bientrodaytay1Value - target_tay_gat1)> 10 )	{vTaskDelay(1); if(!wantExit())	break;}
				}

}

// ********** gap lan 3 **********
void gap_tay2_bac_400(void) 
{	
		Kep_phai_2_ra;
		Tay2_len;
	
		speed_tay_xoay = 100;
		target_xoay_tay = 692;
		for(i=0;i<50;i++)	{ 
		while(bientroxoaytayValue < 690 )	{vTaskDelay(1); if(!wantExit())	break;}
				}
		
		speed_tay_gat2 = 250;
		target_tay_gat2 = (Max_tay_gat2 - 85 );
		for(i=0;i<50;i++)	{ 
						while(abs(bientrodaytay2Value - target_tay_gat2)> 10 )	{vTaskDelay(1); if(!wantExit())	break;}
				}
		
		Ktra_vtri_kep2(); // kiem tra hop tay 2
		vTaskDelay (1000);
				
		speed_tay_gat2 = 250;
		target_tay_gat2 = (Max_tay_gat2 - 7 );
		for(i=0;i<50;i++)	{ 
						while(abs(bientrodaytay2Value - target_tay_gat2)> 10 )	{vTaskDelay(1); if(!wantExit())	break;}
				}
		vTaskDelay (7000);
		Kep_phai_2_vao;
		vTaskDelay (5000);
		Tay2_xuong;
	
		speed_tay_gat2 = 250;
		target_tay_gat2 = vitri_tay2home;
		for(i=0;i<50;i++)	{ 
					while(abs(bientrodaytay2Value - target_tay_gat2)> 10)	{vTaskDelay(1); if(!wantExit())	break;}
				}
}


/// ************* MODULE GAP TUNG TAY BAC 200 TREN *************************

// ********** gap lan 1 **********
void gap_tay4(void) 
{	
			Kep_phai_4_ra;
			Tay2_len;
	
			speed_tay_gat2 = 250;
			target_tay_gat2 = Min_tay_gat2 + 25;
			for(i=0;i<50;i++)	{ 
							while(abs(bientrodaytay2Value - target_tay_gat2)> 10 )	{vTaskDelay(1); if(!wantExit())	break;}
					}
			Ktra_vtri_kep4(); // kiem tra hop 
			vTaskDelay (1000);
			
			speed_tay_gat2 = 250;
			target_tay_gat2 = Min_tay_gat2 ;
			for(i=0;i<550;i++)	{ 

					while(abs(bientrodaytay2Value - target_tay_gat2)> 10 )	
					{vTaskDelay(1); if(!wantExit())	break;}
				}
			
			vTaskDelay (7000);
			Kep_phai_4_vao;
			vTaskDelay (5000);
			Tay2_xuong;	
			
			speed_tay_gat2 = 250;
			target_tay_gat2 = vitri_tay2home;
			for(i=0;i<50;i++)	{ 
					while(abs(bientrodaytay2Value - target_tay_gat2)> 10 )	{vTaskDelay(1); if(!wantExit())	break;}
				}
	
}

// ********** gap lan 2 **********
void gap_tay1(void) 
{		
		Kep_phai_1_ra;
		Tay1_len;
		speed_tay_gat1 = 200;
		target_tay_gat1 = Max_tay_gat1 - 50;
		for(i=0;i<50;i++)	{ 
						while(abs(bientrodaytay1Value - target_tay_gat1)> 10 )	{vTaskDelay(1); if(!wantExit())	break;}
				}
		Ktra_vtri_kep1(); // kiem tra hop 
	
		speed_tay_gat1 = 200;
		target_tay_gat1 = (Max_tay_gat1 - 5);
		for(i=0;i<50;i++)	{ 
					while(abs(bientrodaytay1Value - target_tay_gat1)> 10 )	{vTaskDelay(1); if(!wantExit())	break;}
				}
		vTaskDelay (3000);
		Kep_phai_1_vao;
		vTaskDelay (5000);
		Tay1_xuong;
				
		speed_tay_gat1 = 250;
		target_tay_gat1 = vitri_tay1home;
		for(i=0;i<50;i++)	{ 
				while(abs(bientrodaytay1Value - target_tay_gat1)> 10 )	{vTaskDelay(1); if(!wantExit())	break;}
				}
}

// ********** gap lan 3 **********
void gap_tay2(void) 
{	
		Kep_phai_2_ra;
		Tay2_len;
	
		speed_tay_gat2 = 250;
		target_tay_gat2 = Max_tay_gat2 - 25;
		for(i=0;i<50;i++)	{ 
						while(abs(bientrodaytay2Value - target_tay_gat2)> 10 )	{vTaskDelay(1); if(!wantExit())	break;}
				}
		Ktra_vtri_kep2(); // kiem tra hop 

		speed_tay_xoay = 250;
		target_xoay_tay = 692;
		for(i=0;i<50;i++)	{ 
		while(bientroxoaytayValue < 690 )	{vTaskDelay(1); if(!wantExit())	break;}
				}
				
		speed_tay_gat2 = 250;
		target_tay_gat2 = (Max_tay_gat2 );
		for(i=0;i<50;i++)	{ 
						while(abs(bientrodaytay2Value - target_tay_gat2)> 10 )	{vTaskDelay(1); if(!wantExit())	break;}
				}
		vTaskDelay (7000);
		Kep_phai_2_vao;
		vTaskDelay (5000);
		Tay2_xuong;
	
		speed_tay_gat2 = 250;
		target_tay_gat2 = vitri_tay2home;
		for(i=0;i<50;i++)	{ 
					while(abs(bientrodaytay2Value - target_tay_gat2)> 10 )	{vTaskDelay(1); if(!wantExit())	break;}
				}
}

// GAP LAN 4
void gap_tay3(void)
{	
		Kep_phai_3_ra;
		Tay1_len;
	
		speed_tay_gat1 = 200;
		target_tay_gat1 = Min_tay_gat1 + 40;
		for(i=0;i<50;i++)	{ 
						while(abs(bientrodaytay1Value - target_tay_gat1)> 10 )	{vTaskDelay(1); if(!wantExit())	break;}
				}
		Ktra_vtri_kep3(); // kiem tra hop 
	
		speed_tay_gat1 = 200;
		target_tay_gat1 = (Min_tay_gat1+ 5);
		for(i=0;i<50;i++)	{ 
						while(abs(bientrodaytay1Value - target_tay_gat1)> 10 )	{vTaskDelay(1); if(!wantExit())	break;}
				}
		vTaskDelay (7000);
		Kep_phai_3_vao;
		vTaskDelay (5000);
		Tay1_xuong;
	
		speed_tay_gat1 = 250;
		target_tay_gat1 = vitri_tay1home;
		for(i=0;i<50;i++)	{ 
					while(abs(bientrodaytay1Value - target_tay_gat1)> 10 )	{vTaskDelay(1); if(!wantExit())	break;}
				}
		
}


////// ************************** GAP 200 BAC DUOI *******************

// ********** gap lan 1 **********
void gap_tay4_duoi(void) 
{	
			Kep_phai_4_ra;
			vTaskDelay (500);
			Tay2_len;
	
			vTaskDelay (2000);
//					
			/// nhac dit len
			Nang_cham();
			target_chan_truoc = 395;
			target_chan_sau = 275;
			
			
			speed_tay_gat2 = 250;
			target_tay_gat2 = Min_tay_gat2  ;
			for(i=0;i<550;i++)	{ 

					while(abs(bientrodaytay2Value - target_tay_gat2) > 10 )	
					{vTaskDelay(1); if(!wantExit())	break;}
				}
			
			vTaskDelay (9000);
			Kep_phai_4_vao;
			vTaskDelay (5000);
			Tay2_xuong;	
			
			// nhat dit ve
			Nang_cham();
			target_chan_truoc = 265;
			target_chan_sau = 265;
				
			speed_tay_gat2 = 250;
			target_tay_gat2 = vitri_tay2home;
			for(i=0;i<50;i++)	{ 
						while(abs(bientrodaytay2Value - target_tay_gat2)> 10 )	{vTaskDelay(1); if(!wantExit())	break;}
					}
				

	
}

// ********** gap lan 2 **********
void gap_tay1_duoi(void) 
{		
		speed_tay_xoay = 100;
		target_xoay_tay = vi_tri_tay_12;
		for(i=0;i<150;i++)	{ 
				while((abs(bientroxoaytayValue - target_xoay_tay) > 10) )	{vTaskDelay(1); if(!wantExit())	break;}
		}
		Kep_phai_1_ra;
		vTaskDelay (500);
		Tay1_len;
		
		vTaskDelay (1000);
		/// nhac dit len
			Nang_cham();
			target_chan_truoc = 395;
			target_chan_sau = 275;
				
		speed_tay_gat1 = 170;
		target_tay_gat1 = (Max_tay_gat1 - 5);
		for(i=0;i<50;i++)	{ 
					while(abs(bientrodaytay1Value - target_tay_gat1)> 10 )	{vTaskDelay(1); if(!wantExit())	break;}
				}
		vTaskDelay (2000);
		Kep_phai_1_vao;
		vTaskDelay (2000);
		Tay1_xuong;
				
		// nhat dit ve
			Nang_cham();
			target_chan_truoc = 265;
			target_chan_sau = 265;
				
		speed_tay_gat1 = 250;
		target_tay_gat1 = vitri_tay1home;
		for(i=0;i<50;i++)	{ 
					while(abs(bientrodaytay1Value - target_tay_gat1)> 10 )	{vTaskDelay(1); if(!wantExit())	break;}
				}

}

void test_lay_hop (void) {
		Nang_cham();
		target_chan_truoc = 395;
		target_chan_sau = 275;

}

// ********** gap lan 3 **********
void gap_tay2_duoi(void) 
{	
		speed_tay_xoay = 100;
					target_xoay_tay = vi_tri_tay_12;
					for(i=0;i<150;i++)	{ 
							while((abs(bientroxoaytayValue - target_xoay_tay) > 10) )	{vTaskDelay(1); if(!wantExit())	break;}
					}
		Kep_phai_2_ra;
		vTaskDelay (500);
		Tay2_len;
	
					
		vTaskDelay (1000);
		/// nhac dit len
			Nang_cham();
			target_chan_truoc = 395;
			target_chan_sau = 275;
				
		speed_tay_gat2 = 250;
		target_tay_gat2 = (Max_tay_gat2 - 5 );
		for(i=0;i<50;i++)	{ 
						while(abs(bientrodaytay2Value - target_tay_gat2)> 10 )	{vTaskDelay(1); if(!wantExit())	break;}
				}
		vTaskDelay (8000);
		Kep_phai_2_vao;
		vTaskDelay (5000);
		Tay2_xuong;
	
		// nhat dit ve
			Nang_cham();
			target_chan_truoc = 265;
			target_chan_sau = 265;
				
		speed_tay_gat2 = 250;
		target_tay_gat2 = vitri_tay2home;
		for(i=0;i<50;i++)	{ 
					while(abs(bientrodaytay2Value - target_tay_gat2)> 10 )	{vTaskDelay(1); if(!wantExit())	break;}
				}

}

// GAP LAN 4
void gap_tay3_duoi(void)
{	
		speed_tay_xoay = 100;
					target_xoay_tay = vi_tri_tay_43;
					for(i=0;i<150;i++)	{ 
							while((abs(bientroxoaytayValue - target_xoay_tay) > 10) )	{vTaskDelay(1); if(!wantExit())	break;}
					}
		Kep_phai_3_ra;
		vTaskDelay (500);
		Tay1_len;

		vTaskDelay (1000);
		/// nhac dit len
			Nang_cham();
			target_chan_truoc = 395;
			target_chan_sau = 275;
	
		speed_tay_gat1 = 200;
		target_tay_gat1 = (Min_tay_gat1+ 10);
		for(i=0;i<50;i++)	{ 
						while(abs(bientrodaytay1Value - target_tay_gat1)> 10 )	{vTaskDelay(1); if(!wantExit())	break;}
				}
		vTaskDelay (8000);
		Kep_phai_3_vao;
		vTaskDelay (5000);
		Tay1_xuong;
	
		// nhat dit ve
			Nang_cham();
			target_chan_truoc = 265;
			target_chan_sau = 265;
				
		speed_tay_gat1 = 250;
		target_tay_gat1 = vitri_tay1home;
		for(i=0;i<50;i++)	{ 
					while(abs(bientrodaytay1Value - target_tay_gat1)> 10 )	{vTaskDelay(1); if(!wantExit())	break;}
				}
		
}


// ********** xoay toi goc tay tiep theo + mo kep
void kiem_tra_huong_quay_tay_gap_phia_truoc (void) {
	
		if (da_lay_tay1 == 0 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
			
				Kep_phai_4_ra;
	
		}
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
			
					// quay mam sang tay 1
						speed_tay_xoay = 100;
						target_xoay_tay = vi_tri_tay_12;
						Kep_phai_1_ra;

						
						}
		// quay mam sang tay 2
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
						speed_tay_xoay = 100;
						target_xoay_tay = vi_tri_tay_12;
						Kep_phai_2_ra;

						}
		// quay mam sang tay 3
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 0) {
					speed_tay_xoay = 100;
					target_xoay_tay = vi_tri_tay_43;	
					Kep_phai_3_ra;
			
						}										
}



/// ****************** HÀM GAP PHÍA TRUOC *************************			
void Lay_phia_truoc_bac_400_tren (void) {
		
			if (da_lay_tay1 == 0 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
					gap_tay4_bac_400();
					da_lay_tay1 = 1;
					}
				
			else if (da_lay_tay1 == 1 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
					gap_tay1_bac_400();
					da_lay_tay2 = 1;
			}
			
			
			// dung tay lan 3 
			else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
					gap_tay2_bac_400();
			
					da_lay_tay3 = 1;
			}
			TinHieu_ChuanBi_GapThang = 0;
			TinHieu_ChuanBi_GapTrai = 0;
			TinHieu_ChuanBi_GapPhai =0;
			di_vao_giua();
			
				}

void Lay_phia_truoc_bac_200_tren (void) {
			robotRunAngle(-900,5,900,0.3);	
			vTaskDelay(3000);
			
			if (da_lay_tay1 == 0 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
					speed_tay_xoay = 100;
					target_xoay_tay = vi_tri_tay_43;
					for(i=0;i<150;i++)	{ 
							while((abs(bientroxoaytayValue - target_xoay_tay) > 10) )	{vTaskDelay(1); if(!wantExit())	break;}
					}
				
					gap_tay4();
					da_lay_tay1 = 1;
					}
			
					// dung tay lan 2
			else if (da_lay_tay1 == 1 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
					speed_tay_xoay = 100;
					target_xoay_tay = vi_tri_tay_12;
					for(i=0;i<150;i++)	{ 
							while((abs(bientroxoaytayValue - target_xoay_tay) > 10) )	{vTaskDelay(1); if(!wantExit())	break;}
					}
					gap_tay1();
					
					da_lay_tay2 = 1;
			}
			
			// dung tay lan 3 
			else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
					speed_tay_xoay = 100;
					target_xoay_tay = vi_tri_tay_12;
					for(i=0;i<150;i++)	{ 
							while((abs(bientroxoaytayValue - target_xoay_tay) > 10) )	{vTaskDelay(1); if(!wantExit())	break;}
					}
					gap_tay2();
					da_lay_tay3 = 1;
			}
			
			// dung tay lan 4
			else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 0) {
					speed_tay_xoay = 100;
					target_xoay_tay = vi_tri_tay_43;
					for(i=0;i<150;i++)	{ 
							while((abs(bientroxoaytayValue - target_xoay_tay) > 10) )	{vTaskDelay(1); if(!wantExit())	break;}
					}
					gap_tay3();
					
					da_lay_tay4 = 1;
			}
			TinHieu_ChuanBi_GapThang = 0;
			TinHieu_ChuanBi_GapTrai = 0;
			TinHieu_ChuanBi_GapPhai =0;
			di_vao_giua();
}

/// *************************************************************

/// ****************** HÀM GAP BEN TRAI *************************		
void Lay_ben_trai_bac_200_tren (void) {
			speed_tay_xoay = 100;
			target_xoay_tay = vi_tri_gap_ngang;
			for(i=0;i<150;i++)	{ 
			while((abs(bientroxoaytayValue - target_xoay_tay) > 10) )	{vTaskDelay(1); if(!wantExit())	break;}
					}
			
}

//////////*******************************************************

void di_vao_giua (void) {

					// da dung tay 1 xong
			if (da_lay_tay1 == 1 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
				robotRunAngle(1650,7,900,0.3);
//				RESET_ENCODER();
//				while(abs(ENCODER_FR()) + abs(ENCODER_FL()) < 2000)	{vTaskDelay (1); if(!wantExit())	break;}
					vTaskDelay (10000);
					robotStop(0);
			
		}
			
			// dung tay 2 xong
			else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
				robotRunAngle(1650,7,900,0.3);
				vTaskDelay (10000);
//				RESET_ENCODER();
//				while(abs(ENCODER_FR()) + abs(ENCODER_FL()) < 2000)	{vTaskDelay (1); if(!wantExit())	break;}
					robotStop(0);
				
			}
			
			// dung tay lan 3 xong
			else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 0) {

				robotRunAngle(150,7,900,0.3);
				vTaskDelay (10000);
//				RESET_ENCODER();
//				//while(abs(ENCODER_FR()) + abs(ENCODER_FL()) < 2000)	{vTaskDelay (1); if(!wantExit())	break;}
					robotStop(0);
				
			}
			// dung tay 4 xong
			else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 1) {

				robotRunAngle(150,7,900,0.3);
//				RESET_ENCODER();
//				while(abs(ENCODER_FR()) + abs(ENCODER_FL()) < 2000)	{vTaskDelay (1); if(!wantExit())	break;}
				vTaskDelay (10000);
					robotStop(0);
				
			}

				
}

/// ******* LAY 200 bac duoi ******************************
void Lay_phia_truoc_bac_200_duoi (void) {
//	
	if (da_lay_tay1 == 0 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
					gap_tay4_duoi();
					da_lay_tay1 = 1;
					su_dung_chan(265);
					di_vao_giua();
					}
			
					// dung tay lan 2
			else if (da_lay_tay1 == 1 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
					gap_tay1_duoi();
					su_dung_chan(265);
					da_lay_tay2 = 1;
					di_vao_giua();
			}
			
			// dung tay lan 3 
			else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
					gap_tay2_duoi();
					su_dung_chan(265);
					da_lay_tay3 = 1;
					di_vao_giua();
			}
			
			// dung tay lan 4
			else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 0) {
					gap_tay3_duoi();
					su_dung_chan(265);
					da_lay_tay4 = 1;
					di_vao_giua();
			}
			TinHieu_ChuanBi_GapThang = 0;
			TinHieu_ChuanBi_GapTrai = 0;
			TinHieu_ChuanBi_GapPhai =0;
	


}

/// *********** HAM tracking vi tri bang laser ****************
#define SPEED_FAST 10
#define SPEED_MIN 4
#define ERROR_MAX 20

int smooth_speed(int error)
{
    int d = abs(error);
		int speed;

    if(d > ERROR_MAX)
        d = ERROR_MAX;

    if(d < 2)
        return SPEED_MIN;

    speed = SPEED_MIN + (SPEED_FAST - SPEED_MIN) * d * d / (ERROR_MAX * ERROR_MAX);

    return speed;
}

void chinh_lai_vi_tri_laser_trai(int vitri, int gia_tri_lap)
{
	int speed ;
	int dieuchinh;
		for(i=0;i<gia_tri_lap;i++)
				{
		while(abs(lazeTraiValue - vitri) > 1)	{
			dieuchinh = lazeTraiValue - vitri;
			speed = smooth_speed(dieuchinh);
			
					if  ((lazeTraiValue - vitri)> 0 ) {
							robotRunAngle(0, speed, 900, 0.5);
					}
					else if ((lazeTraiValue - vitri)< 0) {
					
					robotRunAngle(1800, speed, 900, 0.5);
					
					}
					else {
								robotStop(0);

								}
			}
		}   		
	}

	void chinh_lai_vi_tri_laser_phai(int vitri, int gia_tri_lap)
{
	int speed ;
	int dieuchinh;
		for(i=0;i<gia_tri_lap;i++)
				{
		while(abs(lazePhaiValue - vitri) > 1)	{
			dieuchinh = lazePhaiValue - vitri;
			speed = smooth_speed(dieuchinh);
			
					if  ((lazePhaiValue - vitri)> 0 ) {
							robotRunAngle(1800, speed, 900, 0.5);
					}
					else if ((lazePhaiValue - vitri)< 0) {
					
					robotRunAngle(0, speed, 900, 0.5);
					
					}
					else {
								robotStop(0);

								}
			}
		}   		
	}


/////////////////////////////////////////////////////////
void go_qua (void) {
	if (R2 && O) {
				Kep_phai_4_ra;
				Kep_phai_1_ra;
				Kep_phai_2_ra;
				Kep_phai_3_ra;
	
	}

}
///////////////////////////ktr vi tri kep//////////////////////////////
void Ktra_vtri_kep3 (void) {
		for(i=0;i<500;i++)
				{
					while(CB_kep_3_2 == 0 || CB_kep_3_1 == 0)	
					{	
						if	(CB_kep_3_1 == 0) robotRunAngle(0,3,-900,0.1);	
						else if 	(CB_kep_3_2 == 0) robotRunAngle(1800,3,-900,0.1);	
						else		robotStop(0);				
						vTaskDelay (1);
						if(!wantExit())	break;
					}
				}	
				robotStop(0);
	
	}

	void Ktra_vtri_kep4 (void) {
		for(i=0;i<500;i++)
				{
					while(CB_kep_4_2 == 0 || CB_kep_4_1 == 0)	
					{	
						if	(CB_kep_4_2 == 0) robotRunAngle(0,5,-900,0.3);	
						else if 	(CB_kep_4_1 == 0) robotRunAngle(1800,5,-900,0.3);
						else	{	
						robotStop(0);			
							
						}	
						vTaskDelay (1);
						if(!wantExit())	break;
					}
				}	
				robotStop(0);
	
	}

		void Ktra_vtri_kep1 (void) {
		for(i=0;i<500;i++)
				{
					while(CB_kep_1_2 == 0 || CB_kep_1_1 == 0)	
					{	
						if	(CB_kep_1_2 == 0) robotRunAngle(0,5,-900,0.3);	
						else if 	(CB_kep_1_1 == 0) robotRunAngle(1800,5,-900,0.3);	
						else		robotStop(0);				
						vTaskDelay (1);
						if(!wantExit())	break;
					}
				}	
				robotStop(0);
	
	}
		
	void Ktra_vtri_kep2 (void) {
		for(i=0;i<500;i++)
				{
					while(CB_kep_2_2 == 0 || CB_kep_2_1 == 0)	
					{	
						if	(CB_kep_2_1 == 0) robotRunAngle(0,5,-900,0.3);	
						else if 	(CB_kep_2_2 == 0) robotRunAngle(1800,5,-900,0.3);		
						else		robotStop(0);				
						vTaskDelay (1);
						if(!wantExit())	break;
					}
				}	
				robotStop(0);
	
	}
