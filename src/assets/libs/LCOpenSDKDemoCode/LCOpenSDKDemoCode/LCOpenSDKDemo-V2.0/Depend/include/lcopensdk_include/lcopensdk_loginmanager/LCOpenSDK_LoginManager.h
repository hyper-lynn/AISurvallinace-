#ifndef _LCOPENSDK_LOGINMANAGER_H_
#define _LCOPENSDK_LOGINMANAGER_H_

#include <string>
#include "lcopensdk_global.h"
#include "LCOpenSDK_LoginListener.h"
#include "lcopensdk_api/LCOpenSDK_Define.h"

class LCOPENSDK_EXPORT LCOpenSDK_LoginManager
{
private:
	LCOpenSDK_LoginManager();
	~LCOpenSDK_LoginManager();

public:
	static LCOpenSDK_LoginManager* getInstance();
	
	/*****************************************************************************
	* @函数功能: P2P拉流预打洞操作（批量设备预打洞同步操作）
	* @参数 1  : token(userToken或accessToken)
	* @参数 2  : 添加预打洞设备deviceJsonString[in] json数组格式 [{"PlayToken":string,  "Sn":string}]
	* @返 回 值:  true/false
	*****************************************************************************/
	bool addDevices(const char* token,const char* deviceJsonString);

	/*****************************************************************************
	* @函数功能: P2P拉流预打洞操作（批量预打洞接口异步操作）
	* @参数 1  : token(userToken或accessToken)
	* @参数 2  : 添加预打洞设备deviceJsonString[in] json数组格式 [{"PlayToken":string,  "Sn":string}]
	* @返 回 值:  true/false
	*****************************************************************************/
	bool addDevicesAsync(const char* token,const char* deviceJsonString);

	unsigned short getNetsdkP2pPort(const char* token, const char* deviceId);

	unsigned short getP2pPort(const char* token, const char* deviceId, unsigned short port, unsigned int timeout);

	/*****************************************************************************
	* @函数功能: 获取P2P端口号（需先进行addDevice操作）
	* @参数 1  : token(userToken或accessToken)
	* @参数 2  : playToken
	* @参数 3  : deviceId
	* @参数 4  : 超时时间
	* @返 回 值:  true/false
	*****************************************************************************/
	unsigned short getP2pPort(const char* token, const char *playToken,const char* deviceId,unsigned int timeout);

	/*****************************************************************************
	* @函数功能: 获取P2P穿透类型
	* @返 回 值:  0:P2P_Local, 1:P2P_P2P 
	*****************************************************************************/
	LCOpenSDK_P2P_LINKTYPE getP2PLinkType(const char* deviceId,const char* devicePid);

	void setLoginListener(LCOpenSDK_LoginListener* loginListener);

private:
	void* m_hLCOpenSDK_LoginManager_Inside;
	static LCOpenSDK_LoginManager* sm_instance;
};

#endif /* _LCOPENSDK_LOGINMANAGER_H_ */
