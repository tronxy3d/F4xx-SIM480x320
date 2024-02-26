#pragma once

#include "yLabel.hpp"

class yMultiple : public ySimulation, public yWords //模拟型图标,多图类
{
	public:
		yMultiple(int xStart = 0,int yStart = 0,int width = 0,int height = 0,const ScaleAttr* idle_attr = nullptr,const ScaleAttr* focus_attr = nullptr);
		virtual ~yMultiple(){}
		void setMulti(const PicAttr* pics,int num = 1);
		inline virtual uint8_t update(uint8_t force) {//层级:背景->模拟图标->多图(或文字)
			if(ySimulation::update(force))return 1;
			if(!focus || focusAllUpdate)updateMulti(force);//分开写的目的是为了让承继者可以调用updateMulti
			return 0;
		}
		inline virtual void show(uint8_t force) {
			update(force);
			sign.content.scale = 0;
			sign.content.simulation = 0;
			sign.content.text = 0;
		}
		inline virtual void setfocus(uint8_t tf) {
			yWords::pureSetFocus(tf);
			ySimulation::setfocus(tf);
		}
		inline virtual uint8_t enUpdate(void) {return ySimulation::enUpdate() || (mulPic && sign.content.text == 0);}
	protected:
		const PicAttr* mulPic;
		int mulNum;
		void updateMulti(uint8_t force);
		int multiXScale(const PicAttr* tarp,int num);//获取num个multi x长度(如果提前遇到换行,则到此为止)
};
