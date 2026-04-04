extern int Vi_tri;
extern int da_lay_tay4;
extern int TinHieu_ChuanBi_GapThang;
extern int TinHieu_ChuanBi_GapTrai ;
extern int TinHieu_ChuanBi_GapPhai;

void run_align_center(void);
void kiem_tra_so_qua_tren_tay(void);


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
	
				robotRunAngle(-150 - vu_khi*2,30,5,0.7);
				for(i=0;i<100;i++)
				{
					while(lazePhaiValue < vu_khi - 20)	
					{
						if(!wantExit())	break;
					}
				}

				target_chan_truoc = 610, target_chan_sau =600;
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
				Tay_kep_xuong;
			
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
				
				speed_chan_sau =30;
				speed_chan_truoc = 70;
				
				target_chan_truoc = 610, target_chan_sau = 600;
				
				vTaskDelay(4000);
				
				robotStop(30);
				
				target_chan_truoc = 665, target_chan_sau = 660;
				
				Tay_kep_len; 
				
				vTaskDelay(5000);
				
				robotRun(goc_ve,30);
				robotRotate(-900,-1.2,0);
//				
				RESET_ENCODER(); 
//								
				Nang_cuc_nhanh();
//				
				while(_robotIMUAngle >-750)	
				{
					vTaskDelay (5); 
					if(!wantExit())	break;
					if(_robotIMUAngle < -450)		target_chan_truoc = 265, target_chan_sau = 265;
				}
 
					
	
				robotRunAngle(900,8,-900,0.5);
				
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
				speed_chan_sau =20;
				speed_chan_truoc = 45;
				target_chan_truoc = 255, target_chan_sau = 255;
//				
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
			chinh_lai_vi_tri_laser_phai_custom(vi_tri_cua_rung_xanh_1_lazer_phai_tay_41 , 1000);
	}
	else if (TinHieu_ChuanBi_GapThang == 0) {
			chinh_lai_vi_tri_laser_phai_custom(vi_tri_cua_rung_xanh_1_lazer_phai_tay_41 - 15, 1000);
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
			chinh_lai_vi_tri_laser_phai_custom(vi_tri_cua_rung_xanh_2_lazer_phai_tay_41 - 15 , 1000);
	}
	else if (TinHieu_ChuanBi_GapThang == 1) {
			chinh_lai_vi_tri_laser_phai_custom(vi_tri_cua_rung_xanh_2_lazer_phai_tay_41  , 1000);
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
			chinh_lai_vi_tri_laser_phai_custom(vi_tri_cua_rung_xanh_3_lazer_phai_tay_41  , 1000);
	}
	else if (TinHieu_ChuanBi_GapThang == 0) {
			chinh_lai_vi_tri_laser_phai_custom(vi_tri_cua_rung_xanh_3_lazer_phai_tay_41 - 15 , 1000);
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
	
			su_dung_chan(697);
		
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
	
	robotRunAngle(-900,38,900,0.9);
		for(i=0;i<250;i++)
					{
						while(lazeSauValue > 115)	
						{	
							vTaskDelay (1);
							if(!wantExit())	break;
						}
				}
		
	robotRunAngle(-900,28,900,0.9);
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
							while( CB_vtri_leo == 1 ||CB_Ha_Sau == 1 || CB_Cap_Thanh_Sau == 0)	
							{	
								Bam_thanh_laser_phai(8,-900,900,vitri - 15,2,-350,30);
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
							while( CB_vtri_leo == 1 ||CB_Ha_Sau == 1 || CB_Cap_Thanh_Sau == 0)	
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
	
	robotRunAngle(-900,35,900,0.9);
		for(i=0;i<250;i++)
					{
						while(lazeSauValue > 115)	
						{	
							vTaskDelay (1);
							if(!wantExit())	break;
						}
				}
		
		robotRunAngle(-900,28,900,0.9);
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
							Bam_thanh_laser_trai(20,-900,900,vitri + 15,2,150,30);
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
			// chay toi khi laser sau cham 1
			robotRunAngle(-900,8,900,0.5);
			for(i=0;i<250;i++)	
		{
			while(abs(bientrochansauValue - target_chan_sau) > 10)	{
				vTaskDelay(1); if(!wantExit())	break;}
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
					
			KT_Ha_Tay = 1;
	// chinh lai vi tri cho tay gap
		if (da_lay_tay1 == 0 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
					robotRunAngle(-900,5,900,0.5);
					vTaskDelay (2000);
		
					chinh_lai_vi_tri_laser_trai(vitri_tay41, 1000);
					robotStop(0);
						
			}
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
					robotRunAngle(-900,5,900,0.5);
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
	KT_Ha_Tay_phai = 1;
	if (da_lay_tay1 == 0 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
			chinh_lai_vi_tri_laser_trai(vitri_tay41_laser_trai_GapQua, 200);
			robotRunAngle(-900,5,900,0.5);
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
				for(i=0;i<250;i++)	
			{
				while(abs(bientrochansauValue - target_chan_sau) > 10)	{vTaskDelay(1); if(!wantExit())	break;}
			}		
				robotRunAngle(0,6,900,0.1);
				vTaskDelay(2500);
		}
	else if (da_lay_tay1 == 1 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
			chinh_lai_vi_tri_laser_trai(vitri_tay41_laser_trai_GapQua , 200);
		
			robotRunAngle(-900,5,900,0.5);
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
				for(i=0;i<250;i++)	
			{
				while(abs(bientrochansauValue - target_chan_sau) > 10)	{vTaskDelay(1); if(!wantExit())	break;}
			}
				robotRunAngle(0,6,900,0.1);
				vTaskDelay(2500);
		}
	else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
			chinh_lai_vi_tri_laser_trai(vitri_tay41_laser_trai_GapQua , 200);
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
				robotRunAngle(0,7,900,0.1);
				vTaskDelay(2500);
		}
	
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 0) {
			chinh_lai_vi_tri_laser_trai(vitri_tay41_laser_trai_GapQua , 200);
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
				robotRunAngle(0,7,900,0.1);
				vTaskDelay(2500);
		}
		if (TinHieu_ChuanBi_GapThang == 1 ) {
				chuan_bi_gap_thang_xanh_4();
		}
		robotStop(0); 
}

void chuan_bi_gap_trai_200_duoi_5 (void ) {

	if (da_lay_tay1 == 0 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
				// chuan bi xoay truoc sang trai
					speed_tay_xoay = 240;
					target_xoay_tay = vi_tri_tay_4_trai_duoi;
					Kep_phai_4_ra;
		
					ha_sat_xuong();
					for(i=0;i<250;i++)	
						{
							while(abs(bientrochansauValue - target_chan_sau) > 10)	{vTaskDelay(1); if(!wantExit())	break;}
						}	
					robotRunAngle(-900,5,900,0.5);
						
					for(i=0;i<1550;i++)
						{
							while(HT_3 == 0 && HT_4 == 0)	
							{	
								if(!wantExit())	break;
								vTaskDelay (1);
							}
						}
						
			robotStop(10); 
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
	
			//// dung tay 3 gap duoi lan 2
		else if (da_lay_tay1 == 1 && da_lay_tay4_duoi == 0) {
				// chuan bi xoay truoc sang trai
					speed_tay_xoay = 240;
					target_xoay_tay = vi_tri_tay_3_trai_duoi;
					Kep_phai_4_ra;
			
					ha_sat_xuong();
					for(i=0;i<250;i++)	
				{
					while(abs(bientrochansauValue - target_chan_sau) > 10)	{vTaskDelay(1); if(!wantExit())	break;}
				}
				
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

void chuan_bi_gap_trai_200_duoi_ko_thanh (void ) {
	if (da_lay_tay1 == 0 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
				// chuan bi xoay truoc sang trai
					speed_tay_xoay = 200;
					target_xoay_tay = vi_tri_tay_4_trai_duoi;
					ha_sat_xuong();
		
					for(i=0;i<250;i++)	
						{
							while(abs(bientrochansauValue - target_chan_sau) > 10)	{vTaskDelay(1); if(!wantExit())	break;}
						}	
					robotRunAngle(-900,5,900,0.5);
		
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
	
			//// dung tay 3 gap duoi lan 2
		else if (da_lay_tay1 == 1 && da_lay_tay4_duoi == 0) {
						// chuan bi xoay truoc sang trai
					speed_tay_xoay = 240;
					target_xoay_tay = vi_tri_tay_3_trai_duoi;
					Kep_phai_3_ra;
			
					ha_sat_xuong();
					for(i=0;i<250;i++)	
				{
					while(abs(bientrochansauValue - target_chan_sau) > 10)	{vTaskDelay(1); if(!wantExit())	break;}
				}

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
		if (TinHieu_ChuanBi_GapThang == 1) { 
			kiem_tra_huong_quay_tay_gap_phia_truoc();
		// chay toi khi mat cam bien sau
		robotRunAngle(-900,8,900,0.5);
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
			
		di_tren_buc_khong_thanh_2_ben();
		}
		
}

void chuan_bi_gap_phai_200_duoi_ko_thanh (void ) {
	
	if (da_lay_tay1 == 0 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
						// chuan bi xoay truoc sang phai
					speed_tay_xoay = 240;
					target_xoay_tay = vi_tri_tay_4_phai_duoi;
					Kep_phai_4_ra;
		
					ha_sat_xuong();
					for(i=0;i<250;i++)	
				{
					while(abs(bientrochansauValue - target_chan_sau) > 10)	{vTaskDelay(1); if(!wantExit())	break;}
				}
				
			robotRunAngle(0,5,900,0.5);
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
				// chuan bi xoay truoc sang phai
					speed_tay_xoay = 240;
					target_xoay_tay = vi_tri_tay_3_phai_duoi;
					Kep_phai_3_ra;
					ha_sat_xuong();
					for(i=0;i<250;i++)	
						{
							while(abs(bientrochansauValue - target_chan_sau) > 10)	{vTaskDelay(1); if(!wantExit())	break;}
						}
			robotRunAngle(-900,5,900,0.5);
			for(i=0;i<150;i++)
					{
						while(CB_Ha_Sau == 0)	
						{	
							vTaskDelay (1);
							if(!wantExit())	break;
						}
					}

			robotRunAngle(0,5,900,0.5);
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
		
		if (TinHieu_ChuanBi_GapThang == 1) { 
			kiem_tra_huong_quay_tay_gap_phia_truoc();
		// chay toi khi mat cam bien sau
		robotRunAngle(-900,8,900,0.5);
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
			
		di_tren_buc_khong_thanh_2_ben();
		}
}

void Xuong_bac_200_xanh_4(void)
{	
	int vitri_tay41 = vitri_tay41_laser_trai_GapQua;

	Xuong_bac_200(-900, 900);		
	
	// KHONG CO TIN HIEU GAP
	if (TinHieu_ChuanBi_GapThang == 0 && TinHieu_ChuanBi_GapTrai == 0 && TinHieu_ChuanBi_GapPhai == 0) {
		Nang_cuc_nhanh();
		
		target_chan_truoc = Min_chan_truoc + 250;
		target_chan_sau = Min_chan_sau + 240;
		
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
	if (TinHieu_ChuanBi_GapThang == 1) {
			su_dung_chan(565);	
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
			chuan_bi_gap_thang_xanh_4();
				}
}

void Lay_ben_trai_bac_200_duoi_xanh_ko_thanh(void) {
			Lay_ben_trai_bac_200_duoi_ko_thanh();
			robotStop(0);
			
	if (TinHieu_ChuanBi_GapThang == 1) {
		kiem_tra_huong_quay_tay_gap_phia_truoc();
				// chay toi khi mat cam bien sau
		robotRunAngle(-900,8,900,0.5);
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
			
		di_tren_buc_khong_thanh_2_ben();
				}
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
				Nang_cuc_nhanh();
				
				target_chan_truoc = Min_chan_truoc + 250;
				target_chan_sau = Min_chan_sau + 240;
			
				robotRunAngle(-900,8,900,0.5);
	
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
		for(i=0;i<50;i++)		
			{
				while(abs(bientrochansauValue - target_chan_sau) > 10)	{vTaskDelay(1); if(!wantExit())	break;}
			}
		
		robotRunAngle(-900,8,900,0.5);
		for(i=0;i<1550;i++)
				{
//						while(CB_vtri_leo == 0 || CB_Ha_Sau == 0)	
					while( CB_Ha_Sau == 0 )	
					{	
						if(!wantExit())	break;
						vTaskDelay (1);
					}
				}
				
		robotStop(0);
		KT_Ha_Tay = 1;
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
}


// CHUAN BI GAP PHAI XANH 7 VA 10
void chuan_bi_gap_phai_200_tren_7_10 (void ) {
	if (da_lay_tay1 == 0 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
			KT_Ha_Tay_phai = 1;
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
			KT_Ha_Tay_phai = 1;
			chinh_lai_vi_tri_laser_trai(vitri_tay41_laser_trai_GapQua , 200);
			su_dung_chan(565);
				for(i=0;i<250;i++)	
			{
				while(abs(bientrochansauValue - target_chan_sau) > 10)	{vTaskDelay(1); if(!wantExit())	break;}
			}	
			robotRunAngle(0,7,900,0.1);
			vTaskDelay(2500);
		}
	
			/// gap lan 3
	else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {		
			su_dung_chan(265);
			for(i=0;i<50;i++)		
				{
					while(abs(bientrochansauValue - target_chan_sau) > 10)	{vTaskDelay(1); if(!wantExit())	break;}
				}
			// chay toi khi mat cam bien sau
			robotRunAngle(-900,8,900,0.5);
			for(i=0;i<250;i++)
					{
						while(CB_Ha_Sau == 0)	
					{	
						vTaskDelay (1);
						if(!wantExit())	break;
					}
				}
			chinh_lai_vi_tri_laser_trai(vitri_tay41_laser_trai_GapQua , 200);
			robotStop(10); 
			KT_Ha_Tay_phai = 1;

			su_dung_chan(565);
				for(i=0;i<250;i++)	
			{
				while(abs(bientrochansauValue - target_chan_sau) > 10)	{vTaskDelay(1); if(!wantExit())	break;}
			}	
			robotRunAngle(0,7,900,0.1);
			vTaskDelay(2500);
		}
	/// gap lan 4
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 0) {
			su_dung_chan(265);
			for(i=0;i<50;i++)		
				{
					while(abs(bientrochansauValue - target_chan_sau) > 10)	{vTaskDelay(1); if(!wantExit())	break;}
				}
			// chay toi khi mat cam bien sau
			robotRunAngle(-900,8,900,0.5);
			for(i=0;i<250;i++)
					{
						while(CB_Ha_Sau == 0)	
					{	
						vTaskDelay (1);
						if(!wantExit())	break;
					}
				}
			chinh_lai_vi_tri_laser_trai(vitri_tay41_laser_trai_GapQua , 200);
			robotStop(10); 
			KT_Ha_Tay_phai = 1;

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
		robotRunAngle(-900,8,900,0.5);
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
		for(i=0;i<50;i++)		
	{
		while(abs(bientrochansauValue - target_chan_sau) > 10)	{vTaskDelay(1); if(!wantExit())	break;}
	}
	
	
		vTaskDelay(1000);
		// chay toi khi mat cam bien sau
		robotRunAngle(-900,8,900,0.5);
		for(i=0;i<250;i++)
				{
					while(CB_vtri_leo == 0 || CB_Ha_Sau == 0)

					{	
						vTaskDelay (1);
						if(!wantExit())	break;
					}
				}
		robotStop(0);
				
		KT_Ha_Tay = 1;
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
		KT_Ha_Tay_trai = 1;
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
				robotRunAngle(1800,7,900,0.5);
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
			Lay_ben_trai_bac_200_tren();
			robotRunAngle(0,8,900,0.8);
			vTaskDelay(3000);
			robotStop(0);
			
	if (TinHieu_ChuanBi_GapThang == 1) {
			kiem_tra_huong_quay_tay_gap_phia_truoc();
			chuan_bi_gap_thang_xanh_9();
				}
}


void xuong_bac_200_xanh_12(void) {
		Xuong_bac_200(-900, 900);
		if (TinHieu_ChuanBi_GapThang == 0 && TinHieu_ChuanBi_GapTrai == 0 && TinHieu_ChuanBi_GapPhai == 0) {
				su_dung_chan(265);
				for(i=0;i<50;i++)		
					{
						while(abs(bientrochansauValue - target_chan_sau) > 10)	{vTaskDelay(1); if(!wantExit())	break;}
					}
				// chay toi khi mat cam bien sau
				robotRunAngle(-900,10,900,0.8);
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
		action_table[0][2][4]  = Lay_ben_trai_bac_200_duoi_xanh_5;
		action_table[0][2][5]  = Lay_ben_trai_bac_200_duoi_xanh_ko_thanh;
		action_table[0][2][7]  = Lay_ben_trai_bac_200_duoi_xanh_ko_thanh;
		action_table[0][2][10] = Lay_ben_trai_bac_200_duoi_xanh_ko_thanh;
		
		action_table[0][2][8]  = Lay_ben_trai_bac_200_tren_xanh_9;
		action_table[0][2][11] = Lay_ben_trai_bac_200_tren_xanh_9;

//    /* =========================================
//       move 0 , action 3, dung lai de lay ben PHAI
//       ========================================= */
		action_table[0][3][5] = Lay_ben_phai_bac_200_tren_xanh_4;
		action_table[0][3][6] = Lay_ben_phai_bac_200_tren_xanh_4;
		action_table[0][3][8] = Lay_ben_phai_bac_200_tren_xanh_7;
		
		action_table[0][3][9] = Lay_ben_phai_bac_200_duoi_xanh_8; 
		action_table[0][3][12] = Lay_ben_phai_bac_200_duoi_xanh_8; 
		
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

//////////////// ************** CHAY TU DONG
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
void kiem_tra_qua_tay_nao (void) {
	if (tay_4_co_qua == 1 && tay_1_co_qua == 0 && tay_2_co_qua == 0 && tay_3_co_qua == 0)	{
			speed_tay_xoay = 100;
			target_xoay_tay = vi_tri_dat_hop_3_4;
			for(i=0;i<150;i++)	{ 
					while((abs(bientroxoaytayValue - target_xoay_tay) > 5) )	{vTaskDelay(1); if(!wantExit())	break;}
			}
			tin_hieu_dat_hop_3_4 = 1;
	}
	// moi tay 3 co qua
	else if  (tay_4_co_qua == 0 && tay_1_co_qua == 0 && tay_2_co_qua == 0 && tay_3_co_qua == 1)	{
			speed_tay_xoay = 100;
			target_xoay_tay = vi_tri_dat_hop_3_4;
			for(i=0;i<150;i++)	{ 
					while((abs(bientroxoaytayValue - target_xoay_tay) > 5) )	{vTaskDelay(1); if(!wantExit())	break;}
			}
			tin_hieu_dat_hop_3_4 = 1;
	}
	// moi tay 2 co qua
	else if  (tay_4_co_qua == 0 && tay_1_co_qua == 0 && tay_2_co_qua == 1 && tay_3_co_qua == 0)	{
			speed_tay_xoay = 100;
			target_xoay_tay = vi_tri_dat_hop_1_2;
			for(i=0;i<150;i++)	{ 
					while((abs(bientroxoaytayValue - target_xoay_tay) > 5) )	{vTaskDelay(1); if(!wantExit())	break;}
			}
			tin_hieu_dat_hop_1_2 = 1;
	}
	// moi tay 1 co qua
	else if  (tay_4_co_qua == 0 && tay_1_co_qua == 1 && tay_2_co_qua == 0 && tay_3_co_qua == 0)	{
			speed_tay_xoay = 100;
			target_xoay_tay = vi_tri_dat_hop_1_2;
			for(i=0;i<150;i++)	{ 
					while((abs(bientroxoaytayValue - target_xoay_tay) > 5) )	{vTaskDelay(1); if(!wantExit())	break;}
			}
			tin_hieu_dat_hop_1_2 = 1;
	}
	
	// qua tay 4 1
	else if (tay_4_co_qua == 1 && tay_1_co_qua == 1 && tay_2_co_qua == 0 && tay_3_co_qua == 0)	{
			speed_tay_xoay = 100;
			target_xoay_tay = vi_tri_dat_hop_1_2;
			for(i=0;i<150;i++)	{ 
					while((abs(bientroxoaytayValue - target_xoay_tay) > 5) )	{vTaskDelay(1); if(!wantExit())	break;}
			}
			tin_hieu_dat_hop_1_2= 1;
	}
	// qua tay 4 1 2
	else if ((tay_4_co_qua == 1 && tay_1_co_qua == 1 && tay_2_co_qua == 1 && tay_3_co_qua == 0))	{
			speed_tay_xoay = 100;
			target_xoay_tay = vi_tri_dat_hop_1_2;
			for(i=0;i<150;i++)	{ 
					while((abs(bientroxoaytayValue - target_xoay_tay) > 5) )	{vTaskDelay(1); if(!wantExit())	break;}
			}
			tin_hieu_dat_hop_1_2 = 1;
	}
		// qua tay 4 1 2 3
		else if (tay_4_co_qua == 1 && tay_1_co_qua == 1 && tay_2_co_qua == 1 && tay_3_co_qua == 1)	{
			speed_tay_xoay = 100;
			target_xoay_tay = vi_tri_dat_hop_1_2;
			for(i=0;i<150;i++)	{ 
					while((abs(bientroxoaytayValue - target_xoay_tay) > 5) )	{vTaskDelay(1); if(!wantExit())	break;}
			}
			tin_hieu_dat_hop_1_2 = 1;
	}
		
	// vua dat xong tay 1 con tay 2 va tay 4
		else if (tay_4_co_qua == 1 && tay_1_co_qua == 0 && tay_2_co_qua == 1 && tay_3_co_qua == 0)	{
			speed_tay_xoay = 100;
			target_xoay_tay = vi_tri_dat_hop_1_2;
			for(i=0;i<150;i++)	{ 
					while((abs(bientroxoaytayValue - target_xoay_tay) > 5) )	{vTaskDelay(1); if(!wantExit())	break;}
			}
			tin_hieu_dat_hop_1_2 = 1;
	}
		// vua dat xong tay 1 2 con tay 3 4
		else if (tay_4_co_qua == 1 && tay_1_co_qua == 0 && tay_2_co_qua == 0 && tay_3_co_qua == 1){
			speed_tay_xoay = 100;
			target_xoay_tay = vi_tri_dat_hop_3_4;
			for(i=0;i<150;i++)	{ 
					while((abs(bientroxoaytayValue - target_xoay_tay) > 5) )	{vTaskDelay(1); if(!wantExit())	break;}
			}
			tin_hieu_dat_hop_3_4 = 1;
	}


}

void kiem_tra_qua_tay_nao_xuong_rung (void) {
	if (tay_4_co_qua == 1 && tay_1_co_qua == 0 && tay_2_co_qua == 0 && tay_3_co_qua == 0)	{
			speed_tay_xoay = 100;
			target_xoay_tay = vi_tri_dat_hop_3_4;
			tin_hieu_dat_hop_3_4 = 1;
	}
	// moi tay 3 co qua
	else if  (tay_4_co_qua == 0 && tay_1_co_qua == 0 && tay_2_co_qua == 0 && tay_3_co_qua == 1)	{
			speed_tay_xoay = 100;
			target_xoay_tay = vi_tri_dat_hop_3_4;
			tin_hieu_dat_hop_3_4 = 1;
	}
	// moi tay 2 co qua
	else if  (tay_4_co_qua == 0 && tay_1_co_qua == 0 && tay_2_co_qua == 1 && tay_3_co_qua == 0)	{
			speed_tay_xoay = 100;
			target_xoay_tay = vi_tri_dat_hop_1_2;
			tin_hieu_dat_hop_1_2 = 1;
	}
	// moi tay 1 co qua
	else if  (tay_4_co_qua == 0 && tay_1_co_qua == 1 && tay_2_co_qua == 0 && tay_3_co_qua == 0)	{
			speed_tay_xoay = 100;
			target_xoay_tay = vi_tri_dat_hop_1_2;
			tin_hieu_dat_hop_1_2 = 1;
	}
	
	// qua tay 4 1
	else if (tay_4_co_qua == 1 && tay_1_co_qua == 1 && tay_2_co_qua == 0 && tay_3_co_qua == 0)	{
			speed_tay_xoay = 100;
			target_xoay_tay = vi_tri_dat_hop_1_2;
			tin_hieu_dat_hop_1_2= 1;
	}
	// qua tay 4 1 2
	else if ((tay_4_co_qua == 1 && tay_1_co_qua == 1 && tay_2_co_qua == 1 && tay_3_co_qua == 0))	{
			speed_tay_xoay = 100;
			target_xoay_tay = vi_tri_dat_hop_1_2;
			tin_hieu_dat_hop_1_2 = 1;
	}
		// qua tay 4 1 2 3
		else if (tay_4_co_qua == 1 && tay_1_co_qua == 1 && tay_2_co_qua == 1 && tay_3_co_qua == 1)	{
			speed_tay_xoay = 100;
			target_xoay_tay = vi_tri_dat_hop_1_2;
			tin_hieu_dat_hop_1_2 = 1;
	}
		
	// vua dat xong tay 1 con tay 2 va tay 4
		else if (tay_4_co_qua == 1 && tay_1_co_qua == 0 && tay_2_co_qua == 1 && tay_3_co_qua == 0)	{
			speed_tay_xoay = 100;
			target_xoay_tay = vi_tri_dat_hop_1_2;
			tin_hieu_dat_hop_1_2 = 1;
	}
		// vua dat xong tay 1 2 con tay 3 4
		else if (tay_4_co_qua == 1 && tay_1_co_qua == 0 && tay_2_co_qua == 0 && tay_3_co_qua == 1){
			speed_tay_xoay = 100;
			target_xoay_tay = vi_tri_dat_hop_3_4;
			tin_hieu_dat_hop_3_4 = 1;
	}


}

void DatKFSxanh(int vitri)
{
	kiem_tra_so_qua_tren_tay();
	kiem_tra_qua_tay_nao_xuong_rung(); // ham kiem tra co qua tay nao de dat
	
	Nang_thuong();
	target_chan_truoc = 335;
	target_chan_sau = 335;
	
	for(i=0;i<150;i++)		
	{
		while(abs(bientrochansauValue - target_chan_sau) > 10)	{vTaskDelay(1); if(!wantExit())	break;}
	}
	vTaskDelay(4000); 
	
	chinh_lai_vi_tri_laser_phai_custom(190, 1000);
	

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

		/// ngua ra sau ne hop
		speed_tay_gat1 = 100;
		target_tay_gat1 = vitri_tay1home -40;
		speed_tay_gat2 = 100;
		target_tay_gat2 = vitri_tay1home -40;
	
	for(i=0;i<550;i++)	
	{	
			while(lazeTraiValue > 178)	
			{	
				Bam_laser_sau(5,0,900, vitri, 1, -100, 10);
				vTaskDelay(5); 
				if(!wantExit())	break;
			}
	}	

		robotStop(0);

	// do chan len dat qua
		su_dung_chan(710);
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

void dat_qua_tay_1_2_xanh(void) {
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
	
	 else if (CB_kep_2_2 == 0) {
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

void dat_qua_tay_4_3_xanh(void) {
	if (CB_kep_3_2 == 0) {
		speed_tay_gat1 = 50;
		target_tay_gat1 = vitri_tay1home - 115;

		for(i=0;i<250;i++)	
		{
			while(abs(bientrochansauValue - target_chan_sau) > 4)	{
				vTaskDelay(1); if(!wantExit())	break;}
		}	
		Kep_phai_3_ra;
	}
	
	if (CB_kep_4_2 == 0) {
		speed_tay_gat2 = 250;
		target_tay_gat2 = vitri_tay2home - 115;
			
		for(i=0;i<50;i++)	{ 
			while(abs(bientrodaytay1Value - target_tay_gat1) > (10) || abs(bientrodaytay2Value - target_tay_gat2) > 10 )	
			{vTaskDelay(1); if(!wantExit())	break;}
			}
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

void chuan_bi_dat_hop_tang3 (void) {
		if (tin_hieu_dat_hop_3_4 == 1 && tay_4_co_qua == 1 ) {
				Tay2_len;
				for(i=0;i<50;i++)	{ 
						while(CB_xilanh_tay_2 == 1 )	
						{vTaskDelay(1); if(!wantExit())	break;}
							}
//				speed_tay_gat2 = 150;
//				target_tay_gat2 = vitri_tay1home - 10;	
		}
		else if (tin_hieu_dat_hop_1_2 == 1 && tay_1_co_qua == 1 ) {
				Tay1_len;
				for(i=0;i<50;i++)	{ 
						while(CB_xilanh_tay_1 == 1 )	
						{vTaskDelay(1); if(!wantExit())	break;}
							}
//				speed_tay_gat1 = 150;
//				target_tay_gat1 = vitri_tay1home + 10;
		}
		
		else if (tin_hieu_dat_hop_1_2 == 1 && tay_2_co_qua == 1 ) {
				Tay2_len;
				for(i=0;i<50;i++)	{ 
						while(CB_xilanh_tay_2 == 1 )	
						{vTaskDelay(1); if(!wantExit())	break;}
							}
//				speed_tay_gat2 = 150;
//				target_tay_gat2 = vitri_tay1home + 10;
		}
		
		else if (tin_hieu_dat_hop_3_4 == 1 && tay_3_co_qua == 1) {
				Tay1_len;
				for(i=0;i<50;i++)	{ 
						while(CB_xilanh_tay_1 == 1 )	
						{vTaskDelay(1); if(!wantExit())	break;}
							}
//				speed_tay_gat1 = 150;
//				target_tay_gat1 = vitri_tay1home -10;
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
		while(Quang_tro2 > 40)	{	
		vTaskDelay (1);
		if(!wantExit())	break;
					}
	}
	vTaskDelay (2000);
	nhay_den_lan_1 = 1;
	
	// rut chan va nghieng tay xuong
	if (nhay_den_lan_1 == 1 ) {
			su_dung_chan(350);
			chuan_bi_dat_hop_tang3();
			vTaskDelay (3000);
		
			for(i=0;i<1000;i++)	
			{
		while(Quang_tro2 > 40)	{	
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
			vTaskDelay (3000);
			for(i=0;i<1000;i++)	
			{
		while(Quang_tro2 > 40)	{	
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
	
	robotStop(0);

}
}

// 
void be_len_dat_xanh_1_qua_tren_3 (void) {
	kiem_tra_so_qua_tren_tay();
	kiem_tra_qua_tay_nao();
		// cho nhay den thi dat
	for(i=0;i<1000;i++)	
	{
		while(Quang_tro2 > 40)	{	
		vTaskDelay (1);
		if(!wantExit())	break;
					}
	}
	vTaskDelay (2000);
	nhay_den_lan_1 = 1;
	
	// rut chan va nghieng tay xuong
	if (nhay_den_lan_1 == 1 ) {
			su_dung_chan(350);
			chuan_bi_dat_hop_tang3();
			vTaskDelay (3000);
		
			for(i=0;i<1000;i++)	
			{
		while(Quang_tro2 > 40)	{	
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
	}
	
	robotStop(0);

}




void test_phun_ra (void) {
			Tay2_len;
			Tay1_len;
}

void test_dat_kieu_moi (void) {
			Tay2_len;
			for(i=0;i<50;i++)	{ 
									while(CB_xilanh_tay_1 == 1 )	{vTaskDelay(1); if(!wantExit())	break;}
						
						}
			speed_tay_gat2 = 150;
			target_tay_gat2 = vitri_tay2home - 60;
			
		for(i=0;i<150;i++)	{ 
			while(abs(bientrodaytay2Value - target_tay_gat2) > 10 )	
			{vTaskDelay(1); if(!wantExit())	break;}
			}
			Kep_phai_4_ra;
			su_dung_chan(550);
				for(i=0;i<250;i++)	
		{
			while(abs(bientrochansauValue - target_chan_sau) > 10)	{
				vTaskDelay(1); if(!wantExit())	break;}
		}	
			
}

// // HAM LUI LAI DE DAT VAO O BAC 3
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

// // HAM LUI LAI DE DAT VAO O BAC 3
void dat_full_tang_2 (void) {
			Tay2_len;
			Tay1_len;
			for(i=0;i<50;i++)	{ 
						while(CB_xilanh_tay_2 == 1|| CB_xilanh_tay_2 == 1 )	
						{vTaskDelay(1); if(!wantExit())	break;}
							}
						
		dat_qua_tay_1_2_xanh();
		speed_tay_xoay = 100;
		target_xoay_tay = vi_tri_dat_hop_1_2 + 6;
		for(i=0;i<150;i++)	{ 
					while((abs(bientroxoaytayValue - target_xoay_tay) > 5) )	{vTaskDelay(1); if(!wantExit())	break;}
			}
		dat_qua_tay_1_2_xanh();

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
		while(quangTroValue > 35)	{	
		vTaskDelay (1);
		if(!wantExit())	break;
					}
	}
	
	Tay_kep_mo;
	vTaskDelay (40000);
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
		if (hoan_thanh_chay_rung == 1 ) DatKFSxanh(54),hoan_thanh_chay_rung = 2 ;
		if (hoan_thanh_chay_rung== 2  ) be_len_dat_xanh(),hoan_thanh_chay_rung = 3;
//		if (hoan_thanh_chay_rung== 3	) chuan_bi_dat_tang_3(),hoan_thanh_chay_rung = 4;
//		if (hoan_thanh_chay_rung== 4	) dat_full_tang_2(),hoan_thanh_chay_rung = 5;

}

void retry_zone_2(void) {

		Run_All_Blocks_From_Queue_san_xanh();

	// len dat hop
		if (hoan_thanh_chay_rung == 1 ) DatKFSxanh(50),hoan_thanh_chay_rung = 2 ;
		if (hoan_thanh_chay_rung== 2  ) dat_hop_vao_o(),hoan_thanh_chay_rung = 3;
//		if (hoan_thanh_chay_rung== 3	) chuan_bi_dat_tang_3(),hoan_thanh_chay_rung = 4;
//		if (hoan_thanh_chay_rung== 4	) dat_full_tang_2(),hoan_thanh_chay_rung = 5;
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

void chon_o_retry3(void) {
		if (id_dat_hop == 1) { retry_zone_3_o_1(50);}
		else if (id_dat_hop == 2) { retry_zone_3(106);}
		else if (id_dat_hop == 3) { retry_zone_3(159);}

}

//// ham nhat lai hop roi dat vao o
//void chon_o_nhat_hop_xanh(void) {

//		if (nhat_dat_hop == 1) {
//				chinh_lai_vi_tri_laser_phai_zone3_do(208, 200);
//			}
//		else if (nhat_dat_hop == 2) {
//				chinh_lai_vi_tri_laser_phai_zone3_do(254, 200);
//			}
//		else if (nhat_dat_hop == 3) {
//				chinh_lai_vi_tri_laser_phai_zone3_do(302, 200);
//			}
//		else if (nhat_dat_hop == 4) {
//				robotRotate(900,1,0);
//				while(robotFixAngle()){
//					vTaskDelay (1); 
//					if(!wantExit())	break;
//				}
//			}

//			robotStop(0);
//		if (nhat_dat_hop == 1|| nhat_dat_hop == 2 || nhat_dat_hop == 3) {
////				su_dung_chan(520);
//				su_dung_chan(480);
//				robotRunAngle(1800, 7, 0, 0.5);
//				for(i=0;i<550;i++)	
//				{	
//						while(lazeSauValue > 10)	
//						{	
//							vTaskDelay(1); 
//							if(!wantExit())	break;
//						}
//				}
//			robotStop(0);
//				
//			Tay2_len;
//			for(i=0;i<50;i++)	{ 
//									while(CB_xilanh_tay_2 == 1 )	{vTaskDelay(1); if(!wantExit())	break;}
//							}
//			speed_tay_gat2 = 50;
//			target_tay_gat2 = vitri_tay2home - 120;
//			vTaskDelay(7000);

//			for(i=0;i<5;i++)	{  // kiem tra neu hop thap thi dua chan cao hon
//					if(abs(bientrodaytay2Value - target_tay_gat2) > (10) ){
//							su_dung_chan(495);
//							vTaskDelay(10); if(!wantExit())	break;}
//					}
//			
//			for(i=0;i<5;i++)	{ // kiem tra neu hop cao thi dua chan thap hon
//					if(abs(bientrodaytay2Value - target_tay_gat2) > (10) ){
//							su_dung_chan(465);
//							vTaskDelay(10); if(!wantExit())	break;}
//					}

//			Kep_phai_4_ra;
//	// dat xong ve home tay
//		speed_tay_gat1 = 250;
//		target_tay_gat1 = vitri_tay1home ;
//		speed_tay_gat2 = 250;
//		target_tay_gat2 = vitri_tay2home ;
//		for(i=0;i<50;i++)	{ 
//				while(abs(bientrodaytay2Value - target_tay_gat2) > (30)  )	
//				{vTaskDelay(1); if(!wantExit())	break;}
//					}
//						
//	}
//}			


void nhat_hop_zone3_xanh (void) {
		robotRunAngle(1800, 25, 0, 0.5);
		for(i=0;i<550;i++)	
		{	
				while(lazeSauValue > 350)	
				{	
					vTaskDelay(1); 
					if(!wantExit())	break;
				}
		}
		
		robotRunAngle(1500, 30, 0, 0.6);
		for(i=0;i<550;i++)	
		{	
				while(lazeSauValue > 260)	
				{	
					vTaskDelay(1); 
					if(!wantExit())	break;
				}
		}
		
		for(i=0;i<550;i++)	
	{	
			while(lazeSauValue > 219)	
			{	
				Bam_thanh_laser_phai(15,1800,0, 274, 2, -150, 10);
				vTaskDelay(5); 
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
			target_tay_gat2 = Min_tay_gat2 +25  ;
			for(i=0;i<550;i++)	{ 

					while(abs(bientrodaytay2Value - target_tay_gat2)> 10 )	
					{vTaskDelay(1); if(!wantExit())	break;}
				}
			
			vTaskDelay (2000);
			Kep_phai_4_vao;
			
			speed_tay_gat2 = 250;
			target_tay_gat2 = vitri_tay2home;
			for(i=0;i<50;i++)	{ 
					while(abs(bientrodaytay2Value - target_tay_gat2) > ((vitri_tay2home- Min_tay_gat2) / 2 ))
					{vTaskDelay(1); if(!wantExit())	break;}
				}
			
				// lay xong chay lui ve
			robotRunAngle(0,10,0, 0.5);
			vTaskDelay(3000);
				
//			chon_o_nhat_hop_xanh();
			
}


void xac_dinh_vi_tri_robot_xanh(void) {
    // Sai so cho phep (Margin) de nhan dien vung on dinh
    const int margin = 5; 

    // Kiem tra Vi tri 1: Laze Truoc khoang [102-117], Laze Sau khoang [40-54]
    if ((lazeTruocValue >= (102 - margin) && lazeTruocValue <= (117 + margin)) &&
        (lazeSauValue   >= (40  - margin) && lazeSauValue   <= (54  + margin))) {
        robot_position = 1;
    }
    
    // Kiem tra Vi tri 2: Laze Truoc khoang [51-69], Laze Sau khoang [87-104]
    else if ((lazeTruocValue >= (51 - margin) && lazeTruocValue <= (69 + margin)) &&
             (lazeSauValue   >= (87 - margin) && lazeSauValue   <= (104 + margin))) {
        robot_position = 2;
    }
    
    // Kiem tra Vi tri 3: Laze Truoc khoang [1-8], Laze Sau khoang [146-163]
    else if ((lazeTruocValue >= (1 - margin) && lazeTruocValue <= (8 + margin)) &&
             (lazeSauValue   >= (146 - margin) && lazeSauValue   <= (163 + margin))) {
        robot_position = 3;
    }
    
    // Truong hop robot dang di chuyen hoac nam ngoai vung nhan dien
    else {
        robot_position = 1; 
    }
}

void tu_dong_dat_tang2_xanh(void) {
		xac_dinh_vi_tri_robot_xanh();
		if (robot_position == 1) {
				chinh_lai_vi_tri_laser_sau(52,100);
				robotStop(0);
				chinh_lai_vi_tri_laser_trai(177, 1000);
			}
		else if (robot_position == 2) {
				chinh_lai_vi_tri_laser_sau(103,100);
				robotStop(0);
				chinh_lai_vi_tri_laser_trai(177, 1000);
			}
		else if (robot_position == 3) {
				chinh_lai_vi_tri_laser_sau(156,100);
				robotStop(0);
				chinh_lai_vi_tri_laser_trai(177, 1000);
			}
		
			// do chan len dat
			su_dung_chan(480);
			for(i=0;i<250;i++)	
		{
			while(abs(bientrochansauValue - target_chan_sau) > 10)	{
				vTaskDelay(1); if(!wantExit())	break;}
		}		
			dat_hop_vao_o();
			
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

void test_1 (void) {
			su_dung_chan(350);
			speed_tay_xoay = 100;
			target_xoay_tay = vi_tri_dat_hop_1_2;
			for(i=0;i<150;i++)	{ 
					while((abs(bientroxoaytayValue - target_xoay_tay) > 5) )	{vTaskDelay(1); if(!wantExit())	break;}
			}
				Tay2_len;
				for(i=0;i<50;i++)	{ 
						while(CB_xilanh_tay_2 == 1 )	
						{vTaskDelay(1); if(!wantExit())	break;}
							}
				speed_tay_gat2 = 150;
				target_tay_gat2 = vitri_tay1home - 55;
}