#ifndef __SECURITYUNIT_CIPHERUTILS_H__
#define __SECURITYUNIT_CIPHERUTILS_H__

#include <stddef.h>
#include "Defs.h"

#ifdef  __cplusplus
extern "C" {
#endif

/////////////////////////////SecUnit 基础功能//////////////////////////////////////////////
// 功能：1.内部申请缓存释放。2.设备的证书私钥及配置文件等敏感信息的密钥获取。3.读取解密的文件
///////////////////////////////////////////////////////////////////////////////////

/// 释放申请的缓存
/// \param [in] outdata 		待释放的缓存
void SecUnit_Free(void* outData);

/// 获取当前生成密钥key的算法版本
/// \return 算法版本，具体值参见ESecUnitCipherVer
int SecUnit_GetCurKeyVersion();

/// 根据密钥因子，计算出密钥
/// \param [in] keyFixStr		密钥因子(目前获取解密文件的密钥为 设备类型+序列号；获取私钥密钥为 厂商+设备型号，两个因子直接相加)
/// \param [in] version			版本信息（0，表示最新版本算法，其它值表示对应的版本）
/// \param [out] outdata 		计算出的密钥(需要通过SecUnit_Free释放)，末尾会添加'\0'
/// \return 密钥实际长度，不计末尾长度'\0'
int SecUnit_GetEncryptKey(const char* keyFixStr, int version, unsigned char** outData);

/// 对相应的文件进行解密，解压缩输出
/// \param [in] path			文件路径，文件为加密
/// \param [in] decryptKey		解密密钥
/// \param [in] keyLen			密钥长度
/// \param [out] outdata 		文件进行解密，解压缩输出内容(需要通过SecUnit_Free释放)，末尾会添加'\0'
/// \return 数据的实际长度，不计末尾长度'\0'
int SecUnit_ReadCipherFile(const char* path, const unsigned char* decryptKey,
		size_t keyLen, unsigned char** outData);

/// 对相应的文件进行压缩加密
/// \param [in] path			文件路径
/// \param [in] encryptKey		解密密钥
/// \param [in] keyLen			密钥长度
/// \param [in] inputData		待写入的文件内容
/// \param [in] inputDataLen	待写入的文件内容的长度
/// \return 数据写入的实际长度，注意不一定等于输入长度，因为文件有添加头部和进行压缩，-1表示失败
int SecUnit_WriteCipherFile(const char* path, const unsigned char* encryptKey,
		size_t keyLen, const unsigned char* inputData, size_t inputDataLen);


/////////////////////////////SecUnit AES加解密///////////////////////////////////////////
// 功能：提供以下方式的AES加解密解密,参加ESECUNITAESPADDING和ESECUNITAESCIPHERBIT枚举值
// 加密方式通过SecUnit_SetAesOption可以设置
// 默认方式为 aes-cbc-256 数据不足采用PKCS7填充
///////////////////////////////////////ECB模式////////////////////////////////////////////
// 1. aes-ecb-128 数据不足采用0填充
// 2. aes-ecb-192 数据不足采用0填充
// 3. aes-ecb-256 数据不足采用0填充
///////////////////////////////////////////////////////////////////////////////////////
// 4. aes-ecb-128 数据不足采用PKCS7填充
// 5. aes-ecb-192 数据不足采用PKCS7填充
// 6. aes-ecb-256 数据不足采用PKCS7填充
////////////////////////////////////////CBC模式/////////////////////////////////////////
// 7. aes-cbc-128 数据不足采用0填充
// 8. aes-cbc-192 数据不足采用0填充
// 9. aes-cbc-256 数据不足采用0填充
///////////////////////////////////////////////////////////////////////////////////////
// 10. aes-cbc-128 数据不足采用PKCS7填充
// 11. aes-cbc-192 数据不足采用PKCS7填充
// 12. aes-cbc-256 数据不足采用PKCS7填充
///////////////////////////////////////////////////////////////////////////////////////
// 由于模式组合太多，这里不再全部说明

// 加密参数信息
typedef struct SecUnitAesCipher SecUnitAesCipher;

/// 创建AES加解密密句柄,创建默认的加密,采用aes-cbc-256，iv为"0000000000000000", pkcs7填充方式，加密方式
SecUnitAesCipher* SecUnit_CreateAesCipher();

/// 销毁AES加密句柄
void SecUnit_DestoryAesCipher(SecUnitAesCipher* secUnitAesCipher);

/// 设置加解密模式信息
/// \param [in] secUnitAesCipher		待修改的句柄，如果为NULL，创建一个新的句柄
/// \param [in] mode					AES加密方式
/// \param [in] bits					AES加密的位数
/// \param [out] iv 					AES加密的初始化向量，CBC模式下有用
/// \param [out] len 					AES加密的初始化向量的长度，目前固定为16
/// \param [out] aesPadding 			AES加密的填充方式
/// \return AES加密操作句柄，失败返回NULL
SecUnitAesCipher* SecUnit_SetAesOption(SecUnitAesCipher* secUnitAesCipher,
		ESecUnitAesCipherMode mode, ESecUnitAesCipherBit bits, const unsigned char* iv,
		size_t len, ESecUnitAesPadding aesPadding);

/// 不加密的key,进行解密
/// \param [in] secUnitAesCipher		操作句柄
/// \param [in] data					待解密的数据
/// \param [in] dataLen					待解密的数据长度
/// \param [in] key						解密密钥
/// \param [in] keyLen					密钥长度
/// \param [out] outdata 				解密后的(需要通过SecUnit_Free释放)，数据为二进制数据
/// \return 成功返回数据的实际长度，数据为二进制数据，失败返回-1
int SecUnit_AesDecrypt(const SecUnitAesCipher* secUnitAesCipher,
		const unsigned char* data, size_t dataLen, const unsigned char* key,
		size_t keyLen, unsigned char** outData);

/// 不加密的key,进行加密
/// \param [in] secUnitAesCipher		操作句柄
/// \param [in] data					待解密的数据
/// \param [in] dataLen					待解密的数据长度
/// \param [in] key						解密密钥
/// \param [in] keyLen					密钥长度
/// \param [out] outdata 				解密后的(需要通过SecUnit_Free释放)，数据为二进制数据
/// \return 成功返回数据的实际长度，数据为二进制数据，失败返回-1
int SecUnit_AesEncrypt(const SecUnitAesCipher* secUnitCipherHandle,
		const unsigned char* data, size_t dataLen, const unsigned char* key,
		size_t keyLen, unsigned char** outData);

/// 不加密的key,进行解密,区别于SecUnit_AesDecrypt接口，输出缓存自己申请，可以防止内存申请的性能消耗
/// \param [in] secUnitAesCipher		操作句柄
/// \param [in] data					待解密的数据
/// \param [in] dataLen					待解密的数据长度
/// \param [in] key						解密密钥
/// \param [in] keyLen					密钥长度
/// \param [out] outBuf 				输出缓存
/// \param [in] outBufLen 				输出缓存长度，缓存长度 = dataLen（输入数据的长度）
/// \return 成功返回数据的实际长度，数据为二进制数据，失败返回-1
int SecUnit_AesDecrypt1(const SecUnitAesCipher* secUnitAesCipher,
		const unsigned char* data, size_t dataLen, const unsigned char* key,
		size_t keyLen, unsigned char* outBuf, size_t outBufLen);

/// 不加密的key,进行加密，区别于SecUnit_AesEncrypt接口，输出缓存自己申请，可以防止内存申请的性能消耗
/// \param [in] secUnitAesCipher		操作句柄
/// \param [in] data					待解密的数据
/// \param [in] dataLen					待解密的数据长度
/// \param [in] key						解密密钥
/// \param [in] keyLen					密钥长度
/// \param [out] outBuf 				输出缓存
/// \param [in] outBufLen 				输出缓存长度，缓存长度一般要为dataLen+16，这样才能保证缓存足够
/// \return 成功返回数据的实际长度，数据为二进制数据，失败返回-1
int SecUnit_AesEncrypt1(const SecUnitAesCipher* secUnitCipherHandle,
		const unsigned char* data, size_t dataLen, const unsigned char* key,
		size_t keyLen, unsigned char* outBuf, size_t outBufLen);

/////////////////////////////SecUnit HMAC///////////////////////////////////////////
// 功能：提供以下方式的HMAC,通过枚举值SECUNITHMACMETHOD进行选择
// 1. hmac-md5
// 2. hmac-sha1
// 3. hmac-sha256
// 4. hmac-sha512
///////////////////////////////////////////////////////////////////////////////////////

typedef struct SecUnitHMAC SecUnitHMAC;

/// 创建hamc的操作句柄
/// \param [in] mode		hash算法模式，对应取值参照ESecUnitHmacMethod枚举值
/// \param [in] key			加密密钥
/// \param [in] len			加密密钥的长度
/// \return 失败返回NULL
SecUnitHMAC* SecUnit_HMACCreate(ESecUnitHmacMethod mode, const unsigned char* key, size_t len);

/// 释放句柄
/// \param [in] hmac 		操作句柄，后续hash接口使用
void SecUnit_HMACDestroy(SecUnitHMAC* hmac);

/// 可以多次调用。(用于分段数据hmac)
/// \param [in] hmac 	操作句柄，后续hash接口使用
/// \param [in] data	待操作的数据
/// \param [in] len		待操作的数据的长度
/// \return 成功返回0，失败返回-1
int SecUnit_HMACUpdate(SecUnitHMAC* hmac, const unsigned char* data, size_t len);

/// 结束对数据hashmac并输出结果
/// \param [in] hmac 			操作句柄，后续hash接口使用
/// \param [out] outData		hash得到的数据(需要通过SecUnit_Free释放)，数据为二进制数据
/// \return 成功返回hash得到的数据长度，数据为二进制数据，失败返回-1
int SecUnit_HMACFinal(SecUnitHMAC* hmac, unsigned char** outData);

/// 只对一段数据进行hash，并输出结果
/// \param [in] mode		hash算法模式，对应取值参照ESecUnitHmacMethod枚举值
/// \param [in] data		待操作的数据
/// \param [in] dataLen		待操作的数据的长度
/// \param [out] outData	hash得到的数据(需要通过SecUnit_Free释放)，数据为二进制数据
/// \param [in] key			加密密钥
/// \param [in] KeyLen		加密密钥的长度
/// \return 成功返回hash得到的数据长度，数据为二进制数据，失败返回-1
int SecUnit_HMAC(ESecUnitHmacMethod mode, const unsigned char* data, size_t dataLen,
		const unsigned char* key, size_t KeyLen, unsigned char** outData);

/////////////////////////////SecUnit RAND///////////////////////////////////////////
/// \param [out] buf       存放随机字节的缓存区
/// \param [in] len        缓冲区的长度
void SecUnit_Rand(void* buf, size_t len);

#ifdef  __cplusplus
}
#endif

#endif // __SECURITYUNIT_CIPHERUTILS_H__
