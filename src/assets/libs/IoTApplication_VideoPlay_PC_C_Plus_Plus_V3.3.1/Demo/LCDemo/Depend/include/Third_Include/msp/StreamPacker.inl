#pragma once

inline void StreamPacker::inputPacket(mediaPacketI *packet)
{
	m_packetList.push_back(packet);
}

inline t_int32 RtpPacker::getPayloadType() const
{
	return m_nPayloadType;
}
	
inline t_int32 RtpPacker::getMaxRtpLength() const
{
	return m_nMaxRtpLength;
}

inline t_int32 RtpPacker::getRtpSequence()
{
	return m_rtpSequence++;
}

inline t_int32 RtpPacker::getRtpTimestamp()
{
	return m_rtpTimeStamp++;
}