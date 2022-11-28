#ifndef LGDP4535_API_H
#define LGDP4535_API_H
#ifdef TFT_USE_LGDP4535
/*******************************************************************************
* 此文件配合硬件配置文件使用
* 必须跟在RTFT_WCMD,RTFT_WDAT,RTFT_RDAT定义的后面
* 因为这三个函数或宏定义与硬件配置有关
* 作者：YSZ
* 日期：2017-05-16
*******************************************************************************/
#define						TFT_LMAX									320
#define						TFT_WMAX									240

extern unsigned short LGDP4535_dirVar;
void LGDP4535_Init(unsigned char dir);
void LGDP4535_SetDir(unsigned char dir);

inline u16 LGD4535_readId()
{
	u16 ret=0;
	TFT_DAT(0xFFFF);
	TFT_RS_LOW;
	TFT_CS_LOW;
	TFT_RD_LOW;
	DELAY(10);
	ret=TFT_DAT_VAL;
	TFT_RD_HIGH;
	TFT_CS_HIGH;
	return ret;
}
void LGDP4535_Setpos(const int& x,const int& y);//设置屏幕画点的位置	
void LGDP4535_Workplace(const int& xStart,const int& yStart,const int& xEnd,const int& yEnd);
inline void LGDP4535_ReadPixel(const int& x,const int& y,COLORREF& R,COLORREF& G,COLORREF& B)
{ 
	LGDP4535_Setpos(x,y);
	TFT_DAT_INPUT;
	TFT_RS_HIGH;
	TFT_CS_LOW;
	TFT_RD_LOW;//读取GRAM时,第一次是假读
	do;while(0);
	TFT_RD_HIGH;
	do;while(0);
	TFT_RD_LOW;
	do;while(0);
	R=TFT_DAT_VAL;
	TFT_RD_HIGH;
	TFT_CS_HIGH;
	TFT_DAT_OUTPUT;
	G=(R&0x07E0)>>3;
	B=(R&0x001F)<<3;
	R=(R&0xF800)>>8;
}

inline void LGDP4535_Pixel(const int& x,const int& y,const COLORREF& color)
{
	LGDP4535_Setpos(x,y);
	RTFT_WDAT(color);
}

//将底层函数重命名为公有接口函数,不可直接写公有接口函数,因为一个工程可能会有很多TFT屏底层接口,如果都用公有接口,会重名,并且调用会出错
#define RTFT_INIT						LGDP4535_Init
#define	RTFT_SETDIR					LGDP4535_SetDir
#define	RTFT_SETPOS					LGDP4535_Setpos
#define	RTFT_WORKPLACE			LGDP4535_Workplace
#define	RTFT_PIXEL					LGDP4535_Pixel
#define	RTFT_READPIXEL			LGDP4535_ReadPixel
#define	RTFT_DIRVAR					LGDP4535_dirVar
#endif //#ifdef TFT_USE_ILI9486

#endif
