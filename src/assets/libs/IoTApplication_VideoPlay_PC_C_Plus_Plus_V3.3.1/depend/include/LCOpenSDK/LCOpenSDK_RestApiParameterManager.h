#ifndef _LCOPENSDK_RESTAPIPARAMETERMANAGER_H__
#define _LCOPENSDK_RESTAPIPARAMETERMANAGER_H__

#include "lcopensdk_global.h"
#include <string>

class LCOPENSDK_EXPORT LCOpenSDK_RestApiManager 
{
public:
	typedef struct _RestApiCfg {
	public:
		char _host[128];
		int _port;
		char _clientType[128];
		char _clientID[128];
		char _clientVersion[128];
		char _project[128];
		char _pushID[128];
		char _authUserName[128];
		char _authPwdMd5[128];

		//for app 3.3
		char _clientOV[128];
		char _clientOS[128];
		char _terminalModel[128];
		char _terminalID[128];
		char _language[128];
		char _clientProtoVersion[128];
		char _appID[128];
		int _isHTTPS;
		char _caPath[128];
		int _isUseCA;

		//for lcopensdk
		char lcopen_safe_code[128];
		char lcopen_sdk_version[128];
		char lcopen_api_version[128];
		char lcopen_os_version[128];
		char lcopen_type[128];
		char lcopen_mac[128];
		char lcopen_host[128];
		int         lcopen_port;
		char lcopen_ca_path[128];
		char lcopen_appId[128];
		char lcopen_appSecret[128];

		//for cos 
		char openUserId[256];
		char appSource[256];
		char clientUaInfo[256];
		_RestApiCfg() {
			reset();
		}

		void reset() {
			memset(_host,0,sizeof(_host));
			_port = 0;
			memset(_clientType,0,sizeof(_clientType));
			memset(_clientID,0,sizeof(_clientID));
			memset(_clientVersion,0,sizeof(_clientVersion));
			memset(_project,0,sizeof(_project));
			memset(_pushID,0,sizeof(_pushID));
			memset(_authUserName,0,sizeof(_authUserName));
			memset(_authPwdMd5,0,sizeof(_authPwdMd5));

			memset(_clientOV,0,sizeof(_clientOV));
			memset(_clientOS,0,sizeof(_clientOS));
			memset(_terminalModel,0,sizeof(_terminalModel));
			memset(_terminalID,0,sizeof(_terminalID));
			memset(_language,0,sizeof(_language));
			memset(_clientProtoVersion,0,sizeof(_clientProtoVersion));
			memset(_appID,0,sizeof(_appID));
			_isHTTPS = 0;
			memset(_caPath,0,sizeof(_caPath));
			_isUseCA = 0;

			memset(lcopen_safe_code,0,sizeof(lcopen_safe_code));
			memset(lcopen_sdk_version,0,sizeof(lcopen_sdk_version));
			memset(lcopen_api_version,0,sizeof(lcopen_api_version));
			memset(lcopen_os_version,0,sizeof(lcopen_os_version));
			memset(lcopen_type,0,sizeof(lcopen_type));
			memset(lcopen_mac,0,sizeof(lcopen_mac));
			memset(lcopen_host,0,sizeof(lcopen_host));
			lcopen_port = 0;
			memset(lcopen_ca_path,0,sizeof(lcopen_ca_path));
			memset(lcopen_appId,0,sizeof(lcopen_appId));
			memset(lcopen_appSecret,0,sizeof(lcopen_appSecret));
		}
	}RestApiCfg;


private:
	LCOpenSDK_RestApiManager();
	~LCOpenSDK_RestApiManager();

public:
	static LCOpenSDK_RestApiManager* getInstance();

	bool initRestWithParameter(const LCOpenSDK_RestApiManager::RestApiCfg & param);

	void uninitRestWithParameter();

	LCOpenSDK_RestApiManager::RestApiCfg* getRestApiParameter();
	
	bool getRestApiParameter(void* pRestParam);

private:
	static LCOpenSDK_RestApiManager* sm_instance;
	LCOpenSDK_RestApiManager::RestApiCfg m_restApiCfg;

	
};

#endif //_LCOPENSDK_RESTAPIPARAMETERMANAGER_H__