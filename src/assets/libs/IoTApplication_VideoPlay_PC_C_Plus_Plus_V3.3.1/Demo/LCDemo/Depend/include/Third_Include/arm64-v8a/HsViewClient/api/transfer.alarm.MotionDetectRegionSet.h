/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_transferAlarm_MotionDetectRegionSet_H_
#define _HSVIEW_CLIENT_API_transferAlarm_MotionDetectRegionSet_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
设置动检区域

> 请求参数说明
 + region： 多个32位整形组成的字段（行数个），区域的每一行使用一个32位整型表示，整型的每一位对应一个小块，画面左边对应数字高位.
    - 协议上的行列与输入通道画面图像块坐标的对应关系如下：
    - 画面列：左-->右; 对应协议列（数字位）：左（高位）-->右（低位）由于动检只有22列，对应到数字的低22位，高10位固定填0；
    - 画面行：上-->下; 对应协议行：上-->下；
    - 注： 如region中整数个数不足行数个，默认以0填充，如超过行数个，则丢弃超过个数。

参考PaaS协议：[设置动检参数](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E8%AE%BE%E5%A4%87%E9%85%8D%E7%BD%AE%2F%E6%8A%A5%E8%AD%A6%E9%85%8D%E7%BD%AE%2F%E8%AE%BE%E7%BD%AE%E5%8A%A8%E6%A3%80%E5%8C%BA%E5%9F%9F.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct transferAlarm_MotionDetectRegionSetRequest 
{
	HsviewRequest base;

	struct transferAlarm_MotionDetectRegionSetRequestData
	{
		
		/** 设备通道号 */
		CSTR channelId;
		/** [cstr]/device/alarm/range/config/ */
		#define _STATIC_transferAlarm_MotionDetectRegionSetRequestData_url "/device/alarm/range/config/"
		CSTR url;
		/** struct of transferAlarm_MotionDetectRegionSetRequestData_Content */
		struct transferAlarm_MotionDetectRegionSetRequestData_Content {
			/** 4194303, 3216384, 3216384 */
			CSTR region;
		} content;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} transferAlarm_MotionDetectRegionSetRequest;

C_API transferAlarm_MotionDetectRegionSetRequest *HSAPI_INIT(transferAlarm_MotionDetectRegionSetRequest);

typedef struct transferAlarm_MotionDetectRegionSetResponse 
{
	HsviewResponse base;

	struct transferAlarm_MotionDetectRegionSetResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} transferAlarm_MotionDetectRegionSetResponse;

C_API transferAlarm_MotionDetectRegionSetResponse *HSAPI_INIT(transferAlarm_MotionDetectRegionSetResponse);

#endif
