

////===================================SHAGAI 2 DO======================================//
//void Retry_SanDo_2(void)
//{
//				xl_Nang_Dai_Ve,						delay_ms(500);
//				xl_Nang_Ngan_Ra,					delay_ms(1500);
//				xl_Don_Ra,								delay_ms(500);
//	
//	
//				robotRunAngle(-900,10,-900,0);
//				while(lazeSauTraiValue > 80)		 if(WannaExit())	while(1)	robotStop(0);
//				
//				robotRunAngle(-900,10,-890,0); 
//				delay_ms(300);
//				robotStop(0);
//				
//				xl_Shagai_Kep,												delay_ms(500);
//				xl_Truot_Len,													delay_ms(1000);
//				xl_Don_Ve;														delay_ms(500);
//				xl_Nang_Ngan_Ve;
//				
////---------------------------CHAY VAO VI TRI BAN 2---------------------------------//	
//				RESET_ENCODER();

//				while(lazeSauTraiValue > 200)	
//				{
//					if(WannaExit())	while(1)	robotStop(0);
//					robotRunAngle(-1920,50,0,0);											
//				}

//				RESET_ENCODER();
//				while(ENCODER() < 3000)			
//				{
//					if(WannaExit())	while(1)	robotStop(0);
//					cap_thanh_lazer_truoc(-900,-900,60,40);	
//				}
//				
//				while(ENCODER() < 3200)		
//				{					
//					if(WannaExit())	while(1)	robotStop(0);
//					cap_thanh_lazer_truoc(-900,-900,30,40);	
//				}

////---------------------------XOAY GOC BAN 2---------------------------------//					
//				robotRun(-900,10);
//				robotRotate(-1400,-1,3);
//				while(_robotIMUAngle > -1400)	if(WannaExit())	while(1)	robotStop(0);
//				robotStop(0);
//				
//				robotRun(0,8);
//				xl_Doi_Ra; 									delay_ms(1500);
//				robotStop(0);								
//				xl_Shagai_Nha; 							delay_ms(500);
//				xl_Truot_Xuong; 						delay_ms(700);
//				xl_Shagai_Kep; 							delay_ms(500);
//				xl_Shagai_Nha; 							delay_ms(1500);
//				
//				xl_Ban_Ra; 									delay_ms(1000);
//				xl_Ban_Ve; 									delay_ms(500);
//				xl_Doi_Ve;
//				
//			
//			
////==============================LAY SHAGAI 3===================================//			
//				RESET_ENCODER();
//				
//				while(_robotIMUAngle < -900)
//				{
//					robotRun(1400,25);
//					robotRotate(-900,1,0);
//				}

////---------------------------CAP THANH LUI LAY SHAGAI 3---------------------------------//					
//				while(ENCODER() < 3500)		
//				{					
//					if(WannaExit())	while(1)	robotStop(0);
//					cap_thanh_lazer_truoc(900,-900,70,25);	
//				}
//				
//				while(ENCODER() < 4100)		
//				{					
//					if(WannaExit())	while(1)	robotStop(0);
//					cap_thanh_lazer_truoc(900,-900,60,25);	
//				}
//			
//				
//				while(lazeSauTraiValue < 400)			
//				{
//					if(WannaExit())	while(1)	robotStop(0);
//					robotRunAngle(0,50,-900,0);
//				}				
//				
////---------------------------CHAY LAY SHAGAI 3---------------------------------//					
//				RESET_ENCODER();
//				xl_Nang_Ngan_Ra;
//				
//				while(ENCODER() < 700)		
//				{
//					if(WannaExit())	while(1)	robotStop(0);
//					xl_Nang_Ngan_Ra;
//					robotRunAngle(-250,50,-900,0);
//				}
//	
//				robotRunAngle(-250,35,-900,0);
//				while(ENCODER() < 1500)		 				if(WannaExit())	while(1)	robotStop(0);
//				
//				robotRunAngle(-250,25,-910,0);	
//				while(ENCODER() < 2400)						if(WannaExit())	while(1)	robotStop(0);
//				
//				robotRunAngle(-250,15,-910,0);
//				while(lazeSauTraiValue > 400)				if(WannaExit())	while(1)	robotStop(0);
//				
//				robotRun(900, 8), delay_ms(1000);
//				robotRun(900, 5), delay_ms(500);
//				robotStop(0);
//				
////---------------------------TOI VI TRI GAP SHAGAI 3---------------------------------//	
//				xl_Don_Ra;	delay_ms(500);
//					
//				robotRunAngle(-900,10,0,0); 
//				while(lazeSauTraiValue > 80)				if(WannaExit())	while(1)	robotStop(0);
//				
//				robotRunAngle(-900,10,0,0); 
//				delay_ms(300);
//				robotStop(0);
//				
//				xl_Shagai_Kep,												delay_ms(500);
//				xl_Truot_Len,													delay_ms(1000);
//				xl_Don_Ve;														delay_ms(500);
//				
////---------------------------CHAY VAO VI TRI BAN 3---------------------------------//	
//				
//				while(lazeSauTraiValue < 445 )
//				{
//					if(WannaExit())		while(1)	robotStop(0);
//					robotRun(1800, 15);
//				}
//				robotStop(0);
//				
//				RESET_ENCODER();

//				robotRunAngle(-2040,50,0,0);
//				xl_Nang_Ngan_Ve;											delay_ms(800);
//				while(lazeSauTraiValue > 250)				if(WannaExit())	while(1)	robotStop(0);

//				RESET_ENCODER();
//				while(ENCODER() < 3000)			
//				{
//					if(WannaExit())	while(1)	robotStop(0);
//					cap_thanh_lazer_truoc(-900,-900,60,40);	
//				}
//				
//				while(ENCODER() < 3200)		
//				{					
//					if(WannaExit())	while(1)	robotStop(0);
//					cap_thanh_lazer_truoc(-900,-900,30,40);	
//				}
//	
////---------------------------XOAY GOC BAN 3---------------------------------//					
//				robotRun(-900,10);
//				robotRotate(-1410,-1,3);
//				while(_robotIMUAngle > -1400)	if(WannaExit())	while(1)	robotStop(0);
//	
//				robotRun(0,8);
//				xl_Doi_Ra; 									delay_ms(1500);
//				robotStop(0);
//				
//				xl_Shagai_Nha; 							delay_ms(500);
//				xl_Truot_Xuong; 						delay_ms(700);
//				xl_Shagai_Kep; 							delay_ms(500);
//				xl_Shagai_Nha; 							delay_ms(1500);
//				
//				xl_Ban_Ra; 									delay_ms(1000);
//				xl_Ban_Ve; 									delay_ms(500);
//				xl_Doi_Ve;
//				
//			robotStop(0);
//		}

//		
//		
//		
//		
////--------------------------------------------------------------------------------------//		
////====================================SHAGAI 3 DO==========================================//	
////--------------------------------------------------------------------------------------//		
//		
//void Retry_SanDo_3 (void)
//{
//				xl_Nang_Dai_Ve,						delay_ms(500);
//				xl_Nang_Ngan_Ra,					delay_ms(1500);
//				xl_Don_Ra,								delay_ms(500);
//	
//				robotRunAngle(-900,10,0,0); 
//				while(lazeSauTraiValue > 80)				if(WannaExit())	while(1)	robotStop(0);
//				
//				robotRunAngle(-900,10,0,0); 
//				delay_ms(300);
//				robotStop(0);
//				
//				xl_Shagai_Kep,												delay_ms(500);
//				xl_Truot_Len,													delay_ms(1000);
//				xl_Don_Ve;														delay_ms(500);
//				
////---------------------------CHAY VAO VI TRI BAN 3---------------------------------//	
//				
//				while(lazeSauTraiValue < 445 )
//				{
//					if(WannaExit())		while(1)	robotStop(0);
//					robotRun(1800, 15);
//				}
//				robotStop(0);
//				
//				RESET_ENCODER();

//				robotRunAngle(-2040,50,0,0);
//				xl_Nang_Ngan_Ve;											delay_ms(800);
//				while(lazeSauTraiValue > 250)				if(WannaExit())	while(1)	robotStop(0);

//				RESET_ENCODER();
//				while(ENCODER() < 3000)			
//				{
//					if(WannaExit())	while(1)	robotStop(0);
//					cap_thanh_lazer_truoc(-900,-900,60,40);	
//				}
//				
//				while(ENCODER() < 3200)		
//				{					
//					if(WannaExit())	while(1)	robotStop(0);
//					cap_thanh_lazer_truoc(-900,-900,30,40);	
//				}
//	
////---------------------------XOAY GOC BAN 3---------------------------------//					
//				robotRun(-900,10);
//				robotRotate(-1410,-1,3);
//				while(_robotIMUAngle > -1400)	if(WannaExit())	while(1)	robotStop(0);
//	
//				robotRun(0,8);
//				xl_Doi_Ra; 									delay_ms(1500);
//				robotStop(0);
//				
//				xl_Shagai_Nha; 							delay_ms(500);
//				xl_Truot_Xuong; 						delay_ms(700);
//				xl_Shagai_Kep; 							delay_ms(500);
//				xl_Shagai_Nha; 							delay_ms(1500);
//				
//				xl_Ban_Ra; 									delay_ms(1000);
//				xl_Ban_Ve; 									delay_ms(500);
//				xl_Doi_Ve;
//				
//			robotStop(0);
//	
//}

////-------------------------------------------------------------------------------------------//		
////====================================SHAGAI  2 XANH==========================================//	
////-------------------------------------------------------------------------------------------//		

//void Retry_SanXanh_2 (void)
//{
//				xl_Nang_Dai_Ve,						delay_ms(500);
//				xl_Nang_Ngan_Ra,					delay_ms(1500);
//				xl_Don_Ra,								delay_ms(500);
//	
//				robotRunAngle(900,7,0,0);
//				while(lazeSauTraiValue > 80)		 if(WannaExit())	while(1)	robotStop(0);
//				
//				robotRunAngle(890,7,0,0); 
//				delay_ms(300);
//				robotStop(0);
//				
//				xl_Shagai_Kep,												delay_ms(700);
//				xl_Truot_Len,													delay_ms(1500);
//				xl_Don_Ve;														delay_ms(500);
//				
////---------------------------CHAY VAO VI TRI BAN 2---------------------------------//					
//				RESET_ENCODER();

//				robotRunAngle(1850,40,0,0);
//				xl_Nang_Ngan_Ve;											delay_ms(800);
//				while(lazeSauTraiValue > 200)				if(WannaExit())	while(1)	robotStop(0);

//				RESET_ENCODER();
//				while(ENCODER() < 3100)			
//				{
//					if(WannaExit())	while(1)	robotStop(0);
//					cap_thanh_lazer_truoc(900,900,60,40);	
//				}
//				
//				while(ENCODER() < 3600)		
//				{					
//					if(WannaExit())	while(1)	robotStop(0);
//					cap_thanh_lazer_truoc(900,900,20,40);	
//				}

////---------------------------XOAY GOC BAN 2---------------------------------//				
//				robotRun(900,15);
//				robotRotate(1410,1,4);
//				while(_robotIMUAngle < 1400)	if(WannaExit())	while(1)	robotStop(0);
//	
//				robotRun(0,8), delay_ms(500);
//				robotStop(0);
//				
//				xl_Doi_Ra; 									delay_ms(1200);
//				xl_Shagai_Nha; 							delay_ms(500);
//				xl_Truot_Xuong; 						delay_ms(700);
//				xl_Shagai_Kep; 							delay_ms(500);
//				xl_Shagai_Nha; 							delay_ms(1500);
//				
//				xl_Ban_Ra; 									delay_ms(1000);
//				xl_Ban_Ve; 									delay_ms(500);
//				xl_Doi_Ve;
//			
//			
////=================================LAY SHAGAI 3==================================//
//				RESET_ENCODER();
//				xl_Doi_Ve; 
//	
//				while(_robotIMUAngle > 900)
//				{
//					robotRun(-1400,20);
//					robotRotate(900,-1,0);
//				}
//				
//				while(ENCODER() < 3500)		
//				{					
//					if(WannaExit())	while(1)	robotStop(0);
//					cap_thanh_lazer_truoc(-900,900,60,35);	
//				}
//				
//				while(ENCODER() < 4000)		
//				{					
//					if(WannaExit())	while(1)	robotStop(0);
//					cap_thanh_lazer_truoc(-900,900,40,35);	
//				}
//				
//				robotRunAngle(0,40,900,0);
//				while(lazeSauTraiValue < 300)				 if(WannaExit())	while(1)	robotStop(0);
//				
//				
//				
////---------------------------CHAY LAY SHAGAI 3---------------------------------//
//				RESET_ENCODER();
//				
//				while(ENCODER() < 700)	
//				{
//					if(WannaExit())	while(1)	robotStop(0);
//					xl_Nang_Ngan_Ra;
//					robotRunAngle(200,50,-900,0);	
//				}

//				robotRunAngle(200,35,-900,0);	
//				while(ENCODER() < 1500)					if(WannaExit())	while(1)	robotStop(0);
//				
//				robotRunAngle(200,20,-900,0);	
//				while(ENCODER() < 2450)					if(WannaExit())	while(1)	robotStop(0);

//				robotRunAngle(200,12,-900,0);
//				while(lazeSauTraiValue > 500)			 	if(WannaExit())	while(1)	robotStop(0);
//				
//				robotRunAngle(0,7,-900,0); 
//				delay_ms(1000);
//				
//				robotStop(0);
//				
////---------------------------TOI VI TRI GAP SHAGAI 3---------------------------------//	
//				xl_Don_Ra;	delay_ms(300);
//				
//				robotRunAngle(900,7,0,0);
//				while(lazeSauTraiValue > 80)		 if(WannaExit())	while(1)	robotStop(0);
//				
//				robotRunAngle(890,7,0,0); 
//				delay_ms(300);
//				robotStop(0);
//				
//				xl_Shagai_Kep,												delay_ms(700);
//				xl_Truot_Len,													delay_ms(1500);
//				xl_Don_Ve;														delay_ms(500);
//				
////---------------------------CHAY VAO VI TRI BAN 3---------------------------------//				
//				while(lazeSauTraiValue < 445 )
//				{
//					if(WannaExit())		while(1)	robotStop(0);
//					robotRun(1800, 15);
//				}
//				
//				robotStop(0);
//				RESET_ENCODER();

//				robotRunAngle(2010,40,0,0);
//				xl_Nang_Ngan_Ve;											delay_ms(800);
//				while(lazeSauTraiValue > 200)				if(WannaExit())	while(1)	robotStop(0);

//				RESET_ENCODER();
//				while(ENCODER() < 3100)			
//				{
//					if(WannaExit())	while(1)	robotStop(0);
//					cap_thanh_lazer_truoc(900,900,60,40);	
//				}
//				
//				while(ENCODER() < 3750)		
//				{					
//					if(WannaExit())	while(1)	robotStop(0);
//					cap_thanh_lazer_truoc(900,900,20,40);	
//				}
//				
////---------------------------XOAY GOC BAN 3---------------------------------//					
//				robotRun(900,15);
//				robotRotate(1410,1,4);
//				while(_robotIMUAngle < 1400)	if(WannaExit())	while(1)	robotStop(0);
//	
//				robotRun(0,8), delay_ms(1000);
//				robotStop(0);
//				
//				xl_Doi_Ra; 									delay_ms(1200);
//				xl_Shagai_Nha; 							delay_ms(500);
//				xl_Truot_Xuong; 						delay_ms(700);
//				xl_Shagai_Kep; 							delay_ms(500);
//				xl_Shagai_Nha; 							delay_ms(1500);
//				
//				xl_Ban_Ra; 									delay_ms(1000);
//				xl_Ban_Ve; 									delay_ms(500);
//				xl_Doi_Ve;
//			
//			robotStop(0);
//		}

////-------------------------------------------------------------------------------------------//		
////====================================SHAGAI 3 XANH==========================================//	
////-------------------------------------------------------------------------------------------//

//void Retry_SanXanh_3 (void)
//{
//				xl_Nang_Dai_Ve,						delay_ms(500);
//				xl_Nang_Ngan_Ra,					delay_ms(1500);
//				xl_Don_Ra,								delay_ms(500);


//robotRunAngle(900,7,0,0);
//				while(lazeSauTraiValue > 80)		 if(WannaExit())	while(1)	robotStop(0);
//				
//				robotRunAngle(890,7,0,0); 
//				delay_ms(300);
//				robotStop(0);
//				
//				xl_Shagai_Kep,												delay_ms(700);
//				xl_Truot_Len,													delay_ms(1500);
//				xl_Don_Ve;														delay_ms(500);
//				
////---------------------------CHAY VAO VI TRI BAN 3---------------------------------//				
//				while(lazeSauTraiValue < 445 )
//				{
//					if(WannaExit())		while(1)	robotStop(0);
//					robotRun(1800, 15);
//				}
//				
//				robotStop(0);
//				RESET_ENCODER();

//				robotRunAngle(2010,40,0,0);
//				xl_Nang_Ngan_Ve;											delay_ms(800);
//				while(lazeSauTraiValue > 200)				if(WannaExit())	while(1)	robotStop(0);

//				RESET_ENCODER();
//				while(ENCODER() < 3100)			
//				{
//					if(WannaExit())	while(1)	robotStop(0);
//					cap_thanh_lazer_truoc(900,900,60,40);	
//				}
//				
//				while(ENCODER() < 3750)		
//				{					
//					if(WannaExit())	while(1)	robotStop(0);
//					cap_thanh_lazer_truoc(900,900,20,40);	
//				}
//				
////---------------------------XOAY GOC BAN 3---------------------------------//					
//				robotRun(900,15);
//				robotRotate(1410,1,4);
//				while(_robotIMUAngle < 1400)	if(WannaExit())	while(1)	robotStop(0);
//	
//				robotRun(0,8), delay_ms(1000);
//				robotStop(0);
//				
//				xl_Doi_Ra; 									delay_ms(1200);
//				xl_Shagai_Nha; 							delay_ms(500);
//				xl_Truot_Xuong; 						delay_ms(700);
//				xl_Shagai_Kep; 							delay_ms(500);
//				xl_Shagai_Nha; 							delay_ms(1500);
//				
//				xl_Ban_Ra; 									delay_ms(1000);
//				xl_Ban_Ve; 									delay_ms(500);
//				xl_Doi_Ve;
//			
//			robotStop(0);
//		}








