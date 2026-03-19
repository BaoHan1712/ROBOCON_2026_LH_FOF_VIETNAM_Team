extern int Vi_tri;
extern int da_lay_tay4;
extern int TinHieu_ChuanBi_GapThang;
extern int TinHieu_ChuanBi_GapTrai ;
extern int TinHieu_ChuanBi_GapPhai;


//*************************** XUAT PHAT LAAYS VU KHI 3 ***********************************
void Xuat_Phat_Lay_Vu_Khi_Xanh(int vu_khi, int goc_ve)
 //				RESET_ENCODER(); 
{				
				speed_tay_gat1 = 150;
				target_tay_gat1 = vitri_tay1home;
	
				speed_tay_gat2 = 250;
				target_tay_gat2 = vitri_tay2home;
	
				Nang_cuc_nhanh();
	
				target_chan_truoc = 350, target_chan_sau = 350;
				Kep = 250;
	
				robotRunAngle(-150 - vu_khi*2,30,5,0.3);
				//robotRunAngle(-450,15,5,0.3);
				for(i=0;i<100;i++)
				{
					while(lazePhaiValue < vu_khi - 20)	
					{
						if(!wantExit())	break;
					}
				}

				target_chan_truoc = 615, target_chan_sau =605;
				for(i=0;i<50;i++)		
				{
				while(bientrochantruocValue < 470)	{
				Bam_thanh_laser_phai(25,0,0,vu_khi,1,150,15);
				vTaskDelay(1); 
				if(!wantExit())	break;}
				}
				
				for(i=0;i<250;i++)
				{
					while(lazeTruocValue > 23)	
					{	
	
						Bam_thanh_laser_phai(23,0,0,vu_khi,1,150,15);//robotRun(-450,10);
						if(!wantExit())	break;
					}
				}
//				
				Nang_Ha_Kep = 250;
			
//				
				for(i=0;i<100;i++)
				{
					while(HT_1 == 1 && HT_2 == 1)	
					{				
						Bam_thanh_laser_phai(7,0,0,vu_khi,1,100,15);//robotRun(-450,10);
						if(!wantExit())	break;
					}
				}
//			
				vTaskDelay (3000);
				robotStop(50);
				
				vTaskDelay (2000);
				
				for(i=0;i<500;i++)
				{
					while(CB_tay_kep_vk_T == 1 || CB_tay_kep_vk_P == 1)	
					{	
						if	(CB_tay_kep_vk_P == 1) robotRun(-850,6);
						else if 	(CB_tay_kep_vk_T == 1) robotRun(850,6);
						else		robotStop(0);				
						vTaskDelay (1);
						if(!wantExit())	break;
					}
				}	
				robotStop(0);
				Kep = 0;
				
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
				
				speed_chan_sau =30;
				speed_chan_truoc = 70;
				
				target_chan_truoc = 615, target_chan_sau = 615;
				
				vTaskDelay(4000);
				
				robotStop(30);
				
				target_chan_truoc = 655, target_chan_sau = 630;
				
				Nang_Ha_Kep = 0; 
				
				vTaskDelay(5000);
				
				robotRun(goc_ve,30);
				robotRotate(-900,-1.2,0);
//				
				RESET_ENCODER(); 
//								
				speed_chan_sau =80;
				speed_chan_truoc = 130;
//				
				while(_robotIMUAngle >-750)	
				{
					vTaskDelay (5); 
					if(!wantExit())	break;
					if(_robotIMUAngle < -450)		target_chan_truoc = 250, target_chan_sau = 250;
				}
//				
//				Nang_Ha_Kep = 0; 
					
	
				robotRunAngle(900,8,-900,0.7);
				
				for(i=0;i<100;i++)
				{
					while(HT_3 == 0 && HT_4 == 0)	
					{           
						vTaskDelay (5); 
						if(!wantExit())	break;
					}
				}
				
				speed_chan_sau =20;
				speed_chan_truoc = 45;
				target_chan_truoc = 240, target_chan_sau = 240;
//				
				robotStop(0);
				
			}

//******************** xoay dau detect xem co robot phia truoc hay khong ********************************************
void Xoay_dau_truoc_cua_xanh_1(void)
{
	speed_chan_sau = 15;
	speed_chan_truoc = 60;

	target_chan_truoc = 255;
	target_chan_sau = 255;

	
	vTaskDelay(2000);
	
	Kep_phai_4_ra;

	
	robotRunAngle(-1450,30,900,2);
//				
				while(_robotIMUAngle < 895)	
				{
					vTaskDelay (5); 
					if(!wantExit())	break;
				}
				
	robotStop(0); 
	chinh_lai_vi_tri_laser_phai(vi_tri_cua_rung_xanh_1_lazer_phai_tay_41 , 1000);
	robotStop(0); 	
				
}

void Xoay_dau_truoc_cua_xanh_2 (void)
{
	speed_chan_sau = 15;
	speed_chan_truoc = 60;

	target_chan_truoc = 255;
	target_chan_sau = 255;

	
	vTaskDelay(2000);
	
	Kep_phai_4_ra;

	
	robotRunAngle(-1550,25,900,2);
//				
				while(_robotIMUAngle < 895)	
				{
					vTaskDelay (5); 
					if(!wantExit())	break;
				}
				
	robotStop(0); 
	chinh_lai_vi_tri_laser_phai(vi_tri_cua_rung_xanh_2_lazer_phai_tay_41 , 1000);
	robotStop(0); 	
				
}


/// ********** XOAY DAU TOI CUA XANH 3

void Xoay_dau_truoc_cua_xanh_3 (void)
{
	speed_chan_sau = 15;
	speed_chan_truoc = 60;

	target_chan_truoc = 255;
	target_chan_sau = 255;

	
	vTaskDelay(2000);
	
	Kep_phai_4_ra;

	
	robotRunAngle(-860,25,900,2);
//				
				while(_robotIMUAngle < 895)	
				{
					vTaskDelay (5); 
					if(!wantExit())	break;
				}
				
	robotStop(0); 
	chinh_lai_vi_tri_laser_phai(vi_tri_cua_rung_xanh_3_lazer_phai_tay_41 , 1000);
	robotStop(0); 	
				
}

/// *********** HAM KIEM TRA CO VAT PHIA TRUOC HAY KHÔNG ****************** CO VAT 70. 105 < VAT
void kiem_tra_vat_phia_truoc (int value_lazer_sau, int value_lap) {
			for(i=0;i<value_lap;i++)	
	{
		while(lazeSauValue < value_lazer_sau)	{	
					vTaskDelay (1);
		if(!wantExit())	break;
					}
	}
}


//////////////////////////////////////////////////////////////////////////////
void Vao_rung_mai_1_xanh(int vitri)
{			
	su_dung_chan(500);
				
	for(i=0;i<250;i++)	
	{
		while(bientrochansauValue < 490)
								{	
		Bam_thanh_laser_phai_cua_vao(18,-900,900,vitri,2,450,30);
		if(!wantExit())	break;
					}
		
	}
	
	for(i=0;i<250;i++)
				{
					while(lazeSauValue > 25)	
					{	
						Bam_thanh_laser_phai_cua_vao(20,-900,900,vitri,2,250,30);
						if(!wantExit())	break;
					}
				}
			
	for(i=0;i<250;i++)
				{
					while( CB_vtri_leo == 1 ||CB_Ha_Sau == 1 || CB_Cap_Thanh_Sau == 0)	
					{	
						su_dung_chan(697);
						Bam_thanh_laser_phai_cua_vao(10,-900,900,vitri,2,150,30);
						if(!wantExit())	break;
					}
				}

	vTaskDelay (5); 
	RESET_ENCODER(); 
	
	for(i=0;i<250;i++) {
	while(abs(ENCODER_FR()) + abs(ENCODER_FL()) < 1700)	
		{	
				Bam_thanh_laser_phai_cua_vao(8,-900,900,vitri,2,350,30);
				vTaskDelay (1);
				if(!wantExit())	break;
		}
	}
	robotStop(0); 
	if (TinHieu_ChuanBi_GapThang == 0) {
				chinh_lai_vi_tri_laser_phai(vitri - 5, 1000);
	}
	else if (TinHieu_ChuanBi_GapThang == 1) {
				chinh_lai_vi_tri_laser_phai(vitri, 1000);
	}
	
	
	robotStop(0); 	
	
				
}
//********************************** vao rung mai 2 gap kfs ********************************************
void Vao_rung_mai_2_xanh(int vitri)
{			

	Nang_cuc_nhanh();
	
	target_chan_truoc = 510;
	target_chan_sau = 510;
				
		
 	for(i=0;i<150;i++)		
	{
		while(bientrochansauValue < 500)	
		{
			Bam_thanh_laser_phai(18,-900,900,vitri,2,450,30);
			if(!wantExit())	break;
			vTaskDelay (1);
		}
	}			
				
	for(i=0;i<1550;i++)
				{
					while(CB_Ha_Sau == 1 || CB_Cap_Thanh_Sau == 0)	
					{	
						Bam_thanh_laser_phai(12,-900,900,vitri,2,50,30);
						if(!wantExit())	break;
						vTaskDelay (1);
					}
				}
				
	su_dung_chan(580);
	if (TinHieu_ChuanBi_GapThang == 0) {
				chinh_lai_vi_tri_laser_phai(vitri - 5, 1000);
	}
	else if (TinHieu_ChuanBi_GapThang == 1) {
				chinh_lai_vi_tri_laser_phai(vitri, 1000);
	}
	
	robotStop(0); 			
						
}	

//********************************** vao rung mai 3 gap kfs ********************************************
void Vao_rung_mai_3_xanh(int vitri)
{
		
	Kep_phai_4_ra;			
	kiem_tra_huong_quay_tay_gap_phia_truoc();
	
		// Do chan len 1 nua
		su_dung_chan(500);
				
	for(i=0;i<250;i++)	
	{
		while(bientrochansauValue < 490)
								{	
		Bam_thanh_laser_trai(20,-900,900,vitri,2,350,30);
		if(!wantExit())	break;
					}
		
	}
			
		su_dung_chan(697);
				
		for(i=0;i<1550;i++)
				{
						while( CB_vtri_leo == 1 ||CB_Ha_Sau == 1 || CB_Cap_Thanh_Sau == 0)	
					{	
						
						Bam_thanh_laser_trai(8,-900,900,vitri,2,50,30);
						if(!wantExit())	break;
						vTaskDelay (1);
					}
				}

		RESET_ENCODER(); 
	
	for(i=0;i<250;i++) {
	while(abs(ENCODER_RR()) + abs(ENCODER_RL()) < 1600)	
		{	
				Bam_thanh_laser_trai(8,-900,900,vitri,2,350,30);
				vTaskDelay (1);
				if(!wantExit())	break;
		}
	}
	robotStop(0); 
	if (TinHieu_ChuanBi_GapThang == 0) {
	chinh_lai_vi_tri_laser_trai(vitri + 5, 1000);
	}
	else if (TinHieu_ChuanBi_GapThang == 1) {
	chinh_lai_vi_tri_laser_trai(vitri, 1000);
	}

	robotStop(0); 	
				
}
///////////////////////////////////////////////////////////////
void auto_vao_rung_xanh_cua1(void) {
		Xoay_dau_truoc_cua_xanh_1();
		vTaskDelay (3000);
		kiem_tra_vat_phia_truoc(105,1000);
		Vao_rung_mai_1_xanh(vi_tri_cua_rung_xanh_1_lazer_phai_tay_41);
		
	}


void auto_vao_rung_xanh_cua2(void) {
		Xoay_dau_truoc_cua_xanh_2();
		vTaskDelay (3000);
		kiem_tra_vat_phia_truoc(105,1000);
		Vao_rung_mai_2_xanh(vi_tri_cua_rung_xanh_2_lazer_phai_tay_41);
}

void auto_vao_rung_xanh_cua3(void) {
		Xoay_dau_truoc_cua_xanh_3();
		vTaskDelay (3000);
		kiem_tra_vat_phia_truoc(80,1000);
		Vao_rung_mai_3_xanh(vi_tri_cua_rung_xanh_3_lazer_trai_tay_41);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////

//**************** Xuong_bac_200 ô 4********
void chuan_bi_gap_thang_xanh_4(void) {
		int vitri_tay41 = vitri_tay41_laser_trai_GapQua;
		su_dung_chan(510);
			// chay toi khi laser sau cham 1
			robotRunAngle(-900,8,900,0.5);
			for(i=0;i<250;i++)	
		{
			while(abs(bientrochansauValue - target_chan_sau) > 10)	{vTaskDelay(1); if(!wantExit())	break;}
		}		
		
			for(i=0;i<1550;i++)
					{
						while(CB_Ha_Sau == 1 || CB_vtri_leo == 1 || CB_Cap_Thanh_Sau == 0 )	
						{	
							if(!wantExit())	break;
							vTaskDelay (1);
						}
					}
				
			robotStop(0); 
	// chinh lai vi tri cho tay gap
		if (da_lay_tay1 == 0 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
					robotRunAngle(-900,5,900,0.3);
					vTaskDelay (2000);
					chinh_lai_vi_tri_laser_trai(vitri_tay41, 1000);
					robotStop(0);
						
			}
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
					robotRunAngle(-900,5,900,0.3);
					vTaskDelay (2000);
					chinh_lai_vi_tri_laser_trai(vitri_tay41, 1000);
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
			su_dung_chan(565);
}


void chuan_bi_gap_phai_200_tren_4 (void ) {
	
	if (da_lay_tay1 == 0 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
			chinh_lai_vi_tri_laser_trai(vitri_tay41_laser_trai_GapQua- 3, 200);
			robotRunAngle(-900,5,900,0.5);
					for(i=0;i<150;i++)
					{
						while(lazeSauValue > 31)	
						{	
							vTaskDelay (1);
							if(!wantExit())	break;
						}
					}
					robotRunAngle(0,6,900,0.3);
					vTaskDelay(2000);
						robotStop(0);
			
			su_dung_chan(565);
				for(i=0;i<250;i++)	
			{
				while(abs(bientrochansauValue - target_chan_sau) > 10)	{vTaskDelay(1); if(!wantExit())	break;}
			}		
		}
	else if (da_lay_tay1 == 1 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
			chinh_lai_vi_tri_laser_trai(vitri_tay41_laser_trai_GapQua - 3, 200);
		
			robotRunAngle(-900,5,900,0.5);
					for(i=0;i<150;i++)
					{
						while(lazeSauValue > 31)	
						{	
							vTaskDelay (1);
							if(!wantExit())	break;
						}
					}
					robotRunAngle(0,6,900,0.3);
					vTaskDelay(2000);
						robotStop(0);
			
			su_dung_chan(565);
				for(i=0;i<250;i++)	
			{
				while(abs(bientrochansauValue - target_chan_sau) > 10)	{vTaskDelay(1); if(!wantExit())	break;}
			}		
		}
	else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
			chinh_lai_vi_tri_laser_trai(vitri_tay41_laser_trai_GapQua - 3, 200);
			robotRunAngle(0,6,900,0.3);
			vTaskDelay(2000);
			su_dung_chan(510);
			// chay toi khi laser sau cham 1
			robotRunAngle(-900,8,900,0.5);
				for(i=0;i<250;i++)	
			{
				while(abs(bientrochansauValue - target_chan_sau) > 10)	{vTaskDelay(1); if(!wantExit())	break;}
			}		
			
			for(i=0;i<1550;i++)
						{
							while(CB_Ha_Sau == 1  )	
							{	
								if(!wantExit())	break;
								vTaskDelay (1);
							}
						}
			robotStop(10); 
			
			su_dung_chan(565);
				for(i=0;i<250;i++)	
			{
				while(abs(bientrochansauValue - target_chan_sau) > 10)	{vTaskDelay(1); if(!wantExit())	break;}
			}		
		}
	
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 0) {
			chinh_lai_vi_tri_laser_trai(vitri_tay41_laser_trai_GapQua - 3, 200);
			robotRunAngle(0,6,900,0.3);
			vTaskDelay(2000);
			su_dung_chan(510);
			// chay toi khi laser sau cham 1
			robotRunAngle(-900,8,900,0.5);
				for(i=0;i<250;i++)	
			{
				while(abs(bientrochansauValue - target_chan_sau) > 10)	{vTaskDelay(1); if(!wantExit())	break;}
			}		
			
			for(i=0;i<1550;i++)
						{
							while(CB_Ha_Sau == 1  )	
							{	
								if(!wantExit())	break;
								vTaskDelay (1);
							}
						}
			robotStop(10); 
			su_dung_chan(565);
				for(i=0;i<250;i++)	
			{
				while(abs(bientrochansauValue - target_chan_sau) > 10)	{vTaskDelay(1); if(!wantExit())	break;}
			}		
		}
	
		robotStop(0); 
}

void Xuong_bac_200_xanh_4(void)
{	
	int vitri_tay41 = vitri_tay41_laser_trai_GapQua;

	Xuong_bac_200(-900, 900);		
	
	// KHONG CO TIN HIEU GAP
	if (TinHieu_ChuanBi_GapThang == 0 && TinHieu_ChuanBi_GapTrai == 0 && TinHieu_ChuanBi_GapPhai == 0) {
		su_dung_chan(510);
		robotRunAngle(-900,8,900,0.5);
		for(i=0;i<250;i++)	
	{
		while(abs(bientrochansauValue - target_chan_sau) > 10)	{vTaskDelay(1); if(!wantExit())	break;}
	}		
	
	for(i=0;i<1550;i++)
				{
					while(CB_Ha_Sau == 1  || CB_Cap_Thanh_Sau == 0 )	
					{	
						if(!wantExit())	break;
						vTaskDelay (1);
					}
				}
		su_dung_chan(565);
				
		robotStop(0); 
	}
	// CO LENH GAP THANG
		else if (TinHieu_ChuanBi_GapThang == 1 ) {
				chuan_bi_gap_thang_xanh_4();
				}	
		// CO LENH GAP PHAI
		else if (TinHieu_ChuanBi_GapPhai == 1 ) {
					chuan_bi_gap_phai_200_tren_4();
		}
		
		robotStop(0); 	
}

///////////////////////////////////////////////////////////////////////////////////////////////

/// ****** leo bac 200 o id  5 san xanh
void Leo_bac_200_xanh_5(void)
{	
		int vitri = 153;
		int vitri_tay41 = vitri_tay41_laser_trai_GapQua;
		
		Leo_bac_200(-900, 900);
		
		// KHONG CO TIN HIEU GAP
		if (TinHieu_ChuanBi_GapThang == 0 && TinHieu_ChuanBi_GapTrai == 0 && TinHieu_ChuanBi_GapPhai == 0) {
				su_dung_chan(510);
				robotRunAngle(-900,8,900,0.5);
				for(i=0;i<250;i++)	
			{
				while(abs(bientrochansauValue - target_chan_sau) > 10)	{vTaskDelay(1); if(!wantExit())	break;}
			}		
			for(i=0;i<1550;i++)
						{
							while(CB_Ha_Sau == 1 ||  CB_Cap_Thanh_Sau == 0 )	
							{	
								if(!wantExit())	break;
								vTaskDelay (1);
							}
						}
				su_dung_chan(565);
						
				robotStop(0); 
		}
	// CO LENH GAP THANG
		else if (TinHieu_ChuanBi_GapThang == 1 ) {
				chuan_bi_gap_thang_xanh_4();
				}	
		// CO LENH GAP PHAI
		else if (TinHieu_ChuanBi_GapPhai == 1 ) {
					chuan_bi_gap_phai_200_tren_4();
		}
		
		robotStop(0); 			
}

void chuan_bi_gap_thang_xanh_7(void) {
		int vitri_tay41 = vitri_tay41_laser_trai_GapQua;
		int vitri_tay23 = vitri_tay23_laser_trai_GapQua;
	
		su_dung_chan(265);
		for(i=0;i<50;i++)		
			{
				while(abs(bientrochansauValue - target_chan_sau) > 10)	{vTaskDelay(1); if(!wantExit())	break;}
			}
		robotRunAngle(-900,8,900,0.3);
		for(i=0;i<1550;i++)
				{
						while(CB_vtri_leo == 0 || CB_Ha_Sau == 0)	
					{	
						if(!wantExit())	break;
						vTaskDelay (1);
					}
				}
				
		robotStop(0);
		vTaskDelay (1000);
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


// CHUAN BI GAP PHAI XANH 7 VA 10
void chuan_bi_gap_phai_200_tren_7_10 (void ) {
	
	if (da_lay_tay1 == 0 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {

			chinh_lai_vi_tri_laser_trai(vitri_tay41_laser_trai_GapQua- 3, 200);
			robotRunAngle(0,6,900,0.3);
			vTaskDelay(2000);
			su_dung_chan(565);
				for(i=0;i<250;i++)	
			{
				while(abs(bientrochansauValue - target_chan_sau) > 10)	{vTaskDelay(1); if(!wantExit())	break;}
			}		
		}
	
	else if (da_lay_tay1 == 1 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {

			chinh_lai_vi_tri_laser_trai(vitri_tay41_laser_trai_GapQua - 3, 200);
			robotRunAngle(0,6,900,0.3);
			vTaskDelay(2000);
			su_dung_chan(565);
				for(i=0;i<250;i++)	
			{
				while(abs(bientrochansauValue - target_chan_sau) > 10)	{vTaskDelay(1); if(!wantExit())	break;}
			}		
		}
	
			/// gap lan 3
	else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {		
			su_dung_chan(265);
			for(i=0;i<50;i++)		
				{
					while(abs(bientrochansauValue - target_chan_sau) > 10)	{vTaskDelay(1); if(!wantExit())	break;}
				}
				
			chinh_lai_vi_tri_laser_trai(vitri_tay41_laser_trai_GapQua - 3, 200);
			robotRunAngle(0,6,900,0.3);
			vTaskDelay(2000);
			// chay toi khi mat cam bien sau
			robotRunAngle(-900,8,900,0.1);
			for(i=0;i<250;i++)
					{
						while(CB_Ha_Sau == 0)	
					{	
						vTaskDelay (1);
						if(!wantExit())	break;
					}
				}
			robotStop(10); 
			
			su_dung_chan(565);
				for(i=0;i<250;i++)	
			{
				while(abs(bientrochansauValue - target_chan_sau) > 10)	{vTaskDelay(1); if(!wantExit())	break;}
			}		
		}
	/// gap lan 4
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 0) {
			su_dung_chan(265);
			for(i=0;i<50;i++)		
				{
					while(abs(bientrochansauValue - target_chan_sau) > 10)	{vTaskDelay(1); if(!wantExit())	break;}
				}
			chinh_lai_vi_tri_laser_trai(vitri_tay41_laser_trai_GapQua - 3, 200);
			robotRunAngle(0,6,900,0.3);
			vTaskDelay(2000);

			// chay toi khi mat cam bien sau
			robotRunAngle(-900,8,900,0.1);
			for(i=0;i<250;i++)
					{
						while(CB_Ha_Sau == 0)	
					{	
						vTaskDelay (1);
						if(!wantExit())	break;
					}
				}
			robotStop(10); 
			
			su_dung_chan(565);
				for(i=0;i<250;i++)	
			{
				while(abs(bientrochansauValue - target_chan_sau) > 10)	{vTaskDelay(1); if(!wantExit())	break;}
			}	
		}
	
		robotStop(0); 
}


// ************* leo bac 200 xanh o 7************
void Leo_bac_200_xanh_7(void)  {	
		int vitri_tay41 = vitri_tay41_laser_trai_GapQua;
		int vitri_tay23 = vitri_tay23_laser_trai_GapQua;

		Leo_bac_200(-900, 900);
			
			// KHONG CO TIN HIEU GAP
	if (TinHieu_ChuanBi_GapThang == 0 && TinHieu_ChuanBi_GapTrai == 0 && TinHieu_ChuanBi_GapPhai == 0) {
		su_dung_chan(265);
		for(i=0;i<50;i++)		
			{
				while(abs(bientrochansauValue - target_chan_sau) > 10)	{vTaskDelay(1); if(!wantExit())	break;}
			}
		// chay toi khi mat cam bien sau
		robotRunAngle(-900,8,900,0.3);
		for(i=0;i<1550;i++)
				{
						while(CB_vtri_leo == 0 || CB_Ha_Sau == 0)	
					{	
						if(!wantExit())	break;
						vTaskDelay (1);
					}
				}
				
		robotStop(0);
		vTaskDelay (1000);
			}
	
			// CO TIN HIEU GAP THANG
	else if (TinHieu_ChuanBi_GapThang == 1) {
				chuan_bi_gap_thang_xanh_7();
				}
		// CO TIN HIEU GAP PHAI
	else if (TinHieu_ChuanBi_GapPhai == 1) {
					chuan_bi_gap_phai_200_tren_7_10();
			}
		}

//**************** Xuong_bac_200 xanh ô 9 **************
		
void chuan_bi_gap_thang_xanh_9 (void) {
		int vitri_tay23 = vitri_tay23_phai_laser_GapQua;
		su_dung_chan(265);
		for(i=0;i<50;i++)		
	{
		while(abs(bientrochansauValue - target_chan_sau) > 10)	{vTaskDelay(1); if(!wantExit())	break;}
	}
	
		vTaskDelay(1000);
		// chay toi khi mat cam bien sau
		robotRunAngle(-900,8,900,0.3);
		for(i=0;i<250;i++)
				{
					while(CB_vtri_leo == 0 || CB_Ha_Sau == 0)	
					{	
						vTaskDelay (1);
						if(!wantExit())	break;
					}
				}
				
		robotStop(0);
		vTaskDelay (1000);	
	
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
					vTaskDelay (1000);
						}
			}


void chuan_bi_gap_trai_200_tren (void ) {
	
	if (da_lay_tay1 == 0 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
				su_dung_chan(265);
					for(i=0;i<250;i++)	
				{
					while(abs(bientrochansauValue - target_chan_sau) > 10)	{vTaskDelay(1); if(!wantExit())	break;}
				}	

				// chay toi khi mat cb sau
				robotRunAngle(-900,8,900,0.8);
				for(i=0;i<1550;i++)
							{
								while(CB_Ha_Sau == 0  )	
								{	
									if(!wantExit())	break;
									vTaskDelay (1);
								}
							}
				robotStop(0);
				su_dung_chan(400);
					for(i=0;i<250;i++)	
				{
					while(abs(bientrochansauValue - target_chan_sau) > 8)	{vTaskDelay(1); if(!wantExit())	break;}
				}	
				vTaskDelay(1500);
				
				chinh_lai_vi_tri_laser_phai(vitri_tay23_phai_laser_GapQua, 200);
				robotRunAngle(1800,7,900,0.8);
				vTaskDelay(2500);
				robotStop(0); 
				
				su_dung_chan(565);
					for(i=0;i<250;i++)	
				{
					while(abs(bientrochansauValue - target_chan_sau) > 8)	{vTaskDelay(1); if(!wantExit())	break;}
				}		
		}
	else if (da_lay_tay1 == 1 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
				su_dung_chan(265);
					for(i=0;i<250;i++)	
				{
					while(abs(bientrochansauValue - target_chan_sau) > 10)	{vTaskDelay(1); if(!wantExit())	break;}
				}	 
				// chay toi khi mat cb sau
				robotRunAngle(-900,8,900,0.8);
				for(i=0;i<1550;i++)
							{
								while(CB_Ha_Sau == 0    )	
								{	
									if(!wantExit())	break;
									vTaskDelay (1);
								}
							}
				robotStop(0); 
				su_dung_chan(400);
					for(i=0;i<250;i++)	
				{
					while(abs(bientrochansauValue - target_chan_sau) > 10)	{vTaskDelay(1); if(!wantExit())	break;}
				}
				vTaskDelay(1500);
				
				chinh_lai_vi_tri_laser_phai(vitri_tay23_phai_laser_GapQua, 200);
				robotRunAngle(1800,7,900,0.3);
				vTaskDelay(2500);
				robotStop(0); 
				
				su_dung_chan(565);
					for(i=0;i<250;i++)	
				{
					while(abs(bientrochansauValue - target_chan_sau) > 10)	{vTaskDelay(1); if(!wantExit())	break;}
				}
		}
	else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
				su_dung_chan(400);
					for(i=0;i<250;i++)	
				{
					while(abs(bientrochansauValue - target_chan_sau) > 10)	{vTaskDelay(1); if(!wantExit())	break;}
				}
				vTaskDelay(1500);
				chinh_lai_vi_tri_laser_phai(vitri_tay23_phai_laser_GapQua, 200);
				robotRunAngle(1800,7,900,0.8);
				vTaskDelay(2500);
				su_dung_chan(565);
					for(i=0;i<250;i++)	
				{
					while(abs(bientrochansauValue - target_chan_sau) > 10)	{vTaskDelay(1); if(!wantExit())	break;}
				}		
		}
	
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 0) {
				su_dung_chan(400);
					for(i=0;i<250;i++)	
				{
					while(abs(bientrochansauValue - target_chan_sau) > 10)	{vTaskDelay(1); if(!wantExit())	break;}
				}
				vTaskDelay(2500);
				chinh_lai_vi_tri_laser_phai(vitri_tay23_phai_laser_GapQua, 200);
				robotRunAngle(1800,7,900,0.8);
				vTaskDelay(2500);
				su_dung_chan(565);
					for(i=0;i<250;i++)	
				{
					while(abs(bientrochansauValue - target_chan_sau) > 10)	{vTaskDelay(1); if(!wantExit())	break;}
				}
		}
	
		robotStop(0); 
}


void Xuong_bac_200_xanh_9(void)
{	
		int vitri_tay23 = vitri_tay23_phai_laser_GapQua;
		Xuong_bac_200(-900, 900);
		
		if (TinHieu_ChuanBi_GapThang == 0 && TinHieu_ChuanBi_GapTrai == 0 && TinHieu_ChuanBi_GapPhai == 0) {
				su_dung_chan(265);
				for(i=0;i<50;i++)		
						{
				while(abs(bientrochansauValue - target_chan_sau) > 10)	{vTaskDelay(1); if(!wantExit())	break;}
						}
			
				vTaskDelay(1000);
				// chay toi khi mat cam bien sau
				robotRunAngle(-900,8,900,0.8);
				for(i=0;i<250;i++)
							{
							while( CB_Ha_Sau == 0 ) {	vTaskDelay (1); if(!wantExit())	break;
							}
						}
						
				robotStop(0);
				vTaskDelay (1000);
				}				
	
		else if (TinHieu_ChuanBi_GapThang == 1) {
					chuan_bi_gap_thang_xanh_9();
					}
		else if (TinHieu_ChuanBi_GapTrai == 1) {
					chuan_bi_gap_trai_200_tren();
				}
			robotStop(0);
				
			}

	
void Lay_ben_trai_bac_200_tren_xanh_9(void) {
			ve_home_2_tay();
			Lay_ben_trai_bac_200_tren();
			robotRunAngle(0,8,900,0.8);
			vTaskDelay(3000);
			robotStop(0);
			
	if (TinHieu_ChuanBi_GapThang == 1) {
			chuan_bi_gap_thang_xanh_9();
				}

}


void xuong_bac_200_xanh_12(void) {
		Xuong_bac_200(-900, 900);

		if (TinHieu_ChuanBi_GapTrai == 1) {
					chuan_bi_gap_trai_200_tren();
				}
			robotStop(0);
}



/// *********** ESP chay tu dong***************
/* =====================================================
 *  DISPATCH TABLE: [move][action][block]
 *  input order: move, action, block
 * ===================================================== */

#define MAX_MOVE   30
#define MAX_ACTION 30
#define MAX_ID     13

/* ================= TYPE ================= */

typedef void (*ActionFunc)(void);

/* ================= PROTOTYPE ================= */

void DoNothing(void);

/* ================= GLOBAL TABLE ================= */
/* QUAN TRoNG: move truoc */
ActionFunc action_table[MAX_MOVE][MAX_ACTION][MAX_ID];   // state 2
ActionFunc zone3_table [MAX_MOVE][MAX_ACTION][MAX_ID];   // state 3

/* ================= DEFAULT ================= */

void DoNothing(void) {}
	
extern int hoan_thanh_chay_rung;


/* ================= INIT CUA STATE 2 VUOT RUNG SAN XANH ================= */

void Init_Action_Table_san_xanh(void)
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
    action_table[10][10][1] = auto_vao_rung_xanh_cua1;
    action_table[10][10][2] = auto_vao_rung_xanh_cua2;
    action_table[10][10][3] = auto_vao_rung_xanh_cua3;
	
	    /* =========================================
       move 2 , action 10 sang trai o ria rung
       ========================================= */
    action_table[2][10][1] = qua_trai_len_bac_400;
    action_table[2][10][2] = qua_trai_len_bac_200_cua_vao;

	    /* =========================================
		
       move 3 , action 10 sang phai o ria rung
       ========================================= */
    action_table[3][10][2] = qua_phai_len_bac_200_cua_vao;
    action_table[3][10][3] = qua_phai_len_bac_400;

	    /* =========================================
       move 20 , action 20 chay ra cua ra
       ========================================= */
    action_table[20][20][10] = vuot_rung_ve_homeTay_bac_200;
    action_table[20][20][11] = vuot_rung_ve_homeTay_bac_400;
    action_table[20][20][12] = vuot_rung_ve_homeTay_bac_200;


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
		action_table[0][2][8]  = Lay_ben_trai_bac_200_tren_xanh_9;
		action_table[0][2][11] = Lay_ben_trai_bac_200_tren_xanh_9;

//    /* =========================================
//       move 0 , action 3, dung lai de lay ben PHAI
//       ========================================= */
		action_table[0][3][5] = Lay_ben_phai_bac_200_tren_xanh_4;
		action_table[0][3][6] = Lay_ben_phai_bac_200_tren_xanh_4;
		action_table[0][3][8] = Lay_ben_phai_bac_200_tren_xanh_7;
		action_table[0][3][11]= Lay_ben_phai_bac_200_tren_xanh_11;
    /* =========================================
       move 1 , action 4 chay thang
       ========================================= */
    action_table[1][4][1] = Leo_bac_400_ko_thanh;
    action_table[1][4][2] = Leo_bac_200_bam_thanh_phai;
		action_table[1][4][3] = Leo_bac_400_co_thanh;
		action_table[1][4][4] = Xuong_bac_200_xanh_4;
    action_table[1][4][5] = Leo_bac_200_xanh_5;
    action_table[1][4][6] = Leo_bac_200_ko_thanh;
    action_table[1][4][7] = Leo_bac_200_xanh_7;
    action_table[1][4][8] = Leo_bac_200_ko_thanh;
    action_table[1][4][9]  = Xuong_bac_200_xanh_9;
    action_table[1][4][10] = xuong_bac_200_xanh_10;
    action_table[1][4][11] = xuong_bac_200_end;
		action_table[1][4][12] = xuong_bac_200_xanh_12;
		
				/* =========================================
//   move 2 , action 4,chay ben trai
//   ========================================= */
//		action_table[2][4][1] = qua_trai_len_bac;

		/* =========================================
//   move 3 , action 4,chay ben phai
//   ========================================= */
//    action_table[3][4][2] = qua_phai_xuong_bac;
		
}

/* ================= INIT CUA STATE 3 DAT KHOI TREN BUC ================= */
void Init_Zone3_Table_xan_xanh(void)
{
    int m,a,i;

    for(m=0;m<MAX_MOVE;m++)
        for(a=0;a<MAX_ACTION;a++)
            for(i=0;i<MAX_ID;i++)
                zone3_table[m][a][i] = DoNothing;
//    zone3_table[14][15][16] = Zone3_Special_Run; 	// o 4, 5,6 trong
//    zone3_table[4][15][16] = Zone3_Special_Run; 	//O 4 BI DAT , o 5,6 trong
//    zone3_table[14][5][16] = Zone3_Special_Run;		//O 5 BI DAT , o 4 6 trong
//    zone3_table[14][15][6] = Zone3_Special_Run;		//O 6 BI DAT , o 4 5 trong
//    zone3_table[4][5][16] = Zone3_Special_Run; 		//O 4 5 BI DAT , O 6 trong
//    zone3_table[4][15][6] = Zone3_Special_Run;		//O 4 6 BI DAT , o 5 trong
//    zone3_table[14][5][6] = Zone3_Special_Run;		//O 5 6 BI DAT , o 4 trong
//    zone3_table[4][5][6] = Zone3_Special_Run; 	// o 4, 5,6 bi dat
}


/* ================= RUN ================= */
int Queue_Peek_Offset(Packet_t *out, uint16_t offset)
{
    uint16_t index;   

    if (count_data_uart4 <= offset)
        return 0;

    index = (tail + offset) % QUEUE_SIZE;

    *out = packet_queue[index];
    return 1;
}

// hàm kiem tra lenh gap truoc 1 buoc
uint8_t Check_Next1_Block_For_Prepare(void)
{
    Packet_t next2;

    if (!Queue_Peek_Offset(&next2, 1))
        return 0;

    if (next2.move == 0 && next2.action == 1)
    {
        TinHieu_ChuanBi_GapThang = 1;
        return 1;
    }
    else if (next2.move == 0 && next2.action == 2)
    {
        TinHieu_ChuanBi_GapTrai = 1;
        return 1;
    }
    else if (next2.move == 0 && next2.action == 3)
    {
        TinHieu_ChuanBi_GapPhai = 1;
        return 1;
    }

    return 0;
}

////// ************** CHAY TU DONG
void Run_All_Blocks_From_Queue_san_xanh(void)
{
    Packet_t pkt;

    if (count_data_uart4 == 0)
        return;

    while (count_data_uart4 > 0)
    {
        /* luôn nhìn tru?c 1 block tru?c khi pop */
        Check_Next1_Block_For_Prepare();

        if (!Queue_Pop(&pkt))
            break;

        if (pkt.move < MAX_MOVE &&
            pkt.action < MAX_ACTION &&
            pkt.id_block < MAX_ID)
        {
            action_table[pkt.move][pkt.action][pkt.id_block]();
        }
						vTaskDelay(5000);
				
    }

    has_active_block = 0;
}

/// CHAY BAN TU DONG

//void Run_All_Blocks_From_Queue_san_xanh(void)
//{
//    Packet_t pkt;

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
//******************************* DatKFSxanh **************************
void DatKFSxanh(int vitri)
{
	speed_tay_xoay = 100;
	target_xoay_tay = vi_tri_dat_hop_1_2;
	
	Nang_thuong();
	target_chan_truoc = 335;
	target_chan_sau = 335;
	
	for(i=0;i<150;i++)		
	{
		while(abs(bientrochansauValue - target_chan_sau) > 10)	{vTaskDelay(1); if(!wantExit())	break;}
	}
	vTaskDelay(4000); 
	
	chinh_lai_vi_tri_laser_phai(180, 1000);
	

		robotRunAngle(-900,30,900,0.7);
		for(i=0;i<550;i++)	
	{	
			while(lazeTraiValue > 340)	
			{	
				vTaskDelay(5); 
				if(!wantExit())	break;
			}
	}	
	vTaskDelay(3000); 
	
		for(i=0;i<550;i++)	
	{	
			while(lazeTraiValue < 300)	
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
				vTaskDelay(5); 
				if(!wantExit())	break;
			}
	}		
		
	
	for(i=0;i<550;i++)	
	{	
			while(lazeTraiValue > 250)	
			{	
				Bam_laser_sau(30,0,900, 50, 3, -100, 10);
				vTaskDelay(5); 
				if(!wantExit())	break;
			}
	}	

		speed_tay_gat1 = 100;
	target_tay_gat1 = vitri_tay1home - 90;
	
	speed_tay_gat2 = 100;
	target_tay_gat2 = vitri_tay2home - 90;

	
	for(i=0;i<550;i++)	
	{	
			while(lazeTraiValue > 170)	
			{	
				Bam_laser_sau(8,0,900, 50, 2, -100, 10);
				vTaskDelay(5); 
				if(!wantExit())	break;
			}
	}	

		robotStop(0);

	// do chan len dat qua
		su_dung_chan(690);
		for(i=0;i<150;i++)		
	{
		while(abs(bientrochansauValue - target_chan_sau) > 10)	{vTaskDelay(1); if(!wantExit())	break;}
	}
	vTaskDelay(2000); 
		
	robotStop(0);
	

}

void dat_qua_tay_1_2_xanh(void) {
	speed_tay_gat1 = 250;
	target_tay_gat1 = vitri_tay1home + 100;
	for(i=0;i<50;i++)	{ 
						while(abs(bientrodaytay1Value - target_tay_gat1)> 5 )	{vTaskDelay(1); if(!wantExit())	break;}
				}
	
	speed_tay_gat2 = 250;
	target_tay_gat2 = vitri_tay2home + 100;
	for(i=0;i<50;i++)	{ 
						while(abs(bientrodaytay2Value - target_tay_gat2)> 10 )	{vTaskDelay(1); if(!wantExit())	break;}
				}
	vTaskDelay(1000);
	Kep_phai_1_ra;
	Kep_phai_2_ra;

}


void tudonghoantoan(void) {
Run_All_Blocks_From_Queue_san_xanh();
vTaskDelay(7000);
if (hoan_thanh_chay_rung == 1 )DatKFSxanh(50),hoan_thanh_chay_rung = 2 ;
if (hoan_thanh_chay_rung== 2) dat_qua_tay_1_2_xanh(),hoan_thanh_chay_rung = 3;
//if (hoan_thanh_chay_rung== 3) dat_qua_o_1(),hoan_thanh_chay_rung = 4;

}
