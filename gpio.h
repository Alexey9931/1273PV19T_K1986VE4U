#ifndef __GPIO_H
#define __GPIO_H


#include <MDR32F9Qx_port.h>
#include <MDR32F9Qx_rst_clk.h>

void PortsInit(void);
void EXT_INT0_IRQHandler(void);
void EXT_INTERRUPT_init(void);

#endif /*__GPIO_H */