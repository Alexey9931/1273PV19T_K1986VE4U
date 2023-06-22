#ifndef __TIMER_H
#define __TIMER_H

void TIMER1_init();
void Delay_micro(uint32_t time_micro);
void TIMER2_IRQHandler(void);

#endif /*__TIMER_H */