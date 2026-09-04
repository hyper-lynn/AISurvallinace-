/*
* Copyright (c) 2007, 浙江大华技术股份有限公司
* All rights reserved.
*
* 文件名称：ITPObject.h
* 文件标识：参见配置管理计划书
* 摘　　要：传输层接口抽象类
*
* 当前版本：2.1
* 作    者：林坚彦
* 完成日期：2008年4月28日
* 修订记录：
	1. 优化server模式下的数据缓冲为QueueJitt
	2. 修改clientId的计算方法为句柄递增方式

* 当前版本：2.0
* 作    者：李明江
* 完成日期：2007年10月26日
* 修订记录：
	1. 数据缓冲区换成了queue。
	2. 连接队列改成了Hash_map
	3. 对RTP库提供了支持，增加了友元类定义，将sendInside改为基类方法。
	4. 修改了_sequence这个成员的名字

* 当前版本：1.0
* 作　　者：李明江
* 完成日期：2007年4月28日

*
* 取代版本：1.0
* 原作者　：
* 完成日期：
* 修订记录：
*/
#ifndef _ITPOBJECT_H_
#define _ITPOBJECT_H_

#include "TPTypedef.h"
#include "ITPListener.h"
#include <assert.h>
#include "ThreadMutex.h"
#include "DataRow.h"

#include "AX_API/AX_Atomic.h"

#include <queue>
#include <map>
#define  TP_SEND_BUF_LEN (64*1024)
#if defined(_WIN32) || defined(_WIN64)
#pragma   warning(disable   :   4996) 
#pragma   warning(disable   :   4786) 
#endif

typedef std::queue<DataRow*> Queue_List;

#if (defined(_WIN32 ) || defined(_WIN64)) && ! defined( __MINGW32__ )
#define _SILENCE_STDEXT_HASH_DEPRECATION_WARNINGS
#include <hash_map>
typedef stdext::hash_map<int, Queue_List*> Queue_Jitt;
typedef stdext::hash_map<unsigned int, client_list*> CONN_MAP;
#else

#ifdef ANDROID
#define _GLIBCXX_PERMIT_BACKWARD_HASH 1
#endif
#include <ext/hash_map>
typedef __gnu_cxx::hash_map<int, Queue_List*> Queue_Jitt;
typedef __gnu_cxx::hash_map<unsigned int, client_list*> CONN_MAP;
#endif

typedef std::map<int, int> Int_Map;

typedef std::map<int, tp_timer*> TIMER_MAP;

// BEGIN -- 跨平台相关的定义，使用者可以跳过
#ifdef _WIN32

#pragma warning( disable:4127 )

#define FDSET_NEW(pset, num) do { \
	char * buf = new char[ sizeof(u_int) + sizeof(u_int) + sizeof(SOCKET) * (num) ]; \
	*(u_int *)buf = (num); \
	(pset) = (fd_set *)( buf + sizeof(u_int) ); \
} while( 0 )
#define FDSET_ZERO( pset ) FD_ZERO( pset )
#define FDSET_CLR(fd, pset) FD_CLR(fd, pset)
#define FDSET_SET(fd, pset) do { \
	u_int __i; \
	for (__i = 0; __i < ((fd_set *)(pset))->fd_count; __i++) { \
	if (((fd_set *)(pset))->fd_array[__i] == (fd)) { \
	break; \
	} \
	} \
	if (__i == ((fd_set *)(pset))->fd_count) { \
	u_int max_num = *(u_int *)( ((char *)pset) - 4 ); \
	if (((fd_set *)(pset))->fd_count < max_num ) { \
	((fd_set *)(pset))->fd_array[__i] = (fd); \
	((fd_set *)(pset))->fd_count++; \
	} \
	} \
} while(0)
#define FDSET_ISSET(fd,pset)	FD_ISSET(fd,pset)
#define FDSET_DELETE(pset) do { \
	delete (((char *)pset) - sizeof(u_int)); \
} while( 0 )
#define FDSET_COPY(pset_d, pset_s) do { \
	if( *(u_int *)( ((char *)pset_d) - 4 ) < *(u_int *)( ((char *)pset_s) - 4 ) ) { \
	FDSET_DELETE( pset_d ); \
	FDSET_NEW( pset_d, *(u_int *)( ((char *)pset_s) - 4 ) ); \
	} \
	(pset_d)->fd_count = (pset_s)->fd_count; \
	memcpy( (pset_d)->fd_array, (pset_s)->fd_array, sizeof( (pset_d)->fd_array[0] ) * ( *(u_int *)( ((char *)pset_s) ) ) ); \
} while( 0 )

#else
#define FDSET_NEW(pset, num) do { \
	int byte_num = ((num) + 7) / 8; \
	char * buf = new char[ sizeof(int) + byte_num ]; \
	*(int *)buf = byte_num; \
	(pset) = (fd_set *)( buf + sizeof(int) ); \
} while( 0 )
#define FDSET_ZERO( pset ) do { \
	int byte_num = *(((int *)pset) - 1); \
	memset( (pset), 0, byte_num ); \
} while( 0 )
#define FDSET_CLR(fd, pset) FD_CLR(fd, pset)
#define FDSET_SET(fd, pset) FD_SET(fd, pset)
#define FDSET_ISSET(fd,pset)	FD_ISSET(fd, pset)
#define FDSET_DELETE(pset) do { \
	delete [] (((char *)pset) - sizeof(int)); \
} while( 0 )
#define FDSET_COPY(pset_d, pset_s) do { \
	if( *(((int *)pset_d) - 1) < *(((int *)pset_s) - 1) ) { \
	FDSET_DELETE( pset_d ); \
	FDSET_NEW( pset_d, *(((int *)pset_s) - 1) ); \
	} \
	memcpy( pset_d, pset_s, *(((int *)pset_s) - 1) ); \
} while( 0 )
#endif
// END -- 跨平台相关的定义，使用者可以跳过

class CRTPSession;
class CRTPServerBase;
class CLinuxRTPServer;

class ITPObject
{
public:   
	ITPObject(ITPListener* instance, int engineId = 0);

    virtual ~ITPObject();
	
	virtual int CloseClient(int id);

	virtual int Listen(char* ip, int port, bool enableReuseAddr = true);
	
	virtual int Connect(const char* ip, int port);

	virtual int Connect(const char* localIp, int localPort, const char* remoteIp, int remotePort);
    
    void SetListener(ITPListener* listener);
	
	virtual int Send(int id, char *pBuf, unsigned int iBufLen) = 0;
    
	virtual int Close(void);

    virtual int Heartbeat() = 0;
	virtual int HeartbeatWithoutSelect() = 0;

	friend class CRTPSession;
	friend class CRTPServerBase;
	friend class CLinuxRTPServer;
	//friend class CRTPAppSession
	friend class TPSelectBase;
public:

	//设置底层套接字缓冲区大小，type表示是发送缓冲区还是接收缓冲区
	int SetSocketBufferSize(TPType type, int size);

	//获取底层套接字缓冲区大小，type表示是发送缓冲区还是接收缓冲区
	int GetSocketBufferSize(TPType type);

	// 设置传输层调用select时的超时值。如果不赋值则默认设sec=0;usec=10;
	// 如果设置为0则表示为轮循状态
	// 各个子类的Heartbeat()和TCP的Connect中使用到select来控制等待时间
	int SetSelectTimeout(long sec, long usec);

	//设置传输层接收缓冲区大小，缓冲区由传输层自己维护，应用层仅指定大小
	int SetRecvTPBuffSize(int size);			

	//用于设置接收缓冲区，可以设定应用程序自己的接收缓冲区，传输层将数据直接接收在该区中。
	//传入的缓冲区要上层自行管理，下层不负责管理。
	int SetTPRecvBuffer(char* buff, int size);

	//使能nagle算法。1为打开，0为关闭
	int SetNodelayFlag(int flag);

	//设置缓冲长度回调的阀值，发送队列长度到达threshold的倍数时回调通知上层，threadhold=0禁用通知
	//回调的长度是当时发送队列的真实长度，并不一定是准确的threshold的倍数
	int SetSendQueueThreshold(int threshold);

	//获取发送缓冲队列
	//返回值是内部发送缓冲队列的指针，使用此接口应慎重
	//应与heartbeat()、senddata()等可能改变发送队列的接口互斥
	virtual Queue_List* GetSendQueue(int connId);


	// 一次性计时器构造方法
	//delay		开始延迟
	//context   上下文，ontimer时会回调该值
	//return	>=0时钟索引，可用于关闭时钟，<0失败
	long SchedureTimer(int delay, int context);

	//循环性计时器构造方法
	//interval	时钟周期，单位：毫秒
	//delay		开始延迟
	//context   上下文，ontimer时会回调该值
	//return	>=0时钟索引，可用于关闭时钟，<0失败
	long SchedureRepeatTimer(int interval, int delay, int context);

	//取消计时器 （一次性时钟回调一次后自动失效，循环性时钟也可通过timeout返回值来取消）
	//timerId		计时器索引
	//return		0成功，<0失败
	int CancelTimer(long timerId);

	virtual int clearSendBuffer();

	//设置缓存池的大小，根据需要进行调整
	//缓存池默认大小为10000
	int SetDataRowPoolSize(int size);

public:	

	//传输层初始化，在主程序入口
	static void Startup(void);
	static void Cleanup(void);
	static int sockaddr_aton( const char * host, int port, struct sockaddr * addr, socklen_t * len );
	static int sockaddr_ntoa( const struct sockaddr * addr, socklen_t len, char ret_addr[TP_NET_ADDR_LEN], int * ret_port );
	static int sockaddr_equal(struct sockaddr * srcAddr,struct sockaddr * dstAddr);

//	unsigned int	_ip;		// IP,PORT 都是网络字节序
	int				_socket;
	sockaddr_storage		_ipAddr;
	socklen_t		_ipAddrLen;
//	unsigned short	_port;

protected:

	int checkTimer();

	DataRow* createDataRow();
	
	virtual int sendInside(int id, char *pBuf, unsigned int iBufLen) = 0;	
	virtual int fillFds(int& maxfd, fd_set* readfds, fd_set* writefds);
	virtual int dealFDResult(int& fds,fd_set* readfds, fd_set* writefds,bool& fdsChange);

protected:
	static int GetNewClientId();
	static atomic_t _newClientId;  // 要求全局唯一，可以直接进行区分

	int getTimerId(void);
	int _newTimerId;  // 新增加的定时器，

	int getSequence(void);
	int	_sequenceNo;  // 发送的数据的序号，供外部处理onSendDataAck()时进行匹配

protected:
	//unsigned int	_localIp; //  todo 待删除
	sockaddr_storage	_localIpAddr;
	socklen_t		_localIpAddrLen;

	unsigned short	_localPort;// todo 待删除

	ITPListener*	_listener;
	CNewMutex*		_mutex;
	CONN_MAP		_clients;
	Queue_List		_queue;//for tcp_client&udp_both
	Queue_Jitt		_queueJitt;	//for tcp_server

	int				_engineId;  // 构造时设置，回调时提供，供外部区分不同的ITPObject对象
	
	int				_nodelay;
	
	int				_recvBuffSize;
	int				_sendBufferSize;	
	int				_tpRecvBuffSize;
	int				_localBuffer;

	struct timeval	_timeout;
	char*			_buffer;

	CDataRowPool	_dataRowPool;

	int				_sendQueueThreshold;
	int				_lastAnouncedThreshold;

	TIMER_MAP		_timerMap;

};

#endif


