#include <stdlib.h>
#include <math.h>


float GIA_TOC; 
float luong_giac_tt,luong_giac_pt,luong_giac_ts,luong_giac_ps;
const  float radian= 3.141592653589793238462643/180;

////bien chua so nguyen
int TOC_DO_XOAY,BIT_XOAY,GOC_LECH;
int HUONG,TOC_DO,MOTOR_LOCK,MAT_ROBOT,CHAY_VA_XOAY,CHAY_GIA_TOC=0; 
int trai_truoc1,phai_truoc1,trai_sau1,phai_sau1,TOC_DO_DAT,ROBOT_STOP;

//////////////////////xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx//////////////////////////

	
void RUN_3_BANH(int _mat_robot,int _huong,int _toc_do_chay,float _gia_toc,int _chay_va_xoay)		
		{				BIT_XOAY		=	0;
						HUONG				=	_huong;
						GIA_TOC			=	_gia_toc;
						ROBOT_STOP	=	0;
						MOTOR_LOCK	=	0;	
						CHAY_GIA_TOC=	10;
						TOC_DO_DAT 	= _toc_do_chay;		
						MAT_ROBOT	 	= _mat_robot;	
						CHAY_VA_XOAY=	_chay_va_xoay;
						TOC_DO			=	2;
			
						luong_giac_tt=(float)(sin(((450 -HUONG)/10)*radian));
						luong_giac_ts=(float)(sin(((1350-HUONG)/10)*radian));
						luong_giac_ps=(float)(sin(((2250-HUONG)/10)*radian));
						luong_giac_pt=(float)(sin(((3150-HUONG)/10)*radian));	
			
}	
		
////xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx	
//void RUN_XOAY()
//	{
//						MAT_ROBOT	=	MAT_ROBOT	-	CHAY_VA_XOAY;
//						HUONG			=	HUONG	+	CHAY_VA_XOAY;	
//		
//						luong_giac_tt=(float)(sin(((450 -HUONG)/10)*radian))*TOC_DO;
//						luong_giac_ts=(float)(sin(((1350-HUONG)/10)*radian))*TOC_DO;
//						luong_giac_ps=(float)(sin(((2250-HUONG)/10)*radian))*TOC_DO;
//						luong_giac_pt=(float)(sin(((3150-HUONG)/10)*radian))*TOC_DO;		
//	}
////xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx	
//void STOP_ROBOT()		
//{						
//						TOC_DO_DAT 	= 0;	
//						TOC_DO_XOAY	=	0;
//						BIT_XOAY		=	0;
//						CHAY_GIA_TOC=	0;
//}		
////xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx	
//void RUN_XOAY_TRON(vs32 _toc_do,float _gia_toc)		
//		{				BIT_XOAY		=	10;
//						GIA_TOC			=	_gia_toc;		
//						TOC_DO_DAT 	= _toc_do;	
//						CHAY_VA_XOAY=	0;
//						TOC_DO			=	2;
//						if(TOC_DO_DAT>0){chieu_trai_sau_toi;chieu_trai_truoc_toi;chieu_phai_sau_lui;chieu_phai_truoc_lui;}
//						else if(TOC_DO_DAT<0){chieu_trai_sau_lui;chieu_trai_truoc_lui;chieu_phai_sau_toi;chieu_phai_truoc_toi;}
//}	
////xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx	
//void TINH_GOC_LECH()		
//{				
//						
//						GOC_LECH=(IMU-MAT_ROBOT)/10;
//						trai_truoc1 =	(int)(luong_giac_tt*TOC_DO  + GOC_LECH);	
//						trai_sau1   =	(int)(luong_giac_ts*TOC_DO  + GOC_LECH);
//						phai_truoc1 =	(int)(luong_giac_pt*TOC_DO  + GOC_LECH);
//						phai_sau1   =	(int)(luong_giac_ps*TOC_DO  + GOC_LECH);///1.1	
////chieu dong coO
//						if(trai_truoc1>0){ chieu_trai_truoc_toi;}
//						else {chieu_trai_truoc_lui;} 
//	
//						if(trai_sau1>0){chieu_trai_sau_toi;}
//						else {chieu_trai_sau_lui;}
//						
//						if(phai_truoc1>0){ chieu_phai_truoc_lui;}
//						else {chieu_phai_truoc_toi;} 

//						if(phai_sau1>0){chieu_phai_sau_lui;}
//						else {chieu_phai_sau_toi ;}
//					
////khoa banh xe khi dang chay neu toc do banh <3
////xuat toc do ra dong co

//						if ( abs(trai_truoc1 < 3))trai_truoc=2;
//						else	{
//										if(abs(trai_truoc1)>=254)trai_truoc1=254;
//										else trai_truoc=abs(trai_truoc1);
//									}
//						if ( abs(trai_sau1) < 3)trai_sau=2;
//						else	{
//										if(abs(trai_sau1)>=254)trai_sau1=254;
//										else trai_sau= abs(trai_sau1);				
//									}
//						if ( abs(phai_truoc1) < 3)phai_truoc=2;
//						else	{
//										if(abs(phai_truoc1)>=254)phai_truoc=254;
//										else phai_truoc= abs(phai_truoc1);
//										}
//						if ( abs(phai_sau1) < 3)phai_sau=2;
//						else	{
//										if(abs(phai_sau1)>=254)phai_sau=254;
//										else phai_sau= abs(phai_sau1);
//									}
////////////////////////////////////////HÀM GIA TÔC//////////////////

//						if(TOC_DO>TOC_DO_DAT){
//									TOC_DO=TOC_DO/GIA_TOC;
//									if(TOC_DO<TOC_DO_DAT)TOC_DO=TOC_DO_DAT; 				
//								}
//						else if(TOC_DO<TOC_DO_DAT){														
//									TOC_DO=TOC_DO*GIA_TOC;
//									if(TOC_DO>TOC_DO_DAT)TOC_DO=TOC_DO_DAT; 
//								}

//						else {
//									if(TOC_DO<=3)STOP_ROBOT();
//									else TOC_DO=TOC_DO_DAT;				
//								}				
//}	

/////////////////////////////////////////////////////
//void RUN_TIMER(){		
//	
//		if(BIT_XOAY==10){
//			
//											if(TOC_DO>abs(TOC_DO_DAT)){
//														TOC_DO=TOC_DO/GIA_TOC;
//														if(TOC_DO<abs(TOC_DO_DAT))TOC_DO=abs(TOC_DO_DAT); 				
//													}
//											else if(TOC_DO<abs(TOC_DO_DAT)){														
//														TOC_DO=TOC_DO*GIA_TOC;
//														if(TOC_DO>abs(TOC_DO_DAT))TOC_DO=abs(TOC_DO_DAT); 
//													}
//											else {
//														if(TOC_DO<=3)STOP_ROBOT();
//														else{
//																TOC_DO=TOC_DO_DAT;
//																}
//														}
//							MOTOR_LOCK=3000;trai_sau=trai_truoc=phai_sau=phai_truoc=TOC_DO;
//		}	
//////////////////////////////////////////////////////		
//		else{
//				if(TOC_DO_DAT>2||CHAY_GIA_TOC==10)
//					{ 
//						MOTOR_LOCK=3000;
//						if(CHAY_VA_XOAY>0){RUN_XOAY();} 
//						TINH_GOC_LECH();	
//					}
//				else
//					{		
//							if(MOTOR_LOCK<=0){MOTOR_LOCK=0;trai_sau=trai_truoc=phai_sau=phai_truoc=TOC_DO=0;	}
//							else{trai_sau=trai_truoc=phai_sau=phai_truoc=TOC_DO=2;MOTOR_LOCK--;}		
//					}			
//				}
//}	


/////////////////////////////////////////////




