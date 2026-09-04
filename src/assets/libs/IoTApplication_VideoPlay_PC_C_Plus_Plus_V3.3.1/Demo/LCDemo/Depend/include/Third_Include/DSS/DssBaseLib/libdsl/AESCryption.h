#ifndef INCLUDE_AES_CRYPTION_H
#define INCLUDE_AES_CRYPTION_H

#include "libdsl/dslbase.h"

BEGIN_NAMESPACE_DSL
/////////////////////////////////////////////////

// 加密头数据
struct cryptHeader {
	unsigned short version;	// 控制向下兼容
							// 若后续加密方式、秘钥发生修改，高版本需要支持解密低版本加密的数据
	char reserved[30];		// 保留字段
};

class AESCryption
{
public:
	enum AESMode
	{
		AES_MODE_BEGIN		= 0,
		AES_MODE_DEFAULT	= AES_MODE_BEGIN,
		AES_MODE_ECB		= 1/*ECB*/,
		AES_MODE_CBC		= 2/*CBC*/,
		AES_MODE_CTR		= 3/*CTR*/,
		AES_MODE_OFB		= 4/*OFB*/,
		AES_MODE_CFB		= 5/*CFB*/,
		AES_MODE_END		= 10,
	};

public:
	AESCryption(AESMode mode = AES_MODE_CBC);
	~AESCryption();

public:
	// key不能最多不能超过32位,一般为16,24,32,不足的用'0'补齐
	int SetCryptionKey(unsigned char* key, int keyLen);
	int SetInitVector(unsigned char* iv, int ivLen);

	int AESEnCryption(const unsigned char* in, int inLen, unsigned char* out, int &outLen);
	int AESDeCryption(const unsigned char* in, int inLen, unsigned char* out, int &outLen);

private:
	AESMode			m_mode;

	void*			m_pEncKey;
	void*			m_pDecKey;
	unsigned char*	m_pIV;
};

/////////////////////////////////////////////////
END_NAMESPACE_DSL

#endif

