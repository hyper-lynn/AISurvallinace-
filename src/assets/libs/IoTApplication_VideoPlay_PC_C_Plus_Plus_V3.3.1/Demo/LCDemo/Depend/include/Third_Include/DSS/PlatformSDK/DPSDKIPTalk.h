/**
 * Copyright (c) 2014, 浙江大华
 * All rights reserved.
 *
 * 文件名称：
 * 文件标识：
 * 摘　　要：Platform SDK的接口文件,IP对讲接口（目前支持大华IP对讲）
 *
 * 当前版本：1.0
 * 原作者　：陈飞飞
 * 完成日期：2014年6月6日
 * 修订记录：创建
 */
#ifndef INCLUDED_DPSDK_DPSDKIPTALK_H
#define INCLUDED_DPSDK_DPSDKIPTALK_H


#include "DPSDK.h"
#include <libdsl/DStr.h>
#include <vector>

BEGIN_NAMESPACE_DPSDK
////////////////////////////////////////////////////
//IP对讲通用消息
class DPSDK_API IpTalkCommonMsg: public DPSDKCBMessage
{
public:
	IpTalkCommonMsg(int nCmd,int nMsgType);
	virtual ~IpTalkCommonMsg(void){}
public:
	char			m_serverId[SERVER_ID_LEN];		    //服务ID
	char			m_devId[DPSDK_DEV_ID_LEN];			//设备ID
	int				m_chnlNO;							//通道号
};

class DPSDK_API IpTalkInviteMsg : public IpTalkCommonMsg
{
public:
	IpTalkInviteMsg(void);
	virtual ~IpTalkInviteMsg(void){}
public:
	//char	m_devId [DPSDK_DEV_ID_LEN];			//设备ID
	//int		m_chnlNO;						//通道号
};

class DPSDK_API IpTalkHangUpMsg : public IpTalkCommonMsg
{
public:
	IpTalkHangUpMsg(void);
	virtual ~IpTalkHangUpMsg(void){}
public:
	//char	m_devId [DPSDK_DEV_ID_LEN];			//设备ID
	//int		m_chnlNO;						//通道号
};

class DPSDK_API IpTalkIgnoreInviteMsg : public IpTalkCommonMsg
{
public:
     IpTalkIgnoreInviteMsg(void);
	 virtual ~IpTalkIgnoreInviteMsg(void){}
};

////////////////////////////////////////////////////

class DPSDK_API IDPSDKIPTalk : public IDPSDKFuncBase
{
public:
	//添加接口

	/**主动挂断，拒绝对讲
	@param const char* szDevID			设备id
	@param int chnlNo					通道号
	*/
	virtual int HangUp(const char* szDevID, int chnlNo) = 0;

protected:
	virtual ~IDPSDKIPTalk(void){};
};
////////////////////////////////////////////////////

END_NAMESPACE_DPSDK
//#endif
#endif