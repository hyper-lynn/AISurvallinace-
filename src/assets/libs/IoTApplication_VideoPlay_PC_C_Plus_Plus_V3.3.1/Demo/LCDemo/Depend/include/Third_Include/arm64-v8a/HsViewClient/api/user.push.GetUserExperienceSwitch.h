/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_userPush_GetUserExperienceSwitch_H_
#define _HSVIEW_CLIENT_API_userPush_GetUserExperienceSwitch_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
海外：查询用户体验开关。（若之前用户没有设置过此开关，平台没有值，返回off；只有用户主动设置平台才会保存此值）
国内：仅使用logReportEnable字段，日志上报开关（登陆后调用）
【使用平台账号签名】
 */

typedef struct userPush_GetUserExperienceSwitchRequest 
{
	HsviewRequest base;

	struct userPush_GetUserExperienceSwitchRequestData
	{
		
		/** [int][O]保留 */
		int _nouse;

	} data;

} userPush_GetUserExperienceSwitchRequest;

C_API userPush_GetUserExperienceSwitchRequest *HSAPI_INIT(userPush_GetUserExperienceSwitchRequest);

typedef struct userPush_GetUserExperienceSwitchResponse 
{
	HsviewResponse base;

	struct userPush_GetUserExperienceSwitchResponseData
	{
		
		/** on打开,off关闭 */
		CSTR enable;
		/** [O]日志埋点上报频率控制，如：50，每次上传50条 */
		CSTR uploadLogNum;
		/** [O]埋点日志上报开关，true：表示可以上报，false：表示不能上报，仅对神策埋点有效，不影响原埋点业务，即仅对UserEventLogReport协议中logsV2生效，与logs无关 */
		CSTR logReportEnable;
 
	} data;

} userPush_GetUserExperienceSwitchResponse;

C_API userPush_GetUserExperienceSwitchResponse *HSAPI_INIT(userPush_GetUserExperienceSwitchResponse);

#endif
