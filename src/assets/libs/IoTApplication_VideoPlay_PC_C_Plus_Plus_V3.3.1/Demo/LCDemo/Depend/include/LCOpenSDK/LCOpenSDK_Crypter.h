#ifndef _LCOPENSDK_CRYPTER_H__
#define _LCOPENSDK_CRYPTER_H__

#include "lcopensdk_global.h"
#include "LCOpenSDK_Define.h"


class LCOPENSDK_EXPORT LCOpenSDK_Crypter
{
public:
	LCOpenSDK_Crypter();
	~LCOpenSDK_Crypter();

	bool initWithRuleVersion(Dahua::LCOpenSDK::E_RULE_VERSION rule);

	Dahua::LCOpenSDK::E_ENCRYPT_RESULT encryptData(const char* pSrcBufIn, int srcBuflen, const char* key, int encryptPos, int encryptLength, char* dstBufOut, int &dstBufLenOut);

	Dahua::LCOpenSDK::E_ENCRYPT_RESULT verifyCrypt(const char* key, const char* pSrcBufIn, int srcBuflen, char* dstBufOut, int & dstBufLenOut);

	Dahua::LCOpenSDK::E_ENCRYPT_RESULT encryptDeviceInfoData(	const char *sBuf, 
																int iLen, 
																const char *sDevId, 
																int iDevIdLen, 
																const char *sAppSecret, 
																int iAppSecretLen, 
																char *sBufOut, 
																int &iBufLenOut);

	Dahua::LCOpenSDK::E_ENCRYPT_RESULT encryptDevPwd(			const char *sBuf, 
																int iLen, 
																const char *sIv, 
																int iIvLen, 
																const char *sAppSecret, 
																int iAppSecretLen, 
																char *sBufOut, int &iBufLenOut);


	Dahua::LCOpenSDK::E_DECRYPT_RESULT decryptDataWithHead(const char* pSrcBufIn, int srcBuflen, const char* key, const char *sDevId, const char *sDevPwd, char* dstBufOut, int &dstBufLenOut);

	Dahua::LCOpenSDK::E_DECRYPT_RESULT decryptDataWithoutHead(const char* pSrcBufIn, int srcBuflen, const char* key, const char *sDevId,const char *sDevPwd, char* dstBufOut, int &dstBufLenOut);

	Dahua::LCOpenSDK::E_DECRYPT_RESULT decryptDeviceInfoData(	const char *sBuf, 
																int iLen, 
																const char *sDevId, 
																int sDevIdLen, 
																const char *sPlayCode, 
																int sPlayCodeLen, 
																char *sBufOut, 
																int &iBufLenOut);

	Dahua::LCOpenSDK::E_DECRYPT_RESULT decryptDeviceInfo(	const char *sBuf, 
															int iLen, 
															const char *sDevId, 
															int sDevIdLen, 
															const char *sSalt, 
															int sSaltLen, 
															char *sBufOut, 
															int &iBufLenOut);

	Dahua::LCOpenSDK::E_DECRYPT_RESULT decryptIOTPlayInfo( 	const char *sBuf, 
															int iLen, 
															const char *sDevId, 
															int sDevIdLen, 
															const char *sSalt, 
															int sSaltLen, 
															char *sBufOut, 
															int &iBufLenOut);

	Dahua::LCOpenSDK::E_DECRYPT_RESULT decryptIOTP2PInfo(const char *sBuf, 
															int iBufLen, 
															const char *sSalt, 
															int iSaltLen, 
															char *sBufOut, 
															int &iBufLenOut);


protected:
	void uninitCrypter();

private:
	void* m_interfaceLock;
	void* m_interfaceLockDecrypter;
	void* m_hLCOpenSDK_Crypter_Inside;
};

#endif //_LCOPENSDK_CRYPTER_H__
