#ifndef _OPENAPIINFO_H_
#define _OPENAPIINFO_H_
#include <QString>

#define CA_PATH     "cert.pem"
#define CA_PATH_EN  "cert_en.pem"
#define HOST    "openapi.lechange.cn"
#define HOST_EN "developer-api-fe.dolynksecurity.com"
#define PORT    443

typedef struct OpenApiInitParam
{
    QString     host;
    int         port;
    QString     caPath;

    OpenApiInitParam()
    {
        port = 0;
    }
}OPEN_API_INIT_PARAM;

#endif /* _OPENAPIINFO_H_ */
