//
//  "$Id: Unknown.h 21790 2011-03-24 06:14:18Z wang_haifeng $"
//
//  Copyright (c)1992-2007, ZheJiang Dahua Technology Stock CO.LTD.
//  All Rights Reserved.
//
//	Description:
//	Revisions:		Year-Month-Day  SVN-Author  Modification
//

#ifndef _COMPONENT_UNKNOWN_H_
#define _COMPONENT_UNKNOWN_H_

#include <vector>
#include <string>
#include "Infra/IntTypes.h"
#include "Infra/Version.h"
#include "Infra/Error.h"
#include "Infra/String.h"
#include "Defs.h"

namespace Dahua {
namespace Component {

/// 远程服务器信息,32位系统下128字节
struct COMPONENT_API ServerInfo
{
	const char* serverAddress;	///< 服务器地址
	uint32_t serverPort;		///< 服务器端口号
	const char* userName;		///< 用户名
	const char* password;		///< 密码明文或鉴权密码
	const char* random;			///< 用于鉴权的随机字符串，Server->Client
	uint8_t loginType;			///< 登录方式：
								///< 0-点对点登录
								///< 1-通过CenterManagerServer登录服务器集中登录
								///< 2-通过CenterManagerSupport登录
								///< 3-通过LDAP服务器登录
								///< 4-通过AD服务器登录
								///< 5-本地环回登录
	uint8_t loginMode;			///< 登录模式，0-阻塞登录，1-非阻塞登录
	uint16_t loginTimeout;		///< 登录超时时间，0-默认超时时间，>0自定义超时时间，单位为毫秒
	const char* clientType;		///< 原始客户端类型，比如本地登陆"GUI"，"Console", "Web3.0", "DVRIP"
	const char* clientAddress;	///< 原始客户端地址
	const char* authorityType;	///< 鉴权方式，指服务端设定的登陆流程类型标识
								///< 可以是 "Default", "HttpDigest", "OldDigest", "Onvif", "OTP"；如果为空，表示 "Default" 方式
								///< "OldDigest":一次登陆，不需要随机数，直接匹配加密后密码即通过
								///< "Default" 两次登陆方式，此种情况下即使passwordType填空，也按Default处理，Default和HttpDigest从鉴权角度看，都属于Challenge-Response模式，本质上属于同一种，因历史原因，被分为两种来使用。
								///< "OTP" One Time Password，一次登陆方式，客户端请求自带随机数或时间因子等值
	const char* authorityInfo;	///< 附加鉴权信息，在passwordType为HttpDigest和WSSE时有用
	uint32_t loginSession;		///< 会话标识号，用于区分相同来源、相同用户、相同登录类型、不同会话的用户登录
	const char* passwordType;	///< 密码类型，可以是 "Plain", "Default", "HttpDigest", "OldDigest", "Onvif", "WSSE"；如果为空，表示 "Plain" 方式
								///<   "Plain": random 填空，password 填密码明文
								///<   "Default": random 为随机字符串，password 为鉴权字符串
								///<   "HttpDigest": random 设为 nonce, authorityInfo 设为 nc:cnonce:qop:ha2, password 设为 ha3
								///<   "OldDigest": random 无意义，password为明文密码直接用修改MD5方式得到的8字节加密值
								///<   "Onvif": random 为随机字符串，password为sha-1加密密码
								///<   "WSSE": random 设为 nonce, authorityInfo 设为 CreationTimestamp, password 设为  Base64 (SHA1 (Nonce + CreationTimestamp + ha1))
								///<   "OldDigestMD5"，消警接口confirmEventByPassword使用，在OldDigest基础上再做一次MD5
								///<   详见《大华信息交换格式》
	uint8_t socketType;			///< 套接字类型，0-TCP, 1-UDP, 2-UDP多播，3-Unix域套接字, 4-Inproc(非套接字，单进程内使用，性能好)。
	uint8_t reservedBytes[3];	///< 保留字节
	uint32_t mediaPort;			///< 媒体服务的端口，0表示复用命令端口或者通过命令服务自动获取媒体端口，非0表示指定媒体端口
	uint32_t passiveSocket;		///< 被动套接字，0或者-1表示内部主动连接，其他表示使用注册服务器接受设备注册时的产生的套接字
	const char* targetID;		///< 目标唯一ID，空表示服务器即为目标，否则表示通过服务器代理连到该目标
	const char* proxyToken;		///< 代理服务器的Token，用于代理服务器做自身鉴权
	const char* stochastic;		///< 用于入网鉴权的随机字符串，Client->Server

	/// 为同时兼容32位和64位, 使用以下计算方法预留保留位数, 增加指针和整数时修改相应的乘数, 并注意64位下用完后, 不可再扩展
	uint8_t reserved[sizeof(void*)*32-sizeof(uint32_t)*6-sizeof(char*)*12];

	static const ServerInfo none;
};

/// 服务器双向鉴权信息,128字节
struct COMPONENT_API ServerChallenge
{
	ServerChallenge();
	~ServerChallenge();
	Infra::CMiniString encryption;		///< 登录加密方式
	Infra::CMiniString realm;			///< 登录器域信息
	Infra::CMiniString random;			///< 登录随机字符串
	Infra::CMiniString id;				///< 入网ID
	Infra::CMiniString authorization;	///< 入网鉴权信息
	
	int reserved [27];					///< 保留字段
};

/// 组件基类
class COMPONENT_API IUnknown
{
public:
	/// 构造函数
	IUnknown();

	/// 析够函数
	virtual ~IUnknown();

	/// 销毁函数
	virtual void destroy() = 0;

	/// 得到组件版本
	virtual Infra::CVersion getVersion(void) = 0;

	/// 增加引用，返回当前引用数；本接口为兼容老接口而保留, 请不要使用
	virtual int addRef(void);

	/// 减少引用，返回当前引用数；本接口为兼容老接口而保留, 请不要使用
	virtual int release(void);

public: // public for conveniance, for intenral using only
	struct UnknownInternal;
	UnknownInternal	*m_internal;
};


/// 组件工厂基类
class COMPONENT_API IFactoryUnknown
{
public:
	virtual ~IFactoryUnknown(){};

	/// 得到组件实现类ID
	/// \detail 对同一个接口，会有多种实现。组件实现类ID由两部分组成，
	///				用'.'分割，前面对应实现所基于的网络协议，后面对应实现的不同数据和代码。
	///				比如"Local.OneClick", "Local"表示本地实现(无网路协议)，"OneClick"
	///				表示一种实现了"AppService"接口的服务类。如果一种协议下只有一种实现，
	///				后半部分及'.'符号可以省略。前半部份支持的协议类型有：
	///				"Local" - 本地实现(无网路协议)
	///				"Dahua3" - 大华三代协议实现
	///				"Dahua2" - 大华二代协议实现
	///				"Sony" - Sony协议的实现
	///				"***" - 其他第三方协议的实现，参见《大华信息交换格式》
	/// \return 实现类ID，是一个常量字符串
	virtual const char* clsid() = 0;

	/// 注册函数，需要每个组件初始化时调用此函数对工厂进行注册
	/// \param iid 组件接口ID, 必须使用各自的IFactory::iid()静态函数获取而来
	/// \return 返回是否成功
	bool registerFactory(const char* iid);

	/// 注销函数，需要每个组件退出时调用此函数对工厂进行注销
	/// \param iid 组件接口ID, 必须使用各自的IFactory::iid()静态函数获取而来
	/// \return 返回是否成功
	bool unregisterFactory(const char* iid);
};

/// 组件实现类ID
struct COMPONENT_API ClassID
{
	explicit ClassID(const char* str):m_str(str){};
	const char* m_str;

	/// 本地组件的类ID
	static const ClassID local;

#ifndef _WIN32
	/// 此接口废弃。WIN32平台下直接去除
	static std::vector<std::string> getClassIDs(const char* iid);
#endif

};

/// 取ClassID列表助手类，得到已经注册的接口ID的全部类ID
class COMPONENT_API ClassIDList
{
	ClassIDList(ClassIDList const&);
	ClassIDList& operator=(ClassIDList const&);

public:
	/// 构造函数
	/// \param iid 接口ID
	ClassIDList(const char* iid);

	/// 析构函数
	~ClassIDList();

	/// 取元素个数
	size_t count() const;

	/// 取第 index 个 ClassID 名称
	Infra::CString operator[](int index) const;

private:
	struct ClassIDListInternal;
	ClassIDListInternal* m_internal;
};


} // namespace Component
} // namespace Dahua

#endif // _COMPONENT_UNKNOWN_H_

#include "Client.h"
#include "ComPtr.h"
#include "Factory.h"

