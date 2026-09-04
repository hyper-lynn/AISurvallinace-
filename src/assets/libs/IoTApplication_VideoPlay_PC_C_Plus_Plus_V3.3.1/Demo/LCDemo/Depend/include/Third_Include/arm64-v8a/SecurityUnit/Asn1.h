#ifndef __SECURITYUNIT_ASN1_H__
#define __SECURITYUNIT_ASN1_H__

#include <stddef.h>

#ifdef  __cplusplus
extern "C" {
#endif

// ASN1 编解码数据类型
typedef enum SECUNIT_EASN1TYPE
{
	SECUNIT_SM2SIG_TYPE = 0, 	// sm2 签名数据类型,编码后的长度最大为72字节
	SECUNIT_SM2CIPHER_TYPE, 	// sm2加密数据类型,编码后的长度为 原数据长度+96+编码增加的字节数（一般12字节，具体和原始数据长度有关）
}SECUNIT_EASN1TYPE;

/// asn1编码
/// \param [in] in 	输入数据
/// \param [in] inLen 	输入数据长度
/// \param [in] type 	输入数据类型
/// \param [out] out 	输出数据长度
/// \param [in] outLen 	输入时为输出缓存长度（缓存长度见EASN1TYPE注释）
/// \return 编码后的数据的实际长度
int SecUnit_asn1Encode(const unsigned char* in, size_t inLen, SECUNIT_EASN1TYPE type,
		unsigned char* out, size_t outLen);

/// asn1解码
/// \param [in] in 	输入数据
/// \param [in] inLen 	输入数据长度
/// \param [in] type 	输入数据类型
/// \param [out] out 	输出数据长度
/// \param [in] outLen 	输入时为输出缓存长度（缓存长度见EASN1TYPE注释）
/// \return 解码后的数据的实际长度
int SecUnit_asn1Decode(const unsigned char* in, size_t inLen, SECUNIT_EASN1TYPE type,
		unsigned char* out, size_t outLen);
		
#ifdef  __cplusplus
}
#endif

#endif // __SECURITYUNIT_ASN1_H__
