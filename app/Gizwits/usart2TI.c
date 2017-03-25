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
#include "dma/dma.h"

void Uart2_DMA_Rx(void);
void Uart2_DAM_Tx(void);
void Uart2_Start_DMA_Tx(uint32_t size);

/*****DMA接收函数*****/

/*void UART_IRQ_FUN(void)
{
    uint8_t value = 0;
    if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
    {
        USART_ClearITPendingBit(USART2,USART_IT_RXNE);
//        value = USART_ReceiveData(USART2);
//        printf("%x\n",value);
        Uart2_DMA_Rx();
//        value = USART_ReceiveData(USART2);      // Clear IDLE interrupt flag bit
//        printf("RX = %x\n",value);
    }
}
void Uart2_DMA_Rx(void)
{
    int temp = 0;
    DMA_Cmd(DMA1_Channel6, DISABLE);       // 关闭DMA ，防止干扰

    DMA_ClearFlag( DMA1_FLAG_GL6 );           // 清DMA标志位

    temp = BUF_SIZE - DMA_GetCurrDataCounter(DMA1_Channel7); //获得接收到的字节数
    
    DMA1_Channel6->CNDTR = BUF_SIZE;    //  重新赋值计数值，必须大于等于最大可能接收到的数据帧数目

    DMA_Cmd(DMA1_Channel6, ENABLE);    */    /* DMA 开启，等待数据。注意，如果中断发送数据帧的速率很快，MCU
    来不及处理此次接收到的数据，中断又发来数据的话，这里不能开启，否则数据会被覆盖。有2种方式解决。

    1. 在重新开启接收DMA通道之前，将LumMod_Rx_Buf缓冲区里面的数据复制到另外一个数组中，然后再开启DMA，然后马上处理复制
    出来的数据。

    2. 建立双缓冲，在LumMod_Uart_DMA_Rx_Data函数中，重新配置DMA_MemoryBaseAddr 的缓冲区地址，那么下次接收到的数据就会
    保存到新的缓冲区中，不至于被覆盖。*/

    //OSMboxPost(mbLumModule_Rx,  LumMod_Rx_Buf); // 发送接收到新数据标志，供前台程序查询
//}
/*******DMA接收中断函数*******/
void DMA1_Channel6_IRQHandler(void)
{
    int temp = 0;  
    DMA_Cmd(DMA1_Channel6, DISABLE);       // 关闭DMA ，防止干扰

    DMA_ClearFlag( DMA1_FLAG_GL6 );             // 清DMA标志位

    temp = BUF_SIZE - DMA_GetCurrDataCounter(DMA1_Channel6); //获得接收到的字节数
    
    DMA1_Channel6->CNDTR = BUF_SIZE;    //  重新赋值计数值，必须大于等于最大可能接收到的数据帧数目

    DMA_Cmd(DMA1_Channel6, ENABLE);        // DMA 开启，等待数据。
}
/******DMA发送中断函数*******/
void DMA1_Channel7_IRQHandler(void)

{

    if(DMA_GetITStatus(DMA1_FLAG_TC7))

    {

        Uart2_DAM_Tx();

    }

}

void Uart2_DAM_Tx(void)

{

    DMA_ClearFlag(DMA1_FLAG_GL7);         // 清除标志

    DMA_Cmd(DMA1_Channel7, DISABLE);   // 关闭DMA通道

    //OSMboxPost(mbLumModule_Tx, (void*)1);           // 设置标志位，这里我用的是UCOSII ，可以根据自己的需求进行修改

}

/********************************* 
@brief     :    DMA发送函数，发送数据到WIFI模组
@param buf :    数据地址
@param len :    数据长度

@return    ：正确返回数据长度；错误返回 -1；
********************************/

int Usart_DMA_WriteParam( uint8_t *buf, uint32_t len)

{
    int i;
    
    if(NULL==buf) return -1;
    
    for(i=0;i<len;i++)
    {
      SendBuff[i] = buf[i];
      if(i>=2&&buf[i]==0xff)
        SendBuff[i++]=0x55;
      len++;
    }

    Uart2_Start_DMA_Tx( len );
    
    return len;
}

 

void Uart2_Start_DMA_Tx(uint32_t size)

{

    DMA1_Channel7->CNDTR = (uint32_t)size; // 设置要发送的字节数目

    DMA_Cmd(DMA1_Channel7, ENABLE);        //开始DMA发送

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
