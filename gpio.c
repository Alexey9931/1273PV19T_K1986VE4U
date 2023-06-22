
#include "GPIO.h"

void PortsInit(void)
{
	// Включение тактирования портов
	RST_CLK_PCLKcmd(RST_CLK_PCLK_RST_CLK|RST_CLK_PCLK_PORTB|RST_CLK_PCLK_PORTA, ENABLE);
	
	//Инициализация порта B для канала 2 таймера 2
	PORT_InitTypeDef GPIO_init_struct_TIMER2;
	
	PORT_StructInit (&GPIO_init_struct_TIMER2);
	GPIO_init_struct_TIMER2.PORT_FUNC = PORT_FUNC_MAIN;
	GPIO_init_struct_TIMER2.PORT_OE = PORT_OE_IN;
	GPIO_init_struct_TIMER2.PORT_SPEED = PORT_SPEED_FAST;
	GPIO_init_struct_TIMER2.PORT_MODE = PORT_MODE_DIGITAL;
	GPIO_init_struct_TIMER2.PORT_Pin = PORT_Pin_10;
	PORT_Init (MDR_PORTB, &GPIO_init_struct_TIMER2);
	
	// Инициализация порта B для функции UART
	PORT_InitTypeDef GPIO_init_struct_UART;

	PORT_StructInit(&GPIO_init_struct_UART);
	// Переопределение функции порта
	GPIO_init_struct_UART.PORT_FUNC = PORT_FUNC_MAIN;
	// Установка короткого фронта
	GPIO_init_struct_UART.PORT_SPEED = PORT_SPEED_MAXFAST;
	// Цифровой режим работы вывода
	GPIO_init_struct_UART.PORT_MODE = PORT_MODE_DIGITAL;
	// Инициализация вывода PF1 как UART_TX (передача)
	GPIO_init_struct_UART.PORT_Pin = PORT_Pin_0;
	GPIO_init_struct_UART.PORT_OE = PORT_OE_OUT;
	PORT_Init(MDR_PORTB, &GPIO_init_struct_UART);
	// Инициализация вывода PF0 как UART_RX (прием)
	GPIO_init_struct_UART.PORT_Pin = PORT_Pin_1;
	GPIO_init_struct_UART.PORT_OE = PORT_OE_IN;
	PORT_Init(MDR_PORTB, &GPIO_init_struct_UART);

	// Инициализация порта A для функции SPI
	PORT_InitTypeDef GPIO_init_struct_SPI;
	
	PORT_StructInit(&GPIO_init_struct_SPI);
	GPIO_init_struct_SPI.PORT_FUNC = PORT_FUNC_MAIN;
	GPIO_init_struct_SPI.PORT_MODE = PORT_MODE_DIGITAL;
	GPIO_init_struct_SPI.PORT_SPEED = PORT_SPEED_MAXFAST;
	//Инициализация вывода PA13 как SCK
	GPIO_init_struct_SPI.PORT_Pin = PORT_Pin_13;
	GPIO_init_struct_SPI.PORT_OE = PORT_OE_IN;
	PORT_Init(MDR_PORTA, &GPIO_init_struct_SPI);
	//Инициализация вывода PA14 как SSP_RX
	GPIO_init_struct_SPI.PORT_Pin = PORT_Pin_14;
	GPIO_init_struct_SPI.PORT_OE = PORT_OE_IN;
	PORT_Init(MDR_PORTA, &GPIO_init_struct_SPI);
	//Инициализация вывода PA15 как SSP_TX
	GPIO_init_struct_SPI.PORT_Pin = PORT_Pin_15;
	GPIO_init_struct_SPI.PORT_OE = PORT_OE_OUT;
	PORT_Init(MDR_PORTA, &GPIO_init_struct_SPI);
	//Инициализация вывода PA12 как SS
	GPIO_init_struct_SPI.PORT_Pin = PORT_Pin_12;
	GPIO_init_struct_SPI.PORT_FUNC = PORT_FUNC_PORT;
	GPIO_init_struct_SPI.PORT_OE = PORT_OE_OUT;
	PORT_Init(MDR_PORTA, &GPIO_init_struct_SPI);
	//установка SS в лог ноль
	PORT_ResetBits(MDR_PORTA,PORT_Pin_12);
	
	//инициализация RESET PA9 Для аппаратного сброса ацп
	GPIO_init_struct_SPI.PORT_Pin = PORT_Pin_9;
	GPIO_init_struct_SPI.PORT_OE = PORT_OE_OUT;
	PORT_Init(MDR_PORTA, &GPIO_init_struct_SPI);
	//установка RESET в лог единицу
	PORT_SetBits(MDR_PORTA,PORT_Pin_9);
	
	//Инициализация PA10 для внешнего прерывания EXT_INT0 от SDOFS
	GPIO_init_struct_SPI.PORT_Pin = PORT_Pin_10;
	GPIO_init_struct_SPI.PORT_OE = PORT_OE_IN;
	GPIO_init_struct_SPI.PORT_FUNC = PORT_FUNC_PORT;
	GPIO_init_struct_SPI.PORT_SPEED = PORT_SPEED_MAXFAST;
	PORT_Init(MDR_PORTA, &GPIO_init_struct_SPI);
	//PORT_ResetBits(MDR_PORTA,PORT_Pin_10);
	
	GPIO_init_struct_SPI.PORT_Pin = PORT_Pin_8;
	GPIO_init_struct_SPI.PORT_OE = PORT_OE_OUT;
	GPIO_init_struct_SPI.PORT_FUNC = PORT_FUNC_PORT;
	GPIO_init_struct_SPI.PORT_SPEED = PORT_SPEED_MAXFAST;
	PORT_Init(MDR_PORTA, &GPIO_init_struct_SPI);
	PORT_ResetBits(MDR_PORTA,PORT_Pin_8);
	
}
void EXT_INTERRUPT_init(void)
{
	NVIC_ClearPendingIRQ(EXT_INT0_IRQn);
	__enable_irq();
	NVIC_EnableIRQ(EXT_INT0_IRQn);
}
void EXT_INT0_IRQHandler(void)
{
	NVIC_DisableIRQ(EXT_INT0_IRQn);
	__IO uint32_t tt = MDR_PORTA->RXTX & PORT_Pin_10;
	MDR_PORTA->RXTX ^= PORT_Pin_8;
while ((MDR_PORTA->RXTX & PORT_Pin_10) != PORT_Pin_10){}
	
	NVIC_ClearPendingIRQ(EXT_INT0_IRQn);
	NVIC_EnableIRQ(EXT_INT0_IRQn);
	//SSP_Cmd(MDR_SSP1, ENABLE);
	//SPI_ReceiveWord(MDR_SSP1);
  
	//SSP_Cmd(MDR_SSP1, DISABLE);
	//NVIC_EnableIRQ(EXT_INT0_IRQn);
	
}
