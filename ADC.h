#ifndef __ADC_H
#define __ADC_H

void ADC1273_init();
void ADC1273_reset();
uint16_t ADC1273_Make_Control_Word(uint8_t data, uint8_t reg_addr, uint8_t dev_addr, uint8_t R_W, uint8_t C_D);

#endif /*__ADC_H */