/* Copyright (c) 2011, 浙江大华技术股份有限公司, All rights reserved.
 * 2011-09
 *
 * DPSDKTime.h : 时间处理函数
 */

#ifndef INCLUDED_DPSDK_DPDSKTIMEHELPER_H
#define INCLUDED_DPSDK_DPDSKTIMEHELPER_H

#include "DPSDKDefine.h"
#include <time.h>
#include <libdsl/DTime.h>

namespace dsl
{
	class DTime;
}

BEGIN_NAMESPACE_DPSDK

//是否需要调整夏令时，减去一个小时
bool DPSDK_API needAdjustDst(time_t secsSince1Jan1970UTC);

//因为服务器没有夏令时概念，客户端在处理时会有夏令时
//所以在获取到的时候就主动减去一个小时,保证ui上显示的时候就是和服务器一样的时间

/*
@return：单位秒
*/
time_t DPSDK_API mktime_dpsdk(struct tm * _Tm);

/*
time(NULL)直接获取的是UTC的时间, 先提取出来内部实现，不改；
@_Time：单位秒
*/
time_t DPSDK_API time_dpsdk(time_t * _Time);


// DPSDKTime：时间的表示和转换的类, 单位均为ms
/**
是对DTime的一个封装，DTime内部关注的是 年月日时分秒，所有处理都会有夏令时的概念
给一个time_t secsSince1Jan1970UTC = 1397196011;//2014/4/11 8:00:11
在DTime内部会随着系统的是否启用夏令时得到不一样的时间
不启用时2014/4/11 8:00:11==>启用时2014/4/11 9:00:11

DPSDKTime的目的就是希望得到的时间都是一样的2014/4/11 8:00:11

==>注意一个比较特殊的情况
例，夏令时 在UTC 1:00点的时候
调用DPSDKTime::SetNow==>获取到的m_ptm.m_hour为2
调用DPSDKTime::SetTime(1)==>获取到的m_ptm.m_hour为1
上层如果同一时刻想通过SetNow和SetTime来对比m_hour会有问题
*/
class DPSDK_API DPSDKTime
{
public:	
	DPSDKTime();
	DPSDKTime( int64_t t );
	virtual ~DPSDKTime(void);

	/*
	该函数实现是直接调用的DTime的SetNow，DTime里面是
	直接获取的是系统展示的小时（如果按夏令时展示，也会展示这一个小时）
	*/
	void SetNow();

	/*
	通过调用DTime的SetTime（如果启用夏令时，因为DTime::SetTime会夏令时处理多出一个小时，
	所以先会从t里面减去一个小时来中和，来得到正确的 小时）
	*/
	void SetTime( int64_t t ); 

	/*
	通过调用DTime的MakeTime(显示为夏令时时, DTime内部是把m_ptm(2014/4/11 8:00:11)作为夏令时时间处理的，
	因此获取出来UTC的ms，其实是前一个小时(2014/4/11 7:00:11)的UTC时间
	所以后面会在加上一个小时，得到2014/4/11 8:00:11对应的ms)	
	*/
	int64_t MakeTime() const;

	inline dsl::DTime* GetObjPointer() const { return m_ptm; }
	inline dsl::DTime& GetObj() const { return (*m_ptm); }

	/*
	这里展示当前系统时间对应的UTC时间
	（注意 夏令时时，DPSDKTime是没有夏令时概念的，对展示的时间是被直接认为 非夏令时状态下的时间
	例，夏令时2014/4/11 8:00:11时，
	DTime获取的是1397192411==>因为DTime认为这个时间是夏令时，对应非夏令时是多一个小时的，
							==>实际是按照2014/4/11 7:00:11获取的UTC
	DPSDKTime获取的是1397196011==>因为DPSDKTime直接就是认为这个是非夏令时，按照2014/4/11 8:00:11获取UTC）
	*/
	static int64_t Now();
	static int64_t GetTime() { return Now(); }
	static uint32_t GetTick(); // ms from system start, 49 days roundup

	//直接调用c函数, 与DTime没有关系
	/*
	struct tm * _Tm: 输出
	*/
	static int Localtime(struct tm * _Tm, const time_t * _Time);

	static bool GetDstEnable() { return m_bDstEnable; }
	static void SetDstEnable(bool bDstEnable) { m_bDstEnable = bDstEnable; }

private:
	dsl::DTime* m_ptm;
	static bool m_bDstEnable;//是否启用夏令时，false时，需要去除夏令时的1个小时
};

/////////////////////////////////////////////////
END_NAMESPACE_DPSDK

#endif

