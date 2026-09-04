/*
* Copyright (c) 2008,　杭州安谐软件有限公司
* All rights reserved.
*
* 文件名称：CRTSPBuffer.h
* 文件标识：
* 摘　　要：RTSP缓冲，当RTSP走TCP连接方式时，需要缓冲以防止数据过长被截断的情况。
*
* 当前版本：1.0
* 作　　者：林坚彦
* 完成日期：2008年7月20日
* 修订记录：创建
*/
//////////////////////////////////////////////////////////////////////

#if !defined(RTSP_BUFFER_INCLUDE)
#define RTSP_BUFFER_INCLUDE

#include "AX_API/AX_Mutex.h"

class CRTSPBuffer
{
public:
	CRTSPBuffer();
	virtual ~CRTSPBuffer();

	int	AddData(const char* data, int len);
	int DecData(int len);

	char*	getDataPtr();
	int		getDataLen();

public:
	//简单缓冲
	char*	_buffer;
	int		_size;
	int		_readPos;
	int		_writePos;
	AX_Mutex	_mutex;
};

#endif // !defined(RTSP_BUFFER_INCLUDE)

