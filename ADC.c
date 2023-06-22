#include <MDR1986BE4.h>
#include <MDR32F9Qx_ssp.h>
#include <MDR32F9Qx_port.h>
#include <MDR32F9Qx_rst_clk.h>
#include "SPI.h"
#include "ADC.h"

int i;
#define DELAY(T) for (i = T; i > 0; i--)

void ADC1273_init()
{
	PORT_SetBits(MDR_PORTA,PORT_Pin_12);
	//Заполняем регистр управления А (режим управления,не смешанный,кол-во устр-в 1, нет сброса)
	SPI_Transmit_WORD(MDR_SSP1, ADC1273_Make_Control_Word(0x00, 0, 0, 0, 1));
	//Заполняем регистр управления B (делитель 1, все по умолчанию)
	/*SPI_Transmit_WORD(MDR_SSP1, ADC1273_Make_Control_Word(0x00, 1, 0, 0, 1));
	//Заполняем регистр управления C(вкл 5в режим,актив вывод REFOUT,вкл внутр опорн ист, вкл питание на всех каналах)
	SPI_Transmit_WORD(MDR_SSP1, ADC1273_Make_Control_Word(0xE1, 2, 0, 0, 1));
	//Заполняем регистр управления D (питание АЦП1,2 вкл, усиления нет)
	SPI_Transmit_WORD(MDR_SSP1, ADC1273_Make_Control_Word(0x88, 3, 0, 0, 1));
	//Заполняем регистр управления E (питание АЦП3,4 вкл, усиления нет)
	SPI_Transmit_WORD(MDR_SSP1, ADC1273_Make_Control_Word(0x88, 4, 0, 0, 1));
	//Заполняем регистр управления F (питание АЦП5,6 вкл, усиления нет)
	SPI_Transmit_WORD(MDR_SSP1, ADC1273_Make_Control_Word(0x88, 5, 0, 0, 1));
	//Заполняем регистр управления G (режим однополярного входа на всех каналах)
	SPI_Transmit_WORD(MDR_SSP1, ADC1273_Make_Control_Word(0xBF, 6, 0, 0, 1));
	//Заполняем регистр управления H (инверсный режим отключен)
	SPI_Transmit_WORD(MDR_SSP1, ADC1273_Make_Control_Word(0x00, 7, 0, 0, 1));*/
	//переход в режим данных
	//SPI_Transmit_WORD(MDR_SSP1, ADC1273_Make_Control_Word(0x01, 0, 0, 0, 1));
	
	//Пробуем считать результата ацп по 1 каналу
	//SPI_Transmit_WORD(MDR_SSP1, 0x7FFF);
	Delay_milli(5);
	PORT_ResetBits(MDR_PORTA,PORT_Pin_12);
}
void ADC1273_reset()
{
	Delay_milli(500);
	PORT_ResetBits(MDR_PORTA,PORT_Pin_9);
	Delay_milli(500);
	PORT_SetBits(MDR_PORTA,PORT_Pin_9);
	Delay_milli(500);
}
uint16_t ADC1273_Make_Control_Word(uint8_t data, uint8_t reg_addr, uint8_t dev_addr, uint8_t R_W, uint8_t C_D)
{
	uint16_t DATA;
	DATA |= C_D;
	DATA = DATA << 1;
	DATA |= R_W;
	DATA = DATA << 3;
	DATA |= dev_addr;
	DATA = DATA << 3;
	DATA |= reg_addr;
	DATA = DATA << 8;
	DATA |= data;
	
	return DATA;
}