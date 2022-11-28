
#pragma once
#include "../yCommon.h"

#define WIDGET_FRAME_COLOR               0xEE0E
#define HORIZONTAL_LINE(y,xStart,xEnd)  LCD_WArea(xStart,y,xEnd,y);LCD_BatchStart(LCD_LBuffer2,xEnd - xStart + 1,0)
#define VERTICAL_LINE(x,yStart,yEnd)    LCD_WArea(x,yStart,x,yEnd);LCD_BatchStart(LCD_LBuffer2,yEnd - yStart + 1,0)

enum TouchEvent
{
	tevt_none = 0,
	tevt_touch,
	tevt_untouch,
	tevt_away,
};
class yWidget
{
	public:
		yWidget(int xStart = 0,int yStart = 0,int width = 0,int height = 0,const ScaleAttr* idle_attr = nullptr,const ScaleAttr* focus_attr = nullptr);
		virtual ~yWidget(){}

	protected:
		uint8_t focus;
		uint8_t focusAllUpdate;//默认为1
		//置0后,调用setfocus时,只更新widget,不更新继承部件,主要针对按下控件加透明色的控件
		//抬起时,会更新全部
		const ScaleAttr* scaAttrIdle,*scaAttrFocus,*scaAttr;
		int wXStart,wYStart,wXEnd,wYEnd;//本控件范围

	public:
		union {
			struct {
				int scale:1;
				int simulation:1;
				int picture:1;//第一次不显示,一般用在需要第一次刷背景,第二次显示文本的情况
				int text:1;
				int other:4;
			}content;//这里标记update绘制哪些部分,见宏定义
			uint8_t all;
		}sign;
		uint8_t colorVertical;
		uint8_t touchChoose;//0:不响应触摸,1一旦触摸,无论是否触到本控件,都必然响应,2,只有触摸到本控件才响应
		uint8_t funParam;
		static WRECT VisualRect;//可见区域
		virtual uint8_t update(uint8_t force = 0);//刷新界面,返回true表示该控件可视区域无显示
		inline virtual void show(uint8_t force = 0) {
			update(force);
			sign.content.scale = 0;
		}
		void (*fun)(yWidget*w,TouchEvent evt);//发生触控事件后,会立即调用本函数
		uint8_t (*funNext)();//发生触控后,调用fun后,在外面调用本函数,可能会释放本控件
		inline virtual void setfocus(uint8_t tf) {
			if(tf && !focus) {
				focus = 1;
				scaAttr = scaAttrFocus;
				sign.content.scale = 1;
			}
			else if(!tf && focus) {
				focus = 0;
				scaAttr = scaAttrIdle;
				sign.content.scale = 1;
			}
		}
		inline void disableFocusAllUpdate(bool en){if(en)focusAllUpdate = 0;else focusAllUpdate = 1;}
		inline virtual uint8_t enUpdate(void) { return !!scaAttr && sign.content.scale == 0; }
		void setRectOffset(int x,int y);
		//求wgRect与VisualRect求交集
		inline uint8_t boundIntersect(int& xStart,int& yStart,int& xEnd,int& yEnd)
		{
			xStart = yMAX(wXStart, VisualRect.xStart);
			xEnd = yMIN(wXEnd, VisualRect.xEnd);
			yStart = yMAX(wYStart, VisualRect.yStart);
			yEnd = yMIN(wYEnd, VisualRect.yEnd);
			return (xEnd < xStart || yStart > yEnd);
		}
		inline uint8_t range(int x,int y,int r = 0){
			return (x >= wXStart + r && x <= wXEnd - r) && (y >= wYStart + r && y <= wYEnd - r);
		}

	protected:
		inline void horizontalLine(color_t color,int xStart,int xEnd,int y)
			{//在屏幕上绘制一条横线
				if(y < wYStart || y < VisualRect.yStart || y > wYEnd || y > VisualRect.yEnd)return;
				if(xStart < wXStart)xStart = wXStart;
				if(xStart < VisualRect.xStart)xStart = VisualRect.xStart;
				if(xEnd > wXEnd)xEnd = wXEnd;
				if(xEnd > VisualRect.xEnd)xEnd = VisualRect.xEnd;
				if(xStart > xEnd)return;
				while(LCD_Busy()){}
				LCD_LBuffer2[0] = color;//必须使用全局变量保存颜色,否则函数返回后,color释放掉了,DMA在传输的这个颜色就不准了
				HORIZONTAL_LINE(y,xStart,xEnd);
			}
		inline void verticalLine(color_t color,int x,int yStart,int yEnd)
			{//在屏幕上绘制一条竖线
				if(x < VisualRect.xStart || x < wXStart || x > VisualRect.xEnd || x > wXEnd)return;
				if(yStart < wYStart)yStart = wYStart;
				if(yStart < VisualRect.yStart)yStart = VisualRect.yStart;
				if(yEnd > wYEnd)yEnd = wYEnd;
				if(yEnd > VisualRect.yEnd)yEnd = VisualRect.yEnd;
				if(yStart > yEnd)return;
				while(LCD_Busy()){}
				LCD_LBuffer2[0] = color;//必须使用全局变量保存颜色,否则函数返回后,color释放掉了,DMA在传输的这个颜色就不准了
				VERTICAL_LINE(x,yStart,yEnd);
			}
		inline void frame(color_t color,int xStart,int yStart,int xEnd,int yEnd) {
			verticalLine(color,xStart,yStart,yEnd);
			verticalLine(color,xEnd,yStart,yEnd);
			horizontalLine(color,xStart,xEnd,yStart);
			horizontalLine(color,xStart,xEnd,yEnd);
		}
		void rect(color_t color,int xStart,int yStart,int xEnd,int yEnd);
		void horizonRect(color_t color_start,color_t color_end);
		void verticalRect(color_t color_start,color_t color_end);
		void line(color_t color,int xStart,int yStart,int xEnd,int yEnd);//画线

	protected:
		//将x,y围与VisualRect求交集
		static inline uint8_t boundIntersect2(int& xStart,int& yStart,int& xEnd,int& yEnd)
		{
			if(xStart < VisualRect.xStart)xStart = VisualRect.xStart;
			if(xEnd > VisualRect.xEnd)xEnd = VisualRect.xEnd;
			if(yStart < VisualRect.yStart)yStart = VisualRect.yStart;
			if(yEnd > VisualRect.yEnd)yEnd = VisualRect.yEnd;
			return (xEnd < xStart || yStart > yEnd);
		}
		//将x,y围与wgRect和VisualRect三方求交集
		inline uint8_t boundIntersect3(int* xStart,int* yStart,int* xEnd,int* yEnd)
		{
			if(wXStart < VisualRect.xStart)
			{
				if(*xStart < VisualRect.xStart)*xStart = VisualRect.xStart;
			}
			else
			{
				if(*xStart < wXStart)*xStart = wXStart;
			}
			if(wYStart < VisualRect.yStart)
			{
				if(*yStart < VisualRect.yStart)*yStart = VisualRect.yStart;
			}
			else
			{
				if(*yStart < wYStart)*yStart = wYStart;
			}
			if(wXEnd > VisualRect.xEnd)
			{
				if(*xEnd > VisualRect.xEnd)*xEnd = VisualRect.xEnd;
			}
			else
			{
				if(*xEnd > wXEnd)*xEnd = wXEnd;
			}
			if(wYEnd > VisualRect.yEnd)
			{
				if(*yEnd > VisualRect.yEnd)*yEnd = VisualRect.yEnd;
			}
			else
			{
				if(*yEnd > wYEnd)*yEnd = wYEnd;
			}
			return (*xStart > *xEnd || *yStart > *yEnd);
		}
};
