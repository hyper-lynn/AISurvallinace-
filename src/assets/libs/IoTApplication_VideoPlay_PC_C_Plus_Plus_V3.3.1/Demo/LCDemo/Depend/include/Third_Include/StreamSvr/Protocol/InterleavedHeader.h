#ifndef __INCLUDED_DAHUA_STREAMSVR_INTERLEAVED_HEADER_H__
#define __INCLUDED_DAHUA_STREAMSVR_INTERLEAVED_HEADER_H__

#include "Infra/Defs.h"

namespace Dahua{
namespace StreamSvr{

#pragma pack(push) //保存对齐状态
#pragma pack(1)//设定为1字节对齐

// rtp首部，具体见RFC3350
struct rtphdr
{
#if __BYTE_ORDER == __LITTLE_ENDIAN
	uint8_t cc : 4,  			// CSRC count
			x : 1,   			// header extend
			p : 1,   			// padding flag
			version : 2;		// version
	uint8_t pt : 7,				// payload type
			m : 1;				// mark bit
#elif __BYTE_ORDER == __BIG_ENDIAN
	uint8_t version : 2,		// version
			p : 1,   			// padding flag
			x : 1,   			// header extend
			cc : 4;  			// CSRC count
	uint8_t m : 1,   			// mark bit
			pt : 7;  			// payload type
#else
#error "Please fix <endian.h>"
#endif
	uint16_t seq;				// sequence number;
	uint32_t ts;				// timestamp
	uint32_t ssrc;				// sync source
};

// Rtp over Rtsp时，加上Rtp首部之前的4字节首部。
struct rtptcphdr
{
	int8_t	dollar;
	int8_t	channel;
	int16_t	len;
};

//大华私有码流的6字节首部。
struct dhtcphdr{
	int8_t	dollar;
	int8_t	channel;
	int32_t	len;
};

/* RTCP packet types */
enum RTCPType 
{
    RTCP_FIR    = 192,
    RTCP_NACK, // 193
    RTCP_SMPTETC,// 194
    RTCP_IJ,   // 195
    RTCP_SR     = 200,
    RTCP_RR,   // 201
    RTCP_SDES, // 202
    RTCP_BYE,  // 203
    RTCP_APP,  // 204
    RTCP_RTPFB,// 205
    RTCP_PSFB, // 206
    RTCP_XR,   // 207
    RTCP_AVB,  // 208
    RTCP_RSI,  // 209
    RTCP_TOKEN,// 210
};
#define RTP_PT_IS_RTCP(x) (((x) >= RTCP_FIR && (x) <= RTCP_IJ) || \
                           ((x) >= RTCP_SR  && (x) <= RTCP_TOKEN))


#pragma pack(pop)//恢复对齐状态


}//StreamSvr
}//Dahua

#endif //__INCLUDED_DAHUA_STREAMSVR_INTERLEAVED_HEADER_H__
