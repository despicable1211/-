#include "usart.h"

u8 USART_RX_BUF[USART_REC_LEN]; //接收缓存区数值长度
u16 USART_RX_STA = 0;

void usart_init(u32 bound)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  USART_InitTypeDef USART_InitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;
  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA,ENABLE);
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA,&GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOA,&GPIO_InitStructure);
  
  
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQN;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
  
  USART_InitStructure.USART_BaudRate = bound;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HarwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.UASRT_Mode = USART_Mode_Rx|USART_Mode_Tx;
  
  USART_Init(USART1,&USART_InitStructure);
  USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
  USART_Cmd(USART1,ENABLE);
}
//串口中断
void USART1_IRQHandler(void)
{
  u8 Res;
  
  if(USART_GetITStatus(USART1,USART_IT_RXNE)!=RESET))
}