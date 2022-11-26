#pragma once

#include "yFigure.hpp"
#include "yIcon.hpp"
#include "yMultiple.hpp"

class yCircleButton : public yMultiple
{
    public:
        yCircleButton(int xStart = 0,int yStart = 0,int width = 0,int height = 0,const ScaleAttr* idle_attr = nullptr,const ScaleAttr* focus_attr = nullptr) :
        yWidget(xStart,yStart,width,height,idle_attr,focus_attr)
		{
            circleR = (width > height ? height : width) / 2;
            circleDis = 1;
            circleX = wXStart + width / 2;
            circleY = wYStart + height / 2;
        }
        virtual ~yCircleButton(){}
        virtual uint8_t update(uint8_t force);
        inline virtual void show(uint8_t force = 0) {
            update(force);
            sign.content.scale = 0;
            sign.content.simulation = 0;
            sign.content.text = 0;
        }
        int circleX,circleY; //圆心坐标
        int circleR;//圆半径
        int circleDis;//圆周厚度
    private:
		void midCircle(color_t color,int r,int x,int y,int dis = 1);//画圆:圆心x,y,半径r,圆边厚度dis
		void pollCircle(color_t color_start,color_t color_end,int r,int dis,int xStart,int yStart,int xEnd,int yEnd);//画圆:半径r,厚度dis
};

class yRoundedBase : virtual public yWidget
{
    public:
        yRoundedBase(int xStart = 0,int yStart = 0,int width = 0,int height = 0,const ScaleAttr* idle_attr = nullptr,const ScaleAttr* focus_attr = nullptr) :
        yWidget(xStart,yStart,width,height,idle_attr,focus_attr)
        {
            rounded_r = 2;
        }
        virtual ~yRoundedBase(){}
        inline void setRoundedRadius(int rs = 1) {rounded_r = rs;}
        virtual uint8_t update(uint8_t force = 0);
    protected:
        void updateRounded(color_t color_start,color_t color_end);
        int rounded_r;
};

class yRoundedSimulation : virtual public yFigure,virtual public yRoundedBase //圆角矩形按钮
{
    public:
        yRoundedSimulation(int xStart = 0,int yStart = 0,int width = 0,int height = 0,const ScaleAttr* idle_attr = nullptr,const ScaleAttr* focus_attr = nullptr) :
        yWidget(xStart,yStart,width,height,idle_attr,focus_attr){}
        virtual ~yRoundedSimulation(){}
        virtual uint8_t update(uint8_t force);//层级:圆角->文字(或多图)
};

class yRoundedPicture : virtual public yIcon, virtual public yRoundedBase
{
    public:
        yRoundedPicture(int xStart = 0,int yStart = 0,int width = 0,int height = 0,const ScaleAttr* idle_attr = nullptr,const ScaleAttr* focus_attr = nullptr) :
        yWidget(xStart,yStart,width,height,idle_attr,focus_attr){}
        virtual ~yRoundedPicture(){}
        virtual uint8_t update(uint8_t force);//层级:圆角->图片->文字
};
