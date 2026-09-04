//
//  "$Id: Defs.h 87354 2012-11-14 08:39:14Z huang_xiaojin $"
//
//  Copyright (c)1992-2010, ZheJiang Dahua Technology Stock CO.LTD.
//  All Rights Reserved.
//
//	Description:	
//	Revisions:		Year-Month-Day  SVN-Author  Modification
//					
//

#ifndef __INCLUDE_DAHUA_STREAMAPP_DEFS_H__
#define __INCLUDE_DAHUA_STREAMAPP_DEFS_H__

#ifdef WIN32

#ifdef STREAMAPP_DLL_BUILD
#define  STREAMAPP_API _declspec(dllexport)
#elif defined STREAMAPP_DLL_USE
#define  STREAMAPP_API _declspec(dllimport)
#else
#define STREAMAPP_API  
#endif

#else
#define STREAMAPP_API  
#endif

#include "Component/Unknown.h"
#include "Json/value.h"


namespace Dahua{

enum RtspError{
	rtspErrorParseFailed = 			0x110a0001,		//数据解析失败
	rtspErrorNetException = 		0x110a0002, 	//网络异常
	rtspErrorInner = 				0x110a0003, 	//内部错误
	rtspErrorAbility = 				0x110a0004,		//能力不足
};//enum RtspError

namespace StreamApp{

enum StreamEvent
{
	StreamStartSuccess = 0x01,	///< 拉流成功事件使能位
	StreamDisconnect   = 0x02,	///< 拉流断开事件使能位
	StreamStartFailed  = 0x04,	///< 拉流失败事件使能位
	StreamLostFrame    = 0x08,	///< 拉流丢帧事件使能位
	StreamDelayFrame   = 0x10,	///< 拉流延时事件使能位
	StreamStartTimeOut = 0x20,	///< 取流超时事件使能位
};	
	
/// 流事件信息回调
///\param [in] Json::Value& 	-流事件信息, 见添加流事件携带的信息
typedef Infra::TFunction1<void, const Json::Value&> StreamEventProc;

}

}//Dahua

#endif  //__INCLUDED_DAHUA_NETPROTOCOL_NET_HANDLER_H__
