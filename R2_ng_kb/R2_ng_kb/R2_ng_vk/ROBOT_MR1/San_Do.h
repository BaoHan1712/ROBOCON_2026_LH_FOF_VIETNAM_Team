//// *********************  HAM GOI RA DE DUNG ********************************
void chinh_lai_vi_tri_VK_do(int vitri, int gia_tri_lap);
void chinh_lai_vi_tri_laser_trai_do(int vitri, int gia_tri_lap);
void chinh_lai_vi_tri_laser_phai_do(int vitri, int gia_tri_lap);
void chinh_lai_vi_tri_laser_phai_custom_do(int vitri, int gia_tri_lap);
void chinh_lai_vi_tri_laser_trai_custom_do(int vitri, int gia_tri_lap);

// ********** VI TRI CHAY SAN DO *************
void Leo_bac_400_co_thanh_do(void);
void Leo_bac_200_ko_thanh_do(void);
void Leo_bac_400_ko_thanh_do(void);
void Leo_bac_200_bam_thanh_phai_do(void);
void Xuong_bac_200_do_4(void);
void Leo_bac_200_do_5(void);
void Lay_ben_phai_bac_200_duoi_do_6(void);
void Leo_bac_200_do_7 (void);
void Lay_ben_phai_bac_200_duoi_do_8(void);
void Xuong_bac_200_do_9(void);
void xuong_bac_200_do_10 (void);
void xuong_bac_200_11_do(void);
void xuong_bac_200_do_12 (void);

void Lay_ben_phai_bac_200_tren_do_9(void);
void Lay_ben_phai_bac_200_duoi_do_5 (void);
void Lay_ben_trai_bac_200_tren_do_5_6 (void);
void Lay_ben_trai_bac_200_duoi_do_8_11(void);
void Lay_ben_trai_bac_200_tren_do_7_10(void);

//// VOID QUA TRAI,  QUA PHAI 
void qua_trai_len_bac_400_do(void);
void qua_trai_len_bac_200_cua_vao_do(void);
void qua_phai_len_bac_400_do(void);
void qua_phai_len_bac_200_cua_vao_do(void);

///// *************************************************************************
//**********************************SAN DO*************************************
void Xuat_Phat_Lay_Vu_Khi_Do(int vu_khi, int goc_ve, int vitri)
 //				RESET_ENCODER(); 
{					
				speed_tay_gat1 = 150;
				target_tay_gat1 = vitri_tay1home;
	
				speed_tay_gat2 = 250;
				target_tay_gat2 = vitri_tay2home;
	
				Nang_cuc_nhanh();
	
				target_chan_truoc = 350, target_chan_sau = 350;
				Tay_kep_mo;

				robotRunAngle(150 + vu_khi*2,30,5,0.3);

//	
				for(i=0;i<100;i++)
				{
					while(lazeTraiValue < vu_khi - 20 )	
					{
						vTaskDelay (1);
						if(!wantExit())	break;
					}
				}
//			
				target_chan_truoc = 615, target_chan_sau =605;
				for(i=0;i<50;i++)		
				{
				while(bientrochantruocValue < 470)	{
				Bam_thanh_laser_trai(25,0,0,vu_khi,1,-150,15);
				vTaskDelay(1); 
				if(!wantExit())	break;}
				}
	
				for(i=0;i<250;i++)
				{
					while(lazeTruocValue > 23)	
					{	
	
						Bam_thanh_laser_trai(14,0,0,vu_khi,1,-150,15);
						if(!wantExit())	break;
					}
				}
				
				Tay_kep_xuong;
			
				for(i=0;i<100;i++)
				{
					while(HT_1 == 1 && HT_2 == 1)	
					{				
						Bam_thanh_laser_trai(7,0,0,vu_khi,1,-100,15);
						if(!wantExit())	break;
					}
				}
				vTaskDelay (3000);
				robotStop(50);
				
				vTaskDelay (2000);
				
				for(i=0;i<500;i++)
				{
					while(CB_tay_kep_vk_T == 1 || CB_tay_kep_vk_P == 1)	
					{	
						if	(CB_tay_kep_vk_T == 1) robotRun(850,6);
						else if 	(CB_tay_kep_vk_P == 1) robotRun(-850,6);
						else		robotStop(0);				
						vTaskDelay (1);
						if(!wantExit())	break;
					}
				}
				
				robotStop(0);
				Tay_kep_dong;
				
				vTaskDelay (2000);
				
				for(i=0;i<500;i++)
				{
					while(CB_kep == 1)	
					{	
						vTaskDelay (1);						
						if(!wantExit())	break;
					}
				}
				robotStop(0);
			
				speed_chan_sau =35;
				speed_chan_truoc = 80;
				
				target_chan_truoc = 615, target_chan_sau = 615;
				
				vTaskDelay(4000);
				
				target_chan_truoc = 665, target_chan_sau = 660;
				vTaskDelay(1000);
				
				Tay_kep_len; 
				
				vTaskDelay(5000);
//		
				robotRun(goc_ve,30);
				robotRotate(920,1,0);
				
				RESET_ENCODER(); 
								
				Nang_cuc_nhanh();
				
				while(_robotIMUAngle < 800)	
				{
					vTaskDelay (5); 
					if(!wantExit())	break;
					if(_robotIMUAngle > 450)		target_chan_truoc = 265, target_chan_sau = 265;
				}

				robotRunAngle(-900,5,900,0.5);
				
				for(i=0;i<100;i++)
				{
					while(HT_3 == 0 && HT_4 == 0)	
					{           
						vTaskDelay (5); 
						if(!wantExit())	break;
					}
				}
				vTaskDelay(2000);
				chinh_lai_vi_tri_VK_do(vitri, 1000);
				
				robotStop(0);
				speed_chan_sau =20;
				speed_chan_truoc = 45;
				target_chan_truoc = 255, target_chan_sau = 255;
				
				robotStop(0);
			
				
}
//// ******************* VAO CUA RUNG SAN DO ************************

/// ********** XOAY DAU TOI CUA DO 1

void Xoay_dau_truoc_cua_do_3 (void)
{
	Nang_cuc_nhanh();

	target_chan_truoc = 255;
	target_chan_sau = 255;

	
	vTaskDelay(2000);
	
	Kep_phai_4_ra;

	
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
			chinh_lai_vi_tri_laser_phai_custom_do(vi_tri_cua_rung_do_3_lazer_phai_tay_41  , 1000);
	}
	else if (TinHieu_ChuanBi_GapThang == 0) {
			chinh_lai_vi_tri_laser_phai_custom_do(vi_tri_cua_rung_do_3_lazer_phai_tay_41 - 10 , 1000);
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
	if (block_pha == 2) {
	SEND_UART (4,1);
		}
	else {
		co_vat_can = 0 ;
	}
	Kep_phai_4_ra;

	
	robotRunAngle(1650,20,-900,2.2);
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
			chinh_lai_vi_tri_laser_phai_custom_do(vi_tri_cua_rung_do_2_lazer_phai_tay_41 , 1000);
	}
	else if (TinHieu_ChuanBi_GapThang == 0) {
			chinh_lai_vi_tri_laser_phai_custom_do(vi_tri_cua_rung_do_2_lazer_phai_tay_41 - 10 , 1000);
	}
	
	robotStop(0); 	
				
}


void Xoay_dau_truoc_cua_do_1(void)
{
	Nang_cuc_nhanh();

	target_chan_truoc = 255;
	target_chan_sau = 255;

	
	vTaskDelay(2000);
	
	Kep_phai_4_ra;

	
	robotRunAngle(1550,20,-900,2);
			
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
				
	if (block_pha == 1) {
	SEND_UART (4,1);
		}
	else {
		co_vat_can = 0 ;
	}
	if (TinHieu_ChuanBi_GapThang == 1) {
			chinh_lai_vi_tri_laser_trai_custom_do(vi_tri_cua_rung_do_1_lazer_trai_tay_41 , 1000);
	}
	else if (TinHieu_ChuanBi_GapThang == 0) {
			chinh_lai_vi_tri_laser_trai_custom_do(vi_tri_cua_rung_do_1_lazer_trai_tay_41 + 10 , 1000);
	}
	robotStop(0); 	
				
}

void Vao_rung_mai_3_do(int vitri)
{
			//		// Do chan len 1 nua
		Nang_cuc_nhanh();
		
		target_chan_truoc = Min_chan_truoc + 250;
		target_chan_sau = Min_chan_sau + 250;
	
		robotRunAngle(900,35,-900,0.9);
		for(i=0;i<250;i++)
					{
						while(lazeSauValue > 115)	
						{	
							vTaskDelay (1);
							if(!wantExit())	break;
						}
				}
		robotRunAngle(900,28,-900,0.9);
		for(i=0;i<250;i++)
					{
						while(lazeSauValue > 60)	
						{	
							vTaskDelay (1);
							if(!wantExit())	break;
						}
				}
			
		Kep_phai_4_ra;			
					
			// chuan bi tay xuong truoc
	if (TinHieu_ChuanBi_GapThang == 1) {
				speed_tay_gat2 = 250;
				target_tay_gat2 = vitri_tay2home - 200;		
	}

		su_dung_chan(697);

	if (TinHieu_ChuanBi_GapThang == 0) {
				for(i=0;i<250;i++)
					{
						while(lazeSauValue > 10)	
						{	
							Bam_thanh_laser_phai(15,900,-900,vitri - 15,2,-150,10);
							vTaskDelay (1);
							if(!wantExit())	break;
						}
				}
					
					for(i=0;i<1550;i++)
							{
									while( CB_vtri_leo == 1 ||CB_Ha_Sau == 1 || CB_Cap_Thanh_Sau == 0)	
								{	
									Bam_thanh_laser_phai(6,900,-900,vitri - 15,2,-150,10);
									vTaskDelay (1);
									if(!wantExit())	break;
									
								}
							}
					vTaskDelay (1000);
				chinh_lai_vi_tri_laser_phai_do(vitri - 15, 1000);
	}
	else if (TinHieu_ChuanBi_GapThang == 1) {
				for(i=0;i<250;i++)
					{
						while(lazeSauValue > 10)	
						{	
							Bam_thanh_laser_phai(15,900,-900,vitri ,2,-150,10);
							vTaskDelay (1);
							if(!wantExit())	break;
						}
				}
					
			for(i=0;i<1550;i++)
							{
									while( CB_vtri_leo == 1 ||CB_Ha_Sau == 1 || CB_Cap_Thanh_Sau == 0)	
								{	
									Bam_thanh_laser_phai(6,900,-900,vitri ,2,-150,10);
									vTaskDelay (1);
									if(!wantExit())	break;
									
								}
							}
					vTaskDelay (1000);
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
	
	robotRunAngle(900,35,-900,0.5);
	for(i=0;i<250;i++)
				{
					while(lazeSauValue > 115)	
					{	
						vTaskDelay (1);
						if(!wantExit())	break;
					}
			}
	robotRunAngle(900,28,-900,0.5);
	for(i=0;i<250;i++)
				{
					while(lazeSauValue > 50)	
					{	
						vTaskDelay (1);
						if(!wantExit())	break;
					}
			}
				
	
	// chuan bi tay xuong truoc
	if (TinHieu_ChuanBi_GapThang == 1) {
				speed_tay_gat2 = 250;
				target_tay_gat2 = vitri_tay2home - 200;		
	}	
	
	if (TinHieu_ChuanBi_GapThang == 0) {
			for(i=0;i<250;i++)
					{
						while(lazeSauValue > 10)	
						{	
							Bam_thanh_laser_phai(15,900,-900,vitri - 10,2,-150,10);
							vTaskDelay (1);
							if(!wantExit())	break;
						}
				}				
			for(i=0;i<1550;i++)
						{
							while( CB_vtri_leo == 1 ||CB_Ha_Sau == 1 || CB_Cap_Thanh_Sau == 0)	
							{	
								Bam_thanh_laser_phai(6,900,-900,vitri - 10,2,-150,10);
								if(!wantExit())	break;
								vTaskDelay (1);
							}
						}
						chinh_lai_vi_tri_laser_phai_do(vitri - 10, 1000);
	}
	else if (TinHieu_ChuanBi_GapThang == 1) {
					for(i=0;i<250;i++)
					{
						while(lazeSauValue > 10)	
						{	
							Bam_thanh_laser_phai(15,900,-900,vitri ,2,-150,10);
							vTaskDelay (1);
							if(!wantExit())	break;
						}
				}				
							
					for(i=0;i<1550;i++)
							{
								while( CB_vtri_leo == 1 ||CB_Ha_Sau == 1 || CB_Cap_Thanh_Sau == 0)	
								{	
									Bam_thanh_laser_phai(6,900,-900,vitri,2,-150,10);
									if(!wantExit())	break;
									vTaskDelay (1);
								}
							}
							su_dung_chan(565);	
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
	
		robotRunAngle(900,38,-900,0.9);
		for(i=0;i<250;i++)
					{
						while(lazeSauValue > 115)	
						{	
							vTaskDelay (1);
							if(!wantExit())	break;
						}
				}
		robotRunAngle(900,28,-900,0.9);
		for(i=0;i<250;i++)
					{
						while(lazeSauValue > 60)	
						{	
							vTaskDelay (1);
							if(!wantExit())	break;
						}
				}
			
		Kep_phai_4_ra;			
					
			// chuan bi tay xuong truoc
	if (TinHieu_ChuanBi_GapThang == 1) {
				speed_tay_gat2 = 250;
				target_tay_gat2 = vitri_tay2home - 200;		
	}

		su_dung_chan(697);

	if (TinHieu_ChuanBi_GapThang == 0) {
					for(i=0;i<250;i++)
					{
						while(lazeSauValue > 10)	
						{	
							Bam_thanh_laser_trai(15,900,-900,vitri + 15,2,150,30);
							vTaskDelay (1);
							if(!wantExit())	break;
						}
				}
					
					for(i=0;i<1550;i++)
							{
									while( CB_vtri_leo == 1 ||CB_Ha_Sau == 1 || CB_Cap_Thanh_Sau == 0)	
								{	
									Bam_thanh_laser_trai(7,900,-900,vitri + 15,2,150,30);
									vTaskDelay (1);
									if(!wantExit())	break;
									
								}
							}
					vTaskDelay (1000);
				chinh_lai_vi_tri_laser_trai_do(vitri + 15, 1000);
	}
	else if (TinHieu_ChuanBi_GapThang == 1) {
				for(i=0;i<250;i++)
					{
						while(lazeSauValue > 10)	
						{	
							Bam_thanh_laser_trai(15,900,-900,vitri ,2,150,30);
							vTaskDelay (1);
							if(!wantExit())	break;
						}
				}
					
					for(i=0;i<1550;i++)
							{
									while( CB_vtri_leo == 1 ||CB_Ha_Sau == 1 || CB_Cap_Thanh_Sau == 0)	
								{	
									Bam_thanh_laser_trai(7,900,-900,vitri ,2,150,30);
									vTaskDelay (1);
									if(!wantExit())	break;
									
								}
							}
					vTaskDelay (1000);
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
	robotStop(30);
	hoan_thanh_chay_rung = 1;

}

void vuot_rung_ve_homeTay_bac_200_do (void) {
	Xuong_bac_200(900, -900);
	robotStop(30);
	hoan_thanh_chay_rung = 1;
}

void kiem_tra_qua_tay_nao_do (void) {
	if (CB_kep_4_2 == 0 && CB_kep_1_2 == 1 && CB_kep_2_2 == 1 && CB_kep_3_2 == 1 )	{
			speed_tay_xoay = 100;
			target_xoay_tay = 410;
			tin_hieu_dat_hop_3_4 = 1;
	}
	else if (CB_kep_4_2 == 0 && CB_kep_1_2 == 0 && CB_kep_2_2 == 1 && CB_kep_3_2 == 1 )	{
			speed_tay_xoay = 100;
			target_xoay_tay = 410;
			tin_hieu_dat_hop_3_4= 1;
	}
	else if (CB_kep_4_2 == 0 && CB_kep_1_2 == 0 && CB_kep_2_2 == 0 && CB_kep_3_2 == 1 )	{
			speed_tay_xoay = 100;
			target_xoay_tay = 410;
			tin_hieu_dat_hop_3_4 = 1;
	}
	else if (CB_kep_4_2 == 0 && CB_kep_1_2 == 0 && CB_kep_2_2 == 0 && CB_kep_3_2 == 0 )	{
			speed_tay_xoay = 100;
			target_xoay_tay = 410;
			tin_hieu_dat_hop_3_4 = 1;
	}
	else {
			speed_tay_xoay = 100;
			target_xoay_tay = 603;
			tin_hieu_dat_hop_1_2 = 1;
	}

}

void DatKFS_do(int vitri)
{
	kiem_tra_qua_tay_nao_do(); // ham kiem tra co qua tay nao de dat
	
	Nang_thuong();
	target_chan_truoc = 335;
	target_chan_sau = 335;
	
	for(i=0;i<150;i++)		
	{
		while(abs(bientrochansauValue - target_chan_sau) > 10)	{vTaskDelay(1); if(!wantExit())	break;}
	}
	vTaskDelay(4000); 
	
	chinh_lai_vi_tri_laser_trai_custom_do(189, 1000);
	

		robotRunAngle(900,35,-900,0.5);
		for(i=0;i<550;i++)	
	{	
			while(lazePhaiValue > 340)	
			{	
				vTaskDelay(5); 
				if(!wantExit())	break;
			}
	}	
	vTaskDelay(3000); 
	
		for(i=0;i<550;i++)	
	{	
			while(lazePhaiValue < 300)	
			{	

				vTaskDelay(5); 
				if(!wantExit())	break;
			}
	}		
	
		vTaskDelay(5000); 
		
	
	for(i=0;i<550;i++)	
	{	
			while(lazeSauValue > 30)	
			{	
				vTaskDelay(1); 
				if(!wantExit())	break;
			}
	}		
		
	
	for(i=0;i<550;i++)	
	{	
			while(lazePhaiValue > 220)	
			{	
				Bam_laser_sau(25,0,-900, vitri, 3, 220, 10);
				vTaskDelay(5); 
				if(!wantExit())	break;
			}
	}

	
	for(i=0;i<550;i++)	
	{	
			while(lazePhaiValue > 168)	
			{	
				Bam_laser_sau(6,0,-900, vitri, 1, 150, 10);
				vTaskDelay(5); 
				if(!wantExit())	break;
			}
	}	

		robotStop(0);

	// do chan len dat qua
		su_dung_chan(467);
		for(i=0;i<150;i++)		
	{
		while(abs(bientrochansauValue - target_chan_sau) > 8)	{vTaskDelay(1); if(!wantExit())	break;}
	}
	vTaskDelay(2000);
	Tay2_len;
	for(i=0;i<50;i++)	{ 
							while(CB_xilanh_tay_2 == 1 )	{vTaskDelay(1); if(!wantExit())	break;}
					}
	Tay1_len;
	for(i=0;i<50;i++)	{ 
							while(CB_xilanh_tay_1 == 1 )	{vTaskDelay(1); if(!wantExit())	break;}
					}
	robotStop(0);
}


void dat_qua_tay_1_2_do(void) {
	if (CB_kep_1_2 == 0) {
		speed_tay_gat1 = 250;
		target_tay_gat1 = vitri_tay1home + 110;
	
		for(i=0;i<50;i++)	{ 
		while(abs(bientrodaytay1Value - target_tay_gat1) > (10) || abs(bientrodaytay2Value - target_tay_gat2) > 10 )	
		{vTaskDelay(1); if(!wantExit())	break;}
		}
		vTaskDelay(3000);
		Kep_phai_1_ra;
	}
	
	if (CB_kep_2_2 == 0) {
			speed_tay_gat2 = 250;
			target_tay_gat2 = vitri_tay2home + 110;
				
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


void dat_hop_vao_o_do (void) {
		if (tin_hieu_dat_hop_3_4 == 1 ) {
				dat_qua_tay_4_3_do();
		}
		else if (tin_hieu_dat_hop_1_2 == 1 ) {
				dat_qua_tay_1_2_do();
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
    action_table[2][10][1] = qua_trai_len_bac_400_do; // chua test
    action_table[2][10][2] = qua_trai_len_bac_200_cua_vao_do;

//	    /* =========================================
//		
//       move 3 , action 10 sang phai o ria rung
//       ========================================= */
    action_table[3][10][2] = qua_phai_len_bac_200_cua_vao_do;
    action_table[3][10][3] = qua_phai_len_bac_400_do;   // chua test

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
		action_table[0][2][5] = Lay_ben_trai_bac_200_tren_do_5_6; 
		action_table[0][2][6] = Lay_ben_trai_bac_200_tren_do_5_6; 	
		action_table[0][2][8] =	Lay_ben_trai_bac_200_tren_do_7_10;	
		action_table[0][2][11]= Lay_ben_trai_bac_200_tren_do_7_10;	
	

		action_table[0][2][9]  = Lay_ben_trai_bac_200_duoi_do_8_11;		
		action_table[0][2][12] = Lay_ben_trai_bac_200_duoi_do_8_11;		

//    /* =========================================
//       move 0 , action 3, dung lai de lay ben PHAI
//       ========================================= */
		action_table[0][3][4] = Lay_ben_phai_bac_200_duoi_do_5; 
		action_table[0][3][5] = Lay_ben_phai_bac_200_duoi_do_6;  
		action_table[0][3][7] =  Lay_ben_phai_bac_200_duoi_do_8;  
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
//		action_table[2][4][1] = qua_trai_len_bac;

		/* =========================================
//   move 3 , action 4,chay ben phai
//   ========================================= */
//    action_table[3][4][2] = qua_phai_xuong_bac;
}

///* ================= RUN TU DONG ================= */
//void Run_All_Blocks_From_Queue_san_do(void)
//{
//     Packet_t pkt;

//    if (count_data_uart4 == 0)
//        return;

//    while (count_data_uart4 > 0)
//    {
//        /* luôn nhìn tru?c 1 block tru?c khi pop */
//        Check_Next1_Block_For_Prepare();

//        if (!Queue_Pop(&pkt))
//            break;

//        if (pkt.move < MAX_MOVE &&
//            pkt.action < MAX_ACTION &&
//            pkt.id_block < MAX_ID)
//        {
//            action_table[pkt.move][pkt.action][pkt.id_block]();
//        }
//						vTaskDelay(5000);
//				
//    }

//    has_active_block = 0;
//}


///* ================= RUN BAN TU DONG ================= */
void Run_All_Blocks_From_Queue_san_do(void)
{
       Packet_t pkt;

    if (count_data_uart4 == 0)
        return;

    /* nhìn truoc 1 block */
    Check_Next1_Block_For_Prepare();

    if (Queue_Pop(&pkt))
    {
        if (pkt.move < MAX_MOVE &&
            pkt.action < MAX_ACTION &&
            pkt.id_block < MAX_ID)
        {	
            action_table[pkt.move][pkt.action][pkt.id_block]();
        }
    }

    has_active_block = 0;

}

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
		while(quangTroValue > 50)	{	
		vTaskDelay (1);
		if(!wantExit())	break;
					}
	}
	
	Tay_kep_mo;
	vTaskDelay (35000);
	da_lay_vk = 1;

}
void tudonghoantoan_san_do(void) {
	// toi lay vk
		Xuat_Phat_Lay_Vu_Khi_Do(161,1650,296) ;
	// cho rb1 lay vk xong thì vuot rung
		mo_vk_san_do();
	
		if ( da_lay_vk == 1)	{	
				Run_All_Blocks_From_Queue_san_do();
	}
	// len dat hop
		if (hoan_thanh_chay_rung == 1 ) DatKFS_do(105),hoan_thanh_chay_rung = 2 ;
		if (hoan_thanh_chay_rung== 2  ) dat_hop_vao_o_do(),hoan_thanh_chay_rung = 3;
		if (hoan_thanh_chay_rung== 3	) chuan_bi_dat_tang_3_do(),hoan_thanh_chay_rung = 4;
		if (hoan_thanh_chay_rung== 4	) dat_full_tang_2_do(),hoan_thanh_chay_rung = 5;

}

void retry_san_do(void) {
	// toi lay vk

		Run_All_Blocks_From_Queue_san_do();
	// len dat hop
		if (hoan_thanh_chay_rung == 1 ) DatKFS_do(106),hoan_thanh_chay_rung = 2 ;
		if (hoan_thanh_chay_rung== 2  ) dat_hop_vao_o_do(),hoan_thanh_chay_rung = 3;
		if (hoan_thanh_chay_rung== 3	) chuan_bi_dat_tang_3_do(),hoan_thanh_chay_rung = 4;
		if (hoan_thanh_chay_rung== 4	) dat_full_tang_2_do(),hoan_thanh_chay_rung = 5;

}



