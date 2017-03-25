#include "buzzer.h"

void buzzer_init(void)
{   
  GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);//使能GPIOD时钟
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;//10MHz
  GPIO_Init(GPIOD, &GPIO_InitStructure);//初始化GPIO
	
  GPIO_ResetBits(GPIOD,GPIO_Pin_1);  //蜂鸣器对应引脚GPIOD1拉低， 
}