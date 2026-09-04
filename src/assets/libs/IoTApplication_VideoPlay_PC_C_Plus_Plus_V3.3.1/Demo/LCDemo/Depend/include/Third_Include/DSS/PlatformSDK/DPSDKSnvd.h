/**
 * Copyright (c) 2012, 浙江大华
 * All rights reserved.
 *
 * 文件名称：
 * 文件标识：
 * 摘　　要：Platform SDK的接口文件,SNVD子模块
 *
 * 当前版本：1.0
 * 原作者　：15693
 * 完成日期：2013年6月27日
 * 修订记录：创建
 */

#ifndef INCLUDED_DPSDK_DPSDKSNVD_H
#define INCLUDED_DPSDK_DPSDKSNVD_H

#include "DPSDK.h"

BEGIN_NAMESPACE_DPSDK
//////////////////////////////////////////////////////////////////////////

struct DPSDK_API screenPosition  
{
	float left;
	float top;
	float width;
	float height;
	screenPosition()
	{
		left=0;
		top=0;
		width=0;
		height=0;
	}
};

class DPSDK_API RegisterToCmsMsg : public DPSDKCBMessage
{
public:
	RegisterToCmsMsg(void);
	virtual ~RegisterToCmsMsg(void){}

	uint32_t		unitId;									// ID
	char			ip[DPSDK_IP_LEN];						// IP
	int				port;									// 端口号
};

class DPSDK_API SnvdCmsCloseMsg : public DPSDKCBMessage
{
public:
	SnvdCmsCloseMsg(void);
	virtual ~SnvdCmsCloseMsg(void){}
};

class DPSDK_API MatrixControlMsg : public DPSDKCBMessage
{
public:
	MatrixControlMsg(void);
	virtual ~MatrixControlMsg(void);

	uint32_t		nClientId;								// 用户ID。							
	char            szMatrixId[DPSDK_MATRIXID_LEN];			// 矩阵服务器ID
	int				nControlType;							// 控制类型
															// 0: 计划任务;1: 手动单屏上墙;2: 关闭单屏;3: 画面分割
	int				nTvIndex;								// 关闭单屏 和画面分割时用到
	int				nSubTvIndex;							// 预留 将来对单个分割屏操作时使用
	int				nSplitNum;								// 分屏数
	screenPosition	stuPos;									// 即时上墙的窗口位置
	int             nTvType;								// 0: 非融合屏;1: 融合屏

	char*			pData;									// 任务数据
	uint32_t		nLen;									// 任务数据长度
};

class DPSDK_API MatrixPlaybackControlMsg : public DPSDKCBMessage
{
public:
	MatrixPlaybackControlMsg(void);
	virtual ~MatrixPlaybackControlMsg(void);

	float			fSpeed;									//速度
	int				nPort;									//回放端口
};
//////////////////////////////////////////////////////////////////////////

class DPSDK_API IDPSDKSnvd : public IDPSDKFuncBase
{
public:
	/** 注册到CMS
		@param const char* remoteIp							服务IP
		@param int remotePort								服务端口
		@param uint32_t nUnitId								服务ID				
	    @return												
	*/
	virtual int RegisterToCms(const char* remoteIp, int remotePort, uint32_t nUnitId) = 0;

protected:
	virtual ~IDPSDKSnvd(void){}
};
//////////////////////////////////////////////////////////////////////////

END_NAMESPACE_DPSDK

#endif

