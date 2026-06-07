//Author by Nguyen Nho Phong Vu
//Date version: 17/8/2024 version 1 - 3 Wheel config
//Date version: 17/8/2024 version 2 - 3 Wheel math
#include <stdlib.h>
#include <math.h>
#define pi 3.1415
#define M_PI 3.14159265358979323846
//=============================LUC_BAN & GOC_BAN===============================================



vs16 IMU;

//=================================================
//--------------- Cac hang so ---------------------
//=================================================
int robotLimitSpeed = 250;  // Toc do toi da se chinh la fixDirError + maxSpeed
float f05 = 0.5, f1 = 1.0, f2 = 2.0, f4 = 4.0, f5 = 5.0, f6 = 6.0, f10 = 10.0, f20 = 20.0, f30 = 30.0, f45 = 45.0, f60 = 60.0, f120 = 120.0;
int i100 = 80, khoangCachGocFix = 120;

//------------ su dung cho ham gia toc bac 1 tuyen tinh--------------
float _robotY = 50;
float _robotX = 120;

int motorLock = 2;
int motorLockRepeat = 200000;//20000
float radian = 3.141592653589793238462643/180;
//=================================================
//------ Bien toan cuc de dieu khien ------
//=================================================
int _robotChange=0, _robotRotatePoint=0;
int _robotCurrentSpeed=0, _robotRunSpeed=0, _robotMaxSpeed=0;
int _robotAccStop=0, _robotCounter=0;
int _robotAngle = 30000, _robotRunAngle = 30000, _robotRotateAngle=0, _robotIMUInit=0, _wheelRotateAngle;
float _robotRotate=0, _robotCurve=0;
int _robotAngleCounterFix=0, _robotAngleToFix=30000;

int _robotIMUAngle=0,_IMUAngle_Before=0, _robotDelayGiamToc = 17; //15
float _robotRunFL=0, _robotRunFR=0, _robotRunRL=0, _robotRunRR=0;

float _robotDirFL=0, _robotDirFR=0, _robotDirRL=0, _robotDirRR=0;

float _robotRotateFL=0, _robotRotateFR=0, _robotRotateRL=0, _robotRotateRR=0;

int Rear_Left_Wheel_Angle, Rear_Right_Wheel_Angle, Front_Left_Wheel_Angle, Front_Right_Wheel_Angle;
int Rear_Left_Wheel_Angle_dir, Rear_Right_Wheel_Angle_dir, Front_Left_Wheel_Angle_dir, Front_Right_Wheel_Angle_dir, dir;

float Vx, Vy, A, B, C, D, WL, WW, _Omega, Robot_Width = 0.28, Robot_Lenght = 0.28, Vy10, Vx10, ABCD;

extern int	current_RL_Angle, current_RR_Angle, current_FL_Angle, current_FR_Angle;

int _lockRobot = 0;
//==========================================================================================
//==========================================================================================


//******************************************************** cap nhat go hien tai ******************************************************************
void	Curent_angle_4_wheel(void)
{
	current_RL_Angle = ENCODER_RL();
	current_RR_Angle = ENCODER_RR();
	current_FL_Angle = ENCODER_FL();
	current_FR_Angle = ENCODER_FR();
}

int close_angle(int targetAngle, int currentAngle)
{
	int goc_den, goc_doi, gd;
	
	goc_doi = fmod(targetAngle,3600);
	if(goc_doi >= 0)			goc_doi = goc_doi - 1800;		//tinh goc doi
	else									goc_doi = goc_doi + 1800;

	goc_den = fmod(targetAngle,3600) - fmod(currentAngle,3600);
	
	if(abs(goc_doi)	<  abs(goc_den))	{goc_den = goc_doi; dir = -1;}
	else															{goc_den = targetAngle;	dir = 1;}
	
	return goc_den;
}

//==========================================================================================
vu8 motorMinFix(int S)
{
	if(S > 250)	S = 250;
	else	if(S < 3)	S = 2;
	else;
	
	return S;
}
//-----------------------------------------------------------------------------------
void setMotor(int speed_FL, int speed_FR, int speed_RL, int speed_RR)
{
	if(!speed_FL) Mor_FrontLeft = motorLock;
	else if(_robotDirFL>0)
 	{
	 	Mor_FrontLeft = motorMinFix(speed_FL);
		Mor_FrontLeft_next;
 	}
	else{
		Mor_FrontLeft = motorMinFix(-speed_FL);
		Mor_FrontLeft_back;
 	}

	if(!speed_FR) Mor_FrontRight = motorLock;
	else if(_robotDirFR>0)
 	{
	 	Mor_FrontRight = motorMinFix(speed_FR);
		Mor_FrontRight_next;
 	}
	else{
		Mor_FrontRight = motorMinFix(-speed_FR);
		Mor_FrontRight_back;
 	}

	if(!speed_RL) Mor_RearLeft = motorLock;
	else if(_robotDirRL>0)
 	{
	 	Mor_RearLeft = motorMinFix(speed_RL);
		Mor_RearLeft_next;
 	}
	else{
		Mor_RearLeft = motorMinFix(-speed_RL);
		Mor_RearLeft_back;
 	}

 	if(!speed_RR) Mor_RearRight = motorLock;
	else if(_robotDirRR>0)
 	{
	 	Mor_RearRight = motorMinFix(speed_RR);
		Mor_RearRight_next;
 	}
	else{
		Mor_RearRight = motorMinFix(-speed_RR);
		Mor_RearRight_back;
 	}
}

void SetRotateMotor(int	Angle_robotRotateFL, int	Angle_robotRotateFR, int	Angle_robotRotateRL, int	Angle_robotRotateRR)
{
	Front_Left_Wheel_Angle = Angle_robotRotateFL;
	Front_Right_Wheel_Angle = Angle_robotRotateFR;
	Rear_Left_Wheel_Angle = Angle_robotRotateRL;
	Rear_Right_Wheel_Angle = Angle_robotRotateRR;
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
	else 	if(T < 0) return (T*0.2 - 0.4)/_robotCurrentSpeed; // tuy thuoc robot ma co the he so toi thieu la 0.5, 1, 2...
				else 			return (T*0.2 + 0.4)/_robotCurrentSpeed;
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
void swervecalculatemotor(float anglecal, float Omegacal)
{
		int R;
		R = sqrtf(powf(Robot_Lenght,Robot_Width));

		WL = (float)(Omegacal);
		WW = (float)(Omegacal);

		Vx = (float)(sinf(anglecal)*2);
		Vy = (float)(cosf(anglecal)*2);
		
		Vy10 = Vy*10;
		Vx10 = roundF(sinf(anglecal));
				
		A = Vx - WL;
		B = Vx + WL;
		C = Vy - WW;
		D = Vy + WW;
		
		_robotRotateFR = atan2f(B,C)*1800/pi;
		_robotRotateFR = close_angle(_robotRotateFR, current_FR_Angle);
		_robotDirFR = dir;
		_robotRunFR = sqrtf(B*B+C*C)*dir;
		
		_robotRotateFL = atan2f(B,D)*1800/pi;
		_robotRotateFL = close_angle(_robotRotateFL, current_FL_Angle);
		_robotDirFL = dir;
		_robotRunFL = sqrtf(B*B+D*D)*dir;

		_robotRotateRL = atan2f(A,D)*1800/pi;
		_robotRotateRL = close_angle(_robotRotateRL, current_RL_Angle);
		_robotDirRL = dir;
		_robotRunRL = sqrtf(A*A+D*D)*dir;
		
		_robotRotateRR = atan2f(A,C)*1800/pi;	
		_robotRotateRR = close_angle(_robotRotateRR, current_RR_Angle);
		_robotDirRR = dir;
		_robotRunRR = sqrtf(A*A+C*C)*dir;
}
//==========================================================================================
//------------------------------------------------------------------------------
void calculateMotor(float rotate)
{
		float angle;
		
	if(_robotAngle == 30000)// khi robot quay tai cho
	{
		_Omega = (float)(rotate*450); 
		swervecalculatemotor(0, _Omega);	
		_robotRunFL = _robotRunFR = _robotRunRL = _robotRunRR = 0;
	
	}
	else // khi robot vua chay vua quay
	{
		//angle = (float)(_robotAngle* radian/f10);
		angle = (float)(_robotAngle - (_robotIMUAngle - _robotIMUInit))* radian/f10;
		//_Omega = (float)_robotRotate; 
		_Omega = (float)_robotRotate;
		swervecalculatemotor(angle, _Omega);
	}

	if(rotate){
		
		switch(_robotRotatePoint)
		{
			case 0:
			if(Vy10 <-10 || Vy10 >10)
				{
					_robotRunFL += rotate ;
					_robotRunFR -= rotate ;
					_robotRunRL += rotate ;
					_robotRunRR -= rotate ;
				}
				else
				{
					_robotRunFL += Vx*_robotDirFL*rotate;
					_robotRunFR += Vx*_robotDirFR*rotate;
					_robotRunRL -= Vx*_robotDirRL*rotate;
					_robotRunRR -= Vx*_robotDirRR*rotate;	
				}
					
					break;
			case 1:
					_robotRunFR -= rotate;
					_robotRunRL += rotate;
					_robotRunRR -= rotate;
					break;
			case 2:
					_robotRunFL += rotate;
					_robotRunRL += rotate;
					_robotRunRR -= rotate;
					break;
			case 3:
					_robotRunFL += rotate;
					_robotRunFR -= rotate;
					_robotRunRR -= rotate;
					break;
			case 4:
					_robotRunFL += rotate;
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
            _robotRunSpeed = 50;//99
            _robotCurrentSpeed = 10;

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
	//_wheelRotateAngle = angle;
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
    	if(absI(_robotRotateAngle - _robotIMUAngle) < 5){
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
									if(_robotAngleCounterFix < 5){
												// Khi dung goc thi dung robot, khoa banh xe, va bat dau Fix Angle
												if(absI(_robotRotateAngle - _robotIMUAngle) < 50)
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
														calculateMotor((float)(5 + absF(_robotCurrentSpeed*_robotRotate/khoangCachGocFix)*absI(_robotRotateAngle - _robotIMUAngle))/_robotCurrentSpeed);
													else
														calculateMotor(-(float)(5 + absF(_robotCurrentSpeed*_robotRotate/khoangCachGocFix)*absI(_robotRotateAngle - _robotIMUAngle))/_robotCurrentSpeed);
													
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
     if(_robotChange) {	setMotor(roundF(_robotCurrentSpeed * _robotRunFL), roundF(_robotCurrentSpeed * _robotRunFR), roundF(_robotCurrentSpeed * _robotRunRL), roundF(_robotCurrentSpeed * _robotRunRR));
												SetRotateMotor(_robotRotateFL, _robotRotateFR, _robotRotateRL, _robotRotateRR);
									
		 }
}