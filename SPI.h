#ifndef __SPI_H
#define __SPI_H

void SPI_init(void);
void SPI_Transmit_WORD(MDR_SSP_TypeDef* SSPx, uint16_t WORD);
void SPI_Transmit_Message(MDR_SSP_TypeDef* SSPx, uint16_t message[], uint32_t length);
uint16_t SPI_ReceiveWord(MDR_SSP_TypeDef* SSPx);

#endif /*__SPI_H */