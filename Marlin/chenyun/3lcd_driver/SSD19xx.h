#pragma once
#if LCD_CHIP_INDEX == 2

#define WIN_LMAX                                  480 //窗口长度,必须大于等于LCD长度,大窗口可以用在小LCD上,图片尺寸必须<=窗口尺寸
#define WIN_WMAX                                  320 //窗口宽度,必须大于等于LCD宽度,大窗口可以用在小LCD上
#define	LCD_LMAX                                  WIN_LMAX
#define	LCD_WMAX                                  272
#define	LCDDIR_INVERT_RB                          0x08	//红蓝交换
#define	LCDDIR_HVCHANGE                           0x20	//第5位是1时为横屏
#define	LCDDIR_REVERSE_W                          0x40	//第6位确定宽方向
#define	LCDDIR_REVERSE_L                          0x80	//第7位确定长方向

void LCD_Init(uint8_t dir = 0x00);
void LCD_Driver_Init(uint8_t ifreset = 1, uint8_t dir = 0x00);

//不同的芯片RGB组合方式可能不一样
#define LCD_Area(xStart,yStart,xEnd,yEnd) \
	LCD_WReg(0x2A);/*x*/\
	LCD_WData((xStart)>>8);\
	LCD_WData((xStart)&0xFF);\
	LCD_WData((xEnd)>>8);\
	LCD_WData((xEnd)&0xFF);\
	LCD_WReg(0x2B);/*y*/\
	LCD_WData((yStart)>>8);\
	LCD_WData((yStart)&0xFF);\
	LCD_WData((yEnd)>>8);\
	LCD_WData((yEnd)&0xFF)

inline void LCD_WArea(int xStart,int yStart,int xEnd,int yEnd) 
{
	LCD_Area(xStart,yStart,xEnd,yEnd);
	LCD_WReg(0x2C);
}

inline void LCD_RArea(int xStart,int yStart,int xEnd,int yEnd) 
{
	LCD_Area(xStart,yStart,xEnd,yEnd);
	LCD_WReg(0x2E);
}

inline void LCD_WPixel(int x,int y,uint16_t color)
{
	LCD_WArea(x,y,x,y);
	LCD_WData(color);/*如果是8位传输,这里需要写成先写color高8位,再写低8位*/
}

#define LCD_RPixel(x,y,R,G,B) \
{ \
	LCD_RArea(x,y,x,y);\
	uint16_t temp;\
	LCD_RData(temp);/*SSD1963是一次性全部读到一个颜色*/\
	COLOR16_TO_RGB565(temp,R,G,B);\
}

#endif
