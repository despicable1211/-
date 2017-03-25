#ifndef __DMA1_H
#define	__DMA1_H	   
#include <stm32f10x.h>
#include <string.h>
#include "usart/usart.h"
							    					    
#define BUF_SIZE1 150  //数据长度

extern u8 ReceiBuff1[BUF_SIZE1];  //数据缓冲区
extern u8 SendBuff1[BUF_SIZE1];  //数据缓冲区

void dma1_init(void);
int32_t uart1Write(uint8_t *buf, uint32_t len);
		   
#endif
