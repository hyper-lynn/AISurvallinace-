#ifndef _IBP_FRAME_H_
#define _IBP_FRAME_H_

#include "ibp_stream_define.h"
#include <list>

class DhFrame;
class IbpFrame
{
public:
	IbpFrame();
	IbpFrame(DhFrame* frame);
	virtual ~IbpFrame();

	uint8_t *GetFrame() const;
	int32_t GetFrameLength() const;

	uint32_t GetFrameType() const;
	uint32_t GetFrameRate() const;
	uint32_t GetEncodeType() const;

	uint32_t GetWidth() const;
	uint32_t GetHeight() const;

	uint32_t GetAudioChannelNum() const;
	uint32_t GetAudioEncodeType() const;
	uint32_t GetAudioSampleRate() const;
	int32_t  GetChannelId() const;
	uint32_t GetFrameIndex() const;

	int32_t  GetFrameTime(IBP_DATE_TIME& nTime);

private:
	DhFrame*  m_frame;
};

class DhStream;
class IbpStream
{
public:
	IbpStream(uint32_t nInitSize = 10*1024, uint32_t nGrow = 4096);
	virtual ~IbpStream();

	int Write(uint8_t *pBuff, int32_t nLen);
	int Read(std::list<IbpFrame *> &frameList);

	//将H.264转化为大华码流。（大华码流就是在H.264基础上添加“大华头”）
	int PackDh(uint8_t *pBuf, int32_t nbuflen, uint32_t datatype, int32_t nwidth,
		int32_t nheight, uint8_t *pOutBuf, int32_t maxLen, int32_t *nOutLen);

private:
	DhStream*  m_stream;
};

#endif
