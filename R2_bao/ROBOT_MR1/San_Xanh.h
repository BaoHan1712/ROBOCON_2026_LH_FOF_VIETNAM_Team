int	KC_Vu_khi;

extern int Vi_tri;
extern int da_lay_tay4;
extern int TinHieu_ChuanBi_GapThang;
extern int TinHieu_ChuanBi_GapTrai ;
extern int TinHieu_ChuanBi_GapPhai;
void ha_chan_dat_tang2_do (void);

void run_align_center(void);
void kiem_tra_so_qua_tren_tay(void);
void tu_dong_dat_tang2_xanh(void);
void dat_hop4_2(int do_cao_chan, int goc_tay, int ha_chan, int chontay);
void dat_hop1_3(int do_cao_chan, int goc_tay, int ha_chan, int chontay);
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
	
				robotRunAngle(-150 - vu_khi*2,35,3,0.3);
				for(i=0;i<100;i++)
				{
					while(lazePhaiValue < vu_khi - 20)	
					{
						if(!wantExit())	break;
					}
				}
				Nang_cuc_nhanh();
				target_chan_truoc = 610, target_chan_sau =605;
				for(i=0;i<50;i++)		
				{
				while(bientrochantruocValue < 470)	{
				Bam_thanh_laser_phai(30,0,0,vu_khi,1,150,15);
				vTaskDelay(1); 
				if(!wantExit())	break;}
				}
				
				for(i=0;i<250;i++)
				{
					while(lazeTruocValue > 16)	
					{	
	
						Bam_thanh_laser_phai(25,0,0,vu_khi,1,100,15);//robotRun(-450,10);
						
						if(!wantExit())	break;
					}
				}
			

				for(i=0;i<100;i++)
				{
					while(HT_1 == 0 && HT_2 == 0)	
					{				
						if(lazeTruocValue < 14)	Tay_kep_xuong;
						Bam_thanh_laser_phai(7,0,0,vu_khi,1,50,15);//robotRun(-450,10);
						if(!wantExit())	break;
					}
				}		
			
				robotStop(50);
						
				for(i=0;i<500;i++)
				{
					while(CB_tay_kep_vk_T == 1 || CB_tay_kep_vk_P == 1)	
					{	
						if	(CB_tay_kep_vk_P == 1) robotRun(-870,6);
						else if 	(CB_tay_kep_vk_T == 1) robotRun(870,6);
						else		robotStop(0);				
						vTaskDelay (2);
						if(!wantExit())	break;
					}
				}	
				
				Tay_kep_dong;
				
				robotRun(0,6);
				
				vTaskDelay (2500);
				
				robotStop(30);

				KC_Vu_khi = lazePhaiValue;
				
//				vTaskDelay (1000);
				
				for(i=0;i<500;i++)
				{
					while(CB_kep == 1 || (CB_tay_kep_vk_T == 1 && CB_tay_kep_vk_P == 1))	
					{	
	
						while(CB_tay_kep_vk_T == 1 || CB_tay_kep_vk_P == 1)	
						{	
							if	(CB_tay_kep_vk_P == 1) robotRun(-870,5);
							else if 	(CB_tay_kep_vk_T == 1) robotRun(870,5);
							else		robotStop(0);				
							vTaskDelay (2);
							if(!wantExit())	break;
						}
					}						
		
				}
				robotStop(0);
				
				
				speed_chan_sau =30;
				speed_chan_truoc = 70;
				
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
				
				robotRun(goc_ve - ((KC_Vu_khi - vu_khi)*10),30);
				robotRotate(-900,-1.2,0);
				
				Nang_cuc_nhanh();
		
				while(_robotIMUAngle >-700)	
				{
					vTaskDelay (2); 
					if(!wantExit())	break;
					if(_robotIMUAngle < -450)		target_chan_truoc = 265, target_chan_sau = 265;
				}
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
				
				vTaskDelay(2000);
				
				chinh_lai_vi_tri_VK(vitri, 1000);
				
				robotStop(0);
				
				robotRunAngle(900,9,-900,0.7);
				
				vTaskDelay(3000);
				
				robotStop(0);
				
				speed_chan_sau =20;
				speed_chan_truoc = 45;
				target_chan_truoc = 255, target_chan_sau = 255;
				
			}

//******************** xoay dau detect xem co robot phia truoc hay khong ********************************************
void Xoay_dau_truoc_cua_xanh_1(void)
{
	Nang_cuc_nhanh();
	target_chan_truoc = 255;
	target_chan_sau = 255;

	
	vTaskDelay(2000);
	
	Kep_phai_4_ra;

	
	robotRunAngle(-1550,20,900,2);
//				
				while(_robotIMUAngle < 895)	
				{
					vTaskDelay (5); 
					if(!wantExit())	break;
				}
				
	robotStop(0);
				
	if (TinHieu_ChuanBi_GapThang == 1) {
			chinh_lai_vi_tri_laser_phai_custom(vi_tri_cua_rung_xanh_1_lazer_phai_tay_41 , 1000, 4 , 65 );
	}
	else if (TinHieu_ChuanBi_GapThang == 0) {
			chinh_lai_vi_tri_laser_phai_custom(vi_tri_cua_rung_xanh_1_lazer_phai_tay_41 - 15, 1000, 5 , 65);
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

	target_chan_truoc = 255;
	target_chan_sau = 255;

	
	vTaskDelay(2000);
	Kep_phai_4_ra;

	
	robotRunAngle(-1650,20,900,2);
//				
				while(_robotIMUAngle < 895)	
				{
					vTaskDelay (5); 
					if(!wantExit())	break;
				}
	robotStop(0);
	if (TinHieu_ChuanBi_GapThang == 0) {
			chinh_lai_vi_tri_laser_phai_custom(vi_tri_cua_rung_xanh_2_lazer_phai_tay_41 - 15 , 1000, 5, 65);
	}
	else if (TinHieu_ChuanBi_GapThang == 1) {
			chinh_lai_vi_tri_laser_phai_custom(vi_tri_cua_rung_xanh_2_lazer_phai_tay_41  , 1000, 4, 65);
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

	target_chan_truoc = 255;
	target_chan_sau = 255;

	
	vTaskDelay(2000);
	
	Kep_phai_4_ra;

	
	robotRunAngle(-1030,15,900,3.5);
//				
				while(_robotIMUAngle < 895)	
				{
					vTaskDelay (5); 
					if(!wantExit())	break;
				}
				
	robotStop(0);
	if (TinHieu_ChuanBi_GapThang == 1) {
			chinh_lai_vi_tri_laser_phai_custom(vi_tri_cua_rung_xanh_3_lazer_phai_tay_41  , 1000, 4, 65);
	}
	else if (TinHieu_ChuanBi_GapThang == 0) {
			chinh_lai_vi_tri_laser_phai_custom(vi_tri_cua_rung_xanh_3_lazer_phai_tay_41 - 15 , 1000, 5, 65);
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
	Nang_cuc_nhanh();
	target_chan_truoc = Min_chan_truoc + 250;
	target_chan_sau = Min_chan_sau + 250;
	
	robotRunAngle(-900,38,900,0.9);
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
			while(abs(bientrochansauValue - target_chan_sau) > 20)
									{	
			Bam_thanh_laser_phai_cua_vao(28,-900,900,vitri,2,150,30);
			if(!wantExit())	break;
						}
		}
		
	robotRunAngle(-900,25,900,0.9);
		for(i=0;i<250;i++)
					{
						while(lazeSauValue > 60)	
						{	
							vTaskDelay (1);
							if(!wantExit())	break;
						}
				}
				
		// chuan bi tay xuong truoc
	if (TinHieu_ChuanBi_GapThang == 1) {
				speed_tay_gat2 = 250;
				target_tay_gat2 = vitri_tay2home - 220;		
		}
	
			su_dung_chan(700);
		
	if (TinHieu_ChuanBi_GapThang == 0) {
			for(i=0;i<250;i++)
					{
						while(lazeSauValue > 15)	
						{	
							Bam_thanh_laser_phai_cua_vao(18,-900,900,vitri - 15,2,150,30);
							vTaskDelay (1);
							if(!wantExit())	break;
						}
				}
					
				for(i=0;i<250;i++)
				{
					while( CB_vtri_leo == 1 ||CB_Ha_Sau == 1 || CB_Cap_Thanh_Sau == 0)	
					{	
						Bam_thanh_laser_phai_cua_vao(8,-900,900,vitri - 15,2,150,30);
						if(!wantExit())	break;
					}
				}
				chinh_lai_vi_tri_laser_phai(vitri - 15, 1000);
	}
	else if (TinHieu_ChuanBi_GapThang == 1) {
					for(i=0;i<250;i++)
					{
						while(lazeSauValue > 15)	
						{	
							Bam_thanh_laser_phai_cua_vao(18,-900,900,vitri ,2,150,30);
							vTaskDelay (1);
							if(!wantExit())	break;
						}
				}
					
					for(i=0;i<250;i++)
				{
					while( CB_vtri_leo == 1 ||CB_Ha_Sau == 1 || CB_Cap_Thanh_Sau == 0)	
					{	
						
						Bam_thanh_laser_phai_cua_vao(8,-900,900,vitri,2,150,30);
						if(!wantExit())	break;
					}
				}
			
				chinh_lai_vi_tri_laser_phai(vitri, 1000);
			}
	
	
	robotStop(0); 	
	
				
}
//********************************** vao rung mai 2 gap kfs ********************************************
void Vao_rung_mai_2_xanh(int vitri)
{
	Nang_cuc_nhanh();
	target_chan_truoc = Min_chan_truoc + 250;
	target_chan_sau = Min_chan_sau + 250;
	
	robotRunAngle(-900,40,900,0.9);
		for(i=0;i<250;i++)
					{
						while(lazeSauValue > 115)	
						{	
							vTaskDelay (1);
							if(!wantExit())	break;
						}
				}
		
	robotRunAngle(-900,35,900,0.9);
		for(i=0;i<250;i++)
					{
						while(lazeSauValue > 60)	
						{	
							vTaskDelay (1);
							if(!wantExit())	break;
						}
				}
					
	/////////
	robotRunAngle(-900,25,900,0.5);
	for(i=0;i<250;i++)
				{
					while(lazeSauValue > 30)	
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
//	
	if (TinHieu_ChuanBi_GapThang == 0) {
			for(i=0;i<250;i++)
				{
					while(lazeSauValue > 30)	
					{	
						Bam_thanh_laser_phai(18,-900,900,vitri - 15,2,-350,30);
						vTaskDelay (1);
						if(!wantExit())	break;
					}
			}	
			for(i=0;i<1550;i++)
						{
							while( CB_Ha_Sau == 1 || CB_Cap_Thanh_Sau == 0)	
							{	
								Bam_thanh_laser_phai(8,-900,900,vitri - 10,2,-350,30);
								if(!wantExit())	break;
								vTaskDelay (1);
							}
						}
			chinh_lai_vi_tri_laser_phai(vitri - 15, 1000);
	}
	else if (TinHieu_ChuanBi_GapThang == 1) {
				for(i=0;i<250;i++)
				{
					while(lazeSauValue > 15)	
					{	
						Bam_thanh_laser_phai(18,-900,900,vitri,2,-350,30);
						vTaskDelay (1);
						if(!wantExit())	break;
					}
			}		
				for(i=0;i<1550;i++)
						{
							while( CB_Ha_Sau == 1 || CB_Cap_Thanh_Sau == 0)	
							{	
								Bam_thanh_laser_phai(8,-900,900,vitri,2,-350,30);
								if(!wantExit())	break;
								vTaskDelay (1);
							}
						}
						su_dung_chan(565);	
						chinh_lai_vi_tri_laser_phai(vitri, 1000);
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
	
	robotRunAngle(-900,38,900,0.7);
		for(i=0;i<250;i++)
					{
						while(lazeSauValue > 115)	
						{	
							vTaskDelay (1);
							if(!wantExit())	break;
						}
				}
		
		robotRunAngle(-900,30,900,0.7);
		for(i=0;i<250;i++)
					{
						while(lazeSauValue > 80)	
						{	
							vTaskDelay (1);
							if(!wantExit())	break;
						}
				}
		for(i=0;i<250;i++)
					{
						while(lazeSauValue > 30)	
						{	
							Bam_thanh_laser_trai(25,-900,900,vitri + 15,2,150,30);
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

		su_dung_chan(700);

	if (TinHieu_ChuanBi_GapThang == 0) {
			for(i=0;i<250;i++)
					{
						while(lazeSauValue > 15)	
						{	
							Bam_thanh_laser_trai(18,-900,900,vitri + 15,2,150,30);
							vTaskDelay (1);
							if(!wantExit())	break;
						}
				}
					
				for(i=0;i<1550;i++)
							{
									while( CB_vtri_leo == 1 ||CB_Ha_Sau == 1 || CB_Cap_Thanh_Sau == 0)	
								{	
									Bam_thanh_laser_trai(8,-900,900,vitri + 15,2,150,30);
									vTaskDelay (1);
									if(!wantExit())	break;
									
								}
							}
					vTaskDelay (1000);
				chinh_lai_vi_tri_laser_trai(vitri + 15, 1000);
	}
	else if (TinHieu_ChuanBi_GapThang == 1) {
			for(i=0;i<250;i++)
					{
						while(lazeSauValue > 15)	
						{	
							Bam_thanh_laser_trai(18,-900,900,vitri ,2,150,30);
							vTaskDelay (1);
							if(!wantExit())	break;
						}
				}
					
			for(i=0;i<1550;i++)
							{
									while( CB_vtri_leo == 1 ||CB_Ha_Sau == 1 || CB_Cap_Thanh_Sau == 0)	
								{	
									Bam_thanh_laser_trai(8,-900,900,vitri ,2,150,30);
									vTaskDelay (1);
									if(!wantExit())	break;
									
								}
							}
					vTaskDelay (1000);
					chinh_lai_vi_tri_laser_trai(vitri, 1000);
	}

	robotStop(0); 	
				
}
// ham nhan tin hieu khong co vat can
void vat_can (void) {
	while(co_vat_can == 1)	{	
				vTaskDelay (1);
			if(!wantExit())	break;
				}
		

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
		kiem_tra_huong_quay_tay_gap_phia_truoc();
		su_dung_chan(510);
					
//		KT_Ha_Tay = 1;
	// chinh lai vi tri cho tay gap
		if (da_lay_tay1 == 0 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
				for(i=0;i<1550;i++) {
						while( CB_Cap_Thanh_Sau == 0 || (abs(bientrochansauValue - target_chan_sau) > 10) )	
						{	
						if(lazeTraiValue > vitri_tay41)			robotRunAngle(-650,15,900,0.7);
						else																robotRunAngle(-900,15,900,0.7);
						vTaskDelay(1);
						if(!wantExit()) break;
									}
							}
				chinh_lai_vi_tri_laser_trai(vitri_tay41, 1000);
			}
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
				for(i=0;i<1550;i++) {
						while( CB_Cap_Thanh_Sau == 0 ||(abs(bientrochansauValue - target_chan_sau) > 10))	
						{	
						if(lazeTraiValue > vitri_tay41)			robotRunAngle(-650,15,900,0.7);
						else																robotRunAngle(-900,15,900,0.7);
						vTaskDelay(1);
						if(!wantExit()) break;
									}
							}
				chinh_lai_vi_tri_laser_trai(vitri_tay41, 1000);
			}

		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
				while( CB_Cap_Thanh_Sau == 0 || (abs(bientrochansauValue - target_chan_sau) > 10) )	{
						if(CB_ROI_2  == 0 && CB_ROI_4 == 0)	robotRunAngle(-1150,15,900,0.7);
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
				while( CB_Cap_Thanh_Sau == 0 || (abs(bientrochansauValue - target_chan_sau) > 10) )	{
				if(CB_ROI_2  == 0 && CB_ROI_4 == 0)	robotRunAngle(-1150,15,900,0.7);
				else																robotRunAngle(-900,15,900,0.7);
				vTaskDelay(1);
				if(!wantExit()) break; }
				// chay toi roi thi di ngang qua trai
				robotRunAngle(1800,10,900,0.7);
				while (CB_ROI_2  == 0 )	 {
					vTaskDelay(1);
					if(!wantExit()) break;
							}
				}
			su_dung_chan(565);
			robotRunAngle(-900,10,900,0.7);
			vTaskDelay(1500);
}	


void chuan_bi_gap_phai_200_tren_4 (void ) {
//	KT_Ha_Tay_phai = 1;
	if (da_lay_tay1 == 0 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
			chinh_lai_vi_tri_laser_trai(vitri_tay41_laser_trai_GapQua, 200);
			robotRunAngle(-900,10,900,0.5);
					for(i=0;i<150;i++)
					{
						while(lazeSauValue > 31)	
						{	
							vTaskDelay (1);
							if(!wantExit())	break;
						}
					}
						robotStop(0);
			
				su_dung_chan(565);	
				robotRunAngle(0,8,900,0.7);
					for(i=0;i<250;i++)	
				{
					while(abs(bientrochansauValue - target_chan_sau) > 10)	{vTaskDelay(1); if(!wantExit())	break;}
				}		
				vTaskDelay(3000);
		}
	else if (da_lay_tay1 == 1 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
			chinh_lai_vi_tri_laser_trai(vitri_tay41_laser_trai_GapQua , 200);
		
			robotRunAngle(-900,10,900,0.5);
					for(i=0;i<150;i++)
					{
						while(lazeSauValue > 31)	
						{	
							vTaskDelay (1);
							if(!wantExit())	break;
						}
					}
						robotStop(0);
				su_dung_chan(565);
				robotRunAngle(0,8,900,0.7);
					for(i=0;i<250;i++)	
				{
					while(abs(bientrochansauValue - target_chan_sau) > 10)	{vTaskDelay(1); if(!wantExit())	break;}
				}		
				vTaskDelay(3000);
		}
	else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
			chinh_lai_vi_tri_laser_trai(vitri_tay41_laser_trai_GapQua , 200);
			su_dung_chan(510);
			// chay toi khi laser sau cham 1
			robotRunAngle(-900,15,900,0.5);
			for(i=0;i<1550;i++)
						{
							while(CB_Ha_Sau == 1 || (abs(bientrochansauValue - target_chan_sau) > 10) )	
							{	
								if(!wantExit())	break;
								vTaskDelay (1);
							}
						}
			robotStop(5); 
			
				su_dung_chan(565);
				robotRunAngle(0,7,900,0.1);
					for(i=0;i<250;i++)	
				{
					while(abs(bientrochansauValue - target_chan_sau) > 10)	{vTaskDelay(1); if(!wantExit())	break;}
				}		
				vTaskDelay(3000);
		}
	
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 0) {
				chinh_lai_vi_tri_laser_trai(vitri_tay41_laser_trai_GapQua , 200);
				su_dung_chan(510);
				// chay toi khi laser sau cham 1
				robotRunAngle(-900,15,900,0.5);
				for(i=0;i<1550;i++)
					{
						while(CB_Ha_Sau == 1 || (abs(bientrochansauValue - target_chan_sau) > 10) )	
						{	
							if(!wantExit())	break;
							vTaskDelay (1);
						}
							}
					robotStop(5); 
				
					su_dung_chan(565);
					robotRunAngle(0,7,900,0.1);
						for(i=0;i<250;i++)	
					{
						while(abs(bientrochansauValue - target_chan_sau) > 10)	{vTaskDelay(1); if(!wantExit())	break;}
					}		
					vTaskDelay(3000);
		}
		robotStop(0); 
}

void chuan_bi_gap_trai_200_duoi_5 (void ) {

	if (da_lay_tay1 == 0 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
				// chuan bi xoay truoc sang trai
					ha_sat_xuong();
					while(HT_3 == 0 && HT_4 == 0 || (abs(bientrochansauValue - target_chan_sau) > 10))	 {
					if(CB_ROI_2  == 0 && CB_ROI_4 == 0)	robotRunAngle(-1150,18,900,0.7);
					else																robotRunAngle(-900,15,900,0.7);
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
					while(HT_3 == 0 && HT_4 == 0 || (abs(bientrochansauValue - target_chan_sau) > 10))	 {
					if(CB_ROI_2  == 0 && CB_ROI_4 == 0)	robotRunAngle(-1150,18,900,0.7);
					else																robotRunAngle(-900,15,900,0.7);
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
		else if  (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 0) {
					ha_sat_xuong();
					robotRunAngle(1800,10,900,0.5);
					for(i=0;i<150;i++)
					{
						while(CB_ROI_4 == 0 || (abs(bientrochansauValue - target_chan_sau) > 10))	
						{	
							vTaskDelay (1);
							if(!wantExit())	break;
						}
					}
				}
		//// gap duoi lan 4
		else if  (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 0) {
					ha_sat_xuong();
					robotRunAngle(1800,10,900,0.8);
					for(i=0;i<150;i++)
					{
						while(CB_ROI_4 == 0 || (abs(bientrochansauValue - target_chan_sau) > 10))	
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
					while(CB_Ha_Sau == 0 || (abs(bientrochansauValue - target_chan_sau) > 10)) {
						if(CB_ROI_2  == 0 && CB_ROI_4 == 0)	robotRunAngle(-1150,18,900,0.7);
						else																robotRunAngle(-900,15,900,0.7);
						vTaskDelay(1);
						if(!wantExit()) break;
									}
						// chay toi roi thi di ngang qua trai
						robotRunAngle(1800,7,900,0.7);
						while (CB_ROI_4  == 0 )	 {
							vTaskDelay(1);
							if(!wantExit()) break;
								}
							robotStop(0);
			}
		
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
					ha_sat_xuong();
					while(CB_Ha_Sau == 0 || (abs(bientrochansauValue - target_chan_sau) > 10)) {
						if(CB_ROI_2  == 0 && CB_ROI_4 == 0)	robotRunAngle(-1150,18,900,0.7);
						else																robotRunAngle(-900,15,900,0.7);
						vTaskDelay(1);
						if(!wantExit()) break;
									}
						// chay toi roi thi di ngang qua trai
						robotRunAngle(1800,7,900,0.7);
						while (CB_ROI_4  == 0 )	 {
							vTaskDelay(1);
							if(!wantExit()) break;
								}
							robotStop(0);
			}
	
			//// gap duoi lan 3
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
					ha_sat_xuong();
					robotRunAngle(1800,8,900,0.5);
					for(i=0;i<150;i++)
					{
						while(CB_ROI_4 == 0 || (abs(bientrochansauValue - target_chan_sau) > 10))	
						{	
							vTaskDelay (1);
							if(!wantExit())	break;
						}
					}
				}
					//// gap duoi lan 4
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 0) {
					ha_sat_xuong();
					robotRunAngle(1800,8,900,0.5);
					for(i=0;i<150;i++)
					{
						while(CB_ROI_4 == 0 || (abs(bientrochansauValue - target_chan_sau) > 10))	
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
						while(CB_ROI_1 == 0 ||  (abs(bientrochansauValue - target_chan_sau) > 10))	
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
					if(CB_ROI_3  == 0 && CB_ROI_1 == 0)	robotRunAngle(-650,18,900,0.7);
					else																robotRunAngle(-900,15,900,0.7);
					vTaskDelay(1);
					if(!wantExit()) break;
						}
					// chay toi roi thi di ngang qua phai
					robotRunAngle(0,8,900,0.7);
					while (CB_ROI_1  == 0 )	 {
						vTaskDelay(1);
						if(!wantExit()) break;
						}
				}
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 0) {		
					ha_sat_xuong();
					while( CB_Ha_Sau == 0 || (abs(bientrochansauValue - target_chan_sau) > 10)) {
					if(CB_ROI_3  == 0 && CB_ROI_1 == 0)	robotRunAngle(-650,18,900,0.7);
					else																robotRunAngle(-900,15,900,0.7);
					vTaskDelay(1);
					if(!wantExit()) break;
						}
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
	int vitri_tay41 = vitri_tay41_laser_trai_GapQua;

	Xuong_bac_200(-900, 900);		
	
	// KHONG CO TIN HIEU GAP
	if (TinHieu_ChuanBi_GapThang == 0 && TinHieu_ChuanBi_GapTrai == 0 && TinHieu_ChuanBi_GapPhai == 0) {
		Nang_cuc_nhanh();
		target_chan_truoc = Min_chan_truoc + 250;
		target_chan_sau = Min_chan_sau + 250;
		
		robotRunAngle(-900,20,900,0.5);
		for(i=0;i<250;i++)	
	{
		while(abs(bientrochansauValue - target_chan_sau) > 10)	{vTaskDelay(1); if(!wantExit())	break;}
	}		
	
	for(i=0;i<1550;i++)
				{
					while(CB_Ha_Sau == 1 )	
						
					{	
						if(!wantExit())	break;
						vTaskDelay (1);
					}
				}
		robotRunAngle(-900,10,900,0.5);
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

//  *********** GAP BEN TRAI 200 DUOI XANH 5
	
void Lay_ben_trai_bac_200_duoi_xanh_5(void) {
			Lay_ben_trai_bac_200_duoi();
			robotStop(0);
			
	if (TinHieu_ChuanBi_GapThang == 1) {
			kiem_tra_huong_quay_tay_gap_phia_truoc();
			vTaskDelay (7000);
			chuan_bi_gap_thang_xanh_4();
			robotRunAngle(-900,12,900,0.7);
			while( CB_Cap_Thanh_Sau == 0 || (abs(bientrochansauValue - target_chan_sau) > 10) )	
						{	
						vTaskDelay(1);if(!wantExit()) break;
						}
				}
			}

void Lay_ben_trai_bac_200_duoi_xanh_ko_thanh(void) {
			Lay_ben_trai_bac_200_duoi();
			robotStop(0);
			
	if (TinHieu_ChuanBi_GapThang == 1) {
			kiem_tra_huong_quay_tay_gap_phia_truoc();
			vTaskDelay (7000);
			di_tren_buc_khong_thanh_2_ben();
				}
}


///////////////////////////////////////////////////////////////////////////////////////////////

/// ****** leo bac 200 o id  5 san xanh
void Leo_bac_200_xanh_5(void) {	
		int vitri = 153;
		int vitri_tay41 = vitri_tay41_laser_trai_GapQua;
		
		Leo_bac_200(-900, 900);
		Nang_cuc_nhanh();
		target_chan_truoc = Min_chan_truoc + 250;
		target_chan_sau = Min_chan_sau + 250;
		
		// KHONG CO TIN HIEU GAP
		if (TinHieu_ChuanBi_GapThang == 0 && TinHieu_ChuanBi_GapTrai == 0 && TinHieu_ChuanBi_GapPhai == 0) {
				robotRunAngle(-900,18,900,0.7);
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
		int vitri_tay41 = vitri_tay41_laser_trai_GapQua;
		int vitri_tay23 = vitri_tay23_laser_trai_GapQua;
		kiem_tra_huong_quay_tay_gap_phia_truoc();
	
		su_dung_chan(265);
		
	// chinh lai vi tri cho tay gap
		if (da_lay_tay1 == 0 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
					while(CB_Ha_Sau == 0 || (abs(bientrochansauValue - target_chan_sau) > 10)) 
					{	
						if(lazeTraiValue > vitri_tay41)			robotRunAngle(-650,20,900,0.7);
						else																robotRunAngle(-900,10,900,0.7);
						vTaskDelay(1);
						if(!wantExit()) break;
									}
					chinh_lai_vi_tri_laser_trai(vitri_tay41, 1000);
			}
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
					while(CB_Ha_Sau == 0 || (abs(bientrochansauValue - target_chan_sau) > 10)) 
					{	
						if(lazeTraiValue > vitri_tay41)			robotRunAngle(-650,20,900,0.7);
						else																robotRunAngle(-900,10,900,0.7);
						vTaskDelay(1);
						if(!wantExit()) break;
									}
					chinh_lai_vi_tri_laser_trai(vitri_tay41, 1000);
			}

		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
				while( CB_Ha_Sau == 0 || (abs(bientrochansauValue - target_chan_sau) > 10)) {
				if(CB_ROI_2  == 0 && CB_ROI_4 == 0)	robotRunAngle(-1150,20,900,0.7);
				else																robotRunAngle(-900,10,900,0.7);
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
					while(CB_Ha_Sau == 0 || (abs(bientrochansauValue - target_chan_sau) > 10)) {
				if(CB_ROI_2  == 0 && CB_ROI_4 == 0)	robotRunAngle(-1150,20,900,0.7);
				else																robotRunAngle(-900,10,900,0.7);
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
//			KT_Ha_Tay_phai = 1;
			chinh_lai_vi_tri_laser_trai(vitri_tay41_laser_trai_GapQua, 200);
			su_dung_chan(565);
				for(i=0;i<250;i++)	
			{
				while(abs(bientrochansauValue - target_chan_sau) > 10)	{vTaskDelay(1); if(!wantExit())	break;}
			}
			robotRunAngle(0,7,900,0.1);
			vTaskDelay(2500);
		}
	
	else if (da_lay_tay1 == 1 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
//			KT_Ha_Tay_phai = 1;
			chinh_lai_vi_tri_laser_trai(vitri_tay41_laser_trai_GapQua , 200);
			su_dung_chan(565);
				for(i=0;i<250;i++)	
			{
				while(abs(bientrochansauValue - target_chan_sau) > 10)	{vTaskDelay(1); if(!wantExit())	break;}
			}	
			robotRunAngle(0,8,900,0.1);
			vTaskDelay(2500);
		}
	
			/// gap lan 3
	else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {		
			su_dung_chan(265);
			// chay toi khi mat cam bien sau
			robotRunAngle(-900,10,900,0.5);
			for(i=0;i<250;i++)
					{
						while(CB_Ha_Sau == 0 || (abs(bientrochansauValue - target_chan_sau) > 10))	
					{	
						vTaskDelay (1);
						if(!wantExit())	break;
					}
				}
			chinh_lai_vi_tri_laser_trai(vitri_tay41_laser_trai_GapQua , 200);
			robotStop(10); 
//			KT_Ha_Tay_phai = 1;

			su_dung_chan(565);
				for(i=0;i<250;i++)	
			{
				while(abs(bientrochansauValue - target_chan_sau) > 10)	{vTaskDelay(1); if(!wantExit())	break;}
			}	
			robotRunAngle(0,8,900,0.1);
			vTaskDelay(2500);
		}
	/// gap lan 4
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 0) {
			su_dung_chan(265);
			// chay toi khi mat cam bien sau
			robotRunAngle(-900,10,900,0.5);
			for(i=0;i<250;i++)
					{
						while(CB_Ha_Sau == 0 || (abs(bientrochansauValue - target_chan_sau) > 10))	
					{	
						vTaskDelay (1);
						if(!wantExit())	break;
					}
				}
			chinh_lai_vi_tri_laser_trai(vitri_tay41_laser_trai_GapQua , 200);
			robotStop(10); 
//			KT_Ha_Tay_phai = 1;

			su_dung_chan(565);
				for(i=0;i<250;i++)	
			{
				while(abs(bientrochansauValue - target_chan_sau) > 10)	{vTaskDelay(1); if(!wantExit())	break;}
			}	
			robotRunAngle(0,7,900,0.1);
			vTaskDelay(2500);
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
			robotRunAngle(-900,20,900,0.5);
			for(i=0;i<1550;i++)
					{
							while( CB_Ha_Sau == 0)	

						{	
							if(!wantExit())	break;
							vTaskDelay (1);
						}
					}
			robotRunAngle(-900,10,900,0.5);
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
		}

//**************** Xuong_bac_200 xanh ô 9 **************		
void chuan_bi_gap_thang_xanh_9 (void) {
		int vitri_tay23 = vitri_tay23_phai_laser_GapQua;
		kiem_tra_huong_quay_tay_gap_phia_truoc();
		su_dung_chan(265);
	
			// chinh lai vi tri cho tay gap
		if (da_lay_tay1 == 0 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
				while(CB_Ha_Sau == 0|| (abs(bientrochansauValue - target_chan_sau) > 10)) {
				if(CB_ROI_3  == 0 && CB_ROI_1 == 0)	robotRunAngle(-650,20,900,0.7);
				else																robotRunAngle(-900,10,900,0.7);
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
				if(CB_ROI_3  == 0 && CB_ROI_1 == 0)	robotRunAngle(-650,20,900,0.7);
				else																robotRunAngle(-900,10,900,0.7);
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
					while( CB_Ha_Sau == 0 || (abs(bientrochansauValue - target_chan_sau) > 10)) 
					{	
					if(lazePhaiValue > vitri_tay23)			robotRunAngle(-1150,20,900,0.7);
					else																robotRunAngle(-900,10,900,0.7);
					vTaskDelay(1);
					if(!wantExit()) break; }
					chinh_lai_vi_tri_laser_phai(vitri_tay23, 1000);
			}
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 0) {
					while(CB_Ha_Sau == 0 || (abs(bientrochansauValue - target_chan_sau) > 10)) 
					{	
					if(lazePhaiValue > vitri_tay23)			robotRunAngle(-1150,20,900,0.7);
					else																robotRunAngle(-900,10,900,0.7);
					vTaskDelay(1);
					if(!wantExit()) break; }
					chinh_lai_vi_tri_laser_phai(vitri_tay23, 1000);
					}
		robotStop(0);
	}


void chuan_bi_gap_trai_200_tren (void ) {
//		KT_Ha_Tay_trai = 1;
	if (da_lay_tay1 == 0 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
						su_dung_chan(265);
						for(i=0;i<1550;i++) {
						while(CB_Ha_Sau == 0  ||  (abs(bientrochansauValue - target_chan_sau) > 10))	
						{	
						if(lazePhaiValue > vitri_tay23_phai_laser_GapQua)			robotRunAngle(-1150,15,900,0.7);
						else																robotRunAngle(-900,10,900,0.7);
						vTaskDelay(1);
						if(!wantExit()) break;
									}
							}
						robotStop(0); 
						su_dung_chan(565);
						for(i=0;i<250;i++)	
						{
							while(abs(bientrochansauValue - target_chan_sau) > 10)	{vTaskDelay(1); if(!wantExit())	break;}
						}

		}
	else if (da_lay_tay1 == 1 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
						su_dung_chan(265);
						for(i=0;i<1550;i++) {
						while(CB_Ha_Sau == 0  ||  (abs(bientrochansauValue - target_chan_sau) > 10))	
						{	
						if(lazePhaiValue > vitri_tay23_phai_laser_GapQua)			robotRunAngle(-1150,15,900,0.7);
						else																robotRunAngle(-900,10,900,0.7);
						vTaskDelay(1);
						if(!wantExit()) break;
									}
							}
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
				chinh_lai_vi_tri_laser_phai(vitri_tay23_phai_laser_GapQua, 200);
				robotRunAngle(1800,10,900,0.8);
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
				chinh_lai_vi_tri_laser_phai(vitri_tay23_phai_laser_GapQua, 200);
				robotRunAngle(1800,10,900,0.8);
				vTaskDelay(2500);
				robotStop(0); 
				su_dung_chan(565);
					for(i=0;i<250;i++)	
				{
					while(abs(bientrochansauValue - target_chan_sau) > 10)	{vTaskDelay(1); if(!wantExit())	break;}
				}
		}
	
		robotStop(0); 
}


void Xuong_bac_200_xanh_9(void){	
		int vitri_tay23 = vitri_tay23_phai_laser_GapQua;
		Xuong_bac_200(-900, 900);
		
		if (TinHieu_ChuanBi_GapThang == 0 && TinHieu_ChuanBi_GapTrai == 0 && TinHieu_ChuanBi_GapPhai == 0) {
				su_dung_chan(265);
				// chay toi khi mat cam bien sau
				robotRunAngle(-900,18,900,0.8);
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

	
void Lay_ben_trai_bac_200_tren_xanh_9(void) {
			Lay_ben_trai_bac_200_tren();
			robotStop(0);
			
	if (TinHieu_ChuanBi_GapThang == 1) {
			kiem_tra_huong_quay_tay_gap_phia_truoc();
			vTaskDelay (7000);
			chuan_bi_gap_thang_xanh_9();
				}
}


void xuong_bac_200_xanh_12(void) {
		Xuong_bac_200(-900, 900);
		if (TinHieu_ChuanBi_GapThang == 0 && TinHieu_ChuanBi_GapTrai == 0 && TinHieu_ChuanBi_GapPhai == 0) {
				su_dung_chan(265);
				// chay toi khi mat cam bien sau
				robotRunAngle(-900,20,900,0.8);
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
    action_table[0][1][1]  = Lay_phia_truoc_bac_400_tren;
    action_table[0][1][2]  = Lay_phia_truoc_bac_200_tren;
    action_table[0][1][3]  = Lay_phia_truoc_bac_400_tren;
		action_table[0][1][4]  = Lay_phia_truoc_bac_200_duoi;
		action_table[0][1][5]  = Lay_phia_truoc_bac_200_tren;	
		action_table[0][1][6]  = Lay_phia_truoc_bac_200_tren;	
		action_table[0][1][7]  = Lay_phia_truoc_bac_200_tren;	
		action_table[0][1][8]  = Lay_phia_truoc_bac_200_tren;	
		action_table[0][1][9]  = Lay_phia_truoc_bac_200_duoi;
		action_table[0][1][10] = Lay_phia_truoc_bac_200_duoi;
		action_table[0][1][11] = Lay_phia_truoc_bac_200_duoi;
		action_table[0][1][12] = Lay_phia_truoc_bac_200_duoi;

//    /* =========================================
//       move 0 , action 2, dung lai de lay ben TRAI
//       ========================================= */
		action_table[0][2][4]  = Lay_ben_trai_bac_200_duoi_xanh_5;
		action_table[0][2][5]  = Lay_ben_trai_bac_200_duoi_xanh_ko_thanh;
		action_table[0][2][7]  = Lay_ben_trai_bac_200_duoi_xanh_ko_thanh;
		action_table[0][2][10] = Lay_ben_trai_bac_200_duoi_xanh_ko_thanh;
		
		action_table[0][2][8]  = Lay_ben_trai_bac_200_tren_xanh_9;
		action_table[0][2][11] = Lay_ben_trai_bac_200_tren_xanh_9;

//    /* =========================================
//       move 0 , action 3, dung lai de lay ben PHAI
//       ========================================= */
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
//		action_table[2][4][1] = qua_trai_len_bac;

		/* =========================================
//   move 3 , action 4,chay ben phai
//   ========================================= */
//    action_table[3][4][2] = qua_phai_xuong_bac;
		
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
                    chay_ngang_qua_o1_xanh = 1; // Bat flag cho ben trai
                }
            }
            
            else if (pkt.move == 3 && pkt.action == 10 && pkt.id_block == 2)
            {
                if (next_pkt.move == 3 && next_pkt.action == 10 && next_pkt.id_block == 3)
                {
                    chay_ngang_qua_o3_xanh = 1; // Bat flag cho ben phai
                }
            }
        }

        if (pkt.move < MAX_MOVE && pkt.action < MAX_ACTION && pkt.id_block < MAX_ID)
        {
            action_table[pkt.move][pkt.action][pkt.id_block]();
        }

        vTaskDelay(2000); 
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

// 0: Nghi, 1: Nhom tay 1-2, 2: Nhom tay 3-4
static int dang_o_nhom = 0; 

void kiem_tra_qua_tay_nao(void) {
	
    // 1. Tinh tong so qua hien co tren tung cum tay
    int so_qua_nhom_1_2 = tay_1_co_qua + tay_2_co_qua;
    int so_qua_nhom_3_4 = tay_3_co_qua + tay_4_co_qua;

    int nhom_se_chon = 0;
    int target_tam = -1;
    kiem_tra_so_qua_tren_tay();


    // --- LOGIC QUYET DINH DIEU HUONG ---

    // UU TIEN 1: Neu dang o mot ben va ben do van con qua thi o lai dat tiep
    // Vi du: Vua dat xong tay 4 nhung tay 3 van con qua -> Khong xoay di dau ca
    if (dang_o_nhom == 1 && so_qua_nhom_1_2 > 0) {
        nhom_se_chon = 1;
        target_tam = vi_tri_dat_hop_1_2;
    } 
    else if (dang_o_nhom == 2 && so_qua_nhom_3_4 > 0) {
        nhom_se_chon = 2;
        target_tam = vi_tri_dat_hop_3_4;
    }
    // UU TIEN 2: Neu nhom hien tai da het qua hoac chua chon nhom, tim ben co 2 qua
    else if (so_qua_nhom_1_2 == 2) {
        nhom_se_chon = 1;
        target_tam = vi_tri_dat_hop_1_2;
    }
    else if (so_qua_nhom_3_4 == 2) {
        nhom_se_chon = 2;
        target_tam = vi_tri_dat_hop_3_4;
    }
    // UU TIEN 3: Neu khong ben nao co 2 qua, chon ben bat ky co it nhat 1 qua
    else if (so_qua_nhom_1_2 > 0) {
        nhom_se_chon = 1;
        target_tam = vi_tri_dat_hop_1_2;
    }
    else if (so_qua_nhom_3_4 > 0) {
        nhom_se_chon = 2;
        target_tam = vi_tri_dat_hop_3_4;
    }
    else {
        // Truong hop tat ca cac tay deu het qua
        dang_o_nhom = 0; 
        return;
    }

    // --- THUC HIEN HANH DONG XOAY ---
    if (target_tam != -1) {
        dang_o_nhom = nhom_se_chon;

        speed_tay_xoay = 100;
        target_xoay_tay = target_tam;

        if (abs(bientroxoaytayValue - target_xoay_tay) > 10) {
            while (abs(bientroxoaytayValue - target_xoay_tay) > 10) {
                vTaskDelay(1); 
                if (!wantExit()) break; 
            }
        }

        // Bat tin hieu kich hoat trinh tu dat hop 
        if (dang_o_nhom == 1) {
            tin_hieu_dat_hop_1_2 = 1;
        } else {
            tin_hieu_dat_hop_3_4 = 1;
        }
    }
}

void kiem_tra_qua_tay_nao_xuong_rung (void) {
		// 1. Tinh tong so qua hien co tren tung cum tay
    int so_qua_nhom_1_2 = tay_1_co_qua + tay_2_co_qua;
    int so_qua_nhom_3_4 = tay_3_co_qua + tay_4_co_qua;

    int nhom_se_chon = 0;
    int target_tam = -1;
    kiem_tra_so_qua_tren_tay();


    // --- LOGIC QUYET DINH DIEU HUONG ---
	
		// Vua dat xong tay 4 nhung tay 3 van con qua -> Khong xoay di dau ca
    if (dang_o_nhom == 1 && so_qua_nhom_1_2 > 0) {
        nhom_se_chon = 1;
        target_tam = vi_tri_dat_hop_1_2;
    } 
    else if (dang_o_nhom == 2 && so_qua_nhom_3_4 > 0) {
        nhom_se_chon = 2;
        target_tam = vi_tri_dat_hop_3_4;
    }
    // UU TIEN 2: Neu nhom hien tai da het qua hoac chua chon nhom, tim ben co 2 qua
    else if (so_qua_nhom_1_2 == 2) {
        nhom_se_chon = 1;
        target_tam = vi_tri_dat_hop_1_2;
    }
    else if (so_qua_nhom_3_4 == 2) {
        nhom_se_chon = 2;
        target_tam = vi_tri_dat_hop_3_4;
    }
    // UU TIEN 3: Neu khong ben nao co 2 qua, chon ben bat ky co it nhat 1 qua
    else if (so_qua_nhom_1_2 > 0) {
        nhom_se_chon = 1;
        target_tam = vi_tri_dat_hop_1_2;
    }
    else if (so_qua_nhom_3_4 > 0) {
        nhom_se_chon = 2;
        target_tam = vi_tri_dat_hop_3_4;
    }
    else {
        // Truong hop tat ca cac tay deu het qua
        dang_o_nhom = 0; 
        return;
    }

    // --- THUC HIEN HANH DONG XOAY ---
    if (target_tam != -1) {
        dang_o_nhom = nhom_se_chon;

        speed_tay_xoay = 100;
        target_xoay_tay = target_tam;


        // Bat tin hieu kich hoat trinh tu dat hop 
        if (dang_o_nhom == 1) {
            tin_hieu_dat_hop_1_2 = 1;
        } else {
            tin_hieu_dat_hop_3_4 = 1;
        }
    }
}




void DatKFSxanh(int vitri)
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
	
	chinh_lai_vi_tri_laser_phai_custom(190, 1000, 5, 50);
	

		robotRunAngle(-900,30,900,0.8);
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
				Bam_laser_sau(35,0,900, vitri, 3, -120, 10);
				vTaskDelay(5); 
				if(!wantExit())	break;
			}
	}
		
	
	for(i=0;i<550;i++)	
	{	
			while(lazeTraiValue > 195)	
			{	
				Bam_laser_sau(5,0,900, vitri, 1, -100, 10);
				vTaskDelay(5); 
				if(!wantExit())	break;
			}
	}	

		robotStop(0);
		robotRotate(900,0.9, 0);
		while(robotFixAngle()){
					vTaskDelay (1); 
					if(!wantExit())	break;
				}
		chinh_lai_vi_tri_laser_trai(185 , 1000);
		
		robotStop(0);
	// do chan len dat qua
		su_dung_chan(700);
		for(i=0;i<150;i++)		
	{
		while(abs(bientrochansauValue - target_chan_sau) > 5)	{vTaskDelay(1); if(!wantExit())	break;}
	}
	
		speed_tay_gat1 = 100;
		target_tay_gat1 = vitri_tay1home ;
		speed_tay_gat2 = 100;
		target_tay_gat2 = vitri_tay1home ;
	robotStop(0);
	

}

bool da_dat_tay_1 = false;
bool da_dat_tay_2 = false;
bool da_dat_tay_3 = false;
bool da_dat_tay_4 = false;


void dat_qua_tay_1_2_xanh(void) {
    if (CB_kep_1_2 == 0 && CB_kep_1_1 == 0 && !da_dat_tay_1) {
        speed_tay_gat1 = 100;
        target_tay_gat1 = vitri_tay1home + 105;
    
        for(i=0; i<50; i++) { 
            while(abs(bientrodaytay1Value - target_tay_gat1) > 10 || abs(bientrodaytay2Value - target_tay_gat2) > 10) {
                vTaskDelay(1); if(!wantExit()) break;
            }
        }
        vTaskDelay(3000);
        Kep_phai_1_ra;    
        da_dat_tay_1 = true; 
    }
    else if (CB_kep_2_2 == 0 && CB_kep_2_1 == 0 && !da_dat_tay_2) {
        speed_tay_gat2 = 100;
        target_tay_gat2 = vitri_tay2home + 105;
            
        for(i=0; i<50; i++) { 
            while(abs(bientrodaytay1Value - target_tay_gat1) > 10 || abs(bientrodaytay2Value - target_tay_gat2) > 10) {
                vTaskDelay(1); if(!wantExit()) break;
            }
        }
        vTaskDelay(3000);
        Kep_phai_2_ra;
        da_dat_tay_2 = true; 
    }
    
    vTaskDelay(3000);
    
    // Ðua tay v? Home
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
void dat_qua_tay_4_3_xanh(void) {
    
    if (CB_kep_4_2 == 0 && CB_kep_4_1 == 0 && !da_dat_tay_4) {
        speed_tay_gat2 = 100;
        target_tay_gat2 = vitri_tay2home - 105;
            
        for(i=0; i<50; i++) { 
            while(abs(bientrodaytay1Value - target_tay_gat1) > 10 || abs(bientrodaytay2Value - target_tay_gat2) > 10) {
                vTaskDelay(1); if(!wantExit()) break;
            }
        }
        Kep_phai_4_ra;
        da_dat_tay_4 = true; //
    }
    
    else if (CB_kep_3_2 == 0 && CB_kep_3_1 == 0 && !da_dat_tay_3) {
        speed_tay_gat1 = 100;
        target_tay_gat1 = vitri_tay1home - 105;

        for(i=0; i<50; i++) { 
            while(abs(bientrodaytay1Value - target_tay_gat1) > 10 || abs(bientrodaytay2Value - target_tay_gat2) > 10) {
                vTaskDelay(1); if(!wantExit()) break;
            }
        }
        
        Kep_phai_3_ra;
        da_dat_tay_3 = true; // Ðánh d?u dã d?t xong tay 3
    }

    vTaskDelay(3000);
        
    // Ðua tay v? Home
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
				if (CB_kep_4_2 == 0 && CB_kep_4_1 == 0) {
					Tay2_len;
					for(i=0;i<50;i++)	{ 
									while(CB_xilanh_tay_2 == 1 )	{vTaskDelay(1); if(!wantExit())	break;}
							}
					dat_hop4_2(485, 345, 35, 4);
					vTaskDelay(3000); 
					speed_tay_gat2 = 250;
					target_tay_gat2 = vitri_tay2home ;
				}
				else if (CB_kep_3_2 == 0 && CB_kep_3_1 == 0) {
					Tay1_len;
					for(i=0;i<50;i++)	{ 
									while(CB_xilanh_tay_1 == 1 )	{vTaskDelay(1); if(!wantExit())	break;}
							}
					dat_hop1_3(485, 345, 35, 3);
					vTaskDelay(3000); 
					speed_tay_gat1 = 250;
					target_tay_gat1 = vitri_tay1home ;
					}	
				
		}
		else if (tin_hieu_dat_hop_1_2 == 1 ) {
				if (CB_kep_1_2 == 0 && CB_kep_1_1 == 0) {
						Tay1_len;
						for(i=0;i<50;i++)	{ 
									while(CB_xilanh_tay_1 == 1 )	{vTaskDelay(1); if(!wantExit())	break;}
							}
						dat_hop1_3(485, 555, 35, 1);
						vTaskDelay(3000); 
						speed_tay_gat1 = 250;
						target_tay_gat1 = vitri_tay1home ;
				}
				else if (CB_kep_2_2 == 0 && CB_kep_2_1 == 0 ) {
						Tay2_len;
						for(i=0;i<50;i++)	{ 
									while(CB_xilanh_tay_2 == 1 )	{vTaskDelay(1); if(!wantExit())	break;}
							}
						dat_hop4_2(485, 555, 35, 2);
						vTaskDelay(3000); 
						speed_tay_gat1 = 250;
						target_tay_gat1 = vitri_tay1home ;
				}
		}
		for(i=0;i<50;i++)	{ 
				while(abs(bientrodaytay1Value - target_tay_gat1) > (10) || abs(bientrodaytay2Value - target_tay_gat2) > 10 )	
				{vTaskDelay(1); if(!wantExit())	break;}
				}
		Tay1_xuong;
		Tay2_xuong;
		
}

void chuan_bi_dat_hop_tang3 (void) {
		if (tin_hieu_dat_hop_3_4 == 1 && tay_4_co_qua == 1 ) {
				Tay2_len;
				for(i=0;i<50;i++)	{ 
									while(CB_xilanh_tay_2 == 1 )	{vTaskDelay(1); if(!wantExit())	break;}
							}
						}
		
		else if (tin_hieu_dat_hop_1_2 == 1 && tay_1_co_qua == 1 ) {
				Tay1_len;
				for(i=0;i<50;i++)	{ 
									while(CB_xilanh_tay_1 == 1 )	{vTaskDelay(1); if(!wantExit())	break;}
							}
						}

		
		else if (tin_hieu_dat_hop_1_2 == 1 && tay_2_co_qua == 1 ) {
				Tay2_len;
				for(i=0;i<50;i++)	{ 
									while(CB_xilanh_tay_2 == 1 )	{vTaskDelay(1); if(!wantExit())	break;}
							}
						}

		
		else if (tin_hieu_dat_hop_3_4 == 1 && tay_3_co_qua == 1) {
				Tay1_len;
				for(i=0;i<50;i++)	{ 
									while(CB_xilanh_tay_1 == 1 )	{vTaskDelay(1); if(!wantExit())	break;}
							}
						}

		}

void kiem_tra_so_qua_tren_tay(void) {
    int dem = 0;

    // Ki?m tra tay 1
    if (CB_kep_1_1 == 0 && CB_kep_1_2 == 0) {
        tay_1_co_qua = 1;
        dem++;
    } else {
        tay_1_co_qua = 0;
    }

    // Ki?m tra tay 2
    if (CB_kep_2_1 == 0 && CB_kep_2_2 == 0) {
        tay_2_co_qua = 1;
        dem++;
    } else {
        tay_2_co_qua = 0;
    }

    // Ki?m tra tay 3
    if (CB_kep_3_1 == 0 && CB_kep_3_2 == 0) {
        tay_3_co_qua = 1;
        dem++;
    } else {
        tay_3_co_qua = 0;
    }

    // Ki?m tra tay 4
    if (CB_kep_4_1 == 0 && CB_kep_4_2 == 0) {
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
		// cho nhay den thi dat
	for(i=0;i<1000;i++)	
		{
		while(Quang_tro2 > 120)	{	
		vTaskDelay (1);
		if(!wantExit())	break;
			}
		}
	vTaskDelay (2000);
	nhay_den_lan_1 = 1;
	
	// rut chan va nghieng tay xuong
	if (nhay_den_lan_1 == 1 ) {
			su_dung_chan(350);
				for(i=0;i<150;i++)		
			{
				while(abs(bientrochansauValue - target_chan_sau) > 5)	{vTaskDelay(1); if(!wantExit())	break;}
			}
			chuan_bi_dat_hop_tang3();
			vTaskDelay (3000);
		
			for(i=0;i<1000;i++)	
			{
		while(Quang_tro2 > 120)	{	
				vTaskDelay (1);
		if(!wantExit())	break;
					}
			}
			nhay_den_lan_1 = 2;
			}
	// nhay lan 2 thi dat hop lan 1
	if (nhay_den_lan_1 == 2) {
			dat_hop_vao_o();
		
			tin_hieu_dat_hop_3_4 = 0;
			tin_hieu_dat_hop_1_2 = 0;
		
			vTaskDelay (1000);
			kiem_tra_so_qua_tren_tay();
			kiem_tra_qua_tay_nao();
			chuan_bi_dat_hop_tang3();
				for(i=0;i<100;i++)	
				{
			while(Quang_tro2 > 120)	{	
					vTaskDelay (1);
			if(!wantExit())	break;
						}
				}
			nhay_den_lan_1 = 3;
		}
	
			// nhay lan 3 thi dat hop lan 2
	if (nhay_den_lan_1 == 3) {
		
			dat_hop_vao_o();
		
			tin_hieu_dat_hop_3_4 = 0;
			tin_hieu_dat_hop_1_2 = 0;
		
			vTaskDelay (1000);
			kiem_tra_so_qua_tren_tay();
			kiem_tra_qua_tay_nao();

			vTaskDelay (3000);
			nhay_den_lan_1 = 4;
			robotStop(0);
		}
	
		// nhay lan 4 ha xuong 
		if (nhay_den_lan_1 == 4) {
				ha_chan_dat_tang2_do();
				nhay_den_lan_1 = 5;
		}
		if (nhay_den_lan_1 == 5) {
				for(i=0;i<1000;i++)	
			{
				while(Quang_tro2 > 120)	{	
				vTaskDelay (1);
			if(!wantExit())	break;
					}
			}
			vTaskDelay (10000);
			
			for(i=0;i<550;i++)
				{
					while( CB_Nang_phai ==  0 || CB_Nang_trai ==  0 )	
					{	
						vTaskDelay (1);
						if(!wantExit())	break;
						
					}
				}
					vTaskDelay (8000);
							
				for(i=0;i<550;i++)	
				{	
						while(lazePhaiValue < 220)	
						{	
							vTaskDelay(1); 
							if(!wantExit())	break;
						}
				}
				su_dung_chan(495);
				for(i=0;i<150;i++)		
				{
					while(abs(bientrochansauValue - target_chan_sau) > 5)	{vTaskDelay(1); if(!wantExit())	break;}
				}
				kiem_tra_so_qua_tren_tay();
				kiem_tra_qua_tay_nao();
				chuan_bi_dat_hop_tang3();
				nhay_den_lan_1 = 6;
		}
		
		
}

void be_len_dat_xanh_1_qua_tren_3 (void) {
	kiem_tra_so_qua_tren_tay();
	kiem_tra_qua_tay_nao();
		// cho nhay den thi dat
	for(i=0;i<1000;i++)	
		{
		while(Quang_tro2 > 120)	{	
		vTaskDelay (1);
		if(!wantExit())	break;
			}
		}
	vTaskDelay (2000);
	nhay_den_lan_1 = 1;
	
	// rut chan 
	if (nhay_den_lan_1 == 1 ) {
			su_dung_chan(350);
			for(i=0;i<150;i++)		
			{
				while(abs(bientrochansauValue - target_chan_sau) > 5)	{vTaskDelay(1); if(!wantExit())	break;}
			}
			chuan_bi_dat_hop_tang3();
			vTaskDelay (3000);
		
			for(i=0;i<1000;i++)	
			{
		while(Quang_tro2 > 120)	{	
				vTaskDelay (1);
		if(!wantExit())	break;
					}
			}
			nhay_den_lan_1 = 2;
			}
	// nhay lan 2 thi dat hop lan 1
	if (nhay_den_lan_1 == 2) {
			dat_hop_vao_o();
		
			tin_hieu_dat_hop_3_4 = 0;
			tin_hieu_dat_hop_1_2 = 0;
		
			vTaskDelay (1000);
			kiem_tra_so_qua_tren_tay();
			kiem_tra_qua_tay_nao();
		
			nhay_den_lan_1 = 3;
		}
		// nhay lan 4 ha xuong 
		if (nhay_den_lan_1 == 3) {
				ha_chan_dat_tang2_do();
				nhay_den_lan_1 = 4;
		}
		if (nhay_den_lan_1 == 4) {
				for(i=0;i<1000;i++)	
			{
				while(Quang_tro2 > 120)	{	
				vTaskDelay (1);
			if(!wantExit())	break;
					}
			}
			vTaskDelay (10000);

			
			for(i=0;i<1550;i++)
				{
					while( CB_Nang_phai ==  0 || CB_Nang_trai ==  0 )	
						{	
						vTaskDelay (1);
						if(!wantExit())	break;
						
						}
				}
				
				vTaskDelay (8000);
				for(i=0;i<550;i++)	
				{	
						while(lazePhaiValue < 220)	
						{	
							vTaskDelay(5); 
							if(!wantExit())	break;
						}
				}
				su_dung_chan(495);
				for(i=0;i<150;i++)		
				{
				while(abs(bientrochansauValue - target_chan_sau) > 5)	{vTaskDelay(1); if(!wantExit())	break;}
				}
				kiem_tra_so_qua_tren_tay();
				kiem_tra_qua_tay_nao();
				chuan_bi_dat_hop_tang3();
				nhay_den_lan_1 = 6;
		}
}

void quyet_dinh_dat_hop_tang3(void) {
		kiem_tra_so_qua_tren_tay();
		if ( so_qua_tren_tay == 1  ) {
				be_len_dat_xanh_1_qua_tren_3();
			}
		else if ( so_qua_tren_tay == 2  ) {
				be_len_dat_xanh_1_qua_tren_3();
			}
		else if (so_qua_tren_tay == 3 ) {
				be_len_dat_xanh();
		}
		else if (so_qua_tren_tay == 4 ) {
				be_len_dat_xanh();
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
	
		for(i=0;i<1000;i++)	
	{
		while(quangTroValue > 30)	{	
		vTaskDelay (1);
		if(!wantExit())	break;
					}
	}
	
	Tay_kep_mo;
	
	vTaskDelay (8000);
	
	for(i=0;i<1000;i++)	
	{
		while(quangTroValue < 90)	{	
		vTaskDelay (1);
		if(!wantExit())	break;
		}
	}
	vTaskDelay (8000);
	
	
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





void tudonghoantoan(void) {
	// toi lay vk
		Xuat_Phat_Lay_Vu_Khi_Xanh(171,-1670,233) ;
	// cho rb1 lay vk xong thì vuot rung
		mo_vk_san_xanh();
	
		if ( da_lay_vk == 2)	{	
				Run_All_Blocks_From_Queue_san_xanh();
	}
	// len dat hop
//		if (hoan_thanh_chay_rung == 1 ) DatKFSxanh(35),hoan_thanh_chay_rung = 2 ;
//		if (hoan_thanh_chay_rung== 2  ) quyet_dinh_dat_hop_tang3(),hoan_thanh_chay_rung = 3;
//		if (hoan_thanh_chay_rung== 3	) tu_dong_dat_tang2_xanh(),hoan_thanh_chay_rung = 4;


}

void retry_zone_2(void) {

		Run_All_Blocks_From_Queue_san_xanh();

	// len dat hop
		if (hoan_thanh_chay_rung == 1 ) DatKFSxanh(50),hoan_thanh_chay_rung = 2 ;
		if (hoan_thanh_chay_rung== 2  ) quyet_dinh_dat_hop_tang3(),hoan_thanh_chay_rung = 3;
		if (hoan_thanh_chay_rung== 3	) tu_dong_dat_tang2_xanh(),hoan_thanh_chay_rung = 4;
}

void retry_zone_3_o_1(int vitri) {
		kiem_tra_qua_tay_nao(); // ham kiem tra co qua tay nao de dat
		
		robotRunAngle(0, 35, 900, 0.3);
		for(i=0;i<550;i++)	
		{	
				while(lazeTraiValue > 420)	
				{	
					vTaskDelay(1); 
					if(!wantExit())	break;
				}
		}
		
		for(i=0;i<550;i++)	
		{	
				while(lazeTraiValue > 350)	
				{	
					Bam_laser_sau(20,0,900, vitri, 3, -200, 10);
					vTaskDelay(5); 
					if(!wantExit())	break;
				}
		}
		
		for(i=0;i<550;i++)	
	{	
			while(lazeTraiValue > 210)	
			{	
				Bam_laser_sau(15,0,900, vitri, 2, -150, 10);
				vTaskDelay(5); 
				if(!wantExit())	break;
			}
	}
		for(i=0;i<550;i++)	
	{	
			while(lazeTraiValue > 178)	
			{	
				Bam_laser_sau(5,0,900, vitri, 1, -150, 10);
				vTaskDelay(5); 
				if(!wantExit())	break;
			}
	}
		robotStop(0);
			// do chan len dat qua
		su_dung_chan(455);
		for(i=0;i<150;i++)		
	{
		while(abs(bientrochansauValue - target_chan_sau) > 5)	{vTaskDelay(1); if(!wantExit())	break;}
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

void retry_zone_3(int vitri) {
		kiem_tra_qua_tay_nao(); // ham kiem tra co qua tay nao de dat
		
		robotRunAngle(0, 30, 900, 0.3);
		for(i=0;i<550;i++)	
		{	
				while(lazeTraiValue > 510)	
				{	
					vTaskDelay(1); 
					if(!wantExit())	break;
				}
		}
		
		robotRunAngle(285, 30, 900, 0.3);
		for(i=0;i<550;i++)	
		{	
				while(lazeTraiValue > 300)	
				{	
					vTaskDelay(1); 
					if(!wantExit())	break;
				}
		}
		
		for(i=0;i<550;i++)	
	{	
			while(lazeTraiValue > 210)	
			{	
				Bam_laser_sau(15,0,900, vitri, 2, -150, 10);
				vTaskDelay(5); 
				if(!wantExit())	break;
			}
	}
		for(i=0;i<550;i++)	
	{	
			while(lazeTraiValue > 178)	
			{	
				Bam_laser_sau(5,0,900, vitri, 1, -150, 10);
				vTaskDelay(5); 
				if(!wantExit())	break;
			}
	}
		robotStop(0);
			// do chan len dat qua
		su_dung_chan(455);
		for(i=0;i<150;i++)		
	{
		while(abs(bientrochansauValue - target_chan_sau) > 5)	{vTaskDelay(1); if(!wantExit())	break;}
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


void dat_hop4_2(int do_cao_chan, int goc_tay, int ha_chan, int chontay) {
    int do_cao_chan_hien_tai = do_cao_chan; 
    int sai_so_cho_phep = 12;
    int target_tay_chinh = goc_tay;
    int so_lan_thu = 0;

    Tay2_len;
    while(CB_xilanh_tay_2 == 1) {
        vTaskDelay(1); 
        if(!wantExit()) return; 
    }

    speed_tay_gat2 = 100;
    target_tay_gat2 = target_tay_chinh;
    vTaskDelay(15000); 

    while(abs(bientrodaytay2Value - target_tay_chinh) > sai_so_cho_phep) 
    {
        so_lan_thu++;
        
        if (so_lan_thu >= 7) {
            speed_tay_gat2 = 100;
            target_tay_gat2 = target_tay_chinh;
            vTaskDelay(15000);
            break; 
        }

        speed_tay_gat2 = 250;
        target_tay_gat2 = vitri_tay2home;
        while(abs(bientrodaytay2Value - target_tay_gat2) > sai_so_cho_phep) {
            vTaskDelay(1); 
            if(!wantExit()) break;
        }

        do_cao_chan_hien_tai -= ha_chan;
        if(do_cao_chan_hien_tai < 350) do_cao_chan_hien_tai = 350;
        su_dung_chan(do_cao_chan_hien_tai);

        for(i=0; i<250; i++) {
            while(abs(bientrochansauValue - target_chan_sau) > 8) { 
                vTaskDelay(1); 
                if(!wantExit()) break;
            }
        }

        speed_tay_gat2 = 50;
        target_tay_gat2 = target_tay_chinh;
        vTaskDelay(15000); 
        if(!wantExit()) break;    
    }

    if (chontay == 4) {
        Kep_phai_4_ra;
    }
    else if (chontay == 2) {
        Kep_phai_2_ra;
    }
}

// tay 3 345, tay 1 550
void dat_hop1_3(int do_cao_chan, int goc_tay, int ha_chan, int chontay) {
    int do_cao_chan_hien_tai = do_cao_chan; 
    int sai_so_cho_phep = 12;
    int target_tay_chinh = goc_tay;
    int so_lan_thu = 0;
        
    Tay1_len;
    while(CB_xilanh_tay_1 == 1) {
        vTaskDelay(1); 
        if(!wantExit()) return; 
    }

    speed_tay_gat1 = 100;
    target_tay_gat1 = target_tay_chinh;
    vTaskDelay(15000); 
                
    while(abs(bientrodaytay1Value - target_tay_chinh) > sai_so_cho_phep) 
    {
        so_lan_thu++;

        if (so_lan_thu >= 7) {
            speed_tay_gat1 = 100;
            target_tay_gat1 = target_tay_chinh;
            vTaskDelay(15000);
            break; 
        }

        speed_tay_gat1 = 250;
        target_tay_gat1 = vitri_tay1home;
        while(abs(bientrodaytay1Value - target_tay_gat1) > sai_so_cho_phep) {
            vTaskDelay(1); 
            if(!wantExit()) break;
        }

        do_cao_chan_hien_tai -= ha_chan;
        
        if(do_cao_chan_hien_tai < 350) do_cao_chan_hien_tai = 350;
        su_dung_chan(do_cao_chan_hien_tai);
        
        for(i=0; i<250; i++) {
            while(abs(bientrochansauValue - target_chan_sau) > 8) { 
                vTaskDelay(1); 
                if(!wantExit()) break;
            }
        }

        speed_tay_gat1 = 50;
        target_tay_gat1 = target_tay_chinh;
        vTaskDelay(15000); 
        if(!wantExit()) break;    
    }

    if (chontay == 1) {
        Kep_phai_1_ra;
    }
    else if (chontay == 3) {
        Kep_phai_3_ra;
    }
}

void chon_o_retry3(void) {
		if (id_dat_hop == 1) { retry_zone_3_o_1(50);}
		else if (id_dat_hop == 2) { retry_zone_3(106);}
		else if (id_dat_hop == 3) { retry_zone_3(159);}

}
void chinh_lai_vi_tri_laser_phai_zone3_do(int vitri, int gia_tri_lap);
void chinh_lai_vi_tri_laser_sau_zone3(int vitri, int gia_tri_lap)
{
	int speed ;
	int dieuchinh;
		for(i=0;i<gia_tri_lap;i++)
				{
		while(abs(lazeSauValue - vitri) > 1)	{
			dieuchinh = lazeSauValue - vitri;
			speed = custom_smooth_speed(dieuchinh, 4, 18);
			
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

		if (nhat_dat_hop == 1 || nhat_dat_hop == 4) {
				chinh_lai_vi_tri_laser_phai_zone3_do(209, 200);
			}
		else if (nhat_dat_hop == 2 || nhat_dat_hop == 5) {
				chinh_lai_vi_tri_laser_phai_zone3_do(252, 200);
			}
		else if (nhat_dat_hop == 3 || nhat_dat_hop == 6) {
				chinh_lai_vi_tri_laser_phai_zone3_do(299, 200);
			}


			robotStop(0);
		if (nhat_dat_hop == 1|| nhat_dat_hop == 2 || nhat_dat_hop == 3) {
							
			Tay2_len;
			for(i=0;i<50;i++)	{ 
									while(CB_xilanh_tay_2 == 1 )	{vTaskDelay(1); if(!wantExit())	break;}
									
			su_dung_chan(485);
			chinh_lai_vi_tri_laser_sau_zone3(6, 1000);
			robotStop(0);

							}
			dat_hop4_2(485, 350,35, 4);
			
			}
		
			// chon be tang 3
			if (nhat_dat_hop == 4 ||nhat_dat_hop == 5 || nhat_dat_hop == 6  ) {
				robotRotate(-900,1,0);
				while(robotFixAngle()){
					vTaskDelay (1); 
					if(!wantExit())	break;
				}
				su_dung_chan(710);
				quyet_dinh_dat_hop_tang3();
			}
}			

void nhat_hop_zone3_xanh (void) {
		su_dung_chan(350);
		robotRunAngle(1800, 35, 0, 0.5);
		for(i=0;i<550;i++)	
		{	
				while(lazeTruocValue < 260)	
				{	
					vTaskDelay(1); 
					if(!wantExit())	break;
				}
		}
		

		robotStop(10);
		/// check tam hop
		for(i=0;i<5000;i++)	
		{	
			run_align_center();
		}
		
		su_dung_chan(400);
		Kep_phai_4_ra;
		speed_tay_gat2 = 250;
		target_tay_gat2 = 180;
		
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
		
		robotRunAngle(1800, 14, 0, 0.5);
		for(i=0;i<550;i++)	
		{	
				while(lazeSauValue > 35)	
				{	
					vTaskDelay(1); 
					if(!wantExit())	break;
				}
		}	
		
		robotRunAngle(1800, 6, 0, 0.5);
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
				Ktra_vtri_kep4(); 

			speed_tay_gat2 = 250;
			target_tay_gat2 = Min_tay_gat2 +10 ;
			for(i=0;i<550;i++)	{ 
					while(abs(bientrodaytay2Value - target_tay_gat2)> 10 )	
					{vTaskDelay(1); if(!wantExit())	break;}
				}
			
			vTaskDelay (2000);
			speed_tay_gat2 = 250;
			target_tay_gat2 = vitri_tay2home;
			vTaskDelay(1000);
			Kep_phai_4_vao;
			robotRunAngle(0,10,0, 0.5);
			vTaskDelay(12000);
			
			// lay xong chay lui ve		
			chon_o_nhat_hop_xanh();
			
}

// hàm xác dinh vi trí dat qua khi dat tang 2
void xac_dinh_vi_tri_robot_xanh(void) {
    const int margin = 5;
    kiem_tra_so_qua_tren_tay();

    if (tay_1_co_qua || tay_4_co_qua) {
        if ((lazeTruocValue >= (110 - 10) && lazeTruocValue <= (110 + 10)) &&
            (lazeSauValue >= (47 - margin) && lazeSauValue <= (47 + margin))) {
            robot_position = 1;
        }
        else if ((lazeTruocValue >= (60 - 10) && lazeTruocValue <= (60 + 10)) &&
                 (lazeSauValue >= (95 - margin) && lazeSauValue <= (95 + margin))) {
            robot_position = 2;
        }
        else if ((lazeTruocValue >= (4 - margin) && lazeTruocValue <= (4 + margin)) &&
                 (lazeSauValue >= (154 - margin) && lazeSauValue <= (154 + margin))) {
            robot_position = 3;
        }
        else {
            long dist1 = abs(lazeTruocValue - 110) + abs(lazeSauValue - 47);
            long dist2 = abs(lazeTruocValue - 60) + abs(lazeSauValue - 95);
            long dist3 = abs(lazeTruocValue - 4) + abs(lazeSauValue - 154);
            if (dist1 <= dist2 && dist1 <= dist3) robot_position = 1;
            else if (dist2 <= dist1 && dist2 <= dist3) robot_position = 2;
            else robot_position = 3;	
        }
    }
    else if (tay_2_co_qua || tay_3_co_qua) {
        if ((lazeSauValue >= (0) && lazeSauValue <= (18)) &&
            (lazeTruocValue >= (139) && lazeTruocValue <= (165))) {
            robot_position = 1;
        }
        else if ((lazeSauValue >= (40) && lazeSauValue <= (73)) &&
                 (lazeTruocValue >= (83) && lazeTruocValue <= (116))) {
            robot_position = 2;
        }
        else if ((lazeSauValue >= (89) && lazeSauValue <= (121)) &&
                 (lazeTruocValue >= (35) && lazeTruocValue <= (66))) {
            robot_position = 3;
        }
        else {
            long dist1 = abs(lazeSauValue - 9) + abs(lazeTruocValue - 152);
            long dist2 = abs(lazeSauValue - 56) + abs(lazeTruocValue - 99);
            long dist3 = abs(lazeSauValue - 105) + abs(lazeTruocValue - 50);
            if (dist1 <= dist2 && dist1 <= dist3) robot_position = 1;
            else if (dist2 <= dist1 && dist2 <= dist3) robot_position = 2;
            else robot_position = 3;
        }
    }
}


void tu_dong_dat_tang2_xanh(void) {
		robotRotate(900,0.2, 0);
		while(robotFixAngle()){
					vTaskDelay (1); 
					if(!wantExit())	break;
				}
		kiem_tra_so_qua_tren_tay();
		xac_dinh_vi_tri_robot_xanh();

		if (tay_1_co_qua || tay_4_co_qua) {
        if (robot_position == 1) {
            chinh_lai_vi_tri_laser_sau(50, 100);
            robotStop(0);
            chinh_lai_vi_tri_laser_trai(176, 1000);
        } 
        else if (robot_position == 2) {
            chinh_lai_vi_tri_laser_sau(101, 100);
            robotStop(0);
            chinh_lai_vi_tri_laser_trai(176, 1000);
        } 
        else if (robot_position == 3) {
            chinh_lai_vi_tri_laser_sau(154, 100);
            robotStop(0);
            chinh_lai_vi_tri_laser_trai(176, 1000);
        }
    } 
    else if (tay_2_co_qua || tay_3_co_qua) {
        if (robot_position == 1) {
            chinh_lai_vi_tri_laser_sau(5, 100);
            robotStop(0);
            chinh_lai_vi_tri_laser_trai(193, 1000); /// trg hop tay 3 vi trí 1
        } 
        else if (robot_position == 2) {
            chinh_lai_vi_tri_laser_sau(59, 100);
            robotStop(0);
            chinh_lai_vi_tri_laser_trai(176, 1000);
        } 
        else if (robot_position == 3) {
            chinh_lai_vi_tri_laser_sau(113, 100);
            robotStop(0);
            chinh_lai_vi_tri_laser_trai(176, 1000);
        }
    }
		
			robotStop(0);
			// do chan len dat
			su_dung_chan(495);
			for(i=0;i<250;i++)	{
				while(abs(bientrochansauValue - target_chan_sau) > 10)	{ vTaskDelay(1); if(!wantExit())	break;}
					}		
			dat_hop_vao_o_tang2();	
}

void quyet_dinh_dat_o_nao (void){
		kiem_tra_so_qua_tren_tay();
		if (so_qua_tren_tay > 2) { // neu hon 2 qua tren tay
				be_len_dat_xanh();
				}
		else {
				be_len_dat_xanh_1_qua_tren_3();
		
				}
}

void bat_dau_chay_xanh (void) {
    if (Start == 0 && mode_chay_rung == 1) {
        tudonghoantoan();
    }
    else if (Start == 0 && mode_chay_rung == 2) {
        retry_zone_2();
    }
    else if (Start == 0 && mode_nhat_hop == 1) {
        nhat_hop_zone3_xanh();
    }
}
	
