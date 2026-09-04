/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetWeatherAreaList_H_
#define _HSVIEW_CLIENT_API_GetWeatherAreaList_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
客户端下载的天气文件地理位置区域列表

文件格式：
{
    "Province": [
        {
            "Name": "北京",
            "City": [
                {
                    "Name": "北京",
                    "District": [
                        "东城",
                        "西城",
                        "崇文",
                        "宣武",
                        "朝阳"
                    ]
                }
            ]
        },
        {
            "Name": "河北",
            "City": [
                {
                    "Name": "石家庄",
                    "District": [
                        "长安",
                        "桥东",
                        "桥西",
                        "新华",
                        "裕华"
                    ]
                },
                {
                    "Name": "张家口",
                    "District": [
                        "桥西",
                        "桥东",
                        "宣化",
                        "下花园"
                    ]
                }
            ]
        }
    ]
}

【使用平台账号签名】
 */

typedef struct GetWeatherAreaListRequest 
{
	HsviewRequest base;

	struct GetWeatherAreaListRequestData
	{
		
		/** [int][O]保留 */
		int _nouse;

	} data;

} GetWeatherAreaListRequest;

C_API GetWeatherAreaListRequest *HSAPI_INIT(GetWeatherAreaListRequest);

typedef struct GetWeatherAreaListResponse 
{
	HsviewResponse base;

	struct GetWeatherAreaListResponseData
	{
		
		/** [long]文件最后更新的UNIX时间戳秒 */
		int64 updateTime;
		/** 用于下载天气文件地理位置区域列表的URL地址 */
		CSTR url;
 
	} data;

} GetWeatherAreaListResponse;

C_API GetWeatherAreaListResponse *HSAPI_INIT(GetWeatherAreaListResponse);

#endif
