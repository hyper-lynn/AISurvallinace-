/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_transferAlarm_MotionDetectParamGet_H_
#define _HSVIEW_CLIENT_API_transferAlarm_MotionDetectParamGet_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取动检参数

>    响应参数说明
 + stall：表示档位，取值范围为[1, 6]。
 + row：动态检测区域的行数（只读，设备能力）
 + column：动态检测区域的列数（只读，设备能力）
 + sensitive: 灵敏度，取值[0, 100]
 + threshold: 面积阀值，取值[0, 100]
 + region： 多个32位整形组成的字段（行数个），区域的每一行使用一个32位整型表示，整型的每一位对应一个小块，画面左边对应数字高位.
    - 协议上的行列与输入通道画面图像块坐标的对应关系如下：
    - 画面列：左-->右; 对应协议列（数字位）：左（高位）-->右（低位）由于动检只有22列，对应到数字的低22位，高10位固定填0。
    - 画面行：上-->下; 对应协议行：上-->下;
参考PaaS协议：[获取动检参数](http://paas.dahuatech.com/wiki/?p=%2F%E8%AE%BE%E5%A4%87%E7%AE%A1%E7%90%86%2F%E8%AE%BE%E5%A4%87%E9%85%8D%E7%BD%AE%2F%E6%8A%A5%E8%AD%A6%E9%85%8D%E7%BD%AE%2F%E8%8E%B7%E5%8F%96%E5%8A%A8%E6%A3%80%E5%8C%BA%E5%9F%9F.md&s=pd)

【需要使用平台账号签名】
 */

typedef struct transferAlarm_MotionDetectParamGetRequest 
{
	HsviewRequest base;

	struct transferAlarm_MotionDetectParamGetRequestData
	{
		
		/** [cstr]/device/alarm/range/query/ */
		#define _STATIC_transferAlarm_MotionDetectParamGetRequestData_url "/device/alarm/range/query/"
		CSTR url;
		/** 通道号 */
		CSTR channelId;
		/** 设备序列号 */
		CSTR deviceId;

	} data;

} transferAlarm_MotionDetectParamGetRequest;

C_API transferAlarm_MotionDetectParamGetRequest *HSAPI_INIT(transferAlarm_MotionDetectParamGetRequest);

typedef struct transferAlarm_MotionDetectParamGetResponse 
{
	HsviewResponse base;

	struct transferAlarm_MotionDetectParamGetResponseData
	{
		
		/** [int][O]表示档位，取值范围为[1, 6]，0表示设备不支持，未返回该字段 */
		int stall;
		/** 4194303, 3216384 */
		CSTR region;
		/** [int]动态检测区域的列数（只读，设备能力） */
		int column;
		/** [int]面积阀值，取值[0, 100] */
		int threshold;
		/** [int]动态检测区域的行数（只读，设备能力） */
		int row;
		/** [int]灵敏度，取值[0, 100] */
		int sensitive;
 
	} data;

} transferAlarm_MotionDetectParamGetResponse;

C_API transferAlarm_MotionDetectParamGetResponse *HSAPI_INIT(transferAlarm_MotionDetectParamGetResponse);

#endif
