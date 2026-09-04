#ifndef __SECURITYUNIT_KDF_H__
#define __SECURITYUNIT_KDF_H__

#ifdef  __cplusplus
extern "C" {
#endif

// 算法版本类型
typedef enum
{
	SECUNIT_VERSION_SHA2 = 1, 	// 支持sha256和sha512
	SECUNIT_VERSION_SHA3, 		// 支持sha3-256和sha3-512,目前版本不支持
	SECUNIT_VERSION_SM3, 		// 支持SM3,目前版本不支持
}SECUNIT_ALGORITHM_VERSION;

// 生成的密钥长度
typedef enum
{
	SECUNIT_DKLEN2048 = 2048, 		// 2048 bit即256字节
	SECUNIT_DKLEN1024 = 1024, 		// 1024 bit即128字节
	SECUNIT_DKLEN512 = 512, 		// 512 bit即64字节
	SECUNIT_DKLEN256 = 256, 		// 256 bit即32字节
}SECUNIT_DERIVATIONKEYLENGTH;

// 特征因子参数
typedef struct SecUnit_CharacteristicFactor
{
	unsigned char* factor;
	int factorSize;
}SecUnit_CharacteristicFactor;

// 盐值参数
typedef struct SecUnit_SaltStructs
{
	unsigned char salt[512/8]; // 512bit
}SecUnit_SaltStructs;

/// 基于ECCE(提取-混淆-压缩-扩展)模型生成衍生密钥
/// \param [in] algVer 			hash算法
/// \param [in] factors 		特征因子
/// \param [in] factorsCount 	特征因子个数（必须>1&& <7）
/// \param [in] salts		 	盐值
/// \param [in] saltsCount 		盐值数目(>=1即可)	
/// \param [in] keyLen 			期望生成的密钥长度,参加SECUNIT_DERIVATIONKEYLENGTH
/// \param [out] keyBuf 		输出的密钥缓存，要保证缓存长度至少为keyLen		
/// \return < 0表示失败，=0表示成功
int SecUnit_getDerivationKeyByECCE(SECUNIT_ALGORITHM_VERSION algVer,
		const SecUnit_CharacteristicFactor* factors, int factorsCount,
		const SecUnit_SaltStructs* salts, int saltsCount,
		SECUNIT_DERIVATIONKEYLENGTH keyLen, unsigned char* keyBuf);

/// 基于ECE2(提取-编码变换-扩展)模型生成衍生密钥
/// \param [in] algVer 			hash算法
/// \param [in] factors 		特征因子
/// \param [in] factorsCount 	特征因子个数（必须>1&& <7）
/// \param [in] salts		 	盐值
/// \param [in] saltsCount 		盐值数目(>=1即可)	
/// \param [in] keyLen 			期望生成的密钥长度,参加SECUNIT_DERIVATIONKEYLENGTH
/// \param [out] keyBuf 		输出的密钥缓存，要保证缓存长度至少为keyLen	
/// \return < 0表示失败，=0表示成功
int SecUnit_getDerivationKeyByECE2(SECUNIT_ALGORITHM_VERSION algVer,
		const SecUnit_CharacteristicFactor* factors, int factorsCount,
		const SecUnit_SaltStructs* salts, int saltsCount,
		SECUNIT_DERIVATIONKEYLENGTH keyLen, unsigned char* keyBuf);


/// 封装openssl的PKCS5_PBKDF2，根据pass口令生成keyBuf密钥，密钥长度由哈希算法决定，SHA1生成20字节密钥，SHA256生成32字节密钥
/// \param [in] pass			被衍生的密钥
/// \param [in] passlen 		密钥长度
/// \param [in] salt			盐值
/// \param [in] saltlen			盐值长度
/// \param [in] iter			迭代次数 （建议10000次左右）
/// \param [in] digest			哈希算法（0--SHA1， 1--SHA256）
/// \param [in] keyLen 			输出密钥缓冲长度（指定不同hash算法生成的密钥长度不同）
/// \param [out] keyBuf 		输出的密钥缓存，要保证缓存长度至少为keyLen（生成为二进制密钥，不能当字符串使用）	
/// \return < 0表示失败，=0表示成功
int SecUnit_PKCS5_PBKDF2(const char *pass, int passlen,
					  const unsigned char *salt, int saltlen, int iter,
					  int digest, int keylen, unsigned char *keyBuf);

		
#ifdef  __cplusplus
}
#endif

#endif // __SECURITYUNIT_KDF_H__
