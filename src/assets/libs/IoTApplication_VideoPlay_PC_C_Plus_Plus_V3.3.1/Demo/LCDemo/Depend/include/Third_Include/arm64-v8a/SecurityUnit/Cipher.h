#ifndef __SECURITYUNIT_CIPHER_H__
#define __SECURITYUNIT_CIPHER_H__

#include "Component/Unknown.h"
#include "Infra/String.h"
#include "Memory/Packet.h"
#include "Defs.h"

namespace Dahua{
namespace SecurityUnit{

/// ICipher组件定位：封装大华业务需要的加解密功能，对加解密数据会有额外的处理
class ICipher : public Component::IUnknown
{
public:
	// RSA填充方式
	enum ERSAPADDTYPE
	{
		E_RSA_UNKNOWN = SECUNIT_RSA_UNKNOWN,
		E_PKCS1 = SECUNIT_RSA_PKCS1,
		E_OEAP = SECUNIT_RSA_OEAP,
	};

	// AES填充方式
	enum EAESPADDTYPE
	{
		E_AES_UNKNOWN = SECUNIT_AESUNKNOWN,
		E_AES_ZERO = SECUNIT_AESZERO_PADDING,		// AES数据不足采用0填充，和现有的RPC SERVER保持一致
		E_AES_PKCS7 = SECUNIT_AESPKCS7_PADDING,		// AES数据不足按PKCS7规范填充
		E_AES_NOPADDING = SECUNIT_NO_PADDING,		// AES数据不填充，要求必须为16的整数倍
	};

public:
	/// 组件工厂
	class IFactory : public Component::IFactoryUnknown
	{
	public:
		// 创建加密对象
		virtual ICipher* create() = 0;

		/// 组件接口ID定义
		static const char* iid(){return "SecurityUnit::Cipher";};
	};

protected:
	virtual ~ICipher(){};

public:
	/// 配置RSA秘钥的路径参数
	/// \param [in] cacert_path 			本地服务器证书路径
	/// \param [in] privkey_path 			本地服务器私钥路径
	virtual bool setCertPath(const char* cacert_path, const char* privkey_path)
		COMPONENT_UNIMPLEMENTED_OPERATION;

	/// 获取设备公钥
	/// \param [out] asymmetric 非对称加密算法"RSA"
	/// \param [out] publicKey 	公钥信息，格式"N:xx,E:xx"
	/// \param [out] cipher 支持的对称加密算法列表,这个参照协议
	virtual bool getEncryptInfo(Infra::CString& asymmetric, Infra::CString& publicKey,
			std::vector<Infra::CString>& cipher)
		COMPONENT_UNIMPLEMENTED_OPERATION;

	/// 设置Aes加密需要的参数
	/// \param [in] mode 		使用的对称加密AES算法的模式,目前只支持"ECB","CBC","OFB"三种,NULL表示采用默认CBC模式
	/// \param [in] bits 		使用的对称加密AES算法，目前只支持128，192, 256，默认256
	/// \param [in] iv 			CBC模式需要的初始化IV，长度为16,NULL表示默认IV "0000000000000000",16个0x30,不是0x00
	/// \param [in] len		 	初始化IV的长度，目前只支持16字节
	/// \param [in] aesPadding 	aes数据填充方式,参照EAESPADDTYPE
	virtual bool setAesOption(const char* mode, unsigned int bits,
			const unsigned char* iv, size_t len, EAESPADDTYPE aesPadding)
		COMPONENT_UNIMPLEMENTED_OPERATION;

	/// 使用经过加密的秘钥因子，解密数据，解密之前需要先调用setAesOption设置解密要的参数
	/// \param [in] 	content 待解密的数据，数据采用Base64编码的
	/// \param [in] 	salt 公钥加密后的内容，并按每个字节高低4bit拆成两个可显字符如0x0E->"0E"
	/// \param [in]		padding 	rsa加密数据填充方式,目前固定为E_PKCS1
	/// \param [out]  	outData 解密后的数据
	virtual bool aesDecryptWithSalt(const char* content, const char* salt,
			ERSAPADDTYPE padding, Memory::CPacket& outData)
		COMPONENT_UNIMPLEMENTED_OPERATION;

	/// 使用不经过任何编码的密码，解密数据，解密之前需要先调用setAesOption设置解密要的参数
	/// \param	[in] 		content 待解密的数据，数据采用Base64编码的
	/// \param	[in] 		key 	用于对称解密密的秘钥
	/// \param	[in] 		len		 对应的解密key的长度，与setAesOption传入的bits的位数对应, 如AES-128的秘钥长度 128/8=16
	/// \param	[out]  		outData 解密后的数据
	virtual bool aesDecryptWithKey(const char* content, const unsigned char* key,
			size_t len, Memory::CPacket& outData)
		COMPONENT_UNIMPLEMENTED_OPERATION;

	/// 使用经过加密的秘钥因子，加密数据，解密之前需要先调用setAesOption设置解密要的参数
	/// \param [in] 	plain 	待加密的明文数据
	/// \param [in] 	plainlen 明文数据长度，单位字节
	/// \param [in] 	salt 	公钥加密后的内容，并按每个字节高低4bit拆成两个可显字符如0x0E->"0E"
	/// \param [in]		padding 	rsa加密数据填充方式,目前固定为E_PKCS1
	/// \param [out]	outData 加密后并做Base64的数据。
	virtual bool aesEncryptWithSalt(const void* plain, size_t plainlen, const char* salt,
			ERSAPADDTYPE padding, Infra::CString& outData)
		COMPONENT_UNIMPLEMENTED_OPERATION;

	/// 加密数据，解密之前需要先调用setAesOption设置解密要的参数
	/// \param [in] 	plain 	待加密的明文数据
	/// \param [in] 	plainlen 明文数据长度，单位字节
	/// \param [in] 	key 	用于对称加密的秘钥,可以调用allocKey生成，也可自己传入，无编码
	/// \param [in] 	len 	秘钥长度，与setAesOption传入的bits对应, 如AES-128的秘钥长度 128/8=16
	/// \param [out]  	outData 加密后并做Base64的数据。
	virtual bool aesEncryptWithKey(const void* plain, size_t plainlen, const unsigned char* key,
			size_t len, Infra::CString& outData)
		COMPONENT_UNIMPLEMENTED_OPERATION;

	/// 使用自己私钥解密数据
	/// \param [in] 	from 待解密的数据，数据不能经过任何编码
	/// \param [in] 	len 待解密的数据长度
	/// \param [in] rasPadding 	rsa加密数据填充方式,参照ERSAPADDTYPE，目前只支持E_PKCS1
	/// \param [out] 	to 解密后的数据
	virtual bool rsaDecrypt(const unsigned char* from, size_t len, ERSAPADDTYPE rsaPadding, Memory::CPacket& outData)
		COMPONENT_UNIMPLEMENTED_OPERATION;

	/// 使用公钥加密数据，不进行任何编码
	/// \param [in] 	strPublicKey 用于加密的公钥，格式"N:xx,E:xx"RSA的N和E是二进制串，进行过BaseString编码，N串为[0-9A-F]{密钥位数/4}.
	/// \param [in] 	from 待加密的数据
	/// \param [in] 	len 待加密的数据长度
	/// \param [in] 	rasPadding 	rsa加密数据填充方式,参照ERSAPADDTYPE，目前只支持E_PKCS1
	/// \param [out] 	outData 加密后的数据
	virtual bool rsaEncrypt(const char* strPublicKey, const unsigned char* from, size_t len,
			ERSAPADDTYPE rsaPadding, Memory::CPacket& outData)
		COMPONENT_UNIMPLEMENTED_OPERATION;

	/// 进行BaseString编码，每个字节高低4bit拆成两个可显字符，长度增加一倍,如0x1B->"1B"
	/// \param [in] from 		待编码的数据
	/// \param [out] len 		待编码的数据长度
	/// \param [out] outData 	编码后的数据
	virtual bool baseStringEncode(const unsigned char* from, size_t len, Infra::CString& outData)
		COMPONENT_UNIMPLEMENTED_OPERATION;

	/// 分配AES随机因子
	/// \param [out] key 	输入为用于存放生成的对称加密的秘钥缓存
	/// \param [in] len 	输入为想生成的秘钥长度
	virtual bool allocKey(unsigned char* key, size_t len)
		COMPONENT_UNIMPLEMENTED_OPERATION;

	/// 通过passwdin生成aes加密的key及iv
	/// \param [in] passin 	输入的原始密码
	/// \param [in] len 	输入的原始密码的字节数
	/// \param [out] key	用于存放生成的对称加密的秘钥缓存，为NULL表示不生成, 用于只更新IV, 不更新秘钥
	/// \param [in] keyLen	生成的秘钥字节数,为0表示不生成
	/// \param [out] iv		用于存放生成的对称加密的iv缓存，为NULL表示不生成
	/// \param [in] ivLen 	生成的iv字节数,为0表示不生成
	virtual bool passwdToKeyIv(const unsigned char* passin, int len,
			unsigned char* key, int keyLen, unsigned char* iv, int ivLen)
		COMPONENT_UNIMPLEMENTED_OPERATION;
	/// 保留到32个虚函数

	DAHUA_COMPONENT_FUNCTION_REVSERVED(20)
};

typedef Component::TComPtr<ICipher> ICipherPtr;

} // namespace SecurityUnit
} // namespace Dahua

extern "C" void initSecurityUnitCipherComponentLibrary();
#endif //__SECURITYUNIT_CIPHER_H__

