/**
  ******************************************************************************
  * @file    TIM/6Steps/stm32f4xx_it.c 
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    30-September-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and peripherals
  *          interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_it.h"
#include <stdio.h>
#include <stdlib.h>

/** @addtogroup STM32F4xx_StdPeriph_Examples
  * @{
  */

/** @addtogroup TIM_6Steps
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

void timer_do_line();	

/******************************************************************************/
/*            Cortex-M4 Processor Exceptions Handlers                         */
/******************************************************************************/

void config_uart3_1(u32 baudrate);



/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {}
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {}
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {}
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {}
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
__weak void SVC_Handler(void)
{}

/**
  * @brief  This function handles PendSV_Handler exception.
  * @param  None
  * @retval None
  */
__weak void PendSV_Handler(void)
{}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
	extern vu8 en_gyro;
	vu32 _view_systick=0;
	u8 _index_gyro=0;
void gp_update_uart ();	
void HMI_TRAN(vs32 so_dong);

/******************************************************************************/
/*            STM32F4xx Peripherals Interrupt Handlers                        */
/******************************************************************************/

/**
  * @brief  This function handles TIM1 Trigger and commutation and TIM11 
  *         global interrupts requests.
  * @param  None
  * @retval None
  */


//xxxxxxxxxxxxxxxxxxxxxxxxxxx
extern vu8 RxBuffer_compass[2],RX_USART1[15];
extern vs16 IMU;


void USART1_IRQHandler(void)// ngat  uart1 RX
{ 
	if(USART_GetITStatus(USART1,USART_IT_RXNE)!= RESET)
    {      
			 USART_ClearFlag(USART1, USART_FLAG_RXNE);
//			USART1->SR = (uint16_t)~USART_FLAG_RXNE;
//			 RxBuffer_compass[_index_gyro++]=USART1->DR;
//			 if(_index_gyro>1)
//			 {
//				IMU=(RxBuffer_compass[0]<<8)|RxBuffer_compass[1];
//			 }

			 
//			 _view_systick++;
		}
		
		
}
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
extern uint8_t MANG_GAME[10],DATA_COLOR[20];
void DMA1_Stream4_IRQHandler(void)// ngat DMA uart1 RX
{
	    
			DMA_ClearITPendingBit(DMA1_Stream4,DMA_IT_TCIF4);
			//if(MANG_GAME[7]!=1)config_uart3_1(115200);
	
}


////////
void DMA1_Stream6_IRQHandler(void) // UART2_TX
{
  /* Test on DMA Stream Transfer Complete interrupt */
  if (DMA_GetITStatus(DMA1_Stream6, DMA_IT_TCIF6))
  {

			//DMA_Cmd(DMA1_Stream6, DISABLE);

    DMA_ClearITPendingBit(DMA1_Stream6, DMA_IT_TCIF6);
  }
}
/////////// uart6 //////

void DMA2_Stream1_IRQHandler(void)
{
    if(DMA_GetITStatus(DMA2_Stream1, DMA_IT_TCIF1))
    {
        DMA_ClearITPendingBit(DMA2_Stream1, DMA_IT_TCIF1);
        ProcessReceivedData();
        DMA_Cmd(DMA2_Stream1, DISABLE);
        DMA_SetCurrDataCounter(DMA2_Stream1, 4);  // Gia su dung 6 byte thì 6

        // Kích hoat lai DMA
        DMA_Cmd(DMA2_Stream1, ENABLE);
    }
}

////////////////
void DMA2_Stream2_IRQHandler(void)// ngat DMA uart1 RX
{
	    
			DMA_ClearITPendingBit(DMA2_Stream2,DMA_IT_TCIF2);
			IMU=(RX_USART1[0]<<8)|RX_USART1[1];
		//	GPIO_WriteBit(GPIOA,GPIO_Pin_5,1^GPIO_ReadOutputDataBit(GPIOA,GPIO_Pin_5));
	
}
void DMA2_Stream5_IRQHandler(void)// ngat DMA uart1 RX
{
	    
			DMA_ClearITPendingBit(DMA2_Stream5,DMA_IT_TCIF5);
			//IMU=(RxBuffer_compass[1]<<8)|RxBuffer_compass[0];
			
	
	
}
//XXXXXXXXXXXXXXXXXXXXXXXX

void DMA1_Stream1_IRQHandler(void) // USART3 RX DMA Transfer Complete Interrupt
{int i;
  if (DMA_GetITStatus(DMA1_Stream1, DMA_IT_TCIF1))
  {

    DMA_ClearITPendingBit(DMA1_Stream1, DMA_IT_TCIF1);
		gp_update_uart();
  }

}  
/**************************************************************************************/

void DMA1_Stream0_IRQHandler(void) // UART5_RX
{
  /* Test on DMA Stream Transfer Complete interrupt */
  if (DMA_GetITStatus(DMA1_Stream0, DMA_IT_TCIF0))
  {
    /* Clear DMA Stream Transfer Complete interrupt pending bit */
    DMA_ClearITPendingBit(DMA1_Stream0, DMA_IT_TCIF0);
		
		ProcessReceivedData();
  }
}

/**************************************************************************************/

void DMA1_Stream7_IRQHandler(void) // UART5_TX
{
  /* Test on DMA Stream Transfer Complete interrupt */
  if (DMA_GetITStatus(DMA1_Stream7, DMA_IT_TCIF7))
  {
    /* Clear DMA Stream Transfer Complete interrupt pending bit */
//USART_SendData(UART5,0xff);
	//	delay_ms(100);
DMA_Cmd(DMA1_Stream7, DISABLE);

			//while(USART_GetFlagStatus(UART5,USART_FLAG_TXE)==RESET){};
    DMA_ClearITPendingBit(DMA1_Stream7, DMA_IT_TCIF7);
  }
}

/********************************** UART4 ********************************************/

void DMA1_Stream2_IRQHandler(void)
{
    if(DMA_GetITStatus(DMA1_Stream2, DMA_IT_TCIF2))
    {
        DMA_ClearITPendingBit(DMA1_Stream2, DMA_IT_TCIF2);
        ProcessReceivedData_2();

        // Vô hi?u hóa DMA d? c?u hình l?i
        DMA_Cmd(DMA1_Stream2, DISABLE);
        
        // Reset l?i con tr? và kích thu?c buffer
        DMA_SetCurrDataCounter(DMA1_Stream2, 7);
        
        // Kích ho?t l?i DMA d? nh?n gói ti?p theo
        DMA_Cmd(DMA1_Stream2, ENABLE);
    }
}

//=============================================================

void RUN_TIMER();
void HMI_RUN_LOOP(vs32 _cause);


void TIM6_DAC_IRQHandler(void)// INTERRUPTS TIM6
{ 
  TIM_ClearITPendingBit(TIM6, TIM_IT_Update);//xóa co ngat

}

void TIM7_IRQHandler(void)
{
	TIM_ClearITPendingBit(TIM7, TIM_IT_Update);
	////////////////////////////////////////////////////
	USART1->DR='z';	
	USART_Cmd(USART3, ENABLE);
	USART_Cmd(USART6, ENABLE);
}

//void TIM7_IRQHandler(void)
//{
// TIM_ClearITPendingBit(TIM7, TIM_IT_Update);
//	////////////////////////////////////////////////////
//USART1->DR='z';	
////USART_Cmd(USART3, ENABLE);
//USART_Cmd(USART6, ENABLE);
////	get_Gamepad_Bluetouch(MANG_GAME);
//}
///////////////////////////////////////////////////////////////////////
extern vs32 num_over_t1;
void TIM1_UP_TIM10_IRQHandler(void)// INTERRUPTS TIM1 OR TIM10 OVERFLOW
{ 
 TIM_ClearITPendingBit(TIM1, TIM_IT_Update);//xóa co ngat
	
	if(TIM1->CR1&TIM_CounterMode_Down)num_over_t1--;	
	else num_over_t1++;
}

void TIM1_TRG_COM_TIM11_IRQHandler(void)
{
  
}

extern vs32 num_over_t2;
void TIM2_IRQHandler(void)
{
  TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	if(TIM2->CR1&TIM_CounterMode_Down)num_over_t2--;	
	else num_over_t2++;
}

extern vs32 num_over_t3;
void TIM3_IRQHandler(void)
{
  TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
	if(TIM3->CR1&TIM_CounterMode_Down)num_over_t3--;	
	else num_over_t3++;	
}

extern vs32 num_over_t4;
void TIM4_IRQHandler(void)
{
  TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
	if(TIM4->CR1&TIM_CounterMode_Down)num_over_t4--;	
	else num_over_t4++;	
}
////////////////////////////////////
extern vs32 num_over_t5;
void TIM5_IRQHandler(void)
{
  TIM_ClearITPendingBit(TIM5, TIM_IT_Update);
	if(TIM5->CR1&TIM_CounterMode_Down)num_over_t5--;	
	else num_over_t5++;	
}
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

void SPI1_IRQHandler(void)
{ 
}

/**
  * @brief  This function handles SPI2 global interrupt request.
  * @param  None
  * @retval None
  */
void SPI3_IRQHandler(void)
{ 
	
	
}

/////////////////////////////
extern vs32 sieu_am;
  void EXTI2_IRQHandler(void)
  {int tang,bien_sieu_am;
		
    if(EXTI_GetITStatus(EXTI_Line2) != RESET)
    {
      GPIO_ToggleBits(GPIOA,GPIO_Pin_5);				
			if (GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_2)==1){TIM_SetCounter(TIM7,0);	}				
			else if (GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_2)==0){

			sieu_am=TIM_GetCounter(TIM7);	
		}	
      EXTI->PR = EXTI_Line2;		
    }
  }
	
////////////////////////////////////////////	
	  void EXTI3_IRQHandler(void)
  {
//    if(EXTI_GetITStatus(EXTI_Line3) != RESET)
//    {
//      GPIO_ToggleBits(GPIOA,GPIO_Pin_5);
//      EXTI->PR = EXTI_Line3;
//    }
  }


/******************************************************************************/
/*                 STM32F4xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f4xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */ 

/**
  * @}
  */ 

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
