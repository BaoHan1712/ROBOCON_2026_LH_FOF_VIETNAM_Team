//// *********************  HAM GOI RA DE DUNG ********************************
void chinh_lai_vi_tri_VK_do(int vitri, int gia_tri_lap);
void chinh_lai_vi_tri_laser_trai_do(int vitri, int gia_tri_lap);
void chinh_lai_vi_tri_laser_phai_do(int vitri, int gia_tri_lap);
void chinh_lai_vi_tri_laser_trai_custom_do(int vitri, int gia_tri_lap);
void chinh_lai_vi_tri_laser_phai_custom_do(int vitri, int gia_tri_lap,int min_toc, int max_toc, int sai_so);

// ********** VI TRI CHAY SAN DO *************
void Leo_bac_400_co_thanh_do(void);
void Leo_bac_200_ko_thanh_do(void);
void Leo_bac_400_ko_thanh_do(void);
void Leo_bac_200_bam_thanh_phai_do(void);
void Xuong_bac_200_do_4(void);
void chuan_bi_gap_trai_200_tren_do_4 (void );
void Leo_bac_200_do_5(void);
void Lay_ben_phai_bac_200_duoi_do_6(void);
void Leo_bac_200_do_7 (void);
void Lay_ben_phai_bac_200_duoi_do_8(void);
void Xuong_bac_200_do_9(void);
void xuong_bac_200_do_10 (void);
void xuong_bac_200_11_do(void);
void xuong_bac_200_do_12 (void);

void Lay_ben_phai_bac_200_tren_do_2(void);
void Lay_ben_trai_bac_200_duoi_do_1(void);
void Lay_ben_trai_bac_200_tren_do_2(void);
void chuan_bi_gap_trai_200_tren_2_do (void );
void Lay_ben_phai_bac_200_duoi_do_3(void);
void Lay_ben_phai_bac_200_tren_do_9(void);
void Lay_ben_phai_bac_200_duoi_do_5 (void);
void Lay_ben_trai_bac_200_tren_do_5_6 (void);
void Lay_ben_trai_bac_200_duoi_do_8_11(void);
void Lay_ben_trai_bac_200_tren_do_7_10(void);
void gap_ngang_2_ben_san_do (void);
void tu_dong_dat_tang2_do(void);

//// VOID QUA TRAI,  QUA PHAI 
void qua_trai_len_bac_400_do(void);
void qua_trai_len_bac_200_cua_vao_do(void);
void qua_phai_len_bac_400_do(void);
void qua_phai_len_bac_200_cua_vao_do(void);

void kiem_tra_qua_tay_nao_do (void);

// ******** CHAY NGANG QUA TRAI *************
void MD_qua_trai_phai_xuong_bac_200 (int goc_quay_ngang,int goc_quay_thang, int di_Cheo, int time_lui, int giu_dau, int Angle, int Robot_Angle);
void MD_qua_trai_phai_len_bac_200 (int goc_quay_ngang,int goc_quay_thang, int di_Cheo, int time_lui, int giu_dau, int Angle, int Robot_Angle);
void qua_trai_xuong_bac_200_2_do (void) ;
void qua_trai_len_bac_200_3_do (void);
void qua_trai_len_bac_200_5_do (void) ;
void qua_trai_len_bac_200_6_do (void);
void qua_trai_len_bac_200_8_do (void);
void qua_trai_xuong_bac_200_9_do (void);
void qua_trai_len_bac_200_11_do (void);
void qua_trai_xuong_bac_200_12_do (void);

// ******* CHAY NGANG QUA PHAI ************
void qua_phai_len_bac_200_1_do (void);
void qua_phai_xuong_bac_200_2_do (void);
void qua_phai_xuong_bac_200_4_do(void);
void qua_phai_xuong_bac_200_5_do(void);
void qua_phai_xuong_bac_200_7_do(void);
void qua_phai_len_bac_200_8_do(void);
void qua_phai_xuong_bac_200_10_do(void);
void qua_phai_len_bac_200_11_do(void); 
///// *************************************************************************
//**********************************SAN DO*************************************
void Xuat_Phat_Lay_Vu_Khi_Do(int vu_khi, int goc_ve, int vitri) {					
				Nang_cuc_nhanh();
	
				target_chan_truoc = 350, target_chan_sau = 350;
				Tay_kep_mo;

				robotRunAngle(150 + vu_khi*2,40,3,0.3);

//	
				for(i=0;i<100;i++)
				{
					while(lazeTraiValue < vu_khi - 10 )	
					{
						vTaskDelay (1);
						if(!wantExit())	break;
					}
				}
				Nang_cuc_nhanh();
				target_chan_truoc = 610, target_chan_sau =613;
				for(i=0;i<50;i++)		
				{
				while(bientrochantruocValue < 470)	{
				Bam_thanh_laser_trai(32,0,0,vu_khi,1,-100,15);
				vTaskDelay(1); 
				if(!wantExit())	break;}
				}
	
				for(i=0;i<250;i++)
				{
					while(lazeTruocValue > 27)	
					{	
	
						Bam_thanh_laser_trai(26,0,0,vu_khi - 1,1,-80,15);
						vTaskDelay(1); 
						if(!wantExit())	break;
					}
				}
				
			
				for(i=0;i<100;i++)
				{
					while(HT_1 == 0 && HT_2 == 0)	
					{			
						if(lazeTruocValue < 25)	Tay_kep_xuong;
						Bam_thanh_laser_trai(8,0,0,vu_khi,1,-50,15);
						vTaskDelay(1); 
						if(!wantExit())	break;
					}
				}
				vTaskDelay (2000);
				robotStop(50);

				for(i=0;i<500;i++)
				{
					while(CB_tay_kep_vk_T == 1 || CB_tay_kep_vk_P == 1)	
					{	
						if	(CB_tay_kep_vk_T == 1) robotRun(870,11);
						else if 	(CB_tay_kep_vk_P == 1) robotRun(-870,11);
						else		robotStop(0);				
						vTaskDelay (1);
						if(!wantExit())	break;
					}
				}
				
				robotRun(0,6);
				Tay_kep_dong;
				
				vTaskDelay (2500);
				
				robotStop(30);
				
				KC_Vu_khi = lazeTraiValue;
		
				for(i=0;i<500;i++)
				{
					while(CB_kep == 1 || (CB_tay_kep_vk_T == 1 && CB_tay_kep_vk_P == 1))	
					{	
						if	(CB_tay_kep_vk_T == 1) robotRun(870,6);
						else if 	(CB_tay_kep_vk_P == 1) robotRun(-870,6);
						else		robotStop(0);				
						vTaskDelay (1);
						if(!wantExit())	break;
					}
				}
				
				robotStop(0);
			
				speed_chan_sau =70;
				speed_chan_truoc = 70;
				
				target_chan_truoc = 660, target_chan_sau = 650;
				
				for(i=0;i<500;i++)
				{
					while(abs(bientrochantruocValue - target_chan_truoc) > 5)
						{	
							vTaskDelay (3);						
							if(!wantExit())	break;
						}
				}

				
				Tay_kep_len; 
				
				robotRun(goc_ve + ((KC_Vu_khi - vu_khi)*5),30);
				robotRotate(900,2,0);
							
				Nang_cuc_nhanh();
				
				while(_robotIMUAngle < 450)	
				{
					vTaskDelay (5); 
					if(!wantExit())	break;
					if(_robotIMUAngle > 450)		target_chan_truoc = 265, target_chan_sau = 265;
				}

				robotRunAngle(-900,10,900,0.7);
				
				for(i=0;i<100;i++)
				{
					while(HT_3 == 0 && HT_4 == 0)	
					{           
						vTaskDelay (5); 
						if(!wantExit())	break;
					}
				}
				vTaskDelay(2000);
				robotStop(0);
				speed_chan_sau =45;
				speed_chan_truoc = 45;
				robotStop(0);
//				chinh_lai_vi_tri_VK_do(vitri, 1000);
				robotRunAngle(-900,8,900,0.5);
				vTaskDelay(2000);
				target_chan_truoc = 231, target_chan_sau = 231;	
				robotStop(0);
}

// HAM PHUN TAY RA TRUOC
void phun_tay_ra (void) {
		if (da_lay_tay1 == 0 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
				Tay2_len;
		}
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
				Tay1_len;
		}
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
				Tay2_len;
		}
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 0) {
				Tay1_len;
		}
}
//// ******************* VAO CUA RUNG SAN DO ************************

/// ********** XOAY DAU TOI CUA DO 3
void Xoay_dau_truoc_cua_do_3 (void)
{
	Nang_cuc_nhanh();

	target_chan_truoc = 255;
	target_chan_sau = 255;

	
	vTaskDelay(2000);
	
	robotRunAngle(1000,20,-900,2.2);
//				
				while(_robotIMUAngle > -650)	
				{
					vTaskDelay (1); 
					if(!wantExit())	break;
				}
				
	robotRotate(-900,0.9, 0);
	while(robotFixAngle()){
					vTaskDelay (1); 
					if(!wantExit())	break;
				}
				
	robotStop(0); 
	if (TinHieu_ChuanBi_GapThang == 1) {
			chinh_lai_vi_tri_laser_phai_custom_do(vi_tri_cua_rung_do_3_lazer_phai_tay_41 - 11 , 1000, 5, 65, 7);
	}
	else if (TinHieu_ChuanBi_GapThang == 0) {
			chinh_lai_vi_tri_laser_phai_custom_do(vi_tri_cua_rung_do_3_lazer_phai_tay_41 - 26 , 1000, 5, 65, 10);
	}
	
	
	if (block_pha == 3) {
			SEND_UART (4,1);
		}
	else {
		co_vat_can = 0 ;
	}
	robotStop(0); 	
				
}

void Xoay_dau_truoc_cua_do_2 (void)
{
	Nang_cuc_nhanh();

	target_chan_truoc = 255;
	target_chan_sau = 255;

	
	vTaskDelay(2000);
	
	robotRunAngle(1450,25,-900,2);
//				
				while(_robotIMUAngle > -650)	
				{
					vTaskDelay (1); 
					if(!wantExit())	break;
				}
				
	robotRotate(-900,0.9, 0);
	while(robotFixAngle()){
					vTaskDelay (1); 
					if(!wantExit())	break;
				}
	robotStop(0); 
	if (TinHieu_ChuanBi_GapThang == 1) {
			chinh_lai_vi_tri_laser_phai_custom_do(vi_tri_cua_rung_do_2_lazer_phai_tay_41 - 8, 1000, 5,  65, 7);
	}
	else if (TinHieu_ChuanBi_GapThang == 0) {
			chinh_lai_vi_tri_laser_phai_custom_do(vi_tri_cua_rung_do_2_lazer_phai_tay_41 - 18 , 1000, 5, 65, 10);
	}
	if (block_pha == 2) {
		SEND_UART (4,1);
			}
	else {
			co_vat_can = 0 ;
	}
	
	robotStop(0); 	
				
}


void Xoay_dau_truoc_cua_do_1(void) {
	Nang_cuc_nhanh();

	target_chan_truoc = 255;
	target_chan_sau = 255;


	robotRunAngle(1560,25,-900,2);
			
	while(_robotIMUAngle > -650)	
	{
		vTaskDelay (1); 
		if(!wantExit())	break;
	}
				
	robotRotate(-900,0.9, 0);
	while(robotFixAngle()){
					vTaskDelay (1); 
					if(!wantExit())	break;
				}
				
	robotStop(0);
				

	if (TinHieu_ChuanBi_GapThang == 1) {
			chinh_lai_vi_tri_laser_phai_custom_do(vi_tri_cua_rung_do_1_lazer_phai_tay_41 - 8, 1000, 5, 60, 7);
	}
	else if (TinHieu_ChuanBi_GapThang == 0) {
			chinh_lai_vi_tri_laser_phai_custom_do(vi_tri_cua_rung_do_1_lazer_phai_tay_41 - 15 , 1000,5, 60, 10);
	}
	
		if (block_pha == 1) {
	SEND_UART (4,1);
		}
	else {
		co_vat_can = 0 ;
	}
	
	robotStop(0); 	
				
}


void test_gui (void) {
		SEND_UART (4,1);
		vTaskDelay (2500);
		gui++;
}

void Vao_rung_mai_3_do(int vitri){
		Nang_cuc_nhanh();
		target_chan_truoc = Min_chan_truoc + 250;
		target_chan_sau = Min_chan_sau + 250;
	
		robotRunAngle(900,45,-900,0.6);
		for(i=0;i<250;i++)
					{
						while(lazeSauValue > 115)	
						{	
							vTaskDelay (1);
							if(!wantExit())	break;
						}
				}
		robotRunAngle(900,34,-900,0.5);
		for(i=0;i<250;i++)
					{
						while(lazeSauValue > 50)	
						{	
							vTaskDelay (1);
							if(!wantExit())	break;
						}
				}
			
		su_dung_chan(710);

	if (TinHieu_ChuanBi_GapThang == 0) {
				for(i=0;i<250;i++)
					{
						while(lazeSauValue > 10)	
						{	
							Bam_thanh_laser_phai(23,900,-900,vitri - 15,2,-150,10);
							vTaskDelay (1);
							if(!wantExit())	break;
						}
				}
					
					for(i=0;i<1550;i++)
							{
									while( CB_vtri_leo == 1 ||CB_Ha_Sau == 1 )	
								{	
									Bam_thanh_laser_phai(10,900,-900,vitri - 15,2,-150,10);
									vTaskDelay (1);
									if(!wantExit())	break;
									
								}
							}
				robotStop(30); 	
				chinh_lai_vi_tri_laser_phai_do(vitri - 15, 1000);
	}
	else if (TinHieu_ChuanBi_GapThang == 1) {
				for(i=0;i<250;i++)
					{
						while(lazeSauValue > 10)	
						{	
							Bam_thanh_laser_phai(23,900,-900,vitri ,2,-150,10);
							vTaskDelay (1);
							if(!wantExit())	break;
						}
				}
				
				// PHUN TAY RA
				phun_tay_ra();
				
				for(i=0;i<1550;i++)
							{
									while( CB_vtri_leo == 1 ||CB_Ha_Sau == 1 || CB_Cap_Thanh_Sau == 0)	
								{	
									Bam_thanh_laser_phai(10,900,-900,vitri ,2,-150,10);
									vTaskDelay (1);
									if(!wantExit())	break;
									
								}
							}
					robotStop(30); 	
					chinh_lai_vi_tri_laser_phai_do(vitri, 1000);
	}

	robotStop(0); 	
				
}
//********************************** vao rung mai 2 gap kfs ********************************************
void Vao_rung_mai_2_do(int vitri)
{
	Nang_cuc_nhanh();
	
	target_chan_truoc = Min_chan_truoc + 250;
	target_chan_sau = Min_chan_sau + 250;
	
	robotRunAngle(900,45,-900,0.5);
	for(i=0;i<250;i++)
				{
					while(lazeSauValue > 115)	
					{	
						vTaskDelay (1);
						if(!wantExit())	break;
					}
			}
		
	robotRunAngle(900,34,-900,0.5);
	for(i=0;i<250;i++)
				{
					while(lazeSauValue > 40)	
					{	
						vTaskDelay (1);
						if(!wantExit())	break;
					}
			}
				
	
	if (TinHieu_ChuanBi_GapThang == 0) {
			for(i=0;i<250;i++)
					{
						while(lazeSauValue > 10)	
						{	
							Bam_thanh_laser_phai(20,900,-900,vitri - 15,2,-100,10);
							vTaskDelay (1);
							if(!wantExit())	break;
						}
				}				
			for(i=0;i<1550;i++)
						{
							while( CB_Ha_Sau == 1 || CB_Cap_Thanh_Sau == 0)	
							{	
								Bam_thanh_laser_phai(10,900,-900,vitri - 15,2,-150,10);
								if(!wantExit())	break;
								vTaskDelay (1);
							}
						}
						robotStop(30); 	
						chinh_lai_vi_tri_laser_phai_do(vitri - 15, 1000);
	}
	else if (TinHieu_ChuanBi_GapThang == 1) {
					su_dung_chan_thuong(565);	
					for(i=0;i<250;i++)
					{
						while(lazeSauValue > 10 || (abs(bientrochansauValue - target_chan_sau) > 200))	
						{	
							Bam_thanh_laser_phai(20,900,-900,vitri ,2,-150,10);
							vTaskDelay (1);
							if(!wantExit())	break;
						}
					}			
					
					// PHUN TAY RA
				phun_tay_ra();
					
					for(i=0;i<1550;i++)
							{
								while(CB_Ha_Sau == 1 || CB_Cap_Thanh_Sau == 0)	
								{	
									Bam_thanh_laser_phai(10,900,-900,vitri,2,-150,10);
									if(!wantExit())	break;
									vTaskDelay (1);
								}
							}
							robotStop(30); 	
							chinh_lai_vi_tri_laser_phai_do(vitri, 1000);
	}
	
	robotStop(0); 			
						
}	

//********************************** vao rung mai 3 gap kfs ********************************************
void Vao_rung_mai_1_do(int vitri)
{
	// Do chan len 1 nua
		Nang_cuc_nhanh();
		target_chan_truoc = Min_chan_truoc + 250;
		target_chan_sau = Min_chan_sau + 250;
	
		robotRunAngle(900,45,-900,0.9);
		for(i=0;i<250;i++)
					{
						while(lazeSauValue > 115)	
						{	
							vTaskDelay (1);
							if(!wantExit())	break;
						}
				}
					
	if (TinHieu_ChuanBi_GapThang == 0) {
				for(i=0;i<250;i++)
					{
						while(lazeSauValue > 55)	
						{	
							Bam_thanh_laser_trai(34,900,-900,vitri + 25,2,150,10);
							vTaskDelay (1);
							if(!wantExit())	break;
						}
				}
				su_dung_chan(710);
				for(i=0;i<250;i++)
					{
						while(lazeSauValue > 10)	
						{	
							Bam_thanh_laser_trai(25,900,-900,vitri + 25,2,150,10);
							vTaskDelay (1);
							if(!wantExit())	break;
						}
				}
					
					for(i=0;i<1550;i++)
							{
									while( CB_Ha_Sau == 1 || CB_Cap_Thanh_Sau == 0)	
								{	
									Bam_thanh_laser_trai(10,900,-900,vitri + 25,2,150,10);
									vTaskDelay (1);
									if(!wantExit())	break;
									
								}
							}
				robotStop(30); 	
				chinh_lai_vi_tri_laser_trai_do(vitri + 25, 1000);
	}
	else if (TinHieu_ChuanBi_GapThang == 1) {
				for(i=0;i<250;i++)
					{
						while(lazeSauValue > 55)	
						{	
							Bam_thanh_laser_trai(34,900,-900,vitri ,2,150,30);
							vTaskDelay (1);
							if(!wantExit())	break;
						}
				}
				su_dung_chan(710);
				for(i=0;i<250;i++)
					{
						while(lazeSauValue > 10)	
						{	
							Bam_thanh_laser_trai(25,900,-900,vitri ,2,150,30);
							vTaskDelay (1);
							if(!wantExit())	break;
						}
				}
				// PHUN TAY RA
				phun_tay_ra();
				
					for(i=0;i<1550;i++)
							{
									while( CB_Ha_Sau == 1 || CB_Cap_Thanh_Sau == 0)	
								{	
									Bam_thanh_laser_trai(10,900,-900,vitri ,2,150,30);
									vTaskDelay (1);
									if(!wantExit())	break;
									
								}
							}
					robotStop(30); 	
					chinh_lai_vi_tri_laser_trai_do(vitri, 1000);
	}

	robotStop(0); 	
}

///////////////////////////////////////////////////////////////
void auto_vao_rung_do_cua1(void) {
		Xoay_dau_truoc_cua_do_1();
		vat_can();
	if  (co_vat_can == 0 ) {
			Vao_rung_mai_1_do(vi_tri_cua_rung_do_1_lazer_trai_tay_41);
			}
			co_vat_can = 1;
		
	}

	
void auto_vao_rung_do_cua2(void) {
		Xoay_dau_truoc_cua_do_2();
		vat_can();
	if  (co_vat_can == 0 ) {
		Vao_rung_mai_2_do(vi_tri_cua_rung_do_2_lazer_phai_tay_41);
		}
	co_vat_can = 1;
}

void auto_vao_rung_do_cua3(void) {
		Xoay_dau_truoc_cua_do_3();
		vat_can();
	if  (co_vat_can == 0 ) {
		Vao_rung_mai_3_do(vi_tri_cua_rung_do_3_lazer_phai_tay_41);
		
		co_vat_can = 1;
	}
}


//// ******* RA CUA RA SAN DO ********************
void vuot_rung_ve_homeTay_bac_400_do (void) {
	Xuong_bac_400(900, -900);
	robotRunAngle(900,10,-900,1);
	vTaskDelay(2000);
	robotStop(0);
	hoan_thanh_chay_rung = 1;

}

void vuot_rung_ve_homeTay_bac_200_do (void) {
	Xuong_bac_200(900, -900);
	robotStop(0);
	hoan_thanh_chay_rung = 1;
}

/// ham chay tat len san do
void chinh_lai_vi_tri_laser_trai_zone3_do(int vitri, int gia_tri_lap, int min_toc, int max_toc) {
	int speed ;
	int dieuchinh;
		for(i=0;i<gia_tri_lap;i++)
				{
		while(abs(lazeTraiValue - vitri) > 2)	{
			dieuchinh = lazeTraiValue - vitri;
			speed = custom_smooth_speed(dieuchinh, min_toc, max_toc);
			
					if  ((lazeTraiValue - vitri)> 0 ) {
							robotRunAngle(1800, speed, -900, 0.5);
					}
					else if ((lazeTraiValue - vitri)< 0) {
					
					robotRunAngle(0, speed, -900, 0.5);
					
					}
					else {
								robotStop(0);

								}
					if(!wantExit())	break;
			}
		}   		
	}

void DatKFS_do(int vitri)
{
	kiem_tra_so_qua_tren_tay();
	kiem_tra_qua_tay_nao_xuong_rung(); // ham kiem tra co qua tay nao de dat
	
	Nang_nhanh();
	target_chan_truoc = 335;
	target_chan_sau = 335;
	
	for(i=0;i<150;i++)		
	{
		while(abs(bientrochansauValue - target_chan_sau) > 100)	{vTaskDelay(1); if(!wantExit())	break;}
	}
	
	chinh_lai_vi_tri_laser_trai_zone3_do(230, 1000, 4, 52);
	
	robotStop(20);
	
	vTaskDelay(700); 

		robotRunAngle(900,55,-900,0.9);
		for(i=0;i<550;i++)	
	{	
			while(lazePhaiValue > 270)	
			{	
				vTaskDelay(1); 
				if(!wantExit())	break;
			}
	}	
	vTaskDelay(3000); 
	
		for(i=0;i<550;i++)	
	{	
			while(lazePhaiValue < 270)	
			{	

				vTaskDelay(1); 
				if(!wantExit())	break;
			}
	}		
	
	robotStop(25);
	
		vTaskDelay(200); 
		
	robotRunAngle(900,18,-900,0.9);
	for(i=0;i<550;i++)	
	{	
			while(lazeSauValue > 42)	
			{	
				vTaskDelay(1); 
				if(!wantExit())	break;
			}
	}		
	
		
		for(i=0;i<550;i++)	
		{	
				while(lazePhaiValue > 440)	
				{	
					Bam_laser_sau(50,0,-900, vitri, 7, 120, 15);
					vTaskDelay(1); 
					if(!wantExit())	break;
				}
		}
		
		robotRunAngle(-150,40,900,1.5);
				
		while(_robotIMUAngle < 810)	
		{
			vTaskDelay (1); 
			if(!wantExit())	break;
		}
					
//		
//		//	**************** che do cay diem  ******************
	if (mode_cay_diem == 1 ) {
		for(i=0;i<550;i++)	
		{	
				while(lazeTraiValue > 280)	
				{	
					Bam_laser_truoc(45,0,900, vitri +35 , 3, 300, 10);
					vTaskDelay(1); 
					if(!wantExit())	break;
				}
		}
		for(i=0;i<550;i++)	
		{	
				while(lazeTraiValue > 220)	
				{	
					Bam_laser_truoc(20,0,900, vitri +35 , 3, 300, 10);
					vTaskDelay(1); 
					if(!wantExit())	break;
				}
		}
		for(i=0;i<550;i++)	
		{	
				while(lazeTraiValue > 195)	
				{	
					Bam_laser_truoc(10,0,900, vitri + 35 , 2, 150, 10);
					vTaskDelay(1); 
					if(!wantExit())	break;
				}
		}
			robotStop(10);
		// do chan len dat qua
			su_dung_chan(710);
			for(i=0;i<150;i++)		
			{
				while(abs(bientrochansauValue - target_chan_sau) > 30)	{vTaskDelay(1); if(!wantExit())	break;}
			}
	}
//	
//		
////	// ************** che do thang nhanh ***********
	if (mode_cay_diem == 2 ) {
			for(i=0;i<550;i++)	
		{	
				while(lazeTraiValue > 280)	
				{	
					Bam_laser_truoc(45,0,900, vitri + 35, 3, 300, 10);
					vTaskDelay(1); 
					if(!wantExit())	break;
				}
		}
		for(i=0;i<550;i++)	
		{	
				while(lazeTraiValue > 220)	
				{	
					Bam_laser_truoc(20,0,900, vitri + 35, 3, 300, 10);
					vTaskDelay(1); 
					if(!wantExit())	break;
				}
		}
		for(i=0;i<550;i++)	
		{	
				while(lazeTraiValue > 188)	
				{	
					Bam_laser_truoc(10,0,900, vitri + 35, 2, 150, 10);
					su_dung_chan_thuong(508);
					vTaskDelay(1); 
					if(!wantExit())	break;
				}
		}
		
	}

	robotStop(0);
}


void dat_qua_tay_1_2_do(void) {
	if (CB_kep_1_2 == 0) {
		speed_tay_gat1 = 250;
		target_tay_gat1 = vitri_tay1home + 115;
	
		for(i=0;i<50;i++)	{ 
		while(abs(bientrodaytay1Value - target_tay_gat1) > (10) || abs(bientrodaytay2Value - target_tay_gat2) > 10 )	
		{vTaskDelay(1); if(!wantExit())	break;}
		}
		vTaskDelay(3000);
		Kep_phai_1_ra;
	}
	
	if (CB_kep_2_2 == 0) {
			speed_tay_gat2 = 250;
			target_tay_gat2 = vitri_tay2home + 115;
				
			for(i=0;i<50;i++)	{ 
				while(abs(bientrodaytay1Value - target_tay_gat1) > (10) || abs(bientrodaytay2Value - target_tay_gat2) > 10 )	
				{vTaskDelay(1); if(!wantExit())	break;}
				}
				vTaskDelay(3000);
				Kep_phai_2_ra;
			}
	
		vTaskDelay(3000);
		
	// dat xong ve home tay
		speed_tay_gat1 = 250;
		target_tay_gat1 = vitri_tay1home ;
		speed_tay_gat2 = 250;
		target_tay_gat2 = vitri_tay2home ;
		
		for(i=0;i<50;i++)	{ 
				while(abs(bientrodaytay1Value - target_tay_gat1) > (10) || abs(bientrodaytay2Value - target_tay_gat2) > 10 )	
				{vTaskDelay(1); if(!wantExit())	break;}
		}
}

void dat_qua_tay_4_3_do(void) {
	if (CB_kep_3_2 == 0) {
		speed_tay_gat1 = 250;
		target_tay_gat1 = vitri_tay1home - 110;
	
		for(i=0;i<50;i++)	{ 
		while(abs(bientrodaytay1Value - target_tay_gat1) > (10) || abs(bientrodaytay2Value - target_tay_gat2) > 10 )	
		{vTaskDelay(1); if(!wantExit())	break;}
		}
		vTaskDelay(3000);
		Kep_phai_3_ra;
	}
	
	if (CB_kep_4_2 == 0) {
		speed_tay_gat2 = 250;
		target_tay_gat2 = vitri_tay2home - 110;
			
		for(i=0;i<50;i++)	{ 
			while(abs(bientrodaytay1Value - target_tay_gat1) > (10) || abs(bientrodaytay2Value - target_tay_gat2) > 10 )	
			{vTaskDelay(1); if(!wantExit())	break;}
			}
			vTaskDelay(3000);
			Kep_phai_4_ra;
		}
			
			vTaskDelay(3000);
		
	// dat xong ve home tay
		speed_tay_gat1 = 250;
		target_tay_gat1 = vitri_tay1home ;
		speed_tay_gat2 = 250;
		target_tay_gat2 = vitri_tay2home ;
		
		for(i=0;i<50;i++)	{ 
				while(abs(bientrodaytay1Value - target_tay_gat1) > (10) || abs(bientrodaytay2Value - target_tay_gat2) > 10 )	
				{vTaskDelay(1); if(!wantExit())	break;}
		}
}



/* ================= INIT CUA STATE 2 VUOT RUNG SAN DO ================= */

void Init_Action_Table_san_do(void)
{
    int m, a, i;

    /* default = DoNothing */
    for (m = 0; m < MAX_MOVE; m++)
        for (a = 0; a < MAX_ACTION; a++)
            for (i = 0; i < MAX_ID; i++)
                action_table[m][a][i] = DoNothing;


    /* =========================================
       move 10 , action 10 chay toi cua vao
       ========================================= */
    action_table[10][10][1] = auto_vao_rung_do_cua1;
    action_table[10][10][2] = auto_vao_rung_do_cua2;
    action_table[10][10][3] = auto_vao_rung_do_cua3;
	
	    /* =========================================
//       move 2 , action 10 sang trai o ria rung
//       ========================================= */
    action_table[2][10][3] = qua_trai_len_bac_400_do;
    action_table[2][10][2] = qua_trai_len_bac_200_cua_vao_do;

//	    /* =========================================
//		
//       move 3 , action 10 sang phai o ria rung
//       ========================================= */
    action_table[3][10][2] = qua_phai_len_bac_200_cua_vao_do;
    action_table[3][10][1] = qua_phai_len_bac_400_do;   

//	    /* =========================================
//       move 20 , action 20 chay ra cua ra
//       ========================================= */
    action_table[20][20][10] = vuot_rung_ve_homeTay_bac_200_do;
    action_table[20][20][11] = vuot_rung_ve_homeTay_bac_400_do;
    action_table[20][20][12] = vuot_rung_ve_homeTay_bac_200_do;


    /* =========================================
       move 0 , action 1, dung lai de lay o phia truoc
//       ========================================= */
    action_table[0][1][1] = Lay_phia_truoc_bac_400_tren;
    action_table[0][1][2] = Lay_phia_truoc_bac_200_tren;
    action_table[0][1][3] = Lay_phia_truoc_bac_400_tren;
		action_table[0][1][4] = Lay_phia_truoc_bac_200_duoi;
		action_table[0][1][5] = Lay_phia_truoc_bac_200_tren;	
		action_table[0][1][6] = Lay_phia_truoc_bac_200_tren;	
		action_table[0][1][7] = Lay_phia_truoc_bac_200_tren;	
		action_table[0][1][8] = Lay_phia_truoc_bac_200_tren;	
		action_table[0][1][9] = Lay_phia_truoc_bac_200_duoi;
		action_table[0][1][10]= Lay_phia_truoc_bac_200_duoi;
		action_table[0][1][11]= Lay_phia_truoc_bac_200_duoi;
		action_table[0][1][12]= Lay_phia_truoc_bac_200_duoi;

//    /* =========================================
//       move 0 , action 2, dung lai de lay ben TRAI
//       ========================================= */
		action_table[0][2][2] = Lay_ben_trai_bac_200_duoi_do_1; 
		action_table[0][2][3] = Lay_ben_trai_bac_200_tren_do_2; 
		action_table[0][2][5] = Lay_ben_trai_bac_200_tren_do_5_6; 
		action_table[0][2][6] = Lay_ben_trai_bac_200_tren_do_5_6; 	
		action_table[0][2][8] =	Lay_ben_trai_bac_200_tren_do_7_10;	
		action_table[0][2][11]= Lay_ben_trai_bac_200_tren_do_7_10;	
	
		action_table[0][2][9]  = Lay_ben_trai_bac_200_duoi_do_8_11;		
		action_table[0][2][12] = Lay_ben_trai_bac_200_duoi_do_8_11;		

//    /* =========================================
//       move 0 , action 3, dung lai de lay ben PHAI
//       ========================================= */
		action_table[0][3][1] = Lay_ben_phai_bac_200_tren_do_2;
		action_table[0][3][2] = Lay_ben_phai_bac_200_duoi_do_3;
		action_table[0][3][4] = Lay_ben_phai_bac_200_duoi_do_5; 
		action_table[0][3][5] = Lay_ben_phai_bac_200_duoi_do_6;  
		action_table[0][3][7] = Lay_ben_phai_bac_200_duoi_do_8;  
		action_table[0][3][8] = Lay_ben_phai_bac_200_tren_do_9;   
		
		action_table[0][3][10] = Lay_ben_phai_bac_200_duoi_do_8;  
		action_table[0][3][11]= Lay_ben_phai_bac_200_tren_xanh_11; 
				
    /* =========================================
       move 1 , action 4 chay thang
       ========================================= */
    action_table[1][4][1] = Leo_bac_400_ko_thanh_do;  
    action_table[1][4][2] = Leo_bac_200_bam_thanh_phai_do;  
		action_table[1][4][3] = Leo_bac_400_co_thanh_do; 
		action_table[1][4][4] = Xuong_bac_200_do_4;	  
    action_table[1][4][5] = Leo_bac_200_do_5;		
    action_table[1][4][6] = Leo_bac_200_ko_thanh_do; 
    action_table[1][4][7] = Leo_bac_200_do_7;   
    action_table[1][4][8] = Leo_bac_200_ko_thanh_do;  
    action_table[1][4][9]  = Xuong_bac_200_do_9; 	
    action_table[1][4][10] = xuong_bac_200_do_10;  
    action_table[1][4][11] = xuong_bac_200_11_do; 
		action_table[1][4][12] = xuong_bac_200_do_12; 
		
		
			/* =========================================
//   move 2 , action 4,chay ben trai
//   ========================================= */
		action_table[2][4][2] = qua_trai_xuong_bac_200_2_do;
		action_table[2][4][3] = qua_trai_len_bac_200_3_do;
		
		action_table[2][4][5] = qua_trai_len_bac_200_5_do;
		action_table[2][4][6] = qua_trai_len_bac_200_6_do;
		
		action_table[2][4][8] = qua_trai_len_bac_200_8_do;  
		action_table[2][4][9] = qua_trai_xuong_bac_200_9_do; 
		
		action_table[2][4][11] = qua_trai_len_bac_200_11_do; 
		action_table[2][4][12] = qua_trai_xuong_bac_200_12_do;

		/* =========================================
//   move 3 , action 4,chay ben phai
//   ========================================= */
		action_table[3][4][1] = qua_phai_len_bac_200_1_do;
    action_table[3][4][2] = qua_phai_xuong_bac_200_2_do;
		
		action_table[3][4][4] = qua_phai_xuong_bac_200_4_do; 
    action_table[3][4][5] = qua_phai_xuong_bac_200_5_do; 
		
		action_table[3][4][7] = qua_phai_xuong_bac_200_7_do;
    action_table[3][4][8] = qua_phai_len_bac_200_8_do; 
		
		action_table[3][4][10] = qua_phai_xuong_bac_200_10_do; 
    action_table[3][4][11] = qua_phai_len_bac_200_11_do; 
		
				/* =========================================
//   move 4 , action 5,check camera nhin khoi 1
//   ========================================= */
		action_table[4][5][4]  = dung_cho_khoi_r1; 
    action_table[4][5][5]  = dung_cho_khoi_r1;  
    action_table[4][5][6]  = dung_cho_khoi_r1; 
    action_table[4][5][7]  = dung_cho_khoi_r1;  
    action_table[4][5][8]  = dung_cho_khoi_r1;  
    action_table[4][5][9]  = dung_cho_khoi_r1;  
    action_table[4][5][10] = dung_cho_khoi_r1;  
    action_table[4][5][11] = dung_cho_khoi_r1;  
		action_table[4][5][12] = dung_cho_khoi_r1; 
}

/////* ================= RUN TU DONG ================= */

void Run_All_Blocks_From_Queue_san_do(void)
{
    Packet_t pkt;
    Packet_t next_pkt;

    if (count_data_uart4 == 0)
        return;

    while (count_data_uart4 > 0)
    {
        Check_Next1_Block_For_Prepare();
        if (!Queue_Pop(&pkt)) break;

        if (Queue_Peek(&next_pkt)) 
        {
            if (pkt.move == 2 && pkt.action == 10 && pkt.id_block == 2) 
            {
                if (next_pkt.move == 2 && next_pkt.action == 10 && next_pkt.id_block == 3) 
                {
                    chay_ngang_qua_o3_do = 1; // Bat flag cho ben trai
                }
            }
            
            else if (pkt.move == 3 && pkt.action == 10 && pkt.id_block == 2)
            {
                if (next_pkt.move == 3 && next_pkt.action == 10 && next_pkt.id_block == 1)
                {
                    chay_ngang_qua_o1_do = 1; // Bat flag cho ben phai
                }
            }
        }

        if (pkt.move < MAX_MOVE && pkt.action < MAX_ACTION && pkt.id_block < MAX_ID)
        {
            action_table[pkt.move][pkt.action][pkt.id_block]();
        }

        vTaskDelay(1000); 
    }

    has_active_block = 0;
}


/////* ================= RUN BAN TU DONG ================= */
//void Run_All_Blocks_From_Queue_san_do(void)
//{
//       Packet_t pkt;

//    if (count_data_uart4 == 0)
//        return;

//    /* nhìn truoc 1 block */
//    Check_Next1_Block_For_Prepare();

//    if (Queue_Pop(&pkt))
//    {
//        if (pkt.move < MAX_MOVE &&
//            pkt.action < MAX_ACTION &&
//            pkt.id_block < MAX_ID)
//        {	
//            action_table[pkt.move][pkt.action][pkt.id_block]();
//        }
//    }

//    has_active_block = 0;
//}

// // HAM LUI LAI DE DAT VAO O BAC 3
void chuan_bi_dat_tang_3_do (void) {
		robotRunAngle(1800, 6,-900,1);
		vTaskDelay (1500);
		speed_tay_xoay = 100;
		target_xoay_tay = 603;
		for(i=0;i<150;i++)	{ 
					while((abs(bientroxoaytayValue - target_xoay_tay) > 5) )	{vTaskDelay(1); if(!wantExit())	break;}
			}
		
		for(i=0;i<550;i++)	
	{	
			while(lazeTruocValue < 103)	
			{	
				Bam_thanh_laser_phai(6,900,-900, 168, 1, -200, 20);
				vTaskDelay(1); 
				if(!wantExit())	break;
			}
	}
	robotStop(0);
	chinh_lai_vi_tri_laser_phai_do(168 , 1000);
	
		robotStop(0);
}

// // HAM LUI LAI DE DAT VAO O BAC 3
void dat_full_tang_2_do (void) {
			Tay2_len;
			Tay1_len;
			for(i=0;i<50;i++)	{ 
						while(CB_xilanh_tay_2 == 1|| CB_xilanh_tay_2 == 1 )	
						{vTaskDelay(1); if(!wantExit())	break;}
							}
						
			dat_qua_tay_1_2_do();
			
		robotStop(0);
}
void mo_vk_san_do(void) {
	
		for(i=0;i<1000;i++)	
	{
		while(quangTroValue > 220)	{	
		vTaskDelay (1);
		if(!wantExit())	break;
					}
	}
	
	Tay_kep_mo;
	
	vTaskDelay (4000);
	
	for(i=0;i<1000;i++)	
	{
		while(quangTroValue < 270)	{	
		vTaskDelay (1);
		if(!wantExit())	break;
		}
	}
	vTaskDelay (6000);
	da_lay_vk = 1;
}

void kiem_tra_qua_tay_nao_do (void) {
	if (CB_kep_4_2 == 0 && CB_kep_4_1 == 0 && CB_kep_1_2 == 1 && CB_kep_1_1 == 1 && CB_kep_2_2 == 1 && CB_kep_2_1 == 1 && CB_kep_3_2 == 1 && CB_kep_3_1 == 1 )	{
			speed_tay_xoay = 100;
			target_xoay_tay = 410;
			tin_hieu_dat_hop_3_4 = 1;
	}
	else if (CB_kep_4_2 == 0 && CB_kep_4_1 == 0 && CB_kep_1_2 == 0 && CB_kep_1_1 == 0 && CB_kep_2_2 == 1 && CB_kep_2_1 == 1 && CB_kep_3_2 == 1 && CB_kep_3_1 == 1 )	{
			speed_tay_xoay = 100;
			target_xoay_tay = 410;
			tin_hieu_dat_hop_3_4= 1;
	}
	
	/// 2 qua o tay 1 2
	else if (CB_kep_4_2 == 0 && CB_kep_4_1 == 0 && CB_kep_1_2 == 0 && CB_kep_1_1 == 0 && CB_kep_2_2 == 0 && CB_kep_2_1 == 0 && CB_kep_3_2 == 1 && CB_kep_3_1 == 1 )	{
			speed_tay_xoay = 100;
			target_xoay_tay = 595;
			tin_hieu_dat_hop_1_2 = 1;
	}
	else if (CB_kep_4_2 == 0 && CB_kep_4_1 == 0 && CB_kep_1_2 == 0 && CB_kep_1_1 == 0 && CB_kep_2_2 == 0 && CB_kep_2_1 == 0 && CB_kep_3_2 == 0 && CB_kep_3_1 == 0 )	{
			speed_tay_xoay = 100;
			target_xoay_tay = 410;
			tin_hieu_dat_hop_3_4 = 1;
	}
	else {
			speed_tay_xoay = 100;
			target_xoay_tay = 595;
			tin_hieu_dat_hop_1_2 = 1;
	}

}

 // 114 o 1 // o 2 56
void retry_zone_3_o_1_do(int vitri) {
		int nhom_A;
		int nhom_B ;
		kiem_tra_so_qua_tren_tay();
		kiem_tra_qua_tay_nao_xuong_rung();
    chon_tay_tiep_theo();
    
		nhom_A = (tay_se_dung_tiep_theo == 1 || tay_se_dung_tiep_theo == 4);
    nhom_B = (tay_se_dung_tiep_theo == 2 || tay_se_dung_tiep_theo == 3);
		
		robotRunAngle(0,45,0,1.5);
		for(i=0;i<550;i++)	
			{	
					while(lazeSauValue < 240)	
					{	
						vTaskDelay(1); 
						if(!wantExit())	break;
					}
			}
					/// di cheo qua
		robotRunAngle(-800,30,0,1.5);
		vTaskDelay(16000); 
		
		/// chay toi 1 doan roi xoay
		robotRunAngle(-100,30,900,1.5);
	
		while(_robotIMUAngle < 860)	
		{
			vTaskDelay (1); 
			if(!wantExit())	break;
		}
		
		for(i=0;i<550;i++)	
			{	
					while(lazeTraiValue > 250)	
					{	
						Bam_laser_truoc(20,0,900, vitri , 3, 150, 10);
						vTaskDelay(5); 
						if(!wantExit())	break;
					}
			}
				
			if (nhom_A) {
			for(i=0;i<550;i++)	
			{	
					while(lazeTraiValue > 180)	
					{	
						Bam_laser_truoc(10,0,900, vitri , 1, 120, 10);
						su_dung_chan_cham(500);
						vTaskDelay(1); 
						if(!wantExit())	break;
					}
				}	
			}
			else if (nhom_B) {
			for(i=0;i<550;i++)	
			{	
					while(lazeTraiValue > 195)	
					{	
						Bam_laser_truoc(10,0,900, vitri , 1, 150, 10);
						su_dung_chan_cham(500);
						vTaskDelay(1); 
						if(!wantExit())	break;
					}
				}	
			}
		
		robotStop(0);
}

void retry_zone_3_o_2_do(int vitri) {
		int nhom_A;
		int nhom_B ;
		kiem_tra_so_qua_tren_tay();
		kiem_tra_qua_tay_nao_xuong_rung();
    chon_tay_tiep_theo();
    
		nhom_A = (tay_se_dung_tiep_theo == 1 || tay_se_dung_tiep_theo == 4);
    nhom_B = (tay_se_dung_tiep_theo == 2 || tay_se_dung_tiep_theo == 3);
		
		robotRunAngle(10,45,0,1.5);
		for(i=0;i<550;i++)	
			{	
					while(lazeSauValue < 210)	
					{	
						vTaskDelay(1); 
						
						if(!wantExit())	break;
					}
			}
				/// di cheo qua
		robotRunAngle(-800,30,0,1.5);
		vTaskDelay(11000); 
		
		/// chay toi 1 doan roi xoay
		robotRunAngle(100,25,900,1.5);
		while(_robotIMUAngle < 860)	
		{
			vTaskDelay (1); 
			if(!wantExit())	break;
		}	
		
		for(i=0;i<550;i++)	
			{	
					while(lazeTraiValue > 250)	
					{	
						Bam_laser_truoc(20,0,900, vitri , 3, 200, 10);
						vTaskDelay(5); 
						if(!wantExit())	break;
					}
			}
				
			for(i=0;i<550;i++)	
			{	
					while(lazeTraiValue > 180)	
					{	
						Bam_laser_truoc(10,0,900, vitri , 1, 150, 10);
						su_dung_chan_cham(500);
						vTaskDelay(1); 
						if(!wantExit())	break;
					}
				}	
			robotStop(0);	
}

void retry_zone_3_o_3_do(int vitri) {
		int nhom_A;
		int nhom_B ;
		kiem_tra_so_qua_tren_tay();
		kiem_tra_qua_tay_nao_xuong_rung();
    chon_tay_tiep_theo();
    
		nhom_A = (tay_se_dung_tiep_theo == 1 || tay_se_dung_tiep_theo == 4);
    nhom_B = (tay_se_dung_tiep_theo == 2 || tay_se_dung_tiep_theo == 3);
		
		robotRunAngle(10,45,0,1.5);
		for(i=0;i<550;i++)	
			{	
					while(lazeSauValue < 210)	
					{	
						vTaskDelay(1); 
						
						if(!wantExit())	break;
					}
			}
				/// di cheo qua
		robotRunAngle(-800,30,0,1.5);
		vTaskDelay(6000); 
		
		/// chay toi 1 doan roi xoay
		robotRunAngle(100,25,900,1.5);
		while(_robotIMUAngle < 860)	
		{
			vTaskDelay (1); 
			if(!wantExit())	break;
		}	
		
		for(i=0;i<550;i++)	
			{	
					while(lazeTraiValue > 250)	
					{	
						Bam_laser_truoc(20,0,900, vitri , 3, 200, 10);
						vTaskDelay(5); 
						if(!wantExit())	break;
					}
			}
				
			for(i=0;i<550;i++)	
			{	
					while(lazeTraiValue > 180)	
					{	
						Bam_laser_truoc(10,0,900, vitri , 1, 150, 10);
						su_dung_chan_cham(500);
						vTaskDelay(1); 
						if(!wantExit())	break;
					}
				}	
			robotStop(0);	
}



void dat_hop_vao_o_do (void) {
		if (tin_hieu_dat_hop_3_4 == 1 ) {
				dat_qua_tay_4_3_do();
		}
		else if (tin_hieu_dat_hop_1_2 == 1 ) {
				dat_qua_tay_1_2_do();
		}
}


void chon_o_retry3_do(void) {
		int nhom_A;
		int nhom_B ;
		int id ;
    kiem_tra_so_qua_tren_tay();
    kiem_tra_qua_tay_nao_xuong_rung();
    chon_tay_tiep_theo();
		
		Nang_cuc_nhanh();
		target_chan_truoc = 335;
		target_chan_sau = 335;

    nhom_A = (tay_se_dung_tiep_theo == 1 || tay_se_dung_tiep_theo == 4);
    nhom_B = (tay_se_dung_tiep_theo == 2 || tay_se_dung_tiep_theo == 3);
    id = (id_dat_hop > 3) ? (id_dat_hop - 3) : id_dat_hop;
	
    if      (id == 1 && nhom_A) { retry_zone_3_o_1_do(vi_tri_dat_hop_1_tay41_do); }
    else if (id == 1 && nhom_B) { retry_zone_3_o_1_do(vi_tri_dat_hop_1_tay23_do);   }
    else if (id == 2 && nhom_A) { retry_zone_3_o_2_do(vi_tri_dat_hop_2_tay41_do); }
    else if (id == 2 && nhom_B) { retry_zone_3_o_2_do(vi_tri_dat_hop_2_tay23_do); }
    else if (id == 3 && nhom_A) { retry_zone_3_o_3_do(vi_tri_dat_hop_3_tay41_do); }
    else if (id == 3 && nhom_B) { retry_zone_3_o_3_do(vi_tri_dat_hop_3_tay23_do);  }
    else { return; }

    if  (id_dat_hop <= 3) { 
				tu_dong_dat_tang2_do();
				robotRunAngle(1800,12,900, 0.5);
				vTaskDelay(5500);
				robotStop(0);
				chinh_lai_vi_tri_laser_truoc_do(vi_tri_dat_hop_3_tay41_do, 1000, 6, 30);
				su_dung_chan_thuong(710);
				robotStop(0);
				quyet_dinh_dat_hop_tang3();
				}
    else if (id_dat_hop >= 4) { 
				su_dung_chan_thuong(710);
				quyet_dinh_dat_hop_tang3();
			}
}




// ham ha chan dat tang 2
void ha_chan_dat_tang2_do (void) {

			for(i=0;i<500;i++)	
			{
		while(Quang_tro2 > 120)	{	
				vTaskDelay (1);
		if(!wantExit())	break;
					}
			}
			su_dung_chan_thuong(710);
			vTaskDelay (4000);

		}

void xac_dinh_vi_tri_robot_do(void)
{
		int val = lazeTruocValue;
    kiem_tra_so_qua_tren_tay();
    // ===== TAY 1 - 4 =====
    if (tay_1_co_qua || tay_4_co_qua)
    {
        int m12 = (vi_tri_dat_hop_1_tay41_do + vi_tri_dat_hop_2_tay41_do) / 2;
        int m23 = (vi_tri_dat_hop_2_tay41_do + vi_tri_dat_hop_3_tay41_do) / 2;

        if (val >= m12)
            robot_position = 1;
        else if (val >= m23)
            robot_position = 2;
        else
            robot_position = 3;
    }

    // ===== TAY 2 - 3 =====
    else if (tay_2_co_qua || tay_3_co_qua)
    {
        int m12 = (vi_tri_dat_hop_1_tay23_do + vi_tri_dat_hop_2_tay23_do) / 2;
        int m23 = (vi_tri_dat_hop_2_tay23_do + vi_tri_dat_hop_3_tay23_do) / 2;

        if (val >= m12)
            robot_position = 1;
        else if (val >= m23)
            robot_position = 2;
        else
            robot_position = 3;
    }
}

void tu_dong_dat_tang2_do(void) {
		robotRotate(890,0.2, 0);
		while(robotFixAngle()){
					vTaskDelay (1); 
					if(!wantExit())	break;
				}
		kiem_tra_so_qua_tren_tay();
		kiem_tra_qua_tay_nao();
		xac_dinh_vi_tri_robot_do();

		if (tay_1_co_qua || tay_4_co_qua) {
        if (robot_position == 3) {
            chinh_lai_vi_tri_laser_truoc_do(vi_tri_dat_hop_3_tay41_do, 100, 4, 20);
            robotStop(0);
            chinh_lai_vi_tri_laser_trai(176, 1000);
        } 
        else if (robot_position == 2) {
            chinh_lai_vi_tri_laser_truoc_do(vi_tri_dat_hop_2_tay41_do, 100, 4, 20);
            robotStop(0);
            chinh_lai_vi_tri_laser_trai(176, 1000);
        } 
        else if (robot_position == 1) {
            chinh_lai_vi_tri_laser_truoc_do(vi_tri_dat_hop_1_tay41_do, 100, 4, 20);
            robotStop(0);
            chinh_lai_vi_tri_laser_trai(176, 1000);
        }
    } 
    else if (tay_2_co_qua || tay_3_co_qua) {
        if (robot_position == 3) {
            chinh_lai_vi_tri_laser_truoc_do(vi_tri_dat_hop_3_tay23_do, 100, 4, 20);
            robotStop(0);
            chinh_lai_vi_tri_laser_trai(176, 1000); /// trg hop tay 3 vi trí 1
        } 
        else if (robot_position == 2) {
            chinh_lai_vi_tri_laser_truoc_do(vi_tri_dat_hop_2_tay23_do, 100, 4, 20);
            robotStop(0);
            chinh_lai_vi_tri_laser_trai(176, 1000);
        } 
        else if (robot_position == 1) {
            chinh_lai_vi_tri_laser_truoc_do(vi_tri_dat_hop_1_tay23_do, 100, 4, 20);
            robotStop(0);
            chinh_lai_vi_tri_laser_trai(195, 1000);
        }
    }
		
			robotStop(0);
			// do chan len dat
			su_dung_chan(500);
			for(i=0;i<250;i++)	{
				while(abs(bientrochansauValue - target_chan_sau) > 10)	{ vTaskDelay(1); if(!wantExit())	break;}
					}		
			dat_hop_vao_o_tang2();
			
}


void retry_co_qua_tren_tay(void) {
    // Ki?m tra tay 1
    if (CB_kep_1_1 == 0 && CB_kep_1_2 == 0) {
        da_lay_tay2 = 1;
    } else {
        da_lay_tay2 = 0;
    }

    // Ki?m tra tay 2
    if (CB_kep_2_1 == 0 && CB_kep_2_2 == 0) {
        da_lay_tay3 = 1;
    } else {
        da_lay_tay3 = 0;
    }

    // Ki?m tra tay 3
    if (CB_kep_3_1 == 0 && CB_kep_3_2 == 0) {
        da_lay_tay4 = 1;
    } else {
        da_lay_tay4 = 0;
    }

    // Ki?m tra tay 4
    if (CB_kep_4_1 == 0 && CB_kep_4_2 == 0) {
        da_lay_tay1 = 1;
    } else {
        da_lay_tay1 = 0;
    }
}

void chinh_lai_vi_tri_laser_truoc_do(int vitri, int gia_tri_lap, int min_toc, int max_toc);
void tudonghoantoan_san_do(void) {
		Kiem_Tra_Ket_Qua_Gap();
	// toi lay vk
		 Xuat_Phat_Lay_Vu_Khi_Do(162,1450,215);
	// cho rb1 lay vk xong thì vuot rung
		mo_vk_san_do();
	
		if ( da_lay_vk == 1)	{	
				Run_All_Blocks_From_Queue_san_do();
			}
		if (hoan_thanh_chay_rung == 1 ) DatKFS_do(18),hoan_thanh_chay_rung = 2 ;
	/// ******* //////
		if (hoan_thanh_chay_rung == 2 && mode_cay_diem == 1)  {
				quyet_dinh_dat_hop_tang3(); // danh cay diem 1
				hoan_thanh_chay_rung = 3 ;}
		else if (hoan_thanh_chay_rung == 2 && mode_cay_diem == 2) {
//				tu_dong_dat_tang2_do(); // danh nhanh 1
				robotRotate(890,0.2, 0);
				while(robotFixAngle()){
					vTaskDelay (1); 
					if(!wantExit())	break;
				}
				robotStop(0);
				chinh_lai_vi_tri_laser_truoc_do(vi_tri_dat_hop_2_tay41_do, 100, 5 , 20);
            robotStop(0);
        chinh_lai_vi_tri_laser_trai(175, 1000);
				robotStop(0);
				dat_hop_vao_o_tang2();	
				robotStop(0);
				
				if (dem_goi_tin_gap != 2 ) {
						robotRunAngle(1800,12,900, 0.5);
						vTaskDelay(7000);
				}
				else {
						robotRunAngle(1800,12,900, 0.5);
						vTaskDelay(2500);
				}
				robotStop(0);
				su_dung_chan_thuong(710);
				chinh_lai_vi_tri_laser_truoc_do(vi_tri_dat_hop_3_tay23_do, 100, 5 , 25);
				hoan_thanh_chay_rung = 3 ;}
		
			robotStop(0);
			
				/// ******* //////
		if (hoan_thanh_chay_rung == 3 && mode_cay_diem == 1)  {
				tu_dong_dat_tang2_do(); // danh cay diem 2
				hoan_thanh_chay_rung = 4 ;}
		else if (hoan_thanh_chay_rung == 3 && mode_cay_diem == 2) {
				quyet_dinh_dat_hop_tang3_danh_nhanh();  // danh nhanh 2
				kiem_tra_so_qua_tren_tay();
				if ( so_qua_tren_tay > 0  ) {
						tu_dong_dat_tang2_xanh();
				}
				hoan_thanh_chay_rung = 4 ;}
		
		robotStop(0);
		if (hoan_thanh_chay_rung == 4 )  {
				kiem_tra_so_qua_tren_tay();
				if ( so_qua_tren_tay == 1  ) {
						su_dung_chan_thuong(710);
						chinh_lai_vi_tri_laser_truoc_do(vi_tri_dat_hop_3_tay23_do, 100, 5, 25);
						be_len_dat_xanh_1_qua_tren_3();
			}
				hoan_thanh_chay_rung = 5 ;}
		
		robotStop(0);
  }

void retry_zone2_do(void) {
	// toi lay vk
		retry_co_qua_tren_tay();
		Run_All_Blocks_From_Queue_san_do();
		if (hoan_thanh_chay_rung == 1 ) DatKFS_do(18),hoan_thanh_chay_rung = 2 ;
	
	/// ******* //////
		if (hoan_thanh_chay_rung == 2 && mode_cay_diem == 1)  {
				quyet_dinh_dat_hop_tang3(); // danh cay diem 1
				hoan_thanh_chay_rung = 3 ;}
		else if (hoan_thanh_chay_rung == 2 && mode_cay_diem == 2) {
//				tu_dong_dat_tang2_do(); // danh nhanh 1
				robotRotate(880,0.2, 0);
				while(robotFixAngle()){
					vTaskDelay (1); 
					if(!wantExit())	break;
				}
				robotStop(0);
				chinh_lai_vi_tri_laser_sau(107, 100, 4, 15);
            robotStop(0);
        chinh_lai_vi_tri_laser_trai(172, 1000);
				robotStop(0);
				dat_hop_vao_o_tang2();	
				robotStop(0);
				robotRunAngle(1800,12,900, 0.5);
				vTaskDelay(7000);
				robotStop(0);
				su_dung_chan_thuong(710);
				chinh_lai_vi_tri_laser_sau(35, 100, 4, 15);
				hoan_thanh_chay_rung = 3 ;}
		
			robotStop(0);
			
				/// ******* //////
		if (hoan_thanh_chay_rung == 3 && mode_cay_diem == 1)  {
				tu_dong_dat_tang2_do(); // danh cay diem 2
				hoan_thanh_chay_rung = 4 ;}
		else if (hoan_thanh_chay_rung == 3 && mode_cay_diem == 2) {
				quyet_dinh_dat_hop_tang3_danh_nhanh();  // danh nhanh 2
				hoan_thanh_chay_rung = 4 ;}
		
		robotStop(0);
		if (hoan_thanh_chay_rung == 4 )  {
				kiem_tra_so_qua_tren_tay();
				if ( so_qua_tren_tay == 1  ) {
						su_dung_chan_thuong(710);
						chinh_lai_vi_tri_laser_truoc_do(vi_tri_dat_hop_3_tay23_do, 100, 5, 25);
						be_len_dat_xanh_1_qua_tren_3();
			}
				hoan_thanh_chay_rung = 5 ;}
		
		robotStop(0);
  }


#define DEAD_ZONE 3       

int calc_encoder(int error)
{
    int abs_err = abs(error);

    float enc = 8.0f * abs_err + 50.0f;
    return (int)enc;
}

// ===== MAIN FUNCTION =====
void run_align_center(void)
{
		int encoder_target = calc_encoder(do_lech);
		
    if (do_lech < 85)
    {
        // lech trái  chay sang phai
        robotRun(900, 13);
				RESET_ENCODER(); 
				while(abs(ENCODER_FR()) + abs(ENCODER_FL()) < encoder_target)	{vTaskDelay (5); if(!wantExit())	break;}
    }
    else if (do_lech > 98)
    {
        // lech phai chay phai
        robotRun(-900, 13);
				RESET_ENCODER(); 
				while(abs(ENCODER_RR()) + abs(ENCODER_RL()) < encoder_target)	{vTaskDelay (5); if(!wantExit())	break;}
    }
		else {
				robotStop(0);
		}
}

void chinh_lai_vi_tri_laser_phai_zone3_do(int vitri, int gia_tri_lap, int min_toc, int max_toc)
{
	int speed ;
	int dieuchinh;
		for(i=0;i<gia_tri_lap;i++)
				{
		while(abs(lazePhaiValue - vitri) > 1)	{
			dieuchinh = lazePhaiValue - vitri;
			speed = custom_smooth_speed(dieuchinh, min_toc, max_toc);
			
					if  ((lazePhaiValue - vitri)> 0 ) {
							robotRunAngle(900, speed, 0, 0.5);
					}
					else if ((lazePhaiValue - vitri) < 0) {
					
					robotRunAngle(-900, speed, 0, 0.5);
					
					}
					else {
								robotStop(0);

								}
				if(!wantExit())	break;
			}
		}   		
	}


// ham nhat lai hop roi dat vao o
void chon_o_nhat_hop_do(void) {

		if (nhat_dat_hop == 1) {
				chinh_lai_vi_tri_laser_phai_zone3_do(205, 200, 4, 25);
			}
		else if (nhat_dat_hop == 2) {
				chinh_lai_vi_tri_laser_phai_zone3_do(255, 200, 4, 25);
			}
		else if (nhat_dat_hop == 3) {
				chinh_lai_vi_tri_laser_phai_zone3_do(299, 200, 4, 25);
			}
		else if (nhat_dat_hop == 4|| nhat_dat_hop == 5 || nhat_dat_hop == 6) {
				chinh_lai_vi_tri_laser_sau_zone3(24, 1000);
				chinh_lai_vi_tri_laser_phai_zone3_do(195, 200, 4, 25);
			}

			robotStop(0);
		if (nhat_dat_hop == 1|| nhat_dat_hop == 2 || nhat_dat_hop == 3) {
				su_dung_chan_thuong(500);
				chinh_lai_vi_tri_laser_sau_zone3(7, 1000);
				robotStop(0);
			
				if (da_lay_tay1 == 0 && da_lay_tay2 == 0) {
					speed_tay_gat2 = 150;
					target_tay_gat2 = 400;
					for(i=0; i<550; i++) 
						{ 
					while(abs(bientrodaytay2Value - target_tay_gat2) > 15) { vTaskDelay(1); if(!wantExit()) break; }
						}
					dat_hop4_2(500, 330,5, 4);
					vTaskDelay(2000); 
					speed_tay_gat2 = 250;
					target_tay_gat2 = vitri_tay2home ;
					for(i=0; i<550; i++) 
						{ 
					while(abs(bientrodaytay2Value - target_tay_gat2) > 15) { vTaskDelay(1); if(!wantExit()) break; }
						}
					}
				else if (da_lay_tay1 == 1 && da_lay_tay2 == 0) {
						speed_tay_gat1 = 150;
				target_tay_gat1 = 470;
				for(i=0; i<550; i++) 
					{ 
				while(abs(bientrodaytay1Value - target_tay_gat1) > 15) { vTaskDelay(1); if(!wantExit()) break; }
					}
				dat_hop1_3(500, 560,5, 1);
				vTaskDelay(2000); 
				speed_tay_gat1 = 250;
				target_tay_gat1 = vitri_tay1home ;
				for(i=0; i<550; i++) 
					{ 
				while(abs(bientrodaytay1Value - target_tay_gat1) > 20) { vTaskDelay(1); if(!wantExit()) break; }
					}
			}
		}

		// chon be tang 3
			else if (nhat_dat_hop == 4 ||nhat_dat_hop == 5 || nhat_dat_hop == 6  ) {
				robotRotate(-890,0.5,0);
				while(robotFixAngle()){
					vTaskDelay (1); 
					if(!wantExit())	break;
				}
				robotStop(0);
				su_dung_chan(710);
				quyet_dinh_dat_hop_tang3();
			}
		robotStop(0);
}			


void nhat_hop_zone3_do (void) {
		int lap;
    bool thu_lai = false;
	
		su_dung_chan(350);
		if (da_lay_tay1 == 0 && da_lay_tay2 == 0) {
				Kep_phai_4_ra;
				speed_tay_gat2 = 250;
				target_tay_gat2 = 180;
		}
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 0) {
				speed_tay_xoay = 220;
				target_xoay_tay = vi_tri_tay_12 + 3;
				Kep_phai_1_ra;
				speed_tay_gat1 = 240;
				target_tay_gat1 = 710;
			}
		robotRunAngle(1800, 50, 0, 0.5);
		for(i=0;i<550;i++)	
		{	
				while(lazeSauValue > 370)	
				{	
					vTaskDelay(1); 
					if(!wantExit())	break;
				}
		}
		
		robotRunAngle(1800, 45, 0, 0.5);
		for(i=0;i<550;i++)	
		{	
				while(lazeSauValue > 220)	
				{	
					vTaskDelay(1); 
					if(!wantExit())	break;
				}
		}

		robotStop(0);
		/// check tam hop
		for(i=0;i<5000;i++)	
		{	
			run_align_center();
		}
		
		su_dung_chan(400);
		
		robotRunAngle(1800, 40, 0, 0.5);
		for(i=0;i<550;i++)	
		{	
				while(lazeSauValue > 120)	
				{	
					vTaskDelay(1); 
					if(!wantExit())	break;
				}
		}		
		for(i=0;i<5000;i++)	
		{	
			run_align_center();
		}
		
		robotRunAngle(1800, 30, 0, 0.5);
		for(i=0;i<550;i++)	
		{	
				while(lazeSauValue > 55)	
				{	
					vTaskDelay(1); 
					if(!wantExit())	break;
				}
		}	
		robotRunAngle(1800, 18, 0, 0.5);
    for(i=0; i<550; i++) {   
        while(lazeSauValue > 25) {   
            vTaskDelay(1); 
            if(!wantExit()) break;
        }
    } 
		
		robotRunAngle(1800, 10, 0, 0.5);
		for(i=0;i<550;i++)	
		{	
				while(lazeSauValue > 6)	
				{	
					vTaskDelay(1); 
					if(!wantExit())	break;
				}
		}		
				vTaskDelay (1000);
				robotStop(0);
		
		// chi tracking hop 
    if (da_lay_tay1 == 0 && da_lay_tay2 == 0) {
 
				Ktra_vtri_kep4(); 
				speed_tay_gat2 = 250;
				target_tay_gat2 = Min_tay_gat2 + 13;
				for(i=0; i<550; i++) { 
						while(abs(bientrodaytay2Value - target_tay_gat2)> 20 ) {
								vTaskDelay(1); 
								if(!wantExit()) break;
						}
				}
				vTaskDelay(1000);
				Kep_phai_4_vao;
				vTaskDelay(1500);
				speed_tay_gat2 = 250;
				target_tay_gat2 = vitri_tay2home;
				for(i=0; i<550; i++) { 
						while(abs(bientrodaytay2Value - target_tay_gat2)> 200 ) {
								vTaskDelay(1); 
								if(!wantExit()) break;
						}
				}
    }
    else if (da_lay_tay1 == 1 && da_lay_tay2 == 0) {

				Ktra_vtri_kep1(); 
				speed_tay_gat1 = 250;
				target_tay_gat1 = Min_tay_gat1 + 16;
				for(i=0; i<550; i++) { 
						while(abs(bientrodaytay1Value - target_tay_gat1)> 20 ) {
								vTaskDelay(1); 
								if(!wantExit()) break;
						}
				}
				vTaskDelay(1000);
				Kep_phai_1_vao;
				vTaskDelay(1500); 
				speed_tay_gat1 = 250;
				target_tay_gat1 = vitri_tay1home;
				for(i=0; i<550; i++) { 
						while(abs(bientrodaytay1Value - target_tay_gat1)> 200 ) {
								vTaskDelay(1); 
								if(!wantExit()) break;
						}
					}
    }
			robotRunAngle(0,15,0, 0.5);
			vTaskDelay(5000);
			robotStop(0);

	//	lui ra roi chay toi dat o
			chon_o_nhat_hop_do();	
			robotStop(0);
		
		    // =========================================================
    // NHAT QUA LAI 3 LAN
    // =========================================================
			for (lap = 0; lap < 10; lap++) {
				Tay2_xuong;
				chinh_lai_vi_tri_laser_phai_zone3_do(162, 500, 4, 35);
        chinh_lai_vi_tri_laser_sau_zone3(210, 1000);
        robotStop(0);
        
        robotRotate(170, 0.2, 0);
        while(robotFixAngle()) {
            vTaskDelay (1); 
            if(!wantExit()) break;
        }
        robotStop(0);
        
        /// Ngó duoi
        Nang_thuong();
        target_chan_truoc = 710 ;
        target_chan_sau = 650;
				
				SEND_UART (4,7);
        
        // reset bien nhat hop //
        mode_nhat_hop = 0;
        do_lech = 0;
        khoangcach = 0;
        nhat_dat_hop = 0;
        /// ***********************
        
        for(i=0; i<350; i++) {   
            while(nhin_hop_duoi_dat  == 0) {   
                vTaskDelay(1); 
                if(!wantExit()) break; 
            }
        }
        // ngó trên
        speed_chan_sau = 15;
        speed_chan_truoc = 15;
        target_chan_truoc = 650 ;
        target_chan_sau = 650;
        vTaskDelay (5500); 
        robotStop(0);
        speed_chan_sau = 10;
        speed_chan_truoc = 10;
        target_chan_truoc = 650 ;
        target_chan_sau = 710;
        vTaskDelay (5500); 
        robotStop(0);
				
				for(i=0; i<350; i++) {   
            while(nhin_hop_tren_buc == 0) {   
                vTaskDelay(1); 
                if(!wantExit()) break; 
            }
        }
    
        // nhan tin hieu xong roi xoay ngang ve home
        robotRotate(10, 0.3, 0);
        while(robotFixAngle()) {
            vTaskDelay (1); 
            if(!wantExit()) break;
        }
        robotStop(0);
        su_dung_chan_thuong(400);
        robotStop(0);
        Kep_phai_4_ra;
        speed_tay_gat2 = 250;
        target_tay_gat2 = 180;
        
        for(i=0; i<350; i++) {   
            while(mode_nhat_hop == 0) {   
                vTaskDelay(1); 
                if(!wantExit()) break; 
            }
        }

        /// nhin thay khoi sau do check lazer trai
        for(i=0; i<350; i++) {   
            while(lazeTraiValue > 350) {   
                vTaskDelay(1); 
                if(!wantExit()) break; 
            }
        }
        vTaskDelay(7000);
				robotRunAngle(1800, 10, 0, 0.5);
				vTaskDelay(3000);
        
        /// check tam hop
        for(i=0; i<5000; i++) {   
            run_align_center();
        }
        
        robotStop(0);
        robotRunAngle(1800, 25, 0, 0.5);
        for(i=0; i<550; i++) {   
            while(lazeSauValue > 30) {   
                vTaskDelay(1); 
                if(!wantExit()) break;
            }
        }   
        
        robotRunAngle(1800, 10, 0, 0.5);
        for(i=0; i<550; i++) {   
            while(lazeSauValue > 6) {   
                vTaskDelay(1); 
                if(!wantExit()) break;
            }
        }       
        robotStop(0);
        
				Ktra_vtri_kep4();
				vTaskDelay(1000);
				speed_tay_gat2 = 250;
				target_tay_gat2 = Min_tay_gat2 + 13;
				
				for(i=0; i<550; i++) { 
						while(abs(bientrodaytay2Value - target_tay_gat2)> 20 ) {
								vTaskDelay(1); 
								if(!wantExit()) break;
						}
				}
				vTaskDelay(1000);
				Kep_phai_4_vao;
				vTaskDelay(1500);
				speed_tay_gat2 = 250;
				target_tay_gat2 = vitri_tay2home;
				for(i=0; i<550; i++) { 
						while(abs(bientrodaytay2Value - target_tay_gat2)> 200 ) {
								vTaskDelay(1); 
								if(!wantExit()) break;
						}
				}

        // ----------------------------------------------------
        
        chon_o_nhat_hop_xanh();
				nhin_hop_duoi_dat = 0; 
				nhin_hop_tren_buc = 0; 
    }
}


void bat_dau_chay_do (void) {
    if (Start == 0 && mode_chay_rung == 1) {
        tudonghoantoan_san_do();
    }
		else if (Start == 0 && mode_chay_rung == 0 && mode_nhat_hop == 0 && mode_retry_zone_3 == 0) {
        Xuat_Phat_Lay_Vu_Khi_Do(162,1450,215);
    }
    else if (Start == 0 && mode_chay_rung == 2) {
        retry_zone2_do();
    }
    else if (Start == 0 && mode_nhat_hop == 1) {
        nhat_hop_zone3_do();
    }
		else if (Start == 0 && mode_retry_zone_3 == 1) {
        chon_o_retry3_do();
    }
}
	
