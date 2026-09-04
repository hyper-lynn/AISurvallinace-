#ifndef _LCOPENSDK_DOWNLOAD_H_
#define _LCOPENSDK_DOWNLOAD_H_

#include "lcopensdk_global.h"
#include "LCOpenSDK_DownloadListener.h"

class LCOPENSDK_EXPORT LCOpenSDK_Download
{
private:
    LCOpenSDK_Download();
    ~LCOpenSDK_Download();

public:
    static LCOpenSDK_Download* getInstance();
	// 云录像  开始
	int startDownload(int index, const char* token, const char* filepath, const char* deviceID, int channelID, const char* decryptKey, const char* recordRegionID, int cloudRecordType, int timeout);
    
	/**
	* 开始本地录像下载（按文件）
	* @param   [in] index                                   下载唯一标示，上层传入
	* @param   [in] token                                   token
	* @param   [in] filePath                                保存下载文件路径
	* @param   [in] deviceID                                设备序列号
	* @param   [in] decryptkey                              解密秘钥
	* @param   [in] fileId                                  文件名称
	* @param   [in] isTls                                   是否采用TLS加密传输（参数默认填false）
    * @param   [in] speed                                   下载速率，1/2/4/8/16，1表示按正常视频播放的速度下载                              
	* @return  int                                          0/非0 成功/失败
	*/
	int startDownload(
		int index,
		const char* token,
		const char* filepath,
		const char* deviceID, 
		const char* decryptKey,
		const char* fileID, 
		bool isTls,
		double speed = 1.0);
    
	/**
	* 开始本地录像下载（按时间）
	* @param   [in] index                                   下载唯一标示，上层传入
	* @param   [in] token                                   token
	* @param   [in] filePath                                保存下载文件路径
	* @param   [in] deviceID                                设备序列号
	* @param   [in] decryptkey                              解密秘钥
	* @param   [in] channelID                               通道号
	* @param   [in] beginTime                               录像开始时间，Unix时间戳
	* @param   [in] endTime                                 录像结束时间，Unix时间戳
	* @param   [in] isTls                                   是否采用TLS加密传输
    * @param   [in] speed                                   下载速率，1/2/4/8/16，1表示按正常视频播放的速度下载                             
	* @return  int                                          0/非0 成功/失败
	*/
	int startDownload(
		int index, 
		const char* token,
		const char* filepath, 
		const char* deviceID,
		const char* decryptKey,
		int channelID,
		long beginTime,
		long endTime, 
		bool isTls,
		double speed = 1.0);
    
	// 停止下载
	int stopDownload(int index);

	// 设置监听
    void setDownloadListener(LCOpenSDK_DownloadListener* downloadListener);
    LCOpenSDK_DownloadListener* getDownloadListener();

private:
    void* m_hLCOpenSDK_Download_Inside;
    static LCOpenSDK_Download* sm_instance;
};

#endif /* _LCOPENSDK_DOWNLOAD_H_ */
