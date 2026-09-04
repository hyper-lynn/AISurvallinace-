/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_UserLogin_H_
#define _HSVIEW_CLIENT_API_UserLogin_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
客户端调用平台服务之前，必须先调用本接口进行用户登录。
【使用平台账号签名】
 */

typedef struct UserLoginRequest 
{
	HsviewRequest base;

	struct UserLoginRequestData
	{
		
		/** 客户端名称。如果是浏览器，填浏览器类型（User-Agent）；如果是手机，填手机型号，如“A199” */
		CSTR clientName;
		/** [O]app注册推送服务器后，推送服务器分配的ID */
		CSTR appId;

	} data;

} UserLoginRequest;

C_API UserLoginRequest *HSAPI_INIT(UserLoginRequest);

typedef struct UserLoginResponse 
{
	HsviewResponse base;

	struct UserLoginResponseData
	{
		
		/** 用户昵称 */
		CSTR nickname;
		/** 客户端第一次登陆时，平台生成的全局唯一标示 */
		CSTR clientId;
		/** [long]用户Id */
		int64 userId;
		/** 用户邮箱,为空表示未绑定邮箱 */
		CSTR email;
		/** 用户头像URL */
		CSTR userIcon;
		/** struct of UserLoginResponseData_LastLoginInfo */
		struct UserLoginResponseData_LastLoginInfo {
			/** 登陆时参考地址，如“浙江”，不一定准确 */
			CSTR refLocation;
			/** 客户端名称 */
			CSTR clientName;
			/** [long]登陆时的UNIX时间戳秒 */
			int64 timestamp;
			/** 客户端类型，web或phone */
			CSTR clientType;
			/** 登陆时的IP地址，如1.2.3.4 */
			CSTR ip;
		} lastLoginInfo;
		/** struct of UserLoginResponseData_P2pServer */
		struct UserLoginResponseData_P2pServer {
			/** [int]P2P服务端口 */
			int port;
			/** P2P服务IP地址 */
			CSTR ip;
		} p2pServer;
		/** [int]主用户类型：0-手机号，1-微信，2-邮箱 */
		int userType;
		/** 用户手机号码,为空表示未绑定手机号 */
		CSTR phoneNumber;
		/** 平台账号用户名 */
		CSTR username;
		/** [int]推送状态，0表示不推送，1表示推送，-1表示没有设置推送信息，需要调用SetPushConfig进行设置 */
		int pushStatus;
		/** 用户昵称 */
		CSTR wxNickname;
 
	} data;

} UserLoginResponse;

C_API UserLoginResponse *HSAPI_INIT(UserLoginResponse);

#endif
