#pragma once

#include "../yCommon.h"

class Output
{
public:
	uint8_t imode;//数制(十进制,),应用是通过参数传入的,被子类使用
	uint8_t index;//标记当前Out编号,从0开始
	Output();
	virtual void send(uint8_t byte) const = 0;
	Output& operator<<(const char*tstr)
	{
		while(*tstr)send(*tstr++);
		return *this;
	}
	Output& operator<<(double d);
	Output& operator<<(int i);
	Output& operator<<(uint8_t n){return *this << (int)n;}
	Output& operator<<(short n){return *this << (int)n;}
	Output& operator<<(uint16_t n){return *this << (int)n;}
	Output& operator<<(long n){return *this << (int)n;}
	Output& operator<<(uint32_t n){return *this << (int)n;}
	Output& operator<<(char c){send(c);return *this;}
	Output& operator<<(Output& out(Output&)){return out(*this);}
	void print(const char*str,...);
};
inline Output& dec(Output& o){o.imode = 0;return o;}
inline Output& hex(Output& o){o.imode = 1;return o;}
inline Output& oct(Output& o){o.imode = 2;return o;}
inline Output& bin(Output& o){o.imode = 3;return o;}
inline Output& endl(Output& o){return o << "\r\n";}

typedef enum
{
	NUM2 = 2,//二进制
	NUM8 = 8,//八进制
	NUM10 = 10,//十进制
	NUM16 = 16 //十六进制
}NUM_MODE;

typedef const char* CPSTR;
typedef char* PSTR;

namespace yString
{
	template<typename T>
	int len(const T*str)//计算字符串长度
	{
		if(!str)return 0;
		int n = 0;
		while(str[n])n++;
		return n;
	}

	template<typename T>
	int cmp(const T* sce, const T* tar)//比较两字符串大小,source > target返回1,source < target返回-1,source == target返回0
	{
		if (!tar && !sce)return 0;
		if (!tar)return 1;
		if (!sce)return -1;
		while (*sce && *tar){
			if (*sce > *tar)return 1;
			else if (*sce < *tar)return -1;
			sce++;
			tar++;
		}
		if (*sce > *tar)return 1;
		else if (*sce < *tar)return -1;
		return 0;
	}

	template<typename T>
	void cpy(T* tar, const T*sce, int maxlen = 0)//复制source到target中
	{
		if(!tar)return;
		if(!sce) {
			*tar = 0;
			return;
		}
		while (*sce) {
			*tar++ = *sce++;
			if(maxlen) {
				--maxlen;
				if(maxlen == 0)break;
			}
		}
		*tar = 0;
	}

	template<typename T>
	void cat(T* tar,const T*sce)//将source追加到target中
	{
		if(!tar || !sce)return;
		while(*tar)tar++;
		cpy(tar,sce);
	}
	
	void memzero(void* target,int size);
	/*******************************************************************************
	* 类名	：  Command		*函数:	hasElement
	* 描述		：判断源串中是否存在独立的目标串
				: 独立:在源串的目标串后边,当end!=0xFF时,后边只可能是空格类或'\0'或end字符
				  当end==0xFF时可以是任何字符
	* 参数		: sce-源串,tar-目标串
	* 返回		:如果存在,返回目标串在源串中的位置,否则返回-1
	* 编写者		：YSZ		编写日期:2020-03-24
	*******************************************************************************/
	int hasElement(const char* sce,const char* tar,uint8_t end = 0);
	uint8_t startWith(const char*source,const char *target);//source以target作开头返回1,否则返回0
	uint8_t endWith(const char *source,const char *target);//source以target作结尾返回1,否则返回0

	template<typename T>
	int alignWidth(T* str, const T*src, int srcLen, int width)
	{
		int i = 0;
		if(width < 0){
			width = -width;
			for(; i < width && i < srcLen; i++)str[i] = src[i];
			for(; i < width; i++)str[i] = ' ';
		}
		else if(width > 0){
			int t = width - srcLen;
			for(; i < t; i++)str[i] = ' ';
			for(; i < width; i++)str[i] = src[i - t];
		}
		else {
			while(i < srcLen)str[i] = src[i];
		}
		str[i] = 0;
		return i;
	}
	/*******************************************************************************
	* 函数名		：intToStr
	* 描述			：数字转字符串
	*	参数	:num 源数字
					:str 转后的字符串存放地址
					:mode 数制
	*	返回	:转换后的字符串长度
	* 编写者		：YSZ
	* 编写日期	：2019-12-28
	*******************************************************************************/
	template<typename T>
	int intToStr(int num, T* str, NUM_MODE mode)
	{
		int tempv = num, n = 0;
		uint32_t temp,t;
		if (!num){
			str[0] = '0';
			str[1] = 0;
			return 1;
		}
		if (mode == 10 && tempv < 0){
			str[0] = '-';
			n = 1;
			temp = -tempv;
		}
		else temp  = tempv;
		for (t = temp; t; n++)t /= mode;//求出显示位数
		str[n] = 0;
		for (t = n - 1; temp > 0; t--){
			str[t] = temp % mode;
					if(str[t] > 9)str[t] = str[t] + 'A' - 10;
					else str[t] += '0';
			temp /= mode;
		}
		return n;
	}

	template<typename T>
	int intToStr(int num, T*str, NUM_MODE mode,int width)
	{
		if(width == 0) return intToStr(num,str,mode);
		T tstr[32];
		int r = intToStr(num,tstr,mode);
		return alignWidth(str,tstr,r,width);
	}
	/*******************************************************************************
	* 函数名        ：floatToStr
	* 描述          ：浮点数转字符串
	* 参数          :num 源数字
                   :str 转后的字符串存放地址
				   :width 转后的总宽度,负数左对齐,正数右对齐
				   :dot_num 转后的小数位数
	* 返回          :转换后的字符串长度
	* 编写者        ：YSZ
	* 编写日期      ：2019-12-28
	*******************************************************************************/
	template<typename T>
	int floatToStr(float num, T*str,int dot_num = 2, int width = 0) {
		uint8_t i;
		T tstr[32];
		int n, tv;
		float t = 0.5;//精度四舍五入
		for(i = 0;i < dot_num;i ++)t /= 10;
		if(num < 0) {
			num -= t;
			num = -num;
			n = (int)num;
			if(width == 0) {
				str[0] = '-';
				tv = intToStr(n, str + 1,NUM10) + 1;
			}
			else {
				tstr[0] = '-';
				tv = intToStr(n, tstr + 1,NUM10) + 1;
			}
		}
		else {
			num += t;
			n = (int)num;
			if(width == 0) tv = intToStr(n, str,NUM10);
			else tv = intToStr(n, tstr,NUM10);
		}
		num -= n;
		if(width == 0)str[tv ++] = '.';
		else tstr[tv ++] = '.';
		for (i = 0; i < dot_num; i++,tv ++) {
			num *= 10;
			n = (int)num;
			num -= n;
			if(width == 0)str[tv] = n + '0';
			else tstr[tv] = n + '0';
		}
		if(width == 0) {
			str[tv] = 0;
			return tv;
		}
		return alignWidth(str,tstr,tv,width);
	}

	/*******************************************************************************
	* 函数名		：strToInt
	* 描述			：字符串转数字
	*	参数	:str 源字符串
					:mode 数制
	*	返回	:转换后的结果
	* 编写者		：YSZ
	* 编写日期	：2020-01-12
	*******************************************************************************/
	template<typename T>
	int strToInt(const T* str,NUM_MODE mode) {
		int n = 0,sign = 1;
		while(*str == ' ')str++;//跳过空格
		switch(mode)
		{
			case NUM2:
				while(*str == '0' || *str == '1'){
					n = (n << 1) + *str - '0';
					str ++;
				}
				break;
			case NUM8:
				while(*str >= '0' && *str <= '7'){
					n = (n << 3) + *str - '0';
					str ++;
				}
				break;
			case NUM10:
				if(*str == '-'){
					str ++;
					sign = -1;
				}
				while(*str >= '0' && *str <= '9'){
					n = n * 10 + *str - '0';
					str ++;
				}
				n *= sign;
				break;
			case NUM16:
				while(1){
					if(*str >= '0' && *str <= '9')n = (n << 4) + *str - '0';
					else if(*str >= 'A' && *str <= 'F')n = (n << 4) + *str - 'A' + 10;
					else if(*str >= 'a' && *str <= 'f')n = (n << 4) + *str - 'a' + 10;
					else break;
					str ++;
				}
				break;
		}
		return n;
	}

	/*******************************************************************************
	* 函数名		：strToDouble
	* 描述			：字符串转浮点数
	*	参数	:str 源字符串
	*	返回	:转换后的结果
	* 编写者		：YSZ
	* 编写日期	：2020-01-12
	*******************************************************************************/
	template<typename T>
	float strToDouble(const T* str) {
		int sign = 1,dot = 0,pos = 1;
		float d = 0.0;
		while(*str && *str != '-' && (*str < '0' || *str > '9'))str++;//跳过非数字段
		if(!*str)return 0.0;
		if(*str == '-'){
			sign = -1;
			str ++;
		}
		while(1){
			if(*str == '.' && dot == 0){
				dot = 1;
			}else if(*str >= '0' && *str <= '9'){
				if(dot == 1)pos *= 10;
				d = d * 10 + *str - '0';
			}
			else break;
			str ++;
		}
		d /= pos * sign;
		return d;
	}

	inline uint8_t isspace(char x){return x == ' ' || x == '\t' || x == '\f' || x == '\r' || x == '\n';}
	inline uint8_t isseparate(char x,char v){return isspace(x) || x == v;}
	inline void pass(PSTR& x,char v){while(*x && !isseparate(*x,v))x++; while(isseparate(*x,v))x ++;}
};

extern uint32_t romdataAddr;
void romdataUpdate(void);
uint8_t romdataReset(uint32_t taddr,uint32_t period = 200); //失败返回0xFF
uint8_t romdataGetOnebyte(void);//返回0xFF可能是失败了
uint8_t romdataGetData(uint8_t *dst,int len);//失败返回0xFF
void romdataJump(uint32_t leng);

