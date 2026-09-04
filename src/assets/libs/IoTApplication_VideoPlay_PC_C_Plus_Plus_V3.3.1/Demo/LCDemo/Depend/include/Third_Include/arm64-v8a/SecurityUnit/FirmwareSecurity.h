/*
 *   固件加解密接口头文件
*/
#ifndef __SECURITYUNIT_FIRMWARESECURITY_H__
#define __SECURITYUNIT_FIRMWARESECURITY_H__

#ifdef  __cplusplus
extern "C" {
#endif

/// 传入密钥因子最大长度
#define SECUNIT_MAX_FACTOR_KEY_LENTH 16
/// 每次加密块大小
#define SECUNIT_ENCRYPT_BLOCK_SIZE 512


/// 密钥用途
enum SecUnitKeyUseMode
{
	SecUnitKernelCrypto = 0, 	// 用于内核加解密密钥标志
	SecUnitRootfsCrypto,		// 用于文件系统加解密密钥标志
	SecUnitbootenvCrypto,		// 用于boot加解密密钥标志
};

/// 设置固件加密因子
/// \param [in] key		用户设置的密钥因子
/// \param [in] length	对应密钥因子长度,最长为16字节
/// \param [in] flag	密钥标志位 0表示 kernel 1表示文件系统,2表示boot，参见SecAppKeyUseMode
/// \return 0表示设置密钥因子正常 -1表示设置密钥因子异常
int SecUnit_SetKeyFactor(const unsigned char *key, unsigned int length, int flag);

/// 加解密固件,如果加密数据输入长度不足512将填充0
/// \param [in] inputData	输入数据
/// \param [in] inputLen	输入数据长度
/// \param [out] outData	输出数据
/// \param [in] outLen		输出缓存长度
/// \param [in] flag		模块标志位，采用掩码:低4bit:0x0表示内核加解密，0x1表示文件系统加解密，0x2表示boot加解密，高4bit: 0x0表示数据加密，0x1表示数据解密
/// \param [in] jumpNum		跳块的数量，0：不跳块（全部加密），第一个512个字节一定会加密,后续将跳过512*jumpNum字节，再加密512字节，这样循环进行
/// \param [in/out] count	当前整体数据的已经加解密密的块数目主要用于支持分块加解密，对某个整体数据解密让count为0即可，不能传NULL,对于分块加解密，第二次解密参数为第一次的返回值
/// \return 写入输出缓存的数据长度，-1表示失败
int SecUnit_EncryptFirmware(const unsigned char *inputData, unsigned int inputLen, unsigned char *outData,
		unsigned int outLen, unsigned char flag, unsigned int jumpNum, int* count);

#ifdef  __cplusplus
}
#endif

#endif //__SECURITYUNIT_FIRMWARESECURITY_H__

