
#include "dma.h"
#include <string.h>


u8 ReceiBuff[BUF_SIZE];  //数据缓冲区
u8 SendBuff[BUF_SIZE*2];  //数据缓冲区



u16 DMA1_MEM_LEN;//保存DMA每次数据传送的长度 	    

//DMA初始化

void dma_init(void)
{
        DMA_InitTypeDef DMA_InitStructure;
        NVIC_InitTypeDef NVIC_InitStructure;

        RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);	//使能DMA传输
        
/**************** Tx_DMA conifg ************************/
        
        DMA_Cmd(DMA1_Channel7, DISABLE);   // 关DMA通道
        DMA_DeInit(DMA1_Channel7);   //将DMA的通道7寄存器重设为缺省值
        
	DMA1_MEM_LEN=BUF_SIZE;
	DMA_InitStructure.DMA_PeripheralBaseAddr =(u32)(&USART2->DR);  //DMA外设基地址
	DMA_InitStructure.DMA_MemoryBaseAddr =(u32) SendBuff;  //DMA内存基地址
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;  //数据传输方向，从内存读取发送到外设
	DMA_InitStructure.DMA_BufferSize = DMA1_MEM_LEN;  //DMA通道的DMA缓存的大小
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;  //外设地址寄存器不变
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;  //内存地址寄存器递增
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;  //数据宽度为8位
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte; //数据宽度为8位
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;  //工作在正常模式
	DMA_InitStructure.DMA_Priority = DMA_Priority_Medium; //DMA通道 x拥有中优先级 
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;  //DMA通道x没有设置为内存到内存传输
	DMA_Init(DMA1_Channel7, &DMA_InitStructure);  //根据DMA_InitStruct中指定的参数初始化DMA的通道USART1_Tx_DMA_Channel所标识的寄存器
        DMA_ClearFlag(DMA1_FLAG_GL7);                                 // 清除DMA所有标志
        DMA_Cmd(DMA1_Channel7, DISABLE); // 关闭DMA
        DMA_ITConfig(DMA1_Channel7, DMA_IT_TC, ENABLE);            // 开启发送DMA通道中断
        
/**************** Rx_DMA conifg ************************/ 
        
        DMA_Cmd(DMA1_Channel6, DISABLE);   // 关DMA通道
        DMA_DeInit(DMA1_Channel6);   //将DMA的通道7寄存器重设为缺省值
        
	DMA1_MEM_LEN=BUF_SIZE;
	DMA_InitStructure.DMA_PeripheralBaseAddr =(u32)(&USART2->DR);  //DMA外设基地址
	DMA_InitStructure.DMA_MemoryBaseAddr =(u32) ReceiBuff;  //DMA内存基地址
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;  //数据传输方向，从内存读取发送到外设
	DMA_InitStructure.DMA_BufferSize = DMA1_MEM_LEN;  //DMA通道的DMA缓存的大小
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;  //外设地址寄存器不变
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;  //内存地址寄存器递增
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;  //数据宽度为8位
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte; //数据宽度为8位
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;  //工作在正常模式
	DMA_InitStructure.DMA_Priority = DMA_Priority_Medium; //DMA通道 x拥有中优先级 
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;  //DMA通道x没有设置为内存到内存传输
	DMA_Init(DMA1_Channel6, &DMA_InitStructure);  //根据DMA_InitStruct中指定的参数初始化DMA的通道USART1_Tx_DMA_Channel所标识的寄存器
        DMA_ClearFlag(DMA1_FLAG_GL6);                                 // 清除DMA所有标志
        DMA_Cmd(DMA1_Channel6, ENABLE); // 打开DMA
        DMA_ITConfig(DMA1_Channel6, DMA_IT_TC, ENABLE);            // 开启发送DMA通道中断
        
        //DMA发送中断设置  
        NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel6_IRQn;  
        NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  
        NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;  
        NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;  
        NVIC_Init(&NVIC_InitStructure); 
        
        NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel7_IRQn;  
        NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  
        NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;  
        NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;  
        NVIC_Init(&NVIC_InitStructure); 
}


/*******DMA接收中断函数*******/
void DMA1_Channel6_IRQHandler(void)
{
 
    DMA_Cmd(DMA1_Channel6, DISABLE);       // 关闭DMA ，防止干扰

    DMA_ClearFlag( DMA1_FLAG_GL6 );        // 清DMA标志位

    //temp = BUF_SIZE - DMA_GetCurrDataCounter(DMA1_Channel6); //获得接收到的字节数
    
    DMA1_Channel6->CNDTR = BUF_SIZE;        //  重新赋值计数值，必须大于等于最大可能接收到的数据帧数目

    DMA_Cmd(DMA1_Channel6, ENABLE);        // DMA 开启，等待数据。
}

/******DMA发送中断函数*******/
void DMA1_Channel7_IRQHandler(void)

{

    if(DMA_GetITStatus(DMA1_FLAG_TC7))

    {

    DMA_ClearFlag(DMA1_FLAG_GL7);         // 清除标志

    DMA_Cmd(DMA1_Channel7, DISABLE);   // 关闭DMA通道   
    }
}

/********************************* 
@brief     :    DMA发送函数，发送数据到WIFI模组
@param buf :    数据地址
@param len :    数据长度

@return    ：正确返回数据长度；错误返回 -1；
********************************/

int32_t uartWrite( uint8_t *buf, uint32_t len)

{
    int i;
    
    if(NULL==buf) return -1;
    
    for(i=0;i<len;i++)
    {
      SendBuff[i] = buf[i];
      if(i>=2&&buf[i]==0xff)
      { 
        SendBuff[i++]=0x55;
        len++;
      }      
    }
    
    DMA1_Channel7->CNDTR = len; // 设置要发送的字节数目

    DMA_Cmd(DMA1_Channel7, ENABLE);        //开始DMA发送
    printf("MCU to WIFI:");
    for(i=0;i<len;i++)
    {
      printf("%x",SendBuff[i]);
    }
    printf("\n");
    return len;
}




















