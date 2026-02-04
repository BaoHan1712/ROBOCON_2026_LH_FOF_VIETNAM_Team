//*****************************8 bien toan cuc *************************************
char xl_truot_lua, xl_kep_lua_tren, xl_kep_lua_duoi, xl_nang_lua,gt_kep_bong;
int vi_tri = 0, Cbcc = 0, Cbnv = 0, Cbnn = 0,vt_xl_nang_lua = 0;
char	On_Off_Ban = 0;
int xl_ban_bong = 0;
int Nang_vong_max = 322, Nang_vong_min = 105, i;
int Nang_goc_max = 540, Nang_goc_min = 300;
int touchpad_press =0;
int laybong =0;
int en_tru = 60;
int max_speed = 10;
int speed_tay_lua = 100;
int speed_xoay = 200;

int xl_kepbong_state = 0;
int xl_nangkep_state = 0;
int ban_bong_state=0 ;

//extern vu8 update;
extern speed_temp;
extern vu8	Cam;
extern float	JTL;
int state_nang = 1;
int state_ha = 1;

int	Min_chan_truoc = 220, Max_chan_truoc = 692, target_chan_truoc;
int	Min_chan_sau = 220, Max_chan_sau = 692, target_chan_sau;
int	Min_xoay_tay = 332, Max_xoay_tay = 710, target_xoay_tay;

int	speed_chan_sau, speed_chan_truoc,speed_tay_xoay;

int force_F;
int final_force;
float result;

extern int Man_xoay_tay;

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
//						XI_LANH_HA_NONG;
//}	


//			
//				
//	if(RJOY){
//		Ban_1 =  Ban_2 =  Ban_3 = 40;
//		Ban_1_back, Ban_2_back, Ban_3_back;
//		vTaskDelay(20000);
//		Ban_1 = 0, Ban_2 = 0, Ban_3 = 0;			

//		
//	}
//}
//void test(void)
//{
//if(LJOY)    Cylinder_L = 250;
//else Cylinder_L = 0;
//}

// *****************************88 nang ha bo ban *********************************
//void Nang_ha_bo_ban(vu8 speed)
//{
//	if(TRIANGLE)  Cylinder_next , Cylinder = speed;
//	else if(X)		 Cylinder_back , Cylinder = speed;
//	else Cylinder = 2;
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
void xoaytam(int received_offset) {  
    int latest_offset;
    float received_speed;

    saveOffset(received_offset);


   if (R2) {
        latest_offset = getLatestOffset();  

        // D?ng n?u offset dã v? g?n CENTER (98 - 100)
        if (latest_offset >= 98 && latest_offset <= 102) {
            robotRotateStop(0);
        }

        // Tính t?c d? xoay m?i nh?t
        received_speed = calculateSpeed(latest_offset);

        // Xoay v? CENTER
        if (latest_offset < CENTER - OFFSET_TOLERANCE) {
            robotRotateFree(-received_speed, 0);  // Xoay ph?i  
        } else if (latest_offset > CENTER + OFFSET_TOLERANCE) {
            robotRotateFree(received_speed, 0); // Xoay trái
        }
    }
	}



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

//void tinhlucban_depthcam(float received_distance) {
//    float gocBanCam = 0;
//    float lucBanCam = 0;
//    // Tính l?c b?n v?i công th?c phi tuy?n
//    lucBanCam = LUC_MOC * pow((received_distance / MOCCHUAN), LUC_BETA);

//    // Gi?i h?n l?c b?n trong kho?ng cho phép
//    if (lucBanCam > LUC_MAX1) {
//        lucBanCam = LUC_MAX1;
//    } else if (lucBanCam < LUC_MIN1) {
//        lucBanCam = LUC_MIN1;
//    }
//    // Tính góc b?n v?i h? s? hi?u ch?nh và kho?ng d?ng
//    lucBanCam = GOC_MOC + ((received_distance - MOCCHUAN) / MOCCHUAN) * (GOC_MAX1 - GOC_MIN1) * GOC_ALPHA;

//    // Gi?i h?n góc b?n trong kho?ng cho phép
//    if (lucBanCam > GOC_MAX1) {
//        lucBanCam = GOC_MAX1;
//    } else if (lucBanCam < GOC_MIN1) {
//        lucBanCam = GOC_MIN1;
//    }
//    calculated_force = lucBanCam;
//    calculated_distance = lucBanCam;
//}



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
	static unsigned int QuangtroCouter = 0, Quangtro_SUM = 0;
	static unsigned int lazeTruocNhoCouter = 0, lazeTruocNho_SUM = 0;

	// Bien tro vi tri co cau
	static unsigned int bientromamxoayCouter = 0, bientromamxoay_SUM = 0;
	static unsigned int bientrochansauCouter = 0, bientrochansau_SUM = 0;
	static unsigned int bientrochantruocCouter = 0, bientrochantruoc_SUM = 0;
	static unsigned int bientroxoaytayCouter = 0, bientroxoaytay_SUM = 0;
	static unsigned int bientrodaytayCouter = 0, bientrodaytay_SUM = 0;
	static unsigned int bientronangtayCouter = 0, bientronangtay_SUM = 0;
	////----------------TINH TOAN LAZER---------------
//	if (lazeSauCouter++ < 100)
//	{
//		lazeSau_SUM += cam_bien_laze_sau;
//	}
//	else
//	{
//		lazeSauValue = lazeSau_SUM / 100;
//		lazeSauCouter = 0;
//		lazeSau_SUM = 0;
//	}
	//-------------------------------------------
	if (lazeTruocCouter++ < 70)
	{
		lazeTruoc_SUM += cam_bien_laze_truoc;
	}
	else
	{
		lazeTruocValue = lazeTruoc_SUM / 70;
		lazeTruocCouter = 0;
		lazeTruoc_SUM = 0;
	}
	//------------------------------ laze truoc--------------
	if (lazePhaiCouter++ < 70)
	{
		lazePhai_SUM += cam_bien_laze_phai;
	}
	else
	{
		lazePhaiValue = lazePhai_SUM / 70;
		lazePhaiCouter = 0;
		lazePhai_SUM = 0;
	}
	//------------------------------ laze truoc nho --------------
	if (lazeTruocNhoCouter++ < 70)
	{
		lazeTruocNho_SUM += cam_bien_laze_truoc_nho;
	}
	else
	{
		lazeTruocNhoValue = lazeTruocNho_SUM / 70;
		lazeTruocNhoCouter = 0;
		lazeTruocNho_SUM = 0;
	}
	//----------------------------------------- laze sau-------------
	if (lazeTraiCouter++ < 70)
	{
		lazeTrai_SUM += cam_bien_laze_trai;
	}
	else
	{
		lazeTraiValue = lazeTrai_SUM / 70;
		lazeTraiCouter = 0;
		lazeTrai_SUM = 0;
	}
	//----------------------------------------- laze sau-------------
	if (QuangtroCouter++ < 50)
	{
		Quangtro_SUM += Quang_tro;
	}
	else
	{
		quangTroValue = Quangtro_SUM / 50;
		QuangtroCouter = 0;
		Quangtro_SUM = 0;
	}
	//-----------------TINH TOAN BIEN TRO---------------

//	if (bientromamxoayCouter++ < 10)
//	{
//		bientromamxoay_SUM += bien_tro_nong_ban;
//	}
//	else
//	{
//		BienTroNongBanValue = bientromamxoay_SUM / 10;
//		bientromamxoayCouter = 0;
//		bientromamxoay_SUM = 0;
//	}
	//-----------------------------------
	if (bientrochansauCouter++ < 50)
	{
		bientrochansau_SUM += bien_tro_chan_sau;
	}
	else
	{
		bientrochansauValue = bientrochansau_SUM / 50;
		bientrochansauCouter = 0;
		bientrochansau_SUM = 0;
	}
	//-----------------------------
	if (bientrochantruocCouter++ < 50)
	{
		bientrochantruoc_SUM += bien_tro_chan_truoc;
	}
	else
	{
		bientrochantruocValue = bientrochantruoc_SUM / 50;
		bientrochantruocCouter = 0;
		bientrochantruoc_SUM = 0;
	}


	//-----------------------------
	if (bientroxoaytayCouter++ < 50)
	{
		bientroxoaytay_SUM += bien_tro_xoay_tay;
	}
	else
	{
		bientroxoaytayValue = bientroxoaytay_SUM / 50;
		bientroxoaytayCouter = 0;
		bientroxoaytay_SUM = 0;
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


void Chan_truoc()
{
//		if(BienTroNongBanValue < taget_BT_Xoay - 5 ){
//			Cylinder = 0;
//			return;
//		}
	
	if (target_chan_truoc < Min_chan_truoc)
		target_chan_truoc = Min_chan_truoc;
	if (target_chan_truoc > Max_chan_truoc)
		target_chan_truoc = Max_chan_truoc;

	if (abs(bientrochantruocValue - target_chan_truoc) > 5)
	{
		if (bientrochantruocValue > target_chan_truoc)	mor_lift_front_down;
		else																						mor_lift_front_up;

		speed_temp = abs(bientrochantruocValue - target_chan_truoc)*3;
//		if (speed_temp > 170)
//				speed_temp = 170;
		if (speed_temp > speed_chan_truoc)
				speed_temp = speed_chan_truoc;
		if (speed_temp < 30)
				speed_temp = 30;
	
		mor_lift_front = speed_temp;
	}
	else mor_lift_front = 0;
}


void Chan_sau()
{
	if (target_chan_sau < Min_chan_sau)
		target_chan_sau = Min_chan_sau;
	if (target_chan_sau > Max_chan_sau)
		target_chan_sau = Max_chan_sau;

	if (abs(bientrochansauValue - target_chan_sau) > 5)
	{
		if (bientrochansauValue > target_chan_sau)			mor_lift_rear_down;
		else																						mor_lift_rear_up;

		speed_temp = abs(bientrochansauValue - target_chan_sau)*3;
		if (speed_temp > speed_chan_sau)
				speed_temp = speed_chan_sau;
		if (speed_temp < 50)
				speed_temp = 50;
	
		mor_lift_rear = speed_temp;
	}
	else mor_lift_rear = 0;
}

//************************************** xoay tay kep auto **************************************
	void Xoay_tay_kep()
{
	if (target_xoay_tay < Min_xoay_tay)
		target_xoay_tay = Min_xoay_tay;
	if (target_xoay_tay > Max_xoay_tay)
		target_xoay_tay = Max_xoay_tay;

	if ((abs(bientroxoaytayValue - target_xoay_tay) > 2) && CB_tay1_giua == 0 && CB_tay2_giua == 0 && CB_tay3_giua == 0)
	{
		if (bientroxoaytayValue > target_xoay_tay)			tay_xoay_thuan;
		else																						tay_xoay_nghich;

		speed_temp = abs(bientroxoaytayValue - target_xoay_tay);
		if (speed_temp > speed_tay_xoay)
				speed_temp = speed_tay_xoay;
		if (speed_temp < 50)
				speed_temp = 50;
	
		tay_xoay = speed_temp;
	}
	else tay_xoay = 0;
}

//******************************** leo bac 200 ****************************
void Leo_bac_200(void)
{	
	int i;
			// nâng bánh trc lên 
	speed_chan_sau = 100;
	speed_chan_truoc = 140;
	
	target_chan_truoc = 460, target_chan_sau = 460;
	
	for(i=0;i<50;i++)		
	{
		while(bientrochantruocValue < 455)	{vTaskDelay(1); if(!wantExit())	break;}
	}
	
		for(i=0;i<250;i++)	
	{	
		while(CB_Ha_Dau == 0)	{vTaskDelay(1); if(!wantExit())	break;} 
	}
	
//	robotRun(0,10);
	robotRunAngle(-900,15,-900,0.2);
	
	for(i=0;i<250;i++)	
	{	
		while(CB_Ha_Dau == 1)	{vTaskDelay(1); if(!wantExit())	break;}
	}
//	
//	RESET_ENCODER(); 
//	
//	while(ENCODER_RL() < 250)	{vTaskDelay (1); if(!wantExit())	break;}
//	
	robotStop(0);
////	
	target_chan_truoc = 222;
	for(i=0;i<50;i++)		
	{
		while(bientrochantruocValue > 225)	{vTaskDelay(1); if(!wantExit())	break;}
	}
	
	// nâng bánh sau lên 
	target_chan_sau = 490;
	robotRunAngle(-900,15,-900,0.2);
	
	for(i=0;i<550;i++)	
	{	
		while(CB_bung == 1)	{vTaskDelay(1); if(!wantExit())	break;}
	}
	target_chan_truoc = 240;
	RESET_ENCODER(); 
	
	while(ENCODER_FR() + ENCODER_FL() < 300)	{vTaskDelay (5); if(!wantExit())	break;}

	robotStop(0);
	
	target_chan_sau = 232;

	for(i=0;i<250;i++)	
	{
		while(bientrochansauValue > 235)	{vTaskDelay(1); if(!wantExit())	break;}
	}
	
	robotRunAngle(-900,12,-900,0.2);
	for(i=0;i<150;i++) 
	{
		while(CB_Ha_Sau == 1)		{vTaskDelay(1); if(!wantExit())	break;}
	}
	
//////	
	robotStop(0);
	
}
//******************************** leo bac 400 ****************************
void Leo_bac_400(void)
{	
	int i;
	
	speed_chan_sau = 100;
	speed_chan_truoc = 140;
	
	target_chan_truoc = 690, target_chan_sau = 690;
	
	for(i=0;i<250;i++)	
	{
		while(bientrochantruocValue < 688)	{vTaskDelay(5); if(!wantExit())	break;}
	}
	robotRunAngle(-900,10,-900,0.2);
	
	for(i=0;i<550;i++)	
	{	
		while(CB_Ha_Dau == 1)	{vTaskDelay(1); if(!wantExit())	break;}
	}

	RESET_ENCODER(); 
	
	while(ENCODER_RR() + ENCODER_RL() < 200)	{vTaskDelay (5); if(!wantExit())	break;}
	
	robotStop(0); 
//	
	target_chan_truoc = 222;
	
	for(i=0;i<50;i++)		
	{
		while(bientrochantruocValue > 225)	{vTaskDelay(5); if(!wantExit())	break;}
	}
	
	robotStop(0);
	
	target_chan_sau = 692;
	robotRunAngle(-900,15,-900,0.2);
	
	for(i=0;i<550;i++)	
	{	
		while(CB_bung == 1)	{vTaskDelay(1); if(!wantExit())	break;}
	}
	target_chan_truoc = 240;

	RESET_ENCODER(); 
	
	while(ENCODER_FR() + ENCODER_FL() < 400)	{vTaskDelay (5); if(!wantExit())	break;}

	robotStop(0);
////	
	target_chan_sau = 232;
	for(i=0;i<250;i++)	
	{
		while(bientrochansauValue > 235)	{vTaskDelay(5); if(!wantExit())	break;}
	}


	robotStop(0);
//	
	robotRunAngle(-900,12,-900,0.2);
//	robotRun(0,20);
	
	for(i=0;i<150;i++) 
	{
		while(CB_Ha_Sau == 1)		{vTaskDelay(1); if(!wantExit())	break;}
	}

////	
	robotStop(0);
	
}

////******************************** xuong bac 200 ****************************88
void Xuong_bac_200(void)
{	
	int i;
	speed_chan_sau = 100;
	speed_chan_truoc = 140;
	
	target_chan_truoc = 238, target_chan_sau = 238;
	
	for(i=0;i<250;i++)	
	{
		while(CB_Ha_Dau == 1)	{vTaskDelay(5); if(!wantExit())	break;}
	}
	
	robotRunAngle(-900,7,-900,0.2);

	for(i=0;i<250;i++)
	{	
		while(CB_Ha_Dau == 0)	{vTaskDelay(5); if(!wantExit())	break;}
	}

	RESET_ENCODER();
	
	while(abs(ENCODER_RR()) + abs(ENCODER_RL()) < 1150)	{vTaskDelay (1); if(!wantExit())	break;}
	
	robotStop(0);
//	
//	vTaskDelay(2500);
	target_chan_truoc = 460;
	
		for(i=0;i<250;i++)	
	{
		while(bientrochantruocValue < 458)	{vTaskDelay(5); if(!wantExit())	break;}
	}
		robotStop(0);
//	target_chan_sau = 232;
	robotRunAngle(-900,7,-900,0.2);
//	robotRun(0,20);
	
	for(i=0;i<550;i++)	
	{	
		while(CB_bung == 0)	{vTaskDelay(1); if(!wantExit())	break;}
	}

	RESET_ENCODER(); 
	
	while(abs(ENCODER_FR()) + abs(ENCODER_FL()) < 1600)	{vTaskDelay (1); if(!wantExit())	break;}
	
	robotStop(0);

	target_chan_sau = 460;
	
	for(i=0;i<250;i++)	
	{
		while(bientrochansauValue < 458)	{vTaskDelay(5); if(!wantExit())	break;}
	}
	robotStop(0);

	robotRunAngle(-900,10,-900,0.2);
	
	for(i=0;i<150;i++) 
	{
		while(CB_Ha_Sau == 0)		{vTaskDelay(1); if(!wantExit())	break;}
	}
//	
	robotStop(30);
}
	

////******************************** xuong bac 400 ****************************88
	void Xuong_bac_400 (void)
{	
	int i;
	speed_chan_sau = 100;
	speed_chan_truoc = 140;
	
	target_chan_truoc = 238, target_chan_sau = 238;
	
	for(i=0;i<250;i++)	
	{
		while(CB_Ha_Dau == 1)	{vTaskDelay(5); if(!wantExit())	break;}
	}
	
	robotRunAngle(-900,7,-900,0.2);

	for(i=0;i<250;i++)
	{	
		while(CB_Ha_Dau == 0)	{vTaskDelay(5); if(!wantExit())	break;}
	}

	RESET_ENCODER();
	
	while(abs(ENCODER_RR()) + abs(ENCODER_RL()) < 1150)	{vTaskDelay (1); if(!wantExit())	break;}
	
	robotStop(0);
	target_chan_truoc = 690;
	
		for(i=0;i<250;i++)	
	{
		while(bientrochantruocValue < 686)	{vTaskDelay(5); if(!wantExit())	break;}
	}
		robotStop(0);
////	
	robotRunAngle(-900,7,-900,0.2);
//	robotRun(0,20);
//	
	for(i=0;i<550;i++)	
	{	
		while(CB_bung == 0)	{vTaskDelay(1); if(!wantExit())	break;}
	}
	
	RESET_ENCODER(); 
	
	while(abs(ENCODER_FR()) + abs(ENCODER_FL()) < 1600)	{vTaskDelay (1); if(!wantExit())	break;}
	
	robotStop(0);

	target_chan_sau = 690;
	
	for(i=0;i<250;i++)	
	{
		while(bientrochansauValue < 686)	{vTaskDelay(5); if(!wantExit())	break;}
	}
	robotStop(0);

	robotRunAngle(-900,10,-900,0.2);
	
	for(i=0;i<150;i++) 
	{
		while(CB_Ha_Sau == 0)		{vTaskDelay(1); if(!wantExit())	break;}
	}
////	

	robotStop(30);
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

//********************************************* bam thanh laser phai ********************************************
void Bam_thanh_laser_trai(int speed, int runangle, int AngleHead, int lazer_stable_phai, int num_change_stable, int fix_max,int rat)
{
	int fix;

	fix = abs(lazeTraiValue - lazer_stable_phai) * rat;

	if (fix > fix_max)
	fix = fix_max;

	if (lazeTraiValue - lazer_stable_phai < num_change_stable)
	{
		robotRunAngle(runangle + fix, speed, AngleHead, 0.3);
	}
	else if (lazeTraiValue - lazer_stable_phai > num_change_stable)
	{
		robotRunAngle(runangle - fix, speed, AngleHead, 0.3);
	}
	else
		robotRunAngle(runangle, speed, AngleHead, 0.3);
}


//********************************************* bam thanh laser truoc ********************************************
void Bam_laser_truoc(int speed, int runangle, int AngleHead, int lazer_stable_truoc, int num_change_stable, int fix_max,int rat)
{
	int fix;

	fix = abs(lazeTruocValue - lazer_stable_truoc) * rat;

	if (fix > fix_max)
	fix = fix_max;

	if (lazeTruocValue - lazer_stable_truoc < num_change_stable)
	{
		robotRunAngle(runangle - fix, speed, AngleHead, 0.7);
	}
	else if (lazeTruocValue - lazer_stable_truoc > num_change_stable)
	{
		robotRunAngle(runangle + fix, speed, AngleHead, 0.7);
	}
	else
		robotRunAngle(runangle, speed, AngleHead, 0.77);
}
/////////////////////////////leodoc/////////////////////////////////////////
	void leodoc1(void)
{	
	int i;
	
	speed_chan_sau = 100;
	speed_chan_truoc = 160;
	
	target_chan_truoc = 270, target_chan_sau = 280;
	
	robotRun(0,30);
	for(i=0;i<550;i++)	
	{	
			while(lazeTruocValue > 40)	{vTaskDelay(5); if(wantExit())	break;}
	}
	
	robotRun(0,30);
	for(i=0;i<550;i++)	
	{	
			while(lazeTruocValue < 70)	{vTaskDelay(5); if(wantExit())	break;}
	}	
	
	robotRun(0,30);
	
	for(i=0;i<550;i++)	
	{	
			while(lazeTruocValue > 50)	{vTaskDelay(5); if(wantExit())	break;}
	}			
	
	
	robotStop(0);
	
	for(i=0;i<550;i++)	
	{	
			while(lazeTraiValue > 100)	
			{	
				Bam_laser_truoc(60,-900,0,32,2,200,30);
				vTaskDelay(5); 
				if(wantExit())	break;
			}
		
	}	
	
	for(i=0;i<550;i++)	
	{	
			while(lazeTraiValue > 15)	
			{	
				Bam_laser_truoc(20,-900,0,32,2,200,30);
				vTaskDelay(5); 
				if(wantExit())	break;
			}
		
	}	
	robotStop(0);
}

void leodoc2(void)
{	
	int i;
	
	speed_chan_sau = 100;
	speed_chan_truoc = 160;
	
	target_chan_truoc = 270, target_chan_sau = 280;
	
	robotRun(0,30);
	for(i=0;i<550;i++)	
	{	
			while(lazeTruocValue > 40)	{vTaskDelay(5); if(wantExit())	break;}
	}
	
	robotRun(0,30);
	for(i=0;i<550;i++)	
	{	
			while(lazeTruocValue < 70)	{vTaskDelay(5); if(wantExit())	break;}
	}	
	
	robotRun(0,30);
	
	for(i=0;i<550;i++)	
	{	
			while(lazeTruocValue > 50)	{vTaskDelay(5); if(wantExit())	break;}
	}			
	
	
	robotStop(0);
	
	for(i=0;i<550;i++)	
	{	
			while(lazeTraiValue > 100)	
			{	
				Bam_laser_truoc(60,-900,0,32,2,200,30);
				vTaskDelay(5); 
				if(wantExit())	break;
			}
		
	}	
	
	for(i=0;i<550;i++)	
	{	
			while(lazeTraiValue > 15)	
			{	
				Bam_laser_truoc(20,-900,0,32,2,200,30);
				vTaskDelay(5); 
				if(wantExit())	break;
			}
		
	}	
	robotStop(0);
}

//****************************** tay gap kfs 1 ********************************
void Tay_3_gap_kfs_len(void)
{
	Tay3_len_on;
	Tay3_xuong_off;
}
void Tay_3_gap_kfs_xuong(void)
{
	Tay3_xuong_on;
	Tay3_len_off;
}
void Tay_3_gap_kfs_dung(void)
{
	Tay3_xuong_off;
	Tay3_len_off;
}

//****************************** tay gap kfs 1 ********************************
void Tay_1_gap_kfs_len(void)
{
	Tay1_len_on;
	Tay1_xuong_off;
}
void Tay_1_gap_kfs_xuong(void)
{
	Tay1_xuong_on;
	Tay1_len_off;
}
void Tay_1_gap_kfs_dung(void)
{
	Tay1_xuong_off;
	Tay1_len_off;
}

//****************************** tay gap kfs 1 ********************************
void Tay_2_gap_kfs_len(void)
{
	Tay2_len_on;
	Tay2_xuong_off;
}
void Tay_2_gap_kfs_xuong(void)
{
	Tay2_xuong_on;
	Tay2_len_off;
}
void Tay_2_gap_kfs_dung(void)
{
	Tay2_xuong_off;
	Tay2_len_off;
}
void Tay_len_all(void)
{
	Tay1_len_on;
	Tay1_xuong_off;
	Tay2_len_on;
	Tay2_xuong_off;
	Tay3_len_on;
	Tay3_xuong_off;
}

//******************************* nang ha bang tayu **************************
void Xoay_tay_Manual(void)
{
	if (SQUARE && !R1 && !R2 && !L2 && bientroxoaytayValue < Max_xoay_tay ) 				
	{
		if(L1 && bientroxoaytayValue < Max_xoay_tay - 20)	tay_xoay = 100;
		else		tay_xoay = 40;
		tay_xoay_thuan;
		target_xoay_tay = bientroxoaytayValue;
		Man_xoay_tay = 1;
	}
	else	if (O && !R1 && !R2 && !L2 && bientroxoaytayValue > Min_xoay_tay) 	
				{
					if(L1 && bientroxoaytayValue > Min_xoay_tay + 20)	tay_xoay = 100;
					else		tay_xoay = 40;
					tay_xoay_nghich;
					target_xoay_tay = bientroxoaytayValue;
					Man_xoay_tay = 1;
				}
	else Man_xoay_tay = 0;
}
