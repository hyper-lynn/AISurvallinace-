/**
 * Copyright (c) 2012, 浙江大华
 * All rights reserved.
 *
 * 文件名称：
 * 文件标识：
 * 摘　　要：Platform SDK的接口文件,获取服务信息模块
 *
 * 当前版本：1.0
 * 原作者　：13031
 * 完成日期：2013年5月9日
 * 修订记录：创建
 */

#ifndef INCLUDED_DPSDK_DPSDKSERVERINFO_H
#define INCLUDED_DPSDK_DPSDKSERVERINFO_H

#include "DPSDK.h"

BEGIN_NAMESPACE_DPSDK
//////////////////////////////////////////////////////////////////////////

// 服务状态
typedef enum
{
	SERVER_STATUS_OK	= 0,										// 正常
	SERVER_STATUS_WARNING,											// 警告
	SERVER_STATUS_ERROR,											// 异常
}dpsdk_server_status_e;

// 服务类型----参照CFL_UNIT_TYPE
typedef enum
{
	SERVER_TYPE_UNKNOW	= 0,
	SERVER_TYPE_SS,
	SERVER_TYPE_MTS,
	SERVER_TYPE_CMS,
	SERVER_TYPE_DMS,
	SERVER_TYPE_VMS		= 6,

	SERVER_TYPE_PCS		= 12,
	SERVER_TYPE_PTS,

	SERVER_TYPE_ADS		= 16
}dpsdk_server_type_e;

// 服务列表信息
typedef struct DPSDK_API ServerInfo
{
	dpsdk_server_type_e		nType;									// 服务类型
	char					szCode[DPSDK_SERVERCODE_LEN];			// 服务编号
	dpsdk_server_status_e	nStatus;								// 服务状态
	char					szName[DPSDK_SERVER_NAME_LEN];			// 服务名称
	char					szOrgCode[DPSDK_SERVER_ORG_CODE_LEN];	// 服务所属组织结构的code
	char					szIp[DPSDK_IP_LEN];						// 服务IP
	uint32_t				nPort;									// 服务端口

	ServerInfo()
	{
		nType = SERVER_TYPE_UNKNOW;
		memset(szCode, 0, sizeof(szCode));
		nStatus = SERVER_STATUS_OK;
		memset(szName, 0, sizeof(szName));
		memset(szOrgCode, 0, sizeof(szOrgCode));
		memset(szIp, 0, sizeof(szIp));
		nPort = 0;
	}
}ServerInfo_t;

// 平台域列表信息
typedef struct DPSDK_API DomainInfo
{
	char					szDomainId[DPSDK_DOMAINID_LEN];			// 平台域ID
	dpsdk_server_status_e	nStatus;								// 平台状态

	DomainInfo()
	{
		memset(szDomainId, 0, sizeof(szDomainId));
		nStatus = SERVER_STATUS_OK;
	}
}DomainInfo_t;

// 查询服务列表回调消息（CMD=DPSDK_CMD_SERVER_INFO_QUERY_SERVER_LIST）
class DPSDK_API QueryServerListMsg : public DPSDKCBMessage
{
public:
	QueryServerListMsg(void);  
	virtual ~QueryServerListMsg(void);

public:
	// request
	char					szDomainId[DPSDK_DOMAINID_LEN];			// 平台域ID
	int						nLevel;									// 查询域的级数 0表示所有 目前只支持1

	enum{GOTO_CMS,GOTO_PCS};
	int						status;									// 串行获取服务列表

	// response
	char					szVersion[DPSDK_VERSION_LEN];			// 平台版本
	dpsdk_server_status_e	nStatus;								// 平台状态

	int32_t                 nServerCount;							// 服务个数
	ServerInfo_t*		    pServers;								// 服务信息

	int32_t					nDomainCount;							// 子域个数
	DomainInfo_t*			pDomains;								// 子域信息
};

// 查询服务信息回调基类消息
class DPSDK_API QueryServerInfoBaseMsg : public DPSDKCBMessage
{
public:
	QueryServerInfoBaseMsg(int cmd = DPSDK_CMD_UNKNOWN, int msgType = DPSDK_MSG_REQUEST);
	virtual ~QueryServerInfoBaseMsg(void){}

public:
	// request
	char					szCode[DPSDK_SERVERCODE_LEN];			// 服务编号
	char                    szDomainId[DPSDK_DOMAINID_LEN];			// 服务所在域
	dpsdk_server_type_e		enType;									// 服务类型

	// response
	dpsdk_server_status_e	nStatus;								// 服务状态
	char					szVersion[DPSDK_VERSION_LEN];			// 服务版本
	uint32_t				nCpu;									// cpu使用率 0~100
	uint32_t				nMemUsed;								// 进程虚拟内存使用 单位（KB） 
	uint64_t				nDiskUsed;								// 磁盘使用量 单位（KB）
	uint64_t				nDiskTotal;								// 磁盘总量 单位（KB）
};

// 查询CMS服务信息回调消息（CMD=DPSDK_CMD_SERVER_INFO_QUERY_CMS）
class DPSDK_API QueryCMSInfoMsg : public QueryServerInfoBaseMsg
{
public:
	QueryCMSInfoMsg(void);  
	virtual ~QueryCMSInfoMsg(void){}

public:
	int32_t					nActiveUsers;							// 用户连接数
};

// 查询DMS服务信息回调消息（CMD=DPSDK_CMD_SERVER_INFO_QUERY_DMS）
class DPSDK_API QueryDMSInfoMsg : public QueryServerInfoBaseMsg
{
public:
	QueryDMSInfoMsg(void);  
	virtual ~QueryDMSInfoMsg(void){}

public:
	int32_t					nActiveDevice;							// 在线设备数
	int32_t					nTotalDevice;							// 服务管理设备数
	int32_t					nActiveChannel;							// 在线通道数
	uint64_t				nAlarmTotal;							// 总报警数量
};

// 查询MTS服务信息回调消息（CMD=DPSDK_CMD_SERVER_INFO_QUERY_MTS）
class DPSDK_API QueryMTSInfoMsg : public QueryServerInfoBaseMsg
{
public:
	QueryMTSInfoMsg(void);  
	virtual ~QueryMTSInfoMsg(void){}

public:
	int32_t					nInput;									// 输入视频通道数
	int32_t					nOutput;								// 输出视频通道数

	uint64_t				nNetIn;									// 接收网络流量 单位（KB）
	uint64_t				nNetOut;								// 发送网络流量	单位（KB）
};

// 查询SS服务信息回调消息（CMD=DPSDK_CMD_SERVER_INFO_QUERY_SS）
class DPSDK_API QuerySSInfoMsg : public QueryServerInfoBaseMsg
{
public:
	QuerySSInfoMsg(void);  
	virtual ~QuerySSInfoMsg(void){}

public:
	int32_t					nInput;									// 输入录像路数
	int32_t					nStorage;								// 存储路数
	int32_t					nOutput;								// 回放路数

	uint64_t				nNetIn;									// 接收网络流量 单位（KB）
	uint64_t				nNetOut;								// 发送网络流量	单位（KB）

	uint64_t				nDiskIn;								// 总磁盘写流量 单位（KB）
	uint64_t				nDiskOut;								// 总磁盘读流量 单位（KB）

	uint64_t				nMDiskUsed;								// 已使用磁盘量 单位（KB）
	uint64_t				nMDiskTotal;							// 磁盘总量 单位（KB）
	uint64_t				nMDiskConsume;							// 使用状况(总的/已使用的)
};

// 查询VMS服务信息回调消息（CMD=DPSDK_CMD_SERVER_INFO_QUERY_VMS）
class DPSDK_API QueryVMSInfoMsg : public QueryServerInfoBaseMsg
{
public:
	QueryVMSInfoMsg(void);  
	virtual ~QueryVMSInfoMsg(void){}

public:
	int32_t					nActiveDevice;							// 在线设备数
	int32_t					nTotalDevice;							// 服务管理设备数
};

// 查询ADS服务信息回调消息（CMD=DPSDK_CMD_SERVER_INFO_QUERY_ADS）
class DPSDK_API QueryADSInfoMsg : public QueryServerInfoBaseMsg
{
public:
	QueryADSInfoMsg(void);  
	virtual ~QueryADSInfoMsg(void){}

public:
	uint64_t				nAlarmTotal;							// 总报警数量
};

// 查询PTS服务信息回调消息（CMD=DPSDK_CMD_SERVER_INFO_QUERY_PTS）
class DPSDK_API QueryPTSInfoMsg : public QueryServerInfoBaseMsg
{
public:
	QueryPTSInfoMsg(void);  
	virtual ~QueryPTSInfoMsg(void){}

public:
	int32_t					nActiveDevice;							// 在线设备数
	int32_t					nTotalDevice;							// 服务管理设备数
	int32_t					nActiveChannel;							// 在线通道数

	uint64_t				nInput;									// 图片接收总数
	uint64_t				nStorage;								// 图片存储总数
	uint64_t				nOutput;								// 图片发送总数

	uint64_t				nNetIn;									// 接收网络流量 单位（KB）
	uint64_t				nNetOut;								// 发送网络流量	单位（KB）

	uint64_t				nMDiskUsed;								// 已使用磁盘量 单位（KB）
	uint64_t				nMDiskTotal;							// 磁盘总量 单位（KB）
	uint64_t				nMDiskConsume;							// 使用状况(总的/已使用的)
};

// 查询PCS服务信息回调消息（CMD=DPSDK_CMD_SERVER_INFO_QUERY_PCS）
class DPSDK_API QueryPCSInfoMsg : public QueryServerInfoBaseMsg
{
public:
	QueryPCSInfoMsg(void);  
	virtual ~QueryPCSInfoMsg(void){}

public:
	int32_t					nActiveUsers;							// 用户连接数
};

// 服务重启回调消息（CMD=DPSDK_CMD_SERVER_INFO_RESTRART）
class DPSDK_API RestartServerMsg : public DPSDKCBMessage
{
public:
	RestartServerMsg(void);
	virtual ~RestartServerMsg(void){}

public:
	// request
	char					szCode[DPSDK_SERVERCODE_LEN];			// 服务编号
	char                    szDomainId[DPSDK_DOMAINID_LEN];			// 服务所在域
	dpsdk_server_type_e		enType;									// 服务类型
};

// 服务状态通知消息（CMD=DPSDK_CMD_SERVER_INFO_REPORT_STATUS）
class DPSDK_API ServerStatusNotifyMsg : public DPSDKCBMessage
{
public:
	ServerStatusNotifyMsg(void);
	virtual ~ServerStatusNotifyMsg(void);

public:
	char					szDomainId[DPSDK_DOMAINID_LEN];			// 平台域ID
	char					szVersion[DPSDK_VERSION_LEN];			// 平台版本
	dpsdk_server_status_e	nStatus;								// 平台状态

	int32_t                 nServerCount;							// 服务个数,目前只会等于1
	ServerInfo_t*			pServerInfo;							// 服务信息
};

//////////////////////////////////////////////////////////////////////////

class DPSDK_API IDPSDKServerInfo : public IDPSDKFuncBase
{
public:

	/** 获取服务列表
		@param const char* szDomainId						平台域ID（本级时填空，即""，其他接口类似）
		@param const int nLevel								查询域的级数 0表示所有 目前只支持1
		@return												异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int QueryServerList(const char* szDomainId, const int nLevel) = 0;

	/** 获取服务信息
		@param const char* szDomainId						服务所在域ID
		@param const char* szCode							服务编号
		@param dpsdk_server_type_e enType					服务类型
		@return												异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int QueryServerInfo(const char* szDomainId, const char* szCode, dpsdk_server_type_e enType) = 0;

	/** 服务重启
		@param const char* szDomainId						平台域ID
		@param const char* szCode							服务编号
		@param dpsdk_server_type_e enType					服务类型
		@return												异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int RestartServer(const char* szDomainId, const char* szCode, dpsdk_server_type_e enType) = 0;

protected:
	virtual ~IDPSDKServerInfo(void){}
};
//////////////////////////////////////////////////////////////////////////

END_NAMESPACE_DPSDK

#endif
