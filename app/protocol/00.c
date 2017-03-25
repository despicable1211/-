memcpy(data, rb->rbHead, copySz);
 memset((uint8_t *)&gizwitsProtocol.waitAck, 0, sizeof(protocolWaitAck_t));

 
 typedef struct{
	 uint8		dataArry[20];
 }dataXlink;//数据结构体
 
 typedef struct{
    uint8       len;
    uint8       cmd;
    dataXlink    data;     
 }XOR_typ;//需要校验数据结构体
 
 typedef struct{
   uint8	header;
   XOR_typ      XORdata;
   uint8        XOR;
   uint8	tail;	 
 }protocol;     //数据帧结构体
 
#define	HEADER	0xFF;//命令头
#define TAIL    0xFE;//命令尾
 //异或校验
 uint8 XORCheck(uint8 * data){
	 uint8 datalen,temp;
	 uint8 * tm;
	 datalen = sizeof(dataLen_typ);
	 tm = data;
	 temp = tm[1]^tm[0];
	 for(i=2;i<datalen;i++){
		 temp ^= tm[i]; 
	 }
	 return temp;
 }

int sendCMD(uint8 cmd,uint8 * data){
        XOR_typ->len = sizeof(data) + 3;
        XOR_typ->cmd = cmd;
        mencpy(XORdata.data,data,sizeof(data));
        temp = XORcheck(XOR_typ);
	memset((uint8 *)&protocol.header, HEADER, 1);
        menset((uint8 *)&protocol.XOR,temp,1);
        menset((uint8 *)&protocol.tail,TAIL);
        protocolLen = sizeof(protocol);
	if(uartWrite(protocol,protocolLen)<0) printf("数据为空");
}