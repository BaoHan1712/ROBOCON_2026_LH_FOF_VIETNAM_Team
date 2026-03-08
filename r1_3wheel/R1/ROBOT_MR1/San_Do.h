//0**********************************SAN DO*************************************
void Xuat_Phat_Lay_Gay_vtri1_Do(int kc1) 
{				
	int i;
	
	speed_nang = 250;
	target_nang = 380;
	target_taykfs = 836;
//	
	for(i=0;i<550;i++)	
	{	
			while(lazePhaiValue < 30)	
			{
				Bam_thanh_laser_phai(50,0,-5,kc1,2,-200,30);
				vTaskDelay(1); 
				if(wantExit())	break;
			}
	}
	
		for(i=0;i<550;i++)	
	{	
			while(lazePhaiValue > 16)	
			{
				Bam_thanh_laser_phai(30,0,-5,kc1,1,-50,30);
				vTaskDelay(1); 
				if(wantExit())	break;
			}
	}
	
	RESET_ENCODER_CHAY();
	robotRunAngle(0,25,-5,0.2);
	while(abs(ENCODER_CHAY()) < 3000)	{vTaskDelay(5); if(wantExit())	break;}
	

	robotRunAngle(0,20,-5,0.2);
	for(i=0;i<200;i++)	
	{	
		while(CB_Dau == 1 && lazeSauValue > 315)	
		{
		vTaskDelay(5); 
		if(wantExit())	break;
		}
	}
	XI_LANH_TAY_LEN;
	XI_LANH_KEP_MO;
	robotStop(20);
	
	speed_nang = 250;
	target_nang = 323;
	
}

//*********************************** vtr2 *********************************
	void Xuat_Phat_Lay_Gay_vtri2_Do(int kc1) 
{				
	int i;
	
	XI_LANH_TAY_RA;
	vTaskDelay(4000);
	XI_LANH_KEP_DONG;
	vTaskDelay(3000);
	
	speed_nang = 250;
	target_nang = 333;
//	
	vTaskDelay(2000);
	
	XI_LANH_TAY_VAO;	
	vTaskDelay(2000);
//	
	speed_nang = 250;
	target_nang = 380;
	
	for(i=0;i<550;i++)	
	{	
			while(lazeTraiValue > 160)	{
				
			if(lazeTraiValue < 185)	XI_LANH_TAY_XUONG;
			Bam_thanh_laser_trai(50,0,-5,155,2,-350,30);
			vTaskDelay(1); if(wantExit())	break;}
	}
//	
	Chot_gay = 200,Chot_gay_vao;
	speed_nang = 250;
	target_nang = 490;
//	
	for(i=0;i<100;i++)	
	{	
			while(lazeSauValue > 130)	
			{
				if(CB_Dau == 1) Chot_gay = 0;
				Bam_thanh_laser_trai(35,0,-5,155,2,-100,5);
				vTaskDelay(1); 
				if(wantExit())	break;
			}
		
	}
//	Take_Next_Block_From_Queue();
	Chot_gay = 0;
	
		for(i=0;i<40;i++)	
	{	
			while(CB_Dung == 0 && lazeSauValue > 100)	
			{
				Bam_thanh_laser_trai(20,0,-3,155,2,-100,5);
				vTaskDelay(1); 
				if(wantExit())	break;
			}
		
	}
//	
////	RESET_ENCODER_CHAY();
////	robotRunAngle(0,7,15,0.5);
////	while(ENCODER_CHAY() < 2)	{vTaskDelay(5); if(wantExit())	break;}

	robotStop(20);
}
//*********************************** leodoc *********************************
void leodocdo(void)
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
		while(CB_Driff_TRAI == 0 )	
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
//	
	robotRunAngle(-900,60,0,0.1);
		for(i=0;i<500;i++)	
	{	
			while(CB_Driff_TRAI == 1 )	
			{	
				vTaskDelay(1); 
				if(wantExit())	break;
			}
	} 
//	
	robotRunAngle(-900,40,0,0.1);
	
				for(i=0;i<500;i++)	
	{	
			while(lazeTruocValue < 100 )	
			{	
				vTaskDelay(1); 
				if(wantExit())	break;
			}
	}
//	
		robotRunAngle(-900,30,0,0.1);
	for(i=0;i<550;i++)	
	{	
			while(lazePhaiValue > 8 )	{vTaskDelay(1); if(wantExit())	break;}
	}	

	robotRunAngle(-900,20,0,0.1);
	
	for(i=0;i<550;i++)	
	{	
			while(CB_THANH_PHAI == 1)	{vTaskDelay(1); if(wantExit())	break;}
	}			
	
	
	robotStop(0);

}
//*********************************** DatKFS *********************************8
void DatKFSDo(int vi_tri ,int goc1,int goc2)
{				
		leodocdo();
	
		vTaskDelay(2000);
	
		robotRunAngle(1800,50,0,-0.1);
		for(i=0;i<250;i++)	
	{	
			while(lazeTruocValue > 405)	
			{	
				vTaskDelay(1); 
				if(wantExit())	break;
			}
	}
//	robotRunAngle(0,50,0,-0.1);
//		for(i=0;i<250;i++)	
//	{	
//			while(lazeTruocValue > 400)	
//			{	
//				speed_nang = 150,target_nang = 780;
//				vTaskDelay(1); 
//				if(wantExit())	break;
//			}
//	}
for(i=0;i<250;i++)	
	{	
			while(lazeTruocValue > 170)	
			{	
				speed_nang = 150,target_nang = 805;
				Bam_thanh_laser_phai(70,1800,0,vi_tri,2,goc2,5);
				vTaskDelay(2); 
				if(wantExit())	break;
			}
	}
//	
		for(i=0;i<500;i++)	
	{	
			while(lazeTruocValue > 70)	
			{	
				speed_nang = 150,target_nang = 805;
				Bam_thanh_laser_phai(60,1800,0,vi_tri,2,goc2,30);
				vTaskDelay(2); 
				if(wantExit())	break;
			}
	}
		for(i=0;i<500;i++)	
	{	
			while(lazeTruocValue > 49)	
			{	
				speed_taykfs = 200 ,target_taykfs =  510;
				Bam_thanh_laser_phai(25,1800,0,vi_tri,2,goc2,20);
				vTaskDelay(1); 
				if(wantExit())	break;
			}
	}
			for(i=0;i<500;i++)	
	{	
			while(lazeTruocValue > 20)	
			{	
				vTaskDelay(2); 
				if(wantExit())	break;
			}
	}

	robotStop(40);
	speed_nang = 150,target_nang = 753;
}
//*****************************************  Driff do 1 ****************************************************
void Cua_goc_do_1(void)
{
	robotRun(1800, 15);
	for(i=0;i<500;i++)	
	{	
			while(CB_CHAM_DUOI == 1 )	
			{	
				vTaskDelay(1); 
				if(wantExit())	break;
			}
	}
	
	robotRun(-900,15);
	
	for(i=0;i<500;i++)	
	{	
			while(lazeTraiValue > 75)	
			{	
				vTaskDelay(1); 
				if(wantExit())	break;
			}
	}
	
	robotRun(0,15);
	
	robotRotate(-900,-0.9,0);
}

//*****************************************  vtri 3,6,9,12 ****************************************************
void Trai_do(int vitri,int giamtoc,int cao,int dai)
{
	robotRunAngle(-900,20,0,0.2);
	for(i=0;i<500;i++)	
	{	
			while(lazeTraiValue > 20)	
			{	
				vTaskDelay(1); 
				if(wantExit())	break;
			}
	}
	
		robotStop(0);
		robotRunAngle(1800,20,0,0.2);

		for(i=0;i<500;i++)	
	{	
			while(lazeTraiValue < 150 )	
			{	
				speed_nang = 250;
				target_nang = 960;
				//Bam_thanh_laser_trai(20,1800,0,5,3,-120,20);
				vTaskDelay(1); 
				if(wantExit())	break;
			}
	}
	
		RESET_ENCODER_CHAY();
		robotRunAngle(-1650,20,0,0.2);
	
		for(i=0;i<500;i++)	
	{	
		while(ENCODER_CHAY() > 3900)	{vTaskDelay(1); if(wantExit())	break;}
	}
		robotStop(0);
		
	
		robotRunAngle(-900,20,0,0.2);
		for(i=0;i<500;i++)	
	{	
			while(lazeTraiValue > 610)	
			{	
				vTaskDelay(1); 
				if(wantExit())	break;
			}
	}
		
			for(i=0;i<500;i++)	
	{	
			while(lazeTraiValue > giamtoc)	
			{	
				Bam_thanh_laser_truoc(30,-900,0,40,2,-50,20);
				vTaskDelay(1); 
				if(wantExit())	break;
			}
	}
	
		for(i=0;i<250;i++)	
	{	
			while(lazeTraiValue > vitri)	
			{	
				Bam_thanh_laser_truoc(15,-900,0,40,2,-50,20);
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
	Bac_kfs(cao,dai);	;		
	vTaskDelay(2000);
	
	robotStop(0);

	
}
//*****************************************  vtri 4,7,10 ****************************************************
 void Phai_do(int vitri,int giamtoc,int cao,int dai)
{
	robotRunAngle(-900,40,0,0.2);
	for(i=0;i<500;i++)	
	{	
			while(lazeTraiValue > 85)	
			{	
				vTaskDelay(1); 
				if(wantExit())	break;
			}
	}
	
		robotStop(0);

		robotRun(-150,30);
		robotRotate(-900, -0.7,0);

			while(_robotIMUAngle > -800 )	
				{
					vTaskDelay (1); 
					if(wantExit())	break;
				}
				
		robotRotateStop();		
				
		robotRunAngle(0,40,-900,0.1);
				
	for(i=0;i<500;i++)	
	{	
			while(lazePhaiValue > 110)	
			{	
				vTaskDelay(1); 
				if(wantExit())	break;
			}
	}
//			robotStop(0);
	
			robotRun(350,30);
			robotRotate(-1800, -0.6,0);

			while(_robotIMUAngle > -1750 )	
				{
					vTaskDelay (1); 
					if(wantExit())	break;
				}
	
		robotRotateStop();		
		robotRunAngle(-900,20,-1800,0.2);
		for(i=0;i<500;i++)	
	{	
			while(lazeTraiValue < 327)	
			{	
				vTaskDelay(1); 
				if(wantExit())	break;
			}
	}
		
			for(i=0;i<500;i++)	
	{	
			while(lazeTraiValue < giamtoc)	
			{	
				Bam_thanh_laser_truoc(30,-900,-1800,40,2,120,20);
				vTaskDelay(1); 
				if(wantExit())	break;
			}
	}
	
		for(i=0;i<500;i++)	
	{	
			while(lazeTraiValue < vitri)	
			{	
				Bam_thanh_laser_truoc(15,-900,-1800,40,2,80,20);
				Bac_kfs(cao,dai);		
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
	
	robotStop(0);
}
//*****************************************  vtri 1,2****************************************************
void vtri1vs2do(int vitri,int giamtoc,int cao,int dai)
{
	robotRunAngle(-900,30,0,0.2);
	for(i=0;i<500;i++)	
	{	
			while(lazeTraiValue > 85)	
			{	
				vTaskDelay(1); 
				if(wantExit())	break;
			}
	}
	
		robotStop(0);

		robotRun(-150,20);
		robotRotate(-900, -0.7,0);

			while(_robotIMUAngle > -850 )	
				{
					Bac_kfs(cao,dai);		
					vTaskDelay (1); 
					if(wantExit())	break;
				}
		robotRotateStop();		
				
		robotRunAngle(0,25,-900,0.2);
	for(i=0;i<500;i++)	
	{	
			while(lazePhaiValue > giamtoc)	
			{	
				vTaskDelay(1); 
				if(wantExit())	break;
			}
	}
	
		robotRunAngle(-150,7,-900,0.2);
	for(i=0;i<500;i++)	
	{	
			while(lazePhaiValue > vitri)	
			{	
				vTaskDelay(1); 
				if(wantExit())	break;
			}
	}
		robotStop(0);
	
		robotRun(0,7);
		for(i=0;i<500;i++)	
	{	
			while(lazeTruocValue > 38)	
			{	
				vTaskDelay(3); 
				if(wantExit())	break;
			}
	}
	
	robotStop(30);
}
//*****************************************  vtri 11 ****************************************************
void vtri11do(int cao,int dai)
{
	robotRunAngle(-900,20,0,0.2);
	for(i=0;i<500;i++)	
	{	
			while(lazeTraiValue > 20)	
			{	
				vTaskDelay(1); 
				if(wantExit())	break;
			}
	}
	
		robotStop(0);
		robotRunAngle(1800,20,0,0.2);

		for(i=0;i<500;i++)	
	{	
			while(lazeTraiValue < 150 )	
			{	
				speed_nang = 250;
				target_nang = 960;
				//Bam_thanh_laser_trai(20,1800,0,5,3,-120,20);
				vTaskDelay(1); 
				if(wantExit())	break;
			}
	}
	
		RESET_ENCODER_CHAY();
		robotRunAngle(-1650,20,0,0.2);
	
		for(i=0;i<500;i++)	
	{	
		while(ENCODER_CHAY() > 3900)	{vTaskDelay(1); if(wantExit())	break;}
	}
		robotStop(0);
		
	
		robotRunAngle(-900,20,0,0.2);
		for(i=0;i<500;i++)	
	{	
			while(lazeTraiValue > 610)	
			{	
				vTaskDelay(1); 
				if(wantExit())	break;
			}
	}
		
		for(i=0;i<500;i++)	
	{	
			while(lazeTraiValue > 180)	
			{	
				Bam_thanh_laser_truoc(40,-900,0,40,1,-80,20);
				vTaskDelay(1); 
				if(wantExit())	break;
			}
	}
				
	for(i=0;i<500;i++)	
	{	
			while(lazeTraiValue > 140)	
			{	
				Bam_thanh_laser_truoc(10,-900,0,40,1,-80,20);
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
				robotRotateStop();
				
				
	robotRunAngle(0,20,900,0.1);
				
			for(i=0;i<500;i++)	
	{	
			while(lazePhaiValue < 285 )	
			{	
				//Bam_thanh_laser_truoc(15,0,0,879,1,-50,20);
				Bac_kfs(cao,dai);	
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
	
	robotStop(0);

	
}
//*****************************************  cettot ****************************************************
void testdo(void)
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
		while(CB_Driff_TRAI == 0 )	
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
//	
	robotRunAngle(-900,60,0,0.1);
		for(i=0;i<500;i++)	
	{	
			while(CB_Driff_TRAI == 1 )	
			{	
				vTaskDelay(1); 
				if(wantExit())	break;
			}
	} 
//	
	robotRunAngle(-900,40,0,0.1);
	
				for(i=0;i<500;i++)	
	{	
			while(lazeTruocValue < 100 )	
			{	
				vTaskDelay(1); 
				if(wantExit())	break;
			}
	}
//	
		robotRunAngle(-900,30,0,0.1);
	for(i=0;i<550;i++)	
	{	
			while(lazePhaiValue > 8 )	{vTaskDelay(1); if(wantExit())	break;}
	}	

	robotRunAngle(-900,20,0,0.1);
	
	for(i=0;i<550;i++)	
	{	
			while(CB_THANH_PHAI == 1)	{vTaskDelay(1); if(wantExit())	break;}
	}			
	
	
	robotStop(0);
}



///////////////////////////// Ham nhan data chay tu  dong////////////////////
extern void Trai_do(int vitri,int giamtoc,int cao,int dai);
extern void Phai_do(int vitri,int giamtoc,int cao,int dai);
extern void vtri1vs2do(int vitri,int giamtoc,int cao,int dai);
extern void vtri11do(int cao,int dai);
extern uint8_t has_active_block ;
extern uint8_t id_block ;




////// vi du cach dung
void chaytudong_esp_now_san1(void)
{
    

    if (has_active_block)
    {
        // ?? x? lý move, action, take_data_block ? dây

				if (take_data_block == 3) {
					Trai_do(586,600,725,150);	
					Finish_Current_Block();
					}
				else if (take_data_block == 6) {
					Trai_do(464,536,955,166);
					Finish_Current_Block();
					}
				else if (take_data_block == 9) {
					Trai_do(323,406,725,150);
					Finish_Current_Block();
					}
				else if (take_data_block == 12) {
					Trai_do(172,237,553,161);
					Finish_Current_Block();
					}
				else if (take_data_block == 1) {
					vtri1vs2do(149,163,725,150);
					Finish_Current_Block();
					}
				else if (take_data_block == 4) {
					Phai_do(520,463,553,161);
					Finish_Current_Block();
					}
				else if (take_data_block == 7) {
					Phai_do(620,575,725,150); 
					Finish_Current_Block();
					}
				else if (take_data_block == 10) {
					Phai_do(688,658,553,161); 
					Finish_Current_Block();
					}
				else if (take_data_block == 2) {
					vtri1vs2do(302,307,553,161);
					Finish_Current_Block();					
					}
				else if (take_data_block == 11) {
					vtri11do(725,150);
					Finish_Current_Block();
					}
							}
}