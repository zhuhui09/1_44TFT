#ifndef UART_H
#define UART_H

#include "stm32f10x_conf.h"

#define BOUND 115200

void USARTNV(void);
void USART_SEND_DATA( USART_TypeDef* USARTx, uint8_t * dat );

#endif
