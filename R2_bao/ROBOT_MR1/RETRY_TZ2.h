
void retry_TZ2(void)  
{
	
	RESET_ENCODER(2); //reser encoder ngang
	RESET_ENCODER(3); //reser encoder doc
	Robot_Stop_Now(0);	
	
	
	MAIN_CONTROL(0,-1740,50,0.1,0);	
	while(ENCODER_DOC() < 1000) 
	{      
		vTaskDelay(1);
	}
	
	xl_NangGoc_On;
	
	MAIN_CONTROL(0,-1740,180,0.1,0.05);	
	while(ENCODER_DOC() < 40000) 
	{      
		if(IMU<(-110))break;
		vTaskDelay(1);
	}

	MAIN_CONTROL(-110,-1650,170,0.05,0);	
	while(ENCODER_DOC() < 50000)
	{      
		vTaskDelay(1);
	}
	
	MAIN_CONTROL(-110,-1650,60,0.05,0);	
	while(ENCODER_DOC() < 73000)
	{    
		vTaskDelay(1);
	}
	
	tt_laycon =1;
	MAIN_CONTROL(-110,-800,70,0.05,0);
	while((lazer_Chuan < 400) || (lazer_Chuan > 550))
	{
		vTaskDelay(1);
	}
	
	
	bitKhoaDieuAp =1;
	
	MAIN_CONTROL(-110,-800,30,1.5,0);
	while(((lazer_Chuan > 370) && (lazer_Chuan < 495)) || (lazer_Chuan > 540))
	{
		vTaskDelay(1);
	} 
	
	Robot_Stop_Now(4);	
	
	while(CB_QuaCon)
	{
		if(!CB_Con)
		{
			xl_DoCon_On;
		}
		
		
		if((-110-IMU) > 4)
		{
			Robot_Stop_Now(0);	
			MAIN_CONTROL(0,-40000,3,0.01,0);
		}
		else if((-110-IMU) < -4)
		{
			Robot_Stop_Now(0);	
			MAIN_CONTROL(0,40000,3,0.01,0);
		}
		else 
		{
			Robot_Stop_Now(4);	
		}
		vTaskDelay(1);
	}
		
	xl_kepCon_On;
	xl_DoCon_On;	
	nhanConVang =1;
	
	bitKhoaDieuAp =1;
	
	while(nhanConVang==1) {vTaskDelay(1);}
	

	xl_DoCon_Off;
	den_On;
	vTaskDelay(500);
	
	xl_BanDayRa_On;
	vTaskDelay(1000);
	
	tt_laycon =1;
	nhanCon=0;
	vTaskDelay(4500);
	
	xl_BanDayRa_Off;
	den_Off;

	
	Robot_Stop_Now(4);
	
	Robot_Stop_Now(0);
	
	vTaskDelay(1000);
	
	MAIN_CONTROL(0,940,100,0.1,0);
	while(lazer_Chuan < 350)//235
	{
		
		vTaskDelay(1);
	} 
	
	MAIN_CONTROL(0,940,50,1,0);
	while(lazer_Chuan > 270)//235
	{
		
		vTaskDelay(1);
	} 
	
	MAIN_CONTROL(0,940,15,2,0);
	while(lazer_Chuan > 238)
	{
		
		vTaskDelay(1);
	} 
	
	Robot_Stop_Now(4);
}