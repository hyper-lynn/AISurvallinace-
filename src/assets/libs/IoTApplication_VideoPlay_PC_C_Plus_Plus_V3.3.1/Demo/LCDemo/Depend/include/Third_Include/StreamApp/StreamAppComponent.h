#ifndef __INCLUDE_DAHUA_STREAMAPP_STREAMAPP_COMPONENT_H__
#define __INCLUDE_DAHUA_STREAMAPP_STREAMAPP_COMPONENT_H__

#include "StreamApp/Defs.h"

/// ==========流媒体所有的组件工厂都在该文件列出=========


///\brief 注册流媒体库的所有组件
///\      该接口会调用下面的组件接口进行功能组件的注册
///\      未调用的组件需要应用单独调用，用以减少代码空间
///\    initStreamAppServerComponent();

///\	initStreamAppDHEncryptComponent();

///\	initStreamAppRtspStreamSourceComponent();

///\	initStreamAppQuickMulticastComponent();

///\	initStreamAppHttpTalkClientComponent();

///\	initStreamAppTsMulticastServiceComponent();

///\	initStreamAppUdpMulticastServiceComponent();

///\	initStreamAppHttpTalkbackSvrComponent();

///\	initStreamSvrParseCreaterComponent();

///\	initStreamAppDHEncryptClientComponent();
extern "C" void initStreamAppComponentLibrary();


///\brief 主要用于设备注册流媒体库554 端口RTSP 功能的服务端组件
extern "C" void initStreamAppServerComponent();

///\brief 注册流媒体库实时流源以及文件流源组件
///\         主要用于前端web 客户端的直播拉流和文件拉流,
///\         以及NVR 设备服务端的转发拉流
extern "C" void initStreamAppRtspStreamSourceComponent();

///\brief 注册流媒体库快速组播组件
///\         主要用于设备Onvif 接入的快速组播功能
extern "C" void initStreamAppQuickMulticastComponent();

///\brief 注册流媒体库Http 对讲的客户端组件
///\         主要用于前端设备web 的语音对讲
extern "C" void initStreamAppHttpTalkClientComponent();

///\brief 注册流媒体库Ts 组播组件
///\         主要用于实现设备的TS 组播相关功能
extern "C" void initStreamAppTsMulticastServiceComponent();

///\brief 注册流媒体库Udp 组播组件
///\         主要用于实现设备的Udp 组播相关功能
extern "C" void initStreamAppUdpMulticastServiceComponent();

///\brief 注册流媒体库Ps 组播组件
///\         主要用于实现设备的PS 组播相关功能
extern "C" void initStreamAppPsMulticastServiceComponent();

///\brief 注册流媒体库智网产品线特殊需求相关组件
///\         主要用于智网产品线相关特殊功能的实现
extern "C" void initStreamAppZWANGComponent();

///\brief 注册流媒体库Http 对讲的服务端组件
///\         主要用于前端设备处理web 的Http 语音对讲
extern "C" void initStreamAppHttpTalkbackSvrComponent();

///\brief 注册流媒体服务端视频加密、语音对讲解密功能组件
///\         主要用于华视微讯,  乐橙等互联网设备
extern "C" void initStreamAppDHEncryptComponent();

///\brief 注册流媒体库RTP , TS , PS 等流拆封包组件
///\         如果服务端或客户端仅需要支持
///\         通过RTSP 协议TCP 方式拉大华私有码流的情况
///\         可以不注册该组件, 否则都需要注册该组件
extern "C" void initStreamSvrParseCreaterComponent();

///\brief 注册流媒体客户端视频解密、语音对讲加密功能组件
///\         主要用于华视微讯,  乐橙等互联网项目的客户端
extern "C" void initStreamAppDHEncryptClientComponent();

///\brief 注册基于SSL 套接字的rtsp 流媒体服务
///\         主要用于设备端传输基于SSL 套接字的加密流
extern "C" void initStreamAppSSlSvrComponent();

///\brief 注册使用StreamExt库来拉流,以及软件线客户端通过
///\          私有rtsp 协议来拉流的服务组件
extern "C" void initExtSvrComponent();

///\brief 注册在客户端rtp 组帧时,预留0xB1大华码流osd 扩展帧头空间的组件
///\         主要用于博世NVR onvif 拉流定制项目
extern "C" void initDhframeModifyComponent();

///\brief 注册通过大华帧头中0x95加密字段对裸码流和大华帧尾进行加密的组件
///\         主要用于IPC, DVR等设备服务端通过和慧眼加密码流方式接入平台
extern "C" void initStreamAppHHYEncryptComponent();

///\brief 注册在UDP传输方式下对一定rtp数据包乱序情况的重新排列组件
///\         主要用于手机等客户端在UDP方式下拉RTP流出现一定程度乱序情况
extern "C" void initStreamSvrRtpResortComponent();

///\brief 注册流媒体SRTP加密组件
///\         主要对标准码流进行SRTP加密
extern "C"	void initStreamSvrSrtpComponent();

///\brief 注册流媒体Url 服务组件, 用于提供RTMP 等协议Url 的获取及token 令牌的安全校验
///\         主要用于Rtmp协议Url 中包含token 令牌的权限校验
extern "C" void initStreamUrlServiceComponent();

///\brief 注册流媒体网络框架发送组件, 用于优化发送性能
///\         主要用于优化平台的大路数发送性能需求,开启后不支持UDP 方式传输
extern "C" void initStreamSenderCreaterComponent();

///\brief 注册流媒体Rtmp 协议服务组件
///\         主要用于设备或平台端的Rtmp协议码流发送
extern "C" void initStreamAppRtmpServerComponent();

///\brief 注册流媒体Rtmp 推流服务组件
///\         主要用于设备进行Rtmp协议推流
extern "C" void initStreamAppRtmpPushClientComponent();

///\brief 注册基于DHTS 套接字的rtsp 流媒体服务
///\         主要用于设备端传输基于DHTS 套接字的码流
extern "C" void initStreamAppDhtsSvrComponent();

///\brief 注册DHTS 套接字组件
///\         主要用于DHTS套接字的组件化封装, 未注册则DHTS套接字不可用
extern "C" void initStreamSvrDhtsSockComponent();

///\brief 注册Rtsp Over WebSocket协议组件
///\         主要用于Rtsp Over WebSocket协议的组件化封装, 用于设备端支持无插件流媒体播放
extern "C" void initStreamAppRtspWebSocketComponent();

///\brief 注册流媒体HttpDh 私有协议服务端组件
///\         主要用于乐橙设备或平台端的HttpDh私有协议码流发送
extern "C" void initStreamAppHttpDhSvrComponent();

///\brief 注册流媒体HttpDh 私有协议客户端组件
///\         主要用于乐橙设备或平台端客户端的HttpDh私有协议码流接收
extern "C" void initStreamAppHttpStreamClientComponent();

///\brief 注册流媒体服务能力集组件
///\         主要用于提供流媒体模块服务能力集配置,目前只供HttpDh 私有协议服务端使用
extern "C" void initStreamAppCapacitySetComponent();

///\brief 注册流媒体服务端用于创建保存sdp 信息的缓存,用于快速回复sdp 信息
///\         主要用于本地编码设备快速显示画面
extern "C" void initStreamAppDataSrcBufferComponent();

///\brief 注册流媒体客户端获取流信息组件
///\         主要用于乐橙客户端获取拉流过程中的流信息
extern "C" void initStreamAppClientStateComponent();

///\brief 注册流媒体服务端获取流信息组件
///\         主要用于流媒体服务端获取拉流过程中的流信息
extern "C" void initStreamAppSvrStatComponent();

///\brief 注册帧状态信息统计组件
///\         主要用于设备获取帧发送信息
extern "C" void initStreamSvrFrameStateComponent();

///\brief 注册TCP 码流发送工具组件
///\         主要用于设备直接通过TCP 协议发送码流
extern "C" void initStreamAppTcpStreamSenderComponent();

///\brief 注册HLS服务Ts分片组件
///\		  主要用于HLS服务发送Ts分片
extern "C" void initStreamAppTsSegmentsComponent();

///\brief 注册HLS服务Fmp4分片组件
///\		  主要用于HLS服务发送Fmp4分片
extern "C" void initStreamAppFmp4SegmentsComponent();

///\brief 注册通过使用大华0xB5码流加密方式对大华帧裸码流进行加解密的组件
///\          主要用于乐橙设备,手机客户端和平台进行大华帧加解密
extern "C" void initStreamAppDHEncrypt3Component();

#endif // end __INCLUDE_DAHUA_STREAMAPP_STREAMAPP_COMPONENT_H__

