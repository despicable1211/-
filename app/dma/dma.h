#ifndef __DMA_H
#define	__DMA_H	   
#include <stm32f10x.h>

							    					    
#define BUF_SIZE 150  //数据长度

extern u8 ReceiBuff[BUF_SIZE];  //数据缓冲区
extern u8 SendBuff[BUF_SIZE*2];  //数据缓冲区

void dma_init(void);
int32_t uartWrite(uint8_t *buf, uint32_t len);
		   
#endif




