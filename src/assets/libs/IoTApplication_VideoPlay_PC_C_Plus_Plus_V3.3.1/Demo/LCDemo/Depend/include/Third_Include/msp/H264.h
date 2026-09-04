#pragma once

#include <list>
#include "h264_api.h"
#include "media_rtp_packet_i.h"

#ifndef UINT
#define UINT unsigned int
#endif

#ifndef BYTE
#define BYTE unsigned char
#endif

#ifndef PBYTE
#define PBYTE BYTE *
#endif

#ifdef WIN32
class H264Encoder
{
public:
	H264Encoder(int width, int height, int i_key_interval = 50, int i_framerate = 25);
	virtual ~H264Encoder();

	// 编码函数，返回编码后数据，返回NULL表示编码失败
	char *EncodeFromRgb24(char *pData, enc_stat_t &stat);
	int GetWidth() const;
	int GetHeight() const;

private:
	int m_width;
	int m_height;
	char *m_pYuvBuff;
	char *m_pBuffer;
	void *m_hEncoder;
};
#endif


// H264 RTP打包类
class H264RtpPacker
{
public:
	H264RtpPacker(int nSamplingRate = 90000, int nPacketLength = 1400);
	virtual ~H264RtpPacker();

	int InputData(PBYTE pBuff, const enc_stat_t &stat, time_t nTimeStamp);
	void clear();

	// 获取RTP 数据包，返回的CRTPPacket 对象由外部控制delete, 循环获取后，须使用clear清理队列
	mediaRtpPacketI *GetFirstRtpInfo();
	mediaRtpPacketI *GetNextRtpInfo();

protected:
	int decode_nal_unit(PBYTE pBuff, int nLen);

protected:
	int m_nPacketLength;
	std::list<mediaRtpPacketI *> m_rtpList;
	std::list<mediaRtpPacketI *>::iterator m_itRtp;

	int m_nSamplingRate;
	unsigned int m_timeStamp;
	unsigned short m_nSeq;

private:
	H264RtpPacker(const H264RtpPacker &other);
	void operator=(const H264RtpPacker &other);
};


#ifdef WIN32

inline int H264Encoder::GetWidth() const
{
	return m_width;
}

inline int H264Encoder::GetHeight() const
{
	return m_height;
}

#endif
