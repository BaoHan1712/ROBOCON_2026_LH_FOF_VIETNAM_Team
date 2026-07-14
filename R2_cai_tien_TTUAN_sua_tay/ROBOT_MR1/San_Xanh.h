int	KC_Vu_khi;

extern int Vi_tri;
extern int da_lay_tay4;
extern int TinHieu_ChuanBi_GapThang;
extern int TinHieu_ChuanBi_GapTrai ;
extern int TinHieu_ChuanBi_GapPhai;
void ha_chan_dat_tang2_do (void);

void phun_tay_ra (void);
void run_align_center(void);
void kiem_tra_so_qua_tren_tay(void);
void tu_dong_dat_tang2_xanh(void);
void dat_hop4_2(int do_cao_chan, int goc_tay, int ha_chan, int chontay);
void dat_hop1_3(int do_cao_chan, int goc_tay, int ha_chan, int chontay);
void retry_co_qua_tren_tay(void);
void nghieng_tay_k_dat_tang2(void);
void dung_cho_khoi_r1_ben_canh (void);



void gap_ngang_2_ben_san_xanh (void){
		if (da_lay_tay1 == 1 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
					robotRunAngle(900,12,900,0.7);
					RESET_ENCODER(); 
					while(abs(ENCODER_FR())  < 500)	{vTaskDelay (1); if(!wantExit())	break;}
				}
				robotStop(0);
}


void reset_ha_tay_truoc (void) {
		KT_Ha_Tay_Trc_400 = 0;
		KT_Ha_Tay = 0;
		KT_Ha_Tay_Trc_200_Duoi = 0;
		led_bao_hieu_off;

}
//*************************** XUAT PHAT LAAYS VU KHI 3 ***********************************
void Xuat_Phat_Lay_Vu_Khi_Xanh(int vu_khi, int goc_ve,int vitri)
{				

				Tay_kep_mo;
	
				robotSetACC(45, 60); // gia toc

				Nang_nhanh();
				target_chan_truoc = 615, target_chan_sau =620;

				
				for(i=0;i<250;i++)
				{
					while(lazeTruocValue > 150)	
					{	
	
						Bam_thanh_laser_phai(42,0,0,vu_khi,2,150,20);
						
						if(!wantExit())	break;
					}
				}
				for(i=0;i<250;i++)
				{
					while(lazeTruocValue > 140)	
					{	
	
						Bam_thanh_laser_phai(14,0,0,vu_khi,1,80,10);
						
						if(!wantExit())	break;
					}
				}
				Tay_kep_xuong;

				for(i=0;i<100;i++)
				{
					while(HT_1 == 0 && HT_2 == 0)	
					{				
						if(lazeTruocValue < 140)	Tay_kep_xuong;
						Bam_thanh_laser_phai(10,0,0,vu_khi,1,70,10);
						if(!wantExit())	break;
					}
				}
				vTaskDelay(2000); 
			
				robotStop(50);
						
				for(i=0;i<500;i++)
				{
					while(CB_tay_kep_vk_T == 1 || CB_tay_kep_vk_P == 1)	
					{	
						if	(CB_tay_kep_vk_P == 1) robotRun(-870,10);
						else if 	(CB_tay_kep_vk_T == 1) robotRun(870,10);
						else		robotStop(0);				
						vTaskDelay (1);
						if(!wantExit())	break;
					}
				}	
				
				robotStop(0);
				
				Tay_kep_dong;
				
				vTaskDelay (1000);
				
				robotRun(0,6);
				
				vTaskDelay (2000);
				
				robotStop(30);

				KC_Vu_khi = lazePhaiValue;
				
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
				
				robotStop(2);
//				
				run_encoder(200, 1800, 0, 20, 8, 50, 10);
				
				robotRun(goc_ve - ((KC_Vu_khi - vu_khi)*5),50);
				robotRotate(-900,-1.2,0);
				
				speed_chan_sau = 120;
				speed_chan_truoc = 120;
		
				while(_robotIMUAngle >-450)	
				{
					vTaskDelay (1); 
					if(!wantExit())	break;
					if(_robotIMUAngle < -450)		target_chan_truoc = 265, target_chan_sau = 265;
				}
				
				target_chan_truoc = 265, target_chan_sau = 265;
				robotStop(0);
 
				robotRunAngle(900,18,-900,0.8);
				
				for(i=0;i<250;i++)
				{
					while(lazeSauValue > 133)	
					{	
						vTaskDelay(1); 
						if(!wantExit())	break;
					}
				}
				
				robotStop(2);

				robotSetACC(120, 85); // gia toc
				
				robotRunAngle(900,8,-900,0.7);
				for(i=0;i<100;i++)
				{
					while(HT_3 == 0 && HT_4 == 0)	
					{           
						vTaskDelay (1); 
						if(!wantExit())	break;
					}
				}
				robotStop(2);
				chinh_lai_vi_tri_VK(vitri, 1000, 6, 50, 0);
				robotStop(2);
				robotRunAngle(900,8,-900,0.7);
				vTaskDelay(3000);
				speed_chan_sau =50;
				speed_chan_truoc = 50;
				target_chan_truoc = 231, target_chan_sau = 231;
				
				robotStop(0);
			}

//******************** xoay dau detect xem co robot phia truoc hay khong ********************************************
void Xoay_dau_truoc_cua_xanh_1(void)
{
	Nang_cuc_nhanh();
	target_chan_truoc = 300;
	target_chan_sau = 300;

	
	robotSetACC(45, 60); // gia toc nhanh

	robotRunAngle(-1460,30,900,2);
//				
				while(_robotIMUAngle < 895)	
				{
					vTaskDelay (1); 
					if(!wantExit())	break;
				}
				
	robotStop(0);
				
	su_dung_chan(480);
	run_encoder(16000, -1540, 900, 70, 10, 6000, 100);
				
	if (TinHieu_ChuanBi_GapThang == 1) {
			chinh_lai_vi_tri_laser_phai_custom(vi_tri_cua_rung_xanh_1_lazer_phai_tay_41  , 1000, 10 , 60, 2);
	}
	else if (TinHieu_ChuanBi_GapThang == 0) {
			chinh_lai_vi_tri_laser_phai_custom(vi_tri_cua_rung_xanh_1_lazer_phai_tay_41 , 1000, 10 , 60, 4);
	}
	if (block_pha == 1) {
//			SEND_UART (4,1);
			cho_r1 = 1;
		}
	else {
		co_vat_can = 0 ;
	}
	
	robotSetACC(120, 85); // gia toc nhanh
	robotStop(0); 	
				
}

void Xoay_dau_truoc_cua_xanh_2 (void)
{
	Nang_cuc_nhanh();

	target_chan_truoc = 265;
	target_chan_sau = 265;

	
	vTaskDelay(2000);
	robotRunAngle(-1450,30,900,2);
//				
				while(_robotIMUAngle < 895)	
				{
					vTaskDelay (1); 
					if(!wantExit())	break;
				}
	robotStop(0);
	run_encoder(3800, 1800, 900, 60, 15, 800, 50);
				
	if (TinHieu_ChuanBi_GapThang == 0) {
			chinh_lai_vi_tri_laser_phai_custom(vi_tri_cua_rung_xanh_2_lazer_phai_tay_41  , 1000, 10, 70, 3);
	}
	else if (TinHieu_ChuanBi_GapThang == 1) {
			chinh_lai_vi_tri_laser_phai_custom(vi_tri_cua_rung_xanh_2_lazer_phai_tay_41  , 1000, 10, 70, 1);
	}
	robotStop(0); 
		if (block_pha == 2) {
	SEND_UART (4,1);
		}
	else {
		co_vat_can = 0 ;
	}
				
}


/// ********** XOAY DAU TOI CUA XANH 3

void Xoay_dau_truoc_cua_xanh_3 (void)
{
	Nang_cuc_nhanh();

	target_chan_truoc = 300;
	target_chan_sau = 300;
	
	robotSetACC(45, 60); // gia toc nhanh
	robotRunAngle(-1100,30,900,2.4);
//				
				while(_robotIMUAngle < 885)	
				{
					vTaskDelay (1); 
					if(!wantExit())	break;
				}
				
	robotStop(20);
				
	robotSetACC(55, 70); // gia toc nhanh
				
	if (TinHieu_ChuanBi_GapThang == 1) {
			chinh_lai_vi_tri_laser_phai_custom(vi_tri_cua_rung_xanh_3_lazer_phai_tay_41  , 1000, 10, 70, 1);
	}
	else if (TinHieu_ChuanBi_GapThang == 0) {
			chinh_lai_vi_tri_laser_phai_custom(vi_tri_cua_rung_xanh_3_lazer_phai_tay_41  , 1000, 10, 70, 3);
	}
	
	if (block_pha == 3) {
//			SEND_UART (4,1);
			cho_r1 = 1;
		}
	else {
		co_vat_can = 0 ;
	}
	robotStop(0); 	
	robotSetACC(120, 85); // gia toc nhanh
}


//////////////////////////////////////////////////////////////////////////////
void Vao_rung_mai_1_xanh(int vitri)
{
	Nang_nhanh();
	target_chan_truoc = Min_chan_truoc + 250;
	target_chan_sau = Min_chan_sau + 250;
	
	robotSetACC(45, 60); // gia toc nhanh

		for(i=0;i<250;i++)
		{
			while(lazeSauValue > 175)	
			{	
			Bam_thanh_laser_phai_cua_vao(60,-900,900,vitri,2,180,30);
				vTaskDelay (1);
				if(!wantExit())	break;
			}
				}
			for(i=0;i<250;i++)	
		{
			while(abs(bientrochansauValue - target_chan_sau) > 20)
									{	
			Bam_thanh_laser_phai_cua_vao(55,-900,900,vitri,2,180,30);
			if(!wantExit())	break;
						}
		}
	
	robotRunAngle(-900,45,900,0.9);
		for(i=0;i<250;i++)
					{
						while(lazeSauValue > 158)	
						{	
							vTaskDelay (1);
							if(!wantExit())	break;
						}
				}
				

			su_dung_chan_cuc_nhanh(720);
				
			robotSetACC(120, 85); // gia toc nhanh
		
	if (TinHieu_ChuanBi_GapThang == 0) {
			for(i=0;i<250;i++)
					{
						while(lazeSauValue > 135  )	
						{	
							Bam_thanh_laser_phai_cua_vao(25,-900,900,vitri ,1,150,30);
							vTaskDelay (1);
							if(!wantExit())	break;
						}
				}
					
				for(i=0;i<250;i++)
				{
					while( CB_Cap_Thanh_Sau == 0)	
					{	
						Bam_thanh_laser_phai_cua_vao(10,-900,900,vitri ,1,150,30);
						if(!wantExit())	break;
					}
				}
				robotStop(0);
				
				if (block_pha == 1) {
						led_bao_hieu_on;
						robotRunAngle(-900,14,900,0.6);
						vTaskDelay(2500);
						robotStop(0); 
						
						SEND_UART (4,5);
						robotStop(0); 

						for(i=0;i<250;i++)	
						{
						while(cho_r1 == 1)	{vTaskDelay(1); if(!wantExit())	break;}
						}
						led_bao_hieu_off;
						cho_r1 = 1;
				}
				
	}
	else if (TinHieu_ChuanBi_GapThang == 1) {
		
					for(i=0;i<250;i++)
					{
						while(lazeSauValue > 135)	
						{	
							Bam_thanh_laser_phai_cua_vao(25,-900,900,vitri ,1,180,30);
							vTaskDelay (1);
							if(!wantExit())	break;
						}
				}
				// PHUN TAY RA
				phun_tay_ra();
					for(i=0;i<250;i++)
				{
					while( CB_Cap_Thanh_Sau == 0)	
					{	
						
						Bam_thanh_laser_phai_cua_vao(10,-900,900,vitri,1,180,30);
						if(!wantExit())	break;
					}
				}
				robotStop(30); 	
			}
	
	
	robotStop(0); 	
	
				
}
//********************************** vao rung mai 2 gap kfs ********************************************
void Vao_rung_mai_2_xanh(int vitri)
{
	Nang_nhanh();
	target_chan_truoc = Min_chan_truoc + 250;
	target_chan_sau = Min_chan_sau + 250;
	
	robotSetACC(45, 60); // gia toc nhanh
	
	robotRunAngle(-900,65,900,0.9);
		for(i=0;i<250;i++)
					{
						while(lazeSauValue > 175)	
						{	
							vTaskDelay (1);
							if(!wantExit())	break;
						}
				}
	
		for(i=0;i<250;i++)
				{
					while(lazeSauValue > 158)	
					{	
						Bam_thanh_laser_phai(45,-900,900,vitri ,2,-180,30);
						vTaskDelay (1);
						if(!wantExit())	break;
					}
				}	
			
	robotSetACC(120, 85); // gia toc nhanh

	if (TinHieu_ChuanBi_GapThang == 0) {
			for(i=0;i<250;i++)
				{
					while(lazeSauValue > 135)	
					{	
						Bam_thanh_laser_phai(25,-900,900,vitri ,1,-150,30);
						vTaskDelay (1);
						if(!wantExit())	break;
					}
				}	
			for(i=0;i<1550;i++)
						{
							while(  CB_Cap_Thanh_Sau == 0)	
							{	
								Bam_thanh_laser_phai(10,-900,900,vitri ,1,-150,30);
								if(!wantExit())	break;
								vTaskDelay (1);
							}
						}
	}
	else if (TinHieu_ChuanBi_GapThang == 1) {
				su_dung_chan_thuong(565);	
				for(i=0;i<250;i++)
				{
					while(lazeSauValue > 135 || (abs(bientrochansauValue - target_chan_sau) > 200))	
					{	
						Bam_thanh_laser_phai(25,-900,900,vitri,1,-180,30);
						vTaskDelay (1);
						if(!wantExit())	break;
					}
			}
				// PHUN TAY RA
				phun_tay_ra();
				for(i=0;i<1550;i++)
						{
							while( CB_Cap_Thanh_Sau == 0)	
							{	
								Bam_thanh_laser_phai(10,-900,900,vitri,1,-150,30);
								if(!wantExit())	break;
								vTaskDelay (1);
							}
						}
						robotStop(30); 
	}
	
	robotStop(0); 			
						
}	

//********************************** vao rung mai 3 gap kfs ********************************************
void Vao_rung_mai_3_xanh(int vitri)
{
			//// Do chan len 1 nua
	Nang_cuc_nhanh();
	target_chan_truoc = Min_chan_truoc + 250;
	target_chan_sau = Min_chan_sau + 250;
	
	robotSetACC(55, 70); // gia toc nhanh
	
	robotRunAngle(-900,60,900,0.7);
	for(i=0;i<250;i++)
					{
						while(lazeSauValue > 175)	
						{	
							vTaskDelay (1);
							if(!wantExit())	break;
						}
				}

		for(i=0;i<250;i++)
					{
						while(lazeSauValue > 158)	
						{	
							Bam_thanh_laser_trai(45,-900,900,vitri ,2,150,30);
							vTaskDelay (1);
							if(!wantExit())	break;
						}
				}
					

		su_dung_chan(720);

	if (TinHieu_ChuanBi_GapThang == 0) {
			for(i=0;i<250;i++)
					{
						while(lazeSauValue > 135)	
						{	
							Bam_thanh_laser_trai(25,-900,900,vitri ,1,150,30);
							vTaskDelay (1);
							if(!wantExit())	break;
						}
				}
					
				for(i=0;i<1550;i++)
							{
									while( CB_Cap_Thanh_Sau == 0)	
								{	
									Bam_thanh_laser_trai(10,-900,900,vitri ,1,150,30);
									vTaskDelay (1);
									if(!wantExit())	break;
									
								}
							}
					robotStop(0);
							
				if (block_pha == 3) {
					led_bao_hieu_on;
					robotRunAngle(-900,15,900,0.6);
					vTaskDelay(2500);
					robotStop(0); 
					
					SEND_UART (4,5);
					robotStop(0); 

					for(i=0;i<250;i++)	
					{
					while(cho_r1 == 1)	{vTaskDelay(1); if(!wantExit())	break;}
					}
					led_bao_hieu_off;
					cho_r1 = 1;
			}
	}
	else if (TinHieu_ChuanBi_GapThang == 1) {
			for(i=0;i<250;i++)
					{
						while(lazeSauValue > 135)	
						{	
							Bam_thanh_laser_trai(25,-900,900,vitri ,1,150,30);
							vTaskDelay (1);
							if(!wantExit())	break;
						}
				}
			// PHUN TAY RA
				phun_tay_ra();
			for(i=0;i<1550;i++)
							{
									while( CB_Cap_Thanh_Sau == 0)	
								{	
									Bam_thanh_laser_trai(10,-900,900,vitri ,1,150,30);
									vTaskDelay (1);
									if(!wantExit())	break;
									
								}
							}
					robotStop(30); 
	}

	robotStop(0); 	
				
}
// ham nhan tin hieu khong co vat can
void vat_can (void) {
	led_bao_hieu_on;
	while(co_vat_can == 1)	{	
				vTaskDelay (1);
			if(!wantExit())	break;
				}
	led_bao_hieu_off;

}

///////////////////////////////////////////////////////////////
void auto_vao_rung_xanh_cua1(void) {
		Xoay_dau_truoc_cua_xanh_1();
//		vat_can();
//	if  (co_vat_can == 0 ) {
			Vao_rung_mai_1_xanh(vi_tri_cua_rung_xanh_1_lazer_phai_tay_41);
//			}
//			co_vat_can = 1;
		
	}


void auto_vao_rung_xanh_cua2(void) {
		Xoay_dau_truoc_cua_xanh_2();
		vat_can();
	if  (co_vat_can == 0 ) {
		Vao_rung_mai_2_xanh(vi_tri_cua_rung_xanh_2_lazer_phai_tay_41);
		}
	co_vat_can = 1;
}

void auto_vao_rung_xanh_cua3(void) {
		Xoay_dau_truoc_cua_xanh_3();
//		vat_can();
//	if  (co_vat_can == 0 ) {
		Vao_rung_mai_3_xanh(vi_tri_cua_rung_xanh_3_lazer_trai_tay_41);
		
//		co_vat_can = 1;
//	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////

//**************** Xuong_bac_200 ô 4********
void chuan_bi_gap_thang_xanh_4(void) {
		int vitri_tay41 = vitri_tay41_laser_trai_GapQua + 10;
		su_dung_chan_thuong(565);

		if (da_lay_tay1 == 0 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
				for(i=0;i<1550;i++) {
						while( CB_Cap_Thanh_Sau == 0 || (abs(bientrochansauValue - target_chan_sau) > 300) )	
						{	
						if(lazeTraiValue > vitri_tay41)			robotRunAngle(-450,20,900,0.7);
						else																robotRunAngle(-900,12,900,0.7), Tay2_len;
						vTaskDelay(1);
						if(!wantExit()) break;
									}
						
							}
					}
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
				for(i=0;i<1550;i++) {
						while( CB_Cap_Thanh_Sau == 0 ||(abs(bientrochansauValue - target_chan_sau) > 300))	
						{	
						if(lazeTraiValue > vitri_tay41)			robotRunAngle(-450,20,900,0.7);
						else																robotRunAngle(-900,12,900,0.7), Tay1_len;
						vTaskDelay(1);
						if(!wantExit()) break;
									}
						
							}
					}

		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
				while( CB_Cap_Thanh_Sau == 0 || (abs(bientrochansauValue - target_chan_sau) > 300) )	{
						if(CB_ROI_2  == 0 && CB_ROI_4 == 0)	robotRunAngle(-1550,20,900,0.7);
						else																robotRunAngle(-900,12,900,0.7), Tay2_len ;
						vTaskDelay(1);
						if(!wantExit()) break;
						}
						
						// chay toi roi thi di ngang qua trai
						robotRunAngle(1800,8,900,0.7);
						while (CB_ROI_2  == 0 )	 {
							vTaskDelay(1);
							if(!wantExit()) break;
						}
					
				}
		
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 0) {
				while( CB_Cap_Thanh_Sau == 0 || (abs(bientrochansauValue - target_chan_sau) > 300) )	{
				if(CB_ROI_2  == 0 && CB_ROI_4 == 0)	robotRunAngle(-1550,20,900,0.7);
				else																robotRunAngle(-900,12,900,0.7),Tay1_len;
				vTaskDelay(1);
				if(!wantExit()) break; }
				
				
				// chay toi roi thi di ngang qua trai
				robotRunAngle(1800,8,900,0.7);
				while (CB_ROI_2  == 0 )	 {
					vTaskDelay(1);
					if(!wantExit()) break;
							}
				}
			robotStop(0);
			robotRunAngle(-900,10,900,0.5);
			vTaskDelay(1500);
			robotStop(0); 	
}	

void chuan_bi_gap_phai_200_tren_3 (void ) {
	if (da_lay_tay1 == 0 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
			su_dung_chan(565);	
			robotRunAngle(100,18,900,0.5);
					for(i=0;i<150;i++)
					{
						while(lazeTraiValue > vitri_tay41_laser_trai_GapQua)	
						{	
							vTaskDelay (1);
							Tay2_len;
							if(!wantExit())	break;
						}
					}
			robotRunAngle(0,10,900,0.5);
			vTaskDelay (2000);
		}
	else if (da_lay_tay1 == 1 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
				su_dung_chan(565);	
				robotRunAngle(100,18,900,0.5);
					for(i=0;i<150;i++)
					{
						while(lazeTraiValue > vitri_tay41_laser_trai_GapQua)	
						{	
							vTaskDelay (1);
							Tay1_len;
							if(!wantExit())	break;
						}
					}
				robotRunAngle(0,10,900,0.5);
				vTaskDelay (2000);
		}
	else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
			chinh_lai_vi_tri_laser_trai(vitri_tay41_laser_trai_GapQua , 200);
			su_dung_chan_thuong(565);
			// chay toi khi laser sau cham 1
			robotRunAngle(-900,18,900,0.7);
			for(i=0;i<1550;i++)
						{
							while(lazeSauValue > 134 || (abs(bientrochansauValue - target_chan_sau) > 200) )	
							{	
								if(!wantExit())	break;
								vTaskDelay (1);
							}
						}
				Tay2_len;
				robotStop(0); 
				robotRunAngle(0,10,900,0.1);
				vTaskDelay(2500);
		}
	
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 0) {
				chinh_lai_vi_tri_laser_trai(vitri_tay41_laser_trai_GapQua , 200);
				su_dung_chan(565);
				robotRunAngle(-900,18,900,0.7);
				for(i=0;i<1550;i++)
					{
						while(lazeSauValue > 134 || (abs(bientrochansauValue - target_chan_sau) > 200) )	
						{	
							if(!wantExit())	break;
							vTaskDelay (1);
						}
							}
					Tay1_len;
					robotStop(0); 
					robotRunAngle(0,10,900,0.1);
					vTaskDelay(2500);
			}
		robotStop(0); 
}


void chuan_bi_gap_trai_200_tren_1 (void ) {
	if (da_lay_tay1 == 0 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
			su_dung_chan_thuong(565);	
			for(i=0;i<1550;i++) {
						while( lazeSauValue > 134 )	
						{	
						if(lazePhaiValue > vitri_tay23_phai_laser_GapQua)			robotRunAngle(-1550,18,900,0.7);
						else																									robotRunAngle(-900,12,900,0.7);
						vTaskDelay(1);
						if(!wantExit()) break;
									}
							}
				robotRunAngle(1800,14,900,0.1);
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
						while( lazeSauValue > 134 )	
						{	
						if(lazePhaiValue > vitri_tay23_phai_laser_GapQua)			robotRunAngle(-1550,18,900,0.7);
						else																									robotRunAngle(-900,12,900,0.7);
						vTaskDelay(1);
						if(!wantExit()) break;
									}
							}
				robotRunAngle(1800,14,900,0.1);
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
			robotRunAngle(1900,14,900,0.5);
					for(i=0;i<150;i++)
					{
						while(lazePhaiValue > vitri_tay23_phai_laser_GapQua)	
						{	
							vTaskDelay (1);
							if(!wantExit())	break;
						}
					}
				robotRunAngle(1800,10,900,0.5);
				vTaskDelay (2000);
		}
	
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 0) {
				su_dung_chan_thuong(565);	
				robotRunAngle(1900,14,900,0.5);
					for(i=0;i<150;i++)
					{
						while(lazePhaiValue > vitri_tay23_phai_laser_GapQua)	
						{	
							vTaskDelay (1);
							if(!wantExit())	break;
						}
					}
				robotRunAngle(1800,10,900,0.5);
				vTaskDelay (2000);
			}
		robotStop(0); 
}


void chuan_bi_gap_phai_200_tren_4 (void ) {
	if (da_lay_tay1 == 0 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
			su_dung_chan_thuong(565);	
			Tay2_len;
			robotRunAngle(180,14,900,0.5);
				for(i=0;i<150;i++)
					{
						while(lazeTraiValue > vitri_tay41_laser_trai_GapQua)	
						{	
							vTaskDelay (1);
							if(!wantExit())	break;
						}
					}
			vTaskDelay (2000);
		}
	else if (da_lay_tay1 == 1 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
				su_dung_chan_thuong(565);	
				Tay1_len;
				robotRunAngle(180,14,900,0.5);
					for(i=0;i<150;i++)
					{
						while(lazeTraiValue > vitri_tay41_laser_trai_GapQua)	
						{	
							vTaskDelay (1);
							if(!wantExit())	break;
						}
					}
				vTaskDelay (2000);
		}
	else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
			su_dung_chan_thuong(565);
			// chay toi khi laser sau cham 1
			robotRunAngle(-500,20,900,0.7);
			for(i=0;i<1550;i++)
						{
							while(lazeSauValue > 134 || (abs(bientrochansauValue - target_chan_sau) > 300) )	
							{	
								if(!wantExit())	break;
								vTaskDelay (1);
							}
						}
				Tay2_len;
				robotRunAngle(0,12,900,0.1);
				for(i=0;i<150;i++)
					{
						while(lazeTraiValue > vitri_tay41_laser_trai_GapQua)	
						{	
							vTaskDelay (1);
							if(!wantExit())	break;
						}
					}
				vTaskDelay(2500);
		}
	
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 0) {
				su_dung_chan_thuong(565);
			// chay toi khi laser sau cham 1
			robotRunAngle(-500,20,900,0.7);
			for(i=0;i<1550;i++)
						{
							while(lazeSauValue > 134 || (abs(bientrochansauValue - target_chan_sau) > 300) )	
							{	
								if(!wantExit())	break;
								vTaskDelay (1);
							}
						} 
				Tay1_len;
				robotRunAngle(0,12,900,0.1);
				for(i=0;i<150;i++)
					{
						while(lazeTraiValue > vitri_tay41_laser_trai_GapQua)	
						{	
							vTaskDelay (1);
							if(!wantExit())	break;
						}
					}
				vTaskDelay(2500);
			}
		robotStop(0); 
}

void chuan_bi_gap_trai_200_duoi_5 (void ) {

	if (da_lay_tay1 == 0 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
				// chuan bi xoay truoc sang trai
					ha_sat_xuong();
					while(HT_3 == 0 && HT_4 == 0 || (abs(bientrochansauValue - target_chan_sau) > 20))	 {
					if(CB_ROI_2  == 0 && CB_ROI_4 == 0)	robotRunAngle(-1350,16,900,0.7);
					else																robotRunAngle(-900,14,900,0.7);
					vTaskDelay(1);
					if(!wantExit()) break;
								}
					Tay2_len;
					// chay toi roi thi di ngang qua trai
					robotRunAngle(1800,8,900,0.7);
					while (CB_ROI_4  == 0 )	 {
						vTaskDelay(1);
						if(!wantExit()) break;
								}
					}
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
				// chuan bi xoay truoc sang trai
					ha_sat_xuong();
					while(HT_3 == 0 && HT_4 == 0 || (abs(bientrochansauValue - target_chan_sau) > 20))	 {
					if(CB_ROI_2  == 0 && CB_ROI_4 == 0)	robotRunAngle(-1350,16,900,0.7);
					else																robotRunAngle(-900,14,900,0.7);
					vTaskDelay(1);
					if(!wantExit()) break;
								}
					Tay1_len;
					// chay toi roi thi di ngang qua trai
					robotRunAngle(1800,8,900,0.7);
					while (CB_ROI_4  == 0 )	 {
						vTaskDelay(1);
						if(!wantExit()) break;
								}
				}
	
			//// gap duoi lan 3
		else if  (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
					ha_sat_xuong();
					{
					while(abs(bientrochansauValue - target_chan_sau) > 15)	{vTaskDelay(1); if(!wantExit())	break;}
						}
					robotRunAngle(1800,15,900,0.5);
					for(i=0;i<150;i++)
					{
						while(CB_ROI_2 == 0 || (abs(bientrochansauValue - target_chan_sau) > 40))	
						{	
							vTaskDelay (1);
							if(!wantExit())	break;
						}
					}
					Tay2_len;
					robotRunAngle(1800,8,900,0.5);
					for(i=0;i<150;i++)
					{
						while(CB_ROI_4 == 0 || (abs(bientrochansauValue - target_chan_sau) > 20))	
						{	
							vTaskDelay (1);
							if(!wantExit())	break;
						}
					}
				}
		//// gap duoi lan 4
		else if  (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 0) {
					ha_sat_xuong();
					{
					while(abs(bientrochansauValue - target_chan_sau) > 15)	{vTaskDelay(1); if(!wantExit())	break;}
						}
					robotRunAngle(1800,15,900,0.5);
					for(i=0;i<150;i++)
					{
						while(CB_ROI_2 == 0 || (abs(bientrochansauValue - target_chan_sau) > 40))	
						{	
							vTaskDelay (1);
							if(!wantExit())	break;
						}
					}
					Tay1_len;
					robotRunAngle(1800,8,900,0.8);
					for(i=0;i<150;i++)
					{
						while(CB_ROI_4 == 0 || (abs(bientrochansauValue - target_chan_sau) > 20))	
						{	
							vTaskDelay (1);
							if(!wantExit())	break;
						}
					}
				}
				robotStop(0);
}

void chuan_bi_gap_trai_200_duoi_ko_thanh (void ) {
	if (da_lay_tay1 == 0 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
					ha_sat_xuong();
					robotRunAngle(1800,22,900,0.8);
					for(i=0;i<150;i++)
					{
						while(CB_ROI_2 == 0 || (abs(bientrochansauValue - target_chan_sau) > 40))	
						{	
							vTaskDelay (1);
							if(!wantExit())	break;
						}
					}
					Tay2_len;
					robotRunAngle(1800,8,900,0.8);
					for(i=0;i<150;i++)
					{
						while(CB_ROI_4 == 0 || (abs(bientrochansauValue - target_chan_sau) > 20))	
						{	
							vTaskDelay (1);
							if(!wantExit())	break;
						}
					}
					robotStop(0);
					robotRunAngle(-900,18,900,0.8);
					RESET_ENCODER(); 
					while(abs(ENCODER_FR()) + abs(ENCODER_FL()) < 1650)	{
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
					robotRunAngle(1800,22,900,0.8);
					for(i=0;i<150;i++)
					{
						while(CB_ROI_2 == 0 || (abs(bientrochansauValue - target_chan_sau) > 40))	
						{	
							vTaskDelay (1);
							if(!wantExit())	break;
						}
					}
					Tay1_len;
					robotRunAngle(1800,8,900,0.8);
					for(i=0;i<150;i++)
					{
						while(CB_ROI_4 == 0 || (abs(bientrochansauValue - target_chan_sau) > 20))	
						{	
							vTaskDelay (1);
							if(!wantExit())	break;
						}
					}
					robotStop(0);
					robotRunAngle(-900,18,900,0.8);
					RESET_ENCODER(); 
					
					while(abs(ENCODER_FR()) + abs(ENCODER_FL()) < 1650)	{
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
					robotRunAngle(1800,22,900,0.8);
					for(i=0;i<150;i++)
					{
						while(CB_ROI_2 == 0 || (abs(bientrochansauValue - target_chan_sau) > 40))	
						{	
							vTaskDelay (1);
							if(!wantExit())	break;
						}
					}
					Tay2_len;
					robotRunAngle(1800,8,900,0.8);
					for(i=0;i<150;i++)
					{
						while(CB_ROI_4 == 0 || (abs(bientrochansauValue - target_chan_sau) > 20))	
						{	
							vTaskDelay (1);
							if(!wantExit())	break;
						}
					}
				}
					//// gap duoi lan 4
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 0) {
					ha_sat_xuong();
					robotRunAngle(1800,22,900,0.8);
					for(i=0;i<150;i++)
					{
						while(CB_ROI_2 == 0 || (abs(bientrochansauValue - target_chan_sau) > 40))	
						{	
							vTaskDelay (1);
							if(!wantExit())	break;
						}
					}
					Tay1_len;
					robotRunAngle(1800,8,900,0.8);
					for(i=0;i<150;i++)
					{
						while(CB_ROI_4 == 0 || (abs(bientrochansauValue - target_chan_sau) > 20))	
						{	
							vTaskDelay (1);
							if(!wantExit())	break;
						}
					}
				}
				robotStop(0);
}


void chuan_bi_gap_phai_200_duoi_ko_thanh (void ) {
	
	if (da_lay_tay1 == 0 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
					ha_sat_xuong();
		
					robotRunAngle(50,22,900,0.8);
					for(i=0;i<150;i++)
					{
						while(CB_ROI_3 == 0 )	
						{	
							vTaskDelay (1);
							if(!wantExit())	break;
						}
					}
					Tay2_len;
					robotRunAngle(0,8,900,0.8);
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
					robotRunAngle(50,22,900,0.8);
					for(i=0;i<150;i++)
					{
						while(CB_ROI_3 == 0 ||  (abs(bientrochansauValue - target_chan_sau) > 30))	
						{	
							vTaskDelay (1);
							if(!wantExit())	break;
						}
					}
					Tay1_len;
					robotRunAngle(0,8,900,0.8);
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
					robotRunAngle(0,22,900,0.8);
					for(i=0;i<150;i++)
					{
						while(CB_ROI_3 == 0 ||  (abs(bientrochansauValue - target_chan_sau) > 30))	
						{	
							vTaskDelay (1);
							if(!wantExit())	break;
						}
					}
					Tay2_len;
					robotRunAngle(0,8,900,0.8);
					for(i=0;i<150;i++)
					{
						while(CB_ROI_1 == 0 )	
						{	
							vTaskDelay (1);
							if(!wantExit())	break;
						}
					}
					robotStop(0);
					
					robotRunAngle(-900,18,900,0.8);
					RESET_ENCODER(); 
					while(abs(ENCODER_FR()) + abs(ENCODER_FL()) < 1650)	{
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
					robotRunAngle(0,22,900,0.8);
					for(i=0;i<150;i++)
					{
						while(CB_ROI_3 == 0 ||  (abs(bientrochansauValue - target_chan_sau) > 30))	
						{	
							vTaskDelay (1);
							if(!wantExit())	break;
						}
					}
					Tay1_len;
					robotRunAngle(0,8,900,0.8);
					for(i=0;i<150;i++)
					{
						while(CB_ROI_1 == 0 )	
						{	
							vTaskDelay (1);
							if(!wantExit())	break;
						}
					}
					robotStop(0);
					
					robotRunAngle(-900,18,900,0.8);
					RESET_ENCODER(); 
					while(abs(ENCODER_FR()) + abs(ENCODER_FL()) < 1650)	{
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

void chuan_bi_gap_phai_200_duoi_kt_8 (void ) {
	
	if (da_lay_tay1 == 0 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
					ha_sat_xuong();
		
					robotRunAngle(0,24,900,0.8);
					for(i=0;i<150;i++)
					{
						while(CB_ROI_3 == 0 )	
						{	
							vTaskDelay (1);
							if(!wantExit())	break;
						}
					}
					Tay2_len;
					robotRunAngle(0,8,900,0.8);
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
					robotRunAngle(0,24,900,0.8);
					for(i=0;i<150;i++)
					{
						while(CB_ROI_3 == 0 ||  (abs(bientrochansauValue - target_chan_sau) > 30))	
						{	
							vTaskDelay (1);
							if(!wantExit())	break;
						}
					}
					Tay1_len;
					robotRunAngle(0,9,900,0.8);
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
					robotRunAngle(0,25,900,0.8);
					for(i=0;i<150;i++)
					{
						while(CB_ROI_3 == 0 )	
						{	
							vTaskDelay (1);
							if(!wantExit())	break;
						}
					}
					
					Tay2_len;
					// chay toi roi thi di ngang qua phai
					robotRunAngle(0,8,900,0.7);
					while (CB_ROI_1  == 0 )	 {
						vTaskDelay(1);
						if(!wantExit()) break;
						}
				}
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 0) {		
					ha_sat_xuong();
					robotRunAngle(0,25,900,0.8);
					for(i=0;i<150;i++)
					{
						while(CB_ROI_3 == 0 )	
						{	
							vTaskDelay (1);
							if(!wantExit())	break;
						}
					}
					Tay1_len;
					// chay toi roi thi di ngang qua phai
					robotRunAngle(0,8,900,0.7);
					while (CB_ROI_1  == 0 )	 {
						vTaskDelay(1);
						if(!wantExit()) break;
						}
				}
				robotStop(0);
}



void Xuong_bac_200_xanh_4(void)
{	
	int vitri_tay41 = vitri_tay41_laser_trai_GapQua + 4;

	Xuong_bac_200(-900, 900);		
	
	// KHONG CO TIN HIEU GAP
	if (TinHieu_ChuanBi_GapThang == 0 && TinHieu_ChuanBi_GapTrai == 0 && TinHieu_ChuanBi_GapPhai == 0 && TinHieu_QuaPhai == 0) {
		Nang_thuong();
		target_chan_truoc = Min_chan_truoc + 250;
		target_chan_sau = Min_chan_sau + 250;
		
		robotRunAngle(-900,22,900,0.8);
		for(i=0;i<250;i++)	
	{
		while(abs(bientrochansauValue - target_chan_sau) > 40)	{vTaskDelay(1); if(!wantExit())	break;}
	}		
	
	for(i=0;i<1550;i++)
				{
					while(CB_Ha_Sau == 1 )	
						
					{	
						if(!wantExit())	break;
						vTaskDelay (1);
					}
				}
				
	}
	// CO LENH GAP THANG
		else if (TinHieu_ChuanBi_GapThang == 1 ) {
				chuan_bi_gap_thang_xanh_4();
				}	
		// CO LENH GAP PHAI
		else if (TinHieu_ChuanBi_GapPhai == 1 ) {
					chuan_bi_gap_phai_200_tren_4();
		}
		
//		robotStop(0); 	
}


//  *********** GAP BEN TRAI 200 DUOI XANH 3
	
void Lay_ben_trai_bac_200_duoi_xanh_3(void) {
			Lay_ben_trai_bac_200_duoi();
			robotStop(0);
			
	if (TinHieu_ChuanBi_GapThang == 1) {
			kiem_tra_huong_quay_tay_gap_phia_truoc();
			vTaskDelay (4000);
			chuan_bi_gap_thang_xanh_3();
		
				}
	}


//  *********** GAP BEN TRAI 200 DUOI XANH 5
	
void Lay_ben_trai_bac_200_duoi_xanh_5(void) {
			Lay_ben_trai_bac_200_duoi();
			robotStop(0);
			
	if (TinHieu_ChuanBi_GapPhai == 1 ) {
			kiem_tra_huong_quay_tay_gap_ben_phai();
			vTaskDelay (4000);
//			gap_ngang_2_ben_san_xanh();
			chuan_bi_gap_phai_200_tren_4();
		}
	
	else if (TinHieu_ChuanBi_GapThang == 1) {
			kiem_tra_huong_quay_tay_gap_phia_truoc();
			vTaskDelay (3000);
			chuan_bi_gap_thang_xanh_4();
			robotRunAngle(-900,12,900,0.7);
			while( CB_Cap_Thanh_Sau == 0 || (abs(bientrochansauValue - target_chan_sau) > 10) )	
						{	
						vTaskDelay(1);if(!wantExit()) break;
						}
				}
	robotStop(0);
}



void Lay_ben_trai_bac_200_duoi_xanh_ko_thanh(void) {
			Lay_ben_trai_bac_200_duoi();
			robotStop(0);
	
	if (TinHieu_ChuanBi_GapPhai == 1 ) {
			kiem_tra_huong_quay_tay_gap_ben_phai();
			vTaskDelay (1000);
			gap_ngang_2_ben_san_xanh();
//			chuan_bi_gap_phai_200_duoi_ko_thanh();
			chuan_bi_gap_phai_200_duoi_kt_8();
		}
	else if (TinHieu_ChuanBi_GapThang == 1) {
			kiem_tra_huong_quay_tay_gap_phia_truoc();
			vTaskDelay (3000);
			di_tren_buc_khong_thanh_2_ben();
				}
}

void Lay_ben_trai_bac_200_duoi_xanh_6(void) {
			Lay_ben_trai_bac_200_duoi();
			robotStop(0);

	if (TinHieu_ChuanBi_GapThang == 1) {
			kiem_tra_huong_quay_tay_gap_phia_truoc();
			vTaskDelay (1000);
			di_tren_buc_khong_thanh_2_ben();
				}
}

///////////////////////////////////////////////////////////////////////////////////////////////

/// ****** leo bac 200 o id  5 san xanh
void Leo_bac_200_xanh_5(void) {	
		Leo_bac_200(-900, 900);
		Nang_nhanh();
		target_chan_truoc = Min_chan_truoc + 250;
		target_chan_sau = Min_chan_sau + 250;
		
		// KHONG CO TIN HIEU GAP
		if (TinHieu_ChuanBi_GapThang == 0 && TinHieu_ChuanBi_GapTrai == 0 && TinHieu_ChuanBi_GapPhai == 0 && TinHieu_QuaPhai == 0 && TinHieu_QuaTrai == 0) {
				robotRunAngle(-900,21,900,0.7);
				for(i=0;i<1550;i++)
				{
				while(CB_Ha_Sau == 1 || (abs(bientrochansauValue - target_chan_sau) > 20)	 )	
					{	
						vTaskDelay (1);
						if(!wantExit())	break;
					}
				}

				}
			
	// CO LENH GAP THANG
		else if (TinHieu_ChuanBi_GapThang == 1 ) {
				chuan_bi_gap_thang_xanh_4();
				}	
		// CO LENH GAP PHAI
		else if (TinHieu_ChuanBi_GapPhai == 1 ) {
					chuan_bi_gap_phai_200_tren_4();
		}
		// CO LENH GAP TRAI
		else if (TinHieu_ChuanBi_GapTrai == 1 ) {
					chuan_bi_gap_trai_200_duoi_5();
		}
		
//		robotStop(0); 			
}

void chuan_bi_gap_thang_xanh_7(void) {
		int vitri_tay41 = vitri_tay41_laser_trai_GapQua + 10;
		su_dung_chan(265);
		
	// chinh lai vi tri cho tay gap
		if (da_lay_tay1 == 0 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
					while(CB_Ha_Sau == 0 || (abs(bientrochansauValue - target_chan_sau) > 20)) 
					{	
						if(lazeTraiValue > vitri_tay41)			robotRunAngle(-450,20,900,0.7);
						else																robotRunAngle(-900,20,900,0.7);
						vTaskDelay(1);
						if(!wantExit()) break;
									}
			}
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
					while(CB_Ha_Sau == 0 || (abs(bientrochansauValue - target_chan_sau) > 20)) 
					{	
						if(lazeTraiValue > vitri_tay41)			robotRunAngle(-450,20,900,0.7);
						else																robotRunAngle(-900,20,900,0.7);
						vTaskDelay(1);
						if(!wantExit()) break;
									}
			}

		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
				while( CB_Ha_Sau == 0 || (abs(bientrochansauValue - target_chan_sau) > 20)) {
				if(CB_ROI_2  == 0 && CB_ROI_4 == 0)	robotRunAngle(-1550,20,900,0.7);
				else																robotRunAngle(-900,20,900,0.7);
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
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 0) {
					while(CB_Ha_Sau == 0 || (abs(bientrochansauValue - target_chan_sau) > 20)) {
				if(CB_ROI_2  == 0 && CB_ROI_4 == 0)	robotRunAngle(-1550,20,900,0.7);
				else																robotRunAngle(-900,20,900,0.7);
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
		
		robotRunAngle(-900,10,900,0.7);
		RESET_ENCODER(); 
		while(abs(ENCODER_FR()) + abs(ENCODER_FL()) < 250)	{vTaskDelay (1); if(!wantExit())	break;}
		robotStop(0);	
}


// CHUAN BI GAP PHAI XANH 7 VA 10
void chuan_bi_gap_phai_200_tren_7_10 (void ) {
	if (da_lay_tay1 == 0 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
			su_dung_chan(565);
				for(i=0;i<250;i++)	
			{
				while(abs(bientrochansauValue - target_chan_sau) > 100)	{vTaskDelay(1); if(!wantExit())	break;}
			}
			Tay2_len;
			robotRunAngle(0,12,900,0.5);
				for(i=0;i<150;i++)
					{
						while(lazeTraiValue > vitri_tay41_laser_trai_GapQua)	
						{	
							vTaskDelay (1);
							if(!wantExit())	break;
						}
					}
			vTaskDelay (2000);
		}
	
	else if (da_lay_tay1 == 1 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
			su_dung_chan(565);
				for(i=0;i<250;i++)	
			{
				while(abs(bientrochansauValue - target_chan_sau) > 100)	{vTaskDelay(1); if(!wantExit())	break;}
			}
			Tay1_len;
			robotRunAngle(0,12,900,0.5);
				for(i=0;i<150;i++)
					{
						while(lazeTraiValue > vitri_tay41_laser_trai_GapQua)	
						{	
							vTaskDelay (1);
							if(!wantExit())	break;
						}
					}
			vTaskDelay (2000);
		}
	
			/// gap lan 3
	else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {		
			su_dung_chan_thuong(565);
				for(i=0;i<250;i++)	
			{
				while(abs(bientrochansauValue - target_chan_sau) > 300)	{vTaskDelay(1); if(!wantExit())	break;}
			}
			
			robotRunAngle(-650,16,900,0.8);
			RESET_ENCODER(); 
			while(abs(ENCODER_FR()) + abs(ENCODER_FL()) < 1680)	{vTaskDelay (1); if(!wantExit())	break;}
			robotStop(0);
			Tay2_len;
			robotRunAngle(0,12,900,0.5);
				for(i=0;i<150;i++)
					{
						while(lazeTraiValue > vitri_tay41_laser_trai_GapQua)	
						{	
							vTaskDelay (1);
							if(!wantExit())	break;
						}
					}
			vTaskDelay (2000);
		}
	/// gap lan 4
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 0) {
			
				su_dung_chan_thuong(565);
				for(i=0;i<250;i++)	
			{
				while(abs(bientrochansauValue - target_chan_sau) > 300)	{vTaskDelay(1); if(!wantExit())	break;}
			}
			
			robotRunAngle(-650,16,900,0.8);
			RESET_ENCODER(); 
			while(abs(ENCODER_FR()) + abs(ENCODER_FL()) < 1680)	{vTaskDelay (1); if(!wantExit())	break;}
			robotStop(0);
			Tay1_len;
			robotRunAngle(0,12,900,0.5);
				for(i=0;i<150;i++)
					{
						while(lazeTraiValue > vitri_tay41_laser_trai_GapQua)	
						{	
							vTaskDelay (1);
							if(!wantExit())	break;
						}
					}
			vTaskDelay (2000);
		}
	
		robotStop(0); 
}


// ************* leo bac 200 xanh o 7************
void Leo_bac_200_xanh_7(void)  {	
		Leo_bac_200(-900, 900);
			
			// KHONG CO TIN HIEU GAP
	if (TinHieu_ChuanBi_GapThang == 0 && TinHieu_ChuanBi_GapTrai == 0 && TinHieu_ChuanBi_GapPhai == 0 && TinHieu_QuaPhai == 0) {
			su_dung_chan(265);
			// chay toi khi mat cam bien sau
			robotRunAngle(-900,25,900,0.7);
			for(i=0;i<1550;i++)
					{
							while( CB_Ha_Sau == 0 || (abs(bientrochansauValue - target_chan_sau) > 30)	)	

						{	
							if(!wantExit())	break;
							vTaskDelay (1);
						}
					}

					
//			robotStop(0);
			}
	
			// CO TIN HIEU GAP THANG
	else if (TinHieu_ChuanBi_GapThang == 1) {
				chuan_bi_gap_thang_xanh_7();
				}
		// CO TIN HIEU GAP PHAI
	else if (TinHieu_ChuanBi_GapPhai == 1) {
					chuan_bi_gap_phai_200_tren_7_10();
			}
//	robotStop(0); 	
		}

//**************** Xuong_bac_200 xanh ô 9 **************		
void chuan_bi_gap_thang_xanh_9 (void) {
		int vitri_tay23 = vitri_tay23_phai_laser_GapQua + 10;
		su_dung_chan(265);
	
			// chinh lai vi tri cho tay gap
		if (da_lay_tay1 == 0 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
				while(CB_Ha_Sau == 0|| (abs(bientrochansauValue - target_chan_sau) > 40)) {
				if(CB_ROI_3  == 0 && CB_ROI_1 == 0)	robotRunAngle(-400,20,900,0.7);
				else																robotRunAngle(-900,20,900,0.7);
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
				while(CB_Ha_Sau == 0 || (abs(bientrochansauValue - target_chan_sau) > 40)) {
				if(CB_ROI_3  == 0 && CB_ROI_1 == 0)	robotRunAngle(-400,20,900,0.7);
				else																robotRunAngle(-900,20,900,0.7);
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

		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
					while( CB_Ha_Sau == 0 || (abs(bientrochansauValue - target_chan_sau) > 40)) 
					{	
					if(lazePhaiValue > vitri_tay23)			robotRunAngle(-1550,20,900,0.7);
					else																robotRunAngle(-900,20,900,0.7);
					vTaskDelay(1);
					if(!wantExit()) break; }
			}
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 0) {
					while( CB_Ha_Sau == 0 || (abs(bientrochansauValue - target_chan_sau) > 40) ) 
					{	
					if(lazePhaiValue > vitri_tay23)			robotRunAngle(-1550,20,900,0.7);
					else																robotRunAngle(-900,20,900,0.7);
					vTaskDelay(1);
					if(!wantExit()) break; }
					}
		robotRunAngle(-900,10,900,0.7);
		RESET_ENCODER(); 
		while(abs(ENCODER_FR()) + abs(ENCODER_FL()) < 250)	{vTaskDelay (1); if(!wantExit())	break;}
		robotStop(0);	
	}


void chuan_bi_gap_trai_200_tren (void ) {
	if (da_lay_tay1 == 0 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
			su_dung_chan_thuong(565);
			robotRunAngle(-1800,10,900,0.9);
				for(i=0;i<150;i++)
					{
				while(lazePhaiValue > vitri_tay23_phai_laser_GapQua )	
						{	
							vTaskDelay (1);
							if(!wantExit())	break;
						}
					}
				vTaskDelay (2500);
				Tay2_len;
				robotRunAngle(-910,12,900,0.9);
					for(i=0;i<150;i++)
					{
						while(lazeTruocValue < 144 || (abs(bientrochansauValue - target_chan_sau) > 300))	
						{	
							vTaskDelay (1);
							if(!wantExit())	break;
						}
					}
		}
	else if (da_lay_tay1 == 1 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
					su_dung_chan_thuong(565);
					robotRunAngle(-1800,10,900,0.9);
						for(i=0;i<150;i++)
							{
						while(lazePhaiValue > vitri_tay23_phai_laser_GapQua )	
								{	
									vTaskDelay (1);
									if(!wantExit())	break;
								}
							}
						vTaskDelay (2500);
						Tay2_len;
						robotRunAngle(-910,12,900,0.9);
							for(i=0;i<150;i++)
							{
								while(lazeTruocValue < 144 || (abs(bientrochansauValue - target_chan_sau) > 300))	
								{	
									vTaskDelay (1);
									if(!wantExit())	break;
								}
							}
		}
	else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
				su_dung_chan_thuong(565);
				Tay2_len;
				robotRunAngle(1650,10,900,0.9);
				for(i=0;i<150;i++)
					{
				while(lazePhaiValue > vitri_tay23_phai_laser_GapQua || (abs(bientrochansauValue - target_chan_sau) > 200))	
						{	
							vTaskDelay (1);
							if(!wantExit())	break;
						}
					}
					vTaskDelay(2500);
		}
	
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 0) {
				su_dung_chan_thuong(565);
				Tay1_len;
				robotRunAngle(1650,10,900,0.9);
				for(i=0;i<150;i++)
					{
				while(lazePhaiValue > vitri_tay23_phai_laser_GapQua || (abs(bientrochansauValue - target_chan_sau) > 200))	
						{	
							vTaskDelay (1);
							if(!wantExit())	break;
						}
					}
					vTaskDelay(2500);
		}
	
		robotStop(0); 
}


void Xuong_bac_200_xanh_9(void){	
		Xuong_bac_200(-900, 900);
		
		if (TinHieu_ChuanBi_GapThang == 0 && TinHieu_ChuanBi_GapTrai == 0 && TinHieu_ChuanBi_GapPhai == 0 && TinHieu_QuaTrai == 0 ) {
				// chay toi khi mat cam bien sau
				su_dung_chan(265);
				robotRunAngle(-900,25,900,0.8);
				for(i=0;i<250;i++)
							{
							while( CB_Ha_Sau == 0 || (abs(bientrochansauValue - target_chan_sau) > 40) ) 
								{	vTaskDelay (1); if(!wantExit())	break;
							}
						}

						
//				robotStop(0);
				}				
	
		else if (TinHieu_ChuanBi_GapThang == 1) {
					chuan_bi_gap_thang_xanh_9();
					}
		else if (TinHieu_ChuanBi_GapTrai == 1) {
					chuan_bi_gap_trai_200_tren();
				}
//			robotStop(0);
	}

void Lay_ben_trai_bac_200_tren_xanh_1(void) {
			Lay_ben_trai_bac_200_tren();
			robotStop(0);
	
	if (TinHieu_ChuanBi_GapPhai == 1) {	
			kiem_tra_huong_quay_tay_gap_ben_phai();
			vTaskDelay (3000);
			gap_ngang_2_ben_san_xanh();
			chuan_bi_gap_phai_200_tren_3();
		}
	else if (TinHieu_ChuanBi_GapThang == 1) {
			kiem_tra_huong_quay_tay_gap_phia_truoc();
			vTaskDelay (4000);
			chuan_bi_thang_xanh_2();
			}
	robotStop(0);
}
	
void Lay_ben_trai_bac_200_tren_xanh_9(void) {
			Lay_ben_trai_bac_200_tren();
			robotStop(0);
			
		if (TinHieu_ChuanBi_GapThang == 1) {
			kiem_tra_huong_quay_tay_gap_phia_truoc();
			vTaskDelay (4000);
			su_dung_chan(265);
			for(i=0;i<50;i++)		
				{
					while(abs(bientrochansauValue - target_chan_sau) > 10)	{vTaskDelay(1); if(!wantExit())	break;}
				}
			chuan_bi_gap_thang_xanh_9();
				}
		robotStop(0);
}

void xuong_bac_200_xanh_12(void) {
		Xuong_bac_200(-900, 900);
		
		if (TinHieu_ChuanBi_GapThang == 0 && TinHieu_ChuanBi_GapTrai == 0 && TinHieu_ChuanBi_GapPhai == 0 && TinHieu_QuaTrai == 0) {
				su_dung_chan(265);
				// chay toi khi mat cam bien sau
				robotRunAngle(-900,25,900,0.8);
				for(i=0;i<1550;i++)
						{
								while(CB_Ha_Sau == 0 || (abs(bientrochansauValue - target_chan_sau) > 30))	
							{	
								if(!wantExit())	break;
								vTaskDelay (1);
							}
						}
						
//				robotStop(0);
			
			}
		else if (TinHieu_ChuanBi_GapTrai == 1) {
					chuan_bi_gap_trai_200_tren();
				}
//			robotStop(0);
}


/// ****** DI NGANG PHAI **************


void qua_phai_xuong_bac_200_2_xanh (void) {
		if (da_lay_tay1 == 0 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
				MD_qua_trai_phai_xuong_bac_200(1800, 900, 850, 5500,900, 0, 1800);
			}
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
				MD_qua_trai_phai_xuong_bac_200(1800, 900, 1450, 5500,900, 0, 1800);
			}
			//// gap 2 lan r
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {		
				MD_qua_trai_phai_xuong_bac_200(1800, 900, 1450, 5500,900, 0, 1800);
			}
		//// gap 3 lan r
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 0) {		
				MD_qua_trai_phai_xuong_bac_200(1800, 900, 450, 5500,900, 0, 1800);
			}
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 1) {		
				MD_qua_trai_phai_xuong_bac_200(1800, 900, 450, 5500,900, 0, 1800);
			}
		robotStop(0);
			
		su_dung_chan(480);
		for(i=0;i<250;i++)	
		{
		while(abs(bientrochansauValue - target_chan_sau) > 20)	{vTaskDelay(1); if(!wantExit())	break;}
		}	
		if (TinHieu_ChuanBi_GapThang == 0 && TinHieu_ChuanBi_GapTrai == 0 && TinHieu_ChuanBi_GapPhai == 0) {
				robotRunAngle(-900,20,900,0.7);
				for(i=0;i<1550;i++)
						{
							while(CB_Ha_Sau == 1  || (abs(bientrochansauValue - target_chan_sau) > 20))	
							{	
								vTaskDelay (1);
								if(!wantExit())	break;
							}
						}

				robotRunAngle(-900,10,900,0.7);
				for(i=0;i<1550;i++)
						{
							while(CB_Cap_Thanh_Sau == 0)	
							{	
								vTaskDelay (1);
								if(!wantExit())	break;
							}
						}
					}
			else if (TinHieu_ChuanBi_GapThang == 1) {		
						chuan_bi_thang_xanh_2();
				}
			else if (TinHieu_ChuanBi_GapPhai == 1) {		
						chuan_bi_gap_phai_200_tren_3();
				}
			else if (TinHieu_ChuanBi_GapTrai == 1) {		
						chuan_bi_gap_trai_200_tren_1();
				}
 					
}

void qua_phai_len_bac_200_3_xanh (void) {
		if (da_lay_tay1 == 0 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
				MD_qua_trai_phai_len_bac_200(1800, 900, 850, 5500,900, 0, 1800);
			}
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
				MD_qua_trai_phai_len_bac_200(1800, 900, 1450, 5500,900, 0, 1800);
			}
			//// gap 2 lan r
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {		
				MD_qua_trai_phai_len_bac_200(1800, 900, 1450, 5500,900, 0, 1800);
			}
		//// gap 3 lan r
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 0) {		
				MD_qua_trai_phai_len_bac_200(1800, 900, 450, 5500,900, 0, 1800);
			}
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 1) {		
				MD_qua_trai_phai_len_bac_200(1800, 900, 450, 5500,900, 0, 1800);
			}
		robotStop(0);
			
		Nang_nhanh();
		target_chan_truoc = Min_chan_truoc + 250;
		target_chan_sau = Min_chan_sau + 250;
		for(i=0;i<250;i++)	
		{
		while(abs(bientrochansauValue - target_chan_sau) > 100)	{vTaskDelay(1); if(!wantExit())	break;}
		}	
		if (TinHieu_ChuanBi_GapThang == 0 && TinHieu_ChuanBi_GapTrai == 0 && TinHieu_ChuanBi_GapPhai == 0) {
				robotRunAngle(-900,20,900,0.7);
				for(i=0;i<1550;i++)
						{
							while(CB_Ha_Sau == 1  || (abs(bientrochansauValue - target_chan_sau) > 20))	
							{	
								vTaskDelay (1);
								if(!wantExit())	break;
							}
						}

				robotRunAngle(-900,10,900,0.7);
				for(i=0;i<1550;i++)
						{
							while(CB_Cap_Thanh_Sau == 0)	
							{	
								vTaskDelay (1);
								if(!wantExit())	break;
							}
						}
					}
			
			else if (TinHieu_ChuanBi_GapThang == 1) {
				chuan_bi_gap_thang_xanh_3();
			}

			// CO LENH GAP TRAI
			else if (TinHieu_ChuanBi_GapTrai == 1 ) {
						chuan_bi_gap_trai_200_duoi_5();
			}

}

void qua_phai_len_bac_200_5_xanh (void) {
		int time_41 = 0;
		int time_23 = 0;
		int di_cheo_41 = 0;
		int di_cheo_23 = 0;
		if (TinHieu_QuaPhai == 1  && CB_Cap_Thanh_Sau == 1) { // th vua gap trc xong
				time_41 = 9000;
				time_23 = 9000;
				di_cheo_41 = 1450;
				di_cheo_23 = 450;
		}
		else if (TinHieu_QuaPhai == 1 && CB_Cap_Thanh_Sau == 0) { // TH k gap di ngang
				time_41 = 4000;
				time_23 = 4000;
				di_cheo_41 = -1450;
				di_cheo_23 = -450;
		}
		else {
				time_41 = 4500;
				time_23 = 4500;
				di_cheo_41 = 1450;
				di_cheo_23 = 450;
		}
		TinHieu_QuaPhai = 0;
		// ***************************** //
		if (da_lay_tay1 == 0 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
				MD_qua_trai_phai_len_bac_200(1800, 900, 850, 10,900, 0, 1800);
			}
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
				MD_qua_trai_phai_len_bac_200(1800, 900, di_cheo_41, time_41,900, 0, 1800);
			}
			//// gap 2 lan r
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {		
				MD_qua_trai_phai_len_bac_200(1800, 900, di_cheo_41, time_41,900, 0, 1800);
			}
		//// gap 3 lan r
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 0) {		
				MD_qua_trai_phai_len_bac_200(1800, 900, di_cheo_23, time_23,900, 0, 1800);
			}
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 1) {		
				MD_qua_trai_phai_len_bac_200(1800, 900, di_cheo_23, time_23,900, 0, 1800);
			}
		robotStop(0);
			
		Nang_nhanh();
		target_chan_truoc = Min_chan_truoc + 250;
		target_chan_sau = Min_chan_sau + 250;
		for(i=0;i<250;i++)	
		{
		while(abs(bientrochansauValue - target_chan_sau) > 100)	{vTaskDelay(1); if(!wantExit())	break;}
		}	
		
		// KHONG CO TIN HIEU GAP
		if (TinHieu_ChuanBi_GapThang == 0 && TinHieu_ChuanBi_GapTrai == 0 && TinHieu_ChuanBi_GapPhai == 0) {
				robotRunAngle(-900,20,900,0.8);	
				for(i=0;i<1550;i++)
						{
							while(CB_Ha_Sau == 1 )	
							{	
								if(!wantExit())	break;
								vTaskDelay (1);
							}
						}
			robotRunAngle(-900,10,900,0.8);
			for(i=0;i<1550;i++)
						{
							while(CB_Ha_Sau == 1  || CB_Cap_Thanh_Sau == 0 )	
								
							{	
								if(!wantExit())	break;
								vTaskDelay (1);
							}
						}
			}
				
		// CO LENH GAP THANG
			else if (TinHieu_ChuanBi_GapThang == 1 ) {
					chuan_bi_gap_thang_xanh_4();
					}	
			// CO LENH GAP PHAI
			else if (TinHieu_ChuanBi_GapPhai == 1 ) {
						chuan_bi_gap_phai_200_tren_4();
			}
			// CO LENH GAP TRAI
			else if (TinHieu_ChuanBi_GapTrai == 1 ) {
						chuan_bi_gap_trai_200_duoi_5();
			}
						
}

void qua_phai_len_bac_200_6_xanh (void) {
		int time_41 = 0;
		int time_23 = 0;
		int di_cheo_41 = 0;
		int di_cheo_23 = 0;
		if (TinHieu_QuaPhai == 1 && CB_Cap_Thanh_Sau == 1) { // th vua gap trc xong
				time_41 = 9000;
				time_23 = 9000;
				di_cheo_41 = 1450;
				di_cheo_23 = 450;
		}
		else if (TinHieu_QuaPhai == 1 && CB_Cap_Thanh_Sau == 0 ) { // TH k gap di ngang
				time_41 = 4000;
				time_23 = 4000;
				di_cheo_41 = -1450;
				di_cheo_23 = -450;
		}
		else {
				time_41 = 4500;
				time_23 = 4500;
				di_cheo_41 = 1450;
				di_cheo_23 = 450;
		}
		TinHieu_QuaPhai = 0;
		/// ***************************
		
		if (da_lay_tay1 == 0 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
				MD_qua_trai_phai_len_bac_200(1800, 900, 850, 10,900, 0, 1800);
			}
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
				MD_qua_trai_phai_len_bac_200(1800, 900, di_cheo_41, time_41,900, 0, 1800);
			}
			//// gap 2 lan r
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {		
				MD_qua_trai_phai_len_bac_200(1800, 900, di_cheo_41, time_41,900, 0, 1800);
			}
		//// gap 3 lan r
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 0) {		
				MD_qua_trai_phai_len_bac_200(1800, 900, di_cheo_23, time_23,900, 0, 1800);
			}
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 1) {		
				MD_qua_trai_phai_len_bac_200(1800, 900, di_cheo_23, time_23,900, 0, 1800);
			}
		robotStop(0);
			
		su_dung_chan(265);
		for(i=0;i<250;i++)	
		{
		while(abs(bientrochansauValue - target_chan_sau) > 20)	{vTaskDelay(1); if(!wantExit())	break;}
		}	
		
		if (TinHieu_ChuanBi_GapThang == 0 && TinHieu_ChuanBi_GapTrai == 0 && TinHieu_ChuanBi_GapPhai == 0) {
			// chay toi khi mat cam bien sau
			robotRunAngle(-900,20,900,0.7);
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

void qua_phai_len_bac_200_8_xanh (void) {
		int time_41 = 0;
		int time_23 = 0;
		int di_cheo_41 = 0;
		int di_cheo_23 = 0;
		if (TinHieu_QuaPhai == 1 && CB_Ha_Sau == 1 && (bientrochansauValue <= 300)) { // th vua gap trc xong
				time_41 = 9000;
				time_23 = 9000;
				di_cheo_41 = 1450;
				di_cheo_23 = 450;
		}
		else if (TinHieu_QuaPhai == 1 && CB_Ha_Sau == 0 && (bientrochansauValue <= 300)) { // TH k gap di ngang
				time_41 = 4000;
				time_23 = 4000;
				di_cheo_41 = -1450;
				di_cheo_23 = -450;
		}
		else {
				time_41 = 4500;
				time_23 = 4500;
				di_cheo_41 = 1450;
				di_cheo_23 = 450;
		}
		TinHieu_QuaPhai = 0;
		/// ***************************
		if (da_lay_tay1 == 0 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
				MD_qua_trai_phai_len_bac_200(1800, 900, 850, 10,900, 0, 1800);
			}
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
				MD_qua_trai_phai_len_bac_200(1800, 900, di_cheo_41, time_41,900, 0, 1800);
			}
			//// gap 2 lan r
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {		
				MD_qua_trai_phai_len_bac_200(1800, 900, di_cheo_41, time_41,900, 0, 1800);
			}
		//// gap 3 lan r
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 0) {		
				MD_qua_trai_phai_len_bac_200(1800, 900, di_cheo_23, time_23,900, 0, 1800);
			}
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 1) {		
				MD_qua_trai_phai_len_bac_200(1800, 900, di_cheo_23, time_23,900, 0, 1800);
			}
		robotStop(0);
			
		su_dung_chan(265);
		for(i=0;i<250;i++)	
		{
		while(abs(bientrochansauValue - target_chan_sau) > 20)	{vTaskDelay(1); if(!wantExit())	break;}
		}	
		
		if (TinHieu_ChuanBi_GapThang == 0 && TinHieu_ChuanBi_GapTrai == 0 && TinHieu_ChuanBi_GapPhai == 0) {
			// chay toi khi mat cam bien sau
			robotRunAngle(-900,20,900,0.7);
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

void qua_phai_xuong_bac_200_9_xanh (void) {
		int time_41 = 0;
		int time_23 = 0;
		int di_cheo_41 = 0;
		int di_cheo_23 = 0;
		if (TinHieu_QuaPhai == 1 && CB_Ha_Sau == 1) { // th vua gap trc xong
				time_41 = 9000;
				time_23 = 9000;
				di_cheo_41 = 1450;
				di_cheo_23 = 450;
		}
		else if (TinHieu_QuaPhai == 1 && CB_Ha_Sau == 0 ) { // TH k gap di ngang
				time_41 = 4000;
				time_23 = 4000;
				di_cheo_41 = -1450;
				di_cheo_23 = -450;
		}
		else {
				time_41 = 4500;
				time_23 = 4500;
				di_cheo_41 = 1450;
				di_cheo_23 = 450;
		}
		TinHieu_QuaPhai = 0;
		/// ***************************
		if (da_lay_tay1 == 0 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
				MD_qua_trai_phai_xuong_bac_200(1800, 900, 850, 10,900, 0, 1800);
			}
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
				MD_qua_trai_phai_xuong_bac_200(1800, 900, di_cheo_41, time_41,900, 0, 1800);
			}
			//// gap 2 lan r
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {		
				MD_qua_trai_phai_xuong_bac_200(1800, 900, di_cheo_41, time_41,900, 0, 1800);
			}
		//// gap 3 lan r
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 0) {		
				MD_qua_trai_phai_xuong_bac_200(1800, 900, di_cheo_23, time_23,900, 0, 1800);
			}
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 1) {		
				MD_qua_trai_phai_xuong_bac_200(1800, 900, di_cheo_23, time_23,900, 0, 1800);
			}
		robotStop(0);
			
		su_dung_chan(265);
		for(i=0;i<250;i++)	
		{
		while(abs(bientrochansauValue - target_chan_sau) > 20)	{vTaskDelay(1); if(!wantExit())	break;}
		}	
		
		if (TinHieu_ChuanBi_GapThang == 0 && TinHieu_ChuanBi_GapTrai == 0 && TinHieu_ChuanBi_GapPhai == 0) {
				// chay toi khi mat cam bien sau
				robotRunAngle(-900,20,900,0.8);
				for(i=0;i<250;i++)
							{
							while( CB_Ha_Sau == 0 ) 
								{	vTaskDelay (1); if(!wantExit())	break;
							}
						}
				}				
		else if (TinHieu_ChuanBi_GapThang == 1) {
					chuan_bi_gap_thang_xanh_9();
					}
		else if (TinHieu_ChuanBi_GapTrai == 1) {
					chuan_bi_gap_trai_200_tren();
				}
}


void qua_phai_len_bac_200_11_xanh (void) {
		int time_41 = 0;
		int time_23 = 0;
		int di_cheo_41 = 0;
		int di_cheo_23 = 0;
		if (TinHieu_QuaPhai == 1 && CB_Ha_Sau == 1 && (bientrochansauValue <= 300)) { // th vua gap trc xong
				time_41 = 9000;
				time_23 = 9000;
				di_cheo_41 = 1450;
				di_cheo_23 = 450;
		}
		else if (TinHieu_QuaPhai == 1 && CB_Ha_Sau == 1 && (bientrochansauValue >= 300)) { // TH k gap di ngang
				time_41 = 3500;
				time_23 = 3500;
				di_cheo_41 = -1450;
				di_cheo_23 = -450;
		}
		else {
				time_41 = 4500;
				time_23 = 4500;
				di_cheo_41 = 1450;
				di_cheo_23 = 450;
		}
		TinHieu_QuaPhai = 0;
		/// ************************
		if (da_lay_tay1 == 0 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
				MD_qua_trai_phai_len_bac_200(1800, 900, 850, 10,900, 0, 1800);
			}
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
				MD_qua_trai_phai_len_bac_200(1800, 900, di_cheo_41, time_41,900, 0, 1800);
			}
			//// gap 2 lan r
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {		
				MD_qua_trai_phai_len_bac_200(1800, 900, di_cheo_41, time_41,900, 0, 1800);
			}
		//// gap 3 lan r
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 0) {		
				MD_qua_trai_phai_len_bac_200(1800, 900, di_cheo_23, time_23,900, 0, 1800);
			}
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 1) {		
				MD_qua_trai_phai_len_bac_200(1800, 900, di_cheo_23, time_23,900, 0, 1800);
			}
		robotStop(0);
			
		su_dung_chan(265);
		for(i=0;i<250;i++)	
		{
		while(abs(bientrochansauValue - target_chan_sau) > 20)	{vTaskDelay(1); if(!wantExit())	break;}
		}	
		if (TinHieu_ChuanBi_GapThang == 0 && TinHieu_ChuanBi_GapTrai == 0 && TinHieu_ChuanBi_GapPhai == 0) {
				// chay toi khi mat cam bien sau
				robotRunAngle(-900,20,900,0.8);
				for(i=0;i<1550;i++)
						{
								while(CB_Ha_Sau == 0)	
							{	
								if(!wantExit())	break;
								vTaskDelay (1);
							}
						}
			}
		else if (TinHieu_ChuanBi_GapTrai == 1 ) {
				chuan_bi_gap_trai_200_duoi_ko_thanh();
		}
		// CO LENH GAP PHAI
		else if (TinHieu_ChuanBi_GapPhai == 1 ) {
					chuan_bi_gap_phai_200_duoi_ko_thanh();
		}	
}


void qua_phai_xuong_bac_200_12_xanh (void) {
		int time_41 = 0;
		int time_23 = 0;
		int di_cheo_41 = 0;
		int di_cheo_23 = 0;
		if (TinHieu_QuaPhai == 1 && CB_Ha_Sau == 1 && (bientrochansauValue <= 300)) { // th vua gap trc xong
				time_41 = 9000;
				time_23 = 9000;
				di_cheo_41 = 1450;
				di_cheo_23 = 450;	
		}
		else if (TinHieu_QuaPhai == 1 && CB_Ha_Sau == 1 && (bientrochansauValue >= 300)) { // TH k gap di ngang
				time_41 = 3500;
				time_23 = 3500;
				di_cheo_41 = -1450;
				di_cheo_23 = -450;
		}
		else {
				time_41 = 4500;
				time_23 = 4500;
				di_cheo_41 = 1450;
				di_cheo_23 = 450;
		}
		TinHieu_QuaPhai = 0;
		/// ************************
		if (da_lay_tay1 == 0 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
				MD_qua_trai_phai_xuong_bac_200(1800, 900, 850, 10,900, 0, 1800);
			}
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
				MD_qua_trai_phai_xuong_bac_200(1800, 900, di_cheo_41, time_41,900, 0, 1800);
			}
			//// gap 2 lan r
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {		
				MD_qua_trai_phai_xuong_bac_200(1800, 900, di_cheo_41, time_41,900, 0, 1800);
			}
		//// gap 3 lan r
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 0) {		
				MD_qua_trai_phai_xuong_bac_200(1800, 900, di_cheo_23, time_23,900, 0, 1800);
			}
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 1) {		
				MD_qua_trai_phai_xuong_bac_200(1800, 900, di_cheo_23, time_23,900, 0, 1800);
			}
		robotStop(0);
			
		su_dung_chan(265);
		for(i=0;i<250;i++)	
		{
		while(abs(bientrochansauValue - target_chan_sau) > 20)	{vTaskDelay(1); if(!wantExit())	break;}
		}	
		if (TinHieu_ChuanBi_GapThang == 0 && TinHieu_ChuanBi_GapTrai == 0 && TinHieu_ChuanBi_GapPhai == 0) {
				// chay toi khi mat cam bien sau
				robotRunAngle(-900,20,900,0.8);
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
					chuan_bi_gap_trai_200_tren();
				}
}

/// ******** QUA TRAI SAN XANH **********


void qua_trai_xuong_bac_200_2_xanh (void) {
		if (da_lay_tay1 == 0 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
				MD_qua_trai_phai_xuong_bac_200(0, 900, 850, 4500,900, -1800, 0);
			}
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
				MD_qua_trai_phai_xuong_bac_200(0, 900, 1450, 4500,900, -1800, 0);
			}
			//// gap 2 lan r
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {		
				MD_qua_trai_phai_xuong_bac_200(0, 900, 1450, 4500,900, -1800, 0);
			}
		//// gap 3 lan r
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 0) {		
				MD_qua_trai_phai_xuong_bac_200(0, 900, 450, 4500,900, -1800, 0);
			}
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 1) {		
				MD_qua_trai_phai_xuong_bac_200(0, 900, 450, 4500,900, -1800, 0);
			}
		robotStop(0);
		Nang_thuong();
		target_chan_truoc = Min_chan_truoc + 250;
		target_chan_sau = Min_chan_sau + 250;
		for(i=0;i<250;i++)	
			{
				while(abs(bientrochansauValue - target_chan_sau) > 150)	{vTaskDelay(1); if(!wantExit())	break;}
			}	
		if (TinHieu_ChuanBi_GapThang == 0 && TinHieu_ChuanBi_GapTrai == 0 && TinHieu_ChuanBi_GapPhai == 0) {
			robotRunAngle(-900,14,900,0.7);
			for(i=0;i<1550;i++)
				{
				while(CB_Ha_Sau == 1 || CB_Cap_Thanh_Sau == 0 || (abs(bientrochansauValue - target_chan_sau) > 20))	
					{	
						vTaskDelay (1);
						if(!wantExit())	break;
					}
				}
			}
		
	else if (TinHieu_ChuanBi_GapThang == 1) {		
				chuan_bi_thang_xanh_2();
		}
		else if (TinHieu_ChuanBi_GapPhai == 1) {		
				chuan_bi_gap_phai_200_tren_3();
		}
		else if (TinHieu_ChuanBi_GapTrai == 1) {		
				chuan_bi_gap_trai_200_tren_1();
		}
						
}
			

void qua_trai_xuong_bac_200_4_xanh (void) {
		int time_41 = 0;
		int time_23 = 0;
		int di_cheo_41 = 0;
		int di_cheo_23 = 0;
		if (TinHieu_QuaTrai == 1 && CB_Cap_Thanh_Sau == 1) { // th vua gap trc xong
				time_41 = 9000;
				time_23 = 9000;
				di_cheo_41 = 1450;
				di_cheo_23 = 450;
		}
		else if (TinHieu_QuaTrai == 1 && CB_Cap_Thanh_Sau == 0 ) { // TH k gap di ngang
				time_41 = 4000;
				time_23 = 4000;
				di_cheo_41 = -1450;
				di_cheo_23 = -450;
		}
		else {
				time_41 = 4500;
				time_23 = 4500;
				di_cheo_41 = 1450;
				di_cheo_23 = 450;
		}
		TinHieu_QuaTrai = 0;
		/// ***************************
		if (da_lay_tay1 == 0 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
				MD_qua_trai_phai_xuong_bac_200(0, 900, 850, 10,900, -1800, 0);
			}
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
				MD_qua_trai_phai_xuong_bac_200(0, 900, di_cheo_41, time_41,900, -1800, 0);
			}
			//// gap 2 lan r
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {		
				MD_qua_trai_phai_xuong_bac_200(0, 900, di_cheo_41, time_41,900, -1800, 0);
			}
		//// gap 3 lan r
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 0) {		
				MD_qua_trai_phai_xuong_bac_200(0, 900, di_cheo_23, time_23,900, -1800, 0);
			}
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 1) {		
				MD_qua_trai_phai_xuong_bac_200(0, 900, di_cheo_23, time_23,900, -1800, 0);
			}
		robotStop(0);
		Nang_thuong();
		target_chan_truoc = Min_chan_truoc + 250;
		target_chan_sau = Min_chan_sau + 250;
		for(i=0;i<250;i++)	
			{
				while(abs(bientrochansauValue - target_chan_sau) > 100)	{vTaskDelay(1); if(!wantExit())	break;}
			}	
			
		if (TinHieu_ChuanBi_GapThang == 0 && TinHieu_ChuanBi_GapTrai == 0 && TinHieu_ChuanBi_GapPhai == 0) {
				robotRunAngle(-900,20,900,0.8);
				for(i=0;i<1550;i++)
							{
								while(CB_Ha_Sau == 1 )	
									
								{	
									if(!wantExit())	break;
									vTaskDelay (1);
								}
							}
					robotRunAngle(-900,10,900,0.8);
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
				}
				// CO LENH GAP THANG
					else if (TinHieu_ChuanBi_GapThang == 1 ) {
							chuan_bi_gap_thang_xanh_4();
							}	
					// CO LENH GAP PHAI
					else if (TinHieu_ChuanBi_GapPhai == 1 ) {
								chuan_bi_gap_phai_200_tren_4();
					}	
}


void qua_trai_len_bac_200_1_xanh (void) {
		if (da_lay_tay1 == 0 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
				MD_qua_trai_phai_len_bac_200(0, 900, 850, 4500,900, -1800, 0);
			}
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
				MD_qua_trai_phai_len_bac_200(0, 900, 1450, 4500,900, -1800, 0);
			}
			//// gap 2 lan r
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {		
				MD_qua_trai_phai_len_bac_200(0, 900, 1450, 4500,900, -1800, 0);
			}
		//// gap 3 lan r
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 0) {		
				MD_qua_trai_phai_len_bac_200(0, 900, 450, 4500,900, -1800, 0);
			}
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 1) {		
				MD_qua_trai_phai_len_bac_200(0, 900, 450, 4500,900, -1800, 0);
			}
		robotStop(0);			
		su_dung_chan(265);
		for(i=0;i<250;i++)	
			{
			while(abs(bientrochansauValue - target_chan_sau) > 20)	{vTaskDelay(1); if(!wantExit())	break;}
			}
		if (TinHieu_ChuanBi_GapThang == 0 && TinHieu_ChuanBi_GapTrai == 0 && TinHieu_ChuanBi_GapPhai == 0) {
				robotRunAngle(-900,22,900,0.9);
				for(i=0;i<250;i++)
						{
								while(CB_Ha_Sau == 0 )	

							{	
								vTaskDelay (1);
								if(!wantExit())	break;
							}
						}

					}
			else if (TinHieu_ChuanBi_GapThang == 1 ) {
					di_tren_buc_khong_thanh_2_ben();
				}
			else if (TinHieu_ChuanBi_GapPhai == 1 ) {
				chuan_bi_gap_phai_200_duoi_ko_thanh();
				}	
}

void qua_trai_xuong_bac_200_5_xanh (void) {
		int time_41 = 0;
		int time_23 = 0;
		int di_cheo_41 = 0;
		int di_cheo_23 = 0;
		if (TinHieu_QuaTrai == 1 && CB_Ha_Sau == 1) { // th vua gap trc xong
				time_41 = 9000;
				time_23 = 9000;
				di_cheo_41 = 1450;
				di_cheo_23 = 450;
		}
		else if (TinHieu_QuaTrai == 1 && CB_Ha_Sau == 0 ) { // TH k gap di ngang
				time_41 = 4000;
				time_23 = 4000;
				di_cheo_41 = -1450;
				di_cheo_23 = -450;
		}
		else {
				time_41 = 4500;
				time_23 = 4500;
				di_cheo_41 = 1450;
				di_cheo_23 = 450;
		}
		TinHieu_QuaTrai = 0;
		/// ***************************
		
		if (da_lay_tay1 == 0 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
				MD_qua_trai_phai_xuong_bac_200(0, 900, 850, 10,900, -1800, 0);
			}
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
				MD_qua_trai_phai_xuong_bac_200(0, 900, di_cheo_41, time_41,900, -1800, 0);
			}
			//// gap 2 lan r
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {		
				MD_qua_trai_phai_xuong_bac_200(0, 900, di_cheo_41, time_41,900, -1800, 0);
			}
		//// gap 3 lan r
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 0) {		
				MD_qua_trai_phai_xuong_bac_200(0, 900, di_cheo_23, time_23,900, -1800, 0);
			}
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 1) {		
				MD_qua_trai_phai_xuong_bac_200(0, 900, di_cheo_23, time_23,900, -1800, 0);
			}
		robotStop(0);
		Nang_thuong();
		target_chan_truoc = Min_chan_truoc + 250;
		target_chan_sau = Min_chan_sau + 250;
		for(i=0;i<250;i++)	
			{
				while(abs(bientrochansauValue - target_chan_sau) > 100)	{vTaskDelay(1); if(!wantExit())	break;}
			}	
		// KHONG CO TIN HIEU GAP
		if (TinHieu_ChuanBi_GapThang == 0 && TinHieu_ChuanBi_GapTrai == 0 && TinHieu_ChuanBi_GapPhai == 0) {
				robotRunAngle(-900,14,900,0.7);
				for(i=0;i<1550;i++)
						{
					while(CB_Ha_Sau == 1 ||  CB_Cap_Thanh_Sau == 0 )	
							{	
								if(!wantExit())	break;
								vTaskDelay (1);
							}
						}	
				}
			
	// CO LENH GAP THANG
		else if (TinHieu_ChuanBi_GapThang == 1 ) {
				chuan_bi_gap_thang_xanh_4();
				}	
		// CO LENH GAP PHAI
		else if (TinHieu_ChuanBi_GapPhai == 1 ) {
					chuan_bi_gap_phai_200_tren_4();
		}
		// CO LENH GAP TRAI
		else if (TinHieu_ChuanBi_GapTrai == 1 ) {
					chuan_bi_gap_trai_200_duoi_5();
		}
		
		
}


void qua_trai_xuong_bac_200_7_xanh (void) {
		int time_41 = 0;
		int time_23 = 0;
		int di_cheo_41 = 0;
		int di_cheo_23 = 0;
		if (TinHieu_QuaTrai == 1 && CB_Ha_Sau == 1 && (bientrochansauValue <= 300)) { // th vua gap trc xong
				time_41 = 9000;
				time_23 = 9000;
				di_cheo_41 = 1450;
				di_cheo_23 = 450;
		}
		else if (TinHieu_QuaTrai == 1 && CB_Ha_Sau == 0 && (bientrochansauValue <= 300)) { // TH k gap di ngang
				time_41 = 4000;
				time_23 = 4000;
				di_cheo_41 = -1450;
				di_cheo_23 = -450;
		}
		
		else {
				time_41 = 4500;
				time_23 = 4500;
				di_cheo_41 = 1450;
				di_cheo_23 = 450;
		}
		TinHieu_QuaTrai = 0;
		/// ***************************
		if (da_lay_tay1 == 0 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
				MD_qua_trai_phai_xuong_bac_200(0, 900, 850, 10,900, -1800, 0);
			}
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
				MD_qua_trai_phai_xuong_bac_200(0, 900, di_cheo_41, time_41,900, -1800, 0);
			}
			//// gap 2 lan r
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {		
				MD_qua_trai_phai_xuong_bac_200(0, 900, di_cheo_41, time_41,900, -1800, 0);
			}
		//// gap 3 lan r
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 0) {		
				MD_qua_trai_phai_xuong_bac_200(0, 900, di_cheo_23, time_23,900, -1800, 0);
			}
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 1) {		
				MD_qua_trai_phai_xuong_bac_200(0, 900, di_cheo_23, time_23,900, -1800, 0);
			}
		robotStop(0);
		Nang_thuong();
		target_chan_truoc = Min_chan_truoc + 250;
		target_chan_sau = Min_chan_sau + 250;
		for(i=0;i<250;i++)	
			{
				while(abs(bientrochansauValue - target_chan_sau) > 100)	{vTaskDelay(1); if(!wantExit())	break;}
			}	
		if (TinHieu_ChuanBi_GapThang == 0 && TinHieu_ChuanBi_GapTrai == 0 && TinHieu_ChuanBi_GapPhai == 0) {
				// chay toi khi mat cam bien sau
				robotRunAngle(-900,20,900,0.7);
				for(i=0;i<1550;i++)
						{
								while( CB_Ha_Sau == 0 	)	
							{	
								if(!wantExit())	break;
								vTaskDelay (1);
							}
						}

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


void qua_trai_len_bac_200_8_xanh (void) {
		int time_41 = 0;
		int time_23 = 0;
		int di_cheo_41 = 0;
		int di_cheo_23 = 0;
		if (TinHieu_QuaTrai == 1 && CB_Ha_Sau == 1 && (bientrochansauValue <= 300)) { // th vua gap trc xong
				time_41 = 9000;
				time_23 = 9000;
				di_cheo_41 = 1450;
				di_cheo_23 = 450;
		}
		else if (TinHieu_QuaTrai == 1 && CB_Ha_Sau == 1 && (bientrochansauValue >= 300)) { // TH k gap di ngang
				time_41 = 3500;
				time_23 = 3500;
				di_cheo_41 = -1450;
				di_cheo_23 = -450;
		}
		else {
				time_41 = 4500;
				time_23 = 4500;
				di_cheo_41 = 1450;
				di_cheo_23 = 450;
		}
		TinHieu_QuaTrai = 0;
		/// ***************************
		if (da_lay_tay1 == 0 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
				MD_qua_trai_phai_len_bac_200(0, 900, 850, 10,900, -1800, 0);
			}
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
				MD_qua_trai_phai_len_bac_200(0, 900, di_cheo_41, time_41,900, -1800, 0);
			}
			//// gap 2 lan r
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {		
				MD_qua_trai_phai_len_bac_200(0, 900, di_cheo_41, time_41,900, -1800, 0);
			}
		//// gap 3 lan r
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 0) {		
				MD_qua_trai_phai_len_bac_200(0, 900, di_cheo_23, time_23,900, -1800, 0);
			}
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 1) {		
				MD_qua_trai_phai_len_bac_200(0, 900, di_cheo_23, time_23,900, -1800, 0);
			}
		robotStop(0);			
		su_dung_chan(265);
		for(i=0;i<250;i++)	
			{
			while(abs(bientrochansauValue - target_chan_sau) > 20)	{vTaskDelay(1); if(!wantExit())	break;}
			}	
	
		if (TinHieu_ChuanBi_GapThang == 0 && TinHieu_ChuanBi_GapTrai == 0 && TinHieu_ChuanBi_GapPhai == 0) {
			// chay toi khi mat cam bien sau
			robotRunAngle(-900,22,900,0.7);
			for(i=0;i<1550;i++)
					{
							while(CB_Ha_Sau == 0)	
					
						{	
							if(!wantExit())	break;
							vTaskDelay (1);
						}
					}

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


void qua_trai_len_bac_200_11_xanh (void) {
		int time_41 = 0;
		int time_23 = 0;
		int di_cheo_41 = 0;
		int di_cheo_23 = 0;
		if (TinHieu_QuaTrai == 1 && CB_Ha_Sau == 1 && (bientrochansauValue <= 300)) { // th vua gap trc xong
				time_41 = 9000;
				time_23 = 9000;
				di_cheo_41 = 1450;
				di_cheo_23 = 450;
		}
		else if (TinHieu_QuaTrai == 1 && CB_Ha_Sau == 1 && (bientrochansauValue >= 300)) { // TH k gap di ngang
				time_41 = 3500;
				time_23 = 3500;
				di_cheo_41 = -1450;
				di_cheo_23 = -450;
		}
		else {
				time_41 = 4500;
				time_23 = 4500;
				di_cheo_41 = 1450;
				di_cheo_23 = 450;
		}
		TinHieu_QuaTrai = 0;
		/// ***************************
		if (da_lay_tay1 == 0 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
				MD_qua_trai_phai_len_bac_200(0, 900, 850, 10,900, -1800, 0);
			}
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
				MD_qua_trai_phai_len_bac_200(0, 900, di_cheo_41, time_41,900, -1800, 0);
			}
			//// gap 2 lan r
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {		
				MD_qua_trai_phai_len_bac_200(0, 900, di_cheo_41, time_41,900, -1800, 0);
			}
		//// gap 3 lan r
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 0) {		
				MD_qua_trai_phai_len_bac_200(0, 900, di_cheo_23, time_23,900, -1800, 0);
			}
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 1) {		
				MD_qua_trai_phai_len_bac_200(0, 900, di_cheo_23, time_23,900, -1800, 0);
			}
		robotStop(0);			
		su_dung_chan(265);
		for(i=0;i<250;i++)	
			{
			while(abs(bientrochansauValue - target_chan_sau) > 20)	{vTaskDelay(1); if(!wantExit())	break;}
			}	
		if (TinHieu_ChuanBi_GapThang == 0 && TinHieu_ChuanBi_GapTrai == 0 && TinHieu_ChuanBi_GapPhai == 0) {
				robotRunAngle(-900,22,900,0.8);
				for(i=0;i<1550;i++)
						{
								while(CB_Ha_Sau == 0)	
							{	
								if(!wantExit())	break;
								vTaskDelay (1);
							}
						}
				}
	
		else if (TinHieu_ChuanBi_GapTrai == 1 ) {
				chuan_bi_gap_trai_200_duoi_ko_thanh();
		}
		// CO LENH GAP PHAI
		else if (TinHieu_ChuanBi_GapPhai == 1 ) {
					chuan_bi_gap_phai_200_duoi_ko_thanh();
		}	
}


void qua_trai_xuong_bac_200_10_xanh (void) {
		int time_41 = 0;
		int time_23 = 0;
		int di_cheo_41 = 0;
		int di_cheo_23 = 0;
		if (TinHieu_QuaTrai == 1 && CB_Ha_Sau == 1 && (bientrochansauValue <= 300)) { // th vua gap trc xong
				time_41 = 9000;
				time_23 = 9000;
				di_cheo_41 = 1450;
				di_cheo_23 = 450;
		}
		else if (TinHieu_QuaTrai == 1 && CB_Ha_Sau == 1 && (bientrochansauValue >= 300)) { // TH k gap di ngang
				time_41 = 3500;
				time_23 = 3500;
				di_cheo_41 = -1450;
				di_cheo_23 = -450;
		}
		else {
				time_41 = 4500;
				time_23 = 4500;
				di_cheo_41 = 1450;
				di_cheo_23 = 450;
		}
		TinHieu_QuaTrai = 0;
		/// ***************************
		if (da_lay_tay1 == 0 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
				MD_qua_trai_phai_xuong_bac_200(0, 900, 850, 10,900, -1800, 0);
			}
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
				MD_qua_trai_phai_xuong_bac_200(0, 900, di_cheo_41, time_41,900, -1800, 0);
			}
			//// gap 2 lan r
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {		
				MD_qua_trai_phai_xuong_bac_200(0, 900, di_cheo_41, time_41,900, -1800, 0);
			}
		//// gap 3 lan r
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 0) {		
				MD_qua_trai_phai_xuong_bac_200(0, 900, di_cheo_23, time_23,900, -1800, 0);
			}
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 1) {		
				MD_qua_trai_phai_xuong_bac_200(0, 900, di_cheo_23, time_23,900, -1800, 0);
			}
		robotStop(0);
		su_dung_chan(265);
		for(i=0;i<250;i++)	
			{
			while(abs(bientrochansauValue - target_chan_sau) > 20)	{vTaskDelay(1); if(!wantExit())	break;}
			}
			
		if (TinHieu_ChuanBi_GapThang == 0 && TinHieu_ChuanBi_GapTrai == 0 && TinHieu_ChuanBi_GapPhai == 0) {
				robotRunAngle(-900,20,900,0.8);
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
					chuan_bi_gap_phai_200_tren_7_10();
			}
}

void dung_cho_khoi_r1_tren_MD (int Angle, int Robot_Angle) {
			robotStop(0);
			Nang_nhanh();
			target_chan_truoc = Min_chan_truoc + 250;
			target_chan_sau = Min_chan_sau + 250;
			
			for(i=0;i<50;i++)		
			{
				while(abs(bientrochansauValue - target_chan_sau) > 15)	{vTaskDelay(1); if(!wantExit())	break;}
			}
			
			led_bao_hieu_on;
			
			robotRunAngle(Angle,16,Robot_Angle,0.8);
			for(i=0;i<150;i++)	
			{	
				while(CB_Ha_Sau == 1  )	{vTaskDelay(1); if(!wantExit())	break;}
			}
			robotStop(0);
			
			SEND_UART (4,5);
			
			
			for(i=0;i<250;i++)	
			{
			while(cho_r1 == 1)	{vTaskDelay(1); if(!wantExit())	break;}
			}
			led_bao_hieu_off;
			cho_r1 = 1;
}

void dung_cho_khoi_r1_duoi_MD (int Angle, int Robot_Angle) {
			robotStop(0);
			led_bao_hieu_on;
			su_dung_chan(255);
			for(i=0;i<50;i++)		
			{
				while(abs(bientrochansauValue - target_chan_sau) > 10)	{vTaskDelay(1); if(!wantExit())	break;}
			}
			
			robotRunAngle(Angle,15,Robot_Angle,1);

			for(i=0;i<1000;i++)
			{	
				while(CB_Ha_Sau == 0 ) {
						vTaskDelay(1); if(!wantExit())	break;
				}
			}
			
			robotStop(0);
			SEND_UART (4,5);
		
			for(i=0;i<250;i++)	
			{
			while(cho_r1 == 1)	{vTaskDelay(1); if(!wantExit())	break;}
			}
			led_bao_hieu_off;
			cho_r1 = 1;
}

void dung_cho_khoi_r1_tren_xanh(void) {
			robotStop(0);	
			dung_cho_khoi_r1_tren_MD(-900, 900);
}

void dung_cho_khoi_r1_duoi_xanh(void) {
			robotStop(0);	
			dung_cho_khoi_r1_duoi_MD(-900, 900);
}


void dung_cho_khoi_r1_tren_do(void) {
			robotStop(0);
			dung_cho_khoi_r1_tren_MD(900, -900);
}

void dung_cho_khoi_r1_duoi_do(void) {
			robotStop(0);
			dung_cho_khoi_r1_duoi_MD(900, -900);
}

void bao_hieu_check_r1_ngang (void) {
			robotStop(0);
		 bat_bien_check_r1_ngang = 1;
			cho_r1_ben_Canh = 1;
			
}

void dung_cho_khoi_r1_ben_canh (void) {
			robotStop(0);	
			SEND_UART (4,5);
			led_bao_hieu_on;
			for(i=0;i<250;i++)	
			{
			while(cho_r1_ben_Canh == 1)	{vTaskDelay(1); if(!wantExit())	break;}
			}
			led_bao_hieu_off;
			cho_r1_ben_Canh = 1;
			bat_bien_check_r1_ngang = 0; // tat bien kiem tra r1 ben canh
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
    action_table[20][20][10] = vuot_rung_ve_homeTay_bac_200_10;
    action_table[20][20][11] = vuot_rung_ve_homeTay_bac_400;
    action_table[20][20][12] = vuot_rung_ve_homeTay_bac_200_12;


    /* =========================================
       move 0 , action 1, dung lai de lay o phia truoc
//       ========================================= */
    action_table[0][1][1]  = Lay_phia_truoc_bac_400_tren;
    action_table[0][1][2]  = Lay_phia_truoc_bac_200_tren;
    action_table[0][1][3]  = Lay_phia_truoc_bac_400_tren;
		action_table[0][1][4]  = lay_thang_200_duoi;
		action_table[0][1][5]  = Lay_phia_truoc_bac_200_tren;	
		action_table[0][1][6]  = Lay_phia_truoc_bac_200_tren;	
		action_table[0][1][7]  = Lay_phia_truoc_bac_200_tren;	
		action_table[0][1][8]  = Lay_phia_truoc_bac_200_tren;	
		action_table[0][1][9]  = lay_thang_200_duoi;
		action_table[0][1][10] = lay_thang_200_duoi;
		action_table[0][1][11] = lay_thang_200_duoi;
		action_table[0][1][12] = lay_thang_200_duoi;

//    /* =========================================
//       move 0 , action 2, dung lai de lay ben TRAI
//       ========================================= */
		action_table[0][2][1]  = Lay_ben_trai_bac_200_tren_xanh_1;
		action_table[0][2][2]  = Lay_ben_trai_bac_200_duoi_xanh_3;
		action_table[0][2][4]  = Lay_ben_trai_bac_200_duoi_xanh_5;
		action_table[0][2][5]  = Lay_ben_trai_bac_200_duoi_xanh_6;
		action_table[0][2][7]  = Lay_ben_trai_bac_200_duoi_xanh_ko_thanh;
		action_table[0][2][10] = Lay_ben_trai_bac_200_duoi_xanh_ko_thanh;
		
		action_table[0][2][8]  = Lay_ben_trai_bac_200_tren_xanh_9;
		action_table[0][2][11] = Lay_ben_trai_bac_200_tren_xanh_9;

//    /* =========================================
//       move 0 , action 3, dung lai de lay ben PHAI
//       ========================================= */

		action_table[0][3][2]  = Lay_ben_phai_bac_200_duoi_xanh_2; 
		action_table[0][3][3]  = Lay_ben_phai_bac_200_tren_xanh_3; 
		action_table[0][3][5]  = Lay_ben_phai_bac_200_tren_xanh_4;
		action_table[0][3][6]  = Lay_ben_phai_bac_200_tren_xanh_4;
		action_table[0][3][8]  = Lay_ben_phai_bac_200_tren_xanh_7;
		
		action_table[0][3][9]  = Lay_ben_phai_bac_200_duoi_xanh_8; 
		action_table[0][3][12] = Lay_ben_phai_bac_200_duoi_xanh_8; 
		
		action_table[0][3][11] = Lay_ben_phai_bac_200_tren_xanh_11;
    /* =========================================
       move 1 , action 4 chay thang
       ========================================= */
    action_table[1][4][1]  = Leo_bac_400_ko_thanh; 
    action_table[1][4][2]  = Leo_bac_200_bam_thanh_phai;
		action_table[1][4][3]  = Leo_bac_400_co_thanh;
		action_table[1][4][4]  = Xuong_bac_200_xanh_4; 
    action_table[1][4][5]  = Leo_bac_200_xanh_5;  
    action_table[1][4][6]  = Leo_bac_200_ko_thanh; 
    action_table[1][4][7]  = Leo_bac_200_xanh_7;  
    action_table[1][4][8]  = Leo_bac_200_ko_thanh;  
    action_table[1][4][9]  = Xuong_bac_200_xanh_9;  
    action_table[1][4][10] = xuong_bac_200_xanh_10;  
    action_table[1][4][11] = xuong_bac_200_end;  
		action_table[1][4][12] = xuong_bac_200_xanh_12; 
		
				/* =========================================
//   move 2 , action 4,chay ben trai
//   ========================================= */
		action_table[2][4][1] = qua_trai_len_bac_200_1_xanh;
		action_table[2][4][2] = qua_trai_xuong_bac_200_2_xanh;
		
		action_table[2][4][4] = qua_trai_xuong_bac_200_4_xanh; 
		action_table[2][4][5] = qua_trai_xuong_bac_200_5_xanh; 
		
		action_table[2][4][8] = qua_trai_len_bac_200_8_xanh;  
		action_table[2][4][7] = qua_trai_xuong_bac_200_7_xanh; 
		
		action_table[2][4][11] = qua_trai_len_bac_200_11_xanh;  
		action_table[2][4][10] = qua_trai_xuong_bac_200_10_xanh; 

		/* =========================================
//   move 3 , action 4,chay ben phai
//   ========================================= */
		action_table[3][4][2] = qua_phai_xuong_bac_200_2_xanh; 
		action_table[3][4][3] = qua_phai_len_bac_200_3_xanh;
		
    action_table[3][4][5] = qua_phai_len_bac_200_5_xanh;
		action_table[3][4][6] = qua_phai_len_bac_200_6_xanh; 
		
		action_table[3][4][8] = qua_phai_len_bac_200_8_xanh;  
		action_table[3][4][9] = qua_phai_xuong_bac_200_9_xanh; 
		
		action_table[3][4][11] = qua_phai_len_bac_200_11_xanh;  
		action_table[3][4][12] = qua_phai_xuong_bac_200_12_xanh;  
		
				/* =========================================
//   move 4 , action 5,check camera nhin khoi 1
//   ========================================= */
		action_table[4][5][4]  = dung_cho_khoi_r1_duoi_xanh; 
    action_table[4][5][5]  = dung_cho_khoi_r1_tren_xanh;  
    action_table[4][5][6]  = dung_cho_khoi_r1_tren_xanh; 
    action_table[4][5][7]  = dung_cho_khoi_r1_tren_xanh;  
    action_table[4][5][8]  = dung_cho_khoi_r1_tren_xanh;  
    action_table[4][5][9]  = dung_cho_khoi_r1_duoi_xanh;  
    action_table[4][5][10] = dung_cho_khoi_r1_duoi_xanh;  
    action_table[4][5][11] = dung_cho_khoi_r1_duoi_xanh;  
		action_table[4][5][12] = dung_cho_khoi_r1_duoi_xanh; 
		
		/* =========================================
//   move 5 , action 5,check camera nhin khoi 1 ben canh
//   ========================================= */
		action_table[5][5][4]  = bao_hieu_check_r1_ngang; 
    action_table[5][5][5]  = bao_hieu_check_r1_ngang;  
    action_table[5][5][6]  = bao_hieu_check_r1_ngang; 
    action_table[5][5][7]  = bao_hieu_check_r1_ngang;  
    action_table[5][5][8]  = bao_hieu_check_r1_ngang;  
    action_table[5][5][9]  = bao_hieu_check_r1_ngang;  
    action_table[5][5][10] = bao_hieu_check_r1_ngang;  
    action_table[5][5][11] = bao_hieu_check_r1_ngang;  
		action_table[5][5][12] = bao_hieu_check_r1_ngang; 
		
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
				kiem_tra_huong_quay_tay_gap_phia_truoc();
        
        switch (next2.id_block)
        {
            // --- KT_Ha_Tay_Trc_400 ---
            case 1: 
                KT_Ha_Tay_Trc_400 = 1;
                break;
            case 3: 
                KT_Ha_Tay_Trc_400 = 1;
                break;
                
            // ---  KT_Ha_Tay_Trc_200_Tren ---
            case 2: 
                KT_Ha_Tay = 1;
                break;
            case 5: 
                KT_Ha_Tay = 1;
                break;
            case 6: 
                KT_Ha_Tay = 1;
                break;
            case 7: 
                KT_Ha_Tay = 1;
                break;
            case 8: 
                KT_Ha_Tay = 1;
                break;
                
            // --- ham gap thang 200 duoi ---
            case 4: 
                KT_Ha_Tay_Trc_200_Duoi = 1;
                break;
            case 9: 
                KT_Ha_Tay_Trc_200_Duoi = 1;
                break;
            case 10: 
                KT_Ha_Tay_Trc_200_Duoi = 1;
                break;
            case 11: 
                KT_Ha_Tay_Trc_200_Duoi = 1;
                break;
            case 12: 
                KT_Ha_Tay_Trc_200_Duoi = 1;
                break;
                
            default:
                break;
        }
        return 1;
    }
    else if (next2.move == 0 && next2.action == 2)
    {
        TinHieu_ChuanBi_GapTrai = 1;
        kiem_tra_huong_quay_tay_gap_ben_trai();
        return 1;
    }
    else if (next2.move == 0 && next2.action == 3)
    {
        TinHieu_ChuanBi_GapPhai = 1;
        kiem_tra_huong_quay_tay_gap_ben_phai();
        return 1;
    }
    else if (next2.move == 2 && next2.action == 4) // TH di ngang trái
    {
        TinHieu_QuaTrai = 1;
        return 1;
    }
    else if (next2.move == 3 && next2.action == 4)  // TH di ngang phai
    {
        TinHieu_QuaPhai = 1;
        return 1;
    }

    return 0;
}

//////////////// ************** CHAY TU DONG ***************

void Run_All_Blocks_From_Queue_san_xanh(void)
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
                if (next_pkt.move == 2 && next_pkt.action == 10 && next_pkt.id_block == 1) 
                {
                    chay_ngang_qua_o1_xanh = 1;
                }
            }
            else if (pkt.move == 3 && pkt.action == 10 && pkt.id_block == 2)
            {
                if (next_pkt.move == 3 && next_pkt.action == 10 && next_pkt.id_block == 3)
                {
                    chay_ngang_qua_o3_xanh = 1;
                }
            }
        }

        if (pkt.move < MAX_MOVE && pkt.action < MAX_ACTION && pkt.id_block < MAX_ID)
        {
            action_table[pkt.move][pkt.action][pkt.id_block]();
        }

//        vTaskDelay(100); 
    }

    has_active_block = 0;
}

//////////////////// CHAY BAN TU DONG

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

static int dang_o_nhom = 0; 

void kiem_tra_qua_tay_nao(void)
{
    int so_qua_nhom_1_2;
    int so_qua_nhom_3_4;

    int nhom_se_chon = 0;
    int target_tam = -1;

    kiem_tra_so_qua_tren_tay();

    so_qua_nhom_1_2 = tay_1_co_qua + tay_2_co_qua;
    so_qua_nhom_3_4 = tay_3_co_qua + tay_4_co_qua;

    // =========================================================
    // UU TIEN CAO NHAT:
    // Neu tay 1 con qua -> luon uu tien cum 1-2
    // =========================================================
    if (tay_1_co_qua)
    {
        nhom_se_chon = 1;
        target_tam = vi_tri_dat_hop_1_2;
    }

    // =========================================================
    // UU TIEN 2:
    // Neu dang o cum nao va cum do con qua thi giu nguyen
    // =========================================================
    else if (dang_o_nhom == 1 && so_qua_nhom_1_2 > 0)
    {
        nhom_se_chon = 1;
        target_tam = vi_tri_dat_hop_1_2;
    }
    else if (dang_o_nhom == 2 && so_qua_nhom_3_4 > 0)
    {
        nhom_se_chon = 2;
        target_tam = vi_tri_dat_hop_3_4;
    }

    // =========================================================
    // UU TIEN 3:
    // Ben nao co du 2 qua thi chon
    // =========================================================
    else if (so_qua_nhom_1_2 == 2)
    {
        nhom_se_chon = 1;
        target_tam = vi_tri_dat_hop_1_2;
    }
    else if (so_qua_nhom_3_4 == 2)
    {
        nhom_se_chon = 2;
        target_tam = vi_tri_dat_hop_3_4;
    }

    // =========================================================
    // UU TIEN 4:
    // Neu tay 2 con qua -> van uu tien cum 1-2
    // =========================================================
    else if (tay_2_co_qua)
    {
        nhom_se_chon = 1;
        target_tam = vi_tri_dat_hop_1_2;
    }

    // =========================================================
    // UU TIEN 5:
    // Con lai moi xet cum 3-4
    // =========================================================
    else if (so_qua_nhom_3_4 > 0)
    {
        nhom_se_chon = 2;
        target_tam = vi_tri_dat_hop_3_4;
    }
    else
    {
        dang_o_nhom = 0;
        return;
    }

    // =========================================================
    // THUC THI XOAY
    // =========================================================
    dang_o_nhom = nhom_se_chon;

    speed_tay_xoay = 180;
    target_xoay_tay = target_tam;

    if (abs(bientroxoaytayValue - target_xoay_tay) > 10)
    {
        while (abs(bientroxoaytayValue - target_xoay_tay) > 10)
        {
            vTaskDelay(1);

            if (!wantExit())
                break;
        }
    }

    if (dang_o_nhom == 1)
    {
        tin_hieu_dat_hop_1_2 = 1;
    }
    else
    {
        tin_hieu_dat_hop_3_4 = 1;
    }
}



void kiem_tra_qua_tay_nao_xuong_rung(void)
{
    int so_qua_nhom_1_2;
    int so_qua_nhom_3_4;

    int nhom_se_chon = 0;
    int target_tam = -1;

    kiem_tra_so_qua_tren_tay();

    so_qua_nhom_1_2 = tay_1_co_qua + tay_2_co_qua;
    so_qua_nhom_3_4 = tay_3_co_qua + tay_4_co_qua;

    // =========================================================
    // UU TIEN CAO NHAT:
    // Neu tay 1 con qua -> luon uu tien cum 1-2
    // =========================================================
    if (tay_1_co_qua)
    {
        nhom_se_chon = 1;
        target_tam = vi_tri_dat_hop_1_2;
    }

    // =========================================================
    // UU TIEN 2:
    // Neu dang o cum nao va cum do con qua thi giu nguyen
    // =========================================================
    else if (dang_o_nhom == 1 && so_qua_nhom_1_2 > 0)
    {
        nhom_se_chon = 1;
        target_tam = vi_tri_dat_hop_1_2;
    }
    else if (dang_o_nhom == 2 && so_qua_nhom_3_4 > 0)
    {
        nhom_se_chon = 2;
        target_tam = vi_tri_dat_hop_3_4;
    }

    // =========================================================
    // UU TIEN 3:
    // Ben nao co du 2 qua thi chon
    // =========================================================
    else if (so_qua_nhom_1_2 == 2)
    {
        nhom_se_chon = 1;
        target_tam = vi_tri_dat_hop_1_2;
    }
    else if (so_qua_nhom_3_4 == 2)
    {
        nhom_se_chon = 2;
        target_tam = vi_tri_dat_hop_3_4;
    }

    // =========================================================
    // UU TIEN 4:
    // Neu tay 2 con qua -> van uu tien cum 1-2
    // =========================================================
    else if (tay_2_co_qua)
    {
        nhom_se_chon = 1;
        target_tam = vi_tri_dat_hop_1_2;
    }

    // =========================================================
    // UU TIEN 5:
    // Con lai moi xet cum 3-4
    // =========================================================
    else if (so_qua_nhom_3_4 > 0)
    {
        nhom_se_chon = 2;
        target_tam = vi_tri_dat_hop_3_4;
    }
    else
    {
        dang_o_nhom = 0;
        return;
    }

    // =========================================================
    // THUC THI XOAY
    // =========================================================
    dang_o_nhom = nhom_se_chon;

    speed_tay_xoay = 150;
    target_xoay_tay = target_tam;

    if (dang_o_nhom == 1)
    {
        tin_hieu_dat_hop_1_2 = 1;
    }
    else
    {
        tin_hieu_dat_hop_3_4 = 1;
    }
}

void test_chon_tay (void) {
		kiem_tra_so_qua_tren_tay();
		kiem_tra_qua_tay_nao_xuong_rung();
}

void DatKFSxanh(int vitri)
{
	kiem_tra_so_qua_tren_tay();
//	kiem_tra_qua_tay_nao_xuong_rung(); // ham kiem tra co qua tay nao de dat
	speed_tay_xoay = 150;
  target_xoay_tay = vi_tri_dat_hop_1_2;
	tin_hieu_dat_hop_1_2 = 1;
	
	Nang_nhanh();
	target_chan_truoc = 300;
	target_chan_sau = 300;
	
	for(i=0;i<150;i++)		
	{
		while(abs(bientrochansauValue - target_chan_sau) > 150)	{vTaskDelay(1); if(!wantExit())	break;}
	}
	
		if (vi_tri_chay_ngang_xanh == 10) {
			robotSetACC(45, 55); // gia toc
			chinh_lai_vi_tri_laser_phai_custom(182, 1000, 15, 75, 2);
			robotSetACC(120, 85); // gia toc
	}
	else if (vi_tri_chay_ngang_xanh == 11) { 
			robotSetACC(60, 65); // gia toc
			chinh_lai_vi_tri_laser_phai_custom(182, 1000, 12, 70, 3);
			robotSetACC(120, 85); // gia toc
	}
	else if ( vi_tri_chay_ngang_xanh == 12) { 
			robotSetACC(65, 75); // gia toc nhanh
			chinh_lai_vi_tri_laser_phai_custom(182, 1000, 10, 70, 3);
			robotSetACC(120, 85); // gia toc
	}
	
	robotStop(50);
//	
		robotRunAngle(-900,50,900,0.5);
		for(i=0;i<550;i++)	
	{	
			while(lazeTraiValue > 210)	
			{	
				vTaskDelay(5); 
				if(!wantExit())	break;
			}
	}	
	vTaskDelay(5000); 
	
		for(i=0;i<550;i++)	
	{	
			while(lazeTraiValue < 210)	
			{	

				vTaskDelay(1); 
				if(!wantExit())	break;
			}
	}		
		vTaskDelay(1700);
		robotStop(50);
	
		robotRunAngle(-900,28,900,0.5);
		for(i=0;i<550;i++)	
		{	
				while(lazeSauValue > 148)	
				{	
					vTaskDelay(1); 
					if(!wantExit())	break;
				}
		}
		robotStop(50);
		
		robotSetACC(55, 70);
		
		robotRunAngle(0,65,900,0.5);
		for(i=0;i<550;i++)	
		{	
			while(lazePhaiValue < 178)	
			{	
				vTaskDelay(1); 
				if(!wantExit())	break;
			}
		}
		
		robotRunAngle(20,72,900,0.6);
		for(i=0;i<550;i++)	
		{	
			while(lazePhaiValue < 280)	
			{	
				vTaskDelay(1); 
				if(!wantExit())	break;
			}
		}	
		
		
		nghieng_tay_k_dat_tang2(); // nghieng tay de tranh dung qua ngta
		
//	**************** che do cay diem  ******************
	if (mode_cay_diem == 1 ) {
			for(i=0;i<550;i++)	
			{	
					while(lazeTraiValue > 260)	
					{	
						Bam_laser_sau(40,0,900, vitri - 20, 3, -120, 10);
						vTaskDelay(1); 
						if(!wantExit())	break;
					}
			}
		for(i=0;i<550;i++)	
			{	
					while(lazeTraiValue > 225)	
					{	
						Bam_laser_sau(25,0,900, vitri - 20, 3, -120, 10);
						vTaskDelay(5); 
						if(!wantExit())	break;
					}
			}
			
			robotSetACC(120, 85);
				
			
			for(i=0;i<550;i++)	
			{	
					while(lazeTraiValue > 214)	
					{	
						Bam_laser_sau(10,0,900, vitri - 20, 1, -100, 10);
						vTaskDelay(5); 
						if(!wantExit())	break;
					}
			}	

			robotStop(0);

			robotRotate(890,0.2, 0);
			while(robotFixAngle()){
						vTaskDelay (1); 
						if(!wantExit())	break;
					}
			
			robotStop(0);
		// do chan len dat qua
			su_dung_chan(730);
			for(i=0;i<150;i++)		
			{
				while(abs(bientrochansauValue - target_chan_sau) > 30)	{vTaskDelay(1); if(!wantExit())	break;}
			}
	}
	
	
//	// ************** che do thang nhanh ***********
	if (mode_cay_diem == 2 ) {
		
		robotRunAngle(400,45,900,0.5);
		for(i=0;i<550;i++)	
		{	
			while(lazeTraiValue > 265)	
			{	
				vTaskDelay(1); 
				if(!wantExit())	break;
			}
		}	
		
			for(i=0;i<550;i++)	
			{	
					while(lazeTraiValue > 205)	
					{	
						Bam_laser_sau(40,0,900, vitri , 2, -250, 10);
						vTaskDelay(1); 
						if(!wantExit())	break;
					}
			}	
			
			
		for(i=0;i<550;i++)	
			{	
					while(lazeTraiValue > 175)	
					{	
						Bam_laser_sau(25,0,900, vitri , 2, -200, 10);
						vTaskDelay(1); 
						if(!wantExit())	break;
					}
			}	
			
			robotSetACC(120, 85);
			
			for(i=0;i<550;i++)	
			{	
					while(lazeTraiValue > 165)	
					{	
						Bam_laser_sau(10,0,900, vitri - 1 , 2, -150, 10);
						su_dung_chan_thuong(490);
						vTaskDelay(1); 
						if(!wantExit())	break;
					}
			}	
		}
			robotStop(0);
}


bool da_dat_tay_1 = false;
bool da_dat_tay_2 = false;
bool da_dat_tay_3 = false;
bool da_dat_tay_4 = false;


void dat_qua_tay_1_2_xanh(void) {
    if (((CB_kep_1_2 == 0  || CB_kep_1_1 == 0 ) || check_hop_1 == 0) && !da_dat_tay_1) {
        speed_tay_gat1 = 100;
        target_tay_gat1 = vitri_tay1home + 90;
    
        for(i=0; i<50; i++) { 
            while(abs(bientrodaytay1Value - target_tay_gat1) > 10 || abs(bientrodaytay2Value - target_tay_gat2) > 10) {
                vTaskDelay(1); if(!wantExit()) break;
            }
        }
				
			led_bao_hieu_on;
      for(i=0;i<1000;i++)	
				{
			while(Quang_tro2 > 120)	{	
					vTaskDelay (1);
			if(!wantExit())	break;
						}
				}
			led_bao_hieu_off;
				
			Kep_phai_1_ra; //
			vTaskDelay(1500);
			da_dat_tay_1 = true; 
				
			vTaskDelay(4500);
			led_bao_hieu_on;
			for(i=0;i<1000;i++)	
					{
					while(Quang_tro2 > 120)	{	
					vTaskDelay (1);
					if(!wantExit())	break;
						}
					}
			led_bao_hieu_off;
					
			// Ðua tay ve Home
			speed_tay_gat1 = 250;
			target_tay_gat1 = vitri_tay1home;
			
			for(i=0; i<50; i++) { 
					while(abs(bientrodaytay1Value - target_tay_gat1) > 40 ) {
							vTaskDelay(1); if(!wantExit()) break;
							}
					}
			Kep_phai_1_vao;
			vTaskDelay(8000);
			Tay1_xuong;
					
			speed_tay_gat2 = 200;
			target_tay_gat2 = vitri_tay2home;
			
			for(i=0; i<50; i++) { 
					while(abs(bientrodaytay2Value - target_tay_gat2) > 30 ) {
							vTaskDelay(1); if(!wantExit()) break;
							}
					}
    }
		
		///////////////////////
    else if (((CB_kep_2_1 == 0 || CB_kep_2_2 == 0 ) || check_hop_2 == 0) && !da_dat_tay_2) {
        speed_tay_gat2 = 100;
        target_tay_gat2 = vitri_tay2home + 90;
            
        for(i=0; i<50; i++) { 
            while(abs(bientrodaytay1Value - target_tay_gat1) > 10 || abs(bientrodaytay2Value - target_tay_gat2) > 10) {
                vTaskDelay(1); if(!wantExit()) break;
            }
        }
				
			led_bao_hieu_on;
      for(i=0;i<1000;i++)	
				{
			while(Quang_tro2 > 120)	{	
					vTaskDelay (1);
			if(!wantExit())	break;
						}
				}
			led_bao_hieu_off;
				
			Kep_phai_2_ra;
			vTaskDelay(1500);
			da_dat_tay_2 = true; 
				
			vTaskDelay(4500);
			led_bao_hieu_on;
			for(i=0;i<1000;i++)	
					{
					while(Quang_tro2 > 120)	{	
					vTaskDelay (1);
					if(!wantExit())	break;
						}
					}
			led_bao_hieu_off;
					
			// Ðua tay ve Home
			speed_tay_gat2 = 250;
			target_tay_gat2 = vitri_tay2home;
			
			for(i=0; i<50; i++) { 
					while(abs(bientrodaytay2Value - target_tay_gat2) > 40 ) {
							vTaskDelay(1); if(!wantExit()) break;
							}
					}
			Kep_phai_2_vao;
			vTaskDelay(8000);
			Tay2_xuong;
					
			speed_tay_gat1 = 200;
			target_tay_gat1 = vitri_tay2home;
			
			for(i=0; i<50; i++) { 
					while(abs(bientrodaytay1Value - target_tay_gat1) > 30 ) {
							vTaskDelay(1); if(!wantExit()) break;
							}
					}
				
    }
    
}
void dat_qua_tay_4_3_xanh(void) {
    
    if ( ( (CB_kep_4_2 == 0 || CB_kep_4_1 == 0 ) || check_hop_4 == 1) && !da_dat_tay_4) {
        speed_tay_gat2 = 100;
        target_tay_gat2 = vitri_tay2home - 90;
            
        for(i=0; i<50; i++) { 
            while(abs(bientrodaytay1Value - target_tay_gat1) > 10 || abs(bientrodaytay2Value - target_tay_gat2) > 10) {
                vTaskDelay(1); if(!wantExit()) break;
							}
						}
			led_bao_hieu_on;
			for(i=0;i<1000;i++)	
				{
			while(Quang_tro2 > 120)	{	
					vTaskDelay (1);
			if(!wantExit())	break;
						}
				}
			led_bao_hieu_off;
			
        Kep_phai_4_ra; //
				vTaskDelay(1000);
        da_dat_tay_4 = true; //
				
				vTaskDelay(4500);
				led_bao_hieu_on;
				for(i=0;i<1000;i++)	
						{
						while(Quang_tro2 > 120)	{	
						vTaskDelay (1);
						if(!wantExit())	break;
							}
						}
				led_bao_hieu_off;
						
				// Ðua tay ve Home
				speed_tay_gat2 = 250;
				target_tay_gat2 = vitri_tay2home;
				
				for(i=0; i<50; i++) { 
						while(abs(bientrodaytay2Value - target_tay_gat2) > 40 ) {
								vTaskDelay(1); if(!wantExit()) break;
								}
						}
				Kep_phai_4_vao;
				vTaskDelay(8000);
				Tay2_xuong;
						
				speed_tay_gat1 = 200;
				target_tay_gat1 = vitri_tay2home;
				
				for(i=0; i<50; i++) { 
						while(abs(bientrodaytay1Value - target_tay_gat1) > 30 ) {
								vTaskDelay(1); if(!wantExit()) break;
								}
						}
    }
    
		///////////////////
    else if ( ( (CB_kep_3_1 == 0 || CB_kep_3_2 == 0 ) || check_hop_3 == 1) && !da_dat_tay_3) {
        speed_tay_gat1 = 100;
        target_tay_gat1 = vitri_tay1home - 90;

        for(i=0; i<50; i++) { 
            while(abs(bientrodaytay1Value - target_tay_gat1) > 10 || abs(bientrodaytay2Value - target_tay_gat2) > 10) {
                vTaskDelay(1); if(!wantExit()) break;
            }
        }
        led_bao_hieu_on;
				for(i=0;i<1000;i++)	
				{
					while(Quang_tro2 > 120)	{	
					vTaskDelay (1);
				if(!wantExit())	break;
						}
				}
				led_bao_hieu_off;
				
        Kep_phai_3_ra;
				vTaskDelay(1000);
        da_dat_tay_3 = true; // Ðánh dau dã dat xong tay 3
				
			vTaskDelay(4500);
			led_bao_hieu_on;
			for(i=0;i<1000;i++)	
					{
					while(Quang_tro2 > 120)	{	
					vTaskDelay (1);
					if(!wantExit())	break;
						}
					}
			led_bao_hieu_off;
					
			// Ðua tay ve Home
			speed_tay_gat1 = 250;
			target_tay_gat1 = vitri_tay1home;
			
			for(i=0; i<50; i++) { 
					while(abs(bientrodaytay1Value - target_tay_gat1) > 40 ) {
							vTaskDelay(1); if(!wantExit()) break;
							}
					}
			Kep_phai_3_vao;
			vTaskDelay(8000);
			Tay1_xuong;
					
			speed_tay_gat2 = 200;
			target_tay_gat2 = vitri_tay2home;
			
			for(i=0; i<50; i++) { 
					while(abs(bientrodaytay2Value - target_tay_gat2) > 30 ) {
							vTaskDelay(1); if(!wantExit()) break;
							}
					}
    }


}


void dat_hop_vao_o (void) {
		if (tin_hieu_dat_hop_3_4 == 1 ) {
				dat_qua_tay_4_3_xanh();			
		}
		else if (tin_hieu_dat_hop_1_2 == 1 ) {
				dat_qua_tay_1_2_xanh();
		}
}


void dat_hop_vao_o_tang2 (void) {
		if (tin_hieu_dat_hop_3_4 == 1 ) {
				if ( (CB_kep_4_2 == 0 || CB_kep_4_1 == 0 ) || check_hop_4 == 1) {
					speed_tay_gat1 = 180;
					target_tay_gat1 = vitri_tay1home + 70; // nghieng tay 1 max
					
					speed_tay_gat2 = 200;
					target_tay_gat2 = 421;
					for(i=0; i<550; i++) 
					{ 
					while(abs(bientrodaytay2Value - target_tay_gat2) > 10) { vTaskDelay(1); if(!wantExit()) break; }
          }
					dat_hop4_2(490, 325, 5, 4);
					vTaskDelay(2000); 
				}
				else if ( (CB_kep_3_1 == 0 || CB_kep_3_2 == 0 ) || check_hop_3 == 1) {
					speed_tay_gat2 = 180;
					target_tay_gat2 = vitri_tay2home + 70; // nghieng tay 2 max
					
					speed_tay_gat1 = 200;
					target_tay_gat1 = 423;
					for(i=0; i<550; i++) 
					{ 
					while(abs(bientrodaytay1Value - target_tay_gat1) > 6) { vTaskDelay(1); if(!wantExit()) break; }
          }
					dat_hop1_3(490, 325, 5, 3);
					vTaskDelay(2000); 

					}	
				
		}
		else if (tin_hieu_dat_hop_1_2 == 1 ) {
				if ((CB_kep_1_2 == 0  || CB_kep_1_1 == 0 ) || check_hop_1 == 0) {
						speed_tay_gat2 = 180;
						target_tay_gat2 = vitri_tay2home - 70; // nghieng tay 2 ve min
					
						speed_tay_gat1 = 200;
						target_tay_gat1 = 468;
						for(i=0; i<550; i++) 
						{ 
						while(abs(bientrodaytay1Value - target_tay_gat1) > 6) { vTaskDelay(1); if(!wantExit()) break; }
						}
						dat_hop1_3(490, 555, 5, 1);
						vTaskDelay(2000); 
						
				}
				else if ((CB_kep_2_1 == 0 || CB_kep_2_2 == 0 ) || check_hop_2 == 0) {
					
						speed_tay_gat1 = 180;
						target_tay_gat1 = vitri_tay1home - 70; // nghieng tay 1 ve min
					
						speed_tay_gat2 = 200;
						target_tay_gat2 = 467;
						for(i=0; i<550; i++) 
						{ 
						while(abs(bientrodaytay2Value - target_tay_gat2) > 6) { vTaskDelay(1); if(!wantExit()) break; }
						}
						dat_hop4_2(490, 560, 5, 2);
						vTaskDelay(2000); 
						
				}
		}
	
				tin_hieu_dat_hop_3_4 = 0;
				tin_hieu_dat_hop_1_2 = 0;
				
}

void nghieng_tay_k_dat_tang2(void) {
		speed_tay_gat2 = 80;
		target_tay_gat2 = vitri_tay2home - 70;
		speed_tay_gat1 = 80;
		target_tay_gat1 = 385;
	}

void chuan_bi_dat_hop_tang3 (void) {
		if (tin_hieu_dat_hop_3_4 == 1 && tay_4_co_qua == 1 ) {
				speed_tay_gat1 = 120;
        target_tay_gat1 = vitri_tay1home + 145;
				Tay2_len;
				for(i=0;i<50;i++)	{ 
									while(CB_xilanh_tay_2 == 1 )	{vTaskDelay(1); if(!wantExit())	break;}
							}
						}
		
		else if (tin_hieu_dat_hop_1_2 == 1 && tay_1_co_qua == 1 ) {
				speed_tay_gat2 = 120;
        target_tay_gat2 = vitri_tay2home - 145;
				Tay1_len;
				for(i=0;i<50;i++)	{ 
									while(CB_xilanh_tay_1 == 1 )	{vTaskDelay(1); if(!wantExit())	break;}
							}
						}

		
		else if (tin_hieu_dat_hop_1_2 == 1 && tay_2_co_qua == 1 ) {
				speed_tay_gat1 = 120;
        target_tay_gat1 = vitri_tay1home - 145;
				Tay2_len;
				for(i=0;i<50;i++)	{ 
									while(CB_xilanh_tay_2 == 1 )	{vTaskDelay(1); if(!wantExit())	break;}
							}
						}

		
		else if (tin_hieu_dat_hop_3_4 == 1 && tay_3_co_qua == 1) {
				speed_tay_gat2 = 120;
        target_tay_gat2 = vitri_tay2home + 145;
				Tay1_len;
				for(i=0;i<50;i++)	{ 
									while(CB_xilanh_tay_1 == 1 )	{vTaskDelay(1); if(!wantExit())	break;}
							}
						}
		}

void kiem_tra_so_qua_tren_tay(void) {
    int dem = 0;

    // Ki?m tra tay 1
    if ((CB_kep_1_2 == 0  || CB_kep_1_1 == 0 ) || check_hop_1 == 0) {
//	if (check_hop_1 == 0) {
        tay_1_co_qua = 1;
        dem++;
    } else {
        tay_1_co_qua = 0;
    }

    // Ki?m tra tay 2
    if ((CB_kep_2_1 == 0 || CB_kep_2_2 == 0 ) || check_hop_2 == 0) {
//		 if (check_hop_2 == 0) {
        tay_2_co_qua = 1;
        dem++;
    } else {
        tay_2_co_qua = 0;
    }

    // Ki?m tra tay 3
    if ( (CB_kep_3_1 == 0 || CB_kep_3_2 == 0 ) || check_hop_3 == 1) {
//		if (check_hop_3 == 1) {
        tay_3_co_qua = 1;
        dem++;
    } else {
        tay_3_co_qua = 0;
    }

    // Ki?m tra tay 4
    if ( (CB_kep_4_2 == 0 || CB_kep_4_1 == 0 ) || check_hop_4 == 1) {
//		if (check_hop_4 == 1) {
        tay_4_co_qua = 1;
        dem++;
    } else {
        tay_4_co_qua = 0;
    }

    so_qua_tren_tay = dem;
}


void be_len_dat_xanh (void) {
	kiem_tra_so_qua_tren_tay();
	kiem_tra_qua_tay_nao();
	
	led_bao_hieu_on;
	// cho nhay den thi dat
	for(i=0; i<1000; i++) {
        while(Quang_tro2 > 120) {    
            vTaskDelay (1);
            if(!wantExit()) break;
        }
    }
	led_bao_hieu_off;

	vTaskDelay (2000);
	nhay_den_lan_1 = 1;
	
	// TRANG THÁI 1: rut chan va nghieng tay xuong
	if (nhay_den_lan_1 == 1 ) {
			su_dung_chan_thuong(350);
			for(i=0;i<150;i++)		
			{
				while(abs(bientrochansauValue - target_chan_sau) > 50)	{vTaskDelay(1); if(!wantExit())	break;}
			}
			chuan_bi_dat_hop_tang3();
			vTaskDelay (1000);
			
			led_bao_hieu_on;
			for(i=0;i<1000;i++)	
			{
			while(Quang_tro2 > 120)	{	
					vTaskDelay (1);
			if(!wantExit())	break;
					}
			}
			led_bao_hieu_off;
			nhay_den_lan_1 = 2;
	}
	
	// TRANG THÁI 2: nhay lan 2 thi dat hop lan 1
	if (nhay_den_lan_1 == 2) {
			dat_hop_vao_o();
		
			tin_hieu_dat_hop_3_4 = 0;
			tin_hieu_dat_hop_1_2 = 0;
		
			vTaskDelay (1000);
			kiem_tra_so_qua_tren_tay();
			// cho nhay den thi xoay
			led_bao_hieu_on;
			for(i=0;i<1000;i++)	
				{
				while(Quang_tro2 > 120)	{	
				vTaskDelay (1);
				if(!wantExit())	break;
					}
				}
			led_bao_hieu_off;
				
			kiem_tra_qua_tay_nao();
				
			// KIEM TRA ÐIEU KIEN DE DAT TANG 2
        if (chuyen_doi_T3 == 0) {
            nhay_den_lan_1 = 4;
        }
		else {
			chuan_bi_dat_hop_tang3(); // phut xi lang len
			
			led_bao_hieu_on;
			for(i=0;i<100;i++)	
				{
					while(Quang_tro2 > 120)	{	
					vTaskDelay (1);
			if(!wantExit())	break;
						}
				}
			led_bao_hieu_off;
				
			if (chuyen_doi_T3 == 0) {
            nhay_den_lan_1 = 4;
        }
		else {
			nhay_den_lan_1 = 3;
						}
					}
			}
	
	// TRANG THÁI 3: nhay lan 3 thi dat hop lan 2
	if (nhay_den_lan_1 == 3) {
		
			dat_hop_vao_o();
		
			tin_hieu_dat_hop_3_4 = 0;
			tin_hieu_dat_hop_1_2 = 0;
		
			vTaskDelay (1000);
			kiem_tra_so_qua_tren_tay();
			// cho nhay den thi xoay
			
			led_bao_hieu_on;
			for(i=0;i<1000;i++)	
				{
				while(Quang_tro2 > 120)	{	
				vTaskDelay (1);
				if(!wantExit())	break;
					}
				}
			led_bao_hieu_off;
				
			kiem_tra_qua_tay_nao();

			vTaskDelay (1000);
			nhay_den_lan_1 = 4;
			robotStop(0);
		}
	
	// TRANG THÁI 4: nhay lan 4 ha xuong
		if (nhay_den_lan_1 == 4) {
				ha_chan_dat_tang2_do();
				
				led_bao_hieu_on;
				for(i=0; i<1000; i++) {
					while(Quang_tro2 > 120) {    
						vTaskDelay (1);
						if(!wantExit()) break;
					}
				}
				led_bao_hieu_off;
				
				if (chuyen_doi_T3 == 1) {
					nhay_den_lan_1 = 7;
				} else {
					nhay_den_lan_1 = 5;
				}
		}

	// TRANG THÁI 7: dang thap muon len cao dat lai
		if (nhay_den_lan_1 == 7) {
				tin_hieu_dat_hop_3_4 = 0;
				tin_hieu_dat_hop_1_2 = 0;
			
				su_dung_chan_thuong(350);
				kiem_tra_so_qua_tren_tay();
				kiem_tra_qua_tay_nao(); 
				chuan_bi_dat_hop_tang3();
				
				led_bao_hieu_on;
				for(i=0; i<1000; i++) {
					while(Quang_tro2 > 120) {    
						vTaskDelay (1);
						if(!wantExit()) break;
					}
				}
				led_bao_hieu_off;
			
				dat_hop_vao_o();
				robotStop(0);
				ha_chan_dat_tang2_do();
				nhay_den_lan_1 = 5; 
		}
		
		if (nhay_den_lan_1 == 5) {
			
			led_bao_hieu_on;
			for(i=0;i<1000;i++)	
			{
				while(Quang_tro2 > 160)	{	
				vTaskDelay (1);
			if(!wantExit())	break;
					}
			}
			led_bao_hieu_off;
			
			for(i=0;i<550;i++)
				{
					while( CB_Nang_phai ==  0 || CB_Nang_trai ==  0 )	
					{	
						vTaskDelay (1);
						if(!wantExit())	break;
						
					}
				}
					vTaskDelay (2500);
							
				for(i=0;i<550;i++)	
				{	
						while(lazePhaiValue < 180)	
						{	
							vTaskDelay(1); 
							if(!wantExit())	break;
						}
				}
				su_dung_chan(490);
				for(i=0;i<150;i++)		
				{
					while(abs(bientrochansauValue - target_chan_sau) > 15)	{vTaskDelay(1); if(!wantExit())	break;}
				}
				kiem_tra_so_qua_tren_tay();
				kiem_tra_qua_tay_nao();
		}
}

void be_len_dat_xanh_4_qua (void) {
    kiem_tra_so_qua_tren_tay();
    kiem_tra_qua_tay_nao();
    
		led_bao_hieu_on;
    // cho nhay den thi dat
    for(i=0; i<1000; i++) {
        while(Quang_tro2 > 120) {    
            vTaskDelay (1);
            if(!wantExit()) break;
        }
    }
		led_bao_hieu_off;
		
    vTaskDelay (2000);
    nhay_den_lan_1 = 1;
    
    // TRANG THÁI 1: rut chan va nghieng tay xuong
    if (nhay_den_lan_1 == 1 ) {
        su_dung_chan_thuong(350);
        for(i=0; i<150; i++) {
            while(abs(bientrochansauValue - target_chan_sau) > 50) {
                vTaskDelay(1); 
                if(!wantExit()) break;
            }
        }
        chuan_bi_dat_hop_tang3(); // nghieng tay
        vTaskDelay (1000);
    
				led_bao_hieu_on;
        for(i=0; i<1000; i++) {
            while(Quang_tro2 > 120) {    
                vTaskDelay (1);
                if(!wantExit()) break;
            }
        }
				led_bao_hieu_off;
				
        nhay_den_lan_1 = 2;
    }
    
    // TRANG THÁI 2: nhay lan 2 thi dat hop lan 1
    if (nhay_den_lan_1 == 2) {
        dat_hop_vao_o();
    
        tin_hieu_dat_hop_3_4 = 0;
        tin_hieu_dat_hop_1_2 = 0;
    
        vTaskDelay (1000);
        kiem_tra_so_qua_tren_tay();
        
        // cho nhay den thi xoay
				led_bao_hieu_on;
        for(i=0; i<1000; i++) {
            while(Quang_tro2 > 120) {    
                vTaskDelay (1);
                if(!wantExit()) break;
            }
        }
				led_bao_hieu_off;
				
        kiem_tra_qua_tay_nao();

        // KIEM TRA ÐIEU KIEN SAU KHI ÐAT LAN 1
        if (chuyen_doi_T3 == 0) {
            nhay_den_lan_1 = 5; // Bo qua dAt lAn 2 và 3
        } 
				else if ( chuyen_doi_T3 == 1) {
            chuan_bi_dat_hop_tang3();
						
						led_bao_hieu_on;
            for(i=0; i<100; i++) {
                while(Quang_tro2 > 120) {    
                    vTaskDelay (1);
                    if(!wantExit()) break;
                }
            }
						led_bao_hieu_off;
						
						if (chuyen_doi_T3 == 0) {
								nhay_den_lan_1 = 5;
        }
						else if (chuyen_doi_T3 == 1) {
								nhay_den_lan_1 = 3; }
        }
    }
    
    // TRANG THÁI 3: nhay lan 3 thi dat hop lan 2
    if (nhay_den_lan_1 == 3) {
        dat_hop_vao_o();
    
        tin_hieu_dat_hop_3_4 = 0;
        tin_hieu_dat_hop_1_2 = 0;
    
        vTaskDelay (1000);
        kiem_tra_so_qua_tren_tay();
        
        // cho nhay den thi xoay
				led_bao_hieu_on;
        for(i=0; i<1000; i++) {
            while(Quang_tro2 > 120) {    
                vTaskDelay (1);
                if(!wantExit()) break;
            }
        }
				led_bao_hieu_off;
				
        kiem_tra_qua_tay_nao();

        // KIEM TRA ÐIEU KIEN SAU KHI ÐAT LAN 2 XONG
        if (chuyen_doi_T3 == 0) {
            nhay_den_lan_1 = 5; 
        } else {
            vTaskDelay (1000);
            chuan_bi_dat_hop_tang3();
								// cho nhay den thi xoay
						led_bao_hieu_on;
						for(i=0; i<1000; i++) {
								while(Quang_tro2 > 120) {    
										vTaskDelay (1);
										if(!wantExit()) break;
									}
								}
						led_bao_hieu_off;
						
					if (chuyen_doi_T3 == 0) {
            nhay_den_lan_1 = 5;
						}
					else {
            nhay_den_lan_1 = 4;}
            robotStop(0);
        }
    }
        
    // TRANG THÁI 4: nhay lan 4 thi dat hop lan 3
    if (nhay_den_lan_1 == 4) {
			
				led_bao_hieu_on;
        for(i=0; i<1000; i++) {
            while(Quang_tro2 > 120) {    
                vTaskDelay (1);
                if(!wantExit()) break;
            }
        }
				led_bao_hieu_off;
    
        dat_hop_vao_o();
    
        tin_hieu_dat_hop_3_4 = 0;
        tin_hieu_dat_hop_1_2 = 0;
    
        vTaskDelay (1000);
        kiem_tra_so_qua_tren_tay();
        
        // cho nhay den thi xoay
				led_bao_hieu_on;
        for(i=0; i<1000; i++) {
            while(Quang_tro2 > 120) {    
                vTaskDelay (1);
                if(!wantExit()) break;
            }
        }
				led_bao_hieu_off;
				
        kiem_tra_qua_tay_nao();
        vTaskDelay (1000);
        nhay_den_lan_1 = 5;
        robotStop(0);
    }
    
    // TRANG THÁI 5: nhay lan 5 ha xuong 
    if (nhay_den_lan_1 == 5) {
        ha_chan_dat_tang2_do();
				// cho nhay den 
				
				led_bao_hieu_on;
        for(i=0; i<1000; i++) {
            while(Quang_tro2 > 120) {    
                vTaskDelay (1);
                if(!wantExit()) break;
            }
        }
				led_bao_hieu_off;
        
        if (chuyen_doi_T3 == 1) {
            nhay_den_lan_1 = 7; //qua TT7
        } else {
            nhay_den_lan_1 = 6; // quay ve bth
        }
    }

    // TRANG THÁI 7: dang thap muon len cao dat lai
    if (nhay_den_lan_1 == 7) {
        tin_hieu_dat_hop_3_4 = 0;
        tin_hieu_dat_hop_1_2 = 0;
    
        su_dung_chan_thuong(350);
        kiem_tra_so_qua_tren_tay();
        kiem_tra_qua_tay_nao(); 
        chuan_bi_dat_hop_tang3();

        for(i=0; i<1000; i++) {
            while(Quang_tro2 > 120) {    
                vTaskDelay (1);
                if(!wantExit()) break;
            }
        }
    
        dat_hop_vao_o();
        ha_chan_dat_tang2_do();
        // quay ve logic cu
        nhay_den_lan_1 = 6; 
    }
    
    // TRANG THÁI 6: Xu ly con lai
    if (nhay_den_lan_1 == 6) {
			
				led_bao_hieu_on;
        for(i=0; i<1000; i++) {
            while(Quang_tro2 > 140) {    
                vTaskDelay (1);
                if(!wantExit()) break;
            }
        }
				led_bao_hieu_off;
        
        for(i=0; i<550; i++) {
            while( CB_Nang_phai == 0 || CB_Nang_trai == 0 ) {   
                vTaskDelay (1);
                if(!wantExit()) break;
            }
        }
        vTaskDelay (2500);
                        
        for(i=0; i<550; i++) {   
            while(lazePhaiValue < 220) {   
                vTaskDelay(1); 
                if(!wantExit()) break;
            }
        }
        su_dung_chan(490);
        for(i=0; i<150; i++) {
            while(abs(bientrochansauValue - target_chan_sau) > 15) {
                vTaskDelay(1); 
                if(!wantExit()) break;
            }
        }
        kiem_tra_so_qua_tren_tay();
        kiem_tra_qua_tay_nao();
    }
}

void be_len_dat_xanh_1_qua_tren_3 (void) {
	kiem_tra_so_qua_tren_tay();
	kiem_tra_qua_tay_nao();
		// cho nhay den thi dat
	
	led_bao_hieu_on;
	for(i=0;i<1000;i++)	
		{
		while(Quang_tro2 > 120)	{	
		vTaskDelay (1);
		if(!wantExit())	break;
			}
		}
	vTaskDelay (1000);
	led_bao_hieu_off;
		
	nhay_den_lan_1 = 1;
	
	// rut chan 
	if (nhay_den_lan_1 == 1 ) {
			su_dung_chan_thuong(350);
			for(i=0;i<150;i++)		
			{
				while(abs(bientrochansauValue - target_chan_sau) > 50)	{vTaskDelay(1); if(!wantExit())	break;}
			}
			chuan_bi_dat_hop_tang3();
			vTaskDelay (1000);
		
			led_bao_hieu_on;
			for(i=0;i<1000;i++)	
			{
				while(Quang_tro2 > 120)	{	
				vTaskDelay (1);
			if(!wantExit())	break;
					}
			}
			led_bao_hieu_off;
			
			nhay_den_lan_1 = 2;
			}
	// nhay lan 2 thi dat hop lan 1
	if (nhay_den_lan_1 == 2) {
			dat_hop_vao_o();
		
			tin_hieu_dat_hop_3_4 = 0;
			tin_hieu_dat_hop_1_2 = 0;
		
			vTaskDelay (1000);
			kiem_tra_so_qua_tren_tay();
				// cho nhay den thi xoay
			led_bao_hieu_on;
			for(i=0;i<1000;i++)	
				{
				while(Quang_tro2 > 120)	{	
				vTaskDelay (1);
				if(!wantExit())	break;
					}
				}
			led_bao_hieu_off;
				
			kiem_tra_qua_tay_nao();
		
			nhay_den_lan_1 = 3;
		}
		// nhay lan 4 ha xuong 
		if (nhay_den_lan_1 == 3) {
				ha_chan_dat_tang2_do();
				nhay_den_lan_1 = 4;
		}
		if (nhay_den_lan_1 == 4) {
			
			led_bao_hieu_on;
			for(i=0;i<1000;i++)	
			{
				while(Quang_tro2 > 120)	{	
				vTaskDelay (1);
			if(!wantExit())	break;
					}
			}
			vTaskDelay (6000);
			led_bao_hieu_off;
			
			for(i=0;i<1550;i++)
				{
					while( CB_Nang_phai ==  0 || CB_Nang_trai ==  0 )	
						{	
						vTaskDelay (1);
						if(!wantExit())	break;
						
						}
				}
				
				vTaskDelay (2500);
				for(i=0;i<550;i++)	
				{	
						while(lazePhaiValue < 220)	
						{	
							vTaskDelay(5); 
							if(!wantExit())	break;
						}
				}
				su_dung_chan(490);
				for(i=0;i<150;i++)		
				{
				while(abs(bientrochansauValue - target_chan_sau) > 10)	{vTaskDelay(1); if(!wantExit())	break;}
				}
				kiem_tra_so_qua_tren_tay();
				kiem_tra_qua_tay_nao();
				chuan_bi_dat_hop_tang3();
				nhay_den_lan_1 = 6;
		}
}

void quyet_dinh_dat_hop_tang3(void) {
		kiem_tra_so_qua_tren_tay();
	
		Kep_phai_1_vao;
		Kep_phai_2_vao;
		Kep_phai_3_vao;
		Kep_phai_4_vao;	
		vTaskDelay(3000);
		Tay2_xuong;
		Tay1_xuong; 
	
		speed_tay_gat1 = 150;
    target_tay_gat1 = vitri_tay1home;
		speed_tay_gat2 = 150;
     target_tay_gat2 = vitri_tay2home ;

		if ( so_qua_tren_tay == 1  ) {
				be_len_dat_xanh_1_qua_tren_3();
			}
		else if ( so_qua_tren_tay == 2  ) {
				be_len_dat_xanh();
			}
		else if (so_qua_tren_tay == 3 ) {
				be_len_dat_xanh_4_qua();
		}
		else if (so_qua_tren_tay == 4 ) {
				be_len_dat_xanh_4_qua();
		}
		Kep_phai_1_vao;
		Kep_phai_2_vao;
		Kep_phai_3_vao;
		Kep_phai_4_vao;	
		vTaskDelay(3000);
		
		Tay1_xuong;
		Tay2_xuong;
		speed_tay_gat1 = 150;
    target_tay_gat1 = vitri_tay1home;
		speed_tay_gat2 = 150;
     target_tay_gat2 = vitri_tay2home ;
		robotStop(0);
}

void quyet_dinh_dat_hop_tang3_danh_nhanh(void) {
		kiem_tra_so_qua_tren_tay();
		speed_tay_gat1 = 150;
    target_tay_gat1 = vitri_tay1home;
		speed_tay_gat2 = 150;
    target_tay_gat2 = vitri_tay2home ;
	
		if ( so_qua_tren_tay == 1  ) {
				be_len_dat_xanh_1_qua_tren_3();
			}
		else if ( so_qua_tren_tay == 2  ) {
					be_len_dat_xanh();
			}
		else if (so_qua_tren_tay == 3 ) {
				be_len_dat_xanh_4_qua();
		}
		else if (so_qua_tren_tay == 4 ) {
				be_len_dat_xanh_4_qua();
		}

}

// // HAM  DAT VAO O BAC 3
void chuan_bi_dat_tang_3 (void) {
		robotRunAngle(1800, 6,900,0.5);
		vTaskDelay (1500);
		kiem_tra_qua_tay_nao();
		for(i=0;i<150;i++)	{ 
					while((abs(bientroxoaytayValue - target_xoay_tay) > 5) )	{vTaskDelay(1); if(!wantExit())	break;}
			}
		
		for(i=0;i<550;i++)	
	{	
			while(lazeTruocValue > 47)	
			{	
				Bam_thanh_laser_trai(6,900,900, 178, 1, -200, 10);
				vTaskDelay(1); 
				if(!wantExit())	break;
			}
	}
	robotStop(0);
	chinh_lai_vi_tri_laser_trai(176 , 1000);
		robotStop(0);
}

//// kiem tra truoc khi xuat phat ////////
void kiem_tra_vat_truoc_khi_bd (int value_lazer_truoc, int value_lap) {
			for(i=0;i<value_lap;i++)	
	{
		while(lazeTruocValue < value_lazer_truoc)	{	
					vTaskDelay (10);
		if(!wantExit())	break;
					}
	}
}


void mo_vk_san_xanh(void) {
	
	led_bao_hieu_on;
	for(i=0;i<1000;i++)	
	{
		while(quangTroValue > 120)	{	
		vTaskDelay (1);
		if(!wantExit())	break;
					}
	}
	led_bao_hieu_off;
	
	Tay_kep_mo;
	
	led_bao_hieu_on;
	for(i=0;i<1000;i++)	
	{
		while(quangTroValue < 120)	{	
		vTaskDelay (1);
		if(!wantExit())	break;
		}
	}
	vTaskDelay (1000);
	led_bao_hieu_off;
	
	
	da_lay_vk = 1;
		
	if (da_lay_vk == 1 ) {
		speed_tay_gat1 = 250;
		target_tay_gat1 = vitri_tay1home;
	
		speed_tay_gat2 = 250;
		target_tay_gat2 = vitri_tay2home;
		
		kiem_tra_vat_truoc_khi_bd(142, 1000);
		da_lay_vk = 2;
		}		
}

void check_dat_hop_tren_T2_xanh(void) {
    
    if (check_dat_hop_T2 == 1) {
				
        dat_hop_vao_o_tang2(); 
    } 
    else {
				chinh_lai_vi_tri_laser_truoc_xanh(vi_tri_dat_hop_3_tay41_xanh_truoc + 10, 100, 5, 40);
				robotStop(0);
				vTaskDelay (20000);
				led_bao_hieu_on;
				while(lazePhaiValue > 190)	{
							vTaskDelay (1); 
							if(!wantExit())	break;
						}
				led_bao_hieu_off;
				chinh_lai_vi_tri_laser_trai(162, 1000);
				robotStop(0);
				chinh_lai_vi_tri_laser_truoc_xanh(vi_tri_dat_hop_2_tay41_xanh_truoc , 100, 5, 40);
				robotStop(0);
				dat_hop_vao_o_tang2(); 
    }
		robotStop(0);
		

		run_encoder(2500, 1800, 900, 35, 10, 1500, 50);
		robotStop(0);
		
		Kep_phai_1_vao;
		Kep_phai_2_vao;
		Kep_phai_4_vao;
		Kep_phai_3_vao;
		vTaskDelay(3000); 
		
		Tay1_xuong;
		Tay2_xuong;
		
		speed_tay_gat1 = 200;
		target_tay_gat1 = vitri_tay1home;
		speed_tay_gat2 = 200;
		target_tay_gat2 = vitri_tay2home;
				
		robotStop(0);
	
}


void chay_toi_o_dat_qua(int lz_sau, int lz_truoc) {
    int SAI_SO_ALLOW = 30;
    int gia_tri_laser_truoc_thuc_te = lazeTruocValue; 
    int gia_tri_laser_sau_thuc_te = lazeSauValue;

    int delta_truoc = abs(gia_tri_laser_truoc_thuc_te - lz_truoc);
    int delta_sau = abs(gia_tri_laser_sau_thuc_te - lz_sau);

    if (delta_truoc > SAI_SO_ALLOW && delta_sau > SAI_SO_ALLOW) {
        robotStop(0);
        led_bao_hieu_on; 
    }
    else {
        if (delta_truoc <= delta_sau) {
            chinh_lai_vi_tri_laser_truoc_xanh(lz_truoc, 100, 4, 20);
            robotStop(0);
        } 
        else {
            chinh_lai_vi_tri_laser_sau(lz_sau, 100, 4, 20);
            robotStop(0);
        }
    }
}

void chay_toi_o_dat_qua_do(int lz_sau, int lz_truoc) {
    int SAI_SO_ALLOW = 30;
    int gia_tri_laser_truoc_thuc_te = lazeTruocValue; 
    int gia_tri_laser_sau_thuc_te = lazeSauValue;

    int delta_truoc = abs(gia_tri_laser_truoc_thuc_te - lz_truoc);
    int delta_sau = abs(gia_tri_laser_sau_thuc_te - lz_sau);


    if (delta_truoc > SAI_SO_ALLOW && delta_sau > SAI_SO_ALLOW) {
        robotStop(0);
        led_bao_hieu_on; 
    }
    else {
        if (delta_truoc <= delta_sau) {
            chinh_lai_vi_tri_laser_truoc_do(lz_truoc, 100, 4, 17);
            robotStop(0);
        } 
        else {
            chinh_lai_vi_tri_laser_sau(lz_sau, 100, 4, 15);
            robotStop(0);
        }
    }
}


void tudonghoantoan(void) {
	
		Kiem_Tra_Ket_Qua_Gap();
	
		Xuat_Phat_Lay_Vu_Khi_Xanh(163, -1650, 199);
    mo_vk_san_xanh();
    
    if (da_lay_vk == 2) {    
        Run_All_Blocks_From_Queue_san_xanh();
    }
		if (hoan_thanh_chay_rung == 1 ) DatKFSxanh(vi_tri_dat_hop_2_tay41_xanh),hoan_thanh_chay_rung = 2 ;
		
		/// ******* //////
		if (hoan_thanh_chay_rung == 2 && mode_cay_diem == 1)  {
				quyet_dinh_dat_hop_tang3(); // danh cay diem 1
				hoan_thanh_chay_rung = 3 ;}
		
		else if (hoan_thanh_chay_rung == 2 && mode_cay_diem == 2) {
				robotRotate(890,0.2, 0);
				while(robotFixAngle()){
					vTaskDelay (1); 
					if(!wantExit())	break;
				}
				robotStop(0);
				
				chinh_lai_vi_tri_laser_trai(162, 1000);
				robotStop(0);

				chay_toi_o_dat_qua(vi_tri_dat_hop_2_tay41_xanh, vi_tri_dat_hop_2_tay41_xanh_truoc);
				robotStop(0);
				check_dat_hop_tren_T2_xanh();
				robotStop(0);

				robotRunAngle(1800, 15, 900, 0.5);
				RESET_ENCODER(); 
				while(abs(ENCODER_FR()) + abs(ENCODER_FL()) < 800)	{
				su_dung_chan_thuong(730);
				vTaskDelay (1); 
				if(!wantExit())	break;
				}
				robotStop(0);

				hoan_thanh_chay_rung = 3 ;
			}
		
			robotStop(0);
			
//				/// ******* //////
		if (hoan_thanh_chay_rung == 3 && mode_cay_diem == 1)  {
				tu_dong_dat_tang2_xanh(); // danh cay diem 2
				robotStop(0);
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
				if ( so_qua_tren_tay > 0  ) {
						su_dung_chan(730);
						robotStop(0);
						chinh_lai_vi_tri_laser_truoc_xanh(vi_tri_dat_hop_1_tay41_xanh_truoc , 100, 5, 25);
						robotStop(0);
						be_len_dat_xanh_1_qua_tren_3();
						robotStop(0);
			}
				hoan_thanh_chay_rung = 5 ;}
		
		robotStop(0);
}



void retry_zone_2(void) {
		retry_co_qua_tren_tay();
		Run_All_Blocks_From_Queue_san_xanh();

		if (hoan_thanh_chay_rung == 1 ) DatKFSxanh(vi_tri_dat_hop_2_tay41_xanh),hoan_thanh_chay_rung = 2 ;
		
		/// ******* //////
		if (hoan_thanh_chay_rung == 2 && mode_cay_diem == 1)  {
				quyet_dinh_dat_hop_tang3(); // danh cay diem 1
				hoan_thanh_chay_rung = 3 ;}
		
		else if (hoan_thanh_chay_rung == 2 && mode_cay_diem == 2) {
				robotRotate(890,0.2, 0);
				while(robotFixAngle()){
					vTaskDelay (1); 
					if(!wantExit())	break;
				}
				robotStop(0);
				
				chinh_lai_vi_tri_laser_trai(162, 1000);
				robotStop(0);
				chay_toi_o_dat_qua(vi_tri_dat_hop_2_tay41_xanh, vi_tri_dat_hop_2_tay41_xanh_truoc);
				robotStop(0);
				check_dat_hop_tren_T2_xanh();
				
				robotStop(0);
				
				su_dung_chan(730);
				robotStop(0);
				
				hoan_thanh_chay_rung = 3 ;
			}
		
			robotStop(0);
			
//				/// ******* //////
		if (hoan_thanh_chay_rung == 3 && mode_cay_diem == 1)  {
				tu_dong_dat_tang2_xanh(); // danh cay diem 2
				robotStop(0);
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
				if ( so_qua_tren_tay > 0  ) {
						su_dung_chan(730);
						robotStop(0);
						chinh_lai_vi_tri_laser_truoc_xanh(vi_tri_dat_hop_1_tay41_xanh_truoc , 100, 5, 25);
						robotStop(0);
						be_len_dat_xanh_1_qua_tren_3();
						robotStop(0);
			}
				hoan_thanh_chay_rung = 5 ;}
		
		robotStop(0);
}


void chon_tay_tiep_theo(void) {
    if (dang_o_nhom == 1) {
        // Uu tiên tay dang cam quà tru?c
        if (tay_1_co_qua) {
            tay_se_dung_tiep_theo = 1;
        } else if (tay_2_co_qua) {
            tay_se_dung_tiep_theo = 2;
        }
    } 
    else if (dang_o_nhom == 2) {
        if (tay_3_co_qua) {
            tay_se_dung_tiep_theo = 3;
        } else if (tay_4_co_qua) {
            tay_se_dung_tiep_theo = 4;
        }
    }
    else {
        tay_se_dung_tiep_theo = 0;
    }
}

void retry_zone_3_o_1(int vitri) {
		int nhom_A;
		int nhom_B ;
		kiem_tra_so_qua_tren_tay();
		kiem_tra_qua_tay_nao_xuong_rung();
    chon_tay_tiep_theo();
    
		nhom_A = (tay_se_dung_tiep_theo == 1 || tay_se_dung_tiep_theo == 4);
    nhom_B = (tay_se_dung_tiep_theo == 2 || tay_se_dung_tiep_theo == 3);
	
		robotSetACC(60, 65); // gia toc nhanh
		
		robotRunAngle(40,55,0,1.5);
		for(i=0;i<550;i++)	
			{	
					while(lazeSauValue < 210)	
					{	
						vTaskDelay(1); 
						if(!wantExit())	break;
					}
			}
		
		robotRunAngle(650,40,0,1.5);
		for(i=0;i<550;i++)	
			{	
					while(lazeTraiValue < 160)	
					{	
						vTaskDelay(1); 
						if(!wantExit())	break;
					}
			}
			
			robotSetACC(120, 85); // gia toc
		
		/// chay toi 1 doan roi xoay
		robotRunAngle(100,35,900,1.5);
	
		while(_robotIMUAngle < 860)	
		{
			vTaskDelay (1); 
			if(!wantExit())	break;
		}
		
		for(i=0;i<550;i++)	
			{	
					while(lazeTraiValue > 175)	
					{	
						Bam_laser_sau(30,0,900, vitri , 2, -150, 10);
						vTaskDelay(5); 
						if(!wantExit())	break;
					}
			}
				
			for(i=0;i<550;i++)	
			{	
					while(lazeTraiValue > 165)	
					{	
						Bam_laser_sau(10,0,900, vitri , 1, -150, 20);
						su_dung_chan_cham(490);
						vTaskDelay(1); 
						if(!wantExit())	break;
					}
				}	

		robotStop(0);
}

void retry_zone_3_o_2(int vitri) {
		int nhom_A;
		int nhom_B ;
		kiem_tra_so_qua_tren_tay();
		kiem_tra_qua_tay_nao_xuong_rung();
    chon_tay_tiep_theo();
    
		nhom_A = (tay_se_dung_tiep_theo == 1 || tay_se_dung_tiep_theo == 4);
    nhom_B = (tay_se_dung_tiep_theo == 2 || tay_se_dung_tiep_theo == 3);
		
		robotSetACC(60, 65); // gia toc nhanh
	
		robotRunAngle(40,55,0,1.5);
		for(i=0;i<550;i++)	
			{	
					while(lazeSauValue < 200)	
					{	
						vTaskDelay(1); 
						
						if(!wantExit())	break;
					}
			}
					/// di cheo qua
		robotRunAngle(750,40,0,1.5);
		for(i=0;i<550;i++)	
			{	
					while(lazeTraiValue < 190)	
					{	
						vTaskDelay(1); 
						if(!wantExit())	break;
					}
			}
			
		robotSetACC(120, 85); // gia toc
			
		/// chay toi 1 doan roi xoay
		robotRunAngle(100,35,900,1.5);
		while(_robotIMUAngle < 860)	
		{
			vTaskDelay (1); 
			if(!wantExit())	break;
		}	
		
		for(i=0;i<550;i++)	
			{	
					while(lazeTraiValue > 175)	
					{	
						Bam_laser_sau(30,0,900, vitri , 3, -250, 10);
						vTaskDelay(5); 
						if(!wantExit())	break;
					}
			}
				
			for(i=0;i<550;i++)	
			{	
					while(lazeTraiValue > 165)	
					{	
						Bam_laser_sau(10,0,900, vitri , 1, -150, 10);
						su_dung_chan_cham(490);
						vTaskDelay(1); 
						if(!wantExit())	break;
					}
				}	
			robotStop(0);	
}


void retry_zone_3_o_3(int vitri) {
		int nhom_A;
		int nhom_B ;
		kiem_tra_so_qua_tren_tay();
		kiem_tra_qua_tay_nao_xuong_rung();
    chon_tay_tiep_theo();
    
		nhom_A = (tay_se_dung_tiep_theo == 1 || tay_se_dung_tiep_theo == 4);
    nhom_B = (tay_se_dung_tiep_theo == 2 || tay_se_dung_tiep_theo == 3);
		
		robotSetACC(60, 65); // gia toc nhanh
	
		robotRunAngle(50,55,0,1.5);
		for(i=0;i<550;i++)	
			{	
					while(lazeSauValue < 200)	
					{	
						vTaskDelay(1); 
						
						if(!wantExit())	break;
					}
			}

		/// di cheo qua
		robotRunAngle(800,40,0,1.5);
		for(i=0;i<550;i++)	
			{	
					while(lazeTraiValue < 210)	
					{	
						vTaskDelay(1); 
						if(!wantExit())	break;
					}
			}
		
		robotSetACC(120, 85); // gia toc
			
		/// chay toi 1 doan roi xoay
		robotRunAngle(100,35,900,1.5);
		while(_robotIMUAngle < 860)	
		{
			vTaskDelay (1); 
			if(!wantExit())	break;
		}	
		
		for(i=0;i<550;i++)	
			{	
					while(lazeTraiValue > 175)	
					{	
						Bam_laser_sau(30,0,900, vitri , 3, -250, 10);
						vTaskDelay(5); 
						if(!wantExit())	break;
					}
			}
				
			for(i=0;i<550;i++)	
			{	
					while(lazeTraiValue > 165)	
					{	
						Bam_laser_sau(10,0,900, vitri , 1, -150, 10);
						su_dung_chan_cham(490);
						vTaskDelay(1); 
						if(!wantExit())	break;
					}
				}	
			robotStop(0);	
}

void dat_hop4_2_retry(int do_cao_chan, int goc_tay, int ha_chan, int chontay, int gc1, int gc2, int giu_dau, int gt_chuanbi)
{
    int do_cao_chan_hien_tai = do_cao_chan;
    int timeout = 3000;
    int t = 0;
    int retry_count = 0;
    int i = 0;

retry:
    t = 0;
		speed_tay_gat2 = 150;
		target_tay_gat2 = gt_chuanbi;
		for(i=0; i<550; i++) 
			{ 
		while(abs(bientrodaytay2Value - target_tay_gat2) > 5) { vTaskDelay(1); if(!wantExit()) break; }
			}
		vTaskDelay(1000);
    Tay2_len;
    vTaskDelay(8000);

    for(i = 0; i < 550; i++)
    {
        while(CB_xilanh_tay_2 == 1)
        {
            vTaskDelay(1);
            t++;

            if(t > timeout)
            {
                do_cao_chan_hien_tai -= ha_chan;

                if(do_cao_chan_hien_tai < 440)
                    do_cao_chan_hien_tai = 440;

                su_dung_chan(do_cao_chan_hien_tai);

                while(abs(bientrochansauValue - target_chan_sau) > 10)
                {
                    vTaskDelay(1);
                    if(!wantExit()) break;
                }
                break;
            }

            if(!wantExit()) break;
        }
    }

    speed_tay_gat2 = 160;
    target_tay_gat2 = goc_tay;

    for(i = 0; i < 550; i++)
    {
        while(abs(bientrodaytay2Value - target_tay_gat2) > 5)
        {
            vTaskDelay(1);
            if(!wantExit()) break;
        }
    }

    if(IMUxoayDoc > 30)
    {
        retry_count++;

        robotStop(0);
        su_dung_chan(490);

        speed_tay_gat2 = 150;
        target_tay_gat2 = 485;
        Tay2_xuong;

        for(i = 0; i < 50; i++)
        {
            while(abs(bientrodaytay2Value - target_tay_gat2) > 5)
            {
                vTaskDelay(1);
                if(!wantExit()) break;
            }
        }

        vTaskDelay(2500);
        robotStop(0);

        if(retry_count == 1)
        {
            robotRunAngle(gc1, 10, giu_dau, 0.5);
            RESET_ENCODER();

            while(abs(ENCODER_FR()) + abs(ENCODER_FL()) < 580)
            {
                vTaskDelay(5);
                if(!wantExit()) break;
            }
        }
        else
        {
            robotRunAngle(gc2, 10, giu_dau, 0.5);
            RESET_ENCODER();

            while(abs(ENCODER_FR()) + abs(ENCODER_FL()) < 850)
            {
                vTaskDelay(5);
                if(!wantExit()) break;
            }
        }

        robotStop(0);
        vTaskDelay(2000);

        if(retry_count < 3)
            goto retry;
    }

    vTaskDelay(2500);

    if(retry_count >= 3) // dat 3 lan khong duoc
    {
        if(chontay == 2)
        {
            Kep_phai_2_vao;
            vTaskDelay(2500);
        }
        else if(chontay == 4)
        {
            Kep_phai_4_vao;
            vTaskDelay(2500);
        }
				robotStop(0);

				run_encoder(3000, 0, 0, 35, 15, 1500, 50);
				
				robotStop(0);
				speed_tay_gat2 = 150;
        target_tay_gat2 = 445;
				Tay2_xuong;
				robotStop(0);
				robotRotateQuick(-900, 1.3, 0, 0.3,  20);
				robotStop(0);
				su_dung_chan(730);
				robotStop(0);
				quyet_dinh_dat_hop_tang3_danh_nhanh();
				robotStop(0);
    }
    else
    {
        if(chontay == 2)
            Kep_phai_2_ra;
        else if(chontay == 4)
            Kep_phai_4_ra;
    }
}


//void dat_hop4_2(int do_cao_chan, int goc_tay, int ha_chan, int chontay)
//{
//    int do_cao_chan_hien_tai = do_cao_chan;
//    int timeout = 3000;   
//    int t = 0;
//	
//    Tay2_len;
//		vTaskDelay(8000);
//		for (i = 0; i < 550; i++)
//    {
//    while (CB_xilanh_tay_2 == 1)
//    {
//        vTaskDelay(1);
//        t++;

//        if (t > timeout)
//        {
//            do_cao_chan_hien_tai -= ha_chan;
//            if (do_cao_chan_hien_tai < 440)
//                do_cao_chan_hien_tai = 440;

//            su_dung_chan(do_cao_chan_hien_tai);
//            while (abs(bientrochansauValue - target_chan_sau) > 10)
//            {
//                vTaskDelay(1);
//								check_time++; 
//                if (!wantExit()) break;
//            }
//            break; 
//        }
//        if (!wantExit()) break;
//				}
//			}

//    speed_tay_gat2 = 160;
//    target_tay_gat2 = goc_tay;
//		for(i=0; i<550; i++) 
//				{ 
//        while(abs(bientrodaytay2Value - target_tay_gat2) > 5) { vTaskDelay(1); if(!wantExit()) break; }
//          }
//		vTaskDelay(2000);
//					
//    if (chontay == 4)
//    {
//        Kep_phai_4_ra; // 
//    }
//    else if (chontay == 2)
//    {
//        Kep_phai_2_ra; // 
//    }
//}

// tay 4 345, tay 2 550
void dat_hop4_2(int do_cao_chan, int goc_tay, int ha_chan, int chontay)
{
    int do_cao_chan_hien_tai = do_cao_chan;
    int timeout = 3000;
    int t = 0;
    int retry_count = 0;
    int i = 0;

retry:
    t = 0;

    Tay2_len;
    vTaskDelay(8000);

    for (i = 0; i < 550; i++)
    {
        while (CB_xilanh_tay_2 == 1)
        {
            vTaskDelay(1);
            t++;

            if (t > timeout)
            {
                do_cao_chan_hien_tai -= ha_chan;

                if (do_cao_chan_hien_tai < 440)
                    do_cao_chan_hien_tai = 440;

                su_dung_chan(do_cao_chan_hien_tai);

                while (abs(bientrochansauValue - target_chan_sau) > 8)
                {
                    vTaskDelay(1);
                    if (!wantExit()) break;
                }
                break;
            }

            if (!wantExit()) break;
        }
    }

    speed_tay_gat2 = 200;
    target_tay_gat2 = goc_tay;

    for (i = 0; i < 550; i++)
    {
        while (abs(bientrodaytay2Value - target_tay_gat2) > 5)
        {
            vTaskDelay(1);
            if (!wantExit()) break;
        }
    }

    if (IMUxoay > 17)
    {
        retry_count++;

        robotStop(0);
        su_dung_chan(490);

        speed_tay_gat2 = 200;
        target_tay_gat2 = 485;
        Tay2_xuong;

        for (i = 0; i < 50; i++)
        {
            while (abs(bientrodaytay2Value - target_tay_gat2) > 5)
            {
                vTaskDelay(1);
                if (!wantExit()) break;
            }
        }

        vTaskDelay(2500);
        robotStop(0);

        if (retry_count == 1)
        {
            robotRunAngle(-900, 10, 900, 0.5);
            RESET_ENCODER();

            while (abs(ENCODER_FR()) + abs(ENCODER_FL()) < 580)
            {
                vTaskDelay(5);
                if (!wantExit()) break;
            }
        }
        else
        {
            robotRunAngle(900, 10, 900, 0.5);
            RESET_ENCODER();

            while (abs(ENCODER_FR()) + abs(ENCODER_FL()) < 850)
            {
                vTaskDelay(5);
                if (!wantExit()) break;
            }
        }

        robotStop(0);
        vTaskDelay(2000);

        if (retry_count < 3)
            goto retry;
    }

    vTaskDelay(2500);

    if (retry_count >= 3)
    {
        if (chontay == 2)
        {
            Kep_phai_2_vao;
            vTaskDelay(2500);
        }
        else if (chontay == 4)
        {
            Kep_phai_4_vao;
            vTaskDelay(2500);
        }
    }
    else
    {
        if (chontay == 2)
        {
            Kep_phai_2_ra;
        }
        else if (chontay == 4)
        {
            Kep_phai_4_ra;
        }
    }
}

// tay 3 345, tay 1 550
void dat_hop1_3(int do_cao_chan, int goc_tay, int ha_chan, int chontay)
{
    int do_cao_chan_hien_tai = do_cao_chan;
    int timeout = 8000;
    int t = 0;
    int retry_count = 0;
    int i = 0; 

retry:
    t = 0;
    
    Tay1_len;
    vTaskDelay(5000);

    for (i = 0; i < 550; i++)
    {
        while (CB_xilanh_tay_1 == 1)
        {
            vTaskDelay(1);
            t++;

            if (t > timeout)
            {
                do_cao_chan_hien_tai -= ha_chan;

                if (do_cao_chan_hien_tai < 440)
                    do_cao_chan_hien_tai = 440;

                su_dung_chan(do_cao_chan_hien_tai);

                while (abs(bientrochansauValue - target_chan_sau) > 8)
                {
                    vTaskDelay(1);
                    if (!wantExit()) break;
                }
                break;
            }

            if (!wantExit()) break;
        }
    }

    speed_tay_gat1 = 200;
    target_tay_gat1 = goc_tay;

    for (i = 0; i < 550; i++)
    {
        while (abs(bientrodaytay1Value - target_tay_gat1) > 35)
        {
            vTaskDelay(1);
            if (!wantExit()) break;
        }
    }

    if (IMUxoay > 17)
    {
        retry_count++;

        robotStop(0);
        su_dung_chan(490);

        speed_tay_gat1 = 200;
        target_tay_gat1 = 485;
        Tay1_xuong;

        for(i = 0; i < 50; i++)
        {
            while(abs(bientrodaytay1Value - target_tay_gat1) > 5)
            {
                vTaskDelay(1);
                if(!wantExit()) break;
            }
        }

        vTaskDelay(2500);
        robotStop(0);

        if(retry_count == 1)
        {
            robotRunAngle(-900, 10, 900, 0.5);
            RESET_ENCODER();

            while(abs(ENCODER_FR()) + abs(ENCODER_FL()) < 580)
            {
                vTaskDelay(5);
                if(!wantExit()) break;
            }
        }
        else
        {

            robotRunAngle(900, 10, 900, 0.5);
            RESET_ENCODER();

            while(abs(ENCODER_FR()) + abs(ENCODER_FL()) < 850)
            {
                vTaskDelay(5);
                if(!wantExit()) break;
            }
        }

        robotStop(0);
        vTaskDelay(2000);


        if(retry_count < 3)
            goto retry;
    }

    vTaskDelay(2500);

    if (retry_count >= 3)
    {

        if (chontay == 1) {
            Kep_phai_1_vao;
						vTaskDelay(2500);
				}
        else if (chontay == 3) {
            Kep_phai_3_vao;
						vTaskDelay(2500);
						}
    }
    else
    {
        if (chontay == 1)
            Kep_phai_1_ra;
        else if (chontay == 3)
            Kep_phai_3_ra;
    }
}



void chon_o_retry3(void) {
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

    if      (id == 1 && nhom_A) { retry_zone_3_o_1(vi_tri_dat_hop_1_tay41_xanh); }
    else if (id == 1 && nhom_B) { retry_zone_3_o_1(vi_tri_dat_hop_1_tay23_xanh);   }
    else if (id == 2 && nhom_A) { retry_zone_3_o_2(vi_tri_dat_hop_2_tay41_xanh); }
    else if (id == 2 && nhom_B) { retry_zone_3_o_2(vi_tri_dat_hop_2_tay23_xanh);  }
    else if (id == 3 && nhom_A) { retry_zone_3_o_3(vi_tri_dat_hop_3_tay41_xanh); }
    else if (id == 3 && nhom_B) { retry_zone_3_o_3(vi_tri_dat_hop_3_tay23_xanh); }
    else { return; }

    if  (id_dat_hop <= 3) { 
				tu_dong_dat_tang2_xanh();

				robotStop(0);
				su_dung_chan(730);
				robotStop(0);
				quyet_dinh_dat_hop_tang3();
				kiem_tra_so_qua_tren_tay();
				if ( so_qua_tren_tay > 0  ) {
						tu_dong_dat_tang2_xanh();
				}
				}
    else if (id_dat_hop >= 4) { 
				su_dung_chan(730);
				quyet_dinh_dat_hop_tang3();
				kiem_tra_so_qua_tren_tay();
				if ( so_qua_tren_tay > 0  ) {
						tu_dong_dat_tang2_xanh();
				}	
			}
}


void chinh_lai_vi_tri_laser_phai_zone3_do(int vitri, int gia_tri_lap, int min_toc, int max_toc);
void chinh_lai_vi_tri_laser_sau_zone3(int vitri, int gia_tri_lap)
{
	int speed ;
	int dieuchinh;
		for(i=0;i<gia_tri_lap;i++)
				{
		while(abs(lazeSauValue - vitri) > 0)	{
			dieuchinh = lazeSauValue - vitri;
			speed = custom_smooth_speed(dieuchinh, 4, 40);
			
					if  ((lazeSauValue - vitri)> 0 ) {
							robotRunAngle(1800, speed, 0, 0.5);
					}
					else if ((lazeSauValue - vitri)< 0) {
					
					robotRunAngle(0, speed, 0, 0.5);
					
					}
					else {
								robotStop(0);
								}
				if(!wantExit())	break;
			}
		} 				
	}

//// ham nhat lai hop roi dat vao o
void chon_o_nhat_hop_xanh(void) {

		if (nhat_dat_hop == 1 ) {
				chinh_lai_vi_tri_laser_phai_zone3_do(186, 200, 5, 45);
			}
		else if (nhat_dat_hop == 2 ) {
				chinh_lai_vi_tri_laser_phai_zone3_do(217, 200, 5, 45);
			}
		else if (nhat_dat_hop == 3 ) {
				chinh_lai_vi_tri_laser_phai_zone3_do(248, 200, 5, 45);
			}
		else if (nhat_dat_hop == 4|| nhat_dat_hop == 5 || nhat_dat_hop == 6) {
				chinh_lai_vi_tri_laser_sau_zone3(152, 1000);
				chinh_lai_vi_tri_laser_phai_zone3_do(187, 200, 5, 50);
			}

			robotStop(0);
		if (nhat_dat_hop == 1|| nhat_dat_hop == 2 || nhat_dat_hop == 3) {
							
			su_dung_chan_thuong(490);
			chinh_lai_vi_tri_laser_sau_zone3(135, 1000);
			robotStop(0);

			if (da_lay_tay1 == 0 && da_lay_tay2 == 0) {

				dat_hop4_2_retry(490, 330, 5, 4, -900, 900, 0, 407);
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
				dat_hop1_3(490, 550,5, 1);
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
				kiem_tra_so_qua_tren_tay();
				kiem_tra_qua_tay_nao();
			
				chinh_lai_vi_tri_laser_sau_zone3(152, 1000);
				chinh_lai_vi_tri_laser_phai_zone3_do(187, 200, 5, 50);
				robotStop(0);
			
				robotRotate(-890,1.2,0);
				while(robotFixAngle()){
					vTaskDelay (1); 
					if(!wantExit())	break;
					}
				robotStop(0);
				su_dung_chan(730);
				robotStop(0);
				quyet_dinh_dat_hop_tang3();
				robotStop(0);
				robotRotate(10, 0.9, 0);
        while(robotFixAngle()) {
            vTaskDelay (1); 
            if(!wantExit()) break;
        }
					}
				robotStop(0);
				speed_tay_xoay = 200;
				target_xoay_tay = vi_tri_tay_43;
				robotStop(0);
				
}			


void nhat_hop_zone3_xanh (void) {
    int lap;
    bool thu_lai = false;
    
    retry_co_qua_tren_tay(); // kiem tra dang dung tay nao
    su_dung_chan_thuong(400);
	
		robotSetACC(60, 65); // gia toc nhanh
	
		run_encoder(19000, 1800, 0, 65, 35, 3000, 50);

		speed_tay_gat2 = 250;
		target_tay_gat2 = 195;
		
		Kep_phai_4_ra; //
		
		robotSetACC(120, 85); // gia toc giam
     
		led_bao_hieu_on;
    for(i=0; i<5000; i++) {   
        run_align_center();
    }
		led_bao_hieu_off;
		
    
    robotRunAngle(1800, 25, 0, 0.5);
    for(i=0; i<550; i++) {   
        while(lazeSauValue > 150) {   
            vTaskDelay(1); 
            if(!wantExit()) break;
        }
    }  
    robotRunAngle(1800, 10, 0, 0.5);
    for(i=0; i<550; i++) {   
        while(lazeSauValue > 133) {   
            vTaskDelay(1); 
            if(!wantExit()) break;
        }
    }       
    robotStop(0);
    
    // chi tracking hop 
    if (da_lay_tay1 == 0 && da_lay_tay2 == 0) {
			ha_tay_4_k_xlang(120, 75, 200, 20, 1, -900, 900, 7);
			vTaskDelay(1500);
			Kep_phai_4_vao;
			vTaskDelay(3000);
			
			su_dung_chan(460);
			robotStop(0);
			robotRunAngle(0,20,0, 0.5);
			RESET_ENCODER(); 
			while(abs(ENCODER_FR()) + abs(ENCODER_FL()) < 2500)	{
						vTaskDelay (5); 
						if(!wantExit())	break;}
			robotStop(30);
			speed_tay_gat2 = 250;
			target_tay_gat2 = vitri_tay2home; 
				
			speed_tay_gat1 = 150;
			target_tay_gat1 = vitri_tay1home + 90; 

			for(i=0; i<50; i++) { 
				while(abs(bientrodaytay2Value - target_tay_gat2) > ((vitri_tay2home - Min_tay_gat2) / 1.8)) {
					vTaskDelay(1); 
					if(!wantExit()) break;
					}
			}
		}

    robotStop(0);
//    
    // lay xong chay lui ve      
    chon_o_nhat_hop_xanh();
    robotStop(0);
    
    // =========================================================
    // NHAT QUA LAI 3 LAN
    // =========================================================
    for (lap = 0; lap < 8; lap++) {
      // chuan bi lay lan tiep theo
				Kep_phai_4_vao;	
				vTaskDelay(2500);
				Tay2_xuong;
				robotRunAngle(0,25,0, 0.5);
				RESET_ENCODER(); 
				while(abs(ENCODER_FR()) + abs(ENCODER_FL()) < 1800)	{
							vTaskDelay (5); 
							if(!wantExit())	break;}
				robotStop(0);
							
				speed_tay_xoay = 220;
				target_xoay_tay = vi_tri_tay_43;
				chinh_lai_vi_tri_laser_phai_zone3_do(160, 500, 5, 50);
        chinh_lai_vi_tri_laser_sau_zone3(253, 1000);
        robotStop(0);
        
        robotRotate(170, 0.2, 0);
        while(robotFixAngle()) {
            vTaskDelay (1); 
            if(!wantExit()) break;
        }
        robotStop(0);
        
        /// Ngó duoi
        Nang_cham();
        target_chan_truoc = 710 ;
        target_chan_sau = 650;
        SEND_UART (4,6);
        
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
        robotRotate(10, 0.5, 0);
        while(robotFixAngle()) {
            vTaskDelay (1); 
            if(!wantExit()) break;
        }
        robotStop(0);
        su_dung_chan_thuong(400);
        robotStop(0);
        
        speed_tay_gat2 = 250;
        target_tay_gat2 = 195;
				
				for(i=0; i<50; i++) { 
				while(abs(bientrodaytay2Value - target_tay_gat2) > 15) {
					vTaskDelay(1); 
					if(!wantExit()) break;
						}
					}
        Kep_phai_4_ra; //
					
				led_bao_hieu_on;
        for(i=0; i<350; i++) {   
            while(mode_nhat_hop == 0) {   
                vTaskDelay(1); 
                if(!wantExit()) break; 
            }
        }
				
				led_bao_hieu_off;
        /// nhin thay khoi sau do check lazer trai
        for(i=0; i<350; i++) {   
            while(lazeTraiValue > 210) {   
                vTaskDelay(1); 
                if(!wantExit()) break; 
            }
        }
        vTaskDelay(7000);
				robotRunAngle(1800, 10, 0, 0.5);
				vTaskDelay(3000);
        
				led_bao_hieu_on;
        /// check tam hop
        for(i=0; i<5000; i++) {   
            run_align_center();
        }
				led_bao_hieu_off;
        
        robotStop(0);
        robotRunAngle(1800, 25, 0, 0.5);
        for(i=0; i<550; i++) {   
            while(lazeSauValue > 150) {   
                vTaskDelay(1); 
                if(!wantExit()) break;
            }
        }   
        
        robotRunAngle(1800, 10, 0, 0.5);
        for(i=0; i<550; i++) {   
            while(lazeSauValue > 133) {   // lz moi
                vTaskDelay(1); 
                if(!wantExit()) break;
            }
        }       
        robotStop(0);
        ha_tay_4_k_xlang(120, 75, 200, 10, 1, -900, 900, 7);
				vTaskDelay(1500);
				Kep_phai_4_vao;
				vTaskDelay(3000);
				
				su_dung_chan(460);
				robotStop(0);
				robotRunAngle(0,20,0, 0.5);
				RESET_ENCODER(); 
				while(abs(ENCODER_FR()) + abs(ENCODER_FL()) < 2000)	{
							vTaskDelay (5); 
							if(!wantExit())	break;}
				robotStop(30);
				speed_tay_gat2 = 250;
				target_tay_gat2 = vitri_tay2home; 
				
				speed_tay_gat1 = 150;
				target_tay_gat1 = vitri_tay1home + 90; 

				for(i=0; i<50; i++) { 
					while(abs(bientrodaytay2Value - target_tay_gat2) > ((vitri_tay2home - Min_tay_gat2) / 1.8)) {
						vTaskDelay(1); 
						if(!wantExit()) break;
						}
				}

		robotStop(0);
			
		// ----------------------------------------------------
		
		chon_o_nhat_hop_xanh();
		nhin_hop_duoi_dat = 0; 
		nhin_hop_tren_buc = 0; 
    }
		robotStop(0);
}

void xac_dinh_vi_tri_robot_xanh(void)
{
    kiem_tra_so_qua_tren_tay();

    // ===== TAY 1 - 4 =====
    if (tay_1_co_qua || tay_4_co_qua)
    {
        int val = lazeSauValue;

        int m12 = (vi_tri_dat_hop_1_tay41_xanh + vi_tri_dat_hop_2_tay41_xanh) / 2;
        int m23 = (vi_tri_dat_hop_2_tay41_xanh + vi_tri_dat_hop_3_tay41_xanh) / 2;

        if (val < m12)
            robot_position = 1;
        else if (val < m23)
            robot_position = 2;
        else
            robot_position = 3;
    }

    // ===== TAY 2 - 3 =====
    else if (tay_2_co_qua || tay_3_co_qua)
    {
        int val = lazeSauValue;

        int m12 = (vi_tri_dat_hop_1_tay23_xanh + vi_tri_dat_hop_2_tay23_xanh) / 2;
        int m23 = (vi_tri_dat_hop_2_tay23_xanh + vi_tri_dat_hop_3_tay23_xanh) / 2;

        if (val < m12)
            robot_position = 1;
        else if (val < m23)
            robot_position = 2;
        else
            robot_position = 3;
    }
}


void tu_dong_dat_tang2_xanh(void) {
		robotRotate(890,0.2, 0);
		while(robotFixAngle()){
					vTaskDelay (1); 
					if(!wantExit())	break;
				}
		robotStop(0);
		kiem_tra_so_qua_tren_tay();
		kiem_tra_qua_tay_nao();
		xac_dinh_vi_tri_robot_xanh();

		if (tay_1_co_qua || tay_4_co_qua) {
        if (robot_position == 1) {
						chay_toi_o_dat_qua(vi_tri_dat_hop_1_tay41_xanh, vi_tri_dat_hop_1_tay41_xanh_truoc);
            robotStop(0);
            chinh_lai_vi_tri_laser_trai(162, 1000);
        } 
        else if (robot_position == 2) {
						chay_toi_o_dat_qua(vi_tri_dat_hop_2_tay41_xanh, vi_tri_dat_hop_2_tay41_xanh_truoc);
            robotStop(0);
            chinh_lai_vi_tri_laser_trai(162, 1000);
        } 
        else if (robot_position == 3) {
						chay_toi_o_dat_qua(vi_tri_dat_hop_3_tay41_xanh, vi_tri_dat_hop_3_tay41_xanh_truoc);
            robotStop(0);
            chinh_lai_vi_tri_laser_trai(162, 1000);
        }
    } 
    else if (tay_2_co_qua || tay_3_co_qua) {
        if (robot_position == 1) {
						chay_toi_o_dat_qua(vi_tri_dat_hop_1_tay23_xanh, vi_tri_dat_hop_1_tay23_xanh_truoc);
            robotStop(0);
            chinh_lai_vi_tri_laser_trai(170, 1000); /// trg hop tay 3 vi trí 1
        } 
        else if (robot_position == 2) {
						chay_toi_o_dat_qua(vi_tri_dat_hop_2_tay23_xanh, vi_tri_dat_hop_2_tay23_xanh_truoc);
            robotStop(0);
            chinh_lai_vi_tri_laser_trai(162, 1000);
        } 
        else if (robot_position == 3) {
						chay_toi_o_dat_qua(vi_tri_dat_hop_3_tay23_xanh, vi_tri_dat_hop_3_tay23_xanh_truoc);
            robotStop(0);
            chinh_lai_vi_tri_laser_trai(162, 1000);
        }
    }
		
			robotStop(0);
			// do chan len dat
			su_dung_chan(490);
			for(i=0;i<250;i++)	{
				while(abs(bientrochansauValue - target_chan_sau) > 10)	{ vTaskDelay(1); if(!wantExit())	break;}
					}		
			dat_hop_vao_o_tang2();
			robotStop(0);

			run_encoder(2500, 1800, 900, 35, 10, 1500, 50);
			robotStop(0);
			
			Kep_phai_1_vao;
			Kep_phai_2_vao;
			Kep_phai_4_vao;
			Kep_phai_3_vao;
			vTaskDelay(3000); 
			
			Tay1_xuong;
			Tay2_xuong;
			
			speed_tay_gat1 = 200;
			target_tay_gat1 = vitri_tay1home;
			speed_tay_gat2 = 200;
			target_tay_gat2 = vitri_tay2home;
					
			robotStop(0);
			
}


void bat_dau_chay_xanh (void) {
    if (Start == 0 && mode_chay_rung == 1) {
				led_bao_hieu_off;
        tudonghoantoan();
    }
		else if (Start == 0 && mode_chay_rung == 0 && mode_nhat_hop == 0 && mode_retry_zone_3 == 0) {
				led_bao_hieu_off;
        Xuat_Phat_Lay_Vu_Khi_Xanh(163, -1650, 199);
    }
    else if (Start == 0 && mode_chay_rung == 2) {
				led_bao_hieu_off;
				su_dung_chan(265);
				robotRunAngle(-900, 15, 0,0.5);
				RESET_ENCODER(); 
				while(abs(ENCODER_FR()) + abs(ENCODER_FL()) < 1000)	{vTaskDelay (5); if(!wantExit())	break;}
				robotStop(0);
				robotRotate(-890,1.2, 0);
				while(robotFixAngle()){
				vTaskDelay (1); 
				if(!wantExit())	break;
						}
				robotStop(0);
        retry_zone_2();
    }
    else if (Start == 0 && mode_nhat_hop == 1) {
				led_bao_hieu_off;
        nhat_hop_zone3_xanh();
    }
		else if (Start == 0 && mode_retry_zone_3 == 1) {
				led_bao_hieu_off;
        chon_o_retry3();
    }
}


int Tinh_Toc_Do_Gat_Tay_Excel(int current_error, int target_error, int start_error, int max_toc, int min_toc, float k)
{
    int speed_out;
    float ratio;

    if (current_error >= start_error)
    {
        return max_toc;
    }
    
    if (current_error <= target_error)
    {
        return min_toc;
    }

    ratio = (float)(start_error - current_error) / (float)(start_error - target_error);
    
    speed_out = min_toc + (int)((float)(max_toc - min_toc) * (1.0f - powf(ratio, k)));

    if (speed_out > max_toc) speed_out = max_toc;
    if (speed_out < min_toc) speed_out = min_toc;

    return speed_out;
}

void ha_tay_4(int target_tay, int hs_trackking, int max_toc, int min_toc, float k, int gc_cb2, int gc_cb1, int toc_track) {
    int current_error;
    int target_error;
    int start_error;

    uint8_t is_hop_detected = 0; 
    uint8_t current_track_speed = 8; 
    uint8_t last_active_sensor = 0;   

    Tay2_len;

    for(i=0; i<50; i++) { 
        while(CB_xilanh_tay_2 == 1) { 
            vTaskDelay(1); 
            if(!wantExit()) break; 
        }
    }
		Kep_phai_4_ra; //
    
    target_tay_gat2 = target_tay; 
    
    target_error = hs_trackking;
    start_error = target_error + 90; 

    while(1) { 
        current_error = abs(bientrodaytay2Value - target_tay_gat2);
				Kep_phai_4_ra;
        
        if (current_error <= target_error) {
            break;
        }
                
        speed_tay_gat2 = Tinh_Toc_Do_Gat_Tay_Excel(current_error, target_error, start_error, max_toc, min_toc, k);
        
        vTaskDelay(1); 
        if(!wantExit()) break; 
    }
    Kep_phai_4_ra;
    while(abs(bientrodaytay2Value - target_tay_gat2) > 5) {
        
        if (check_hop_4 == 1) {
            is_hop_detected = 1;
        }

        if (is_hop_detected == 1) {
            speed_tay_gat2 = 100;
            led_bao_hieu_off;
            robotStop(0); 
        } 
        else if (CB_kep_4_2 == 0 || CB_kep_4_1 == 0) {
            led_bao_hieu_on;
            
            if (CB_kep_4_2 == 0 ) {
                if (last_active_sensor == 1) {
                    current_track_speed = toc_track; 
                }
                last_active_sensor = 2; 

                robotRun(gc_cb2, current_track_speed);
                speed_tay_gat2 = 20; 
            } 
            else if (CB_kep_4_1 == 0 ) {
                if (last_active_sensor == 2) {
                    current_track_speed = toc_track; 
                }
                last_active_sensor = 1;

                robotRun(gc_cb1, current_track_speed);
                speed_tay_gat2 = 20;
            }
        } 
        else {
            speed_tay_gat2 = 100;
            led_bao_hieu_off;
            robotStop(0);
        }
        
        vTaskDelay(1); 
        if(!wantExit()) break;
    }

    led_bao_hieu_off;
    robotStop(0);
}

void ha_tay_1(int target_tay, int hs_trackking, int max_toc, int min_toc, float k, int gc_cb2, int gc_cb1, int toc_track) {
    int current_error;
    int target_error;
    int start_error;

    uint8_t is_hop_detected = 0;
    uint8_t is_tracking_done = 0;
    uint8_t current_track_speed = 8;
    uint8_t last_active_sensor = 0;

    Tay1_len;
    
    for(i=0; i<50; i++) { 
        while(CB_xilanh_tay_1 == 1) { 
            vTaskDelay(1); 
            if(!wantExit()) break; 
        }
    }
    
		
    target_tay_gat1 = target_tay; 
    
    target_error = hs_trackking;
    start_error = target_error + 90; 
		Kep_phai_1_ra;

    while(1) { 
        current_error = abs(bientrodaytay1Value - target_tay_gat1);
        Kep_phai_1_ra;
			
        if (current_error <= target_error) {
            break;
        }
                
        speed_tay_gat1 = Tinh_Toc_Do_Gat_Tay_Excel(current_error, target_error, start_error, max_toc, min_toc, k);
        
        vTaskDelay(1); 
        if(!wantExit()) break; 
    }
    Kep_phai_1_ra;
    while(abs(bientrodaytay1Value - target_tay_gat1) > 5) {
        if (check_hop_1 == 0) {
            is_hop_detected = 1;
        }

        if (is_hop_detected == 1 || is_tracking_done == 1) {
            speed_tay_gat1 = 100;
            led_bao_hieu_off;
            robotStop(0);
        } 
        else if (CB_kep_1_2 == 0 || CB_kep_1_1 == 0) {
            led_bao_hieu_on;
            if (CB_kep_1_2 == 0 ) {
                if (last_active_sensor == 1) {
                    current_track_speed = toc_track;
                }
                last_active_sensor = 2;

                robotRun(gc_cb2, current_track_speed);
                speed_tay_gat1 = 20;
            } 
            else if (CB_kep_1_1 == 0 ) {
                if (last_active_sensor == 2) {
                    current_track_speed = toc_track;
                }
                last_active_sensor = 1;

                robotRun(gc_cb1, current_track_speed);
                speed_tay_gat1 = 20;
            }
        } 
        else {
            speed_tay_gat1 = 100;
            led_bao_hieu_off;
            robotStop(0);

            if (last_active_sensor != 0) {
                is_tracking_done = 1;
            }
        }
        
        vTaskDelay(1);
        if(!wantExit()) break;
    }
    
    led_bao_hieu_off;
    robotStop(0);
}

void ha_tay_2(int target_tay, int hs_trackking, int max_toc, int min_toc, float k, int gc_cb2, int gc_cb1, int toc_track) {
    int current_error;
    int target_error;
    int start_error;

    uint8_t is_hop_detected = 0;
    uint8_t is_tracking_done = 0;
    uint8_t current_track_speed = 8;
    uint8_t last_active_sensor = 0;

    Tay2_len;
    
    for(i=0; i<50; i++) { 
        while(CB_xilanh_tay_2 == 1) { 
            vTaskDelay(1); 
            if(!wantExit()) break; 
        }
    }
		
    target_tay_gat2 = target_tay; 
    
    target_error = hs_trackking;
    start_error = target_error + 90; 

    while(1) { 
        current_error = abs(bientrodaytay2Value - target_tay_gat2);
        Kep_phai_2_ra;
        if (current_error <= target_error) {
            break;
        }
                
        speed_tay_gat2 = Tinh_Toc_Do_Gat_Tay_Excel(current_error, target_error, start_error, max_toc, min_toc, k);
        
        vTaskDelay(1); 
        if(!wantExit()) break; 
    }
    
		Kep_phai_2_ra;
    while(abs(bientrodaytay2Value - target_tay_gat2) > 5) {
				
        if (check_hop_2 == 0) {
            is_hop_detected = 1;
        }

        if (is_hop_detected == 1 || is_tracking_done == 1) {
            speed_tay_gat2 = 100;
            led_bao_hieu_off;
            robotStop(0);
        } 
        else if (CB_kep_2_2 == 0 || CB_kep_2_1 == 0) {
            led_bao_hieu_on;
            if (CB_kep_2_2 == 0 ) {
                if (last_active_sensor == 1) {
                    current_track_speed = toc_track;
                }
                last_active_sensor = 2;

                robotRun(gc_cb2, current_track_speed);
                speed_tay_gat2 = 20;
            } 
            else if (CB_kep_2_1 == 0 ) {
                if (last_active_sensor == 2) {
                    current_track_speed = toc_track;
                }
                last_active_sensor = 1;

                robotRun(gc_cb1, current_track_speed);
                speed_tay_gat2 = 20;
            }
        } 
        else {
            speed_tay_gat2 = 100;
            led_bao_hieu_off;
            robotStop(0);

            if (last_active_sensor != 0) {
                is_tracking_done = 1;
            }
        }
        
        vTaskDelay(1);
        if(!wantExit()) break;
    }
    
    led_bao_hieu_off;
    robotStop(0);
}


void ha_tay_3(int target_tay, int hs_trackking, int max_toc, int min_toc, float k, int gc_cb2, int gc_cb1, int toc_track) {
    int current_error;
    int target_error;
    int start_error;

    uint8_t is_hop_detected = 0;
    uint8_t is_tracking_done = 0;
    uint8_t current_track_speed = 8;
    uint8_t last_active_sensor = 0;

    
    Tay1_len;
    
    for(i=0; i<50; i++) { 
        while(CB_xilanh_tay_1 == 1) { 
            vTaskDelay(1); 
            if(!wantExit()) break; 
        }
    }
		
		Kep_phai_3_ra;
    
    target_tay_gat1 = target_tay; 
    
    target_error = hs_trackking;
    start_error = target_error + 90; 

    while(1) { 
        current_error = abs(bientrodaytay1Value - target_tay_gat1);
        Kep_phai_3_ra;
        if (current_error <= target_error) {
            break;
        }
                
        speed_tay_gat1 = Tinh_Toc_Do_Gat_Tay_Excel(current_error, target_error, start_error, max_toc, min_toc, k);
        
        vTaskDelay(1); 
        if(!wantExit()) break; 
    }
    Kep_phai_3_ra;
    while(abs(bientrodaytay1Value - target_tay_gat1) > 5) {
        if (check_hop_3 == 1) {
            is_hop_detected = 1;
        }

        if (is_hop_detected == 1 || is_tracking_done == 1) {
            speed_tay_gat1 = 100;
            led_bao_hieu_off;
            robotStop(0);
        } 
        else if (CB_kep_3_2 == 0 || CB_kep_3_1 == 0) {
            led_bao_hieu_on;
            if (CB_kep_3_2 == 0 ) {
                if (last_active_sensor == 1) {
                    current_track_speed = toc_track;
                }
                last_active_sensor = 2;

                robotRun(gc_cb2, current_track_speed);
                speed_tay_gat1 = 15;
            } 
            else if (CB_kep_3_1 == 0 ) {
                if (last_active_sensor == 2) {
                    current_track_speed = toc_track;
                }
                last_active_sensor = 1;

                robotRun(gc_cb1, current_track_speed);
                speed_tay_gat1 = 15;
            }
        } else {
            speed_tay_gat1 = 100;
            led_bao_hieu_off;
            robotStop(0);

            if (last_active_sensor != 0) {
                is_tracking_done = 1;
            }
        }
        
        vTaskDelay(1);
        if(!wantExit()) break;
    }
    
    led_bao_hieu_off;
    robotStop(0);
}


void ha_tay_4_k_xlang(int target_tay, int hs_trackking, int max_toc, int min_toc, float k, int gc_cb2, int gc_cb1, int toc_track) {
    int current_error;
    int target_error;
    int start_error;

    uint8_t is_hop_detected = 0; 

    
    target_tay_gat2 = target_tay; 
    
    target_error = hs_trackking;
    start_error = target_error + 85; 
	
		Kep_phai_4_ra; //

    while(1) { 
        current_error = abs(bientrodaytay2Value - target_tay_gat2);
        Kep_phai_4_ra;
        if (current_error <= target_error) {
            break;
        }
                
        speed_tay_gat2 = Tinh_Toc_Do_Gat_Tay_Excel(current_error, target_error, start_error, max_toc, min_toc, k);
        
        vTaskDelay(1); 
        if(!wantExit()) break; 
    }
    Kep_phai_4_ra;
    while(abs(bientrodaytay2Value - target_tay_gat2) > 5) {
        
        if (check_hop_4 == 1) {
            is_hop_detected = 1;
        }

        if (is_hop_detected == 1) {
            speed_tay_gat2 = 100;
            led_bao_hieu_off;
            robotStop(0); 
        } 
        else if (CB_kep_4_2 == 0 || CB_kep_4_1 == 0) {
            led_bao_hieu_on;
            if (CB_kep_4_2 == 0 ) {
                robotRun(gc_cb2, toc_track);
                speed_tay_gat2 = 20; 
            } 
            else if (CB_kep_4_1 == 0 ) {
                robotRun(gc_cb1, toc_track);
                speed_tay_gat2 = 20;
            }
        } 
        else {
            speed_tay_gat2 = 100;
            led_bao_hieu_off;
            robotStop(0);
        }
        
        vTaskDelay(1); 
        if(!wantExit()) break;
    }

    led_bao_hieu_off;
    robotStop(0);
}

void ha_tay_1_k_xlang(int target_tay, int hs_trackking, int max_toc, int min_toc, float k, int gc_cb2, int gc_cb1, int toc_track) {
    int current_error;
    int target_error;
    int start_error;
    uint8_t is_hop_detected = 0;

    Kep_phai_1_ra;
    
    target_tay_gat1 = target_tay; 
    
    target_error = hs_trackking;
    start_error = target_error + 80; 

    while(1) { 
        current_error = abs(bientrodaytay1Value - target_tay_gat1);
        Kep_phai_1_ra;
        if (current_error <= target_error) {
            break;
        }
                
        speed_tay_gat1 = Tinh_Toc_Do_Gat_Tay_Excel(current_error, target_error, start_error, max_toc, min_toc, k);
        
        vTaskDelay(1); 
        if(!wantExit()) break; 
    }
    Kep_phai_1_ra;
    while(abs(bientrodaytay1Value - target_tay_gat1) > 5) {
        if (check_hop_1 == 0) {
            is_hop_detected = 1;
        }

        if (is_hop_detected == 1) {
            speed_tay_gat1 = 100;
            led_bao_hieu_off;
            robotStop(0);
        } 
        else if (CB_kep_1_2 == 0 || CB_kep_1_1 == 0) {
            led_bao_hieu_on;
            if (CB_kep_1_2 == 0 ) {
                robotRun(gc_cb2, toc_track);
                speed_tay_gat1 = 25;
            } 
            else if (CB_kep_1_1 == 0 ) {
                robotRun(gc_cb1, toc_track);
                speed_tay_gat1 = 25;
            }
        } 
        else {
            speed_tay_gat1 = 100;
            led_bao_hieu_off;
            robotStop(0);
        }
        
        vTaskDelay(1);
        if(!wantExit()) break;
    }
    
    led_bao_hieu_off;
    robotStop(0);
}


void ha_tay_2_k_xlang(int target_tay, int hs_trackking, int max_toc, int min_toc, float k, int gc_cb2, int gc_cb1, int toc_track) {
    int current_error;
    int target_error;
    int start_error;
    uint8_t is_hop_detected = 0;

    Kep_phai_2_ra;

    target_tay_gat2 = target_tay; 
    
    target_error = hs_trackking;
    start_error = target_error + 80; 

    while(1) { 
        current_error = abs(bientrodaytay2Value - target_tay_gat2);
        Kep_phai_2_ra;
        if (current_error <= target_error) {
            break;
        }
                
        speed_tay_gat2 = Tinh_Toc_Do_Gat_Tay_Excel(current_error, target_error, start_error, max_toc, min_toc, k);
        
        vTaskDelay(1); 
        if(!wantExit()) break; 
    }
    Kep_phai_2_ra;
    while(abs(bientrodaytay2Value - target_tay_gat2) > 5) {
        if (check_hop_2 == 0) {
            is_hop_detected = 1;
        }

        if (is_hop_detected == 1) {
            speed_tay_gat2 = 100;
            led_bao_hieu_off;
            robotStop(0);
        } 
        else if (CB_kep_2_2 == 0 || CB_kep_2_1 == 0) {
            led_bao_hieu_on;
            if (CB_kep_2_2 == 0 ) {
                robotRun(gc_cb2, toc_track);
                speed_tay_gat2 = 25;
            } 
            else if (CB_kep_2_1 == 0 ) {
                robotRun(gc_cb1, toc_track);
                speed_tay_gat2 = 25;
            }
        } 
        else {
            speed_tay_gat2 = 100;
            led_bao_hieu_off;
            robotStop(0);
        }
        
        vTaskDelay(1);
        if(!wantExit()) break;
    }
    
    led_bao_hieu_off;
    robotStop(0);
}


void ha_tay_3_k_xlang(int target_tay, int hs_trackking, int max_toc, int min_toc, float k, int gc_cb2, int gc_cb1, int toc_track) {
   int current_error;
    int target_error;
    int start_error;
    uint8_t is_hop_detected = 0;

    Kep_phai_3_ra;
    
    target_tay_gat1 = target_tay; 
    
    target_error = hs_trackking;
    start_error = target_error + 90; 

    while(1) { 
        current_error = abs(bientrodaytay1Value - target_tay_gat1);
        Kep_phai_3_ra;
        if (current_error <= target_error) {
            break;
        }
                
        speed_tay_gat1 = Tinh_Toc_Do_Gat_Tay_Excel(current_error, target_error, start_error, max_toc, min_toc, k);
        
        vTaskDelay(1); 
        if(!wantExit()) break; 
    }
    Kep_phai_3_ra;
    while(abs(bientrodaytay1Value - target_tay_gat1) > 5) {
        if (check_hop_3 == 1) {
            is_hop_detected = 1;
        }

        if (is_hop_detected == 1) {
            speed_tay_gat1 = 100;
            led_bao_hieu_off;
            robotStop(0);
        } 
        else if (CB_kep_3_2 == 0 || CB_kep_3_1 == 0) {
            led_bao_hieu_on;
            if (CB_kep_3_2 == 0 ) {
                robotRun(gc_cb2, toc_track);
                speed_tay_gat1 = 23;
            } 
            else if (CB_kep_3_1 == 0 ) {
                robotRun(gc_cb1, toc_track);
                speed_tay_gat1 = 23;
            }
        } else {
            speed_tay_gat1 = 100;
            led_bao_hieu_off;
            robotStop(0);
        }
        
        vTaskDelay(1);
        if(!wantExit()) break;
    }
    led_bao_hieu_off;
    
    robotStop(0);
}


