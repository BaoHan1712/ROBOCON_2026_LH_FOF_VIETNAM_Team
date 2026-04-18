//=========================================================================
void Hong_setupDuLieu(){
	soTruBanTuDong_T = 3;
	soTruBanTuDong_P = 4;
	
	//----------- thiet lap goc bu tru khi den san moi ------------------------

	setupDB_Tru_T(1, 285 	, 92  , 0	);		// 0.5m Phai
	setupDB_Tru_T(2, 195	, 87  , 1	);		// 1.0m Phai
	setupDB_Tru_T(3, 135 	, 50  , 1	);		// Gan
	setupDB_Tru_T(4, 80 	, 86  , 1	);		// Cao
	setupDB_Tru_T(5, 25   , 112 , 0	);		// Xa

	setupDB_Tru_P(1, 260 	, 92 	, 0	);		// 0.5m Trai
	setupDB_Tru_P(2, 170 	, 87  , 1	);		// 1.0m Trai
	setupDB_Tru_P(3, 130	, 50 	, 1	);		// Gan
	setupDB_Tru_P(4, 50   , 87  , 1	);		// Cao
	setupDB_Tru_P(5, 10   , 112 , 0	);		// Xa	

//========================================================================
	setupDB_Tru_T(0, 90, 0 , 0);// trang thai ban dau
	ThuTuBanTruT[0] = 0; 		SoLanBanTruT[0] = 0;

	setupDB_Tru_P(0, 90, 0 , 0);// trang thai ban dau
	ThuTuBanTruP[0] = 0; 		SoLanBanTruP[0] = 0;
	//------------------------------------------------------------------------
	
	ThuTuBanTruT[1] = 1; 		SoLanBanTruT[1] = 3;
	ThuTuBanTruT[2] = 2; 		SoLanBanTruT[2] = 3;
	ThuTuBanTruT[3] = 5; 		SoLanBanTruT[3] = 3;
	
//	ThuTuBanTruT[4] = 3; 		SoLanBanTruT[4] = 3;
//	ThuTuBanTruT[5] = 4; 		SoLanBanTruT[5] = 3;

	ThuTuBanTruP[1] = 4; 		SoLanBanTruP[1] = 3;
	ThuTuBanTruP[2] = 2; 		SoLanBanTruP[2] = 3;
	ThuTuBanTruP[3] = 1; 		SoLanBanTruP[3] = 3;
	ThuTuBanTruP[4] = 3; 		SoLanBanTruP[4] = 3;
//	ThuTuBanTruP[5] = 5; 		SoLanBanTruP[5] = 5;

}
//=========================================================================
int Hong_XuatPhat(){
		int KhoangCach = 5000;  							//cong them emcoder duong chay + 1600
		
		if(!CTHT_THUNG_DIA) return 1;
	
		ResetEncoder();

		robotRunAngle(-30,150, 0);
		while(Encoder() < KhoangCach)
		{
			if(!X)  return 0;
		}

		ResetEncoder();

		robotRunAngle(-60, 100, 0);
		while(Encoder() < 2000)
		{
			if(!X)  return 0;
		}	

		robotRunAngle(-80, 70, 0);
		while(Encoder() < 2700)
		{
			if(!X)  return 0;
		}	

		robotResetIMU();
		xilanh_Ban_Trai_off;
		xilanh_Ban_Phai_off;			

		robotRunAngle(-80, 17, 0);
		while(CTHT_THUNG_DIA)
		{
			lcdViewer(1);
			if(!X)  return 0;
		}	
		
		robotStop(5);
		while(!robotIsStop());
		
		robotStop(0);
		return 1;
}
//----------------------------------------------------
int Hong_DenViTriBan(){
	int gocDung = -920;
	KhoaNap = 1;
	
	lucBan_Trai = DBT[1][1];
	lucBan_Phai = DBT[1][1];
	
	xilanh_Ban_Trai_off;
	xilanh_Ban_Phai_off;			

	napDia_Trai(250);
	napDia_Phai(250);

	ResetEncoder();
	robotRunAngle(1500, 60, -200);	
	while(Encoder() < 300)
	{
		lcdViewer(1);
		if(!X)  return 0;
	}

	ResetEncoder();
	robotRunAngle(1690, 90, gocDung);
	while(Encoder() < 3000)
	{
		lcdViewer(1);
		if(!X)  return 0;
	}

	robotRunAngle(1700, 30, gocDung);
	while(Encoder() < 5000)			
	{
		lcdViewer(1);
		if(!X)  return 0;
	}

	setup_Tru_Trai(ThuTuBanTruT[1]);
	setup_Tru_Phai(ThuTuBanTruP[1]);
	
	robotRunAngle(1700, 10, gocDung);
	while(Encoder() < 5280)
	{
		lcdViewer(1);
		if(!X)  return 0;
	}

	robotStop(0);

	KhoaNap = 0;
	xilanh_Ban_Trai_off;
	xilanh_Ban_Phai_off;			
	return 1;
	
}

//=========================================================================
int Hong_RetryVO(){
		int gocDung = 920;

		robotResetIMU();
		ResetEncoder();

		robotRunAngle(830, 70, gocDung);
		while(Encoder() < 4000)				// xuat phat den gan khu vuc lay dia// 900000
		{
			lcdViewer(1);
			if(!X)  return 0;
		}	

		robotRunAngle(850, 20, gocDung);
		while(Encoder() < 5200)				// xuat phat den gan khu vuc lay dia// 900000
		{
			lcdViewer(1);
			if(!X)  return 0;
		}	

		robotStop(5);
		while(!robotIsStop());
		
		robotStop(0);
		return 1;
}
//----------------------------------------------------
//----------------------------------------------------
void autoRobotControler_Hong(){
	
		Hong_setupDuLieu();
		//-----------------------

		if(!Hong_XuatPhat()){ robotStop(0); while(1) lcdViewer(2); }

		if(!Hong_DenViTriBan()){ robotStop(0); while(1) lcdViewer(2);}

		DieuKhienTuDong(1); // (tu dong ban)
		
		while(1){
			napDia_Trai(-200);
			napDia_Phai(-200);
			lucBan_Trai=0;
			lucBan_Phai=0;
			BangTai_Trai=0;
			BangTai_Phai=0;
			
			if(!Hong_RetryVO()) { robotStop(0); while(1) lcdViewer(2);}
			
			while(START){
				lcdViewer(1);
			}

			robotResetIMU();
			
			// chay ra lan Retry thi chinh encoder o day
			if(!Hong_DenViTriBan()){ robotStop(0); while(1) lcdViewer(2);}

			DieuKhienTuDong(0); // (tu dong ban)
		}
}
//----------------------------------------------------
