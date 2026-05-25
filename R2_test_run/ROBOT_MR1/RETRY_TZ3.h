
void retry_TZ3(void)  
{
	
	RESET_ENCODER(2); //reser encoder ngang
	RESET_ENCODER(3); //reser encoder doc
	Robot_Stop_Now(0);	
	
	
	MAIN_CONTROL(0,-1710,50,0.1,0);	
	while(ENCODER_DOC() < 1000) 
	{      
		vTaskDelay(1);
	}
	
	xl_NangGoc_Off;
	
	MAIN_CONTROL(0,-1710,190,0.1,0);	
	while(ENCODER_DOC() < 44000) 
	{      
		vTaskDelay(1);
	}

	MAIN_CONTROL(0,-1710,160,0.05,0);	
	while(ENCODER_DOC() < 55000)
	{      
		vTaskDelay(1);
	}
	
	MAIN_CONTROL(0,-1710,100,0.05,0);	
	while(ENCODER_DOC() < 60000)
	{      
		vTaskDelay(1);
	}
	
	
	MAIN_CONTROL(0,-1710,40,0.1,0);	
	while(ENCODER_DOC() < 77000)
	{    
		vTaskDelay(1);
	}

	
	MAIN_CONTROL(0,-900,15,0.05,0);
	while(lazer_Chuan < 238 || (lazer_Chuan > 300))
	{
		vTaskDelay(1);
	}
	tt_laycon =1;
	Robot_Stop_Now(4);	
}