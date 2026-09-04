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
    int startCloudDownload(int index, const char* filepath, const char* deviceID, int channelID, const char* recordId, int needBeginTime, int needEndTime, int offsetTime, const char* playInfo, const char* signatureUrl, const char* recordPath, const char* recordRegionId);
    int startDownload(int index, const char* token, const char* filepath, const char* deviceID, const char* decryptKey, const char* fileID, int needBeginTime, int needEndTime, const char* playInfo, int channelID);
    int startDownloadWithJsonString(int index, const char* jsonString);
	int stopDownload(int index);
    void setDownloadListener(LCOpenSDK_DownloadListener* downloadListener);
    LCOpenSDK_DownloadListener* getDownloadListener();

private:
    void* m_hLCOpenSDK_Download_Inside;
    static LCOpenSDK_Download* sm_instance;
};

#endif /* _LCOPENSDK_DOWNLOAD_H_ */
