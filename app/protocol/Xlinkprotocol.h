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
  checkWIFOMac = 0x00,          //MCU查询WIFI的MAC地址
  linkStatus = 0x01,            //MCU查询WIFI连接状态或WIFI连接状态改变时通知MCU
  checkPIDandKey = 0x02,        //MCU查询WIFI的PID和Key
  setPIDandKey = 0x03,          //MCU设置WIFI的PID和Key
  setWIFILinkMode = 0x04,       //MCU设置WIFI进入配网模式
  restartWIFI = 0x05,           //MCU重启WIFI
  resetWIFI = 0x06,             //MCU重置WIFI模组，清楚WiFi连接服务器保存的所有信息】
  checkFirmwareVersion  = 0x07, //MCU查询WIFI固件版本
  getWIFITime = 0x08,           //MCU获取WiFi本地模糊时间
  setWIFIExposeStatus = 0x09,   //MCU设置WIFI被发现状态
  WIFItoMCUDate = 0x80,         //WIFI向MCU转发接收到的数据
  MCUtoWIFIDate = 0x81,         //MCU向WIFI发透传数据
  WIFItoMCUDatePoint = 0x82,    //WIFI向MCU转发接收到的数据端点数据
  MCUtoWIFIDatePont = 0x83,     //MCU向WIFI转发数据端点数据
  MCUtoWIFIDateAllPoint = 0x84, //MCU向WIFI转发所有的数据端点数据
  //0x0A-0x7F和0x85-0xFF命令保留
}xlinkCMD;


u8 sendCMD(u8 cmd,u8* data,u16 arraylen);
u8 getOneBackpack(u8 *frameBuff);
u8 setWIFIproductIDandKey();
u8 dataProcess(u8 *dataPoint);
#endif