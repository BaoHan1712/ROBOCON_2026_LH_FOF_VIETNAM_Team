//*****************************8 bien toan cuc *************************************
char xl_truot_lua, xl_kep_lua_tren, xl_kep_lua_duoi, xl_nang_lua,gt_kep_bong;
int vi_tri = 0, Cbcc = 0, Cbnv = 0, Cbnn = 0,vt_xl_nang_lua = 0;
char	On_Off_Ban = 0;
char  Act = 0;
int xl_ban_bong = 0;
int Nang_vong_max = 322, Nang_vong_min = 105, i;
int Nang_goc_max = 540, Nang_goc_min = 300;
int touchpad_press =0;
int laybong =0;
int en_tru = 60;
int max_speed = 10;
int speed_tay_lua = 100;
int speed_xoay = 200;

int imuNow, imuNow = 0;
int xl_kepbong_state = 0;
int xl_nangkep_state = 0;
int ban_bong_state=0 ;

//extern vu8 update;
extern speed_temp;
extern vu8	Cam;
extern float	JTL;
extern int Vi_tri, Man_ra_vao,Man_nang_ha;
int state_nang = 1;
int state_ha = 1;

int	Min_nang = 260, Max_nang = 970, target_nang;
int	Min_taykfs = 135, Max_taykfs = 900, target_taykfs;
int	speed_nang,speed_tayday,speed_taykfs;
int force_F;
int final_force;
float result;

vu8 Day = 0, Kep = 0, Xoay = 0, hut_nha_kfs = 0;
void robotLineRunLeft(vu8 speed);
void robotLineRunRight(vu8 speed);
//=========================================BAN BONG==============================

//void Ban_bong(void){
////ban bong
//if (!L1&&TOUCHPAD) {
//            Ban_1 = Ban_2 = Ban_3 = force_F;
//						Ban_1_next, Ban_2_next, Ban_3_next;
//						vTaskDelay(15000); // Wait for 1.5 seconds
//						Cylinder_L = 250; // Activate the cylinder
//            vTaskDelay(20000);
//            Ban_1=  Ban_2 = Ban_3 = 0;
//            Cylinder_L = 0;
////						XI_LANH_HA_NONG;
//}	


			
				
//	if(RJOY){
//		Ban_1 =  Ban_2 =  Ban_3 = 40;
//		Ban_1_back, Ban_2_back, Ban_3_back;
//		vTaskDelay(20000);
//		Ban_1 = 0, Ban_2 = 0, Ban_3 = 0;			

//		
//	}
////}
//void test(void)
//{
//if(LJOY)    Cylinder_L = 250;
//else Cylinder_L = 0;
//}



#include <math.h>

#define OFFSET_TOLERANCE 1   
#define CENTER 100
#define MAX_SPEED 1
#define MIN_SPEED 0.2
#define K_FAR 0.005

#define OFFSET_ARRAY_SIZE 20 

int offsetArray[OFFSET_ARRAY_SIZE] = {0};  // M?ng luu giá tr? offset
int offsetIndex = 0;  // Ch? m?c d? c?p nh?t m?ng

// Hàm luu offset vào m?ng theo vòng tròn
void saveOffset(int new_offset) {
    offsetArray[offsetIndex] = new_offset;
    offsetIndex = (offsetIndex + 1) % OFFSET_ARRAY_SIZE;  // C?p nh?t ch? m?c vòng l?p
}

// Hàm l?y giá tr? offset m?i nh?t t? m?ng
int getLatestOffset() {
    int latestIndex = (offsetIndex - 1 + OFFSET_ARRAY_SIZE) % OFFSET_ARRAY_SIZE;  
    return offsetArray[latestIndex];
}

// Hàm tính t?c d? xoay d?a vào kho?ng cách v?i CENTER
float calculateSpeed(int received_offset) {
    float distanceFromCenter = abs(received_offset - CENTER);
    
    // S? d?ng hàm tanh d? tang t?c khi xa, gi?m t?c khi g?n
    float speed = MIN_SPEED + (MAX_SPEED - MIN_SPEED) * tanh(0.05 * distanceFromCenter);

    return speed;
}
//void xoaytam(int received_offset) {  
//    int latest_offset;
//    float received_speed;

//    saveOffset(received_offset);


//    if (R2 &&!UP && !DOWN && !RIGHT && LEFT && !R1 {
//        latest_offset = getLatestOffset();  

//        // D?ng n?u offset dã v? g?n CENTER (98 - 100)
//        if (latest_offset >= 98 && latest_offset <= 102) {
//            robotRotateStop(0);
//        }

//        // Tính t?c d? xoay m?i nh?t
//        received_speed = calculateSpeed(latest_offset);

//        // Xoay v? CENTER
//        if (latest_offset < CENTER - OFFSET_TOLERANCE) {
//            robotRotateFree(-received_speed, 0);  // Xoay ph?i  
//        } else if (latest_offset > CENTER + OFFSET_TOLERANCE) {
//            robotRotateFree(received_speed, 0); // Xoay trái
//        }
//    }
//}




#define MOCCHUAN 4090  
#define LUC_MOC 106
#define GOC_MOC 600

#define LUC_MAX1 250
#define LUC_MIN1 50

#define GOC_MAX1 600    
#define GOC_MIN1 550    

#define LUC_BETA 1.1  // H? s? phi tuy?n cho luc ban
#define GOC_ALPHA 0.7

int calculated_force;
int calculated_distance;
float result_Cam;

void tinhlucban_depthcam(float received_distance) {
    float gocBanCam = 0;
    float lucBanCam = 0;
    // Tính l?c b?n v?i công th?c phi tuy?n
    lucBanCam = LUC_MOC * pow((received_distance / MOCCHUAN), LUC_BETA);

    // Gi?i h?n l?c b?n trong kho?ng cho phép
    if (lucBanCam > LUC_MAX1) {
        lucBanCam = LUC_MAX1;
    } else if (lucBanCam < LUC_MIN1) {
        lucBanCam = LUC_MIN1;
    }
    // Tính góc b?n v?i h? s? hi?u ch?nh và kho?ng d?ng
    lucBanCam = GOC_MOC + ((received_distance - MOCCHUAN) / MOCCHUAN) * (GOC_MAX1 - GOC_MIN1) * GOC_ALPHA;

    // Gi?i h?n góc b?n trong kho?ng cho phép
    if (lucBanCam > GOC_MAX1) {
        lucBanCam = GOC_MAX1;
    } else if (lucBanCam < GOC_MIN1) {
        lucBanCam = GOC_MIN1;
    }
    calculated_force = lucBanCam;
    calculated_distance = lucBanCam;
}



#define MOCCU 2500       
#define LUC_TAI_MOC 90


#define LUC_MAX 250
#define LUC_MIN 50

 void lucbanlazer(float received_distance) {
    float gocBan = 0;
    float lucBan = 0;
	  float corrected_distance = sqrt((received_distance * received_distance));
    lucBan = LUC_TAI_MOC * (corrected_distance / MOCCU);

    if (lucBan > LUC_MAX) {
        lucBan = LUC_MAX;
    } else if (lucBan < LUC_MIN) {
        lucBan = LUC_MIN;
    }
		
    force_F = lucBan;
		final_force = force_F;
		final_force = force_F * (result)/10 ;
		
	}

//**********************************************************************
//void banxoay(void)
//{	int tocdo;
//	if(L2) tocdo = 20;
//	else	tocdo = 7;
//	
//	 if (SQUARE)													  Mor_CamRotate = tocdo, Mor_CamRotate_next;
//	 else if (O) 	                          Mor_CamRotate = tocdo, Mor_CamRotate_back;
//	 else	                                        Mor_CamRotate = 2;
//}


//void nangcam(void)
// {

//	if (!R1&&TRIANGLE)													state_nang = 1, state_ha = 0, target_Nang_Ha = 165;
//	if (!R1&&X)
//	{ 					 
//				target_Nang_Ha = 610 ;
//	 }
//	 else if(state_ha == 0&& target_Nang_Ha == 610 && BienTroNongBanValue > 595) 
//			{
//				state_nang = 0;
//				state_ha = 1;
//			 }	 
// }

//void Nang_Ha_Nong_Ban(void)
//{
//	if (R1 && X && (taget_BT_Xoay < Max_BT_Xoay))
//		taget_BT_Xoay++, vTaskDelay(300);
//	else if (R1 && TRIANGLE && (taget_BT_Xoay > Min_BT_Xoay))
//		taget_BT_Xoay--, vTaskDelay(400);
//}


//====================================================================================


// char CB_line_trai, CB_line_phai, Nho_trai_truoc, Nho_trai_sau, Nho_phai_truoc, Nho_phai_truoc;
//void robotGamePadControl(vu8 speedMin, vu8 speedMax)
//{
//	int tocdo = 20, td_x = 5;
//	float tocdoXoay = 0;
//	int rJoy_LR = (RJOY_LR >= 5 && RJOY_LR <= 250) ? 1 : 0;
//	int lJoy_LR = (LJOY_LR >= 5 && LJOY_LR <= 250) ? 1 : 0;

//	if (UP && DOWN && RIGHT && LEFT && rJoy_LR)
//	{				  // Khong dieu khien
//		robotStop(0); // truot banh

//		return;
//	}
//	/*_____________________________//___________________________*/

//	/********************** TOC DO ****************************/
//	/*_____________________________//___________________________*/
//	if (!L1)
//		tocdo = speedMax, tocdoXoay = 0.5;
//	else
//		tocdo = speedMin, tocdoXoay = 0.3;

//	//--------- chay cac huong -----------
//	if (!UP && DOWN && RIGHT && LEFT && L2)
//		robotRun(0, tocdo);
//	else if (UP && !DOWN && RIGHT && LEFT && L2)
//		robotRun(1800, tocdo);
//	else if (UP && DOWN && !RIGHT && LEFT && L2)
//		robotRun(900, tocdo);
//	else if (UP && DOWN && RIGHT && !LEFT && L2)
//		robotRun(-900, tocdo);

//	else if (!UP && DOWN && !RIGHT && LEFT && L2)
//		robotRun(450, tocdo);
//	else if (!UP && DOWN && RIGHT && !LEFT && L2)
//		robotRun(-450, tocdo);
//	else if (UP && !DOWN && !RIGHT && LEFT && L2)
//		robotRun(1350, tocdo);
//	else if (UP && !DOWN && RIGHT && !LEFT && L2)
//		robotRun(-1350, tocdo);

//	//-------------- Dang chay va Khong chay nua, chi xoay ----------------
//	if (UP && DOWN && RIGHT && LEFT && !rJoy_LR && lJoy_LR && robotIsRun())
//		robotStop(0);

//	//-------------- Xoay ----------------
//	if (rJoy_LR)
//		robotRotateStop();
//	else if (RJOY_LR < 5) 
//	{
//		if (robotIsRun())
//			robotRotateFree(tocdoXoay, 0);
//		else
//			robotRotateFree(tocdoXoay, 0);
//	}
//	else if (RJOY_LR > 250)
//	{
//		if (robotIsRun())
//			robotRotateFree(-tocdoXoay, 0);
//		else
//			robotRotateFree(-tocdoXoay, 0);
//		//			robotLineRunLeft(20);//
//	}

//	else
//		robotRotateStop();
//}

//////-------------------------------------------------------------
void ADCValue_Control(void)
{
	// khai bao lazer
	static unsigned int lazeSauCouter = 0, lazeSau_SUM = 0;
	static unsigned int lazeTruocCouter = 0, lazeTruoc_SUM = 0;
	static unsigned int lazePhaiCouter = 0, lazePhai_SUM = 0;
	static unsigned int lazeTraiCouter = 0, lazeTrai_SUM = 0;

	// Bien tro vi tri co cau
	static unsigned int bientromamxoayCouter = 0, bientromamxoay_SUM = 0;
	static unsigned int bientronangluaCouter = 0, bientronanglua_SUM = 0;
	static unsigned int bientrotaykfsCouter = 0, bientrotaykfs_SUM = 0;
	static unsigned int bientronangCouter = 0, bientronang_SUM = 0;
	static unsigned int bientrotaydayCouter = 0, bientrotayday_SUM = 0;
	////----------------TINH TOAN LAZER---------------
	if (lazeSauCouter++ < 20)
	{
		lazeSau_SUM += cam_bien_laze_sau;
	}
	else
	{
		lazeSauValue = lazeSau_SUM / 20;
		lazeSauCouter = 0;
		lazeSau_SUM = 0;
	}
	//-------------------------------------------
	if (lazeTruocCouter++ < 20)
	{
		lazeTruoc_SUM += cam_bien_laze_truoc;
	}
	else
	{
		lazeTruocValue = lazeTruoc_SUM / 20;
		lazeTruocCouter = 0;
		lazeTruoc_SUM = 0;
	}
	//------------------------------
	if (lazePhaiCouter++ < 50)
	{
		lazePhai_SUM += cam_bien_laze_phai;
	}
	else
	{
		lazePhaiValue = lazePhai_SUM / 40;
		lazePhaiCouter = 0;
		lazePhai_SUM = 0;
	}
	//-----------------------------------------
	if (lazeTraiCouter++ < 50)
	{
		lazeTrai_SUM += cam_bien_laze_trai;
	}
	else
	{
		lazeTraiValue = lazeTrai_SUM / 40;
		lazeTraiCouter = 0;
		lazeTrai_SUM = 0;
	}
	//-----------------TINH TOAN BIEN TRO---------------

if (bientromamxoayCouter++ < 10)
	{
		bientromamxoay_SUM += bien_tro_nong_ban;
	}
	else
	{
		BienTroNongBanValue = bientromamxoay_SUM / 10;
		bientromamxoayCouter = 0;
		bientromamxoay_SUM = 0;
	}
	//-----------------------------------
	if (bientronangCouter++ < 50)
	{
		bientronang_SUM += bien_tro_nang;
	}
	else
	{
		BienTroNangValue = bientronang_SUM / 50;
		bientronangCouter = 0;
		bientronang_SUM = 0;
	}
	//-----------------------------------
	if (bientrotaykfsCouter++ < 50)
	{
		bientrotaykfs_SUM += bien_tro_tay_kfs;
	}
	else
	{
		BienTroTaykfsValue = bientrotaykfs_SUM / 50;
		bientrotaykfsCouter = 0;
		bientrotaykfs_SUM = 0;
	}

}
	

 
 

//	if (taget_BT_Nong_Ban < Min_BT_Nong_Ban)
//		taget_BT_Nong_Ban = Min_BT_Nong_Ban;
//	if (taget_BT_Nong_Ban > Max_BT_Nong_Ban)
//		taget_BT_Nong_Ban = Max_BT_Nong_Ban;

//	if (abs(BienTroNongBanValue - taget_BT_Nong_Ban) > 1)
//	{
//		if (BienTroNongBanValue > taget_BT_Nong_Ban)
//			Cylinder_back;
//		else
//			Cylinder_next;

//		speed_temp = abs(BienTroNongBanValue - taget_BT_Nong_Ban)*10;
//		if (speed_temp > 250) // 50
//			speed_temp = 250;
//		if (speed_temp < 50) 
//			speed_temp = 50;

//		Cylinder = speed_temp;
//	}
//	else
//		Cylinder = 0;
//}

//void Xoay_Nong_Ban()
//{
//	if (target_BT_Xoay < Min_BT_Xoay )
//		target_BT_Xoay = Min_BT_Xoay;
//	if (target_BT_Xoay > Max_BT_Xoay)
//		target_BT_Xoay = Max_BT_Xoay;

//	if (abs(BienTroXoayValue - target_BT_Xoay) > 2)
//	{
//		if (BienTroXoayValue > target_BT_Xoay)
//			Mor_CamRotate_back;
//		else
//			Mor_CamRotate_next;

//		speed_temp = abs(BienTroXoayValue - target_BT_Xoay);
//		if (speed_temp > 70) // 50
//			speed_temp = 70;
//		if (speed_temp < 8) 							
//			speed_temp = 8;
//		Mor_CamRotate = speed_temp;
//	}
//	else
//		Mor_CamRotate = 0;
//}

//void Nang_Ha_Nong_Ban_abs(void)
//{
//	if (R1 && X && (taget_BT_Nong_Ban < Max_BT_Nong_Ban))
//		taget_BT_Nong_Ban++, vTaskDelay(300);
//	else if (R1 && TRIANGLE && (taget_BT_Nong_Ban > Min_BT_Nong_Ban))
//		taget_BT_Nong_Ban--, vTaskDelay(300);
//}

////***************************** xoay nong ban bang tay **************************************
////void Xoay_nong_ban(vu8 speed)
////{
////	if(R1 && SQUARE)					Mor_CamRotate = speed, Mor_CamRotate_next;
////	else	if(R1 && O)					Mor_CamRotate = speed, Mor_CamRotate_back;
////	else											Mor_CamRotate = 2;
////}
//void Xoay_nong (void)
//{
//	if (R1 && O && (target_BT_Xoay < Max_BT_Xoay))
//		target_BT_Xoay++, vTaskDelay(500);
//	else if (R1 && SQUARE && (target_BT_Xoay > Min_BT_Xoay))
//		target_BT_Xoay--, vTaskDelay(500);
//}

void Nang()
{
	if (target_nang < Min_nang)
		target_nang = Min_nang;
	if (target_nang > Max_nang)
		target_nang = Max_nang;

	if (abs(BienTroNangValue - target_nang) > 2)
	{
		if (BienTroNangValue > target_nang)	nang_xuong;
		else																nang_len;

		speed_temp = abs(BienTroNangValue - target_nang)*4;

		if (speed_temp > speed_nang)
				speed_temp = speed_nang;
		if (speed_temp < 100)
				speed_temp = 100;
	
		nang = speed_temp;
	}
	else nang = 0;
}


void Taykfs()
{
	if (target_taykfs < Min_taykfs)
		target_taykfs = Min_taykfs;
	if (target_taykfs > Max_taykfs)
		target_taykfs = Max_taykfs;

	if (abs(BienTroTaykfsValue - target_taykfs) > 7)
	{
		if (BienTroTaykfsValue > target_taykfs)	Tay_kfs_vao;
		else																		Tay_kfs_ra;

		speed_temp = abs(BienTroTaykfsValue - target_taykfs)*4;

		if (speed_temp > speed_taykfs)
				speed_temp = speed_taykfs;
		if (speed_temp < 90)
				speed_temp = 90;
	
		Tay_kfs = speed_temp;
	}
	else Tay_kfs = 0;
}


void Nang_Ha(void)
{
	if (TRIANGLE && (target_nang < Max_nang)&& !L2 && !R1 && !L1)
		target_nang++, vTaskDelay(150);
	else if (X && (target_nang > Min_nang)&& !L2 && !R1 && !L1)
		target_nang--, vTaskDelay(150);
}

void Cylinder_Tay_Day(void)
{
	if(TRIANGLE && R1 && !L2 && !R2)	
	{
		Day = ~Day;
		while(TRIANGLE && R1)	
		{
			vTaskDelay(1);
			if(Day == 0)	XI_LANH_TAY_VAO;
			else					XI_LANH_TAY_RA;
		}
	}

}

void Cylinder_Tay_Kep(void)
{
	if(O && R1 && !L2 && !R2 )	
	{
		Kep = ~Kep;
		while(O && R1)	
		{
			vTaskDelay(1);
			if(Kep == 0)	XI_LANH_KEP_DONG;
			else					XI_LANH_KEP_MO;
		}
	}

}


void Cylinder_Xoay_Kep(void)
{
	if(X && R1 && !L2 && !R2)
	{
		Xoay = ~Xoay;
		while(X && R1)	
		{
			vTaskDelay(1);
			if(Xoay == 0)	XI_LANH_TAY_XUONG;
			else					XI_LANH_TAY_LEN;
		}
	}
	
}

void Hut_nha_KFS(void)
{
	if(SQUARE && !R1 && !L2 && R2)	
	{
		hut_nha_kfs = ~hut_nha_kfs;
		while(SQUARE && !L2 && !R1 && R2)	
		{
			Act = 0;
			vTaskDelay(1);
			if(hut_nha_kfs == 0)	Bom = 0;
			else									Bom = 250;
		}
	}

}

void Lay_khoi_gia(void)
{
	
	speed_nang = 250;
	target_nang = 350;
	XI_LANH_TAY_LEN;
	XI_LANH_KEP_MO;
	vTaskDelay(10000);
	XI_LANH_TAY_RA;
	vTaskDelay(8000);
	XI_LANH_KEP_DONG;
	vTaskDelay(8000);
	XI_LANH_TAY_VAO;
	
	
}

//******************************* nang ha bang tayu **************************
void Nang_Ha_Manual(void)
{
	if (TRIANGLE && !R1 && !R2 && !L2 && BienTroNangValue < Max_nang ) 				
	{
		if(L1 && BienTroNangValue < Max_nang - 20)	nang = 250;
		else		nang = 40;
		nang_len;
		target_nang = BienTroNangValue;
		Man_nang_ha = 1;
	}
	else	if (X && !R1 && !R2 && !L2 && BienTroNangValue > Min_nang) 	
				{
					if(L1 && BienTroNangValue > Min_nang + 20)	nang = 250;
					else		nang = 20;
					nang_xuong;
					target_nang = BienTroNangValue;
					Man_nang_ha = 1;
				}
	else Man_nang_ha = 0;
}

//**************************** ra vao bang tay ****************************
void Ra_vao_tay_lay_KFS(void)
{
	if (RJOY_UD < 30 && BienTroTaykfsValue < Max_taykfs - 10) 				
	{
		if(L1 && BienTroTaykfsValue < Max_taykfs - 40)	Tay_kfs = 250;
		else		Tay_kfs = 100;
		Tay_kfs_ra;
		target_taykfs = BienTroTaykfsValue;
		Man_ra_vao = 1;
	}
	else	if (RJOY_UD > 230 && BienTroTaykfsValue > Min_taykfs + 10) 	
				{
					if(L1 && BienTroTaykfsValue > Min_taykfs + 40)	Tay_kfs = 250;
					else		Tay_kfs = 100;
					Tay_kfs_vao;
					target_taykfs = BienTroTaykfsValue;
					Man_ra_vao = 1;
				}
	else Man_ra_vao = 0;
}
//********************************************* bam thanh laser phai ********************************************
void Bam_thanh_laser_phai(int speed, int runangle, int AngleHead, int lazer_stable_phai, int num_change_stable, int fix_max,int rat)
{
	int fix;

	fix = abs(lazePhaiValue - lazer_stable_phai) * rat;

	if (fix > fix_max)
	fix = fix_max;

	if (lazePhaiValue - lazer_stable_phai < num_change_stable)
	{
		robotRunAngle(runangle - fix, speed, AngleHead, 0.3);
	}
	else if (lazePhaiValue - lazer_stable_phai > num_change_stable)
	{
		robotRunAngle(runangle + fix, speed, AngleHead, 0.3);
	}
	else
		robotRunAngle(runangle, speed, AngleHead, 0.3);
}
//********************************************* bam thanh laser trai ********************************************
void Bam_thanh_laser_trai(int speed, int runangle, int AngleHead, int lazer_stable_trai, int num_change_stable, int fix_max,int rat)
{
	int fix;

	fix = abs(lazeTraiValue - lazer_stable_trai) * rat;

	if (fix > fix_max)
	fix = fix_max;

	if (lazeTraiValue - lazer_stable_trai < num_change_stable)
	{
		robotRunAngle(runangle + fix, speed, AngleHead, 0.1);
	}
	else if (lazeTraiValue - lazer_stable_trai > num_change_stable)
	{
		robotRunAngle(runangle - fix, speed, AngleHead, 0.1);
	}
	else
		robotRunAngle(runangle, speed, AngleHead, 0.1);
}

//********************************************* bam thanh laser trai ********************************************
void Bam_thanh_laser_trai_runangle(int speed, int runangle, int AngleHead, int lazer_stable_trai, int num_change_stable, int fix_max,int rat)
{
	int fix;

	fix = abs(lazeTraiValue - lazer_stable_trai) * rat;

	if (fix > fix_max)
	fix = fix_max;

	if (lazeTraiValue - lazer_stable_trai < num_change_stable)
	{
		robotRun(runangle + fix, speed);
	}
	else if (lazeTraiValue - lazer_stable_trai > num_change_stable)
	{
		robotRun(runangle - fix, speed);
	}
	else
		robotRun(runangle, speed);
}
//********************************************* bam thanh laser truoc ********************************************
void Bam_thanh_laser_truoc(int speed, int runangle, int AngleHead, int lazer_stable_truoc, int num_change_stable, int fix_max,int rat)
{
	int fix;

	fix = abs(lazeTruocValue - lazer_stable_truoc) * rat;

	if (fix > fix_max)
	fix = fix_max;

	if (lazeTruocValue - lazer_stable_truoc < num_change_stable)
	{
		robotRunAngle(runangle + fix, speed, AngleHead, 0.7);
	}
	else if (lazeTruocValue - lazer_stable_truoc > num_change_stable)
	{
		robotRunAngle(runangle - fix, speed, AngleHead, 0.7);
	}
	else
		robotRunAngle(runangle, speed, AngleHead, 0.77);
}
//***************************************** lay KFS tu dong ****************************************************

void Lay_KFS_Tu_Dong(void)
{
	if(!R1 && R2 && TRIANGLE && CB_NHAN_KFS == 1) 
	{
		speed_nang = 200;
		target_nang = BienTroNangValue - 200;
		Bom = 250;
		Act = 1;
	}
	
	if(CB_NHAN_KFS == 0 && Act == 1)	
	{
		for(i=0;i<150;i++)	
		{
			if(CB_NHAN_KFS == 1)	
			{
				i=0;
				break;
			}
			vTaskDelay(2);
		}
		if(i>145)
		{
			speed_nang = 250;
			target_nang = BienTroNangValue + 320;
			Bom = 250;
			speed_taykfs = 250;
			target_taykfs = 867;
			Act = 2;
		}
	}
	
}
//*****************************************  vi tri KFS cac bac ****************************************************
void Bac_kfs(int len ,int ra)
{
speed_nang = 250,target_nang = len;
vTaskDelay(1000);	
speed_taykfs = 250,target_taykfs = ra;
}
//*****************************************  home ****************************************************
void Ve_home(void)
{
	robotResetIMU();
	vTaskDelay(200);
	speed_nang = 200;
	target_nang = 430;
	target_taykfs = 836;
	XI_LANH_KEP_DONG;
	XI_LANH_TAY_XUONG;
	XI_LANH_TAY_VAO;
	Vi_tri = 0;
}
//**************************** Cua_phai ****************************
void Cua_phai_trai(void)
{
	if (LJOY_LR < 50 ) 
			{
			imuNow = _robotIMUAngle + 820;
				
			while (CB_Driff_TRAI == 1){vTaskDelay(1); if(wantExit())	break;}
			
			Bam_thanh_laser_truoc(40,-900,0,53,2,30,15);
				
			while (CB_Driff_TRAI == 0 && lazeTraiValue > 106){vTaskDelay(1); if(wantExit())	break;}
			
			robotRun(-470,15);
			robotRotate(850, 0.8,0);

				while(_robotIMUAngle < imuNow )	
				{
					vTaskDelay (1); 
					if(wantExit())	break;
				}

			robotResetIMU();
			robotStop(0);
			}
			
	if (LJOY_LR > 200 )
			{
			imuNow = _robotIMUAngle - 820;
			
			Bam_thanh_laser_truoc(40,900,0,53,2,20,15);
				
			while (CB_Driff_PHAI == 0 && lazePhaiValue > 106){vTaskDelay(1); if(wantExit())	break;}
			
			robotRun(500,15);
			robotRotate(-950, -0.8,0);

				while(_robotIMUAngle > imuNow )	
				{
					vTaskDelay (1); 
					if(wantExit())	break;
				}

			robotResetIMU();
			robotStop(0);

			}
}
////////////////////////// code den vi tri kfs cac o do////////////////////
//Trai_do(583,589,725,150); //3
//Trai_do(468,536,955,166);//6
//Trai_do(323,406,725,150);//9
//Trai_do(172,237,553,161);//12
//vtri1vs2do(302,307,553,161);//2
//vtri11do(725,150);//11
//vtri1vs2do(159,163,725,150);//1
//Phai_do(517,463,553,161);//4
//Phai_do(618,575,725,150);//7 
//Phai_do(685,658,553,161);//10
////////////////////////// Ham nhan data chay tu  dong////////////////////
extern void Trai_do(int vitri,int giamtoc,int cao,int dai);
extern void Phai_do(int vitri,int giamtoc,int cao,int dai);
extern void vtri1vs2do(int vitri,int giamtoc,int cao,int dai);
extern void vtri11do(int cao,int dai);
extern uint8_t has_active_block ;
extern uint8_t id_block ;

//void chaytudong_esp_now(void) {
//if (id_block == 3) {
//Trai_do(586,600,725,150);	
//}
//else if (id_block == 6) {
//Trai_do(465,536,955,166);	
//}
//else if (id_block == 9) {
//Trai_do(323,406,725,150);
//}
//else if (id_block == 12) {
//Trai_do(172,237,553,161);
//}
//else if (id_block == 1) {
//Phai_do(390,340,725,150);
//}
//else if (id_block == 4) {
//Phai_do(517,463,553,161);
//}
//else if (id_block == 7) {
//Phai_do(618,575,725,150); 
//}
//else if (id_block == 10) {
//Phai_do(685,658,553,161); 
//}
//else if (id_block == 2) {
//vtri1vs2do(302,307,553,161); 
//}
//else if (id_block == 11) {
//vtri11do(725,150);
//}
//}


////// vi du cach dung
void chaytudong_esp_now(void)
{
    

    if (has_active_block)
    {
        // ?? x? lý move, action, take_data_block ? dây

				if (take_data_block == 3) {
					Trai_do(586,600,725,150);	
					Finish_Current_Block();
					}
				else if (take_data_block == 6) {
					Trai_do(465,536,955,166);
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
					vtri1vs2do(159,163,725,150);
					Finish_Current_Block();
					}
				else if (take_data_block == 4) {
					Phai_do(517,463,553,161);
					Finish_Current_Block();
					}
				else if (take_data_block == 7) {
					Phai_do(618,575,725,150); 
					Finish_Current_Block();
					}
				else if (take_data_block == 10) {
					Phai_do(685,658,553,161); 
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


// hàm thuc hien cho den khi het data trong hang doi

extern Leo_bac_200(void);
void Run_All_Blocks_From_Queue(void)
{
    Packet_t pkt;

    while (Queue_Pop(&pkt))   // còn data thì ch?y ti?p
    {
        take_data_block = pkt.id_block;
        move   = pkt.move;
        action = pkt.action;

        switch (take_data_block)
        {
            case 2:  Leo_bac_200(); break;
//            case 6:  Trai_do(465,536,955,166); break;
//            case 9:  Trai_do(323,406,725,150); break;
//            case 12: Trai_do(172,237,553,161); break;
//            case 1:  vtri1vs2do(159,163,725,150); break;
//            case 4:  Phai_do(517,463,553,161); break;
//            case 7:  Phai_do(618,575,725,150); break;
//            case 10: Phai_do(685,658,553,161); break;
//            case 2:  vtri1vs2do(302,307,553,161); break;
//            case 11: vtri11do(725,150); break;
            default: break;
        }
    }

    has_active_block = 0;
    take_data_block = 0;
}


