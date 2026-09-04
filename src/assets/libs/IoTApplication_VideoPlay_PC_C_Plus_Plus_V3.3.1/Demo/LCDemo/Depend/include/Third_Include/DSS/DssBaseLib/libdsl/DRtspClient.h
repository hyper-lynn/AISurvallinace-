/* Copyright (c) 2011, 浙江大华技术股份有限公司, All rights reserved.
 * 2012-12
 *
 * DRtspClient.h : Rtsp客户端库
 */

#ifndef INCLUDED_LIBDSL_DHRTSPCLIENT_H
#define INCLUDED_LIBDSL_DHRTSPCLIENT_H

#include <libdsl/DHttpClient.h>

BEGIN_NAMESPACE_DSL
/////////////////////////////////////////////////

class DRtp;
class DRtspClient;
class DRtspSession;

enum emTransport
{
	TRANS_UNKNOWN = 0,
	TRANS_DH_RTP_TCP,	// 0x24($) + 交织通道(interleaved)1字节 + 2字节长度信息 + RTP头 + 大华帧的分包数据
	TRANS_DH_AVP_TCP,	// 0x24($) + 交织通道(interleaved)1字节 + 4字节长度信息 + 完整大华帧
};

class LIBDSL_API DRtspStreamHandler : public DRefObj
{
public:
	DRtspStreamHandler(emTransport em = TRANS_DH_RTP_TCP);

	// 返回0：当前无数据；1：已缓存部分数据，等待接收新数据
	virtual int getStatus(); 
	// 返回0：数据长度不足以解析；-1：处理出错；>0：拷贝长度 
	virtual int onData(const char* pBuffer, int len);
	virtual void onRTPPacket(const DRef< DRtp > rtp) = 0;	// TRANS_DH_RTP_TCP
	virtual void onDHAV(const char* pDHAV, int len) = 0;	// TRANS_DH_AVP_TCP

protected:
	virtual ~DRtspStreamHandler();

private:
	emTransport m_trans;

	char* m_buffer;
	int m_bufLen;
	unsigned int m_PacketLen;
	DRef< DRtp > m_rtp;
};

class LIBDSL_API DRtspSession : public DHttpSession
{
public:
	DRtspSession();

	void SetStreamHandler( const DRef< DRtspStreamHandler > & handler );

protected:
	virtual ~DRtspSession();

	virtual void OnData( SOCKID hSocket, const char * pBuffer, int len, const char* remoteAddr, int remotePort );

	void onRtsp();

protected:
	friend class DRtspClient;

	char m_buffer[32*1024];
	int m_bufLen;

	DRef< DRtspStreamHandler > m_streamHandler;
};

class LIBDSL_API DRtspClient
{
public:
	DRtspClient( DNetEngine * ne );
	virtual ~DRtspClient(void);

	DRef<DRtspSession> Connect( const char * ip, int port, const DRef<DHttpHandler> & handler = 0 );

protected:
	DNetEngine * m_neteng;
};

/////////////////////////////////////////////////
END_NAMESPACE_DSL

#endif // INCLUDED_LIBDSL_DHRTSPCLIENT_H
