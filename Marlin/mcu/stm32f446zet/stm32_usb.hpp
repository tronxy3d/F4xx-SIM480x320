#pragma once
#if USBHOST_HS_EN && defined(STM32F4xx)

#include "STM32_USB_HOST_Library/Class/MSC/inc/usbh_msc.h"

extern USBH_HandleTypeDef hUSBHost;
extern  uint8_t USBH_USR_ApplicationState ;

#endif // define STM32F4xx

void USBH_Init(void);
void USBH_Process(void);
bool USBH_UDISK_Status(void);
bool USBH_UDISK_Read(uint8_t* buf,uint32_t sector,uint32_t cnt);
bool USBH_UDISK_Write(const uint8_t* buf,uint32_t sector,uint32_t cnt);
