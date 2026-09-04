/*
* Copyright (c) 2007, 浙江大华技术股份有限公司
* All rights reserved.
*
* 文件名称：CRTCPSession.h
* 文件标识：参见配置管理计划书
* 摘　　要：RTP基本会话类。这是RTP会话的最上层类，实现RTP会话，封装了RTCP会话，自动完成。发送方支持缓冲。
*
*/

#ifndef __FE_RTP_SESSION_H__
#define __FE_RTP_SESSION_H__

#include <map>
#include <vector>
#include <deque>

#include "TPLayer/ITPListener.h"
#include "RTP/RTPProtocol.h"
#include "RTP/CRTPPacket.h"
#include "RTP/CRTCPPacket.h"
#include <RTP/FIFOBuffer.h>

#include <TPLayer/TPTCPClient.h>
#include <TPLayer/TPTCPServer.h>
#include <TPLayer/TPUDPClient.h>
#include <TPLayer/TPUDPServer.h>
#include <TPLayer/ThreadMutex.h>

#define R_RTP_ID	100
#define R_RTCP_ID	101
#define L_RTP_ID	102
#define L_RTCP_ID	103

#define RTP_EXTENSION_PACKET_LENGTH	1

//using namespace std;
typedef std::map<unsigned int, CRTPPacket*> RTPMap;
typedef std::map<unsigned int, CRTPPacket*>::value_type rtpmap_pair;
typedef RTPMap::iterator RTPMapIterator;

//typedef std::map<unsigned int, RTPMap*> JitterMap;
typedef std::deque<CRTPPacket*> BufferQueue;


#define PACKET_NUM	100

class CRTPServerBase;
class CWin32RTPServer;
class CLinuxRTPServer;

class CRTPSession : public ITPListener
{
public:
	friend class CRTPServerBase;
	friend class CWin32RTPServer;
	friend class CLinuxRTPServer;


	/* type用于设置RTP会话的类型，0：RTP over UDP，1：RTP over TCP，2：RTP over RTSP */
	CRTPSession(int id, Model model, int type = 0);
	CRTPSession(int id, Model model, CNewMutex* mutex, int type = 0);
	CRTPSession();
	virtual ~CRTPSession();

	/* 在会话为RTP over RTSP的模式下需要设置RTSP的连接。此连接只在type为2时有效 */
	void setRTSPConnection(ITPObject* rtsp);
	
	/* 用于设定初始时间戳,一般不用设,从0开始. */
	void setTimestamp(unsigned long time);

	/* 用于设置图像速率,用于自动生成时间戳. */
	void setRate(int rate);

	/* size,单位为字节,一般为K的整数倍.本方法用于调整UDP发送效率,UDP的包为设置后的大小*/
	void setPacketSize(int size);

	/* 设置负载类型 */
	void setPayload(int payload);

	/* 设置是否启用RTCP,enable, 1:启用,2不启用*/
	void setRTCPStatus(int enable);

	/* 读取RTCP是否启用状态 */
	int getRTCPStatus(void);

	/* 设置SSRC, 4字节长 */
	void setSSRC(unsigned long ssrc);

	/* 获取SSRC值 */
	unsigned long getSSRC(void);

	/* 设置RTCP发送间隔(由于使用情形限定,我们不使用动态间隔),单位是秒 */
	void setRTCPInterval(int interval);

	/* 如果是发送方,需要指定服务器的地址,地址是RTP地址,RTCP端口号自动加1 */
	int setDistAddress(char* ip, int port);

	/* 发送方也需要指定发送时的地址和端口,端口是包含RTCP的,为RTP端口加1 */
	int setLocalAddress(char*ip, int port);

	/* 如果是接收方,需要指定自身监听的地址和端口,RTCP端口号自动加1 */
	int setListenAddress(char* ip, int port);

	/*本接口仅可在ＲＴＰ侦听方想要复用对端的ＲＴＰ连接时调用，不可在其他情况下单独调用*/
	int setDistRTPAddress(char* ip, int port);
	/*本接口仅可在ＲＴＰ侦听方想要复用对端的ＲＴＣＰ连接时调用，不可在其他情况下单独调用*/
	int setDistRTCPAddress(char* ip, int port);

	/* 无论是发送方还是接收方,如果需要做流控,都需要监听RTCP报文 */
	int addRTCPListener(IRTCPListener* listener);

	int addRTPListener(IRTPListener* listener);

	/* 设置时间戳的增长幅度，1 by 帧率，0 by step, >1 按值增长*/
	int setTimestampStep(int type);

	/* 以帧为单位发送数据,底层会自动分包并置帧标志位. RTCP报文自动统计并发送
	type 1:I帧，2:P帧，3:B帧*/
	int sendFrame(int type, char* data, int len);

	/* 不按帧发送数据,即发送蒙包 */
	int sendData(char* data, int len);

	/* 用于发送RTP包。RTP分组由应用层生成，下层只负责发送，不负责打包工作。一般出现在转发的情况下。
	 * CRTPPacket对象可以使用指针的构造函数生成，可以避免内存拷贝。
	 */
	int sendPacket(CRTPPacket* packet);

	/* 将来要增加个发送RTCP报文的接口，有时候还是需要上层发送些RTCP报文的。 */

	/* 这个Buffer为RTP包的Buffer,size为帧的数量.会话层缓冲设定数量的帧数据,
	 * 用于解决重发问题.如果是蒙包,则size为蒙包的数量.???要考虑,I帧被分多包的情况
	 */
	void sendBufferSize(int size);

	/* 生命心跳 */
	int heartbeat(void);

	/* 重传某包请求，使用RTP中的sequence作为参数。重传需要对方库支持，一般RTP不支持重传。
	 * 不支持时此请求会被忽略。如果对端也使用本库则可以实现重传机制。本库支持最大缓冲300个
	 * UDP包的能力。
	 */
	int sendResendRequest(unsigned short sequence);

	void setResendPacket(int packets);

	//2007-09-07 李明江 增加底层缓冲控制接口

	//设置底层连接缓冲大小。type:1接收，2发送，size:缓冲区尺寸
	int setTPBufferSize(TPType type, int size);

	int getTPBufferSize(TPType type);

	//设置底层连接select超时值
	int setTPSelectTimeout(long sec, long usec);

	int DecTimestamp();

	uint64 SetSmoothInterval(int smoothInterval);

	//缓冲区管理接口，对抖动、重发等增加支持

	/* 得到发送队列，注意：调用此函数后，需要停止调用此会话任何发送接口，避免缓冲区的重入问题。
	 * 丢帧、丢包、等逻辑由应用层拿到队列后来做。（丢包会引发接收端发出重发指令，稍后要加强，增加
	 * 丢包的RTCP通知，解决重发的问题）
	 * 该接口目前不可用 -by林坚彦
	 */
	BufferQueue* getSendQueue();


	CRTPPacket* createPacket();
	CRTPPacket* createPacket(CRTPPacket* packet);

	int closeListenSocket();
	int closeDistSocket();

	unsigned short getSequenceNum(void);

	int setMaxBufferLen(size_t len);

	void clearSendBuffer();
	void setUdpNotSendWhenBufFull(bool value);

public:
	virtual int onData(int engineId, int connId, const char* data, int len);
	virtual int onClose(int engineId, int connId);
	virtual int onConnect(int engineId, int connId, const char* ip, int port);
	virtual int onSendDataAck(int engineId, int connId, int id, int sendLen);
	virtual int onSendStatus(int engineId, int connId, int statusType, int param);
	virtual int onTimeout(int id, int context);
protected:
	CNewMutex* _mutex;
	BufferQueue _buffer;
	size_t		_maxBufferLen;

//	BufferQueue _packetPool;

	RTPMap _resendBuffer;
	RTPMap _ackBuffer;
	
	IRTCPListener* _rtcpListener;
	IRTPListener* _rtpListener;
	
	int _id;
	int _bufferSize;
	Model _model;
	int _supportResend;
	int _timestamp_step;
	struct timeval _timeout;
	int _bInit;
	unsigned short _resend_sequence;
	unsigned short _sequenceNum;

	ITPObject *_remoteRTPChannel;
	ITPObject *_remoteRTCPChannel;
	ITPObject *_localRTPChannel;
	ITPObject *_localRTCPChannel;

	ITPObject *_rtspConnection;

	int _rtpModel;
	unsigned long _timestamp;
	int _frames;
	char _localIp[64];
	int _localPort;
	char _remoteIp[64];
	int _remotePort;
	char _listenIp[64];
	int _listenPort;
	int _rate;
	int _packetSize;
	int _payload;
	int	_rtcpEnable;
	unsigned long _ssrc;
	uint64 _rtcpInterval;
	uint64 _rtcpTime;
	int _resendPackets;
	int _tpRcvBufferSize;
	int _tpSndBufferSize;

	int sendSRPackets();
	int sendRRPackets();

	virtual int onRTPPacketInside(int session, int connId, CRTPPacket* packet);
	virtual int onRTCPPacketInside(int session, int connId, CRTCPPacket* packet);

	int sendResendRequestInside(unsigned short sequence);
	void reset(void);

	int onDataInside(int engineId, int connId, const char* data, int len);
	
	unsigned long _rtcp_rec_fraction_lost;
	unsigned long _rtcp_rec_packet_lost;
	unsigned long _rtcp_snd_octet;
	unsigned long _rtcp_snd_packet;
	unsigned long _rtcp_hight_sequence;

	CRTPPacket* _rtpPacket;
	CRTCPPacket* _rtcpPacket;

// 	unsigned int _clientIp;
// 	unsigned short _clientPort;
	sockaddr_storage _clientIpAddr;
	socklen_t	_clientIpAddrLen;
	//when type = overTCP, should store connId
	int			_clientConnId;
	bool		_clientSendAble;

// 	unsigned int _clientRTCPIp;
// 	unsigned short _clientRTCPPort;

	sockaddr_storage _clientRTCPIpAddr;
	socklen_t	_clientRTCPIpAddrLen;

	uint64 _smoothInterval;
	uint64 _lastTime;

	//fd_set _readfds;
	//int _maxfd;

	int checkSeq_;

	//when type = overTCP, need tcp buffer
	CFIFOBuffer *_remoteRTPBuffer;
	CFIFOBuffer *_localRTPBuffer;

	bool	_udpNotSendWhenBufFull;
};
#endif

