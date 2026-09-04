/*
* Copyright (c) 2008, 浙江大华
* All rights reserved.
*
* 文件名称：HTTPStreamParser.h
* 文件标识：
* 摘　　要：处理HTTP数据流的解析
*

* 当前版本：1.0
* 原作者　：高圩
* 完成日期：2009年1月4日
* 修订记录：创建
*/
#ifndef _HTTP_STREAM_PARSER_H_
#define _HTTP_STREAM_PARSER_H_

#include "HTTP/DH_HTTP.h"

#define LEN_HTTP_PARSER_BUF		(64*1024)		//解析命令的缓冲区大小
#define LEN_HTTP_PARSER_BODY	(2*1024*1024)	//存放信令包体的缓冲大小，主要针对包体是二进制流

class IHTTPStreamListener;

class DOAX_DEPRECATED HTTPStreamParser
{
public:
	HTTPStreamParser(int id, IHTTPStreamListener* listener);
	virtual ~HTTPStreamParser(void);

	int parse(const char* data, int len);

	void reset(void);

protected:
	int parseInside(const char* data, int len);

protected:
	int				_id;

	IHTTPStreamListener* _listener;

	char			_buf[LEN_HTTP_PARSER_BUF];
	int				_dataLen;

	char*			_body;		//存放信令包体的缓冲，主要针对包体是二进制流，有需要的情况下才动态生成
	int				_bodyTotalLen; //存放包体地缓冲长度
	int				_bodyLen;   //包体缓冲里的数据长度

	//信令包体太大地情况下，一次无法接收完毕，所以暂时记下当前的PDU，以便下次接收的数据与之对应起来
	HTTPCommon*		_tmpPdu; 
};

class DOAX_DEPRECATED IHTTPStreamListener
{
public:
	virtual ~IHTTPStreamListener() {}
	//每接收到一段数据，就回调给上层
	virtual int onHttpParserData(int id, int sequence, char* buf, int len, int totallen) = 0;

	//数据接收结束，result表示HTTP应答结果，2XX表示成功
	virtual int onHttpParserComplete(int id, int sequence, int result) = 0;
};

#endif

