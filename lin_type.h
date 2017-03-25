#ifndef LIN_CONF_H
#define LIN_CONF_H

#include "stm32f10x.h"

///////下面定义基础变量与基础宏定义//////
//下面定义位操作
#define BIT0		(u8)0x01
#define BIT1		(u8)0x02
#define BIT2		(u8)0x04
#define BIT3		(u8)0x08
#define BIT4		(u8)0x10
#define BIT5		(u8)0x20
#define BIT6		(u8)0x40
#define BIT7		(u8)0x80
#define ALL_BIT	(u8)0xFF

//定义boolean 类型
typedef enum {FALSE = 0, TRUE = !FALSE} bool;

//下面定义线程相关常量
#define MAXTASKS				32	//最大线程数
//#define SYS_TICK_TIME_1ms		36000	//系统时钟1ms
//#define SYS_TICK_TIME_100us		3600	//系统时钟100us
#define SYS_TICK_TIME_1ms		(SystemCoreClock/1000)	//系统时钟1ms
#define SYS_TICK_TIME_100us	(SystemCoreClock/10000)	//系统时钟100us
#define TASK_COUNT				20
#define TASK_BASE_ID			0
#define TASK_NORMAL_ID(ID)		(TASK_BASE_ID+ID)
#define TASK_NO_RUN_ID(ID)		(TASK_COUNT-ID)

//定义超短延时函数常量
#define DELAY_US_TICKS			(SYS_TICK_TIME_100us/100)	//系统时钟1us
#define DELAY_MS_TICKS			(DELAY_US_TICKS*1000)		//系统时钟1ms

//定义GPIO 引脚结构体
typedef struct{
	GPIO_TypeDef * GPIOx;
	u16 Pinx;
}GPIO_Channel_TypeDef;

//下面定义系统常量
typedef struct{
	u8 rtc_flag;
	u16 one_second_count;
	u32 system_time;
	u32 boot_time;
}SYSTEM_lin_TypeDef;


/////////////下面定义运行结构体///////////////
typedef struct{
	//定义系统结构体
	SYSTEM_lin_TypeDef SYS_DATA;
	
}run_lin_TypeDef;

#endif
