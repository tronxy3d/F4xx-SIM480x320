#pragma once

#include "yLabel.hpp"

class yVariant : virtual public yWords
{
	public:
		yVariant(int xStart = 0,int yStart = 0,int width = 0,int height = 0,const ScaleAttr* idle_attr = nullptr,const ScaleAttr* focus_attr = nullptr) :
		yWidget(xStart,yStart,width,height,idle_attr,focus_attr) {
			fixedEdge = 1;
		}
		virtual ~yVariant(){}
		virtual uint8_t update(uint8_t force = 0) {
			if(yWidget::update(force))return 1;
			if(!focus || focusAllUpdate)updateWords(force);
			return 0;
		}
		inline virtual void show(uint8_t force = 0) {
			update(force);
			sign.content.scale = 0;
			sign.content.text = 0;
		}
		inline virtual void setfocus(uint8_t tf) {
			yWidget::setfocus(tf);
			yWords::pureSetFocus(tf);
		}

		uint8_t fixedEdge;//1-当colorVertical为true时上边,否则左边固定;0-当colorVertical为true时,下边,否则右边固定;
		void changeBorder(int v);//fixedEdge决定固定边,这里变化的是与之对应的可变的边
};
