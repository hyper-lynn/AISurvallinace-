//
//  "$Id: StreamApp.h 126042 2013-07-10 12:08:39Z shu_wang $"
//
//  Copyright (c)1992-2010, ZheJiang Dahua Technology Stock CO.LTD.
//  All Rights Reserved.
//
//  Description:    
//  Revisions:      Year-Month-Day  SVN-Author  Modification
//                  2012-01-12        huang_xiaojin Create
//
#ifndef DAHUA_STREAMAPP_EXTSVR_H
#define DAHUA_STREAMAPP_EXTSVR_H

#include <Component/Unknown.h>
#include "StreamApp/Defs.h"


namespace Dahua{
namespace StreamApp{

///\brief 用于软件线或StreamExt 库拉流服务组件
class STREAMAPP_API IExtRtspSvr: public Component::IUnknown
{
public:

	// ExtRtsp服务配置参数设置
	enum ExtRtspSvrConfig
	{
		ExtRtspSvrSendBuf = 0,			///< 发送缓存大小，单位字节
		ExtRtspSvrConfigNum,
	};
	
	/// 组件工厂
	class IFactory : public Component::IFactoryUnknown
	{
	public:
		/// 获取组件实例
		virtual IExtRtspSvr* instance() = 0;

		/// 组件接口ID定义
		static const char* iid() {return "ExtRtspsvr";};
	};	
public:
	/// 析构函数
	virtual ~IExtRtspSvr(){};
	
public:
	///\brief 开启用于软件线客户端接入的流媒体服务
	///\param [in] port-开启服务的端口
	///\return true-ok, false-failed
	virtual bool startsvr(int port)
		COMPONENT_UNIMPLEMENTED_OPERATION

	///\brief 停止用于软件线客户端接入的流媒体服务
	///\param [in] force-是否强制断开所有会话
	///\return true-ok, false-failed
	virtual bool close(bool force)
		COMPONENT_UNIMPLEMENTED_OPERATION

	///\brief 设置用户配置参数
	///\param [in]	name-配置名称
	///\param [in]	value-配置参数指针
	///\param [in]	len-配置参数指针所指区域的可访问长度
	///\return true-ok, false-failed
	virtual bool setconfig(ExtRtspSvrConfig name, const void *value, int len)
		COMPONENT_UNIMPLEMENTED_OPERATION
		
	DAHUA_COMPONENT_FUNCTION_REVSERVED(15)
};

}//namespace StreamApp
}//namespace Dahua
#endif //DAHUA_STREAMAPP_EXTSVR_H