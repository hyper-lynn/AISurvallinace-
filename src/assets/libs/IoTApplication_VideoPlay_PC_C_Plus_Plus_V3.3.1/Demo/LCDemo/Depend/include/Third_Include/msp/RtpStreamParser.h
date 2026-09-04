
#ifndef _RTP_STREAM_PARSER_H_
#define _RTP_STREAM_PARSER_H_

#include "StreamParser.h"

enum RtpStreamParseType
{
	STREAM_RAW,
	STREAM_ORG_H264,
	STREAM_RTP_H264,
	STREAM_ORG_G711A,
	STREAM_ORG_G711U,
};

class RtpPacketManager;

class RtpStreamParser : public StreamParser
{
public:
	RtpStreamParser();
	virtual ~RtpStreamParser();

	void SetVideoRtpType(int type);
	int GetVideoRtpType() const;

	void SetAudioRtpType(int type);
	int GetAudioRtpType() const;

	void SetVideoStreamParseType(RtpStreamParseType type);
	RtpStreamParseType GetVideoStreamParseType() const;

	void SetAudioStreamParseType(RtpStreamParseType type);
	RtpStreamParseType GetAudioStreamParseType() const;
	
	virtual int InputPacket(mediaPacketI *packet);
	virtual int InputData(t_int8 *pData, t_int32 nLen);
	virtual int GetMediaFrame(MediaFrame &frame);
	virtual void Clear();

	void setSPS(t_int8 *pBuff, t_int32 nLen);
	t_int8 *getSPS(t_int32 &nLen);

	void setPPS(t_int8 *pBuff, t_int32 nLen);
	t_int8 *getPPS(t_int32 &nLen);

protected:
	bool IsPacketOutofDate(mediaRtpPacketI *packet, std::map<t_uint32, RtpPacketManager *> &packetMap);
	int InputPacket(mediaRtpPacketI *packet, std::map<t_uint32, RtpPacketManager *> &packetMap, RtpStreamParseType parseType);

	int GetMediaFrame(std::map<t_uint32, RtpPacketManager *> &packetMap, MediaFrame &frame);

	t_uint32 GetFrameId();

private:
	int m_videoRtpType;
	RtpStreamParseType m_videoParseType;
	std::map<t_uint32, RtpPacketManager *> m_videoPacketMap;

	int m_audioRtpType;
	RtpStreamParseType m_audioParseType;
	std::map<t_uint32, RtpPacketManager *> m_audioPacketMap;

	t_uint32 m_frameId;

	t_int8  *m_pSPS;
	t_int32  m_nSPSLength;

	t_int8  *m_pPPS;
	t_int32  m_nPPSLength;
};

#include "RtpStreamParser.inl"

#endif
