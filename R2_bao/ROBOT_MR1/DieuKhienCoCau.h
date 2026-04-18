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
void tracking_traiPhaiThang_tren_tay4(void);
void tracking_traiPhaiThang_tren_tay1(void);
void tracking_traiPhaiThang_tren_tay2(void);
void tracking_traiPhaiThang_tren_tay3(void);
void chinh_lai_vi_tri_laser_phai_custom(int vitri, int gia_tri_lap, int min_toc, int max_toc );
//extern vu8 update;
extern speed_temp;
extern vu8	Cam;
extern float	JTL;
int state_nang = 1;
int state_ha = 1;

int Xoay_ok;

extern int TinHieu_ChuanBi_GapThang;
extern int TinHieu_ChuanBi_GapTrai ;
extern int TinHieu_ChuanBi_GapPhai;
extern int vitri_tay41_laser_trai_GapQua;
extern int vitri_tay23_laser_trai_GapQua;

void di_vao_giua_do(void);
void kiem_tra_huong_ha_tay_gap_phia_truoc(void);
void chuan_bi_gap_thang_xanh_4 (void);
void chuan_bi_gap_thang_xanh_7(void);
void chuan_bi_gap_phai_200_tren_7_10(void);
void Lay_ben_trai_bac_200_tren_xanh_9(void);
void Lay_ben_trai_bac_200_tren (void);
void chuan_bi_gap_trai_200_duoi_ko_thanh(void);
void ha_sat_xuong (void);
void chuan_bi_gap_phai_200_duoi_ko_thanh(void);

void kiem_tra_huong_quay_tay_gap_ben_trai (void);
void kiem_tra_huong_quay_tay_gap_ben_phai (void);

// *************** thong so tay gap ************
int	Min_chan_truoc = 230, Max_chan_truoc = 710, target_chan_truoc;
int	Min_chan_sau = 230, Max_chan_sau = 710, target_chan_sau;
int	Min_xoay_tay = 250, Max_xoay_tay = 710, target_xoay_tay;
int	Min_tay_gat1 = 96, Max_tay_gat1 = 782, target_tay_gat1;
int	Min_tay_gat2 = 95, Max_tay_gat2 = 782, target_tay_gat2;

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

void Ktra_vtri_kep4_trai (void);
void Ktra_vtri_kep1_trai (void);
void Ktra_vtri_kep2_trai (void);
void Ktra_vtri_kep3_trai (void);


void Ktra_vtri_kep4_phai (void);
void Ktra_vtri_kep1_phai (void);
void Ktra_vtri_kep2_phai (void);
void Ktra_vtri_kep3_phai (void);

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

	if (abs(bientrochantruocValue - target_chan_truoc) > 4)
	{
		if (bientrochantruocValue > target_chan_truoc)	mor_lift_front_down;
		else																						mor_lift_front_up;

		speed_temp = abs(bientrochantruocValue - target_chan_truoc)*4;
//		if (speed_temp > 170)
//				speed_temp = 170;
		if (speed_temp > speed_chan_truoc)
				speed_temp = speed_chan_truoc;
		if (speed_temp < 70)
				speed_temp = 70;
		
		mor_lift_front = speed_temp;
	}
	else mor_lift_front = 20, mor_lift_front_up;
}


void Chan_sau()
{
	if (target_chan_sau < Min_chan_sau)
		target_chan_sau = Min_chan_sau;
	if (target_chan_sau > Max_chan_sau)
		target_chan_sau = Max_chan_sau;

	if (abs(bientrochansauValue - target_chan_sau) > 4)
	{
		if (bientrochansauValue > target_chan_sau)			mor_lift_rear_down;
		else																						mor_lift_rear_up;

		speed_temp  = abs(bientrochansauValue - target_chan_sau)*4;
		if (speed_temp > speed_chan_sau)
				speed_temp = speed_chan_sau;
		if (speed_temp < 40)
				speed_temp = 40;
		
		mor_lift_rear = speed_temp;
	}
	else mor_lift_rear = 10, mor_lift_rear_up;
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
		if (speed_temp < 100)
				speed_temp = 100;
		
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
		if (speed_temp < 100)
				speed_temp = 100;
		
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

	if ((abs(bientroxoaytayValue - target_xoay_tay) > 2) && (abs(bientrodaytay1Value - vitri_tay1home) < 20) && (abs(bientrodaytay2Value - vitri_tay2home) < 20))
	{
		if (bientroxoaytayValue > target_xoay_tay)			tay_xoay_thuan;
		else																						tay_xoay_nghich;

		speed_temp = abs(bientroxoaytayValue - target_xoay_tay);
		if (speed_temp > speed_tay_xoay)
				speed_temp = speed_tay_xoay;
		if (speed_temp < 50)
				speed_temp = 50;
	
		tay_xoay = speed_temp;
		Xoay_ok = 0;
	}
	else tay_xoay = 0, Xoay_ok = 1;
}



//********************************Speed nang ****************************
void Nang_cham	(void) {
	speed_chan_sau = 37;
	speed_chan_truoc = 37;
}

void Nang_thuong	(void) {
	speed_chan_sau = 61;
	speed_chan_truoc = 68;
}

void Nang_nhanh	(void) {
	speed_chan_sau = 82;
	speed_chan_truoc = 115;
}

void Nang_cuc_nhanh	(void) {
	speed_chan_sau = 100;
	speed_chan_truoc = 130;
}


void su_dung_chan (int value_chan) {
	Nang_nhanh();

	target_chan_truoc = value_chan ;
	target_chan_sau = value_chan;
}

void su_dung_chan_thuong (int value_chan) {
	Nang_thuong();

	target_chan_truoc = value_chan ;
	target_chan_sau = value_chan;
}

void su_dung_chan_nhanh (int value_chan) {
	Nang_nhanh();

	target_chan_truoc = value_chan ;
	target_chan_sau = value_chan;
}
/// ************** VE TAY HOME 2 TAY **************
void ve_home_2_tay (void) {
			speed_tay_gat1 = 250;
			target_tay_gat1 = vitri_tay1home;
			speed_tay_gat2 = 250;
			target_tay_gat2 = vitri_tay2home;
			for(i=0;i<50;i++)	{ 
				while(abs(bientrodaytay1Value - target_tay_gat1) > ((vitri_tay1home- Min_tay_gat1) / 2 ) || abs(bientrodaytay2Value - target_tay_gat2) > ((vitri_tay2home- Min_tay_gat2) / 3 ) )	
				{vTaskDelay(1); if(!wantExit())	break;}
					}
}

void di_tren_buc_khong_thanh_2_ben (void) {
		if (da_lay_tay1 == 0 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
				while( CB_Ha_Sau == 0) {
				if(CB_ROI_3  == 0 && CB_ROI_1 == 0)	robotRunAngle(-650,16,900,0.7);
				else																robotRunAngle(-900,12,900,0.7);
				vTaskDelay(1);
				if(!wantExit()) break;
					}
				// chay toi roi thi di ngang qua phai
				robotRunAngle(0,10,900,0.7);
				while (CB_ROI_3  == 0 )	 {
					vTaskDelay(1);
					if(!wantExit()) break;
					}
			}
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
				while(CB_Ha_Sau == 0) {
				if(CB_ROI_3  == 0 && CB_ROI_1 == 0)	robotRunAngle(-650,16,900,0.7);
				else																robotRunAngle(-900,12,900,0.7);
				vTaskDelay(1);
				if(!wantExit()) break;
					}
				// chay toi roi thi di ngang qua phai
				robotRunAngle(0,10,900,0.7);
				while (CB_ROI_3  == 0 )	 {
					vTaskDelay(1);
					if(!wantExit()) break;
					}
				}

		// quay mam sang tay 2
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
				while( CB_Ha_Sau == 0) {
				if(CB_ROI_2  == 0 && CB_ROI_4 == 0)	robotRunAngle(-1250,16,900,0.7);
				else																robotRunAngle(-900,12,900,0.7);
				vTaskDelay(1);
				if(!wantExit()) break;
							}
				// chay toi roi thi di ngang qua trai
				robotRunAngle(1800,10,900,0.7);
				while (CB_ROI_2  == 0 )	 {
					vTaskDelay(1);
					if(!wantExit()) break;
						}
				}
		
		// quay mam sang tay 3
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 0) {
				while( CB_Ha_Sau == 0) {
				if(CB_ROI_2  == 0 && CB_ROI_4 == 0)	robotRunAngle(-1250,16,900,0.7);
				else																robotRunAngle(-900,12,900,0.7);
				vTaskDelay(1);
				if(!wantExit()) break;
						}
				// chay toi roi thi di ngang qua trai
				robotRunAngle(1800,10,900,0.7);
				while (CB_ROI_2  == 0 )	 {
					vTaskDelay(1);
					if(!wantExit()) break;
							}
					}
		robotStop(0);	
}

//******************************** leo bac 200 ****************************
void Leo_bac_200(int Angle, int Robot_Angle)
{	
		int i;
			// nâng bánh trc lên 
	Nang_cuc_nhanh();
	
	target_chan_truoc = Min_chan_truoc + 250;
	target_chan_sau = Min_chan_sau + 250;
	
 	for(i=0;i<50;i++)		
	{
		while(abs(bientrochansauValue - target_chan_sau) > 15)	{vTaskDelay(1); if(!wantExit())	break;}
	}
	
	robotRunAngle(Angle,14,Robot_Angle,0.8);
	for(i=0;i<150;i++)	
	{	
		while(CB_Ha_Sau == 1  || CB_Cap_Thanh_Sau == 0)	{vTaskDelay(1); if(!wantExit())	break;}
	}
	robotStop(0);
	////	// nâng bánh sau lên 
	speed_chan_sau = 100;
	target_chan_sau = Min_chan_sau + 10;
	for(i=0;i<50;i++)		
	{
			while(abs(bientrochansauValue - target_chan_sau) > 5)	{vTaskDelay(1); if(!wantExit())	break;}
	}
	
	vTaskDelay(700);
	
	robotRunAngle(Angle,14,Robot_Angle,0.7);
	
	vTaskDelay(1700);
	for(i=0;i<1000;i++)	
	{	
		while(CB_ROI_1 == 1  && CB_ROI_4 == 1)	{vTaskDelay(1); if(!wantExit())	break;}
	}
	vTaskDelay(1500);
	
	speed_chan_sau =150;
	target_chan_sau = Min_chan_sau + 30;
	
	robotRunAngle(Angle,14,Robot_Angle,0.8);
	
	for(i=0;i<550;i++)	
	{	
		while(CB_bung_duoi == 1)	{vTaskDelay(2); if(!wantExit())	break;}
	}


	robotRunAngle(Angle,14,Robot_Angle,0.8);
		for(i=0;i<1000;i++)	
	{	
		while(CB_bung == 1)	{vTaskDelay(1); if(!wantExit())	break;}
	}

	//vTaskDelay(1000); 
	
  robotStop(0);
	speed_chan_truoc = 100;
	target_chan_truoc = Min_chan_truoc + 3;
	
	vTaskDelay(1000);
	
	speed_chan_sau = 80;
	target_chan_sau = Min_chan_sau + 20;

	for(i=0;i<250;i++)	
	{
		while(abs(bientrochantruocValue - target_chan_truoc) > 4)	{vTaskDelay(1); if(!wantExit())	break;}
	}
	
	vTaskDelay(1000);
	
	robotRunAngle(Angle,12,Robot_Angle,0.9);
	for(i=0;i<250;i++)	
	{
	while(CB_ROI_2 == 1  && CB_ROI_3 == 1)	{vTaskDelay(1); if(!wantExit())	break;}
	}

	RESET_ENCODER(); 
	while(abs(ENCODER_FR()) + abs(ENCODER_FL()) < 400)	{vTaskDelay (5); if(!wantExit())	break;}

  Nang_cuc_nhanh();
	target_chan_truoc = 260, target_chan_sau = 260;
	
	robotRunAngle(Angle,12,Robot_Angle,0.9);

	for(i=0;i<100;i++) 
		{
		while(CB_Ha_Dau == 1)		{vTaskDelay(1); if(!wantExit())	break;}
		}

	robotStop(0);
}


void Leo_bac_200_bam_thanh_phai(void)
{	
	int vitri_tay41 = vitri_tay41_laser_trai_GapQua;
	int vitri_tay23 = vitri_tay23_phai_laser_GapQua;
	
	Leo_bac_200(-900, 900);
	Nang_cuc_nhanh();
	target_chan_truoc = Min_chan_truoc + 250;
	target_chan_sau = Min_chan_sau + 250;

	if (TinHieu_ChuanBi_GapThang == 0) {
			robotRunAngle(-900,18,900,0.7);
			for(i=0;i<1550;i++)
				{
				while(CB_Ha_Sau == 1 || CB_Cap_Thanh_Sau == 0 || (abs(bientrochansauValue - target_chan_sau) > 10))	
					{	
						vTaskDelay (1);
						if(!wantExit())	break;
					}
				}
			}
		
	else if (TinHieu_ChuanBi_GapThang == 1) {		
//			KT_Ha_Tay = 1;
			su_dung_chan(565);
		if (da_lay_tay1 == 0 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
					for(i=0;i<1550;i++) {
						
					while( CB_Cap_Thanh_Sau == 0 ||  (abs(bientrochansauValue - target_chan_sau) > 10))	
					{	
					if(lazeTraiValue > vitri_tay41)			robotRunAngle(-650,16,900,0.7);
					else																robotRunAngle(-900,12,900,0.7);
					vTaskDelay(1);
					if(!wantExit()) break;
								}
						}
					}
			
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
					for(i=0;i<1550;i++) {
					while( CB_Cap_Thanh_Sau == 0 ||  (abs(bientrochansauValue - target_chan_sau) > 10))	
					{	
					if(lazeTraiValue > vitri_tay41)			robotRunAngle(-650,16,900,0.7);
					else																robotRunAngle(-900,12,900,0.7);
					vTaskDelay(1);
					if(!wantExit()) break;
								}
						}

			}

		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
						for(i=0;i<1550;i++) {
						while( CB_Cap_Thanh_Sau == 0 ||  (abs(bientrochansauValue - target_chan_sau) > 10))	
						{	
						if(lazePhaiValue > vitri_tay23)			robotRunAngle(-1250,16,900,0.7);
						else																robotRunAngle(-900,12,900,0.7);
						vTaskDelay(1);
						if(!wantExit()) break;
									}
							}
						}
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 0) {
						for(i=0;i<1550;i++) {
						while( CB_Cap_Thanh_Sau == 0 ||  (abs(bientrochansauValue - target_chan_sau) > 10))	
						{	
						if(lazePhaiValue > vitri_tay23)			robotRunAngle(-1250,16,900,0.7);
						else																robotRunAngle(-900,12,900,0.7);
						vTaskDelay(1);
						if(!wantExit()) break;
									}
							}
						}
		}
		
		robotStop(0); 					
}


void chuan_bi_gap_trai_200_tren_8 (void ) {
	
	if (da_lay_tay1 == 0 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
			ha_sat_xuong;
			for(i=0;i<250;i++)	
				{
					while(abs(bientrochansauValue - target_chan_sau) > 10)	{vTaskDelay(1); if(!wantExit())	break;}
				}
				
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
	
			//// dung tay 3 gap duoi lan 2
		else if (da_lay_tay1 == 1 && da_lay_tay4_duoi == 0) {
					ha_sat_xuong;
					for(i=0;i<250;i++)	
						{
							while(abs(bientrochansauValue - target_chan_sau) > 10)	{vTaskDelay(1); if(!wantExit())	break;}
						}	
					robotRunAngle(-900,5,900,0.5);
			
					for(i=0;i<1550;i++)
						{
							while (CB_Ha_Sau == 0 )	
							{	
								if(!wantExit())	break;
								vTaskDelay (1);
							}
						}
			robotStop(0); 
						
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

///// ********* leo bac 200 khong thanh **************
void Leo_bac_200_ko_thanh(void)
{	
		Leo_bac_200(-900, 900);
		su_dung_chan(265);
	
	if (TinHieu_ChuanBi_GapThang == 0 && TinHieu_ChuanBi_GapTrai == 0 && TinHieu_ChuanBi_GapPhai == 0) {
		// chay toi khi mat cam bien sau
		robotRunAngle(-900,18,900,0.7);
		for(i=0;i<1550;i++)
				{
						while(CB_Ha_Sau == 0 || (abs(bientrochansauValue - target_chan_sau) > 10))	
				
					{	
						if(!wantExit())	break;
						vTaskDelay (1);
					}
				}
		robotRunAngle(-900,10,900,0.7);
		for(i=0;i<1550;i++)
				{
						while(CB_vtri_leo == 0 || CB_Ha_Sau == 0)	
				
					{	
						if(!wantExit())	break;
						vTaskDelay (1);
					}
				}
				
		robotStop(0);
			}
		else if (TinHieu_ChuanBi_GapThang == 1) {
					di_tren_buc_khong_thanh_2_ben();
		}
	// CO LENH GAP TRAI
		else if (TinHieu_ChuanBi_GapTrai == 1 ) {
					chuan_bi_gap_trai_200_duoi_ko_thanh();
		}
		// CO LENH GAP PHAI
		else if (TinHieu_ChuanBi_GapPhai == 1 ) {
					chuan_bi_gap_phai_200_duoi_ko_thanh();
		}
}

//***************** leo bac 200 bam thanh laser trai + laser truoc *************



//******************************** leo bac 400 ****************************
void Leo_bac_400(int Angle, int Robot_Angle)
{	
	int i;
	
	Nang_cuc_nhanh();
	
	target_chan_truoc = Max_chan_truoc - 7, target_chan_sau = Max_chan_sau - 7;
	
	for(i=0;i<250;i++)	
	{
		while(abs(bientrochansauValue - target_chan_sau) > 10)	{vTaskDelay(1); if(!wantExit())	break;}
	}
//	
//	robotStop(0);
	robotRunAngle(Angle,12,Robot_Angle,0.8);
	
	for(i=0;i<150;i++)	
	{	
		while(CB_Ha_Sau == 1 || CB_vtri_leo == 1 || CB_Cap_Thanh_Sau == 0)	{vTaskDelay(1); if(!wantExit())	break;}
	}

	RESET_ENCODER(); 
	
	while(abs(ENCODER_FR()) + abs(ENCODER_FL()) < 200)	{vTaskDelay (5); if(!wantExit())	break;}
	
	robotStop(0); 
//	
	speed_chan_sau = 140;
	target_chan_sau = Min_chan_sau ;

	for(i=0;i<50;i++)		
	{
		while(abs(bientrochansauValue - target_chan_sau) > 10)	{vTaskDelay(5); if(!wantExit())	break;}
	}
	
	vTaskDelay(700);
	
	robotRunAngle(Angle,12,Robot_Angle,0.8);
	
	vTaskDelay(1700);
	for(i=0;i<1050;i++)	
	{	
		while(CB_ROI_1 == 1  && CB_ROI_4 == 1)	{vTaskDelay(1); if(!wantExit())	break;}
	}
	speed_chan_sau = 200;
	target_chan_sau = Min_chan_sau + 30;
	
	robotRunAngle(Angle,12,Robot_Angle,0.8);
	
	for(i=0;i<550;i++)	
	{	
		while(CB_bung_duoi == 1)	{vTaskDelay(2); if(!wantExit())	break;}
	}
	
	for(i=0;i<1000;i++)	
	{	
		while(CB_bung == 1)	{vTaskDelay(1); if(!wantExit())	break;}
	}
	
	vTaskDelay(600);
	
  robotStop(0);
	speed_chan_truoc = 200;
	target_chan_truoc = Min_chan_truoc ;
		
	speed_chan_sau = 50;
	target_chan_sau = Min_chan_sau + 17;

	for(i=0;i<250;i++)	
	{
		while(abs(bientrochantruocValue - target_chan_truoc) > 4)	{vTaskDelay(1); if(!wantExit())	break;}
	}
	
	vTaskDelay(1500);
	
	robotRunAngle(Angle,20,Robot_Angle,0.8);
	for(i=0;i<250;i++)	
	{
	while(CB_ROI_2 == 1  || CB_ROI_3 == 1)	{vTaskDelay(1); if(!wantExit())	break;}
	}

	RESET_ENCODER(); 
	while(abs(ENCODER_FR()) + abs(ENCODER_FL()) < 400)	{vTaskDelay (5); if(!wantExit())	break;}

  Nang_cuc_nhanh();
	target_chan_truoc = 265, target_chan_sau = 263;
	
	robotRunAngle(Angle,12,Robot_Angle,0.8);

	for(i=0;i<100;i++) 
		{
		while(CB_Ha_Dau == 1)		{vTaskDelay(1); if(!wantExit())	break;}
		}
	Man_gat2 = 0;
		
	robotStop(0);
}


void Leo_bac_400_ko_thanh(void)
{		
		Leo_bac_400(-900, 900);
		su_dung_chan(265);
		
	if (TinHieu_ChuanBi_GapThang == 0 ) {
		// chay toi khi mat cam bien sau
		robotRunAngle(-900,18,900,0.9);
		for(i=0;i<250;i++)
				{
						while(CB_Ha_Sau == 0 ||  (abs(bientrochansauValue - target_chan_sau) > 10))	

					{	
						vTaskDelay (1);
						if(!wantExit())	break;
					}
				}
		robotRunAngle(-900,10,900,0.9);
		for(i=0;i<250;i++)
				{
						while(CB_vtri_leo == 0 || CB_Ha_Sau == 0 )	

					{	
						vTaskDelay (1);
						if(!wantExit())	break;
					}
				}
		robotStop(0);
			}
				
	else if (TinHieu_ChuanBi_GapThang == 1 ) {
		di_tren_buc_khong_thanh_2_ben();
		}

}

void Leo_bac_400_co_thanh(void) {
		Leo_bac_400(-900, 900);
	
		Nang_cuc_nhanh();
		target_chan_truoc = Min_chan_truoc + 250;
		target_chan_sau = Min_chan_sau + 250;
		
		// chay toi khi laser sau cham
		robotRunAngle(-900,18,900,0.7);
		for(i=0;i<1550;i++)
				{
					while(CB_Ha_Sau == 1  || (abs(bientrochansauValue - target_chan_sau) > 7) )	
					{	
						vTaskDelay (1);
						if(!wantExit())	break;
					}
				}
		robotRunAngle(-900,15,900,0.7);
		for(i=0;i<1550;i++)
				{
					while(CB_Ha_Sau == 1 || CB_Cap_Thanh_Sau == 0 )	
					{	
						vTaskDelay (5);
						if(!wantExit())	break;
					}
				}
		
		robotStop(3);
	
if (TinHieu_ChuanBi_GapThang == 1) {
		su_dung_chan(565);
		if (da_lay_tay1 == 0 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
				// chay toi roi thi di ngang qua phai
				robotRunAngle(0,10,900,0.7);
				while (CB_ROI_3  == 0 || (abs(bientrochansauValue - target_chan_sau) > 10))	 {
					vTaskDelay(1);
					if(!wantExit()) break;
					}
				}
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
				// chay toi roi thi di ngang qua phai
				robotRunAngle(0,10,900,0.7);
				while (CB_ROI_3  == 0 || (abs(bientrochansauValue - target_chan_sau) > 10))	 {
					vTaskDelay(1);
					if(!wantExit()) break;
					}
				}

		// quay mam sang tay 2
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
				// chay toi roi thi di ngang qua trai
				robotRunAngle(1800,10,900,0.7);
				while (CB_ROI_2  == 0 || (abs(bientrochansauValue - target_chan_sau) > 10))	 {
					vTaskDelay(1);
					if(!wantExit()) break;
						}
				}
		// quay mam sang tay 3
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 0) {
				// chay toi roi thi di ngang qua trai
				robotRunAngle(1800,10,900,0.7);
				while (CB_ROI_2  == 0 || (abs(bientrochansauValue - target_chan_sau) > 10))	 {
					vTaskDelay(1);
					if(!wantExit()) break;
							}
					}
		}
	robotStop(0); 
}



////******************************** xuong bac 200 ****************************88
void Xuong_bac_200(int Angle, int Robot_Angle)
{	
	int i;
	Nang_nhanh();
	
	target_chan_truoc = Min_chan_truoc + 10, target_chan_sau = Min_chan_sau + 10;
	for(i=0;i<50;i++)		
	{
		while(abs(bientrochansauValue - target_chan_sau) > 10)	{vTaskDelay(1); if(!wantExit())	break;}
	}
	
	
	robotRunAngle(Angle,12,Robot_Angle,1);

	for(i=0;i<500;i++)
	{	
		while(CB_Ha_Sau == 0 || CB_vtri_leo == 0 || (CB_ROI_1 == 0  && CB_ROI_4 == 0))	{vTaskDelay(1); if(!wantExit())	break;}
	}
	robotStop(7);
//	
	speed_chan_sau = 80;
	target_chan_sau = Min_chan_sau + 240;
	
	for(i=0;i<250;i++)		
	{
		while(abs(bientrochansauValue - target_chan_sau) > 80)	{vTaskDelay(1); if(!wantExit())	break;}
	}
	
	speed_chan_sau =30;
	
	for(i=0;i<250;i++)		
	{
		while(abs(bientrochansauValue - target_chan_sau) > 13)	{vTaskDelay(1); if(!wantExit())	break;}
	}
	robotStop(0);
	
	robotRunAngle(Angle,10,Robot_Angle,1);
	
	for(i=0;i<550;i++)	
	{	
		while(CB_bung == 0)	{vTaskDelay(1); if(!wantExit())	break;}
	}

	target_chan_truoc = Min_chan_truoc + 5;

	
	for(i=0;i<1000;i++)	
	{	
		while( CB_vtri_leo_dau == 0)	{vTaskDelay(1); if(!wantExit())	break;}
	}
	
	
	robotStop(0);
	
	speed_chan_truoc = 80;
	target_chan_truoc = Min_chan_truoc + 250;
	
	for(i=0;i<250;i++)		
	{
		while(abs(bientrochantruocValue - target_chan_truoc) > 100)	{vTaskDelay(1); if(!wantExit())	break;}
	}
	
	speed_chan_truoc = 40;
	
	for(i=0;i<50;i++)		
	{
		while(abs(bientrochantruocValue - target_chan_truoc) > 10)	{vTaskDelay(1); if(!wantExit())	break;}
	}
	
	robotRunAngle(Angle,10,Robot_Angle,1);
	
 	{
		while(CB_Ha_Dau == 0)		{vTaskDelay(1); if(!wantExit())	break;}
	}
	vTaskDelay(1000);
	
	robotStop(0);


}
	
void xuong_bac_200_xanh_10 (void) {
	Xuong_bac_200(-900, 900);
		if (TinHieu_ChuanBi_GapThang == 0 && TinHieu_ChuanBi_GapTrai == 0 && TinHieu_ChuanBi_GapPhai == 0) {
				su_dung_chan(265);
				// chay toi khi mat cam bien sau
				robotRunAngle(-900,16,900,0.8);
				for(i=0;i<1550;i++)
						{
								while(CB_Ha_Sau == 0 || (abs(bientrochansauValue - target_chan_sau) > 10))	
							{	
								if(!wantExit())	break;
								vTaskDelay (1);
							}
						}
					}

		else if (TinHieu_ChuanBi_GapPhai == 1) {
					chuan_bi_gap_phai_200_tren_7_10();
			}
			robotStop(0);
	}	


void xuong_bac_200_end(void) {
		Xuong_bac_200(-900, 900);
		if (TinHieu_ChuanBi_GapThang == 0 && TinHieu_ChuanBi_GapTrai == 0 && TinHieu_ChuanBi_GapPhai == 0) {
				su_dung_chan(265);
				// chay toi khi mat cam bien sau
				robotRunAngle(-900,16,900,0.8);
				for(i=0;i<1550;i++)
						{
								while(CB_Ha_Sau == 0|| (abs(bientrochansauValue - target_chan_sau) > 10))	
							{	
								if(!wantExit())	break;
								vTaskDelay (1);
							}
						}
						
				robotStop(0);
			
			}
	
		else if (TinHieu_ChuanBi_GapTrai == 1 ) {
				chuan_bi_gap_trai_200_duoi_ko_thanh();
		}
		// CO LENH GAP PHAI
		else if (TinHieu_ChuanBi_GapPhai == 1 ) {
					chuan_bi_gap_phai_200_duoi_ko_thanh();
		}
}

// qua trai len 400 o cua vao rung
void qua_trai_len_bac_400(void) {
	su_dung_chan(700);
	
	for(i=0;i<150;i++)		
	{
		while(abs(bientrochansauValue - target_chan_sau) > 10)	{vTaskDelay(1); if(!wantExit())	break;}
	}
	
	kiem_tra_huong_quay_tay_gap_phia_truoc();
	
	for(i=0;i<1050;i++)	
	{	
		while( lazePhaiValue < 220)	{vTaskDelay(1); if(!wantExit())	break;}
	}
	chinh_lai_vi_tri_laser_phai(vi_tri_cua_rung_xanh_1_lazer_phai_tay_41 - 10, 1000);
	
		
	robotRunAngle(-900,6,900,0.2);
	for(i=0;i<1050;i++)	
	{	
		while(CB_Cap_Thanh_Sau == 0)	{vTaskDelay(1); if(!wantExit())	break;}
	}
	robotStop(10);
		
	if (TinHieu_ChuanBi_GapThang == 1 ) {
		if (da_lay_tay1 == 1 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
					chinh_lai_vi_tri_laser_phai(vi_tri_cua_rung_xanh_1_lazer_phai_tay_41, 1000);
					}
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
					chinh_lai_vi_tri_laser_phai(vi_tri_cua_rung_xanh_1_lazer_phai_tay_23, 1000);
					}
				}
	robotRunAngle(-900,6,900,0.2);
	for(i=0;i<1050;i++)	
	{	
		while(CB_Cap_Thanh_Sau == 0)	{vTaskDelay(1); if(!wantExit())	break;}
	}
	vTaskDelay(2000);
	robotStop(0);
}

//============== Sang phai lên bac 400 o ria rung ===================

void qua_phai_len_bac_400(void) {
	su_dung_chan(700);
	
	for(i=0;i<150;i++)		
	{
		while(abs(bientrochansauValue - target_chan_sau) > 10)	{vTaskDelay(1); if(!wantExit())	break;}
	}
	
	kiem_tra_huong_quay_tay_gap_phia_truoc();
	for(i=0;i<1050;i++)	
	{	
		while( lazeTraiValue < 230)	{vTaskDelay(1); if(!wantExit())	break;}
	}
	chinh_lai_vi_tri_laser_phai(vi_tri_cua_rung_xanh_3_lazer_phai_tay_23 + 10, 1000);
	
	robotStop(0);
	robotRunAngle(-900,6,900,0.8);
	for(i=0;i<1050;i++)	
	{	
		while(CB_Cap_Thanh_Sau == 0)	{vTaskDelay(1); if(!wantExit())	break;}
	}

	robotStop(10);
	if (TinHieu_ChuanBi_GapThang == 1 ) {
				
		if (da_lay_tay1 == 1 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
					chinh_lai_vi_tri_laser_phai(vi_tri_cua_rung_xanh_3_lazer_phai_tay_41, 1000);
					}
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
					chinh_lai_vi_tri_laser_phai(vi_tri_cua_rung_xanh_3_lazer_phai_tay_23, 1000);
					}
				}
	
	robotStop(0);
				robotRunAngle(-900,6,900,0.8);
	for(i=0;i<1050;i++)	
	{	
		while(CB_Cap_Thanh_Sau == 0)	{vTaskDelay(1); if(!wantExit())	break;}
	}
	vTaskDelay(2000);
	robotStop(0);
		
		
}
//============== Sang trai lên bac 200 o ria ===================
void qua_trai_len_bac_200_cua_vao(void) {

	
	kiem_tra_huong_quay_tay_gap_phia_truoc();
	
	for(i=0;i<1050;i++)	
	{	
		while( lazePhaiValue < 380)	{vTaskDelay(1); if(!wantExit())	break;}
	}

	if ( TinHieu_ChuanBi_GapThang == 1 ) {
				chinh_lai_vi_tri_laser_phai(vi_tri_cua_rung_xanh_2_lazer_phai_tay_41 , 1000);
				robotRunAngle(-900,6,900,0.8);
				for(i=0;i<1050;i++)	
				{	
					while( CB_Cap_Thanh_Sau == 0)	{vTaskDelay(1); if(!wantExit())	break;}
				}
					vTaskDelay(2000);
				}
		
		else if  ( TinHieu_ChuanBi_GapThang == 0 ) {
			if (chay_ngang_qua_o1_xanh == 0) {
					chinh_lai_vi_tri_laser_phai_custom(vi_tri_cua_rung_xanh_2_lazer_phai_tay_41 - 15, 1000, 5, 50);
			}
			else if (chay_ngang_qua_o1_xanh == 1) {
					chinh_lai_vi_tri_laser_phai_custom(vi_tri_cua_rung_xanh_1_lazer_phai_tay_41 - 10, 1000, 5, 65);
					}
				}
		
	bai_db = 1;
	robotStop(0);
}

//============== Sang phai lên bac 200 o ria ===================
void qua_phai_len_bac_200_cua_vao(void) {
	kiem_tra_huong_quay_tay_gap_phia_truoc();
	for(i=0;i<1050;i++)	
	{	
		while( lazeTraiValue < 360)	{vTaskDelay(1); if(!wantExit())	break;}
	}

	if ( TinHieu_ChuanBi_GapThang == 1 ) {
				chinh_lai_vi_tri_laser_phai(vi_tri_cua_rung_xanh_2_lazer_phai_tay_41 , 1000);
				robotRunAngle(-900,6,900,0.6);
				for(i=0;i<1050;i++)	
				{	
					while( CB_Cap_Thanh_Sau == 0)	{vTaskDelay(1); if(!wantExit())	break;}
				}
					vTaskDelay(2000);
				}
		
		else if  ( TinHieu_ChuanBi_GapThang == 0 ) {
			if (chay_ngang_qua_o3_xanh == 0) {
					chinh_lai_vi_tri_laser_phai_custom(vi_tri_cua_rung_xanh_2_lazer_phai_tay_41 - 15, 1000, 5 , 50);
			}
			else if (chay_ngang_qua_o3_xanh == 1) {
						chinh_lai_vi_tri_laser_phai_custom(vi_tri_cua_rung_xanh_3_lazer_phai_tay_23 + 10, 1000, 5,65);
						}

				}
		
		robotStop(10);
		bai_db = 1;

}

void moqua(void) {
		Kep_phai_4_ra;
		vTaskDelay(2000);
		Kep_phai_1_ra;
		vTaskDelay(2000);
		Kep_phai_2_ra;
		vTaskDelay(2000);
		Kep_phai_3_ra;
		vTaskDelay(2000);
}

	void Xuong_bac_400 (int Angle, int Robot_Angle)
{	
	int i;
	Nang_nhanh();
	
	target_chan_truoc = Min_chan_truoc + 10, target_chan_sau = Min_chan_sau + 10;
	for(i=0;i<50;i++)		
	{
		while(abs(bientrochansauValue - target_chan_sau) > 8)	{vTaskDelay(1); if(!wantExit())	break;}
	}
	
	robotRunAngle(Angle,12,Robot_Angle,0.7);

	for(i=0;i<250;i++)
	{	
		while(CB_vtri_leo == 0 || CB_ROI_1 == 1  && CB_ROI_4 == 1)	{vTaskDelay(5); if(!wantExit())	break;}
	}
	
	vTaskDelay(2200);
	
	target_chan_sau = Min_chan_sau + 5;
	
	robotRunAngle(Angle,10,Robot_Angle,0.5);
	RESET_ENCODER();
	
	while(abs(ENCODER_FR()) + abs(ENCODER_FL()) < 500)	{vTaskDelay (1); if(!wantExit())	break;}
	
	robotStop(0);
		
	speed_chan_sau = 170;
	target_chan_sau = Max_chan_sau - 10;
	
	for(i=0;i<50;i++)		
	{
		while(abs(bientrochansauValue - target_chan_sau) > 100)	{vTaskDelay(1); if(!wantExit())	break;}
	}
	
	speed_chan_sau = 25;
	
	for(i=0;i<50;i++)		
	{
		while(abs(bientrochansauValue - target_chan_sau) > 15)	{vTaskDelay(1); if(!wantExit())	break;}
	}
	
	vTaskDelay(1000);

	robotRunAngle(Angle,10,Robot_Angle,0.5);
	
	for(i=0;i<550;i++)	
	{	
		while(CB_bung == 0)	{vTaskDelay(1); if(!wantExit())	break;}
	}
	
	target_chan_truoc = Min_chan_truoc + 5;
	
	for(i=0;i<1000;i++)	
	{	
		while( CB_ROI_3 == 0 ||  CB_ROI_2 == 0)	{vTaskDelay(1); if(!wantExit())	break;}
	}
	vTaskDelay(1500);
	robotStop(0);

	speed_chan_truoc = 200;
	target_chan_truoc = Max_chan_truoc - 10;
	
	for(i=0;i<250;i++)		
	{
		while(abs(bientrochantruocValue - target_chan_truoc) > 100)	{vTaskDelay(1); if(!wantExit())	break;}
	}
	
	speed_chan_truoc = 40;
	
	for(i=0;i<250;i++)		
	{
		while(abs(bientrochantruocValue - target_chan_truoc) > 10)	{vTaskDelay(1); if(!wantExit())	break;}
	}
	
	robotRunAngle(Angle,10,Robot_Angle,0.5);
	
	for(i=0;i<150;i++) 
	{
		while(CB_Ha_Dau == 0)		{vTaskDelay(1); if(!wantExit())	break;}
	}
	vTaskDelay(1500);
	robotStop(0);
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
		robotRunAngle(runangle - fix, speed, AngleHead, 0.5);
	}
	else if (lazePhaiValue - lazer_stable_phai > num_change_stable)
	{
		robotRunAngle(runangle + fix, speed, AngleHead, 0.5);
	}
	else
		robotRunAngle(runangle, speed, AngleHead, 0.5);
}

void Bam_thanh_laser_phai_cua_vao(int speed, int runangle, int AngleHead, int lazer_stable_phai, int num_change_stable, int fix_max,int rat)
{
	int fix;

	fix = abs(lazePhaiValue - lazer_stable_phai) * rat;

	if (fix > fix_max)
	fix = fix_max;

	if (lazePhaiValue - lazer_stable_phai < num_change_stable)
	{
		robotRunAngle(runangle + fix, speed, AngleHead, 0.5);
	}
	else if (lazePhaiValue - lazer_stable_phai > num_change_stable)
	{
		robotRunAngle(runangle - fix, speed, AngleHead, 0.5);
	}
	else
		robotRunAngle(runangle, speed, AngleHead, 0.5);
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


//********************************************* bam thanh laser sau ********************************************
void Bam_laser_sau(int speed, int runangle, int AngleHead, int lazer_stable_sau, int num_change_stable, int fix_max,int rat)
{
	int fix;

	fix = abs(lazeSauValue - lazer_stable_sau) * rat;

	if (fix > fix_max)
	fix = fix_max;

	if (lazeSauValue - lazer_stable_sau < num_change_stable)
	{
		robotRunAngle(runangle - fix, speed, AngleHead, 0.7);
	}
	else if (lazeSauValue - lazer_stable_sau > num_change_stable)
	{
		robotRunAngle(runangle + fix, speed, AngleHead, 0.7);
	}
	else
		robotRunAngle(runangle, speed, AngleHead, 0.7);
}
/////////////////////////////leodoc/////////////////////////////////////////
	void leodoc1(void)
{	
	int i;
	
	Nang_cuc_nhanh();
	
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
	
	Nang_cuc_nhanh();
	
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
	else Man_xoay_tay = 0,tay_xoay = 0;
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
	Xuong_bac_400(-900, 900);
	robotRunAngle(-900,10,900,0.8);
	vTaskDelay (4000);
	robotStop(0);
	mode_chay_rung = 0;
	hoan_thanh_chay_rung = 1;

}

void vuot_rung_ve_homeTay_bac_200 (void) {
	Xuong_bac_200(-900, 900);
	robotRunAngle(-900,10,900,0.8);
	vTaskDelay (4000);
	robotStop(0);
	mode_chay_rung = 0;
	hoan_thanh_chay_rung = 1;

}
// ******************Home***************************
void vehome(void)
{
	robotStop(0);
	robotResetIMU();

	Nang_thuong();

	target_chan_truoc = 280;
	target_chan_sau = 280;

	speed_tay_gat2 = 200;
	target_tay_gat2 = vitri_tay2home;
	
	speed_tay_gat1 =200;
	target_tay_gat1 = vitri_tay1home;
	
	
	speed_tay_xoay = 100;
	target_xoay_tay = vi_tri_tay_43;
	
	Tay2_xuong;
	Tay1_xuong;
	Tay_kep_dong;
	
	Kep_phai_1_vao;
	Kep_phai_2_vao;
	Kep_phai_3_vao;
	Kep_phai_4_vao;
	
	if(!wantExit());
}

void vehome_xuat_phat(void)
{
	robotStop(0);
	robotResetIMU();

	Nang_cham();

	target_chan_truoc = 247;//
	target_chan_sau = 247;//home lay vk
	
//	speed_tay_gat2 = 50;
//	target_tay_gat2 = 564;//home lay vk
////	
//	speed_tay_gat1 =50;
//	target_tay_gat1 = 565;
//	
	speed_tay_xoay = 100;
	target_xoay_tay = vi_tri_tay_43;
	
	Tay2_xuong;
	Tay1_xuong;
	
	Kep_phai_1_vao;
	Kep_phai_2_vao;
	Kep_phai_3_vao;
	Kep_phai_4_vao;
}


void phun_tay(void) {
		Tay2_len;
		Tay1_len;
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
    bool retry;
    do {
        retry = false;
        Kep_phai_4_ra;
        Tay2_len;

        speed_tay_gat2 = 250;
        target_tay_gat2 = Min_tay_gat2 + 105;
        for(i=0; i<50; i++) { 
            while(abs(bientrodaytay2Value - target_tay_gat2) > 10) { vTaskDelay(1); if(!wantExit()) break; }
        }
        for(i=0; i<550; i++) { 
            while(CB_xilanh_tay_2 == 1) { vTaskDelay(1); if(!wantExit()) break; }
        }
                
        tracking_traiPhaiThang_tren_tay4();
        
        speed_tay_gat2 = 250;
        target_tay_gat2 = (Min_tay_gat2 + 45);
        vTaskDelay(5000); 
        for(i=0; i<500; i++) { 
            while (abs(bientrodaytay2Value - (Min_tay_gat2 + 45)) > 10) 
            {
                speed_tay_gat2 = 250;
                target_tay_gat2 = Min_tay_gat2 + 105;
                
                while (abs(bientrodaytay2Value - target_tay_gat2) > 8) 
                {
                    vTaskDelay(1); 
                    if (!wantExit()) break; 
                }
                
                vTaskDelay(1000);
                tracking_traiPhaiThang_tren_tay4();

                speed_tay_gat2 = 150;
                target_tay_gat2 = Min_tay_gat2 + 45;
                vTaskDelay(5000); 

                if (!wantExit()) break;
            }
        }
        vTaskDelay(1000);
        Kep_phai_4_vao;
        vTaskDelay(1000);

        Tay2_xuong;    
        
        speed_tay_gat2 = 250;
        target_tay_gat2 = vitri_tay2home;
        for(i=0; i<50; i++) { 
            while(abs(bientrodaytay2Value - target_tay_gat2) > ((vitri_tay2home - Min_tay_gat2) / 1.6))    
            { vTaskDelay(1); if(!wantExit()) break; }
        }

        if (CB_kep_4_2 == 1 && CB_kep_4_1 == 1) {
            retry = true;
        }

    } while (retry && wantExit());
}

// ********** gap lan 2 **********
void gap_tay1_bac_400(void) 
{
    bool retry;
    do {
        retry = false;
        Kep_phai_1_ra;
        Tay1_len;
    
        speed_tay_gat1 = 250;
        target_tay_gat1 = (Max_tay_gat1 - 90);
        for(i = 0; i < 50; i++) { 
            while(abs(bientrodaytay1Value - target_tay_gat1) > 10) { vTaskDelay(1); if(!wantExit()) break; }
        }
        for(i = 0; i < 50; i++) { 
            while(CB_xilanh_tay_1 == 1) { vTaskDelay(1); if(!wantExit()) break; }
        }
        
        tracking_traiPhaiThang_tren_tay1();
        
        speed_tay_gat1 = 250;
        target_tay_gat1 = (Max_tay_gat1 - 45);
        vTaskDelay(5000); 
        
        for(i = 0; i < 50; i++) { 
            while(abs(bientrodaytay1Value - (Max_tay_gat1 - 45)) > 5) {
                speed_tay_gat1 = 250;
                target_tay_gat1 = Max_tay_gat1 - 90;
                
                for(i = 0; i < 50; i++) { 
                    while(abs(bientrodaytay1Value - target_tay_gat1) > 5) {
                        vTaskDelay(1); 
                        if(!wantExit()) break;
                    }
                }
                vTaskDelay(1000);
                tracking_traiPhaiThang_tren_tay1();

                speed_tay_gat1 = 50;
                target_tay_gat1 = (Max_tay_gat1 - 45);
                vTaskDelay(7000); 
            
                vTaskDelay(1); 
                if(!wantExit()) break;
            }
        }
        
        vTaskDelay(1000);
        Kep_phai_1_vao;
        vTaskDelay(1000);
        Tay1_xuong;
                
        speed_tay_gat1 = 150;
        target_tay_gat1 = vitri_tay1home;
        for(i = 0; i < 50; i++) { 
            while(abs(bientrodaytay1Value - target_tay_gat1) > ((vitri_tay1home - Min_tay_gat1) / 1.6)) {
                vTaskDelay(1); if(!wantExit()) break;
            }
        }

        if (CB_kep_1_2 == 1 && CB_kep_1_1 == 1) {
            retry = true;
        }

    } while (retry && wantExit());
}

// ********** gap lan 3 **********
void gap_tay2_bac_400(void) 
{
    bool retry;
    do {
        retry = false;
        Kep_phai_2_ra;
        Tay2_len;
    
        speed_tay_xoay = 100;
        target_xoay_tay = 692;
        for(i = 0; i < 50; i++) { 
            while(bientroxoaytayValue < 690) { vTaskDelay(1); if(!wantExit()) break; }
        }
        
        speed_tay_gat2 = 250;
        target_tay_gat2 = (Max_tay_gat2 - 105);
        for(i = 0; i < 550; i++) { 
            while(abs(bientrodaytay2Value - target_tay_gat2) > 10) { vTaskDelay(1); if(!wantExit()) break; }
        }
        for(i = 0; i < 50; i++) { 
            while(CB_xilanh_tay_2 == 1) { vTaskDelay(1); if(!wantExit()) break; }
        }
        vTaskDelay(1000);
        tracking_traiPhaiThang_tren_tay2(); 
                
        speed_tay_gat2 = 250;
        target_tay_gat2 = (Max_tay_gat2 - 50);
        vTaskDelay(5000); 
            
        for(i = 0; i < 50; i++) { 
            while(abs(bientrodaytay2Value - (Max_tay_gat2 - 50)) > 10) {
                speed_tay_gat2 = 200;
                target_tay_gat2 = Max_tay_gat2 - 105;
                
                for(i = 0; i < 50; i++) { 
                    while(abs(bientrodaytay2Value - target_tay_gat2) > 5) {
                        vTaskDelay(1); 
                        if(!wantExit()) break;
                    }
                }
                vTaskDelay(1000);
                tracking_traiPhaiThang_tren_tay2();

                speed_tay_gat2 = 50;
                target_tay_gat2 = (Max_tay_gat2 - 50);
                vTaskDelay(5000); 
            
                vTaskDelay(1); 
                if(!wantExit()) break;
            }
        }    
        vTaskDelay(1000);
        Kep_phai_2_vao;
        vTaskDelay(1000);
        Tay2_xuong;
    
        speed_tay_gat2 = 250;
        target_tay_gat2 = vitri_tay2home;
        for(i = 0; i < 50; i++) { 
            while(abs(bientrodaytay2Value - target_tay_gat2) > ((vitri_tay2home - Min_tay_gat2) / 1.6)) {
                vTaskDelay(1); if(!wantExit()) break;
            }
        }

        if (CB_kep_2_2 == 1 && CB_kep_2_1 == 1) {
            retry = true;
        }

    } while (retry && wantExit());
}

/// ************* MODULE GAP TUNG TAY BAC 200 TREN *************************


void tracking_traiPhaiThang_tren_tay4(void) {
			if (TinHieu_ChuanBi_GapTrai == 1 ) {
						Ktra_vtri_kep4_trai(); 
					}
			else if (TinHieu_ChuanBi_GapPhai == 1 ) {
						
						Ktra_vtri_kep4_phai(); 
					}
			else  if (TinHieu_ChuanBi_GapThang == 1 ) {
						Ktra_vtri_kep4(); 
					} 
}

void tracking_traiPhaiThang_tren_tay1(void) {
			if (TinHieu_ChuanBi_GapTrai == 1 ) {
						Ktra_vtri_kep1_trai(); 
					}
			else if (TinHieu_ChuanBi_GapPhai == 1 ) {
						
						Ktra_vtri_kep1_phai(); 
					}
			else  if (TinHieu_ChuanBi_GapThang == 1 ) {
						Ktra_vtri_kep1(); 
					} 
}

void tracking_traiPhaiThang_tren_tay2(void) {
			if (TinHieu_ChuanBi_GapTrai == 1 ) {
						Ktra_vtri_kep2_trai(); 
					}
			else if (TinHieu_ChuanBi_GapPhai == 1 ) {
						
						Ktra_vtri_kep2_phai(); 
					}
			else  if (TinHieu_ChuanBi_GapThang == 1 ) {
						Ktra_vtri_kep2(); 
					} 
}

void tracking_traiPhaiThang_tren_tay3(void) {
			if (TinHieu_ChuanBi_GapTrai == 1 ) {
						Ktra_vtri_kep3_trai(); 
					}
			else if (TinHieu_ChuanBi_GapPhai == 1 ) {
						
						Ktra_vtri_kep3_phai(); 
					}
			else  if (TinHieu_ChuanBi_GapThang == 1 ) {
						Ktra_vtri_kep3(); 
					} 
}
// ********** gap lan 1 **********
void gap_tay4(void) 
{
    bool retry;
    do {
        retry = false;
        Kep_phai_4_ra;
        Tay2_len;

        speed_tay_gat2 = 250;
        target_tay_gat2 = Min_tay_gat2 + 75;
        for(i=0; i<50; i++) { 
            while(CB_xilanh_tay_2 == 1) { vTaskDelay(1); if(!wantExit()) break; }
        }
        for(i=0; i<50; i++) { 
            while(abs(bientrodaytay2Value - target_tay_gat2) > 10) { vTaskDelay(1); if(!wantExit()) break; }
        }

        vTaskDelay(1000);
        tracking_traiPhaiThang_tren_tay4();

        speed_tay_gat2 = 40;
        target_tay_gat2 = Min_tay_gat2 + 25;
        vTaskDelay(5000); 

//        for(i=0; i<500; i++) { 
//            while (abs(bientrodaytay2Value - (Min_tay_gat2 + 25)) > 10) 
//            {
//                speed_tay_gat2 = 250;
//                target_tay_gat2 = Min_tay_gat2 + 75;
//                
//                while (abs(bientrodaytay2Value - target_tay_gat2) > 10) 
//                {
//                    vTaskDelay(1); 
//                    if (!wantExit()) break; 
//                }
//                
//                vTaskDelay(1000);
//                tracking_traiPhaiThang_tren_tay4();

//                speed_tay_gat2 = 150;
//                target_tay_gat2 = Min_tay_gat2 + 25;
//                vTaskDelay(5000); 

//                if (!wantExit()) break;
//            }
//        }
        
        vTaskDelay(1000);
        Kep_phai_4_vao;
        vTaskDelay(1000);
        Tay2_xuong;    
        
        speed_tay_gat2 = 250;
        target_tay_gat2 = vitri_tay2home;
        for(i=0; i<50; i++) { 
            while(abs(bientrodaytay2Value - target_tay_gat2) > ((vitri_tay2home - Min_tay_gat2) / 1.6))
            { vTaskDelay(1); if(!wantExit()) break; }
        }

        if (CB_kep_4_2 == 1 && CB_kep_4_1 == 1) {
            retry = true;
        }

    } while (retry && wantExit());
}

// ********** gap lan 2 **********
void gap_tay1(void) 
{
    bool retry;
    do {
        retry = false;
        Kep_phai_1_ra;
        Tay1_len;
    
        speed_tay_gat1 = 230;
        target_tay_gat1 = Max_tay_gat1 - 70;
                
        for(i=0; i<550; i++) { 
            while(CB_xilanh_tay_1 == 1) { vTaskDelay(1); if(!wantExit()) break; }
        }
        for(i=0; i<50; i++) { 
            while(abs(bientrodaytay1Value - target_tay_gat1) > 5) { vTaskDelay(1); if(!wantExit()) break; }
        }
        
        vTaskDelay(1000);
        tracking_traiPhaiThang_tren_tay1();
            
        speed_tay_gat1 = 50;
        target_tay_gat1 = (Max_tay_gat1 - 25);
        vTaskDelay(5000); 
//            
//        for(i=0; i<50; i++) { 
//            while(abs(bientrodaytay1Value - (Max_tay_gat1 - 25)) > 10) {
//                speed_tay_gat1 = 250;
//                target_tay_gat1 = Max_tay_gat1 - 70;
//                
//                for(i=0; i<50; i++) { 
//                    while(abs(bientrodaytay1Value - target_tay_gat1) > 10) {
//                        vTaskDelay(1); 
//                        if(!wantExit()) break;
//                    }
//                }
//                vTaskDelay(1000);
//                tracking_traiPhaiThang_tren_tay1();

//                speed_tay_gat1 = 50;
//                target_tay_gat1 = (Max_tay_gat1 - 25);
//                vTaskDelay(5000); 
//            
//                vTaskDelay(1); 
//                if(!wantExit()) break;
//            }
//        }
        vTaskDelay(1000);
        Kep_phai_1_vao;
        vTaskDelay(1000);
        Tay1_xuong;
                
        speed_tay_gat1 = 250;
        target_tay_gat1 = vitri_tay1home;
        for(i=0; i<50; i++) { 
            while(abs(bientrodaytay1Value - target_tay_gat1) > ((vitri_tay1home - Min_tay_gat1) / 1.6))
            { vTaskDelay(1); if(!wantExit()) break; }
        }

        if (CB_kep_1_2 == 1 && CB_kep_1_1 == 1) {
            retry = true;
        }

    } while (retry && wantExit());
}

// ********** gap lan 3 **********
void gap_tay2(void) 
{
    bool retry;
    do {
        retry = false;
        Kep_phai_2_ra;
        Tay2_len;
    
        speed_tay_gat2 = 250;
        target_tay_gat2 = Max_tay_gat2 - 80;
        
        for(i=0; i<50; i++) { 
            while(CB_xilanh_tay_2 == 1) { vTaskDelay(1); if(!wantExit()) break; }
        }
        for(i=0; i<50; i++) { 
            while(abs(bientrodaytay2Value - target_tay_gat2) > 10) { vTaskDelay(1); if(!wantExit()) break; }
        }
        
        vTaskDelay(1000);
        tracking_traiPhaiThang_tren_tay2();

        speed_tay_gat2 = 100;
        target_tay_gat2 = (Max_tay_gat2 - 20);
        vTaskDelay(6000); 
            
//        for(i=0; i<50; i++) { 
//            while(abs(bientrodaytay2Value - (Max_tay_gat2 -25)) > 10) {
//                speed_tay_gat2 = 200;
//                target_tay_gat2 = Max_tay_gat2 - 80;
//                
//                for(i=0; i<50; i++) { 
//                    while(abs(bientrodaytay2Value - target_tay_gat2) > 8) {
//                        vTaskDelay(1); 
//                        if(!wantExit()) break;
//                    }
//                }
//                vTaskDelay(1000);
//                tracking_traiPhaiThang_tren_tay2();

//                speed_tay_gat2 = 50;
//                target_tay_gat2 = (Max_tay_gat2 - 25);
//                vTaskDelay(5000); 
//            
//                vTaskDelay(1); 
//                if(!wantExit()) break;
//            }
//        }    
        
        vTaskDelay(1000);
        Kep_phai_2_vao;
        vTaskDelay(1000);
        Tay2_xuong;
    
        speed_tay_gat2 = 250;
        target_tay_gat2 = vitri_tay2home;
        for(i=0; i<50; i++) { 
            while(abs(bientrodaytay2Value - target_tay_gat2) > ((vitri_tay2home - Min_tay_gat2) / 1.6))
            { vTaskDelay(1); if(!wantExit()) break; }
        }

        if (CB_kep_2_2 == 1 && CB_kep_2_1 == 1) {
            retry = true;
        }

    } while (retry && wantExit());
}

// GAP LAN 4
void gap_tay3(void)
{
    bool retry;
    do {
        retry = false;
        Kep_phai_3_ra;
        Tay1_len;
    
        speed_tay_gat1 = 200;
        target_tay_gat1 = Min_tay_gat1 + 87;
        for(i=0; i<50; i++) { 
            while(CB_xilanh_tay_1 == 1) { vTaskDelay(1); if(!wantExit()) break; }
        }
        for(i=0; i<50; i++) { 
            while(abs(bientrodaytay1Value - target_tay_gat1) > 10) { vTaskDelay(1); if(!wantExit()) break; }
        }
                    
        vTaskDelay(1000);
        tracking_traiPhaiThang_tren_tay3();

        speed_tay_gat1 = 50;
        target_tay_gat1 = (Min_tay_gat1 + 40);
        vTaskDelay(5000);
                    
//        for(i=0; i<50; i++) { 
//            while(abs(bientrodaytay1Value - (Min_tay_gat1 + 40)) > 10) {
//                speed_tay_gat1 = 250;
//                target_tay_gat1 = Min_tay_gat1 + 87;
//                
//                for(i=0; i<50; i++) { 
//                    while(abs(bientrodaytay1Value - target_tay_gat1) > 10) {
//                        vTaskDelay(1); 
//                        if(!wantExit()) break;
//                    }
//                }
//                vTaskDelay(1000);
//                tracking_traiPhaiThang_tren_tay3();

//                speed_tay_gat1 = 50;
//                target_tay_gat1 = (Min_tay_gat1 + 40);
//                vTaskDelay(5000); 
//            
//                vTaskDelay(1); 
//                if(!wantExit()) break;
//            }
//        }
        
        vTaskDelay(1000);
        Kep_phai_3_vao;
        vTaskDelay(1000);
        Tay1_xuong;
    
        speed_tay_gat1 = 250;
        target_tay_gat1 = vitri_tay1home;
        for(i=0; i<50; i++) { 
            while(abs(bientrodaytay1Value - target_tay_gat1) > ((vitri_tay1home - Min_tay_gat1) / 1.6))
            { vTaskDelay(1); if(!wantExit()) break; }                
        }

        if (CB_kep_3_2 == 1 && CB_kep_3_1 == 1) {
            retry = true;
        }

    } while (retry && wantExit());
}

/// ************* MODULE GAP TAY 4 3 BAC 200 DUOI TRAI PHAI  *************************

// ********** gap lan 1 **********
void gap_tay4_duoi_trai_phai(int vi_tri) 
{
    bool retry;
    do {
        retry = false;
        speed_tay_xoay = 200;
        target_xoay_tay = vi_tri;
        for(i=0; i<150; i++) { 
            while((abs(bientroxoaytayValue - target_xoay_tay) > 10)) { vTaskDelay(1); if(!wantExit()) break; }
        }
        
        Kep_phai_4_ra;
        Tay2_len;
            
        speed_tay_gat2 = 250;
        target_tay_gat2 = Min_tay_gat2 + 35;

        for(i=0; i<50; i++) { 
            while(CB_xilanh_tay_2 == 1) { vTaskDelay(1); if(!wantExit()) break; }
        }
        for(i=0; i<50; i++) { 
            while(abs(bientrodaytay2Value - target_tay_gat2) > 10) { vTaskDelay(1); if(!wantExit()) break; }
        }

        vTaskDelay(1000);
                
        if (TinHieu_ChuanBi_GapTrai == 1) {
            Ktra_vtri_kep4_trai(); 
        }
        else if (TinHieu_ChuanBi_GapPhai == 1) {
            Ktra_vtri_kep4_phai(); 
        }
                
        vTaskDelay(1000);
        
        speed_tay_gat2 = 50;
        target_tay_gat2 = Min_tay_gat2;
        vTaskDelay(5000); 
        
        for(i=0; i<550; i++) { 
            while(abs(bientrodaytay2Value - Min_tay_gat2) > 8) 
            {
                speed_tay_gat2 = 250;
                target_tay_gat2 = Min_tay_gat2 + 35;
                for(i=0; i<50; i++) { 
                    while(abs(bientrodaytay2Value - target_tay_gat2) > 8) { vTaskDelay(1); if(!wantExit()) break; }
                }
                if (TinHieu_ChuanBi_GapTrai == 1) {
                    Ktra_vtri_kep4_trai(); 
                }
                else if (TinHieu_ChuanBi_GapPhai == 1) {
                    Ktra_vtri_kep4_phai(); 
                }
                speed_tay_gat2 = 50;
                target_tay_gat2 = Min_tay_gat2;
                vTaskDelay(5000); 
                
                vTaskDelay(1);
                if(!wantExit()) break;
            }
        }
        
        vTaskDelay(1000);
        Kep_phai_4_vao;
        vTaskDelay(1000);
        Tay2_xuong;    
        
        speed_tay_gat2 = 250;
        target_tay_gat2 = vitri_tay2home;
        for(i=0; i<50; i++) { 
            while(abs(bientrodaytay2Value - target_tay_gat2) > ((vitri_tay2home - Min_tay_gat2) / 1.6))
            { vTaskDelay(1); if(!wantExit()) break; }
        }

        if (CB_kep_4_2 == 1 && CB_kep_4_1 == 1) {
            retry = true;
        }

    } while (retry && wantExit());
}

// ********** gap lan 2**********
void gap_tay1_duoi_trai_phai(int vi_tri) 
{
    bool retry;
    do {
        retry = false;
        speed_tay_xoay = 200;
        target_xoay_tay = vi_tri;
        for(i=0; i<150; i++) { 
            while((abs(bientroxoaytayValue - target_xoay_tay) > 10)) { vTaskDelay(1); if(!wantExit()) break; }
        }
        
        Kep_phai_1_ra;
        Tay1_len;
            
        speed_tay_gat1 = 250;
        target_tay_gat1 = Max_tay_gat1 - 45;

        for(i=0; i<50; i++) { 
            while(CB_xilanh_tay_1 == 1) { vTaskDelay(1); if(!wantExit()) break; }
        }
        for(i=0; i<50; i++) { 
            while(abs(bientrodaytay1Value - target_tay_gat1) > 10) { vTaskDelay(1); if(!wantExit()) break; }
        }

        vTaskDelay(1000);
//                
        if (TinHieu_ChuanBi_GapTrai == 1) {
            Ktra_vtri_kep1_trai(); 
        }
        else if (TinHieu_ChuanBi_GapPhai == 1) {
            Ktra_vtri_kep1_phai(); 
        }
                
        vTaskDelay(1000);
        
        speed_tay_gat1 = 50;
        target_tay_gat1 = Max_tay_gat1;
        vTaskDelay(5000); 
//        
        for(i=0; i<550; i++) { 
            while(abs(bientrodaytay1Value - Max_tay_gat1) > 8) 
            {
                speed_tay_gat1 = 250;
                target_tay_gat1 =  Max_tay_gat1 - 45;
                for(i=0; i<50; i++) { 
                    while(abs(bientrodaytay1Value - target_tay_gat1) > 8) { vTaskDelay(1); if(!wantExit()) break; }
                }
                if (TinHieu_ChuanBi_GapTrai == 1) {
                    Ktra_vtri_kep1_trai(); 
                }
                else if (TinHieu_ChuanBi_GapPhai == 1) {
                    Ktra_vtri_kep1_phai(); 
                }
                speed_tay_gat1 = 50;
                target_tay_gat1 = Max_tay_gat1;
                vTaskDelay(5000); 
                
                vTaskDelay(1);
                if(!wantExit()) break;
            }
        }
        
        vTaskDelay(1000);
        Kep_phai_1_vao;
        vTaskDelay(1000);
        Tay1_xuong;    
        
        speed_tay_gat1 = 250;
        target_tay_gat1 = vitri_tay1home;
        for(i=0; i<50; i++) { 
            while(abs(bientrodaytay1Value - target_tay_gat1) > ((vitri_tay1home - Min_tay_gat1) / 1.6))
            { vTaskDelay(1); if(!wantExit()) break; }
        }

        if (CB_kep_1_2 == 1 && CB_kep_1_1 == 1) {
            retry = true;
        }

    } while (retry && wantExit());
}

// gap lan 3
void gap_tay2_duoi_trai_phai(int vi_tri)
{
    bool retry;
    do {
        retry = false;
        speed_tay_xoay = 200;
        target_xoay_tay = vi_tri;
        for(i=0; i<150; i++) { 
            while((abs(bientroxoaytayValue - target_xoay_tay) > 10)) { vTaskDelay(1); if(!wantExit()) break; }
        }
        
        Kep_phai_2_ra;
        Tay2_len;
        speed_tay_gat2 = 250;
        target_tay_gat2 = Max_tay_gat2 - 50;
        for(i=0; i<50; i++) { 
            while(CB_xilanh_tay_2 == 1) { vTaskDelay(1); if(!wantExit()) break; }
        }
            
        for(i=0; i<50; i++) { 
            while(abs(bientrodaytay2Value - target_tay_gat2) > 10) { vTaskDelay(1); if(!wantExit()) break; }
        }
        
        vTaskDelay(1000);
        if (TinHieu_ChuanBi_GapTrai == 1) {
            Ktra_vtri_kep2_trai(); 
        }
        else if (TinHieu_ChuanBi_GapPhai == 1) {
            Ktra_vtri_kep2_phai(); 
        }
    
        speed_tay_gat2 = 50;
        target_tay_gat2 = (Max_tay_gat2);
        vTaskDelay(5000);
        
        for(i=0; i<50; i++) { 
            while(abs(bientrodaytay2Value - Max_tay_gat2) > 8) {
                speed_tay_gat2 = 250;
                target_tay_gat2 = Max_tay_gat2 + 60;
                for(i=0; i<50; i++) { 
                    while(abs(bientrodaytay2Value - target_tay_gat2) > 8) { vTaskDelay(1); if(!wantExit()) break; }
                }
                if (TinHieu_ChuanBi_GapTrai == 1) {
                    Ktra_vtri_kep2_trai(); 
                }
                else if (TinHieu_ChuanBi_GapPhai == 1) {
                    Ktra_vtri_kep2_phai(); 
                }
                speed_tay_gat2 = 50;
                target_tay_gat2 = (Max_tay_gat2);
                vTaskDelay(5000);
                
                vTaskDelay(1); 
                if(!wantExit()) break;
            }
        }
        vTaskDelay(1000);
        Kep_phai_2_vao;
        vTaskDelay(1000);
        Tay2_xuong;
    
        speed_tay_gat2 = 250;
        target_tay_gat2 = vitri_tay1home;
        for(i=0; i<50; i++) { 
            while(abs(bientrodaytay2Value - target_tay_gat2) > ((vitri_tay2home - Min_tay_gat2) / 1.6))
            { vTaskDelay(1); if(!wantExit()) break; }
        }

        if (CB_kep_2_2 == 1 && CB_kep_2_1 == 1) {
            retry = true;
        }

    } while (retry && wantExit());
}

// GAP LAN 4
void gap_tay3_duoi_trai_phai(int vi_tri)
{
    bool retry;
    do {
        retry = false;
        speed_tay_xoay = 200;
        target_xoay_tay = vi_tri;
        for(i=0; i<150; i++) { 
            while((abs(bientroxoaytayValue - target_xoay_tay) > 10)) { vTaskDelay(1); if(!wantExit()) break; }
        }
        
        Kep_phai_3_ra;
        Tay1_len;
        speed_tay_gat1 = 250;
        target_tay_gat1 = Min_tay_gat1 + 65;
        for(i=0; i<50; i++) { 
            while(CB_xilanh_tay_1 == 1) { vTaskDelay(1); if(!wantExit()) break; }
        }
            
        for(i=0; i<50; i++) { 
            while(abs(bientrodaytay1Value - target_tay_gat1) > 10) { vTaskDelay(1); if(!wantExit()) break; }
        }
        
        vTaskDelay(1000);
        if (TinHieu_ChuanBi_GapTrai == 1) {
            Ktra_vtri_kep3_trai(); 
        }
        else if (TinHieu_ChuanBi_GapPhai == 1) {
            Ktra_vtri_kep3_phai(); 
        }
    
        speed_tay_gat1 = 50;
        target_tay_gat1 = (Min_tay_gat1 + 5);
        vTaskDelay(5000);
        
        for(i=0; i<50; i++) { 
            while(abs(bientrodaytay1Value - (Min_tay_gat1 + 5)) > 10) {
                speed_tay_gat1 = 250;
                target_tay_gat1 = Min_tay_gat1 + 65;
                for(i=0; i<50; i++) { 
                    while(abs(bientrodaytay1Value - target_tay_gat1) > 8) { vTaskDelay(1); if(!wantExit()) break; }
                }
                if (TinHieu_ChuanBi_GapTrai == 1) {
                    Ktra_vtri_kep3_trai(); 
                }
                else if (TinHieu_ChuanBi_GapPhai == 1) {
                    Ktra_vtri_kep3_phai(); 
                }
                speed_tay_gat1 = 50;
                target_tay_gat1 = (Min_tay_gat1 + 6);
                vTaskDelay(5000);
                
                vTaskDelay(1); 
                if(!wantExit()) break;
            }
        }
        vTaskDelay(1000);
        Kep_phai_3_vao;
        vTaskDelay(1000);
        Tay1_xuong;
    
        speed_tay_gat1 = 250;
        target_tay_gat1 = vitri_tay1home;
        for(i=0; i<50; i++) { 
            while(abs(bientrodaytay1Value - target_tay_gat1) > ((vitri_tay1home - Min_tay_gat1) / 1.6))
            { vTaskDelay(1); if(!wantExit()) break; }
        }

        if (CB_kep_3_2 == 1 && CB_kep_3_1 == 1) {
            retry = true;
        }

    } while (retry && wantExit());
}
////// ************************** GAP 200 BAC DUOI THANG *******************

// ********** gap lan 1 **********
void gap_tay4_duoi(void) 
{
    bool thu_lai = false;

    do {
        Kep_phai_4_ra;
        Tay2_len;
        speed_tay_gat2 = 250;
        target_tay_gat2 = Min_tay_gat2 + 40;
        
        for(i=0; i<250; i++) { 
            while(CB_xilanh_tay_2 == 1) {
                vTaskDelay(1); 
                if(!wantExit()) return; 
            }
        }
        
        for(i=0; i<550; i++) { 
            while(abs(bientrodaytay2Value - target_tay_gat2) > 6) {
                vTaskDelay(1); 
                if(!wantExit()) return;
            }
        }

        vTaskDelay(1000);
        Ktra_vtri_kep4(); 

        Nang_thuong();
        target_chan_truoc = 365;
        target_chan_sau = 275;
        for(i=0; i<150; i++) {
            while(abs(bientrochantruocValue - target_chan_truoc) > 10) {
                vTaskDelay(1); 
                if(!wantExit()) return;
            }
        }
        
        speed_tay_gat2 = 50;
        target_tay_gat2 = Min_tay_gat2 + 18;
        vTaskDelay(5000);

        for(i=0; i<50; i++) { 
            while(abs(bientrodaytay2Value - (Min_tay_gat2 + 18)) > 10) {
                speed_tay_gat2 = 250;
                target_tay_gat2 = Min_tay_gat2 + 80;
                for(i=0; i<550; i++) { 
                    while(abs(bientrodaytay2Value - target_tay_gat2) > 10) {
                        vTaskDelay(1); 
                        if(!wantExit()) return;
                    }
                }
                Ktra_vtri_kep4(); 
                speed_tay_gat2 = 50;
                target_tay_gat2 = Min_tay_gat2 + 18;
                vTaskDelay(5000);
                
                vTaskDelay(1); 
                if(!wantExit()) break; 
            }
        }

        Kep_phai_4_vao;
        Tay2_xuong;    
        
        Nang_cham();
        target_chan_truoc = 265;
        target_chan_sau = 265;

        speed_tay_gat2 = 250;
        target_tay_gat2 = vitri_tay2home;
        for(i=0; i<50; i++) { 
            while(abs(bientrodaytay2Value - target_tay_gat2) > ((vitri_tay2home - Min_tay_gat2) / 1.6)) {
                vTaskDelay(1); 
                if(!wantExit()) return;
            }
        }
        if (CB_kep_4_2 == 1 && CB_kep_4_1 == 1) {
            thu_lai = true;
        } else {
            thu_lai = false;
        }

    } while (thu_lai && wantExit());
}

// ********** gap lan 2 **********
void gap_tay1_duoi(void) 
{
    bool check_failed = false;

    do {
        speed_tay_xoay = 100;
        target_xoay_tay = vi_tri_tay_12 + 3;
        
        for(i=0; i<150; i++) { 
            while(abs(bientroxoaytayValue - target_xoay_tay) > 10) {
                vTaskDelay(1); 
                if(!wantExit()) return; 
            }
        }
        Tay1_len;
        Kep_phai_1_ra;
        speed_tay_gat1 = 150;
        target_tay_gat1 = (Max_tay_gat1 - 35);
        
        for(i=0; i<50; i++) { 
            while(CB_xilanh_tay_1 == 1) {
                vTaskDelay(1); 
                if(!wantExit()) return;
            }
        }
        
        for(i=0; i<550; i++) { 
            while(abs(bientrodaytay1Value - target_tay_gat1) > 10) {
                vTaskDelay(1); 
                if(!wantExit()) return;
            }
        }

        vTaskDelay(1400);
        Ktra_vtri_kep1(); 
                        
        // -Nâng nhanh ---
        Nang_thuong();
        target_chan_truoc = 365;
        target_chan_sau = 275;
        for(i=0; i<150; i++) {
            while(abs(bientrochantruocValue - target_chan_truoc) > 10) {
                vTaskDelay(1); 
                if(!wantExit()) return;
            }
        }
        
        speed_tay_gat1 = 50;
        target_tay_gat1 = Max_tay_gat1 - 17;
        vTaskDelay(5000);

        // --- ---
        for(i=0; i<50; i++) { 
            while(abs(bientrodaytay1Value -  (Max_tay_gat1 - 17 )) > 10) {
                speed_tay_gat1 = 250;
                target_tay_gat1 = (Max_tay_gat1 - 65);
                for(i=0; i<550; i++) { 
                    while(abs(bientrodaytay1Value - target_tay_gat1) > 8) {
                        vTaskDelay(1); 
                        if(!wantExit()) break;
                    }
                }
                Ktra_vtri_kep1();
                speed_tay_gat1 = 50;
                target_tay_gat1 = Max_tay_gat1 - 17;
                vTaskDelay(5000);
                
                vTaskDelay(1); 
                if(!wantExit()) break;
            }
        }

        vTaskDelay(1000);
        Kep_phai_1_vao;
        Tay1_xuong;
                
        Nang_cham();
        target_chan_truoc = 265;
        target_chan_sau = 265;
    
        speed_tay_gat1 = 250;
        target_tay_gat1 = vitri_tay1home;
        for(i=0; i<50; i++) { 
            while(abs(bientrodaytay1Value - target_tay_gat1) > ((vitri_tay1home - Min_tay_gat1) / 1.6)) {
                vTaskDelay(1); 
                if(!wantExit()) break;
            }
        }
        if (CB_kep_1_2 == 1 && CB_kep_1_1 == 1) {
            check_failed = true;
        } else {
            check_failed = false;
        }

    } while (check_failed && wantExit()); 
}


// ********** gap lan 3 **********
void gap_tay2_duoi(void) 
{
    bool retry;
    do {
        retry = false;
        speed_tay_xoay = 100;
        target_xoay_tay = vi_tri_tay_12 + 5;
        Kep_phai_2_ra;
        Tay2_len;
        
        speed_tay_gat2 = 200;
        target_tay_gat2 = (Max_tay_gat2 - 50);
    
        for(i=0; i<50; i++) { 
            while(CB_xilanh_tay_2 == 1) { vTaskDelay(1); if(!wantExit()) break; }
        }
        for(i=0; i<150; i++) { 
            while((abs(bientroxoaytayValue - target_xoay_tay) > 10)) { vTaskDelay(1); if(!wantExit()) break; }
        }
        for(i=0; i<550; i++) { 
            while(abs(bientrodaytay2Value - target_tay_gat2) > 8) { vTaskDelay(1); if(!wantExit()) break; }
        }
        
        vTaskDelay(1400);
        Ktra_vtri_kep2(); 
				kiem_tra_loi = 1;

        Nang_thuong();
				kiem_tra_loi = 2;
        target_chan_truoc = 365;
				kiem_tra_loi = 3;
        target_chan_sau = 275;
				kiem_tra_loi = 4;
					for(i=0; i<150; i++) {
            while(abs(bientrochantruocValue - target_chan_truoc) > 10) {
                vTaskDelay(1); 
                if(!wantExit()) break;
            }
        }
        kiem_tra_loi = 5;
        speed_tay_gat2 = 50;
        target_tay_gat2 = (Max_tay_gat2 - 20);
				kiem_tra_loi = 6;
        vTaskDelay(5000);

        for(i=0; i<50; i++) { 
            while(abs(bientrodaytay2Value - (Max_tay_gat2 - 20)) > 10) {
                speed_tay_gat2 = 250;
                target_tay_gat2 = (Max_tay_gat2 - 60);
                for(i=0; i<550; i++) { 
                    while(abs(bientrodaytay2Value - target_tay_gat2) > 8) { vTaskDelay(1); if(!wantExit()) break; }
                }
                Ktra_vtri_kep2(); 
                speed_tay_gat2 = 250;
                target_tay_gat2 = (Max_tay_gat2 - 20);
                vTaskDelay(5000);
                vTaskDelay(1);
                if(!wantExit()) break;
            }
        }
        
        vTaskDelay(1000);
        Kep_phai_2_vao;
        Tay2_xuong;
        
        Nang_cham();
        target_chan_truoc = 265;
        target_chan_sau = 265;
                
        speed_tay_gat2 = 250;
        target_tay_gat2 = vitri_tay2home;
        for(i=0; i<50; i++) { 
            while(abs(bientrodaytay2Value - target_tay_gat2) > ((vitri_tay2home - Min_tay_gat2) / 1.6)) {
                vTaskDelay(1); if(!wantExit()) break;
            }
        }
        
        if (CB_kep_2_2 == 1 && CB_kep_2_1 == 1) {
            retry = true;
        }

    } while (retry && wantExit());
}

// GAP LAN 4
void gap_tay3_duoi(void)
{
    bool retry;
    do {
        retry = false;
        speed_tay_xoay = 100;
        target_xoay_tay = vi_tri_tay_43 - 5;
        for(i=0; i<150; i++) { 
            while((abs(bientroxoaytayValue - target_xoay_tay) > 10)) { vTaskDelay(1); if(!wantExit()) break; }
        }
        
        Kep_phai_3_ra;
        Tay1_len;
        speed_tay_gat1 = 200;
        target_tay_gat1 = (Min_tay_gat1 + 65);
                
        for(i=0; i<50; i++) { 
            while(CB_xilanh_tay_1 == 1) { vTaskDelay(1); if(!wantExit()) break; }
        }
        for(i=0; i<50; i++) { 
            while(abs(bientrodaytay1Value - target_tay_gat1) > 7) { vTaskDelay(1); if(!wantExit()) break; }
        }

        vTaskDelay(1400);
        Ktra_vtri_kep3(); 
        
        Nang_thuong();
        target_chan_truoc = 365;
        target_chan_sau = 275;
        for(i=0; i<150; i++) {
            while(abs(bientrochantruocValue - target_chan_truoc) > 10) { vTaskDelay(1); if(!wantExit()) break; }
        }
    
        speed_tay_gat1 = 50;
        target_tay_gat1 = (Min_tay_gat1 + 35);
        vTaskDelay(5000); 
                    
        for(i=0; i<250; i++) { 
            while(abs(bientrodaytay1Value - (Min_tay_gat1 + 35)) > 8) {
                speed_tay_gat1 = 250;
                target_tay_gat1 = (Min_tay_gat1 + 80);
                for(i=0; i<150; i++) { 
                    while(abs(bientrodaytay1Value - target_tay_gat1) > 8) { vTaskDelay(1); if(!wantExit()) break; }
                }
                Ktra_vtri_kep3(); 
                speed_tay_gat1 = 50;
                target_tay_gat1 = (Min_tay_gat1 + 35);
                vTaskDelay(5000); 
                vTaskDelay(1); 
                if(!wantExit()) break;
            }
        }
        vTaskDelay(1000);
        Kep_phai_3_vao;
        Tay1_xuong;
        
        Nang_cham();
        target_chan_truoc = 265;
        target_chan_sau = 265;
                
        speed_tay_gat1 = 250;
        target_tay_gat1 = vitri_tay1home;
        for(i=0; i<50; i++) { 
            while(abs(bientrodaytay1Value - target_tay_gat1) > ((vitri_tay1home - Min_tay_gat1) / 1.6)) {
                vTaskDelay(1); if(!wantExit()) break;
            }
        }

        if (CB_kep_3_2 == 1 && CB_kep_3_1 == 1) {
            retry = true;
        }

    } while (retry && wantExit());
}


// ********** xoay toi goc tay tiep theo + mo kep

void kiem_tra_huong_quay_tay_gap_phia_truoc (void) {
	
		if (da_lay_tay1 == 0 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
				Kep_phai_4_ra;
	
		}
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
			
					// quay mam sang tay 1
						speed_tay_xoay = 180;
						target_xoay_tay = vi_tri_tay_12 + 3;
						Kep_phai_1_ra;
						KT_Ha_Tay = 1;
						
						}
		// quay mam sang tay 2
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
						speed_tay_xoay = 180;
						target_xoay_tay = vi_tri_tay_12 - 5;
						Kep_phai_2_ra;
						KT_Ha_Tay = 1;

						}
		// quay mam sang tay 3
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 0) {
					speed_tay_xoay = 180;
					target_xoay_tay = vi_tri_tay_43 - 5;	
					Kep_phai_3_ra;
					KT_Ha_Tay = 1;
					}		
}
/// ******************** CHUAN BI XOAY TAY GAP TRAI *****************************
void kiem_tra_huong_quay_tay_gap_ben_trai (void) {
	
		if (da_lay_tay1 == 0 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
						speed_tay_xoay = 180;
						target_xoay_tay = vi_tri_tay_4_trai_tren;
						Kep_phai_4_ra;
						KT_Ha_Tay_trai = 1;
				
	
		}
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
					// quay mam sang tay 1
						speed_tay_xoay = 180;
						target_xoay_tay = vi_tri_tay_1_trai_tren;
						Kep_phai_1_ra;
						KT_Ha_Tay_trai = 1;
						}
		// quay mam sang tay 2
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
						speed_tay_xoay = 180;
						target_xoay_tay = vi_tri_tay_2_trai_tren;
						Kep_phai_2_ra;
						KT_Ha_Tay_trai = 1;
			
						}
		// quay mam sang tay 3
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 0) {
					speed_tay_xoay = 180;
					target_xoay_tay = vi_tri_tay_3_trai_tren;	
					Kep_phai_3_ra;
					KT_Ha_Tay_trai = 1;
						}										
}
	
/// ******************** CHUAN BI XOAY TAY GAP PHAI *****************************
void kiem_tra_huong_quay_tay_gap_ben_phai (void) {
	
		if (da_lay_tay1 == 0 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
						speed_tay_xoay = 180;
						target_xoay_tay = vi_tri_tay_4_phai_tren;
						Kep_phai_4_ra;
						KT_Ha_Tay_phai = 1;
		}
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
			
					// quay mam sang tay 1
						speed_tay_xoay = 180;
						target_xoay_tay = vi_tri_tay_1_phai_tren;
						Kep_phai_1_ra;
						KT_Ha_Tay_phai = 1;
						}
		// quay mam sang tay 2
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
						speed_tay_xoay = 180;
						target_xoay_tay = vi_tri_tay_2_phai_tren;
						Kep_phai_2_ra;
						KT_Ha_Tay_phai = 1;
						}
		// quay mam sang tay 3
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 0) {
					speed_tay_xoay = 180;
					target_xoay_tay = vi_tri_tay_3_phai_tren;	
					Kep_phai_3_ra;
					KT_Ha_Tay_phai = 1;
						}										
}

// ********** chuan bi ha tay xuong truoc khi toi ////
void kiem_tra_huong_ha_tay_gap_ben_trai (void) {
	
		if (da_lay_tay1 == 0 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0 && Xoay_ok == 1) {
				if (abs(bientroxoaytayValue -  (vi_tri_tay_4_trai_tren)) <= 5) {
				Kep_phai_4_ra;
				speed_tay_gat2 = 240;
				target_tay_gat2 = Min_tay_gat2 + 90;
				}
		}
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0 && Xoay_ok == 1) {
				if (abs(bientroxoaytayValue -  (vi_tri_tay_1_trai_tren)) <= 5) {
						Kep_phai_1_ra;
						speed_tay_gat1 = 200;
						target_tay_gat1 = Max_tay_gat1 - 85;
							}
					}
		// quay mam sang tay 2
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 0 && da_lay_tay4 == 0 && Xoay_ok == 1) {
					if (abs(bientroxoaytayValue -  (vi_tri_tay_2_trai_tren)) <= 5) {
						Kep_phai_2_ra;
						speed_tay_gat2 = 240;
						target_tay_gat2 = Max_tay_gat2 - 85;
							}
					}
		// quay mam sang tay 3
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 0 && Xoay_ok == 1) {
					if (abs(bientroxoaytayValue -  (vi_tri_tay_3_trai_tren)) <= 5) {
						Kep_phai_3_ra;
						speed_tay_gat1 = 200;
						target_tay_gat1 = Min_tay_gat1 + 90;
							}
					}										
}

void kiem_tra_huong_ha_tay_gap_ben_phai (void) {
	
		if (da_lay_tay1 == 0 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0 && Xoay_ok == 1) {
				if (abs(bientroxoaytayValue -  (vi_tri_tay_4_phai_tren)) <= 5) {
				Kep_phai_4_ra;
				speed_tay_gat2 = 240;
				target_tay_gat2 = Min_tay_gat2 + 90;
				}
		}
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0 && Xoay_ok == 1) {
				if (abs(bientroxoaytayValue -  (vi_tri_tay_1_phai_tren)) <= 5) {
						Kep_phai_1_ra;
						speed_tay_gat1 = 200;
						target_tay_gat1 = Max_tay_gat1 - 85;
							}
					}
		// quay mam sang tay 2
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 0 && da_lay_tay4 == 0 && Xoay_ok == 1) {
					if (abs(bientroxoaytayValue -  (vi_tri_tay_2_phai_tren)) <= 5) {
						Kep_phai_2_ra;
						speed_tay_gat2 = 240;
						target_tay_gat2 = Max_tay_gat2 - 85;
							}
					}
		// quay mam sang tay 3
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 0 && Xoay_ok == 1) {
					if (abs(bientroxoaytayValue -  (vi_tri_tay_3_phai_tren)) <= 5) {
						Kep_phai_3_ra;
						speed_tay_gat1 = 200;
						target_tay_gat1 = Min_tay_gat1 + 90;
							}
					}										
}
		
			
/// ********************************************************************************
// ********** chuan bi ha tay xuong truoc khi toi ////
void kiem_tra_huong_ha_tay_gap_phia_truoc (void) {
	
		if (da_lay_tay1 == 0 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0 && Xoay_ok == 1) {
				Kep_phai_4_ra;
				speed_tay_gat2 = 240;
				target_tay_gat2 = Min_tay_gat2 + 85;

		}
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0 && Xoay_ok == 1) {
					if (abs(bientroxoaytayValue -   (vi_tri_tay_12 + 3)) <= 5) {
						Kep_phai_1_ra;
						speed_tay_gat1 = 200;
						target_tay_gat1 = Max_tay_gat1 - 90;
						Tay1_len;
								}
						}
		// quay mam sang tay 2
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 0 && da_lay_tay4 == 0 && Xoay_ok == 1) {
					if (abs(bientroxoaytayValue -  (vi_tri_tay_12 - 5)) <= 5) {
						Kep_phai_2_ra;
						speed_tay_gat2 = 240;
						target_tay_gat2 = Max_tay_gat2 - 90;
						Tay2_len;
								}
						}
		// quay mam sang tay 3
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 0 && Xoay_ok == 1) {
						if (abs(bientroxoaytayValue -  (vi_tri_tay_43 - 5)) <= 5) {
						Kep_phai_3_ra;
						speed_tay_gat1 = 200;
						target_tay_gat1 = Min_tay_gat1 + 85;
						Tay1_len;
								}		
						}										
}


/// ****************** HÀM GAP PHÍA TRUOC *************************			
void Lay_phia_truoc_bac_400_tren (void) {
			KT_Ha_Tay =0 ; /// tat ha tay 400 tren
			if (da_lay_tay1 == 0 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
					speed_tay_xoay = 100;
					target_xoay_tay = vi_tri_tay_43;
					for(i=0;i<150;i++)	{ 
							while((abs(bientroxoaytayValue - target_xoay_tay) > 10) )	{vTaskDelay(1); if(!wantExit())	break;}
					}
					gap_tay4_bac_400();
					da_lay_tay1 = 1;
					}
				
			else if (da_lay_tay1 == 1 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
					speed_tay_xoay = 100;
					target_xoay_tay = vi_tri_tay_12 + 3;
					for(i=0;i<150;i++)	{ 
							while((abs(bientroxoaytayValue - target_xoay_tay) > 10) )	{vTaskDelay(1); if(!wantExit())	break;}
					}
					gap_tay1_bac_400();
					da_lay_tay2 = 1;
			}
			
			
			// dung tay lan 3 
			else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
					speed_tay_xoay = 100;
					target_xoay_tay = vi_tri_tay_12 ;
					for(i=0;i<150;i++)	{ 
							while((abs(bientroxoaytayValue - target_xoay_tay) > 10) )	{vTaskDelay(1); if(!wantExit())	break;}
					}
					gap_tay2_bac_400();
					da_lay_tay3 = 1;
			}
			TinHieu_ChuanBi_GapThang = 0;
			
		if(CHON_SAN == 0){
					di_vao_giua_do();
			}
		else {
					di_vao_giua();
		}
		
	}

void Lay_phia_truoc_bac_200_tren (void) {
				KT_Ha_Tay =0 ; /// tat ha tay 200 tren
			if (da_lay_tay1 == 0 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
					speed_tay_xoay = 200;
					target_xoay_tay = vi_tri_tay_43;
					for(i=0;i<150;i++)	{ 
							while((abs(bientroxoaytayValue - target_xoay_tay) > 8) )	{vTaskDelay(1); if(!wantExit())	break;}
					}
					vTaskDelay(1000);
					gap_tay4();
					da_lay_tay1 = 1;
					}
			
					// dung tay lan 2
			else if (da_lay_tay1 == 1 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
					speed_tay_xoay = 200;
					target_xoay_tay = vi_tri_tay_12 + 3;
					for(i=0;i<150;i++)	{ 
							while((abs(bientroxoaytayValue - target_xoay_tay) > 8) )	{vTaskDelay(1); if(!wantExit())	break;}
					}
					vTaskDelay(1000);
					gap_tay1();
					da_lay_tay2 = 1;
			}
			
			// dung tay lan 3 
			else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
					speed_tay_xoay = 200;
					target_xoay_tay = vi_tri_tay_12 - 5;
					for(i=0;i<150;i++)	{ 
							while((abs(bientroxoaytayValue - target_xoay_tay) > 8) )	{vTaskDelay(1); if(!wantExit())	break;}
					}
					vTaskDelay(1000);
					gap_tay2();
					da_lay_tay3 = 1;
			}
			
			// dung tay lan 4
			else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 0) {
					speed_tay_xoay = 200;
					target_xoay_tay = vi_tri_tay_43 - 5;
					for(i=0;i<150;i++)	{ 
							while((abs(bientroxoaytayValue - target_xoay_tay) > 8) )	{vTaskDelay(1); if(!wantExit())	break;}
					}
					vTaskDelay(1000);
					gap_tay3();
					
					da_lay_tay4 = 1;
			}
			TinHieu_ChuanBi_GapThang = 0;
			if(CHON_SAN == 0){
					di_vao_giua_do();
			}
			else {
						di_vao_giua();
			}
}

	/// ****************** HÀM GAP BEN phai *************************		
	void Lay_ben_phai_bac_200_tren (void) {
					KT_Ha_Tay_phai = 0;
			if (da_lay_tay1 == 0 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
						speed_tay_xoay = 100;
						target_xoay_tay = vi_tri_tay_4_phai_tren;
						for(i=0;i<550;i++)	{ 
								while((abs(bientroxoaytayValue - target_xoay_tay) > 3) )	{vTaskDelay(1); if(!wantExit())	break;}
						}
						vTaskDelay(1000);
						gap_tay4();
						
						if(CHON_SAN == 0)			{
							robotRunAngle(-1050,10,-900,0.8);
							vTaskDelay (4000);
						}
						else {
								robotRunAngle(-1050,10,900,0.8);
								vTaskDelay (4000);
						}
						da_lay_tay1 = 1;
						}
				
						// dung tay lan 2
				else if (da_lay_tay1 == 1 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
						speed_tay_xoay = 100;
						target_xoay_tay = vi_tri_tay_1_phai_tren;
						for(i=0;i<550;i++)	{ 
								while((abs(bientroxoaytayValue - target_xoay_tay) > 3) )	{vTaskDelay(1); if(!wantExit())	break;}
						}
						vTaskDelay(1000);
						gap_tay1();
						
						if(CHON_SAN == 0)			{
							robotRunAngle(1050,10,-900,0.8);
							vTaskDelay (4000);
						}
						else {
								robotRunAngle(-1050,10,900,0.8);
								vTaskDelay (4000);
						}
						da_lay_tay2 = 1;
				}
				
				// dung tay lan 3 
				else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
						speed_tay_xoay = 100;
						target_xoay_tay = vi_tri_tay_2_phai_tren;
						for(i=0;i<550;i++)	{ 
								while((abs(bientroxoaytayValue - target_xoay_tay) > 3) )	{vTaskDelay(1); if(!wantExit())	break;}
						}
						vTaskDelay(1000);
						gap_tay2();
						if(CHON_SAN == 0)			{
							robotRunAngle(-20,10,-900,0.8);
							vTaskDelay (4000);
						}
						else {
								robotRunAngle(-1820,10,900,0.8);
								vTaskDelay (4000);
						}
						da_lay_tay3 = 1;
				}
				
				// dung tay lan 4
				else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 0) {
						speed_tay_xoay = 100;
						target_xoay_tay = vi_tri_tay_3_phai_tren;
						for(i=0;i<150;i++)	{ 
								while((abs(bientroxoaytayValue - target_xoay_tay) > 3) )	{vTaskDelay(1); if(!wantExit())	break;}
						}
						vTaskDelay(1000);
						gap_tay3();
						if(CHON_SAN == 0)			{
							robotRunAngle(-20,10,-900,0.8);
							vTaskDelay (4000);
						}
						else {
								robotRunAngle(-1820,10,900,0.8);
								vTaskDelay (4000);
						}
						da_lay_tay4 = 1;
				}
				
//				
				TinHieu_ChuanBi_GapPhai =0;	
	}
	
void Lay_ben_phai_bac_200_tren_xanh_4(void) {
			Lay_ben_phai_bac_200_tren();
			robotRunAngle(1650,9,900,0.3);
			vTaskDelay (4000);
			robotStop(0);
			
	if (TinHieu_ChuanBi_GapThang == 1) {
			kiem_tra_huong_quay_tay_gap_phia_truoc();
			vTaskDelay (7000);
			chuan_bi_gap_thang_xanh_4();
				}
			robotStop(0);
}





///  ****** MODULE LAY 200 BEN PHAI DUOI ******
void Lay_ben_phai_bac_200_duoi (void) {
		KT_Ha_Tay_phai = 0;
		if (da_lay_tay1 == 0 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
					speed_tay_xoay = 200;
					target_xoay_tay = vi_tri_tay_4_phai_tren;
					for(i=0;i<150;i++)	{ 
							while((abs(bientroxoaytayValue - target_xoay_tay) > 5) )	{vTaskDelay(1); if(!wantExit())	break;}
					}
					gap_tay4_duoi_trai_phai(vi_tri_tay_4_phai_tren);
//					
					if(CHON_SAN == 0)	{ // san do
					robotRunAngle(50,10,-900,0.8);
					vTaskDelay(6000);
						}
					else { // san xanh
					robotRunAngle(-1750,10,900,0.8);
					vTaskDelay(6000);
					}
					da_lay_tay1 = 1;
					}
		// dung tay lan 2
			else if (da_lay_tay1 == 1 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
					speed_tay_xoay = 200;
					target_xoay_tay = vi_tri_tay_1_phai_tren;
					for(i=0;i<150;i++)	{ 
							while((abs(bientroxoaytayValue - target_xoay_tay) > 5) )	{vTaskDelay(1); if(!wantExit())	break;}
					}
					gap_tay1_duoi_trai_phai(vi_tri_tay_1_phai_tren);
					
					if(CHON_SAN == 0)	{ // san do
					robotRunAngle(50,10,-900,0.8);
					vTaskDelay(6000);
						}
					else { // san xanh
					robotRunAngle(-1750,10,900,0.8);
					vTaskDelay(6000);
					}
					da_lay_tay2 = 1;
					}
			// dung tay lan 3
			else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
					speed_tay_xoay = 200;
					target_xoay_tay = vi_tri_tay_2_phai_tren;
					for(i=0;i<150;i++)	{ 
							while((abs(bientroxoaytayValue - target_xoay_tay) > 5) )	{vTaskDelay(1); if(!wantExit())	break;}
					}
					gap_tay2_duoi_trai_phai(vi_tri_tay_2_phai_tren);
					
					if(CHON_SAN == 0)	{ // san do
					robotRunAngle(-50,10,-900,0.8);
					vTaskDelay(6000);
						}
					else { // san xanh
					robotRunAngle(-1850,10,900,0.8);
					vTaskDelay(6000);
					}
					da_lay_tay3 = 1;
					}

			else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 0) {
					speed_tay_xoay = 200;
					target_xoay_tay = vi_tri_tay_3_phai_tren;
					for(i=0;i<150;i++)	{ 
							while((abs(bientroxoaytayValue - target_xoay_tay) > 5) )	{vTaskDelay(1); if(!wantExit())	break;}
					}
					gap_tay3_duoi_trai_phai(vi_tri_tay_3_phai_tren);
					da_lay_tay4 = 1;
					
					if(CHON_SAN == 0)	{ // san do
					robotRunAngle(-50,10,-900,0.8);
					vTaskDelay(6000);
					}
					else { // san xanh
					robotRunAngle(-1850,10,900,0.8);
					vTaskDelay(6000);
					}
			}

			TinHieu_ChuanBi_GapPhai = 0;
}

// *********** HAM LAY BEN PHAI 200 DUOI ***********
void Lay_ben_phai_bac_200_duoi_xanh_8(void) {
			Lay_ben_phai_bac_200_duoi();
			robotStop(0);
			
	if (TinHieu_ChuanBi_GapThang == 1) {
			kiem_tra_huong_quay_tay_gap_phia_truoc();
			vTaskDelay (7000);
			di_tren_buc_khong_thanh_2_ben();
				}
		// CO LENH GAP TRAI
		else if (TinHieu_ChuanBi_GapTrai == 1 ) {
				kiem_tra_huong_quay_tay_gap_ben_trai();
				vTaskDelay (7000);
				chuan_bi_gap_trai_200_duoi_ko_thanh();
		}
}


void Lay_ben_phai_bac_200_tren_xanh_7(void) {
			Lay_ben_phai_bac_200_tren();
			robotRunAngle(1650,9,900,0.5);
			vTaskDelay (4000);
			robotStop(0);
	
	if (TinHieu_ChuanBi_GapThang == 1) {
			kiem_tra_huong_quay_tay_gap_phia_truoc();
			vTaskDelay (7000);
			chuan_bi_gap_thang_xanh_7();
		}
			robotStop(0);
}

void Lay_ben_phai_bac_200_tren_xanh_11 (void) {
		Lay_ben_phai_bac_200_tren();
		robotStop(0);


}

/// *************** LAY BEN TRAI 200 TREN ********************
void Lay_ben_trai_bac_200_tren (void) {
		KT_Ha_Tay_trai = 0;
		if (da_lay_tay1 == 0 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
					speed_tay_xoay = 100;
					target_xoay_tay = vi_tri_tay_4_trai_tren;
					for(i=0;i<150;i++)	{ 
							while((abs(bientroxoaytayValue - target_xoay_tay) > 3) )	{vTaskDelay(1); if(!wantExit())	break;}
					}
					gap_tay4();
					if(CHON_SAN == 0) {	 // san do
						robotRunAngle(1900,15,-900,0.8);
						vTaskDelay(5000);
						}
					else {  // san xanh
						robotRunAngle(100,15,900,0.8);
						vTaskDelay(5000);
						}
					da_lay_tay1 = 1;
					}
			
					// dung tay lan 2
			else if (da_lay_tay1 == 1 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
					speed_tay_xoay = 100;
					target_xoay_tay = vi_tri_tay_1_trai_tren;
					for(i=0;i<150;i++)	{ 
							while((abs(bientroxoaytayValue - target_xoay_tay) > 3) )	{vTaskDelay(1); if(!wantExit())	break;}
					}
					gap_tay1();
					if(CHON_SAN == 0) {	 // san do
						robotRunAngle(1900,15,-900,0.8);
						vTaskDelay(5000);
						}
					else {  // san xanh
						robotRunAngle(100,15,900,0.8);
						vTaskDelay(5000);
						}
					da_lay_tay2 = 1;
			}
			
			// dung tay lan 3 
			else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
					speed_tay_xoay = 100;
					target_xoay_tay = vi_tri_tay_2_trai_tren;
					for(i=0;i<150;i++)	{ 
							while((abs(bientroxoaytayValue - target_xoay_tay) > 3) )	{vTaskDelay(1); if(!wantExit())	break;}
					}
					gap_tay2();
					if(CHON_SAN == 0) {	 // san do
						robotRunAngle(1650,15,-900,0.8);
						vTaskDelay(5000);
						}
					else {  // san xanh
						robotRunAngle(-150,15,900,0.8);
						vTaskDelay(5000);
						}
					da_lay_tay3 = 1;
			}
			
			// dung tay lan 4
			else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 0) {
					speed_tay_xoay = 100;
					target_xoay_tay = vi_tri_tay_3_trai_tren;
					for(i=0;i<150;i++)	{ 
							while((abs(bientroxoaytayValue - target_xoay_tay) > 3) )	{vTaskDelay(1); if(!wantExit())	break;}
					}
					gap_tay3();
					if(CHON_SAN == 0) {	 // san do
						robotRunAngle(1650,15,-900,0.8);
						vTaskDelay(5000);
						}
					else {  // san xanh
						robotRunAngle(-150,15,900,0.8);
						vTaskDelay(5000);
						}
					
					da_lay_tay4 = 1;
			}

			TinHieu_ChuanBi_GapTrai = 0;
}

//// **************** MODULE GAP 200 DUOI TAY 3 4 ********
void Lay_ben_trai_bac_200_duoi (void) {
		KT_Ha_Tay_trai = 0;
		if (da_lay_tay1 == 0 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
					speed_tay_xoay = 200;
					target_xoay_tay = vi_tri_tay_4_trai_tren;
					for(i=0;i<150;i++)	{
							while((abs(bientroxoaytayValue - target_xoay_tay) > 5) )	{vTaskDelay(1); if(!wantExit())	break;}
					}
					gap_tay4_duoi_trai_phai(vi_tri_tay_4_trai_tren);
					da_lay_tay1 = 1;
					
					if(CHON_SAN == 0)		{							//SAN DO
							robotRunAngle(1750,10,-900,0.5);
							vTaskDelay(6000); }
					else {
							robotRunAngle(50,10,900,0.8);
							vTaskDelay(6000);
						}
					}
		
			// lay lan 2
			else if (da_lay_tay1 == 1 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
					speed_tay_xoay = 200;
					target_xoay_tay = vi_tri_tay_1_trai_tren;
					for(i=0;i<150;i++)	{ 
							while((abs(bientroxoaytayValue - target_xoay_tay) > 5) )	{vTaskDelay(1); if(!wantExit())	break;}
					}
					gap_tay1_duoi_trai_phai(vi_tri_tay_1_trai_tren);
					da_lay_tay2 = 1;
					
					if(CHON_SAN == 0)		{							//SAN DO
							robotRunAngle(1750,10,-900,0.5);
							vTaskDelay(6000); }
					else {
							robotRunAngle(50,10,900,0.8);
							vTaskDelay(6000);
						}
					}
			
			else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
					speed_tay_xoay = 200;
					target_xoay_tay = vi_tri_tay_2_trai_tren;
					for(i=0;i<150;i++)	{ 
							while((abs(bientroxoaytayValue - target_xoay_tay) > 3) )	{vTaskDelay(1); if(!wantExit())	break;}
					}
					gap_tay2_duoi_trai_phai(vi_tri_tay_2_trai_tren);
					da_lay_tay3 = 1;
					
					if(CHON_SAN == 0)		{							//SAN DO
							robotRunAngle(1850,10,-900,0.8);
							vTaskDelay(6000); }
					else {
							robotRunAngle(-50,10,900,0.5);
							vTaskDelay(6000);
						}
			}

			// dung tay lan 4
			else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 0) {
					speed_tay_xoay = 200;
					target_xoay_tay = vi_tri_tay_3_trai_tren;
					for(i=0;i<150;i++)	{ 
							while((abs(bientroxoaytayValue - target_xoay_tay) > 3) )	{vTaskDelay(1); if(!wantExit())	break;}
					}
					gap_tay3_duoi_trai_phai(vi_tri_tay_3_trai_tren);
					da_lay_tay4 = 1;
					if(CHON_SAN == 0)		{							//SAN DO
							robotRunAngle(1850,10,-900,0.8);
							vTaskDelay(6000); }
					else {
							robotRunAngle( 0,10,900,0.8);
							vTaskDelay(6000);
						}
			}

			TinHieu_ChuanBi_GapTrai = 0;
}

//void Lay_ben_trai_bac_200_duoi_ko_thanh (void) { /// dang viet
//		KT_Ha_Tay_trai = 0;
//		if (da_lay_tay1 == 0 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
//					speed_tay_xoay = 200;
//					target_xoay_tay = vi_tri_tay_4_trai_duoi - 4;
//					for(i=0;i<150;i++)	{ 
//							while((abs(bientroxoaytayValue - target_xoay_tay) > 3) )	{vTaskDelay(1); if(!wantExit())	break;}
//					}
//					gap_tay4_duoi_trai_phai(vi_tri_tay_4_trai_duoi- 4);
//					da_lay_tay1 = 1;
//					
//					if(CHON_SAN == 0) {	 // san do
//						robotRunAngle(1800,15,-900,0.8);
//						vTaskDelay(5000);
//						}
//					else {  // san xanh
//						robotRunAngle(0,15,900,0.8);
//						vTaskDelay(5000);
//						}
//					}

//			// dung tay lan 2
//			else if (da_lay_tay1 == 1 && da_lay_tay4_duoi == 0) {
//					speed_tay_xoay = 200;
//					target_xoay_tay = vi_tri_tay_3_trai_duoi;
//					for(i=0;i<150;i++)	{ 
//							while((abs(bientroxoaytayValue - target_xoay_tay) > 3) )	{vTaskDelay(1); if(!wantExit())	break;}
//					}
//					gap_tay3_duoi_trai_phai(vi_tri_tay_3_trai_duoi);
//					da_lay_tay4_duoi = 1;
//					
//					if(CHON_SAN == 0) {	 /// san do
//						robotRunAngle(1800,15,-900,0.8);
//						vTaskDelay(5000);
//							}
//					else { // san xanh
//						robotRunAngle(0,15,900,0.8);
//						vTaskDelay(5000);
//						}
//			}

//			TinHieu_ChuanBi_GapTrai = 0;
//}


//////////*******************************************************

void di_vao_giua (void) {

					// da dung tay 1 xong
			if (da_lay_tay1 == 1 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
					robotRunAngle(1650,10,900,0.3);
					vTaskDelay (6000);
					robotStop(0);
		}
			
			// dung tay 2 xong
			else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
					robotRunAngle(1650,10,900,0.3);
					vTaskDelay (6000);
					robotStop(0);
			}
			
			// dung tay lan 3 xong
			else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 0) {
					robotRunAngle(150,10,900,0.3);
					vTaskDelay (6000);
					robotStop(0);
			}
			// dung tay 4 xong
			else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 1) {
				robotRunAngle(150,10,900,0.3);
				vTaskDelay (6000);
					robotStop(0);
			}		
}

/// ******* LAY 200 bac duoi ******************************
void Lay_phia_truoc_bac_200_duoi (void) {
	KT_Ha_Tay =0 ; /// tat ha tay 200 duoi
	if (da_lay_tay1 == 0 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
					speed_tay_xoay = 100;
					target_xoay_tay = vi_tri_tay_43;
					for(i=0;i<150;i++)	{ 
							while((abs(bientroxoaytayValue - target_xoay_tay) > 5) )	{vTaskDelay(1); if(!wantExit())	break;}
					}
					vTaskDelay(1000);
					gap_tay4_duoi();
					da_lay_tay1 = 1;

					}
			
					// dung tay lan 2
			else if (da_lay_tay1 == 1 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
					speed_tay_xoay = 100;
					target_xoay_tay = vi_tri_tay_12 + 3;
					for(i=0;i<150;i++)	{ 
							while((abs(bientroxoaytayValue - target_xoay_tay) > 5) )	{vTaskDelay(1); if(!wantExit())	break;}
					}
					vTaskDelay(1000);
					gap_tay1_duoi();
					da_lay_tay2 = 1;

			}
			
			// dung tay lan 3 
			else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
					speed_tay_xoay = 100;
					target_xoay_tay = vi_tri_tay_12 - 5;
					for(i=0;i<150;i++)	{ 
							while((abs(bientroxoaytayValue - target_xoay_tay) > 5) )	{vTaskDelay(1); if(!wantExit())	break;}
					}
					vTaskDelay(1000);
					gap_tay2_duoi();
					da_lay_tay3 = 1;

			}
			
			// dung tay lan 4
			else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 0) {
					speed_tay_xoay = 100;
					target_xoay_tay = vi_tri_tay_43 - 5;
					for(i=0;i<150;i++)	{ 
							while((abs(bientroxoaytayValue - target_xoay_tay) > 5) )	{vTaskDelay(1); if(!wantExit())	break;}
					}
					vTaskDelay(1000);
					gap_tay3_duoi();
					da_lay_tay4 = 1;

			}
			
			TinHieu_ChuanBi_GapThang = 0;
			
			if(CHON_SAN == 0){
					di_vao_giua_do();
			}
			else {
						di_vao_giua();
			}
	


}

/// *********** HAM tracking vi tri bang laser ****************
#define SPEED_FAST 25
#define SPEED_MIN 4
#define ERROR_MAX 60

int smooth_speed(int error)
{
    int d = abs(error);
		int speed;

    if(d > ERROR_MAX)
        d = ERROR_MAX;

    if(d < 6)
        return SPEED_MIN;

    speed = SPEED_MIN + (SPEED_FAST - SPEED_MIN) * d * d / (ERROR_MAX * ERROR_MAX);

    return speed;
}

int custom_smooth_speed(int error, int tocdo_min, int tocdo_max)
{
    int d = abs(error);
		float smooth;
		int speed; 

    // xa -> max luôn 
    if (d > 60)
        return tocdo_max;

    // rat gan 
    if (d < 15)
        return tocdo_min;

    // sigmoid 
    smooth = (float)d / (d + 35.0f);   

    speed = tocdo_min + (tocdo_max - tocdo_min) * smooth;

    return speed;
}

// ***************** CHINH LAI VI TRI LAZER SAN XANH **************
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
							robotRunAngle(0, speed, 900, 0.9);
					}
					else if ((lazeTraiValue - vitri)< 0) {
					
					robotRunAngle(1800, speed, 900, 0.9);
					
					}
					else {
								robotStop(0);

								}
					if(!wantExit())	break;
			}
		}   		
	}

	void chinh_lai_vi_tri_laser_trai_custom(int vitri, int gia_tri_lap)
{
	int speed ;
	int dieuchinh;
		for(i=0;i<gia_tri_lap;i++)
				{
		while(abs(lazeTraiValue - vitri) > 1)	{
			dieuchinh = lazeTraiValue - vitri;
			speed = custom_smooth_speed(dieuchinh, 4, 45);
			
					if  ((lazeTraiValue - vitri)> 0 ) {
							robotRunAngle(0, speed, 900, 0.9);
					}
					else if ((lazeTraiValue - vitri)< 0) {
					
					robotRunAngle(1800, speed, 900, 0.9);
					
					}
					else {
								robotStop(0);

								}
					if(!wantExit())	break;
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
							robotRunAngle(1800, speed, 900, 0.9);
					}
					else if ((lazePhaiValue - vitri)< 0) {
					
					robotRunAngle(0, speed, 900, 0.9);
					
					}
					else {
								robotStop(0);
					}
				if(!wantExit())	break;
			}
		}   		
	}

	
void chinh_lai_vi_tri_laser_sau(int vitri, int gia_tri_lap)
{
	int speed ;
	int dieuchinh;
		for(i=0;i<gia_tri_lap;i++)
				{
		while(abs(lazeSauValue - vitri) > 1)	{
			dieuchinh = lazeSauValue - vitri;
			speed = custom_smooth_speed(dieuchinh, 4, 8);
			
					if  ((lazeSauValue - vitri)> 0 ) {
							robotRunAngle(-900, speed, 900, 0.5);
					}
					else if ((lazeSauValue - vitri)< 0) {
					
					robotRunAngle(900, speed, 900, 0.5);
					
					}
					else {
								robotStop(0);
								}
				if(!wantExit())	break;
			}
		}   		
	}

void chinh_lai_vi_tri_laser_phai_custom(int vitri, int gia_tri_lap, int min_toc, int max_toc )
{
	int speed ;
	int dieuchinh;
		for(i=0;i<gia_tri_lap;i++)
				{
		while(abs(lazePhaiValue - vitri) > 1)	{
			dieuchinh = lazePhaiValue - vitri;
			speed = custom_smooth_speed(dieuchinh, min_toc, max_toc);
			
					if  ((lazePhaiValue - vitri)> 0 ) {
							robotRunAngle(1800, speed, 900, 0.7);
					}
					else if ((lazePhaiValue - vitri)< 0) {
					
					robotRunAngle(0, speed, 900, 0.7);
					
					}
					else {
								robotStop(1);

								}
					if(!wantExit())	break;
			}
		}   		
	}

	

	void chinh_lai_vi_tri_VK(int vitri, int gia_tri_lap)
{
	int speed ;
	int dieuchinh;
		for(i=0;i<gia_tri_lap;i++)
				{
		while(abs(lazePhaiValue - vitri) > 1)	{
			dieuchinh = lazePhaiValue - vitri;
			speed = smooth_speed(dieuchinh);
			
					if  ((lazePhaiValue - vitri)> 0 ) {
							robotRunAngle(0, speed, -900, 0.8);
					}
					else if ((lazePhaiValue - vitri)< 0) {
					
					robotRunAngle(1800, speed, -900, 0.8);
					
					}
					else {
								robotStop(0);

								}
					if(!wantExit())	break;
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
						if	(CB_kep_3_2 == 0 && CB_ROI_1 == 0 ) 			robotRun(-900,4);	
						else if 	(CB_kep_3_1 == 0 && CB_ROI_4 == 0 ) robotRun(900,4);
					
						vTaskDelay (1);
						if(!wantExit())	break;
					}
				}
				vTaskDelay (1200);
				robotStop(0);
	
	}

	void Ktra_vtri_kep4 (void) {
		for(i=0;i<500;i++)
				{
					while(CB_kep_4_2 == 0 || CB_kep_4_1 == 0 )	
					{	
						if	(CB_kep_4_2 == 0 && CB_ROI_1 == 0 ) 					robotRun(-900,4);	
						else if 	(CB_kep_4_1 == 0  && CB_ROI_4 == 0 ) robotRun(900,4);
						vTaskDelay (1);
						if(!wantExit())	break;
					}
				}	
				
				vTaskDelay (1200);
				robotStop(0);
	
	}

		void Ktra_vtri_kep1 (void) {
			
		vTaskDelay (3500);	
		for(i=0;i<500;i++)
				{
					while(CB_kep_1_2 == 0 || CB_kep_1_1 == 0)	
					{	
						if	(CB_kep_1_2 == 0 && CB_ROI_1 == 0  ) 			robotRun(-900,4);	
						else if 	(CB_kep_1_1 == 0 && CB_ROI_4 == 0  ) robotRun(900,4);
						
						vTaskDelay (5);
						if(!wantExit())	break;
					}
				}
				vTaskDelay (1200);
				robotStop(0);
	
	}
		
	void Ktra_vtri_kep2 (void) {
		for(i=0;i<500;i++)
				{
					while(CB_kep_2_2 == 0 || CB_kep_2_1 == 0)	
					{	
						if	(CB_kep_2_2 == 0 && CB_ROI_1 == 0 ) 			robotRun(-900,4);
						else if 	(CB_kep_2_1 == 0 && CB_ROI_4 == 0  ) robotRun(900,4);
							
						vTaskDelay (1);
						if(!wantExit())	break;
					}
				}	
				vTaskDelay (1200);
				robotStop(0);
	}

///////////////////////////ktr vi tri kep TRAI  //////////////////////////////
void Ktra_vtri_kep3_trai (void) {
		for(i=0;i<500;i++)
				{
					while(CB_kep_3_2 == 0 || CB_kep_3_1 == 0)	
					{	
						if				(CB_kep_3_2 == 0  ) 		robotRun(1800,4);	
						else if 	(CB_kep_3_1 == 0 ) robotRun(0,4);
									
						vTaskDelay (1);
						if(!wantExit())	break;
					}
				}	
				vTaskDelay (1200);
				robotStop(0);
	
	}

	void Ktra_vtri_kep4_trai (void) {
		for(i=0;i<500;i++)
				{
					while(CB_kep_4_2 == 0 || CB_kep_4_1 == 0 )	
					{	
						if						(CB_kep_4_2 == 0 ) robotRun(1800,4);	
						else if 	(CB_kep_4_1 == 0   ) robotRun(0,4);
						
						vTaskDelay (1);
						if(!wantExit())	break;
					}
				}
				vTaskDelay (500);
				robotStop(0);
	
	}


void Ktra_vtri_kep1_trai (void) {
		for(i=0;i<500;i++)
				{
					while(CB_kep_1_2 == 0 || CB_kep_1_1 == 0)	
					{	
						if	(CB_kep_1_2 == 0 ) 			robotRun(1800,4);	
						else if 	(CB_kep_1_1 == 0 ) robotRun(0,4);
									
						vTaskDelay (1);
						if(!wantExit())	break;
					}
				}	
				vTaskDelay (1200);
				robotStop(0);
	
	}
		
	void Ktra_vtri_kep2_trai (void) {
		for(i=0;i<500;i++)
				{
					while(CB_kep_2_2 == 0 || CB_kep_2_1 == 0)	
					{	
						if	(CB_kep_2_2 == 0 ) 			robotRun(1800,4);
						else if 	(CB_kep_2_1 == 0 ) robotRun(0,4);
									
						vTaskDelay (1);
						if(!wantExit())	break;
					}
				}	
				vTaskDelay (1200);
				robotStop(0);
	}	
	
///////////////////////////ktr vi tri kep PHAI //////////////////////////////
void Ktra_vtri_kep3_phai (void) {
		for(i=0;i<500;i++)
				{
					while(CB_kep_3_2 == 0 || CB_kep_3_1 == 0)	
					{	
						if				(CB_kep_3_2 == 0 ) 		robotRun(0,4);	
						else if 	(CB_kep_3_1 == 0 ) robotRun(1800,4);
									
						vTaskDelay (1);
						if(!wantExit())	break;
					}
				}	
				vTaskDelay (1200);
				robotStop(0);
	
	}

	void Ktra_vtri_kep4_phai (void) {
		for(i=0;i<500;i++)
				{
					while(CB_kep_4_2 == 0 || CB_kep_4_1 == 0 )	
					{	
						if						(CB_kep_4_2 == 0 ) robotRun(0,4);	
						else if 	(CB_kep_4_1 == 0   ) robotRun(1800,4);
					
						vTaskDelay (1);
						if(!wantExit())	break;
					}
				}	
				vTaskDelay (1200);
				robotStop(0);
	
	}


void Ktra_vtri_kep1_phai (void) {
		for(i=0;i<500;i++)
				{
					while(CB_kep_1_2 == 0 || CB_kep_1_1 == 0)	
					{	
						if	(CB_kep_1_2 == 0 ) 			robotRun(0,4);	
						else if  (CB_kep_1_1 == 0 ) robotRun(1800,4);
						
						vTaskDelay (1);
						if(!wantExit())	break;
					}
				}	
				vTaskDelay (1200);
				robotStop(0);
	
	}
		
	void Ktra_vtri_kep2_phai (void) {
		for(i=0;i<500;i++)
				{
					while(CB_kep_2_2 == 0 || CB_kep_2_1 == 0)	
					{	
						if	(CB_kep_2_2 == 0 ) 			robotRun(0,4);
						else if 	(CB_kep_2_1 == 0 ) robotRun(1800,4);
									
						vTaskDelay (1);
						if(!wantExit())	break;
					}
				}	
				vTaskDelay (1200);
				robotStop(0);
	}	

void nhac_dit(void) {
			/// nhac dit len
			Nang_thuong();
			target_chan_truoc = 395;
			target_chan_sau = 275;
}

void ha_sat_xuong(void) {
			/// nhac dit len
			Nang_thuong();
			target_chan_truoc = 255;
			target_chan_sau = 255;
}
