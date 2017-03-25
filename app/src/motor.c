#include "motor.h"

void left_motor_gpio_init(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD|RCC_APB2Periph_GPIOE|RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC, ENABLE);//使能GPIOD时钟
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;//10MHz
    GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIO
          
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;//10MHz
    GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIO 
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;//10MHz
    GPIO_Init(GPIOC, &GPIO_InitStructure);//初始化GPIO
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;//10MHz
    GPIO_Init(GPIOD, &GPIO_InitStructure);//初始化GPIO
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;//10MHz
    GPIO_Init(GPIOE, &GPIO_InitStructure);//初始化GPIO
}

void left_motor_pwm_init(u16 arr,u16 psc)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    TIM_OCInitTypeDef  TIM_OCInitStructure;
    

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);	
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB  | RCC_APB2Periph_AFIO, ENABLE);  
    
    GPIO_PinRemapConfig(GPIO_Remap_TIM4, ENABLE);     


    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8; 
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);


    TIM_TimeBaseStructure.TIM_Period = arr; 
    TIM_TimeBaseStructure.TIM_Prescaler =psc; 
    TIM_TimeBaseStructure.TIM_ClockDivision = 0; 
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); 
    
	 
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //选择定时器模式:TIM脉冲宽度调制模式2
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性高
    TIM_OC2Init(TIM4, &TIM_OCInitStructure);  

    TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);  

    TIM_Cmd(TIM4, ENABLE);  
}