extern int Vi_tri;
extern int da_lay_tay4;
extern int TinHieu_ChuanBi_GapThang;
extern int TinHieu_ChuanBi_GapTrai ;
extern int TinHieu_ChuanBi_GapPhai;


//*************************** XUAT PHAT LAAYS VU KHI 3 ***********************************
void Xuat_Phat_Lay_Vu_Khi_Xanh(int vu_khi, int goc_ve)
 //				RESET_ENCODER(); 
{				
				speed_tay_gat1 = 150;
				target_tay_gat1 = 131;
	
				speed_tay_gat2 = 250;
				target_tay_gat2 = 137;
	
				Nang_cuc_nhanh();
	
				target_chan_truoc = 350, target_chan_sau = 350;
				Kep = 250;
	
				robotRunAngle(-150 - vu_khi*2,30,5,0.3);
				//robotRunAngle(-450,15,5,0.3);
				for(i=0;i<100;i++)
				{
					while(lazePhaiValue < vu_khi - 20)	
					{
						if(!wantExit())	break;
					}
				}

				target_chan_truoc = 605, target_chan_sau =600;
				for(i=0;i<50;i++)		
				{
				while(bientrochantruocValue < 430)	{
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
				Nang_Ha_Kep = 250;
			
//				
				for(i=0;i<100;i++)
				{
					while(HT_1 == 1 && HT_2 == 1)	
					{				
						Bam_thanh_laser_phai(10,0,0,vu_khi,1,100,15);//robotRun(-450,10);
						if(!wantExit())	break;
					}
				}
//			
				robotStop(50);
				
				vTaskDelay (2000);
				
				for(i=0;i<500;i++)
				{
					while(CB_tay_kep_vk_T == 1 || CB_tay_kep_vk_P == 1)	
					{	
						if	(CB_tay_kep_vk_P == 1) robotRun(-900,6);
						else if 	(CB_tay_kep_vk_T == 1) robotRun(900,6);
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
						vTaskDelay (1);						
						if(!wantExit())	break;
					}
				}
				robotStop(0);
				
				speed_chan_sau =30;
				speed_chan_truoc = 70;
				
				target_chan_truoc = 615, target_chan_sau = 615;
				
				vTaskDelay(4000);
				
				robotStop(30);
				
				target_chan_truoc = 655, target_chan_sau = 630;
				
				Nang_Ha_Kep = 0; 
				
				vTaskDelay(5000);
				
				robotRun(goc_ve,30);
				robotRotate(-900,-1.2,0);
//				
				RESET_ENCODER(); 
//								
				speed_chan_sau =80;
				speed_chan_truoc = 130;
//				
				while(_robotIMUAngle >-750)	
				{
					vTaskDelay (5); 
					if(!wantExit())	break;
					if(_robotIMUAngle < -450)		target_chan_truoc = 250, target_chan_sau = 250;
				}
//				
//				Nang_Ha_Kep = 0; 
					
	
				robotRunAngle(900,8,-900,0.7);
				
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
				robotStop(00);
				
			}

//********************************** vao rung mai 1 gap kfs ********************************************
void Vao_rung_mai_1_xanh(int vitri)
{
	speed_chan_sau = 15;
	speed_chan_truoc = 60;

	target_chan_truoc = 250;
	target_chan_sau = 250;

	
	vTaskDelay(2000);
	
	Kep_phai_4_ra;

	
	robotRunAngle(-1450,30,900,1.8);
//				
				while(_robotIMUAngle < 895)	
				{
					vTaskDelay (5); 
					if(!wantExit())	break;
				}
				
	robotRunAngle(-1600,30,900,0.2);
	for(i=0;i<250;i++)
				{
					while(lazePhaiValue > vitri + 15)	
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
		Bam_thanh_laser_phai_cua_vao(15,-900,900,vitri,2,450,30);
		if(!wantExit())	break;
					}
		
	}
	
	for(i=0;i<250;i++)
				{
					while(lazeSauValue > 25)	
					{	
						Bam_thanh_laser_phai_cua_vao(12,-900,900,vitri,2,250,30);
						if(!wantExit())	break;
					}
				}
			
	for(i=0;i<250;i++)
				{
					while(lazeSauValue > 1 || CB_Ha_Sau == 1)	
					{	
						su_dung_chan(697);
						Bam_thanh_laser_phai_cua_vao(8,-900,900,vitri,2,150,30);
						if(!wantExit())	break;
					}
				}

	vTaskDelay (5); 
	RESET_ENCODER(); 
	
	for(i=0;i<250;i++) {
	while(abs(ENCODER_FR()) + abs(ENCODER_FL()) < 1700)	
		{	
				Bam_thanh_laser_phai_cua_vao(8,-900,900,vitri,2,350,30);
				vTaskDelay (1);
				if(!wantExit())	break;
		}
	}
	robotStop(0); 
	chinh_lai_vi_tri_laser_phai(vitri, 1000);
	robotStop(0); 	
		
				
}

void auto_vao_rung_cua1(void) {
		Vao_rung_mai_1_xanh(310);
}

//********************************** vao rung mai 2 gap kfs ********************************************
void Vao_rung_mai_2_xanh(int vitri)
{
	speed_chan_sau = 15;
	speed_chan_truoc = 60;

	target_chan_truoc = 250;
	target_chan_sau = 250;

	//kiem_tra_huong_quay_tay_gap_phia_truoc();
	Kep_phai_4_ra;
	
	
	robotRunAngle(-1550,25,900,1.8);
//				
				while(_robotIMUAngle < 895)	
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
						Bam_thanh_laser_trai(20,-900,900,vitri,2,450,30);//robotRun(-450,10);
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
			Bam_thanh_laser_trai(8,-900,900,vitri,2,350,30);//robotRun(-450,10);
			if(!wantExit())	break;
			vTaskDelay (1);
		}
	}			
				
	for(i=0;i<1550;i++)
				{
					while(lazeSauValue > 2 || CB_Ha_Sau == 1)	
					{	
						Bam_thanh_laser_trai(8,-900,900,vitri,2,50,30);
						if(!wantExit())	break;
						vTaskDelay (1);
					}
				}
				
	su_dung_chan(580);
	RESET_ENCODER(); 
	
	while(abs(ENCODER_FR()) + abs(ENCODER_FL()) < 1700)	
		{	
				Bam_thanh_laser_trai(8,-900,900,vitri,2,50,30);
				if(!wantExit())	break;
		}
		
	robotStop(0); 
		
	chinh_lai_vi_tri_laser_trai(vitri, 1000);
	
	robotStop(0); 			
						
}	


void auto_vao_rung_xanh_cua2(void) {
		Vao_rung_mai_2_xanh(460);
}




//********************************** vao rung mai 3 gap kfs ********************************************
void Vao_rung_mai_3_xanh(int vitri)
{
	
	 ////// chay toi gan cua vao
		speed_chan_sau = 15;
	speed_chan_truoc = 60;

	target_chan_truoc = 250;
	target_chan_sau = 250;

	
	vTaskDelay(2000);
	
	robotRunAngle(-900,25,900,1.8);
//				
				while(_robotIMUAngle < 895)	
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
		Bam_thanh_laser_trai(20,-900,900,vitri,2,350,30);
		if(!wantExit())	break;
					}
		
	}
	
	for(i=0;i<250;i++)
				{
					while(lazeSauValue > 25)	
					{	
						Bam_thanh_laser_trai(20,-900,900,vitri,2,350,30);
							vTaskDelay (1);
						if(!wantExit())	break;
					}
				}
			
		su_dung_chan(697);
				
		for(i=0;i<1550;i++)
				{
					while(lazeSauValue > 1 || CB_Ha_Sau == 1)	
					{	
						
						Bam_thanh_laser_trai(8,-900,900,vitri,2,50,30);
						if(!wantExit())	break;
						vTaskDelay (1);
					}
				}

		RESET_ENCODER(); 
	
	for(i=0;i<250;i++) {
	while(abs(ENCODER_RR()) + abs(ENCODER_RL()) < 1600)	
		{	
				Bam_thanh_laser_trai(8,-900,900,vitri,2,350,30);
				vTaskDelay (1);
				if(!wantExit())	break;
		}
	}
	robotStop(0); 
	chinh_lai_vi_tri_laser_trai(vitri, 1000);
	
	robotStop(0); 	
				

}

void auto_vao_rung_xanh_cua3(void) {
		Vao_rung_mai_3_xanh(314);
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
    action_table[10][10][1] = auto_vao_rung_cua1;
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
//       move 0 , action 2, dung lai de lay ben trai
//       ========================================= */

//    /* =========================================
//       move 0 , action 3, dung lai de lay ben phai
//       ========================================= */

    /* =========================================
       move 1 , action 4 chay thang
       ========================================= */
    action_table[1][4][1] = Leo_bac_400_ko_thanh;
    action_table[1][4][2] = Leo_bac_200_bam_thanh_phai;
		action_table[1][4][3] = Leo_bac_400_co_thanh;
		action_table[1][4][4] = Xuong_bac_200_bam_thanh_phai;
    action_table[1][4][5] = Leo_bac_200_bam_thanh_phai;
    action_table[1][4][6] = Leo_bac_200_ko_thanh;
    action_table[1][4][7] = Leo_bac_200_bam_thanh_phai_encoder;
    action_table[1][4][8] = Leo_bac_200_ko_thanh;
    action_table[1][4][9]  = Xuong_bac_200_encoder_bam_thanh_trai;
    action_table[1][4][10] = xuong_bac_200_end;
    action_table[1][4][11] = xuong_bac_200_end;
		action_table[1][4][12] = xuong_bac_200_end;
		
				/* =========================================
//   move 2 , action 4,chay ben trai
//   ========================================= */
//		action_table[2][4][1] = qua_trai_len_bac;
//    action_table[2][4][2] = qua_trai_xuong_bac;
//    action_table[2][4][4] = qua_trai_xuong_bac;
//    action_table[2][4][5] = qua_trai_xuong_bac;
//    action_table[2][4][7] = qua_trai_xuong_bac;
//    action_table[2][4][8]  = qua_trai_len_bac;
//    action_table[2][4][10] = qua_trai_xuong_bac;
//		action_table[2][4][11] = qua_trai_len_bac;

		/* =========================================
//   move 3 , action 4,chay ben phai
//   ========================================= */
//    action_table[3][4][2] = qua_phai_xuong_bac;
//		action_table[3][4][3] = qua_phai_len_bac;
//		action_table[3][4][5]  =qua_phai_len_bac;
//    action_table[3][4][6] = qua_phai_len_bac;
//    action_table[3][4][8] = qua_phai_len_bac;
//    action_table[3][4][9] = qua_phai_xuong_bac;
//    action_table[3][4][11] = qua_phai_len_bac;
//    action_table[3][4][12] = qua_phai_xuong_bac;
//		
}

/* ================= INIT CUA STATE 3 DAT KHOI TREN BUC ================= */
void Init_Zone3_Table_xan_xanh(void)
{
    int m,a,i;

    for(m=0;m<MAX_MOVE;m++)
        for(a=0;a<MAX_ACTION;a++)
            for(i=0;i<MAX_ID;i++)
                zone3_table[m][a][i] = DoNothing;
//    zone3_table[14][15][16] = Zone3_Special_Run; 	// o 4, 5,6 trong
//    zone3_table[4][15][16] = Zone3_Special_Run; 	//O 4 BI DAT , o 5,6 trong
//    zone3_table[14][5][16] = Zone3_Special_Run;		//O 5 BI DAT , o 4 6 trong
//    zone3_table[14][15][6] = Zone3_Special_Run;		//O 6 BI DAT , o 4 5 trong
//    zone3_table[4][5][16] = Zone3_Special_Run; 		//O 4 5 BI DAT , O 6 trong
//    zone3_table[4][15][6] = Zone3_Special_Run;		//O 4 6 BI DAT , o 5 trong
//    zone3_table[14][5][6] = Zone3_Special_Run;		//O 5 6 BI DAT , o 4 trong
//    zone3_table[4][5][6] = Zone3_Special_Run; 	// o 4, 5,6 bi dat
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
        return 1;
    }
    else if (next2.move == 0 && next2.action == 2)
    {
        TinHieu_ChuanBi_GapTrai = 1;
        return 1;
    }
    else if (next2.move == 0 && next2.action == 3)
    {
        TinHieu_ChuanBi_GapPhai = 1;
        return 1;
    }

    return 0;
}
void Run_All_Blocks_From_Queue_san_xanh(void)
{
    Packet_t pkt;

    if (count_data_uart4 == 0)
        return;

    /* nhìn tru?c 2 block */
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

//void Run_All_Blocks_From_Queue_san_xanh(void)
//{
//    Packet_t pkt;

//    while (Queue_Pop(&pkt))
//    {
//        ActionFunc f = DoNothing;

//        if (pkt.move   >= MAX_MOVE   ||
//            pkt.action >= MAX_ACTION ||
//            pkt.id_block >= MAX_ID)
//        {
//            f();
//            continue;
//        }

//        switch(pkt.state_rb)
//        {
//            case 2: // VUOT RUNG
//                f = action_table[pkt.move][pkt.action][pkt.id_block];
//                break;

//            case 3:   // DAT KHOI LEN BUC	
//                f = zone3_table[pkt.move][pkt.action][pkt.id_block];
//                break;

//            default:
//                break;
//        }

//        f();
//    }

//    has_active_block = 0;
//}



//******************************* DatKFSxanh **************************
void DatKFSxanh(int vitri)
{
				speed_chan_sau =180;
				speed_chan_truoc = 250;
				target_chan_truoc = 300, target_chan_sau = 300;
	for(i=0;i<250;i++)	
	{
		while(bientrochansauValue < 300)	{vTaskDelay(5); if(!wantExit())	break;}
	}
		robotRunAngle(1800,40,-900,0.1);
		for(i=0;i<550;i++)	
	{	
			while(lazeTraiValue > 64)	
			{	
				vTaskDelay(5); 
				if(!wantExit())	break;
			}
	}	
	robotStop(0);
	
		for(i=0;i<550;i++)	
	{	
			while(lazePhaiValue > 100)	
			{	
				Bam_thanh_laser_trai(30,-900,-900,64,2,150,20);
				vTaskDelay(5); 
				if(!wantExit())	break;
			}
	}	
	
		for(i=0;i<550;i++)	
	{	
			while(lazePhaiValue < 100)	
			{	
				Bam_thanh_laser_trai(30,-900,-900,64,2,150,20);
				vTaskDelay(5); 
				if(!wantExit())	break;
			}
	}		
	
	for(i=0;i<550;i++)	
	{	
			while(lazeTruocValue > 110)	
			{	
				Bam_thanh_laser_trai(30,-900,-900,64,2,150,20);
				vTaskDelay(5); 
				if(!wantExit())	break;
			}
	}		
	robotStop(0);
	
	robotRunAngle(0,20,0,0.7);

	while(_robotIMUAngle < -50)	
				{
					vTaskDelay (5); 
					if(!wantExit())	break;
				}
//	robotRotateStop();
//				
	robotRunAngle(0,40,0,0.1);
		for(i=0;i<550;i++)	
	{	
			while(lazeTruocNhoValue > 400)	
			{	
				Bam_thanh_laser_trai(40,0,0,vitri,2,350,20);
				vTaskDelay(5); 
				if(!wantExit())	break;
			}
	}	
	
		for(i=0;i<550;i++)	
	{	
			while(lazeTruocNhoValue > 220)	
			{	
				Bam_thanh_laser_trai(20,0,0,vitri,2,350,20);
				vTaskDelay(5); 
				if(!wantExit())	break;
			}
	}	

		for(i=0;i<550;i++)	
	{	
			while(lazeTruocNhoValue > 165)	
			{	
				Bam_thanh_laser_trai(8,0,0,vitri,2,350,20);
				vTaskDelay(5); 
				if(!wantExit())	break;
			}
	}	
	robotStop(0);
}

//int hoan_thanh_xoay_tay1 = 0;
//int hoan_thanh_xoay_tay2 = 0;
//int hoan_thanh_xoay_tay3 = 0;

//void xoay_tay_dat_qua(void) {
//if (da_lay_tay1 == 1) {
//		speed_tay_xoay = 150;
//		target_xoay_tay = 618;
//		vTaskDelay(12000);
//		hoan_thanh_xoay_tay1 = 1;
//		hoan_thanh_xoay_tay2 = 0;
//		hoan_thanh_xoay_tay3 = 0;
//}
//else if (da_lay_tay2 == 1) {
//		speed_tay_xoay = 150;
//		target_xoay_tay = 520;
//		vTaskDelay(12000);
//		hoan_thanh_xoay_tay1 = 0;
//		hoan_thanh_xoay_tay2 = 1;
//		hoan_thanh_xoay_tay3 = 0;
//	
//	
//	} 
//else if (da_lay_tay3 == 1) {
//		speed_tay_xoay = 100;
//		target_xoay_tay = 410;
//		vTaskDelay(12000);
//		hoan_thanh_xoay_tay1 = 0;
//		hoan_thanh_xoay_tay2 = 0;
//		hoan_thanh_xoay_tay3 = 1;
//	}
//}

//// ************** dat qua o 1 **************
//void dat_qua_o_1(void) {
//	
//	speed_chan_sau = 100;
//	speed_chan_truoc = 140;
//	
//	target_chan_truoc = 560, target_chan_sau = 560;

//	
//	
//		for(i=0;i<250;i++)	
//	{
//		while(bientrochantruocValue < 650)	{vTaskDelay(5); if(!wantExit())	break;}
//	}		
//	if (hoan_thanh_xoay_tay1 == 1) {
//		Tay_1_gap_kfs_xuong();
//		vTaskDelay(3000);

//		Tay_1_gap_kfs_dung();
//	
//		Bom1_off;

//		for(i=0;i<250;i++)	
//		{
//		while(HT_qua_1 == 0)	{vTaskDelay(5); if(!wantExit())	break;}
//		}
//		vTaskDelay(5000);
////		for(i=0;i<5;i++)	
////		{
////		speed_tay_xoay = 150;
////		target_xoay_tay = 618 - 20;
////		vTaskDelay(12000);
////		speed_tay_xoay = 150;
////		target_xoay_tay = 618 + 20;
////		vTaskDelay(12000);
////		}
////		target_xoay_tay= 618;
//	}
//	
//	if (hoan_thanh_xoay_tay2 == 1) {
//		vTaskDelay(3000);

//		Tay_2_gap_kfs_dung();
//	
//		Bom2_off;
//		Kep_phai_4_ra;
//		for(i=0;i<250;i++)	
//		{
//		while(HT_qua_2 == 0)	{vTaskDelay(5); if(!wantExit())	break;}
//		}
//		vTaskDelay(5000);
//		
//		// lac lac hop 2 ben
//		for(i=0;i<5;i++)	
//		{
//		speed_tay_xoay = 150;
//		target_xoay_tay = 520+ 20;
//		vTaskDelay(12000);
//		speed_tay_xoay = 150;
//		target_xoay_tay = 520 - 20;
//		vTaskDelay(12000);
//		}
//		target_xoay_tay= 520;
//		
//	}
//	if (hoan_thanh_xoay_tay3 == 1) {
//		Tay_3_gap_kfs_xuong();
//		vTaskDelay(3000);
//		
//		Tay_3_gap_kfs_dung();
//	
//		Bom3_off;
//		Tay3_xa_on;
//		for(i=0;i<250;i++)	
//		{
//		while(HT_qua_3 == 0)	{vTaskDelay(5); if(!wantExit())	break;}
//		}
//		vTaskDelay(5000);
//				// lac lac hop 2 ben
//		for(i=0;i<5;i++)	
//		{
//		speed_tay_xoay = 100;
//		target_xoay_tay = 410 + 20;
//		vTaskDelay(12000);
//		speed_tay_xoay = 100;
//		target_xoay_tay = 410 - 20;
//		vTaskDelay(12000);
//		}
//		target_xoay_tay= 410;
//		
//	}
//			robotRunAngle(200 , 5, 0, 0.2);
//			vTaskDelay(7000);
//			robotStop(30);
//			robotRun(1800 , 5);
//			vTaskDelay(5000);
//			robotStop(30);
//}


//void tudonghoantoan(void) {
//Run_All_Blocks_From_Queue_san_xanh();
//vTaskDelay(7000);
//if (hoan_thanh_chay_rung == 1 )DatKFSxanh(45),hoan_thanh_chay_rung = 2 ;
//if (hoan_thanh_chay_rung== 2) xoay_tay_dat_qua(),hoan_thanh_chay_rung = 3;
//if (hoan_thanh_chay_rung== 3) dat_qua_o_1(),hoan_thanh_chay_rung = 4;

//}
