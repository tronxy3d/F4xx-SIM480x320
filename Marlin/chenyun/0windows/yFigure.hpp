#pragma once

#include "yLabel.hpp"
class yFigure : virtual public ySimulation, virtual public yWords
{
	public:
		yFigure(int xStart = 0,int yStart = 0,int width = 0,int height = 0,const ScaleAttr* idle_attr = nullptr,const ScaleAttr* focus_attr = nullptr) :
		yWidget(xStart,yStart,width,height,idle_attr,focus_attr)
		{}
		virtual ~yFigure(){}
		virtual uint8_t update(uint8_t force = 0);
		inline virtual void show(uint8_t force = 0) {
			update(force);
			sign.content.scale = 0;
			sign.content.simulation = 0;
			sign.content.text = 0;
		}
		inline virtual void setfocus(uint8_t tf) {
			yWords::pureSetFocus(tf);
			ySimulation::setfocus(tf);
		}
		inline virtual uint8_t enUpdate(void) {return ySimulation::enUpdate() || yWords::enUpdate();}
};

class mFigure : public yFigure
{
	public:
		mFigure(int xStart = 0,int yStart = 0,int width = 0,int height = 0,const ScaleAttr* idle_attr = nullptr,const ScaleAttr* focus_attr = nullptr) :
		yWidget(xStart,yStart,width,height,idle_attr,focus_attr)
		{
			info = nullptr;
			infoOffsetX = 0;
			infoOffsetY = 0;
		}
		virtual uint8_t update(bool force = false);
		void setInfo(int n,const uint16_t* s = nullptr);
		inline void setInfoOffset(int x,int y) {
			infoOffsetX = x;
			infoOffsetY = y;
		}
		inline void setInfoColor(color_t fr,color_t bg) {
			infoFr = fr;
			infoBg = bg;
		}
		uint16_t *info;

	private:
		int infoOffsetX,infoOffsetY;
		color_t infoFr,infoBg;
		void updateInfo(bool force);
};
