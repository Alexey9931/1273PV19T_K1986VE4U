#include "rst.h"

#include <MDR1986BE4.h>
#include <MDR32F9Qx_rst_clk.h>

void U_RST_Init(void)
{
	//настройка тактирования от внешнего кварца 16 МГц
	// Включаем генератор на внешнем кварце
	RST_CLK_HSEconfig (RST_CLK_HSE_ON);
	while (RST_CLK_HSEstatus () != SUCCESS);
	
	// Настраиваем источник и коэффициент умножения PLL
	//(CPU_C1_SEL = HSE / 1 * 5 = 80 МГц )
	RST_CLK_CPU_PLLconfig ( RST_CLK_CPU_PLLsrcHSEdiv1,RST_CLK_CPU_PLLmul5);
	
	// Включаем PLL, но еще не подключаем к кристаллу (PLL умножает частоту тактирования)
	RST_CLK_CPU_PLLcmd (ENABLE);
	while (RST_CLK_CPU_PLLstatus () != SUCCESS);
	
	// Делитель С3 ( CPU_C3_SEL = CPU_C2_SEL )
	RST_CLK_CPUclkPrescaler (RST_CLK_CPUclkDIV1);
	
	// На С2 идет с PLL, а не напрямую с С1 (CPU_C2_SEL = PLL)
	RST_CLK_CPU_PLLuse (ENABLE);
	// CPU берет тактирование с выхода С3
	//(HCLK_SEL = CPU_C3_SEL = 80 МГц)
	RST_CLK_CPUclkSelection(RST_CLK_CPUclkCPU_C3);
	
	//тактирование UART,TIM,SSP (PER1_C2_SEL)-берем от PLLCPU0(80МГц)
	RST_CLK_PCLKPer1_C2_CLKSelection(RST_CLK_PER1_C2_CLK_SRC_PLLCPU);
}