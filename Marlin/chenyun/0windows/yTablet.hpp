#pragma once

#include "yLabel.hpp"

typedef struct
{
	int lineHighest;
	uint16_t* word;
}TPAD;

class yTablet : virtual public yWords
{
	public:
		yTablet(int xStart = 0,int yStart = 0,int width = 0,int height = 0,const ScaleAttr* idle_attr = nullptr,const ScaleAttr* focus_attr = nullptr) :
		yWidget(xStart,yStart,width,height,idle_attr,focus_attr){
			Column = 0;
			Row = 0;
			Pad = 0;
			margin = 1;
		}
		virtual ~yTablet(){freePad();}
		virtual uint8_t update(uint8_t force = 0);
		inline virtual void show(uint8_t force = 0) {
			update(force);
			sign.content.scale = 0;
			sign.content.text = 0;
		}

		inline virtual uint8_t enUpdate(void) {return yWidget::enUpdate() || (Pad && sign.content.text == 0);}
		void addChars(const char*str);//向Notepad加入字符串
		void addChars(const uint16_t*tar);
		void setBuffSpace(int row,int column);
		int margin;//文字离边界距离

	private:
		uint8_t Column,Row;//一共有多少列多少行
		uint8_t curRow,curColumn;//光标位置:所在行和列
		int curXPixel;//光标列像素位置(用以计算是否越边界)
		TPAD *Pad;
		void freePad();
		void allocPad();//此函数应该在设置utf16是否为true后调用
		void lineFeed();//换行
};

