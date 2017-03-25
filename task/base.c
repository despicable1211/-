#include "base.h"
#include "dma/dma1.h"
#include "usart/usart.h"
#include "protocol/Xlinkprotocol.h"

u8 frame[3]={'A','T','\n'};
u8 data[4] = {0x08,0x09,0x05,0x06};
u8 cmd = 0x00;
//u8 frameBuff[200];

u8 task_base(void){
_SS
	static bool running=TRUE;
	static u16 time_out = 0;
        int temp=0,i = 0;
	Delay_s(1);
	while(1){
		time_out ++;
//                sendCMD(cmd,data,0);
//               setWIFIproductIDandKey();
//              uart1Write(frame,3);
                dataProcess(data);
//              getOneBackpack(frameBuff);
                Delay_ms(400);
	}
_EE
}

//WiFi
u8 task_wifi(void)
{
  _SS
      while(1)
      {
        //uart1Write(SendBuff1,15);
        Delay_ms(100);
      }
  _EE
}