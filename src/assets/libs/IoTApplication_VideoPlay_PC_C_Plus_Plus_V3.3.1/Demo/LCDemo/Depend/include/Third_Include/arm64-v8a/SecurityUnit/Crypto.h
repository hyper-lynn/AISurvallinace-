#ifndef __SECURITYUNIT_CRYPTO_H__
#define __SECURITYUNIT_CRYPTO_H__

#include "Component/Unknown.h"
#include "Memory/Packet.h"
#include "Defs.h"

namespace Dahua{
namespace SecurityUnit{

/// ICrypto组件定位：基于OpenSSL或其它加密库的封装，操作裸数据
class ICrypto : public Component::IUnknown
{
public:
	/// 组件工厂
	class IFactory : public Component::IFactoryUnknown
	{
	public:
		// 创建加密对象
		virtual ICrypto* create() = 0;

		/// 组件接口ID定义
		static const char* iid(){return "SecurityUnit::Crypto";};
	};

protected:
	virtual ~ICrypto(){};

public:
	/// 设置加解密需要的参数
	/// \param [in] mode 		使用的对称加密算法的模式,参照ESecUnitCipherMode
	/// \param [in] bits 		使用的对称加密算法的位数，不同的算法位数不同，比如DES只支持64，AES支持128,192,256。
	/// \param [in] iv 			CBC模式需要的初始化IV
	/// \param [in] len		 	初始化IV的长度，需要和对应的加解密算法的的分块长度对应，DES为8byte
	/// \param [in] aesPadding 	数据填充方式,参照ESecUnitCipherPadding
	virtual bool setCryptoOption(ESecUnitCipherMode mode, ESecUnitCipherBit bits,
			const unsigned char* iv, size_t len, ESecUnitCipherPadding cipherPadding)
		COMPONENT_UNIMPLEMENTED_OPERATION;

	/// 使用不经过任何编码的密码，解密数据，解密之前需要先调用setCryptoOption设置解密要的参数
	/// \param [in] 		plain 	待解密的数据
	/// \param [in] 		plainlen 待解密的数据数据长度，单位字节
	/// \param	[in] 		key 	用于解密的秘钥
	/// \param	[in] 		len		 对应的解密key的长度，与setAesOption传入的bits/8对应
	/// \param	[out]  		outData 解密后的数据
	virtual bool decryptWithKey(const void* plain, size_t plainlen, const unsigned char* key,
			size_t len, Memory::CPacket& outData)
		COMPONENT_UNIMPLEMENTED_OPERATION;

	/// 加密数据，解密之前需要先调用setCryptoOption设置解密要的参数
	/// \param [in] 	plain 	待加密的明文数据
	/// \param [in] 	plainlen 明文数据长度，单位字节
	/// \param [in] 	key 	用于对称加密的秘钥
	/// \param [in] 	len 	秘钥长度，与setAesOption传入的bits/8对应
	/// \param [out]  	outData 加密后的数据为二进制。
	virtual bool encryptWithKey(const void* plain, size_t plainlen, const unsigned char* key,
			size_t len, Memory::CPacket& outData)
		COMPONENT_UNIMPLEMENTED_OPERATION;

	/// 保留到32个虚函数
	DAHUA_COMPONENT_FUNCTION_REVSERVED(28)
};

typedef Component::TComPtr<ICrypto> ICryptoPtr;

} // namespace SecurityUnit
} // namespace Dahua

extern "C" void initSecurityUnitCryptoComponentLibrary();
#endif //__SECURITYUNIT_CRYPTO_H__

