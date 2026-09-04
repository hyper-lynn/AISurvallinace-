#ifndef __INCLUDED_DAHUA_STREAMSVR_SDPPARSER_H__
#define __INCLUDED_DAHUA_STREAMSVR_SDPPARSER_H__

#include <list>
#include <string>
#include <stdlib.h>

#include "StreamSvr/Defs.h"
#include "StreamSvr/Protocol/RtspUtil.h"
#include "StreamSvr/Media/MediaUtil.h"

namespace Dahua{
namespace StreamSvr{

///\brief 将采样率枚举转换成采样率
///\param [in] freq_code- 采样枚举, 见DAHUA_AUDIO_FREQ
///\return 采样率
STREAMSVR_API uint32_t freqcode2freq(int freq_code);

///\brief 将采样率转换成采样率枚举
///\param [in] freq- 采样率
///\return 采样枚举, 见DAHUA_AUDIO_FREQ
STREAMSVR_API uint8_t freq2freqcode(int freq);

/***************************************************************
*	Sdp协议解析器模块
*	按照RFC4566文档标准，完成SDP包的解析和组建
*	模块相关文档请参考《解析器分析及优化设计文档》第4节
***************************************************************/
class STREAMSVR_API CSdpParser
{
public:
	static const int sdpShortLen	= 16;
	static const int sdpNormalLen 	= 32;
	static const int sdpLongLen 	= 64;

	//媒体类型
	enum MediaType
	{
		mediaTypeAudio,
		mediaTypeVideo,
		mediaTypeText,
		mediaTypeApplication,
		mediaTypeMessage,
		mediaTypeUnknown
	};
	
	//用于表示连续的字符串描述
	typedef std::list< std::string > SdpValueList;
	
	//SDP 源字段
	//o=<username> <sess-id> <sess-version> <nettype> <addrtype> <unicast-address>    
	struct sdp_origin 
	{
		char		o_username[ sdpNormalLen ];	/* 用户在创建主机上的用户名，或者如果创建主机不支持用户ID的概念，则使用"-" */
 		uint64_t	o_id;      	 				/* 会话id */
		uint64_t	o_version;  				/* 会话描述的版本号 */
		char		o_nettype[ sdpShortLen ];   /* 网络的类型，eg."IN"的含义是"Internet" */  
		char		o_addrtype[ sdpShortLen ];  /* 地址的类型 "IP4"或"IP6"*/
		char		o_address[ sdpLongLen ];	/* 创建会话的主机地址,可为ip或域名*/
	};
	
	//SDP 连接字段
	//单播时：
	//c=<nettype> <addrtype> <connection-address>
	//多播时：
	//c=<nettype> <addrtype> <connection-address>[/ttl]/<number of addresses>
	struct sdp_conn 
	{
		char		c_nettype[ sdpShortLen ];	/* 网络类型 */
		char		c_addrtype[ sdpShortLen ];	/* 地址类型 */
		char		c_address[ sdpLongLen ];	/* 连接地址: 单播或多播组地址*/
		int			c_addrcount;   				/* 多播时，地址数*/                           
		uint8_t		c_ttl;         				/* IPV4多播时TTL值。注意IPV6不存在TTL字段 */
	};
	typedef std::list< struct sdp_conn >  SdpConnList;
		
	//SDP 时间字段
	//t=<start-time> <stop-time>
	struct sdp_time 
	{
		uint64_t	t_start;	/* 会话开始时间 */
		uint64_t	t_stop;     /* 会话结束时间 */
	};
	typedef std::list< struct sdp_time > SdpTimeList;
		
	//SDP 时区字段.
	//z=<adjustment time> <offset> <adjustment time> <offset> ....
	struct sdp_zone 
	{
		uint64_t	z_time;    				/* 基准时间 */
		char		z_offset[ sdpShortLen ];/* 时间偏移量 */
	};
	typedef std::list< struct sdp_zone > SdpZoneList;
	
	//SDP 属性字段.
	//a=<attribute> or a=<attribute>:<value>
	struct sdp_attr 
	{
		char		a_name[ sdpNormalLen ];	/* 属性名 */
		std::string	a_value;				/* 属性值 */
	};
	typedef std::list< struct sdp_attr > SdpAttrList;
			
	//SDP 带宽字段
	//b=<bwtype>:<bandwidth>
	struct sdp_bandwidth 
	{   
		char					b_type[ sdpShortLen ];	/* <bwtype>是一个字母数字的修饰符给出<bandwidth>数字的含义 */
		uint64_t				b_value;   				/* 带宽值 */
	};
	typedef std::list< struct sdp_bandwidth	> SdpBandwidthList;
	
	//密钥字段 (基于整个SDP会话或某个媒体)
	//k=<method> or k=<method>:<encryption key>
	struct sdp_key 
	{
		char		k_method[ sdpNormalLen ];	/* 密钥的机制 */
		std::string	k_enckey;					/* 密钥 */
	};

	//SDP 媒体部分, 包含媒体字段和其他字段
	//m=<media> <port>[/number of ports] <proto> <fmt> ...
	struct sdp_media {
		int					m_track_id;				/* 媒体的id号 */    
		std::string         m_track_url;			/* 媒体的control URL */
		char				m_name[ sdpNormalLen ];	/* 媒体类型名，有"audio"，"video"，"text"，"application"，和"message"等值 */
		uint32_t			m_port;					/* 传输端口 */
		int					m_portcount;			/* 端口数量 */
		char				m_proto[ sdpShortLen ];	/* 传输协议 如：udp, RTP/AVP, RTP/SAVP */
		uint32_t			m_payload_type;			/* 载荷类型 */
		SdpValueList		m_format;				/* 媒体格式描述 */       
		std::string			m_info;					/* 媒体信息字段 */
		SdpConnList			m_conn;					/* 媒体连接字段 */
		SdpBandwidthList	m_bw;					/* 媒体带宽字段 */
		struct sdp_key		m_key;					/* 媒体密钥字段 */
		SdpAttrList			m_attr;					/* 媒体属性字段 */         
	};
	typedef std::list< struct sdp_media > SdpMediaList;
		
	struct sdp_session 
	{
		int					s_version;           /* SDP版本号 eg. v=0  */
		struct sdp_origin	s_origin;          	 /* SDP源字段 */
		char				s_name[sdpNormalLen];/* 会话名 eg. s=<session name> */
		std::string			s_info;              /* 会话信息  eg. i=<session description> */
		std::string			s_uri;            	 /* SDP uri字段 eg. u=<uri> */
		SdpValueList		s_email;           	 /* SDP 电子邮件 eg. e=<email-address> */
		SdpValueList		s_phone;         	 /* SDP 电话号码 eg. p=<phone-number> */
		SdpConnList			s_conn;              /* SDP 连接字段 */
		SdpBandwidthList	s_bw;                /* SDP 带宽字段 */
		SdpTimeList			s_time;           	 /* SDP 时间字段 */
		SdpZoneList			s_zone;            	 /* SDP 时区字段 */
		struct sdp_key		s_key;        	   	 /* SDP 密钥字段 */
		SdpAttrList			s_attr;              /* SDP 会话属性字段 */
		SdpMediaList		s_media;             /* SDP 媒体字段 */
	};
	
private:
	CSdpParser(const CSdpParser & other){};
public:
	CSdpParser();
	CSdpParser& operator=( CSdpParser& other );	
	~CSdpParser();
	
	///\brief 解析输入的字符串文本
	///\param [in]	sdp: 输入的字符串指针
	///\return  	0 解析成功 -1 解析失败
	int attach( const char *sdp );
	
	///\brief 获取SDP buffer
	///\return 		NULL: 失败，else: SDP字符串描述的格式
	const char*	getStream();
	
	//这是一组SDP通用信息的设置接口，用户若无特殊需求，可不关心，系统会自动生成相关参数的信息。

	///\brief 添加源字段
	//o=<username> <sess-id> <sess-version> <nettype> <addrtype> <unicast-address>
	///\param [in]  name 创建用户的用户名，id 会话id，ver 会话版本号, nettype 网络类型，addrtype 主机地址，address 地址类型。
	///\return		-1 添加失败  0 添加成功
	int addOrigin( const char* name, uint64_t id, uint64_t ver, 
										const char* nettype, const char* addrtype, const char* address );
	///\brief 添加会话名
	//s=<session name>
	///\param [in]	name: 会话名的字符串(需以‘\0’作为结束符)的指针
	///\return		-1 添加失败, 0 添加成功
	int addName( const char* name );
	
	///\brief 添加会话uri字段
	//u=<uri>
	///\param [in]  value: url的字符串(需以‘\0’作为结束符)的指针
	///\return		-1 添加失败  0 添加成功
	int	addUri( const char* value );
	
	///\brief 添加会话信息
	//i=<session description>
	///\param [in]  value: url的字符串(需以‘\0’作为结束符)的指针
	///\return		-1 添加失败, 0 添加成功
	int addInfo( const char* value );
	
	///\brief 添加会话email地址
	//e=<email-address>
	///\param [in]  value Email地址的字符串(需以‘\0’作为结束符)的指针
	///\return		-1 添加失败, 0 添加成功
	int addEmail( const char* value );
	
	///\brief 添加会话电话号码
	//p=<phone-number>
	///\param [in]  value 电话号码的字符串(需以‘\0’作为结束符)的指针
	///\return  -1 添加失败  0 添加成功
	int addPhone( const char* value );
	
	///\brief 往会话域内添加带宽字段
	//b=<bwtype>:<bandwidth>
	///\param [in]  type 带宽的量度单位如( CT, AS )
	///\param [in]	value: 对应单位的数值
	///\return  	-1 添加失败, 0 添加成功
	int addBandwidthToSession( const char* type, uint64_t value );
	
	///\brief 往会话内追加时间字段
	//t=<start-time> <stop-time>
	///\param [in]  starttime 会话开始时间  stoptime 会话结束时间 
	//			如果stoptime被设置为0,说明会话是不会被终止的 starttime也被设置为0,表明该会话是永久的
	///\return  -1 添加失败  0 添加成功
	int addTime( uint64_t starttime, uint64_t stoptime );
	
	///\brief 往会话内追加时区字段
	//z=<adjustment time> <offset> <adjustment time> <offset> ....
	///\param [in]  time: NTP时间  
	///\param [in]  offset: 离基准时间的偏移量的字符串
	///\return  	-1 添加失败  0 添加成功
	int addZone( uint64_t time, const char* offset );
	
	///\brief 往会话内追加会话密钥
	//k=<method>
	//k=<method>:<encryption key>
	///\param [in]  method: 获取可用密钥的机
	///\param [in]	enckey: 表示该机制获取的密钥
	///\return  	-1 添加失败  0 添加成功
	int addKeyToSession( const char* method, const char* enckey );
	
	///\brief 往会话内追加会话属性
	//a=<attribute>, 若该属性已存在则进行替换
	//a=<attribute>:<value>, value为空则删除该属性
	///\param [in]  name 属性的名字  value 属性的描述
	///\return  -1 执行失败  0 执行成功
	int	addAttributeToSession( const char* name, const char* value = NULL );
	
	///\brief 往会话域内添加连接字段，主要用于UDP组播
	//c=<nettype> <addrtype> <connection-address>[/ttl]/<number of addresses>
	///\param [in]  address 链接地址的描述 ttl 生存时间(TTL)值，作为对多播地址的一个补充 
	//		addrcount 链接地址的数量(默认为1 即包括address)
	//			nettype 网络类型 默认输入NULL( 即IN ) addrtype 地址类型 默认输入NULL( 即IPv4 )
	///\return  -1 执行失败  0 执行成功	
	int addConnectionToSession( const char* address, uint8_t ttl, int addrcount,
															const char* nettype = NULL, const char* addrtype = NULL);
	///\brief 清空会话域内的连接字段
	void cleanConnectionToSession();
	
	///\brief 获取会话的连接信息。
	///\param [in]	sql_conn_list: 用于获取链接信息(实际上一般以一个为准)
	///\return		-1 获取失败  0 获取成功
	int getConnectionOfSession( SdpConnList& sql_conn_list );

	///\brief 设置会话的播放长度
	//a=range:npt=0-70.031383
	///\param [in] start 开始时间  end时间 单位:微秒
	///\return		-1 执行失败  0 执行成功
	int setRange( RangeInfo info );

	///\brief 获取会话的播放长度  
	///\param [in] 	info  CRangeInfo结构体 可以兼容保存npt、clock、 byte三种类型的范围值
	///\return  	成功返回0 没有找到Range信息(参数 info的type会被置play_range_type_unknown)和获取信息不完整(比如范围只有开始值没有结束值)则返回-1
	int getRange( RangeInfo& info );

	///\brief 获取数据源打包格式
	///\return  数据源打包的类型
	MediaPacketType getPacketType();

	//这是媒体相关的一组信息设置接口
	
	///\brief 往会话内追加媒体
	//m=<media> <port>[/portcount] <proto> <fmt> ...
	///\param [in]  	name media 的名字  port 媒体链接使用的端口	portcount在port之后连续使用的端口数量(包括port自身) 
	//				protcol 传输协议 fmt 媒体格式描述 trackid 媒体的track id
	///\return  成功返回0，失败则返回-1。
	int addMedia( const char* name, uint32_t port, int portcount, 
					const char* protocol, const char* fmt, int trackid);

	///\brief 在会话中删除一个媒体。
	///\param [in] index: 表示media唯一索引
	///\return  -1 执行失败  0 执行成功 
	int delMedia( int index );

	///\brief 往媒体内追加媒体属性
	//a=<attribute>, 若该属性已存在则进行替换
	//a=<attribute>:<value>, value为空则删除该属性
	///\param [in] index: 表示media唯一索引
	///\param [in] name 属性的名字  value 属性的描述 
	///\return  -1 执行失败  0 执行成功
	int	addAttributeToMedia( int index, const char* name, const char* value = NULL );  			          

	///\brief 往媒体域内添加连接字段
	//c=<nettype> <addrtype> <connection-address>[/ttl]/<number of addresses>
	///\param [in] index 表示media唯一索引
	///\param [in] address 链接地址的描述 
	///\param [in] ttl 生存时间(TTL)值，作为对多播地址的一个补充
	///\param [in] addrcount 链接地址的数量(默认为1 即包括address)
	///\param [in] nettype 网络类型 默认输入NULL( 即IN )
	///\param [in] addrtype 地址类型 默认输入NULL( 即IPv4 )
	///\return  -1 执行失败  0 执行成功
	int addConnectionToMedia( int index, const char* address, uint8_t ttl, 
							  int addrcount, const char* nettype=NULL, const char* addrtype = NULL ); 						

	///\brief 清空媒体域内的连接字段
	///\param [in] index 表示media唯一索引
	void cleanConnectionToMedia( int index );

	///\brief 设置媒体的端口
	///\param [in] index 表示media唯一索引
	///\param [in] newPort 新的端口号的值
	///\return		-1 执行失败  0 执行成功
	int setMediaPort( int index, uint16_t newPort );

	///\brief 往媒体内追加密钥
	//k=<method>
	//k=<method>:<encryption key>
	///\param [in] index 表示media唯一性的id
	///\param [in] method 获取可用密钥的机 
	///\param [in] enckey 表示该机制获取的密钥 
	///\return  -1 添加失败  0 添加成功
	int addKeyToMedia( int index, const char* method, const char* enckey );

	//这是媒体相关的一组信息获取接口

	///\brief 获取媒体总数
	///\return	媒体的数量
	int getMediaTotal();

	///\brief 获取媒体的某个属性
	///\param [in]  index 表示媒体索引   attr_name 属性名称
	///\return		成功则返回对应属性的描述 失败返回NULL 
	const char* getMediaAttrByIndex( int index, const char* attr_name );
	
  	///\brief 通过下标获取媒体的URL
  	///\param [in]  index 媒体的下标
	///\return		媒体的URL 失败返回 NULL 
	const char* getMediaURLByIndex( int index );
	
	///\brief 通过匹配是否存在传入的track_url,返回相应的track_id。
	///\param [in]  媒体对应的track_url 
	///\return		返回对应的track_id, 返回 -1 匹配失败。 
	int getTrackIdByURL( const char* track_url );

	///\brief 通过下标获取媒体的媒体类型
  	///\param [in]  	index 媒体的下标
	///\return 	MediaType枚举	
	int getMediaTypeByIndex( int index );
	
	///\brief 返回媒体子类型
	///\param [in]  用于获取当前sdp信息中带有video类型信息的track_id
	///\return 	VideoSubType枚举
	int getVideoSubType( int &mediaIndex );
	
	///\brief 返回媒体子类型
	///\param [in]  用于获取当前sdp信息中带有audio类型信息的track_id
	///\return 	AudioSubType枚举
	int getAudioSubType(int &mediaIndex);
	
	///\brief 获取媒体的媒体的连接信息。
	///\param [in] index表示媒体唯一性的index  
	///\param [in] sql_conn_list 用于获取链接信息(媒体允许多个连接)
	///\return		-1 获取失败  0 获取成功
	int getConnListOfMediaByIndex( int index, SdpConnList& sql_conn_list );

	///\brief 获取媒体的端口
	///\param [in] index 表示媒体唯一index 	
	///\return 	成功返回端口号 失败返回-1
	int getMediaPortByIndex( int index );

	///\brief 获取音频声道数
	///\param [in] index: 媒体索引
	///\return -1:失败, else: 音频声道数
	int getAudioChannelTotal( int mediaIndex );

	//以下接口获取音视频频属性，包括playload type,载荷名，采用率

	///\brief 获取媒体video的帧率和payload_type，如果没有视频，则返回音频的payload_type及默认帧率25
	///\param [in]  payload 获取载荷类型
	///\return  帧率
	int getfps( int &payload_type );

	///\brief 参数: media_index 媒体的下标
	///\return  媒体的载荷类型
	int getPayloadType( int media_index );

	///\brief 获取载荷类型名称
	///\param [in]  media_index 媒体的下标 buf 用于获取载荷类型名称 buf_len  buf的长度
	///\return   0 获取成功  -1 不存在该类型 >0 buf的长度不够 返回需要的buf长度
	int	getPayloadName( int media_index, char* buf, int buf_len );

	///\brief 称获指定媒体的所有载荷类型值列表
	///\param [in]  media_index 媒体的下标 
	///\param [out] payload_list 获取的载荷类型值列表
	///\return 0 成功, -1 失败
	int getAllPayloadType( int media_index, SdpValueList & payload_list);

	///\brief 通过载荷类型值获取载荷名称
	///\param [in]  media_index 媒体的下标 
	///\param [in]  payload_type 指定载荷类型值
	///\param [out] payload_name 获取的载荷类型名称
	///\param [in]  payload_name_len 获取的载荷类型名称长度
	///\return 0 成功,   -1 失败
	int getPayloadNameByType( int media_index, const int payload_type, char* payload_name, int payload_name_len );

	///\brief 通过载荷名称获取载荷类型值
	///\param [in]  media_index 媒体的下标 
	///\param [in]  payload_name 指定载荷名称 
	///\param [in]  payload_name_len 指定载荷名称长度 
	///\return  媒体的载荷类型
	int getPayloadTypeByName( int media_index, const char* payload_name, int payload_name_len );

	///\brief 通过载荷名称获取采样率
	///\param [in]  media_index 媒体的下标 
	///\param [in]  payload_name 指定载荷名称 
	///\param [in]  payload_name_len 指定载荷名称长度 
	///\return  媒体的采样率
	int getSampleRateByName( int media_index, const char* payload_name, int payload_name_len );

	///\brief 获取采样率
	///\param [in]  media_index 媒体的下标
	///\return  成功返回采样率 失败返回 -1
	int getSampleRate( int media_index );

	///\ 媒体的收发属性
	enum SendRecvAttr{
		sendRecvAttrSendRecv,			//缺省属性
		sendRecvAttrSendOnly,
		sendRecvAttrRecvOnly,
		sendRecvAttrUnknownAttr,
	};
	
	///\brief 获取对应媒体的收发属性
	///\param [in] mediaIndex-媒体索引(0,1,2,...)
	///\return CSdpParser::SendRecvAttr,UNKNOWN_SR_ATTR表示失败，其它为成功
	SendRecvAttr getSendRecvAttr(int index);

   	///\brief 获取Mikey管理请求密文,实现在会话属性
	///\param [in/out] message-Mikey消息缓冲区
	///\param [in/out] maxLen-输入表示缓冲长度，输出表示获取的mikey消息数据长度(仅在返回值==0时有效)
	///\return 0-ok, -1-失败
	int getMikeyMessage(char* message, uint32_t &maxLen); 

	///\brief 获得rtp 打包支持的荷载类型
	///\return rtp打包支持的荷载类型
	MediaRtpPayloadType getRtpPayloadType();

	///\brief 修改会话内指定索引的媒体
	///\m=<media> <port>[/portcount] <proto> <fmt> ...
	///\param [in] index -表示media唯一索引
	///\param [in] name -media 的名字
	///\param [in] port -媒体链接使用的端口
	///\param [in] portcount -在port之后连续使用的端口数量(包括port自身) 
	///\param [in] protcol -传输协议
	///\param [in] fmt -媒体格式描述
	///\param [in] trackid -媒体的track id
	///\return  成功返回0，失败则返回-1。
	int modifyMedia(int index, const char* name, uint32_t port, int portcount, const char* protocol, const char* fmt, int trackid);

	///\brief 获得会话属性指定名称的描述
	///\param [in] name - 属性的名字  
	///\return  获取失败返回NULL,  否则返回属性名称对应的描述
	const char* getSessionAttribute(const char *name);
private:
	struct Internal;
	Internal *m_inter;
};

}//namespace StreamSvr
}//namespace Dahua

#endif //__INCLUDED_DAHUA_STREAMSVR_LIB_SDP_R_H__

