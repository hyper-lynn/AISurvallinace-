
#ifndef _DH_FRAME_INLINE_
#define _DH_FRAME_INLINE_

inline const DH_FRAME_HEAD_V06 &DhFrame::GetHead() const
{
	return m_head;
}

inline const DH_FRAME_TAIL_V06 &DhFrame::GetTail() const
{
	return m_tail;
}

inline uint8_t *DhFrame::GetBody() const
{
	return m_pBody;
}

inline int32_t DhFrame::GetBodyLength() const
{
	return m_nBodyLen;
}

inline uint8_t *DhFrame::GetFrame() const
{
	return m_pFrame;
}

inline int32_t DhFrame::GetFrameLength() const
{
	return m_nFrameLen;
}

inline uint32_t DhFrame::GetFrameRate() const
{
	return m_nFrameRate;
}

inline uint32_t DhFrame::GetEncodeType() const
{
	return m_nEncodeType;
}

inline uint32_t DhFrame::GetWidth() const
{
	return m_nWidth;
}

inline uint32_t DhFrame::GetHeight() const
{
	return m_nHeight;
}

inline uint32_t DhFrame::GetAudioChannelNum() const
{
	return m_nAudioChannelNum;
}
	
inline uint32_t DhFrame::GetAudioEncodeType() const
{
	return m_nAudioEncodeType;
}
	
inline uint32_t DhFrame::GetAudioSampleRate() const
{
	return m_nAudioSampleRate;
}

inline int32_t DhStream::GetFreeLength() const
{
	return m_nLength - m_nWritePos;
}

inline uint32_t DhFrame::ConvertAudioSampleRate(uint32_t nSampleRate)
{
	return ConvertAudioSampleRateFromDH(nSampleRate);
}

#endif
