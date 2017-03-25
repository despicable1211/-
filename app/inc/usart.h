#ifndef __USART_H
#define __USART_H

#include "stdio.h"
#include "stm32f10x.h"

#define USART_REC_LEN  200
#define EN_USART_RX     1

void usart_init(u32 bound);
#endif