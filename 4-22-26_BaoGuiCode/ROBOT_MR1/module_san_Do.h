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
							robotRunAngle(0, speed, 900, 0.5);
					}
					else if ((lazeTraiValue - vitri)< 0) {
					
					robotRunAngle(1800, speed, 900, 0.5);
					
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

		
void chinh_lai_vi_tri_laser_phai_custom_do(int vitri, int gia_tri_lap,int min_toc, int max_toc)
{
	int speed ;
	int dieuchinh;
		for(i=0;i<gia_tri_lap;i++)
				{
		while(abs(lazePhaiValue - vitri) > 1)	{
			dieuchinh = lazePhaiValue - vitri;
			speed = custom_smooth_speed(dieuchinh, min_toc, max_toc);
			
					if  ((lazePhaiValue - vitri)> 0 ) {
							robotRunAngle(0, speed, -900, 0.8);
					}
					else if ((lazePhaiValue - vitri)< 0) {
					
					robotRunAngle(1800, speed, -900, 0.8);
					
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
			speed = custom_smooth_speed(dieuchinh, 4, 60);
			
					if  ((lazeTraiValue - vitri)> 0 ) {
							robotRunAngle(1800, speed, -900, 0.8);
					}
					else if ((lazeTraiValue - vitri)< 0) {
					
					robotRunAngle(0, speed, -900, 0.8);
					
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
					robotRunAngle(-150,10,-900,0.8);
					vTaskDelay (4000);
					robotStop(0);
			
		}
			
			// dung tay 2 xong
			else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
					robotRunAngle(-150,10,-900,0.8);
					vTaskDelay (4000);
					robotStop(0);
				
			}
			
			// dung tay lan 3 xong
			else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 0) {
					robotRunAngle(1950,10,-900,0.8);
					vTaskDelay (4000);
					robotStop(0);
				
			}
			// dung tay 4 xong
			else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 1) {
				robotRunAngle(1950,10,-900,0.8);
				vTaskDelay (4000);
					robotStop(0);
			}		
}

// qua trai len 400 o cua vao rung
void qua_trai_len_bac_400_do(void) {
	su_dung_chan(700);
	
	for(i=0;i<150;i++)		
	{
		while(abs(bientrochansauValue - target_chan_sau) > 10)	{vTaskDelay(1); if(!wantExit())	break;}
	}
	
	kiem_tra_huong_quay_tay_gap_phia_truoc();
	chinh_lai_vi_tri_laser_phai_do(vi_tri_cua_rung_do_3_lazer_phai_tay_41 - 10, 1000);
	
		
	robotRunAngle(900,6,-900,0.5);
	for(i=0;i<1050;i++)	
	{	
		while(CB_Cap_Thanh_Sau == 0)	{vTaskDelay(1); if(!wantExit())	break;}
	}
	robotStop(10);
		
	if (TinHieu_ChuanBi_GapThang == 1 ) {
		if (da_lay_tay1 == 1 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
					chinh_lai_vi_tri_laser_phai_do(vi_tri_cua_rung_do_3_lazer_phai_tay_41, 1000);
					}
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
					chinh_lai_vi_tri_laser_phai_do(vi_tri_cua_rung_do_3_lazer_phai_tay_23, 1000); 
					}
				}
	robotRunAngle(900,6,-900,0.5);
	for(i=0;i<1050;i++)	
	{	
		while(CB_Cap_Thanh_Sau == 0)	{vTaskDelay(1); if(!wantExit())	break;}
	}
	vTaskDelay(2000);
	robotStop(0);
}

void qua_trai_len_bac_200_cua_vao_do(void) {
	kiem_tra_huong_quay_tay_gap_phia_truoc();
	if ( TinHieu_ChuanBi_GapThang == 1 ) {
				chinh_lai_vi_tri_laser_phai_do(vi_tri_cua_rung_do_2_lazer_phai_tay_41 , 1000);
				su_dung_chan(575);
				robotRunAngle(900,6,-900,0.3);
				for(i=0;i<1050;i++)	
					{	
					while( CB_Cap_Thanh_Sau == 0)	{vTaskDelay(1); if(!wantExit())	break;}
					}
					vTaskDelay(2000);
				}
		
		else if  ( TinHieu_ChuanBi_GapThang == 0 ) {
					if (chay_ngang_qua_o3_do == 0) {
							chinh_lai_vi_tri_laser_phai_custom_do(vi_tri_cua_rung_do_2_lazer_phai_tay_41 - 15, 1000, 5, 55);
			}
			else if (chay_ngang_qua_o3_do == 1) {
						chinh_lai_vi_tri_laser_phai_custom_do(vi_tri_cua_rung_do_1_lazer_phai_tay_41 - 15, 1000, 5, 60);
						}
				}
		
	bai_db = 1;
	robotStop(0);
}

//============== Sang phai lên bac 400 o ria rung ===================

void qua_phai_len_bac_400_do(void) {
	su_dung_chan(700);
	
	for(i=0;i<150;i++)		
	{
		while(abs(bientrochansauValue - target_chan_sau) > 10)	{vTaskDelay(1); if(!wantExit())	break;}
	}
	
	kiem_tra_huong_quay_tay_gap_phia_truoc();
	chinh_lai_vi_tri_laser_phai_do(vi_tri_cua_rung_do_1_lazer_phai_tay_23 + 10, 1000);
	
	robotStop(0);
	robotRunAngle(900,6,-900,0.5);
	for(i=0;i<1050;i++)	
	{	
		while(CB_Cap_Thanh_Sau == 0)	{vTaskDelay(1); if(!wantExit())	break;}
	}

	robotStop(10);
	if (TinHieu_ChuanBi_GapThang == 1 ) {
				
		if (da_lay_tay1 == 1 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
					chinh_lai_vi_tri_laser_phai_do(vi_tri_cua_rung_do_1_lazer_phai_tay_41, 1000);
					}
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
					chinh_lai_vi_tri_laser_phai_do(vi_tri_cua_rung_do_1_lazer_phai_tay_23, 1000);
					}
				}
	
	robotStop(0);
				robotRunAngle(900,6,-900,0.5);
	for(i=0;i<1050;i++)	
	{	
		while(CB_Cap_Thanh_Sau == 0)	{vTaskDelay(1); if(!wantExit())	break;}
	}
	vTaskDelay(2000);
	robotStop(0);
		
}

void qua_phai_len_bac_200_cua_vao_do(void) {
	
	// kiem tra tay gap
	kiem_tra_huong_quay_tay_gap_phia_truoc();

		if ( TinHieu_ChuanBi_GapThang == 1 ) {
				chinh_lai_vi_tri_laser_phai_do(vi_tri_cua_rung_do_2_lazer_phai_tay_41 , 1000);
				su_dung_chan(575);
				robotRunAngle(900,6,-900,0.3);
				for(i=0;i<1050;i++)	
				{	
					while( CB_Cap_Thanh_Sau == 0)	{vTaskDelay(1); if(!wantExit())	break;}
				}
					vTaskDelay(2000);
				}
		
		else if  ( TinHieu_ChuanBi_GapThang == 0 ) {
				if (chay_ngang_qua_o1_do == 0) {
						chinh_lai_vi_tri_laser_phai_custom_do(vi_tri_cua_rung_do_2_lazer_phai_tay_41 - 15, 1000, 5, 55);
			}
			else if (chay_ngang_qua_o1_do == 1) {
						chinh_lai_vi_tri_laser_phai_custom_do(vi_tri_cua_rung_do_3_lazer_phai_tay_41 - 15, 1000,5,  60);
						}
				}
		
		robotStop(0);
		bai_db = 1;
//		
}

////////////////// CODE DI CHUYEN SAN DO ****************************************

void di_tren_buc_khong_thanh_2_ben_do(void) {
		if (da_lay_tay1 == 0 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
				while(CB_Ha_Sau == 0) {
				if(CB_ROI_3  == 0 && CB_ROI_1 == 0)	robotRunAngle(1550,15,-900,0.7); // di voi goc xéo phai
				else																robotRunAngle(900,12,-900,0.7); // di thang
				vTaskDelay(1);
				if(!wantExit()) break;
					}
//				// chay toi roi thi di ngang qua phai
//				robotRunAngle(1800,10,-900,0.7);
//				while (CB_ROI_3  == 0 )	 {
//					vTaskDelay(1);
//					if(!wantExit()) break;
//					}
			}
		
	else if (da_lay_tay1 == 1 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
				while( CB_Ha_Sau == 0) {
				if(CB_ROI_3  == 0 && CB_ROI_1 == 0)	robotRunAngle(1550,15,-900,0.7); // di xeo phai
				else																robotRunAngle(900,12,-900,0.7);  // di thang 
				vTaskDelay(1);
				if(!wantExit()) break;
					}
//				// chay toi roi thi di ngang qua phai
//				robotRunAngle(1800,10,-900,0.7);
//				while (CB_ROI_3  == 0 )	 {
//					vTaskDelay(1);
//					if(!wantExit()) break;
//					}
				}
//fix2
		// quay mam sang tay 2
			else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
				while( CB_Ha_Sau == 0) {
				if(CB_ROI_2  == 0 && CB_ROI_4 == 0)	robotRunAngle(350,15,-900,0.7); //di xeo qua trai
				else																robotRunAngle(900,12,-900,0.7); //di thang
				vTaskDelay(1);
				if(!wantExit()) break;
							}
//				// chay toi roi thi di ngang qua trai
//				robotRunAngle(0,10,-900,0.7);
//				while (CB_ROI_2  == 0 )	 {
//					vTaskDelay(1);
//					if(!wantExit()) break;
//						}
				}
		
		// quay mam sang tay 3
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 0) {
				while(CB_Ha_Sau == 0) {
				if(CB_ROI_2  == 0 && CB_ROI_4 == 0)	robotRunAngle(350,15,-900,0.7);
				else																robotRunAngle(900,12,-900,0.7);
				vTaskDelay(1);
				if(!wantExit()) break;
						}
//				// chay toi roi thi di ngang qua trai
//				robotRunAngle(0,10,-900,0.7);
//				while (CB_ROI_2  == 0 )	 {
//					vTaskDelay(1);
//					if(!wantExit()) break;
//							}
					}
			robotStop(0);
			
			
					}

void chuan_bi_gap_trai_200_duoi_ko_thanh_do (void ) {
			if (da_lay_tay1 == 0 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
					ha_sat_xuong();
					while( CB_Ha_Sau == 0 || (abs(bientrochansauValue - target_chan_sau) > 10)) {
					if(CB_ROI_4  == 0 && CB_ROI_2 == 0)	robotRunAngle(550,15,-900,0.8);
					else																robotRunAngle(900,12,-900,0.8);
					vTaskDelay(1);
					if(!wantExit()) break;
						}
					// chay toi roi thi di ngang qua phai
					robotRunAngle(0,8,-900,0.7);
					while (CB_ROI_4  == 0 )	 {
						vTaskDelay(1);
						if(!wantExit()) break;
						}
			}
		
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
					ha_sat_xuong();
					while( CB_Ha_Sau == 0 || (abs(bientrochansauValue - target_chan_sau) > 10)) {
					if(CB_ROI_4  == 0 && CB_ROI_2 == 0)	robotRunAngle(550,15,-900,0.8);
					else																robotRunAngle(900,12,-900,0.8);
					vTaskDelay(1);
					if(!wantExit()) break;
						}
					// chay toi roi thi di ngang qua phai
					robotRunAngle(0,8,-900,0.7);
					while (CB_ROI_4  == 0 )	 {
						vTaskDelay(1);
						if(!wantExit()) break;
						}
			}
			//// gap duoi lan 3
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {		
					ha_sat_xuong();
					for(i=0;i<50;i++)		
				{
					while(abs(bientrochansauValue - target_chan_sau) > 15)	{vTaskDelay(1); if(!wantExit())	break;}
				}
					robotRunAngle(0,8,-900,0.8);
					for(i=0;i<150;i++)
					{
						while(CB_ROI_4 == 0 )	
						{	
							vTaskDelay (1);
							if(!wantExit())	break;
						}
					}
				}
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 0) {		
					ha_sat_xuong();
					for(i=0;i<50;i++)		
					{
						while(abs(bientrochansauValue - target_chan_sau) > 15)	{vTaskDelay(1); if(!wantExit())	break;}
					}
					robotRunAngle(0,8,-900,0.8);
					for(i=0;i<150;i++)
					{
						while(CB_ROI_4 == 0 )	
						{	
							vTaskDelay (1);
							if(!wantExit())	break;
						}
					}
				}
				robotStop(0);
}


///// ********* leo bac 200 khong thanh **************

void chuan_bi_gap_phai_200_duoi_ko_thanh_do(void ) {
		if (da_lay_tay1 == 0 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
					ha_sat_xuong();
					{
					while(abs(bientrochansauValue - target_chan_sau) > 15)	{vTaskDelay(1); if(!wantExit())	break;}
						}
					robotRunAngle(1800,10,-900,0.8);
					for(i=0;i<150;i++)
					{
						while(CB_ROI_1 == 0 ||  (abs(bientrochansauValue - target_chan_sau) > 10))	
						{	
							vTaskDelay (1);
							if(!wantExit())	break;
						}
					}
			}
		
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
					ha_sat_xuong();
					{
					while(abs(bientrochansauValue - target_chan_sau) > 15)	{vTaskDelay(1); if(!wantExit())	break;}
						}
					robotRunAngle(1800,10,-900,0.8);
					for(i=0;i<150;i++)
					{
						while(CB_ROI_1 == 0 || (abs(bientrochansauValue - target_chan_sau) > 10))	
						{	
							vTaskDelay (1);
							if(!wantExit())	break;
						}
					}
			}
			//// gap duoi lan 3
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {		
					ha_sat_xuong();
					while( CB_Ha_Sau == 0 || (abs(bientrochansauValue - target_chan_sau) > 10)) {
					if(CB_ROI_3  == 0 && CB_ROI_1 == 0)	robotRunAngle(1250,15,-900,0.8);
					else																robotRunAngle(900,10,-900,0.8);
					vTaskDelay(1);
					if(!wantExit()) break;
						}
					// chay toi roi thi di ngang qua phai
					robotRunAngle(1800,8,-900,0.7);
					while (CB_ROI_1  == 0 )	 {
						vTaskDelay(1);
						if(!wantExit()) break;
						}
				}
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 0) {		
					ha_sat_xuong();
					while( CB_Ha_Sau == 0 || (abs(bientrochansauValue - target_chan_sau) > 10)) {
					if(CB_ROI_3  == 0 && CB_ROI_1 == 0)	robotRunAngle(1250,15,-900,0.8);
					else																robotRunAngle(900,10,-900,0.8);
					vTaskDelay(1);
					if(!wantExit()) break;
						}
					// chay toi roi thi di ngang qua phai
					robotRunAngle(1800,8,-900,0.7);
					while (CB_ROI_1  == 0 )	 {
						vTaskDelay(1);
						if(!wantExit()) break;
						}
				}
				robotStop(0);
}

void Leo_bac_200_ko_thanh_do(void)
{	
		Leo_bac_200(900,-900);
		su_dung_chan(265);

	if (TinHieu_ChuanBi_GapThang == 0 && TinHieu_ChuanBi_GapTrai == 0 && TinHieu_ChuanBi_GapPhai == 0) {
		// chay toi khi mat cam bien sau
		robotRunAngle(900,20,-900,0.7);
		for(i=0;i<1550;i++)
				{
						while(CB_Ha_Sau == 0 || (abs(bientrochansauValue - target_chan_sau) > 10))	
					{	
						if(!wantExit())	break;
						vTaskDelay (1);
					}
				}
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
		else if (TinHieu_ChuanBi_GapThang == 1) {
					di_tren_buc_khong_thanh_2_ben_do();
		}
//	// CO LENH GAP TRAI
		else if (TinHieu_ChuanBi_GapTrai == 1 ) {
					chuan_bi_gap_trai_200_duoi_ko_thanh_do();
		}
		// CO LENH GAP PHAI
		else if (TinHieu_ChuanBi_GapPhai == 1 ) {
					chuan_bi_gap_phai_200_duoi_ko_thanh_do();
		}
}



void Leo_bac_400_co_thanh_do(void) {
		Leo_bac_400(900, -900);
			
	if (TinHieu_ChuanBi_GapThang == 0) {
		su_dung_chan(480);

		// chay toi khi laser sau cham 1
		robotRunAngle(900,20,-900,0.7);
		for(i=0;i<1550;i++)
				{
					while(CB_Ha_Sau == 1  || (abs(bientrochansauValue - target_chan_sau) > 20))	
					{	
						vTaskDelay (1);
						if(!wantExit())	break;
					}
				}

		robotRunAngle(900,10,-900,0.7);
		for(i=0;i<1550;i++)
				{
					while(CB_Cap_Thanh_Sau == 0 || (abs(bientrochansauValue - target_chan_sau) > 20))	
					{	
						vTaskDelay (1);
						if(!wantExit())	break;
					}
				}
	}
			
else if (TinHieu_ChuanBi_GapThang == 1) {
			su_dung_chan(565);
			
		if (da_lay_tay1 == 0 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
				while(CB_Cap_Thanh_Sau == 0 || (abs(bientrochansauValue - target_chan_sau) > 20))	 {
				if(CB_ROI_3  == 0 && CB_ROI_1 == 0)	robotRunAngle(1250,15,-900,0.7);
				else																robotRunAngle(900,10,-900,0.7);
				vTaskDelay(1);
				if(!wantExit()) break;
					}
				// chay toi roi thi di ngang qua phai
				robotRunAngle(1800,10,-900,0.7);
				while (CB_ROI_3  == 0 )	 {
					vTaskDelay(1);
					if(!wantExit()) break;
					}
				}
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
				while(CB_Cap_Thanh_Sau == 0 || (abs(bientrochansauValue - target_chan_sau) > 20))	 {
				if(CB_ROI_3  == 0 && CB_ROI_1 == 0)	robotRunAngle(1250,15,-900,0.7);
				else																robotRunAngle(900,10,-900,0.7);
				vTaskDelay(1);
				if(!wantExit()) break;
					}
				// chay toi roi thi di ngang qua phai
				robotRunAngle(1800,10,-900,0.7);
				while (CB_ROI_3  == 0 )	 {
					vTaskDelay(1);
					if(!wantExit()) break;
					}
				}

		// quay mam sang tay 2
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
				while(CB_Cap_Thanh_Sau == 0 || (abs(bientrochansauValue - target_chan_sau) > 20))	 {
				if(CB_ROI_4  == 0 && CB_ROI_2 == 0)	robotRunAngle(650,15,-900,0.7);
				else																robotRunAngle(900,12,-900,0.7);
				vTaskDelay(1);
				if(!wantExit()) break;
					}
				// chay toi roi thi di ngang qua trai
				robotRunAngle(0,10,-900,0.7);
				while (CB_ROI_2  == 0 )	 {
					vTaskDelay(1);
					if(!wantExit()) break;
					}
				}
		// quay mam sang tay 3
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 0) {
				while(CB_Cap_Thanh_Sau == 0 || (abs(bientrochansauValue - target_chan_sau) > 20))	 {
				if(CB_ROI_4  == 0 && CB_ROI_2 == 0)	robotRunAngle(650,15,-900,0.7);
				else																robotRunAngle(900,12,-900,0.7);
				vTaskDelay(1);
				if(!wantExit()) break;
					}
				// chay toi roi thi di ngang qua trai
				robotRunAngle(0,10,-900,0.7);
				while (CB_ROI_2  == 0 )	 {
					vTaskDelay(1);
					if(!wantExit()) break;
							}
				}
		}
			robotStop(0);
}

//**************** Xuong_bac_200 do ô 9 **************		
void chuan_bi_gap_thang_do_9 (void) {
		int vitri_tay41 = vitri_tay41_laser_trai_GapQua;
		kiem_tra_huong_quay_tay_gap_phia_truoc();
		su_dung_chan(265);
			// chinh lai vi tri cho tay gap
			if (da_lay_tay1 == 0 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
				while( CB_Ha_Sau == 0 || (abs(bientrochansauValue - target_chan_sau) > 20)) 
					{	
					if(lazeTraiValue > vitri_tay41)			robotRunAngle(1250,15,-900,0.7);
					else																robotRunAngle(900,12,-900,0.7);
					vTaskDelay(1);
					if(!wantExit()) break; }
			}
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
				while(CB_Ha_Sau == 0 || (abs(bientrochansauValue - target_chan_sau) > 20)) 
					{	
					if(lazeTraiValue > vitri_tay41)			robotRunAngle(1250,15,-900,0.7);
					else																robotRunAngle(900,12,-900,0.7);
					vTaskDelay(1);
					if(!wantExit()) break; }
				}

		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
					while(CB_Ha_Sau == 0 || (abs(bientrochansauValue - target_chan_sau) > 20)) {
				if(CB_ROI_2  == 0 && CB_ROI_4 == 0)	robotRunAngle(650,15,-900,0.7);
				else																robotRunAngle(900,12,-900,0.7);
				vTaskDelay(1);
				if(!wantExit()) break;
					}
				// chay toi roi thi di ngang qua trai
				robotRunAngle(0,10,-900,0.7);
				while (CB_ROI_2  == 0 )	 {
					vTaskDelay(1);
					if(!wantExit()) break;
						}
			}
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 0) {
					while(CB_Ha_Sau == 0 || (abs(bientrochansauValue - target_chan_sau) > 20)) {
				if(CB_ROI_2  == 0 && CB_ROI_4 == 0)	robotRunAngle(650,15,-900,0.7);
				else																robotRunAngle(900,12,-900,0.7);
				vTaskDelay(1);
				if(!wantExit()) break;
					}
				// chay toi roi thi di ngang qua trai
				robotRunAngle(0,10,-900,0.7);
				while (CB_ROI_2  == 0 )	 {
					vTaskDelay(1);
					if(!wantExit()) break;
						}
					}
				robotStop(0); 
			}

void chuan_bi_gap_phai_200_tren_do (void ) {
		if (da_lay_tay1 == 0 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
			chinh_lai_vi_tri_laser_trai_do(vitri_tay41_laser_trai_GapQua, 200);
			su_dung_chan(565);
				for(i=0;i<250;i++)	
			{
				while(abs(bientrochansauValue - target_chan_sau) > 10)	{vTaskDelay(1); if(!wantExit())	break;}
			}
			robotRunAngle(1800,10,-900,0.1);
			vTaskDelay(2500);
		}
	
	else if (da_lay_tay1 == 1 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
			chinh_lai_vi_tri_laser_trai_do(vitri_tay41_laser_trai_GapQua, 200);
			su_dung_chan(565);
				for(i=0;i<250;i++)	
			{
				while(abs(bientrochansauValue - target_chan_sau) > 10)	{vTaskDelay(1); if(!wantExit())	break;}
			}
			robotRunAngle(1800,10,-900,0.1);
			vTaskDelay(2500);
		}
	
			/// gap lan 3
	else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {		
			su_dung_chan(265);
			// chay toi khi mat cam bien sau
			robotRunAngle(900,10,-900,0.5);
			for(i=0;i<250;i++)
					{
						while(CB_Ha_Sau == 0 || (abs(bientrochansauValue - target_chan_sau) > 10))	
					{	
						vTaskDelay (1);
						if(!wantExit())	break;
					}
				}
			chinh_lai_vi_tri_laser_trai_do(vitri_tay41_laser_trai_GapQua , 200);
			robotStop(10); 
			su_dung_chan(565);
				for(i=0;i<250;i++)	
			{
				while(abs(bientrochansauValue - target_chan_sau) > 10)	{vTaskDelay(1); if(!wantExit())	break;}
			}	
			robotRunAngle(1800,8,-900,0.1);
			vTaskDelay(2500);
		}
	/// gap lan 4
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 0) {
			su_dung_chan(265);
			// chay toi khi mat cam bien sau
			robotRunAngle(900,10,-900,0.5);
			for(i=0;i<250;i++)
					{
						while(CB_Ha_Sau == 0 || (abs(bientrochansauValue - target_chan_sau) > 10))	
					{	
						vTaskDelay (1);
						if(!wantExit())	break;
					}
				}
			chinh_lai_vi_tri_laser_trai_do(vitri_tay41_laser_trai_GapQua , 200);
			robotStop(10); 
			su_dung_chan(565);
				for(i=0;i<250;i++)	
			{
				while(abs(bientrochansauValue - target_chan_sau) > 10)	{vTaskDelay(1); if(!wantExit())	break;}
			}	
			robotRunAngle(1800,8,-900,0.1);
			vTaskDelay(2500);
		}
	
		robotStop(0); 

}


void Xuong_bac_200_do_9(void)
{	
		Xuong_bac_200(900, -900);
		
		if (TinHieu_ChuanBi_GapThang == 0 && TinHieu_ChuanBi_GapTrai == 0 && TinHieu_ChuanBi_GapPhai == 0) {
				su_dung_chan(265);
				// chay toi khi mat cam bien sau
				robotRunAngle(900,20,-900,0.7);
				for(i=0;i<1550;i++)
				{
						while(CB_Ha_Sau == 0 || (abs(bientrochansauValue - target_chan_sau) > 20))	
					{	
						if(!wantExit())	break;
						vTaskDelay (1);
					}
				}
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
	
		else if (TinHieu_ChuanBi_GapThang == 1) {
					chuan_bi_gap_thang_do_9();
					}
		else if (TinHieu_ChuanBi_GapPhai == 1) {
					chuan_bi_gap_phai_200_tren_do();
				}
			robotStop(0);
				
	}

void xuong_bac_200_do_12(void) {
		Xuong_bac_200(900, -900);
		if (TinHieu_ChuanBi_GapThang == 0 && TinHieu_ChuanBi_GapTrai == 0 && TinHieu_ChuanBi_GapPhai == 0) {
				su_dung_chan(265);
				// chay toi khi mat cam bien sau
				robotRunAngle(900,16,-900,0.5);
				for(i=0;i<1550;i++)
						{
								while(CB_Ha_Sau == 0 || (abs(bientrochansauValue - target_chan_sau) > 20))	
							{	
								if(!wantExit())	break;
								vTaskDelay (1);
							}
						}
						
				robotStop(0);
			
			}
		else if (TinHieu_ChuanBi_GapPhai == 1) {
					chuan_bi_gap_phai_200_tren_do();
				}
			robotStop(0);
}


void Leo_bac_400_ko_thanh_do(void)
{		
		Leo_bac_400(900, -900);

		su_dung_chan(265);
		if (TinHieu_ChuanBi_GapThang == 0 ) {
		// chay toi khi mat cam bien sau
		robotRunAngle(900,18,-900,0.9);
		for(i=0;i<250;i++)
				{
						while(CB_Ha_Sau == 0 || (abs(bientrochansauValue - target_chan_sau) > 20))
					{	
						vTaskDelay (1);
						if(!wantExit())	break;
					}
				}
		robotRunAngle(900,10,-900,0.9);
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
	target_chan_sau = Min_chan_sau + 250;
	
if (TinHieu_ChuanBi_GapThang == 0) {
			robotRunAngle(900,20,-900,0.7);
			for(i=0;i<1550;i++)
				{
				while(CB_Ha_Sau == 1 || CB_Cap_Thanh_Sau == 0 || (abs(bientrochansauValue - target_chan_sau) > 20)	 )	
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
						
					while( CB_Cap_Thanh_Sau == 0 ||  (abs(bientrochansauValue - target_chan_sau) > 20))	
					{	
					if(lazeTraiValue > vitri_tay41)			robotRunAngle(1150,12,-900,0.7);
					else																robotRunAngle(900,10,-900,0.7);
					vTaskDelay(1);
					if(!wantExit()) break;
								}
						}
					}
			
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
					for(i=0;i<1550;i++) {
					while( CB_Cap_Thanh_Sau == 0 ||  (abs(bientrochansauValue - target_chan_sau) > 20))	
					{	
					if(lazeTraiValue > vitri_tay41)			robotRunAngle(1150,12,-900,0.7);
					else																robotRunAngle(900,10,-900,0.7);
					vTaskDelay(1);
					if(!wantExit()) break;
								}
							}
					}

		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
						for(i=0;i<1550;i++) {
						while( CB_Cap_Thanh_Sau == 0 ||  (abs(bientrochansauValue - target_chan_sau) > 20))	
						{	
						if(lazePhaiValue > vitri_tay23)			robotRunAngle(750,12,-900,0.7);
						else																robotRunAngle(900,10,-900,0.7);
						vTaskDelay(1);
						if(!wantExit()) break;
									}
							}
						}
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 0) {
						for(i=0;i<1550;i++) {
						while( CB_Cap_Thanh_Sau == 0 ||  (abs(bientrochansauValue - target_chan_sau) > 20))	
						{	
						if(lazePhaiValue > vitri_tay23)			robotRunAngle(750,12,-900,0.7);
						else																robotRunAngle(900,10,-900,0.7);
						vTaskDelay(1);
						if(!wantExit()) break;
										}
								}
							}
				}
		robotStop(0); 		
}

//**************** Xuong_bac_200 ô 4********
void chuan_bi_gap_thang_do_4(void) {
	int vitri_tay23 = vitri_tay23_phai_laser_GapQua;
		kiem_tra_huong_quay_tay_gap_phia_truoc();
		su_dung_chan(510);
//		KT_Ha_Tay = 1;
		if (da_lay_tay1 == 0 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
			for(i=0;i<1550;i++) {
				while( CB_Cap_Thanh_Sau == 0 || (abs(bientrochansauValue - target_chan_sau) > 20) )	{
						if(CB_ROI_1  == 0 && CB_ROI_3 == 0)	robotRunAngle(1550,14,-900,0.7);
						else																robotRunAngle(900,10,-900,0.7);
						vTaskDelay(1);
						if(!wantExit()) break;
									}
								}
						// chay toi roi thi di ngang qua phai
						for(i=0;i<1550;i++) {
						robotRunAngle(1800,10,-900,0.7);
						while (CB_ROI_3  == 0 )	 {
							vTaskDelay(1);
							if(!wantExit()) break;
								}
							}
			}
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
				for(i=0;i<1550;i++) {
				while( CB_Cap_Thanh_Sau == 0 || (abs(bientrochansauValue - target_chan_sau) > 20) )	{
						if(CB_ROI_1  == 0 && CB_ROI_3 == 0)	robotRunAngle(1550,14,-900,0.7);
						else																robotRunAngle(900,10,-900,0.7);
						vTaskDelay(1);
						if(!wantExit()) break;
									}
								}
						// chay toi roi thi di ngang qua phai
						for(i=0;i<1550;i++) {
						robotRunAngle(1800,10,-900,0.7);
						while (CB_ROI_3  == 0 )	 {
							vTaskDelay(1);
							if(!wantExit()) break;
								}
							}
				}

		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
			for(i=0;i<150;i++) {
						while( CB_Cap_Thanh_Sau == 0 ||(abs(bientrochansauValue - target_chan_sau) > 20))	
						{	
						if(lazePhaiValue > vitri_tay23)			robotRunAngle(350,14,-900,0.7);
						else																robotRunAngle(900,10,-900,0.7);
						vTaskDelay(1);
						if(!wantExit()) break;
									}
							}
					}
		
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 0) {
			for(i=0;i<1550;i++) {
						while( CB_Cap_Thanh_Sau == 0 ||(abs(bientrochansauValue - target_chan_sau) > 20))	
						{	
						if(lazePhaiValue > vitri_tay23)			robotRunAngle(350,14,-900,0.7);
						else																robotRunAngle(900,10,-900,0.7);
						vTaskDelay(1);
						if(!wantExit()) break;
									}
							}
					}	
				robotStop(0);
				su_dung_chan(565);
				robotRunAngle(900,10,-900,0.7);
				vTaskDelay(1500);
		}

void Lay_ben_phai_bac_200_duoi_do_5(void) {
			Lay_ben_phai_bac_200_duoi();
			robotStop(0);
			
	if (TinHieu_ChuanBi_GapThang == 1) {
			kiem_tra_huong_quay_tay_gap_phia_truoc();
			vTaskDelay(8000);
			chuan_bi_gap_thang_do_4();
				}
			robotStop(0);
}

void Lay_ben_phai_bac_200_duoi_do_6(void) {
			Lay_ben_phai_bac_200_duoi();
			robotStop(0);
			
	if (TinHieu_ChuanBi_GapThang == 1) {
			kiem_tra_huong_quay_tay_gap_phia_truoc();
			vTaskDelay(8000);
				// chay toi khi mat cam bien sau
			robotRunAngle(900,10,-900,0.5);
			for(i=0;i<1550;i++)
					{
							while( CB_Ha_Sau == 0)	
						{	
							if(!wantExit())	break;
							vTaskDelay (1);
						}
					}
					
			robotStop(0);
			vTaskDelay (1000);
			
		di_tren_buc_khong_thanh_2_ben_do();
				}
			robotStop(0);
}

void Lay_ben_phai_bac_200_tren_do_9(void) {
			Lay_ben_phai_bac_200_tren();
			robotStop(0);
	
	if (TinHieu_ChuanBi_GapThang == 1) {
			kiem_tra_huong_quay_tay_gap_phia_truoc();
			vTaskDelay(8000);
			chuan_bi_gap_thang_do_9();
		}
			robotStop(0);
}


void Lay_ben_phai_bac_200_duoi_do_8(void) {
			Lay_ben_phai_bac_200_duoi();
			
	if (TinHieu_ChuanBi_GapThang == 1) {
			kiem_tra_huong_quay_tay_gap_phia_truoc();
			vTaskDelay(8000);
				// chay toi khi mat cam bien sau
			robotRunAngle(900,10,-900,0.5);
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
		robotStop(0);
}


void chuan_bi_gap_trai_200_tren_do_4 (void ) {
	su_dung_chan(510);
	if (da_lay_tay1 == 0 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
				for(i=0;i<1550;i++) {
						while( CB_Cap_Thanh_Sau == 0 ||  (abs(bientrochansauValue - target_chan_sau) > 20))	
						{	
						if(lazePhaiValue > vitri_tay23_phai_laser_GapQua)			robotRunAngle(550,14,-900,0.7);
						else																									robotRunAngle(900,10,-900,0.7);
						vTaskDelay(1);
						if(!wantExit()) break;
										}
								}
					chinh_lai_vi_tri_laser_phai_do(vitri_tay23_phai_laser_GapQua, 1000);
					su_dung_chan(565);
						for(i=0;i<250;i++)	
					{
						while(abs(bientrochansauValue - target_chan_sau) > 10)	{vTaskDelay(1); if(!wantExit())	break;}
					}
					robotRunAngle(0,10,-900,0.1);
					vTaskDelay(3000);
		}
	else if (da_lay_tay1 == 1 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
					for(i=0;i<1550;i++) {
						while( CB_Cap_Thanh_Sau == 0 ||  (abs(bientrochansauValue - target_chan_sau) > 10))	
						{	
						if(lazePhaiValue > vitri_tay23_phai_laser_GapQua)			robotRunAngle(550,14,-900,0.7);
						else																									robotRunAngle(900,10,-900,0.7);
						vTaskDelay(1);
						if(!wantExit()) break;
										}
								}
					chinh_lai_vi_tri_laser_phai_do(vitri_tay23_phai_laser_GapQua, 1000);
					su_dung_chan(565);
						for(i=0;i<250;i++)	
					{
						while(abs(bientrochansauValue - target_chan_sau) > 10)	{vTaskDelay(1); if(!wantExit())	break;}
					}
					robotRunAngle(0,10,-900,0.1);
					vTaskDelay(3000);
				}
	else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
					chinh_lai_vi_tri_laser_phai_do(vitri_tay23_phai_laser_GapQua, 1000);
					robotRunAngle(900,7,-900,0.5);
							for(i=0;i<150;i++)
							{
								while(lazeSauValue > 31 || (abs(bientrochansauValue - target_chan_sau) > 10))	
								{	
									vTaskDelay (1);
									if(!wantExit())	break;
								}
							}
					su_dung_chan(565);
						for(i=0;i<250;i++)	
					{
						while(abs(bientrochansauValue - target_chan_sau) > 10)	{vTaskDelay(1); if(!wantExit())	break;}
					}
						robotRunAngle(0,10,-900,0.1);
						vTaskDelay(3000);
				}
	
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 0) {
					chinh_lai_vi_tri_laser_phai_do(vitri_tay23_phai_laser_GapQua, 1000);
					robotRunAngle(900,7,-900,0.5);
							for(i=0;i<150;i++)
							{
								while(lazeSauValue > 31 || (abs(bientrochansauValue - target_chan_sau) > 10))	
								{	
									vTaskDelay (1);
									if(!wantExit())	break;
								}
							}
					su_dung_chan(565);
						for(i=0;i<250;i++)	
					{
						while(abs(bientrochansauValue - target_chan_sau) > 10)	{vTaskDelay(1); if(!wantExit())	break;}
					}
						robotRunAngle(0,10,-900,0.1);
					vTaskDelay(3000);
				}
			
				robotStop(0); 
}

void Xuong_bac_200_do_4(void)
{	
	Xuong_bac_200(900,-900);		
	
	// KHONG CO TIN HIEU GAP
	if (TinHieu_ChuanBi_GapThang == 0 && TinHieu_ChuanBi_GapTrai == 0 && TinHieu_ChuanBi_GapPhai == 0) {
		Nang_cuc_nhanh();
		target_chan_truoc = Min_chan_truoc + 250;
		target_chan_sau = Min_chan_sau + 250;
		
		robotRunAngle(900,20,-900,0.7);

		for(i=0;i<1550;i++)
				{
					while(CB_Ha_Sau == 1 || (abs(bientrochansauValue - target_chan_sau) > 10) )	
						
					{	
						if(!wantExit())	break;
						vTaskDelay (1);
					}
				}
		robotRunAngle(900,10,-900,0.7);
		for(i=0;i<1550;i++)
				{
					while(CB_Ha_Sau == 1  || CB_Cap_Thanh_Sau == 0 || (abs(bientrochansauValue - target_chan_sau) > 10))	
					{	
						if(!wantExit())	break;
						vTaskDelay (1);
					}
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
	
void Lay_ben_trai_bac_200_tren_do_5_6(void) {
			Lay_ben_trai_bac_200_tren();
			robotStop(0);
			
	if (TinHieu_ChuanBi_GapThang == 1) {
			kiem_tra_huong_quay_tay_gap_phia_truoc();
			vTaskDelay(8000);
			chuan_bi_gap_thang_do_4();			
				}
	}

void chuan_bi_gap_phai_200_duoi_do_5 (void ) {
		if (da_lay_tay1 == 0 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
					ha_sat_xuong();
					{
					while(abs(bientrochansauValue - target_chan_sau) > 15)	{vTaskDelay(1); if(!wantExit())	break;}
						}
					robotRunAngle(1800,10,-900,0.7);
					for(i=0;i<150;i++)
					{
						while(CB_ROI_1 == 0 || (abs(bientrochansauValue - target_chan_sau) > 10))	
						{	
							vTaskDelay (1);
							if(!wantExit())	break;
						}
					}
					}
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
					ha_sat_xuong();
					{
					while(abs(bientrochansauValue - target_chan_sau) > 15)	{vTaskDelay(1); if(!wantExit())	break;}
						}
					robotRunAngle(1800,10,-900,0.7);
					for(i=0;i<150;i++)
					{
						while(CB_ROI_1 == 0 || (abs(bientrochansauValue - target_chan_sau) > 10))	
						{	
							vTaskDelay (1);
							if(!wantExit())	break;
						}
					}
				}
	
			//// gap duoi lan 3
		else if  (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 0) {
					ha_sat_xuong();
					while(HT_3 == 0 && HT_4 == 0 || (abs(bientrochansauValue - target_chan_sau) > 10))	 {
					if(CB_ROI_1  == 0 && CB_ROI_3 == 0)	robotRunAngle(1250,14,-900,0.7);
					else																robotRunAngle(900,10,-900,0.7);
					vTaskDelay(1);
					if(!wantExit()) break;
								}
					// chay toi roi thi di ngang qua phai
					robotRunAngle(1800,8,-900,0.7);
					while (CB_ROI_1  == 0 )	 {
						vTaskDelay(1);
						if(!wantExit()) break;
								}
				}
		//// gap duoi lan 4
		else if  (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 0) {
					ha_sat_xuong();
					while(HT_3 == 0 && HT_4 == 0 || (abs(bientrochansauValue - target_chan_sau) > 10))	 {
					if(CB_ROI_1  == 0 && CB_ROI_3 == 0)	robotRunAngle(1250,14,-900,0.7);
					else																robotRunAngle(900,10,-900,0.7);
					vTaskDelay(1);
					if(!wantExit()) break;
								}
					// chay toi roi thi di ngang qua phai
					robotRunAngle(1800,8,-900,0.7);
					while (CB_ROI_1  == 0 )	 {
						vTaskDelay(1);
						if(!wantExit()) break;
								}
				}
				robotStop(0);
}


/// ****** leo bac 200 o id  5 san xanh
void Leo_bac_200_do_5(void) {	
		Leo_bac_200(900, -900);
	  Nang_cuc_nhanh();
		target_chan_truoc = Min_chan_truoc + 250;
		target_chan_sau = Min_chan_sau + 250;
		
		// KHONG CO TIN HIEU GAP
		if (TinHieu_ChuanBi_GapThang == 0 && TinHieu_ChuanBi_GapTrai == 0 && TinHieu_ChuanBi_GapPhai == 0) {
				robotRunAngle(900,20,-900,0.7);
				for(i=0;i<1550;i++)
						{
					while(CB_Ha_Sau == 1 ||  CB_Cap_Thanh_Sau == 0 || (abs(bientrochansauValue - target_chan_sau) > 10) )	
							{	
								if(!wantExit())	break;
								vTaskDelay (1);
							}
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
//		// CO LENH GAP PHAI
		else if (TinHieu_ChuanBi_GapPhai == 1 ) {
					chuan_bi_gap_phai_200_duoi_do_5();
		}
		
			robotStop(0); 			
}

void chuan_bi_gap_thang_do_7(void) {
		int vitri_tay23 = vitri_tay23_phai_laser_GapQua;
		kiem_tra_huong_quay_tay_gap_phia_truoc();
		su_dung_chan(265);

	// chinh lai vi tri cho tay gap
	if (da_lay_tay1 == 0 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
				while(CB_Ha_Sau == 0 || (abs(bientrochansauValue - target_chan_sau) > 15)) {
				if(CB_ROI_1  == 0 && CB_ROI_3 == 0)	robotRunAngle(1250,12,-900,0.7);
				else																robotRunAngle(900,8,-900,0.7);
				vTaskDelay(1);
				if(!wantExit()) break;
							}
				// chay toi roi thi di ngang qua phai
				robotRunAngle(1800,8,-900,0.7);
				while (CB_ROI_3  == 0 )	 {
					vTaskDelay(1);
					if(!wantExit()) break;
						}
			}
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
				while( CB_Ha_Sau == 0 || (abs(bientrochansauValue - target_chan_sau) > 15)) {
				if(CB_ROI_1  == 0 && CB_ROI_3 == 0)	robotRunAngle(1250,12,-900,0.7);
				else																robotRunAngle(900,8,-900,0.7);
				vTaskDelay(1);
				if(!wantExit()) break;
							}
				// chay toi roi thi di ngang qua phai
				robotRunAngle(1800,8,-900,0.7);
				while (CB_ROI_3  == 0 )	 {
					vTaskDelay(1);
					if(!wantExit()) break;
						}
			}

		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
					while(CB_Ha_Sau == 0 || (abs(bientrochansauValue - target_chan_sau) > 15)) 
					{	
						if(lazePhaiValue > vitri_tay23)			robotRunAngle(650,12,-900,0.7);
						else																robotRunAngle(900,8,-900,0.7);
						vTaskDelay(1);
						if(!wantExit()) break;
									}
				}
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 0) {
						while(CB_Ha_Sau == 0 || (abs(bientrochansauValue - target_chan_sau) > 15)) 
					{	
						if(lazePhaiValue > vitri_tay23)			robotRunAngle(650,12,-900,0.7);
						else																robotRunAngle(900,8,-900,0.7);
						vTaskDelay(1);
						if(!wantExit()) break;
									}
								}
			robotStop(0);
}

void chuan_bi_gap_trai_200_tren_do_7_10 (void ) {
	if (da_lay_tay1 == 0 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
				su_dung_chan(265);
				while(CB_Ha_Sau == 0 || (abs(bientrochansauValue - target_chan_sau) > 10)) 
					{	
						if(lazePhaiValue > vitri_tay23_phai_laser_GapQua)			robotRunAngle(650,12,-900,0.7);
						else																									robotRunAngle(900,10,-900,0.7);
						vTaskDelay(1);
						if(!wantExit()) break;
									}
				robotStop(0); 
				chinh_lai_vi_tri_laser_phai_do(vitri_tay23_phai_laser_GapQua, 200);
				robotRunAngle(0,7,-900,0.1);
				vTaskDelay(2000);
				su_dung_chan(565);
					for(i=0;i<250;i++)	
				{
					while(abs(bientrochansauValue - target_chan_sau) > 8)	{vTaskDelay(1); if(!wantExit())	break;}
				}		
		}
	else if (da_lay_tay1 == 1 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
				su_dung_chan(265);
				while(CB_Ha_Sau == 0 || (abs(bientrochansauValue - target_chan_sau) > 10)) 
					{	
					if(lazePhaiValue > vitri_tay23_phai_laser_GapQua)			robotRunAngle(650,12,-900,0.7);
					else																									robotRunAngle(900,10,-900,0.7);
					vTaskDelay(1);
					if(!wantExit()) break;
									}
				robotStop(0); 
				chinh_lai_vi_tri_laser_phai_do(vitri_tay23_phai_laser_GapQua, 200);
				robotRunAngle(0,7,-900,0.1);
				vTaskDelay(2000);
				su_dung_chan(565);
					for(i=0;i<250;i++)	
				{
					while(abs(bientrochansauValue - target_chan_sau) > 8)	{vTaskDelay(1); if(!wantExit())	break;}
				}	
		}
	else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
				su_dung_chan(500);
					for(i=0;i<250;i++)	
				{
					while(abs(bientrochansauValue - target_chan_sau) > 10)	{vTaskDelay(1); if(!wantExit())	break;}
				}
				vTaskDelay(1500);
				chinh_lai_vi_tri_laser_phai_do(vitri_tay23_phai_laser_GapQua, 200);
				robotRunAngle(0,7,-900,0.1);
				vTaskDelay(2000);
				su_dung_chan(565);
					for(i=0;i<250;i++)	
				{
					while(abs(bientrochansauValue - target_chan_sau) > 10)	{vTaskDelay(1); if(!wantExit())	break;}
				}		
		}
	
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 0) {
				su_dung_chan(500);
					for(i=0;i<250;i++)	
				{
					while(abs(bientrochansauValue - target_chan_sau) > 10)	{vTaskDelay(1); if(!wantExit())	break;}
				}
				vTaskDelay(2500);
				chinh_lai_vi_tri_laser_phai_do(vitri_tay23_phai_laser_GapQua, 200);
				robotRunAngle(0,7,-900,0.2);
				vTaskDelay(2500);
				su_dung_chan(565);
					for(i=0;i<250;i++)	
				{
					while(abs(bientrochansauValue - target_chan_sau) > 10)	{vTaskDelay(1); if(!wantExit())	break;}
				}
		}
	
		robotStop(0); 
}


void Leo_bac_200_do_7(void)  {	
		Leo_bac_200(900, -900);
			// KHONG CO TIN HIEU GAP
	if (TinHieu_ChuanBi_GapThang == 0 && TinHieu_ChuanBi_GapTrai == 0 && TinHieu_ChuanBi_GapPhai == 0) {
		su_dung_chan(265);
		// chay toi khi mat cam bien sau
		robotRunAngle(900,20,-900,0.7);
		for(i=0;i<1550;i++)
				{
						while(CB_Ha_Sau == 0 || (abs(bientrochansauValue - target_chan_sau) > 10)	)	
			
					{	
						if(!wantExit())	break;
						vTaskDelay (1);
					}
				}
				
		robotRunAngle(900,10,-900,0.7);
		for(i=0;i<1550;i++)
				{
						while(CB_Ha_Sau == 0 || CB_vtri_leo == 0 || (abs(bientrochansauValue - target_chan_sau) > 10)	)	
			
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
		// CO TIN HIEU GAP TRAI
	else if (TinHieu_ChuanBi_GapTrai == 1) {
					chuan_bi_gap_trai_200_tren_do_7_10();
			}
		}

	
void xuong_bac_200_do_10 (void) {
	Xuong_bac_200(900, -900);
		if (TinHieu_ChuanBi_GapThang == 0 && TinHieu_ChuanBi_GapTrai == 0 && TinHieu_ChuanBi_GapPhai == 0) {
				su_dung_chan(265);
				// chay toi khi mat cam bien sau
				robotRunAngle(900,15,-900,0.5);
				for(i=0;i<1550;i++)
						{
								while(CB_Ha_Sau == 0 || (abs(bientrochansauValue - target_chan_sau) > 10))	
							{	
								if(!wantExit())	break;
								vTaskDelay (1);
							}
						}
						
				robotStop(0);
			
			}
		
	else if (TinHieu_ChuanBi_GapTrai == 1) {
					chuan_bi_gap_trai_200_tren_do_7_10();
			}
}

void Lay_ben_trai_bac_200_tren_do_7_10(void) {
			Lay_ben_trai_bac_200_tren();
			robotStop(0);
			
	if (TinHieu_ChuanBi_GapThang == 1) {
			kiem_tra_huong_quay_tay_gap_phia_truoc();
			vTaskDelay(4000);
			su_dung_chan(265);
			for(i=0;i<50;i++)		
				{
					while(abs(bientrochansauValue - target_chan_sau) > 15)	{vTaskDelay(1); if(!wantExit())	break;}
				}
		
			chuan_bi_gap_thang_do_7();
			
				}
}

void Lay_ben_trai_bac_200_duoi_do_8_11(void) {
			Lay_ben_trai_bac_200_duoi();
			robotStop(0);
			
	if (TinHieu_ChuanBi_GapThang == 1) {
			kiem_tra_huong_quay_tay_gap_phia_truoc();
			vTaskDelay(8000);
			chuan_bi_gap_thang_xanh_4();
				}
}

void Lay_ben_trai_bac_200_duoi_do_ko_thanh(void) {
			Lay_ben_trai_bac_200_duoi();
			robotStop(0);
			
	if (TinHieu_ChuanBi_GapThang == 1) {
		kiem_tra_huong_quay_tay_gap_phia_truoc();
				// chay toi khi mat cam bien sau
		robotRunAngle(900,10,-900,0.5);
		for(i=0;i<1550;i++)
				{
						while( CB_Ha_Sau == 0)	
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

void xuong_bac_200_11_do(void) {
		Xuong_bac_200(900, -900);
		robotStop(0);
		if (TinHieu_ChuanBi_GapThang == 0 && TinHieu_ChuanBi_GapTrai == 0 && TinHieu_ChuanBi_GapPhai == 0) {
				su_dung_chan(265);

				// chay toi khi mat cam bien sau
				robotRunAngle(900,15,-900,0.5);
				for(i=0;i<1550;i++)
						{
								while(CB_Ha_Sau == 0 || (abs(bientrochansauValue - target_chan_sau) > 10))	
							{	
								if(!wantExit())	break;
								vTaskDelay (1);
							}
						}
						
				robotStop(0);
			
			}
	
		else if (TinHieu_ChuanBi_GapTrai == 1 ) {
				chuan_bi_gap_trai_200_duoi_ko_thanh_do();
		}
		// CO LENH GAP PHAI
		else if (TinHieu_ChuanBi_GapPhai == 1 ) {
					chuan_bi_gap_phai_200_duoi_ko_thanh_do();
		}
}
