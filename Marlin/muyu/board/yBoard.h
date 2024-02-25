#pragma once

#include "src/inc/MarlinConfig.h"
#if TRONXY_UI

#define LCD_USE_TOUCH
#include "src/HAL/STM32/tft/xpt2046.h"

#ifdef STM32F4xx
#include "stm32f446zet/stm32_flash.hpp"
#else
#include "stm32f103zet/stm32_flash.hpp"
#endif
#include "2periphery/yAt24cxx.hpp"

void BoardInit(void);
extern uint16_t LCD_TOTAL_BUFF[];

#define TEXT_FONT_XPIXEL  8
#define TEXT_FONT_YPIXEL  16

#endif
#define	POS_BOOTINFO        0x0800C000 //扇区:C000-10000:16KB
#define	POS_FIRMWARENAME    0x0800C008
#define POS_VERSION         0x0800C200
#define POS_INTERRUPT       0x0800C500
#define BOOT_INFO_SIZE      1060
#define INTERRUPT_SIGN      0xA5A5

