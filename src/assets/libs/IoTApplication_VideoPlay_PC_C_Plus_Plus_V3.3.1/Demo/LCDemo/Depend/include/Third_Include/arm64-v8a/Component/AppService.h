//
//  "$Id$"
//
//  Copyright (c)1992-2008, ZheJiang Dahua Technology Stock CO.LTD.
//  All Rights Reserved.
//
//	Description:	应用服务接口类
//	Revisions:		Year-Month-Day  SVN-Author  Modification
//                  2008-06-05      wang_haifeng 创建

#ifndef _UTIL_APP_SERVICE_H_
#define _UTIL_APP_SERVICE_H_

#include "Unknown.h"

namespace Dahua {
namespace Component {

// 应用服务，作为网络应用和GUI应用的接口基类，提供统一的接口
class IAppService : public IUnknown
{
public:
	class IFactory : public IFactoryUnknown
	{
	public:
		virtual IAppService* instance( ) = 0;

		// 组件接口ID定义
		static const char* iid(){return "AppService";};
	};


public:
	virtual ~IAppService(void){};

	/// 服务启动
	/// \param [in,out]	param 启动参数
	/// \param [in]		length 参数长度
	/// \return 是否成功
	virtual bool start(void * param = 0, int length = 0) = 0;

    /// 服务停止
	/// \param [in,out]	param 停止参数
	/// \param [in]		length 参数长度
	/// \return 是否成功
	virtual bool stop(void * param = 0, int length = 0) = 0;

    /// 服务控制
    /// \param [in]		request 控制请求编号
	/// \param [in,out]	param 控制参数
	/// \param [in]		length 参数长度
	/// \return 是否成功
	virtual bool control(int request, void * param = 0, int length = 0) = 0;

	/// 服务初始化配置，可调用多次初始化不同类别参数，在start之前调用
	/// \param [in]		type 初始化参数类型
	/// \param [in,out]	param 控制参数
	/// \param [in]		length 参数长度
	/// \return 是否成功
	virtual bool init(int type, void * param = 0, int length = 0) {return false;}
};

typedef TComPtr<IAppService> IAppServicePtr;

} // namespace Component
} // namespace Dahua

#endif // _UTIL_APP_SERVICE_H_

