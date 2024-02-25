#pragma once
#if LCD_CHIP_INDEX == 1

#if TRONXY_UI == UI_SIM320X480
#define WIN_LMAX                                  320 //窗口长度,必须大于等于LCD长度,大窗口可以用在小LCD上,图片尺寸必须<=窗口尺寸
#define WIN_WMAX                                  480 //窗口宽度,必须大于等于LCD宽度,大窗口可以用在小LCD上
#define	LCD_LMAX                                  WIN_LMAX
#define	LCD_WMAX                                  WIN_WMAX
#else
#define WIN_LMAX                                  480 //窗口长度,必须大于等于LCD长度,大窗口可以用在小LCD上,图片尺寸必须<=窗口尺寸
#define WIN_WMAX                                  320 //窗口宽度,必须大于等于LCD宽度,大窗口可以用在小LCD上
#define	LCD_LMAX                                  WIN_LMAX
#define	LCD_WMAX                                  WIN_WMAX
#endif
#define	LCDDIR_INVERT_RB                          0x08	//红蓝交换
#define	LCDDIR_HVCHANGE                           0x20	//第5位是1时为横屏
#define	LCDDIR_REVERSE_W                          0x40	//第6位确定宽方向
#define	LCDDIR_REVERSE_L                          0x80	//第7位确定长方向

void LCD_Init(unsigned char dir = LCDDIR_HVCHANGE | LCDDIR_INVERT_RB | LCDDIR_REVERSE_W | LCDDIR_REVERSE_L);
void LCD_Driver_Init(unsigned char dir = LCDDIR_HVCHANGE | LCDDIR_INVERT_RB | LCDDIR_REVERSE_W | LCDDIR_REVERSE_L);
void LCD_SetDir(unsigned char dir);

//不同的芯片RGB组合方式可能不一样
#define LCD_Area(xStart,yStart,xEnd,yEnd) \
	LCD_WReg(0x2A);/*x*/\
	LCD_WData((xStart) >> 8);\
	LCD_WData((xStart) & 0xFF);\
	LCD_WData((xEnd) >> 8);\
	LCD_WData((xEnd) & 0xFF);\
	LCD_WReg(0x2B);/*y*/\
	LCD_WData((yStart) >> 8);\
	LCD_WData((yStart) & 0xFF);\
	LCD_WData((yEnd) >> 8);\
	LCD_WData((yEnd) & 0xFF)

inline void LCD_WArea(int xStart,int yStart,int xEnd,int yEnd) {
	LCD_Area(xStart,yStart,xEnd,yEnd);
	LCD_WReg(0x2C);
}

inline void LCD_WPixel(int x,int y,uint16_t color) {
	LCD_Area(x,y,x,y);
	LCD_WReg(0x2C);
	LCD_WData(color);
}

#define LCD_RPixel(x,y,R,G,B) \
	do{ LCD_Area(x,y,x,y);\
	LCD_WReg(0x2E);\
	LCD_RData(B);/*dummy*/\
	LCD_RData(R);/*RG*/ G = R & 0x00FF; G >>= 2; R >>= 11;\
	LCD_RData(B);/*B*/ B >>= 11;}while(0)

#endif