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
					robotRunAngle(900,10,900,0.7);
					vTaskDelay (5000);
				}
				robotStop(0);
}



//*************************** XUAT PHAT LAAYS VU KHI 3 ***********************************
void Xuat_Phat_Lay_Vu_Khi_Xanh(int vu_khi, int goc_ve,int vitri)
 //				RESET_ENCODER(); 
{				
				speed_tay_gat1 = 150;
				target_tay_gat1 = vitri_tay1home;
	
				speed_tay_gat2 = 250;
				target_tay_gat2 = vitri_tay2home;
	
				Nang_cuc_nhanh();
	
				target_chan_truoc = 350, target_chan_sau = 350;
				Tay_kep_mo;
	
				robotRunAngle(-150 - vu_khi*2,40,3,0.5);
				for(i=0;i<100;i++)
				{
					while(lazePhaiValue < vu_khi-7)	
					{
						if(!wantExit())	break;
					}
				}
				Nang_cuc_nhanh();
				target_chan_truoc = 608, target_chan_sau =617;
				for(i=0;i<50;i++)		
				{
				while(bientrochantruocValue < 470)	{
				Bam_thanh_laser_phai(34,0,0,vu_khi,2,100,15);
				vTaskDelay(1); 
				if(!wantExit())	break;}
				}
				
				for(i=0;i<250;i++)
				{
					while(lazeTruocValue > 30)	
					{	
	
						Bam_thanh_laser_phai(32,0,0,vu_khi,2,80,15);
						
						if(!wantExit())	break;
					}
				}
				for(i=0;i<250;i++)
				{
					while(lazeTruocValue > 16)	
					{	
	
						Bam_thanh_laser_phai(18,0,0,vu_khi,2,80,15);
						
						if(!wantExit())	break;
					}
				}
				Tay_kep_xuong;

				for(i=0;i<100;i++)
				{
					while(HT_1 == 0 && HT_2 == 0)	
					{				
						if(lazeTruocValue < 17)	Tay_kep_xuong;
						Bam_thanh_laser_phai(10,0,0,vu_khi,3,70,15);
						if(!wantExit())	break;
					}
				}
				vTaskDelay(2000); 
			
				robotStop(50);
						
				for(i=0;i<500;i++)
				{
					while(CB_tay_kep_vk_T == 1 || CB_tay_kep_vk_P == 1)	
					{	
						if	(CB_tay_kep_vk_P == 1) robotRun(-870,11);
						else if 	(CB_tay_kep_vk_T == 1) robotRun(870,11);
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
				
				robotRun(goc_ve - ((KC_Vu_khi - vu_khi)*10),30);
				robotRotate(-900,-2.35,0);
				
				Nang_cuc_nhanh();
		
				while(_robotIMUAngle >-450)	
				{
					vTaskDelay (2); 
					if(!wantExit())	break;
					if(_robotIMUAngle < -450)		target_chan_truoc = 265, target_chan_sau = 265;
				}
				
				target_chan_truoc = 265, target_chan_sau = 265;
				robotStop(0);
 
				robotRunAngle(900,9,-900,0.7);
				
				for(i=0;i<100;i++)
				{
					while(HT_3 == 0 && HT_4 == 0)	
					{           
						vTaskDelay (5); 
						if(!wantExit())	break;
					}
				}
				
				vTaskDelay(1500);
				robotStop(0);
				chinh_lai_vi_tri_VK(vitri, 1000);
				robotStop(0);
				speed_chan_sau =40;
				speed_chan_truoc = 41;
				target_chan_truoc = 231, target_chan_sau = 231;
				robotStop(0);
				robotRunAngle(900,9,-900,0.7);
				vTaskDelay(1500);
				robotStop(0);
			}

//******************** xoay dau detect xem co robot phia truoc hay khong ********************************************
void Xoay_dau_truoc_cua_xanh_1(void)
{
	Nang_cuc_nhanh();
	target_chan_truoc = 265;
	target_chan_sau = 265;

	
	vTaskDelay(2000);

	robotRunAngle(-1450,30,900,2);
//				
				while(_robotIMUAngle < 895)	
				{
					vTaskDelay (5); 
					if(!wantExit())	break;
				}
				
	robotStop(0);
				
	if (TinHieu_ChuanBi_GapThang == 1) {
			chinh_lai_vi_tri_laser_phai_custom(vi_tri_cua_rung_xanh_1_lazer_phai_tay_41 + 5 , 1000, 5 , 65, 7 );
	}
	else if (TinHieu_ChuanBi_GapThang == 0) {
			chinh_lai_vi_tri_laser_phai_custom(vi_tri_cua_rung_xanh_1_lazer_phai_tay_41 - 15, 1000, 5 , 65, 10);
	}
	if (block_pha == 1) {
			SEND_UART (4,1);
		}
	else {
		co_vat_can = 0 ;
	}
	robotStop(0); 	
				
}

void Xoay_dau_truoc_cua_xanh_2 (void)
{
	Nang_cuc_nhanh();

	target_chan_truoc = 265;
	target_chan_sau = 265;

	
	vTaskDelay(2000);
	robotRunAngle(-1500,30,900,2);
//				
				while(_robotIMUAngle < 895)	
				{
					vTaskDelay (5); 
					if(!wantExit())	break;
				}
	robotStop(0);
	if (TinHieu_ChuanBi_GapThang == 0) {
			chinh_lai_vi_tri_laser_phai_custom(vi_tri_cua_rung_xanh_2_lazer_phai_tay_41 - 15 , 1000, 5, 65, 10);
	}
	else if (TinHieu_ChuanBi_GapThang == 1) {
			chinh_lai_vi_tri_laser_phai_custom(vi_tri_cua_rung_xanh_2_lazer_phai_tay_41  , 1000, 5, 65, 7);
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

	target_chan_truoc = 265;
	target_chan_sau = 265;
	
	vTaskDelay(2000);
	robotRunAngle(-1030,20,900,3);
//				
				while(_robotIMUAngle < 895)	
				{
					vTaskDelay (5); 
					if(!wantExit())	break;
				}
				
	robotStop(0);
	if (TinHieu_ChuanBi_GapThang == 1) {
			chinh_lai_vi_tri_laser_phai_custom(vi_tri_cua_rung_xanh_3_lazer_phai_tay_41  , 1000, 5, 65, 7);
	}
	else if (TinHieu_ChuanBi_GapThang == 0) {
			chinh_lai_vi_tri_laser_phai_custom(vi_tri_cua_rung_xanh_3_lazer_phai_tay_41 - 15 , 1000, 5, 65, 10);
	}
	
	if (block_pha == 3) {
			SEND_UART (4,1);
		}
	else {
		co_vat_can = 0 ;
	}
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
	Nang_nhanh();
	target_chan_truoc = Min_chan_truoc + 250;
	target_chan_sau = Min_chan_sau + 250;

		for(i=0;i<250;i++)
		{
			while(lazeSauValue > 115)	
			{	
			Bam_thanh_laser_phai_cua_vao(50,-900,900,vitri,5,150,30);
				vTaskDelay (1);
				if(!wantExit())	break;
			}
				}
			for(i=0;i<250;i++)	
		{
			while(abs(bientrochansauValue - target_chan_sau) > 20)
									{	
			Bam_thanh_laser_phai_cua_vao(40,-900,900,vitri,2,150,30);
			if(!wantExit())	break;
						}
		}
	
	robotRunAngle(-900,35,900,0.9);
		for(i=0;i<250;i++)
					{
						while(lazeSauValue > 40)	
						{	
							vTaskDelay (1);
							if(!wantExit())	break;
						}
				}
				

			su_dung_chan(710);
		
	if (TinHieu_ChuanBi_GapThang == 0) {
			for(i=0;i<250;i++)
					{
						while(lazeSauValue > 15  )	
						{	
							Bam_thanh_laser_phai_cua_vao(25,-900,900,vitri - 15,2,150,30);
							vTaskDelay (1);
							if(!wantExit())	break;
						}
				}
					
				for(i=0;i<250;i++)
				{
					while( CB_vtri_leo == 1 ||CB_Ha_Sau == 1 || CB_Cap_Thanh_Sau == 0)	
					{	
						Bam_thanh_laser_phai_cua_vao(14,-900,900,vitri - 15,2,150,30);
						if(!wantExit())	break;
					}
				}
//				chinh_lai_vi_tri_laser_phai(vitri - 15, 1000);
	}
	else if (TinHieu_ChuanBi_GapThang == 1) {
		
					for(i=0;i<250;i++)
					{
						while(lazeSauValue > 15)	
						{	
							Bam_thanh_laser_phai_cua_vao(25,-900,900,vitri ,2,150,30);
							vTaskDelay (1);
							if(!wantExit())	break;
						}
				}
				// PHUN TAY RA
				phun_tay_ra();
					for(i=0;i<250;i++)
				{
					while( CB_vtri_leo == 1 ||CB_Ha_Sau == 1 || CB_Cap_Thanh_Sau == 0)	
					{	
						
						Bam_thanh_laser_phai_cua_vao(14,-900,900,vitri,2,150,30);
						if(!wantExit())	break;
					}
				}
				robotStop(30); 	
				chinh_lai_vi_tri_laser_phai(vitri, 1000);
			}
	
	
	robotStop(0); 	
	
				
}
//********************************** vao rung mai 2 gap kfs ********************************************
void Vao_rung_mai_2_xanh(int vitri)
{
	Nang_nhanh();
	target_chan_truoc = Min_chan_truoc + 250;
	target_chan_sau = Min_chan_sau + 250;
	
	robotRunAngle(-900,55,900,0.9);
		for(i=0;i<250;i++)
					{
						while(lazeSauValue > 120)	
						{	
							vTaskDelay (1);
							if(!wantExit())	break;
						}
				}
	
		for(i=0;i<250;i++)
				{
					while(lazeSauValue > 60)	
					{	
						Bam_thanh_laser_phai(45,-900,900,vitri -15,3,-120,30);
						vTaskDelay (1);
						if(!wantExit())	break;
					}
				}	
					
	/////////
	for(i=0;i<250;i++)
				{
					while(lazeSauValue > 30)	
					{	
						Bam_thanh_laser_phai(35,-900,900,vitri - 15,3,-120,30);
						vTaskDelay (1);
						if(!wantExit())	break;
					}
				}	
					
//	
	if (TinHieu_ChuanBi_GapThang == 0) {
			for(i=0;i<250;i++)
				{
					while(lazeSauValue > 30)	
					{	
						Bam_thanh_laser_phai(20,-900,900,vitri - 15,3,-150,30);
						vTaskDelay (1);
						if(!wantExit())	break;
					}
				}	
			for(i=0;i<1550;i++)
						{
							while( CB_Ha_Sau == 1 || CB_Cap_Thanh_Sau == 0)	
							{	
								Bam_thanh_laser_phai(14,-900,900,vitri - 15,2,-150,30);
								if(!wantExit())	break;
								vTaskDelay (1);
							}
						}
	}
	else if (TinHieu_ChuanBi_GapThang == 1) {
				su_dung_chan_thuong(565);	
				for(i=0;i<250;i++)
				{
					while(lazeSauValue > 15 || (abs(bientrochansauValue - target_chan_sau) > 200))	
					{	
						Bam_thanh_laser_phai(20,-900,900,vitri,2,-150,30);
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
								Bam_thanh_laser_phai(14,-900,900,vitri,2,-150,30);
								if(!wantExit())	break;
								vTaskDelay (1);
							}
						}
						robotStop(30); 
						chinh_lai_vi_tri_laser_phai(vitri, 1000);
	}
	
	robotStop(0); 			
						
}	

//********************************** vao rung mai 3 gap kfs ********************************************
void Vao_rung_mai_3_xanh(int vitri)
{
			//// Do chan len 1 nua
	Nang_nhanh();
	target_chan_truoc = Min_chan_truoc + 250;
	target_chan_sau = Min_chan_sau + 250;
	
	robotRunAngle(-900,45,900,0.7);
	for(i=0;i<250;i++)
					{
						while(lazeSauValue > 115)	
						{	
							vTaskDelay (1);
							if(!wantExit())	break;
						}
				}

		for(i=0;i<250;i++)
					{
						while(lazeSauValue > 80)	
						{	
							Bam_thanh_laser_trai(40,-900,900,vitri + 15,4,150,30);
							vTaskDelay (1);
							if(!wantExit())	break;
						}
				}
					
		for(i=0;i<250;i++)
					{
						while(lazeSauValue > 30)	
						{	
							Bam_thanh_laser_trai(35,-900,900,vitri + 15,3,150,30);
							vTaskDelay (1);
							if(!wantExit())	break;
						}
				}
			
		su_dung_chan(710);

	if (TinHieu_ChuanBi_GapThang == 0) {
			for(i=0;i<250;i++)
					{
						while(lazeSauValue > 15)	
						{	
							Bam_thanh_laser_trai(25,-900,900,vitri + 15,2,150,30);
							vTaskDelay (1);
							if(!wantExit())	break;
						}
				}
					
				for(i=0;i<1550;i++)
							{
									while( CB_vtri_leo == 1 ||CB_Ha_Sau == 1 || CB_Cap_Thanh_Sau == 0)	
								{	
									Bam_thanh_laser_trai(14,-900,900,vitri + 15,2,150,30);
									vTaskDelay (1);
									if(!wantExit())	break;
									
								}
							}
					vTaskDelay (1000);
//				chinh_lai_vi_tri_laser_trai(vitri + 15, 1000);
	}
	else if (TinHieu_ChuanBi_GapThang == 1) {
			for(i=0;i<250;i++)
					{
						while(lazeSauValue > 15)	
						{	
							Bam_thanh_laser_trai(25,-900,900,vitri ,2,150,30);
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
									Bam_thanh_laser_trai(14,-900,900,vitri ,2,150,30);
									vTaskDelay (1);
									if(!wantExit())	break;
									
								}
							}
					robotStop(30); 
					chinh_lai_vi_tri_laser_trai(vitri, 1000);
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
		vat_can();
	if  (co_vat_can == 0 ) {
			Vao_rung_mai_1_xanh(vi_tri_cua_rung_xanh_1_lazer_phai_tay_41);
			}
			co_vat_can = 1;
		
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
		vat_can();
	if  (co_vat_can == 0 ) {
		Vao_rung_mai_3_xanh(vi_tri_cua_rung_xanh_3_lazer_trai_tay_41);
		
		co_vat_can = 1;
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////

//**************** Xuong_bac_200 ô 4********
void chuan_bi_gap_thang_xanh_4(void) {
		int vitri_tay41 = vitri_tay41_laser_trai_GapQua;
		su_dung_chan_thuong(565);

		if (da_lay_tay1 == 0 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
				for(i=0;i<1550;i++) {
						while( CB_Cap_Thanh_Sau == 0 || (abs(bientrochansauValue - target_chan_sau) > 300) )	
						{	
						if(lazeTraiValue > vitri_tay41)			robotRunAngle(-550,18,900,0.7);
						else																robotRunAngle(-900,12,900,0.7);
						vTaskDelay(1);
						if(!wantExit()) break;
									}
							}
					}
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
				for(i=0;i<1550;i++) {
						while( CB_Cap_Thanh_Sau == 0 ||(abs(bientrochansauValue - target_chan_sau) > 300))	
						{	
						if(lazeTraiValue > vitri_tay41)			robotRunAngle(-550,18,900,0.7);
						else																robotRunAngle(-900,12,900,0.7);
						vTaskDelay(1);
						if(!wantExit()) break;
									}
							}
					}

		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
				while( CB_Cap_Thanh_Sau == 0 || (abs(bientrochansauValue - target_chan_sau) > 300) )	{
						if(CB_ROI_2  == 0 && CB_ROI_4 == 0)	robotRunAngle(-1650,18,900,0.7);
						else																robotRunAngle(-900,12,900,0.7);
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
				if(CB_ROI_2  == 0 && CB_ROI_4 == 0)	robotRunAngle(-1650,18,900,0.7);
				else																robotRunAngle(-900,12,900,0.7);
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
			robotRunAngle(100,10,900,0.5);
					for(i=0;i<150;i++)
					{
						while(lazeTraiValue > vitri_tay41_laser_trai_GapQua)	
						{	
							vTaskDelay (1);
							if(!wantExit())	break;
						}
					}
			robotRunAngle(0,10,900,0.5);
			vTaskDelay (2000);
		}
	else if (da_lay_tay1 == 1 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
				su_dung_chan(565);	
				robotRunAngle(100,10,900,0.5);
					for(i=0;i<150;i++)
					{
						while(lazeTraiValue > vitri_tay41_laser_trai_GapQua)	
						{	
							vTaskDelay (1);
							if(!wantExit())	break;
						}
					}
				robotRunAngle(0,10,900,0.5);
				vTaskDelay (2000);
		}
	else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
			chinh_lai_vi_tri_laser_trai(vitri_tay41_laser_trai_GapQua , 200);
			su_dung_chan(510);
			// chay toi khi laser sau cham 1
			robotRunAngle(-900,15,900,0.7);
			for(i=0;i<1550;i++)
						{
							while(CB_Ha_Sau == 1 || (abs(bientrochansauValue - target_chan_sau) > 20) )	
							{	
								if(!wantExit())	break;
								vTaskDelay (1);
							}
						}
				robotStop(0); 
				su_dung_chan(565);	
				robotRunAngle(0,10,900,0.1);
				vTaskDelay(2500);
		}
	
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 0) {
				chinh_lai_vi_tri_laser_trai(vitri_tay41_laser_trai_GapQua , 200);
				su_dung_chan(510);
				robotRunAngle(-900,15,900,0.7);
				for(i=0;i<1550;i++)
					{
						while(CB_Ha_Sau == 1 || (abs(bientrochansauValue - target_chan_sau) > 20) )	
						{	
							if(!wantExit())	break;
							vTaskDelay (1);
						}
							}
					robotStop(0); 
					su_dung_chan(565);	
					robotRunAngle(0,10,900,0.1);
					vTaskDelay(2500);
			}
		robotStop(0); 
}


void chuan_bi_gap_trai_200_tren_1 (void ) {
	if (da_lay_tay1 == 0 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
			su_dung_chan_thuong(565);	
			for(i=0;i<1550;i++) {
						while( lazeSauValue > 1 )	
						{	
						if(lazePhaiValue > vitri_tay23_phai_laser_GapQua)			robotRunAngle(-1550,14,900,0.7);
						else																									robotRunAngle(-900,10,900,0.7);
						vTaskDelay(1);
						if(!wantExit()) break;
									}
							}
				robotRunAngle(1800,10,900,0.1);
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
						while( lazeSauValue > 1 )	
						{	
						if(lazePhaiValue > vitri_tay23_phai_laser_GapQua)			robotRunAngle(-1550,14,900,0.7);
						else																									robotRunAngle(-900,10,900,0.7);
						vTaskDelay(1);
						if(!wantExit()) break;
									}
							}
				robotRunAngle(1800,10,900,0.1);
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
			robotRunAngle(1900,10,900,0.5);
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
				robotRunAngle(1900,10,900,0.5);
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
			robotRunAngle(180,10,900,0.5);
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
				robotRunAngle(180,10,900,0.5);
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
			chinh_lai_vi_tri_laser_trai(vitri_tay41_laser_trai_GapQua , 200);
			su_dung_chan(510);
			// chay toi khi laser sau cham 1
			robotRunAngle(-900,15,900,0.7);
			for(i=0;i<1550;i++)
						{
							while(CB_Ha_Sau == 1 || (abs(bientrochansauValue - target_chan_sau) > 10) )	
							{	
								if(!wantExit())	break;
								vTaskDelay (1);
							}
						}
			robotStop(5); 
			
				su_dung_chan_thuong(565);	
				robotRunAngle(0,10,900,0.1);
				vTaskDelay(2500);
		}
	
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 0) {
				chinh_lai_vi_tri_laser_trai(vitri_tay41_laser_trai_GapQua , 200);
				su_dung_chan(510);
				robotRunAngle(-900,15,900,0.7);
				for(i=0;i<1550;i++)
					{
						while(CB_Ha_Sau == 1 || (abs(bientrochansauValue - target_chan_sau) > 10) )	
						{	
							if(!wantExit())	break;
							vTaskDelay (1);
						}
							}
					robotStop(5); 
				
					su_dung_chan_thuong(565);	
					robotRunAngle(0,10,900,0.1);
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
					else																robotRunAngle(-900,10,900,0.7);
					vTaskDelay(1);
					if(!wantExit()) break;
								}
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
					else																robotRunAngle(-900,10,900,0.7);
					vTaskDelay(1);
					if(!wantExit()) break;
								}
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
					robotRunAngle(1800,10,900,0.5);
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
					robotRunAngle(1800,10,900,0.8);
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
					while(CB_Ha_Sau == 0 || (abs(bientrochansauValue - target_chan_sau) > 20)) {
						if(CB_ROI_2  == 0 && CB_ROI_4 == 0)	robotRunAngle(-1350,14,900,0.7);
						else																robotRunAngle(-900,10,900,0.7);
						vTaskDelay(1);
						if(!wantExit()) break;
									}
						// chay toi roi thi di ngang qua trai
						robotRunAngle(1700,7,900,0.7);
						while (CB_ROI_4  == 0 )	 {
							vTaskDelay(1);
							if(!wantExit()) break;
								}
							robotStop(0);
			}
		
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
					ha_sat_xuong();
					while(CB_Ha_Sau == 0 || (abs(bientrochansauValue - target_chan_sau) > 20)) {
						if(CB_ROI_2  == 0 && CB_ROI_4 == 0)	robotRunAngle(-1350,14,900,0.7);
						else																robotRunAngle(-900,10,900,0.7);
						vTaskDelay(1);
						if(!wantExit()) break;
									}
						// chay toi roi thi di ngang qua trai
						robotRunAngle(1700,8,900,0.7);
						while (CB_ROI_4  == 0 )	 {
							vTaskDelay(1);
							if(!wantExit()) break;
								}
							robotStop(0);
			}
	
			//// gap duoi lan 3
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
					ha_sat_xuong();
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
					robotRunAngle(0,10,900,0.8);
					for(i=0;i<150;i++)
					{
						while(CB_ROI_1 == 0 ||  (abs(bientrochansauValue - target_chan_sau) > 20))	
						{	
							vTaskDelay (1);
							if(!wantExit())	break;
						}
					}
			}
		
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
					ha_sat_xuong();
					robotRunAngle(0,10,900,0.8);
					for(i=0;i<150;i++)
					{
						while(CB_ROI_1 == 0 || (abs(bientrochansauValue - target_chan_sau) > 20))	
						{	
							vTaskDelay (1);
							if(!wantExit())	break;
						}
					}
			}
			//// gap duoi lan 3
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {		
					ha_sat_xuong();
					while( CB_Ha_Sau == 0 || (abs(bientrochansauValue - target_chan_sau) > 20)) {
					if(CB_ROI_3  == 0 && CB_ROI_1 == 0)	robotRunAngle(-550,14,900,0.7);
					else																robotRunAngle(-900,10,900,0.7);
					vTaskDelay(1);
					if(!wantExit()) break;
						}
					// chay toi roi thi di ngang qua phai
					robotRunAngle(100,8,900,0.7);
					while (CB_ROI_1  == 0 )	 {
						vTaskDelay(1);
						if(!wantExit()) break;
						}
				}
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 0) {		
					ha_sat_xuong();
					while( CB_Ha_Sau == 0 || (abs(bientrochansauValue - target_chan_sau) > 20)) {
					if(CB_ROI_3  == 0 && CB_ROI_1 == 0)	robotRunAngle(-550,14,900,0.7);
					else																robotRunAngle(-900,10,900,0.7);
					vTaskDelay(1);
					if(!wantExit()) break;
						}
					// chay toi roi thi di ngang qua phai
					robotRunAngle(100,8,900,0.7);
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
		
		robotRunAngle(-900,20,900,0.8);
		for(i=0;i<250;i++)	
	{
		while(abs(bientrochansauValue - target_chan_sau) > 100)	{vTaskDelay(1); if(!wantExit())	break;}
	}		
	
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
			vTaskDelay (3000);
			gap_ngang_2_ben_san_xanh();
			chuan_bi_gap_phai_200_duoi_ko_thanh();
		}
	else if (TinHieu_ChuanBi_GapThang == 1) {
			kiem_tra_huong_quay_tay_gap_phia_truoc();
			vTaskDelay (3000);
			di_tren_buc_khong_thanh_2_ben();
				}
}


///////////////////////////////////////////////////////////////////////////////////////////////

/// ****** leo bac 200 o id  5 san xanh
void Leo_bac_200_xanh_5(void) {	
		int vitri = 153;
		int vitri_tay41 = vitri_tay41_laser_trai_GapQua;
		
		Leo_bac_200(-900, 900);
		Nang_nhanh();
		target_chan_truoc = Min_chan_truoc + 250;
		target_chan_sau = Min_chan_sau + 250;
		
		// KHONG CO TIN HIEU GAP
		if (TinHieu_ChuanBi_GapThang == 0 && TinHieu_ChuanBi_GapTrai == 0 && TinHieu_ChuanBi_GapPhai == 0 && TinHieu_QuaPhai == 0 && TinHieu_QuaTrai == 0) {
				robotRunAngle(-900,20,900,0.7);
				for(i=0;i<1550;i++)
						{
					while(CB_Ha_Sau == 1 ||  CB_Cap_Thanh_Sau == 0 || (abs(bientrochansauValue - target_chan_sau) > 20) )	
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
		
		robotStop(0); 			
}

void chuan_bi_gap_thang_xanh_7(void) {
		int vitri_tay41 = vitri_tay41_laser_trai_GapQua + 6;
		kiem_tra_huong_quay_tay_gap_phia_truoc();
		su_dung_chan(265);
		
	// chinh lai vi tri cho tay gap
		if (da_lay_tay1 == 0 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
					while(CB_Ha_Sau == 0 || (abs(bientrochansauValue - target_chan_sau) > 20)) 
					{	
						if(lazeTraiValue > vitri_tay41)			robotRunAngle(-450,18,900,0.7);
						else																robotRunAngle(-900,15,900,0.7);
						vTaskDelay(1);
						if(!wantExit()) break;
									}
			}
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
					while(CB_Ha_Sau == 0 || (abs(bientrochansauValue - target_chan_sau) > 20)) 
					{	
						if(lazeTraiValue > vitri_tay41)			robotRunAngle(-450,18,900,0.7);
						else																robotRunAngle(-900,15,900,0.7);
						vTaskDelay(1);
						if(!wantExit()) break;
									}
			}

		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
				while( CB_Ha_Sau == 0 || (abs(bientrochansauValue - target_chan_sau) > 20)) {
				if(CB_ROI_2  == 0 && CB_ROI_4 == 0)	robotRunAngle(-1450,18,900,0.7);
				else																robotRunAngle(-900,15,900,0.7);
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
				if(CB_ROI_2  == 0 && CB_ROI_4 == 0)	robotRunAngle(-1450,18,900,0.7);
				else																robotRunAngle(-900,15,900,0.7);
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


// CHUAN BI GAP PHAI XANH 7 VA 10
void chuan_bi_gap_phai_200_tren_7_10 (void ) {
	if (da_lay_tay1 == 0 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
			su_dung_chan(565);
				for(i=0;i<250;i++)	
			{
				while(abs(bientrochansauValue - target_chan_sau) > 100)	{vTaskDelay(1); if(!wantExit())	break;}
			}
			robotRunAngle(0,10,900,0.5);
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
			robotRunAngle(0,10,900,0.5);
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
			
			robotRunAngle(-900,10,900,0.8);
			vTaskDelay (10500);
			robotRunAngle(0,10,900,0.5);
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
			
			robotRunAngle(-900,10,900,0.8);
			vTaskDelay (10500);
			robotRunAngle(0,10,900,0.5);
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
			robotRunAngle(-900,20,900,0.7);
			for(i=0;i<1550;i++)
					{
							while( CB_Ha_Sau == 0 || (abs(bientrochansauValue - target_chan_sau) > 10)	)	

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
	
			// CO TIN HIEU GAP THANG
	else if (TinHieu_ChuanBi_GapThang == 1) {
				chuan_bi_gap_thang_xanh_7();
				}
		// CO TIN HIEU GAP PHAI
	else if (TinHieu_ChuanBi_GapPhai == 1) {
					chuan_bi_gap_phai_200_tren_7_10();
			}
	robotStop(0); 	
		}

//**************** Xuong_bac_200 xanh ô 9 **************		
void chuan_bi_gap_thang_xanh_9 (void) {
		int vitri_tay23 = vitri_tay23_phai_laser_GapQua;
		kiem_tra_huong_quay_tay_gap_phia_truoc();
		su_dung_chan(265);
	
			// chinh lai vi tri cho tay gap
		if (da_lay_tay1 == 0 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
				while(CB_Ha_Sau == 0|| (abs(bientrochansauValue - target_chan_sau) > 10)) {
				if(CB_ROI_3  == 0 && CB_ROI_1 == 0)	robotRunAngle(-450,18,900,0.7);
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
				while(CB_Ha_Sau == 0 || (abs(bientrochansauValue - target_chan_sau) > 10)) {
				if(CB_ROI_3  == 0 && CB_ROI_1 == 0)	robotRunAngle(-450,18,900,0.7);
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

		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
					while( CB_Ha_Sau == 0 || (abs(bientrochansauValue - target_chan_sau) > 30)) 
					{	
					if(lazePhaiValue > vitri_tay23)			robotRunAngle(-1450,18,900,0.7);
					else																robotRunAngle(-900,12,900,0.7);
					vTaskDelay(1);
					if(!wantExit()) break; }
			}
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 0) {
					while( CB_Ha_Sau == 0 || (abs(bientrochansauValue - target_chan_sau) > 30) ) 
					{	
					if(lazePhaiValue > vitri_tay23)			robotRunAngle(-1450,18,900,0.7);
					else																robotRunAngle(-900,12,900,0.7);
					vTaskDelay(1);
					if(!wantExit()) break; }
					}
		robotStop(0);
	}


void chuan_bi_gap_trai_200_tren (void ) {
	if (da_lay_tay1 == 0 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
			su_dung_chan_thuong(565);
			robotRunAngle(-1350,10,900,0.9);
			for(i=0;i<150;i++)
					{
				while(lazeTruocValue < 28 || (abs(bientrochansauValue - target_chan_sau) > 300))	
						{	
							vTaskDelay (1);
							if(!wantExit())	break;
						}
					}
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
		}
	else if (da_lay_tay1 == 1 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
			su_dung_chan_thuong(565);
			robotRunAngle(-1350,10,900,0.9);
			for(i=0;i<150;i++)
					{
				while(lazeTruocValue < 28 || (abs(bientrochansauValue - target_chan_sau) > 300))	
						{	
							vTaskDelay (1);
							if(!wantExit())	break;
						}
					}
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
		}
	else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
				su_dung_chan_thuong(565);
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
		int vitri_tay23 = vitri_tay23_phai_laser_GapQua + 4;
		Xuong_bac_200(-900, 900);
		
		if (TinHieu_ChuanBi_GapThang == 0 && TinHieu_ChuanBi_GapTrai == 0 && TinHieu_ChuanBi_GapPhai == 0 && TinHieu_QuaTrai == 0 ) {
				// chay toi khi mat cam bien sau
				su_dung_chan(265);
				robotRunAngle(-900,20,900,0.8);
				for(i=0;i<250;i++)
							{
							while( CB_Ha_Sau == 0 || (abs(bientrochansauValue - target_chan_sau) > 10) ) 
								{	vTaskDelay (1); if(!wantExit())	break;
							}
						}
				robotRunAngle(-900,10,900,0.7);
				for(i=0;i<250;i++)
				{
						while(CB_vtri_leo == 0 || CB_Ha_Sau == 0|| (abs(bientrochansauValue - target_chan_sau) > 10) ){	
						vTaskDelay (1);
						if(!wantExit())	break;
						}
					}
						
				robotStop(0);
				}				
	
		else if (TinHieu_ChuanBi_GapThang == 1) {
					chuan_bi_gap_thang_xanh_9();
					}
		else if (TinHieu_ChuanBi_GapTrai == 1) {
					chuan_bi_gap_trai_200_tren();
				}
			robotStop(0);
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
				robotRunAngle(-900,20,900,0.8);
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
		else if (TinHieu_ChuanBi_GapTrai == 1) {
					chuan_bi_gap_trai_200_tren();
				}
			robotStop(0);
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
				robotRunAngle(-900,15,900,0.7);
				for(i=0;i<1550;i++)
						{
							while(CB_Ha_Sau == 1  || (abs(bientrochansauValue - target_chan_sau) > 20))	
							{	
								vTaskDelay (1);
								if(!wantExit())	break;
							}
						}

				robotRunAngle(-900,8,900,0.7);
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
				
				robotStop(0); 					
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
				robotRunAngle(-900,15,900,0.7);
				for(i=0;i<1550;i++)
						{
							while(CB_Ha_Sau == 1  || (abs(bientrochansauValue - target_chan_sau) > 20))	
							{	
								vTaskDelay (1);
								if(!wantExit())	break;
							}
						}

				robotRunAngle(-900,8,900,0.7);
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
		robotStop(0); 
		
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
				robotRunAngle(-900,15,900,0.8);	
				for(i=0;i<1550;i++)
						{
							while(CB_Ha_Sau == 1 )	
							{	
								if(!wantExit())	break;
								vTaskDelay (1);
							}
						}
			robotRunAngle(-900,8,900,0.8);
			for(i=0;i<1550;i++)
						{
							while(CB_Ha_Sau == 1  || CB_Cap_Thanh_Sau == 0 )	
								
							{	
								if(!wantExit())	break;
								vTaskDelay (1);
							}
						}
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
			// CO LENH GAP TRAI
			else if (TinHieu_ChuanBi_GapTrai == 1 ) {
						chuan_bi_gap_trai_200_duoi_5();
			}
			
			robotStop(0); 			
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
			robotRunAngle(-900,15,900,0.7);
			for(i=0;i<1550;i++)
					{
							while(CB_Ha_Sau == 0 )	
						{	
							if(!wantExit())	break;
							vTaskDelay (1);
						}
					}
			robotRunAngle(-900,8,900,0.7);
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
			robotStop(0); 	
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
			robotRunAngle(-900,15,900,0.7);
			for(i=0;i<1550;i++)
					{
							while(CB_Ha_Sau == 0 )	
						{	
							if(!wantExit())	break;
							vTaskDelay (1);
						}
					}
			robotRunAngle(-900,8,900,0.7);
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
			robotStop(0); 	
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
				robotRunAngle(-900,15,900,0.8);
				for(i=0;i<250;i++)
							{
							while( CB_Ha_Sau == 0 ) 
								{	vTaskDelay (1); if(!wantExit())	break;
							}
						}
				robotRunAngle(-900,8,900,0.7);
				for(i=0;i<250;i++)
				{
						while(CB_vtri_leo == 0 || CB_Ha_Sau == 0 ){	
						vTaskDelay (1);
						if(!wantExit())	break;
						}
					}
				robotStop(0);
				}				
		else if (TinHieu_ChuanBi_GapThang == 1) {
					chuan_bi_gap_thang_xanh_9();
					}
		else if (TinHieu_ChuanBi_GapTrai == 1) {
					chuan_bi_gap_trai_200_tren();
				}
			robotStop(0);
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
				robotRunAngle(-900,12,900,0.8);
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
		robotStop(0); 	
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
				robotRunAngle(-900,12,900,0.8);
				for(i=0;i<1550;i++)
						{
								while(CB_Ha_Sau == 0 )	
							{	
								if(!wantExit())	break;
								vTaskDelay (1);
							}
						}
				robotStop(0);
			}
		else if (TinHieu_ChuanBi_GapTrai == 1) {
					chuan_bi_gap_trai_200_tren();
				}
			robotStop(0);
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
			robotRunAngle(-900,15,900,0.7);
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
		
		robotStop(0); 					
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
				robotRunAngle(-900,15,900,0.8);
				for(i=0;i<1550;i++)
							{
								while(CB_Ha_Sau == 1 )	
									
								{	
									if(!wantExit())	break;
									vTaskDelay (1);
								}
							}
					robotRunAngle(-900,8,900,0.8);
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
				robotRunAngle(-900,14,900,0.9);
				for(i=0;i<250;i++)
						{
								while(CB_Ha_Sau == 0 )	

							{	
								vTaskDelay (1);
								if(!wantExit())	break;
							}
						}
				robotRunAngle(-900,8,900,0.9);
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
			else if (TinHieu_ChuanBi_GapPhai == 1 ) {
				chuan_bi_gap_phai_200_duoi_ko_thanh();
				}
				robotStop(0); 	
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
				robotRunAngle(-900,12,900,0.7);
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
		
		robotStop(0); 			
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
				robotRunAngle(-900,15,900,0.7);
				for(i=0;i<1550;i++)
						{
								while( CB_Ha_Sau == 0 	)	
							{	
								if(!wantExit())	break;
								vTaskDelay (1);
							}
						}
				robotRunAngle(-900,8,900,0.7);
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
					chuan_bi_gap_thang_xanh_7();
					}
			// CO TIN HIEU GAP PHAI
		else if (TinHieu_ChuanBi_GapPhai == 1) {
						chuan_bi_gap_phai_200_tren_7_10();
				}
		robotStop(0); 		
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
			robotRunAngle(-900,14,900,0.7);
			for(i=0;i<1550;i++)
					{
							while(CB_Ha_Sau == 0)	
					
						{	
							if(!wantExit())	break;
							vTaskDelay (1);
						}
					}
			robotRunAngle(-900,8,900,0.7);
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
			robotStop(0); 	
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
				robotRunAngle(-900,14,900,0.8);
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
		robotStop(0); 		
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
				robotRunAngle(-900,14,900,0.8);
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
			robotStop(0);
}

void dung_cho_khoi_r1_tren_MD (int Angle, int Robot_Angle) {
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
			dung_cho_khoi_r1_tren_MD(-900, 900);
}

void dung_cho_khoi_r1_duoi_xanh(void) {
			dung_cho_khoi_r1_duoi_MD(-900, 900);
}


void dung_cho_khoi_r1_tren_do(void) {
			dung_cho_khoi_r1_tren_MD(900, -900);
}

void dung_cho_khoi_r1_duoi_do(void) {
			dung_cho_khoi_r1_duoi_MD(900, -900);
}

void bao_hieu_check_r1_ngang (void) {
		 bat_bien_check_r1_ngang = 1;
			cho_r1_ben_Canh = 1;
}

void dung_cho_khoi_r1_ben_canh (void) {
			
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
		action_table[0][2][5]  = Lay_ben_trai_bac_200_duoi_xanh_ko_thanh;
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
            if (pkt.move == 0 && pkt.action == 1)
            {
                if (next_pkt.move == 1 && next_pkt.action == 4)
                {
                    gap_truoc_dac_biet = 1; 
                }
            }
						
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

        vTaskDelay(200); 
    }

    has_active_block = 0;
}

//	void Run_All_Blocks_From_Queue_san_xanh(void)
//	{
//		Packet_t pkt;
//		Packet_t next_pkt;

//		if (count_data_uart4 == 0)
//				return;

//		while (count_data_uart4 > 0)
//		{
//				Check_Next1_Block_For_Prepare();
//				if (!Queue_Pop(&pkt)) break;

//				if (Queue_Peek(&next_pkt)) 
//				{
//						if (pkt.move == 2 && pkt.action == 10 && pkt.id_block == 2) 
//						{
//								if (next_pkt.move == 2 && next_pkt.action == 10 && next_pkt.id_block == 1) 
//								{
//										chay_ngang_qua_o1_xanh = 1; // Bat flag cho ben trai
//								}
//						}
//						
//						else if (pkt.move == 3 && pkt.action == 10 && pkt.id_block == 2)
//						{
//								if (next_pkt.move == 3 && next_pkt.action == 10 && next_pkt.id_block == 3)
//								{
//										chay_ngang_qua_o3_xanh = 1; // Bat flag cho ben phai
//								}
//						}
//				}

//				if (pkt.move < MAX_MOVE && pkt.action < MAX_ACTION && pkt.id_block < MAX_ID)
//				{
//						action_table[pkt.move][pkt.action][pkt.id_block]();
//				}

//				vTaskDelay(200); 
//		}

//		has_active_block = 0;
//	}
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
	kiem_tra_qua_tay_nao_xuong_rung(); // ham kiem tra co qua tay nao de dat
	
	Nang_cuc_nhanh();
	target_chan_truoc = 300;
	target_chan_sau = 300;
	
	for(i=0;i<150;i++)		
	{
		while(abs(bientrochansauValue - target_chan_sau) > 50)	{vTaskDelay(1); if(!wantExit())	break;}
	}
	
	chinh_lai_vi_tri_laser_phai_custom(190, 1000, 5, 58, 4);
	robotStop(50);
//	
		robotRunAngle(-900,45,900,0.5);
		for(i=0;i<550;i++)	
	{	
			while(lazeTraiValue > 270)	
			{	
				vTaskDelay(5); 
				if(!wantExit())	break;
			}
	}	
	vTaskDelay(5000); 
	
		for(i=0;i<550;i++)	
	{	
			while(lazeTraiValue < 270)	
			{	

				vTaskDelay(5); 
				if(!wantExit())	break;
			}
	}		
	
		vTaskDelay(4600);
//		robotStop(20);
			
		robotRunAngle(-900,18,900,0.8);
		for(i=0;i<550;i++)	
		{	
				while(lazeSauValue > 40)	
				{	
					vTaskDelay(1); 
					if(!wantExit())	break;
				}
		}		
		robotStop(30);
		robotRunAngle(-900,15,900,0.8);
		for(i=0;i<550;i++)	
		{	
				while(lazeSauValue > 6)	
				{	
					vTaskDelay(1); 
					if(!wantExit())	break;
				}
		}
		robotStop(0);
		robotRunAngle(0,30,900,0.8);
		for(i=0;i<550;i++)	
		{	
			while(lazePhaiValue < 226)	
			{	
				vTaskDelay(1); 
				if(!wantExit())	break;
			}
		}
		
		robotRunAngle(0,45,900,0.8);
		for(i=0;i<550;i++)	
		{	
			while(lazePhaiValue < 400)	
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
					while(lazeTraiValue > 280)	
					{	
						Bam_laser_sau(40,0,900, vitri + 15, 3, -120, 10);
						vTaskDelay(1); 
						if(!wantExit())	break;
					}
			}
		for(i=0;i<550;i++)	
			{	
					while(lazeTraiValue > 220)	
					{	
						Bam_laser_sau(25,0,900, vitri + 15, 3, -120, 10);
						vTaskDelay(5); 
						if(!wantExit())	break;
					}
			}
				
			
			for(i=0;i<550;i++)	
			{	
					while(lazeTraiValue > 192)	
					{	
						Bam_laser_sau(10,0,900, vitri + 15, 1, -100, 10);
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
			su_dung_chan(710);
			for(i=0;i<150;i++)		
			{
				while(abs(bientrochansauValue - target_chan_sau) > 30)	{vTaskDelay(1); if(!wantExit())	break;}
			}
	}
	
	
//	// ************** che do thang nhanh ***********
	if (mode_cay_diem == 2 ) {
		
		robotRunAngle(470,45,900,0.5);
		for(i=0;i<550;i++)	
		{	
			while(lazeTraiValue > 310)	
			{	
				vTaskDelay(1); 
				if(!wantExit())	break;
			}
		}	
		
			for(i=0;i<550;i++)	
			{	
					while(lazeTraiValue > 270)	
					{	
						Bam_laser_sau(40,0,900, vitri + 70, 3, -150, 10);
						vTaskDelay(5); 
						if(!wantExit())	break;
					}
			}	
		for(i=0;i<550;i++)	
			{	
					while(lazeTraiValue > 220)	
					{	
						Bam_laser_sau(25,0,900, vitri + 70, 3, -150, 10);
						vTaskDelay(1); 
						if(!wantExit())	break;
					}
			}	
			
			for(i=0;i<550;i++)	
			{	
					while(lazeTraiValue > 184)	
					{	
						Bam_laser_sau(10,0,900, vitri + 70, 2, -150, 10);
						su_dung_chan_thuong(512);
						vTaskDelay(1); 
						if(!wantExit())	break;
					}
			}	
		}
			robotStop(0);
}

void test_vi_tri(void) {
		kiem_tra_so_qua_tren_tay();
		kiem_tra_qua_tay_nao_xuong_rung(); // ham kiem tra co qua tay nao de dat
		su_dung_chan(500);
		Tay1_len;
}

void test_dat_hop (void) {
		id_dat_hop =  id_dat_hop + 1;
		vTaskDelay(6000);
}

bool da_dat_tay_1 = false;
bool da_dat_tay_2 = false;
bool da_dat_tay_3 = false;
bool da_dat_tay_4 = false;


void dat_qua_tay_1_2_xanh(void) {
    if ((CB_kep_1_2 == 0 || CB_kep_1_1 == 0) && !da_dat_tay_1) {
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
				
        Kep_phai_1_ra;
				vTaskDelay(1000);
        da_dat_tay_1 = true; 
    }
    else if ((CB_kep_2_2 == 0 || CB_kep_2_1 == 0) && !da_dat_tay_2) {
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
				vTaskDelay(1000);
        da_dat_tay_2 = true; 
    }
    
    vTaskDelay(2000);
    
		led_bao_hieu_on;
		for(i=0;i<1000;i++)	
				{
				while(Quang_tro2 > 120)	{	
				vTaskDelay (1);
				if(!wantExit())	break;
					}
				}
		led_bao_hieu_off;
				
    // Ðua tay v? Home
    speed_tay_gat1 = 250;
    target_tay_gat1 = vitri_tay1home;
    speed_tay_gat2 = 250;
    target_tay_gat2 = vitri_tay2home;
    
    for(i=0; i<50; i++) { 
        while(abs(bientrodaytay1Value - target_tay_gat1) > 20 || abs(bientrodaytay2Value - target_tay_gat2) > 20) {
            vTaskDelay(1); if(!wantExit()) break;
        }
    }
}
void dat_qua_tay_4_3_xanh(void) {
    
    if ( ( CB_kep_4_2 == 0 || CB_kep_4_1 == 0 ) && !da_dat_tay_4) {
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
			
        Kep_phai_4_ra;
				vTaskDelay(1000);
        da_dat_tay_4 = true; //
    }
    
    else if ((CB_kep_3_2 == 0 || CB_kep_3_1 == 0 ) && !da_dat_tay_3) {
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
        da_dat_tay_3 = true; // Ðánh d?u dã d?t xong tay 3
    }

    vTaskDelay(2000);
		
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
    speed_tay_gat2 = 250;
    target_tay_gat2 = vitri_tay2home;
    
    for(i=0; i<50; i++) { 
        while(abs(bientrodaytay1Value - target_tay_gat1) > 10 || abs(bientrodaytay2Value - target_tay_gat2) > 10) {
            vTaskDelay(1); if(!wantExit()) break;
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
		Tay1_xuong;
		Tay2_xuong;
		Kep_phai_1_vao;
		Kep_phai_2_vao;
		Kep_phai_3_vao;
		Kep_phai_4_vao;	
}


void dat_hop_vao_o_tang2 (void) {
		if (tin_hieu_dat_hop_3_4 == 1 ) {
				if (CB_kep_4_2 == 0 || CB_kep_4_1 == 0) {
					speed_tay_gat2 = 150;
					target_tay_gat2 = 410;
					for(i=0; i<550; i++) 
					{ 
					while(abs(bientrodaytay2Value - target_tay_gat2) > 10) { vTaskDelay(1); if(!wantExit()) break; }
          }
					dat_hop4_2(512, 320, 5, 4);
					vTaskDelay(3000); 
					speed_tay_gat2 = 250;
					target_tay_gat2 = vitri_tay2home ;
				}
				else if (CB_kep_3_2 == 0 || CB_kep_3_1 == 0) {
					speed_tay_gat1 = 150;
					target_tay_gat1 = 410;
					for(i=0; i<550; i++) 
					{ 
					while(abs(bientrodaytay1Value - target_tay_gat1) > 10) { vTaskDelay(1); if(!wantExit()) break; }
          }
					dat_hop1_3(512, 325, 5, 3);
					vTaskDelay(3000); 
					speed_tay_gat1 = 250;
					target_tay_gat1 = vitri_tay1home ;
					}	
				
		}
		else if (tin_hieu_dat_hop_1_2 == 1 ) {
				if (CB_kep_1_2 == 0 || CB_kep_1_1 == 0) {
						speed_tay_gat1 = 150;
						target_tay_gat1 = 480;
						for(i=0; i<550; i++) 
						{ 
						while(abs(bientrodaytay1Value - target_tay_gat1) > 10) { vTaskDelay(1); if(!wantExit()) break; }
						}
						dat_hop1_3(512, 560, 5, 1);
						vTaskDelay(3000); 
						speed_tay_gat1 = 250;
						target_tay_gat1 = vitri_tay1home ;
				}
				else if (CB_kep_2_2 == 0 || CB_kep_2_1 == 0 ) {
						speed_tay_gat2 = 150;
						target_tay_gat2 = 480;
						for(i=0; i<550; i++) 
						{ 
						while(abs(bientrodaytay2Value - target_tay_gat2) > 10) { vTaskDelay(1); if(!wantExit()) break; }
						}
						dat_hop4_2(512, 560, 5, 2);
						vTaskDelay(3000); 
						speed_tay_gat2 = 250;
						target_tay_gat2 = vitri_tay1home ;
				}
		}
		for(i=0;i<50;i++)	{ 
				while(abs(bientrodaytay1Value - target_tay_gat1) > (20) || abs(bientrodaytay2Value - target_tay_gat2) > 20 )	
				{vTaskDelay(1); if(!wantExit())	break;}
				}
				speed_tay_gat1 = 200;
				target_tay_gat1 = vitri_tay1home;
				speed_tay_gat2 = 200;
				target_tay_gat2 = vitri_tay2home;
				Tay1_xuong;
				Tay2_xuong;
				tin_hieu_dat_hop_3_4 = 0;
				tin_hieu_dat_hop_1_2 = 0;
				
}

void nghieng_tay_k_dat_tang2(void) {
		speed_tay_gat2 = 100;
		target_tay_gat2 = vitri_tay2home - 45;
		speed_tay_gat1 = 100;
		target_tay_gat1 = 385;
	}

void chuan_bi_dat_hop_tang3 (void) {
		if (tin_hieu_dat_hop_3_4 == 1 && tay_4_co_qua == 1 ) {
				speed_tay_gat1 = 100;
        target_tay_gat1 = vitri_tay1home + 45;
				Tay2_len;
				for(i=0;i<50;i++)	{ 
									while(CB_xilanh_tay_2 == 1 )	{vTaskDelay(1); if(!wantExit())	break;}
							}
						}
		
		else if (tin_hieu_dat_hop_1_2 == 1 && tay_1_co_qua == 1 ) {
				speed_tay_gat2 = 100;
        target_tay_gat2 = vitri_tay2home - 45;
				Tay1_len;
				for(i=0;i<50;i++)	{ 
									while(CB_xilanh_tay_1 == 1 )	{vTaskDelay(1); if(!wantExit())	break;}
							}
						}

		
		else if (tin_hieu_dat_hop_1_2 == 1 && tay_2_co_qua == 1 ) {
				speed_tay_gat1 = 100;
        target_tay_gat1 = vitri_tay1home - 45;
				Tay2_len;
				for(i=0;i<50;i++)	{ 
									while(CB_xilanh_tay_2 == 1 )	{vTaskDelay(1); if(!wantExit())	break;}
							}
						}

		
		else if (tin_hieu_dat_hop_3_4 == 1 && tay_3_co_qua == 1) {
				speed_tay_gat2 = 100;
        target_tay_gat2 = vitri_tay2home + 45;
				Tay1_len;
				for(i=0;i<50;i++)	{ 
									while(CB_xilanh_tay_1 == 1 )	{vTaskDelay(1); if(!wantExit())	break;}
							}
						}
		}

void kiem_tra_so_qua_tren_tay(void) {
    int dem = 0;

    // Ki?m tra tay 1
    if (CB_kep_1_2 == 0  || CB_kep_1_1 == 0) {
        tay_1_co_qua = 1;
        dem++;
    } else {
        tay_1_co_qua = 0;
    }

    // Ki?m tra tay 2
    if (CB_kep_2_1 == 0 || CB_kep_2_2 == 0 ) {
        tay_2_co_qua = 1;
        dem++;
    } else {
        tay_2_co_qua = 0;
    }

    // Ki?m tra tay 3
    if (CB_kep_3_1 == 0 || CB_kep_3_2 == 0) {
        tay_3_co_qua = 1;
        dem++;
    } else {
        tay_3_co_qua = 0;
    }

    // Ki?m tra tay 4
    if (CB_kep_4_2 == 0 || CB_kep_4_1 == 0) {
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
				su_dung_chan(512);
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
        chuan_bi_dat_hop_tang3();
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
        su_dung_chan(512);
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
				su_dung_chan(512);
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
		Tay1_xuong;
		Tay2_xuong;
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
		while(quangTroValue > 220)	{	
		vTaskDelay (1);
		if(!wantExit())	break;
					}
	}
	led_bao_hieu_off;
	
	Tay_kep_mo;
	
	vTaskDelay (6000);
	
	led_bao_hieu_on;
	for(i=0;i<1000;i++)	
	{
		while(quangTroValue < 220)	{	
		vTaskDelay (1);
		if(!wantExit())	break;
		}
	}
	vTaskDelay (11000);
	led_bao_hieu_off;
	
	
	da_lay_vk = 1;
		
	if (da_lay_vk == 1 ) {
		speed_tay_gat1 = 250;
		target_tay_gat1 = vitri_tay1home;
	
		speed_tay_gat2 = 250;
		target_tay_gat2 = vitri_tay2home;
		
		kiem_tra_vat_truoc_khi_bd(122, 1000);
		da_lay_vk = 2;
		}		
}

void check_dat_hop_tren_T2_xanh(void) {
    
    if (check_dat_hop_T2 == 1) {
				
        dat_hop_vao_o_tang2(); 
    } 
    else {
//				chinh_lai_vi_tri_laser_sau(vi_tri_dat_hop_3_tay41_xanh - 10, 100, 4, 25);
				chinh_lai_vi_tri_laser_truoc_xanh(vi_tri_dat_hop_3_tay41_xanh_truoc + 10, 100, 4, 30);
				robotStop(0);
				vTaskDelay (20000);
				led_bao_hieu_on;
				while(lazePhaiValue > 270)	{
							vTaskDelay (1); 
							if(!wantExit())	break;
						}
				led_bao_hieu_off;
				chinh_lai_vi_tri_laser_trai(177, 1000);
				robotStop(0);
//				chinh_lai_vi_tri_laser_sau(vi_tri_dat_hop_2_tay41_xanh , 100, 4, 25);
				chinh_lai_vi_tri_laser_truoc_xanh(vi_tri_dat_hop_2_tay41_xanh_truoc , 100, 4, 30);
				robotStop(0);
				dat_hop_vao_o_tang2(); 
    }
		robotStop(0);
		
}

void test_dat (void ) {
		DatKFSxanh(35);
		robotRotate(890,0.2, 0);
				while(robotFixAngle()){
					vTaskDelay (1); 
					if(!wantExit())	break;
				}
				robotStop(0);
				
				chinh_lai_vi_tri_laser_trai(177, 1000);
				robotStop(0);
				chinh_lai_vi_tri_laser_truoc_xanh(vi_tri_dat_hop_2_tay41_xanh_truoc , 100, 4, 20);
				robotStop(0);
				check_dat_hop_tren_T2_xanh();
				
				robotStop(0);

}

void tudonghoantoan(void) {
	
		Kiem_Tra_Ket_Qua_Gap();
	
		Xuat_Phat_Lay_Vu_Khi_Xanh(169, -1670, 198);
    mo_vk_san_xanh();
    
    if (da_lay_vk == 2) {    
        Run_All_Blocks_From_Queue_san_xanh();
    }
		if (hoan_thanh_chay_rung == 1 ) DatKFSxanh(35),hoan_thanh_chay_rung = 2 ;
		
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
				
				chinh_lai_vi_tri_laser_trai(177, 1000);
				robotStop(0);
//				chinh_lai_vi_tri_laser_sau(vi_tri_dat_hop_2_tay41_xanh, 100, 4, 20);
				chinh_lai_vi_tri_laser_truoc_xanh(vi_tri_dat_hop_2_tay41_xanh_truoc, 100, 4, 20);
				robotStop(0);
				check_dat_hop_tren_T2_xanh();
				
				robotStop(0);
				
				su_dung_chan_thuong(710);
				robotRunAngle(1800,12,900, 0.5);
				RESET_ENCODER(); 
				while(abs(ENCODER_FR()) + abs(ENCODER_FL()) < 2000)	{vTaskDelay (5); if(!wantExit())	break;}
				robotStop(0);
//				chinh_lai_vi_tri_laser_sau(14, 100, 5, 30);
				hoan_thanh_chay_rung = 3 ;
			}
		
			robotStop(0);
			
//				/// ******* //////
		if (hoan_thanh_chay_rung == 3 && mode_cay_diem == 1)  {
				tu_dong_dat_tang2_xanh(); // danh cay diem 2
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
						su_dung_chan_thuong(710);
						chinh_lai_vi_tri_laser_truoc_xanh(vi_tri_dat_hop_1_tay41_xanh_truoc , 100, 4, 20);
						be_len_dat_xanh_1_qua_tren_3();
			}
				hoan_thanh_chay_rung = 5 ;}
		
		robotStop(0);
}



void retry_zone_2(void) {
		retry_co_qua_tren_tay();
		Run_All_Blocks_From_Queue_san_xanh();

		if (hoan_thanh_chay_rung == 1 ) DatKFSxanh(35),hoan_thanh_chay_rung = 2 ;
		
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
				
				chinh_lai_vi_tri_laser_trai(176, 1000);
				robotStop(0);
//				chinh_lai_vi_tri_laser_sau(vi_tri_dat_hop_2_tay41_xanh, 100, 4, 20);
				chinh_lai_vi_tri_laser_truoc_xanh(vi_tri_dat_hop_2_tay41_xanh_truoc , 1000, 4, 20);
				robotStop(0);
				check_dat_hop_tren_T2_xanh();
				
				robotStop(0);
				
				su_dung_chan_thuong(710);
				robotRunAngle(1800,12,900, 0.5);
				RESET_ENCODER(); 
				while(abs(ENCODER_FR()) + abs(ENCODER_FL()) < 2000)	{vTaskDelay (5); if(!wantExit())	break;}
				robotStop(0);
				hoan_thanh_chay_rung = 3 ;
			}
		
			robotStop(0);
			
//				/// ******* //////
		if (hoan_thanh_chay_rung == 3 && mode_cay_diem == 1)  {
				tu_dong_dat_tang2_xanh(); // danh cay diem 2
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
						su_dung_chan_thuong(710);
//						chinh_lai_vi_tri_laser_sau(7, 100, 5, 30);
						chinh_lai_vi_tri_laser_truoc_xanh(vi_tri_dat_hop_1_tay41_xanh_truoc , 1000, 4, 20);
						be_len_dat_xanh_1_qua_tren_3();
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
		
		robotRunAngle(0,45,0,1.5);
		for(i=0;i<550;i++)	
			{	
					while(lazeSauValue < 240)	
					{	
						vTaskDelay(1); 
						if(!wantExit())	break;
					}
			}
		
		/// chay toi 1 doan roi xoay
		robotRunAngle(100,30,900,1.5);
	
		while(_robotIMUAngle < 860)	
		{
			vTaskDelay (1); 
			if(!wantExit())	break;
		}
		
		for(i=0;i<550;i++)	
			{	
					while(lazeTraiValue > 250)	
					{	
						Bam_laser_sau(20,0,900, vitri , 3, -150, 10);
						vTaskDelay(5); 
						if(!wantExit())	break;
					}
			}
				
			if (nhom_A) {
			for(i=0;i<550;i++)	
			{	
					while(lazeTraiValue > 185)	
					{	
						Bam_laser_sau(10,0,900, vitri , 1, -120, 10);
						su_dung_chan_cham(500);
						vTaskDelay(1); 
						if(!wantExit())	break;
					}
				}	
			}
			else if (nhom_B) {
			for(i=0;i<550;i++)	
			{	
					while(lazeTraiValue > 198)	
					{	
						Bam_laser_sau(10,0,900, vitri , 1, -120, 10);
						su_dung_chan_cham(500);
						vTaskDelay(1); 
						if(!wantExit())	break;
					}
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
		robotRunAngle(800,30,0,1.5);
		vTaskDelay(10000); 
		
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
						Bam_laser_sau(20,0,900, vitri , 3, -250, 10);
						vTaskDelay(5); 
						if(!wantExit())	break;
					}
			}
				
			for(i=0;i<550;i++)	
			{	
					while(lazeTraiValue > 185)	
					{	
						Bam_laser_sau(10,0,900, vitri , 1, -150, 10);
						su_dung_chan_cham(500);
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
		robotRunAngle(800,30,0,1.5);
		vTaskDelay(17000); 
		
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
						Bam_laser_sau(20,0,900, vitri , 3, -250, 10);
						vTaskDelay(5); 
						if(!wantExit())	break;
					}
			}
				
			for(i=0;i<550;i++)	
			{	
					while(lazeTraiValue > 185)	
					{	
						Bam_laser_sau(10,0,900, vitri , 1, -150, 10);
						su_dung_chan_cham(500);
						vTaskDelay(1); 
						if(!wantExit())	break;
					}
				}	
			robotStop(0);	
}



void dat_hop4_2(int do_cao_chan, int goc_tay, int ha_chan, int chontay)
{
    int do_cao_chan_hien_tai = do_cao_chan;
    int timeout = 3000;   
    int t = 0;
	
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
            if (do_cao_chan_hien_tai < 400)
                do_cao_chan_hien_tai = 400;

            su_dung_chan(do_cao_chan_hien_tai);
            while (abs(bientrochansauValue - target_chan_sau) > 10)
            {
                vTaskDelay(1);
								check_time++; 
                if (!wantExit()) break;
            }
            break; 
        }
        if (!wantExit()) break;
				}
			}

    speed_tay_gat2 = 150;
    target_tay_gat2 = goc_tay;
		for(i=0; i<550; i++) 
				{ 
        while(abs(bientrodaytay2Value - target_tay_gat2) > 8) { vTaskDelay(1); if(!wantExit()) break; }
          }
    if (chontay == 4)
    {
        Kep_phai_4_ra;
    }
    else if (chontay == 2)
    {
        Kep_phai_2_ra;
    }
}

// tay 3 345, tay 1 550
void dat_hop1_3(int do_cao_chan, int goc_tay, int ha_chan, int chontay)
{
    int do_cao_chan_hien_tai = do_cao_chan;
    int timeout = 8000;
    int t = 0;

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
            if (do_cao_chan_hien_tai < 400)
                do_cao_chan_hien_tai = 400;

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
    speed_tay_gat1 = 150;
    target_tay_gat1 = goc_tay;
    for (i = 0; i < 550; i++)
    {
        while (abs(bientrodaytay1Value - target_tay_gat1) > 10)
        {
            vTaskDelay(1);
            if (!wantExit()) break;
        }
    }
    if (chontay == 1)
    {
        Kep_phai_1_ra;
    }
    else if (chontay == 3)
    {
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

    if      (id == 1 && nhom_A) { retry_zone_3_o_1(50);  }
    else if (id == 1 && nhom_B) { retry_zone_3_o_1(5);   }
    else if (id == 2 && nhom_A) { retry_zone_3_o_2(106); }
    else if (id == 2 && nhom_B) { retry_zone_3_o_2(59);  }
    else if (id == 3 && nhom_A) { retry_zone_3_o_3(156); }
    else if (id == 3 && nhom_B) { retry_zone_3_o_3(115); }
    else { return; }

    if  (id_dat_hop <= 3) { 
				tu_dong_dat_tang2_xanh();
				robotRunAngle(1800,12,900, 0.5);
				vTaskDelay(5000);
				robotStop(0);
//				chinh_lai_vi_tri_laser_sau(35, 100, 5, 25);
				su_dung_chan_thuong(710);
				robotStop(0);
				quyet_dinh_dat_hop_tang3();
				kiem_tra_so_qua_tren_tay();
				if ( so_qua_tren_tay > 0  ) {
						tu_dong_dat_tang2_xanh();
				}
				}
    else if (id_dat_hop >= 4) { 
				su_dung_chan_thuong(710);
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
		while(abs(lazeSauValue - vitri) > 1)	{
			dieuchinh = lazeSauValue - vitri;
			speed = custom_smooth_speed(dieuchinh, 5, 35);
			
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
				chinh_lai_vi_tri_laser_phai_zone3_do(205, 200, 4, 35);
			}
		else if (nhat_dat_hop == 2 ) {
				chinh_lai_vi_tri_laser_phai_zone3_do(253, 200, 4, 35);
			}
		else if (nhat_dat_hop == 3 ) {
				chinh_lai_vi_tri_laser_phai_zone3_do(299, 200, 4, 35);
			}
		else if (nhat_dat_hop == 4|| nhat_dat_hop == 5 || nhat_dat_hop == 6) {
				chinh_lai_vi_tri_laser_sau_zone3(24, 1000);
				chinh_lai_vi_tri_laser_phai_zone3_do(195, 200, 4, 35);
			}

			robotStop(0);
		if (nhat_dat_hop == 1|| nhat_dat_hop == 2 || nhat_dat_hop == 3) {
							
			su_dung_chan_thuong(510);
			chinh_lai_vi_tri_laser_sau_zone3(8, 1000);
			robotStop(0);

			if (da_lay_tay1 == 0 && da_lay_tay2 == 0) {
				speed_tay_gat2 = 150;
				target_tay_gat2 = 400;
				for(i=0; i<550; i++) 
					{ 
				while(abs(bientrodaytay2Value - target_tay_gat2) > 15) { vTaskDelay(1); if(!wantExit()) break; }
					}
				dat_hop4_2(510, 330,5, 4);
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
				dat_hop1_3(510, 560,5, 1);
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
				chinh_lai_vi_tri_laser_sau_zone3(30, 1000);
				chinh_lai_vi_tri_laser_phai_zone3_do(195, 200, 4, 35);
				robotStop(0);
				robotRotate(-890,0.5,0);
				while(robotFixAngle()){
					vTaskDelay (1); 
					if(!wantExit())	break;
					}
				robotStop(0);
				su_dung_chan(710);
				robotStop(0);
				quyet_dinh_dat_hop_tang3();
				robotStop(0);
				robotRotate(10, 0.5, 0);
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
		if (da_lay_tay1 == 0 && da_lay_tay2 == 0) {
        Kep_phai_4_ra;
        speed_tay_gat2 = 250;
        target_tay_gat2 = 180;
    }

    robotRunAngle(1800, 45, 0, 0.5);
    RESET_ENCODER(); 
		while(abs(ENCODER_FR()) + abs(ENCODER_FL()) < 22000)	{vTaskDelay (5); if(!wantExit())	break;}
		robotStop(30);
		
    led_bao_hieu_on;
    /// check tam hop
    for(i=0; i<5000; i++) {   
        run_align_center();
    }
		led_bao_hieu_off;
    
    robotRunAngle(1800, 30, 0, 0.5);
    for(i=0; i<550; i++) {   
        while(lazeSauValue > 100) {   
            vTaskDelay(1); 
            if(!wantExit()) break;
        }
    }   
		led_bao_hieu_on;
    for(i=0; i<5000; i++) {   
        run_align_center();
    }
		led_bao_hieu_off;
    
    robotRunAngle(1800, 25, 0, 0.5);
    for(i=0; i<550; i++) {   
        while(lazeSauValue > 55) {   
            vTaskDelay(1); 
            if(!wantExit()) break;
        }
    }  
		robotRunAngle(1800, 15, 0, 0.5);
    for(i=0; i<550; i++) {   
        while(lazeSauValue > 25) {   
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
    
    // chi tracking hop 
    if (da_lay_tay1 == 0 && da_lay_tay2 == 0) {
            Ktra_vtri_kep4(); 
						Ktra_vtri_kep4();
            speed_tay_gat2 = 250;
            target_tay_gat2 = Min_tay_gat2 + 14;
            for(i=0; i<550; i++) { 
                while(abs(bientrodaytay2Value - target_tay_gat2)> 20 ) {
                    vTaskDelay(1); 
                    if(!wantExit()) break;
																			}
																	}
            vTaskDelay(1000);
            Kep_phai_4_vao;
            vTaskDelay(1500);
						su_dung_chan(460);
						robotStop(0);
						robotRunAngle(0, 18, 0, 0.5);
						RESET_ENCODER(); 
						while(abs(ENCODER_FR()) + abs(ENCODER_FL()) < 2500)	{
								vTaskDelay (1); if(!wantExit())	break;
						}
						robotStop(0);
            speed_tay_gat2 = 250;
            target_tay_gat2 = vitri_tay2home; 
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
				Tay2_xuong;
        chinh_lai_vi_tri_laser_phai_zone3_do(162, 500, 5, 35);
        chinh_lai_vi_tri_laser_sau_zone3(210, 1000);
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
            while(lazeTraiValue > 350) {   
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
        robotRunAngle(1800, 20, 0, 0.5);
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
				su_dung_chan(460);
				robotStop(0);
				robotRunAngle(0, 18, 0, 0.5);
				RESET_ENCODER(); 
				while(abs(ENCODER_FR()) + abs(ENCODER_FL()) < 3000)	{vTaskDelay (5); if(!wantExit())	break;}
				robotStop(0);
				speed_tay_gat2 = 250;
				target_tay_gat2 = vitri_tay2home; 
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
//            chinh_lai_vi_tri_laser_sau(vi_tri_dat_hop_1_tay41_xanh, 100, 5, 20);
					chinh_lai_vi_tri_laser_truoc_xanh(vi_tri_dat_hop_1_tay41_xanh_truoc, 100, 5, 20);
            robotStop(0);
            chinh_lai_vi_tri_laser_trai(177, 1000);
        } 
        else if (robot_position == 2) {
//            chinh_lai_vi_tri_laser_sau(vi_tri_dat_hop_2_tay41_xanh, 100, 5, 20);
						chinh_lai_vi_tri_laser_truoc_xanh(vi_tri_dat_hop_2_tay41_xanh_truoc, 100, 5, 20);
            robotStop(0);
            chinh_lai_vi_tri_laser_trai(177, 1000);
        } 
        else if (robot_position == 3) {
//            chinh_lai_vi_tri_laser_sau(vi_tri_dat_hop_3_tay41_xanh, 100, 5, 20);
						chinh_lai_vi_tri_laser_truoc_xanh(vi_tri_dat_hop_3_tay41_xanh_truoc, 100, 5, 20);
            robotStop(0);
            chinh_lai_vi_tri_laser_trai(177, 1000);
        }
    } 
    else if (tay_2_co_qua || tay_3_co_qua) {
        if (robot_position == 1) {
//            chinh_lai_vi_tri_laser_sau(vi_tri_dat_hop_1_tay23_xanh, 100, 5, 20);
						chinh_lai_vi_tri_laser_truoc_xanh(vi_tri_dat_hop_1_tay23_xanh_truoc, 100, 5, 20);
            robotStop(0);
            chinh_lai_vi_tri_laser_trai(192, 1000); /// trg hop tay 3 vi trí 1
        } 
        else if (robot_position == 2) {
//            chinh_lai_vi_tri_laser_sau(vi_tri_dat_hop_2_tay23_xanh, 100, 5, 20);
						chinh_lai_vi_tri_laser_truoc_xanh(vi_tri_dat_hop_2_tay23_xanh_truoc, 100, 5, 20);
            robotStop(0);
            chinh_lai_vi_tri_laser_trai(177, 1000);
        } 
        else if (robot_position == 3) {
//            chinh_lai_vi_tri_laser_sau(vi_tri_dat_hop_3_tay23_xanh, 100, 5, 20);
						chinh_lai_vi_tri_laser_truoc_xanh(vi_tri_dat_hop_3_tay23_xanh_truoc, 100, 5, 20);
            robotStop(0);
            chinh_lai_vi_tri_laser_trai(177, 1000);
        }
    }
		
			robotStop(0);
			// do chan len dat
			su_dung_chan(512);
			for(i=0;i<250;i++)	{
				while(abs(bientrochansauValue - target_chan_sau) > 10)	{ vTaskDelay(1); if(!wantExit())	break;}
					}		
			dat_hop_vao_o_tang2();	
			
}

void quyet_dinh_dat_o_nao (void){
		kiem_tra_so_qua_tren_tay();
		if (so_qua_tren_tay > 2) { // neu con 2 qua tren tay
				be_len_dat_xanh();
				}
		else {
				be_len_dat_xanh_1_qua_tren_3();
		
				}
}

void bat_dau_chay_xanh (void) {
    if (Start == 0 && mode_chay_rung == 1) {
				led_bao_hieu_off;
        tudonghoantoan();
    }
		else if (Start == 0 && mode_chay_rung == 0 && mode_nhat_hop == 0 && mode_retry_zone_3 == 0) {
				led_bao_hieu_off;
        Xuat_Phat_Lay_Vu_Khi_Xanh(169, -1670, 198);
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
	
