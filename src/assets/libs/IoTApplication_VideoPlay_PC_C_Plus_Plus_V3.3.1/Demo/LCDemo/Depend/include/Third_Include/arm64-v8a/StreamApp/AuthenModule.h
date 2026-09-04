#ifndef __INCLUDED_DAHUA_STREAMAPP_AUTHEN_MODULE_H__
#define __INCLUDED_DAHUA_STREAMAPP_AUTHEN_MODULE_H__

#include <string>
#include "Infra/Function.h"
#include "Infra/Error.h"
#include "Component/Defs.h"

namespace Dahua {
namespace StreamApp {

#define AUTH_INFO_MAX       3          // 支持的最大权限方式数目

///\brief 鉴权基类
class IAuthModule
{
public:
	///\brief 认证结果
	enum AuthResult
	{
		authResultAuthPassed,		///> 认证通过
		authResultFailed,			///> 认证失败
		authChannelCheckFailed,		///> 权限校验失败
		authChannelInternalError,	///> 权限校验内部错误
		authErrorHasNotInit,		///> 认证失败,设备账号密码未初始化
	};

	///\返回给客户端的鉴权信息
	struct authTypeInfo
	{
		std::string authkey;		///< 关键字信息, 没有特殊要求为"WWW-Authenticate"
		std::string authinfo;		///< 鉴权相关信息, 如 "Basic realm=\"MediaServer3.0\""
	};

    ///\brief Url类型
    enum UrlType
    {
        urlTypeLive,	///> 直播Url
        urlTypeVod,		///> 点播Url
        urlTypeUnknown,	///> 未知
    };
	
protected:
	///\brief 虚析构函数
	virtual ~IAuthModule(){}

public:
	///\brief 检测是否需要认证
	///\param [out] auth-认证类型信息
	///\param [out] num-认证类型信息的数目
	///\return 0-不需要认证，1-需要认证
	virtual int checkAuth(authTypeInfo auth[AUTH_INFO_MAX], int &num) = 0;

	///\brief 用户认证
	///\param [in] authDetail-客户端传入的认证信息，如 Basic认证时，为 "Basic xxxxxxxxxx"
	///\param [in] clientIp-远程客户端ip
	///\return 参考 @see AuthResult
	virtual int challenge(const std::string& authDetail, const std::string clientIp = "") = 0;

	///\brief 认证信息提取并保存
	///\param [in] rawauth-认证的原始信息(实际上就是OPTIONS或者DESCRIBE的信令)
	///\param [in] authlen-认证原始信息的长度
	virtual void parseAuthInfo(const char* rawauth, int authlen) = 0;

	///\brief 销毁对象
	virtual void destroy() = 0;

	///\brief 设置通道鉴权使能
	///\param [in] channelAuth-通道鉴权使能
	///\param [in] urltype-url 类型, 直播还是点播, 见UrlType枚举
	///\param [in] channel-通道号信息
	///\param [in] reserve-保留参数
	///\return 0-设置成功，其他设置失败
	virtual int setChannelAuth(bool channelAuth, int urltype, int channel, void *reserve) = 0;

	///\brief 用户重新认证
	///\return 参考 @see AuthResult
	virtual int reChallenge() = 0;

	///\brief 获得用户名称
	///\param [out] username-用户名称
	///\return 0-成功, -1 无需鉴权或未找到对应的用户
	virtual int getUser(std::string &username) = 0;

	DAHUA_COMPONENT_FUNCTION_REVSERVED(11);
};

///\brief 创建鉴权器回调函数
///\param [in] const char*-请求的url 信息
///\param [int/out] int& -当前的鉴权类型见ConfigAuthType , 如果返回空指针会按该类型进行鉴权
///\param [in] void *-保留参数
///\return 鉴权器指针
typedef Infra::TFunction3<IAuthModule*, const char*, int&, void *> AuthCreateProc;

} //namespace StreamApp
} //namespace Dahua

#endif //__INCLUDED_DAHUA_STREAMAPP_AUTHEN_MODULE_H__
