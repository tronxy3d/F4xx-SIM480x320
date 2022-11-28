#pragma once

#define	LCD_LMAX                                  480
#define	LCD_WMAX                                  272
#define	LCDDIR_HVCHANGE                           0x20	//第5位是1时为横屏
#define	LCDDIR_REVERSE_W                          0x40	//第6位确定宽方向
#define	LCDDIR_REVERSE_L                          0x80	//第7位确定长方向

void NT35510_Init(unsigned char dir = 0x00);

#define NT35510_WStart() LCD_WReg(0x2C00) //开始写
#define NT35510_RStart() LCD_WReg(0x2E00) //开始读

inline void LCD_WArea(int xStart,int yStart,int xEnd,int yEnd) 
{
	int w = xEnd - xStart + 1;
	LCD_WReg(0x2A00);/*x*/
	LCD_WData(xStart >> 8);
	LCD_WReg(0x2A01);
	LCD_WData(xStart & 0xFF);
	LCD_WReg(0x2A02);
	LCD_WData(w >> 8);
	LCD_WReg(0x2A03);
	LCD_WData(w & 0xFF);

	int h = yEnd - yStart + 1;
	LCD_WReg(0x2B00);/*y*/
	LCD_WData(yStart >> 8);
	LCD_WReg(0x2B01);
	LCD_WData(yStart & 0xFF);
	LCD_WReg(0x2B02);
	LCD_WData(h >> 8);
	LCD_WReg(0x2B03);
	LCD_WData(h & 0xFF);
	NT35510_WStart();
}

inline void LCD_RArea(int xStart,int yStart,int xEnd,int yEnd) 
{
	int w = xEnd - xStart + 1;
	LCD_WReg(0x2A00);/*x*/
	LCD_WData(xStart >> 8);
	LCD_WReg(0x2A01);
	LCD_WData(xStart & 0xFF);
	LCD_WReg(0x2A02);
	LCD_WData(w >> 8);
	LCD_WReg(0x2A03);
	LCD_WData(w & 0xFF);

	int h = yEnd - yStart + 1;
	LCD_WReg(0x2B00);/*y*/
	LCD_WData(yStart >> 8);
	LCD_WReg(0x2B01);
	LCD_WData(yStart & 0xFF);
	LCD_WReg(0x2B02);
	LCD_WData(h >> 8);
	LCD_WReg(0x2B03);
	LCD_WData(h & 0xFF);

	NT35510_RStart();
}

inline void LCD_WPixel(int x,int y,uint16_t color)
{
	LCD_WReg(0x2A00);/*x*/
	LCD_WData(x >> 8);
	LCD_WReg(0x2A01);
	LCD_WData(x & 0xFF);
	LCD_WReg(0x2B00);/*y*/
	LCD_WData(y >> 8);
	LCD_WReg(0x2B01);
	LCD_WData(y & 0xFF);
	NT35510_WStart();
	LCD_WData(color);/*如果是8位传输,这里需要写成先写color高8位,再写低8位*/
}

#define LCD_RPixel(x,y,R,G,B) \
{ \
	LCD_WReg(0x2A00);/*x*/\
	LCD_WData(x >> 8);\
	LCD_WReg(0x2A01);\
	LCD_WData(x & 0xFF);\
	LCD_WReg(0x2B00);/*y*/\
	LCD_WData(y >> 8);\
	LCD_WReg(0x2B01);\
	LCD_WData(y & 0xFF);\
	NT35510_RStart();\
	uint16_t temp;\
	LCD_RData(temp);/*第一次假读dummy*/\
	LCD_RData(temp);/*读rg值,r在前8位,g在后8位*/\
	R = (temp >> 8);\
	G = temp & 0xFF;\
	LCD_RData(B);\
}

#define LCD_Init       NT35510_Init