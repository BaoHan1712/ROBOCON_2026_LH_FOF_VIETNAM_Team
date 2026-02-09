/*
//================================================
* 4 Swerve Robot Controler
* Created: 03/2017 and developed : 18/8/2025
* Author: Huynh Cao Tuan, Vu, Han Quoc Bao
* 
//================================================

	void robotAnalytics(void) // Dat trong timer de Robot hoat dong
	//----------------------
	void robotRun(int angle, int maxSpeed)
	void robotCurve(int angle, int maxSpeed, float curve)

	vidu: robotRun(450, 70)
			Chay Robot huong:	450
			Toc do toi da: 		70
	//----------------------
	void robotRunAngle(float angle, int maxSpeed, float robotAngle)
	
	vidu:
		while(.....){
			robotRunAngle(900, 70, 450) Chay Robot huong la ban 900. V? quay dau robot huong 450.
		}

	//----------------------
	void robotRotateFree(float rotate, int rotatePoint)
	void robotRotate(int rotateAngle, float rotate, int rotatePoint)
	int robotFixAngle()

	vidu: robotRotate(0.5, 0)
			Quay robot tu do:		30000 	{Neu nho hon thi nghia la quay den goc do thi Stop}
			Huong va ty le quay: 	0.5
			Tam quay :				0 		{0 : tam robot, 1: banh truoc trai...,2,3, 4: Banh sau phai}
	
	vidu:
		(300, 0.5, 0);
		while(robotFixAngle()){
			
			
		}
	//----------------------
	void robotSetACC(float X, float Y)			// Thiet lap gia toc
	void robotStop(int acc) 		// Stop tat ca
	void robotRotateStop() 	    // Stop xoay
	void robotResetIMU()
	//----------------------
	int robotIsRun() 		// Kiem tra ro bot co dang chay hay khong
	int robotIsStop()
	int robotAngle()  		// Tra ve gia tri hien tai cua La ban
	int robotSpeed()  		//Toc do hien tai cua robot
*/

#include <stdlib.h>
#include <math.h>

 vs16 IMU;

//=================================================
//--------------- Cac hang so ---------------------
//=================================================
int robotLimitSpeed = 250;  // Toc do toi da se chinh la fixDirError + maxSpeed
float f05 = 0.5, f1 = 1.0, f2 = 2.0, f4 = 4.0, f5 = 5.0, f6 = 6.0, f10 = 10.0, f20 = 20.0, f30 = 30.0, f45 = 45.0, f60 = 60.0, f120 = 120.0;
int i100 = 80, khoangCachGocFix = 200;

int motorLock = 2;
int motorLockRepeat = 10000;//20000 thoi gian phanh
float radian = 3.141592653589793238462643/180;
float pi = 3.14;
//=================================================
//------ Bien toan cuc de dieu khien ------
//=================================================
int _robotChange=0, _robotRotatePoint=0;
int _robotCurrentSpeed=0, _robotRunSpeed=0, _robotMaxSpeed=0;
int _robotAccStop=0, _robotCounter=0;
int _robotAngle = 30000, _robotRunAngle = 30000, _robotRotateAngle=0, _robotIMUInit=0;
float _robotRotate=0, _robotCurve=0;
int _robotAngleCounterFix=0, _robotAngleToFix=30000;

int _robotIMUAngle=0,_IMUAngle_Before=0, _robotDelayGiamToc = 20; //15
float _robotRun0h=0, _robotRun4h=0, _robotRun8h=0;

//========================================================
float _robotDir0h=0, _robotDir4h=0, _robotDir8h=0;
float _robotRotate0h=0, _robotRotate4h=0, _robotRotate8h=0;

int vu_gocXoay, vu_v, vu_omega;
int _0h_Wheel_Angle, _4h_Wheel_Angle, _8h_Wheel_Angle;
int _0h_Wheel_Angle_dir, _4h_Wheel_Angle_dir,_8h_Wheel_Angle_dir, dir;

float Vx, Vy, A, B, C, D, WL, WW, _Omega, Robot_Width = 0.28, Robot_Lenght = 0.28, Vy10, Vx10, ABCD;

extern int	current_0h_Angle, current_4h_Angle, current_8h_Angle;

int _lockRobot = 0;
int demVui = 0;
//==========================================================================================
//==========================================================================================


//******************************************************** cap nhat goc hien tai ******************************************************************
void	Curent_angle_4_wheel(void)
{
	current_0h_Angle = ENCODER_0h();
	current_4h_Angle = ENCODER_4h();
	current_8h_Angle = ENCODER_8h();
}

//----------------------------------------------------------------------------------------
// ham tinh goc gan nhat de xoay
int close_angle(int targetAngle, int currentAngle)
{
    int goc_den, goc_doi, gd;
    goc_doi = fmod(targetAngle,3600);
    if(goc_doi >= 0) goc_doi = goc_doi - 1800;
    else goc_doi = goc_doi + 1800;
    goc_den = fmod(targetAngle,3600) - fmod(currentAngle,3600);

    if(abs(goc_doi) < abs(goc_den)) { 
        goc_den = goc_doi; 
        dir = -1;          //  Lui
    }
    else {
        goc_den = targetAngle; 
        dir = 1;               //  TIeN
    }
    return goc_den; 
}

// int close_angle(int targetAngle, int currentAngle)
// {
//     int tg = ((targetAngle % 3600) + 3600) % 3600;
//     int cg = ((currentAngle % 3600) + 3600) % 3600;

//     // Khoảng cách quay nếu tiến
//     int forward = (tg - cg + 3600) % 3600;

//     // Khoảng cách quay nếu lùi + đảo hướng robot
//     int backward = (cg - (tg + 1800) % 3600 + 3600) % 3600;

//     if (forward <= backward) {
//         dir = 1; // đi đúng hướng
//         return forward;
//     } else {
//         dir = -1; // đảo hướng robot
//         return backward;
//     }
// }





//==========================================================================================
vu8 motorMinFix(int S)
{
	if(S > 250)	S = 250;
	else	if(S <= 3)	S = 2;
	else;
	
	return S;
}
//-----------------------------------------------------------------------------------
void setMotor(int speed_0h, int speed_4h, int speed_8h)
{
	if(!speed_0h) Mor_0h = motorLock;
	else if(_robotDir0h>0)
 	{
	 	Mor_0h = motorMinFix(speed_0h);
		Mor_0h_next;
 	}
	else{
		Mor_0h = motorMinFix(-speed_0h);
		Mor_0h_back;
 	}

	if(!speed_4h) Mor_4h = motorLock;
	else if(_robotDir4h>0)
 	{
	 	Mor_4h = motorMinFix(speed_4h);
		Mor_4h_next;
 	}
	else{
		Mor_4h = motorMinFix(-speed_4h);
		Mor_4h_back;
 	}

	if(!speed_8h) Mor_8h = motorLock;
	else if(_robotDir8h>0)
 	{
	 	Mor_8h = motorMinFix(speed_8h);
		Mor_8h_next;
 	}
	else{
		Mor_8h = motorMinFix(-speed_8h);
		Mor_8h_back;
 	}

}

void SetRotateMotor(int	Angle_robotRotate0h, int	Angle_robotRotate4h, int	Angle_robotRotate8h)
{
	_0h_Wheel_Angle = Angle_robotRotate0h;
	_4h_Wheel_Angle = Angle_robotRotate4h;
	_8h_Wheel_Angle = Angle_robotRotate8h;

}
//------------------------------------------------------------------------------
void setAllMotor(int speed)
{
	Mor_0h = speed;
	Mor_4h = speed;
	Mor_8h = speed;
}
//------------------------------------------------------------------------------
int robotIsStop()
{
    return Mor_0h < 3 && Mor_4h < 3 && Mor_8h < 3;
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void robotLock()
{
    _lockRobot = 1;
}
int robotIsRun()
{
	return (_robotAngle == 30000)? 0: 1;
}
//------------------------------------------------------------------------------
void robotResetIMU(void)
{
	run_read_gyro_uart1();
}
//------------------------------------------------------------------------------
vs32 robotAngle(void)
{
	return -IMU;
}
//------------------------------------------------------------------------------
//==========================================================================================
//------------------------------------------------------------------------------
int roundF(float num)
{
	if(num < 0) return num - f05;
	else return num + f05;
}
//------------------------------------------------------------------------------
// float fixMotorValue(int T)
// {
// 	if(T == 0) 			return 0;
// 	else 	if(T < 0) return (T*0.07 - 0.1)/_robotCurrentSpeed; // tuy thuoc robot ma co the he so toi thieu la 0.5, 1, 2...
// 				else 			return (T*0.07 + 0.1)/_robotCurrentSpeed;
// }

float fixMotorValue(int T)
{
    float gain = 0.05f;       // Hệ số khuếch đại
    float offset = 0.7f;     // troi dau thi + offset
    float deadzone = 2;       // rung nhe + deadzone
	float linearOutput, smooth;

    if (abs(T) < deadzone) return 0;

    linearOutput = T * gain + (T > 0 ? offset : -offset);
    smooth = tanhf(linearOutput) * fabs(linearOutput);

    return smooth / _robotCurrentSpeed;
}


//------------------------------------------------------------------------------
float absF(float num)
{
	if(num >= 0) return num;
	else return -num;
}
//------------------------------------------------------------------------------
int absI(int num)
{
	if(num >= 0) return num;
	else return -num;
}
//------------------------------------------------------------------------------

//------------ su dung cho ham gia toc, giam toc --------------
float _robotY = 30;  //80
float _robotX = 250;

//int giaToc(int x)
//{
//	// ------ gia toc bac 1 -----------
//	float y = (-_robotY/_robotX)*x + _robotY;
//	
//	return (int)y;
//}

int giaToc(int x)
{
    float t;
    float y;
    const float maxY = _robotY;
    const float maxX = _robotX;
	
    t = (float)x / maxX;
    if (t < 0.0f) t = 0.0f;
    if (t > 1.0f) t = 1.0f;

    y = maxY * t;
    return (int)(y + 0.5f);
}


int giamToc(int x)
{
    const int tocDoMin = 10;
    const int tocDoMax = 80;
		float tocDo;

    float heSoGiamToc = 0.7f;  // càng nhỏ càng giảm nhiều, càng lớn càng mượt

    if (x <= tocDoMin) return tocDoMin;
    if (x >= tocDoMax) return tocDoMax;

    tocDo = tocDoMin + (x - tocDoMin) * heSoGiamToc;
    if (tocDo > tocDoMax) tocDo = tocDoMax;
    if (tocDo < tocDoMin) tocDo = tocDoMin;

    return (int)tocDo;
}


//------------------------------------------------------------------------------
float maxF3(float N1, float N2, float N3)
{
	float _maxNum = 0.001;
	if(N1<0) N1 = -N1;
	if(N2<0) N2 = -N2;
	if(N3<0) N3 = -N3;

	if(N1>_maxNum) _maxNum = N1;
	if(N2>_maxNum) _maxNum = N2;
	if(N3>_maxNum) _maxNum = N3;

	return _maxNum;
}
//------------------------------------------------------------------------------
int robotSpeed()
{
    return _robotCurrentSpeed;
}
//------------------------------------------------------------------------------
int robotFixAngle()
{
		return _robotAngleCounterFix;
}
//------------------------------------------------------------------------------
int findSection(float angle) {
    // Ham xac dinh huong di chuyen cua robot
    float normalizedAngle = fmod(fmod(angle, 3600) + 3600, 3600);
    if ((normalizedAngle > 3150 && normalizedAngle < 3600) || (normalizedAngle >= 0 && normalizedAngle <= 450)) {
        return 1; // Phan 1
    } else if (normalizedAngle <= 1350) {
        return 2; // Phan 2
    } else if (normalizedAngle <= 2250) {
        return 3; // Phan 3
    } else {
        return 4; // Phan 4
    }
}
extern float momen;
// ======================================================================================
void swervecalculatemotor(float gocXoay, float V, float Omegacal)
{
	// Goc di chuyen, do lon vector, toc do robot
		float R,V0hx, V0hy, V4hx, V4hy, V8hx, V8hy;
		V0hx = V * cos(gocXoay * pi / 1800);
		V0hy = (V * sin(gocXoay * pi / 1800)) + Omegacal;
		V4hx = V * cos((gocXoay - 1200) * pi / 1800);
		V4hy = (V * sin((gocXoay - 1200) * pi / 1800)) + Omegacal;
		V8hx = V * cos((gocXoay - 2400) * pi / 1800);
		V8hy = (V * sin((gocXoay - 2400) * pi / 1800)) + Omegacal;
		
		_robotRotate0h =  atan2f(V0hy,V0hx) *1800/pi; // tinh goc vector banh xoay
		// ch?n g�c g?n v?i g�c hi?n t?i c?a b�nh xe
		_robotRotate0h = close_angle(_robotRotate0h, current_0h_Angle); 
		_robotDir0h = dir; // ch?y th?ng hay l�i
		_robotRun0h =  sqrt(pow(V0hx,2) + pow(V0hy,2))/40*dir; //t?c d? m� b�nh xe c?n quay
		
		_robotRotate4h =  atan2f(V4hy,V4hx) *1800/pi;
		_robotRotate4h = close_angle(_robotRotate4h, current_4h_Angle);
		_robotDir4h = dir;
		_robotRun4h =  sqrt(pow(V4hx,2) + pow(V4hy,2))/40*dir;

		_robotRotate8h =  atan2f(V8hy,V8hx) *1800/pi;
		_robotRotate8h = close_angle(_robotRotate8h, current_8h_Angle);
		_robotDir8h = dir;
		_robotRun8h = sqrt(pow(V8hx,2) + pow(V8hy,2))/40*dir;
		
		vu_gocXoay = sqrt(pow(V8hx,2) + pow(V8hy,2));
		vu_v = _robotRun4h; 
		vu_omega = findSection(_robotAngle);
		momen = vu_v;
}


//==========================================================================================
float gioiHan(float input){
	float bienReturn = input;
	if(input < -f10) bienReturn = -f10;
	else if(_robotRun8h > f10) bienReturn = f10;
	return bienReturn;
}
//------------------------------------------------------------------------------
void tru8h(float sotru){
	if(_robotRun8h > 0)	_robotRun8h -= sotru;
	else _robotRun8h += sotru;

	if(_robotRun8h < -f10) _robotRun8h = -f10;
	else if(_robotRun8h > f10) _robotRun8h = f10;
}
void cong8h(float sotru){
	if(_robotRun8h > 0)	_robotRun8h += sotru;
	else _robotRun8h -= sotru;

	if(_robotRun8h < -f10) _robotRun8h = -f10;
	else if(_robotRun8h > f10) _robotRun8h = f10;
}
void tru4h(float sotru){
	if(_robotRun4h > 0)	_robotRun4h -= sotru;
	else _robotRun4h += sotru;

	if(_robotRun4h < -f10) _robotRun4h = -f10;
	else if(_robotRun4h > f10) _robotRun4h = f10;
}
void cong4h(float sotru){
	if(_robotRun4h > 0)	_robotRun4h += sotru;
	else _robotRun4h -= sotru;

	if(_robotRun4h < -f10) _robotRun4h = -f10;
	else if(_robotRun4h > f10) _robotRun4h = f10;
}
void tru0h(float sotru){
	if(_robotRun0h > 0)	_robotRun0h -= sotru;
	else _robotRun0h += sotru;

	if(_robotRun0h < -f10) _robotRun0h = -f10;
	else if(_robotRun0h > f10) _robotRun0h = f10;
}
void cong0h(float sotru){
	if(_robotRun0h > 0)	_robotRun0h += sotru;
	else _robotRun0h -= sotru;

	if(_robotRun0h < -f10) _robotRun0h = -f10;
	else if(_robotRun0h > f10) _robotRun0h = f10;
}


extern float error_show;


float FixOmegaFromIMU() {
    float maxGain = 30.0f;   // Hệ số quay lớn nhất
    float minGain = 10.0f;    // Hệ số quay nhỏ nhất
    float omega = 0;
		float gain;
		int absError;
		int error;

    error = _robotIMUAngle - _robotIMUInit;

    if (error > 1800) error -= 3600;
    if (error < -1800) error += 3600;

    error_show = error;

    absError = abs(error);

    if (absError < -1 && absError > 1) {
        gain = minGain + (float)absError / 1800.0f * (maxGain - minGain);
        omega = _robotRotate * gain;
    }
		else {    omega = _robotRotate * 12.0f;}

    return omega;
}

void calculateMotor(float rotate)
{
	float angle; 
	float absRotate;
	absRotate = rotate* 0.5;
	
	
	if(_robotAngle == 30000)
	{
		_Omega = (float)(rotate*15); 
		swervecalculatemotor(0, 0, _Omega);	
	
	}
	 if (!rotate && _robotAngle != 30000) {// dang chay k xoay
		angle = (float)(_robotAngle - (_robotIMUAngle - _robotIMUInit)); ;
		_Omega = FixOmegaFromIMU ();
		swervecalculatemotor(angle, _robotRunSpeed, _Omega);
	}
	 if (rotate && _robotAngle != 30000) {// dang chay co xoay
		angle = (float)(_robotAngle - (_robotIMUAngle - _robotIMUInit)); 
		_Omega = (float)_robotRotate*12;
		swervecalculatemotor(angle, _robotRunSpeed, _Omega);
			switch(findSection(_robotAngle))
		{
			case 1:
					tru4h(absRotate);
					cong8h(absRotate);
					break;
			case 2:
					cong0h(absRotate);
					tru4h(absRotate);
					break;
			case 3:
					cong4h(absRotate);
					tru8h(absRotate);
					break;
			case 4:
					tru0h(absRotate);
					cong8h(absRotate);
					break;
		}
	}
	//----------- tinh toc do toi da ----------------
	_robotMaxSpeed = (int)(robotLimitSpeed/maxF3(_robotRun0h, _robotRun4h, _robotRun8h));
    if(_robotCurrentSpeed > _robotMaxSpeed) _robotCurrentSpeed = _robotMaxSpeed;
	//------------------------------------------------
	_robotChange = 1;
}
//------------------------------------------------------------------------------
void robotStop(unsigned int acc)
{
		_robotRunSpeed = 0;
		_robotAccStop = acc;

		if(!acc){
			_robotCurrentSpeed = 0;
			_robotCurve = 0;
			_robotAngle = 30000;
			_robotRunAngle = 30000;
			
			_robotRotate = 0;
			_robotRotatePoint = 0;
			_robotRotateAngle = 0;
			_robotAngleCounterFix = 0;
			_lockRobot = 0;
			
			calculateMotor(0);
		}
}
//------------------------------------------------------------------------------
void robotRotateStop()
{

	if(_robotRotate || _robotRotatePoint || _robotRotateAngle)
    {
        _robotRotate = 0;
        _robotRotatePoint = 0;
        _robotRotateAngle = 0;

        _robotIMUInit = _robotIMUAngle;

        calculateMotor(_robotRotate);
    }
}
//------------------------------------------------------------------------------
void robotSetACC(float fX, float fY)
{
    _robotY = fY;
		_robotX = fX;
}
//------------------------------------------------------------------------------
void robotCurve(int angle, int maxSpeed, float curve)
{
    if(_robotAngle != angle || _robotRunSpeed != maxSpeed || _robotCurve != curve)
    {
        _robotRunSpeed = maxSpeed;
				if(_robotCurrentSpeed == 0) _robotCurrentSpeed = 5;
        _robotIMUInit = _robotIMUAngle;
        _robotCurve = curve;
        _robotAngle = angle;
        _robotCounter = 0;
			
        calculateMotor(_robotRotate);
    }
}
//------------------------------------------------------------------------------
void robotRotate(int rotateAngle, float rotate, int rotatePoint)
{
    if(_robotRotateAngle != rotateAngle || _robotRotate != rotate || _robotRotatePoint != rotatePoint)
    {
        if(_robotAngle == 30000)
        {
            _robotRunSpeed = 99;//99
            _robotCurrentSpeed = 15;

            if(rotateAngle < 30000){//
							_robotAngleCounterFix = 1;
							if((rotate > 0 && _robotIMUAngle > rotateAngle) || (rotate < 0 && _robotIMUAngle < rotateAngle )) rotate = - rotate;        
						}
				}
        _robotRotateAngle = rotateAngle;
        _robotRotatePoint = rotatePoint;
        _robotRotate = rotate;
        _robotCounter = 0;
        		
        calculateMotor(_robotRotate);
    }
}
//------------------------------------------------------------------------------
void robotRotateFree(float rotate, int rotatePoint)
{
	robotRotate(30000, rotate, rotatePoint);
}
//----------------------------------------------------------------		
void robotRun(int angle, int maxSpeed)
{
	robotCurve(angle, maxSpeed, 0);
}
//============================================================================

void robotRunAngle(float angle, int maxSpeed, float robotAngle, float rotate)
{
    if(_robotRunAngle != angle || _robotRunSpeed != maxSpeed || _robotRotateAngle != robotAngle)
    {
			_robotRunAngle = angle;
			
			robotCurve(angle - _robotIMUAngle , maxSpeed, 0);
			
			robotRotate(robotAngle, (absF(robotAngle - _robotIMUAngle) > 50? (robotAngle > _robotIMUAngle ? rotate: -rotate):(robotAngle - _robotIMUAngle)*0.0005), 0);
		
		}
}
//------------------------------------------------------------------------------
void robotAngleAnalytics(void)
{
    if(_robotAngleCounterFix > 1)
    {
    	if(absI(_robotRotateAngle - _robotIMUAngle) < 5){ // 5
	    	if(_robotAngleCounterFix++ > 500) // 500
				{
						robotStop(0);
						return;
				}
	    }else{
				
					if(_robotAngleCounterFix > 250){
						_robotRunSpeed = 5;
						_robotCurrentSpeed = 5;
						_robotAngleCounterFix = 251;
					}else{
						_robotRunSpeed = 5;
						_robotCurrentSpeed = 5;
					}
					
	        if(_robotIMUAngle > _robotRotateAngle) _robotRotate = -1;
	        else _robotRotate = 1;
				
					calculateMotor(_robotRotate);
    	}
    }

}
//-----------------------------------------------------------------
// ham giu dau robot khi chay thang
// void robotDirectionAnalytics()
// {
//     // Khi chay duong cong hoac khong chay hoac quay tu do thi thoat
//     if(_robotCurve || !_robotCurrentSpeed || _robotRotateAngle >= 30000) return;
//     // Khi chay thang	
//     calculateMotor(fixMotorValue(_robotIMUInit - _robotIMUAngle));
// }

void robotDirectionAnalytics()
{
		float omegaFix;
		int error;
   // Khi chay duong cong hoac khong chay hoac quay tu do thi thoat
   if(_robotCurve || !_robotCurrentSpeed || _robotRotateAngle >= 30000) return;
	if (_robotRunSpeed > 0 && _robotRotate) {
        return;
    }
   // Khi co lenh xoay
   if(_robotRotate)
   {
       // Khi chi xoay tai cho
       if(_robotAngle == 30000)
       {
           if((_robotRotate > 0 && _robotIMUAngle > _robotRotateAngle - khoangCachGocFix) ||
              (_robotRotate < 0 && _robotIMUAngle < _robotRotateAngle + khoangCachGocFix)) 
						{
									if(_robotAngleCounterFix < 3){
												// Khi dung goc thi dung robot, khoa banh xe, va bat dau Fix Angle
												if(absI(_robotRotateAngle - _robotIMUAngle) < 10)
												{
														_robotAngleToFix = _robotRotateAngle;
														_robotCurrentSpeed = 5;
														_robotRunSpeed = 5;
														_robotRotate = 0;
														_robotAngleCounterFix = 2;

														calculateMotor(_robotRotate);
													
														return;
												}else{
													if(_robotRotateAngle > _robotIMUAngle)
														calculateMotor((float)(f6 + absF(_robotCurrentSpeed*_robotRotate/khoangCachGocFix)*absI(_robotRotateAngle - _robotIMUAngle))/_robotCurrentSpeed);
													else
														calculateMotor(-(float)(f6 + absF(_robotCurrentSpeed*_robotRotate/khoangCachGocFix)*absI(_robotRotateAngle - _robotIMUAngle))/_robotCurrentSpeed);
													
												}
									}
           }else calculateMotor(_robotRotate);
       }
        else
       {// Vua chay thang vua xoay
            if((_robotRotate > 0 && _robotIMUAngle > _robotRotateAngle - _robotCurrentSpeed*_robotRotate - i100) ||
             (_robotRotate < 0 && _robotIMUAngle < _robotRotateAngle - _robotCurrentSpeed*_robotRotate + i100))
          {
	 			calculateMotor(0);
           }
          // else calculateMotor(_robotRotate);//---- Neu chua dat den goc can quay ----------
       }
       
       return;
   }

   // Khi chay thang 
   calculateMotor(fixMotorValue(_robotIMUInit - _robotIMUAngle));
	 if (!(_robotRunSpeed > 0 
          && _robotCurve == 0 
          && _robotRotate == 0 
          && _robotRotateAngle >= 30000))
    {
        // Mọi trường hợp khác (xoay, cong, stop) đều thoát
        return;
    }
		
			error = _robotIMUInit - _robotIMUAngle;
    if (error >  1800) error -= 3600;
    if (error < -1800) error += 3600;

    // Nếu lệch quá nhỏ thì không chỉnh
    if (abs(error) < 1) {
        calculateMotor(0);
        return;
    }

    // Tính omega để bẻ về
    omegaFix = FixOmegaFromIMU();
    calculateMotor(omegaFix);
}

//==========================================================================================
void ac_Stop(void)
{
		if(_robotAngleCounterFix < 3){
			_robotCurve = 0;
			_robotRotate = 0;
			_robotRotatePoint = 0;
			_robotAngle = 30000;
			_robotRunAngle = 30000;
			_robotRotateAngle = 0;
    }
		//-------------------------------------
		if(++_robotCounter < motorLockRepeat) setAllMotor(motorLock);
		else {
			_robotCounter = motorLockRepeat;
			if(_lockRobot) setAllMotor(motorLock);
			else setAllMotor(0);
		}
}
//------------------------------------------------------------------------------
void ac_SpeedACC(int acc, int n)
{
	if(++_robotCounter > acc)
    {
        _robotCurrentSpeed += n;
        _robotCounter = 0;
    }
}
//------------------------------------------------------------------------------
void robotAnalytics(void)//-------- Dat trong Interup Timer ---------
{
		_robotIMUAngle = robotAngle();
	
    //======= Fix goc robot ==========
		robotAngleAnalytics();

    //======= Gia toc di chuyen ==========
    if(_robotRunSpeed > 0)// Robot dang duoc ra lenh chay
    {
        if(_robotCurrentSpeed != _robotRunSpeed)
        {
            if(_robotCurrentSpeed < _robotRunSpeed)
            {
            	if(_robotCurrentSpeed < _robotMaxSpeed) ac_SpeedACC(giaToc(_robotCurrentSpeed), 1); //--- Phuong trinh Gia toc --------	
            }
						else ac_SpeedACC(giamToc(_robotCurrentSpeed), -1); //--- Phuong trinh Giam toc --------
			
        }
    }
    else  //-------- Robot duoc lenh Stop -----------
        if(_robotCurrentSpeed > 0) ac_SpeedACC(_robotAccStop, -1); //-------- Giam toc do -----------
				else{
					ac_Stop();
					return;
				}
	
		//======= Fix robot theo IMU ==========
    if(_IMUAngle_Before != _robotIMUAngle)
    {
        robotDirectionAnalytics();
        _IMUAngle_Before = _robotIMUAngle;
    }

    //======= Thiet lap thong so dong co ==========
     if(_robotChange) {	setMotor(roundF(_robotCurrentSpeed * _robotRun0h), roundF(_robotCurrentSpeed * _robotRun4h), roundF(_robotCurrentSpeed * _robotRun8h));
					SetRotateMotor(_robotRotate0h, _robotRotate4h, _robotRotate8h);
									
		 }
}
