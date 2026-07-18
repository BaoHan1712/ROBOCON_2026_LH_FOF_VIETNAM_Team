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

void reset_ha_tay_truoc (void);

void dung_cho_khoi_r1_ben_canh (void);
void tracking_traiPhaiThang_tren_tay4(void);
void tracking_traiPhaiThang_tren_tay1(void);
void tracking_traiPhaiThang_tren_tay2(void);
void tracking_traiPhaiThang_tren_tay3(void);
void Lay_ben_phai_bac_200_duoi (void);
void chuan_bi_gap_trai_200_tren_1 (void );
void Lay_ben_phai_bac_200_tren_xanh_3(void);
void Xuong_bac_200(int Angle, int Robot_Angle);

void ha_tay_4(int target_tay, int hs_trackking, int max_toc, int min_toc, float k, int gc_cb2, int gc_cb1, int toc_track);
void ha_tay_1(int target_tay, int hs_trackking, int max_toc, int min_toc, float k, int gc_cb2, int gc_cb1, int toc_track);
void ha_tay_2(int target_tay, int hs_trackking, int max_toc, int min_toc, float k, int gc_cb2, int gc_cb1, int toc_track);
void ha_tay_3(int target_tay, int hs_trackking, int max_toc, int min_toc, float k, int gc_cb2, int gc_cb1, int toc_track);

void ha_tay_4_k_xlang(int target_tay, int hs_trackking, int max_toc, int min_toc, float k, int gc_cb2, int gc_cb1, int toc_track);
void ha_tay_1_k_xlang(int target_tay, int hs_trackking, int max_toc, int min_toc, float k, int gc_cb2, int gc_cb1, int toc_track);
void ha_tay_2_k_xlang(int target_tay, int hs_trackking, int max_toc, int min_toc, float k, int gc_cb2, int gc_cb1, int toc_track);
void ha_tay_3_k_xlang(int target_tay, int hs_trackking, int max_toc, int min_toc, float k, int gc_cb2, int gc_cb1, int toc_track);


void chinh_lai_vi_tri_laser_phai_custom(int vitri, int gia_tri_lap, int min_toc, int max_toc, int sai_so);
void phun_tay_ra (void);

extern speed_temp;
extern vu8	Cam;
extern float	JTL;
int state_nang = 1;
int state_ha = 1;

int Xoay_ok;

extern int TinHieu_ChuanBi_GapThang;
extern int TinHieu_ChuanBi_GapTrai ;
extern int TinHieu_ChuanBi_GapPhai;
extern int vitri_tay41_laser_trai_GapQua;
extern int vitri_tay23_laser_trai_GapQua;

void di_vao_giua_do(void);
void chuan_bi_gap_phai_200_tren_3(void);
void kiem_tra_huong_ha_tay_gap_phia_truoc(void);
void chuan_bi_gap_thang_xanh_4 (void);
void chuan_bi_gap_thang_xanh_7(void);
void chuan_bi_gap_phai_200_tren_7_10(void);
void Lay_ben_trai_bac_200_tren_xanh_9(void);
void Lay_ben_trai_bac_200_tren (void);
void chuan_bi_gap_trai_200_duoi_ko_thanh(void);
void ha_sat_xuong (void);
void chuan_bi_gap_phai_200_duoi_ko_thanh(void);

void kiem_tra_huong_quay_tay_gap_ben_trai (void);
void kiem_tra_huong_quay_tay_gap_ben_phai (void);
 void chuan_bi_gap_trai_200_duoi_5 (void);
 void chuan_bi_gap_phai_200_tren_4 (void );

// *************** thong so tay gap ************
int	Min_chan_truoc = 230, Max_chan_truoc = 730, target_chan_truoc;
int	Min_chan_sau = 230, Max_chan_sau = 730, target_chan_sau;
int	Min_xoay_tay = 250, Max_xoay_tay = 710, target_xoay_tay;
int	Min_tay_gat1 = 95, Max_tay_gat1 = 803, target_tay_gat1;
int	Min_tay_gat2 = 94, Max_tay_gat2 = 800, target_tay_gat2; 


/// cchinh bien tro max la 135

int	speed_chan_sau, speed_chan_truoc,speed_tay_xoay,speed_tay_gat1,speed_tay_gat2;
int home_trc,home_sau;

int force_F;
int final_force;
float result;

extern int Man_xoay_tay;
extern int Man_gat1;
extern int Man_gat2;

extern int da_lay_tay1;
extern int da_lay_tay2;
extern int da_lay_tay3;
extern int da_lay_tay4;


void robotLineRunLeft(vu8 speed);
void robotLineRunRight(vu8 speed);
void kiem_tra_huong_quay_tay_gap_phia_truoc (void);
void chinh_lai_vi_tri_laser_trai(int vitri, int gia_tri_lap);
void chinh_lai_vi_tri_laser_phai(int vitri, int gia_tri_lap);
void Ktra_vtri_kep4 (void);
void Ktra_vtri_kep1 (void);
void Ktra_vtri_kep2 (void);
void Ktra_vtri_kep3 (void);
void di_vao_giua (void);

void Ktra_vtri_kep4_trai (void);
void Ktra_vtri_kep1_trai (void);
void Ktra_vtri_kep2_trai (void);
void Ktra_vtri_kep3_trai (void);


void Ktra_vtri_kep4_phai (void);
void Ktra_vtri_kep1_phai (void);
void Ktra_vtri_kep2_phai (void);
void Ktra_vtri_kep3_phai (void);

void Bam_thanh_laser_trai(int speed, int runangle, int AngleHead, int lazer_stable_phai, int num_change_stable, int fix_max,int rat);
void Bam_thanh_laser_phai(int speed, int runangle, int AngleHead, int lazer_stable_phai, int num_change_stable, int fix_max,int rat);


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
	static unsigned int bientrodaytay1Couter = 0, bientrodaytay1_SUM = 0;
	static unsigned int bientrodaytay2Couter = 0, bientrodaytay2_SUM = 0;
	////----------------TINH TOAN LAZER---------------
	if (lazeSauCouter++ < 70)
	{
		lazeSau_SUM += cam_bien_laze_sau;
	}
	else
	{
		lazeSauValue = lazeSau_SUM / 70;
		lazeSauCouter = 0;
		lazeSau_SUM = 0;
	}
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
	//------------------------------ laze phai --------------
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
//	//------------------------------ laze truoc nho --------------
//	if (lazeTruocNhoCouter++ < 70)
//	{
//		lazeTruocNho_SUM += cam_bien_laze_truoc_nho;
//	}
//	else
//	{
//		lazeTruocNhoValue = lazeTruocNho_SUM / 70;
//		lazeTruocNhoCouter = 0;
//		lazeTruocNho_SUM = 0;
//	}
	//----------------------------------------- laze trai -------------
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
	if (bientroxoaytayCouter++ < 70)
	{
		bientroxoaytay_SUM += bien_tro_xoay_tay;
	}
	else
	{
		bientroxoaytayValue = bientroxoaytay_SUM / 70;
		bientroxoaytayCouter = 0;
		bientroxoaytay_SUM = 0;
	}

	//-----------------------------
	if (bientrodaytay1Couter++ < 70)
	{
		bientrodaytay1_SUM += bien_tro_gat1;
	}
	else
	{
		bientrodaytay1Value = bientrodaytay1_SUM / 70;
		bientrodaytay1Couter = 0;
		bientrodaytay1_SUM = 0;
	}

//-----------------------------
	if (bientrodaytay2Couter++ < 70)
	{
		bientrodaytay2_SUM += bien_tro_gat2;
	}
	else
	{
		bientrodaytay2Value = bientrodaytay2_SUM / 70;
		bientrodaytay2Couter = 0;
		bientrodaytay2_SUM = 0;
	}

}


//void Chan_truoc()
//{
////		if(BienTroNongBanValue < taget_BT_Xoay - 5 ){
////			Cylinder = 0;
////			return;
////		}
//	
//	if (target_chan_truoc < Min_chan_truoc)
//		target_chan_truoc = Min_chan_truoc;
//	if (target_chan_truoc > Max_chan_truoc)
//		target_chan_truoc = Max_chan_truoc;

//	if (abs(bientrochantruocValue - target_chan_truoc) > 4)
//	{
//		if (bientrochantruocValue > target_chan_truoc)	mor_lift_front_down;
//		else																						mor_lift_front_up;

//		speed_temp = abs(bientrochantruocValue - target_chan_truoc)*2;
////		if (speed_temp > 170)
////				speed_temp = 170;
//		if (speed_temp > speed_chan_truoc)
//				speed_temp = speed_chan_truoc;
//		if (speed_temp < 50)
//				speed_temp = 50;
//		
//		mor_lift_front = speed_temp;
//	}
//	else mor_lift_front = 25, mor_lift_front_up;
//}


//void Chan_sau()
//{
//	if (target_chan_sau < Min_chan_sau)
//		target_chan_sau = Min_chan_sau;
//	if (target_chan_sau > Max_chan_sau)
//		target_chan_sau = Max_chan_sau;

//	if (abs(bientrochansauValue - target_chan_sau) > 5)
//	{
//		if (bientrochansauValue > target_chan_sau)			mor_lift_rear_down;
//		else																						mor_lift_rear_up;

//		speed_temp  = abs(bientrochansauValue - target_chan_sau)*2;
//		if (speed_temp > speed_chan_sau)
//				speed_temp = speed_chan_sau;
//		if (speed_temp < 20)
//				speed_temp = 20;
//		
//		mor_lift_rear = speed_temp;
//	}
//	else mor_lift_rear = 10, mor_lift_rear_up;
//}

// Dao dong/rung xung quanh target thi ||  Giam Kp, tang Kd


//// ===== PID Variables cho Chan Truoc =====
//float pid_kp_chan_truoc = 0.5f;
//float pid_ki_chan_truoc = 0.0f;
//float pid_kd_chan_truoc = 0.0f;

//float pid_integral_chan_truoc = 0.0f;
//float pid_prev_error_chan_truoc = 0.0f;
//float pid_output_chan_truoc = 0.0f;
//#define PID_INTEGRAL_LIMIT_CHAN_TRUOC  500.0f



//void Chan_truoc()
//{
//    float error = (float)(target_chan_truoc - bientrochantruocValue);
//    float i_term;
//    float d_term;
//    float p_term = pid_kp_chan_truoc * error;

//    if (target_chan_truoc < Min_chan_truoc)
//        target_chan_truoc = Min_chan_truoc;
//    if (target_chan_truoc > Max_chan_truoc)
//        target_chan_truoc = Max_chan_truoc;

//    if (abs(error) > 2)
//    {
//        pid_integral_chan_truoc += error;
//        if (pid_integral_chan_truoc > PID_INTEGRAL_LIMIT_CHAN_TRUOC)
//            pid_integral_chan_truoc = PID_INTEGRAL_LIMIT_CHAN_TRUOC;
//        if (pid_integral_chan_truoc < -PID_INTEGRAL_LIMIT_CHAN_TRUOC)
//            pid_integral_chan_truoc = -PID_INTEGRAL_LIMIT_CHAN_TRUOC;

//        i_term = pid_ki_chan_truoc * pid_integral_chan_truoc;
//        d_term = pid_kd_chan_truoc * (error - pid_prev_error_chan_truoc);
//        pid_prev_error_chan_truoc = error;

//        pid_output_chan_truoc = p_term + i_term + d_term;

//        if (error < 0)
//            mor_lift_front_down;  
//        else
//            mor_lift_front_up;   

//        speed_temp = (uint16_t)abs(pid_output_chan_truoc) * 3;
//        if (speed_temp > speed_chan_truoc)
//            speed_temp = speed_chan_truoc;
//        if (speed_temp < 20)
//            speed_temp = 20;

//        mor_lift_front = speed_temp;
//    }
//    else
//    {
//        // Ðã den target thi giu motor
//        pid_integral_chan_truoc  = 0.0f;
//        pid_prev_error_chan_truoc = 0.0f;
//        mor_lift_front = 2;
//        mor_lift_front_up;
//    }
//}

// ===== PID Variables cho Chan Truoc =====
float pid_kp_chan_truoc = 0.5f;
float pid_ki_chan_truoc = 0.001f;
float pid_kd_chan_truoc = 2.1f;

float pid_integral_chan_truoc = 0.0f;
float pid_prev_error_chan_truoc = 0.0f;
float pid_output_chan_truoc = 0.0f;

#define PID_INTEGRAL_LIMIT_CHAN_TRUOC  300.0f

// ===== Gia t?c =====
#define MAX_STEP_CHAN_TRUOC  4   // giong maxStep = 2~5 tùy ch?nh

static float speed_prev = 0;

// ===== MAIN =====
void Chan_truoc()
{			
		float speed_now;
		float delta ;
    float error = (float)(target_chan_truoc - bientrochantruocValue);
    float i_term, d_term;
    float p_term = pid_kp_chan_truoc * error;

    // ===== Clamp target =====
    if (target_chan_truoc < Min_chan_truoc)
        target_chan_truoc = Min_chan_truoc;
    if (target_chan_truoc > Max_chan_truoc)
        target_chan_truoc = Max_chan_truoc;

    if (abs(error) > 6)
    {
        // ===== PID =====
        pid_integral_chan_truoc += error;

        if (pid_integral_chan_truoc > PID_INTEGRAL_LIMIT_CHAN_TRUOC)
            pid_integral_chan_truoc = PID_INTEGRAL_LIMIT_CHAN_TRUOC;
        if (pid_integral_chan_truoc < -PID_INTEGRAL_LIMIT_CHAN_TRUOC)
            pid_integral_chan_truoc = -PID_INTEGRAL_LIMIT_CHAN_TRUOC;

        i_term = pid_ki_chan_truoc * pid_integral_chan_truoc;
        d_term = pid_kd_chan_truoc * (error - pid_prev_error_chan_truoc);
        pid_prev_error_chan_truoc = error;

        pid_output_chan_truoc = p_term + i_term + d_term;

        // ===== Direction =====
        if (error < 0)
            mor_lift_front_down;
        else
            mor_lift_front_up;

        // ===== Speed t? PID =====
        speed_now = (float)abs(pid_output_chan_truoc) * 3.2f;

        if (speed_now > speed_chan_truoc)
            speed_now = speed_chan_truoc;
        if (speed_now < 20)
            speed_now = 20;

        // ===== GI?I H?N GIA T?C (CHÍNH) =====
        delta = speed_now - speed_prev;

        if (delta > MAX_STEP_CHAN_TRUOC)
            speed_now = speed_prev + MAX_STEP_CHAN_TRUOC;
        else if (delta < -MAX_STEP_CHAN_TRUOC)
            speed_now = speed_prev - MAX_STEP_CHAN_TRUOC;

        speed_prev = speed_now;

        mor_lift_front = (uint16_t)speed_now;
    }
    else
    {
        // ===== HOLD =====
        pid_integral_chan_truoc = 0.0f;
        pid_prev_error_chan_truoc = 0.0f;

        mor_lift_front = 2;
        mor_lift_front_up;

        // reset gia t?c
        speed_prev = 0;
    }
}

// ===== PID Variables cho Chan Sau =====
float pid_kp_chan_sau = 0.5f;
float pid_ki_chan_sau = 0.001f;
float pid_kd_chan_sau = 2.1f;

float pid_integral_chan_sau = 0.0f;
float pid_prev_error_chan_sau = 0.0f;
float pid_output_chan_sau = 0.0f;

#define PID_INTEGRAL_LIMIT_CHAN_SAU  300.0f

// ===== Gia t?c =====
#define MAX_STEP_CHAN_SAU 4

static float speed_prev_sau = 0;

// ===== MAIN =====
void Chan_sau()
{
    float error = (float)(target_chan_sau - bientrochansauValue);
    float i_term, d_term;
    float p_term = pid_kp_chan_sau * error;

    float speed_now;
    float delta;

    // ===== Clamp target =====
    if (target_chan_sau < Min_chan_sau)
        target_chan_sau = Min_chan_sau;
    if (target_chan_sau > Max_chan_sau)
        target_chan_sau = Max_chan_sau;

    if (abs(error) > 6)
    {
        // ===== PID =====
        pid_integral_chan_sau += error;

        if (pid_integral_chan_sau > PID_INTEGRAL_LIMIT_CHAN_SAU)
            pid_integral_chan_sau = PID_INTEGRAL_LIMIT_CHAN_SAU;
        if (pid_integral_chan_sau < -PID_INTEGRAL_LIMIT_CHAN_SAU)
            pid_integral_chan_sau = -PID_INTEGRAL_LIMIT_CHAN_SAU;

        i_term = pid_ki_chan_sau * pid_integral_chan_sau;

        d_term = pid_kd_chan_sau * (error - pid_prev_error_chan_sau);
        pid_prev_error_chan_sau = error;

        pid_output_chan_sau = p_term + i_term + d_term;

        // ===== Direction =====
        if (error < 0)
            mor_lift_rear_down;
        else
            mor_lift_rear_up;

        // ===== Speed t? PID =====
        speed_now = (float)abs(pid_output_chan_sau) * 3.2f;

        if (speed_now > speed_chan_sau)
            speed_now = speed_chan_sau;

        if (speed_now < 20)
            speed_now = 20;

        // ===== GI?I H?N GIA T?C =====
        delta = speed_now - speed_prev_sau;

        if (delta > MAX_STEP_CHAN_SAU)
            speed_now = speed_prev_sau + MAX_STEP_CHAN_SAU;
        else if (delta < -MAX_STEP_CHAN_SAU)
            speed_now = speed_prev_sau - MAX_STEP_CHAN_SAU;

        speed_prev_sau = speed_now;

        mor_lift_rear = (uint16_t)speed_now;
    }
    else
    {
        // ===== HOLD =====
        pid_integral_chan_sau = 0.0f;
        pid_prev_error_chan_sau = 0.0f;

        mor_lift_rear = 2;
        mor_lift_rear_up;

        // reset gia t?c
        speed_prev_sau = 0;
    }
}

//************************************** gat1 **************************************
void Gat_1()
{
	if (target_tay_gat1 < Min_tay_gat1)
		target_tay_gat1 = Min_tay_gat1;
	if (target_tay_gat1 > Max_tay_gat1)
		target_tay_gat1 = Max_tay_gat1;

	if (abs(bientrodaytay1Value - target_tay_gat1) > 3)
	{
		if (bientrodaytay1Value > target_tay_gat1)			Gat_tay1_xuong;
		else																						Gat_tay1_len;

		speed_temp = abs(bientrodaytay1Value - target_tay_gat1)*25;
		if (speed_temp > speed_tay_gat1)
				speed_temp = speed_tay_gat1;
		if (speed_temp < 20)
				speed_temp = 20;
		
		Gat_tay1 = speed_temp;
	}
	else Gat_tay1 = 0;
}
//************************************** gat2 **************************************
void Gat_2()
{
	if (target_tay_gat2 < Min_tay_gat2)
		target_tay_gat2 = Min_tay_gat2;
	if (target_tay_gat2 > Max_tay_gat2)
		target_tay_gat2 = Max_tay_gat2;

	if (abs(bientrodaytay2Value - target_tay_gat2) > 3)
	{
		if (bientrodaytay2Value > target_tay_gat2)			Gat_tay2_len;
		else																						Gat_tay2_xuong;

		speed_temp = abs(bientrodaytay2Value - target_tay_gat2)*25;
		if (speed_temp > speed_tay_gat2)
				speed_temp = speed_tay_gat2;
		if (speed_temp < 20)
				speed_temp = 20;
		
		Gat_tay2 = speed_temp;
	}
	else Gat_tay2 = 0;
}
//************************************** xoay tay kep auto **************************************
	void Xoay_tay_kep()
{
	if (target_xoay_tay < Min_xoay_tay)
		target_xoay_tay = Min_xoay_tay;
	if (target_xoay_tay > Max_xoay_tay)
		target_xoay_tay = Max_xoay_tay;

	if ((abs(bientroxoaytayValue - target_xoay_tay) > 1) && (abs(bientrodaytay1Value - vitri_tay1home) < 15) && (abs(bientrodaytay2Value - vitri_tay2home) < 15))
	{
		if (bientroxoaytayValue > target_xoay_tay)			tay_xoay_thuan;
		else																						tay_xoay_nghich;

		speed_temp = abs(bientroxoaytayValue - target_xoay_tay)*15;
		if (speed_temp > speed_tay_xoay)
				speed_temp = speed_tay_xoay;
		if (speed_temp < 60)
				speed_temp = 60;
	
		tay_xoay = speed_temp;
		Xoay_ok = 0;
	}
	else tay_xoay = 0, Xoay_ok = 1;
}



//********************************Speed nang ****************************
void Nang_cham	(void) {
	speed_chan_sau = 30;
	speed_chan_truoc = 30;
}

void Nang_thuong	(void) {
	speed_chan_sau = 80;
	speed_chan_truoc = 80;
}

void Nang_nhanh	(void) {
	speed_chan_sau = 115;
	speed_chan_truoc = 115;
}

void Nang_cuc_nhanh	(void) {
	speed_chan_sau = 150;
	speed_chan_truoc = 150;
}


void su_dung_chan (int value_chan) {
	Nang_nhanh();
	target_chan_truoc = value_chan ;
	target_chan_sau = value_chan;
}

void su_dung_chan_cham (int value_chan) {
	Nang_cham();

	target_chan_truoc = value_chan ;
	target_chan_sau = value_chan;
}

void su_dung_chan_thuong (int value_chan) {
	Nang_thuong();
	target_chan_truoc = value_chan ;
	target_chan_sau = value_chan;
}

void su_dung_chan_cuc_nhanh (int value_chan) {
	Nang_cuc_nhanh();

	target_chan_truoc = value_chan ;
	target_chan_sau = value_chan;
}
/// ************** VE TAY HOME 2 TAY **************
void ve_home_2_tay (void) {
			speed_tay_gat1 = 250;
			target_tay_gat1 = vitri_tay1home;
			speed_tay_gat2 = 250;
			target_tay_gat2 = vitri_tay2home;
			for(i=0;i<50;i++)	{ 
				while(abs(bientrodaytay1Value - target_tay_gat1) > ((vitri_tay1home- Min_tay_gat1) / 2 ) || abs(bientrodaytay2Value - target_tay_gat2) > ((vitri_tay2home- Min_tay_gat2) / 3 ) )	
				{vTaskDelay(1); if(!wantExit())	break;}
					}
}


void di_tren_buc_khong_thanh_2_ben (void) {
		su_dung_chan(265);
		if (da_lay_tay1 == 0 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
				while( CB_Ha_Sau == 0) {
				if(CB_ROI_3  == 0 && CB_ROI_1 == 0)	robotRunAngle(-400,20,900,0.7);
				else																robotRunAngle(-900,20,900,0.7), Tay2_len;
				vTaskDelay(1);
				if(!wantExit()) break;
					}
				// chay toi roi thi di ngang qua phai
				robotRunAngle(150,10,900,0.7);
				while (CB_ROI_3  == 0 )	 {
					vTaskDelay(1);
					if(!wantExit()) break;
					}
			}
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
				while(CB_Ha_Sau == 0) {
				if(CB_ROI_3  == 0 && CB_ROI_1 == 0)	robotRunAngle(-400,20,900,0.7);
				else																robotRunAngle(-900,20,900,0.7), Tay1_len;
				vTaskDelay(1);
				if(!wantExit()) break;
					}
				// chay toi roi thi di ngang qua phai
				robotRunAngle(150,10,900,0.7);
				while (CB_ROI_3  == 0 )	 {
					vTaskDelay(1);
					if(!wantExit()) break;
					}
				}

		// quay mam sang tay 2
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
				while( CB_Ha_Sau == 0) {
				if(CB_ROI_2  == 0 && CB_ROI_4 == 0)	robotRunAngle(-1550,20,900,0.7);
				else																robotRunAngle(-900,20,900,0.7), Tay2_len;
				vTaskDelay(1);
				if(!wantExit()) break;
							}
				// chay toi roi thi di ngang qua trai
				robotRunAngle(1700,10,900,0.7);
				while (CB_ROI_2  == 0 )	 {
					vTaskDelay(1);
					if(!wantExit()) break;
						}
				}
		
		// quay mam sang tay 3
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 0) {
				while( CB_Ha_Sau == 0) {
				if(CB_ROI_2  == 0 && CB_ROI_4 == 0)	robotRunAngle(-1550,20,900,0.7);
				else																robotRunAngle(-900,20,900,0.7), Tay1_len;
				vTaskDelay(1);
				if(!wantExit()) break;
						}
				// chay toi roi thi di ngang qua trai
				robotRunAngle(1700,10,900,0.7);
				while (CB_ROI_2  == 0 )	 {
					vTaskDelay(1);
					if(!wantExit()) break;
							}
					}
		
		robotRunAngle(-900,10,900,0.7);
		RESET_ENCODER(); 
		while(abs(ENCODER_FR()) + abs(ENCODER_FL()) < 200)	{vTaskDelay (1); if(!wantExit())	break;}
		robotStop(0);	
}

//******************************** leo bac 200 ****************************
void Leo_bac_200(int Angle, int Robot_Angle)
{	
	int i;
	speed_chan_sau = 110;
	speed_chan_truoc = 110;
	
	target_chan_truoc = Min_chan_truoc + 247;
	target_chan_sau = Min_chan_sau + 245;
	
 	for(i=0;i<50;i++)		
	{
		while(abs(bientrochansauValue - target_chan_sau) > 8)	{vTaskDelay(1); if(!wantExit())	break;}
	}
	
	robotRunAngle(Angle,18,Robot_Angle,0.8);
	for(i=0;i<50;i++)	
	{	
		while(CB_Ha_Sau == 1  )	{vTaskDelay(1); if(!wantExit())	break;}
	}

	
	robotRunAngle(Angle,4,Robot_Angle,0.8);
	//// nâng bánh sau lên 
	speed_chan_sau = 250;
	target_chan_sau = Min_chan_sau ;
	for(i=0;i<50;i++)		
	{
			while(abs(bientrochansauValue - target_chan_sau) > 8)	{vTaskDelay(1); if(!wantExit())	break;}
	}
	
	
	robotSetACC(50, 65); // gia toc nhanh
	
	robotRunAngle(Angle,50,Robot_Angle,0.8);
	
	for(i=0;i<1000;i++)	
	{	
		while(CB_ROI_1 == 1  && CB_ROI_4 == 1)	{vTaskDelay(1); if(!wantExit())	break;}
	}

	robotRunAngle(Angle,30,Robot_Angle,0.5);
	
	for(i=0;i<550;i++)	
	{	
		while(CB_bung_duoi == 1)	{vTaskDelay(1); if(!wantExit())	break;}
	}
	speed_chan_sau = 40;
	target_chan_sau = Min_chan_sau + 14;
	
	robotSetACC(120, 85); // gia toc

	robotRunAngle(Angle,8,Robot_Angle,0.5);
		for(i=0;i<1000;i++)	
	{	
		while(CB_bung == 1)	{vTaskDelay(1); if(!wantExit())	break;}
	}
	
//  robotStop(0);
	
	
	robotRunAngle(Angle,4,Robot_Angle,0.5);
	speed_chan_truoc = 250;
	target_chan_truoc = Min_chan_truoc + 5;


	for(i=0;i<250;i++)	
	{
		while(abs(bientrochantruocValue - target_chan_truoc) > 8)	{vTaskDelay(1); if(!wantExit())	break;}
	}
	
	robotRunAngle(Angle,20,Robot_Angle,0.6);
	for(i=0;i<2550;i++)	
	{
	while(CB_ROI_2 == 1  && CB_ROI_3 == 1)	{vTaskDelay(1); if(!wantExit())	break;}
	}
	RESET_ENCODER(); 
	while(abs(ENCODER_FR()) + abs(ENCODER_FL()) < 420)	{vTaskDelay (1); if(!wantExit())	break;}

	for(i=0;i<2550;i++)	
	{
	while(CB_vtri_leo_dau == 1)	{vTaskDelay(1); if(!wantExit())	break;}
	}
	
  Nang_nhanh();
	target_chan_truoc = 265, target_chan_sau = 265;
	
	robotRunAngle(Angle,20,Robot_Angle,0.6);

	for(i=0;i<100;i++) 
		{
		while(CB_Ha_Dau == 1)		{vTaskDelay(1); if(!wantExit())	break;}
		}

	robotStop(0);
}



void MD_qua_trai_phai_len_bac_200 (int goc_quay_ngang,int goc_quay_thang, int di_Cheo, int time_lui, int giu_dau, int Angle, int Robot_Angle) {
		robotStop(0);
		robotRunAngle(di_Cheo, 16, giu_dau,0.7);
		vTaskDelay (time_lui); 
		robotStop(0);
		robotRotateQuick(goc_quay_ngang, 1.6, 0, 0.3, 300); 
		robotStop(0);
		Nang_nhanh();
		target_chan_truoc = Min_chan_truoc + 250;
		target_chan_sau = Min_chan_sau + 250;
		
		for(i=0;i<50;i++)		
		{
			while(abs(bientrochansauValue - target_chan_sau) > 15)	{vTaskDelay(1); if(!wantExit())	break;}
		}
		
		robotRunAngle(Angle,20,Robot_Angle,0.8);
		for(i=0;i<150;i++)	
		{	
			while(CB_Ha_Sau == 1  )	{vTaskDelay(1); if(!wantExit())	break;}
		}
		
		robotRunAngle(Angle,14,Robot_Angle,0.8);
		for(i=0;i<150;i++)	
		{	
			while(CB_Ha_Sau == 1  || CB_Cap_Thanh_Sau == 0)	{vTaskDelay(1); if(!wantExit())	break;}
		}

		
		
		/// bat cam check khoi ben canh
		if (bat_bien_check_r1_ngang == 1) {
				dung_cho_khoi_r1_ben_canh();
		}
	
		Leo_bac_200(Angle, Robot_Angle);
		robotStop(0);
		robotRotateQuick(goc_quay_thang, 1.6, 0, 0.3, 300); 
		robotStop(0);
}

void MD_qua_trai_phai_xuong_bac_200 (int goc_quay_ngang,int goc_quay_thang, int di_Cheo, int time_lui, int giu_dau, int Angle, int Robot_Angle) {
		robotStop(0);
		su_dung_chan_thuong(350);
		robotStop(0);
		robotRunAngle(di_Cheo, 16, giu_dau,0.5);
		vTaskDelay (time_lui); 
		robotStop(0);
		robotRotateQuick(goc_quay_ngang, 1.6, 0, 0.3, 300);
		robotStop(0);
				
		su_dung_chan(265);
		for(i=0;i<50;i++)		
		{
			while(abs(bientrochansauValue - target_chan_sau) > 40)	{vTaskDelay(1); if(!wantExit())	break;}
		}
		
			robotRunAngle(Angle,18,Robot_Angle,0.7);

		for(i=0;i<1000;i++)
		{	
			while(CB_Ha_Sau == 0 ) {
					vTaskDelay(1); if(!wantExit())	break;
			}
		}
		
		/// bat cam check khoi ben canh
		if (bat_bien_check_r1_ngang == 1) {
				dung_cho_khoi_r1_ben_canh();
		}
				
		Xuong_bac_200(Angle, Robot_Angle);
		robotStop(0);
		robotRotateQuick(goc_quay_thang, 1.6, 0, 0.3, 300);
		robotStop(0);
}



void chuan_bi_thang_xanh_2(void) {
		int vitri_tay41 = vitri_tay41_laser_trai_GapQua + 9;
		int vitri_tay23 = vitri_tay23_phai_laser_GapQua + 9;
		su_dung_chan(565);
		if (da_lay_tay1 == 0 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
					for(i=0;i<1550;i++) {
						
					while( CB_Cap_Thanh_Sau == 0 ||  (abs(bientrochansauValue - target_chan_sau) > 30))	
					{	
					if(lazeTraiValue > vitri_tay41)			robotRunAngle(-600,18,900,0.7);
					else																robotRunAngle(-900,12,900,0.7), Tay2_len;
					vTaskDelay(1);
					if(!wantExit()) break;
								}
					
						}
					}
			
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
					for(i=0;i<1550;i++) {
					while( CB_Cap_Thanh_Sau == 0 ||  (abs(bientrochansauValue - target_chan_sau) > 30))	
					{	
					if(lazeTraiValue > vitri_tay41)			robotRunAngle(-600,18,900,0.7);
					else																robotRunAngle(-900,12,900,0.7), Tay1_len;
					vTaskDelay(1);
					if(!wantExit()) break;
								}
					
						}
			}

		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
						for(i=0;i<1550;i++) {
						while( CB_Cap_Thanh_Sau == 0 ||  (abs(bientrochansauValue - target_chan_sau) > 30))	
						{	
						if(lazePhaiValue > vitri_tay23)			robotRunAngle(-1550,18,900,0.7), Tay2_len;
						else																robotRunAngle(-900,12,900,0.7), Tay2_len;
						vTaskDelay(1);
						if(!wantExit()) break;
									}
						
							}
						}
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 0) {
						for(i=0;i<1550;i++) {
						while( CB_Cap_Thanh_Sau == 0 ||  (abs(bientrochansauValue - target_chan_sau) > 30))	
						{	
						if(lazePhaiValue > vitri_tay23)			robotRunAngle(-1550,18,900,0.7), Tay1_len;
						else																robotRunAngle(-900,12,900,0.7), Tay1_len;
						vTaskDelay(1);
						if(!wantExit()) break;
									}
						
							}
						}
			robotStop(0); 	
}

void Leo_bac_200_bam_thanh_phai(void)
{	
	Leo_bac_200(-900, 900);
	Nang_thuong();
	target_chan_truoc = Min_chan_truoc + 250;
	target_chan_sau = Min_chan_sau + 250;

	if (TinHieu_ChuanBi_GapThang == 0 && TinHieu_ChuanBi_GapTrai == 0 && TinHieu_ChuanBi_GapPhai == 0) {
					robotRunAngle(-900,21,900,0.7);
				for(i=0;i<1550;i++)
						{
							while(CB_Ha_Sau == 1  || (abs(bientrochansauValue - target_chan_sau) > 50))	
							{	
								vTaskDelay (1);
								if(!wantExit())	break;
							}
						}

					}
		
	else if (TinHieu_ChuanBi_GapThang == 1) {		
				chuan_bi_thang_xanh_2();
		}
		else if (TinHieu_ChuanBi_GapPhai == 1) {		
				chuan_bi_gap_phai_200_tren_3();
		}
		else if (TinHieu_ChuanBi_GapTrai == 1) {		
				chuan_bi_gap_trai_200_tren_1();
		}
		
//		robotStop(0); 					
}


void chuan_bi_gap_trai_200_tren_8 (void ) {
	
	if (da_lay_tay1 == 0 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
			ha_sat_xuong;
			for(i=0;i<250;i++)	
				{
					while(abs(bientrochansauValue - target_chan_sau) > 10)	{vTaskDelay(1); if(!wantExit())	break;}
				}
				
			robotRunAngle(1800,5,900,0.5);
					for(i=0;i<150;i++)
					{
						while(CB_ROI_2 == 0)	
						{	
							vTaskDelay (1);
							if(!wantExit())	break;
						}
					}
						robotStop(0);
			}
	
			//// dung tay 3 gap duoi lan 2
		else if (da_lay_tay1 == 1 && da_lay_tay4_duoi == 0) {
					ha_sat_xuong;
					for(i=0;i<250;i++)	
						{
							while(abs(bientrochansauValue - target_chan_sau) > 10)	{vTaskDelay(1); if(!wantExit())	break;}
						}	
					robotRunAngle(-900,5,900,0.5);
			
					for(i=0;i<1550;i++)
						{
							while (CB_Ha_Sau == 0 )	
							{	
								if(!wantExit())	break;
								vTaskDelay (1);
							}
						}
			robotStop(0); 
						
			robotRunAngle(1800,5,900,0.5);
					for(i=0;i<150;i++)
					{
						while(CB_ROI_2 == 0)	
						{	
							vTaskDelay (1);
							if(!wantExit())	break;
						}
					}
					robotStop(0);
				}
}

///// ********* leo bac 200 khong thanh **************
void Leo_bac_200_ko_thanh(void)
{	
		Leo_bac_200(-900, 900);
		su_dung_chan(265);
	
	if (TinHieu_ChuanBi_GapThang == 0 && TinHieu_ChuanBi_GapTrai == 0 && TinHieu_ChuanBi_GapPhai == 0 && TinHieu_QuaPhai == 0 && TinHieu_QuaTrai == 0){
		robotRunAngle(-900,28,900,0.7);
		for(i=0;i<1550;i++)
				{
						while(CB_Ha_Sau == 0 || (abs(bientrochansauValue - target_chan_sau) > 30))	
				
					{	
						if(!wantExit())	break;
						vTaskDelay (1);
					}
				}
				
//		robotStop(0);
			}
		else if (TinHieu_ChuanBi_GapThang == 1) {
					di_tren_buc_khong_thanh_2_ben();
		}
	// CO LENH GAP TRAI
		else if (TinHieu_ChuanBi_GapTrai == 1 ) {
					chuan_bi_gap_trai_200_duoi_ko_thanh();
		}
		// CO LENH GAP PHAI
		else if (TinHieu_ChuanBi_GapPhai == 1 ) {
					chuan_bi_gap_phai_200_duoi_ko_thanh();
		}
//		robotStop(0); 	
}

//***************** leo bac 200 bam thanh laser trai + laser truoc *************



//******************************** leo bac 400 ****************************
void Leo_bac_400(int Angle, int Robot_Angle)
{	
	int i;
	
	Nang_nhanh();
	
	target_chan_truoc = Max_chan_truoc - 27, target_chan_sau = Max_chan_sau - 27;
	
	for(i=0;i<250;i++)	
	{
		while(abs(bientrochansauValue - target_chan_sau) > 8)	{vTaskDelay(1); if(!wantExit())	break;}
	}

	robotRunAngle(Angle,12,Robot_Angle,0.6);
	
	for(i=0;i<150;i++)	
	{	
		while(CB_Ha_Sau == 1 ||  CB_Cap_Thanh_Sau == 0)	{vTaskDelay(1); if(!wantExit())	break;}
	}

	robotStop(0); 
//	
	speed_chan_sau = 250;
	target_chan_sau = Min_chan_sau ;

	for(i=0;i<50;i++)		
	{
		while(abs(bientrochansauValue - target_chan_sau) > 8)	{vTaskDelay(1); if(!wantExit())	break;}
	}
	
	robotSetACC(65, 80); // gia toc nhanh
	
	robotRunAngle(Angle,50,Robot_Angle,0.6);
	for(i=0;i<1050;i++)	
	{	
		while(CB_ROI_1 == 1  && CB_ROI_4 == 1)	{vTaskDelay(1); if(!wantExit())	break;}
	}
	
	robotRunAngle(Angle,30,Robot_Angle,0.6);
	
	for(i=0;i<550;i++)	
	{	
		while(CB_bung_duoi == 1)	{vTaskDelay(1); if(!wantExit())	break;}
	}
	
	speed_chan_sau = 40;
	target_chan_sau = Min_chan_sau + 10;
	
	robotSetACC(120, 85); // gia toc nhanh
	
	robotRunAngle(Angle,10,Robot_Angle,0.8);
	for(i=0;i<1000;i++)	
	{	
		while(CB_bung == 1)	{vTaskDelay(1); if(!wantExit())	break;}
	}
	
  robotStop(0);
	speed_chan_truoc = 250;
	target_chan_truoc = Min_chan_truoc + 5 ;

	for(i=0;i<250;i++)	
	{
		while(abs(bientrochantruocValue - target_chan_truoc) > 10)	{vTaskDelay(1); if(!wantExit())	break;}
	}
	
	
	robotRunAngle(Angle,20,Robot_Angle,0.6);
	for(i=0;i<150;i++)	
	{
	while(CB_ROI_2 == 1  && CB_ROI_3 == 1)	{vTaskDelay(1); if(!wantExit())	break;}
	}

	RESET_ENCODER(); 
	while(abs(ENCODER_FR()) + abs(ENCODER_FL()) < 400)	{vTaskDelay (1); if(!wantExit())	break;}
	
	for(i=0;i<2550;i++)	
	{
	while(CB_vtri_leo_dau == 1)	{vTaskDelay(1); if(!wantExit())	break;}
	}

  Nang_nhanh();
	target_chan_truoc = 265, target_chan_sau = 265;
	
	robotRunAngle(Angle,18,Robot_Angle,0.5);

	for(i=0;i<100;i++) 
		{
		while(CB_Ha_Dau == 1)		{vTaskDelay(1); if(!wantExit())	break;}
		}
		
	robotStop(0);
}


void Leo_bac_400_ko_thanh(void)
{		
		Leo_bac_400(-900, 900);
		su_dung_chan(265);
		
		if (TinHieu_ChuanBi_GapThang == 0 && TinHieu_ChuanBi_GapTrai == 0 && TinHieu_ChuanBi_GapPhai == 0) {
		// chay toi khi mat cam bien sau
		robotRunAngle(-900,25,900,0.9);
		for(i=0;i<250;i++)
				{
						while(CB_Ha_Sau == 0 ||  (abs(bientrochansauValue - target_chan_sau) > 10))	

					{	
						vTaskDelay (1);
						if(!wantExit())	break;
					}
				}

//		robotStop(0);
			}
				
	else if (TinHieu_ChuanBi_GapThang == 1 ) {
			di_tren_buc_khong_thanh_2_ben();
		}
	else if (TinHieu_ChuanBi_GapPhai == 1 ) {
		chuan_bi_gap_phai_200_duoi_ko_thanh();
		}
//		robotStop(0); 	

}

void chuan_bi_gap_thang_xanh_3(void) {
		su_dung_chan(565);
		if (da_lay_tay1 == 0 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
				while(CB_Cap_Thanh_Sau == 0 || (abs(bientrochansauValue - target_chan_sau) > 100))	 {
				if(CB_ROI_3  == 0 && CB_ROI_1 == 0)	robotRunAngle(-450,18,900,0.7);
				else																robotRunAngle(-900,12,900,0.7), Tay2_len;
				vTaskDelay(1);
				
				if(!wantExit()) break;
					}
				}
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
				while(CB_Cap_Thanh_Sau == 0 || (abs(bientrochansauValue - target_chan_sau) > 100))	 {
				if(CB_ROI_3  == 0 && CB_ROI_1 == 0)	robotRunAngle(-450,18,900,0.7);
				else																robotRunAngle(-900,12,900,0.7), Tay1_len;
				vTaskDelay(1);
				
				if(!wantExit()) break;
					}
				}

		// quay mam sang tay 2
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
				while(CB_Cap_Thanh_Sau == 0 || (abs(bientrochansauValue - target_chan_sau) > 100))	 {
				if(CB_ROI_4  == 0 && CB_ROI_2 == 0)	robotRunAngle(-1550,18,900,0.7);
				else																robotRunAngle(-900,12,900,0.7), Tay2_len;
				vTaskDelay(1);
				
				if(!wantExit()) break;
					}
				}
		// quay mam sang tay 3
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 0) {
				while(CB_Cap_Thanh_Sau == 0 || (abs(bientrochansauValue - target_chan_sau) > 100))	 {
				if(CB_ROI_4  == 0 && CB_ROI_2 == 0)	robotRunAngle(-1550,18,900,0.7);
				else																robotRunAngle(-900,12,900,0.7), Tay1_len;
				vTaskDelay(1);
				
				if(!wantExit()) break;
						}
					}
		robotStop(0);
}

void Leo_bac_400_co_thanh(void) {
		Leo_bac_400(-900, 900);
	
		if (TinHieu_ChuanBi_GapThang == 0 && TinHieu_ChuanBi_GapTrai == 0 && TinHieu_ChuanBi_GapPhai == 0) {
			su_dung_chan(480);

			// chay toi khi laser sau cham 1
			robotRunAngle(-900,22,900,0.7);
			for(i=0;i<1550;i++)
					{
						while(CB_Ha_Sau == 1  || (abs(bientrochansauValue - target_chan_sau) > 10))	
						{	
							vTaskDelay (1);
							if(!wantExit())	break;
						}
					}

	}
		
		else if (TinHieu_ChuanBi_GapThang == 1) {
			chuan_bi_gap_thang_xanh_3();
		}

		// CO LENH GAP TRAI
		else if (TinHieu_ChuanBi_GapTrai == 1 ) {
					chuan_bi_gap_trai_200_duoi_5();
		}

}


void test_dung (int Angle, int Robot_Angle) {

	int i;
	Nang_thuong();
	
	target_chan_truoc = Min_chan_truoc + 3, target_chan_sau = Min_chan_sau + 3;
	for(i=0;i<50;i++)		
	{
		while(abs(bientrochansauValue - target_chan_sau) > 10)	{vTaskDelay(1); if(!wantExit())	break;}
	}
	
	robotRunAngle(Angle,25,Robot_Angle,0.7);

	for(i=0;i<1000;i++)
	{	
		while(CB_Ha_Sau == 0 ) {
				vTaskDelay(1); if(!wantExit())	break;
		}
	}
	robotStop(0);

}
	


////******************************** xuong bac 200 ****************************88
void Xuong_bac_200(int Angle, int Robot_Angle)
{	
	int i;
	Nang_thuong();
	
	target_chan_truoc = Min_chan_truoc + 5, target_chan_sau = Min_chan_sau + 3;
	for(i=0;i<50;i++)		
	{
		while(abs(bientrochansauValue - target_chan_sau) > 10)	{vTaskDelay(1); if(!wantExit())	break;}
	}
	
	robotRunAngle(Angle,28,Robot_Angle,0.7);

	for(i=0;i<1000;i++)
	{	
		while(CB_Ha_Sau == 0 ) {
				vTaskDelay(1); if(!wantExit())	break;
		}
	}
	robotRunAngle(Angle,18,Robot_Angle,0.7);

	for(i=0;i<500;i++)
	{			while(CB_Ha_Sau == 0 ||  (CB_ROI_1 == 0  && CB_ROI_4 == 0)) {
				vTaskDelay(1); if(!wantExit())	break;
		}
	}
	
	speed_chan_sau = 250;
	target_chan_sau = Min_chan_sau + 245;
	
	
	robotRunAngle(Angle,40,Robot_Angle,0.5);
	for(i=0;i<550;i++)	
	{	
		while(CB_bung_duoi == 0)	{vTaskDelay(1); if(!wantExit())	break;}
	}

	robotRunAngle(Angle,25,Robot_Angle,0.5);
	for(i=0;i<550;i++)	
	{	
		while(CB_bung == 0)	{vTaskDelay(1); if(!wantExit())	break;}
	}

	robotRunAngle(Angle,15,Robot_Angle,0.4);

	{	
		while( CB_vtri_leo_dau == 0 || CB_bung == 0)	{vTaskDelay(1); if(!wantExit())	break;}
	}
	
	speed_chan_truoc = 250;
	target_chan_truoc = Min_chan_truoc + 245;

	robotRunAngle(Angle,10,Robot_Angle,0.5);
	
	for(i=0;i<100;i++)	
 	{
		while(CB_Ha_Dau == 0)		{vTaskDelay(1); if(!wantExit())	break;}
	}
	
	robotRunAngle(Angle,16,Robot_Angle,0.5);
	RESET_ENCODER(); 
	while(abs(ENCODER_FR()) + abs(ENCODER_FL()) < 380)	{vTaskDelay (1); if(!wantExit())	break;}
	robotStop(0);

}

void test_xuong_bac_3_lan (void) {
		Xuong_bac_200	(900, -900);
//		robotStop(0);
	
		su_dung_chan(265);
				// chay toi khi mat cam bien sau
				robotRunAngle(900,20,-900,0.5);
				for(i=0;i<1550;i++)
						{
								while(CB_Ha_Sau == 0 || (abs(bientrochansauValue - target_chan_sau) > 20))	
							{	
								if(!wantExit())	break;
								vTaskDelay (1);
							}
						}
//		robotStop(0);
		Xuong_bac_200	(900, -900);
		su_dung_chan(265);
				// chay toi khi mat cam bien sau
				robotRunAngle(900,20,-900,0.5);
				for(i=0;i<1550;i++)
						{
								while(CB_Ha_Sau == 0 || (abs(bientrochansauValue - target_chan_sau) > 20))	
							{	
								if(!wantExit())	break;
								vTaskDelay (1);
							}
						}
//		robotStop(0);
		Xuong_bac_200	(900, -900);

}
	
void xuong_bac_200_xanh_10 (void) {
	Xuong_bac_200(-900, 900);
	
		if (TinHieu_ChuanBi_GapThang == 0 && TinHieu_ChuanBi_GapTrai == 0 && TinHieu_ChuanBi_GapPhai == 0 && TinHieu_QuaPhai == 0) {
				// chay toi khi mat cam bien sau
				su_dung_chan(265);
				robotRunAngle(-900,28,900,0.7);
				for(i=0;i<1550;i++)
						{
								while(CB_Ha_Sau == 0 || (abs(bientrochansauValue - target_chan_sau) > 30))	
							{	
								if(!wantExit())	break;
								vTaskDelay (1);
							}
						}
					}

		else if (TinHieu_ChuanBi_GapPhai == 1) {
					chuan_bi_gap_phai_200_tren_7_10();
			}
//			robotStop(0);
	}	


void xuong_bac_200_end(void) {
		Xuong_bac_200(-900, 900);
		
		if (TinHieu_ChuanBi_GapThang == 0 && TinHieu_ChuanBi_GapTrai == 0 && TinHieu_ChuanBi_GapPhai == 0 && TinHieu_QuaPhai == 0 && TinHieu_QuaTrai == 0) {
				// chay toi khi mat cam bien sau
				su_dung_chan(265);
				robotRunAngle(-900,22,900,0.5);
				for(i=0;i<1550;i++)
						{
								while(CB_Ha_Sau == 0|| (abs(bientrochansauValue - target_chan_sau) > 30))	
							{	
								if(!wantExit())	break;
								vTaskDelay (1);
							}
						}
						
//				robotStop(0);
			
			}
	
		else if (TinHieu_ChuanBi_GapTrai == 1 ) {
				chuan_bi_gap_trai_200_duoi_ko_thanh();
		}
		// CO LENH GAP PHAI
		else if (TinHieu_ChuanBi_GapPhai == 1 ) {
					chuan_bi_gap_phai_200_duoi_ko_thanh();
		}
//		robotStop(0); 	
}

// qua trai len 400 o cua vao rung
void qua_trai_len_bac_400(void) {
	su_dung_chan(720);
	
	for(i=0;i<150;i++)		
	{
		while(abs(bientrochansauValue - target_chan_sau) > 15)	{vTaskDelay(1); if(!wantExit())	break;}
	}
	vTaskDelay(1000);
//	for(i=0;i<1050;i++)	
//	{	
//		while( lazePhaiValue < 230)	{vTaskDelay(1); if(!wantExit())	break;}
//	}
	robotStop(0);
	chinh_lai_vi_tri_laser_phai_custom(vi_tri_cua_rung_xanh_1_lazer_phai_tay_41 , 1000, 10, 50, 2);
	
	robotRunAngle(-900,14,900,0.6);
	for(i=0;i<1050;i++)	
	{	
		while(CB_Cap_Thanh_Sau == 0)	{vTaskDelay(1); if(!wantExit())	break;}
	}
	robotStop(50);

}

//============== Sang phai lên bac 400 o ria rung ===================

void qua_phai_len_bac_400(void) {
	su_dung_chan(720);
	
	for(i=0;i<150;i++)		
	{
		while(abs(bientrochansauValue - target_chan_sau) > 15)	{vTaskDelay(1); if(!wantExit())	break;}
	}
	vTaskDelay(1000);

	chinh_lai_vi_tri_laser_phai_custom(vi_tri_cua_rung_xanh_3_lazer_phai_tay_41 , 1000, 10, 50, 2);
	
	robotStop(0);
	robotRunAngle(-900,14,900,0.8);
	for(i=0;i<1050;i++)	
	{	
		while(CB_Cap_Thanh_Sau == 0)	{vTaskDelay(1); if(!wantExit())	break;}
	}

	robotStop(50);

}
//============== Sang trai lên bac 200 o ria ===================
void qua_trai_len_bac_200_cua_vao(void) {
	su_dung_chan(720);
	for(i=0;i<150;i++)		
	{
		while(abs(bientrochansauValue - target_chan_sau) > 15)	{vTaskDelay(1); if(!wantExit())	break;}
	}
	
	for(i=0;i<1050;i++)	
	{	
		while( lazePhaiValue < 320)	{vTaskDelay(1); if(!wantExit())	break;}
	}   
	vTaskDelay(4000);
	robotStop(0);
	if ( TinHieu_ChuanBi_GapThang == 1 ) {
				run_encoder(10000, 1800, 900, 45, 5, 4000, 50);
				robotRunAngle(-900,15,900,0.8);
				for(i=0;i<1050;i++)	
				{	
					while( CB_Cap_Thanh_Sau == 0)	{vTaskDelay(1); if(!wantExit())	break;}
				}
			}
		
	else if  ( TinHieu_ChuanBi_GapThang == 0 ) {
			if (chay_ngang_qua_o1_xanh == 0) {
					run_encoder(10000, 1800, 900, 45, 5, 5000, 50);
					robotStop(0);
			}
			else if (chay_ngang_qua_o1_xanh == 1) {

					run_encoder(20700, 1800, 900, 45, 12, 5000, 50);
					robotStop(0);

					}
				}
		
	robotStop(0);
}

//============== Sang phai lên bac 200 o ria ===================
void qua_phai_len_bac_200_cua_vao(void) {
	su_dung_chan(720);
		for(i=0;i<150;i++)		
	{
		while(abs(bientrochansauValue - target_chan_sau) > 15)	{vTaskDelay(1); if(!wantExit())	break;}
	}
	
	robotRunAngle(750,10,900,0.6);
	vTaskDelay(3500);
	robotStop(20);
	for(i=0;i<1050;i++)	
	{	
		while( lazeTraiValue < 320)	{vTaskDelay(1); if(!wantExit())	break;}
	}
	vTaskDelay(4000);
	robotStop(0);
	if ( TinHieu_ChuanBi_GapThang == 1 ) {
				run_encoder(10000, 0, 900, 45, 5, 4000, 100);
				robotStop(0);

				robotRunAngle(-900,15,900,0.6);
				for(i=0;i<1050;i++)	
				{	
					while( CB_Cap_Thanh_Sau == 0)	{vTaskDelay(1); if(!wantExit())	break;}
				}
			}
		
		else if  ( TinHieu_ChuanBi_GapThang == 0 ) {
			if (chay_ngang_qua_o3_xanh == 0) {

					run_encoder(10000, 0, 900, 45, 5, 4000, 100);
				
					robotStop(0);

			}
			else if (chay_ngang_qua_o3_xanh == 1) {

						run_encoder(20700, -30, 900, 45, 12, 5000, 100);
				
						robotStop(0);

						}
				}
		robotStop(10);
		bai_db = 1;

}

void moqua(void) {
	

		speed_tay_gat1 = 140;
		target_tay_gat1 = 300;

		speed_tay_gat2 = 140;
		target_tay_gat2 = 500;

		Kep_phai_4_ra;
		vTaskDelay(1000);
		Kep_phai_1_ra;
		vTaskDelay(1000);
		Kep_phai_2_ra;
		vTaskDelay(1000);
		Kep_phai_3_ra;
		vTaskDelay(1000);
}

//************************************** xuong bac 400 ************************************
	void Xuong_bac_400 (int Angle, int Robot_Angle)
{	
	int i;
	Nang_nhanh();
	
	target_chan_truoc = Min_chan_truoc + 5, target_chan_sau = Min_chan_sau + 5;
	for(i=0;i<50;i++)		
	{
		while(abs(bientrochansauValue - target_chan_sau) > 8)	{vTaskDelay(1); if(!wantExit())	break;}
	}
	
	robotRunAngle(Angle,22,Robot_Angle,0.5);

	for(i=0;i<1000;i++)
	{	
		while(CB_Ha_Sau == 0 )
				{vTaskDelay(1); if(!wantExit())	break;}
	}
	
	robotRunAngle(Angle,15,Robot_Angle,0.4);

	for(i=0;i<1000;i++)
	{	
		while(CB_Ha_Sau == 0 || (CB_ROI_1 == 0  && CB_ROI_4 == 0))
				{vTaskDelay(1); if(!wantExit())	break;}
	}

	robotStop(5);

	speed_chan_sau = 230;
	target_chan_sau = Max_chan_sau - 27;
	
	for(i=0;i<250;i++)		
	{
		while(abs(bientrochansauValue - target_chan_sau) > 20)	{vTaskDelay(1); if(!wantExit())	break;}
	}
	robotStop(0);
	
	robotRunAngle(Angle,35,Robot_Angle,0.3);
	for(i=0;i<550;i++)	
	{	
		while(CB_bung_duoi == 0)	{vTaskDelay(2); if(!wantExit())	break;}
	}
	
	robotRunAngle(Angle,25,Robot_Angle,1);
	
	for(i=0;i<550;i++)	
	{	
		while(CB_bung == 0)	{vTaskDelay(1); if(!wantExit())	break;}
	}

	robotRunAngle(Angle,12,Robot_Angle,0.4);
	for(i=0;i<1000;i++)	
	{	
		while( CB_vtri_leo_dau == 0)	{vTaskDelay(1); if(!wantExit())	break;}
	}
	
	robotStop(20);

	speed_chan_truoc = 230;
	target_chan_truoc = Max_chan_truoc - 27;
	
	for(i=0;i<50;i++)		
	{
		while(abs(bientrochantruocValue - target_chan_truoc) > 10)	{vTaskDelay(1); if(!wantExit())	break;}
	}
	
	robotStop(5);
	robotStop(0);
	
	robotRunAngle(Angle,12,Robot_Angle,0.3);
	for(i=0;i<500;i++)	
		{
		while(CB_Ha_Dau == 0)		{vTaskDelay(1); if(!wantExit())	break;}
		}
		
	robotRunAngle(Angle,18,Robot_Angle,0.3);
	RESET_ENCODER(); 
	while(abs(ENCODER_FR()) + abs(ENCODER_FL()) < 450)	{vTaskDelay (5); if(!wantExit())	break;}
	
	robotStop(5);

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
		robotRunAngle(runangle - fix, speed, AngleHead, 0.5);
	}
	else if (lazePhaiValue - lazer_stable_phai > num_change_stable)
	{
		robotRunAngle(runangle + fix, speed, AngleHead, 0.5);
	}
	else
		robotRunAngle(runangle, speed, AngleHead, 0.5);
}

void Bam_thanh_laser_phai_cua_vao(int speed, int runangle, int AngleHead, int lazer_stable_phai, int num_change_stable, int fix_max,int rat)
{
	int fix;

	fix = abs(lazePhaiValue - lazer_stable_phai) * rat;

	if (fix > fix_max)
	fix = fix_max;

	if (lazePhaiValue - lazer_stable_phai < num_change_stable)
	{
		robotRunAngle(runangle + fix, speed, AngleHead, 0.5);
	}
	else if (lazePhaiValue - lazer_stable_phai > num_change_stable)
	{
		robotRunAngle(runangle - fix, speed, AngleHead, 0.5);
	}
	else
		robotRunAngle(runangle, speed, AngleHead, 0.5);
}


//********************************************* bam thanh laser trai ********************************************
void Bam_thanh_laser_trai(int speed, int runangle, int AngleHead, int lazer_stable_phai, int num_change_stable, int fix_max,int rat)
{
	int fix;

	fix = abs(lazeTraiValue - lazer_stable_phai) * rat;

	if (fix > fix_max)
	fix = fix_max;

	if (lazeTraiValue - lazer_stable_phai < num_change_stable)
	{
		robotRunAngle(runangle - fix, speed, AngleHead, 0.3);
	}
	else if (lazeTraiValue - lazer_stable_phai > num_change_stable)
	{
		robotRunAngle(runangle + fix, speed, AngleHead, 0.3);
	}
	else
		robotRunAngle(runangle, speed, AngleHead, 0.3);
}

void Bam_thanh_laser_trai_cua_vao(int speed, int runangle, int AngleHead, int lazer_stable_phai, int num_change_stable, int fix_max,int rat)
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


//********************************************* bam thanh laser sau ********************************************
void Bam_laser_sau(int speed, int runangle, int AngleHead, int lazer_stable_sau, int num_change_stable, int fix_max,int rat)
{
	int fix;

	fix = abs(lazeSauValue - lazer_stable_sau) * rat;

	if (fix > fix_max)
	fix = fix_max;

	if (lazeSauValue - lazer_stable_sau < num_change_stable)
	{
		robotRunAngle(runangle - fix, speed, AngleHead, 0.7);
	}
	else if (lazeSauValue - lazer_stable_sau > num_change_stable)
	{
		robotRunAngle(runangle + fix, speed, AngleHead, 0.7);
	}
	else
		robotRunAngle(runangle, speed, AngleHead, 0.7);
}


//******************************* XOAY bang tayu **************************
void Xoay_tay_Manual(void)
{
	if (SQUARE && !R1 && !R2 && !L2 && bientroxoaytayValue > Min_xoay_tay ) 				
	{
		if(L1 && bientroxoaytayValue < Max_xoay_tay - 20)	tay_xoay = 120;
		else		tay_xoay = 35;
		tay_xoay_thuan;
		target_xoay_tay = bientroxoaytayValue;
		Man_xoay_tay = 1;
	}
	else	if (O && !R1 && !R2 && !L2 && bientroxoaytayValue < Max_xoay_tay) 	
				{
					if(L1 && bientroxoaytayValue > Min_xoay_tay + 20)	tay_xoay = 120;
					else		tay_xoay = 35;
					tay_xoay_nghich;
					target_xoay_tay = bientroxoaytayValue;
					Man_xoay_tay = 1;
				}
	else Man_xoay_tay = 0,tay_xoay = 0;
}
//******************************* nang ha 1 bang tay **************************
void Nang_Ha_tay1_Manual(void)
{
	if (LJOY && !R1 && !R2 && !L2 && bientrodaytay1Value < Max_tay_gat1) 				
	{
		if(L1 && bientrodaytay1Value > Min_tay_gat1 + 20)	Gat_tay1 = 150;
		else		Gat_tay1 = 50;
		Gat_tay1_len;
		target_tay_gat1 = bientrodaytay1Value;
		Man_gat1 = 1;
	}
	else	if (RJOY && !R1 && !R2 && !L2 && bientrodaytay1Value > Min_tay_gat1) 	
				{
		if(L1 && bientrodaytay1Value < Max_tay_gat1 - 20)	Gat_tay1 = 150;
	 	else		Gat_tay1 = 50;
					
		Gat_tay1_xuong;
		target_tay_gat1 = bientrodaytay1Value;
		Man_gat1 = 1;
				}
	else Man_gat1 = 0;
}
//******************************* nang ha 2 bang tay **************************
void Nang_Ha_tay2_Manual(void)
{
	if (TRIANGLE && !R1 && !R2 && !L2 && bientrodaytay2Value > Min_tay_gat2 ) 				
	{
		if(L1 && bientrodaytay2Value < Max_tay_gat2 - 20)	Gat_tay2 = 150;
	 	else		Gat_tay2 = 50;
		Gat_tay2_len;
		target_tay_gat2 = bientrodaytay2Value;
		Man_gat2 = 1;
	}
	else	if (X && !R1 && !R2 && !L2 && bientrodaytay2Value < Max_tay_gat2) 	
				{
		if(L1 && bientrodaytay2Value > Min_tay_gat2 + 20)	Gat_tay2 = 150;
		else	Gat_tay2 = 50;
		Gat_tay2_xuong;
		target_tay_gat2 = bientrodaytay2Value;
		Man_gat2 = 1;
				}
	else Man_gat2 = 0;
}

// ************* roi khoi dung thi tay ve home ***************
void vuot_rung_ve_homeTay_bac_400 (void) {
	Xuong_bac_400(-900, 900);
	robotRunAngle(-900,10,900,0.8);
	vTaskDelay (3000);
	robotStop(0);
	mode_chay_rung = 0;
	hoan_thanh_chay_rung = 1;
	vi_tri_chay_ngang_xanh = 11;

}

void vuot_rung_ve_homeTay_bac_200_12 (void) {
	Xuong_bac_200(-900, 900);
	robotRunAngle(-900,10,900,0.8);
	vTaskDelay (3000);
	robotStop(0);
	mode_chay_rung = 0;
	hoan_thanh_chay_rung = 1;
	vi_tri_chay_ngang_xanh = 12;
}

void vuot_rung_ve_homeTay_bac_200_10 (void) {
	Xuong_bac_200(-900, 900);
	robotRunAngle(-900,10,900,0.8);
	vTaskDelay (3000);
	robotStop(0);
	mode_chay_rung = 0;
	hoan_thanh_chay_rung = 1;
	vi_tri_chay_ngang_xanh = 10;

}
// ******************Home***************************
void vehome(void)
{
	robotStop(0);
	robotResetIMU();
	Tay_kep_len;

	Nang_thuong();

	target_chan_truoc = 280;
	target_chan_sau = 280;
	
	Kep_phai_1_vao;
	Kep_phai_2_vao;
	Kep_phai_3_vao;
	Kep_phai_4_vao;
	vTaskDelay(3500);

	speed_tay_gat2 = 100;
	target_tay_gat2 = vitri_tay2home;
	
	speed_tay_gat1 =100;
	target_tay_gat1 = vitri_tay1home;
	
	
	speed_tay_xoay = 150;
	target_xoay_tay = vi_tri_tay_43;
	
	Tay2_xuong;
	Tay1_xuong;
	Tay_kep_dong;
	
	
	
	if(!wantExit());
}

void vehome_xuat_phat(void)
{
	robotStop(0);
	robotResetIMU();
	
	Kep_phai_1_vao;
	Kep_phai_2_vao;
	Kep_phai_3_vao;
	Kep_phai_4_vao;
	vTaskDelay(3500);

	Nang_cham();

	target_chan_truoc = 232;//
	target_chan_sau = 232;//home lay vk
	
	speed_tay_xoay = 100;
	target_xoay_tay = vi_tri_tay_43;
	
	Tay2_xuong;
	Tay1_xuong;
	

}


void phun_tay(void) {
		Tay2_len;
		Tay1_len;
}

// su dung mam xoay toi vi tri mong muon
void su_dung_mam_xoay (int value_mucTieu_MamXoay) {
	int value_mamXoay_HienTai = bientroxoaytayValue;
	
	if (value_mamXoay_HienTai < value_mucTieu_MamXoay) {
			speed_tay_xoay = 100;
			target_xoay_tay = value_mucTieu_MamXoay;
		for(i=0;i<50;i++)	{ 
			while(bientroxoaytayValue < value_mucTieu_MamXoay - 3)	{vTaskDelay(1); if(!wantExit())	break;}
					}
	}
	
	else if (value_mamXoay_HienTai > value_mucTieu_MamXoay) {
			speed_tay_xoay = 100;
			target_xoay_tay = value_mucTieu_MamXoay;
		for(i=0;i<50;i++)	{ 
			while(bientroxoaytayValue > value_mucTieu_MamXoay + 3)	{vTaskDelay(1); if(!wantExit())	break;}
					}
	}
}


/// ************* MODULE GAP TUNG TAY BAC 200 TREN *************************


void tracking_traiPhaiThang_tren_tay4(void) {
			if (TinHieu_ChuanBi_GapTrai == 1 ) {
						Ktra_vtri_kep4_trai(); 
					}
			else if (TinHieu_ChuanBi_GapPhai == 1 ) {
						
						Ktra_vtri_kep4_phai(); 
					}
			else  if (TinHieu_ChuanBi_GapThang == 1 ) {
						Ktra_vtri_kep4(); 
					} 
}

void tracking_traiPhaiThang_tren_tay1(void) {
			if (TinHieu_ChuanBi_GapTrai == 1 ) {
						Ktra_vtri_kep1_trai(); 
					}
			else if (TinHieu_ChuanBi_GapPhai == 1 ) {
						
						Ktra_vtri_kep1_phai(); 
					}
			else  if (TinHieu_ChuanBi_GapThang == 1 ) {
						Ktra_vtri_kep1(); 
					} 
}

void tracking_traiPhaiThang_tren_tay2(void) {
			if (TinHieu_ChuanBi_GapTrai == 1 ) {
						Ktra_vtri_kep2_trai(); 
					}
			else if (TinHieu_ChuanBi_GapPhai == 1 ) {
						
						Ktra_vtri_kep2_phai(); 
					}
			else  if (TinHieu_ChuanBi_GapThang == 1 ) {
						Ktra_vtri_kep2(); 
					} 
}

void tracking_traiPhaiThang_tren_tay3(void) {
			if (TinHieu_ChuanBi_GapTrai == 1 ) {
						Ktra_vtri_kep3_trai(); 
					}
			else if (TinHieu_ChuanBi_GapPhai == 1 ) {
						
						Ktra_vtri_kep3_phai(); 
					}
			else  if (TinHieu_ChuanBi_GapThang == 1 ) {
						Ktra_vtri_kep3(); 
					} 
}

// ********** gap lan 1 thang **********

void Gap_tay4_thang(int gap, int tracking, int toc_max, int toc_min, float hs, int gc_cb2, int gc_cb1, int toc_track) 
{

	ha_tay_4(gap, tracking, toc_max, toc_min, hs, gc_cb2, gc_cb1, toc_track);
	vTaskDelay(1500);
	Kep_phai_4_vao;
	vTaskDelay(3000);
	
	speed_tay_gat2 = 250;
	target_tay_gat2 = vitri_tay2home;
	Tay2_xuong;

}

// gap lan 2 thang
void Gap_tay1_thang(int gap, int tracking, int toc_max, int toc_min, float hs, int gc_cb2, int gc_cb1, int toc_track)
{
	ha_tay_1(gap, tracking, toc_max, toc_min, hs, gc_cb2, gc_cb1, toc_track);
	vTaskDelay(1500);
	Kep_phai_1_vao;
	vTaskDelay(3000);

	speed_tay_gat1 = 250;
	target_tay_gat1 = vitri_tay1home;
	Tay1_xuong;
}


/// GAP LAN 3 

void Gap_tay2_thang(int gap, int tracking, int toc_max, int toc_min, float hs, int gc_cb2, int gc_cb1, int toc_track)
{
	ha_tay_2(gap, tracking, toc_max, toc_min, hs, gc_cb2, gc_cb1, toc_track);
	vTaskDelay(2000);
	Kep_phai_2_vao;
	vTaskDelay(3000);

	speed_tay_gat2 = 250;
	target_tay_gat2 = vitri_tay2home;
	Tay2_xuong;

}

// gap lan 4 thang
void Gap_tay3_thang(int gap, int tracking, int toc_max, int toc_min, float hs, int gc_cb2, int gc_cb1, int toc_track)
{
	ha_tay_3(gap, tracking, toc_max, toc_min, hs, gc_cb2, gc_cb1, toc_track);
	vTaskDelay(1500);
	Kep_phai_3_vao;
	vTaskDelay(3000);

	speed_tay_gat1 = 250;
	target_tay_gat1 = vitri_tay1home;
	Tay1_xuong;

}


////// ************************** GAP 200 BAC DUOI THANG KH XAI XILANG *******************

void gap_tay4_duoi_db(int gap, int tracking) 
{

	ha_tay_4_k_xlang(gap, tracking, 250, 25, 1.6, -900, 900, 8);
	vTaskDelay(1000);
	Kep_phai_4_vao;
	vTaskDelay(2500);

	speed_tay_gat2 = 250;
	target_tay_gat2 = vitri_tay2home;

}


void gap_tay1_duoi_db(int gap, int tracking) 
{

	speed_tay_xoay = 250;
	target_xoay_tay = vi_tri_tay_12 ;
	
	for(i=0; i<150; i++) { 
			while(abs(bientroxoaytayValue - target_xoay_tay) > 10) {
					vTaskDelay(1); 
					if(!wantExit()) break; 
			}
	}
	
	ha_tay_1_k_xlang(gap, tracking, 250, 25, 1.6, -900, 900, 8);
	vTaskDelay(1000);
	Kep_phai_1_vao;
	vTaskDelay(2500);
	Tay1_xuong;
	
	speed_tay_gat1 = 250;
	target_tay_gat1 = vitri_tay1home;

}


//// ********** gap lan 3 **********
void gap_tay2_duoi_db(int gap, int tracking) 
{

	speed_tay_xoay = 250;
	target_xoay_tay = vi_tri_tay_12 ;
	
	for(i=0; i<150; i++) { 
			while(abs(bientroxoaytayValue - target_xoay_tay) > 10) {
					vTaskDelay(1); 
					if(!wantExit()) break; 
			}
	}

	ha_tay_2_k_xlang(gap, tracking, 250, 25, 1.5, -900, 900, 8);
	vTaskDelay(1000);
	Kep_phai_2_vao;
	vTaskDelay(2000);
	
	speed_tay_gat2 = 250;
	target_tay_gat2 = vitri_tay2home;

}
		
void gap_tay3_duoi_db(int gap, int tracking) 
{
	speed_tay_xoay = 250;
	target_xoay_tay = vi_tri_tay_43 ;
	
	for(i=0; i<150; i++) { 
			while((abs(bientroxoaytayValue - target_xoay_tay) > 10)) { 
					vTaskDelay(1); 
					if(!wantExit()) break; 
			}
	}
	
	ha_tay_3_k_xlang(gap, tracking, 250, 25, 1.5, -900, 900, 8);
	Kep_phai_3_vao;
	vTaskDelay(2000);

	speed_tay_gat1 = 250;
	target_tay_gat1 = vitri_tay1home;

}


// ********** xoay toi goc tay tiep theo + mo kep
void kiem_tra_huong_quay_tay_gap_phia_truoc_200_duoi (void) {
	
		if (da_lay_tay1 == 0 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
				KT_Ha_Tay_Trc_200_Duoi = 1;
		}
		
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
			
			// quay mam sang tay 1
				speed_tay_xoay = 250;
				target_xoay_tay = vi_tri_tay_12 ;
				KT_Ha_Tay_Trc_200_Duoi = 1;
						
						}
		// quay mam sang tay 2
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
				speed_tay_xoay = 250;
				target_xoay_tay = vi_tri_tay_12 ;
				KT_Ha_Tay_Trc_200_Duoi = 1;

						}
		// quay mam sang tay 3
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 0) {
				speed_tay_xoay = 250;
				target_xoay_tay = vi_tri_tay_43 ;	
				KT_Ha_Tay_Trc_200_Duoi = 1;
					}		
}



///  200 tren thang
void kiem_tra_huong_quay_tay_gap_phia_truoc (void) {
	
		led_bao_hieu_on;
	
		if (da_lay_tay1 == 0 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
				led_bao_hieu_on;
		}
		
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
			
			// quay mam sang tay 1
				speed_tay_xoay = 250;
				target_xoay_tay = vi_tri_tay_12 ;
						
						}
		// quay mam sang tay 2
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {	
				speed_tay_xoay = 250;
				target_xoay_tay = vi_tri_tay_12 ;

						}
		// quay mam sang tay 3
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 0) {
				speed_tay_xoay = 250;
				target_xoay_tay = vi_tri_tay_43 ;	
					}		
}
/// ******************** CHUAN BI XOAY TAY GAP TRAI *****************************
void kiem_tra_huong_quay_tay_gap_ben_trai (void) {
	
		if (da_lay_tay1 == 0 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
						speed_tay_xoay = 250;
						target_xoay_tay = vi_tri_tay_4_trai_tren;
						KT_Ha_Tay_trai = 1;
		}
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
					// quay mam sang tay 1
						speed_tay_xoay = 250;
						target_xoay_tay = vi_tri_tay_1_trai_tren;
						KT_Ha_Tay_trai = 1;
						}
		// quay mam sang tay 2
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
						speed_tay_xoay = 250;
						target_xoay_tay = vi_tri_tay_2_trai_tren;
						KT_Ha_Tay_trai = 1;
			
						}
		// quay mam sang tay 3
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 0) {
					speed_tay_xoay = 250;
					target_xoay_tay = vi_tri_tay_3_trai_tren;	
					KT_Ha_Tay_trai = 1;
						}										
}
	
/// ******************** CHUAN BI XOAY TAY GAP PHAI *****************************
void kiem_tra_huong_quay_tay_gap_ben_phai (void) {
	
		if (da_lay_tay1 == 0 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
						speed_tay_xoay = 250;
						target_xoay_tay = vi_tri_tay_4_phai_tren;
						KT_Ha_Tay_phai = 1;
		}
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
			
					// quay mam sang tay 1
						speed_tay_xoay = 250;
						target_xoay_tay = vi_tri_tay_1_phai_tren;
						KT_Ha_Tay_phai = 1;
						}
		// quay mam sang tay 2
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
						speed_tay_xoay = 250;
						target_xoay_tay = vi_tri_tay_2_phai_tren;
						KT_Ha_Tay_phai = 1;
						}
		// quay mam sang tay 3
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 0) {
					speed_tay_xoay = 250;
					target_xoay_tay = vi_tri_tay_3_phai_tren;	
					KT_Ha_Tay_phai = 1;
						}										
}

// ********** chuan bi ha tay xuong truoc khi toi ////
void kiem_tra_huong_ha_tay_gap_ben_trai (void) {
	
		if (da_lay_tay1 == 0 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0 && Xoay_ok == 1) {
				if (abs(bientroxoaytayValue -  (vi_tri_tay_4_trai_tren)) <= 10) {
				speed_tay_gat2 = 250;
				target_tay_gat2 = Min_tay_gat2 + 110;
				Kep_phai_4_ra;
				}
		}
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0 && Xoay_ok == 1) {
				if (abs(bientroxoaytayValue -  (vi_tri_tay_1_trai_tren)) <= 10) {
						speed_tay_gat1 = 250;
						target_tay_gat1 = Max_tay_gat1 - 110;
						Kep_phai_1_ra;
							}
					}
		// quay mam sang tay 2
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 0 && da_lay_tay4 == 0 && Xoay_ok == 1) {
					if (abs(bientroxoaytayValue -  (vi_tri_tay_2_trai_tren)) <= 10) {
						speed_tay_gat2 = 250;
						target_tay_gat2 = Max_tay_gat2 - 120;
						if (bientrodaytay2Value > Max_tay_gat2 - 135 ) {
								Kep_phai_2_ra; //
								}
						}
					}
		// quay mam sang tay 3
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 0 && Xoay_ok == 1) {
					if (abs(bientroxoaytayValue -  (vi_tri_tay_3_trai_tren)) <= 10) {
						speed_tay_gat1 = 250;
						target_tay_gat1 = Min_tay_gat1 + 120;
						if (bientrodaytay1Value < Min_tay_gat1 + 135 ) {
								Kep_phai_3_ra; //
								}
							}
					}										
}

void kiem_tra_huong_ha_tay_gap_ben_phai (void) {
	
		if (da_lay_tay1 == 0 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0 && Xoay_ok == 1) {
				if (abs(bientroxoaytayValue -  (vi_tri_tay_4_phai_tren)) <= 10) {
				speed_tay_gat2 = 250;
				target_tay_gat2 = Min_tay_gat2 + 110;
				Kep_phai_4_ra;
				}
		}
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0 && Xoay_ok == 1) {
				if (abs(bientroxoaytayValue -  (vi_tri_tay_1_phai_tren)) <= 10) {
						speed_tay_gat1 = 250;
						target_tay_gat1 = Max_tay_gat1 - 110;
						Kep_phai_1_ra;
							}
					}
		// quay mam sang tay 2
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 0 && da_lay_tay4 == 0 && Xoay_ok == 1) {
					if (abs(bientroxoaytayValue -  (vi_tri_tay_2_phai_tren)) <= 10) {
						speed_tay_gat2 = 250;
						target_tay_gat2 = Max_tay_gat2 - 120;
						if (bientrodaytay2Value > Max_tay_gat2 - 135 ) {
								Kep_phai_2_ra; //
								}
						
						}
					}
		// quay mam sang tay 3
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 0 && Xoay_ok == 1) {
					if (abs(bientroxoaytayValue -  (vi_tri_tay_3_phai_tren)) <= 10) {
						speed_tay_gat1 = 250;
						target_tay_gat1 = Min_tay_gat1 + 120;
					if (bientrodaytay1Value < Min_tay_gat1 + 135 ) {
								Kep_phai_3_ra; //
								}
							}
					}										
}
		
			
/// ********************************************************************************

void kiem_tra_huong_ha_tay_gap_phia_truoc_400 (void) {
	
		if (da_lay_tay1 == 0 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0 && Xoay_ok == 1) {
			if (abs(bientroxoaytayValue -   (vi_tri_tay_43 )) <= 5) {
				speed_tay_gat2 = 80;
				target_tay_gat2 = Min_tay_gat2 + 115;	
				Kep_phai_4_ra; //
			}

		}
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0 && Xoay_ok == 1) {
					if (abs(bientroxoaytayValue -   (vi_tri_tay_12 )) <= 5) {
						speed_tay_gat1 = 200;
						target_tay_gat1 = Max_tay_gat1 - 115;
						Kep_phai_1_ra; //
								}
						}

}

// ********** chuan bi ha tay xuong truoc khi toi ////
void kiem_tra_huong_ha_tay_gap_phia_truoc (void) {
	
		if (da_lay_tay1 == 0 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0 && Xoay_ok == 1) {
			if (abs(bientroxoaytayValue -   (vi_tri_tay_43 )) <= 5) {
				speed_tay_gat2 = 140;
				target_tay_gat2 = Min_tay_gat2 + 100;	
				Kep_phai_4_ra; //
			}

		}
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0 && Xoay_ok == 1) {
					if (abs(bientroxoaytayValue -   (vi_tri_tay_12 )) <= 5) {
						speed_tay_gat1 = 250;
						target_tay_gat1 = Max_tay_gat1 - 105;
						Kep_phai_1_ra; //
								}
						}
		// quay mam sang tay 2
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 0 && da_lay_tay4 == 0 && Xoay_ok == 1) {
					if (abs(bientroxoaytayValue -  (vi_tri_tay_12 )) <= 5) {
						speed_tay_gat2 = 250;
						target_tay_gat2 = Max_tay_gat2 - 110;
						if (bientrodaytay2Value > Max_tay_gat2 - 130 ) {
								Kep_phai_2_ra; //
							}
								}
						}
		// quay mam sang tay 3
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 0 && Xoay_ok == 1) {
						if (abs(bientroxoaytayValue -  (vi_tri_tay_43 )) <= 5) {
						speed_tay_gat1 = 250;
						target_tay_gat1 = Min_tay_gat1 + 115;
						if (bientrodaytay1Value < Min_tay_gat1 + 130 ) {
								Kep_phai_3_ra; //
									}

								}		
						}										
}


void kiem_tra_huong_ha_tay_gap_phia_truoc_duoi (void) {
	
		if (da_lay_tay1 == 0 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0 && Xoay_ok == 1) {
			if (abs(bientroxoaytayValue -   (vi_tri_tay_43 )) <= 5) {
				speed_tay_gat2 = 250;
				target_tay_gat2 = Min_tay_gat2 + 75;	
				Kep_phai_4_ra; //
			}

		}
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0 && Xoay_ok == 1) {
			if (abs(bientroxoaytayValue -   (vi_tri_tay_12 )) <= 5) {
				speed_tay_gat1 = 250;
				target_tay_gat1 = Max_tay_gat1 - 80;
				Kep_phai_1_ra; //
							}
					}
		// quay mam sang tay 2
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 0 && da_lay_tay4 == 0 && Xoay_ok == 1) {
				if (abs(bientroxoaytayValue -  (vi_tri_tay_12 )) <= 5) {
					speed_tay_gat2 = 250;
					target_tay_gat2 = Max_tay_gat2 - 85;
					if (bientrodaytay2Value > Max_tay_gat2 - 130 ) {
								Kep_phai_2_ra; //
								}
							}
						}
		// quay mam sang tay 3
		else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 0 && Xoay_ok == 1) {
				if (abs(bientroxoaytayValue -  (vi_tri_tay_43 )) <= 6) {
					speed_tay_gat1 = 250;
					target_tay_gat1 = Min_tay_gat1 + 85;
					if (bientrodaytay1Value < Min_tay_gat1 + 130 ) {
								Kep_phai_3_ra; //
								}
							}		
						}										
}

/// ****************** HÀM GAP PHÍA TRUOC *************************			
void Lay_phia_truoc_bac_400_tren (void) {
//			KT_Ha_Tay =0 ; /// tat ha tay 400 tren
				reset_ha_tay_truoc();
			if (da_lay_tay1 == 0 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
					speed_tay_xoay = 200;
					target_xoay_tay = vi_tri_tay_43;
					for(i=0;i<150;i++)	{ 
							while((abs(bientroxoaytayValue - target_xoay_tay) > 10) )	{vTaskDelay(1); if(!wantExit())	break;}
					}
					Gap_tay4_thang(Min_tay_gat2 + 55  ,65 ,250 ,25 ,1.3 ,-900 ,900 ,5);
					da_lay_tay1 = 1;
					}
				
			else if (da_lay_tay1 == 1 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
					speed_tay_xoay = 200;
					target_xoay_tay = vi_tri_tay_12 ;
					for(i=0;i<150;i++)	{ 
							while((abs(bientroxoaytayValue - target_xoay_tay) > 10) )	{vTaskDelay(1); if(!wantExit())	break;}
					}
					Gap_tay1_thang(Max_tay_gat1 - 62  ,65 ,250 ,25 ,1.3 ,-900 ,900 ,5);
					da_lay_tay2 = 1;
			}
						// dung tay lan 3 
			else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
					speed_tay_xoay = 200;
					target_xoay_tay = vi_tri_tay_12 ;
					for(i=0;i<150;i++)	{ 
							while((abs(bientroxoaytayValue - target_xoay_tay) > 10) )	{vTaskDelay(1); if(!wantExit())	break;}
					}

					Gap_tay2_thang(Max_tay_gat2 - 54  ,75 ,250 ,25 ,1.3 ,-900 ,900 ,5 );
					da_lay_tay3 = 1;
			}
			TinHieu_ChuanBi_GapThang = 0;
		
}

void Lay_phia_truoc_bac_200_tren (void) {
//				KT_Ha_Tay =0 ; /// tat ha tay 200 tren
			reset_ha_tay_truoc();
			if (da_lay_tay1 == 0 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
					speed_tay_xoay = 250;
					target_xoay_tay = vi_tri_tay_43;
					for(i=0;i<150;i++)	{ 
							while((abs(bientroxoaytayValue - target_xoay_tay) > 8) )	{vTaskDelay(1); if(!wantExit())	break;}
					}
					Gap_tay4_thang(Min_tay_gat2 + 50, 60, 250, 25, 1.5, -900, 900, 5 );
					da_lay_tay1 = 1;
					}
			
					// dung tay lan 2
			else if (da_lay_tay1 == 1 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
					speed_tay_xoay = 250;
					target_xoay_tay = vi_tri_tay_12 ;
					for(i=0;i<150;i++)	{ 
							while((abs(bientroxoaytayValue - target_xoay_tay) > 8) )	{vTaskDelay(1); if(!wantExit())	break;}
					}
					Gap_tay1_thang(Max_tay_gat1 - 58, 60, 250, 25, 1.5, -900, 900, 5 );
					da_lay_tay2 = 1;
			}
			
			// dung tay lan 3 
			else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
					speed_tay_xoay = 250;
					target_xoay_tay = vi_tri_tay_12 ;
					for(i=0;i<150;i++)	{ 
							while((abs(bientroxoaytayValue - target_xoay_tay) > 8) )	{vTaskDelay(1); if(!wantExit())	break;}
					}

					Gap_tay2_thang(Max_tay_gat2 - 58, 70, 250, 24, 1.2, -900, 900, 5 );
					da_lay_tay3 = 1;
			}
			
			// dung tay lan 4
			else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 0) {
					speed_tay_xoay = 250;
					target_xoay_tay = vi_tri_tay_43 ;
					for(i=0;i<150;i++)	{ 
							while((abs(bientroxoaytayValue - target_xoay_tay) > 8) )	{vTaskDelay(1); if(!wantExit())	break;}
					}

					Gap_tay3_thang(Min_tay_gat1 + 50, 70, 250, 24, 1.2, -900, 900, 5 );
					
					da_lay_tay4 = 1;
			}
			TinHieu_ChuanBi_GapThang = 0;
}

	/// ****************** HÀM GAP BEN phai *************************		
	void Lay_ben_phai_bac_200_tren (void) {
					KT_Ha_Tay_phai = 0;
			if (da_lay_tay1 == 0 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
						speed_tay_xoay = 250;
						target_xoay_tay = vi_tri_tay_4_phai_tren ;
						for(i=0;i<550;i++)	{ 
								while((abs(bientroxoaytayValue - target_xoay_tay) > 8) )	{vTaskDelay(1); if(!wantExit())	break;}
						}
						Gap_tay4_thang(Min_tay_gat2 + 40 ,70 ,250 ,25 ,1.4 ,0 ,1800 ,5);
						
						if(CHON_SAN == 0)	{ // san do
							robotRunAngle(600,16,-900,0.8);
							vTaskDelay(6500);
								}
							else { // san xanh
							robotRunAngle(-1400,16,900,0.8);
							vTaskDelay(6500);
							}
						da_lay_tay1 = 1;
						}
				
						// dung tay lan 2
				else if (da_lay_tay1 == 1 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
						speed_tay_xoay = 250;
						target_xoay_tay = vi_tri_tay_1_phai_tren ;
						for(i=0;i<550;i++)	{ 
								while((abs(bientroxoaytayValue - target_xoay_tay) > 8) )	{vTaskDelay(1); if(!wantExit())	break;}
						}
				
						Gap_tay1_thang(Max_tay_gat1 - 50 ,70 ,250 ,25 ,1.4 ,0 ,1800 ,5);			
						
						if(CHON_SAN == 0)	{ // san do
							robotRunAngle(600,16,-900,0.8);
							vTaskDelay(8500);
								}
							else { // san xanh
							robotRunAngle(-1400,16,900,0.8);
							vTaskDelay(6500);
							}
						da_lay_tay2 = 1;
				}
				
				// dung tay lan 3 
				else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
						speed_tay_xoay = 250;
						target_xoay_tay = vi_tri_tay_2_phai_tren ;
						for(i=0;i<550;i++)	{ 
								while((abs(bientroxoaytayValue - target_xoay_tay) > 8) )	{vTaskDelay(1); if(!wantExit())	break;}
						}
						
						Gap_tay2_thang(Max_tay_gat2 - 40 ,75 ,250 ,25 ,1.1 ,0 ,1800 ,4);
						
						if(CHON_SAN == 0)	{ // san do
							robotRunAngle(50,16,-900,0.8);
							vTaskDelay(4000);
							}
						else { // san xanh
							robotRunAngle(1850,16,900,0.8);
							vTaskDelay(4000);
						}
						da_lay_tay3 = 1;
				}
				
				// dung tay lan 4
				else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 0) {
						speed_tay_xoay = 250;
						target_xoay_tay = vi_tri_tay_3_phai_tren ;
						for(i=0;i<150;i++)	{ 
								while((abs(bientroxoaytayValue - target_xoay_tay) > 8) )	{vTaskDelay(1); if(!wantExit())	break;}
						}
						
						Gap_tay3_thang(Min_tay_gat1 + 40 ,75 ,250 ,25 ,1.1 ,0 ,1800 ,4);
									
						if(CHON_SAN == 0)	{ // san do
							robotRunAngle(50,16,-900,0.8);
							vTaskDelay(4000);
							}
						else { // san xanh
							robotRunAngle(1850,16,900,0.8);
							vTaskDelay(4000);
						}
						da_lay_tay4 = 1;
				}
		
				TinHieu_ChuanBi_GapPhai =0;	
	}

	
void Lay_ben_phai_bac_200_duoi_xanh_2(void) {
			Lay_ben_phai_bac_200_duoi();
			robotStop(0);
			
	if (TinHieu_ChuanBi_GapThang == 1) {
			kiem_tra_huong_quay_tay_gap_phia_truoc();
			vTaskDelay (4000);
			di_tren_buc_khong_thanh_2_ben();
				}
}

void Lay_ben_phai_bac_200_tren_xanh_3(void) {
			Lay_ben_phai_bac_200_tren();
			robotStop(0);
			
	if (TinHieu_ChuanBi_GapThang == 1) {
			kiem_tra_huong_quay_tay_gap_phia_truoc();
			vTaskDelay (4000);
			chuan_bi_thang_xanh_2();
				}
			robotStop(0);
}
	
void Lay_ben_phai_bac_200_tren_xanh_4(void) {
			Lay_ben_phai_bac_200_tren();
			robotStop(0);
			
	if (TinHieu_ChuanBi_GapThang == 1) {
			kiem_tra_huong_quay_tay_gap_phia_truoc();
			vTaskDelay (4000);
			chuan_bi_gap_thang_xanh_4();
				}
			robotStop(0);
}


///  ****** MODULE LAY 200 BEN PHAI DUOI ******
void Lay_ben_phai_bac_200_duoi (void) {
		KT_Ha_Tay_phai = 0;
		ha_sat_xuong();
		robotStop(0);
		if (da_lay_tay1 == 0 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
					speed_tay_xoay = 250;
					target_xoay_tay = vi_tri_tay_4_phai_tren;
					for(i=0;i<150;i++)	{ 
							while((abs(bientroxoaytayValue - target_xoay_tay) > 6) )	{vTaskDelay(1); if(!wantExit())	break;}
					}
					
					Gap_tay4_thang(Min_tay_gat2  ,75 ,250 ,24 ,1.4 ,0 ,1800 ,5);
				
					su_dung_chan_thuong(350);
					robotStop(0);
					
					if(CHON_SAN == 0)	{ // san do
					robotRunAngle(600,16,-900,0.8);
					vTaskDelay(7000);
						}
					else { // san xanh
					robotRunAngle(-1300,16,900,0.8);
					vTaskDelay(7000);
					}
					
					da_lay_tay1 = 1;
					}
		// dung tay lan 2
			else if (da_lay_tay1 == 1 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
					speed_tay_xoay = 250;
					target_xoay_tay = vi_tri_tay_1_phai_tren;
					for(i=0;i<150;i++)	{ 
							while((abs(bientroxoaytayValue - target_xoay_tay) > 6) )	{vTaskDelay(1); if(!wantExit())	break;}
					}

					Gap_tay1_thang(Max_tay_gat1 - 8 ,75 ,250 ,24 ,1.4 ,0 ,1800 ,5);
					
					su_dung_chan_thuong(350);
					robotStop(0);
					if(CHON_SAN == 0)	{ // san do
					robotRunAngle(600,16,-900,0.8);
					vTaskDelay(7000);
						}
					else { // san xanh
					robotRunAngle(-1300,16,900,0.8);
					vTaskDelay(7000);
					}
					da_lay_tay2 = 1;
					}
			// dung tay lan 3
			else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
					speed_tay_xoay = 250;
					target_xoay_tay = vi_tri_tay_2_phai_tren;
					for(i=0;i<150;i++)	{ 
							while((abs(bientroxoaytayValue - target_xoay_tay) > 6) )	{vTaskDelay(1); if(!wantExit())	break;}
					}

					Gap_tay2_thang(Max_tay_gat2 - 10  ,75 ,250 ,22 ,1.2 ,0 ,1800 ,5);
					su_dung_chan_thuong(350);
					robotStop(0);
					if(CHON_SAN == 0)	{ // san do
						robotRunAngle(50,16,-900,0.8);
						vTaskDelay(6000);
						}
					else { // san xanh
						robotRunAngle(1850,16,900,0.8);
						vTaskDelay(6000);
					}
					da_lay_tay3 = 1;
					}

			else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 0) {
					speed_tay_xoay = 250;
					target_xoay_tay = vi_tri_tay_3_phai_tren;
					for(i=0;i<150;i++)	{ 
							while((abs(bientroxoaytayValue - target_xoay_tay) > 6) )	{vTaskDelay(1); if(!wantExit())	break;}
					}

					Gap_tay3_thang(Min_tay_gat1 - 8 ,75 ,250 ,22 ,1.2 ,0 ,1800 ,5);
					da_lay_tay4 = 1;
					su_dung_chan_thuong(350);
					robotStop(0);
					if(CHON_SAN == 0)	{ // san do
						robotRunAngle(50,16,-900,0.8);
						vTaskDelay(6000);
					}
					else { // san xanh
						robotRunAngle(1850,16,900,0.8);
						vTaskDelay(6000);
					}
					
			}

			TinHieu_ChuanBi_GapPhai = 0;
}

// *********** HAM LAY BEN PHAI 200 DUOI ***********
void Lay_ben_phai_bac_200_duoi_xanh_8(void) {
			Lay_ben_phai_bac_200_duoi();
			robotStop(0);
			
	if (TinHieu_ChuanBi_GapThang == 1) {
			kiem_tra_huong_quay_tay_gap_phia_truoc();
			vTaskDelay (4000);
			di_tren_buc_khong_thanh_2_ben();
				}
		// CO LENH GAP TRAI
		else if (TinHieu_ChuanBi_GapTrai == 1 ) {
				kiem_tra_huong_quay_tay_gap_ben_trai();
				vTaskDelay (4000);
				chuan_bi_gap_trai_200_duoi_ko_thanh();
		}
}


void Lay_ben_phai_bac_200_tren_xanh_7(void) {
			Lay_ben_phai_bac_200_tren();
			robotRunAngle(1650,9,900,0.5);
			vTaskDelay (4000);
			robotStop(0);
	
	if (TinHieu_ChuanBi_GapThang == 1) {
			kiem_tra_huong_quay_tay_gap_phia_truoc();
			vTaskDelay (4000);
			su_dung_chan(265);
			for(i=0;i<50;i++)		
				{
					while(abs(bientrochansauValue - target_chan_sau) > 10)	{vTaskDelay(1); if(!wantExit())	break;}
				}
			chuan_bi_gap_thang_xanh_7();
		}
			robotStop(0);
}

void Lay_ben_phai_bac_200_tren_xanh_11 (void) {
		Lay_ben_phai_bac_200_tren();
		robotStop(0);


}

/// *************** LAY BEN TRAI 200 TREN ********************
void Lay_ben_trai_bac_200_tren (void) {
		KT_Ha_Tay_trai = 0;
		su_dung_chan(565);
		robotStop(0);
		if (da_lay_tay1 == 0 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
					speed_tay_xoay = 250;
					target_xoay_tay = vi_tri_tay_4_trai_tren ;
					for(i=0;i<150;i++)	{ 
							while((abs(bientroxoaytayValue - target_xoay_tay) > 8) )	{vTaskDelay(1); if(!wantExit())	break;}
					}
					Gap_tay4_thang(Min_tay_gat2 + 40, 65,250,25,1.4, 1800, 0, 5);

					if(CHON_SAN == 0) {	 // san do
						robotRunAngle(-1600,14,-900,0.2);
						vTaskDelay(8000);
						}
					else {  // san xanh
						robotRunAngle(200,14,900,0.2);
						vTaskDelay(8000);
						}
					da_lay_tay1 = 1;
					}
			
					// dung tay lan 2
			else if (da_lay_tay1 == 1 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
					speed_tay_xoay = 250;
					target_xoay_tay = vi_tri_tay_1_trai_tren ;
					for(i=0;i<150;i++)	{ 
							while((abs(bientroxoaytayValue - target_xoay_tay) > 8) )	{vTaskDelay(1); if(!wantExit())	break;}
					}

					Gap_tay1_thang(Max_tay_gat1 - 50 , 75,250 ,25 ,1.4, 1800, 0, 5);

					if(CHON_SAN == 0) {	 // san do
						robotRunAngle(-1600,14,-900,0.2);
						vTaskDelay(8000);
						}
					else {  // san xanh
						robotRunAngle(200,14,900,0.2);
						vTaskDelay(8000);
						}
					da_lay_tay2 = 1;
			}
			
			// dung tay lan 3 
			else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
					speed_tay_xoay = 250;
					target_xoay_tay = vi_tri_tay_2_trai_tren  ;
					for(i=0;i<150;i++)	{ 
							while((abs(bientroxoaytayValue - target_xoay_tay) > 8) )	{vTaskDelay(1); if(!wantExit())	break;}
					}

					Gap_tay2_thang(Max_tay_gat2 - 40 , 75,250 ,24 ,1.1, 1800, 0, 4);
					
					if(CHON_SAN == 0) {	 // san do
						robotRunAngle(1300,16,-900,0.2);
						vTaskDelay(5500);
						}
					else {  // san xanh
						robotRunAngle(-600,16,900,0.2);
						vTaskDelay(5500);
						}
					da_lay_tay3 = 1;
			}
			
			// dung tay lan 4
			else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 0) {
					speed_tay_xoay = 250;
					target_xoay_tay = vi_tri_tay_3_trai_tren ;
					for(i=0;i<150;i++)	{ 
							while((abs(bientroxoaytayValue - target_xoay_tay) > 8) )	{vTaskDelay(1); if(!wantExit())	break;}
					}
					
					Gap_tay3_thang(Min_tay_gat1 + 40 , 75,250 ,24 ,1.1, 1800, 0, 4);
					
					if(CHON_SAN == 0) {	 // san do
						robotRunAngle(1300,16,-900,0.2);
						vTaskDelay(5000);
						}
					else {  // san xanh
						robotRunAngle(-600,16,900,0.2);
						vTaskDelay(5000);
						}
					
					da_lay_tay4 = 1;
			}

			TinHieu_ChuanBi_GapTrai = 0;
}



//// **************** MODULE GAP 200 DUOI TAY 3 4 ********
void Lay_ben_trai_bac_200_duoi (void) {
		KT_Ha_Tay_trai = 0;
		ha_sat_xuong();
		robotStop(0);
		if (da_lay_tay1 == 0 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
					speed_tay_xoay = 250;
					target_xoay_tay = vi_tri_tay_4_trai_tren;
					for(i=0;i<150;i++)	{
							while((abs(bientroxoaytayValue - target_xoay_tay) > 5) )	{vTaskDelay(1); if(!wantExit())	break;}
					}

					Gap_tay4_thang(Min_tay_gat2  ,75 ,250 ,25 ,1.4 ,1800 ,0 ,5);
					da_lay_tay1 = 1;
					su_dung_chan_thuong(350);
					robotStop(0);
					if(CHON_SAN == 0)		{							//SAN DO
							robotRunAngle(-1600,16,-900,0.5);
							vTaskDelay(7000); }
					else {
							robotRunAngle(200,16,900,0.5);
							vTaskDelay(7000);
						}
					}
		
			// lay lan 2
			else if (da_lay_tay1 == 1 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
					speed_tay_xoay = 250;
					target_xoay_tay = vi_tri_tay_1_trai_tren;
					for(i=0;i<150;i++)	{ 
							while((abs(bientroxoaytayValue - target_xoay_tay) > 5) )	{vTaskDelay(1); if(!wantExit())	break;}
					}

					Gap_tay1_thang(Max_tay_gat1 - 8  ,75 ,250 ,25 ,1.4 ,1800 ,0 ,6);
					
					da_lay_tay2 = 1;
					su_dung_chan_thuong(350);
					robotStop(0);
					if(CHON_SAN == 0)		{							//SAN DO
							robotRunAngle(-1600,16,-900,0.5);
							vTaskDelay(7000); }
					else {
							robotRunAngle(200,16,900,0.5);
							vTaskDelay(7000);
						}
					}
			
			else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
					speed_tay_xoay = 250;
					target_xoay_tay = vi_tri_tay_2_trai_tren;
					for(i=0;i<150;i++)	{ 
							while((abs(bientroxoaytayValue - target_xoay_tay) > 6) )	{vTaskDelay(1); if(!wantExit())	break;}
					}

					Gap_tay2_thang(Max_tay_gat2 - 8  ,75 ,250 ,25 ,1.2 ,1800 ,0 ,5);
					da_lay_tay3 = 1;
					su_dung_chan_thuong(350);
					robotStop(0);
					if(CHON_SAN == 0)		{							//SAN DO
							robotRunAngle(1400,18,-900,0.5);
							vTaskDelay(7500);
					}
					else {
							robotRunAngle(-500,18,900,0.5);
							vTaskDelay(7500);
						}
			}

			// dung tay lan 4
			else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 0) {
					speed_tay_xoay = 250;
					target_xoay_tay = vi_tri_tay_3_trai_tren;
					for(i=0;i<150;i++)	{ 
							while((abs(bientroxoaytayValue - target_xoay_tay) > 6) )	{vTaskDelay(1); if(!wantExit())	break;}
					}

					Gap_tay3_thang(Min_tay_gat1 -5 ,75 ,250 ,25 ,1.2 ,1800 ,0 ,5);
					da_lay_tay4 = 1;
					su_dung_chan_thuong(350);
					robotStop(0);
					if(CHON_SAN == 0)		{							//SAN DO
							robotRunAngle(1400,18,-900,0.5);
							vTaskDelay(7500);
					}
					else {
							robotRunAngle(-500,18,900,0.5);
							vTaskDelay(7500);
						}
			}

			TinHieu_ChuanBi_GapTrai = 0;
}

//////////*******************************************************

void di_vao_giua (void) {
					// da dung tay 1 xong
			if (da_lay_tay1 == 1 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
					robotRunAngle(1650,10,900,0.3);
					vTaskDelay (4000);
					robotStop(0);
		}
			
			// dung tay 2 xong
			else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
					robotRunAngle(1650,10,900,0.3);
					vTaskDelay (4000);
					robotStop(0);
			}
			
			// dung tay lan 3 xong
			else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 0) {
					robotRunAngle(150,10,900,0.3);
					vTaskDelay (4000);
					robotStop(0);
			}
			// dung tay 4 xong
			else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 1) {
				robotRunAngle(150,10,900,0.3);
				vTaskDelay (4000);
					robotStop(0);
			}		
}

/// ******* LAY 200 bac duoi ******************************
void Lay_phia_truoc_bac_200_duoi (void) {
	su_dung_chan(265);
	robotStop(0);
	reset_ha_tay_truoc();
	if (da_lay_tay1 == 0 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
					speed_tay_xoay = 250;
					target_xoay_tay = vi_tri_tay_43;
					for(i=0;i<150;i++)	{ 
							while((abs(bientroxoaytayValue - target_xoay_tay) > 7) )	{vTaskDelay(1); if(!wantExit())	break;}
					}
					vTaskDelay(1000);
					Gap_tay4_thang(Min_tay_gat2 , 75, 250, 25, 1.4, -900, 900, 5 );
					da_lay_tay1 = 1;

					}
			
					// dung tay lan 2
			else if (da_lay_tay1 == 1 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
					speed_tay_xoay = 250;
					target_xoay_tay = vi_tri_tay_12 ;
					for(i=0;i<150;i++)	{ 
							while((abs(bientroxoaytayValue - target_xoay_tay) > 7) )	{vTaskDelay(1); if(!wantExit())	break;}
					}
					vTaskDelay(1000);
//					gap_tay1_duoi();
					Gap_tay1_thang(Max_tay_gat1 - 11  ,75 ,250 ,25 ,1.4 ,-900 ,900 ,5);
					da_lay_tay2 = 1;

			}
			
			// dung tay lan 3 
			else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
					speed_tay_xoay = 250;
					target_xoay_tay = vi_tri_tay_12 ;
					for(i=0;i<150;i++)	{ 
							while((abs(bientroxoaytayValue - target_xoay_tay) > 7) )	{vTaskDelay(1); if(!wantExit())	break;}
					}
					vTaskDelay(1000);
//					gap_tay2_duoi();
					Gap_tay2_thang(Max_tay_gat2 - 11 ,75 ,250 ,25 ,1.4 ,-900 ,900 ,5 );
					da_lay_tay3 = 1;

			}
			
			// dung tay lan 4
			else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 0) {
					speed_tay_xoay = 250;
					target_xoay_tay = vi_tri_tay_43 ;
					for(i=0;i<150;i++)	{ 
							while((abs(bientroxoaytayValue - target_xoay_tay) > 7) )	{vTaskDelay(1); if(!wantExit())	break;}
					}
					vTaskDelay(1000);
					Kep_phai_3_ra;
					Gap_tay3_thang(Min_tay_gat1 + 11, 85, 250, 20, 1.1, -900, 900, 5 );
					da_lay_tay4 = 1;

			}
			
			TinHieu_ChuanBi_GapThang = 0;
}

void Lay_phia_truoc_bac_200_duoi_dac_biet (int Angle, int Robot_Angle) {
	int i;
	Nang_nhanh();
	
	target_chan_truoc = Min_chan_truoc + 8, target_chan_sau = Min_chan_sau + 8;
	for(i=0;i<50;i++)		
	{
		while(abs(bientrochansauValue - target_chan_sau) > 10)	{vTaskDelay(1); if(!wantExit())	break;}
	}
	
	robotRunAngle(Angle,12,Robot_Angle,0.7);

	for(i=0;i<1000;i++)
	{	
		while(CB_Ha_Sau == 0 ) {
				vTaskDelay(1); if(!wantExit())	break;
		}
	}
	robotRunAngle(Angle,10,Robot_Angle,0.7);

	for(i=0;i<1000;i++)
	{	
		while(CB_Ha_Sau == 0 ||  (CB_ROI_1 == 0  && CB_ROI_4 == 0)) {
				vTaskDelay(1); if(!wantExit())	break;
		}
	}
	vTaskDelay(300);
	robotStop(0);
	
	speed_chan_sau = 245;
	target_chan_sau = Min_chan_sau + 245;
	
	for(i=0;i<250;i++)		
	{
		while(abs(bientrochansauValue - target_chan_sau) > 10)	{vTaskDelay(1); if(!wantExit())	break;}
	}
	
	robotRunAngle(Angle,14,Robot_Angle,1);
	for(i=0;i<550;i++)	
	{	
		while(CB_bung_duoi == 0)	{vTaskDelay(2); if(!wantExit())	break;}
	}
	robotStop(0);
	
	robotRunAngle(Angle,14,Robot_Angle,1);
	RESET_ENCODER(); 
	while(abs(ENCODER_FR()) + abs(ENCODER_FL()) < 450)	{
	vTaskDelay (1); if(!wantExit())	break;}
	robotStop(0);
	
//	KT_Ha_Tay =0 ;
	reset_ha_tay_truoc();
	
	if (da_lay_tay1 == 0 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
					speed_tay_xoay = 250;
					target_xoay_tay = vi_tri_tay_43;
					for(i=0;i<150;i++)	{ 
							while((abs(bientroxoaytayValue - target_xoay_tay) > 5) )	{vTaskDelay(1); if(!wantExit())	break;}
					}
					gap_tay4_duoi_db(Min_tay_gat2 + 4, 70 );
					da_lay_tay1 = 1;

					}
			
					// dung tay lan 2
			else if (da_lay_tay1 == 1 && da_lay_tay2 == 0 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
					speed_tay_xoay = 250;
					target_xoay_tay = vi_tri_tay_12 ;
					for(i=0;i<150;i++)	{ 
							while((abs(bientroxoaytayValue - target_xoay_tay) > 5) )	{vTaskDelay(1); if(!wantExit())	break;}
					}
					vTaskDelay(1000);
					gap_tay1_duoi_db( Max_tay_gat1 ,  70 );
					da_lay_tay2 = 1;

			}
			
			// dung tay lan 3 
			else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 0 && da_lay_tay4 == 0) {
					speed_tay_xoay = 250;
					target_xoay_tay = vi_tri_tay_12 ;
					for(i=0;i<150;i++)	{ 
							while((abs(bientroxoaytayValue - target_xoay_tay) > 5) )	{vTaskDelay(1); if(!wantExit())	break;}
					}
					vTaskDelay(1000);
					gap_tay2_duoi_db(Max_tay_gat2 ,75  );
					da_lay_tay3 = 1;

			}
			
			// dung tay lan 4
			else if (da_lay_tay1 == 1 && da_lay_tay2 == 1 && da_lay_tay3 == 1 && da_lay_tay4 == 0) {
					speed_tay_xoay = 250;
					target_xoay_tay = vi_tri_tay_43 ;
					for(i=0;i<150;i++)	{ 
							while((abs(bientroxoaytayValue - target_xoay_tay) > 4) )	{vTaskDelay(1); if(!wantExit())	break;}
					}
					vTaskDelay(1000);
					gap_tay3_duoi_db(Min_tay_gat1 + 4,  75);
					da_lay_tay4 = 1;

			}
			
			TinHieu_ChuanBi_GapThang = 0;
	
}

void lay_thang_200_duoi(void) {
			Lay_phia_truoc_bac_200_duoi();

}

void lay_thang_200_duoi_do(void) {
			Lay_phia_truoc_bac_200_duoi();

}
/// *********** HAM tracking vi tri bang laser ****************
#define SPEED_FAST 30
#define SPEED_MIN 6
#define ERROR_MAX 50

int smooth_speed(int error)
{
    int d = abs(error);
		int speed;

    if(d > ERROR_MAX)
        d = ERROR_MAX;

    if(d < 7)
        return SPEED_MIN;

    speed = SPEED_MIN + (SPEED_FAST - SPEED_MIN) * d * d / (ERROR_MAX * ERROR_MAX);

    return speed;
}

int custom_smooth_speed(int error, int tocdo_min, int tocdo_max)
{
    int d = abs(error);
		float smooth;
		int speed; 

    // xa -> max luôn 
    if (d > 60)
        return tocdo_max;

    // rat gan 
    if (d < 15)
        return tocdo_min;

    // sigmoid 
    smooth = (float)d / (d + 35.0f);   

    speed = tocdo_min + (tocdo_max - tocdo_min) * smooth;

    return speed;
}


int custom_smooth_speed_2(int error, int tocdo_min, int tocdo_max, int kc_max, int kc_min)
{
    int d = abs(error);
		float smooth;
		int speed; 

    // xa -> max luôn 
    if (d > kc_max)
        return tocdo_max;

    // rat gan 
    if (d < kc_min)
        return tocdo_min;

    // sigmoid 
    smooth = (float)d / (d + 35.0f);   

    speed = tocdo_min + (tocdo_max - tocdo_min) * smooth;

    return speed;
}

// ***************** CHINH LAI VI TRI LAZER SAN XANH **************
void chinh_lai_vi_tri_laser_trai(int vitri, int gia_tri_lap)
{
	int speed ;
	int dieuchinh;
		for(i=0;i<gia_tri_lap;i++)
				{
		while(abs(lazeTraiValue - vitri) > 0)	{
			dieuchinh = lazeTraiValue - vitri;
			speed = smooth_speed(dieuchinh);
			
					if  ((lazeTraiValue - vitri)> 0 ) {
							robotRunAngle(0, speed, 900, 0.9);
					}
					else if ((lazeTraiValue - vitri)< 0) {
					
					robotRunAngle(1800, speed, 900, 0.9);
					
					}
					else {
								robotStop(0);

								}
					if(!wantExit())	break;
			}
		}   		
	}

	void chinh_lai_vi_tri_laser_trai_custom(int vitri, int gia_tri_lap)
{
	int speed ;
	int dieuchinh;
		for(i=0;i<gia_tri_lap;i++)
				{
		while(abs(lazeTraiValue - vitri) > 1)	{
			dieuchinh = lazeTraiValue - vitri;
			speed = custom_smooth_speed(dieuchinh, 4, 45);
			
					if  ((lazeTraiValue - vitri)> 0 ) {
							robotRunAngle(0, speed, 900, 0.9);
					}
					else if ((lazeTraiValue - vitri)< 0) {
					
					robotRunAngle(1800, speed, 900, 0.9);
					
					}
					else {
								robotStop(0);

								}
					if(!wantExit())	break;
			}
		}   		
	}

	
	

void chinh_lai_vi_tri_laser_phai(int vitri, int gia_tri_lap)
{
	int speed ;
	int dieuchinh;
		for(i=0;i<gia_tri_lap;i++)
				{
		while(abs(lazePhaiValue - vitri) > 1)	{
			dieuchinh = lazePhaiValue - vitri;
			speed = smooth_speed(dieuchinh);
			
					if  ((lazePhaiValue - vitri)> 0 ) {
							robotRunAngle(1800, speed, 900, 0.9);
					}
					else if ((lazePhaiValue - vitri)< 0) {
					
					robotRunAngle(0, speed, 900, 0.9);
					
					}
					else {
								robotStop(0);
					}
				if(!wantExit())	break;
			}
		}   		
	}

	
void chinh_lai_vi_tri_laser_sau(int vitri, int gia_tri_lap, int min_toc, int max_toc)
{
	int speed ;
	int dieuchinh;
		for(i=0;i<gia_tri_lap;i++)
				{
		while(abs(lazeSauValue - vitri) > 0)	{
			dieuchinh = lazeSauValue - vitri;
			speed = custom_smooth_speed(dieuchinh, min_toc, max_toc);
			
					if  ((lazeSauValue - vitri)> 0 ) {
							robotRunAngle(-900, speed, 900, 0.7);
					}
					else if ((lazeSauValue - vitri)< 0) {
					
					robotRunAngle(900, speed, 900, 0.7);
					
					}
					else {
								robotStop(0);
								}
				if(!wantExit())	break;
			}
		}   		
	}

	
void chinh_lai_vi_tri_laser_truoc_xanh(int vitri, int gia_tri_lap, int min_toc, int max_toc)
{
	int speed ;
	int dieuchinh;
		for(i=0;i<gia_tri_lap;i++)
				{
		while(abs(lazeTruocValue - vitri) > 0)	{
			dieuchinh = lazeTruocValue - vitri;
			speed = custom_smooth_speed(dieuchinh, min_toc, max_toc);
			
					if  ((lazeTruocValue - vitri)> 0 ) {
							robotRunAngle(900, speed, 900, 0.8);
					}
					else if ((lazeTruocValue - vitri)< 0) {
					
					robotRunAngle(-900, speed, 900, 0.8);
					
					}
					else {
								robotStop(0);
								}
				if(!wantExit())	break;
			}
		}   		
	}

void chinh_lai_vi_tri_laser_truoc_do(int vitri, int gia_tri_lap, int min_toc, int max_toc)
{
	int speed ;
	int dieuchinh;
		for(i=0;i<gia_tri_lap;i++)
				{
		while(abs(lazeTruocValue - vitri) > 1)	{
			dieuchinh = lazeTruocValue - vitri;
			speed = custom_smooth_speed(dieuchinh, min_toc, max_toc);
			
					if  ((lazeTruocValue - vitri)> 0 ) {
							robotRunAngle(900, speed, 900, 0.8);
					}
					else if ((lazeTruocValue - vitri)< 0) {
					
					robotRunAngle(-900, speed, 900, 0.8);
					
					}
					else {
								robotStop(0);
								}
				if(!wantExit())	break;
			}
		}   		
	}

void chinh_lai_vi_tri_laser_phai_custom(int vitri, int gia_tri_lap, int min_toc, int max_toc, int sai_so )
{
	int speed ;
	int dieuchinh;
		for(i=0;i<gia_tri_lap;i++)
				{
		while(abs(lazePhaiValue - vitri) > sai_so)	{
			dieuchinh = lazePhaiValue - vitri;
			speed = custom_smooth_speed(dieuchinh, min_toc, max_toc);
			
					if  ((lazePhaiValue - vitri)> 0 ) {
							robotRunAngle(1800, speed, 900, 0.8);
					}
					else if ((lazePhaiValue - vitri)< 0) {
					
					robotRunAngle(0, speed, 900, 0.8);
					
					}
					else {
								robotStop(1);

								}
					if(!wantExit())	break;
			}
		}   		
	}

	

	void chinh_lai_vi_tri_VK(int vitri, int gia_tri_lap, int min, int max, int saiso)
{
	int speed ;
	int dieuchinh;
		for(i=0;i<gia_tri_lap;i++)
				{
		while(abs(lazePhaiValue - vitri) > saiso)	{
			dieuchinh = lazePhaiValue - vitri;
			speed = custom_smooth_speed(dieuchinh,min, max);
			
					if  ((lazePhaiValue - vitri)> 0 ) {
							robotRunAngle(0, speed, -900, 0.8);
					}
					else if ((lazePhaiValue - vitri)< 0) {
					
					robotRunAngle(1800, speed, -900, 0.8);
					
					}
					else robotStop(0);
	
					if(!wantExit())	break;
			}
		}   		
	}


/////////////////////////////////////////////////////////
void go_qua (void) {
	if (R2 && O) {
		
			speed_tay_xoay = 120;
			target_xoay_tay = vi_tri_tay_43;
			for(i=0;i<150;i++)	{ 
							while((abs(bientroxoaytayValue - target_xoay_tay) > 5) )	{vTaskDelay(1); if(!wantExit())	break;}
					}
		
			speed_tay_gat1 = 120;
			target_tay_gat1 = 270;
	
			speed_tay_gat2 = 150;
			target_tay_gat2 = 500;
			
			for(i=0;i<50;i++)	{ 
				while(abs(bientrodaytay1Value - target_tay_gat1) > 10 || abs(bientrodaytay2Value - target_tay_gat2) > 10 )	
				{vTaskDelay(1); if(!wantExit())	break;}
					}
			
			Kep_phai_4_ra;
			Kep_phai_1_ra;
			Kep_phai_2_ra;
			Kep_phai_3_ra;
			Tay_kep_mo;
	}
	if (R2 && SQUARE) {
		
			speed_tay_xoay = 120;
			target_xoay_tay = vi_tri_tay_43;
			for(i=0;i<150;i++)	{ 
							while((abs(bientroxoaytayValue - target_xoay_tay) > 5) )	{vTaskDelay(1); if(!wantExit())	break;}
					}
		
			speed_tay_gat1 = 120;
			target_tay_gat1 = 500;
	
			speed_tay_gat2 = 150;
			target_tay_gat2 = 270;
			
			for(i=0;i<50;i++)	{ 
				while(abs(bientrodaytay1Value - target_tay_gat1) > 10 || abs(bientrodaytay2Value - target_tay_gat2) > 10 )	
				{vTaskDelay(1); if(!wantExit())	break;}
					}
			
			Kep_phai_4_ra;
			Kep_phai_1_ra;
			Kep_phai_2_ra;
			Kep_phai_3_ra;
			Tay_kep_mo;
	}
	
}
///////////////////////////ktr vi tri kep//////////////////////////////
void Ktra_vtri_kep3 (void) {
		for(i=0;i<500;i++)
				{
					while(CB_kep_3_2 == 0 || CB_kep_3_1 == 0)	
					{	
						if	(CB_kep_3_2 == 0 && CB_ROI_1 == 0 ) 			robotRun(-900,4);	
						else if 	(CB_kep_3_1 == 0 && CB_ROI_4 == 0 ) robotRun(900,4);
					
						vTaskDelay (1);
						if(!wantExit())	break;
					}
				}
				vTaskDelay (1200);
				robotStop(0);
	
	}

	void Ktra_vtri_kep4 (void) {
		for(i=0;i<500;i++)
				{
					while(CB_kep_4_2 == 0 || CB_kep_4_1 == 0 )	
					{	
						if	(CB_kep_4_2 == 0 && CB_ROI_1 == 0 ) 					robotRun(-900,4);	
						else if 	(CB_kep_4_1 == 0  && CB_ROI_4 == 0 ) robotRun(900,4);
						vTaskDelay (1);
						if(!wantExit())	break;
					}
				}	
				
				vTaskDelay (1200);
				robotStop(0);
	
	}

void Ktra_vtri_kep1 (void) {
		for(i=0;i<500;i++)
				{
					while(CB_kep_1_2 == 0 || CB_kep_1_1 == 0)	
					{	
						if	(CB_kep_1_2 == 0 && CB_ROI_1 == 0  ) 			robotRun(-900,4);	
						else if 	(CB_kep_1_1 == 0 && CB_ROI_4 == 0  ) robotRun(900,4);
						
						vTaskDelay (5);
						if(!wantExit())	break;
					}
				}
				vTaskDelay (1200);
				robotStop(0);
	
	}
		
	void Ktra_vtri_kep2 (void) {
		for(i=0;i<500;i++)
				{
					while(CB_kep_2_2 == 0 || CB_kep_2_1 == 0)	
					{	
						if	(CB_kep_2_2 == 0 && CB_ROI_1 == 0 ) 			robotRun(-900,4);
						else if 	(CB_kep_2_1 == 0 && CB_ROI_4 == 0  ) robotRun(900,4);
							
						vTaskDelay (1);
						if(!wantExit())	break;
					}
				}	
				vTaskDelay (1200);
				robotStop(0);
	}

///////////////////////////ktr vi tri kep TRAI  //////////////////////////////
void Ktra_vtri_kep3_trai (void) {
		for(i=0;i<1000;i++)
				{
					while(CB_kep_3_2 == 0 || CB_kep_3_1 == 0)	
					{	
						if				(CB_kep_3_2 == 0  ) 		robotRun(1800,4);	
						else if 	(CB_kep_3_1 == 0 ) robotRun(0, 4);
									
						vTaskDelay (1);
						if(!wantExit())	break;
					}
				}	
				vTaskDelay (1200);
				robotStop(0);
	
	}

	void Ktra_vtri_kep4_trai (void) {
		for(i=0;i<1000;i++)
				{
					while(CB_kep_4_2 == 0 || CB_kep_4_1 == 0 )	
					{	
						if						(CB_kep_4_2 == 0 ) robotRun(1800,4);	
						else if 	(CB_kep_4_1 == 0   ) robotRun(0,4);
						
						vTaskDelay (1);
						if(!wantExit())	break;
					}
				}
				vTaskDelay (1500);
				robotStop(0);
	
	}


void Ktra_vtri_kep1_trai (void) {
		for(i=0;i<1000;i++)
				{
					while(CB_kep_1_2 == 0 || CB_kep_1_1 == 0)	
					{	
						if	(CB_kep_1_2 == 0 ) 			robotRun(1800,4);	
						else if 	(CB_kep_1_1 == 0 ) robotRun(0,4);
									
						vTaskDelay (1);
						if(!wantExit())	break;
					}
				}	
				vTaskDelay (1200);
				robotStop(0);
	
	}
		
	void Ktra_vtri_kep2_trai (void) {
		for(i=0;i<1000;i++)
				{
					while(CB_kep_2_2 == 0 || CB_kep_2_1 == 0)	
					{	
						if	(CB_kep_2_2 == 0 ) 			robotRun(1800,4);
						else if 	(CB_kep_2_1 == 0 ) robotRun(0, 4);
									
						vTaskDelay (1);
						if(!wantExit())	break;
					}
				}	
				vTaskDelay (1200);
				robotStop(0);
	}	
	
///////////////////////////ktr vi tri kep PHAI //////////////////////////////
void Ktra_vtri_kep3_phai (void) {
		for(i=0;i<1000;i++)
				{
					while(CB_kep_3_2 == 0 || CB_kep_3_1 == 0)	
					{	
						if				(CB_kep_3_2 == 0 ) 		robotRun(0,4);	
						else if 	(CB_kep_3_1 == 0 ) robotRun(1800,4);
									
						vTaskDelay (1);
						if(!wantExit())	break;
					}
				}	
				vTaskDelay (1000);
				robotStop(0);
	
	}

	void Ktra_vtri_kep4_phai (void) {
		for(i=0;i<1000;i++)
				{
					while(CB_kep_4_2 == 0 || CB_kep_4_1 == 0 )	
					{	
						if						(CB_kep_4_2 == 0 ) robotRun(0,4);	
						else if 	(CB_kep_4_1 == 0   ) robotRun(1800,4);
					
						vTaskDelay (1);
						if(!wantExit())	break;
					}
				}	
				vTaskDelay (1000);
				robotStop(0);
	
	}


void Ktra_vtri_kep1_phai (void) {
		for(i=0;i<1000;i++)
				{
					while(CB_kep_1_2 == 0 || CB_kep_1_1 == 0)	
					{	
						if	(CB_kep_1_2 == 0 ) 			robotRun(0,4);	
						else if  (CB_kep_1_1 == 0 ) robotRun(1800,4);
						
						vTaskDelay (1);
						if(!wantExit())	break;
					}
				}	
				vTaskDelay (1000);
				robotStop(0);
	
	}
		
	void Ktra_vtri_kep2_phai (void) {
		for(i=0;i<1000;i++)
				{
					while(CB_kep_2_2 == 0 || CB_kep_2_1 == 0)	
					{	
						if	(CB_kep_2_2 == 0 ) 			robotRun(0,4);
						else if 	(CB_kep_2_1 == 0 ) robotRun(1800,4);
									
						vTaskDelay (1);
						if(!wantExit())	break;
					}
				}	
				vTaskDelay (800);
				robotStop(0);
	}	

void nhac_dit(void) {
			/// nhac dit len
			Nang_nhanh();
			target_chan_truoc = 395;
			target_chan_sau = 275;
}

void ha_sat_xuong(void) {
			/// nhac dit len
			Nang_nhanh();
			target_chan_truoc = 245;
			target_chan_sau = 245;
}


