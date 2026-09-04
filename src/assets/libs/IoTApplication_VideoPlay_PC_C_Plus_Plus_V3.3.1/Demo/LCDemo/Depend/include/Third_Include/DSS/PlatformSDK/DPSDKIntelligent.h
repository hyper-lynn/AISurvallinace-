/**
 * Copyright (c) 2012, 浙江大华
 * All rights reserved.
 *
 * 文件名称：
 * 文件标识：
 * 摘　　要：Platform SDK的接口文件，智能相关模块
 *
 * 当前版本：1.0
 * 原作者　：12928
 * 完成日期：2012年9月14日
 * 修订记录：创建
 */

#ifndef INCLUDED_DPSDK_DPSDKINTELLIGENT_H
#define INCLUDED_DPSDK_DPSDKINTELLIGENT_H

#include "DPSDK.h"

BEGIN_NAMESPACE_DPSDK
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
#define DPSDK_IVS_EVENT_NAME_LEN		32					// 规则事件名称长度

// fixme::后续的人流量统计查询粒度可采用该枚举
// 人流量统计查询粒度，0:分钟,1:小时,2:日,3:周,4:月,5:季,6:年;
typedef enum
{
	QUERY_GRANULARITY_MINUTE	= 0,						// 分钟
	QUERY_GRANULARITY_HOUR,									// 小时
	QUERY_GRANULARITY_DAY,									// 日
	QUERY_GRANULARITY_WEEK,									// 周
	QUERY_GRANULARITY_MONTH,								// 月
	QUERY_GRANULARITY_QUARTER,								// 季
	QUERY_GRANULARITY_YEAR,									// 年
}dpsdk_query_granularity_e;

// 人员统计信息
typedef struct DPSDK_API tagPerson_Count_Info
{
	int			nChannelID;									// 统计通道号
	char		szRuleName[DPSDK_IVS_EVENT_NAME_LEN];		// 规则名称
	uint32_t	nStartTime;									// 开始时间
	uint32_t	nEndTime;									// 结束时间
	uint32_t	nEnteredSubTotal;							// 进入人数小计
	uint32_t	nExitedSubtotal;							// 出去人数小计
	uint32_t	nAvgInside;									// 平均保有人数(除去零值)
	uint32_t	nMaxInside;									// 最大保有人数

	tagPerson_Count_Info(void);
}Person_Count_Info_t;
//////////////////////////////////////////////////////////////////////////

// 智能模块回调消息基类
class DPSDK_API IntelligentBaseMsg : public DPSDKCBMessage
{
public:
	IntelligentBaseMsg(int cmd = DPSDK_CMD_UNKNOWN, int msgType = DPSDK_MSG_REQUEST);
	virtual ~IntelligentBaseMsg(void){}

public:
	char		szCameraId[DPSDK_CHL_ID_LEN];				// 摄像头ID
	char		serverId[SERVER_ID_LEN];					// 服务ID，【注】外部使用时无需填充此字段
};

// 获取智能规则回调消息（CMD=DPSDK_CMD_GET_IVSRULE）
class DPSDK_API GetIvsRuleMsg : public IntelligentBaseMsg
{
public:
	GetIvsRuleMsg(void);
	virtual ~GetIvsRuleMsg(void);

public:
	uint32_t	nSessionId;									// 会话ID

	char*		pRuleInfo;									// 规则数据
	int			nLen;										// 数据长度
};

// 查询人流量总数回调消息（CMD=DPSDK_CMD_QUERY_IVSPC_CONUT）
class DPSDK_API QueryPersonCountMsg : public IntelligentBaseMsg
{
public:
	QueryPersonCountMsg(void);
	virtual ~QueryPersonCountMsg(void){}

public:
	uint32_t	nStartTime;									// 开始时间
	uint32_t	nEndTime;									// 结束时间
	int			nGranularity;								// 查询粒度

	uint32_t	nTotalCount;								// 查询总数
	uint32_t	nQuerySession;								// 查询会话
	uint32_t	nPlanId;									// 计划ID，只对球机有效，取值[1,4]
};

// 一次查询人流量统计信息回调消息（CMD=DPSDK_CMD_QUERY_IVSPC_BYPAGE）
class DPSDK_API QueryPersonCountByPageMsg : public IntelligentBaseMsg
{
public:
	QueryPersonCountByPageMsg(void);
	virtual ~QueryPersonCountByPageMsg(void);

public:
	uint32_t				nQuerySession;					// 查询会话
	uint32_t				nIndex;							// 开始值
	uint32_t				nCount;							// 查询条数

	Person_Count_Info_t*	pRetData;						// 查询结果信息
	uint32_t				nRetCount;						// 实际结果条数
};

// 停止查询人流量统计回调消息（CMD=DPSDK_CMD_QUERY_IVSPC_STOP）
class DPSDK_API StopQueryPersonCountMsg : public IntelligentBaseMsg
{
public:
	StopQueryPersonCountMsg(void);
	virtual ~StopQueryPersonCountMsg(void){}

public:
	uint32_t	nQuerySession;								// 查询会话
};

// 智能球手动跟踪回调消息（CMD=DPSDK_CMD_MANUAL_TRACK）
class IntelligentManualTrackMsg : public IntelligentBaseMsg
{
public:
	IntelligentManualTrackMsg(void);
	virtual ~IntelligentManualTrackMsg(void){}

public:
	int			nObjId;										// 物体ID
	uint32_t	nLeft;										// 左《点的坐标归一化到[0,8192]区间》
	uint32_t	nTop;										// 上
	uint32_t	nRight;										// 右
	uint32_t	nBottom;									// 下
};

// 主从跟踪智能盒手动跟踪回调消息（CMD = DPSDK_CMD_MASTERSLAVE_TRACK）
class DPSDK_API IntelligentMasterSlaveTrackMsg : public IntelligentBaseMsg
{
public:
	IntelligentMasterSlaveTrackMsg(void);
	virtual ~IntelligentMasterSlaveTrackMsg(void){}

public:
	int			nObjId;										// 物体ID
};

// 主从跟踪智能盒定点跟踪回调消息（CMD = DPSDK_CMD_FIXEDPOINT_TRACK）
class DPSDK_API IntelligentFixedPointTrackMsg : public IntelligentBaseMsg
{
public:
	IntelligentFixedPointTrackMsg(void);
	virtual ~IntelligentFixedPointTrackMsg(void){}

public:
	uint32_t	nPointX;									// X《点的坐标归一化到[0,8192]区间》
	uint32_t	nPointY;									// Y
};
//////////////////////////////////////////////////////////////////////////

class DPSDK_API IDPSDKIntelligent : public IDPSDKFuncBase
{
public:
	/** 获取智能规则
	    @param const char* szCameraId						摄像头ID
	    @param uint32_t nSessionId							保存上层的会话ID
	    @return												返回Sequence请求顺序号
	*/
	virtual int GetIvsRule(const char* szCameraId, uint32_t nSessionId) = 0;

	/** 查询统计总数
	    @param const char* szCameraId						摄像头ID
	    @param uint32_t nStartTime							开始时间
		@param uint32_t nEndTime							结束时间
		@param int nGranularity								查询粒度，0:分钟,1:小时,2:日,3:周,4:月,5:季,6:年;
		@param uint32_t nPlanId								计划ID，只对球机有效
	    @return												返回Sequence请求顺序号
	*/
	virtual int QueryPersonCount(const char* szCameraId, uint32_t nStartTime, uint32_t nEndTime, int nGranularity, uint32_t nPlanId = 1) = 0;

	/** 查询统计结果
	    @param const char* szCameraId						摄像头ID
	    @param uint32_t nQuerySession						查询会话，查询统计总数时返回的
		@param uint32_t nIndex								此次查询的开始值
		@param uint32_t nCount								此次查询的数量
	    @return												返回Sequence请求顺序号
	*/
	virtual int QueryPersonCountBypage(const char* szCameraId, uint32_t nQuerySession, uint32_t nIndex, uint32_t nCount) = 0;

	/** 查询统计结果
	    @param const char* szCameraId						摄像头ID
	    @param uint32_t nQuerySession						查询会话，查询统计总数时返回的
	    @return												返回Sequence请求顺序号
	*/
	virtual int StopQueryPersonCount(const char* szCameraId, uint32_t nQuerySession) = 0;
	
	/** 查询统计总数
	    @param const char* szCameraId						摄像头ID
	    @param int nObjId									物体ID，-1表示框选的是智能帧上传框外任意位置物体，>=0表示框选的是智能帧上传的物体
		@param uint32_t nLeft								左《点的坐标归一化到[0,8192]区间》
		@param uint32_t nTop								上
		@param uint32_t nRight								右
		@param uint32_t nBottom								下
	    @return												返回Sequence请求顺序号
	*/
	virtual int IntelligentManualTrack(const char* szCameraId, int nObjId, uint32_t nLeft, uint32_t nTop, uint32_t nRight, uint32_t nBottom) = 0;

	/** 主从手动跟踪
	    @param const char* szCameraId						摄像头ID
	    @param int nObjId									物体ID，-1表示框选的是智能帧上传框外任意位置物体，>=0表示框选的是智能帧上传的物体
	    @return												返回Sequence请求顺序号
	*/
	virtual int MasterSlaveIntellManualTrack(const char* szCameraId, int nObjId) = 0;

	/** 主从定点跟踪
	    @param const char* szCameraId						摄像头ID
		@param uint32_t nPointX								点坐标《点的坐标归一化到[0,8192]区间》
		@param uint32_t nPointY								点坐标
	    @return												返回Sequence请求顺序号
	*/
	virtual int MasterSlaveIntellFixedPointTrack(const char* szCameraId, uint32_t nPointX, uint32_t nPointY) = 0;

protected:
	virtual ~IDPSDKIntelligent(void){}
};
//////////////////////////////////////////////////////////////////////////

END_NAMESPACE_DPSDK

#endif
