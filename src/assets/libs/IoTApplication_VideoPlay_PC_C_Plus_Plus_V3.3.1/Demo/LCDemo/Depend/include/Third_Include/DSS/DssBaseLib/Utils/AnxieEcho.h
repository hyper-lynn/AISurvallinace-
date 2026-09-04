
/*
* Copyright (c) 2008, 杭州安谐软件有限公司
* All rights reserved.
*
* 文件名称：AnxieEcho.h
* 文件标识：
* 摘　　要：网络状况检测工具类(类似于ping) .h文件
			工作原理为通过定时发送UDP包模拟固定大小的echo包，计算收到响应的延时
			包的发送方向为client->server->client， server不主动发包。

* 当前版本：1.0
* 原作者　：林坚彦
* 完成日期：2008年9月23日
* 修订记录：创建
*/

#ifndef ANXIEECHO_H_INCLUDE
#define ANXIEECHO_H_INCLUDE

#include <map>
#include <list>
#include "TPLayer/ITPObject.h"

#define ANXIE_ECHO_PACKET_LEN	32	//固定为32字节大小的包，格式为["AnxieEcho"][seq]......
#define ANXIE_ECHO_TCP_BUFFER_LEN	(ANXIE_ECHO_PACKET_LEN*50)	//tcp缓存大小
#define ANXIE_ECHO_HEAD		"AnxieEcho"

typedef struct Tcp_Buffer 
{
	char buf[ANXIE_ECHO_TCP_BUFFER_LEN];	//tcp缓存
	int  writePos;
	int  readPos;
}Tcp_Buffer_t;
typedef std::map<int, Tcp_Buffer_t> TcpBufMap;
typedef std::map<int, char*> PacketMap;
typedef std::list<char*> PacketList;

class IAnxieEchoListener;
class CAnxieEcho : public ITPListener
{
//constructor & destructor
public:
	//engineId:存在多个CAnxieEcho对象时可用其作对象标识, mode:1-client; 2-server, protocol:1-udp; 2-tcp
	CAnxieEcho(int engineId, int mode, int protocol = 1);
	virtual ~CAnxieEcho();

public:
	virtual int setListener(IAnxieEchoListener* listener);
	virtual int setDetectInterval(uint64 interval);	//设置探测频度，单位ms，不得小于1000，该值也为onReport所能上报的最大延时值。
	virtual int setLocalAddr(char* ip, int port);	//mode == 2(server)时必须调用此接口
	virtual int setDistAddr(char* ip, int port);	//mode == 1(client)时必须调用此接口

	virtual int heartbeat();	//如果return != 0，请稍加sleep再重新调用heartbeat，以免cpu空转

	virtual int SetSocketSelectTimeout(int sec, int usec);

//callbacks.
public:    
	virtual int onData(int engineId, int connId, const char* data, int len);
	virtual int onClose(int engineId, int connId);
	virtual int onConnect(int engineId, int connId, const char* ip, int port);
	virtual int onSendDataAck(int engineId, int connId, int id, int sendLen);
	virtual int onSendStatus(int engineId, int connId, int statusType, int param);
	virtual int onTimeout(int id, int context);

private:
	char* createPacket(void);
protected:
	ITPObject* _tpObject;
	IAnxieEchoListener* _listener;

	int _engineId;
	uint64	_detectInterval;
	int _workMode;
	int _protocol;

	uint64 _lastDetectTime;
	unsigned long _currentSeq;
	int _lastSeq;	//最近收到的seq。
	//char _packet[ANXIE_ECHO_PACKET_LEN];	//因数据流量很小，只需缓存一个包，无需保持一个队列。
	PacketMap  _sendingPackets; //正在发送的包
	PacketList _packetPool; //包缓存

	TcpBufMap _tcpBufs;	
};

class IAnxieEchoListener
{
public:    
	virtual ~IAnxieEchoListener() {}

	//latency: 网络时延
	virtual int onReport(int engineId, uint64 latency) = 0;
	virtual int onEchoClose(int engineId) { return 0; }
};

#endif // ANXIEECHO_H_INCLUDE
