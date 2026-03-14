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
				//robotRunAngle(-450,15,5,0.3);
	
//				RESET_ENCODER();
//	
//				while(abs(ENCODER_RR()) + abs(ENCODER_RL()) < 1350)	{vTaskDelay (1); if(!wantExit())	break;}
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
	
						Bam_thanh_laser_trai(25,0,0,vu_khi,1,150,15);//robotRun(-450,10);
						if(!wantExit())	break;
					}
				}
//////				
				Nang_Ha_Kep = 250;
////				
					for(i=0;i<250;i++)
				{
					while(lazeTruocValue > 20)	
					{	
						Bam_thanh_laser_trai(20 ,0,0,vu_khi,1,150,15);//robotRun(-450,10);
						if(!wantExit())	break;
					}
				}
//////				
				for(i=0;i<100;i++)
				{
					while(HT_1 == 1 && HT_2 == 1)	
					{				
						Bam_thanh_laser_trai(10,0,0,vu_khi,1,100,15);//robotRun(-450,10);
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

//********************************** vao rung mai 1 gap kfs ********************************************
void Vao_rung_mai_1_do(void)
{
	speed_chan_sau = 15;
	speed_chan_truoc = 60;

	target_chan_truoc = 260;
	target_chan_sau = 260;

	
	vTaskDelay(2000);
	
	robotRunAngle(-1500,35,-900,0.2);
	
	for(i=0;i<250;i++)
				{
					while(lazeTruocValue > 210)	
					{	
						vTaskDelay (1);
						if(!wantExit())	break;
					}
				}
				
	for(i=0;i<250;i++)
				{
					while(lazeTraiValue > 175)	
					{	
						vTaskDelay (1);
						if(!wantExit())	break;
					}
				}
				
	for(i=0;i<250;i++)
				{
					while(lazeTruocValue > 18)	
					{	
						Bam_thanh_laser_trai(15,-900,-880,164,2,200,15);//robotRun(-450,10);
						if(!wantExit())	break;
					}
				}
	robotStop(20);
						
				
}

//********************************** vao rung mai 2 gap kfs ********************************************
void Vao_rung_mai_2_do(void)
{
	speed_chan_sau = 15;
	speed_chan_truoc = 60;

	target_chan_truoc = 260;
	target_chan_sau = 260;

	
	vTaskDelay(2000);
	
	robotRunAngle(-1350,35,-900,0.2);
	
	for(i=0;i<250;i++)
				{
					while(lazeTruocValue > 210)	
					{	
						vTaskDelay (1);
						if(!wantExit())	break;
					}
				}
				
	for(i=0;i<250;i++)
				{
					while(lazeTraiValue > 290)	
					{	
						vTaskDelay (1);
						if(!wantExit())	break;
					}
				}
				
	for(i=0;i<250;i++)
				{
					while(lazeTruocValue > 23)	
					{	
						Bam_thanh_laser_trai(15,-900,-880,271,2,150,15);//robotRun(-450,10);
						if(!wantExit())	break;
					}
				}
	robotStop(20);
		
}		


//********************************** vao rung mai 3 gap kfs ********************************************
void Vao_rung_mai_3_do(void)
{
	
	 ////// chay toi gan cua vao
	speed_chan_sau = 15;
	speed_chan_truoc = 60;

	target_chan_truoc = 260;
	target_chan_sau = 260;
//	
//	speed_tay_xoay = 100;
//	target_xoay_tay = 623;
	
	vTaskDelay(2000);
	
	robotRunAngle(-900,35,-900,0.2);
	
	for(i=0;i<250;i++)
				{
					while(lazeTruocValue > 210)	
					{	
						vTaskDelay (1);
						if(!wantExit())	break;
					}
				}
				
	for(i=0;i<250;i++)
				{
					while(lazeTruocValue > 45)	
					{	
							Bam_thanh_laser_phai(30,-900,-880,132,2,160,15);//robotRun(-450,10);
						vTaskDelay (1);
						if(!wantExit())	break;
					}
				}
				
	for(i=0;i<250;i++)
				{
					while(lazeTruocValue > 21)	
					{	
						Bam_thanh_laser_phai(15,-900,-880,132,2, 160,15); //robotRun(-450,10);
						if(!wantExit())	break;
					}
				}
				
	for(i=0;i<250;i++)
				{
					while(lazeTruocValue > 20)	
					{	
						Bam_thanh_laser_phai(15,-900,-880,132,2,160,15);//robotRun(-450,10);
						if(!wantExit())	break;
					}
				}
	robotStop(20); 
				
/////////	do chân cao lên cua 3					
	
	speed_chan_sau = 180;
	speed_chan_truoc = 250;

	target_chan_truoc = 690;
	target_chan_sau = 690;
				
	for(i=0;i<250;i++)	
	{
		while(bientrochantruocValue < 685)	{vTaskDelay(5); if(!wantExit())	break;}
	}			
				

	for(i=0;i<250;i++)	
	{
		while(CB_Ha_Dau == 1)	
			{	
						Bam_thanh_laser_phai(7,-900,-880,132,2,150,15);//robotRun(-450,10);
						if(!wantExit())	break;
			}
	}
	
	RESET_ENCODER();
	
	while(abs(ENCODER_RR()) + abs(ENCODER_RL()) < 540)	
	{	
		Bam_thanh_laser_phai(7,-900,-880,132,2,150,15);//robotRun(-450,10);
		if(!wantExit())	break;
	}
	
	robotStop(30);

}


/// *********** ESP chay tu dong***************
/* ================= INIT CUA STATE 2 VUOT RUNG SAN XANH ================= */

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
    action_table[10][10][1] = Vao_rung_mai_1_do;
    action_table[10][10][2] = Vao_rung_mai_2_do;
    action_table[10][10][3] = Vao_rung_mai_3_do;
	
	    /* =========================================
       move 20 , action 20 chay ra cua ra
       ========================================= */
    action_table[20][20][10] = vuot_rung_ve_homeTay_bac_200;
    action_table[20][20][11] = vuot_rung_ve_homeTay_bac_400;
    action_table[20][20][12] = vuot_rung_ve_homeTay_bac_200;


    /* =========================================
       move 0 , action 1, dung lai de lay o phia truoc
       ========================================= */
//    action_table[0][1][1] = Lay_phia_truoc_bac_400;
//    action_table[0][1][2] = Lay_phia_truoc_bac_200_tren;
//    action_table[0][1][3] = Lay_phia_truoc_bac_400;
//		action_table[0][1][4] = Lay_phia_truoc_bac_200_duoi;
//		action_table[0][1][5] = Lay_phia_truoc_bac_200_tren;
//		action_table[0][1][6] = Lay_phia_truoc_bac_200_tren;
//		action_table[0][1][7] = Lay_phia_truoc_bac_200_tren;
//		action_table[0][1][8] = Lay_phia_truoc_bac_200_tren;
//		action_table[0][1][9] = Lay_phia_truoc_bac_200_duoi;
//		action_table[0][1][10]= Lay_phia_truoc_bac_200_duoi;
//		action_table[0][1][11]= Lay_phia_truoc_bac_200_duoi;
//		action_table[0][1][12]= Lay_phia_truoc_bac_200_duoi;

//    /* =========================================
//       move 0 , action 2, dung lai de lay ben trai
//       ========================================= */

//    /* =========================================
//       move 0 , action 3, dung lai de lay ben phai
//       ========================================= */

    /* =========================================
       move 1 , action 4 chay thang
       ========================================= */
    action_table[1][4][1] = Leo_bac_400;
    action_table[1][4][2] = Leo_bac_200_bam_thanh_phai;
		action_table[1][4][3] = Leo_bac_400;
		action_table[1][4][4]  = Xuong_bac_200_bam_thanh_trai;
//    action_table[1][4][5] = Leo_bac_200_bam_thanh_trai;
    action_table[1][4][6] = Leo_bac_200;
//    action_table[1][4][7] = Leo_bac_200_bam_thanh_trai_encoder;
    action_table[1][4][8] = Leo_bac_200;
//    action_table[1][4][9]  = Xuong_bac_200_encoder_bam_thanh_phai;
    action_table[1][4][10] = Xuong_bac_200;
    action_table[1][4][11] = Xuong_bac_200;
		action_table[1][4][12] = Xuong_bac_200;
		
		/* =========================================
//   move 2 , action 4,chay ben trai
//   ========================================= */

//    action_table[2][4][2] = qua_trai_xuong_bac;
//		action_table[2][4][3] = qua_trai_len_bac;
//    action_table[2][4][5] = qua_trai_len_bac;
//    action_table[2][4][6] = qua_trai_len_bac;
//    action_table[2][4][8] = qua_trai_len_bac;
//    action_table[2][4][9] = qua_trai_xuong_bac;
//    action_table[2][4][11]= qua_trai_len_bac;
//		action_table[2][4][12]= qua_trai_xuong_bac;

		/* =========================================
//   move 3 , action 4,chay ben phai
//   ========================================= */
//		action_table[3][4][1] = qua_phai_len_bac;
//    action_table[3][4][2] = qua_phai_xuong_bac;
//		action_table[3][4][4] =	qua_phai_xuong_bac;
//    action_table[3][4][5] = qua_phai_xuong_bac;
//    action_table[3][4][7] = qua_phai_xuong_bac;
//    action_table[3][4][8] = qua_phai_len_bac;
//    action_table[3][4][10]= qua_phai_xuong_bac;
//    action_table[3][4][11]= qua_phai_len_bac;
//		
}

/* ================= INIT CUA STATE 3 DAT KHOI TREN BUC ================= */
void Init_Zone3_Table_san_do(void)
{
    int m,a,i;

    for(m=0;m<MAX_MOVE;m++)
        for(a=0;a<MAX_ACTION;a++)
            for(i=0;i<MAX_ID;i++)
                zone3_table[m][a][i] = DoNothing;

//    zone3_table[4][15][16] = Zone3_Special_Run; 	//O 4 BI DAT , o 5,6 trong
//    zone3_table[14][5][16] = Zone3_Special_Run;		//O 5 BI DAT , o 4 6 trong
//    zone3_table[14][15][6] = Zone3_Special_Run;		//O 6 BI DAT , o 4 5 trong
//    zone3_table[4][5][16] = Zone3_Special_Run; 		//O 4 5 BI DAT , O 6 trong
//    zone3_table[4][15][6] = Zone3_Special_Run;		//O 4 6 BI DAT , o 5 trong
//    zone3_table[14][5][6] = Zone3_Special_Run;		//O 5 6 BI DAT , o 4 trong
}


/* ================= RUN ================= */
void Run_All_Blocks_From_Queue_san_do(void)
{
    Packet_t pkt;

    while (Queue_Pop(&pkt))
    {
        ActionFunc f = DoNothing;

        if (pkt.move   >= MAX_MOVE   ||
            pkt.action >= MAX_ACTION ||
            pkt.id_block >= MAX_ID)
        {
            f();
            continue;
        }

        switch(pkt.state_rb)
        {
            case 2: // VUOT RUNG
                f = action_table[pkt.move][pkt.action][pkt.id_block];
                break;

            case 3:   // DAT KHOI
                f = zone3_table[pkt.move][pkt.action][pkt.id_block];
                break;

            default:
                break;
        }

        f();
    }

    has_active_block = 0;
}


