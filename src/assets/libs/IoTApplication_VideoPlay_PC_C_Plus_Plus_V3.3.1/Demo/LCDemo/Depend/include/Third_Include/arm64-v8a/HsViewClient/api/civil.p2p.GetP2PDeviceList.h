/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetP2PDeviceList_H_
#define _HSVIEW_CLIENT_API_GetP2PDeviceList_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取p2p绑定的设备列表
【使用平台账号签名认证】
 */

typedef struct GetP2PDeviceListRequest 
{
	HsviewRequest base;

	struct GetP2PDeviceListRequestData
	{
		
		/** [long]起始ID，-1则代表重新查询 */
		int64 id;
		/** [int]每次获取的设备数量，最大值100 */
		int count;

	} data;

} GetP2PDeviceListRequest;

C_API GetP2PDeviceListRequest *HSAPI_INIT(GetP2PDeviceListRequest);

typedef struct GetP2PDeviceListResponse 
{
	HsviewResponse base;

	struct GetP2PDeviceListResponseData
	{
		
		/** define a list with struct of GetP2PDeviceListResponseData_DevicesElement */
		DECLARE_LIST(struct GetP2PDeviceListResponseData_DevicesElement
		{
			/** 设备编号 */
			CSTR deviceCode;
			/** 回放码流类型:main-主码流，sub-辅码流 */
			CSTR preferStreamPlayback;
			/** [long]平台内部唯一标识 */
			int64 id;
			/** [int]rtsp端口 */
			int rtspPort;
			/** 设备名称 */
			CSTR deviceName;
			/** 设备密码 */
			CSTR password;
			/** 设备局域网IP */
			CSTR localIP;
			/** 设备用户名 */
			CSTR username;
			/** [int]http端口 */
			int httpPort;
			/** 实时码流类型:main-主码流，sub-辅码流 */
			CSTR preferStreamReal;
			/** [int]设备NetSDK局域网端口 */
			int localPort;
		}) devices;
 
	} data;

} GetP2PDeviceListResponse;

C_API GetP2PDeviceListResponse *HSAPI_INIT(GetP2PDeviceListResponse);

#endif
