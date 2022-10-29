#pragma once

#ifdef STM32F1xx
#include "variant.h"
#include "stm32f1xx_hal.h"
// #include "stm32f103xe.h"

#define T_DMA(x)                    (((uint32_t)x > (uint32_t)DMA1_Channel7) ? DMA2 : DMA1)

typedef struct {
  __IO uint16_t REG;
  __IO uint16_t RAM;
  } FMC_LCD_TypeDef;
extern  FMC_LCD_TypeDef *mLCD;
extern uint8_t _lcd_writing;

void myDelayMs(uint32_t n);
void myDelayUs(uint32_t n);
typedef struct
{
  uint8_t memToMem;
  uint8_t fromMem;
  uint8_t memInc;
  uint8_t perInc;
  uint32_t mem;
  uint32_t per;
  uint32_t len;
}DMA_START_St;
void yDmaInit(DMA_Channel_TypeDef* dma,int memDataBit,int perDataBit);
void yDmaStart(DMA_Channel_TypeDef* pdma, DMA_START_St* st); //dir 0:mem->per 1:per->mem 2:mem->mem
uint32_t yDmaSignIndex(DMA_Channel_TypeDef* dma);

int LCD_McuInit(uint8_t background_on = 0);
void LCD_McuDeinit(void);
void LCD_Reset(void);
#define LCD_WReg(v)      mLCD->REG = (v);__DSB()
#define LCD_WData(v)     mLCD->RAM = (v);__DSB()
#define LCD_RData(v)     v = mLCD->RAM;__DSB()
#define BACKGROUND_LIGHT_ON()  GPIOD->BSRR = 1UL << 13
#define BACKGROUND_LIGHT_OFF() GPIOD->BSRR = (1UL << 13) << 16

#define LCD_DMA_TAR                 DMA2_Channel1
#define LCD_DMA_TC_FLAG             DMA_FLAG_TC1 //传输完成标志
#define LCD_DMA_TE_FLAG             DMA_FLAG_TE1 //传输错误标志
uint8_t LCD_Busy(void);

inline void LCD_BatchStart(const uint16_t* colors,uint32_t num,uint8_t autoInc) {
  DMA_START_St st = {
    1,//memToMem
    1,//fromMem
    autoInc,//memInc
    0,//perInc
    (uint32_t)colors,//mem
    (uint32_t)&mLCD->RAM,//per
    num,//len
  };
  yDmaStart(LCD_DMA_TAR,&st);
  _lcd_writing = 1;
}

#define LCD_BatchMaxNum            65520
void  LCD_BatchSyn(const uint16_t* colors,int len,uint8_t autoInc);

void w25q_spi_init(void);
inline void w25q_spi_cs_high() {GPIOB->BSRR = 1UL << 12;} //CS:PB12拉高
inline void w25q_spi_cs_low() {GPIOB->BRR = 1UL << 12;} //CS:PB12拉低
uint8_t w25q_spi_send_receive(const uint8_t *sendDt, bool sendInc,uint8_t *rcvDt,bool rcvInc,int len);
#define W25Q_DMA_RX              DMA1_Channel4
#define W25Q_DMA_TX              DMA1_Channel5
#define W25Q_RC_FLAG             DMA_FLAG_TC4
#define W25Q_RE_FLAG             DMA_FLAG_TE4
#define W25Q_SPI                 SPI2

void w25q_spi_dma(const uint8_t*sendBuff, uint8_t* recvBuff, uint32_t len);
#ifdef W25Q_DMA_RX
void w25q_spi_dma_stop(uint32_t period = 200);
uint8_t w25q_spi_dma_ok(void);
#else
inline void w25q_spi_dma_stop(uint32_t period = 200){(void)period;}
inline uint8_t w25q_spi_dma_ok(void){return 1;}
#endif

inline void at24_iic_cs_high() {
  GPIOF->BSRR = 1UL << 12; //AT24CXX_WP:PF12=1
}
inline void at24_iic_cs_low() {
  GPIOF->BRR = 1UL << 12; //AT24CXX_WP:PF12=0
}
#endif
