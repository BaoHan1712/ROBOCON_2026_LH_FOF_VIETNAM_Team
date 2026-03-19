//**********************************SAN DO*************************************
void Xuat_Phat_Lay_Vu_Khi_Do(int vu_khi, int goc_ve)
 //				RESET_ENCODER(); 
{					
				speed_chan_sau =180;
				speed_chan_truoc = 250;
	
				target_chan_truoc = 350, target_chan_sau = 350;
				Kep = 250;
	
				speed_tay_gat1 = 150;
				target_tay_gat1 = 131;
	
				speed_tay_gat2 = 250;
				target_tay_gat2 = 137;
				robotRunAngle(150 + vu_khi*2,30,5,0.3);

//	
				for(i=0;i<100;i++)
				{
					while(lazeTraiValue < vu_khi )	
					{
						vTaskDelay (1);
						if(!wantExit())	break;
					}
				}
//			
				target_chan_truoc = 596, target_chan_sau =596;
	
				for(i=0;i<250;i++)
				{
					while(lazeTruocValue > 25)	
					{	
	
						Bam_thanh_laser_trai(25,0,0,vu_khi,1,150,15);
						if(!wantExit())	break;
					}
				}
				
				Nang_Ha_Kep = 250;
			
					for(i=0;i<250;i++)
				{
					while(lazeTruocValue > 20)	
					{	
						Bam_thanh_laser_trai(20 ,0,0,vu_khi,1,150,15);
						if(!wantExit())	break;
					}
				}
				
				for(i=0;i<100;i++)
				{
					while(HT_1 == 1 && HT_2 == 1)	
					{				
						Bam_thanh_laser_trai(10,0,0,vu_khi,1,100,15);
						if(!wantExit())	break;
					}
				}
				
				
//				
				robotStop(0);
				
				vTaskDelay (2000);
				
				for(i=0;i<500;i++)
				{
					while(CB_tay_kep_vk_T == 1 || CB_tay_kep_vk_P == 1)	
					{	
						if	(CB_tay_kep_vk_T == 1) robotRun(900,8);
						else if 	(CB_tay_kep_vk_P == 1) robotRun(-900,8);
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
						if	(CB_tay_kep_vk_T == 1) robotRun(900,8);
						else if 	(CB_tay_kep_vk_P == 1) robotRun(-900,8);
						else		robotStop(0);							
						vTaskDelay (1);
						if(!wantExit())	break;
					}
				}
				robotStop(0);				
				speed_chan_sau =30;
				speed_chan_truoc = 70;
				
				target_chan_truoc = 615, target_chan_sau = 615;
//				
				vTaskDelay(4000);
				
				robotStop(30);
//				
				target_chan_truoc = 643, target_chan_sau = 628;
				Nang_Ha_Kep = 0; 
				
				vTaskDelay(5000);
////				
				robotRun(goc_ve,30);
				robotRotate(920,1.2,0);
				
				RESET_ENCODER(); 
								
				speed_chan_sau =80;
				speed_chan_truoc = 130;
				
				while(_robotIMUAngle < 800)	
				{
					vTaskDelay (5); 
					if(!wantExit())	break;
					if(_robotIMUAngle > 450)		target_chan_truoc = 250, target_chan_sau = 250;
				}
//				
//				Nang_Ha_Kep = 0; 
				robotStop(10);		
//				
				robotRunAngle(-900,6,900,0.2);
				
				for(i=0;i<100;i++)
				{
					while(HT_3 == 1 && HT_4 == 1)	
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
//// ******************* VAO CUA RUNG SAN DO ************************
void Vao_rung_mai_1_do(int vitri)
{
	
	 ////// chay toi gan cua vao
	speed_chan_sau = 15;
	speed_chan_truoc = 60;

	target_chan_truoc = 250;
	target_chan_sau = 250;

	
	vTaskDelay(2000);
	
	robotRunAngle(780,25,-900,1.8);
//				
	while(_robotIMUAngle > -895)	
	{
		vTaskDelay (5); 
		if(!wantExit())	break;
	}

	Kep_phai_4_ra;
	
	speed_tay_gat2 = 250;
	target_tay_gat2 = (Min_tay_gat2 + 100);
						
	kiem_tra_huong_quay_tay_gap_phia_truoc();
	
		// Do chan len 1 nua
		su_dung_chan(500);
				
	for(i=0;i<250;i++)	
	{
		while(bientrochansauValue < 490)
								{	
		Bam_thanh_laser_phai(20,900,-900,vitri,2,350,30);
		if(!wantExit())	break;
					}
		
	}
	
	for(i=0;i<250;i++)
				{
					while(lazeSauValue > 25)	
					{	
						Bam_thanh_laser_phai(20,900,-900,vitri,2,350,30);
							vTaskDelay (1);
						if(!wantExit())	break;
					}
				}
			
		su_dung_chan(697);
				
		for(i=0;i<1550;i++)
				{
					while(lazeSauValue > 1 || CB_Ha_Sau == 1)	
					{	
						
						Bam_thanh_laser_phai(8,900,-900,vitri,2,50,30);
						if(!wantExit())	break;
						vTaskDelay (1);
					}
				}

		RESET_ENCODER(); 
	
	for(i=0;i<250;i++) {
	while(abs(ENCODER_RR()) + abs(ENCODER_RL()) < 1600)	
		{	
				Bam_thanh_laser_phai(8,900,-900,vitri,2,350,30);
				vTaskDelay (1);
				if(!wantExit())	break;
		}
	}
	robotStop(0); 
	chinh_lai_vi_tri_laser_phai_do(vitri, 1000);
	
	robotStop(0); 	
				
}

//********************************** vao rung mai 2 gap kfs ********************************************
void Vao_rung_mai_2_do(int vitri)
{
	speed_chan_sau = 15;
	speed_chan_truoc = 60;

	target_chan_truoc = 250;
	target_chan_sau = 250;

	Kep_phai_4_ra;
	
	
	robotRunAngle(1550,25,-900,1.8);
//				
				while(_robotIMUAngle > -895)	
				{
					vTaskDelay (5); 
					if(!wantExit())	break;			
				}
				
		speed_tay_gat2 = 250;
		target_tay_gat2 = (Min_tay_gat2 + 70);
	
//	kiem_tra_huong_quay_tay_gap_phia_truoc();

	for(i=0;i<250;i++)
				{
					while(lazeSauValue > 35)	
					{	
						Bam_thanh_laser_phai(20,900,-900,vitri,2,450,30);//robotRun(-450,10);
						if(!wantExit())	break;
						vTaskDelay (1);
					}
				}
				
	Nang_cuc_nhanh();
	target_chan_truoc = 510;
	target_chan_sau = 510;
				
		
 	for(i=0;i<150;i++)		
	{
		while(bientrochansauValue < 500)	
		{
			Bam_thanh_laser_phai(8,900,-900,vitri,2,350,30);//robotRun(-450,10);
			if(!wantExit())	break;
			vTaskDelay (1);
		}
	}			
				
	for(i=0;i<1550;i++)
				{
					while(lazeSauValue > 2 || CB_Ha_Sau == 1)	
					{	
						Bam_thanh_laser_phai(8,900,-900,vitri,2,50,30);
						if(!wantExit())	break;
						vTaskDelay (1);
					}
				}
				
	su_dung_chan(580);
	RESET_ENCODER(); 
	
	while(abs(ENCODER_FR()) + abs(ENCODER_FL()) < 1700)	
		{	
				Bam_thanh_laser_phai(8,900,-900,vitri,2,50,30);
				if(!wantExit())	break;
		}
		
	robotStop(0); 
		
	chinh_lai_vi_tri_laser_phai_do(vitri, 1000);
	robotStop(0); 			
						
}	

//********************************** vao rung mai 3 gap kfs ********************************************

void Vao_rung_mai_3_do(int vitri)
{
	speed_chan_sau = 15;
	speed_chan_truoc = 60;

	target_chan_truoc = 250;
	target_chan_sau = 250;

	
	vTaskDelay(2000);
	
	Kep_phai_4_ra;

	
	robotRunAngle(1600,30,-900,1.8);
//				
				while(_robotIMUAngle < -895)	
				{
					vTaskDelay (5); 
					if(!wantExit())	break;
				}
				
	robotRunAngle(1600,30,-900,0.2);
	for(i=0;i<250;i++)
				{
					while(lazeTraiValue > vitri + 15)	
					{	
						vTaskDelay (1);
						if(!wantExit())	break;
					}
				}
				
	speed_tay_gat2 = 250;
	target_tay_gat2 = (Min_tay_gat2 + 100);
		
	su_dung_chan(500);
				
	for(i=0;i<250;i++)	
	{
		while(bientrochansauValue < 490)
								{	
		Bam_thanh_laser_trai(15,900,-900,vitri,2,450,30);
		if(!wantExit())	break;
					}
		
	}
	
	for(i=0;i<250;i++)
				{
					while(lazeSauValue > 25)	
					{	
						Bam_thanh_laser_trai(12,900,-900,vitri,2,250,30);
						if(!wantExit())	break;
					}
				}
			
	for(i=0;i<250;i++)
				{
					while(lazeSauValue > 1 || CB_Ha_Sau == 1)	
					{	
						su_dung_chan(697);
						Bam_thanh_laser_trai(8,900,-900,vitri,2,150,30);
						if(!wantExit())	break;
					}
				}

	vTaskDelay (5); 
	RESET_ENCODER(); 
	
	for(i=0;i<250;i++) {
	while(abs(ENCODER_FR()) + abs(ENCODER_FL()) < 1700)	
		{	
				Bam_thanh_laser_trai(8,900,-900,vitri,2,350,30);
				vTaskDelay (1);
				if(!wantExit())	break;
		}
	}
	robotStop(0); 
	chinh_lai_vi_tri_laser_trai_do(vitri, 1000);
	robotStop(0); 	
		
				
}

///////////////////////////////////////////////////////////////
void auto_vao_rung_do_cua1(void) {
		Vao_rung_mai_1_do(vi_tri_cua_rung_xanh_1_lazer_phai_tay_41);
}


void auto_vao_rung_do_cua2(void) {
		Vao_rung_mai_2_do(vi_tri_cua_rung_xanh_2_lazer_trai_tay_41);
}

void auto_vao_rung_do_cua3(void) {
		Vao_rung_mai_3_do(vi_tri_cua_rung_xanh_3_lazer_trai_tay_41);
}



/// ***************** leo bac 200 o id  5 san do *******************

void Leo_bac_200_do_5(void)
{	
	int vitri_tay23 = vitri_tay23_phai_laser_GapQua;
	
	Leo_bac_200(-900, 900);
	su_dung_chan(510);
		
		// chay toi khi cb leo nhan 
		for(i=0;i<250;i++)	
	{
		while(abs(bientrochansauValue - target_chan_sau) > 10)	{vTaskDelay(1); if(!wantExit())	break;}
	}	
	vTaskDelay(1000);
	robotRunAngle(-900,8,900,0.5);
	
	for(i=0;i<1550;i++)
			{
				while(CB_Ha_Sau == 1 || CB_vtri_leo == 1 )	
				{	
					if(!wantExit())	break;
					vTaskDelay (1);
				}
			}
	vTaskDelay (2000);
	robotStop(0); 
			
	if (TinHieu_ChuanBi_GapThang == 1 ) {
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
						robotRunAngle(-900,5,900,0.3);
						vTaskDelay (2000);
						robotStop(0);
						
						}
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 0) {
						chinh_lai_vi_tri_laser_phai(vitri_tay23, 1000);
						robotRunAngle(-900,5,900,0.3);
						vTaskDelay (2000);
						robotStop(0);
					}
				}		
		
		su_dung_chan(565);
		
		robotStop(0); 			
}

//**************** Xuong_bac_200 do ô 6  *************
void Xuong_bac_200_do_6(void)
{	
int vitri_tay23 = vitri_tay23_phai_laser_GapQua;

	Xuong_bac_200(-900, 900);		
	
	su_dung_chan(510);
		// chay toi khi laser sau cham 1
		robotRunAngle(-900,8,900,0.5);
		for(i=0;i<250;i++)	
	{
		while(abs(bientrochansauValue - target_chan_sau) > 10)	{vTaskDelay(1); if(!wantExit())	break;}
	}		
	
	for(i=0;i<1550;i++)
				{
					while(CB_Ha_Sau == 1 || CB_vtri_leo == 1 )	
					{	
						if(!wantExit())	break;
						vTaskDelay (1);
					}
				}
				
		robotStop(0); 
		if (TinHieu_ChuanBi_GapThang == 1 ) {
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
						robotRunAngle(-900,5,900,0.3);
						vTaskDelay (2000);
						robotStop(0);
						
						}
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 0) {
						chinh_lai_vi_tri_laser_phai(vitri_tay23, 1000);
						robotRunAngle(-900,5,900,0.3);
						vTaskDelay (2000);
						robotStop(0);
					}
				}		
		su_dung_chan(565);
		
		robotStop(0); 	
}


/// ***************xuong bac 200 do ô 7****************

void Xuong_bac_200_do_7(void)
{	
		int vitri_tay41 = vitri_tay41_laser_trai_GapQua;

		Xuong_bac_200(-900, 900);
		su_dung_chan(265);
		for(i=0;i<50;i++)		
	{
		while(abs(bientrochansauValue - target_chan_sau) > 5)	{vTaskDelay(1); if(!wantExit())	break;}
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
		

	if (TinHieu_ChuanBi_GapThang == 1) {
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
		robotStop(0);
}


//**************** Leo_bac_200 do ô 9 ********
void Leo_bac_200_do_9(void)
{	
		int vitri_tay23 = vitri_tay23_phai_laser_GapQua;
		Leo_bac_200(900, -900);
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
	
	if (TinHieu_ChuanBi_GapThang == 1) {
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
					robotStop(0);
					
				}
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 0) {
					chinh_lai_vi_tri_laser_phai(vitri_tay23, 1000);
					robotStop(0);
						}
			}
			robotStop(0);
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
		action_table[0][1][4] = Lay_phia_truoc_bac_200_tren;
		action_table[0][1][5] = Lay_phia_truoc_bac_200_tren;	
		action_table[0][1][6] = Lay_phia_truoc_bac_200_duoi;	
		action_table[0][1][7] = Lay_phia_truoc_bac_200_duoi;	
		action_table[0][1][8] = Lay_phia_truoc_bac_200_tren;	
		action_table[0][1][9] = Lay_phia_truoc_bac_200_tren;
		action_table[0][1][10]= Lay_phia_truoc_bac_200_duoi;
		action_table[0][1][11]= Lay_phia_truoc_bac_200_duoi;
		action_table[0][1][12]= Lay_phia_truoc_bac_200_duoi;

//    /* =========================================
//       move 0 , action 2, dung lai de lay ben TRAI
//       ========================================= */
//		action_table[0][2][4] = Lay_phia_truoc_bac_200_duoi;
//		action_table[0][2][5] = Lay_phia_truoc_bac_200_tren;	
//		action_table[0][2][6] = Lay_phia_truoc_bac_200_tren;	
//		action_table[0][2][7] = Lay_phia_truoc_bac_200_tren;	
//		action_table[0][2][8] = Lay_phia_truoc_bac_200_tren;	
//		action_table[0][2][9] = Lay_phia_truoc_bac_200_duoi;
//		action_table[0][2][10]= Lay_phia_truoc_bac_200_duoi;
//		action_table[0][2][11]= Lay_phia_truoc_bac_200_duoi;
//		action_table[0][2][12]= Lay_phia_truoc_bac_200_duoi;
		
//    /* =========================================
//       move 0 , action 3, dung lai de lay ben PHAI
//       ========================================= */

    /* =========================================
       move 1 , action 4 chay thang
       ========================================= */
    action_table[1][4][1]  = Leo_bac_400_co_thanh;
    action_table[1][4][2]  = Leo_bac_200_bam_thanh_phai;
		action_table[1][4][3]  = Leo_bac_400_ko_thanh;
		action_table[1][4][4]  = Leo_bac_200_ko_thanh;
    action_table[1][4][5]  = Leo_bac_200_do_5;
    action_table[1][4][6]  = Xuong_bac_200_do_6;
    action_table[1][4][7]  = Xuong_bac_200_do_7;
    action_table[1][4][8]  = Leo_bac_200_ko_thanh;
    action_table[1][4][9]  = Leo_bac_200_do_9;
    action_table[1][4][10] = xuong_bac_200_end;
    action_table[1][4][11] = xuong_bac_200_end;
		action_table[1][4][12] = xuong_bac_200_end;
		
				/* =========================================
//   move 2 , action 4,chay ben trai
//   ========================================= */
//    action_table[2][4][4] = qua_trai_xuong_bac;
//    action_table[2][4][5] = qua_trai_xuong_bac;
//    action_table[2][4][7] = qua_trai_xuong_bac;
//    action_table[2][4][8]  = qua_trai_len_bac;
//    action_table[2][4][10] = qua_trai_xuong_bac;
//		action_table[2][4][11] = qua_trai_len_bac;

		/* =========================================
//   move 3 , action 4,chay ben phai
//   ========================================= */
//		action_table[3][4][5]  =qua_phai_len_bac;
//    action_table[3][4][6] = qua_phai_len_bac;
//    action_table[3][4][8] = qua_phai_len_bac;
//    action_table[3][4][9] = qua_phai_xuong_bac;
//    action_table[3][4][11] = qua_phai_len_bac;
//    action_table[3][4][12] = qua_phai_xuong_bac;
//		
}

/* ================= RUN ================= */
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


