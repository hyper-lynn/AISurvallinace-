/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_TransferAp_H_
#define _HSVIEW_CLIENT_API_TransferAp_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
配件信令透传接口
 */

typedef struct TransferApRequest 
{
	HsviewRequest base;

	struct TransferApRequestData
	{
		
		/** 设备ID */
		CSTR devId;
		/** 无需设置 */
		CSTR optional;
		/** [cstr]POST */
		#define _STATIC_TransferApRequestData_METHOD "POST"
		/** [cstr]agcmd */
		#define _STATIC_TransferApRequestData_CMD "agcmd"
		/** struct of TransferApRequestData_Body */
		struct TransferApRequestData_Body {
			/** 配件类型 */
			CSTR Type;
			/** 命令：设置声光报警使能：set-alarm-enable，详细见各协议 */
			CSTR Action;
			/** [bool]使能状态：true/false */
			BOOL Enable;
			/** 升级包地址 */
			CSTR Package;
			/** 当前的报警状态：on/off */
			CSTR Status;
			/** 声音的大小：mute-静音，notice-轻柔，alert-大声 */
			CSTR Sound;
			/** 配件id */
			CSTR ID;
		} body;

	} data;

} TransferApRequest;

C_API TransferApRequest *HSAPI_INIT(TransferApRequest);

typedef struct TransferApResponse 
{
	HsviewResponse base;

	struct TransferApResponseData
	{
		
		/** 版本号 */
		CSTR Version;
		/** [int]返回错误码。成功为0，1- 配件不存在；2-升级地址解析错误；3-当前设备状态不可升级，稍后再试； 4-其他错误 */
		int Code;
		/** 当前的报警状态：on/off|升级的状态：Idle -空闲，Downloading -下载，Upgrading -升级中 */
		CSTR Status;
		/** [int]进度百分比  0-100 */
		int Percent;
		/** 声音的大小：mute-静音，notice-轻柔，alert-大声 */
		CSTR Sound;
		/** [bool]使能状态：true/false */
		BOOL Enable;
 
	} data;

} TransferApResponse;

C_API TransferApResponse *HSAPI_INIT(TransferApResponse);

#endif
