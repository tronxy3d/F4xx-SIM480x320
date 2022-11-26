#pragma once

#include "yBinary.hpp"

extern const PicAttr Font_En8x16Camb;
class yWords : virtual public yBinary
{
	public:
		yWords(int xStart = 0,int yStart = 0,int width = 0,int height = 0,const ScaleAttr* idle_attr = nullptr,const ScaleAttr* focus_attr = nullptr);
		virtual ~yWords();
		void setWBuffer(uint16_t size,const char*content);
		void setWBuffer(uint16_t size,const uint16_t*content = nullptr);
		void setWBuffer(uint16_t size,uint16_t c,bool full = true);
		void setChars(const char* src);
		void addChars(const char* src);
		void setChars(const uint16_t *src);
		void addChars(const uint16_t *src);
		void addChar(uint16_t t);
		inline void setWordsYScale(int ystart,int yend) {lbYStart = ystart;lbYEnd = yend;}
		inline void setWordsColor(color_t fr_idle,color_t bg_idle,color_t fr_focus = 0,color_t bg_focus = 0) {
			wordsFrIdle = fr_idle;
			wordsBgIdle = bg_idle;
			wordsFrFocus = fr_focus;
			wordsBgFocus = bg_focus;
		}
		uint8_t wordsOpaque;
		uint8_t _fillMargin;
		uint8_t wxCenter; //文字X自动居中
		uint8_t textDistance;//必须在addChars等函数之前,因为它们会用到这个值
		uint8_t representChar;//如果这里被赋非0值,则显示字符时,只显示本变量,不显示真实的字符,常用于密码显示
		static uint16_t uw_start_addr;//显示国际语言起点地址
		//如果全部显示,则为0
		//如果只显示某种语言,则起始地址为该语言第一个字符在unicode中的位置
		//例如只显示中文则为0x4E00,中文范围0x4E00~0x9FBB
		int wordOffsetX,wordOffsetY;//不能直接变成wordX的原因是当窗口移动调用setRectOffset所有控件的位置都会变
		int verticalDistance;//垂直间距
		const PicAttr *wEnPic,*wCnPic;
		uint16_t *words;

	protected:
		color_t wordsFrIdle,wordsFrFocus,wordsBgIdle,wordsBgFocus;
		uint16_t wordsLen;
		int lbYStart,lbYEnd;//Y范围
		uint8_t putc(uint16_t c);
		void fillMargin();
		void updateWords(uint8_t force);
		void showWords(uint8_t force) { updateWords(force);sign.content.text = 0;}
		inline void pureSetFocus(uint8_t tf) {
			if(tf && !focus) {
				if(focusAllUpdate)sign.content.text = 1;
			}
			else if(!tf && focus) {
				sign.content.text = 1;
			}
		}
		inline virtual uint8_t enUpdate(void) {return sign.content.text == 0 && words;}
		int wordsXScale(const uint16_t* tar);
		int oneWordXSize(uint16_t c);
};

class yLabel : virtual public yWords
{
	public:
		yLabel(int xStart = 0,int yStart = 0,int width = 0,int height = 0,const ScaleAttr* idle_attr = nullptr,const ScaleAttr* focus_attr = nullptr) :
		yWidget(xStart,yStart,width,height,idle_attr,focus_attr){}
		virtual ~yLabel(){}
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
			yWords::pureSetFocus(tf);
			yWidget::setfocus(tf);
		}
		inline virtual uint8_t enUpdate(void) {return yWidget::enUpdate() || yWords::enUpdate();}
};
