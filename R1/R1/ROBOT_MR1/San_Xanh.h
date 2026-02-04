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
	target_nang = 507;
	
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
	
	Chot_gay = 0;
	
		for(i=0;i<40;i++)	
	{	
			while(CB_Dung == 0 && lazeTruocValue > 110)	
			{
				Bam_thanh_laser_trai(10,0,8,145,2,100,5);
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
	vTaskDelay(500);
	
	speed_nang = 150;
	target_nang = 516;
	target_taykfs =  845;
	
	robotRun(-910,30);
				for(i=0;i<500;i++)	
	{	
			while(CB_Driff_TRAI == 1 ||  CB_Driff_PHAI == 1)	
			{	
				vTaskDelay(1); 
				if(wantExit())	break;
			}
	}
	
	robotRun(-910,30);
				for(i=0;i<500;i++)	
	{	
			while(lazeTruocValue > 200 )	
			{	
				vTaskDelay(1); 
				if(wantExit())	break;
			}
	}
	
		robotRun(-910,30);
	
				for(i=0;i<500;i++)	
	{	
			while(CB_Driff_TRAI == 0 ||  CB_Driff_PHAI == 0)	
			{	
				vTaskDelay(1); 
				if(wantExit())	break;
			}
	}
	
	robotRun(-910,30);
	
		for(i=0;i<500;i++)	
	{	
			while(CB_Driff_TRAI == 1 ||  CB_Driff_PHAI == 1)	
			{	
				vTaskDelay(1); 
				if(wantExit())	break;
			}
	}
	
	robotRun(-910,20);
	
	for(i=0;i<550;i++)	
	{	
			while(lazeTraiValue > 10)	{vTaskDelay(1); if(wantExit())	break;}
	}			
	
	robotRun(-910,7);
	
	for(i=0;i<550;i++)	
	{	
			while(CB_THANH_TRAI == 1)	{vTaskDelay(1); if(wantExit())	break;}
	}			
	
	
	robotStop(00);

}
//*********************************** DatKFS *********************************8
void DatKFS_Xanh(int vi_tri ,int goc1,int goc2)
{				
		leodoc();
	
		vTaskDelay(2000);
	
		robotRun(0, 70);
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
				speed_nang = 150,target_nang = 790;
				Bam_thanh_laser_trai(50,0,0,vi_tri,2,goc2,30);
				vTaskDelay(2); 
				if(wantExit())	break;
			}
	}
		for(i=0;i<500;i++)	
	{	
			while(lazeTruocValue > 75)	
			{	
				speed_nang = 150,target_nang = 765;
				speed_taykfs = 200 ,target_taykfs =  620;
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
//*****************************************  vtri 10 ****************************************************
void vitri10xanh(void)
{
	
		for(i=0;i<500;i++)	
	{	
			while(lazeTraiValue > 85 )	
			{	
				robotRun(-900,30);
				vTaskDelay(1); 
				if(wantExit())	break;
			}
	}
	
		robotStop(0);
	
	for(i=0;i<500;i++)	
	{	
			while(lazeTraiValue < 90 )	
			{	
				speed_nang = 250;
				target_nang = 730;
				Bam_thanh_laser_trai(50,1800,0,5,3,-120,20);
				vTaskDelay(1); 
				if(wantExit())	break;
			}
	}
	
	for(i=0;i<500;i++)	
	{	
			while(CB_CHAM_DUOI == 1 )	
			{	
				robotRun(1800,10);
				vTaskDelay(1); 
				if(wantExit())	break;
			}
	}
	
		for(i=0;i<500;i++)	
	{	
			while(lazeTruocValue > 64)	
			{	
				robotRun(-900,30);
				vTaskDelay(1); 
				if(wantExit())	break;
			}
	}
	
	for(i=0;i<500;i++)	
	{	
			while(lazeTraiValue > 320)	
			{	
				Bam_thanh_laser_truoc(40,-900,0,46,1,-80,20);
				vTaskDelay(1); 
				if(wantExit())	break;
			}
	}
	
	for(i=0;i<500;i++)	
	{	
			while(lazeTraiValue > 189)	
			{	
				Bam_thanh_laser_truoc(15,-900,0,46,2,-80,20);
				vTaskDelay(1); 
				if(wantExit())	break;
			}
	}
	
		for(i=0;i<500;i++)	
	{	
			while(lazeTruocValue > 42)	
			{	
				robotRun(0,7);
				vTaskDelay(1); 
				if(wantExit())	break;
			}
	}
	Bac_kfs(553,161);
	vTaskDelay(2000);
	
	robotStop(0);

	
}
//*****************************************  vtri 11 ****************************************************
void vitri11xanh(void)
{
	
		for(i=0;i<500;i++)	
	{	
			while(lazeTraiValue > 85 )	
			{	
				robotRun(-900,30);
				vTaskDelay(1); 
				if(wantExit())	break;
			}
	}
	
		robotStop(0);
	
	for(i=0;i<500;i++)	
	{	
			while(lazeTraiValue < 90 )	
			{	
				speed_nang = 250;
				target_nang = 730;
				Bam_thanh_laser_trai(50,1800,0,5,3,-120,20);
				vTaskDelay(1); 
				if(wantExit())	break;
			}
	}
	
	for(i=0;i<500;i++)	
	{	
			while(CB_CHAM_DUOI == 1 )	
			{	
				robotRun(1800,10);
				vTaskDelay(1); 
				if(wantExit())	break;
			}
	}
	
		for(i=0;i<500;i++)	
	{	
			while(lazeTruocValue > 64)	
			{	
				robotRun(-900,30);
				vTaskDelay(1); 
				if(wantExit())	break;
			}
	}
	
	for(i=0;i<500;i++)	
	{	
			while(lazeTraiValue > 180)	
			{	
				Bam_thanh_laser_truoc(40,-900,0,46,1,-80,20);
				vTaskDelay(1); 
				if(wantExit())	break;
			}
	}
	
	for(i=0;i<500;i++)	
	{	
			while(lazeTraiValue > 180)	
			{	
				Bam_thanh_laser_truoc(40,-900,0,46,1,-80,20);
				vTaskDelay(1); 
				if(wantExit())	break;
			}
	}
				
	for(i=0;i<500;i++)	
	{	
			while(lazeTraiValue > 140)	
			{	
				Bam_thanh_laser_truoc(10,-900,0,46,1,-80,20);
				vTaskDelay(1); 
				if(wantExit())	break;
			}
	}
				
			while (CB_Driff_TRAI == 0 ){vTaskDelay(1); if(wantExit())	break;}
			
			robotRun(-470,15);
			robotRotate(850, 0.7,0);

			
			while(_robotIMUAngle < 850 )	
				{
					vTaskDelay (1); 
					if(wantExit())	break;
				}
				robotStop(0);
				robotResetIMU();
				
	for(i=0;i<500;i++)	
	{	
			while(lazePhaiValue < 303)	
			{	
				Bam_thanh_laser_truoc(15,-900,0,46,1,-80,20);
				vTaskDelay(1); 
				if(wantExit())	break;
			}
	}
	
	for(i=0;i<500;i++)	
	{	
			while(lazeTruocValue > 40)	
			{	
				robotRun(0,7);
				vTaskDelay(1); 
				if(wantExit())	break;
			}
	}
	Bac_kfs(725,150);
	vTaskDelay(2000);
	robotStop(0);

	
}
//*****************************************  vtri 12 ****************************************************
void vitri12xanh(void)
{
	
		for(i=0;i<500;i++)	
	{	
			while(lazeTraiValue > 85 )	
			{	
				robotRun(-900,30);
				vTaskDelay(1); 
				if(wantExit())	break;
			}
	}
	
		robotStop(0);
	
	for(i=0;i<500;i++)	
	{	
			while(lazeTraiValue < 90 )	
			{	
				speed_nang = 250;
				target_nang = 730;
				Bam_thanh_laser_trai(50,1800,0,5,3,-120,20);
				vTaskDelay(1); 
				if(wantExit())	break;
			}
	}
	
	for(i=0;i<500;i++)	
	{	
			while(CB_CHAM_DUOI == 1 )	
			{	
				robotRun(1800,10);
				vTaskDelay(1); 
				if(wantExit())	break;
			}
	}
	
		for(i=0;i<500;i++)	
	{	
			while(lazeTruocValue > 64)	
			{	
				robotRun(-900,30);
				vTaskDelay(1); 
				if(wantExit())	break;
			}
	}
	
	for(i=0;i<500;i++)	
	{	
			while(lazeTraiValue > 180)	
			{	
				Bam_thanh_laser_truoc(40,-900,0,46,1,-80,20);
				vTaskDelay(1); 
				if(wantExit())	break;
			}
	}
				
	for(i=0;i<500;i++)	
	{	
			while(lazeTraiValue > 140)	
			{	
				Bam_thanh_laser_truoc(10,-900,0,46,1,-80,20);
				vTaskDelay(1); 
				if(wantExit())	break;
			}
	}
				
			while (CB_Driff_TRAI == 0 ){vTaskDelay(1); if(wantExit())	break;}
			
			robotRun(-470,15);
			robotRotate(850, 0.7,0);

			
			while(_robotIMUAngle < -850 )	
				{
					vTaskDelay (1); 
					if(wantExit())	break;
				}
				robotStop(0);
				robotResetIMU();
				
	for(i=0;i<500;i++)	
	{	
			while(lazeTraiValue > 145)	
			{	
				Bam_thanh_laser_truoc(15,-900,0,46,1,-80,20);
				vTaskDelay(1); 
				if(wantExit())	break;
			}
	}
	
	for(i=0;i<500;i++)	
	{	
			while(lazeTruocValue > 40)	
			{	
				robotRun(0,7);
				vTaskDelay(1); 
				if(wantExit())	break;
			}
	}
	Bac_kfs(553,161);
	vTaskDelay(2000);
	robotStop(0);

	
}