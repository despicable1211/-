#include "key.h"

void key_init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOC, ENABLE);//使能GPIOA,GPIOC时钟
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_12;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  
  GPIO_Init(GPIOA,GPIO_InitStructure);//初始化按键a8，a12
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
  
  GPIO_Init(GPIOC,GPIO_InitStructure);//初始化按键c6

}
//按键扫描函数
//mode：0，不支持连续按；1，支持连续按
int key_scan(int mode)
{
  static int key_up = 1;
  if(mode) key_up = 1;
  if(key_up&&(KEY1==0||KEY2==0||KEY3==0))
  {
    delay_ms(10);
    key_up = 0;
    if(KEY1==0)return KEY1_PRES;
    else if(KEY2==0)return KEY2_PRES;
    else if(KEY3==0)return KEY3_PRES;
  }else if(KEY0==1&&KEY2==1&&KEY3==1)key_up = 1;
  return 0;
}