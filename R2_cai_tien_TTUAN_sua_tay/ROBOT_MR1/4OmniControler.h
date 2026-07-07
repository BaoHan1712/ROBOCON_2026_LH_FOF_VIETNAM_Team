/*
//================================================
* 4 Omni Robot Controler
* Created: 03/2017 12:30:00
* Author: Huynh Cao Tuan
* Development: Han Quoc Bao
//================================================

	void robotAnalytics(void) // Dat trong timer de Robot hoat dong
	//----------------------
	void robotRun(int angle, int maxSpeed)
	void robotCurve(int angle, int maxSpeed, float curve)

	vidu: robotRun(450, 70)
			Chay Robot huong:	450
			Toc do toi da: 		70
	//----------------------
	void (float angle, int maxSpeed, float robotAngle)
	
	vidu:
		while(.....){
			robotRunAngle(900, 70, 450) Chay Robot huong la ban 900. Và quay dau robot huong 450.
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
int robotLimitSpeed = 254;  // Toc do toi da se chinh la fixDirError + maxSpeed
float f05 = 0.5, f1 = 1.0, f2 = 2.0, f4 = 4.0, f5 = 5.0, f6 = 6.0, f10 = 10.0, f20 = 20.0, f30 = 30.0, f45 = 45.0, f60 = 60.0, f120 = 120.0;
int i100 = 100, khoangCachGocFix = 200;

//------------ su dung cho ham gia toc bac 1 tuyen tinh--------------

float _robotX = 120;
float _robotY = 85; // gia toc xuat phat


int motorLock = 2;
int motorLockRepeat = 100000;//20000
float radian = 3.141592653589793238462643/180;
//=================================================
//------ Bien toan cuc de dieu khien ------
//=================================================
int _robotChange=0, _robotRotatePoint=0;
int _robotCurrentSpeed=0, _robotRunSpeed=0, _robotMaxSpeed=0;
int _robotAccStop=0, _robotCounter=0;
int _robotAngle = 30000, _robotRunAngle = 30000, _robotRotateAngle=0, _robotIMUInit=0;
float _robotRotate=0, _robotCurve=0;
int _robotAngleCounterFix=0, _robotAngleToFix=30000;

int _robotIMUAngle=0,_IMUAngle_Before=0, _robotDelayGiamToc = 17; //15
float _robotRunFL=0, _robotRunFR=0, _robotRunRL=0, _robotRunRR=0;

int _lockRobot = 0;
//==========================================================================================
//==========================================================================================
//==========================================================================================
vu8 motorMinFix(vu8 S)
{
	return (S < 5 ? 0 : S);
}
//-----------------------------------------------------------------------------------
void setMotor(int speed_FL, int speed_FR, int speed_RL, int speed_RR)
{
	if(!speed_FL) Mor_FrontLeft = motorLock;
	else if(speed_FL > 0)
 	{
	 	Mor_FrontLeft = motorMinFix(speed_FL);
		Mor_FrontLeft_thuan;
 	}else{
		Mor_FrontLeft = motorMinFix(-speed_FL);
		Mor_FrontLeft_nghich;
 	}

	if(!speed_FR) Mor_FrontRight = motorLock;
	else if(speed_FR > 0)
 	{
	 	Mor_FrontRight = motorMinFix(speed_FR);
		Mor_FrontRight_thuan;
 	}else{
		Mor_FrontRight = motorMinFix(-speed_FR);
		Mor_FrontRight_nghich;
 	}

	if(!speed_RL) Mor_RearLeft = motorLock;
	else if(speed_RL > 0)
 	{
	 	Mor_RearLeft = motorMinFix(speed_RL);
		Mor_RearLeft_thuan;
 	}else{
		Mor_RearLeft = motorMinFix(-speed_RL);
		Mor_RearLeft_nghich;
 	}

 	if(!speed_RR) Mor_RearRight = motorLock;
	else if(speed_RR > 0)
 	{
	 	Mor_RearRight = motorMinFix(speed_RR);
		Mor_RearRight_thuan;
 	}else{
		Mor_RearRight = motorMinFix(-speed_RR);
		Mor_RearRight_nghich;
 	}
}
//------------------------------------------------------------------------------
void setAllMotor(int speed)
{
	Mor_FrontLeft = speed;
	Mor_FrontRight = speed;
	Mor_RearLeft = speed;
	Mor_RearRight = speed;
}
//------------------------------------------------------------------------------
int robotIsStop()
{
    return Mor_FrontLeft < 3 && Mor_FrontRight < 3 && Mor_RearLeft < 3 && Mor_RearRight < 3;
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
float fixMotorValue(int T)
{
	if(T == 0) 			return 0;
	else 	if(T < 0) return (T*0.15 - 0.2)/_robotCurrentSpeed; // tuy thuoc robot ma co the he so toi thieu la 0.5, 1, 2...
				else 			return (T*0.15 + 0.2)/_robotCurrentSpeed;
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
int giaToc(int x)
{
	// ------ gia toc bac 1 -----------
	float y = (-_robotY/_robotX)*x + _robotY;
	
	return (int)y;
}
//------------------------------------------------------------------------------
float maxF4(float N1, float N2, float N3, float N4)
{
	float _maxNum = 0.001;
	if(N1<0) N1 = -N1;
	if(N2<0) N2 = -N2;
	if(N3<0) N3 = -N3;
	if(N4<0) N4 = -N4;

	if(N1>_maxNum) _maxNum = N1;
	if(N2>_maxNum) _maxNum = N2;
	if(N3>_maxNum) _maxNum = N3;
	if(N4>_maxNum) _maxNum = N4;

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
//==========================================================================================
//------------------------------------------------------------------------------
void calculateMotor(float rotate)
{
		float angle;

	if(_robotAngle == 30000)// khi robot quay tai cho
	{
		_robotRunFL = _robotRunFR = _robotRunRL = _robotRunRR = 0;
	}
	else // khi robot vua chay vua quay
	{
		angle = (float)(_robotAngle - (_robotIMUAngle - _robotIMUInit));// - _robotRotate * f30);		
		angle = radian * (angle/f10 + f45);

		_robotRunRR = sinf(angle)*2;
		_robotRunRL = cosf(angle)*2;

		_robotRunFL = _robotRunRR + _robotCurve;
		_robotRunFR = _robotRunRL - _robotCurve;
	}

	if(rotate){
		switch(_robotRotatePoint)
		{
			case 0:
					_robotRunFL += rotate;
					_robotRunFR -= rotate;
					_robotRunRL += rotate;
					_robotRunRR -= rotate;
					break;
			case 1:
					_robotRunFR -= rotate;
					_robotRunRL += rotate;
					_robotRunRR -= rotate*f2;
					break;
			case 2:
					_robotRunFL += rotate;
					_robotRunRL += rotate*f2;
					_robotRunRR -= rotate;
					break;
			case 3:
					_robotRunFL += rotate;
					_robotRunFR -= rotate*f2;
					_robotRunRR -= rotate;
					break;
			case 4:
					_robotRunFL += rotate*f2;
					_robotRunFR -= rotate;
					_robotRunRL += rotate;
					break;
		}
	}

	//----------- tinh toc do toi da ----------------
	_robotMaxSpeed = (int)(robotLimitSpeed/maxF4(_robotRunFL, _robotRunFR, _robotRunRL, _robotRunRR));
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
            _robotRunSpeed = 40;//99
            if(_robotCurrentSpeed == 0 ) _robotCurrentSpeed = 10;

            if(rotateAngle < 30000){// Quay theo goc no do
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
//------------------------------------------------------------------------------		
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
			robotRotate(robotAngle, (abs(robotAngle - _robotIMUAngle) > 100? (robotAngle > _robotIMUAngle ? rotate: -rotate):(robotAngle - _robotIMUAngle)*0.005), 0);
		}
}
//------------------------------------------------------------------------------
void robotAngleAnalytics(void)
{
    if(_robotAngleCounterFix > 1)
    {
    	if(absI(_robotRotateAngle - _robotIMUAngle) < 10){
	    	if(_robotAngleCounterFix++ > 500)  
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
void robotDirectionAnalytics()
{
    // Khi chay duong cong hoac khong chay hoac quay tu do thi thoat
    if(_robotCurve || !_robotCurrentSpeed || _robotRotateAngle >= 30000) return;
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
												if(absI(_robotRotateAngle - _robotIMUAngle) < 8)
												{
														_robotAngleToFix = _robotRotateAngle;
														_robotCurrentSpeed = 0;
														_robotRunSpeed = 0;
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
								calculateMotor(fixMotorValue(_robotRotateAngle - _robotIMUAngle));
            }
            else calculateMotor(_robotRotate);//---- Neu chua dat den goc can quay ----------
        }
        
        return;
    }

    // Khi chay thang	
    calculateMotor(fixMotorValue(_robotIMUInit - _robotIMUAngle));
}

//==========================================================================================
void ac_Stop(void)
{
		if(_robotAngleCounterFix < 2){
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
						else ac_SpeedACC(_robotDelayGiamToc, -1); //--- Phuong trinh Giam toc --------
        }
    }
    else  //-------- Robot duoc lenh Stop -----------
        if(_robotCurrentSpeed > 0) ac_SpeedACC(_robotAccStop, -2); //-------- Giam toc do -----------
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
     if(_robotChange) setMotor(roundF(_robotCurrentSpeed * _robotRunFL), roundF(_robotCurrentSpeed * _robotRunFR), roundF(_robotCurrentSpeed * _robotRunRL), roundF(_robotCurrentSpeed * _robotRunRR));
}


void robotRotateCompass(int goc_la_ban_tuyet_doi, float toc_do_quay, int tam_quay, int sai_so)
{
    int current_imu = robotAngle();
    float actual_rotate = absF(toc_do_quay);

    if (absI(goc_la_ban_tuyet_doi - current_imu) <= sai_so) {
        return; 
    }

    if (goc_la_ban_tuyet_doi < current_imu) {
        actual_rotate = -actual_rotate;
    }

    _robotAngleCounterFix = 1; 
    _robotRotateAngle = goc_la_ban_tuyet_doi; 
    _robotRotatePoint = tam_quay;
    _robotRotate = actual_rotate;
    _robotCounter = 0;

    if(_robotAngle == 30000)
    {
        _robotRunSpeed = 30;
        if(_robotCurrentSpeed == 0) _robotCurrentSpeed = 10;
    }

    calculateMotor(_robotRotate);

    while(robotFixAngle() > 0)
    {

    }
}


// than so toi uu la robotRotateQuick(900, 1.6, 0, 0.2, 300); 
void robotRotateQuick(int goc_la_ban, float toc_do_quay, int tam_quay, float min_toc, int vung_giam)
{
    int current_imu = robotAngle();
    float actual_rotate = absF(toc_do_quay);
    float slow_rotate = min_toc;
    int vung_giam_toc = vung_giam;
    int is_slow_mode = 0;
		int goc_la_ban_tuyet_doi = goc_la_ban - 16;

    if (absI(goc_la_ban_tuyet_doi - current_imu) <= 10) {
        return; 
    }

    if (goc_la_ban_tuyet_doi < current_imu) {
        robotRotateFree(-actual_rotate, tam_quay);
        
        while ((current_imu = robotAngle()) > goc_la_ban_tuyet_doi) {
            if (!is_slow_mode && (current_imu - goc_la_ban_tuyet_doi) <= vung_giam_toc) {
                robotRotateFree(-slow_rotate, tam_quay);
                is_slow_mode = 1;
            }
        }
    } else {
        robotRotateFree(actual_rotate, tam_quay);
        
        while ((current_imu = robotAngle()) < goc_la_ban_tuyet_doi) {
            if (!is_slow_mode && (goc_la_ban_tuyet_doi - current_imu) <= vung_giam_toc) {
                robotRotateFree(slow_rotate, tam_quay);
                is_slow_mode = 1;
            }
        }
    }
    
    robotStop(0);
}
//==========================================================================================

