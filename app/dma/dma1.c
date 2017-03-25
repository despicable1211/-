
#include "dma1.h"

void Uart1_DMA_Rx(void);
void Uart1_DAM_Tx(void);
void Uart1_Start_DMA_Tx(uint32_t size);


u8 ReceiBuff1[BUF_SIZE1];  //数据缓冲区
u8 SendBuff1[BUF_SIZE1];  //数据缓冲区



 	    

//DMA初始化

void dma1_init(void)
{
        u16 DMA1_MEM_LEN;                                       //保存DMA每次数据传送的长度
        DMA_InitTypeDef DMA_InitStructure;
        NVIC_InitTypeDef NVIC_InitStructure;

        RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);	//使能DMA传输

        
/**************** Tx_DMA conifg ************************/
        
        DMA_Cmd(DMA1_Channel4, DISABLE);   // 关DMA通道
        DMA_DeInit(DMA1_Channel4);   //将DMA的通道7寄存器重设为缺省值
        
	DMA1_MEM_LEN=BUF_SIZE1;
	DMA_InitStructure.DMA_PeripheralBaseAddr =(u32)(&USART1->DR);  //DMA外设基地址
	DMA_InitStructure.DMA_MemoryBaseAddr =(u32) SendBuff1;  //DMA内存基地址
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;  //数据传输方向，从内存读取发送到外设
	DMA_InitStructure.DMA_BufferSize = DMA1_MEM_LEN;  //DMA通道的DMA缓存的大小
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;  //外设地址寄存器不变
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;  //内存地址寄存器递增
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;  //数据宽度为8位
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte; //数据宽度为8位
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;  //工作在正常模式
	DMA_InitStructure.DMA_Priority = DMA_Priority_Medium; //DMA通道 x拥有中优先级 
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;  //DMA通道x没有设置为内存到内存传输
	DMA_Init(DMA1_Channel4, &DMA_InitStructure);  //根据DMA_InitStruct中指定的参数初始化DMA的通道USART1_Tx_DMA_Channel所标识的寄存器
        DMA_ClearFlag(DMA1_FLAG_GL4);                                 // 清除DMA所有标志
        DMA_Cmd(DMA1_Channel4, DISABLE); // 关闭DMA
        DMA_ITConfig(DMA1_Channel4, DMA_IT_TC, ENABLE);            // 开启发送DMA通道中断
        
/**************** Rx_DMA conifg ************************/ 
        
        DMA_Cmd(DMA1_Channel5, DISABLE);   // 关DMA通道
        DMA_DeInit(DMA1_Channel5);   //将DMA的通道7寄存器重设为缺省值
        
	DMA1_MEM_LEN=BUF_SIZE1;
	DMA_InitStructure.DMA_PeripheralBaseAddr =(u32)(&USART1->DR);  //DMA外设基地址
	DMA_InitStructure.DMA_MemoryBaseAddr =(u32) ReceiBuff1;  //DMA内存基地址
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;  //数据传输方向，从内存读取发送到外设
	DMA_InitStructure.DMA_BufferSize = DMA1_MEM_LEN;  //DMA通道的DMA缓存的大小
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;  //外设地址寄存器不变
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;  //内存地址寄存器递增
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;  //数据宽度为8位
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte; //数据宽度为8位
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;  //工作在正常模式
	DMA_InitStructure.DMA_Priority = DMA_Priority_Medium; //DMA通道 x拥有中优先级 
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;  //DMA通道x没有设置为内存到内存传输
	DMA_Init(DMA1_Channel5, &DMA_InitStructure);  //根据DMA_InitStruct中指定的参数初始化DMA的通道USART1_Tx_DMA_Channel所标识的寄存器
        DMA_ClearFlag(DMA1_FLAG_GL5);                                 // 清除DMA所有标志
        DMA_Cmd(DMA1_Channel5, ENABLE); // 打开DMA
        DMA_ITConfig(DMA1_Channel5, DMA_IT_TC, ENABLE);            // 开启发送DMA通道中断
        
        //DMA发送中断设置  
        NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel4_IRQn;  
        NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  
        NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;  
        NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;  
        NVIC_Init(&NVIC_InitStructure);   
        NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel5_IRQn;  
        NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  
        NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;  
        NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;  
        NVIC_Init(&NVIC_InitStructure);      

}


/*******DMA接收中断函数*******/
void DMA1_Channel5_IRQHandler(void)
{
    int temp = 0;  
    DMA_Cmd(DMA1_Channel5, DISABLE);       // 关闭DMA ，防止干扰

    DMA_ClearFlag( DMA1_FLAG_GL5 );        // 清DMA标志位

    temp = BUF_SIZE1 - DMA_GetCurrDataCounter(DMA1_Channel5); //获得接收到的字节数

    DMA1_Channel5->CNDTR = BUF_SIZE1;        //  重新赋值计数值，必须大于等于最大可能接收到的数据帧数目

    DMA_Cmd(DMA1_Channel5, ENABLE);        // DMA 开启，等待数据。
}
/******DMA发送中断函数*******/
void DMA1_Channel4_IRQHandler(void)

{

    if(DMA_GetITStatus(DMA1_FLAG_TC4))

    {

        Uart1_DAM_Tx();

    }

}

void Uart1_DAM_Tx(void)

{

    DMA_ClearFlag(DMA1_FLAG_GL4);         // 清除标志

    DMA_Cmd(DMA1_Channel4, DISABLE);   // 关闭DMA通道
}

/********************************* 
@brief     :    DMA发送函数，发送数据到WIFI模组
@param buf :    数据地址
@param len :    数据长度

@return    ：正确返回数据长度；错误返回 -1；
********************************/

int uart1Write( uint8_t *buf, uint32_t len)

{
    int i;
    
    if(NULL==buf) return -1;
        
    for(i=0;i<len;i++)
    {
      SendBuff1[i] = buf[i];
     
    }
        
    Uart1_Start_DMA_Tx( len );
    
    return len;
}

 

void Uart1_Start_DMA_Tx(uint32_t size)

{

    DMA1_Channel4->CNDTR = (uint32_t)size; // 设置要发送的字节数目 
    DMA_Cmd(DMA1_Channel4, ENABLE);        //开始DMA发送

}





















