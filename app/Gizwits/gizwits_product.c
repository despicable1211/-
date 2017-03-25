/**
************************************************************
* @file         gizwits_product.c
* @brief        Gizwits 控制协议处理,及平台相关的硬件初始化 
* @author       Gizwits
* @date         2016-09-05
* @version      V03010101
* @copyright    Gizwits
* 
* @note         机智云.只为智能硬件而生
*               Gizwits Smart Cloud  for Smart Products
*               链接|增值ֵ|开放|中立|安全|自有|自由|生态
*               www.gizwits.com
*
***********************************************************/

#include <stdio.h>
#include <string.h>
#include "usart.h"
#include "usart2TI.h"
#include "dma.h"


/**
* @brief USART2串口中断函数

* 接收功能，用于接收与WiFi模组间的串口协议数据
* @param none
* @return none
*/
void UART_IRQ_FUN(void)
{
    uint8_t value = 0;
    if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
    {
        USART_ClearITPendingBit(USART2,USART_IT_RXNE);
        value = USART_ReceiveData(USART2);
        
        printf("%x\n",value);
 
        USART_DMACmd(USART2,USART_DMAReq_Rx,ENABLE); //是你串口接收     
	MYDMA_Enable(DMA1_Channel4);
    }
}


/**
* @brief 串口写操作，发送数据到WiFi模组
*
* @param buf      : 数据地址
* @param len       : 数据长度
*
* @return : 正确返回有效数据长度;-1，错误返回
*/
int32_t uartWrite(uint8_t *buf, uint32_t len)
{
    uint32_t i = 0;
    
    if(NULL == buf)
    {
        return -1;
    }

    
    for(i=0; i<len; i++)
    {
        USART_SendData(UART, buf[i]);
        while (USART_GetFlagStatus(UART, USART_FLAG_TXE) == RESET);//Loop until the end of transmission

        if(i >=2 && buf[i] == 0xFF)
        {
          USART_SendData(UART,0x55);
          while (USART_GetFlagStatus(UART, USART_FLAG_TXE) == RESET);//Loop until the end of transmission

        }
    }
    

    
    return len;
}
