#include <MDR1986BE4.h>
#include <MDR32F9Qx_timer.h>
#include <MDR32F9Qx_port.h>
#include <MDR32F9Qx_rst_clk.h>
#include "TIMER.h"
#include "GPIO.h"

//Структуры для 1 таймера
TIMER_CntInitTypeDef TIMER1InitStruct;
TIMER_ChnInitTypeDef sTIM1_ChnInit;
//Структуры для 2 таймера
TIMER_CntInitTypeDef TIMER2InitStruct;
TIMER_ChnInitTypeDef sTIM2_ChnInit;
static uint8_t count = 0; 

void TIMER1_init(void)//период 1сек
{
	 RST_CLK_PCLKcmd (RST_CLK_PCLK_TIMER1, ENABLE);
	 /* Initializes the TIMERx Counter */
	 TIMER_CntStructInit(&TIMER1InitStruct);
	 TIMER1InitStruct.TIMER_Period = 0x3E7;//1000-1
	 TIMER1InitStruct.TIMER_Prescaler = 0x3E7F;//16000-1
	 
	 TIMER_CntInit(MDR_TIMER1, &TIMER1InitStruct);
	
   /* Enable TIMER1 clock */
   TIMER_BRGInit(MDR_TIMER1,TIMER_HCLKdiv1);

	 /* Enable TIMER1 */
   TIMER_Cmd(MDR_TIMER1,ENABLE);
}

void Delay_milli(uint32_t time_milli)//задержка максимум 1сек(time_milli=999)
{ 
	MDR_TIMER1->CNT = 0;
	while(TIMER_GetCounter(MDR_TIMER1)!=time_milli);
}

void TIMER2_init(void)//в режиме захвата
{
	 RST_CLK_PCLKcmd (RST_CLK_PCLK_TIMER2, ENABLE);

	 /* Initializes the TIMERx Counter */
	 TIMER_CntStructInit(&TIMER2InitStruct);
	 TIMER2InitStruct.TIMER_Prescaler = 0;
	 TIMER2InitStruct.TIMER_Period = 0;
	 TIMER2InitStruct.TIMER_CounterDirection = TIMER_CntDir_Up;
	 TIMER2InitStruct.TIMER_CounterMode = TIMER_CntMode_EvtFixedDir;
	 TIMER2InitStruct.TIMER_EventSource = TIMER_EvSrc_CH2;
	 TIMER2InitStruct.TIMER_ARR_UpdateMode = TIMER_ARR_Update_Immediately;
	 TIMER2InitStruct.TIMER_FilterSampling = TIMER_FDTS_TIMER_CLK_div_1;
	 TIMER2InitStruct.TIMER_ETR_FilterConf = TIMER_Filter_8FF_at_FTDS_div_32;
	 TIMER2InitStruct.TIMER_ETR_Prescaler = TIMER_ETR_Prescaler_None;
	 TIMER2InitStruct.TIMER_ETR_Polarity = TIMER_ETRPolarity_NonInverted;
	 TIMER2InitStruct.TIMER_BRK_Polarity = TIMER_BRKPolarity_NonInverted;
	 TIMER_CntInit (MDR_TIMER2, &TIMER2InitStruct);
	
	 TIMER_ChnStructInit (&sTIM2_ChnInit);
	 sTIM2_ChnInit.TIMER_CH_Number = TIMER_CHANNEL2;
   sTIM2_ChnInit.TIMER_CH_Mode = TIMER_CH_MODE_CAPTURE;
   sTIM2_ChnInit.TIMER_CH_EventSource = TIMER_CH_EvSrc_PE; //отрицательный фронт
   TIMER_ChnInit (MDR_TIMER2, &sTIM2_ChnInit);
	 
	 TIMER_ChnCCR1_Cmd(MDR_TIMER2, TIMER_CHANNEL2, ENABLE);

	 NVIC_EnableIRQ(TIMER2_IRQn);
	 TIMER_ITConfig(MDR_TIMER2, TIMER_STATUS_CCR_CAP1_CH2, ENABLE);
	 NVIC_SetPriority(TIMER2_IRQn, 0);

	 /* Enable TIMER2 clock */
   TIMER_BRGInit(MDR_TIMER2,TIMER_HCLKdiv1);
	 /* Enable TIMER2 */
   TIMER_Cmd(MDR_TIMER2,ENABLE);
}
//void TIMER2_IRQHandler(void)
//{
//	uint16_t rx;
//	//TIMER_Cmd(MDR_TIMER2,DISABLE);
//	SSP_Cmd(MDR_SSP1, ENABLE);
//	//MDR_PORTA->RXTX ^= PORT_Pin_8;
//  //MDR_PORTA->RXTX = (MDR_PORTA->RXTX ^ PORT_Pin_8);
//	/*if (PORT_ReadInputDataBit (MDR_PORTA, PORT_Pin_8) == 0)
//	{
//			PORT_SetBits(MDR_PORTA, PORT_Pin_8); 
//	}
//	else 
//	{
//			PORT_ResetBits(MDR_PORTA, PORT_Pin_8);
//	}*/
//	//SPI_Transmit_WORD(MDR_SSP1, 0x8388);
//	//uint16_t rx_word = SPI_ReceiveWord(MDR_SSP1);
//	//SPI_Transmit_WORD(MDR_SSP1, 0x8388);
//	if ((count%2)==0)
//	{
//		SSP_SendData(MDR_SSP1, 0x8355);
//	  rx = SPI_ReceiveWord(MDR_SSP1);
//	}
//	else
//	{
//		SSP_SendData(MDR_SSP1, 0xC300);
//	  rx = SPI_ReceiveWord(MDR_SSP1);
//	}
//	count++;
//	//TIMER_Cmd(MDR_TIMER2,ENABLE);
//	SSP_Cmd(MDR_SSP1, DISABLE);
//	TIMER_ClearITPendingBit(MDR_TIMER2, TIMER_STATUS_CCR_CAP1_CH2);

//}
