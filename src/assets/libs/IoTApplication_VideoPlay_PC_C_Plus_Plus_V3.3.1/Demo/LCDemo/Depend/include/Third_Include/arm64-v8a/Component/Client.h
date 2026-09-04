//
//  "$Id: Unknown.h 21790 2011-03-24 06:14:18Z wang_haifeng $"
//
//  Copyright (c)1992-2007, ZheJiang Dahua Technology Stock CO.LTD.
//  All Rights Reserved.
//
//	Description:
//	Revisions:		Year-Month-Day  SVN-Author  Modification
//

#ifndef _COMPONENT_CLIENT_H_
#define _COMPONENT_CLIENT_H_

#include <vector>
#include "Unknown.h"
#include <Infra/Function.h>

namespace Dahua {
namespace Component {


/// 客户端组件接口。每种网络协议(或无网络协议的本地)都必须实现一个IClient接口。
/// 其他组件创建时会使用IClient来登录到服务器
class COMPONENT_API IClient : public IUnknown
{
public:
	class COMPONENT_API IFactory : public IFactoryUnknown
	{
	public:
		// 创建客户端实例
		virtual IClient* create(const ServerInfo& server) = 0;

		// 获取客户端实例
		IClient* instance(int uid);

		// 组件接口ID定义
		static const char* iid(){return "Client";};
	};

public:
	enum Status
	{
		statusLoginSucceeded,	// 登录成功
		statusLoginFailed,		// 登录失败
		statusSessionAborted,	// 会话中断
	};
	
	///回调函数，客户端内部状态变化产生回调
	/// \param void * 用户自定义数据
	/// \param ClassID &实现类ID
	/// \param TComPtr<IClient> 产生该回调的IClient
	/// \param Status 新的状态
	/// \param int 登录失败或者会话断开的错误码
	typedef Infra::TFunction5<void, void *, ClassID, TComPtr<IClient>, Status, int> StatusProc;
	
public:
	/// 构造函数
	IClient();

	/// 析构函数
	virtual ~IClient();

	/// 会话是否断开，以下情况认为处于断开状态：没有登录，登录失败，连接断开，主动登出
	virtual bool isBroken( ) = 0;

	/// 建立连接，用户登陆，可能实现为非阻塞操作，这种情况下登录时应该先返回false，并将错误号设置为componentTryingLogin。
	/// 如果上次由于密码用户名不对等原因登录失败，下次登录应该返回fase，并将错误号设置为对应的值
	virtual bool login( ) = 0;

	/// 用户登出，并断开连接
	virtual bool logout( ) = 0;

	/// 获取客户端用户ID
	/// \param uid 用户ID，必须>=0。-1表示免登陆ID，仅供本地组件使用
	virtual bool getUserID(int& uid) = 0;

#ifndef _WIN32
	/// 此接口废弃。WIN32平台下直接去除
	virtual bool checkAuthority(const std::string& auth)
		COMPONENT_UNIMPLEMENTED_OPERATION
#endif

	/// 得到客户端当前系统时间
	virtual bool getCurrentTime(Infra::CTime& time)
		COMPONENT_UNIMPLEMENTED_OPERATION

	/// 设置客户端当前系统时间
	/// \param time 新的时间
	/// \param toleranceSeconds 容差，表示容许设置时间和当前差多少秒内不做修改
	virtual bool setCurrentTime(const Infra::CTime& time, int toleranceSeconds = 0)
		COMPONENT_UNIMPLEMENTED_OPERATION

	/// 使用新的ServerInfo再次登录，新老ServerInfo的userName必须相同
	/// \note 双向鉴权调用顺序：loginFirst()->getChallenge()->loginAgain()
	virtual bool loginAgain(const ServerInfo& si)
		COMPONENT_UNIMPLEMENTED_OPERATION

	/// 权限是否有效，用户已经登录而且权限存在时权限才算有效
	/// \param auth 权限名称
	virtual bool checkAuthorityString(const char* auth)
		COMPONENT_UNIMPLEMENTED_OPERATION

	/// 使用ServerInfo首次登陆，如果需要双向鉴权，则返回失败，错误号设置为
	/// \note 双向鉴权调用顺序：loginFirst()->getChallenge()->loginAgain()
	/// componentErrorLoginChallenge，和getChallenge，loginAgain配合使用
	virtual bool loginFirst( )
		COMPONENT_UNIMPLEMENTED_OPERATION

	/// 获取服务器双向鉴权信息，在需要做二次鉴权或者入网认证时使用
	/// \note 双向鉴权调用顺序：loginFirst()->getChallenge()->loginAgain()
	/// \param sc 鉴权信息
	virtual bool getChallenge(ServerChallenge & sc)
		COMPONENT_UNIMPLEMENTED_OPERATION
		
	/// 取得服务器信息，其中密码会被屏蔽。
	bool getServerInfo(ServerInfo & si);

	/// 获取登录时间
	bool getLoginTime(Infra::CTime & time);
	
	/// 会话中断，内部调用logout虚接口，有服务器踢出用户和网络断开两类原因
	/// \param reason 中断的原因，采用错误号表示
	bool abort(int reason);

	/// 注册状态函数
	/// \param proc 回调函数
	virtual bool attachStatusProc(StatusProc proc);
	
	/// 注销状态函数
	/// \param proc 回调函数
	virtual bool detachStatusProc(StatusProc proc);
	
	/// 设置用户自定义数据
	void setCustomData(void * data);

	/// 获取用户自定义数据
	void * getCustomData( );

	/// （挑战者鉴权模式下成功后)设置client用户名，只设置一次
	bool saveUserName(const char* username);

	/// 获取当前线程用户ID，只能在业务组件接口函数实现里(或者所调用的其他函数里)调用，
	/// 以识别调用该接口的用户。
	/// \retval -1 表示没有当前用户，是系统自发的操作，这时对应虚拟的用户名"System"
	/// \retval >=0 正常的用户ID，通过ID可以获取对应的用户组件，然后再进行权限验证或者
	/// 获取用户信息。
	static int getCurrentUserID(void);

	/// 设置为当前线程用户，此接口已废弃，请勿使用
	void setAsCurrentUser( );

public: //public for conveniance, for intenral using only
	struct ClientInternal;
	ClientInternal *m_internal;
};

typedef TComPtr<IClient> IClientPtr;

} // namespace Component
} // namespace Dahua

#endif // _COMPONENT_CLIENT_H_
