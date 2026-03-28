	// ***************** CHINH LAI VI TRI LAZER SAN DO **************

void chinh_lai_vi_tri_laser_trai_do(int vitri, int gia_tri_lap)
{
	int speed ;
	int dieuchinh;
		for(i=0;i<gia_tri_lap;i++)
				{
		while(abs(lazeTraiValue - vitri) > 1)	{
			dieuchinh = lazeTraiValue - vitri;
			speed = smooth_speed(dieuchinh);
			
					if  ((lazeTraiValue - vitri)> 0 ) {
							robotRunAngle(1800, speed, -900, 0.9);
					}
					else if ((lazeTraiValue - vitri)< 0) {
					
					robotRunAngle(0, speed, -900, 0.9);
					
					}
					else {
								robotStop(0);

								}
				if(!wantExit())	break;
			}
		}   		
	}

void chinh_lai_vi_tri_VK_do(int vitri, int gia_tri_lap)
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

	void chinh_lai_vi_tri_laser_phai_do(int vitri, int gia_tri_lap)
{
	int speed ;
	int dieuchinh;
		for(i=0;i<gia_tri_lap;i++)
				{
		while(abs(lazePhaiValue - vitri) > 1)	{
			dieuchinh = lazePhaiValue - vitri;
			speed = smooth_speed(dieuchinh);
			
					if  ((lazePhaiValue - vitri)> 0 ) {
							robotRunAngle(0, speed, -900, 0.5);
					}
					else if ((lazePhaiValue - vitri)< 0) {
					
					robotRunAngle(1800, speed, -900, 0.5);
					
					}
					else {
								robotStop(0);

								}
				if(!wantExit())	break;
			}
		}   		
	}

		
void chinh_lai_vi_tri_laser_phai_custom_do(int vitri, int gia_tri_lap)
{
	int speed ;
	int dieuchinh;
		for(i=0;i<gia_tri_lap;i++)
				{
		while(abs(lazePhaiValue - vitri) > 1)	{
			dieuchinh = lazePhaiValue - vitri;
			speed = custom_smooth_speed(dieuchinh, 4, 30);
			
					if  ((lazePhaiValue - vitri)> 0 ) {
							robotRunAngle(0, speed, -900, 0.9);
					}
					else if ((lazePhaiValue - vitri)< 0) {
					
					robotRunAngle(1800, speed, -900, 0.9);
					
					}
					else {
								robotStop(0);
				if(!wantExit())	break;
								}
			
			}
		}   		
	}

		
void chinh_lai_vi_tri_laser_trai_custom_do(int vitri, int gia_tri_lap)
{
	int speed ;
	int dieuchinh;
		for(i=0;i<gia_tri_lap;i++)
				{
		while(abs(lazeTraiValue - vitri) > 1)	{
			dieuchinh = lazeTraiValue - vitri;
			speed = custom_smooth_speed(dieuchinh, 4, 30);
			
					if  ((lazeTraiValue - vitri)> 0 ) {
							robotRunAngle(1800, speed, -900, 0.9);
					}
					else if ((lazeTraiValue - vitri)< 0) {
					
					robotRunAngle(0, speed, -900, 0.9);
					
					}
					else {
								robotStop(0);

								}
					if(!wantExit())	break;
			}
		}   		
	}


	void Ktra_vtri_kep4_do (void) {
		for(i=0;i<200;i++)
				{
					while(CB_kep_4_2 == 0 || CB_kep_4_1 == 0 )	
					{	
						if	(CB_kep_4_2 == 0 && CB_ROI_1 == 0 ) robotRun(-910,4);	
						else if 	(CB_kep_4_1 == 0 && CB_ROI_4 == 0  ) robotRun(910,4);
						else	{	
						robotStop(0);			
							
						}	
						vTaskDelay (1);
						if(!wantExit())	break;
					}
				}	
				robotStop(0);
	}
	

void di_vao_giua_do (void) {

					// da dung tay 1 xong
			if (da_lay_tay1 == 1 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
					robotRunAngle(-150,7,-900,0.3);
					vTaskDelay (10000);
					robotStop(0);
			
		}
			
			// dung tay 2 xong
			else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
					robotRunAngle(-150,7,-900,0.3);
					vTaskDelay (10000);
					robotStop(0);
				
			}
			
			// dung tay lan 3 xong
			else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 0) {
					robotRunAngle(1950,7,-900,0.3);
					vTaskDelay (10000);
					robotStop(0);
				
			}
			// dung tay 4 xong
			else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 1) {
				robotRunAngle(1950,7,-900,0.3);
				vTaskDelay (10000);
					robotStop(0);
				
			}		
}
////////////////// CODE DI CHUYEN SAN DO ****************************************

void di_tren_buc_khong_thanh_2_ben_do(void) {

		if (da_lay_tay1 == 0 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
			
				kiem_tra_huong_ha_tay_gap_phia_truoc();
				//// qua phai cho den khi cb roi phai  mat
					robotRunAngle(1800,5,-900,0.5);
								
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
					kiem_tra_huong_ha_tay_gap_phia_truoc();
					robotRunAngle(1800,5,-900,0.5);
								
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
					kiem_tra_huong_ha_tay_gap_phia_truoc();
					robotRunAngle(0,5,-900,0.5);
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
					kiem_tra_huong_ha_tay_gap_phia_truoc();
					robotRunAngle(0,5,-900,0.5);
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


void chuan_bi_gap_trai_200_duoi_ko_thanh_do (void ) {
	
	if (da_lay_tay1 == 0 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
					ha_sat_xuong();
					for(i=0;i<250;i++)	
						{
							while(abs(bientrochansauValue - target_chan_sau) > 10)	{vTaskDelay(1); if(!wantExit())	break;}
						}	
					robotRunAngle(900,5,-900,0.9);
				
					// chuan bi xoay truoc sang trai
						speed_tay_xoay = 240;
						target_xoay_tay = vi_tri_tay_4_trai_duoi;
						Kep_phai_4_ra;
						
					for(i=0;i<1550;i++)
						{
							while(CB_Ha_Sau == 0)	
							{	
								if(!wantExit())	break;
								vTaskDelay (1);
							}
						}
			robotStop(0); 
			robotRunAngle(1800,5,-900,0.9);
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
	
			//// dung tay 3 gap duoi lan 2
		else if (da_lay_tay1 == 1 && da_lay_tay4_duoi == 0) {
					ha_sat_xuong();
					for(i=0;i<250;i++)	
				{
					while(abs(bientrochansauValue - target_chan_sau) > 10)	{vTaskDelay(1); if(!wantExit())	break;}
				}
				// chuan bi xoay truoc sang trai
						speed_tay_xoay = 240;
						target_xoay_tay = vi_tri_tay_3_trai_duoi;
						Kep_phai_3_ra;
				
			robotRunAngle(1800,5,-900,0.9);
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
		if (TinHieu_ChuanBi_GapThang == 1) { 
					kiem_tra_huong_quay_tay_gap_phia_truoc();
				// chay toi khi mat cam bien sau
				robotRunAngle(900,8,-900,0.7);
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
					
				di_tren_buc_khong_thanh_2_ben_do();
				}
		
}


///// ********* leo bac 200 khong thanh **************
void Leo_bac_200_ko_thanh_do(void)
{	
		Leo_bac_200(900,-900);
		su_dung_chan(265);
		for(i=0;i<50;i++)		
	{
		while(abs(bientrochansauValue - target_chan_sau) > 10)	{vTaskDelay(1); if(!wantExit())	break;}
	}
	if (TinHieu_ChuanBi_GapThang == 0 && TinHieu_ChuanBi_GapTrai == 0 && TinHieu_ChuanBi_GapPhai == 0) {
		// chay toi khi mat cam bien sau
		robotRunAngle(900,10,-900,0.8);
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
		else if (TinHieu_ChuanBi_GapThang == 1) {
			// chay toi khi mat cam bien sau
		robotRunAngle(900,8,-900,0.8);
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
			
		di_tren_buc_khong_thanh_2_ben_do();
		}
//	// CO LENH GAP TRAI
		else if (TinHieu_ChuanBi_GapTrai == 1 ) {
					chuan_bi_gap_trai_200_duoi_ko_thanh_do();
		}
//		// CO LENH GAP PHAI
//		else if (TinHieu_ChuanBi_GapPhai == 1 ) {
//					chuan_bi_gap_phai_200_duoi_ko_thanh();
//		}
}


void Leo_bac_400_co_thanh_do(void) {
		Leo_bac_400(900, -900);
	
		Nang_cuc_nhanh();
		
		target_chan_truoc = Min_chan_truoc + 250;
		target_chan_sau = Min_chan_sau + 240;
		
		// chay toi khi laser sau cham 1
		robotRunAngle(900,10,-900,0.1);
		for(i=0;i<150;i++)		
				{
					while(abs(bientrochansauValue - target_chan_sau) > 7)
					{
						if(!wantExit())	break;
						vTaskDelay (1);
					}
				}		
	
		for(i=0;i<1550;i++)
				{
					while(CB_Ha_Sau == 1 || CB_Cap_Thanh_Sau == 0 )	
					{	
						vTaskDelay (1);
						if(!wantExit())	break;
						vTaskDelay (1);
					}
				}
		
		vTaskDelay (2000);	
		robotStop(0);

			
if (TinHieu_ChuanBi_GapThang == 1) {
		
		di_tren_buc_khong_thanh_2_ben_do();
			
			//do Chan len
		su_dung_chan(580);
		}
	robotStop(0); 
}
//**************** Xuong_bac_200 xanh ô 9 **************		
void chuan_bi_gap_thang_do_9 (void) {
		int vitri_tay41 = vitri_tay41_laser_trai_GapQua;
		kiem_tra_huong_quay_tay_gap_phia_truoc();
		su_dung_chan(265);
		for(i=0;i<50;i++)		
	{
		while(abs(bientrochansauValue - target_chan_sau) > 10)	{vTaskDelay(1); if(!wantExit())	break;}
	}
	
	
		vTaskDelay(1000);
		// chay toi khi mat cam bien sau
		robotRunAngle(900,8,-900,0.3);
		for(i=0;i<250;i++)
				{
					while(CB_vtri_leo == 0 || CB_Ha_Sau == 0)	
					{	
						vTaskDelay (1);
						if(!wantExit())	break;
					}
				}
		kiem_tra_huong_ha_tay_gap_phia_truoc();
		robotStop(0);
	
			// chinh lai vi tri cho tay gap
		if (da_lay_tay1 == 0 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
						chinh_lai_vi_tri_laser_trai_do(vitri_tay41, 1000);
						robotStop(0);	
			}
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
					chinh_lai_vi_tri_laser_trai_do(vitri_tay41, 1000);
						robotStop(0);	
			}

		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
					robotRunAngle(0,5,-900,0.5);
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
					robotRunAngle(0,5,-900,0.5);
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

void Xuong_bac_200_do_9(void)
{	
		Xuong_bac_200(900, -900);
		
		if (TinHieu_ChuanBi_GapThang == 0 && TinHieu_ChuanBi_GapTrai == 0 && TinHieu_ChuanBi_GapPhai == 0) {
				su_dung_chan(265);
				for(i=0;i<50;i++)		
						{
				while(abs(bientrochansauValue - target_chan_sau) > 10)	{vTaskDelay(1); if(!wantExit())	break;}
						}
			
				vTaskDelay(1000);
				// chay toi khi mat cam bien sau
				robotRunAngle(900,8,-900,0.8);
				for(i=0;i<250;i++)
							{
							while( CB_Ha_Sau == 0 ) {	vTaskDelay (1); if(!wantExit())	break;
							}
						}
						
				robotStop(0);
				}				
	
		else if (TinHieu_ChuanBi_GapThang == 1) {
					chuan_bi_gap_thang_do_9();
					}
//		else if (TinHieu_ChuanBi_GapPhai == 1) {
//					chuan_bi_gap_phai_200_tren();
//				}
			robotStop(0);
				
			}

void xuong_bac_200_do_12(void) {
		Xuong_bac_200(900, -900);
		if (TinHieu_ChuanBi_GapThang == 0 && TinHieu_ChuanBi_GapTrai == 0 && TinHieu_ChuanBi_GapPhai == 0) {
				su_dung_chan(265);
				for(i=0;i<50;i++)		
					{
						while(abs(bientrochansauValue - target_chan_sau) > 10)	{vTaskDelay(1); if(!wantExit())	break;}
					}
				// chay toi khi mat cam bien sau
				robotRunAngle(900,10,-900,0.8);
				for(i=0;i<1550;i++)
						{
								while(CB_Ha_Sau == 0)	
							{	
								if(!wantExit())	break;
								vTaskDelay (1);
							}
						}
						
				robotStop(0);
			
			}
//		else if (TinHieu_ChuanBi_GapTrai == 1) {
//					chuan_bi_gap_trai_200_tren();
//				}
			robotStop(0);
}


void Leo_bac_400_ko_thanh_do(void)
{		
		Leo_bac_400(900, -900);

		su_dung_chan(265);
		for(i=0;i<50;i++)		
	{
		while(abs(bientrochansauValue - target_chan_sau) > 10)	{vTaskDelay(1); if(!wantExit())	break;}
	}
		// chay toi khi mat cam bien sau
		robotRunAngle(900,10,-900,0.5);
		for(i=0;i<250;i++)
				{
						while(CB_vtri_leo == 0 || CB_Ha_Sau == 0 )	
					{	
						vTaskDelay (1);
						if(!wantExit())	break;
					}
				}
		robotStop(3);
				
	if (TinHieu_ChuanBi_GapThang == 1 ) {
		di_tren_buc_khong_thanh_2_ben_do();
		}
}


void Leo_bac_200_bam_thanh_phai_do(void)
{	
	int vitri_tay41 = vitri_tay41_laser_trai_GapQua;
	int vitri_tay23 = vitri_tay23_phai_laser_GapQua;
	
	Leo_bac_200(900, -900);
	
	Nang_cuc_nhanh();
	target_chan_truoc = Min_chan_truoc + 250;
	target_chan_sau = Min_chan_sau + 240;
	robotRunAngle(900,8,-900,0.7);
	for(i=0;i<250;i++)	
			{
				while(abs(bientrochansauValue - target_chan_sau) > 10)	{vTaskDelay(1); if(!wantExit())	break;}
			}	
	
		for(i=0;i<1550;i++)
				{
					while(CB_Ha_Sau == 1 || CB_Cap_Thanh_Sau == 0 )	
					{	
						if(!wantExit())	break;
						vTaskDelay (1);
					}
				}
		vTaskDelay (1000);
		
		if (TinHieu_ChuanBi_GapThang == 1) {
				su_dung_chan(565);		
		}
		
	if (TinHieu_ChuanBi_GapThang == 1) {
		kiem_tra_huong_ha_tay_gap_phia_truoc();
	// chinh lai vi tri cho tay gap
		if (da_lay_tay1 == 0 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
					robotRunAngle(900,5,-900,0.6);
					vTaskDelay (2000);
					chinh_lai_vi_tri_laser_trai_do(vitri_tay41, 1000);
			}
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
					robotRunAngle(900,5,-900,0.6);
					vTaskDelay (2000);
					chinh_lai_vi_tri_laser_trai_do(vitri_tay41, 1000);	
			}

		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
						robotRunAngle(900,5,-900,0.6);
						vTaskDelay (2000);
						chinh_lai_vi_tri_laser_phai_do(vitri_tay23, 1000);	
						}
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 0) {
						robotRunAngle(900,5,-900,0.6);
						vTaskDelay (2000);
						chinh_lai_vi_tri_laser_phai_do(vitri_tay23, 1000);
						}			
		}
		robotStop(0); 					
}


//**************** Xuong_bac_200 ô 4********
void chuan_bi_gap_thang_do_4(void) {
		int vitri_tay23 = vitri_tay23_phai_laser_GapQua;
		kiem_tra_huong_quay_tay_gap_phia_truoc();
		su_dung_chan(510);
			// chay toi khi laser sau cham 1
			robotRunAngle(900,8,-900,0.7);
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
					kiem_tra_huong_ha_tay_gap_phia_truoc();
					robotRunAngle(1800,5,-900,0.5);
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
					kiem_tra_huong_ha_tay_gap_phia_truoc();
					robotRunAngle(1800,5,-900,0.5);
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
					robotRunAngle(900,5,-900,0.8);
					vTaskDelay (2000);
					kiem_tra_huong_ha_tay_gap_phia_truoc();
					chinh_lai_vi_tri_laser_phai_do(vitri_tay23, 1000);
						}
		
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 0) {
					robotRunAngle(900,5,-900,0.8);
					vTaskDelay (2000);
					kiem_tra_huong_ha_tay_gap_phia_truoc();
					chinh_lai_vi_tri_laser_phai_do(vitri_tay23, 1000);
					}
			su_dung_chan(565);
}


void chuan_bi_gap_trai_200_tren_do_4 (void ) {
	
	if (da_lay_tay1 == 0 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
			chinh_lai_vi_tri_laser_phai_do(vitri_tay23_phai_laser_GapQua, 1000);
					robotRunAngle(900,5,-900,0.7);
							for(i=0;i<150;i++)
							{
								while(lazeSauValue > 31)	
								{	
									vTaskDelay (1);
									if(!wantExit())	break;
								}
							}
							robotRunAngle(0,6,-900,0.7);
							vTaskDelay(2000);
								robotStop(0);
					
					su_dung_chan(565);
						for(i=0;i<250;i++)	
					{
						while(abs(bientrochansauValue - target_chan_sau) > 10)	{vTaskDelay(1); if(!wantExit())	break;}
					}		
		}
	else if (da_lay_tay1 == 1 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
					chinh_lai_vi_tri_laser_phai_do(vitri_tay23_phai_laser_GapQua, 1000);
					robotRunAngle(900,5,-900,0.7);
							for(i=0;i<150;i++)
							{
								while(lazeSauValue > 31)	
								{	
									vTaskDelay (1);
									if(!wantExit())	break;
								}
							}
							robotRunAngle(0,6,-900,0.7);
							vTaskDelay(2000);
								robotStop(0);
					
					su_dung_chan(565);
						for(i=0;i<250;i++)	
					{
						while(abs(bientrochansauValue - target_chan_sau) > 10)	{vTaskDelay(1); if(!wantExit())	break;}
					}		
		}
	else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
					chinh_lai_vi_tri_laser_phai_do(vitri_tay23_phai_laser_GapQua, 1000);
					robotRunAngle(0,6,-900,0.7);
					vTaskDelay(2000);
					su_dung_chan(510);
					// chay toi khi laser sau cham 1
					robotRunAngle(900,8,-900,0.7);
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
					chinh_lai_vi_tri_laser_phai_do(vitri_tay23_phai_laser_GapQua, 1000);
					robotRunAngle(0,6,-900,0.7);
					vTaskDelay(2000);
					su_dung_chan(510);
					// chay toi khi laser sau cham 1
					robotRunAngle(900,8,-900,0.7);
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

void Xuong_bac_200_do_4(void)
{	
	int vitri_tay41 = vitri_tay41_laser_trai_GapQua;

	Xuong_bac_200(900,-900);		
	
	// KHONG CO TIN HIEU GAP
	if (TinHieu_ChuanBi_GapThang == 0 && TinHieu_ChuanBi_GapTrai == 0 && TinHieu_ChuanBi_GapPhai == 0) {
		Nang_cuc_nhanh();
		
		target_chan_truoc = Min_chan_truoc + 250;
		target_chan_sau = Min_chan_sau + 240;
		
		robotRunAngle(900,8,-900,0.7);
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
	if (TinHieu_ChuanBi_GapThang == 1) {
			su_dung_chan(565);	
	}	
	
	}
	// CO LENH GAP THANG
		else if (TinHieu_ChuanBi_GapThang == 1 ) {
				chuan_bi_gap_thang_do_4();
				}	
		// CO LENH GAP TRAI
		else if (TinHieu_ChuanBi_GapTrai == 1 ) {
					chuan_bi_gap_trai_200_tren_do_4();
		}
		
		robotStop(0); 	
}


void chuan_bi_gap_phai_200_duoi_do_5 (void ) {
	
	if (da_lay_tay1 == 0 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
					ha_sat_xuong();
					for(i=0;i<250;i++)	
						{
							while(abs(bientrochansauValue - target_chan_sau) > 10)	{vTaskDelay(1); if(!wantExit())	break;}
						}	
					robotRunAngle(900,5,-900,0.7);
				
					// chuan bi xoay truoc sang trai
						speed_tay_xoay = 240;
						target_xoay_tay = vi_tri_tay_4_phai_duoi;
						Kep_phai_4_ra;
						
					for(i=0;i<1550;i++)
						{
							while(HT_3 == 0 && HT_4 == 0)	
							{	
								if(!wantExit())	break;
								vTaskDelay (1);
							}
						}
			robotStop(10); 
			robotRunAngle(1800,5,-900,0.5);
					for(i=0;i<150;i++)
					{
						while(CB_ROI_1 == 0)	
						{	
							vTaskDelay (1);
							if(!wantExit())	break;
						}
					}
					robotStop(0);
			}
	
			//// dung tay 3 gap duoi lan 2
		else if (da_lay_tay1 == 1 && da_lay_tay4_duoi == 0) {
					ha_sat_xuong();
					for(i=0;i<250;i++)	
						{
							while(abs(bientrochansauValue - target_chan_sau) > 10)	{vTaskDelay(1); if(!wantExit())	break;}
						}	
					robotRunAngle(900,5,-900,0.7);
				
					// chuan bi xoay truoc sang trai
						speed_tay_xoay = 240;
						target_xoay_tay = vi_tri_tay_4_phai_duoi;
						Kep_phai_4_ra;
							
						for(i=0;i<1550;i++)
							{
								while(HT_3 == 0 && HT_4 == 0)	
								{	
									if(!wantExit())	break;
									vTaskDelay (1);
								}
							}
				robotStop(10); 
				robotRunAngle(1800,5,-900,0.5);
						for(i=0;i<150;i++)
						{
							while(CB_ROI_1 == 0)	
							{	
								vTaskDelay (1);
								if(!wantExit())	break;
							}
						}
						robotStop(0);
				}
}


/// ****** leo bac 200 o id  5 san xanh
void Leo_bac_200_do_5(void) {	
		Leo_bac_200(900, -900);
		
		// KHONG CO TIN HIEU GAP
		if (TinHieu_ChuanBi_GapThang == 0 && TinHieu_ChuanBi_GapTrai == 0 && TinHieu_ChuanBi_GapPhai == 0) {
				Nang_cuc_nhanh();
				
				target_chan_truoc = Min_chan_truoc + 250;
				target_chan_sau = Min_chan_sau + 240;
			
				robotRunAngle(900,10,-900,0.7);
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
				if (TinHieu_ChuanBi_GapThang == 1) {
					su_dung_chan(565);
						}	
				
						
				robotStop(0); 
		}
	// CO LENH GAP THANG
		else if (TinHieu_ChuanBi_GapThang == 1 ) {
				chuan_bi_gap_thang_do_4();
				}	
		// CO LENH GAP TRAI
		else if (TinHieu_ChuanBi_GapTrai == 1 ) {
					chuan_bi_gap_trai_200_tren_do_4();
		}
		// CO LENH GAP PHAI
		else if (TinHieu_ChuanBi_GapPhai == 1 ) {
					chuan_bi_gap_phai_200_duoi_do_5();
		}
		
		robotStop(0); 			
}



void chuan_bi_gap_thang_do_7(void) {
		int vitri_tay23 = vitri_tay23_phai_laser_GapQua;
		kiem_tra_huong_quay_tay_gap_phia_truoc();
	
		su_dung_chan(265);
		for(i=0;i<50;i++)		
			{
				while(abs(bientrochansauValue - target_chan_sau) > 10)	{vTaskDelay(1); if(!wantExit())	break;}
			}
		
		robotRunAngle(900,8,-900,0.7);
		for(i=0;i<1550;i++)
				{
						while(CB_vtri_leo == 0 || CB_Ha_Sau == 0)	
					{	
						if(!wantExit())	break;
						vTaskDelay (1);
					}
				}
		kiem_tra_huong_ha_tay_gap_phia_truoc();
				
		robotStop(0);
		vTaskDelay (1000);
	// chinh lai vi tri cho tay gap
		if (da_lay_tay1 == 0 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
					robotRunAngle(1800,5,-900,0.5);
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
					robotRunAngle(1800,5,-900,0.5);
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
					chinh_lai_vi_tri_laser_phai_do(vitri_tay23, 1000);	
				}
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 0) {
					chinh_lai_vi_tri_laser_phai_do(vitri_tay23, 1000);	
						}
}


void Leo_bac_200_do_7(void)  {	
		Leo_bac_200(900, -900);
			
			// KHONG CO TIN HIEU GAP
	if (TinHieu_ChuanBi_GapThang == 0 && TinHieu_ChuanBi_GapTrai == 0 && TinHieu_ChuanBi_GapPhai == 0) {
		su_dung_chan(265);
		for(i=0;i<50;i++)		
			{
				while(abs(bientrochansauValue - target_chan_sau) > 10)	{vTaskDelay(1); if(!wantExit())	break;}
			}
		// chay toi khi mat cam bien sau
		robotRunAngle(900,10,-900,0.7);
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
	
			// CO TIN HIEU GAP THANG
	else if (TinHieu_ChuanBi_GapThang == 1) {
				chuan_bi_gap_thang_do_7();
				}
//		// CO TIN HIEU GAP PHAI
//	else if (TinHieu_ChuanBi_GapPhai == 1) {
//					chuan_bi_gap_phai_200_tren_7_10();
//			}
		}

	
void xuong_bac_200_do_10 (void) {
	Xuong_bac_200(900, -900);
		if (TinHieu_ChuanBi_GapThang == 0 && TinHieu_ChuanBi_GapTrai == 0 && TinHieu_ChuanBi_GapPhai == 0) {
				su_dung_chan(265);
				for(i=0;i<50;i++)		
					{
						while(abs(bientrochansauValue - target_chan_sau) > 10)	{vTaskDelay(1); if(!wantExit())	break;}
					}
				// chay toi khi mat cam bien sau
				robotRunAngle(900,10,-900,0.7);
				for(i=0;i<1550;i++)
						{
								while(CB_Ha_Sau == 0)	
							{	
								if(!wantExit())	break;
								vTaskDelay (1);
							}
						}
						
				robotStop(0);
			
			}
//	else if (TinHieu_ChuanBi_GapPhai == 1) {
//					chuan_bi_gap_phai_200_tren_7_10();
//			}
}

void xuong_bac_200_11_do(void) {
		Xuong_bac_200(900, -900);
		robotStop(0);
		if (TinHieu_ChuanBi_GapThang == 0 && TinHieu_ChuanBi_GapTrai == 0 && TinHieu_ChuanBi_GapPhai == 0) {
				su_dung_chan(265);
				for(i=0;i<50;i++)		
					{
						while(abs(bientrochansauValue - target_chan_sau) > 10)	{vTaskDelay(1); if(!wantExit())	break;}
					}
				// chay toi khi mat cam bien sau
				robotRunAngle(900,10,-900,0.8);
				for(i=0;i<1550;i++)
						{
								while(CB_Ha_Sau == 0)	
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
