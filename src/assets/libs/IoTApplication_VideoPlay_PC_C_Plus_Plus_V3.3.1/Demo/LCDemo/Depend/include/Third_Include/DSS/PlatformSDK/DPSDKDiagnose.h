/**
摘要：视频质量诊断
*/

#ifndef INCLUDED_DPSDK_DPSDKDIAGNOSE_H
#define INCLUDED_DPSDK_DPSDKDIAGNOSE_H

#include "DPSDK.h"
// #include <map>
#include <string>
#include <vector>

BEGIN_NAMESPACE_DPSDK

enum VQD_ITEM_TYPE    //视频诊断项的定义，与Web保持一致
{
	DPSDK_DIAGNOSE_TYPE_MOTION		=		0,	// 视频运动
	DPSDK_DIAGNOSE_TYPE_STRIAPE		=		1,	// 条纹干扰
	DPSDK_DIAGNOSE_TYPE_LOSS		=		2,	// 视频丢失
	DPSDK_DIAGNOSE_TYPE_COVERED		=		3,	// 视频遮挡
	DPSDK_DIAGNOSE_TYPE_FROZEN		=		4,	// 视频冻结
	DPSDK_DIAGNOSE_TYPE_HIGHBRIGHT	=		5,	// 高亮度
	DPSDK_DIAGNOSE_TYPE_LOWBRIGHT	=		6,	// 低亮度
	DPSDK_DIAGNOSE_TYPE_NOISE		=		7,	// 视频噪声
	DPSDK_DIAGNOSE_TYPE_COLOCR		=		8,	// 视频颜色
	DPSDK_DIAGNOSE_TYPE_CLARITY		=		9,  // 清晰程度
	DPSDK_DIAGNOSE_TYPE_CHANGED		=		10,	// 场景变化
	DPSDK_DIAGNOSE_TYPE_LOWCONTRAST	=		11,	// 低对比度
	DPSDK_DIAGNOSE_TYPE_FLICKERING	=		13,	// 视频闪烁

	DPSDK_DIAGNOSE_TYPE             =       255,// 诊断无效
};


struct DiagnoseReportInfo
{
	VQD_ITEM_TYPE	item;
	std::string		cameraId;
};

struct DiagnoseList
{
	std::string cameraId;
	int loss;
	int highbright;
	int lowbright;
	int clarify;
	int constract;
	int color;
	time_t diagTime;
};

struct DiagnoseChnList
{
	int loss;
	int highbright;
	int lowbright;
	int clarify;
	int constract;
	int color;
	time_t diagTime;
};

class DPSDK_API QueryDiagnoseCountMsg : public DPSDKCBMessage
{
public:
	QueryDiagnoseCountMsg();
	virtual ~QueryDiagnoseCountMsg(void) {}

public:
	char				orgCode[DPSDK_CHL_ID_LEN];

	int					session;
	int					count;
};

class DPSDK_API GetDiagnoseDateMsg : public DPSDKCBMessage
{
public:
	GetDiagnoseDateMsg();
	virtual ~GetDiagnoseDateMsg(void) {}

public:
	int					session;
	int					startIndex;
	int					count;

	std::vector<DiagnoseReportInfo>   vecInfo;
};

class DPSDK_API StopDiagnoseMsg : public DPSDKCBMessage
{
public:
	StopDiagnoseMsg();
	virtual ~StopDiagnoseMsg(void) {}

public: 
	int					session;
};

class DPSDK_API QueryChnListDiagnoseDateMsg : public DPSDKCBMessage
{
public:
	QueryChnListDiagnoseDateMsg();
	virtual ~QueryChnListDiagnoseDateMsg(void) {}

public:
	char				orgCode[DPSDK_CHL_ID_LEN];

	std::vector<DiagnoseList> vecList;
};

class DPSDK_API QueryChnDiagnoseCountMsg : public DPSDKCBMessage
{
public:
	QueryChnDiagnoseCountMsg();
	virtual ~QueryChnDiagnoseCountMsg(void) {}

public:
	char				cameraId[DPSDK_DEV_ID_LEN];
	uint64_t			begintime;
	uint64_t			endtime;

	int					session;
	int					count;
};

class DPSDK_API GetChnDiagnoseDateMsg : public DPSDKCBMessage
{
public:
	GetChnDiagnoseDateMsg();
	virtual ~GetChnDiagnoseDateMsg() {}

public:
	int								session;
	int								startIndex;
	int								count;

	std::vector<DiagnoseChnList>	vecChnList;
};

class DPSDK_API StopChnDiagnoseMsg : public DPSDKCBMessage
{
public:
	StopChnDiagnoseMsg();
	virtual ~StopChnDiagnoseMsg(void) {}

public: 
	int					session;
}; 

class DPSDK_API IDPSDKDiagnose : public IDPSDKFuncBase
{
public:
	/** 查询组织节点诊断项异常数量
		@param const char* orgCode	组织结构编号
		@return
	*/
	virtual int QueryOrgDiagnoseCount(const char* orgCode) = 0;

	/** 通过session获取诊断内容		
		@param int nSession			查询id
		@param int nStartIndex		起始编号
		@param int nCount			查询数量
		@return
	*/
	virtual int GetDiagnoseDateBySession(int nSession, int nStartIndex, int nCount) = 0;

	/**	停止获取诊断内容
		@param int nSession			查询id
		@return
	*/
	virtual int StopGetDiagnoseDate(int nSession) = 0;

	/**	查询通道最近一次质量诊断结果
		@param const char* orgCode  组织结构编号
		@return
	*/
	virtual int QueryChnListDiagnoseDate(const char* orgCode) = 0;

	/** 查询通道历史质量诊断数
		@param const char* cameraId	设备id
		@param int64_t begintime	开始时间
		@param int64_t endtime		结束时间
		@return
	*/
	virtual int QueryChnDiagnoseCount(const char* cameraId, int64_t begintime = 0, int64_t endtime = 0 ) = 0;

	/** 获取通道历史质量诊断数据
		@param int nSession			查询id
		@param int nStartIndex		起始编号
		@param int nCount			查询数量
		@return
	*/
	virtual int GetChnDiagnoseDate(int nSession, int nStartIndex, int nCount) = 0;

	/** 停止获取通道质量诊断内容
		@param int nSession			查询id
	*/
	virtual int StopChnDiagnoseDate(int nSession) = 0;
};

END_NAMESPACE_DPSDK

#endif

