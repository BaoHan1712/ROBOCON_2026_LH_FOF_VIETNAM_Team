
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
char buf[150],ky_tu[40],ky_tu_1[40],ky_tu_2[40],ky_tu_3[40];
uint8_t Buffer_HMI[150];
vs32 bien_hmi;

void HMI_ky_tu(char *_buf1)		  //???????
{

    int len = strlen(_buf1);
    if (strcmp(Buffer_HMI, _buf1) != 0) {	
        strncpy(Buffer_HMI, _buf1, sizeof(Buffer_HMI) - 1);  // Sao chép n?i dung m?i vào Buffer_HMI v?i gi?i h?n kích thu?c

        DMA_Cmd(DMA1_Stream7, DISABLE);  // D?ng DMA d? thi?t l?p l?i
        DMA1_Stream7->M0AR = (uint32_t)Buffer_HMI;  // C?p nh?t b? d?m m?i cho DMA
        DMA1_Stream7->NDTR = len;  // Ð?t s? lu?ng d? li?u c?n truy?n
        DMA_Cmd(DMA1_Stream7, ENABLE);  // B?t l?i DMA
    }
}	
	
///////////////
void HMISends(char *buf1)		  //???????
{
	u8 hmi=0;
	while(1)
	{
	 if(buf1[hmi]!=0)
	 	{
			USART_SendData(UART5,buf1[hmi]);  //??h???
		//	delay_ms(5);
			while(USART_GetFlagStatus(UART5,USART_FLAG_TXE)==RESET){};//??????
			//goto main;
		 	hmi++;
		}
	 else 
	 return ;

		}
	}
void HMISendb(u8 k)		         //??????
{		 
	u8 hmi;
	 for(hmi=0;hmi<3;hmi++)
	 {
	 if(k!=0)
	 	{
			USART_SendData(UART5,k);  //??h???
			while(USART_GetFlagStatus(UART5,USART_FLAG_TXE)==RESET){};//??????
		}
	 else 
	 return ;

	 } 
} 

/////////////////////////////////


void gui_so(vs32 so_can_gui, u8 vi_tri_gui) {
    HMISendb(0x00);
    HMISends("t");
    snprintf(buf, sizeof(buf), "%d", vi_tri_gui);
    HMISends(buf);

    HMISends(".txt=\"");

    snprintf(buf, sizeof(buf), "%d", so_can_gui);
    HMISends(buf);

    HMISends("\"");
    HMISendb(0xff);
    HMISendb(0xff);
    HMISendb(0xff);
}
//////////
void gui_chu(char* chu_can_gui,u8 vi_tri_gui){
		//HMISendb(0x00);
		HMISends("t");	
		sprintf(buf,"%d",vi_tri_gui);
					HMISends(buf);
	
	HMISends(".txt=\"");
	HMISends(chu_can_gui);
	HMISends("\"");
						HMISendb(0xff);
					//	HMISendb(0xff);
					//	HMISendb(0xff);
}
////////////////////////////////////
void HMI_DMI(char* chu_can_gui,vs32 bien_can_gui,vs32 vi_tri_gui){
	char k=0xff,i;
	char 	ky_tu_3[]=".txt=\"";
	char 	ky_tu_4[]="\"";
	char	ky_tu[]="t";	

for(i=0;i<30;i++){
		ky_tu_2[i]=0;
		ky_tu_1[i]=0;
		buf[i]=0;	
	Buffer_HMI[i]=0;
}
buf[0]=10;
buf[1]=255;
buf[2]=255;
buf[3]=255;

sprintf(ky_tu_1,"%d",vi_tri_gui);
strcat (ky_tu,ky_tu_1);
strcat(buf,ky_tu);        ///// 0t1  //nhan duoc chuoi
strcat(buf,ky_tu_3);	    ///// chuoi buf nhan duoc .txt=
strcat(buf,chu_can_gui);	///// chuoi buf nhan duoc chuoi can gui
sprintf(ky_tu_1,"%d",bien_can_gui);
strcat(buf,ky_tu_1);
strcat(buf,ky_tu_4);         
ky_tu_2[0]=0xff;
ky_tu_2[1]=0xff;
ky_tu_2[2]=0xff;

strcat(buf,ky_tu_2);
HMI_ky_tu(buf);

}


void HMI_PUTS(char* chu_can_gui,char* bien_can_gui,vs32 vi_tri_gui){
	char k=0xff,i;
	char 	ky_tu_3[]=".txt=\"";
	char 	ky_tu_4[]="\"";
	char	ky_tu[]="t";	

for(i=0;i<10;i++){
		ky_tu_2[i]=0;
		ky_tu_1[i]=0;
		buf[i]=0;	
}
buf[0]=10;
buf[1]=255;
buf[2]=255;
buf[3]=255;
sprintf(ky_tu_1,"%d",vi_tri_gui);
strcat (ky_tu,ky_tu_1);
strcat(buf,ky_tu);        ///// 0t1  //nhan duoc chuoi
strcat(buf,ky_tu_3);	    ///// chuoi buf nhan duoc .txt=
strcat(buf,chu_can_gui);	///// chuoi buf nhan duoc chuoi can gui
strcat(buf,bien_can_gui);
strcat(buf,ky_tu_4);         
ky_tu_2[0]=0xff;
ky_tu_2[1]=0xff;
ky_tu_2[2]=0xff;
ky_tu_2[3]=0;
ky_tu_2[4]=0;
strcat(buf,ky_tu_2);
HMI_ky_tu(buf);

}


void HMI_PUT_j(vs32 tham_so) {
    char buffer[50];
    snprintf(buffer, sizeof(buffer), "j0.val=%d", tham_so);
    HMI_ky_tu(buffer);
}

void HMI_DMI_CHI_GUI_SO(char* chu_can_gui,vs32 vi_tri_gui){
	char k=0xff,i;
	char 	ky_tu_3[]=".txt=\"";
	char 	ky_tu_4[]="\"";
	char	ky_tu[]="t";	

for(i=0;i<30;i++){
		ky_tu_2[i]=0;
		ky_tu_1[i]=0;
		buf[i]=0;	
	Buffer_HMI[i]=0;
}
buf[0]=10;
buf[1]=255;
buf[2]=255;
buf[3]=255;

sprintf(ky_tu_1,"%d",vi_tri_gui);
strcat (ky_tu,ky_tu_1);
strcat(buf,ky_tu);        ///// 0t1  //nhan duoc chuoi
strcat(buf,ky_tu_3);	    ///// chuoi buf nhan duoc .txt=
strcat(buf,chu_can_gui);
strcat(buf,ky_tu_1);
strcat(buf,ky_tu_4);         
ky_tu_2[0]=0xff;
ky_tu_2[1]=0xff;
ky_tu_2[2]=0xff;

strcat(buf,ky_tu_2);
HMI_ky_tu(buf);

}
