/*
* Copyright (c) 2009, 浙江大华
* All rights reserved.
*
* 文件名称：MyCOMListener.h
* 文件标识：
* 摘　　要：提供串口的读取、写入功能接口，由外部开启线程驱动
*

* 当前版本：1.0
* 原作者　：高圩
* 完成日期：2009年12月18日
* 修订记录：创建
*/
#ifndef _MY_COM_VISITOR_H_
#define _MY_COM_VISITOR_H_

#if defined(_WIN32) || defined(_WIN64)

#include "AX_API/platform.h"
#include "AX_API/winsock2i.h"

class DOAX_DEPRECATED CMyCOMVisitor
{
public:
	CMyCOMVisitor();
	~CMyCOMVisitor();

public:
	enum{
		FC_XONXOFF = 0x00,
		FC_DTRDSR  = 0x01,
		FC_RTSCTS  = 0x02,
	};

	enum{
		EVENTCHAR = 0x0d
	};

	enum{
		ASCII_XON  = 0x11,
		ASCII_XOFF = 0x13
	};

	struct COM_Info
	{
		int8   port;
		int8   byteSize;
		int8   stopBits;
		int8   parity;
		uint32 baudRate;
		int8   flowCtrl;
		char   evtChar;
		uint32 fBinary;
		COM_Info()
			: port(1)
			, byteSize(8)
			, stopBits(ONESTOPBIT)
			, parity(NOPARITY)
			, baudRate(9600)
			, flowCtrl(FC_XONXOFF)
			, evtChar(EVENTCHAR)
			, fBinary(1)
		{
		}
	};

public:
	int open(COM_Info& info);
	int close();

	//buf: 读取数据存放的缓冲
	//buflen: 缓冲总大小
	//返回值：读取的数据长度
	int read(char* buf, int buflen);

	//data：写入的数据缓冲
	//len：写入的数据长度
	//返回值：写入的数据长度
	int write(char* data, int len);

protected:
	HANDLE		_hSerialPort;	// 串口句柄
	OVERLAPPED	_rdos;
	OVERLAPPED  _wtos;
};

#endif // WIN32

#endif

