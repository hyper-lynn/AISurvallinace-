/*
* Copyright (c) 2008,　杭州安谐软件有限公司
* All rights reserved.
*
* 文件名称：CFIFOBuffer.h
* 文件标识：
* 摘　　要：FIFO缓冲，当RTP走over TCP连接方式时，需要缓冲以防止数据过长被截断的情况。
*
* 当前版本：1.0
* 作　　者：林坚彦
* 完成日期：2008年7月23日
* 修订记录：创建
*/
//////////////////////////////////////////////////////////////////////

#if !defined(FIFO_BUFFER_INCLUDE)
#define FIFO_BUFFER_INCLUDE

#include "AX_API/AX_Mutex.h"

//在路数很多的情况下，如果该缓冲太大，空间浪费太严重，gaowei 09-08-06
#define	FIFO_BUFFER_LENGTH	1024*256 //1024*1024*1	//默认1M

class CFIFOBuffer
{
public:
	CFIFOBuffer();
	virtual ~CFIFOBuffer();

	//返回实际缓冲的长度，add by gaowei 09-08-06
	int AppendData(const char* data, int len);

	int	AddData(const char* data, int len);
	int DecData(int len);

	char*	getDataPtr();
	int		getDataLen();

protected:
	//简单缓冲
	char	_buffer[FIFO_BUFFER_LENGTH];
	int		_readPos;
	int		_writePos;
	AX_Mutex	_mutex;
};

#endif // !defined(RTSP_BUFFER_INCLUDE)

