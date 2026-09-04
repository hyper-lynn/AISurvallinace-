#ifndef __INCLUDED_DAHUA_STREAMSVR_RTCPPARSER_H__
#define __INCLUDED_DAHUA_STREAMSVR_RTCPPARSER_H__

#include <list>
#include "StreamSvr/Defs.h"

namespace Dahua{
namespace StreamSvr{

/***************************************************************
*	RTCP协议解析器
*	按照RFC3350文档标准，支持SR、RR、SDES、BYE类型RTCP包的组建和解析
*	模块相关文档请参考《解析器分析及优化设计文档》第1节
***************************************************************/

class STREAMSVR_API CRtcpParser
{
public:

#pragma pack(push) //保存对齐状态
#pragma pack(1)//设定为1字节对齐
	///\ 通用头部信息
	struct  rtcp_hdr_t{
#if __BYTE_ORDER == __BIG_ENDIAN
		uint8_t	version : 2,/* protocol version */
		p : 1,              /* padding flag */
		count	:	5;      /* varies by packet type */
		uint8_t	pt : 8;     /* RTCP packet type */
#elif __BYTE_ORDER == __LITTLE_ENDIAN
		uint8_t	count : 5,  /* varies by packet type */
		p : 1,              /* padding flag */
		version : 2;        /* protocol version */
		uint8_t pt : 8;     /* RTCP packet type */
#else
#	error "Please fix <endian.h>"
#endif
		uint16_t length;    /* pkt len in words, w/o this word */
	};

	///\ RTCP 载荷类型
	enum{
		RTCP_TYPE_SR 		= 200,	/* RTCP sender report. */
		RTCP_TYPE_RR 		= 201,	/* RTCP receiver report. */
		RTCP_TYPE_SDES 	= 202, 		/* RTCP source description packet. */
		RTCP_TYPE_BYE 	= 203,  	/* RTCP bye packet. */
		RTCP_TYPE_APP 	= 204		/* RTCP packet containing application specific data. */
	};

	///\ 接收者报告块
	struct  rr_block_t{
		uint32_t ssrc;           	/* data source being reported */
		uint32_t fraction:8,      	/* fraction lost since last SR/RR */
		lost:24;       				/* cumul. no. pkts lost (signed!) */
		uint32_t last_seq;        	/* extended last seq. no. received */
		uint32_t jitter;          	/* interarrival jitter */
		uint32_t lsr;            	/* last SR packet from this source */
		uint32_t dlsr;           	/* delay since last SR packet */
	};

#pragma pack(pop)

	///\ 源描述子项类型
	enum{ 
		END = 0,	/* Used when the iteration over the items has finished. */
		CNAME,		/* Used for a CNAME (canonical name) item. */
		NAME,		/* Used for a NAME item. */
		EMAIL,		/* Used for an EMAIL item. */
		PHONE,		/* Used for a PHONE item. */
		LOC,		/* Used for a LOC (location) item. */
		TOOL,		/* Used for a TOOL item. */
		NOTE,		/* Used for a NOTE item. */
		PRIV,		/* Used for a PRIV item. */
		Unknown 	/* Used when there is an item present, but the type is not recognized. */
	};

	///\ 源描述子项
	struct  sdes_item_t{
		uint8_t type;		/* type of item (rtcp_sdes_type_t) */
		uint8_t length;		/* length of item (in octets) */
		uint8_t data[0];	/* text, not null-terminated */
	};	
	typedef std::list< sdes_item_t* > ItemList;

	///\ SDES包
	struct rtcp_sdes_t {
		uint32_t	ssrc;       /* first SSRC/CSRC */
		ItemList	*item_list;	/* list of SDES items */
	};

	///\ SR包
	struct rtcp_sr_t{
		uint32_t ssrc;		/* sender generating this report */
		uint32_t ntp_sec;	/* NTP timestamp */
		uint32_t ntp_frac;	/*for less than 68 years, padding with 0 */
		uint32_t rtp_ts;	/* RTP timestamp */
		uint32_t psent;		/* packets sent */
		uint32_t osent;		/* octets sent */
	};

	///\ RR包
	struct rtcp_rr_t{
		uint32_t ssrc;				/* receiver generating this report */
		struct rr_block_t rr_block;	/* variable-length rr_block */
	};

	///\ BYE包
	struct rtcp_bye_t{
		uint32_t	ssrc;			/* sender generating this report */
		uint8_t		reason[0];		/* reason data, optional support */
	};

	///\ RTCP包结构体
	struct rtcp_pack_t{
		struct rtcp_hdr_t common;		/* 通用头部信息 */
		void* data;						/* 未深入解析之前，作为数据包起始地址索引 */
		union{							/* 经过内部解析之后，填充数据包的详细信息 */
			struct rtcp_sr_t sr;		/* sender report (SR) */
			struct rtcp_rr_t rr;		/* reception report (RR) */
			struct rtcp_sdes_t sdes;	/* source description (SDES) */
			struct rtcp_bye_t bye;		/* BYE */
		}pack;
	};
	typedef std::list< rtcp_pack_t* > PackList;

	//发送者统计信息
	struct sr_statistic_t{
		uint32_t  send_packets;			/* 总共发送的RTP包个数 */
		uint32_t  send_bytes;			/* 总共发送的RTP字节数  */
		uint32_t  send_rtp_pts;			/* 最新发送的RTP包时间戳 */
	};

	//接收者统计信息
	struct rr_statistic_t{
		uint32_t	ssrc;				/* 发送者的SSRC */
		uint32_t  receive_fraction_lost;/* 本次丢失的RTP包个数 */
		uint32_t  receive_packet_lost;  /* 总共丢失的RTP包个数 */
		uint32_t  receive_hightest_seq; /* 最新的RTP包序列号 */
	};

public:
	//通过参数传入源标识，构造RTCP解析器。
	CRtcpParser( uint32_t ssrc );
	~CRtcpParser();
	
	//更新发送者数据统计信息。
	//sr_statistic:发送者统计信息
	void updateInfo( struct sr_statistic_t *sr_statistic );
	
	//更新接收者数据统计信息。
	//rr_statistic:接收者统计信息
	void updateInfo( struct rr_statistic_t *rr_statistic );
	
	//重新统计收发信息，并清空额外添加的描述项。
	void reset();
	
	//根据统计信息，快速获取最新的发送者报告: SR+SDES复合包。
	//buf：结果填充缓冲，必须足够大。length缓冲区有效长度
	//返回：NULL失败，否则返回组建完毕的包，length表示包长度。
	uint8_t* getSRPacket( uint8_t *buf, uint32_t &length );
	
	//根据统计信息，快速获取最新的接收者报告: RR+SDES复合包。
	//buf：结果填充缓冲，必须足够大。length缓冲区有效长度
	//返回：NULL失败，否则返回组建完毕的包，length表示包长度。
	uint8_t* getRRPacket( uint8_t *buf, uint32_t &length );
	
	//快速获取一个BYE复合包，可直接用于在网络上发送。
	//buf：结果填充缓冲，必须足够大。length缓冲区有效长度
	//reason: 离开会话的原因的文本描述， reason_len: reason串的长度。
	//返回：NULL失败，否则返回组建完毕的包，length表示包长度。
	uint8_t* getBYEPacket( uint8_t *buf, uint32_t &length, const uint8_t *reason = NULL, uint8_t reason_len = 0 );

	//往SDES描述中添加新的源描述项。
	//type:描述项类型， length:描述项长度， data:描述内容
	int addSDESItem( uint8_t type, uint8_t length, uint8_t *data );

	///\brief 设置本地时区
	///\param [in] parameter 本地时区
	///\return -1:设置失败，0:成功
	int setTimeZone(int timezone);
	
public:
	//分析接收的Rtcp包数据，仅完成复合包的浅解析(rtcp_hdr_t)，须注意此时并不拷贝data数据。
	//has_bye: 返回解析的包是否为Bye包，是Bye包返回true, 否则返回false
	//compound：置为true表示需要校验复合包组包规则，支持单包解析时应置false
	//返回：成功解析的包的数量。
	int parseData( uint8_t *data, const uint32_t length, bool& has_bye, bool compound = true );

	//清空当前接收缓存数据，回收rtcp_pack_t
	void  clearPackList();
	
	//获取成功解析的复合包列表
	//返回：当前接收的复合包列表
	const PackList* getPacketList() const;

private:
	struct Internal;
	Internal *m_inter;
};


}//namespace StreamSvr
}//namespace Dahua

#endif //__INCLUDED_DAHUA_STREAM_RTCP_H__

