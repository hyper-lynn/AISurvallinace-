#ifndef INCLUDE_RSA_CRYPTION_H
#define INCLUDE_RSA_CRYPTION_H

#include "libdsl/dslbase.h"

BEGIN_NAMESPACE_DSL
/////////////////////////////////////////////////

class RSACryption
{
public:
	RSACryption();
	~RSACryption();

public:
	// 使用内部产生的密钥对
	int GenerateRSAKey(int length = 2048);
	// 使用外部导入的密钥对
	int SetPrivateKey(const char* privateKey, int privateKeyLen);
	// 使用外部导入的公钥，PrivateDecrypt不可用
	int SetPublicKey(const char* publicKey, int publicKeyLen);

	int GetPublicKey(char* publicKey, int &publicKeyLen);

	int PublicEncrypt(const unsigned char* from, int fromLen, unsigned char* to, int& tolen);
	int PrivateDecrypt(const unsigned char* from, int fromLen, unsigned char* to, int& tolen);

private:
	void*	m_rsa;
	bool	m_bPublicOnly;
};

/////////////////////////////////////////////////
END_NAMESPACE_DSL

#endif
