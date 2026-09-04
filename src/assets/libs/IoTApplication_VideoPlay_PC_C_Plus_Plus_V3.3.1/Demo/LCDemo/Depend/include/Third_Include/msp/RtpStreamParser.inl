
#ifndef _RTP_STREAM_PARSER_INLINE_
#define _RTP_STREAM_PARSER_INLINE_

inline void RtpStreamParser::SetVideoRtpType(int type)
{
	m_videoRtpType = type;
}
	
inline int RtpStreamParser::GetVideoRtpType() const
{
	return m_videoRtpType;
}

inline void RtpStreamParser::SetAudioRtpType(int type)
{
	m_audioRtpType = type;
}
	
inline int RtpStreamParser::GetAudioRtpType() const
{
	return m_audioRtpType;
}

inline void RtpStreamParser::SetVideoStreamParseType(RtpStreamParseType type)
{
	m_videoParseType = type;
}

inline RtpStreamParseType RtpStreamParser::GetVideoStreamParseType() const
{
	return m_videoParseType;
}

inline void RtpStreamParser::SetAudioStreamParseType(RtpStreamParseType type)
{
	m_audioParseType = type;
}
	
inline RtpStreamParseType RtpStreamParser::GetAudioStreamParseType() const
{
	return m_audioParseType;
}

inline t_uint32 RtpStreamParser::GetFrameId()
{
	return m_frameId++;
}

#endif
