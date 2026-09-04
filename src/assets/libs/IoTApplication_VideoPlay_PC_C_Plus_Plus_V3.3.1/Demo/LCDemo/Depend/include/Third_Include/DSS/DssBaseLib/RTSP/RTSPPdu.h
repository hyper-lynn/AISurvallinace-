/*
* Copyright (c) 2007, 浙江大华技术股份有限公司
* All rights reserved.
*
* 文件名称：CRTSPPdu.h
* 文件标识：参见配置管理计划书
* 摘　　要：RTSP数据单元封装。RTSP是一个HTTP风格的流媒体协议，所以从本质上来说是一个HTTP协议，RTSP PDU也就是扩展的HTTP PDU。
			因为我们的HTTP处理库已经对RTSP做了支持，所以CRTSPPdu主要是由一个HTTPCommon对象组成。
			为了支持不同的业务扩展RTSP的需要，在CRTSPPdu中增加了原始流数据保存的功能，以便应用可以使用业务专用PDU类进行再次
			反序列化，以得到扩展的头域。（注：发送接口对扩展没有影响。）
*
* 当前版本：1.0
* 作　　者：李明江
* 完成日期：2007年7月20日
* 修订记录：稳定。

*
* 取代版本：0.1
* 原作者　：李明江
* 完成日期：2007年7月1日
* 修订记录：创建
*/
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RTSPPDU_H__C971B3E3_E0D3_486E_B5A6_AAF9B3259172__INCLUDED_)
#define AFX_RTSPPDU_H__C971B3E3_E0D3_486E_B5A6_AAF9B3259172__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <stddef.h>
#include "HTTP/DH_HTTP.h"
#include "AX_API/AX_IAddRefAble.h"

class CRTSPPdu : public AX_IAddRefAble
{
public:
	CRTSPPdu();
	virtual ~CRTSPPdu();

	HTTPCommon* getBody(void);

	int getType(void);	//Request or Response
	int getProtocol(void);	//SIP or HTTP

#if 0    // 这些数据应该没有用途
	void addOriData(char* data, int len);
	char* getOriData(void);
	int getOriDataLen();
#endif 

protected:
	HTTPCommon* _body;
//	char _oriData[3*1024];
//	int _len;
};

class CRTSPRequestPdu : public CRTSPPdu
{
public:
	CRTSPRequestPdu(HTTPCommon* body=NULL);
	virtual ~CRTSPRequestPdu();
};

class CRTSPResponsePdu : public CRTSPPdu
{
public:
	CRTSPResponsePdu(HTTPCommon* body=NULL);
	virtual ~CRTSPResponsePdu();
};


#endif // !defined(AFX_RTSPPDU_H__C971B3E3_E0D3_486E_B5A6_AAF9B3259172__INCLUDED_)
