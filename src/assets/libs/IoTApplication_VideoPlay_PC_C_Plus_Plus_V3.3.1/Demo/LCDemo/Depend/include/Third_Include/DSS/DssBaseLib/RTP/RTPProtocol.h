/*
* Copyright (c) 2007, 浙江大华技术股份有限公司
* All rights reserved.
*
* 文件名称：RTPProtocol.h
* 文件标识：参见配置管理计划书
* 摘　　要：RTP全局宏、预定义文件。
*
* 当前版本：1.0
* 作　　者：李明江
* 完成日期：2007年7月15日
* 修订记录：稳定，标准RTP及带重发的RTP会话都完成了。

*
* 取代版本：0.1
* 原作者　：李明江
* 完成日期：2007年7月1日
* 修订记录：创建
*/

#ifndef _RTP_PROTOCOL_H_
#define _RTP_PROTOCOL_H_

#if defined(_WIN32)||defined(WINCE)||defined(_WIN64)
	#include <AX_API/winsock2i.h>
#else
	#include<netinet/in.h>
#endif

#define MIN_HEAD_LENGTH		12
#define PROTOCOL_VERSION	2
#define RTP_BUFFER_SIZE		8*1024

enum Model
{
	SENDER = 1,
	RECEIVER
};

enum PayloadTypes 
{
	PCMU,         // G.711 u-Law
	FS1016,       // Federal Standard 1016 CELP
	G721,         // ADPCM - Subsumed by G.726
	G726 = G721,
	GSM,          // GSM 06.10
	G7231,        // G.723.1 at 6.3kbps or 5.3 kbps
	DVI4_8k,      // DVI4 at 8kHz sample rate
	DVI4_16k,     // DVI4 at 16kHz sample rate
	LPC,          // LPC-10 Linear Predictive CELP
	PCMA,         // G.711 A-Law
	G722,         // G.722
	L16_Stereo,   // 16 bit linear PCM
	L16_Mono,     // 16 bit linear PCM
	G723,         // G.723
	CN,           // Confort Noise
	MPA,          // MPEG1 or MPEG2 audio
	G728,         // G.728 16kbps CELP
	DVI4_11k,     // DVI4 at 11kHz sample rate
	DVI4_22k,     // DVI4 at 22kHz sample rate
	G729,         // G.729 8kbps
	Cisco_CN,     // Cisco systems comfort noise (unofficial)

	CelB = 25,    // Sun Systems Cell-B video
	JPEG,         // Motion JPEG
	H261 = 31,    // H.261
	MPV,          // MPEG1 or MPEG2 video
	MP2T,         // MPEG2 transport system
	H263,         // H.263

	LastKnownPayloadType,

	DynamicBase = 96,
	DynamicVideo = DynamicBase,
	DynamicAudio = 97,

	MaxPayloadType = 127,
	Tunnel = 128,	//穿网打洞包，无实际意义
	IllegalPayloadType
};

enum RTCPTYPE
{
	SR		= 200,
	RR		= 201,
	SDES	= 202,
	BYE		= 203,
	APP		= 204,
};

#define RESEND	14

typedef struct
{
	unsigned long ntpTimestampHigh;
	unsigned long ntpTimestampLow;
	unsigned long rtpTimestamp;
	unsigned long packetCount;
	unsigned long octetCount;
} SSenderInfo;

typedef struct
{
	unsigned long fractionLost : 8;
	unsigned long packetsLost  : 24;
} SLost;

typedef struct
{
	unsigned long ssrc;
	SLost lost;
	unsigned long highestSequence;
	unsigned long jitter;
	unsigned long lastSR;
	unsigned long delaySR;
} SReportBlock;

typedef struct 
{
	unsigned char type;
	unsigned char length;
	unsigned char data[64];
}SCname;

typedef struct 
{
	unsigned long ssrc;
	SCname scname;
}SChunk;

typedef struct 
{
	unsigned long name;
	unsigned short seqence1;
	unsigned short seqence2;
}SAppResend;


#endif//_RTP_PROTOCOL_H_
