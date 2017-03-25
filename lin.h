#ifndef LIN_H
#define LIN_H

#include "stm32f10x.h"
#include "stm32f10x_it.h"
#include "stm32f10x_conf.h"
#include "lin_type.h"
#include "task.h"

/****小小调度器开始**********************************************/
extern volatile u8 timers[MAXTASKS];
#define _SS static u8 _lc=0;static u16 delay_ms_i; static u16 delay_s_i; switch(_lc){default: 
#define _EE ;}; _lc=0; return 255;
#define Delay_100us(tickets)  do {_lc=(__LINE__+((__LINE__%256)==0))%256; return tickets ;} while(0); case (__LINE__+((__LINE__%256)==0))%256: 

#define RunTask(TaskName,TaskID) do { if (timers[TaskID]==0) timers[TaskID]=TaskName(); }  while(0); 
#define RunTaskA(TaskName,TaskID) { if (timers[TaskID]==0) {timers[TaskID]=TaskName(); continue;} }   //前面的任务优先保证执行

#define CallSub(SubTaskName) do {u8 currdt; _lc=(__LINE__+((__LINE__%256)==0))%256; return 0; case (__LINE__+((__LINE__%256)==0))%256:  currdt=SubTaskName(); if(currdt!=255) return currdt;} while(0);
#define InitTasks(count) {u8 i; for(i=count;i>0 ;i--) timers[i]=0;for(i=count;i<MAXTASKS ;i++)timers[i]=255;}
#define UpdateTimers(count) {u8 i; for(i=count;i>0 ;i--){if((timers[i-1]!=0)&&(timers[i-1]!=255)) timers[i-1]--;}}
#define StartTasks(mubner) {timers[mubner]=0;}
#define StopTasks(mubner) {timers[mubner]=255;}

#define TasksRestart(mubner) {if(timers[mubner]==255)timers[mubner]=0;}

#define SEM u16
//初始化信号量
#define InitSem(sem) SEM sem=0
//包含外部信号量
#define ExternSem(sem) extern SEM sem
//等待信号量
#define WaitSem(sem) do{ sem=1; Delay_100us(1); if (sem>0) return 1;} while(0)
//长时间等待信号量10ms 周期
#define LongWaitSem(sem) do{ sem=1; Delay_100us(100); if (sem>0) return 1;} while(0)
//等待信号量或定时器溢出， 定时器tickets 最大为0xFFFE
#define WaitSemX(sem,tickets) do { sem=tickets+1; Delay_100us(1); if(sem>1){ sem--;  return 1;} } while(0)
//发送信号量
#define SendSem(sem) do {sem=0;} while(0)
//中断发送信号量
#define SendSemInt(sem) sem=0
//判断信号量是否被等待
#define SemIsWaited(sem) (sem!=0)

/*****小小调度器结束*******************************************************/

/*****小小调度器延伸*******************************************************/
////////////////调度器延时函数//////////////////
//#define Delay_ms(i, time) for(i=0;i<time;i++){Delay_100us(10);}
//#define Delay_s(i, time) for(i=0;i<time;i++){Delay_ms(100);}
#define Delay_ms(time) for(delay_ms_i=0;delay_ms_i<time;delay_ms_i++){Delay_100us(10);}
#define Delay_s(time) for(delay_s_i=0;delay_s_i<time;delay_s_i++){Delay_ms(1000);}

////检测系统繁忙函数
#define system_is_busy	(SysTick->VAL < (SYS_TICK_TIME_100us/2))

/*****小小调度器延伸结束*******************************************************/

///////////////运行数据//////////////
extern run_lin_TypeDef run_struct;

//////////下面定义快捷方式////////
#define SYSTEM_RTC_FALG			run_struct.SYS_DATA.rtc_flag
#define SYSTEM_TIME					run_struct.SYS_DATA.system_time
#define SYSTEM_BOOT_TIME			run_struct.SYS_DATA.boot_time
#define SYSTEM_100US_COUNT		run_struct.SYS_DATA.one_second_count

///////////////系统初始化函数/////////////////
void CLK_Init_lin(void);

///////////////通用功能函数/////////////////
void delay_us(u8 time);//延时少于10us
void initDelay_ms(u16 time);//不能用于线程内, 初始化使用的延时

#endif
