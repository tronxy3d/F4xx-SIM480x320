#pragma once

#include "yFigure.hpp"
#include "yPicture.hpp"
#define ALIGN_CONTENT_LENGTH  9 //1换行符,M10086 ;8个对齐字符
class yFigureSd : public yFigure
{
    public:
        yFigureSd(int xStart = 0,int yStart = 0,int width = 0,int height = 0,const ScaleAttr* idle_attr = nullptr,const ScaleAttr* focus_attr = nullptr) :
		yWidget(xStart,yStart,width,height,idle_attr,focus_attr)
        {
            sdfileName = nullptr;
            picSign = nullptr; //图标识
            picOffsetFromFile = 0; //图信息在SD文件中的位置(可以快速找到图片)
            picXOffset = 0;
            picYOffset = 0;
        }
        virtual ~yFigureSd();
        virtual uint8_t update(uint8_t force = 0);
        // inline virtual void setfocus(uint8_t tf) {
        //     yFigure::setfocus(tf);
        // }
        uint8_t updateSdpic(uint8_t force = 0);
        void setSdpicInfo(const char* name,const char*sign, uint32_t offset, int width, int height);
        void clearSdpicInfo();
        inline void setSdpicOffset(int x,int y) {picXOffset = x; picYOffset = y;}
        //检测是否有sdpic,如果有,返回其图像偏移量,当返回0xFFFFFFFE时,文件打不开,返回0xFFFFFFFF时,没有sdpic
        static uint32_t sdpicCheck(const char*fname,const char* sign,uint32_t picOffset);
        static void exeSdpic(const char*fname,int xsize,int ysize, uint32_t& foffset, void (*)(const void*,int));
    private:
        char *sdfileName, *picSign;
        int picXOffset, picYOffset;
        int picXSize, picYSize;
        uint32_t picOffsetFromFile;
};
