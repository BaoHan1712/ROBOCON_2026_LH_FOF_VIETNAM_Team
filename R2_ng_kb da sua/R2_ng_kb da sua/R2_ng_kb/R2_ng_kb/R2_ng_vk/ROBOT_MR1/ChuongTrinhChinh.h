int vungBan =0;
void ChuongTrinhChinh(void)
{
	if(!start && vungBan ==1)
	{
		xuatPhat_TZ1();
		vungBan =2;
		
	}
	if(!button1 && vungBan ==1)
	{
		retry_TZ2();
		vungBan =3;
	
	}
	if(!button2 && vungBan ==1)
	{
		retry_TZ3();
		vungBan =3;
		
	}
	if(vungBan==2)
	{
		while(CB_QuaCon)
		{
			if(!CB_Con)
			{
				xl_DoCon_On;
			}
			
			
			if((-145-IMU) > 4)
			{
				Robot_Stop_Now(0);	
				MAIN_CONTROL(0,-40000,3,0.01,0);
			}
			else if((-145-IMU) < -4)
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
		xl_DoCon_On;
		xl_kepCon_On;
		
		nhanConVang =1;
		vTaskDelay(2000);
		vungBan_TZ2();

		vungBan =3;
	
	}
	if(vungBan==3)
	{
		vungBan_TZ3_BTay();
		vungBan_TZ3_Thanh();
	}
}
