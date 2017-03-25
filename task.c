#include "lin.h"
#include "base.h"


//InitSem(xx);

void Task_Init_lin(void){
	InitTasks(TASK_COUNT); //初始化任务，实际上是给timers清零
	SysTick_Config(SYS_TICK_TIME_100us);
	SYSTEM_100US_COUNT = 0x00;
	
	//初始化不运行的任务
	//StopTasks(TASK_NO_RUN_ID(1));
}

void updateTask(void){
	if(SYSTEM_BOOT_TIME > 3600000){
		SYSTEM_BOOT_TIME = 0;
	}else{
		SYSTEM_BOOT_TIME ++;
	}
	if(SYSTEM_100US_COUNT == 10000){
		SYSTEM_100US_COUNT = 0x00;
		SYSTEM_TIME ++;
	}else{
		SYSTEM_100US_COUNT ++;
	}
	UpdateTimers(TASK_COUNT);
}

void runTask(void){
	while(1){
		
		RunTask(task_base, TASK_NORMAL_ID(0));
                //RunTask(task_wifi,TASK_NORMAL_ID(1));
		
	}
}

