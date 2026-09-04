//
//  "$Id: RtspSvrMessage.h 11665 2010-07-29 03:36:39Z huang_xiaojin $"
//
//  Copyright (c)1992-2010, ZheJiang Dahua Technology Stock CO.LTD.
//  All Rights Reserved.
//
//	Description:	
//	Revisions:		Year-Month-Day  SVN-Author  Modification
//								2013-10-29		he_linqiang	Create
//

#ifndef __INCLUDED_DAHUA_RTSP_MESSAGE_H__
#define __INCLUDED_DAHUA_RTSP_MESSAGE_H__

namespace Dahua{
namespace StreamApp{

//负责处理RTSP协议流程的模块，如果在RTSP处理中途失败，则向消息接收者发送该消息
//收到该消息，接收者应该调用Close()进行客户端关闭，消息的附带参数attach未使用。
#define MSG_RTSP_FAIL			0x1000

//表示客户端已完成跟对端的初始化设置步骤，此时用户可获取SDP，
//消息的附带参数attach未使用。
#define MSG_RTSP_READY		0x1001

#define MSG_RTSP_PAUSE		0x1002

#define MSG_RTSP_PLAY		0x1003

//表示服务端的流已经全部接收完毕, 接收者应该调用Close()进行资源清理
//消息的附带参数attach未使用。
#define MSG_RTSP_FINISH		0x1004

//表示鉴权失败
#define MSG_RTSP_AUTHORIZATIONFAIL	0x1005

// RTSP 的上层用户信息传递消息, 用于通知客户端上层服务端发过来的一些信息
// 消息的附带参数为服务端传递过来的信息码, 流媒体仅透传该信息码
#define MSG_RTSP_USRMSG         	0x1006

// RTSP流源STOP消息，用于自己抛消息给自己, 实现流源的异步关闭, 相当定时器的功能
#define MSG_STREAMSOURCE_STOP		0x1007

// RTSP 重定向消息, 当客户端配置了clientConfigRedirDisable 配置为使能后, 会通知该消息给上层,
// 由上层实现重定向功能
#define MSG_RTSP_REDIRECT		    0x1008

//表示服务端直播支持PASUE
#define MSG_RTSP_LIVEPAUSE_ENABLE			0x1009

//表示服务端的直播正常结束, 接收者应该调用Close()进行资源清理
//消息的附带参数attach未使用。
#define MSG_RTSP_LIVE_FINISH		0x100a


}//namespace StreamMedia
}//namespace Dahua
#endif //__INCLUDED_DAHUA_RTSP_MESSAGE_H__
