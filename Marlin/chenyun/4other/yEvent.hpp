#ifndef Y_EVENT_HPP
#define	Y_EVENT_HPP
#include "../yCommon.h"
#define	EVENT_MAX_NUM	16	//支持多达16路线程,每路线程多达32个事件
#define EVENT_MAX_EVT   32

typedef uint8_t (*yEventFun)(void);
class yEvent
{
private:
	uint8_t number;
	uint8_t paral[EVENT_MAX_NUM];
	uint8_t head[EVENT_MAX_NUM];
	uint8_t tail[EVENT_MAX_NUM];
	uint32_t _evt[EVENT_MAX_NUM];
	uint8_t (*funs[EVENT_MAX_NUM][EVENT_MAX_EVT])(void);
public:
	yEvent();
	/*******************************************************************************
	* 函数名    :setEvt
	* 描述      :在目标任务上开启一个事件
	* 参数      :taskIndex任务编号,该任务必须先被注册
				:evt事件号,不能大于31
				:evtFun事件函数,如果不为nullptr,则会更新注册或上次setEvt的函数
	* 返回      :开启成功返回true,否则false
	* 编写者	    :YSZ
	* 编写日期  :2020-02-20
	*******************************************************************************/
	uint8_t setEvt(uint8_t taskIndex, uint8_t evt, uint8_t (*const evtFun)(void) = nullptr);

	/*******************************************************************************
	* 函数名    :deleteEvt
	* 描述      :在目标任务上删除一个事件
	* 参数      :taskIndex任务编号
				:evt事件号,不能大于31
	* 返回      :开启成功返回true,否则false
	* 编写者	    :YSZ
	* 编写日期  :2022-09-06
	*******************************************************************************/
	uint8_t deleteEvt(uint8_t taskIndex, uint8_t evt);
	inline uint8_t hasEvt(uint8_t taskIndex, uint8_t evt)
	{
		return (_evt[taskIndex] & (1UL << evt));
	}
	yEventFun getEvtFun(uint8_t taskIndex, uint8_t evt);
	
	/*******************************************************************************
	* 函数名    :addEvt
	* 描述      :在任务上添加一个事件,事件不需先注册
	* 参数      :taskIndex 任务编号
				:evtFun事件函数
	* 返回      :如果是并行任务,则返回false添加失败
	* 编写者    :YSZ
	* 编写日期  :2022-09-05
	*******************************************************************************/
	uint8_t addEvt(uint8_t taskIndex, uint8_t (*const evtFun)(void) = nullptr);
	uint8_t getNextEvt(uint8_t taskIndex);//获取下一个可被加入事件的编号

	/*******************************************************************************
	* 函数名	    :registerTask
	* 描述      :任务注册
	* 参数      :index-注册的任务的编号,可自由定义,注意,不同的任务必须分配不同的编号,最大不能超过EVENT_MAX_NUM - 1
				:funLen-该任务需要执行的所有事件对应的函数数量,不能大于EVENT_MAX_EVT - 1
				:fun-该任务需要执行的所有事件对应的函数集合
				:parallel-该任务的所有事件是否并行执行,true并行,false优先级执行,事件号越小优先级越高
	* 返回      :注册成功返回true,否则false
	* 编写者	    :YSZ
	* 编写日期  :2020-02-20
	*******************************************************************************/
	uint8_t registerTask(uint8_t index, uint8_t funLen, uint8_t (*const fun[])(void), uint8_t parallel = false);
	/*******************************************************************************
	* 函数名    :execute
	* 描述      :不停的进行任务事件循环
	* 参数      :-
	* 返回      :-
	* 编写者	    :YSZ
	* 编写日期  :2020-02-20
	*******************************************************************************/
	void execute();
};

#endif
