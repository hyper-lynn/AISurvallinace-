#ifndef _DH_FRAME_H_
#define _DH_FRAME_H_

#include "DhDefine.h"
#include <list>

class DhFrame
{
public:
	static DhFrame *CreateFrame(uint8_t *pBuff, int32_t nLen);
	virtual ~DhFrame();	

	bool IsValid();
	bool ParseHeadExInfo();

	const DH_FRAME_HEAD_V06 &GetHead() const;	
	const DH_FRAME_TAIL_V06 &GetTail() const;

	uint8_t *GetFrame() const;
	int32_t GetFrameLength() const;	

	uint8_t *GetBody() const;
	int32_t GetBodyLength() const;	

	uint32_t GetFrameRate() const;
	uint32_t GetEncodeType() const;

	uint32_t GetWidth() const;
	uint32_t GetHeight() const;

	uint32_t GetAudioChannelNum() const;
	uint32_t GetAudioEncodeType() const;
	uint32_t GetAudioSampleRate() const;

	static uint32_t ConvertAudioSampleRate(uint32_t nSampleRate);
	static uint32_t ConvertAudioSampleRateFromDH(uint32_t nSampleRate);
	static uint32_t ConvertAudioSampleRateToDH(uint32_t nSampleRate);

private:
	DhFrame();
	void ParseHeadExInfo(uint8_t *pData, uint32_t nLen);

private:
	DH_FRAME_HEAD_V06 m_head;
	DH_FRAME_TAIL_V06 m_tail;

	uint8_t *m_pFrame;
	int32_t m_nFrameLen;

	uint8_t *m_pBody;
	int32_t m_nBodyLen;
	
	uint32_t m_nFrameRate;
	uint32_t m_nEncodeType;

	uint32_t m_nWidth;
	uint32_t m_nHeight;

	uint32_t m_nAudioChannelNum;
	uint32_t m_nAudioEncodeType;
	uint32_t m_nAudioSampleRate;
};

class DhStream
{
public:
	DhStream(uint32_t nInitSize = 10*1024, uint32_t nGrow = 4096);
	virtual ~DhStream();

	int Write(uint8_t *pBuff, int32_t nLen);
	int Read(std::list<DhFrame *> &frameList);
	//将H.264转化为大华码流。（大华码流就是在H.264基础上添加“大华头”）
	int PackDh(uint8_t *pBuf, int32_t nbuflen, uint32_t datatype, int32_t nwidth, int32_t nheight, uint8_t *pOutBuf, int32_t maxLen, int32_t *nOutLen);

protected:
	int32_t GetFreeLength() const;

private:
	uint8_t *m_pBuff;
	int32_t m_nLength;
	int32_t m_nGrow;
	int32_t m_nWritePos;

	uint32_t m_nFrameId;	//帧号自增
};

#include "DhFrame.inl"

#endif

