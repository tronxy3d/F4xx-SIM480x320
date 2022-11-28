/**
 * Marlin 3D Printer Firmware
 * Copyright (c) 2020 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
 *
 * Based on Sprinter and grbl.
 * Copyright (c) 2011 Camiel Gubbels / Erik van der Zalm
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */
#pragma once

// #if NOT_TARGET(__STM32F1__, __STM32F4__)
//   #error "Oops! Select an STM32F1/4 board in 'Tools > Board.'"
// #endif

/**
 * 2017 Victor Perez Marlin for stm32f1 test
 */

#define BOARD_INFO_NAME      "TronxyStm32f103"
#define DEFAULT_MACHINE_NAME "STM32F103ZET6"

#define DISABLE_JTAG

//
// EEPROM
//

#if NO_EEPROM_SELECTED
  #define EEPROM_AT24CXX
  // #define FLASH_EEPROM_EMULATION
#endif

#if ENABLED(FLASH_EEPROM_EMULATION)
  // SoC Flash (framework-arduinoststm32-maple/STM32F1/libraries/EEPROM/EEPROM.h)
  #define EEPROM_START_ADDRESS (0x8000000UL + (512 * 1024) - 2 * EEPROM_PAGE_SIZE)
  #define EEPROM_PAGE_SIZE     (0x800U)           // 2KB, but will use 2x more (4KB)
  #define MARLIN_EEPROM_SIZE    EEPROM_PAGE_SIZE
#else
  #define MARLIN_EEPROM_SIZE              0x800  // On SD, Limit to 2KB, require this amount of RAM
#endif

//
// Limit Switches
//
#define X_STOP_PIN                          PG10

#define Y_STOP_PIN                          PA12
#if !defined(Z_MIN_PROBE_USES_Z_MIN_ENDSTOP_PIN)
#define Z_MIN_PROBE_PIN                     PG9
#define Z_MIN_PIN                           PA14
#elif defined(FIX_MOUNTED_PROBE)
#define Z_STOP_PIN                          PG9
#else
#define Z_MIN_PIN                           PA14
#endif
#define Z_MAX_PIN                           PA13

//
// Steppers
//

#define X_ENABLE_PIN                        PC13
#define X_STEP_PIN                          PE5
#define X_DIR_PIN                           PE6

#define Y_ENABLE_PIN                        PE4
#define Y_STEP_PIN                          PE2
#define Y_DIR_PIN                           PE3

#define Z_ENABLE_PIN                        PE1
#define Z_STEP_PIN                          PB9
#define Z_DIR_PIN                           PE0

#define Z2_ENABLE_PIN                       PF3
#define Z2_STEP_PIN                         PF5
#define Z2_DIR_PIN                          PF1

#define E0_ENABLE_PIN                       PB8
#define E0_STEP_PIN                         PB4
#define E0_DIR_PIN                          PB5

#define E1_ENABLE_PIN                       PG8
#define E1_STEP_PIN                         PC7
#define E1_DIR_PIN                          PC6

//
// Temperature Sensors
//
#if NEED_HEAT_HEAD
  #define TEMP_0_PIN                          PA1   // TH1
#endif
#if NEED_HEAT_BED
  #define TEMP_BED_PIN                        PA0   // TB1       
#endif                

//
// Heaters
//
#if NEED_HEAT_HEAD
  #define HEATER_0_PIN                        PG12  // HEATER1
#endif
#if NEED_HEAT_BED
  #define HEATER_BED_PIN                      PG11  // HOT BED
  //#define HEATER_BED_INVERTING              true
#endif

//
// Fans
//
#define CONTROLLER_FAN_PIN                  PD6   // BOARD FAN
#define FAN_PIN                             PG13  // FAN
#define THROAT_FAN                          1
#define FAN1_PIN                            PG14
//
// Misc
//
#define BEEPER_PIN                          PB0
//#define LED_PIN                           PD3
#define PS_ON_PIN                           PD3 //暂时以LED模拟开关机
#define POWER_LOSS_PIN                      PG2 // PW_DET YSZ-COMMENT:这里接的是比较器LM393的输出,配置成上拉输入
#define POWER_LM393_PIN                     PG4 //YSZ-COMMENT:这里接的是比较器LM393的正极,必须配置成输出,高电平

#ifndef FIL_RUNOUT_PIN
  #define FIL_RUNOUT_PIN                    PA15  // MT_DET
#endif
#ifndef FIL_RUNOUT2_PIN
  #define FIL_RUNOUT2_PIN                   PF13
#endif

#define STEP_TIMER                            3
#define TEMP_TIMER                            4

#if ENABLED(LASER_FEATURE)
#define SPINDLE_LASER_ENA_PIN                 PB11 //wifi:TX
#endif
#if ENABLED(SPINDLE_LASER_USE_PWM)
#define SPINDLE_LASER_PWM_PIN                 PB10 //wifi:RX-TIM2_CH3
//这里必须复合PeripheralPins.c中的PWM pin定义const PinMap PinMap_PWM[]
//详见PWM_PIN(x)定义
#endif
#if NUM_SERVOS > 0
#define SERVO0_PIN                            PB10 //使能NUM_SERVOS>1后开放,注意,它与激光共用一个引脚,所以不能同时开启
#endif
// SPI Flash:W25QXX
// #define HAS_SPI_FLASH                     1
// #define SPI_FLASH_SIZE                    0x200000  // 2MB
// #define SPI_FLASH_CS_PIN                  PB12
// #define SPI_FLASH_MOSI_PIN                PB15 
// #define SPI_FLASH_MISO_PIN                PB14
// #define SPI_FLASH_SCK_PIN                 PB13

//
// TronXY TFT Support
//

// Shared FSMC Configs
#define TOUCH_CS_PIN                      PB7   // SPI1_NSS
#define TOUCH_SCK_PIN                     PA5   // SPI1_SCK
#define TOUCH_MISO_PIN                    PA6   // SPI1_MISO
#define TOUCH_MOSI_PIN                    PA7   // SPI1_MOSI

#define LCD_RESET_PIN                     PF11
#define LCD_BACKLIGHT_PIN                 PD13
#define TFT_RESET_PIN                     PF11
#define TFT_BACKLIGHT_PIN                 PD13

#define LCD_USE_DMA_FSMC                        // Use DMA transfers to send data to the TFT
#define FSMC_CS_PIN                       PD7
#define FSMC_RS_PIN                       PD11
#define FSMC_DMA_DEV                      DMA2
#define FSMC_DMA_CHANNEL               DMA_CH5 

#define TFT_CS_PIN                 FSMC_CS_PIN
#define TFT_RS_PIN                 FSMC_RS_PIN

// #define TFT_WIDTH                          480
// #define TFT_HEIGHT                         320
// #define TFT_PIXEL_OFFSET_X                  48
// #define TFT_PIXEL_OFFSET_Y                  32
// #define TFT_DRIVER                     ILI9488
// #define TFT_BUFFER_SIZE                  14400
  
  #define XPT2046_X_CALIBRATION           -17181
  #define XPT2046_Y_CALIBRATION            11434
  #define XPT2046_X_OFFSET                   501
  #define XPT2046_Y_OFFSET                    -9

// SPI1(PA7)=LCD & SPI3(PB5)=STUFF, are not available
// so SPI2 is required.
#define ENABLE_SPI2
#define SCK_PIN                             PB13
#define MISO_PIN                            PB14
#define MOSI_PIN                            PB15
#define SS_PIN                              PB12
//
// SD Card
//
#define SDIO_SUPPORT
#define SD_DETECT_PIN                       -1    // PF0, but it isn't connected
#define SDIO_CLOCK                       4500000
#define SDIO_READ_RETRIES                     16

#define SPEAKER //蜂鸣器无源

#define AT24CXX_SCL                         PG0
#define AT24CXX_SDA                         PG1
#define AT24CXX_WP                          PF12
