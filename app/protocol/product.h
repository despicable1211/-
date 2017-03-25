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
*               链接|增值?|开放|中立|安全|自有|自由|生态
*               www.gizwits.com
*
***********************************************************/
#ifndef _PRODUCT_H
#define _PRODUCT_H

#include <stdint.h>
#include <stm32f10x.h>

#define TIMER 					TIM3
#define TIMER_IRQ 				TIM3_IRQn
#define TIMER_RCC 				RCC_APB1Periph_TIM3
#define TIMER_IRQ_FUN 			TIM3_IRQHandler



/**@name 设备状态数据上报间隔时间宏定义*/

#define REPORT_TIME_MAX 6000 //6S


void timerInit(void);

#endif