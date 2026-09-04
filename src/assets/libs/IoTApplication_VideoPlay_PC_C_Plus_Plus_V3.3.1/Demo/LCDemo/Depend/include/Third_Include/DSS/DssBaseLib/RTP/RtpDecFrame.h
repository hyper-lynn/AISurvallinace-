#ifndef DH_RTP_DEV_FRAME_H_INCLUDED
#define DH_RTP_DEV_FRAME_H_INCLUDED

#include "AX_API/platform.h"
// #include "libRtpLog.h"

/*
_allBuffer:
                          |___________ |______________________________________|
_outHeader:
                          |___________ |
_buffer:
                                                |______________________________________| 

*/


class CRtpDecFrame
{
public:
	CRtpDecFrame(int32 outerHeaderLen=0);
	virtual ~CRtpDecFrame();
private:
	CRtpDecFrame(const CRtpDecFrame& frame);
	CRtpDecFrame& operator=(const CRtpDecFrame& frame);
	
public:
	uint32 getTimeStamp();
	uint64 getTimeUs();
	char* getFrameBuffer();
	int32 getFrameLength();
	char* getOutHeader();
	int32 getOutHeaderLen();

	void setTimeStamp(uint32 timeStamp);
	void setTimeUs(uint64 timeUs);
	bool pushData(const char* data, const int32 length);

	bool allocBuffer(const int32 capacity);
    bool reset();
protected:
	uint32 _timestamp;  // RTP包中的timestamp，
	uint64 _timeUs;    // 单位为微秒，第一个包为0，依次递增。
	int32 _length;		//帧的数据的长度
	char *  _buffer;    //存放帧数据的buffer
	int32 _capacity;    //存放帧数据的空间的最大容量
	char* _outHeader;      //用来存放外部自己加的封装头数据的buffer
	int32 _outHeaderLen;   //存放外部头数据的开始buffer
	char* _allBuffer;   //CRtpDecFrame类new出的buffer的开始位置
};

#endif//DH_RTP_DEV_FRAME_H_INCLUDED
