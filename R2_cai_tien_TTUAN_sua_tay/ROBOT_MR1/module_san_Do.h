	// ***************** CHINH LAI VI TRI LAZER SAN DO **************
void chuan_bi_gap_phai_200_duoi_do_5 (void ) ;


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

void chinh_lai_vi_tri_VK_do(int vitri, int gia_tri_lap, int min, int max, int sai_so)
{
	int speed ;
	int dieuchinh;
		for(i=0;i<gia_tri_lap;i++)
				{
		while(abs(lazeTraiValue - vitri) > sai_so)	{
			dieuchinh = lazeTraiValue - vitri;
			speed = custom_smooth_speed(dieuchinh,min, max);
			
					if  ((lazeTraiValue - vitri)> 0 ) {
							robotRunAngle(-100, speed, 900, 0.5);
					}
					else if ((lazeTraiValue - vitri)< 0) {
					
					robotRunAngle(1900, speed, 900, 0.5);
					
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

		
void chinh_lai_vi_tri_laser_phai_custom_do(int vitri, int gia_tri_lap,int min_toc, int max_toc, int sai_so)
{
	int speed ;
	int dieuchinh;
		for(i=0;i<gia_tri_lap;i++)
				{
		while(abs(lazePhaiValue - vitri) > sai_so)	{
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
	su_dung_chan(720);
	for(i=0;i<150;i++)		
	{
		while(abs(bientrochansauValue - target_chan_sau) > 15)	{vTaskDelay(1); if(!wantExit())	break;}
	}
	vTaskDelay(1000);
	
	chinh_lai_vi_tri_laser_phai_custom_do(vi_tri_cua_rung_do_3_lazer_phai_tay_41 , 1000, 12, 45, 2);
	
		
	robotRunAngle(900,12,-900,0.6);
	for(i=0;i<1050;i++)	
	{	
		while(CB_Cap_Thanh_Sau == 0)	{vTaskDelay(1); if(!wantExit())	break;}
	}
	robotStop(40);

}

void qua_trai_len_bac_200_cua_vao_do(void) {
		su_dung_chan(720);
	
		for(i=0;i<150;i++)		
		{
			while(abs(bientrochansauValue - target_chan_sau) > 15)	{vTaskDelay(1); if(!wantExit())	break;}
		}
	
		for(i=0;i<1050;i++)	
			{	
				while( lazePhaiValue < 320)	{vTaskDelay(1); if(!wantExit())	break;}
			}
			vTaskDelay(5000);
			robotStop(0);
	if ( TinHieu_ChuanBi_GapThang == 1 ) {
				run_encoder(10000, 0, -900, 45, 5, 4500, 100);

				su_dung_chan(575);
				robotRunAngle(900,12,-900,0.6);
				for(i=0;i<1050;i++)	
					{	
					while( CB_Cap_Thanh_Sau == 0)	{vTaskDelay(1); if(!wantExit())	break;}
					}
					vTaskDelay(1000);
				}
		
	else if  (TinHieu_ChuanBi_GapThang == 0 ) {
			if (chay_ngang_qua_o3_do == 0) {
				
					run_encoder(10000, 0, -900, 45, 5, 4500, 100);
					robotStop(0);

			}
			else if (chay_ngang_qua_o3_do == 1) {

					run_encoder(21000, 40, -900, 45, 12, 5000, 100);
					robotStop(0);
				}
		}
		
	bai_db = 1;
	robotStop(0);
}

//============== Sang phai lên bac 400 o ria rung ===================

void qua_phai_len_bac_400_do(void) {
	su_dung_chan(720);
	
	for(i=0;i<150;i++)		
	{
		while(abs(bientrochansauValue - target_chan_sau) > 15)	{vTaskDelay(1); if(!wantExit())	break;}
	}
	vTaskDelay(1000);

	chinh_lai_vi_tri_laser_phai_custom_do(vi_tri_cua_rung_do_1_lazer_phai_tay_23 , 1000, 12, 45, 3);
	
	robotStop(0);
	robotRunAngle(900,12,-900,0.5);
	for(i=0;i<1050;i++)	
	{	
		while(CB_Cap_Thanh_Sau == 0)	{vTaskDelay(1); if(!wantExit())	break;}
	}

	robotStop(40);

}

void qua_phai_len_bac_200_cua_vao_do(void) {
	su_dung_chan(720);
	
	for(i=0;i<150;i++)		
	{
		while(abs(bientrochansauValue - target_chan_sau) > 15)	{vTaskDelay(1); if(!wantExit())	break;}
	}
	
	robotRunAngle(-900,10,-900,0.6);
	vTaskDelay(3500);
	robotStop(20);
	for(i=0;i<1050;i++)	
	{	
		while( lazeTraiValue < 320)	{vTaskDelay(1); if(!wantExit())	break;}
	}
	robotStop(0);
		if ( TinHieu_ChuanBi_GapThang == 1 ) {

			
				run_encoder(10000, 1800, -900, 45, 5, 4500, 50);
				robotStop(0);
						
				su_dung_chan(575);
				robotRunAngle(900,12,-900,0.6);
				for(i=0;i<1050;i++)	
				{	
					while( CB_Cap_Thanh_Sau == 0)	{vTaskDelay(1); if(!wantExit())	break;}
				}
					vTaskDelay(1000);
				}
		
		else if  (TinHieu_ChuanBi_GapThang == 0 && TinHieu_ChuanBi_GapTrai == 0 && TinHieu_ChuanBi_GapPhai == 0) {
				if (chay_ngang_qua_o1_do == 0) {
						run_encoder(10000, 1800, -900, 45, 5, 4500, 50);

			}
			else if (chay_ngang_qua_o1_do == 1) {
						run_encoder(21000, 1760, -900, 45, 12, 5000, 50);
				
						}
				}
		robotStop(0);
		bai_db = 1;
//		
}

////////////////// CODE DI CHUYEN SAN DO ****************************************

void di_tren_buc_khong_thanh_2_ben_do(void) {
		kiem_tra_huong_quay_tay_gap_phia_truoc();
		su_dung_chan(265);
		if (da_lay_tay1 == 0 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
				while(CB_Ha_Sau == 0) {
				if(CB_ROI_3  == 0 && CB_ROI_1 == 0)	robotRunAngle(1400,18,-900,0.7); // di voi goc xéo phai
				else																robotRunAngle(900,20,-900,0.7), Tay2_len;; // di thang
				vTaskDelay(1);
				if(!wantExit()) break;
					}
			}
		
	else if (da_lay_tay1 == 1 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
				while( CB_Ha_Sau == 0) {
				if(CB_ROI_3  == 0 && CB_ROI_1 == 0)	robotRunAngle(1400,18,-900,0.7); // di xeo phai
				else																robotRunAngle(900,20,-900,0.7), Tay1_len;;  // di thang 
				vTaskDelay(1);
				if(!wantExit()) break;
					}
				}
		// quay mam sang tay 2
			else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
				while( CB_Ha_Sau == 0) {
				if(CB_ROI_2  == 0 && CB_ROI_4 == 0)	robotRunAngle(300,18,-900,0.7); //di xeo qua trai
				else																robotRunAngle(900,20,-900,0.7), Tay2_len;; //di thang
				vTaskDelay(1);
				if(!wantExit()) break;
							}
				}
		
		// quay mam sang tay 3
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 0) {
				while(CB_Ha_Sau == 0) {
				if(CB_ROI_2  == 0 && CB_ROI_4 == 0)	robotRunAngle(300,18,-900,0.7);
				else																robotRunAngle(900,20,-900,0.7), Tay1_len;;
				vTaskDelay(1);
				if(!wantExit()) break;
						}
					}
		
			robotRunAngle(900,10,-900,0.3);
			RESET_ENCODER(); 
			while(abs(ENCODER_FR()) + abs(ENCODER_FL()) < 250)	{vTaskDelay (1); if(!wantExit())	break;}
			robotStop(0);
			
			
					}

void chuan_bi_gap_trai_200_duoi_ko_thanh_do (void ) {
			if (da_lay_tay1 == 0 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
					ha_sat_xuong();
					robotRunAngle(0,22,-900,0.8);
					for(i=0;i<150;i++)
					{
						while(CB_ROI_2 == 0 )	
						{	
							vTaskDelay (1);
							if(!wantExit())	break;
						}
					}
					Tay2_len;
					robotRunAngle(0,8,-900,0.8);
					for(i=0;i<150;i++)
					{
						while(CB_ROI_4 == 0 )	
						{	
							vTaskDelay (1);
							if(!wantExit())	break;
						}
					}
					robotStop(0);
					
					robotRunAngle(900,16,-900,0.8);
					RESET_ENCODER(); 
					while(abs(ENCODER_FR()) + abs(ENCODER_FL()) < 1750)	{
						 if(CB_Ha_Sau == 1)
							{
									robotStop(0);
									break;
							}
						vTaskDelay (1); 
						if(!wantExit())	break;
					}
					robotStop(0);
					
			}
		
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
					ha_sat_xuong();
					robotRunAngle(0,22,-900,0.8);
					for(i=0;i<150;i++)
					{
						while(CB_ROI_2 == 0 )	
						{	
							vTaskDelay (1);
							if(!wantExit())	break;
						}
					}
					Tay2_len;
					robotRunAngle(0,8,-900,0.8);
					for(i=0;i<150;i++)
					{
						while(CB_ROI_4 == 0 )	
						{	
							vTaskDelay (1);
							if(!wantExit())	break;
						}
					}
					robotStop(0);
					
					robotRunAngle(900,16,-900,0.8);
					RESET_ENCODER(); 
					while(abs(ENCODER_FR()) + abs(ENCODER_FL()) < 1750)	{
						 if(CB_Ha_Sau == 1)
							{
									robotStop(0);
									break;
							}
						vTaskDelay (1); 
						if(!wantExit())	break;
					}
					robotStop(0);
					
			}
			//// gap duoi lan 3
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {		
					ha_sat_xuong();
					for(i=0;i<50;i++)		
				{
					while(abs(bientrochansauValue - target_chan_sau) > 15)	{vTaskDelay(1); if(!wantExit())	break;}
				}
					robotRunAngle(0,22,-900,0.8);
					for(i=0;i<150;i++)
					{
						while(CB_ROI_2 == 0 )	
						{	
							vTaskDelay (1);
							if(!wantExit())	break;
						}
					}
					Tay2_len;
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
					robotRunAngle(0,22,-900,0.8);
					for(i=0;i<150;i++)
					{
						while(CB_ROI_2 == 0 )	
						{	
							vTaskDelay (1);
							if(!wantExit())	break;
						}
					}
					Tay1_len;
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
					while(abs(bientrochansauValue - target_chan_sau) > 40)	{vTaskDelay(1); if(!wantExit())	break;}
						}
					robotRunAngle(1850,22,-900,0.8);
					for(i=0;i<150;i++)
					{
						while(CB_ROI_3 == 0 ||  (abs(bientrochansauValue - target_chan_sau) > 30))	
						{	
							vTaskDelay (1);
							if(!wantExit())	break;
						}
					}
					Tay2_len;
					robotRunAngle(1800,8,-900,0.8);
					for(i=0;i<150;i++)
					{
						while(CB_ROI_1 == 0 )	
						{	
							vTaskDelay (1);
							if(!wantExit())	break;
						}
					}
					robotStop(0);
			}
		
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
					ha_sat_xuong();
					{
					while(abs(bientrochansauValue - target_chan_sau) > 40)	{vTaskDelay(1); if(!wantExit())	break;}
						}
					robotRunAngle(1850,22,-900,0.8);
					for(i=0;i<150;i++)
					{
						while(CB_ROI_3 == 0 ||  (abs(bientrochansauValue - target_chan_sau) > 30))	
						{	
							vTaskDelay (1);
							if(!wantExit())	break;
						}
					}
					Tay1_len;
					robotRunAngle(1800,8,-900,0.8);
					for(i=0;i<150;i++)
					{
						while(CB_ROI_1 == 0 )	
						{	
							vTaskDelay (1);
							if(!wantExit())	break;
						}
					}
					robotStop(0);
			}
			//// gap duoi lan 3
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {		
					ha_sat_xuong();
					robotRunAngle(1800,22,-900,0.8);
					for(i=0;i<150;i++)
					{
						while(CB_ROI_3 == 0 ||  (abs(bientrochansauValue - target_chan_sau) > 30))	
						{	
							vTaskDelay (1);
							if(!wantExit())	break;
						}
					}
					Tay2_len;
					robotRunAngle(1800,8,-900,0.8);
					for(i=0;i<150;i++)
					{
						while(CB_ROI_1 == 0 )	
						{	
							vTaskDelay (1);
							if(!wantExit())	break;
						}
					}
					robotStop(0);
					
					robotRunAngle(900,16,-900,0.8);
					RESET_ENCODER(); 
					while(abs(ENCODER_FR()) + abs(ENCODER_FL()) < 1750)	{
						 if(CB_Ha_Sau == 1)
							{
									robotStop(0);
									break;
							}
						vTaskDelay (1); 
						if(!wantExit())	break;
					}
					robotStop(0);
					
				}
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 0) {		
					ha_sat_xuong();
					robotRunAngle(1800,22,-900,0.8);
					for(i=0;i<150;i++)
					{
						while(CB_ROI_3 == 0 ||  (abs(bientrochansauValue - target_chan_sau) > 30))	
						{	
							vTaskDelay (1);
							if(!wantExit())	break;
						}
					}
					Tay1_len;
					robotRunAngle(1800,8,-900,0.8);
					for(i=0;i<150;i++)
					{
						while(CB_ROI_1 == 0 )	
						{	
							vTaskDelay (1);
							if(!wantExit())	break;
						}
					}
					robotStop(0);
					
					robotRunAngle(900,16,-900,0.8);
					RESET_ENCODER(); 
					while(abs(ENCODER_FR()) + abs(ENCODER_FL()) < 1750)	{
						 if(CB_Ha_Sau == 1)
							{
									robotStop(0);
									break;
							}
						vTaskDelay (1); 
						if(!wantExit())	break;
					}
					robotStop(0);
					
				}
				robotStop(0);
}

void chuan_bi_gap_phai_200_duoi_ko_thanh_do_8(void ) {
		if (da_lay_tay1 == 0 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
					ha_sat_xuong();
					{
					while(abs(bientrochansauValue - target_chan_sau) > 40)	{vTaskDelay(1); if(!wantExit())	break;}
						}
					robotRunAngle(1800,24,-900,0.8);
					for(i=0;i<150;i++)
					{
						while(CB_ROI_3 == 0 ||  (abs(bientrochansauValue - target_chan_sau) > 30))	
						{	
							vTaskDelay (1);
							if(!wantExit())	break;
						}
					}
					Tay2_len;
					robotRunAngle(1800,8,-900,0.8);
					for(i=0;i<150;i++)
					{
						while(CB_ROI_1 == 0 )	
						{	
							vTaskDelay (1);
							if(!wantExit())	break;
						}
					}
			}
		
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
					ha_sat_xuong();
					{
					while(abs(bientrochansauValue - target_chan_sau) > 40)	{vTaskDelay(1); if(!wantExit())	break;}
						}
					robotRunAngle(1800,24,-900,0.8);
					for(i=0;i<150;i++)
					{
						while(CB_ROI_3 == 0 ||  (abs(bientrochansauValue - target_chan_sau) > 30))	
						{	
							vTaskDelay (1);
							if(!wantExit())	break;
						}
					}
					Tay1_len;
					robotRunAngle(1800,8,-900,0.8);
					for(i=0;i<150;i++)
					{
						while(CB_ROI_1 == 0 )	
						{	
							vTaskDelay (1);
							if(!wantExit())	break;
						}
					}
			}
			//// gap duoi lan 3
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {		
					ha_sat_xuong();
					robotRunAngle(1800,25,-900,0.8);
					for(i=0;i<150;i++)
					{
						while(CB_ROI_3 == 0 ||  (abs(bientrochansauValue - target_chan_sau) > 30))	
						{	
							vTaskDelay (1);
							if(!wantExit())	break;
						}
					}
					Tay2_len;
					robotRunAngle(1800,8,-900,0.8);
					for(i=0;i<150;i++)
					{
						while(CB_ROI_1 == 0 )	
						{	
							vTaskDelay (1);
							if(!wantExit())	break;
						}
					}
				}
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 0) {		
					ha_sat_xuong();
					robotRunAngle(1800,25,-900,0.8);
					for(i=0;i<150;i++)
					{
						while(CB_ROI_3 == 0 ||  (abs(bientrochansauValue - target_chan_sau) > 30))	
						{	
							vTaskDelay (1);
							if(!wantExit())	break;
						}
					}
					Tay1_len;
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

	if (TinHieu_ChuanBi_GapThang == 0 && TinHieu_ChuanBi_GapTrai == 0 && TinHieu_ChuanBi_GapPhai == 0 && TinHieu_QuaTrai == 0 && TinHieu_QuaPhai == 0) {
		// chay toi khi mat cam bien sau
		robotRunAngle(900,25,-900,0.7);
		for(i=0;i<1550;i++)
				{
						while(CB_Ha_Sau == 0 || (abs(bientrochansauValue - target_chan_sau) > 10))	
					{	
						if(!wantExit())	break;
						vTaskDelay (1);
					}
				}

				
//		robotStop(0);
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
//		robotStop(0);
}

void chuan_bi_gap_thang_do_3(void) {
		su_dung_chan(565);
		if (da_lay_tay1 == 0 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
				while(CB_Cap_Thanh_Sau == 0 || (abs(bientrochansauValue - target_chan_sau) > 40))	 {
				if(CB_ROI_3  == 0 && CB_ROI_1 == 0)	robotRunAngle(1250,20,-900,0.7);
				else																robotRunAngle(900,12,-900,0.7), Tay2_len;
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
				while(CB_Cap_Thanh_Sau == 0 || (abs(bientrochansauValue - target_chan_sau) > 40))	 {
				if(CB_ROI_3  == 0 && CB_ROI_1 == 0)	robotRunAngle(1250,20,-900,0.7);
				else																robotRunAngle(900,12,-900,0.7), Tay1_len;
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
				while(CB_Cap_Thanh_Sau == 0 || (abs(bientrochansauValue - target_chan_sau) > 40))	 {
				if(CB_ROI_4  == 0 && CB_ROI_2 == 0)	robotRunAngle(300,20,-900,0.7), Tay2_len;
				else																robotRunAngle(900,12,-900,0.7), Tay2_len;
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
				while(CB_Cap_Thanh_Sau == 0 || (abs(bientrochansauValue - target_chan_sau) > 40))	 {
				if(CB_ROI_4  == 0 && CB_ROI_2 == 0)	robotRunAngle(300,20,-900,0.7), Tay1_len;
				else																robotRunAngle(900,12,-900,0.7), Tay1_len;
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

void Leo_bac_400_co_thanh_do(void) {  
		Leo_bac_400(900, -900);
			
	if (TinHieu_ChuanBi_GapThang == 0 && TinHieu_ChuanBi_GapTrai == 0 && TinHieu_ChuanBi_GapPhai == 0) {
		su_dung_chan(480);

		// chay toi khi laser sau cham 1
		robotRunAngle(900,22,-900,0.7);
		for(i=0;i<1550;i++)
				{
					while(CB_Ha_Sau == 1  || (abs(bientrochansauValue - target_chan_sau) > 40))	
					{	
						vTaskDelay (1);
						if(!wantExit())	break;
					}
				}

	}
			
		else if (TinHieu_ChuanBi_GapThang == 1) {
				chuan_bi_gap_thang_do_3();
		}
//		// CO LENH GAP PHAI
		else if (TinHieu_ChuanBi_GapPhai == 1 ) {
					chuan_bi_gap_phai_200_duoi_do_5();
		}
			robotStop(0);
}

//**************** Xuong_bac_200 do ô 9 **************		
void chuan_bi_gap_thang_do_9 (void) {
		int vitri_tay41 = vitri_tay41_laser_trai_GapQua + 10;
		kiem_tra_huong_quay_tay_gap_phia_truoc();
		su_dung_chan(265);
			// chinh lai vi tri cho tay gap
			if (da_lay_tay1 == 0 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
				while( CB_Ha_Sau == 0 || (abs(bientrochansauValue - target_chan_sau) > 20)) 
					{	
					if(lazeTraiValue > vitri_tay41)			robotRunAngle(1450,18,-900,0.7);
					else																robotRunAngle(900,20,-900,0.7), Tay2_len;
					vTaskDelay(1);
					if(!wantExit()) break; }
			}
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
				while(CB_Ha_Sau == 0 || (abs(bientrochansauValue - target_chan_sau) > 20)) 
					{	
					if(lazeTraiValue > vitri_tay41)			robotRunAngle(1450,18,-900,0.7);
					else																robotRunAngle(900,20,-900,0.7), Tay1_len;
					vTaskDelay(1);
					if(!wantExit()) break; }
				}

		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
				while(CB_Ha_Sau == 0 || (abs(bientrochansauValue - target_chan_sau) > 20)) {
				if(CB_ROI_2  == 0 && CB_ROI_4 == 0)	robotRunAngle(300,20,-900,0.7);
				else																robotRunAngle(900,20,-900,0.7), Tay2_len;
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
				if(CB_ROI_2  == 0 && CB_ROI_4 == 0)	robotRunAngle(300,20,-900,0.7);
				else																robotRunAngle(900,20,-900,0.7), Tay1_len;
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
			
				robotRunAngle(900,10,-900,0.3);
				RESET_ENCODER(); 
				while(abs(ENCODER_FR()) + abs(ENCODER_FL()) < 250)	{vTaskDelay (1); if(!wantExit())	break;}
				robotStop(0); 
			}

void chuan_bi_gap_phai_200_tren_do (void ) {
		if (da_lay_tay1 == 0 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
				su_dung_chan_thuong(565);
				robotRunAngle(-1550,10,-900,0.9);
				for(i=0;i<150;i++)
					{
				while(lazeTraiValue > vitri_tay41_laser_trai_GapQua || (abs(bientrochansauValue - target_chan_sau) > 200))	
						{	
							Tay2_len;
							vTaskDelay (1);
							if(!wantExit())	break;
						}
					}
					vTaskDelay(2500);
		}
	
	else if (da_lay_tay1 == 1 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
				su_dung_chan_thuong(565);
				robotRunAngle(-1550,10,-900,0.9);
				for(i=0;i<150;i++)
					{
				while(lazeTraiValue > vitri_tay41_laser_trai_GapQua || (abs(bientrochansauValue - target_chan_sau) > 200))	
						{	
							Tay1_len;
							vTaskDelay (1);
							if(!wantExit())	break;
						}
					}
					vTaskDelay(2500);
		}
	
			/// gap lan 3
	else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {		
				su_dung_chan_thuong(565);
				robotRunAngle(1800,10,-900,0.9);
					for(i=0;i<150;i++)
						{
					while(lazeTraiValue > vitri_tay41_laser_trai_GapQua )	
							{	
								vTaskDelay (1);
								if(!wantExit())	break;
							}
						}
					vTaskDelay (2000);
					Tay2_len;
					robotRunAngle(910,12,-900,0.9);
					for(i=0;i<150;i++)
							{
						while(lazeTruocValue < 144 || (abs(bientrochansauValue - target_chan_sau) > 300))	
								{	
									vTaskDelay (1);
									if(!wantExit())	break;
								}
						}
		}
	/// gap lan 4
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 0) {
					su_dung_chan_thuong(565);
					robotRunAngle(1800,10,-900,0.9);
						for(i=0;i<150;i++)
							{
						while(lazeTraiValue > vitri_tay41_laser_trai_GapQua )	
								{	
									vTaskDelay (1);
									if(!wantExit())	break;
								}
							}
						vTaskDelay (2000);
						Tay2_len;
						robotRunAngle(910,12,-900,0.9);
						for(i=0;i<150;i++)
								{
							while(lazeTruocValue < 144 || (abs(bientrochansauValue - target_chan_sau) > 300))	
									{	
										vTaskDelay (1);
										if(!wantExit())	break;
									}
							}
		}
	
		robotStop(0); 

}


void Xuong_bac_200_do_9(void)
{	
		Xuong_bac_200(900, -900);
		
		if (TinHieu_ChuanBi_GapThang == 0 && TinHieu_ChuanBi_GapTrai == 0 && TinHieu_ChuanBi_GapPhai == 0 && TinHieu_QuaPhai == 0) {
				su_dung_chan(265);
				// chay toi khi mat cam bien sau
				robotRunAngle(900,25,-900,0.7);
				for(i=0;i<1550;i++)
				{
						while(CB_Ha_Sau == 0 || (abs(bientrochansauValue - target_chan_sau) > 20))	
					{	
						if(!wantExit())	break;
						vTaskDelay (1);
					}
				}
						
//				robotStop(0);
				}				
	
		else if (TinHieu_ChuanBi_GapThang == 1) {
					chuan_bi_gap_thang_do_9();
					}
		else if (TinHieu_ChuanBi_GapPhai == 1) {
					chuan_bi_gap_phai_200_tren_do();
				}
//			robotStop(0);
				
	}

void xuong_bac_200_do_12(void) {
		Xuong_bac_200(900, -900);
		if (TinHieu_ChuanBi_GapThang == 0 && TinHieu_ChuanBi_GapTrai == 0 && TinHieu_ChuanBi_GapPhai == 0 && TinHieu_QuaPhai == 0) {
				su_dung_chan(265);
				// chay toi khi mat cam bien sau
				robotRunAngle(900,25,-900,0.7);
				for(i=0;i<1550;i++)
						{
								while(CB_Ha_Sau == 0 || (abs(bientrochansauValue - target_chan_sau) > 20))	
							{	
								if(!wantExit())	break;
								vTaskDelay (1);
							}
						}
						
//				robotStop(0);
			
			}
		else if (TinHieu_ChuanBi_GapPhai == 1) {
					chuan_bi_gap_phai_200_tren_do();
				}
//			robotStop(0);
}


void Leo_bac_400_ko_thanh_do(void)
{		
		Leo_bac_400(900, -900);

		su_dung_chan(265);
		if (TinHieu_ChuanBi_GapThang == 0 && TinHieu_ChuanBi_GapTrai == 0 && TinHieu_ChuanBi_GapPhai == 0) {
				// chay toi khi mat cam bien sau
				robotRunAngle(900,25,-900,0.7);
				for(i=0;i<250;i++)
						{
								while(CB_Ha_Sau == 0 || (abs(bientrochansauValue - target_chan_sau) > 30))
							{	
								vTaskDelay (1);
								if(!wantExit())	break;
							}
						}
//						robotStop(0);
					}
						
				if (TinHieu_ChuanBi_GapThang == 1 ) {
					di_tren_buc_khong_thanh_2_ben_do();
				}
				//	 CO LENH GAP TRAI
				else if (TinHieu_ChuanBi_GapTrai == 1 ) {
							chuan_bi_gap_trai_200_duoi_ko_thanh_do();
				}
//				robotStop(0);
}

void chuan_bi_gap_thang_do_2(void) {
			int vitri_tay41 = vitri_tay41_laser_trai_GapQua + 10;
			int vitri_tay23 = vitri_tay23_phai_laser_GapQua + 10;
			su_dung_chan(565);
			if (da_lay_tay1 == 0 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
					for(i=0;i<1550;i++) {
						
					while( CB_Cap_Thanh_Sau == 0 ||  (abs(bientrochansauValue - target_chan_sau) > 40))	
					{	
					if(lazeTraiValue > vitri_tay41)			robotRunAngle(1450,18,-900,0.7);
					else																robotRunAngle(900,12,-900,0.7), Tay2_len;
					vTaskDelay(1);
					if(!wantExit()) break;
								}
					
						}
					}
			
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
					for(i=0;i<1550;i++) {
					while( CB_Cap_Thanh_Sau == 0 ||  (abs(bientrochansauValue - target_chan_sau) > 40))	
					{	
					if(lazeTraiValue > vitri_tay41)			robotRunAngle(1450,18,-900,0.7);
					else																robotRunAngle(900,12,-900,0.7), Tay1_len;
					vTaskDelay(1);
					if(!wantExit()) break;
								}
					
							}
					}

		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
					for(i=0;i<1550;i++) {
					while( CB_Cap_Thanh_Sau == 0 ||  (abs(bientrochansauValue - target_chan_sau) > 40))	
					{	
					if(lazePhaiValue > vitri_tay23)			robotRunAngle(300,18,-900,0.7);
					else																robotRunAngle(900,12,-900,0.7), Tay2_len;
					vTaskDelay(1);
					if(!wantExit()) break;
								}
						}
					
					}
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 0) {
					for(i=0;i<1550;i++) {
					while( CB_Cap_Thanh_Sau == 0 ||  (abs(bientrochansauValue - target_chan_sau) > 40))	
					{	
					if(lazePhaiValue > vitri_tay23)			robotRunAngle(300,18,-900,0.7);
					else																robotRunAngle(900,12,-900,0.7), Tay1_len;
					vTaskDelay(1);
					if(!wantExit()) break;
									}
					
					}
				}
			robotStop(0); 
	}

void chuan_bi_gap_phai_200_tren_2_do (void ) {
	if (da_lay_tay1 == 0 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
			su_dung_chan_thuong(565);	
			robotRunAngle(1900,14,-900,0.5);
					for(i=0;i<150;i++)
					{
						while(lazeTraiValue > vitri_tay41_laser_trai_GapQua)	
						{	
							vTaskDelay (1);
							if(!wantExit())	break;
						}
					}
			robotRunAngle(1800,10,-900,0.5);
			vTaskDelay (2000);
		}
	else if (da_lay_tay1 == 1 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
			su_dung_chan_thuong(565);	
			robotRunAngle(1900,14,-900,0.5);
				for(i=0;i<150;i++)
				{
					while(lazeTraiValue > vitri_tay41_laser_trai_GapQua)	
					{	
						vTaskDelay (1);
						if(!wantExit())	break;
					}
				}
			robotRunAngle(1800,10,-900,0.5);
			vTaskDelay (2000);
			}
	else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
			su_dung_chan_thuong(565);
			chinh_lai_vi_tri_laser_trai_do(vitri_tay41_laser_trai_GapQua , 200);
			robotRunAngle(900,18,-900,0.7);
			for(i=0;i<1550;i++)
						{
							while(lazeSauValue > 132|| (abs(bientrochansauValue - target_chan_sau) > 300) )	
							{	
								if(!wantExit())	break;
								vTaskDelay (1);
							}
						}
			robotStop(0); 
			robotRunAngle(1800,10,-900,0.1);
			vTaskDelay(2500);
	}
	
	else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 0) {
			su_dung_chan_thuong(565); 
			chinh_lai_vi_tri_laser_trai_do(vitri_tay41_laser_trai_GapQua , 200);
			// chay toi khi laser sau cham 1
			robotRunAngle(900,18,-900,0.7);
			for(i=0;i<1550;i++)
						{
							while(lazeSauValue > 132 || (abs(bientrochansauValue - target_chan_sau) > 300) )	
							{	
								if(!wantExit())	break;
								vTaskDelay (1);
							}
						}
			robotStop(0); 
			robotRunAngle(1800,10,-900,0.1);
			vTaskDelay(2500);
		}
		robotStop(0); 
}

void chuan_bi_gap_trai_200_tren_2_do (void ) {
	if (da_lay_tay1 == 0 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
			su_dung_chan_thuong(565);	
			for(i=0;i<1550;i++) {
				while( lazeSauValue > 132 )	
				{	
				if(lazePhaiValue > vitri_tay23_phai_laser_GapQua)			robotRunAngle(250,18,-900,0.7);
				else																									robotRunAngle(900,14,-900,0.7);
				vTaskDelay(1);
				if(!wantExit()) break;
						}
				}
				robotRunAngle(0,10,-900,0.1);
				for(i=0;i<150;i++)
					{
						while(lazePhaiValue > vitri_tay23_phai_laser_GapQua)	
						{	
							vTaskDelay (1);
							if(!wantExit())	break;
						}
					}
				vTaskDelay(2000);
		}
	else if (da_lay_tay1 == 1 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
			su_dung_chan_thuong(565);	
			for(i=0;i<1550;i++) {
				while( lazeSauValue > 132 )	
				{	
				if(lazePhaiValue > vitri_tay23_phai_laser_GapQua)			robotRunAngle(250,18,-900,0.7);
				else																									robotRunAngle(900,14,-900,0.7);
				vTaskDelay(1);
				if(!wantExit()) break;
						}
				}
				robotRunAngle(0,10,-900,0.1);
				for(i=0;i<150;i++)
					{
						while(lazePhaiValue > vitri_tay23_phai_laser_GapQua)	
						{	
							vTaskDelay (1);
							if(!wantExit())	break;
						}
					}
				vTaskDelay(2000);
		}
	else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
			su_dung_chan_thuong(565);	
			robotRunAngle(-100,12,-900,0.5);
			for(i=0;i<150;i++)
					{
						while(lazePhaiValue > vitri_tay23_phai_laser_GapQua)	
						{	
							vTaskDelay (1);
							if(!wantExit())	break;
						}
					}
			robotRunAngle(0,10,-900,0.5);
			vTaskDelay (2000);
		}
	
	else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 0) {
			su_dung_chan_thuong(565);	
			robotRunAngle(-100,12,-900,0.5);
					for(i=0;i<150;i++)
					{
						while(lazePhaiValue > vitri_tay23_phai_laser_GapQua)	
						{	
							vTaskDelay (1);
							if(!wantExit())	break;
						}
					}
			robotRunAngle(0,10,-900,0.5);
			vTaskDelay (2000);
		}
		robotStop(0); 
}

void Leo_bac_200_bam_thanh_phai_do(void)
{	
	Leo_bac_200(900, -900);
	
	Nang_nhanh();
	target_chan_truoc = Min_chan_truoc + 250;
	target_chan_sau = Min_chan_sau + 250;
	
	if (TinHieu_ChuanBi_GapThang == 0 && TinHieu_ChuanBi_GapTrai == 0 && TinHieu_ChuanBi_GapPhai == 0) {
			robotRunAngle(900,22,-900,0.7);
			for(i=0;i<1550;i++)
				{
				while(CB_Ha_Sau == 1 || (abs(bientrochansauValue - target_chan_sau) > 50)	 )	
					{	
						vTaskDelay (1);
						if(!wantExit())	break;
					}
				}

			}
	else if (TinHieu_ChuanBi_GapThang == 1) {		
				chuan_bi_gap_thang_do_2();
		}
	else if (TinHieu_ChuanBi_GapPhai == 1) {		
				chuan_bi_gap_phai_200_tren_2_do();
		}
	else if (TinHieu_ChuanBi_GapTrai == 1) {		
				chuan_bi_gap_trai_200_tren_2_do();
		}
		robotStop(0); 		
}

//**************** Xuong_bac_200 ô 4********
void chuan_bi_gap_thang_do_4(void) {
	int vitri_tay23 = vitri_tay23_phai_laser_GapQua + 12;
		kiem_tra_huong_quay_tay_gap_phia_truoc();
		su_dung_chan(565);
		if (da_lay_tay1 == 0 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
			for(i=0;i<1550;i++) {
				while( CB_Cap_Thanh_Sau == 0 || (abs(bientrochansauValue - target_chan_sau) > 100) )	{
						if(CB_ROI_1  == 0 && CB_ROI_3 == 0)	robotRunAngle(1450,18,-900,0.7);
						else																robotRunAngle(900,12,-900,0.7), Tay2_len;
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
				while( CB_Cap_Thanh_Sau == 0 || (abs(bientrochansauValue - target_chan_sau) > 100) )	{
						if(CB_ROI_1  == 0 && CB_ROI_3 == 0)	robotRunAngle(1450,18,-900,0.7);
						else																robotRunAngle(900,12,-900,0.7), Tay1_len;
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
						while( CB_Cap_Thanh_Sau == 0 ||(abs(bientrochansauValue - target_chan_sau) > 100))	
						{	
						if(lazePhaiValue > vitri_tay23)			robotRunAngle(300,18,-900,0.7);
						else																robotRunAngle(900,12,-900,0.7), Tay2_len;
						vTaskDelay(1);
						if(!wantExit()) break;
									}
							}
					}
		
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 0) {
			for(i=0;i<1550;i++) {
						while( CB_Cap_Thanh_Sau == 0 ||(abs(bientrochansauValue - target_chan_sau) > 100))	
						{	
						if(lazePhaiValue > vitri_tay23)			robotRunAngle(300,18,-900,0.7);
						else																robotRunAngle(900,12,-900,0.7), Tay1_len;
						vTaskDelay(1);
						if(!wantExit()) break;
									}
							}
					}	
				robotStop(10);
				robotRunAngle(900,10,-900,0.7);
				vTaskDelay(1500);
				robotStop(0);
		}

void Lay_ben_phai_bac_200_tren_do_2(void) {
			Lay_ben_phai_bac_200_tren();
			robotStop(0);
	
	if (TinHieu_ChuanBi_GapTrai == 1) {	
				kiem_tra_huong_quay_tay_gap_ben_trai();
				vTaskDelay(4000);
				chuan_bi_gap_trai_200_tren_2_do();
		}
	
	else if (TinHieu_ChuanBi_GapThang == 1) {
			kiem_tra_huong_quay_tay_gap_phia_truoc();
			vTaskDelay(4000);
			chuan_bi_gap_thang_do_2();
		}
			robotStop(0);
}
		
void Lay_ben_phai_bac_200_duoi_do_3(void) {
			Lay_ben_phai_bac_200_duoi();
			robotStop(0);
			
	if (TinHieu_ChuanBi_GapThang == 1) {
			kiem_tra_huong_quay_tay_gap_phia_truoc();
			vTaskDelay(4000);
			chuan_bi_gap_thang_do_3();
				}
			robotStop(0);
}

void Lay_ben_phai_bac_200_duoi_do_5(void) {
			Lay_ben_phai_bac_200_duoi();
			robotStop(0);
	
		// CO LENH GAP TRAI
	if (TinHieu_ChuanBi_GapTrai == 1 ) {
			kiem_tra_huong_quay_tay_gap_ben_trai();
			vTaskDelay(4000);
			chuan_bi_gap_trai_200_tren_do_4();
		}
			
	else if (TinHieu_ChuanBi_GapThang == 1) {
			kiem_tra_huong_quay_tay_gap_phia_truoc();
			vTaskDelay(4000);
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
			vTaskDelay(6000);
			chuan_bi_gap_thang_do_9();
		}
			robotStop(0);
}


void Lay_ben_phai_bac_200_duoi_do_8(void) {
			Lay_ben_phai_bac_200_duoi();
	
	//	// CO LENH GAP TRAI
	if (TinHieu_ChuanBi_GapTrai == 1 ) {
			kiem_tra_huong_quay_tay_gap_ben_trai();
			vTaskDelay(4000);
			chuan_bi_gap_trai_200_duoi_ko_thanh_do();
			}
	else if (TinHieu_ChuanBi_GapThang == 1) {
			kiem_tra_huong_quay_tay_gap_phia_truoc();
			vTaskDelay(4000);
			di_tren_buc_khong_thanh_2_ben_do();
				}
		robotStop(0);
}


void chuan_bi_gap_trai_200_tren_do_4 (void ) {
	su_dung_chan_thuong(565);	
	if (da_lay_tay1 == 0 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
				for(i=0;i<1550;i++) {
						while( lazeSauValue > 132 ||  (abs(bientrochansauValue - target_chan_sau) > 300))	
						{	
						if(lazePhaiValue > vitri_tay23_phai_laser_GapQua)			robotRunAngle(400,18,-900,0.7);
						else																									robotRunAngle(900,15,-900,0.7);
						vTaskDelay(1);
						if(!wantExit()) break;
										}
								}
				Tay2_len;
				robotRunAngle(0,10,-900,0.1);
				for(i=0;i<150;i++)
					{
						while(lazePhaiValue > vitri_tay23_phai_laser_GapQua)	
						{	
							vTaskDelay (1);
							if(!wantExit())	break;
						}
					}
					vTaskDelay(2000);
		}
	else if (da_lay_tay1 == 1 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
					for(i=0;i<1550;i++) {
						while( lazeSauValue > 132 ||  (abs(bientrochansauValue - target_chan_sau) > 300))	
						{	
						if(lazePhaiValue > vitri_tay23_phai_laser_GapQua)			robotRunAngle(400,18,-900,0.7);
						else																									robotRunAngle(900,15,-900,0.7);
						vTaskDelay(1);
						if(!wantExit()) break;
										}
								}
				Tay1_len;
				robotRunAngle(0,10,-900,0.1);
				for(i=0;i<150;i++)
					{
						while(lazePhaiValue > vitri_tay23_phai_laser_GapQua)	
						{	
							vTaskDelay (1);
							if(!wantExit())	break;
						}
					}
					vTaskDelay(2000);
				}
	else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
				robotRunAngle(-250,14,-900,0.5);
				for(i=0;i<150;i++)
				{
				while(lazePhaiValue > vitri_tay23_phai_laser_GapQua ||(abs(bientrochansauValue - target_chan_sau) > 200))	
					{	
						vTaskDelay (1);
						if(!wantExit())	break;
					}
				}
				Tay2_len;
				robotRunAngle(0,10,-900,0.1);
				for(i=0;i<150;i++)
					{
						while(lazePhaiValue > vitri_tay23_phai_laser_GapQua)	
						{	
							vTaskDelay (1);
							if(!wantExit())	break;
						}
					}
					vTaskDelay (2000);
			}
	
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 0) {
					robotRunAngle(-250,14,-900,0.5);
					for(i=0;i<150;i++)
					{
					while(lazePhaiValue > vitri_tay23_phai_laser_GapQua ||(abs(bientrochansauValue - target_chan_sau) > 200))	
						{	
							vTaskDelay (1);
							if(!wantExit())	break;
						}
					}
					Tay1_len;
					robotRunAngle(0,10,-900,0.1);
				for(i=0;i<150;i++)
					{
						while(lazePhaiValue > vitri_tay23_phai_laser_GapQua)	
						{	
							vTaskDelay (1);
							if(!wantExit())	break;
						}
					}
					vTaskDelay(2000);
				}
			
				robotStop(0); 
}

void Xuong_bac_200_do_4(void)
{	
	Xuong_bac_200(900,-900);		
	
	// KHONG CO TIN HIEU GAP
	if (TinHieu_ChuanBi_GapThang == 0 && TinHieu_ChuanBi_GapTrai == 0 && TinHieu_ChuanBi_GapPhai == 0 && TinHieu_QuaTrai == 0) {
		Nang_nhanh();
		target_chan_truoc = Min_chan_truoc + 250;
		target_chan_sau = Min_chan_sau + 250;
		
		robotRunAngle(900,22,-900,0.7);

		for(i=0;i<1550;i++)
				{
					while(CB_Ha_Sau == 1 || (abs(bientrochansauValue - target_chan_sau) > 40) )	
						
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
	
void Lay_ben_trai_bac_200_tren_do_2(void) {
			Lay_ben_trai_bac_200_tren();
			robotStop(0);
			
	
	if (TinHieu_ChuanBi_GapPhai == 1) {	
				kiem_tra_huong_quay_tay_gap_ben_phai();
				vTaskDelay(4000);
				gap_ngang_2_ben_san_do();
				chuan_bi_gap_phai_200_tren_2_do();
		}
	else if (TinHieu_ChuanBi_GapThang == 1) {
			kiem_tra_huong_quay_tay_gap_phia_truoc();
			vTaskDelay(4000);
			chuan_bi_gap_thang_do_2();			
				}
	}

void gap_ngang_2_ben_san_do (void){
		if (da_lay_tay1 == 1 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
					robotRunAngle(-900,12,-900,0.7);
					RESET_ENCODER(); 
					while(abs(ENCODER_FR())  < 500)	{vTaskDelay (1); if(!wantExit())	break;}
				}
				robotStop(0);
}


void Lay_ben_trai_bac_200_tren_do_5_6(void) {
			Lay_ben_trai_bac_200_tren();
			robotStop(0);
	
	//		// CO LENH GAP PHAI
	if (TinHieu_ChuanBi_GapPhai == 1 ) {
			kiem_tra_huong_quay_tay_gap_ben_phai();
			vTaskDelay(3000);
			su_dung_chan(276);
			{
			while(abs(bientrochansauValue - target_chan_sau) > 25)	{vTaskDelay(1); if(!wantExit())	break;}
			}
			gap_ngang_2_ben_san_do();
			chuan_bi_gap_phai_200_duoi_do_5();
		}
	
	else if (TinHieu_ChuanBi_GapThang == 1) {
			kiem_tra_huong_quay_tay_gap_phia_truoc();
			vTaskDelay(5000);
			chuan_bi_gap_thang_do_4();			
				}
	}

void chuan_bi_gap_phai_200_duoi_do_5 (void ) {
		if (da_lay_tay1 == 0 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
					ha_sat_xuong();
					{
					while(abs(bientrochansauValue - target_chan_sau) > 15)	{vTaskDelay(1); if(!wantExit())	break;}
						}
					robotRunAngle(1900,18,-900,0.7);
					for(i=0;i<150;i++)
					{
						while(CB_ROI_3 == 0 )	
						{	
							vTaskDelay (1);
							if(!wantExit())	break;
						}
					}
					Tay2_len;
					robotRunAngle(1820,8,-900,0.7);
					for(i=0;i<150;i++)
					{
						while(CB_ROI_1 == 0 )	
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
					robotRunAngle(1900,18,-900,0.7);
					for(i=0;i<150;i++)
					{
						while(CB_ROI_3 == 0 )	
						{	
							vTaskDelay (1);
							if(!wantExit())	break;
						}
					}
					Tay1_len;
					robotRunAngle(1820,8,-900,0.7);
					for(i=0;i<150;i++)
					{
						while(CB_ROI_1 == 0 )	
						{	
							vTaskDelay (1);
							if(!wantExit())	break;
						}
					}
				}
	
			//// gap duoi lan 3
		else if  (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
					ha_sat_xuong();
					{
					while(abs(bientrochansauValue - target_chan_sau) > 15)	{vTaskDelay(1); if(!wantExit())	break;}
						}
					while( lazeSauValue > 2 )	 {
					if(CB_ROI_1  == 0 && CB_ROI_3 == 0)	robotRunAngle(1450,18,-900,0.7);
					else																robotRunAngle(900,15,-900,0.7);
					vTaskDelay(1);
					if(!wantExit()) break;
								}
					Tay2_len;
					// chay toi roi thi di ngang qua phai
					robotRunAngle(1900,8,-900,0.7);
					while (CB_ROI_1  == 0 )	 {
						vTaskDelay(1);
						if(!wantExit()) break;
								}
				}
		//// gap duoi lan 4
		else if  (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 0) {
					ha_sat_xuong();
					{
					while(abs(bientrochansauValue - target_chan_sau) > 15)	{vTaskDelay(1); if(!wantExit())	break;}
					}
					while( lazeSauValue > 2 )	 {
					if(CB_ROI_1  == 0 && CB_ROI_3 == 0)	robotRunAngle(1450,18,-900,0.7);
					else																robotRunAngle(900,15,-900,0.7);
					vTaskDelay(1);
					if(!wantExit()) break;
								}
					Tay1_len;
					// chay toi roi thi di ngang qua phai
					robotRunAngle(1900,8,-900,0.7);
					while (CB_ROI_1  == 0 )	 {
						vTaskDelay(1);
						if(!wantExit()) break;
								}
				}
				robotStop(0);
}


/// ****** leo bac 200 o id  5 san do
void Leo_bac_200_do_5(void) {	
		Leo_bac_200(900, -900);
	  Nang_nhanh();
		target_chan_truoc = Min_chan_truoc + 250;
		target_chan_sau = Min_chan_sau + 250;
		
		// KHONG CO TIN HIEU GAP
		if (TinHieu_ChuanBi_GapThang == 0 && TinHieu_ChuanBi_GapTrai == 0 && TinHieu_ChuanBi_GapPhai == 0&& TinHieu_QuaTrai == 0 && TinHieu_QuaPhai == 0) {
				robotRunAngle(900,22,-900,0.7);
				for(i=0;i<1550;i++)
				{
				while(CB_Ha_Sau == 1 || (abs(bientrochansauValue - target_chan_sau) > 40)	 )	
					{	
						vTaskDelay (1);
						if(!wantExit())	break;
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
		
//			robotStop(0); 			
}

void chuan_bi_gap_thang_do_7(void) {
		int vitri_tay23 = vitri_tay23_phai_laser_GapQua + 10;
		su_dung_chan(265);

	// chinh lai vi tri cho tay gap
	if (da_lay_tay1 == 0 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
				while(CB_Ha_Sau == 0 || (abs(bientrochansauValue - target_chan_sau) > 25)) {
				if(CB_ROI_1  == 0 && CB_ROI_3 == 0)	robotRunAngle(1450,20,-900,0.7);
				else																robotRunAngle(900,20,-900,0.7), Tay2_len;
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
				while( CB_Ha_Sau == 0 || (abs(bientrochansauValue - target_chan_sau) > 25)) {
				if(CB_ROI_1  == 0 && CB_ROI_3 == 0)	robotRunAngle(1450,20,-900,0.7);
				else																robotRunAngle(900,20,-900,0.7), Tay1_len;
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
					while(CB_Ha_Sau == 0 || (abs(bientrochansauValue - target_chan_sau) > 25)) 
					{	
						if(lazePhaiValue > vitri_tay23)			robotRunAngle(300,20,-900,0.7);
						else																robotRunAngle(900,20,-900,0.7), Tay2_len;
						vTaskDelay(1);
						if(!wantExit()) break;
									}
				}
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 0) {
						while(CB_Ha_Sau == 0 || (abs(bientrochansauValue - target_chan_sau) > 25)) 
					{	
						if(lazePhaiValue > (vitri_tay23 ))			robotRunAngle(300,20,-900,0.7);
						else																			robotRunAngle(900,20,-900,0.7), Tay1_len;
						vTaskDelay(1);
						if(!wantExit()) break;
									}
								}
		
			robotRunAngle(900,10,-900,0.3);
			RESET_ENCODER(); 
			while(abs(ENCODER_FR()) + abs(ENCODER_FL()) < 250)	{vTaskDelay (1); if(!wantExit())	break;}
			robotStop(0);
}

void chuan_bi_gap_trai_200_tren_do_7_10 (void ) {
	if (da_lay_tay1 == 0 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
			su_dung_chan_thuong(565);
				for(i=0;i<250;i++)	
			{
				while(abs(bientrochansauValue - target_chan_sau) > 300)	{vTaskDelay(1); if(!wantExit())	break;}
			}
			
			robotRunAngle(650,16,-900,0.8);
			RESET_ENCODER(); 
			while(abs(ENCODER_FR()) + abs(ENCODER_FL()) < 1680)	{vTaskDelay (1); if(!wantExit())	break;}
			robotStop(0);
			Tay2_len;
			
			robotRunAngle(0,12,-900,0.5);
				for(i=0;i<150;i++)
					{
						while(lazePhaiValue > vitri_tay23_phai_laser_GapQua)	
						{	
							vTaskDelay (1);
							if(!wantExit())	break;
						}
					}
			vTaskDelay (2000);
		}
	else if (da_lay_tay1 == 1 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
			su_dung_chan_thuong(565);
			for(i=0;i<250;i++)	
			{
				while(abs(bientrochansauValue - target_chan_sau) > 300)	{vTaskDelay(1); if(!wantExit())	break;}
			}
			
			robotRunAngle(650,16,-900,0.8);
			RESET_ENCODER(); 
			while(abs(ENCODER_FR()) + abs(ENCODER_FL()) < 1680)	{vTaskDelay (1); if(!wantExit())	break;}
			robotStop(0);
			
			Tay1_len;
			robotRunAngle(0,12,-900,0.5);
				for(i=0;i<150;i++)
					{
						while(lazePhaiValue > vitri_tay23_phai_laser_GapQua)	
						{	
							vTaskDelay (1);
							if(!wantExit())	break;
						}
					}
			vTaskDelay (2000);
		}
	else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
				su_dung_chan_thuong(565);
				for(i=0;i<250;i++)	
				{
				while(abs(bientrochansauValue - target_chan_sau) > 100)	{vTaskDelay(1); if(!wantExit())	break;}
				}
				Tay2_len;
				robotRunAngle(-50,12,-900,0.5);
				for(i=0;i<150;i++)
					{
						while(lazePhaiValue > vitri_tay23_phai_laser_GapQua)	
						{	
							vTaskDelay (1);
							if(!wantExit())	break;
						}
					}
			vTaskDelay (2000);
		}
	
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 0) {
				su_dung_chan_thuong(565);
				for(i=0;i<250;i++)	
				{
				while(abs(bientrochansauValue - target_chan_sau) > 100)	{vTaskDelay(1); if(!wantExit())	break;}
				}
				Tay1_len;
				robotRunAngle(-50,12,-900,0.5);
				for(i=0;i<150;i++)
					{
						while(lazePhaiValue > vitri_tay23_phai_laser_GapQua)	
						{	
							vTaskDelay (1);
							if(!wantExit())	break;
						}
					}
			vTaskDelay (2000);
		}
	
		robotStop(0); 
}


void Leo_bac_200_do_7(void)  {	
		Leo_bac_200(900, -900);
			// KHONG CO TIN HIEU GAP
	if (TinHieu_ChuanBi_GapThang == 0 && TinHieu_ChuanBi_GapTrai == 0 && TinHieu_ChuanBi_GapPhai == 0 && TinHieu_QuaTrai == 0) {
		su_dung_chan(265);
		// chay toi khi mat cam bien sau
		robotRunAngle(900,20,-900,0.7);
		for(i=0;i<1550;i++)
				{
						while(CB_Ha_Sau == 0 || (abs(bientrochansauValue - target_chan_sau) > 30)	)	
			
					{	
						if(!wantExit())	break;
						vTaskDelay (1);
					}
				}
				
				
//		robotStop(0);
			}
	
			// CO TIN HIEU GAP THANG
	else if (TinHieu_ChuanBi_GapThang == 1) {
				chuan_bi_gap_thang_do_7();
				}
		// CO TIN HIEU GAP TRAI
	else if (TinHieu_ChuanBi_GapTrai == 1) {
					chuan_bi_gap_trai_200_tren_do_7_10();
			}
//		robotStop(0);
}

	
void xuong_bac_200_do_10 (void) {
	Xuong_bac_200(900, -900);
		if (TinHieu_ChuanBi_GapThang == 0 && TinHieu_ChuanBi_GapTrai == 0 && TinHieu_ChuanBi_GapPhai == 0 && TinHieu_QuaTrai == 0) {
				su_dung_chan(265);
				// chay toi khi mat cam bien sau
				robotRunAngle(900,25,-900,0.7);
				for(i=0;i<1550;i++)
						{
								while(CB_Ha_Sau == 0 || (abs(bientrochansauValue - target_chan_sau) > 20))	
							{	
								if(!wantExit())	break;
								vTaskDelay (1);
							}
						}
						
//				robotStop(0);
			
			}
		
	else if (TinHieu_ChuanBi_GapTrai == 1) {
					chuan_bi_gap_trai_200_tren_do_7_10();
			}
//		robotStop(0);
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

void Lay_ben_trai_bac_200_duoi_do_1(void) {
			Lay_ben_trai_bac_200_duoi();
			robotStop(0);
			
	if (TinHieu_ChuanBi_GapThang == 1) {
			kiem_tra_huong_quay_tay_gap_phia_truoc();
			vTaskDelay(4000);
			di_tren_buc_khong_thanh_2_ben_do();
				}
}

void Lay_ben_trai_bac_200_duoi_do_8_11(void) {
			Lay_ben_trai_bac_200_duoi();
			robotStop(0);
	
	// CO LENH GAP PHAI
	if (TinHieu_ChuanBi_GapPhai == 1 ) {
			kiem_tra_huong_quay_tay_gap_ben_phai();
			vTaskDelay(4000);
			gap_ngang_2_ben_san_do();
			chuan_bi_gap_phai_200_duoi_ko_thanh_do_8();
		}
	else if (TinHieu_ChuanBi_GapThang == 1) {
			kiem_tra_huong_quay_tay_gap_phia_truoc();
			vTaskDelay(4000);
			di_tren_buc_khong_thanh_2_ben_do();
				}
}

void Lay_ben_trai_bac_200_duoi_do_ko_thanh(void) {
			Lay_ben_trai_bac_200_duoi();
			robotStop(0);
	
	// CO LENH GAP PHAI
	if (TinHieu_ChuanBi_GapPhai == 1 ) {
			kiem_tra_huong_quay_tay_gap_ben_phai();
			vTaskDelay (3000);
			chuan_bi_gap_phai_200_duoi_ko_thanh_do();
		}
	else if (TinHieu_ChuanBi_GapThang == 1) {
			kiem_tra_huong_quay_tay_gap_phia_truoc();
			vTaskDelay (4000);
			di_tren_buc_khong_thanh_2_ben_do();
			}
}

void xuong_bac_200_11_do(void) {
		Xuong_bac_200(900, -900);
//		robotStop(0);
		if (TinHieu_ChuanBi_GapThang == 0 && TinHieu_ChuanBi_GapTrai == 0 && TinHieu_ChuanBi_GapPhai == 0 && TinHieu_QuaTrai == 0 && TinHieu_QuaPhai == 0) {
				su_dung_chan(265);

				// chay toi khi mat cam bien sau
				robotRunAngle(900,25,-900,0.7);
				for(i=0;i<1550;i++)
						{
								while(CB_Ha_Sau == 0 || (abs(bientrochansauValue - target_chan_sau) > 20))	
							{	
								if(!wantExit())	break;
								vTaskDelay (1);
							}
						}
						
//				robotStop(10);
			
			}
	
		else if (TinHieu_ChuanBi_GapTrai == 1 ) {
				chuan_bi_gap_trai_200_duoi_ko_thanh_do();
		}
		// CO LENH GAP PHAI
		else if (TinHieu_ChuanBi_GapPhai == 1 ) {
					chuan_bi_gap_phai_200_duoi_ko_thanh_do();
		}
//		robotStop(0);
}

/// ************** DI NGANG QUA TRAI ****************


void qua_trai_xuong_bac_200_2_do (void) {
		
		if (da_lay_tay1 == 0 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
				MD_qua_trai_phai_xuong_bac_200(-1800, -900, -850, 3500,-900, 0, -1800);
			}
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
				MD_qua_trai_phai_xuong_bac_200(-1800, -900, -450, 4000,-900, 0, -1800);
			}
			//// gap 2 lan r
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {		
				MD_qua_trai_phai_xuong_bac_200(-1800, -900, -450, 4000,-900, 0, -1800);
			}
		//// gap 3 lan r
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 0) {		
				MD_qua_trai_phai_xuong_bac_200(-1800, -900, -1350, 4000,-900, 0, -1800);
			}
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 1) {		
				MD_qua_trai_phai_xuong_bac_200(-1800, -900, -1350, 4000,-900, 0, -1800);
			}
		robotStop(0);
			
		su_dung_chan(480);
		for(i=0;i<50;i++)		
		{
			while(abs(bientrochansauValue - target_chan_sau) > 100)	{vTaskDelay(1); if(!wantExit())	break;}
		}
		if (TinHieu_ChuanBi_GapThang == 0 && TinHieu_ChuanBi_GapTrai == 0 && TinHieu_ChuanBi_GapPhai == 0) {
				robotRunAngle(900,22,-900,0.7);
				for(i=0;i<1550;i++)
					{
					while(CB_Ha_Sau == 1 || (abs(bientrochansauValue - target_chan_sau) > 20)	 )	
						{	
							vTaskDelay (1);
							if(!wantExit())	break;
						}
					}
				robotRunAngle(900,12,-900,0.7);
				for(i=0;i<1550;i++)
					{
					while(CB_Ha_Sau == 1 || CB_Cap_Thanh_Sau == 0  )	
						{	
							vTaskDelay (1);
							if(!wantExit())	break;
						}
					}
				}
			else if (TinHieu_ChuanBi_GapThang == 1) {		
						chuan_bi_gap_thang_do_2();
				}
			else if (TinHieu_ChuanBi_GapPhai == 1) {		
						chuan_bi_gap_phai_200_tren_2_do();
				}
			else if (TinHieu_ChuanBi_GapTrai == 1) {		
						chuan_bi_gap_trai_200_tren_2_do();
				}
}


void qua_trai_len_bac_200_3_do (void) {
		if (da_lay_tay1 == 0 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
				MD_qua_trai_phai_len_bac_200(-1800, -900, -850, 3500,-900, 0, -1800);
			}
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
				MD_qua_trai_phai_len_bac_200(-1800, -900, -450, 4000,-900, 0, -1800);
			}
			//// gap 2 lan r
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {		
				MD_qua_trai_phai_len_bac_200(-1800, -900, -450, 4000,-900, 0, -1800);
			}
			//// gap 3 lan r
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 0) {		
				MD_qua_trai_phai_len_bac_200(-1800, -900, -1350, 4000,-900, 0, -1800);
			}
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 1) {		
				MD_qua_trai_phai_len_bac_200(-1800, -900, -1350, 4000,-900, 0, -1800);
			}
		
		robotStop(0);
		su_dung_chan(480);
		for(i=0;i<50;i++)		
		{
			while(abs(bientrochansauValue - target_chan_sau) > 100)	{vTaskDelay(1); if(!wantExit())	break;}
		}
		if (TinHieu_ChuanBi_GapThang == 0 && TinHieu_ChuanBi_GapTrai == 0 && TinHieu_ChuanBi_GapPhai == 0) {
				robotRunAngle(900,22,-900,0.7);
				for(i=0;i<1550;i++)
						{
							while(CB_Ha_Sau == 1  || (abs(bientrochansauValue - target_chan_sau) > 20))	
							{	
								vTaskDelay (1);
								if(!wantExit())	break;
							}
						}
				robotRunAngle(900,12,-900,0.7);
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
						chuan_bi_gap_thang_do_3();
				}
		//		// CO LENH GAP PHAI
				else if (TinHieu_ChuanBi_GapPhai == 1 ) {
							chuan_bi_gap_phai_200_duoi_do_5();
				}

}

void qua_trai_len_bac_200_5_do (void) {
		int time_41 = 0;
		int time_23 = 0;
		int di_cheo_41 = 0;
		int di_cheo_23 = 0;
		if (TinHieu_QuaTrai == 1 && CB_Cap_Thanh_Sau == 1) { // th vua gap trc xong
				time_41 = 9000;
				time_23 = 9000;
				di_cheo_41 = -450;
				di_cheo_23 = -1350;
		}
		else if (TinHieu_QuaTrai == 1 && CB_Cap_Thanh_Sau == 0 ) { // TH k gap di ngang
				time_41 = 3500;
				time_23 = 3500;
				di_cheo_41 = 450;
				di_cheo_23 = 1350;
		}
		else {
				time_41 = 4500;
				time_23 = 4500;
				di_cheo_41 = -450;
				di_cheo_23 = -1350;
		}
		TinHieu_QuaTrai = 0;
		/// ***************************
		if (da_lay_tay1 == 0 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
				MD_qua_trai_phai_len_bac_200(-1800, -900, -850, 10,-900, 0, -1800);
			}
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
				MD_qua_trai_phai_len_bac_200(-1800, -900, di_cheo_41, time_41,-900, 0, -1800);
			}
			//// gap 2 lan r
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {		
				MD_qua_trai_phai_len_bac_200(-1800, -900, di_cheo_41, time_41,-900, 0, -1800);
			}
			//// gap 3 lan r
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 0) {		
				MD_qua_trai_phai_len_bac_200(-1800, -900, di_cheo_23, time_23,-900, 0, -1800);
			}
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 1) {		
				MD_qua_trai_phai_len_bac_200(-1800, -900, di_cheo_23, time_23,-900, 0, -1800);
			}
		
		robotStop(0);
		Nang_nhanh();
		target_chan_truoc = Min_chan_truoc + 250;
		target_chan_sau = Min_chan_sau + 250;
		
		// KHONG CO TIN HIEU GAP
		if (TinHieu_ChuanBi_GapThang == 0 && TinHieu_ChuanBi_GapTrai == 0 && TinHieu_ChuanBi_GapPhai == 0) {
				robotRunAngle(900,18,-900,0.7);
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
}

void qua_trai_len_bac_200_6_do (void) {
		int time_41 = 0;
		int time_23 = 0;
		int di_cheo_41 = 0;
		int di_cheo_23 = 0;
		if (TinHieu_QuaTrai == 1 && CB_Cap_Thanh_Sau == 1) { // th vua gap trc xong
				time_41 = 9000;
				time_23 = 9000;
				di_cheo_41 = -450;
				di_cheo_23 = -1350;
		}
		else if (TinHieu_QuaTrai == 1 && CB_Cap_Thanh_Sau == 0 ) { // TH k gap di ngang
				time_41 = 3500;
				time_23 = 3500;
				di_cheo_41 = 450;
				di_cheo_23 = 1350;
		}
		else {
				time_41 = 4500;
				time_23 = 4500;
				di_cheo_41 = -450;
				di_cheo_23 = -1350;
		}
		TinHieu_QuaTrai = 0;
		/// ***************************
		if (da_lay_tay1 == 0 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
				MD_qua_trai_phai_len_bac_200(-1800, -900, -850, 10,-900, 0, -1800);
			}
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
				MD_qua_trai_phai_len_bac_200(-1800, -900, di_cheo_41, time_41,-900, 0, -1800);
			}
			//// gap 2 lan r
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {		
				MD_qua_trai_phai_len_bac_200(-1800, -900, di_cheo_41, time_41,-900, 0, -1800);
			}
		//// gap 3 lan r
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 0) {		
				MD_qua_trai_phai_len_bac_200(-1800, -900, di_cheo_23, time_23,-900, 0, -1800);
			}
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 1) {		
				MD_qua_trai_phai_len_bac_200(-1800, -900, di_cheo_23, time_23,-900, 0, -1800);
			}
		
		robotStop(0);
		su_dung_chan(265);
		for(i=0;i<50;i++)		
				{
					while(abs(bientrochansauValue - target_chan_sau) > 20)	{vTaskDelay(1); if(!wantExit())	break;}
				}
		robotStop(0);

	if (TinHieu_ChuanBi_GapThang == 0 && TinHieu_ChuanBi_GapTrai == 0 && TinHieu_ChuanBi_GapPhai == 0) {
		// chay toi khi mat cam bien sau
		robotRunAngle(900,22,-900,0.7);
		for(i=0;i<1550;i++)
				{
						while(CB_Ha_Sau == 0 )	
					{	
						if(!wantExit())	break;
						vTaskDelay (1);
					}
				}

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

void qua_trai_len_bac_200_8_do (void) {
		int time_41 = 0;
		int time_23 = 0;
		int di_cheo_41 = 0;
		int di_cheo_23 = 0;
		if (TinHieu_QuaTrai == 1 && CB_Ha_Sau == 1 && (bientrochansauValue <= 300)) { // th vua gap trc xong
				time_41 = 9000;
				time_23 = 9000;
				di_cheo_41 = -450;
				di_cheo_23 = -1350;
		}
		else if (TinHieu_QuaTrai == 1 && CB_Ha_Sau == 0 && (bientrochansauValue <= 300)) { // TH k gap di ngang
				time_41 = 3500;
				time_23 = 3500;
				di_cheo_41 = 450;
				di_cheo_23 = 1350;
		}
		else {
				time_41 = 4500;
				time_23 = 4500;
				di_cheo_41 = -450;
				di_cheo_23 = -1350;
		}
		TinHieu_QuaTrai = 0;
		/// ***************************
		if (da_lay_tay1 == 0 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
				MD_qua_trai_phai_len_bac_200(-1800, -900, -850, 10,-900, 0, -1800);
			}
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
				MD_qua_trai_phai_len_bac_200(-1800, -900, di_cheo_41, time_41,-900, 0, -1800);
			}
			//// gap 2 lan r
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {		
				MD_qua_trai_phai_len_bac_200(-1800, -900, di_cheo_41, time_41,-900, 0, -1800);
			}
		//// gap 3 lan r
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 0) {		
				MD_qua_trai_phai_len_bac_200(-1800, -900, di_cheo_23, time_23,-900, 0, -1800);
			}
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 1) {		
				MD_qua_trai_phai_len_bac_200(-1800, -900, di_cheo_23, time_23,-900, 0, -1800);
			}
		
		robotStop(0);
		su_dung_chan(265);
		for(i=0;i<50;i++)		
				{
					while(abs(bientrochansauValue - target_chan_sau) > 20)	{vTaskDelay(1); if(!wantExit())	break;}
				}
		robotStop(0);

	if (TinHieu_ChuanBi_GapThang == 0 && TinHieu_ChuanBi_GapTrai == 0 && TinHieu_ChuanBi_GapPhai == 0) {
		// chay toi khi mat cam bien sau
		robotRunAngle(900,22,-900,0.7);
		for(i=0;i<1550;i++)
				{
						while(CB_Ha_Sau == 0 )	
					{	
						if(!wantExit())	break;
						vTaskDelay (1);
					}
				}
				
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

void qua_trai_xuong_bac_200_9_do (void) {
		int time_41 = 0;
		int time_23 = 0;
		int di_cheo_41 = 0;
		int di_cheo_23 = 0;
		if (TinHieu_QuaTrai == 1 && CB_Ha_Sau == 1 && (bientrochansauValue <= 300)) { // th vua gap trc xong
				time_41 = 9000;
				time_23 = 9000;
				di_cheo_41 = -450;
				di_cheo_23 = -1350;
		}
		else if (TinHieu_QuaTrai == 1 && CB_Ha_Sau == 0 && (bientrochansauValue <= 300)) { // TH k gap di ngang
				time_41 = 3500;
				time_23 = 3500;
				di_cheo_41 = 450;
				di_cheo_23 = 1350;
		}
		else {
				time_41 = 4500;
				time_23 = 4500;
				di_cheo_41 = -450;
				di_cheo_23 = -1350;
		}
		TinHieu_QuaTrai = 0;
		/// ***************************
		if (da_lay_tay1 == 0 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
				MD_qua_trai_phai_xuong_bac_200(-1800, -900, -850, 10,-900, 0, -1800);
			}
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
				MD_qua_trai_phai_xuong_bac_200(-1800, -900, di_cheo_41, time_41,-900, 0, -1800);
			}
			//// gap 2 lan r
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {		
				MD_qua_trai_phai_xuong_bac_200(-1800, -900, di_cheo_41, time_41,-900, 0, -1800);
			}
		//// gap 3 lan r
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 0) {		
				MD_qua_trai_phai_xuong_bac_200(-1800, -900, di_cheo_23, time_23,-900, 0, -1800);
			}
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 1) {		
				MD_qua_trai_phai_xuong_bac_200(-1800, -900, di_cheo_23, time_23,-900, 0, -1800);
			}
		robotStop(0);
			
		su_dung_chan(265);
		for(i=0;i<50;i++)		
		{
			while(abs(bientrochansauValue - target_chan_sau) > 20)	{vTaskDelay(1); if(!wantExit())	break;}
		}
			
		if (TinHieu_ChuanBi_GapThang == 0 && TinHieu_ChuanBi_GapTrai == 0 && TinHieu_ChuanBi_GapPhai == 0) {
				// chay toi khi mat cam bien sau
				robotRunAngle(900,20,-900,0.7);
				for(i=0;i<1550;i++)
				{
						while(CB_Ha_Sau == 0 )	
					{	
						if(!wantExit())	break;
						vTaskDelay (1);
					}
				}

				}				
	
		else if (TinHieu_ChuanBi_GapThang == 1) {
					chuan_bi_gap_thang_do_9();
					}
		else if (TinHieu_ChuanBi_GapPhai == 1) {
					chuan_bi_gap_phai_200_tren_do();
				}
}


void qua_trai_len_bac_200_11_do (void) {
		int time_41 = 0;
		int time_23 = 0;
		int di_cheo_41 = 0;
		int di_cheo_23 = 0;
		if (TinHieu_QuaTrai == 1 && CB_Ha_Sau == 1 && (bientrochansauValue <= 300)) { // th vua gap trc xong
				time_41 = 9000;
				time_23 = 9000;
				di_cheo_41 = -450;
				di_cheo_23 = -1350;
		}
		else if (TinHieu_QuaTrai == 1 && CB_Ha_Sau == 1 && (bientrochansauValue >= 300)) { // TH k gap di ngang
				time_41 = 3500;
				time_23 = 3500;
				di_cheo_41 = 450;
				di_cheo_23 = 1350;
		}
		else {
				time_41 = 4500;
				time_23 = 4500;
				di_cheo_41 = -450;
				di_cheo_23 = -1350;
		}
		TinHieu_QuaTrai = 0;
		/// ***************************
		if (da_lay_tay1 == 0 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
				MD_qua_trai_phai_len_bac_200(-1800, -900, -850, 10,-900, 0, -1800);
			}
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
				MD_qua_trai_phai_len_bac_200(-1800, -900, di_cheo_41, time_41,-900, 0, -1800);
			}
			//// gap 2 lan r
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {		
				MD_qua_trai_phai_len_bac_200(-1800, -900, di_cheo_41, time_41,-900, 0, -1800);
			}
		//// gap 3 lan r
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 0) {		
				MD_qua_trai_phai_len_bac_200(-1800, -900, di_cheo_23, time_23,-900, 0, -1800);
			}
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 1) {		
				MD_qua_trai_phai_len_bac_200(-1800, -900, di_cheo_23, time_23,-900, 0, -1800);
			}
		
		robotStop(0);
		su_dung_chan(265);
		for(i=0;i<50;i++)		
			{
				while(abs(bientrochansauValue - target_chan_sau) > 20)	{vTaskDelay(1); if(!wantExit())	break;}
			}
		
		if (TinHieu_ChuanBi_GapThang == 0 && TinHieu_ChuanBi_GapTrai == 0 && TinHieu_ChuanBi_GapPhai == 0) {
				// chay toi khi mat cam bien sau
				robotRunAngle(900,22,-900,0.5);
				for(i=0;i<1550;i++)
						{
								while(CB_Ha_Sau == 0 || (abs(bientrochansauValue - target_chan_sau) > 20))	
							{	
								if(!wantExit())	break;
								vTaskDelay (1);
							}
						}
			}
	
		else if (TinHieu_ChuanBi_GapTrai == 1 ) {
				chuan_bi_gap_trai_200_duoi_ko_thanh_do();
		}
		// CO LENH GAP PHAI
		else if (TinHieu_ChuanBi_GapPhai == 1 ) {
					chuan_bi_gap_phai_200_duoi_ko_thanh_do();
		}
}


void qua_trai_xuong_bac_200_12_do (void) {
		int time_41 = 0;
		int time_23 = 0;
		int di_cheo_41 = 0;
		int di_cheo_23 = 0;
		if (TinHieu_QuaTrai == 1 && CB_Ha_Sau == 1 && (bientrochansauValue <= 300)) { // th vua gap trc xong
				time_41 = 9000;
				time_23 = 9000;
				di_cheo_41 = -450;
				di_cheo_23 = -1350;
		}
		else if (TinHieu_QuaTrai == 1 && CB_Ha_Sau == 1 && (bientrochansauValue >= 300)) { // TH k gap di ngang
				time_41 = 3500;
				time_23 = 3500;
				di_cheo_41 = 450;
				di_cheo_23 = 1350;
		}
		else {
				time_41 = 4500;
				time_23 = 4500;
				di_cheo_41 = -450;
				di_cheo_23 = -1350;
		}
		TinHieu_QuaTrai = 0;
		/// ***************************
		if (da_lay_tay1 == 0 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
				MD_qua_trai_phai_xuong_bac_200(-1800, -900, -850, 10,-900, 0, -1800);
			}
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
				MD_qua_trai_phai_xuong_bac_200(-1800, -900, di_cheo_41, time_41,-900, 0, -1800);
			}
			//// gap 2 lan r
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {		
				MD_qua_trai_phai_xuong_bac_200(-1800, -900, di_cheo_41, time_41,-900, 0, -1800);
			}
		//// gap 3 lan r
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 0) {		
				MD_qua_trai_phai_xuong_bac_200(-1800, -900, di_cheo_23, time_23,-900, 0, -1800);
			}
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 1) {		
				MD_qua_trai_phai_xuong_bac_200(-1800, -900, di_cheo_23, time_23,-900, 0, -1800);
			}
		robotStop(0);
			
		su_dung_chan(265);
		for(i=0;i<50;i++)		
		{
			while(abs(bientrochansauValue - target_chan_sau) > 20)	{vTaskDelay(1); if(!wantExit())	break;}
		}
		if (TinHieu_ChuanBi_GapThang == 0 && TinHieu_ChuanBi_GapTrai == 0 && TinHieu_ChuanBi_GapPhai == 0) {
				// chay toi khi mat cam bien sau
				robotRunAngle(900,20,-900,0.5);
				for(i=0;i<1550;i++)
						{
								while(CB_Ha_Sau == 0 )	
							{	
								if(!wantExit())	break;
								vTaskDelay (1);
							}
						}

			}
		else if (TinHieu_ChuanBi_GapPhai == 1) {
					chuan_bi_gap_phai_200_tren_do();
				}
}

/// *********   HAM DI QUA PHAI TREN RUNG ************

void qua_phai_xuong_bac_200_4_do (void) {
		int time_41 = 0;
		int time_23 = 0;
		int di_cheo_41 = 0;
		int di_cheo_23 = 0;
		if (TinHieu_QuaPhai == 1  && CB_Cap_Thanh_Sau == 1) { // th vua gap trc xong
				time_41 = 9000;
				time_23 = 9000;
				di_cheo_41 = -450;
				di_cheo_23 = -1350;
		}
		else if (TinHieu_QuaPhai == 1 && CB_Cap_Thanh_Sau == 0) { // TH k gap di ngang
				time_41 = 3500;
				time_23 = 3500;
				di_cheo_41 = 450;
				di_cheo_23 = 1350;
		}
		else {
				time_41 = 4500;
				time_23 = 4500;
				di_cheo_41 = -450;
				di_cheo_23 = -1350;
		}
		TinHieu_QuaPhai = 0;
		// ***************************** //
		if (da_lay_tay1 == 0 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
				MD_qua_trai_phai_xuong_bac_200(0,-900, -750, 10,-900, 1800, 0);
			}
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
				MD_qua_trai_phai_xuong_bac_200(0,-900, di_cheo_41, time_41,-900, 1800, 0);
			}
			//// gap 2 lan r
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {		
				MD_qua_trai_phai_xuong_bac_200(0,-900, di_cheo_41, time_41,-900, 1800, 0);
			}
		//// gap 3 lan r
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 0) {		
				MD_qua_trai_phai_xuong_bac_200(0,-900, di_cheo_23, time_23,-900, 1800, 0);
			}
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 1) {		
				MD_qua_trai_phai_xuong_bac_200(0,-900, di_cheo_23, time_23,-900, 1800, 0);
			}
		robotStop(0);
			
		// KHONG CO TIN HIEU GAP
	if (TinHieu_ChuanBi_GapThang == 0 && TinHieu_ChuanBi_GapTrai == 0 && TinHieu_ChuanBi_GapPhai == 0) {
		Nang_nhanh();
		target_chan_truoc = Min_chan_truoc + 250;
		target_chan_sau = Min_chan_sau + 250;
		
		robotRunAngle(900,20,-900,0.7);

		for(i=0;i<1550;i++)
				{
					while(CB_Ha_Sau == 1  )	
						
					{	
						if(!wantExit())	break;
						vTaskDelay (1);
					}
				}
		robotRunAngle(900,12,-900,0.7);
		for(i=0;i<1550;i++)
				{
					while(CB_Cap_Thanh_Sau == 0 || (abs(bientrochansauValue - target_chan_sau) > 10))	
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


void qua_phai_len_bac_200_1_do (void) {
		if (da_lay_tay1 == 0 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
				MD_qua_trai_phai_len_bac_200(0,-900, -750, 3500,-900, 1800, 0);
			}
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
				MD_qua_trai_phai_len_bac_200(0,-900, -450, 4000,-900, 1800, 0);
			}
			//// gap 2 lan r
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {		
				MD_qua_trai_phai_len_bac_200(0,-900, -450, 4000,-900, 1800, 0);
			}
		//// gap 3 lan r
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 0) {		
				MD_qua_trai_phai_len_bac_200(0,-900, -1350, 4000,-900, 1800, 0);
			}
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 1) {		
				MD_qua_trai_phai_len_bac_200(0,-900, -1350, 4000,-900, 1800, 0);
			}
		robotStop(0);
		su_dung_chan(265);
		for(i=0;i<50;i++)		
				{
					while(abs(bientrochansauValue - target_chan_sau) > 20)	{vTaskDelay(1); if(!wantExit())	break;}
				}
				if (TinHieu_ChuanBi_GapThang == 0 && TinHieu_ChuanBi_GapTrai == 0 && TinHieu_ChuanBi_GapPhai == 0) {
				// chay toi khi mat cam bien sau
				robotRunAngle(900,20,-900,0.9);
				for(i=0;i<250;i++)
						{
								while(CB_Ha_Sau == 0 )
							{	
								vTaskDelay (1);
								if(!wantExit())	break;
							}
						}

					}
						
				if (TinHieu_ChuanBi_GapThang == 1 ) {
					di_tren_buc_khong_thanh_2_ben_do();
				}
				//	 CO LENH GAP TRAI
				else if (TinHieu_ChuanBi_GapTrai == 1 ) {
							chuan_bi_gap_trai_200_duoi_ko_thanh_do();
				}
				robotStop(0);	
}

void qua_phai_xuong_bac_200_2_do (void) {

		if (da_lay_tay1 == 0 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
				MD_qua_trai_phai_xuong_bac_200(0,-900, -750, 3500,-900, 1800, 0);
			}
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
				MD_qua_trai_phai_xuong_bac_200(0,-900, -450, 4000,-900, 1800, 0);
			}
			//// gap 2 lan r
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {		
				MD_qua_trai_phai_xuong_bac_200(0,-900, -450, 4000,-900, 1800, 0);
			}
		//// gap 3 lan r
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 0) {		
				MD_qua_trai_phai_xuong_bac_200(0,-900, -1350, 4000,-900, 1800, 0);
			}
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 1) {		
				MD_qua_trai_phai_xuong_bac_200(0,-900, -1350, 4000,-900, 1800, 0);
			}
		robotStop(0);

		Nang_nhanh();
		target_chan_truoc = Min_chan_truoc + 250;
		target_chan_sau = Min_chan_sau + 250;
		for(i=0;i<50;i++)		
		{
			while(abs(bientrochansauValue - target_chan_sau) > 100)	{vTaskDelay(1); if(!wantExit())	break;}
		}
		if (TinHieu_ChuanBi_GapThang == 0 && TinHieu_ChuanBi_GapTrai == 0 && TinHieu_ChuanBi_GapPhai == 0) {
				robotRunAngle(900,20,-900,0.7);
				for(i=0;i<1550;i++)
					{
					while(CB_Ha_Sau == 1 || (abs(bientrochansauValue - target_chan_sau) > 20)	 )	
						{	
							vTaskDelay (1);
							if(!wantExit())	break;
						}
					}
				robotRunAngle(900,12,-900,0.7);
				for(i=0;i<1550;i++)
					{
					while(CB_Ha_Sau == 1 || CB_Cap_Thanh_Sau == 0  )	
						{	
							vTaskDelay (1);
							if(!wantExit())	break;
						}
					}
				}
		else if (TinHieu_ChuanBi_GapThang == 1) {		
					chuan_bi_gap_thang_do_2();
			}
		else if (TinHieu_ChuanBi_GapPhai == 1) {		
					chuan_bi_gap_phai_200_tren_2_do();
			}
		else if (TinHieu_ChuanBi_GapTrai == 1) {		
					chuan_bi_gap_trai_200_tren_2_do();
			}
			robotStop(0); 		
		
}

void qua_phai_xuong_bac_200_5_do (void) {
		int time_41 = 0;
		int time_23 = 0;
		int di_cheo_41 = 0;
		int di_cheo_23 = 0;
		if (TinHieu_QuaPhai == 1 && CB_Ha_Sau == 1) { // th vua gap trc xong
				time_41 = 9000;
				time_23 = 9000;
				di_cheo_41 = -450;
				di_cheo_23 = -1350;
		}
		else if (TinHieu_QuaPhai == 1 && CB_Ha_Sau == 0 ) { // TH k gap di ngang
				time_41 = 3500;
				time_23 = 3500;
				di_cheo_41 = 450;
				di_cheo_23 = 1350;
		}
		else {
				time_41 = 4500;
				time_23 = 4500;
				di_cheo_41 = -450;
				di_cheo_23 = -1350;
		}
		TinHieu_QuaPhai = 0;
		/// ***************************
		if (da_lay_tay1 == 0 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
				MD_qua_trai_phai_xuong_bac_200(0,-900, -750, time_41,-900, 1800, 0);
			}
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
				MD_qua_trai_phai_xuong_bac_200(0,-900, di_cheo_41, time_41,-900, 1800, 0);
			}
			//// gap 2 lan r
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {		
				MD_qua_trai_phai_xuong_bac_200(0,-900, di_cheo_41, time_41,-900, 1800, 0);
			}
		//// gap 3 lan r
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 0) {		
				MD_qua_trai_phai_xuong_bac_200(0,-900, di_cheo_23, time_23,-900, 1800, 0);
			}
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 1) {		
				MD_qua_trai_phai_xuong_bac_200(0,-900, di_cheo_23, time_23,-900, 1800, 0);
			}
		robotStop(0);

		Nang_nhanh();
		target_chan_truoc = Min_chan_truoc + 250;
		target_chan_sau = Min_chan_sau + 250;
		
		// KHONG CO TIN HIEU GAP
		if (TinHieu_ChuanBi_GapThang == 0 && TinHieu_ChuanBi_GapTrai == 0 && TinHieu_ChuanBi_GapPhai == 0) {
				robotRunAngle(900,16,-900,0.7);
				for(i=0;i<1550;i++)
						{
					while(CB_Ha_Sau == 1 ||  CB_Cap_Thanh_Sau == 0 || (abs(bientrochansauValue - target_chan_sau) > 300) )	
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

void qua_phai_xuong_bac_200_7_do (void) {
		int time_41 = 0;
		int time_23 = 0;
		int di_cheo_41 = 0;
		int di_cheo_23 = 0;
		if (TinHieu_QuaPhai == 1 && CB_Ha_Sau == 1) { // th vua gap trc xong
				time_41 = 9000;
				time_23 = 9000;
				di_cheo_41 = -450;
				di_cheo_23 = -1350;
		}
		else if (TinHieu_QuaPhai == 1 && CB_Ha_Sau == 0 ) { // TH k gap di ngang
				time_41 = 3500;
				time_23 = 3500;
				di_cheo_41 = 450;
				di_cheo_23 = 1350;
		}
		else {
				time_41 = 4500;
				time_23 = 4500;
				di_cheo_41 = -450;
				di_cheo_23 = -1350;
		}
		TinHieu_QuaPhai = 0;
		/// ***************************
		if (da_lay_tay1 == 0 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
				MD_qua_trai_phai_xuong_bac_200(0,-900, -750, time_41,-900, 1800, 0);
			}
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
				MD_qua_trai_phai_xuong_bac_200(0,-900, di_cheo_41, time_41,-900, 1800, 0);
			}
			//// gap 2 lan r
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {		
				MD_qua_trai_phai_xuong_bac_200(0,-900, di_cheo_41, time_41,-900, 1800, 0);
			}
		//// gap 3 lan r
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 0) {		
				MD_qua_trai_phai_xuong_bac_200(0,-900, di_cheo_23, time_23,-900, 1800, 0);
			}
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 1) {		
				MD_qua_trai_phai_xuong_bac_200(0,-900, di_cheo_23, time_23,-900, 1800, 0);
			}
		robotStop(0);
			
		su_dung_chan(265);
		for(i=0;i<50;i++)		
				{
					while(abs(bientrochansauValue - target_chan_sau) > 20)	{vTaskDelay(1); if(!wantExit())	break;}
				}
		if (TinHieu_ChuanBi_GapThang == 0 && TinHieu_ChuanBi_GapTrai == 0 && TinHieu_ChuanBi_GapPhai == 0) {
			// chay toi khi mat cam bien sau
			robotRunAngle(900,20,-900,0.7);
			for(i=0;i<1550;i++)
					{
							while(CB_Ha_Sau == 0 	)	
				
						{	
							if(!wantExit())	break;
							vTaskDelay (1);
						}
					}
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

void qua_phai_len_bac_200_8_do (void) {
		int time_41 = 0;
		int time_23 = 0;
		int di_cheo_41 = 0;
		int di_cheo_23 = 0;
		if (TinHieu_QuaPhai == 1 && CB_Ha_Sau == 1 && (bientrochansauValue <= 300)) { // th vua gap trc xong
				time_41 = 9000;
				time_23 = 9000;
				di_cheo_41 = -450;
				di_cheo_23 = -1350;
		}
		else if (TinHieu_QuaPhai == 1 && CB_Ha_Sau == 1 && (bientrochansauValue >= 300)) { // TH k gap di ngang
				time_41 = 3500;
				time_23 = 3500;
				di_cheo_41 = 450;
				di_cheo_23 = 1350;
		}
		else {
				time_41 = 4500;
				time_23 = 4500;
				di_cheo_41 = -450;
				di_cheo_23 = -1350;
		}
		TinHieu_QuaPhai = 0;
		/// ***************************
		if (da_lay_tay1 == 0 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
				MD_qua_trai_phai_len_bac_200(0,-900, -750, 10,-900, 1800, 0);
			}
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
				MD_qua_trai_phai_len_bac_200(0,-900, di_cheo_41, time_41,-900, 1800, 0);
			}
			//// gap 2 lan r
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {		
				MD_qua_trai_phai_len_bac_200(0,-900, di_cheo_41, time_41,-900, 1800, 0);
			}
		//// gap 3 lan r
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 0) {		
				MD_qua_trai_phai_len_bac_200(0,-900, di_cheo_23, time_23,-900, 1800, 0);
			}
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 1) {		
				MD_qua_trai_phai_len_bac_200(0,-900, di_cheo_23, time_23,-900, 1800, 0);
			}
		robotStop(0);
		su_dung_chan(265);
		for(i=0;i<50;i++)		
				{
					while(abs(bientrochansauValue - target_chan_sau) > 20)	{vTaskDelay(1); if(!wantExit())	break;}
				}

	if (TinHieu_ChuanBi_GapThang == 0 && TinHieu_ChuanBi_GapTrai == 0 && TinHieu_ChuanBi_GapPhai == 0) {
		// chay toi khi mat cam bien sau
		robotRunAngle(900,20,-900,0.7);
		for(i=0;i<1550;i++)
				{
						while(CB_Ha_Sau == 0 )	
					{	
						if(!wantExit())	break;
						vTaskDelay (1);
					}
				}
				
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


void qua_phai_xuong_bac_200_10_do (void) {
		int time_41 = 0;
		int time_23 = 0;
		int di_cheo_41 = 0;
		int di_cheo_23 = 0;
		if (TinHieu_QuaPhai == 1 && CB_Ha_Sau == 1 && (bientrochansauValue <= 300)) { // th vua gap trc xong
				time_41 = 9000;
				time_23 = 9000;
				di_cheo_41 = -450;
				di_cheo_23 = -1350;
		}
		else if (TinHieu_QuaPhai == 1 && CB_Ha_Sau == 1 && (bientrochansauValue >= 300)) { // TH k gap di ngang
				time_41 = 3500;
				time_23 = 3500;
				di_cheo_41 = 450;
				di_cheo_23 = 1350;
		}
		else {
				time_41 = 4500;
				time_23 = 4500;
				di_cheo_41 = -450;
				di_cheo_23 = -1350;
		}
		TinHieu_QuaPhai = 0;
		/// ***************************
		if (da_lay_tay1 == 0 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
				MD_qua_trai_phai_xuong_bac_200(0,-900, -750, 10,-900, 1800, 0);
			}
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
				MD_qua_trai_phai_xuong_bac_200(0,-900, di_cheo_41, time_41,-900, 1800, 0);
			}
			//// gap 2 lan r
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {		
				MD_qua_trai_phai_xuong_bac_200(0,-900, di_cheo_41, time_41,-900, 1800, 0);
			}
		//// gap 3 lan r
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 0) {		
				MD_qua_trai_phai_xuong_bac_200(0,-900, di_cheo_23, time_23,-900, 1800, 0);
			}
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 1) {		
				MD_qua_trai_phai_xuong_bac_200(0,-900, di_cheo_23, time_23,-900, 1800, 0);
			}
		robotStop(0);
			
		su_dung_chan(265);
		for(i=0;i<50;i++)		
				{
					while(abs(bientrochansauValue - target_chan_sau) > 20)	{vTaskDelay(1); if(!wantExit())	break;}
				}
		if (TinHieu_ChuanBi_GapThang == 0 && TinHieu_ChuanBi_GapTrai == 0 && TinHieu_ChuanBi_GapPhai == 0) {
				// chay toi khi mat cam bien sau
				robotRunAngle(900,20,-900,0.5);
				for(i=0;i<1550;i++)
						{
								while(CB_Ha_Sau == 0 )	
							{	
								if(!wantExit())	break;
								vTaskDelay (1);
							}
						}
			}
		else if (TinHieu_ChuanBi_GapTrai == 1) {
					chuan_bi_gap_trai_200_tren_do_7_10();
			}

}

void qua_phai_len_bac_200_11_do (void) {
		int time_41 = 0;
		int time_23 = 0;
		int di_cheo_41 = 0;
		int di_cheo_23 = 0;
		if (TinHieu_QuaPhai == 1 && CB_Ha_Sau == 1 && (bientrochansauValue <= 300)) { // th vua gap trc xong
				time_41 = 9000;
				time_23 = 9000;
				di_cheo_41 = -450;
				di_cheo_23 = -1350;
		}
		else if (TinHieu_QuaPhai == 1 && CB_Ha_Sau == 1 && (bientrochansauValue >= 300)) { // TH k gap di ngang
				time_41 = 3500;
				time_23 = 3500;
				di_cheo_41 = 450;
				di_cheo_23 = 1350;
		}
		else {
				time_41 = 4500;
				time_23 = 4500;
				di_cheo_41 = -450;
				di_cheo_23 = -1350;
		}
		TinHieu_QuaPhai = 0;
		/// ***************************
		
		if (da_lay_tay1 == 0 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
				MD_qua_trai_phai_len_bac_200(0,-900, -750, 10,-900, 1800, 0);
			}
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
				MD_qua_trai_phai_len_bac_200(0,-900, di_cheo_41, time_41,-900, 1800, 0);
			}
			//// gap 2 lan r
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {		
				MD_qua_trai_phai_len_bac_200(0,-900, di_cheo_41, time_41,-900, 1800, 0);
			}
		//// gap 3 lan r
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 0) {		
				MD_qua_trai_phai_len_bac_200(0,-900, di_cheo_23, time_23,-900, 1800, 0);
			}
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 1) {		
				MD_qua_trai_phai_len_bac_200(0,-900, di_cheo_23, time_23,-900, 1800, 0);
			}
		robotStop(0);
		su_dung_chan(265);
		for(i=0;i<50;i++)		
				{
					while(abs(bientrochansauValue - target_chan_sau) > 20)	{vTaskDelay(1); if(!wantExit())	break;}
				}
		if (TinHieu_ChuanBi_GapThang == 0 && TinHieu_ChuanBi_GapTrai == 0 && TinHieu_ChuanBi_GapPhai == 0) {
				// chay toi khi mat cam bien sau
				robotRunAngle(900,20,-900,0.5);
				for(i=0;i<1550;i++)
						{
								while(CB_Ha_Sau == 0 )	
							{	
								if(!wantExit())	break;
								vTaskDelay (1);
							}
						}
			}
		else if (TinHieu_ChuanBi_GapTrai == 1 ) {
				chuan_bi_gap_trai_200_duoi_ko_thanh_do();
		}
		// CO LENH GAP PHAI
		else if (TinHieu_ChuanBi_GapPhai == 1 ) {
					chuan_bi_gap_phai_200_duoi_ko_thanh_do();
		}
		
}