#ifndef _LCOPENSDK_CONVERT_H__
#define _LCOPENSDK_CONVERT_H__

#include "lcopensdk_global.h"
#include "LCOpenSDK_Define.h"
#include "LCOpenSDK/LCOpenSDK_ConvertListener.h"

class LCOPENSDK_EXPORT LCOpenSDK_Convert
{
public:
	LCOpenSDK_Convert();
	~LCOpenSDK_Convert();

	void setListener(LCOpenSDK_ConvertListener* listener);

	int getIndex();

	void setIndex(int index);

	int startConvert(const char* filepath,const char* dstFile, Dahua::LCOpenSDK::E_MEDIA_CONVERT_TYPE type);

	int startConvertReal(Dahua::LCOpenSDK::E_MEDIA_CONVERT_TYPE type);

	int putData(void* data, int len);

	int stopConvert();
private:
	void* m_interfaceLock;
	void* m_hLCOpenSDK_Convert_Inside;
};

#endif //_LCOPENSDK_CONVERT_H__
