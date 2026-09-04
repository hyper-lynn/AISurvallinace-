/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_transferDevice_StorageCapacityGet_H_
#define _HSVIEW_CLIENT_API_transferDevice_StorageCapacityGet_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取存储介质容量

若存储介质错误则返回错误码:13704
若不存在SD卡，则返回错误码:13700
若SD卡加密，且未认证解密，返回错误码：13705
若SD卡不支持寿命检测，返回错误码：13706
若SD卡寿命耗尽，返回错误码：13707

参考PaaS协议：[获取存储介质容量](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E8%AE%BE%E5%A4%87%E9%85%8D%E7%BD%AE%2F%E5%AD%98%E5%82%A8%E4%BB%8B%E8%B4%A8%E9%85%8D%E7%BD%AE%2F%E8%8E%B7%E5%8F%96%E5%AD%98%E5%82%A8%E4%BB%8B%E8%B4%A8%E5%AE%B9%E9%87%8F.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct transferDevice_StorageCapacityGetRequest 
{
	HsviewRequest base;

	struct transferDevice_StorageCapacityGetRequestData
	{
		
		/** 设备序列号 */
		CSTR deviceId;
		/** [cstr]/device/storage/capacity */
		#define _STATIC_transferDevice_StorageCapacityGetRequestData_url "/device/storage/capacity"
		CSTR url;

	} data;

} transferDevice_StorageCapacityGetRequest;

C_API transferDevice_StorageCapacityGetRequest *HSAPI_INIT(transferDevice_StorageCapacityGetRequest);

typedef struct transferDevice_StorageCapacityGetResponse 
{
	HsviewResponse base;

	struct transferDevice_StorageCapacityGetResponseData
	{
		
		/** [long]单位为Byte，已使用字节数 */
		int64 usedBytes;
		/** [O]当前存储模式 */
		CSTR media;
		/** [long]单位为Byte，总共容量字节数 */
		int64 totalBytes;
		/** [O]参考存储介质事件类型定义 */
		CSTR type;
		/** [O]支持的存储模式列表 */
		DECLARE_LIST(CSTR) mediaList;
		/** struct of transferDevice_StorageCapacityGetResponseData_Desc */
		struct transferDevice_StorageCapacityGetResponseData_Desc {
			/** [O]错误码，可选, 普通异常提示格式化,SDCardEncryption */
			CSTR errorCode;
		} desc;
 
	} data;

} transferDevice_StorageCapacityGetResponse;

C_API transferDevice_StorageCapacityGetResponse *HSAPI_INIT(transferDevice_StorageCapacityGetResponse);

#endif
