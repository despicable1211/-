#include "lin.h"
#include <string.h>
#include "usart/usart.h"
//#include "dma/dma.h"
#include "dma/dma1.h"


void main(void)
{
    
    CLK_Init_lin();
    Task_Init_lin();  
    
    uartxInit();        
    //dma_init();
    //timerInit();
    dma1_init();
    //gizwitsSetMode(WIFI_AIRLINK_MODE);
    printf("MCU Init Success \n");
    
    runTask();

}