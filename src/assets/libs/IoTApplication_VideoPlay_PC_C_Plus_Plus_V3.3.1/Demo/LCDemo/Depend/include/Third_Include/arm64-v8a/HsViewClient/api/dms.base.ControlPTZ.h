/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_ControlPTZ_H_
#define _HSVIEW_CLIENT_API_ControlPTZ_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
控制设备云台。

详细说明 
当通道号为0，或者不存在，表示控制此设备的PTZ。

当Operation为move时，表示移动： 

H 水平移动速度：范围-8~8，负数向左，正数向右。
V 垂直移动速度：范围-8~8，负数向下，正数向上。（20151207修改成相反，与实际实现保持一致）
Z 变倍倍数：范围0~正无穷，小于1表示缩小，大于1表示放大。

注：三个参数为 0,0,1 时表示立即停止。

Duration表示移动的持续时间，单位毫秒。没有Duration字段或Duration字段填“last”表示一直运动下去。
当Operation为locate时，表示定位： 

H 水平位置：归一化到-1~1
V 垂直位置：归一化到-1~1
Z 变倍倍数：归一化到0~1

Duration参数无意义，可省略Duration字段。

【需要使用平台账号签名】
 */

typedef struct ControlPTZRequest 
{
	HsviewRequest base;

	struct ControlPTZRequestData
	{
		
		/** 设备ID */
		CSTR devId;
		/** 通道号 */
		CSTR optional;
		/** [cstr]POST */
		#define _STATIC_ControlPTZRequestData_METHOD "POST"
		/** [cstr]ptz */
		#define _STATIC_ControlPTZRequestData_CMD "ptz"
		/** struct of ControlPTZRequestData_Body */
		struct ControlPTZRequestData_Body {
			/** [double]水平操作参数 */
			double H;
			/** [double]变倍参数 */
			double Z;
			/** 操作行为；move表示移动，locate表示定位 */
			CSTR Operation;
			/** 移动持续时间，单位为毫秒。没有Duration字段或Duration字段填“last”表示一直运动下去 */
			CSTR Duration;
			/** [double]垂直操作参数 */
			double V;
		} body;

	} data;

} ControlPTZRequest;

C_API ControlPTZRequest *HSAPI_INIT(ControlPTZRequest);

typedef struct ControlPTZResponse 
{
	HsviewResponse base;

	struct ControlPTZResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} ControlPTZResponse;

C_API ControlPTZResponse *HSAPI_INIT(ControlPTZResponse);

#endif
