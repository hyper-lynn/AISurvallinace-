/**
 * Copyright (c) 2012, 浙江大华
 * All rights reserved.
 *
 * 文件名称：
 * 文件标识：
 * 摘　　要：Platform SDK的接口文件,IVS-PC人流量统计子模块
 *
 * 当前版本：1.0
 * 原作者　：17286
 * 完成日期：2014年1月24日
 * 修订记录：创建
 */

#ifndef INCLUDED_DPSDK_DPSDKIVSPCSTAT_H
#define INCLUDED_DPSDK_DPSDKIVSPCSTAT_H

#include "DPSDK.h"
#include <string>

BEGIN_NAMESPACE_DPSDK
//////////////////////////////////////////////////////////////////////////

typedef struct DPSDK_API PeopleCount
{
	std::string	begin_time;
	std::string	end_time;
	int			count_in_ship;
	int			count_out_ship;
	std::string memo;
	std::string department_code;	//客户端收藏夹树的节点ID
}PeopleCount_t;

//上报人流量总数消息（CMD=DPSDK_CMD_REPORT_IVSPC_COUNT）
class DPSDK_API ReportPeopleCountMsg : public DPSDKCBMessage
{
public:
	ReportPeopleCountMsg(void);
	virtual ~ReportPeopleCountMsg(void);

public:
	char szBeginTime[DPSDK_IVSPC_DATATIME];					// 开始时间
	char szEndTime	[DPSDK_IVSPC_DATATIME];					// 结束时间
	char szDepCode	[DPSDK_IVSPC_DEPARTMENTCODE];			// 节点ID
	char szDepName	[DPSDK_IVSPC_DEPARTMENTNAME];			// 节点名称
	int	 nInPeopleCount;									// 总进入人流量
	int  nOutPeopleCount;									// 总出去人流量
};

//查询人流量总数消息（CMD=DPSDK_CMD_GET_IVSPC_COUNT）
class DPSDK_API GetPeopleCountMsg : public DPSDKCBMessage
{
public:
	GetPeopleCountMsg(void);
	virtual ~GetPeopleCountMsg(void);

public:
	char szBeginTime[DPSDK_IVSPC_DATATIME];					// 开始时间
	char szEndTime	[DPSDK_IVSPC_DATATIME];					// 结束时间

	int			   nDataNum;								// 查询回来的记录个数
	PeopleCount_t* pData;									// 查询回来的记录信息
};

class DPSDK_API IDPSDKIvspcStat : public IDPSDKFuncBase
{
public:
	/** 上报人流量
		@param 	const char* szBeginTime						统计开始时间
		@param  const char* szEndTime						统计结束时间
		@param  const char* szDepName						统计的节点名称
		@param  const char* szDepCode						统计的节点ID
		@param  int nPeopleCount							统计的进入人流量
		@param  int nPeopleCount							统计的出去人流量
		@return															
	*/
	virtual int ReportPeopleCount(const char* szBeginTime, const char* szEndTime, const char* szDepCode,
								const char* szDepName, int nInPeopleCount, int nOutPeopleCount) = 0;

	/** 查询历史人流量
		@param 	const char* szBeginTime						查询开始时间
		@param  const char* szEndTime						查询结束时间
		@return															
	*/
	virtual int GetPeopleCount(const char* szBeginTime, const char* szEndTime) = 0;

protected:
	virtual ~IDPSDKIvspcStat(void){}
};

//////////////////////////////////////////////////////////////////////////
END_NAMESPACE_DPSDK

#endif // INCLUDED_DPSDK_DPSDKIVSPCSTAT_H

