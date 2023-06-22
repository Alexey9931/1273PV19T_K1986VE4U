#include <MDR1986BE4.h>
#include <MDR32F9Qx_ssp.h>
#include "GPIO.h"
#include "rst.h"
#include "SPI.h"
#include "ADC.h"
#include "TIMER.h"

uint8_t oldstate = 10;
uint8_t newstate = 0;
static uint8_t counter = 0; 
int j;
#define DELAY(T) for (j = T; j > 0; j--)

int main(void)
{
	U_RST_Init();
	PortsInit();
	PORT_SetBits(MDR_PORTA,PORT_Pin_12);
	SPI_init();
	TIMER1_init();
	//TIMER2_init();
	ADC1273_reset();

	/*SSP_Cmd(MDR_SSP1, ENABLE);
	SSP_SendData(MDR_SSP1, 0x8388);
	SSP_Cmd(MDR_SSP1, DISABLE);*/
	//SSP_SendData(MDR_SSP1, 0x8388);
	//Delay_milli(999);
	//SSP_SendData(MDR_SSP1, 0xC300);
	//ADC1273_init();
	//EXT_INTERRUPT_init();
	/*SPI_Transmit_WORD(MDR_SSP1, 0x8388);
	Delay_milli(1);
	SPI_Transmit_WORD(MDR_SSP1, 0xC300);*/
  //PORT_ResetBits(MDR_PORTA,PORT_Pin_12);
	
	/*PORT_SetBits(MDR_PORTA,PORT_Pin_12);
	SPI_Transmit_WORD(MDR_SSP1, 0xC300);
	DELAY(5);
	PORT_ResetBits(MDR_PORTA,PORT_Pin_12);*/
	while(1)
	{
		oldstate = newstate;
		newstate = PORT_ReadInputDataBit(MDR_PORTA, PORT_Pin_10);
		if ((newstate == 0)&&(oldstate == 1))
		//if(newstate == 1)
		{
			//MDR_PORTA->RXTX ^= PORT_Pin_8;
			PORT_SetBits(MDR_PORTA,PORT_Pin_8);
			PORT_ResetBits(MDR_PORTA,PORT_Pin_8);
			/*uint16_t rx; 
			SSP_Cmd(MDR_SSP1, ENABLE);
			if ((counter%2)==0)
			{
				SSP_SendData(MDR_SSP1, 0x4355);
				rx = SPI_ReceiveWord(MDR_SSP1);
			}
			else
			{
				SSP_SendData(MDR_SSP1, 0xC300);
				rx = SPI_ReceiveWord(MDR_SSP1);
			}
			counter++;
			SSP_Cmd(MDR_SSP1, DISABLE);*/
		}
		/*PORT_SetBits(MDR_PORTA,PORT_Pin_12);
		SPI_Transmit_WORD(MDR_SSP1, 0xC300);
		Delay_milli(5);
		PORT_ResetBits(MDR_PORTA,PORT_Pin_12);
		Delay_milli(500);*/
	}
}