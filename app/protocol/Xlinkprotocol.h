#ifndef __XLINK_H
#define __XLINK_H

#include <stm32f10x.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dma/dma1.h"

#define	HEADER	0xff;
#define TAIL    0xfe;

#define PRODUCTID      160fa6b16fac03e9160fa6b16fac6601
#define PRODUCTKEY      9ea2b79431162d4dfe88f29bf87e2e3e

typedef enum xlinkCMD{
  checkWIFOMac = 0x00,          //MCU��ѯWIFI��MAC��ַ
  linkStatus = 0x01,            //MCU��ѯWIFI����״̬��WIFI����״̬�ı�ʱ֪ͨMCU
  checkPIDandKey = 0x02,        //MCU��ѯWIFI��PID��Key
  setPIDandKey = 0x03,          //MCU����WIFI��PID��Key
  setWIFILinkMode = 0x04,       //MCU����WIFI��������ģʽ
  restartWIFI = 0x05,           //MCU����WIFI
  resetWIFI = 0x06,             //MCU����WIFIģ�飬���WiFi���ӷ����������������Ϣ��
  checkFirmwareVersion  = 0x07, //MCU��ѯWIFI�̼��汾
  getWIFITime = 0x08,           //MCU��ȡWiFi����ģ��ʱ��
  setWIFIExposeStatus = 0x09,   //MCU����WIFI������״̬
  WIFItoMCUDate = 0x80,         //WIFI��MCUת�����յ�������
  MCUtoWIFIDate = 0x81,         //MCU��WIFI��͸������
  WIFItoMCUDatePoint = 0x82,    //WIFI��MCUת�����յ������ݶ˵�����
  MCUtoWIFIDatePont = 0x83,     //MCU��WIFIת�����ݶ˵�����
  MCUtoWIFIDateAllPoint = 0x84, //MCU��WIFIת�����е����ݶ˵�����
  //0x0A-0x7F��0x85-0xFF�����
}xlinkCMD;


u8 sendCMD(u8 cmd,u8* data,u16 arraylen);
u8 getOneBackpack(u8 *frameBuff);
u8 setWIFIproductIDandKey();
u8 dataProcess(u8 *dataPoint);
#endif