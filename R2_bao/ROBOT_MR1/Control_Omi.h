#include <stdlib.h>
#include <math.h>



float GIA_TOC,TOC_DO=2,CHAY_VA_XOAY,HUONG,MAT_ROBOT; 
float luong_giac_trai,luong_giac_phai,luong_giac_sau;
const  float radian= 3.141592653589793238462643/180;
vs32 chuyen_che_do;
int TOC_DO_XOAY,BIT_XOAY,GOC_LECH;
int MOTOR_LOCK,CHAY_GIA_TOC=0,Tam_Xoay=0; 
int trai,phai,sau,TOC_DO_DAT,ROBOT_STOP;
void RUN_XOAY_TRON(vs32 _toc_do,float _gia_toc);
float trai_1,phai_1,sau_1;
float trai_float,phai_float,sau_float;   //gia_toc_dieu_xung=0.07;
//////////////////////xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx//////////////////////////

	
void MAIN_CONTROL(vs32 _mat_robot,vs32 _huong,vs32 _toc_do_chay,float _gia_toc,float _chay_va_xoay)		
		{		
			
			  chuyen_che_do=0;
				if(abs(_huong)==40000){HUONG =	_huong;RUN_XOAY_TRON(_toc_do_chay,_gia_toc);}
		
				else{
						BIT_XOAY		=	0;
						HUONG				=	_huong;
						GIA_TOC			=	_gia_toc;
						ROBOT_STOP	=	0;
						MOTOR_LOCK	=	1000;	
						CHAY_GIA_TOC=	10;
						TOC_DO_DAT 	= _toc_do_chay;		
						MAT_ROBOT	 	= _mat_robot;	
						CHAY_VA_XOAY=	_chay_va_xoay;			
						if(TOC_DO==0)TOC_DO=	4;
						

					
						luong_giac_trai=(float)(sin(((600 -HUONG)/10)*radian));
						luong_giac_phai=(float)(sin(((-600 -HUONG)/10)*radian));
						luong_giac_sau=(float)(sin(((1800 -HUONG)/10)*radian));
					
					}
}	
		
////xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx	
void robotResetIMU(void)
{
	run_read_gyro_uart1();
}
////xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx	
void RUN_XOAY()
	{					
						MAT_ROBOT	=	MAT_ROBOT	-	CHAY_VA_XOAY;
						HUONG			=	HUONG	+	CHAY_VA_XOAY;	

					
						luong_giac_trai=(float)(sin(((600 -HUONG)/10)*radian));
						luong_giac_phai=(float)(sin(((-600 -HUONG)/10)*radian));
						luong_giac_sau=(float)(sin(((1800 -HUONG)/10)*radian));

	}
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx	
void STOP_ROBOT(void)		
{						
						TOC_DO_DAT 	= 0;	
						TOC_DO_XOAY	=	0;
						BIT_XOAY		=	0;
					//	CHAY_GIA_TOC=	0;
						TOC_DO			=	0;
}		
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx	
void RUN_XOAY_TRON(vs32 _toc_do,float _gia_toc)		
		{				BIT_XOAY		=	10;
						GIA_TOC			=	_gia_toc;		
						TOC_DO_DAT 	= abs(_toc_do);	
						CHAY_VA_XOAY=	0;
						//TOC_DO			=	2;
			                   
			            
						if(HUONG>0){mor_4h_back;mor_8h_back;mor_0h_next;}
						else if(HUONG<0){mor_4h_next;mor_8h_next;mor_0h_back;}
}	                 //       
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx	
void TINH_GOC_LECH()		
{				
						
							GOC_LECH=(IMU-MAT_ROBOT)/5; // do dap ung
	
						trai =	(int)(luong_giac_trai*TOC_DO  + GOC_LECH);
						phai =	(int)(luong_giac_phai*TOC_DO  + GOC_LECH);	
						sau  =	(int)(luong_giac_sau*TOC_DO  + GOC_LECH);	

							if(trai>0){ mor_4h_back;}
							else {mor_4h_next;} 
							
							if(phai<0){ mor_8h_next;}
							else {mor_8h_back;} 

							if(sau<0){ mor_0h_back;}
							else {mor_0h_next;} 							

								if ( abs(trai) < 3)trai_1=2;
								else if(abs(trai)>254)trai_1=254;
								else trai_1=abs(trai);									
								
								if ( abs(phai) < 3)phai_1=2;
								else if(abs(phai)>254)phai_1=254;
								else phai_1=abs(phai);	
							
								if ( abs(sau) < 3)sau_1=2;
								else if(abs(sau)>254)sau_1=254;
								else sau_1=abs(sau);	


//////////////////////////////////////HÀM GIA TÔC//////////////////

					
}
///////////////////////////////////////////////////
void RUN_OMI(){

/////////////////
	
	
					if(TOC_DO>TOC_DO_DAT){
									if(TOC_DO<15)TOC_DO=TOC_DO-1;						
									else TOC_DO=TOC_DO-GIA_TOC;
						
									if(TOC_DO<TOC_DO_DAT)TOC_DO=TOC_DO_DAT; 				
								}
						else if(TOC_DO<TOC_DO_DAT){	
									if(TOC_DO<15)TOC_DO=TOC_DO+1;
									else TOC_DO=TOC_DO+GIA_TOC;
							
									if(TOC_DO>TOC_DO_DAT)TOC_DO=TOC_DO_DAT; 
								}

						else {
									if(TOC_DO<=3)STOP_ROBOT();
									else {TOC_DO=TOC_DO_DAT;}				
								}		

					


////////////////
	
	
	if(BIT_XOAY==10)
		{
			
											if(TOC_DO>abs(TOC_DO_DAT))
												  {
														TOC_DO=TOC_DO-GIA_TOC;
														if(TOC_DO<abs(TOC_DO_DAT))TOC_DO=abs(TOC_DO_DAT); 				
													}
											else if(TOC_DO<abs(TOC_DO_DAT))
												  {														
														TOC_DO=(float)TOC_DO+GIA_TOC;
														if(TOC_DO>abs(TOC_DO_DAT))TOC_DO=abs(TOC_DO_DAT); 
													}
											else 
												  {
														if(TOC_DO<=3)STOP_ROBOT();
														else{TOC_DO=TOC_DO_DAT;}
													}
							MOTOR_LOCK=1000;trai_1=phai_1=sau_1=TOC_DO;
		}	
////////////////////////////////////////////////////		
		else{
				if(TOC_DO_DAT>2&&CHAY_GIA_TOC==10)
					{ 
						MOTOR_LOCK=1000;
						if(CHAY_VA_XOAY!=0){RUN_XOAY();} 
						TINH_GOC_LECH();	
					}
			  else
						{	
							if(MOTOR_LOCK<=0){MOTOR_LOCK=0;TOC_DO=2;trai_1=phai_1=sau_1=0;	STOP_ROBOT();}
							else{																					
								if(TOC_DO<=2)
									{
									  banh_trai=banh_phai=banh_sau=TOC_DO=2;
										
									  trai=phai=sau=0;
									  trai_1=phai_1=sau_1=2;
									  trai_float=phai_float=sau_float=0;
									  MOTOR_LOCK--;
									
								  }
								else {

									if (HUONG==40000){
										TOC_DO=TOC_DO-GIA_TOC;
										phai_1=trai_1=sau_1=TOC_DO;
									}
									else {TINH_GOC_LECH();}	
													
								}
							
							}		
					}			
				}
		

	if(Tam_Xoay==0)
	{
			banh_trai=trai_1;
			banh_phai=phai_1;
			banh_sau=sau_1;
	}
	else if(Tam_Xoay==1)
		 {
			banh_trai=2;
			banh_phai=phai_1;
			banh_sau=sau_1;		
		}	
	 else if(Tam_Xoay==2){
			banh_trai=trai_1;
			banh_phai=2;
			banh_sau=sau_1;		
		}		 
	 	 else if(Tam_Xoay==3){
			banh_trai=trai_1;
			banh_phai=phai_1;
			banh_sau=2;		
		}	
		else{
			banh_trai=trai_1=2;
			banh_phai=phai_1=2;
			banh_sau=sau_1=2;		
			TOC_DO=TOC_DO_DAT=2;
			TOC_DO_DAT 	= 0;	
			TOC_DO_XOAY	=	0;
			BIT_XOAY		=	0;			
			TOC_DO			=	0;
		}			 

				
}	


///////////////////////////////////////////
void Robot_Stop_Now(vs32 _Tam_Xoay)
{
	Tam_Xoay=_Tam_Xoay;	
	if(Tam_Xoay==0)
	{
			banh_trai=trai_1;
			banh_phai=phai_1;
			banh_sau=sau_1;
	}
	else if(Tam_Xoay==1)
		 {
			banh_trai=2;
			banh_phai=phai_1;
			banh_sau=sau_1;		
		}	
	 else if(Tam_Xoay==2){
			banh_trai=trai_1;
			banh_phai=2;
			banh_sau=sau_1;		
		}		 
	 	 else if(Tam_Xoay==3){
			banh_trai=trai_1;
			banh_phai=phai_1;
			banh_sau=2;		
		}	
		else{
			banh_trai=trai_1=2;
			banh_phai=phai_1=2;
			banh_sau=sau_1=2;		
			TOC_DO=TOC_DO_DAT=2;
			TOC_DO_DAT 	= 0;	
			TOC_DO_XOAY	=	0;
			BIT_XOAY		=	0;			
			TOC_DO			=	0;
		}			 
	
}



