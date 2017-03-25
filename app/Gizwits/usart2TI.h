/**
************************************************************
* @file         gizwits_product.h
* @brief        对应gizwits_product.c的头文件(包含产品软硬件版本定义)
* @author       Gizwits
* @date         2016-09-05
* @version      V0.1.2
* @copyright    Gizwits
* 
* @note         机智云.只为智能硬件而生
*               Gizwits Smart Cloud  for Smart Products
*               链接|增值ֵ|开放|中立|安全|自有|自由|生态
*               www.gizwits.com
*
***********************************************************/
#ifndef _GIZWITS_PRODUCT_H
#define _GIZWITS_PRODUCT_H

#include <stdint.h>
#include <stm32f10x.h>



/**@name USART相关宏定义
* @{
*/
#define UART_BAUDRATE 			9600
#define UART_PORT     			2
#define UART          			USART2
#define UART_IRQ      			USART2_IRQn
#define UART_IRQ_FUN  			USART2_IRQHandler

#if (UART_PORT == 1)
#define UART_GPIO_Cmd          RCC_APB2PeriphClockCmd
#define UART_GPIO_CLK          RCC_APB2Periph_GPIOA

#define UART_AFIO_Cmd          RCC_APB2PeriphClockCmd
#define UART_AFIO_CLK          RCC_APB2Periph_AFIO

#define UART_CLK_Cmd           RCC_APB2PeriphClockCmd
#define UART_CLK               RCC_APB2Periph_USART1 

#define UART_GPIO_PORT         GPIOA
#define UART_RxPin             GPIO_Pin_10
#define UART_TxPin             GPIO_Pin_9
#endif

#if (UART_PORT == 2)
#define UART_GPIO_Cmd          RCC_APB2PeriphClockCmd
#define UART_GPIO_CLK          RCC_APB2Periph_GPIOA

#define UART_AFIO_Cmd          RCC_APB2PeriphClockCmd
#define UART_AFIO_CLK          RCC_APB2Periph_AFIO

#define UART_CLK_Cmd           RCC_APB1PeriphClockCmd
#define UART_CLK               RCC_APB1Periph_USART2 

#define UART_GPIO_PORT         GPIOA
#define UART_RxPin             GPIO_Pin_3
#define UART_TxPin             GPIO_Pin_2
#endif


#if (UART_PORT == 3)

#define UART_GPIO_Cmd          RCC_APB2PeriphClockCmd
#define UART_GPIO_CLK          RCC_APB2Periph_GPIOC

#define UART_AFIO_Cmd          RCC_APB2PeriphClockCmd
#define UART_AFIO_CLK          RCC_APB2Periph_AFIO

#define UART_CLK_Cmd           RCC_APB1PeriphClockCmd
#define UART_CLK               RCC_APB1Periph_USART3 

#define UART_GPIO_PORT         GPIOC
#define UART_RxPin             GPIO_Pin_11
#define UART_TxPin             GPIO_Pin_10

#endif

int32_t uartWrite(uint8_t *buf, uint32_t len);
int Usart_DMA_WriteParam( uint8_t *buf, uint32_t len);

#endif
