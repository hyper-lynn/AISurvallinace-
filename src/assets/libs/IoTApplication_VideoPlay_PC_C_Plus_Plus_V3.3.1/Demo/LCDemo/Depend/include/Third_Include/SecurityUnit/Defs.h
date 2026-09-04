#ifndef __SECURITYUNIT_DEFS_H__
#define __SECURITYUNIT_DEFS_H__

// Aes加解密分块长度
#define SECUNIT_AES_BLOCK_LEN 16

///////////////////////敏感信息加密枚举//////////////////////////////
// 加密算法版本
typedef enum {
	SECUNIT_CIPHER_LASTEST = 0,						// 最新版本
	SECUNIT_CIPHER_V1,
}ESecUnitCipherVer;

// 密钥因子索引
typedef enum {
	SECUNIT_OEM_MANUFACTURER = 0,				// 对应厂商及设备型号组成
	SECUNIT_SERIALNO_DEVTYPE,					// 对应设备类型及设备序列号
}ESecUnitECipherIndex;

//////////////////////RSA 填充方式枚举////////////////////////////////
typedef enum {
	SECUNIT_RSA_UNKNOWN = 0,
	SECUNIT_RSA_PKCS1,
	SECUNIT_RSA_OEAP,
}ESecUnitRSAPadding;

/////////////////////AES 加密相关枚举//////////////////////////////
// 加密方式
typedef enum {
	SECUNIT_ECB_MODE = 0,			// ECB
	SECUNIT_CBC_MODE,				// CBC
	SECUNIT_OFB_MODE,				// OFB
}ESecUnitCipherMode;

typedef ESecUnitCipherMode ESecUnitAesCipherMode;

// AES 填充方式
typedef enum {
	SECUNIT_AESUNKNOWN = 0,
	SECUNIT_ZERO_PADDING,								// 数据不是分块长度整数倍时采用0填充
	SECUNIT_AESZERO_PADDING = SECUNIT_ZERO_PADDING,		// 兼容老的AES命名方式
	SECUNIT_PKCS7_PADDING,
	SECUNIT_AESPKCS7_PADDING = SECUNIT_PKCS7_PADDING,	// 数据不是分块长度整数倍时采用PKCS7填充，兼容老的AES命名方式
	SECUNIT_NO_PADDING,									// 此时数据必须为加密分块的整数倍，DES填充方式(采用8byte分组)，AES 填充方式（采用16byte分组）
}ESecUnitCipherPadding;

typedef ESecUnitCipherPadding ESecUnitAesPadding;

// 加密的位数（加密的密钥长度的bit位）
typedef enum {
	SECUNIT_128_BIT = 128,		// 加密位数为128
	SECUNIT_192_BIT = 192,		// 加密位数为192
	SECUNIT_256_BIT = 256,		// 加密位数为256
	SECUNIT_64_BIT = 64,		// 加密位数为64(DES)
}ESecUnitCipherBit;

typedef ESecUnitCipherBit ESecUnitAesCipherBit;

///////////////////HMAC相关枚举值/////////////////////////////
typedef enum {
	SECUNIT_MD5HMAC = 0,
	SECUNIT_SHA1HMAC,
	SECUNIT_SHA256HMAC,
	SECUNIT_SHA512HMAC,
}ESecUnitHmacMethod;

#endif // __SECURITYUNIT_DEFS_H__
