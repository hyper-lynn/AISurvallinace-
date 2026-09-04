#ifndef __SECURITYUNIT_TOKENCENTER_H__
#define __SECURITYUNIT_TOKENCENTER_H__

#include "Infra/Defs.h"
#include "Component/Unknown.h"


namespace Dahua{
namespace SecurityUnit{


class ITokenCenter : public Component::IUnknown
{
public:

	/// 128字节
	struct UserLoginInfo
	{
		char userName[64]; 						//用户名
		char addrType; 							//登陆地址类型  0：IPv4 1：IPv6
		char loginAddr[47]; 					//登陆地址
		uint32_t loginMethod;					//登陆方式 0： 未知； 1：GUI； 2：WEB3.0； 3:Console； 4：DVRIP；
		char res[12];							//预留字节
	};

	/// 32字节
	struct ConditionLimit
	{
		uint64_t timeout;						//token超时时间，单位秒，不允许为0
		uint16_t count;							//token最大使用次数，不允许为0
		uint8_t res[22];						//预留字段 22+2+8 = 32
	};

public:
	/// 组件工厂
	class IFactory : public Component::IFactoryUnknown
	{
	public:
		/// 获取单例接口
		virtual ITokenCenter* instance() = 0;

		/// 组件接口ID定义
		static const char* iid() {return "SecurityUnit::TokenCenter";}
	};

protected:
	virtual ~ITokenCenter(){};

public:
	//\ 创建一个token
	//\param[in] userInfo 客户端登陆信息
	//\param[in] condition 新建token的限制条件
	//\param[out] token 新建的token值
	//[return] true成功，false失败
	virtual bool createToken(struct UserLoginInfo &userInfo, struct ConditionLimit &condition, std::string & token)
		COMPONENT_UNIMPLEMENTED_OPERATION;

	//\ 主动销毁一个token
	//\param[in] token 需要被销毁的token值
	//[return] true成功，false失败
	virtual bool destroyToken(const char* token)
		COMPONENT_UNIMPLEMENTED_OPERATION;

	//\ 验证一个token
	//\param[in] token 待校验的token值
	virtual bool verifyToken(const char* token)
		COMPONENT_UNIMPLEMENTED_OPERATION;

	/// 保留到32个虚函数
	DAHUA_COMPONENT_FUNCTION_REVSERVED(29);
};

typedef Component::TComPtr<ITokenCenter> ITokenCenterPtr;

} // namespace SecurityUnit
} // namespace Dahua

extern "C" void initSecurityUnitTokenCenterComponentLibrary();
#endif //__SECURITYUNIT_TOKENCENTER_H__
