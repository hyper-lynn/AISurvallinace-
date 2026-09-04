/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_clientConfig_IntroductionInfosCheck_H_
#define _HSVIEW_CLIENT_API_clientConfig_IntroductionInfosCheck_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
一键oem协议，设备添加引导配置信息检查更新(使用clientUA内的信息)

【使用平台账号签名】
 */

typedef struct clientConfig_IntroductionInfosCheckRequest 
{
	HsviewRequest base;

	struct clientConfig_IntroductionInfosCheckRequestData
	{
		
		/** [O]表示该型号在对应配对模式未配置流程的情况下需要相应的默认流程，包含以下字符串中的一个或多个：SmartConfig，SoundWave，SoftAP，LAN，SIMCard，QRCode，SoundWaveV2，NBIOT，AP，为空时不会返回对应默认流程(兼容老app无此参数的情况) */
		DECLARE_LIST(CSTR) wifiConfigMode;
		/** APP展示的设备型号名称（产品称之为市场型号） */
		CSTR deviceModelName;
		/** APP本地缓存了配置后，请求使用上次请求配置服务返回的时间，检查是否需要更新配置 */
		CSTR updateTime;

	} data;

} clientConfig_IntroductionInfosCheckRequest;

C_API clientConfig_IntroductionInfosCheckRequest *HSAPI_INIT(clientConfig_IntroductionInfosCheckRequest);

typedef struct clientConfig_IntroductionInfosCheckResponse 
{
	HsviewResponse base;

	struct clientConfig_IntroductionInfosCheckResponseData
	{
		
		/** 是否更新，yes, no */
		CSTR isUpdated;
 
	} data;

} clientConfig_IntroductionInfosCheckResponse;

C_API clientConfig_IntroductionInfosCheckResponse *HSAPI_INIT(clientConfig_IntroductionInfosCheckResponse);

#endif
