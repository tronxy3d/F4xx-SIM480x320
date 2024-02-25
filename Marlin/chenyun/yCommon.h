#pragma once

#include <inttypes.h>
#include "yType.hpp"
#ifdef STM32F4xx
#include "stm32f446zet/stm32.hpp"
#else
#include "stm32f103zet/stm32.hpp"
#endif
#if LCD_CHIP_INDEX == 1
#include "3lcd_driver/ILI94xx.h"
#elif LCD_CHIP_INDEX == 2
#include "3lcd_driver/SSD19xx.h"
#elif LCD_CHIP_INDEX == 3
#include "3lcd_driver/NT35510.h"
#elif LCD_CHIP_INDEX == 4
#include "3lcd_driver/ST7789.h"
#else
#error You must define a lcd.
#endif

/*-->驱动程序需要提供:
LCD_WArea(int xStart,int yStart,int xEnd,int yEnd);//1.屏区域写框定
LCD_RArea(int xStart,int yStart,int xEnd,int yEnd);//2.屏区域读框定
LCD_BatchStart(const color_t* colors,int num,uint8_t autoInc);//4.批量写颜色,执行1,2后可以执行本接口
LCD_Busy();//5.批量写完成判断
LCD_BatchSyn(const uint16_t*colors,int len,uint8_t autoInc);//6.批量写,并等待完成
LCD_WPixel(int x,int y,color_t color);//7.在坐标x,y处写颜色
LCD_RPixel(int x,int y,color_t& R,color_t& G,color_t& B);//8.在坐标x,y处读取颜色并保存到r,g,b分量内
LCD_Read_RGB_Start(int xStart,int yStart,int xEnd,int yEnd);//9.批量读取颜色开始
LCD_Read_RGB(color_t& R,color_t& G,color_t& B);//10.一次读取一个RGB出来,接上面的批量读RGB用
*/
extern color_t *LCD_LBuffer1,*LCD_LBuffer2;//9.屏幕一行像素的一级(准备数据)和二级(显示数据)缓存空间,两者就当被分配到连续的两段空间,buffer1在前
//10.需要对VisualRect进行赋值指定屏的长,宽
extern uint8_t compress_buff_per_line[];//11.一行解压之前的数据空间(最大值)
extern uint16_t compress_len_per_line[];//12.每一行的长度
extern uint8_t (*touchChipPos)(int& x,int& y);//13.获取触摸点,当触摸了返回true
extern uint32_t (*nowMs)(void);//14.当前时间,单位:毫秒
extern const PicAttr *defaultUFont;//15.默认unicode字库,对uw_start_addr进行赋值,指定语言在unicode的起始位置
extern void (*yWatchdog)(void);//16.有的情况下(比如:显示压缩全图时),可能时间较长,需要提供看门狗重置函数

extern uint32_t (*EROM_Init)(void); //17.外部EROM初始化,注意:这里的EROM被用来读取LCD图片信息
extern void (*EROM_ReadStart)(uint32_t addr,void* buff,int len, uint32_t lastreadWait);
extern uint8_t (*EROM_ReadOk)(void);
extern void (*EROM_ReadStop)(uint32_t period);
extern uint8_t (*EROM_SWrite)(uint32_t& addr,uint32_t& nextEraseAddr,const void* data,int len);
extern uint8_t (*EROM_VWrite)(uint32_t addr,const void* data,int len);
extern uint8_t (*EROM_Write)(uint32_t addr,const void* buff,int len,void *exchangeBuff);

#define INFO_STR(x)

