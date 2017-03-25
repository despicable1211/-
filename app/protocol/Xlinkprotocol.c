//memcpy(data, rb->rbHead, copySz);
// memset((uint8_t *)&gizwitsProtocol.waitAck, 0, sizeof(protocolWaitAck_t));
#include "Xlinkprotocol.h"
u8 frameBuff[200];
u8 buffXlink[200];

 //���У��(����У��)
 u8 XORCheckS(u8 * buff,u8 *data,u8 len){
	 u8 temp=0,i;
         temp = 0;
          for(i=0;i<len;i++){
               temp ^= data[i]; 
            }
          temp^=buff[1];
          temp^=buff[2];
          temp^=buff[3];
	 return temp;
 }

 //���У�飨����У�飩
 u8 XORCheckR(u8 *data,u8 len)
 {
   	 u8 temp=0,i;
         
          for(i=1;i<len;i++){
               temp ^= data[i]; 
            }
	 return temp;
 }
//���ݷ��ͺ���
u8 sendCMD(u8 cmd,u8* data,u16 arraylen){
  u16 len;
  u8 dataCurrent,dataLast;
  u8 tmpCount = 4;
  u8 exchangCuonmt = 0;
  buffXlink[0] = 0xff;
  len = arraylen;//sizeof(data)/sizeof(data[0]);
  buffXlink[1] = 0;
  
  buffXlink[3] = cmd;
  if(len != 0)
  {
    for(int i = 0;i<len;i++)
    {
      dataCurrent = data[i];
      if(dataCurrent == 0xff)
      {
        buffXlink[tmpCount] = 0x7f;
        tmpCount++;
        buffXlink[tmpCount] = 0xfd;
        tmpCount++;
        exchangCuonmt++;
      }
      else if(dataCurrent == 0xfe)
      {
        buffXlink[tmpCount] = 0x7e;
        tmpCount++;
        buffXlink[tmpCount] = 0xfd;
        tmpCount++;
        exchangCuonmt++;
      }
      else if(dataCurrent == 0xfd)
      {
        buffXlink[tmpCount] = 0x7d;
        tmpCount++;
        buffXlink[tmpCount] = 0xfd;
        tmpCount++;
        exchangCuonmt++;
      }
      else
      {
        buffXlink[tmpCount] = dataCurrent;
        tmpCount++;
      }
    }
  }
  
  buffXlink[2] = len+2+exchangCuonmt;
  buffXlink[len+4+exchangCuonmt] = XORCheckS(buffXlink,data,len);
  buffXlink[len+5+exchangCuonmt] = 0xfe;
  
  uart1Write(buffXlink,len+6+exchangCuonmt);
  exchangCuonmt = 0;
  return 1;
}

//����֡����
u8 getOneBackpack(u8 *frameBuff)
{
 
  u8 dataCurrent,dataLast,dataXOR,frameBegin,dataLen;
  u8 tmpCount = 0,headerSign = 0,getDataLen = 0;
  u8 frameLen = 0;
  static u8 exchangCount=0;
  
  
  if(ReceiBuff1 == NULL) return -1;
  
  getDataLen =BUF_SIZE1 - DMA_GetCurrDataCounter(DMA1_Channel5); //��ý��յ����ֽ���
  if(getDataLen<5) return 1;
  
  for(int i =0;i<200;i++)
  {
    dataCurrent = ReceiBuff1[i];
    if(dataCurrent == 0xff)
    {
      headerSign = 1;
      frameBegin = i;
      frameBuff[tmpCount] = 0xff;
      tmpCount++;
    }
    else if( headerSign == 1)
    {
      //����ת��0xFF -> 0x7F 0xFD,0xFE -> 0x7E 0xFD,0xFD -> 0x7D 0xFD
      if(dataCurrent ==0xfd && dataLast == 0x7f )
      {
        tmpCount--;
        frameBuff[tmpCount] = 0xff;
        tmpCount++;
        exchangCount++;
      }
      else if(dataCurrent ==0xfd && dataLast == 0x7e )
      {
        tmpCount--;
        frameBuff[tmpCount] = 0xfe;
        tmpCount++;
        exchangCount++;
      }
      else if(dataCurrent ==0xfd && dataLast == 0x7d )
      {
        tmpCount--;
        frameBuff[tmpCount] = 0xdfd;
        tmpCount++;
        exchangCount++;
      }
      else 
      {
        frameBuff[tmpCount] = dataCurrent;
        tmpCount++;
      }
    } 
    //����У��
    if(tmpCount>4)
    {
      dataLen = frameBuff[2] + frameBuff[1]*16;
      if(dataLen+4 == tmpCount+exchangCount)
      {
        dataXOR = XORCheckR(frameBuff,dataLen+2);//-exchangCount
        u8 aa = frameBuff[dataLen+2];
        if(aa == dataXOR)
        {
          frameLen = tmpCount;
          exchangCount = 0;
          tmpCount = 0;
          return frameLen;
        }
      }
    }
    dataLast = dataCurrent;
  }
  return 0;
}

//��ѯ����״̬ ����0x01
u8 checkConnectStatus()
{
  u8 data[] = {0};
  sendCMD(linkStatus,data,0);
  return 1;
}

//��ѯPID��Key ����0x02
u8 checkIDandKey()
{
  u8 data[] = {0};
  sendCMD(checkPIDandKey,data,0);
  return 1;
}

//����WiFi��������ģʽ 0x04
u8 setWifiToConnect()
{
  u8 data[] = {0};
  sendCMD(setWIFILinkMode,data,0);
  return 1;
}


//����WIFI��ID��Key
u8 setWIFIproductIDandKey()
{ 
  u8 setData[] = {"160fa6b16fac03e9160fa6b16fac66019ea2b79431162d4dfe88f29bf87e2e3e"};
  sendCMD(setPIDandKey,setData,64);
  
  return 1;
}

//����DMA
void DMA_Resart(void)
{
  DMA_Cmd(DMA1_Channel5, DISABLE);       // �ر�DMA ����ֹ����
  memset(ReceiBuff1, 0, BUF_SIZE1);
  
  DMA1_Channel5->CNDTR = BUF_SIZE1;       //  ���¸�ֵ����ֵ��������ڵ��������ܽ��յ�������֡��Ŀ

  DMA_Cmd(DMA1_Channel5, ENABLE);        // DMA �������ȴ����ݡ�
}

//���ݴ�����
u8 dataProcess(u8 *dataPoint)
{
  u8 ret=0;
  u8 frameBuff[100];
  u8 cmd;
  u8 frameLen = 0;
  static u8 IDandKeySign = 0;
  
  int j=200;
  
  if(IDandKeySign==0)
  {
    checkIDandKey();
  }
  
  if(IDandKeySign==1)
  {
    checkConnectStatus();
  }
  
  frameLen = getOneBackpack(frameBuff);      //��dma��ȡһ�����ݰ�
  
  if(frameLen != 0)
  {
    DMA_Resart();   
    cmd = frameBuff[3];
    switch(cmd)
    {
    case WIFItoMCUDate:
      sendCMD(MCUtoWIFIDatePont,dataPoint,4);
      break;
    case WIFItoMCUDatePoint:
      
      break;
    case linkStatus://��������״̬
      if(frameBuff[4]==0 && frameBuff[5]==0)
      {
        //WiFiδ�������磬��������
        setWifiToConnect();
      }
      else if(frameBuff[4]==0x01 && frameBuff[5]==0x01)
      {
        //WiFiģ��MCU֪ͨ���ӳɹ�
        sendCMD(MCUtoWIFIDateAllPoint,dataPoint,4);
        IDandKeySign = 3;
      }
      else if(frameBuff[4]==0x01 && frameBuff[5]==0x00)
      {
        //WiFi������·����
        IDandKeySign = 2;
      }
      else if(frameBuff[4]==0x02 && frameBuff[5]==0x00)
      {
        //WiFiģ������
        IDandKeySign = 4;
      }
      break;
    case checkPIDandKey:
      if(frameBuff[4]==0)
      {
        //ID��KeyΪ�գ�����ID��Key
        setWIFIproductIDandKey();
      }
      else
      {
        IDandKeySign = 1;
      }
      break;
    default:
      break;
    }
  }
  memset(frameBuff, 0, frameLen);
  return 1;
}