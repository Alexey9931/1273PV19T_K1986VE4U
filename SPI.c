#include <MDR1986BE4.h>
#include <MDR32F9Qx_ssp.h>
#include <MDR32F9Qx_port.h>
#include <MDR32F9Qx_rst_clk.h>
#include "SPI.h"


void SPI_init(void)
{
	//Структура для инициализации SPI
	SSP_InitTypeDef SSP_InitStruct;
	
	// Включение тактирования SPI
	RST_CLK_PCLKcmd(RST_CLK_PCLK_SSP1, ENABLE);

	SSP_StructInit(&SSP_InitStruct);
	
	SSP_BRGInit (MDR_SSP1, SSP_HCLKdiv1);
	
	SSP_InitStruct.SSP_WordLength = SSP_WordLength16b;
	SSP_InitStruct.SSP_Mode = SSP_ModeSlave;
	SSP_InitStruct.SSP_SPH = SSP_SPH_1Edge;
  SSP_InitStruct.SSP_FRF = SSP_FRF_SPI_Motorola;
  SSP_InitStruct.SSP_HardwareFlowControl = SSP_HardwareFlowControl_SSE;
	//SSP_InitStruct.SSP_SCR  = 0x10;
  SSP_InitStruct.SSP_CPSDVSR = 40;//частота обмена 2МГц
	SSP_Init(MDR_SSP1,&SSP_InitStruct);
	
	// Выбор источников прерываний (прием и передача данных)
  SSP_ITConfig (MDR_SSP1, SSP_IT_RX | SSP_IT_TX, ENABLE);
	
	SSP_Cmd(MDR_SSP1, DISABLE);
	
}
void SPI_Transmit_WORD(MDR_SSP_TypeDef* SSPx, uint16_t WORD)
{
	SSP_SendData(SSPx, WORD);
	while (	SSP_GetFlagStatus(SSPx, SSP_FLAG_TFE) != SET);
}
void SPI_Transmit_Message(MDR_SSP_TypeDef* SSPx, uint16_t message[], uint32_t length)
{
	for(uint32_t i = 0; i < length; i++)
	{
		while(SSP_GetFlagStatus(SSPx, SSP_FLAG_TNF) != SET) {} // Ждем когда в буфере появится место и затем записываем следующий байт
		SSP_SendData(SSPx, message[i]);			
	}	
	while (SSP_GetFlagStatus(SSPx, SSP_FLAG_TFE) != SET) {}  //ждем пока байт уйдет		
}
uint16_t SPI_ReceiveWord(MDR_SSP_TypeDef* SSPx)
{	
	uint16_t tmpVar;
	// Обработка прерывания от приемника данных
	while (SSP_GetFlagStatus(SSPx, SSP_FLAG_RNE) != SET)  {}  //ждем пока появится байт  
	// Получаем данные
	tmpVar = SSP_ReceiveData(SSPx);
		
	return tmpVar;
}