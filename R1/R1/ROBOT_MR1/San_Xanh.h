//*********************************** SAN XANH *********************************8
void Xuat_Phat_Lay_Gay_Xanh(int kc1) 
{				
	int i;
	speed_nang = 200;
	target_nang = 353;
	target_taykfs = 836;
	
	
	for(i=0;i<550;i++)	
	{	
			while(lazePhaiValue < 25)	
			{
				Bam_thanh_laser_phai(50,0,10,kc1,2,200,30);
				vTaskDelay(1); 
				if(wantExit())	break;
			}
	}
		XI_LANH_TAY_LEN;
		XI_LANH_KEP_MO;
	
		for(i=0;i<550;i++)	
	{	
			while(lazePhaiValue > 16)	
			{
				Bam_thanh_laser_phai(25,0,10,kc1,1,80,30);
				vTaskDelay(1); 
				if(wantExit())	break;
			}
	}
	
	RESET_ENCODER_CHAY();
	robotRunAngle(0,12,14,0.5);
	while(ENCODER_CHAY() < 5000)	{vTaskDelay(5); if(wantExit())	break;}
	
	robotRunAngle(0,12,14,0.5);
	for(i=0;i<200;i++)	
	{	
		while(CB_Dau == 1)	
		{
		vTaskDelay(1); 
		if(wantExit())	break;
		}
	}
	
	robotStop(0);
	speed_nang = 250;
	target_nang = 260;
	vTaskDelay(2000);
	XI_LANH_TAY_RA;
	vTaskDelay(4000);
	XI_LANH_KEP_DONG;
	vTaskDelay(3000);
	
	speed_nang = 250;
	target_nang = 290;
	
	vTaskDelay(2000);
	
	XI_LANH_TAY_VAO;	
	vTaskDelay(2000);
	
	speed_nang = 250;
	target_nang = 380;
	
	for(i=0;i<550;i++)	
	{	
			while(lazeTraiValue > 145)	{
				
			if(lazeTraiValue < 165)	XI_LANH_TAY_XUONG;
			Bam_thanh_laser_trai(40,0,14,145,2,350,30);
			vTaskDelay(1); if(wantExit())	break;}
	}

	Chot_gay = 200,Chot_gay_vao;
	speed_nang = 250;
	target_nang = 480;
	
	for(i=0;i<100;i++)	
	{	
			while(lazeTruocValue > 130)	
			{
				if(CB_Dau == 1) Chot_gay = 0;
				Bam_thanh_laser_trai(25,0,14,145,2,100,5);
				vTaskDelay(1); 
				if(wantExit())	break;
			}
		
	}
	Take_Next_Block_From_Queue();
	Chot_gay = 0;
	
		for(i=0;i<40;i++)	
	{	
			while(CB_Dung == 1 && lazeTruocValue > 110)	
			{
				Bam_thanh_laser_trai(8,0,8,146,2,100,5);
				vTaskDelay(1); 
				if(wantExit())	break;
			}
		
	}
	
//	RESET_ENCODER_CHAY();
//	robotRunAngle(0,7,15,0.5);
//	while(ENCODER_CHAY() < 2)	{vTaskDelay(5); if(wantExit())	break;}

	robotStop(0);
}

//********************************** Thoat_rap_vu_khi ***************************
void Thoat_rap_vu_khi(void)
{
	Quang_tro = 250;
	vTaskDelay(500);
	Chot_gay = 150;
	Chot_gay_vao;
	vTaskDelay(1000);
	Chot_gay = 0;
	Quang_tro = 0;
	
	RESET_ENCODER_CHAY();
	robotRunAngle(-550,30,0,0.5);
	while(ENCODER_CHAY() < 3000)	{vTaskDelay(5); if(wantExit())	break;}
	
	for(i=0;i<100;i++)	
	{	
			while(lazeTruocValue > 75)	
			{
				vTaskDelay(1); 
				if(wantExit())	break;
			}
		
	}
	
	robotStop(0);
}
//*********************************** leodoc *********************************
void leodoc(void)
{	
	robotResetIMU();
	vTaskDelay(2000);
	
	speed_nang = 150;
	target_nang = 516;
	target_taykfs =  845;
	
	robotRunAngle(-900,70,0,0.1);
	
				for(i=0;i<500;i++)	
	{	
			while(lazeTruocValue < 100 )	
			{	
				vTaskDelay(1); 
				if(wantExit())	break;
			}
	}
	
		for(i=0;i<500;i++)	
	{	
			while(CB_Driff_PHAI == 0 )	
			{	
				vTaskDelay(1); 
				if(wantExit())	break;
			}
	} 
	
	robotRunAngle(-900,70,0,0.1);
	
				for(i=0;i<500;i++)	
	{	
			while(lazeTruocValue > 200 )	
			{	
				vTaskDelay(1); 
				if(wantExit())	break;
			}
	}
	
	robotRunAngle(-900,70,0,0.1);
		for(i=0;i<500;i++)	
	{	
			while(CB_Driff_PHAI == 1 )	
			{	
				vTaskDelay(1); 
				if(wantExit())	break;
			}
	} 
	
	robotRunAngle(-900,30,0,0.1);
	
				for(i=0;i<500;i++)	
	{	
			while(lazeTruocValue < 100 )	
			{	
				vTaskDelay(1); 
				if(wantExit())	break;
			}
	}
	
		robotRunAngle(-900,20,0,0.1);
	for(i=0;i<550;i++)	
	{	
			while(lazeTraiValue > 7 )	{vTaskDelay(1); if(wantExit())	break;}
	}	

	robotRunAngle(-900,8,0,0.1);
	
	for(i=0;i<550;i++)	
	{	
			while(CB_THANH_TRAI == 1)	{vTaskDelay(1); if(wantExit())	break;}
	}			
	
	
	robotStop(0);

}
//*********************************** DatKFS *********************************8
void DatKFS_Xanh(int vi_tri ,int goc1,int goc2)
{				
		leodoc();
	
		vTaskDelay(2000);
	
			robotRunAngle(0,20,0,0.1);
		for(i=0;i<250;i++)	
	{	
			while(lazeTruocValue > 475)	
			{	
				speed_nang = 150,target_nang = 780;
				vTaskDelay(1); 
				if(wantExit())	break;
			}
	}
	
	robotRunAngle(0,50,0,0.1);
		for(i=0;i<250;i++)	
	{	
			while(lazeTruocValue > 400)	
			{	
				speed_nang = 150,target_nang = 780;
				vTaskDelay(1); 
				if(wantExit())	break;
			}
	}
			for(i=0;i<250;i++)	
	{	
			while(lazeTruocValue > 200)	
			{	
				speed_nang = 150,target_nang = 780;
				Bam_thanh_laser_trai(70,0,0,vi_tri,2,goc2,30);
				vTaskDelay(2); 
				if(wantExit())	break;
			}
	}
	
		for(i=0;i<500;i++)	
	{	
			while(lazeTruocValue > 110)	
			{	
				speed_nang = 150,target_nang = 785;
				Bam_thanh_laser_trai(50,0,0,vi_tri,2,goc2,30);
				vTaskDelay(2); 
				if(wantExit())	break;
			}
	}
		for(i=0;i<500;i++)	
	{	
			while(lazeTruocValue > 75)	
			{	
				speed_nang = 150,target_nang = 785;
				speed_taykfs = 200 ,target_taykfs =  605;
				Bam_thanh_laser_trai(15,0,0,vi_tri,2,goc2,20);
				vTaskDelay(1); 
				if(wantExit())	break;
			}
	}
			for(i=0;i<500;i++)	
	{	
			while(lazeTruocValue > 40)	
			{	
				vTaskDelay(2); 
				if(wantExit())	break;
			}
	}

	robotStop(30);
}
//*****************************************  Driff toi nha ****************************************************
void Cua_goc_xanh_1(void)
{
	robotRun(1800, 7);
	for(i=0;i<500;i++)	
	{	
			while(CB_CHAM_DUOI == 1 )	
			{	
				vTaskDelay(1); 
				if(wantExit())	break;
			}
	}
	
	robotStop(0);

	for(i=0;i<500;i++)	
	{	
			while(lazePhaiValue > 110)	
			{	
				Bam_thanh_laser_truoc(40,900,0,57,2,50,20);
				vTaskDelay(1); 
				if(wantExit())	break;
			}
	}
	
	robotRun(900, 20);
	for(i=0;i<500;i++)	
	{	
			while(lazePhaiValue > 26 )	
			{	
				vTaskDelay(1); 
				if(wantExit())	break;
			}
	}
	
	robotRun(0, 30);
	for(i=0;i<500;i++)	
	{	
			while(lazeTruocValue > 433 )	
			{	
				vTaskDelay(1); 
				if(wantExit())	break;
			}
	}
	
	for(i=0;i<500;i++)	
	{	
			while(lazeTruocValue > 111 )	
			{	\
				Bam_thanh_laser_trai(40,0,0,5,2,50,20);
				vTaskDelay(1); 
				if(wantExit())	break;
			}
	}
	
	robotRun(0, 10);
	for(i=0;i<500;i++)	
	{	
			while(lazeTruocValue > 60 )	
			{	
				vTaskDelay(1); 
				if(wantExit())	break;
			}
	}
	robotStop(0);

	
}
//*****************************************  vtri 1,2****************************************************
void vtri1vs2xanh(int vitri,int giamtoc,int cao,int dai)
{
	robotRunAngle(-900,30,0,0.2);
	for(i=0;i<500;i++)	
	{	
			while(lazeTraiValue > 40)	
			{	
				vTaskDelay(1); 
				if(wantExit())	break;
			}
	}
	
		robotStop(0);

		robotRun(2100,20);
		robotRotate(-900, -0.7,0);

			while(_robotIMUAngle > -870 )	
				{
				speed_nang = 250;
				target_nang = 960;	
					vTaskDelay (1); 
					if(wantExit())	break;
				}
		robotRotateStop();		
				
		robotRunAngle(1800,25,-900,0.2);
	for(i=0;i<500;i++)	
	{	
			while(lazePhaiValue < giamtoc)	
			{	
				Bac_kfs(cao,dai);	
				vTaskDelay(1); 
				if(wantExit())	break;
			}
	}
	
		robotRunAngle(1800,7,-900,0.2);
	for(i=0;i<500;i++)	
	{	
			while(lazePhaiValue < vitri)	
			{	
				vTaskDelay(1); 
				if(wantExit())	break;
			}
	}
		robotStop(0);
//	
		robotRun(0,7);
		for(i=0;i<500;i++)	
	{	
			while(lazeTruocValue > 39)	
			{	
				vTaskDelay(3); 
				if(wantExit())	break;
			}
	}
	
	robotStop(30);
}
//*****************************************  vtri  4,7,10 ****************************************************
void Trai_xanh(int vitri,int giamtoc,int cao,int dai)
{
	robotRunAngle(-900,30,0,0.2);
	for(i=0;i<500;i++)	
	{	
			while(lazeTraiValue > 60)	
			{	
				vTaskDelay(1); 
				if(wantExit())	break;
			}
	}
	
	robotStop(0);
	robotRunAngle(-1700,40,0,0.2);
	for(i=0;i<500;i++)	
	{	
			while(lazeTraiValue > 15)	
			{	
				vTaskDelay(1); 
				if(wantExit())	break;
			}
	}
	

	
	robotRunAngle(1800,40,0,0.1);

		for(i=0;i<500;i++)	
	{	
			while(lazeTraiValue < 150 )	
			{	
				//Bam_thanh_laser_trai(20,1800,0,5,3,-120,20);
				vTaskDelay(1); 
				if(wantExit())	break;
			}
	}
	
		RESET_ENCODER_CHAY();
		robotRunAngle(-1400,20,0,0.1);
	
		for(i=0;i<500;i++)	
	{	
		while(ENCODER_CHAY() > 4000)	{vTaskDelay(1); if(wantExit())	break;}
	}
		robotStop(0);
		
	
		robotRunAngle(-900,20,0,0.2);
		for(i=0;i<500;i++)	
	{	
			while(lazePhaiValue < 325)	
			{	
				vTaskDelay(1); 
				if(wantExit())	break;
			}
	}
		
			for(i=0;i<1000;i++)	
	{	
			while(lazePhaiValue < giamtoc)	
			{	
				Bam_thanh_laser_truoc(30,-900,0,40,2,-50,20);
				vTaskDelay(1); 
				if(wantExit())	break;
			}
	}
	
		for(i=0;i<250;i++)	
	{	
			while(lazePhaiValue < vitri)	
			{	
				Bam_thanh_laser_truoc(10,-900,0,40,2,-50,20);
				Bac_kfs(cao,dai);	;
				vTaskDelay(1); 
				if(wantExit())	break;
			}
	}
	
	robotStop(0);
	
		for(i=0;i<500;i++)	
	{	
			while(lazeTruocValue > 40)	
			{	
				robotRun(0,7);
				vTaskDelay(1); 
				if(wantExit())	break;
			}
	}

	robotStop(0);
	
}
//*****************************************  vtri 3,6,9,12****************************************************
void Phai_xanh(int vitri,int giamtoc,int cao,int dai)
{
	robotRunAngle(-900,30,0,0.2);
	for(i=0;i<500;i++)	
	{	
			while(lazeTraiValue > 112)	
			{	
				vTaskDelay(1); 
				if(wantExit())	break;
			}
	}
	
		robotStop(0);

	robotRunAngle(0,10,0,0.2);
	for(i=0;i<500;i++)	
	{	
			while(lazeTruocValue > 138)	
			{	
				vTaskDelay(1); 
				if(wantExit())	break;
			}
	}
	
		robotRun(-450,7);
		robotRotate(-1800, -2,0);

			while(_robotIMUAngle > -1750 )	
				{
				speed_nang = 250;
				target_nang = 960;	
					vTaskDelay (1); 
					if(wantExit())	break;
				}
		robotRotateStop();		
//				
		robotRunAngle(-900,20,-1800,0.1);
		for(i=0;i<500;i++)	
	{	
			while(lazePhaiValue > 600)	
			{	
				vTaskDelay(1); 
				if(wantExit())	break;
			}
	}
		robotRunAngle(-900,25,-1800,0.1);
	for(i=0;i<500;i++)	
	{	
			while(lazePhaiValue > giamtoc)	
			{	
				vTaskDelay(1); 
				if(wantExit())	break;
			}
	}
	
		robotRunAngle(-900,7,-1800,0.1);
	for(i=0;i<500;i++)	
	{	
			while(lazePhaiValue > vitri)	
			{	
				Bac_kfs(cao,dai);	
				vTaskDelay(1); 
				if(wantExit())	break;
			}
	}
		robotStop(0);
//	
		robotRun(0,7);
		for(i=0;i<500;i++)	
	{	
			while(lazeTruocValue > 40)	
			{	
				vTaskDelay(3); 
				if(wantExit())	break;
			}
	}
	
	robotStop(30);
}
//*****************************************  vtri 11****************************************************
void vtri11xanh(int vitri,int giamtoc,int cao,int dai)
	{
	robotRunAngle(-900,30,0,0.2);
	for(i=0;i<500;i++)	
	{	
			while(lazeTraiValue > 112)	
			{	
				vTaskDelay(1); 
				if(wantExit())	break;
			}
	}
	
		robotStop(0);

	robotRunAngle(0,10,0,0.2);
	for(i=0;i<500;i++)	
	{	
			while(lazeTruocValue > 138)	
			{	
				vTaskDelay(1); 
				if(wantExit())	break;
			}
	}
		robotRun(-450,7);
		robotRotate(-1800, -2,0);

			while(_robotIMUAngle > -1790 )	
				{
				speed_nang = 250;
				target_nang = 960;	
					vTaskDelay (1); 
					if(wantExit())	break;
				}
		robotRotateStop();		
//				
		robotRunAngle(-900,20,-1800,0.1);
		for(i=0;i<500;i++)	
	{	
			while(lazePhaiValue > 600)	
			{	
				vTaskDelay(1); 
				if(wantExit())	break;
			}
	}
		robotRunAngle(-900,40,-1800,0.1);
	for(i=0;i<500;i++)	
	{	
			while(lazePhaiValue > 190)	
			{	
				vTaskDelay(1); 
				if(wantExit())	break;
			}
	}
	
		robotRunAngle(-900,10,-1800,0.1);
	for(i=0;i<500;i++)	
	{	
			while (lazePhaiValue > 119)	
			{	
				vTaskDelay(5); 
				if(wantExit())	break;
			}
	}
			robotRun(450,7);
			robotRotate(-2700, -0.7,0);
	
			while(_robotIMUAngle > -2690 )	
				{	
					vTaskDelay (1); 
					if(wantExit())	break;
				}
		robotRotateStop();		
//	
			robotRunAngle(1800,30,-2700,0.1);
				
			for(i=0;i<500;i++)	
	{	
			while(lazeTraiValue < giamtoc )	
			{	
				vTaskDelay(1); 
				if(wantExit())	break;
			}
	}
	
	robotRunAngle(1800,7,-2700,0.1);
				
			for(i=0;i<500;i++)	
	{	
			while(lazeTraiValue < vitri )	
			{	
				Bac_kfs(cao,dai);	
				vTaskDelay(1); 
				if(wantExit())	break;
			}
	}
	
		robotRun(0,7);
		for(i=0;i<500;i++)	
	{	
			while(lazeTruocValue > 40)	
			{	
				vTaskDelay(3); 
				if(wantExit())	break;
			}
	}
	
	robotStop(30);
}
	

/// ham chay tu Take_Next_Block_From_Queuedong san xanh//////////////////
extern uint8_t has_active_block ;
extern uint8_t id_block ;


////// vi du cach dung
void chaytudong_esp_now_san_xanh(void)
{
    

    if (has_active_block)
    {
        // ?? x? lý move, action, take_data_block ? dây

				if (take_data_block == 3) {
					Phai_xanh(565,590,725,150);	
					Finish_Current_Block();
					}
				else if (take_data_block == 6) {
					Phai_xanh(463,522,955,166);
					Finish_Current_Block();
					}
				else if (take_data_block == 9) {
					Phai_xanh(325,402,725,150);
					Finish_Current_Block();
					}
				else if (take_data_block == 12) {
					Phai_xanh(175,245,553,161);
					Finish_Current_Block();
					}
				else if (take_data_block == 1) {
					vtri1vs2xanh(438,389,725,150);
					Finish_Current_Block();
					}
				else if (take_data_block == 4) {
					Trai_xanh(516,465,553,161);
					Finish_Current_Block();
					}
				else if (take_data_block == 7) {
					Trai_xanh(601,560,725,150); 
					Finish_Current_Block();
					}
				else if (take_data_block == 10) {
					Trai_xanh(659,630,553,161); 
					Finish_Current_Block();
					}
				else if (take_data_block == 2) {
					vtri1vs2xanh(298,230,553,161);
					Finish_Current_Block();					
					}
				else if (take_data_block == 11) {
					vtri11xanh(290,204,725,150); 
					Finish_Current_Block();
					}
							}
}