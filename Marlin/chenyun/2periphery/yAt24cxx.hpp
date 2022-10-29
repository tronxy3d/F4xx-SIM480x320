#pragma once

#include "yCommon.h"
//底层需要提供以下接口
extern void (*at24iicInit)(void);
extern void (*at24iicStart)(void);
extern void (*at24iicStop)(void);
extern uint8_t (*at24iicWaitAck)(void);
extern void (*at24iicSendAck)(void);
extern void (*at24iicSendNAck)(void);
extern void (*at24iicSendByte)(uint8_t data);
extern uint8_t (*at24iicReadByte)(uint8_t ack);
extern void (*at24Cs_High)(void);
extern void (*at24Cs_Low)(void);
extern void (*at24_delay_us)(uint32_t n);

#define AT24CXX_Init() at24iicInit()
void AT24CXX_Write(int& WriteAddr,const void *buffer,int len);
void AT24CXX_Read(int& ReadAddr,void *buffer,int len, const uint8_t writing = 1);
void AT24CXX_WriteOneByte(uint16_t WriteAddr,uint8_t Data);
uint8_t AT24CXX_ReadOneByte(uint16_t ReadAddr);
