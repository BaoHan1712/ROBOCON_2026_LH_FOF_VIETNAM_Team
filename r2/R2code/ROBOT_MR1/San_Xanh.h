//*********************************** SAN XANH *********************************8
void Xuat_Phat_Lay_Vu_Khi_1(void)
 //				RESET_ENCODER(); 
{				
				target_chan_truoc = 460, target_chan_sau = 460;
				while(lazeTruocValue > 25)
				{
					if(lazeTruocValue < 45)	target_chan_truoc = 618, target_chan_sau = 634;
					Bam_thanh_laser_phai(20,0,0,18,2,350,20);//robotRun(-450,10); // 0,0,0,khoang cach vs thanh,0,0,0
				}
				
				while(lazeTruocValue > 8)	
				{
					XI_LANH_HA_KEP;
					target_chan_truoc = 618, target_chan_sau = 634;
					Bam_thanh_laser_phai(15,0,0,18,2,350,20);//robotRun(-450,10);
				}
				 robotRun(0,3);
				
				vTaskDelay(1200);
				
				XI_LANH_KEP_DONG;
				
				vTaskDelay(4000);
				robotStop(20);
				XI_LANH_NANG_KEP;
				target_chan_truoc = 650, target_chan_sau = 650;
				
}
void Xuat_Phat_Lay_Vu_Khi_2(void)
 //				RESET_ENCODER(); 
{				
				target_chan_truoc = 460, target_chan_sau = 460;
				while(lazeTruocValue > 25)	
				{
					if(lazeTruocValue < 45)	target_chan_truoc = 618, target_chan_sau = 640;
					Bam_thanh_laser_phai(15,0,0,40,1,625,30);//robotRun(-450,10); // 0,0,0,khoang cach vs thanh,0,0,0
				}
				
				while(lazeTruocValue > 11)	
				{
					XI_LANH_HA_KEP;
					target_chan_truoc = 618, target_chan_sau = 644;
					Bam_thanh_laser_phai(10,0,0,40,1,350,30);//robotRun(-450,10);
				}
				 robotRunAngle(0,10,0,0);
				
					vTaskDelay(2500);
					robotStop(10);
				
					XI_LANH_KEP_DONG;
					vTaskDelay(4000);
					
					XI_LANH_NANG_KEP;
					target_chan_truoc = 650, target_chan_sau = 650;
				
}
void Xuat_Phat_Lay_Vu_Khi_3(void)
 //				RESET_ENCODER(); 
{				
				while(lazeTruocValue > 25)	
				{
					if(lazeTruocValue < 55)	target_chan_truoc = 618, target_chan_sau = 640;
					Bam_thanh_laser_phai(25,0,0,61,2,785,90);//robotRun(-450,10); // 0,0,0,khoang cach vs thanh,0,0,0
				}
				
				while(lazeTruocValue > 8)	
				{
					XI_LANH_HA_KEP;
					target_chan_truoc = 618, target_chan_sau = 644;
					Bam_thanh_laser_phai(15,0,0,61,2,785,90);//robotRun(-450,10);
				}
				 robotRun(0,3);
				
				vTaskDelay(1500);
				
				XI_LANH_KEP_DONG;
				
				vTaskDelay(3000);
				robotStop(10);
				XI_LANH_NANG_KEP;
				target_chan_truoc = 650, target_chan_sau = 650;
				
}
void Xuat_Phat_Lay_Vu_Khi_4(void)
 //				RESET_ENCODER(); 
{				
				while(lazeTruocValue > 25)	
				{
					if(lazeTruocValue < 45)	target_chan_truoc = 618, target_chan_sau = 634;
					Bam_thanh_laser_phai(25,0,0,81,2,875,80);//robotRun(-450,10); // 0,0,0,khoang cach vs thanh,0,0,0
				}
				
				while(lazeTruocValue > 8)	
				{
					XI_LANH_HA_KEP;
					target_chan_truoc = 618, target_chan_sau = 634;
					Bam_thanh_laser_phai(15,0,0,81,2,875,80);//robotRun(-450,10);
				}
				 robotRun(0,3);
				
				vTaskDelay(1500);
				
				XI_LANH_KEP_DONG;
				
				vTaskDelay(4000);
				robotStop(10);
				XI_LANH_NANG_KEP;
				target_chan_truoc = 650, target_chan_sau = 650;
				
}
void lane_trai(void)
{
				while(lazeTruocValue > 140)	
				{
					Bam_thanh_laser_phai(60,0,0,410,2,700,50);
					if(!wantExit())	break;
				}
				
				while(lazeTruocValue > 12)	
				{
					if(lazeTruocValue < 145)	target_chan_truoc = 685, target_chan_sau = 685;
					Bam_thanh_laser_phai(30,0,0,420,2,350,40);
					if(!wantExit())	break;
				}
				Leo_bac_400();
				vTaskDelay(5);
				Xuong_bac_200();
					RESET_ENCODER();
					robotRunAngle(0,30,0,0);
					
					for(i=0;i<250;i++)	
					{
						while(ENCODER_FR() < 1100)	
						{	
							vTaskDelay(5);
							if(ENCODER_FR() > 900)		target_chan_truoc = 460, target_chan_sau = 460;
							if(!wantExit())	break;
						}
					
					}
				Leo_bac_200();
				vTaskDelay(5);
				Xuong_bac_200();
					RESET_ENCODER();
					robotRunAngle(0,30,0,0);
					
					for(i=0;i<250;i++)	
					{
						while(ENCODER_FR() < 1100)	
						{	
							vTaskDelay(5);
							if(ENCODER_FR() > 900)		target_chan_truoc = 235, target_chan_sau = 235;
							if(!wantExit())	break;
						}
					
					}
				Xuong_bac_200();
					RESET_ENCODER();
					robotRunAngle(0,30,0,0);
					
					for(i=0;i<250;i++)	
					{
						while(ENCODER_FR() < 1100)	
						{	
							vTaskDelay(5);
							if(ENCODER_FR() > 900)		target_chan_truoc = 235, target_chan_sau = 235;
							if(!wantExit())	break;
						}
					
					}
				robotStop(0);
}
	void lane_giua(void)
{
				while(lazeTruocValue > 140)	
				{
					Bam_thanh_laser_phai(60,0,0,230,2,550,40);
					if(!wantExit())	break;
				}
				
				while(lazeTruocValue > 12)	
				{
					if(lazeTruocValue < 100)	target_chan_truoc = 460, target_chan_sau = 460;
					Bam_thanh_laser_phai(30,0,0,280,2,250,40);
					if(!wantExit())	break;
				}
					Leo_bac_200();
					vTaskDelay(5);
					Leo_bac_200();
					vTaskDelay(5);
					Leo_bac_200();
					vTaskDelay(5);
					Xuong_bac_200();
					RESET_ENCODER();
					robotRunAngle(0,30,0,0);
					
					for(i=0;i<250;i++)	
					{
						while(ENCODER_FR() < 1100)	
						{	
							vTaskDelay(5);
							if(ENCODER_FR() > 900)		target_chan_truoc = 235, target_chan_sau = 235;
							if(!wantExit())	break;
						}
					
					}
					
					Xuong_bac_400();
					RESET_ENCODER();
					robotRunAngle(0,30,0,0);
					
					for(i=0;i<250;i++)	
					{
						while(ENCODER_FR() < 1000)	
						{	
							vTaskDelay(5);
							if(ENCODER_FR() > 800)		target_chan_truoc = 235, target_chan_sau = 235;
							if(!wantExit())	break;
						}
					
					}
				robotStop(0);
}
	void lane_phai(void)
{
				while(lazeTruocValue > 140)	
				{
					Bam_thanh_laser_phai(60,0,0,135,2,250,40);
					if(!wantExit())	break;
				}
				
				while(lazeTruocValue > 12)	
				{
					if(lazeTruocValue < 150)	target_chan_truoc = 685, target_chan_sau = 685;
					Bam_thanh_laser_phai(35,0,0,143,2,250,30);
					if(!wantExit())	break;
				}

					Leo_bac_400();
					vTaskDelay(5);
				
					Leo_bac_200();
					vTaskDelay(5);
				
				RESET_ENCODER();
				robotRunAngle(0,30,0,0);
				
				for(i=0;i<250;i++)	
				{
					while(ENCODER_FR() < 2300)	
					{	
						vTaskDelay(5);
						if(ENCODER_FR() > 1000)		target_chan_truoc = 235, target_chan_sau = 235;
						if(!wantExit())	break;
					}
				
				}
					Xuong_bac_200();
				
				RESET_ENCODER();
				robotRunAngle(0,30,0,0);
				
				for(i=0;i<250;i++)	
				{
					while(ENCODER_FR() < 1100)	
					{	
						vTaskDelay(5);
						if(ENCODER_FR() > 900)		target_chan_truoc = 235, target_chan_sau = 235;
						if(!wantExit())	break;
					}
				
				}
					Xuong_bac_200();
				
					RESET_ENCODER();
					robotRunAngle(0,30,0,0);
				
					for(i=0;i<250;i++)	
					{
						while(ENCODER_FR() < 1100)	
					{	
						vTaskDelay(5);
						if(ENCODER_FR() > 900)		target_chan_truoc = 235, target_chan_sau = 235;
						if(!wantExit())	break;
					}
				
				}
					Xuong_bac_200();
					RESET_ENCODER();
					robotRunAngle(0,30,0,0);
				
					for(i=0;i<250;i++)	
					{
						while(ENCODER_FR() < 1100)	
					{	
						vTaskDelay(5);
						if(ENCODER_FR() > 900)		target_chan_truoc = 235, target_chan_sau = 235;
						if(!wantExit())	break;
					}
				
				}
				
				robotStop(0);
}