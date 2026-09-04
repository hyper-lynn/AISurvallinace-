/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_transferMedia_VideoEncodeParaGet_H_
#define _HSVIEW_CLIENT_API_transferMedia_VideoEncodeParaGet_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取视频编码参数
>    响应参数说明
 + stream：码流数组
 + streamType：码流类型。main -主码流；extra1-辅码流1，extra2--辅码流2.
 + resolution:分辨率。可选：1080P，720P，D1，CIF，QCIF。
 + fps：帧率
 + bitRate：码率，单位kbps
 + GoP：关键帧间隔,

参考PaaS协议：[获取视频编码参数](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E8%AE%BE%E5%A4%87%E9%85%8D%E7%BD%AE%2F%E8%A7%86%E9%A2%91%E7%9B%B8%E5%85%B3%E5%8F%82%E6%95%B0%2F%E8%8E%B7%E5%8F%96%E8%A7%86%E9%A2%91%E7%BC%96%E7%A0%81%E5%8F%82%E6%95%B0.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct transferMedia_VideoEncodeParaGetRequest 
{
	HsviewRequest base;

	struct transferMedia_VideoEncodeParaGetRequestData
	{
		
		/** [cstr]/device/video/encode/query/ */
		#define _STATIC_transferMedia_VideoEncodeParaGetRequestData_url "/device/video/encode/query/"
		CSTR url;
		/** 设备通道号 */
		CSTR channelId;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} transferMedia_VideoEncodeParaGetRequest;

C_API transferMedia_VideoEncodeParaGetRequest *HSAPI_INIT(transferMedia_VideoEncodeParaGetRequest);

typedef struct transferMedia_VideoEncodeParaGetResponse 
{
	HsviewResponse base;

	struct transferMedia_VideoEncodeParaGetResponseData
	{
		
		/** define a list with struct of transferMedia_VideoEncodeParaGetResponseData_StreamElement */
		DECLARE_LIST(struct transferMedia_VideoEncodeParaGetResponseData_StreamElement
		{
			/** 码流类型。main -主码流；extra1-辅码流1，extra2--辅码流 */
			CSTR streamType;
			/** [int]关键帧间隔 */
			int gop;
			/** [O]分辨率：1080P，720P，D1，CIF，QCI */
			CSTR resolution;
			/** [int]码率，单位kbps */
			int bitRate;
			/** [int]帧率 */
			int fps;
		}) stream;
 
	} data;

} transferMedia_VideoEncodeParaGetResponse;

C_API transferMedia_VideoEncodeParaGetResponse *HSAPI_INIT(transferMedia_VideoEncodeParaGetResponse);

#endif
