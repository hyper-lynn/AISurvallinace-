/* Copyright (c) 2013, 浙江大华技术股份有限公司, All rights reserved.
* 2013-10
*
* 版本    ：1.0
* ESBService.h : 网域总线处理模块
* 作者    ：吕少卿
* 完成日期：2014年9月29日
*
* 当前版本：1.0
*/

#pragma once

#include <libdsl/DHttpServer.h>
#include <libdsl/ESB/DMsgHandler.h>
#include <libdsl/ESB/DAutoPtr.h>
#include <libdsl/ESB/ISession.h>
#include <libdsl/ESB/DTrader.h>

BEGIN_NAMESPACE_DSL
BEGIN_NAMESPACE_ESB
/////////////////////////////////////////////////

class LIBDSL_API ESBService : public DMsgHandler, public DHttpHandler
{
public:
	ESBService();
	virtual ~ESBService();

	void SetTimeout(unsigned int nTime); // 单位为秒，默认30秒无包超时。

	// 设置Http消息接收超时时间，避免慢速HTTP拒绝服务漏洞，默认为200ms，0表示不超时
	// 此接口需要在AddHandler前调用
	void SetExpire( uint32_t ms );

private:
	//// DMsgHandler
	virtual int OnInitHandler(); 
	virtual int OnAntinitHandler();
	virtual int OnBusRunning();
	virtual void OnTimer( unsigned int nTimerId );
	//// DMsgHandler

	//// DHttpHandler
	virtual int OnConnect( const DRef<DHttpSession> & httpsess, const char * remote_ip, int remote_port );
	virtual int OnHttp( const DRef<DHttpSession> & httpsess, const DHttp & httpmsg  );
	virtual int OnClose( const DRef<DHttpSession> & httpsess );
	//// DHttpHandler

	DECLARE_FUNC_MAP(ESBService)

private:
	DRef<DHttpServerSession>				m_pHttpServer;
	ISession<int, DRef<DTrader> >			m_senTradersInt;
	unsigned int							m_nTime;
	unsigned int							m_nExpire;
};


/////////////////////////////////////////////////
END_NAMESPACE_ESB
END_NAMESPACE_DSL
