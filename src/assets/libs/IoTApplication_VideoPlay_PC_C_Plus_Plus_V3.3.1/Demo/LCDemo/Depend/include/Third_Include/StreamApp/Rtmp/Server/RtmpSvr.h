//
//  "$Id: StreamApp.h 126042 2013-07-10 12:08:39Z shu_wang $"
//
//  Copyright (c)1992-2010, ZheJiang Dahua Technology Stock CO.LTD.
//  All Rights Reserved.
//
//  Description:    
//  Revisions:      Year-Month-Day  SVN-Author  Modification
//                          2016-03-08        tang_bin Create
//
#ifndef DAHUA_STREAMAPP_IRTMPSVR_H
#define DAHUA_STREAMAPP_IRTMPSVR_H

#include <Component/Unknown.h>
#include "StreamApp/Defs.h"
#include "StreamApp/Rtmp/Server/RtmpUtil.h"

namespace Dahua{
namespace StreamApp{

///\brief RTMP 服务组件
class STREAMAPP_API IRtmpSvr: public Component::IUnknown
{
public:
	/// 组件工厂
	class IFactory : public Component::IFactoryUnknown
	{
	public:
		/// 获取组件实例
		virtual IRtmpSvr* instance() = 0;

		/// 组件接口ID定义
		static const char* iid() {return "IRtmpSvr";};
	};	
public:
	///\brief 析构函数
	virtual ~IRtmpSvr(){};
	
public:
	///\brief 开启RTMP 服务
	///\param [in] port-开启服务的端口
	///\return true-ok, false-failed
	virtual bool startsvr(int port = 1935)
		COMPONENT_UNIMPLEMENTED_OPERATION

	///\brief 停止RTMP 服务
	///\param [in] force-是否强制断开所有会话
	///\return true-ok, false-failed
	virtual bool stopsvr(bool force = false)
		COMPONENT_UNIMPLEMENTED_OPERATION

	///\brief 设置RTMP 服务端的配置
	///\param [in] name-配置枚举
	///\param [in] value-配置值
	///\return true-ok, false-failed
	virtual bool setConfig(rtmp_svr_config_t name, void *value)
		COMPONENT_UNIMPLEMENTED_OPERATION

	///\brief 获得RTMP 服务端的配置
	///\param [in] name-配置枚举
	///\param [in] value-配置值
	///\return true-ok, false-failed
	virtual bool getConfig(rtmp_svr_config_t name, void *value)
		COMPONENT_UNIMPLEMENTED_OPERATION

	///\brief 获得RTMP 服务的统计信息
	///\param [in] type  -统计的类型
	///\param [out] value-保存统计信息的地址
	///\param [in] len	  -保存统计信息的地址长度
	///\return true-ok, false-failed
	virtual bool getStatisticInfo(rtmpStatisticType type, void *value, int len)
		COMPONENT_UNIMPLEMENTED_OPERATION

	DAHUA_COMPONENT_FUNCTION_REVSERVED(15)
};

}//namespace StreamApp
}//namespace Dahua
#endif //DAHUA_STREAMAPP_IRTMPSVR_H
