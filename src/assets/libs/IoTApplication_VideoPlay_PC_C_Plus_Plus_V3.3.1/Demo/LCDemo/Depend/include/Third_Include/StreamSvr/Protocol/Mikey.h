#ifndef __INCLUDE_DAHUA_STREAMSVR_MIKEY_H__
#define __INCLUDE_DAHUA_STREAMSVR_MIKEY_H__

#include "Infra/IntTypes.h"
#include "StreamSvr/Defs.h"

namespace Dahua{
namespace StreamSvr{

///\brief 角色类型
enum MikeyRoleType
{
    MikeyRoleInitiator,     ///> Mikey协议发起者
    MikeyRoleResponser,     ///> Mikey协议应答者
};

///\brief Mikey状态
enum MikeyState
{
    MikeyStateStart,        ///> 初始状态
    MikeyStateInitiator,    ///> 发起者状态
    MikeyStateResponser,	///> 应答者状态
    MikeyStateAuthenticated,///> 认证通过状态
    MikeyStateError,		///> 错误状态
};

///\brief 枚举密钥交换的方式
enum KeyExchangeType
{
	KeyExchangePSK,		///> PSK 预共享密钥方式
	KeyExchangePK,		///> PK 公共密钥方式
	KeyExchangeDH,		///> DH霍夫曼密钥方式
	KeyExchangeUnknown,	///> 未知方式
};

///> 前向声明
class CMikeyImpl;

///\brief Mikey密钥管理协议实现
class STREAMSVR_API CMikey 
{
public:
    ///\brief 构造函数
	CMikey();
    
	///\brief 析构接口
	~CMikey();
    
	///\brief 添加发起者对应媒体资源
	///\param [in] ssrc-媒体源ssrc
	///return 0-ok, -1-failed
	int addSender(uint32_t ssrc);

	///\brief 设置秘钥交互Config
	///\param [in] exchangetype-密钥交互方式，参考 @see KeyExchangeType
	///\param [in] config-配置数据，如在PSK交互方式下，代表预共享密钥
	///\param [in] configLen-配置数据长度
	///\return 0-ok, -1-failed
	int setMikeyConfig(int exchangeType, void* config, int configLen);

	///\brief 设置MikeyState
	///\param [in] state-参考 @see MikeyState
	void setMikeyState(int state);

	///\brief Initiator生成Mikey字段
	///\param [in/out] initMessage-生成的base64编码MIKEY消息
	///\param [in/out] maxLen-输入表示缓冲长度，输出表示发起者生成的Mikey发起信息长度
	///\return 0-ok, -1-failed
	int  initiatorCreateMessage(char *initMessage,int &maxLen);
    
	///\brief 发起者校验信息
	///\param [in] message-待校验的密钥信息
	///\param [in] len-待校验的密钥信息长度(信息不一定以进制形式提供)
	///return 0-ok, -1-failed
	bool initiatorAuthenticate(char *message, int len);

	///\brief 应答者校验信息
	///\param [in] message-待校验的密钥信息
	///\param [in] len-待校验的密钥信息长度(信息不一定以进制形式提供)
	///return 0-ok, -1-failed
	bool responderAuthenticate(char* message,int len);
    
	///\brief 应答者生成Mikey信息
	///\param [in/out] initMessage-生成的base64编码MIKEY消息
	///\param [in/out] maxLen-输入表示缓冲长度，输出表示发起者生成的Mikey发起信息长度
	///\return 0-ok, -1-failed
	int responderCreateMessage(char *initMessage,int &maxLen);

	///\brief 生成TEK密钥
	///\param [in] ssrc-媒体对应ssrc
	///\param [in/out] tek-ssrc对应的tek
	///\param [in/out] tek_len-key的长度
	///return 0-ok, -1-failed
	int generateTEK(uint32_t ssrc, uint8_t* tek, int& tekLen);

	///\brief 生成salt密钥
	///\param [in/out] salt-盐值密钥缓冲
	///\param [in/out] len-输入表示缓冲长度，输出表示盐值密钥长度
	///return 0-ok, -1-failed
	int generateSalt(char* salt, int& len);
	
	///\brief 获取MikeyState
	///\return 参考 @see MikeyState
	int getMikeyState() ;	

private:
	CMikeyImpl*	m_impl;	///> 内嵌类对象指针
};

}//StreamSvr
}//Dahua

#endif //__INCLUDE_DAHUA_STREAMSVR_MIKEY_H_

