#include "lin.h"

void CLK_Init_lin(void){
	// ErrorStatus HSEStartUpStatus;
	RCC_DeInit();
	RCC_HSEConfig(RCC_HSE_OFF);	        //关外部高速时钟 
	
	FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
	FLASH_SetLatency(FLASH_Latency_2);
	RCC_HCLKConfig(RCC_SYSCLK_Div1); 
	RCC_PCLK2Config(RCC_HCLK_Div1); 
	RCC_PCLK1Config(RCC_HCLK_Div1);
	RCC_PLLConfig(RCC_PLLSource_HSI_Div2,RCC_PLLMul_9);
	RCC_PLLCmd(ENABLE);
	while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);
	RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
	while(RCC_GetSYSCLKSource() != 0x08);
}

void delay_us(u8 time){
	u32 ticks;
	u32 told,tnow,tcnt=0;
	u32 reload=SysTick->LOAD;					//LOAD的值	    	 
	if(time > 10){
		time = 10;
	}
	ticks=time*DELAY_US_TICKS; 		//需要的节拍数	  		 
	tcnt=0;
	//delay_osschedlock();						//阻止OS调度，防止打断us延时
	told=SysTick->VAL;        					//刚进入时的计数器值
	while(1){
		tnow=SysTick->VAL;	
		if(tnow!=told){	    
			if(tnow<told)tcnt+=told-tnow;		//这里注意一下SYSTICK是一个递减的计数器就可以了.
			else tcnt+=reload-tnow+told;	    
			told=tnow;
			if(tcnt>=ticks)break;				//时间超过/等于要延迟的时间,则退出.
		}  
	}
	//delay_osschedunlock();						//恢复OS调度			
}

void initDelay_ms(u16 time){
	/*
	for(u16 i=0; i<(time*100); i++){
		delay_us(10);
	}
	//*/
	///*
	//不能用于线程内, 初始化使用的延时
	u32 ticks;
	u32 told,tnow,tcnt=0;
	u32 reload=SysTick->LOAD;					//LOAD的值	    	 
	ticks=DELAY_MS_TICKS; 		//需要的节拍数	  		 
	//delay_osschedlock();						//阻止OS调度，防止打断us延时
	for(u16 i=0; i<time; i++){
		tcnt=0;
		told=SysTick->VAL;        					//刚进入时的计数器值
		while(1){
			tnow=SysTick->VAL;	
			if(tnow!=told){	    
				if(tnow<told)tcnt+=told-tnow;		//这里注意一下SYSTICK是一个递减的计数器就可以了.
				else tcnt+=reload-tnow+told;	    
				told=tnow;
				if(tcnt>=ticks)break;				//时间超过/等于要延迟的时间,则退出.
			}  
		}
	}
	//delay_osschedunlock();						//恢复OS调度	
	//*/
}

