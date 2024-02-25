#pragma once

#include "yScale.hpp"
typedef struct __attribute__((__packed__)) {
  int x;
  int y;
  short offset_x;
  short offset_y;
} Touch_t;

class yWindow {
	public:
		//注意,这里会改变控件的位置,所以,在控件有边界判断(如addChars)这种操作时,需要在最后调用yWindow
		yWindow(int x, int y, int width, int height, yWidget *components[], int componentsNum, yWindow* parent = nullptr);
		~yWindow();

		yWindow* Parent;
		void refreshComponents();//刷新本窗口
		void update();//刷新窗口(包括父窗口)

		uint8_t needFresh();
		void clrUpdateSign();//当绘制一次窗口后,清除所有需绘标记,等待其它应用标相应标记后再重绘,必须有顶端窗口指针执行
		void setUpdateSign();
		void move(int x,int y);
		yWidget* getComponent(int index){if(index < ComponentNum)return Components[index];return nullptr;}
		int touchDelay;
		static Touch_t para_calibration;
		uint8_t touch(int &x, int &y, uint8_t ifExecute);
		int continueTouchTimes(int dis = 200);//检测屏幕被连续点击(两次点击时间小于dis ms)的次数,正在点击中返回负数,没有点击,返回0,点击完成返回点击的次数
		uint8_t hasStopContinueTouch(int dis = 1000);//停止了连续点击
		inline void touchReset(void) {
			touchStep = 0;
			touchDelay = -1;
			focusIndex = -1;
			tempIndex = -1;
		}
		static inline void getTouchPos(int &x, int &y) {
			x = ((x * para_calibration.x) >> 16) + para_calibration.offset_x;
    		y = ((y * para_calibration.y) >> 16) + para_calibration.offset_y;
		}
		
	private:
		volatile uint8_t touchStep;
		int tempIndex;
		int focusIndex;
		WRECT winRect;
		yWidget** Components;
		volatile const int ComponentNum;
		inline void componentOffsetCount(int x,int y)
		{
			for(int i = 0;i<ComponentNum;i++)Components[i]->setRectOffset(x,y);
		}
		inline uint8_t getWinVisible()
		{
			if(yWidget::VisualRect.xStart < winRect.xStart)yWidget::VisualRect.xStart = winRect.xStart;
			if(yWidget::VisualRect.xEnd > winRect.xEnd)yWidget::VisualRect.xEnd=winRect.xEnd;
			if(yWidget::VisualRect.yStart < winRect.yStart)yWidget::VisualRect.yStart = winRect.yStart;
			if(yWidget::VisualRect.yEnd > winRect.yEnd)yWidget::VisualRect.yEnd = winRect.yEnd;
			return !(yWidget::VisualRect.xStart > yWidget::VisualRect.xEnd ||
				yWidget::VisualRect.yStart > yWidget::VisualRect.yEnd);
		}
};

