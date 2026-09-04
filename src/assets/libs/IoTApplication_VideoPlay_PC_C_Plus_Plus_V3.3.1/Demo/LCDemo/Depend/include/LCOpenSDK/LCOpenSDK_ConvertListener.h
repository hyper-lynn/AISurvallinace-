#ifndef _LCOPENSDK_CONVERTLISTENER_H__
#define _LCOPENSDK_CONVERTLISTENER_H__

class LCOPENSDK_EXPORT LCOpenSDK_ConvertListener
{
public:
	virtual ~LCOpenSDK_ConvertListener() {}

	/**
	 * 转换进度回调函数
	 *
	 * @param progress  [in] 进度：1-100
	 *
	 */
	virtual void  onConvertProgress(int progress, int index) = 0;

	/**
	 * 转换错误回调接口
	 *
	 * @param errorCode      [in] 错误码
	 *
	 */
	virtual void  onConvertError(int errorCode, int index) = 0;

	
	virtual void  onConvertFrame(void* data, int len, int frameType, int index) = 0;
};

#endif //_LCOPENSDK_CONVERTLISTENER_H__
