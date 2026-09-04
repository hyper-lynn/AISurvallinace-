#ifndef _LCOPENSDK_LOGINMANAGER_H_
#define _LCOPENSDK_LOGINMANAGER_H_

#include <string>
#include "lcopensdk_global.h"
#include "LCOpenSDK_LoginListener.h"
#include "Third_Include/Infra/IntTypes.h"
#include <vector>

class LCOPENSDK_EXPORT LCOpenSDK_LoginManager
{
private:
    LCOpenSDK_LoginManager();
    ~LCOpenSDK_LoginManager();

public:
    static LCOpenSDK_LoginManager* getInstance();

	struct P2PServerInfo {
		std::string p2pKey;
		int port;
		std::string p2pAuthId;
		std::string host;
		int type;
		std::string userAuthId;
	};

	/**
    * 初始化登录组件（在调用此接口之前，只有addDevices会生效，其他接口均不效)
    *
    * @param p2pSerIP:    p2p 服务器地址
    * @param p2pSerPort:  p2p 服务器端口号
    * @param username:    p2p 服务器用户名
    * @param pwd:         p2p 服务器密钥
    * @param isRelay:     p2p relay开关
    * @return 返回初始化是否成功
    * - true  成功
    * - false 失败
    */
	bool init(const char* p2pSerIP, uint16_t p2pSerPort, const char* username, const char* pwd, bool isRelay, int p2pServerType);
	bool initNetSDK();

	bool initP2PSeverAfterSDK(const char* p2pSerIP, uint16_t p2pSerPort, const char* userName, const char* pwd, bool isRelay, int p2pServerType, const char* uuid);

	/**
	 * 使用p2p服务地址、鉴权账户和密码初始化登陆组件
	 * @param p2pSerIP:    p2p 服务器地址
	 * @param p2pSerPort:  p2p 服务器端口号
	 * @param protoType: 0-HTTP，1-HTTPS
	 * @param timeout: 统计服务信令交互超时
	 */
	bool initReporterSvrWithHost(const char* p2pSerIP, uint16_t p2pSerPort, int protoType, int timeout);

	/**
    * 增加p2p服务器，添加无用的服务会影响打洞性能
    *
    * @param p2pSerIP:    p2p 服务器地址
    * @param p2pSerPort:  p2p 服务器端口号
    * @param username:    p2p 服务器用户名
    * @param pwd:         p2p 服务器密钥
    * @param isRelay:     p2p relay开关
    * @return 返回初始化是否成功
    * - true  成功
    * - false 失败
    */
	bool addP2pSvr(const std::string &p2pSerIP, const uint16_t p2pSerPort, const std::string &username, const std::string & pwd,bool isRelay, int p2pServerType, const char* uuid);

	/**
	*初始化OZ P2P,使用OZ库的情况下需要调用 
	* @param path:         证书路径
	*/
	bool startOzP2P(const std::string path);

	/**                                                                     
	*关闭OZ P2P
	*/
	bool destroyNetSDKHandleByOZ(std::string devID);

	/**
	*获取OZ设备登陆句柄
	*/
	void* getNetSDKHandleByOZ(std::string devSeq,std::string devID,std::string username,std::string psw,int iPort,int iTimeout,std::string &logInfoOut);

	/**
     * 反初始化接口
     * @return void
     *
    */
	void unInit();

	/**
    * 批量删除设备
    *
    * @param deviceJsonString[in] [{"Sn":string, "Type":UINT,"Port":UINT,"User":string, "Pwd":string, "IP":string},{},...]
    *
    *           Type: 2  IP:必填
    * @return 返回删除是否成功
    * - true  成功
    * - false 失败
    */
	// bool delDevices(const std::string &deviceJsonString);
	bool delAllDevices();

	/**
    * 设置预登录最大数量
    *
    * @param maxDeviceNum
    */
	void setMaxDeviceNum(uint32_t maxDeviceNum);


    /**
     * （批量）添加预打洞设备
     *
     * @param deviceJsonString[in] [{"Sn":string, "Type":UINT,"Port":UINT,"User":string, "Pwd":string},{},...]
     *           Type---0:大华P2P设备 1:乐橙设备 
     * @return "OK"代表成功，其他代表失败，具体原因得看日志 
     */
    // bool addDevices(const char* token, const char* deviceJsonString);

	bool addDevices(const char* deviceIds[], const char* playInfos[], int count);

	bool delDevicesWithDeviceIds(const char* deviceIds[]);

	bool configureP2PServers(const char* p2pKey, const char* p2pInfo, int encryptMode);

    unsigned short getNetsdkP2pPort(const char* token, const char* deviceId);

    unsigned short getP2pPort(const char* token, const char* deviceId, unsigned short port, unsigned int timeout);

    void setLoginListener(LCOpenSDK_LoginListener* loginListener);

private:
	
	void parseP2PServiceInfo(const char* jsonArrayString, std::vector<P2PServerInfo>& hostList);

	const char* decryptP2PServiceInfo(const char* key, const char* data, int encryptMode, std::string &outDecrypted);
	
    static LCOpenSDK_LoginManager* sm_instance;
	void* m_hLCOpenSDK_LoginManager_Inside;
};

#endif /* _LCOPENSDK_LOGINMANAGER_H_ */
