extern int Vi_tri;


//*************************** XUAT PHAT LAAYS VU KHI 3 ***********************************
void Xuat_Phat_Lay_Vu_Khi_Xanh(int vu_khi, int goc_ve)
 //				RESET_ENCODER(); 
{					
				speed_chan_sau =180;
				speed_chan_truoc = 250;
				target_chan_truoc = 460, target_chan_sau = 460;
				Kep = 250;
	
				robotRunAngle(-450 - vu_khi*2,25,5,0.3);
				//robotRunAngle(-450,15,5,0.3);
				for(i=0;i<100;i++)
				{
					while(lazePhaiValue < vu_khi - 9)	
					{
						vTaskDelay (1);
					//	if(lazePhaiValue > vu_khi-8)	target_chan_truoc = 578, target_chan_sau =578;
					//Bam_thanh_laser_phai(30,0,0,vu_khi,1,750,30);//robotRun(-450,10); // 0,0,0,khoang cach vs thanh,0,0,0
						if(!wantExit())	break;
					}
				}
				target_chan_truoc = 586, target_chan_sau =585;
	
				for(i=0;i<250;i++)
				{
					while(lazeTruocValue > 25)	
					{	
	
						Bam_thanh_laser_phai(20,0,-10,vu_khi,1,150,15);//robotRun(-450,10);
						if(!wantExit())	break;
					}
				}
				
				Nang_Ha_Kep = 250;
				
					for(i=0;i<250;i++)
				{
					while(lazeTruocValue > 18)	
					{	
						Bam_thanh_laser_phai(15,0,-10,vu_khi,1,100,15);//robotRun(-450,10);
						if(!wantExit())	break;
					}
				}
				
				for(i=0;i<100;i++)
				{
					while(HT_1 == 1 && HT_2 == 1)	
					{				
						Bam_thanh_laser_phai(10,0,-10,vu_khi,1,100,15);//robotRun(-450,10);
						if(!wantExit())	break;
					}
				}
				
				Kep = 0;
				
				robotStop(30);
				
				//robotRun(0,3);
				
				vTaskDelay(3000);
				
				speed_chan_sau =15;
				speed_chan_truoc = 35;
				
				target_chan_truoc = 615, target_chan_sau = 615;
				
				vTaskDelay(4000);
				
				robotStop(30);
				
				target_chan_truoc = 650, target_chan_sau = 650;
				
				vTaskDelay(4000);
				
				robotRun(goc_ve,20);
				robotRotate(-920,-0.9,0);
				
				RESET_ENCODER(); 
								
				speed_chan_sau =80;
				speed_chan_truoc = 130;
				
				while(_robotIMUAngle >-840)	
				{
					vTaskDelay (5); 
					if(!wantExit())	break;
					if(_robotIMUAngle < -450)		target_chan_truoc = 270, target_chan_sau = 270;
				}
				
				Nang_Ha_Kep = 0; 
				robotStop(10);		
				
				robotRunAngle(900,6,-900,0.2);
				
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
				target_chan_truoc = 228, target_chan_sau = 228;
				
				robotStop(00);
				
}

//********************************** vao rung mai 1 gap kfs ********************************************
void Vao_rung_mai_1(void)
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
void Vao_rung_mai_2(void)
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
void Vao_rung_mai_3(void)
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
ActionFunc action_table[MAX_MOVE][MAX_ACTION][MAX_ID];


/* ================= DEFAULT ================= */

void DoNothing(void) {}
	
extern int hoan_thanh_chay_rung;


/* ================= INIT ================= */

void Init_Action_Table(void)
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
    action_table[10][10][1] = Vao_rung_mai_1;
    action_table[10][10][2] = Vao_rung_mai_2;
    action_table[10][10][3] = Vao_rung_mai_3;
	
	    /* =========================================
       move 20 , action 20 chay ra cua ra
       ========================================= */
    action_table[20][20][10] = vuot_rung_ve_homeTay_bac_200;
    action_table[20][20][11] = vuot_rung_ve_homeTay_bac_400;
    action_table[20][20][12] = vuot_rung_ve_homeTay_bac_200;


    /* =========================================
       move 0 , action 1, dung lai de lay o phia truoc
       ========================================= */
    action_table[0][1][1] = Lay_phia_truoc_bac_400;
    action_table[0][1][2] = Lay_phia_truoc_bac_200_tren;
    action_table[0][1][3] = Lay_phia_truoc_bac_400;
		action_table[0][1][4] = Lay_phia_truoc_bac_200_duoi;
		action_table[0][1][5] = Lay_phia_truoc_bac_200_tren;
		action_table[0][1][6] = Lay_phia_truoc_bac_200_tren;
		action_table[0][1][7] = Lay_phia_truoc_bac_200_tren;
		action_table[0][1][8] = Lay_phia_truoc_bac_200_tren;
		action_table[0][1][9] = Lay_phia_truoc_bac_200_duoi;
		action_table[0][1][10] = Lay_phia_truoc_bac_200_duoi;
		action_table[0][1][11] = Lay_phia_truoc_bac_200_duoi;
		action_table[0][1][12] = Lay_phia_truoc_bac_200_duoi;

//    /* =========================================
//       move 0 , action 2, dung lai de lay ben trai
//       ========================================= */
//    action_table[0][2][1] = Lay_phia_truoc_bac_400;
//    action_table[0][2][2] = Lay_phia_truoc_bac_200_tren;
//    action_table[0][2][3] = Lay_phia_truoc_bac_400;
//		action_table[0][2][4] = Lay_phia_truoc_bac_200_tren;
//		action_table[0][2][5] = Lay_phia_truoc_bac_200_tren;
//		action_table[0][2][6] = Lay_phia_truoc_bac_200_tren;
//		action_table[0][2][7] = Lay_phia_truoc_bac_200_tren;
//		action_table[0][2][8] = Lay_phia_truoc_bac_200_tren;
//		action_table[0][2][9] = Lay_phia_truoc_bac_200_tren;
////		action_table[0][2][10] = Lay_phia_truoc_bac_200_tren;
////		action_table[0][2][11] = Lay_phia_truoc_bac_200_tren;
////		action_table[0][2][12] = Lay_phia_truoc_bac_200_tren;

//    /* =========================================
//       move 0 , action 3, dung lai de lay ben phai
//       ========================================= */
//    action_table[0][3][1] = Lay_phia_truoc_bac_400;
//    action_table[0][3][2] = Lay_phia_truoc_bac_200_tren;
//    action_table[0][3][3] = Lay_phia_truoc_bac_400;
//		action_table[0][3][4] = Lay_phia_truoc_bac_200_tren;
//		action_table[0][3][5] = Lay_phia_truoc_bac_200_tren;
//		action_table[0][3][6] = Lay_phia_truoc_bac_200_tren;
//		action_table[0][3][7] = Lay_phia_truoc_bac_200_tren;
//		action_table[0][3][8] = Lay_phia_truoc_bac_200_tren;
//		action_table[0][3][9] = Lay_phia_truoc_bac_200_tren;
////		action_table[0][3][10] = Lay_phia_truoc_bac_200_tren;
////		action_table[0][3][11] = Lay_phia_truoc_bac_200_tren;
////		action_table[0][3][12] = Lay_phia_truoc_bac_200_tren;

    /* =========================================
       move 1 , action 4 chay thang
       ========================================= */
    action_table[1][4][1] = Leo_bac_400;
    action_table[1][4][2] = Leo_bac_200_bam_thanh_phai;
		action_table[1][4][3] = Leo_bac_400;
		action_table[1][4][4]  = Xuong_bac_200_encoder_bam_thanh_phai;
    action_table[1][4][5] = Leo_bac_200_bam_thanh_phai;
    action_table[1][4][6] = Leo_bac_200;
    action_table[1][4][7] = Leo_bac_200_bam_thanh_phai_encoder;
    action_table[1][4][8] = Leo_bac_200;
    action_table[1][4][9]  = Xuong_bac_200;
    action_table[1][4][10] = Xuong_bac_200;
    action_table[1][4][11] = Xuong_bac_200;
		action_table[1][4][12] = Xuong_bac_200;
}


/* ================= RUN ================= */

//void Run_All_Blocks_From_Queue(void)
//{
//    Packet_t pkt;

//    while (Queue_Pop(&pkt))
//    {
//        move   = pkt.move;
//        action = pkt.action;
//        take_data_block = pkt.id_block;

//        if (move < MAX_MOVE &&
//            action < MAX_ACTION &&
//            take_data_block < MAX_ID)
//        {
//            action_table[move][action][take_data_block]();
//        }
//        else
//        {
//            DoNothing();
//        }
//    }

//    has_active_block = 0;
//}



void Run_All_Blocks_From_Queue(void)
{
    Packet_t pkt;

    while (Queue_Pop(&pkt))
    {
        move   = pkt.move;
        action = pkt.action;
        take_data_block = pkt.id_block;

        if (move < MAX_MOVE &&
            action < MAX_ACTION &&
            take_data_block < MAX_ID)
        {
            action_table[move][action][take_data_block]();
        }
        else
        {
            DoNothing();
        }
    }

    has_active_block = 0;
}


//void chaytudong_esp_now(void)
//{
//    Take_Next_Block_From_Queue();

//    if (has_active_block)
//    {
//        // ?? x? lý move, action, take_data_block ? dây

//				if (move == 0 && take_data_block == 2 ) {
//					Vao_rung_mai_2(); 	
//					Finish_Current_Block();
//					}
//				else if (move == 1 && take_data_block == 2) {
//					Leo_bac_200();
//					Finish_Current_Block();
//					}
//				else if (take_data_block == 5) {
//					Leo_bac_200();
//					Finish_Current_Block();
//					}
//				else if (take_data_block == 8) {
//					Leo_bac_200();
//					Finish_Current_Block();
//					}
//				else if (take_data_block == 11) {
//					Xuong_bac_200();
//					Finish_Current_Block();
//					}
//				else if (take_data_block == 1) {
//					Leo_bac_200();
//					Finish_Current_Block();
//					}
//				else if (take_data_block == 4) {
//					Phai_do(517,463,553,161);
//					Finish_Current_Block();
//					}
//				else if (take_data_block == 7) {
//					Phai_do(618,575,725,150); 
//					Finish_Current_Block();
//					}
//				else if (take_data_block == 10) {
//					Phai_do(685,658,553,161); 
//					Finish_Current_Block();
//					}
//				else if (take_data_block == 2) {
//					vtri1vs2do(302,307,553,161);
//					Finish_Current_Block();					
//					}
//				else if (take_data_block == 11) {
//					vtri11do(725,150);
//					Finish_Current_Block();
//					}
//							}
//}

//******************************* DatKFSxanh **************************
void DatKFSxanh(int vitri)
{
				speed_chan_sau =180;
				speed_chan_truoc = 250;
				target_chan_truoc = 300, target_chan_sau = 300;

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

//	robotRun(-450,20);
//	robotRotate(0,-0.9,0);
//	
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

int hoan_thanh_xoay_tay1 = 0;
int hoan_thanh_xoay_tay2 = 0;
int hoan_thanh_xoay_tay3 = 0;

void xoay_tay_dat_qua(void) {
if (da_lay_tay1 == 1) {
		speed_tay_xoay = 150;
		target_xoay_tay = 618;
		vTaskDelay(12000);
		hoan_thanh_xoay_tay1 = 1;
		hoan_thanh_xoay_tay2 = 0;
		hoan_thanh_xoay_tay3 = 0;
}
else if (da_lay_tay2 == 1) {
		speed_tay_xoay = 150;
		target_xoay_tay = 520;
		vTaskDelay(12000);
		hoan_thanh_xoay_tay1 = 0;
		hoan_thanh_xoay_tay2 = 1;
		hoan_thanh_xoay_tay3 = 0;
	
	
	} 
else if (da_lay_tay3 == 1) {
		speed_tay_xoay = 100;
		target_xoay_tay = 410;
		vTaskDelay(12000);
		hoan_thanh_xoay_tay1 = 0;
		hoan_thanh_xoay_tay2 = 0;
		hoan_thanh_xoay_tay3 = 1;
	}
}

// ************** dat qua o 1 **************
void dat_qua_o_1(void) {
	
	speed_chan_sau = 100;
	speed_chan_truoc = 140;
	
	target_chan_truoc = 660, target_chan_sau = 660;
	Tay3_day_ra;
	Tay1_day_ra;
	Tay2_day_ra;
	
	
		for(i=0;i<250;i++)	
	{
		while(bientrochantruocValue < 650)	{vTaskDelay(5); if(!wantExit())	break;}
	}		
	if (hoan_thanh_xoay_tay1 == 1) {
		Tay_1_gap_kfs_xuong();
		vTaskDelay(3000);
		Tay1_day_ra;
		Tay_1_gap_kfs_dung();
	
		Bom1_off;
		Tay1_xa_on;
		for(i=0;i<250;i++)	
		{
		while(HT_qua_1 == 0)	{vTaskDelay(5); if(!wantExit())	break;}
		}
		vTaskDelay(5000);
		for(i=0;i<5;i++)	
		{
		speed_tay_xoay = 150;
		target_xoay_tay = 618 - 20;
		vTaskDelay(12000);
		speed_tay_xoay = 150;
		target_xoay_tay = 618 + 20;
		vTaskDelay(12000);
		}
		target_xoay_tay= 618;
	}
	
	if (hoan_thanh_xoay_tay2 == 1) {
		Tay_2_gap_kfs_xuong();
		vTaskDelay(3000);
		Tay2_day_ra;
		Tay_2_gap_kfs_dung();
	
		Bom2_off;
		Tay2_xa_on;
		for(i=0;i<250;i++)	
		{
		while(HT_qua_2 == 0)	{vTaskDelay(5); if(!wantExit())	break;}
		}
		vTaskDelay(5000);
		
		// lac lac hop 2 ben
		for(i=0;i<5;i++)	
		{
		speed_tay_xoay = 150;
		target_xoay_tay = 520+ 20;
		vTaskDelay(12000);
		speed_tay_xoay = 150;
		target_xoay_tay = 520 - 20;
		vTaskDelay(12000);
		}
		target_xoay_tay= 520;
		
	}
	if (hoan_thanh_xoay_tay3 == 1) {
		Tay_3_gap_kfs_xuong();
		vTaskDelay(3000);
		
		Tay_3_gap_kfs_dung();
	
		Bom3_off;
		Tay3_xa_on;
		for(i=0;i<250;i++)	
		{
		while(HT_qua_3 == 0)	{vTaskDelay(5); if(!wantExit())	break;}
		}
		vTaskDelay(5000);
				// lac lac hop 2 ben
		for(i=0;i<5;i++)	
		{
		speed_tay_xoay = 100;
		target_xoay_tay = 410 + 20;
		vTaskDelay(12000);
		speed_tay_xoay = 100;
		target_xoay_tay = 410 - 20;
		vTaskDelay(12000);
		}
		target_xoay_tay= 410;
		
	}
			robotRunAngle(150 , 8, 0, 0.2);
			vTaskDelay(20000);
			robotStop(30);
			robotRun(1800 , 5);
			vTaskDelay(5000);
			robotStop(30);
}


void tudonghoantoan(void) {
Run_All_Blocks_From_Queue();
if (hoan_thanh_chay_rung == 1 )DatKFSxanh(42),hoan_thanh_chay_rung = 2 ;
if (hoan_thanh_chay_rung== 2) xoay_tay_dat_qua(),hoan_thanh_chay_rung = 3;
if (hoan_thanh_chay_rung== 3) dat_qua_o_1(),hoan_thanh_chay_rung = 4;

}
