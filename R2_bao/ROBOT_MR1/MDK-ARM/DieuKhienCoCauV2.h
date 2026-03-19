
//*****************************8 bien toan cuc *************************************
char 	Khoang_cach_1_vong = 16, bien_xl_nang_ha, bien_xl_mac_vong, bien_xl_chot, bien_xl_kep_vong, bien_xl_day,bien_xl_tru_giua,bien_xl_keo_loxo;
char	vi_tri = 0, Cbcc = 0, Cbnv = 0,Cbnn = 0, Resetnangvong = 0;

int  Nang_vong_max = 325, Nang_vong_min = 105, i; 
int  Nang_goc_max = 540, Nang_goc_min = 300;

int en_tru = 60;

int g0 = 447, g1 = 500, g2 = 530, g3 = 485, g4 = 475 , g5 = 481, g6 = 502; 

void capvong(void);
void Dk_cylinder_keo(void);

void testnangxilanhdien()
{
	if (!R1 && !TRIANGLE && R2)   		Xi_lanh_dien = 100,Xi_lanh_dien_up;
	else if (!R1 && !X && R2)					Xi_lanh_dien = 100,Xi_lanh_dien_down;
	else 															Xi_lanh_dien = 0;

}
void testnangvong()
{
	if (!R1 && !SQUARE )   Mor_nang = 200,Mor_nang_up;
	else if (!R1 && !O)	Mor_nang = 200,Mor_nang_down;
	else Mor_nang = 0;

}
void testxilanhkeo()
{
	if (!R2 && !SQUARE)   Mor_keo =200,Mor_keo_down;
	else if (!R2 && !O)	Mor_keo = 200,Mor_keo_up;
	else Mor_keo = 0;

}
void robotGamePadControl(void)
{
	
    int tocdo = 20;
		float	tocdoXoay = 0;
    int rJoy_LR  = (RJOY_LR >= 5 && RJOY_LR <= 250)? 1 : 0; 
    int lJoy_LR  = (LJOY_LR >= 5 && LJOY_LR <= 250)? 1 : 0;

    if(UP && DOWN && RIGHT && LEFT && rJoy_LR && lJoy_LR && O)
		{ // Khong dieu khien
        robotStop(0); //truot banh
				
        return;
    }                
/*_____________________________//___________________________*/

/********************** TOC DO ****************************/
/*_____________________________//___________________________*/
     if(!L1) tocdo = 30, tocdoXoay = 0.5;
		 else tocdo = 15, tocdoXoay = 0.3;
    
    //--------- chay cac huong -----------
    if		(!UP && DOWN && RIGHT && LEFT && L2)   	robotRun(0, tocdo);
    else if(UP && !DOWN && RIGHT && LEFT && L2)   robotRun(1800, tocdo);
    else if(UP && DOWN && !RIGHT && LEFT && L2)   robotRun(750, tocdo);
    else if(UP && DOWN && RIGHT && !LEFT)   robotRun(-750, tocdo);
    
    else if(!UP && DOWN && !RIGHT && LEFT && L2)  robotRun(450,tocdo);
    else if(!UP && DOWN && RIGHT && !LEFT && L2)  robotRun(-450,tocdo);
    else if(UP && !DOWN && !RIGHT && LEFT && L2)  	robotRun(1350,tocdo);
    else if(UP && !DOWN && RIGHT && !LEFT && L2)  robotRun(-1350,tocdo);
	
    //-------------- Dang chay va Khong chay nua, chi xoay ----------------
    if(UP && DOWN && RIGHT && LEFT && !rJoy_LR && lJoy_LR  && robotIsRun()) robotStop(0);   

    //-------------- Xoay ----------------
    if(rJoy_LR) robotRotateStop();
    else if((RJOY_LR < 5) && L2)
    {
        if(robotIsRun()) robotRotateFree(-0.5,0);
        else robotRotateFree(-tocdoXoay,0);
    }
    else if((RJOY_LR > 250) && L2)
    {
        if(robotIsRun()) robotRotateFree(0.5,0);
        else robotRotateFree(tocdoXoay,0);
    }

    else robotRotateStop();		
	}
//////-------------------------------------------------------------	
	void ADCValue_Control(void)
{
	static unsigned int lazeTruocCouter = 0, lazeTruoc_SUM = 0, lazeSauCouter = 0, lazeSau_SUM = 0,BienTroNangCouter = 0, BienTroNang_SUM = 0, BienTroVongCouter = 0, BienTroVong_SUM = 0;
	static unsigned int lazeTruocCouter_t = 0, lazeTruoc_SUM_t = 0;
//------------------------	
	if(lazeTruocCouter++ < 50)	
	{
		lazeTruoc_SUM += cam_bien_laze_truoc;  
	}
	else
  {
		lazeTruocValue = lazeTruoc_SUM/50;
		lazeTruocCouter = 0;
		lazeTruoc_SUM = 0;
	}
//------------------------	
	if(lazeTruocCouter_t++ < 50)	
	{
		lazeTruoc_SUM_t += cam_bien_laze_truoc_trai;  
	}
	else
  {
		lazeTruoctraiValue = lazeTruoc_SUM_t/50;
		lazeTruocCouter_t = 0;
		lazeTruoc_SUM_t = 0;
	}
//------------------------
	if(lazeSauCouter++ < 50)	lazeSau_SUM += cam_bien_laze_sau;  
	
	else
  {
		lazeSauValue = lazeSau_SUM/50;
		lazeSauCouter = 0;
		lazeSau_SUM = 0;
	}


}

//****************************************** NANG VONG **************************************************

void Reset_nang_vong(void)
{
	if(BienTroVongValue > Nang_vong_min)	Mor_nang_down, Mor_nang = 250,vTaskDelay(1);
	else Mor_nang = 0;
}

void nang_vong_xp(int vt)
{
	if(BienTroVongValue < vt)	Mor_nang_up, Mor_nang = 250;
	else											Mor_nang = 0;
}

void Nangvong(void)
{
	int vi_tri_hien_tai = BienTroVongValue;
	int dd_can_den, vi_tri_can_den;
	
	Reset_nang_vong();
	
	if(!TRIANGLE  && L2 && Bien_vong < 11) {	Bien_vong++, noise=0;
																		while(!TRIANGLE && L2)	vTaskDelay(1);	
																	}
	else if(!X && L2  && Bien_vong > 0)		{ Bien_vong--, noise=0;
																		while(!X && L2)	vTaskDelay(1);}
	if(Bien_vong == 0)				vi_tri_can_den = 38;
	else if(Bien_vong == 1)		vi_tri_can_den = 85;	//max 258
	else if(Bien_vong == 2)		vi_tri_can_den = Nang_vong_min;																		
	else if(Bien_vong < 5) 										 	vi_tri_can_den = Nang_vong_min + (Bien_vong-2)* Khoang_cach_1_vong;		
	else if(Bien_vong < 8) 										 	vi_tri_can_den = Nang_vong_min + (Bien_vong-2)* Khoang_cach_1_vong + 5;
	else																				vi_tri_can_den = Nang_vong_min + (Bien_vong-2)* Khoang_cach_1_vong + 10;				
																		
	dd_can_den = vi_tri_hien_tai - vi_tri_can_den;

																		
	if(noise <80)
	{
		if(dd_can_den < 0)					{	if(abs(dd_can_den)+200 > 250)	Mor_nang = 250,Mor_nang_up;
																	else													Mor_nang = abs(dd_can_den)+200,Mor_nang_up;}
		else	if(dd_can_den > 0)		{	if(abs(dd_can_den)+200 > 250)	Mor_nang = 250,Mor_nang_down;
																	else													Mor_nang = abs(dd_can_den)+200,Mor_nang_down;}
		else												Mor_nang = 0, noise++;
																
	}
	else	Mor_nang = 0;																	
}

//****************************************** NANG GOC****************************************************
 void Nang_tay_ban(void)
{
	int vi_tri_hien_tai_tb = BienTroNangValue;
	int vi_tri_can_den_tb, dd_can_den_tb;
	
	if(	NUT_CHUYEN_SAN == 0)		g0 = 512, g1 = 561, g2 = 593, g3 = 569 , g4 = 525,	XANH;
	else												g0 = 521, g1 = 561, g2 = 600, g3 = 575 , g4 = 530, DO;
	
	if(!SQUARE  && L2 && Bien_nang < 6  && R2) {	Bien_nang++, noise1=0;
																		while(!SQUARE && L2)	vTaskDelay(1);	
																	}
	else if(!O && L2  && Bien_nang > 0    &&  R2)		{ Bien_nang--, noise1=0;
																		while(!O && L2)	vTaskDelay(1);}

	if(Bien_nang == 0)	vi_tri_can_den_tb = g0;											
	else	if(Bien_nang == 1)	vi_tri_can_den_tb = g1;		
	else	if(Bien_nang == 2)	vi_tri_can_den_tb = g2;	
	else	if(Bien_nang == 3)	vi_tri_can_den_tb = g3;	
	else	if(Bien_nang == 4)	vi_tri_can_den_tb = g4;																			
	//else	if(Bien_nang == 5)	vi_tri_can_den_tb = g5;		
	//else	if(Bien_nang == 6)	vi_tri_can_den_tb = g6;
	dd_can_den_tb = vi_tri_hien_tai_tb - vi_tri_can_den_tb;	
																		
	if(noise1 < 150)
	{
		if(dd_can_den_tb < -1)				{	if(abs(dd_can_den_tb)+100 > 250)	Xi_lanh_dien = 250,Xi_lanh_dien_up;
																	else																Xi_lanh_dien = abs(dd_can_den_tb)+100,Xi_lanh_dien_up;}
		else	if(dd_can_den_tb > 1)	{	if(abs(dd_can_den_tb)+100 > 250)	Xi_lanh_dien = 250,Xi_lanh_dien_down;
																	else																Xi_lanh_dien = abs(dd_can_den_tb)+100,Xi_lanh_dien_down;}
		else	Xi_lanh_dien = 0, noise1++;
																	
		//osDelay(1);
	}
	else	testnangxilanhdien();															
}

//************************************=====*****************************************
//********************************* BO SUNG CODE 11/ 3**************************************
void test_cylinder(void)
{
	
	//*************************************** XI LANH NANG HA********************************************
	if(!L2 && !O) 
	{	bien_xl_nang_ha = ~bien_xl_nang_ha; 
		while(!L2 && !O  )  vTaskDelay(1);									
	}
	if(bien_xl_nang_ha == 0)	XI_LANH_NANG_HA_OFF;
	else											XI_LANH_NANG_HA_ON;
	
	//***************************************XI LANH KEO **********************************************
	
	if(!L2 && !SQUARE) 
	{	bien_xl_mac_vong = ~bien_xl_mac_vong; 
		while(!L2 && !SQUARE) vTaskDelay(1);	
	}
	if(bien_xl_mac_vong == 0)			XI_LANH_MAC_VONG_OFF;
	else													XI_LANH_MAC_VONG_ON;
//	
//	//***************************************XI LANH KEP VONG **********************************************
//	
	if(!L2 && !TRIANGLE) 
	{	bien_xl_kep_vong = ~bien_xl_kep_vong; 
		while(!L2 && !TRIANGLE) vTaskDelay(1);	
	}
	if(bien_xl_kep_vong == 0)			XI_LANH_KEP_VONG_OFF;							
	else													XI_LANH_KEP_VONG_ON;
//	
//	//***************************************XI LANH DAY VONG **********************************************
//	
	if(!L2 && !X) 
	{	bien_xl_day = ~bien_xl_day; 
		while(!L2 && !X) vTaskDelay(1);	
	}
	if(bien_xl_day == 0)			XI_LANH_DAY_VONG_OFF;									
	else											XI_LANH_DAY_VONG_ON;
	
//	//***************************************XI LANH CHOT **********************************************
	
	if(!LJOY) 
	{	bien_xl_chot = ~bien_xl_chot; 
		while(!LJOY)	vTaskDelay(1);													
	}
	if(bien_xl_chot == 0)														XI_LANH_CHOT_OFF;
	else 																						XI_LANH_CHOT_ON;
	//	//***************************************XI LANH TRU GIUA **********************************************
//	
	if(!L2 && !UP) 
	{	bien_xl_tru_giua = ~bien_xl_tru_giua; 
		while(!L2 && !UP) vTaskDelay(1);	
	}
	if(bien_xl_tru_giua == 0)			XI_LANH_TRU_GIUA_OFF;									
	else											XI_LANH_TRU_GIUA_ON;
	
	//	//***************************************XI LANH KEO LOXO **********************************************
//	
	if(!L2 && !DOWN) 
	{	bien_xl_keo_loxo = ~bien_xl_keo_loxo; 
		while(!L2 && !DOWN) vTaskDelay(1);	
	}
	if(bien_xl_keo_loxo == 0)			XI_LANH_KEO_LOXO_OFF;									
	else													XI_LANH_KEO_LOXO_ON;

	//Dk_cylinder_keo();
	//capvong();
}
//******************************************* XI LANH THU VAO********************************************
void Thuloxove()
{
   if (!L1    &&    !UP   )
	 {	
			Keo_loxo = 2;
	 }
}
//**************************** cap thanh lazer sau ************************************8
void cap_thanh_lazer_sau_phai (int khoang_cach, unsigned char speed) // 
{
	int sai_so;
	sai_so = lazeSauValue - khoang_cach;
	
	//robotRotate(-900,0.,0);
	//robotRun(-200 - _robotIMUAngle,speed);

	if(sai_so > 5)					robotRun(750,speed);				//lazer > khoang cach dat
	else if(sai_so < 5)			robotRun(800,speed);
	else										robotRun(850,speed);
}

void cap_thanh_lazer_sau_trai (int khoang_cach, unsigned char speed)
{
	int sai_so;
	
	sai_so = lazeSauValue - khoang_cach;
	
	if(sai_so > 5)					robotRun(-700,speed);
	else if(sai_so < 5)			robotRun(-800,speed);
	else										robotRun(-850,speed);
}

void chuyen_tru_sang_phai(int distance, int32_t en, unsigned char speed)  //khoang cach laze, khoang cach encoder, toc do
{
	RESET_ENCODER();
											
	Cbcc = 1;			
	
	for(i=0;i<10;i++)	while(ENCODER_TONG() < en)						{		cap_thanh_lazer_sau_phai(120, speed);
																															if(wantExit() == 1) break;	
																															vTaskDelay(1);}
	
	for(i=0;i<10;i++)	while((lazeTruocValue > distance))		{		cap_thanh_lazer_sau_phai(120, 12);
																																															if(wantExit() == 1) break;	
																																															vTaskDelay(1);}					

RESET_ENCODER();
																																															
	for(i=0;i<10;i++)	while(ENCODER_TONG() < 25)						{		cap_thanh_lazer_sau_phai(120, 12);
																															if(wantExit() == 1) break;	
																															vTaskDelay(1);}																																															
	robotStop(0);
	Vi_tri++;																																	
	robotLock();																															//while(1);
}

void chuyen_tru_sang_trai(int distance, int32_t en, unsigned char speed)
{
	RESET_ENCODER();
	Cbcc = 1;																												
		
	
	for(i=0;i<10;i++)	while(ENCODER_TONG() < en)						{		cap_thanh_lazer_sau_trai(120, speed);
																															if(wantExit() == 1) break;	
																															vTaskDelay(1);}
	
	for(i=0;i<10;i++)	while((lazeTruocValue > distance))		{	cap_thanh_lazer_sau_trai(120, 12);
																																														if(wantExit() == 1) break;	
																																														vTaskDelay(1);}
	RESET_ENCODER();
																																															
	for(i=0;i<10;i++)	while(ENCODER_TONG() < 25)						{		cap_thanh_lazer_sau_trai(120, 12);
																															if(wantExit() == 1) break;	
																															vTaskDelay(1);}
	robotStop(0);						
	Vi_tri++;																																	
	robotLock();																															//while(1);
																	
}
//************************************ TEST XI LANH DIEN KEO*********************************************************

void Dk_cylinder_keo(void)
{
	if 			(!R2	&& !TRIANGLE && CBT_HA_TAY_BAN == 1)    	Mor_keo = 250, Mor_keo_up, Keo_loxo = 0;    //  
	else if (!R2 && !X)  															Keo_loxo = 1;
	else if	(Keo_loxo == 1)														Mor_keo   = 250,Mor_keo_down;
	else if	(Keo_loxo == 2 && CBT_HA_TAY_BAN == 1)		Mor_keo = 250, Mor_keo_up;
	else 																							Mor_keo = 0; 
}

//------------------------------------DIEU KHIEN GOC BAN--------------------------------------
void dcNangGoc(int T)       
{	
	static char p = 0;
	
	if(T > 0) 	{ Xi_lanh_dien_up; 	if(BienTroNangValue > Nang_goc_max){ Xi_lanh_dien=0; return;}}
	else 		{ Xi_lanh_dien_up; if(BienTroNangValue < Nang_goc_min){ Xi_lanh_dien=0; return;}}
	
	if(Xi_lanh_dien < abs(T))	{ if(p++ % 10 == 0) Xi_lanh_dien++;}
	else Xi_lanh_dien = abs(T);
}

//void GocTayBan(){
//	int g0 = 567, g1 = 590, g2 = 608, g3 = 630, goc_nang, T;
//	if(!SQUARE  && L2 && Bien_nang < 3) {	Bien_nang++, noise1=0;
//																				while(!SQUARE && L2)	vTaskDelay(1);}				
//	else if(!O && L2  && Bien_nang > 0)	{ Bien_nang--, noise1=0;
//																				while(!O && L2)	vTaskDelay(1);}

//	if(Bien_nang == 0)			goc_nang = g0;	
//	else if(Bien_nang == 0)	goc_nang = g1;
//	else if(Bien_nang == 0)	goc_nang = g2;
//	else if(Bien_nang == 0)	goc_nang = g3;
//																				
//	T = abs(goc_nang - BienTroNangValue);
//	
//	if( T < 2) { dcNangGoc(0);}
//	else if(goc_nang > BienTroNangValue) { dcNangGoc(-(3 + (T < 120? T : 250))); }
//	else { dcNangGoc((3 + (T < 120? T : 250)));}
//}

//------------------------------------DIEU KHIEN GOC BAN--------------------------------------
void NangVongCamBien(void)
{	
	if((!X || Resetnangvong == 1) && R1 && R2 && L2 && (BienTroVongValue > Nang_vong_min))																																		Mor_nang = 250,Mor_nang_down,Bien_vong = 0, Cap_vong = 0;
	else 	if(!TRIANGLE == 1 && R1 && R2 && L2 && (NUT_NHAN_TRAI == 1 || NUT_NHAN_PHAI == 1) && (BienTroVongValue < Nang_vong_max) && Resetnangvong == 0)			Mor_nang = 250,Mor_nang_up, Cap_vong = 0;
	else 	if(Cap_vong == 1 && (NUT_NHAN_TRAI == 1 || NUT_NHAN_PHAI == 1) && (BienTroVongValue < Nang_vong_max))																							Mor_nang = 250,Mor_nang_up;
	else																																																																											Mor_nang = 0, Cap_vong = 0;
	
	if(BienTroVongValue >= Nang_vong_max && CTHT_XILANH_CO == 0)	Resetnangvong =1;
	else if(BienTroVongValue <= Nang_vong_min)										Resetnangvong =0;
}
// *********************************** CAP VONG **********************************************
void capvong(void)
{
	if (!R1 && !L1)		bien_xl_day = ~bien_xl_day, bien_xl_mac_vong = ~bien_xl_mac_vong; 
	while(!R1 && !L1)	vTaskDelay(1);
}

//*********************************** BAN VONG************************************************
void Chuan_bi_co_cau(void)
{
	int ii, Bt_vong;
	if(Cbcc == 1)
	{	
		XI_LANH_KEP_VONG_OFF;
		XI_LANH_MAC_VONG_ON;
		
		Mor_keo_up;
		Mor_keo = 254;
		XI_LANH_KEO_LOXO_ON;
		
		Cap_vong = 1;
		
		for(ii=0;ii<100;ii++)	while(CBT_HA_TAY_BAN == 1 || ((NUT_NHAN_TRAI == 1 || NUT_NHAN_PHAI == 1) && (BienTroVongValue < Nang_vong_max)))	{		
																																																							if(CBT_HA_TAY_BAN == 1)	XI_LANH_CHOT_ON;
																																																							if(CBT_HA_TAY_BAN == 0)	{vTaskDelay(500);
																																																																							//Mor_keo = 0;
																																																																							XI_LANH_CHOT_OFF;
																																																																							vTaskDelay(500);
																																																																							Mor_keo_down;
																																																																							Mor_keo = 254;
																																																																							XI_LANH_KEO_LOXO_OFF;}
																																																							
																																																							if(!UP)	break;
																																																							vTaskDelay(1);}
		vTaskDelay(500);
																													
		Mor_keo = 0;
		XI_LANH_CHOT_OFF;
		
		vTaskDelay(800);
		
//		XI_LANH_MAC_VONG_ON;
	
		Mor_keo_down;
		Mor_keo = 254;
		XI_LANH_KEO_LOXO_OFF;
		
		//Bt_vong = BienTroVongValue + Khoang_cach_1_vong;
		
		//while((BienTroVongValue < Nang_vong_max) && (BienTroVongValue < Bt_vong))	vTaskDelay(1);
		
		for(ii=0;ii<1000;ii++)	while((NUT_NHAN_TRAI == 1 || NUT_NHAN_PHAI == 1) && (BienTroVongValue < Nang_vong_max)) {		Mor_nang_up;
																																																Mor_nang = 250;
																																																if(!UP)	break;																																	
																																																vTaskDelay(1);}	
		Mor_nang_up, Mor_nang = 0;
		XI_LANH_DAY_VONG_ON;
																																																
//		for(ii=0;ii<4500;ii++)	{		if(!UP)	break;
//															vTaskDelay(1);}
																																																
		for(ii=0;ii<100;ii++)	while(CTHT_XILANH_CO == 1)	{		if(!UP)	break;
																									vTaskDelay(1);}
		XI_LANH_DAY_VONG_OFF;
		XI_LANH_MAC_VONG_OFF;	
		
		Cbcc = 0;
		noise1 = 0;
	}
	
	else if(Cbcc == 2)
	{	
		XI_LANH_CHOT_ON;
		
		for(ii=0;ii<500;ii++)	while(CBT_HA_TAY_BAN == 1)	Mor_keo_up, Mor_keo = 254,XI_LANH_KEO_LOXO_ON, vTaskDelay(1);
		
		for(ii=0;ii<150;ii++)	vTaskDelay(1);
		
		Mor_keo = 0;
		XI_LANH_CHOT_OFF;
	
		XI_LANH_KEO_LOXO_OFF;
		Mor_keo_down, Mor_keo = 254;
		
		Cbcc = 0;
		noise1 = 0;
	}
	
	else if(Cbcc == 3)
	{	
		XI_LANH_MAC_VONG_ON;
		XI_LANH_DAY_VONG_ON;
		
		XI_LANH_KEO_LOXO_OFF;
		Mor_keo_down, Mor_keo = 254;
		
//			for(ii=0;ii<3000;ii++)	{		if(!UP)	break;
//															vTaskDelay(1);}
//		
		for(ii=0;ii<2000;ii++)	while(CTHT_XILANH_CO == 1)	{		if(!UP)	break;
																									vTaskDelay(1);};
		
		XI_LANH_MAC_VONG_OFF;
		XI_LANH_DAY_VONG_OFF;
		Cbcc = 0;
		noise1 = 0;
	}
}

void len_co_cau_ban(void)
{	if(Cbnn = 1){
		XI_LANH_CHOT_ON;
		Mor_keo_up, Mor_keo = 254;
		while(CBT_HA_TAY_BAN == 1)	vTaskDelay(1);
		Mor_keo = 0;
		XI_LANH_CHOT_OFF;
		for(i=0;i<500;i++)	vTaskDelay(1);
		Mor_keo_down;
		Mor_keo = 254;
//		XI_LANH_MAC_VONG_ON;
		Cbnn = 0;
	}
}

void nap_vong(void)
{
	int ii;
	if(Cbnv = 1){
		Cbcc = 0;
		Mor_nang_up, Mor_nang = 250;
		while(CBT_HA_TAY_BAN == 0 && (NUT_NHAN_TRAI == 1 || NUT_NHAN_PHAI == 1) && (BienTroVongValue < Nang_vong_max)) vTaskDelay(1);	

		Mor_nang_up, Mor_nang = 0;
		XI_LANH_DAY_VONG_ON;
		
		for(ii=0;ii<5000;ii++)	vTaskDelay(1);
		
		XI_LANH_DAY_VONG_OFF;
//		XI_LANH_MAC_VONG_OFF;	
		
		Cbnv = 0;
	}
}

void Nap_vong(void)
{
	int ii;
//	XI_LANH_MAC_VONG_ON;
	XI_LANH_DAY_VONG_ON;
	
	for(ii=0;ii<5000;ii++)	vTaskDelay(1);
		
	XI_LANH_DAY_VONG_OFF;
//	XI_LANH_MAC_VONG_OFF;	
}
//------------------------------------DIEU KHIEN CO CAU--------------------------------------
void dieuKhienCoCau(void)
{
	Chuan_bi_co_cau();
//	testnangxilanhdien();
}