//// *********************  HAM GOI RA DE DUNG ********************************
void chinh_lai_vi_tri_VK_do(int vitri, int gia_tri_lap);
void chinh_lai_vi_tri_laser_trai_do(int vitri, int gia_tri_lap);
void chinh_lai_vi_tri_laser_phai_do(int vitri, int gia_tri_lap);
void chinh_lai_vi_tri_laser_trai_custom_do(int vitri, int gia_tri_lap);
void chinh_lai_vi_tri_laser_phai_custom_do(int vitri, int gia_tri_lap,int min_toc, int max_toc);

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

void kiem_tra_qua_tay_nao_do (void);

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
				Nang_cuc_nhanh();
				target_chan_truoc = 612, target_chan_sau =615;
				for(i=0;i<50;i++)		
				{
				while(bientrochantruocValue < 470)	{
				Bam_thanh_laser_trai(30,0,0,vu_khi,1,-100,15);
				vTaskDelay(1); 
				if(!wantExit())	break;}
				}
	
				for(i=0;i<250;i++)
				{
					while(lazeTruocValue > 27)	
					{	
	
						Bam_thanh_laser_trai(23,0,0,vu_khi - 1,1,-80,15);
						vTaskDelay(1); 
						if(!wantExit())	break;
					}
				}
				
			
				for(i=0;i<100;i++)
				{
					while(HT_1 == 0 && HT_2 == 0)	
					{			
						if(lazeTruocValue < 14)	Tay_kep_xuong;
						Bam_thanh_laser_trai(7,0,0,vu_khi,1,-50,15);
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
						if	(CB_tay_kep_vk_T == 1) robotRun(870,6);
						else if 	(CB_tay_kep_vk_P == 1) robotRun(-870,6);
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
			
				speed_chan_sau =35;
				speed_chan_truoc = 80;
				
				target_chan_truoc = 650, target_chan_sau = 650;
				
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

				robotRotate(920,1,0);
							
				Nang_cuc_nhanh();
				
				while(_robotIMUAngle < 750)	
				{
					vTaskDelay (5); 
					if(!wantExit())	break;
					if(_robotIMUAngle > 450)		target_chan_truoc = 265, target_chan_sau = 265;
				}

				robotRunAngle(-900,7,900,0.5);
				
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
				
				robotRunAngle(-900,5,900,0.5);
				
				vTaskDelay(3000);
				
				
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
			chinh_lai_vi_tri_laser_phai_custom_do(vi_tri_cua_rung_do_3_lazer_phai_tay_41  , 1000, 5, 65);
	}
	else if (TinHieu_ChuanBi_GapThang == 0) {
			chinh_lai_vi_tri_laser_phai_custom_do(vi_tri_cua_rung_do_3_lazer_phai_tay_41 - 15 , 1000, 5, 65);
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
			chinh_lai_vi_tri_laser_phai_custom_do(vi_tri_cua_rung_do_2_lazer_phai_tay_41 , 1000, 5,  65);
	}
	else if (TinHieu_ChuanBi_GapThang == 0) {
			chinh_lai_vi_tri_laser_phai_custom_do(vi_tri_cua_rung_do_2_lazer_phai_tay_41 - 15 , 1000, 5, 65);
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

	
	vTaskDelay(2000);

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
				

	if (TinHieu_ChuanBi_GapThang == 1) {
			chinh_lai_vi_tri_laser_phai_custom_do(vi_tri_cua_rung_do_1_lazer_phai_tay_41 , 1000, 5, 65);
	}
	else if (TinHieu_ChuanBi_GapThang == 0) {
			chinh_lai_vi_tri_laser_phai_custom_do(vi_tri_cua_rung_do_1_lazer_phai_tay_41 - 15 , 1000,5, 65);
	}
	
		if (block_pha == 1) {
	SEND_UART (4,1);
		}
	else {
		co_vat_can = 0 ;
	}
	
	robotStop(0); 	
				
}

void Vao_rung_mai_3_do(int vitri){
			//		// Do chan len 1 nua
		Nang_cuc_nhanh();
		
		target_chan_truoc = Min_chan_truoc + 250;
		target_chan_sau = Min_chan_sau + 250;
	
		robotRunAngle(900,40,-900,0.6);
		for(i=0;i<250;i++)
					{
						while(lazeSauValue > 115)	
						{	
							vTaskDelay (1);
							if(!wantExit())	break;
						}
				}
					// chuan bi tay xuong truoc
	if (TinHieu_ChuanBi_GapThang == 1) {
				Kep_phai_4_ra;
				speed_tay_gat2 = 250;
				target_tay_gat2 = Min_tay_gat2 + 120;	
	}
		robotRunAngle(900,32,-900,0.5);
		for(i=0;i<250;i++)
					{
						while(lazeSauValue > 50)	
						{	
							vTaskDelay (1);
							if(!wantExit())	break;
						}
				}
			
		su_dung_chan(700);

	if (TinHieu_ChuanBi_GapThang == 0) {
				for(i=0;i<250;i++)
					{
						while(lazeSauValue > 10)	
						{	
							Bam_thanh_laser_phai(20,900,-900,vitri - 15,2,-150,10);
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
					vTaskDelay (1000);
				chinh_lai_vi_tri_laser_phai_do(vitri - 15, 1000);
	}
	else if (TinHieu_ChuanBi_GapThang == 1) {
				for(i=0;i<250;i++)
					{
						while(lazeSauValue > 10)	
						{	
							Bam_thanh_laser_phai(20,900,-900,vitri ,2,-150,10);
							vTaskDelay (1);
							if(!wantExit())	break;
						}
				}
			Tay2_len;
					
			for(i=0;i<1550;i++)
							{
									while( CB_vtri_leo == 1 ||CB_Ha_Sau == 1 || CB_Cap_Thanh_Sau == 0)	
								{	
									Bam_thanh_laser_phai(10,900,-900,vitri ,2,-150,10);
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
	
	robotRunAngle(900,40,-900,0.5);
	for(i=0;i<250;i++)
				{
					while(lazeSauValue > 115)	
					{	
						vTaskDelay (1);
						if(!wantExit())	break;
					}
			}
		
					// chuan bi tay xuong truoc
	if (TinHieu_ChuanBi_GapThang == 1) {
				Kep_phai_4_ra;
				speed_tay_gat2 = 250;
				target_tay_gat2 = Min_tay_gat2 + 120;	
	}
	robotRunAngle(900,32,-900,0.5);
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
						chinh_lai_vi_tri_laser_phai_do(vitri - 15, 1000);
	}
	else if (TinHieu_ChuanBi_GapThang == 1) {
					su_dung_chan(565);	
					for(i=0;i<250;i++)
					{
						while(lazeSauValue > 10 || (abs(bientrochansauValue - target_chan_sau) > 20))	
						{	
							Bam_thanh_laser_phai(20,900,-900,vitri ,2,-150,10);
							vTaskDelay (1);
							if(!wantExit())	break;
						}
					}				
					Tay2_len;		
					for(i=0;i<1550;i++)
							{
								while(CB_Ha_Sau == 1 || CB_Cap_Thanh_Sau == 0)	
								{	
									Bam_thanh_laser_phai(10,900,-900,vitri,2,-150,10);
									if(!wantExit())	break;
									vTaskDelay (1);
								}
							}
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
	
		robotRunAngle(900,40,-900,0.9);
		for(i=0;i<250;i++)
					{
						while(lazeSauValue > 115)	
						{	
							vTaskDelay (1);
							if(!wantExit())	break;
						}
				}
					// chuan bi tay xuong truoc
	if (TinHieu_ChuanBi_GapThang == 1) {
				Kep_phai_4_ra;
				speed_tay_gat2 = 250;
				target_tay_gat2 = Min_tay_gat2 + 120;	
	}
		robotRunAngle(900,30,-900,0.9);
		for(i=0;i<250;i++)
					{
						while(lazeSauValue > 50)	
						{	
							vTaskDelay (1);
							if(!wantExit())	break;
						}
				}
					
		su_dung_chan(700);

	if (TinHieu_ChuanBi_GapThang == 0) {
					for(i=0;i<250;i++)
					{
						while(lazeSauValue > 10)	
						{	
							Bam_thanh_laser_trai(20,900,-900,vitri + 25,2,150,10);
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
					vTaskDelay (1000);
				chinh_lai_vi_tri_laser_trai_do(vitri + 25, 1000);
	}
	else if (TinHieu_ChuanBi_GapThang == 1) {
				for(i=0;i<250;i++)
					{
						while(lazeSauValue > 10)	
						{	
							Bam_thanh_laser_trai(20,900,-900,vitri ,2,150,30);
							vTaskDelay (1);
							if(!wantExit())	break;
						}
				}
					Tay2_len;
					for(i=0;i<1550;i++)
							{
									while( CB_Ha_Sau == 1 || CB_Cap_Thanh_Sau == 0)	
								{	
									Bam_thanh_laser_trai(10,900,-900,vitri ,2,150,30);
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

/// ham chay tat len san do
void chinh_lai_vi_tri_laser_trai_zone3_do(int vitri, int gia_tri_lap) {
	int speed ;
	int dieuchinh;
		for(i=0;i<gia_tri_lap;i++)
				{
		while(abs(lazeTraiValue - vitri) > 1)	{
			dieuchinh = lazeTraiValue - vitri;
			speed = custom_smooth_speed(dieuchinh, 4, 42);
			
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
	
	Nang_cuc_nhanh();
	target_chan_truoc = 335;
	target_chan_sau = 335;
	
	for(i=0;i<150;i++)		
	{
		while(abs(bientrochansauValue - target_chan_sau) > 10)	{vTaskDelay(1); if(!wantExit())	break;}
	}
	vTaskDelay(4000); 
	
	chinh_lai_vi_tri_laser_trai_zone3_do(210, 1000);
	

		robotRunAngle(900,30,-900,0.5);
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
		
	robotRunAngle(900,10,-900,0.5);
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
			while(lazePhaiValue > 440)	
			{	
				Bam_laser_sau(30,0,-900, vitri, 3, 100, 10);
				vTaskDelay(1); 
				if(!wantExit())	break;
			}
	}
	
	robotRunAngle(-100,25,900,1.5);
			
	while(_robotIMUAngle < 810)	
	{
		vTaskDelay (1); 
		if(!wantExit())	break;
	}
				
	
	for(i=0;i<550;i++)	
	{	
			while(lazeTraiValue > 220)	
			{	
				Bam_laser_truoc(25,0,900, vitri + 32, 3, 300, 10);
				vTaskDelay(5); 
				if(!wantExit())	break;
			}
	}
	for(i=0;i<550;i++)	
	{	
			while(lazeTraiValue > 190)	
			{	
				Bam_laser_truoc(6,0,900, vitri + 32, 2, 150, 10);
				vTaskDelay(1); 
				if(!wantExit())	break;
			}
	}


		robotStop(0);

	// xoay qua de be
		robotRotate(895,0.2, 0);
		while(robotFixAngle()){
					vTaskDelay (1); 
					if(!wantExit())	break;
				}
		robotStop(0);


	// do chan len dat qua
		su_dung_chan(700);
		for(i=0;i<150;i++)		
		{
			while(abs(bientrochansauValue - target_chan_sau) > 8)	{vTaskDelay(1); if(!wantExit())	break;}
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
		action_table[0][3][7] = Lay_ben_phai_bac_200_duoi_do_8;  
		action_table[0][3][8] = Lay_ben_phai_bac_200_tren_do_9;   
		
		action_table[0][3][10] = Lay_ben_phai_bac_200_duoi_do_8;  
		action_table[0][3][11]= Lay_ben_phai_bac_200_tren_xanh_11; 
				
    /* =========================================
       move 1 , action 4 chay thang
       ========================================= */
    action_table[1][4][1] = Leo_bac_400_ko_thanh_do;  //
    action_table[1][4][2] = Leo_bac_200_bam_thanh_phai_do;  //
		action_table[1][4][3] = Leo_bac_400_co_thanh_do; //
		action_table[1][4][4] = Xuong_bac_200_do_4;	 //  
    action_table[1][4][5] = Leo_bac_200_do_5;		 //
    action_table[1][4][6] = Leo_bac_200_ko_thanh_do;//
    action_table[1][4][7] = Leo_bac_200_do_7;   //
    action_table[1][4][8] = Leo_bac_200_ko_thanh_do;  //
    action_table[1][4][9]  = Xuong_bac_200_do_9; 	//	
    action_table[1][4][10] = xuong_bac_200_do_10;  //
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
		while(quangTroValue > 100)	{	
		vTaskDelay (1);
		if(!wantExit())	break;
					}
	}
	
	Tay_kep_mo;
	
	vTaskDelay (8000);
	
	for(i=0;i<1000;i++)	
	{
		while(quangTroValue < 130)	{	
		vTaskDelay (1);
		if(!wantExit())	break;
		}
	}
	vTaskDelay (8000);
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
void retry_zone_3_o_1_2_do(int vitri) {
		kiem_tra_qua_tay_nao_do(); // ham kiem tra co qua tay nao de dat
		
		robotRunAngle(900, 35, 0, 0.5);
		for(i=0;i<550;i++)	
		{	
				while(lazePhaiValue > 450)	
				{	
					vTaskDelay(1); 
					if(!wantExit())	break;
				}
		}
//		
		for(i=0;i<550;i++)	
	{	
			while(lazePhaiValue > 330)	
			{	
				Bam_laser_sau(25,900,0, vitri, 2, 350, 10);
				vTaskDelay(5); 
				if(!wantExit())	break;
			}
	}
		
		for(i=0;i<550;i++)	
	{	
			while(lazePhaiValue > 200)	
			{	
				Bam_laser_sau(15,900,0, vitri, 2, 150, 10);
				vTaskDelay(5); 
				if(!wantExit())	break;
			}
	}
		//			// do chan len dat qua
		su_dung_chan(455);
	
		for(i=0;i<550;i++)	
	{	
			while(lazePhaiValue > 171)	
			{	
				Bam_laser_sau(5,900,0, vitri, 2, 150, 10);
				vTaskDelay(5); 
				if(!wantExit())	break;
			}
	}
		robotStop(0);

	if (tin_hieu_dat_hop_3_4 == 1 && CB_kep_4_2 == 0 ) {
			Tay2_len;
			for(i=0;i<50;i++)	{ 
									while(CB_xilanh_tay_2 == 1 )	{vTaskDelay(1); if(!wantExit())	break;}
							}
						}
	else if (tin_hieu_dat_hop_3_4 == 1 && CB_kep_3_2 == 0 ) {
			Tay1_len;
			for(i=0;i<50;i++)	{ 
									while(CB_xilanh_tay_2 == 1 )	{vTaskDelay(1); if(!wantExit())	break;}
							}
						}
	
	else if (tin_hieu_dat_hop_1_2 == 1 && CB_kep_1_2 == 0 ) {
			Tay1_len;
			for(i=0;i<50;i++)	{ 
									while(CB_xilanh_tay_1 == 1 )	{vTaskDelay(1); if(!wantExit())	break;}
							}
						}
	else if (tin_hieu_dat_hop_1_2 == 1 && CB_kep_2_2 == 0 ) {
			Tay2_len;
			for(i=0;i<50;i++)	{ 
									while(CB_xilanh_tay_1 == 1 )	{vTaskDelay(1); if(!wantExit())	break;}
							}
						}
	robotStop(0);
}

void retry_zone_3_o_3_do(int vitri) {
		kiem_tra_qua_tay_nao_do(); // ham kiem tra co qua tay nao de dat
		
		robotRunAngle(900, 35, 0, 0.3);
		for(i=0;i<550;i++)	
		{	
				while(lazePhaiValue > 460)	
				{	
					vTaskDelay(1); 
					if(!wantExit())	break;
				}
		}
		
		for(i=0;i<550;i++)	
		{	
				while(lazePhaiValue > 330)	
				{	
					Bam_laser_sau(30,900,0, vitri, 3, 350, 10);
					vTaskDelay(5); 
					if(!wantExit())	break;
				}
		}
		
		for(i=0;i<550;i++)	
	{	
			while(lazePhaiValue > 210)	
			{	
				Bam_laser_sau(15,900,0, vitri, 2, 150, 10);
				vTaskDelay(5); 
				if(!wantExit())	break;
			}
	}
				// do chan len dat qua
		su_dung_chan(455);
		for(i=0;i<550;i++)	
	{	
			while(lazePhaiValue > 171)	
			{	
					Bam_laser_sau(5,900,0, vitri, 2, 100, 10);
				vTaskDelay(1); 
				if(!wantExit())	break;
			}
	}
		robotStop(0);

	robotStop(0);
	if (tin_hieu_dat_hop_3_4 == 1 && CB_kep_4_2 == 0 ) {
			Tay2_len;
			for(i=0;i<50;i++)	{ 
									while(CB_xilanh_tay_2 == 1 )	{vTaskDelay(1); if(!wantExit())	break;}
							}
						}
	else if (tin_hieu_dat_hop_3_4 == 1 && CB_kep_3_2 == 0 ) {
			Tay1_len;
			for(i=0;i<50;i++)	{ 
									while(CB_xilanh_tay_2 == 1 )	{vTaskDelay(1); if(!wantExit())	break;}
							}
						}
	
	else if (tin_hieu_dat_hop_1_2 == 1 && CB_kep_1_2 == 0 ) {
			Tay1_len;
			for(i=0;i<50;i++)	{ 
									while(CB_xilanh_tay_1 == 1 )	{vTaskDelay(1); if(!wantExit())	break;}
							}
						}
	else if (tin_hieu_dat_hop_1_2 == 1 && CB_kep_2_2 == 0 ) {
			Tay2_len;
			for(i=0;i<50;i++)	{ 
									while(CB_xilanh_tay_1 == 1 )	{vTaskDelay(1); if(!wantExit())	break;}
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
		if (id_dat_hop == 1) { retry_zone_3_o_1_2_do(110);}
		else if (id_dat_hop == 2) { retry_zone_3_o_1_2_do(56);}
		else if (id_dat_hop == 3) { retry_zone_3_o_3_do(1);}
		dat_hop_vao_o_do();

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
			su_dung_chan(710);
			vTaskDelay (5000);

		}

void xac_dinh_vi_tri_robot_do(void) {
    kiem_tra_so_qua_tren_tay();

    // ================= TRUONG HOP TAY 1 HOAC TAY 4 CO QUA =================
    if (tay_1_co_qua || tay_4_co_qua) {
        // Vi tri 3: lz truoc (0 - 18), lz sau (136 - 162)
        if ((lazeTruocValue >= 0 && lazeTruocValue <= 18) && 
            (lazeSauValue >= 136 && lazeSauValue <= 162)) {
            robot_position = 3;
        }
        // Vi tri 2: lz truoc (34 - 70), lz sau (86 - 120)
        else if ((lazeTruocValue >= 34 && lazeTruocValue <= 70) && 
                 (lazeSauValue >= 86 && lazeSauValue <= 120)) {
            robot_position = 2;
        }
        // Vi tri 1: lz truoc (87 - 126), lz sau (27 - 67)
        else if ((lazeTruocValue >= 87 && lazeTruocValue <= 126) && 
                 (lazeSauValue >= 27 && lazeSauValue <= 67)) {
            robot_position = 1;
        }
        // Logic du phong: tinh khoang cach toi tam cua cac vung
        else {
            long dist3 = abs(lazeTruocValue - 9)   + abs(lazeSauValue - 149); // Tam cua (0-18) va (136-162)
            long dist2 = abs(lazeTruocValue - 52)  + abs(lazeSauValue - 103); // Tam cua (34-70) va (86-120)
            long dist1 = abs(lazeTruocValue - 106) + abs(lazeSauValue - 47);  // Tam cua (87-126) va (27-67)
            
            if (dist3 <= dist2 && dist3 <= dist1) robot_position = 3;
            else if (dist2 <= dist3 && dist2 <= dist1) robot_position = 2;
            else robot_position = 1;
        }
    }
    
    // ================= TRUONG HOP TAY 2 HOAC TAY 3 CO QUA =================
    else if (tay_2_co_qua || tay_3_co_qua) {
        // Vi tri 3: lz truoc (24 - 62), lz sau (95 - 133)
        if ((lazeTruocValue >= 24 && lazeTruocValue <= 62) && 
            (lazeSauValue >= 95 && lazeSauValue <= 133)) {
            robot_position = 3;
        }
        // Vi tri 2: lz truoc (77 - 112), lz sau (44 - 79)
        else if ((lazeTruocValue >= 77 && lazeTruocValue <= 112) && 
                 (lazeSauValue >= 44 && lazeSauValue <= 79)) {
            robot_position = 2;
        }
        // Vi tri 1: lz truoc (133 - 162), lz sau (0 - 23)
        else if ((lazeTruocValue >= 133 && lazeTruocValue <= 162) && 
                 (lazeSauValue >= 0 && lazeSauValue <= 23)) {
            robot_position = 1;
        }
        // Logic du phong
        else {
            long dist3 = abs(lazeTruocValue - 43)  + abs(lazeSauValue - 114);
            long dist2 = abs(lazeTruocValue - 94)  + abs(lazeSauValue - 61);
            long dist1 = abs(lazeTruocValue - 147) + abs(lazeSauValue - 11);
            
            if (dist3 <= dist2 && dist3 <= dist1) robot_position = 3;
            else if (dist2 <= dist3 && dist2 <= dist1) robot_position = 2;
            else robot_position = 1;
        }
    }
}


void tu_dong_dat_tang2_do(void) {
		robotRotate(860,0.3, 0);
		while(robotFixAngle()){
					vTaskDelay (1); 
					if(!wantExit())	break;
				}
		kiem_tra_so_qua_tren_tay();
		xac_dinh_vi_tri_robot_do();

		if (tay_1_co_qua || tay_4_co_qua) {
        if (robot_position == 3) {
            chinh_lai_vi_tri_laser_sau(160, 100);
            robotStop(0);
            chinh_lai_vi_tri_laser_trai(168, 1000);
        } 
        else if (robot_position == 2) {
            chinh_lai_vi_tri_laser_sau(107, 100);
            robotStop(0);
            chinh_lai_vi_tri_laser_trai(168, 1000);
        } 
        else if (robot_position == 1) {
            chinh_lai_vi_tri_laser_sau(54, 100);
            robotStop(0);
            chinh_lai_vi_tri_laser_trai(168, 1000);
        }
    } 
    else if (tay_2_co_qua || tay_3_co_qua) {
        if (robot_position == 3) {
            chinh_lai_vi_tri_laser_sau(133, 100);
            robotStop(0);
            chinh_lai_vi_tri_laser_trai(168, 1000); /// trg hop tay 3 vi trí 1
        } 
        else if (robot_position == 2) {
            chinh_lai_vi_tri_laser_sau(95, 100);
            robotStop(0);
            chinh_lai_vi_tri_laser_trai(168, 1000);
        } 
        else if (robot_position == 1) {
            chinh_lai_vi_tri_laser_sau(79, 100);
            robotStop(0);
            chinh_lai_vi_tri_laser_trai(168, 1000);
        }
    }
		
			robotStop(0);
			// do chan len dat
			su_dung_chan(510);
			for(i=0;i<250;i++)	{
				while(abs(bientrochansauValue - target_chan_sau) > 10)	{ vTaskDelay(1); if(!wantExit())	break;}
					}		
			dat_hop_vao_o_tang2();
			
}


void tudonghoantoan_san_do(void) {
	// toi lay vk
		Xuat_Phat_Lay_Vu_Khi_Do(161,1600,283) ;
	// cho rb1 lay vk xong thì vuot rung
		mo_vk_san_do();
	
		if ( da_lay_vk == 1)	{	
				Run_All_Blocks_From_Queue_san_do();
	}
	// len dat hop
		if (hoan_thanh_chay_rung == 1 ) DatKFS_do(18),hoan_thanh_chay_rung = 2 ;
		if (hoan_thanh_chay_rung== 2  ) quyet_dinh_dat_hop_tang3(),hoan_thanh_chay_rung = 3;
		if (hoan_thanh_chay_rung== 3	) tu_dong_dat_tang2_do(),hoan_thanh_chay_rung = 4;
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


void retry_zone2_do(void) {
	// toi lay vk
		retry_co_qua_tren_tay();
		Run_All_Blocks_From_Queue_san_do();
	// len dat hop
//		if (hoan_thanh_chay_rung == 1 ) DatKFS_do(110),hoan_thanh_chay_rung = 2 ;
//		if (hoan_thanh_chay_rung== 2  ) be_len_dat_xanh(),hoan_thanh_chay_rung = 3;
//		if (hoan_thanh_chay_rung== 3	) tu_dong_dat_tang2_do(),hoan_thanh_chay_rung = 4;

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
        robotRun(900, 9);
				RESET_ENCODER(); 
				while(abs(ENCODER_FR()) + abs(ENCODER_FL()) < encoder_target)	{vTaskDelay (5); if(!wantExit())	break;}
    }
    else if (do_lech > 102)
    {
        // lech phai chay phai
        robotRun(-900, 9);
				RESET_ENCODER(); 
				while(abs(ENCODER_RR()) + abs(ENCODER_RL()) < encoder_target)	{vTaskDelay (5); if(!wantExit())	break;}
    }
		else {
				robotStop(0);
		}
}

void chinh_lai_vi_tri_laser_phai_zone3_do(int vitri, int gia_tri_lap)
{
	int speed ;
	int dieuchinh;
		for(i=0;i<gia_tri_lap;i++)
				{
		while(abs(lazePhaiValue - vitri) > 1)	{
			dieuchinh = lazePhaiValue - vitri;
			speed = smooth_speed(dieuchinh);
			
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
				chinh_lai_vi_tri_laser_phai_zone3_do(208, 200);
			}
		else if (nhat_dat_hop == 2) {
				chinh_lai_vi_tri_laser_phai_zone3_do(255, 200);
			}
		else if (nhat_dat_hop == 3) {
				chinh_lai_vi_tri_laser_phai_zone3_do(302, 200);
			}

			robotStop(0);
		if (nhat_dat_hop == 1|| nhat_dat_hop == 2 || nhat_dat_hop == 3) {
				Tay2_len;
				for(i=0;i<50;i++)	{ 
									while(CB_xilanh_tay_2 == 1 )	{vTaskDelay(1); if(!wantExit())	break;}
							}
				su_dung_chan(490);
				chinh_lai_vi_tri_laser_sau_zone3(5, 1000);
				robotStop(0);
				dat_hop4_2(485, 345,35, 4);	
				}
		
		// chon be tang 3
			if (nhat_dat_hop == 4 ||nhat_dat_hop == 5 || nhat_dat_hop == 6  ) {
				robotRotate(-900,0.5,0);
				while(robotFixAngle()){
					vTaskDelay (1); 
					if(!wantExit())	break;
				}
				robotStop(0);
				su_dung_chan(710);
				quyet_dinh_dat_hop_tang3();
			}
}			



void nhat_hop_zone3_do (void) {
		su_dung_chan(350);
		robotRunAngle(1800, 35, 0, 0.5);
		for(i=0;i<550;i++)	
		{	
				while(lazeSauValue > 350)	
				{	
					vTaskDelay(1); 
					if(!wantExit())	break;
				}
		}
		
		robotRunAngle(1800, 25, 0, 0.5);
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
		
		su_dung_chan(430);
		Kep_phai_4_ra;
		speed_tay_gat2 = 250;
		target_tay_gat2 = 170;
		
		robotRunAngle(1800, 20, 0, 0.5);
		for(i=0;i<550;i++)	
		{	
				while(lazeSauValue > 130)	
				{	
					vTaskDelay(1); 
					if(!wantExit())	break;
				}
		}		
		for(i=0;i<5000;i++)	
		{	
			run_align_center();
		}
		
		robotRunAngle(1800, 17, 0, 0.5);
		for(i=0;i<550;i++)	
		{	
				while(lazeSauValue > 25)	
				{	
					vTaskDelay(1); 
					if(!wantExit())	break;
				}
		}	
		
		robotRunAngle(1800, 6, 0, 0.5);
		for(i=0;i<550;i++)	
		{	
				while(lazeSauValue > 4)	
				{	
					vTaskDelay(1); 
					if(!wantExit())	break;
				}
		}		
			
				vTaskDelay (1000);
				robotStop(0);
			// chi tracking hop 
				Ktra_vtri_kep4(); 

			speed_tay_gat2 = 250;
			target_tay_gat2 = Min_tay_gat2 +15  ;
			for(i=0;i<550;i++)	{ 

					while(abs(bientrodaytay2Value - target_tay_gat2)> 5 )	
					{vTaskDelay(1); if(!wantExit())	break;}
				}
			
			vTaskDelay (1000);
			Kep_phai_4_vao;
			vTaskDelay (2000);
			speed_tay_gat2 = 250;
			target_tay_gat2 = vitri_tay2home;
			robotRunAngle(0,15,0, 0.5);
			vTaskDelay(7000);
			robotStop(0);

			
//			// lui ra roi chay toi dat o
				chon_o_nhat_hop_do();			
}



void test_xoay (void) {
	robotRotate(900,0.9, 0);
	while(robotFixAngle()){
					vTaskDelay (1); 
					if(!wantExit())	break;
				}

}

void bat_dau_chay_do (void) {
    if (Start == 0 && mode_chay_rung == 1) {
        tudonghoantoan_san_do();
    }
    else if (Start == 0 && mode_chay_rung == 2) {
        retry_zone2_do();
    }
    else if (Start == 0 && mode_nhat_hop == 1) {
        nhat_hop_zone3_do();
    }
}
	
