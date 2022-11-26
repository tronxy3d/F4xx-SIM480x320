#pragma once

#include "yCommon.h"
//底层需要提供以下接口
void at24iicInit(void);
void at24iicStart(void);
void at24iicStop(void);
uint8_t at24iicWaitAck(void);
void at24iicSendAck(void);
void at24iicSendNAck(void);
void at24iicSendByte(uint8_t data);
uint8_t at24iicReadByte(uint8_t ack);

#define AT24CXX_Init() at24iicInit()
#define at24_delay_us(x) myDelayUs(x)
void AT24CXX_Write(int& WriteAddr,const void *buffer,int len);
void AT24CXX_Read(int& ReadAddr,void *buffer,int len, const uint8_t writing = 1);
void AT24CXX_WriteOneByte(uint16_t WriteAddr,uint8_t Data);
uint8_t AT24CXX_ReadOneByte(uint16_t ReadAddr);
