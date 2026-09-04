#pragma once

#include "media_packet_i.h"

class StreamPacker
{
public:
	StreamPacker();
	virtual ~StreamPacker();

	virtual int inputData(t_uint8 *pData, t_int32 nLen) = 0;
	virtual mediaPacketI *getMediaPacket();

protected:
	void inputPacket(mediaPacketI *packet);

private:
	std::list<mediaPacketI *> m_packetList;
};

class RtpPacker : public StreamPacker
{
public:
	RtpPacker(int nPayloadType = 96, int nMaxRtpLength = 1400);
	virtual ~RtpPacker();

	virtual int inputData(t_uint8 *pData, t_int32 nLen);

	t_int32 getPayloadType() const;
	t_int32 getMaxRtpLength() const;

protected:
	t_int32 getRtpSequence();
	t_int32 getRtpTimestamp();

private:
	const t_int32 m_nMaxRtpLength;
	const t_int32 m_nPayloadType;
	t_int32 m_rtpSequence;
	t_int32 m_rtpTimeStamp;
};

class DhStream;
class H264RtpPacker;

class DhNalPacker : public RtpPacker
{
public:
	DhNalPacker(int nPayloadType = 96, int nMaxRtpLength = 1400);
	virtual ~DhNalPacker();

	virtual int inputData(t_uint8 *pData, t_int32 nLen);

protected:
	void packetVideoFrame(t_uint8 *pData, t_int32 nLen);
	void packetAudioFrame(t_uint8 *pData, t_int32 nLen);

private:
	DhStream *m_pDhStream;
	H264RtpPacker *m_pH264Packer;
};

#include "StreamPacker.inl"