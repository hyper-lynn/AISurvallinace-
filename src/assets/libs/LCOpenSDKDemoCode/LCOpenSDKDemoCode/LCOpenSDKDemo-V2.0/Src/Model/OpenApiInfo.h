#ifndef _OPENAPIINFO_H_
#define _OPENAPIINFO_H_
#include <QString>

#define CA_PATH     "cert.pem"
#define CA_PATH_EN  "cert_en.pem"
/*
  国内测试：funcopenapi.lechange.cn
  国内线上：openapi.lechange.cn
*/

#define HOST    "funcopenapi.lechange.cn"  
#define HOST_EN "openapi.easy4ip.com"
#define PORT    443

typedef struct OpenApiInitParam
{
	QString     host;
	int         port;
	QString     caPath;
	QString     appID;
	QString     appSecret;

	OpenApiInitParam()
	{
		port = 0;
	}
}OPEN_API_INIT_PARAM;

#endif /* _OPENAPIINFO_H_ */
