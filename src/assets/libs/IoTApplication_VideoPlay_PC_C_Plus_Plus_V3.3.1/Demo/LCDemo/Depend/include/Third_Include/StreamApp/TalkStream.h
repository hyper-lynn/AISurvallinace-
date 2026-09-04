//
//  "$Id: TalkStream.h 94221 2012-12-21 05:43:38Z huang_xiaojin $"
//
//  Copyright (c)1992-2010, ZheJiang Dahua Technology Stock CO.LTD.
//  All Rights Reserved.
//
//  Description:    
//  Revisions:      Year-Month-Day  SVN-Author  Modification
//                  2012-01-12        huang_xiaojin Create
//
#ifndef DAHUA_STREAMAPP_TALKSTREAM_H
#define DAHUA_STREAMAPP_TALKSTREAM_H

#include "Component/Unknown.h"
#include "Defs.h"
#include "Stream/StreamSource.h"

namespace Dahua{
namespace StreamApp{

class STREAMAPP_API ITalkStream: public Component::IUnknown
{
public:
	/// 组件工厂
	class IFactory : public Component::IFactoryUnknown
	{
	public:
		/// 取 TalkStream 对象实例
		/// 打开实时数据源
		/// \param [in] channle 对讲通道号		
		virtual ITalkStream* instance(int channel) = 0;

		/// 组件接口ID定义
		static const char* iid() {return "TalkStream";};
	};	
public:
	/// 析构函数
	virtual ~ITalkStream(){};
	
public:	
	enum
	{
		audioOnly = 0, //音频
		videoOnly, 	//视频
		audioVideo	//音视频同时
	};
	enum
	{
		udpUnicast = 0,	//IPv4 udp单播
		multicast			//IPv4 组播
	};
	enum
	{
		sendOnly = 0, 	//只发送
		recvOnly,		//只接收
		sendRecv		//同时收发
	};
	/// 获得本地媒体相关SDP信息，以及UDP端口号，IP地址信息
	/// \param [in] mediaType 音视频类型，获得的SDP信息只包括符合媒体类型的信息
	/// \param [out] buf 保存SDP字符串的缓存
	/// \param [in] bufLen 缓存大小
	/// \param [in] addrType 地址类型，组播或单播，默认UDP单播
	virtual bool getLocalSDP( int mediaType, char* buf, int bufLen, int addrType = udpUnicast )
		COMPONENT_UNIMPLEMENTED_OPERATION
	
	/// 设置远程流的SDP信息
	/// \param [in] sdp 对讲远端SDP描述信息	
	/// \param [in] transfersType 传输类型
	virtual bool setRemoteSDP( const char* sdp ,int transfersType = sendRecv)
		COMPONENT_UNIMPLEMENTED_OPERATION
	/// 启动，启动之后可以创建对讲流的streamsource
	/// \param [in] mediaType 音视频类型
	/// \param [in] transfersType 数据收发类型
	virtual bool start( int mediaType, int transfersType )
		COMPONENT_UNIMPLEMENTED_OPERATION
	
	/// 停止
	/// \param [in] mediaType 音视频类型
	/// \param [in] transfersType 数据收发类型
	virtual bool stop( int mediaType, int transfersType )
		COMPONENT_UNIMPLEMENTED_OPERATION

	/// 加入到组播组,mediaType不支持audioVideo，只支持audioOnly或者videoOnly
	/// 音视频的IP地址和端口号不能同时相等
	/// \param [in] mediaType 音视频类型
	/// \param [in] MulticastAddr组播组ip地址
	/// \param [in] port 组播组端口号
	virtual bool addMulticastGroup( int mediaType,const char * MulticastAddr,const int port)
		COMPONENT_UNIMPLEMENTED_OPERATION

	virtual bool setSource(Stream::IStreamSourcePtr streamSource)
		COMPONENT_UNIMPLEMENTED_OPERATION
		
	///发送RTPEvent,在音频通道传输rtp事件和音频复用同一个socket
	/// \param [in] frame 需要发送的RTPEvent帧，大华帧格式为DTFM辅助帧。
	virtual bool sendRTPEvent(Stream::CMediaFrame const& frame)
		COMPONENT_UNIMPLEMENTED_OPERATION
};

}//namespace StreamApp
}//namespace Dahua
#endif //DAHUA_STREAMAPP_TALKSTREAM_H
