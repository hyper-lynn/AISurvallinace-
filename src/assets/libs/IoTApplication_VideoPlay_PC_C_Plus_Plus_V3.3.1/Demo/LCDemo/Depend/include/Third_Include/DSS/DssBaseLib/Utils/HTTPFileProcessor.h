/*
* Copyright (c) 2008, 浙江大华
* All rights reserved.
*
* 文件名称：HTTPFileProcessor.h
* 文件标识：
* 摘　　要：处理HTTP文件下载、上传
*

* 当前版本：1.0
* 原作者　：高圩
* 完成日期：2009年1月4日
* 修订记录：创建
*/
#ifndef _HTTP_FILE_PROCESSOR_H_
#define _HTTP_FILE_PROCESSOR_H_

#include <map>
#include "Utils/ThreadBase.h"
#include "AX_API/AX_Mutex.h"
#include "TPLayer/TPTCPClient.h"
#include "Utils/HTTPStreamParser.h"

typedef std::map<int, HTTPCommon*> HttpPduMap;
typedef std::map<int, char*> HttpBufMap;

enum EnumHttpFileResult
{
	//下载调用直接应答的结果
	Http_File_Invalid_Url = -1,
	Http_File_Connect_Failed = -2,
	Http_File_Send_Failed = -3,
	Http_File_Other_Server = -4,   //已经连接了一个服务，此次请求不是同一个服务器，此时可以创建另一个HTTPFileProcessor对象来使用
	Http_File_OpenFile_Failed = -5,
	Http_File_ReadFile_Failed = -6,

	//下载调用异步应答的结果
	Http_File_Ack_Failed = 1,  //HTTP应答失败
	Http_File_Disconnect,	   //HTTP连接断开
	Http_File_Timeout,         //HTTP超时
};

class DOAX_DEPRECATED IHTTPFileListener
{
public:
	virtual ~IHTTPFileListener() {}

	//每接收到一段数据，就回调给上层
	virtual int onHttpFileData(int id, int sequence, char* buf, int len, int totallen) = 0;

	//文件接收成功
	virtual int onHttpFileSuccess(int id, int sequence) = 0;

	//文件接收失败，失败结果参见EnumHttpFileResult的异步结果部分
	virtual int onHttpFileError(int id, int sequence, EnumHttpFileResult result) = 0;
};

class DOAX_DEPRECATED HTTPFileProcessor
	: public ThreadBase, public IHTTPStreamListener, public ITPListener
{
public:
	//startThread，1：启动线程；0：不启动
	HTTPFileProcessor(int id, IHTTPFileListener* listener, int startThread = 1);
	virtual ~HTTPFileProcessor(void);

	//<0 失败，具体见EnumHttpFileResult直接返回的结果，
	//>=0 成功返回下载序号，数据回调时，以此序号来区分
	int downloadFile(const char* url);

	//<0 失败，具体见EnumHttpFileResult直接返回的结果，
	// >=0 成功，返回上载序号，成功回调时，以此序号来区分
	int uploadFile(const char* url, const char* filename);

	//在不启动线程地情况下，上层必须自行调用来接收数据
	int heartbeat(void);

protected: //线程执行体
	virtual int run();

protected: //网络回调
	virtual int onData(int engineId, int connId, const char* data, int len);
	virtual int onClose(int engineId, int connId);
	virtual int onConnect(int engineId, int connId, const char* ip, int port);	
	virtual int onSendDataAck(int engineId, int connId, int id, int sendLen);
	virtual int onSendStatus(int engineId, int connId, int statusType, int param);
	virtual int onTimeout(int id, int context);

protected: //解析回调
	virtual int onHttpParserData(int id, int sequence, char* buf, int len, int totallen);
	virtual int onHttpParserComplete(int id, int sequence, int result);

private:
	int getSequence(void);
	int sendPacket(HTTPCommon* http);
	int sendBuffer(char* buf, int len);

	//从URL解析IP和端口
	int parseIpAndPortFromUrl(const char* url, char* ip, int &port);
	int checkHttpServer(const char* ip, int port);

private:
	HTTPStreamParser   _httpParser;
	IHTTPFileListener* _listener;

	int			_id;
	int			_startThread;

	ITPObject*  _tpObj;   //网络传输对象
	char		_remoteIp[32];
	int			_remotePort;
	
	int			_sequence; //生成请求顺序号
	AX_Mutex	_mtxSeq;

	HttpPduMap	_sendingPdus; //正在发送的PDU
	AX_Mutex	_mtxSending;

	int		    _isConnected;
	AX_Mutex	_mtxStatus;

	HttpBufMap	_uploadBufs; //上载文件的缓冲
};

#endif
