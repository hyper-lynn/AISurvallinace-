#ifndef _LCOPENSDK_API_H_
#define _LCOPENSDK_API_H_

#include "lcopensdk_global.h"

struct PTZParams
{
    const char* deviceId;
    const char* playInfo;
    int channelId;
    const char* operation;
    int duration;
    double speed;
};

class LCOPENSDK_EXPORT LCOpenSDK_Api
{
private:
    LCOpenSDK_Api();
    ~LCOpenSDK_Api();

public:
    static LCOpenSDK_Api* GetInstance();
    void initOpenApi(const char* host, int port, const char* caPath);
    int request(void* req, void* resp, int timeout, void* pOpenApiClient = 0, const char* playInfo = "");
    void uninitOpenApi();

	void setLoggerStatus(bool enabled);
	int controlMovePtz(const PTZParams& params);

private:
    void* m_hLCOpenSDK_Api_Inside;
    static LCOpenSDK_Api* sm_instance;

};

#endif /* _LCOPENSDK_API_H_ */
