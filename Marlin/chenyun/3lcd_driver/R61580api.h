#ifndef R61580API_H
#define R61580API_H
#ifdef TFT_USE_R61580
/*******************************************************************************
* 此文件配合硬件配置文件使用
* 必须跟在RTFT_WCMD,RTFT_WDAT,RTFT_RDAT定义的后面
* 因为这三个函数或宏定义与硬件配置有关
* 作者：YSZ
* 日期：2017-05-16
*******************************************************************************/
#define						TFT_LMAX									320
#define						TFT_WMAX									240

extern unsigned short R61580_dirVar;
void R61580_Init(unsigned char dir);
void R61580_SetDir(unsigned char dir);
u16 R61580_ReadId();
void R61580_Workplace(const int& xStart,const int& yStart,const int& xEnd,const int& yEnd);
void R61580_Setpos(const int& x,const int& y);//设置屏幕画点的位置
inline void R61580_ReadPixel(const int& x,const int& y,COLORREF& R,COLORREF& G,COLORREF& B)
{
	RTFT_WCMD(0x4F);
	RTFT_WDAT(x);
	RTFT_WCMD(0x4E);
	RTFT_WDAT(y);
	RTFT_WCMD(0x22);//读取像素命令
	B=RTFT_RREG();//获取像素
	G=(B>>5)&0x3F;
	R=B>>11;
	B=(B>>3)&0x1F;
}

inline void R61580_Pixel(const int& x,const int& y,const COLORREF& color)
{
	R61580_Workplace(x,y,x,y);
	R61580_Setpos(x,y);
	RTFT_WCOLOR(color);
}

//将底层函数重命名为公有接口函数,不可直接写公有接口函数,因为一个工程可能会有很多TFT屏底层接口,如果都用公有接口,会重名,并且调用会出错
#define RTFT_INIT						R61580_Init
#define	RTFT_SETDIR					R61580_SetDir
#define	RTFT_SETPOS					R61580_Setpos
#define	RTFT_WORKPLACE			R61580_Workplace
#define	RTFT_PIXEL					R61580_Pixel
#define	RTFT_READPIXEL			R61580_ReadPixel
#define	RTFT_DIRVAR					R61580_dirVar
#define	RTFT_READID					R61580_ReadId
#endif //#ifdef TFT_USE_R61580
#endif
