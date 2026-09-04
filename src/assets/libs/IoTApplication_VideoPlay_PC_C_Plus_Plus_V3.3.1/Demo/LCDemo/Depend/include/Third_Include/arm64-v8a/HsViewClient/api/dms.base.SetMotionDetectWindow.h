/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_SetMotionDetectWindow_H_
#define _HSVIEW_CLIENT_API_SetMotionDetectWindow_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
设置动检范围

Raw：动态检测区域的行数（只读，设备能力）

Col：动态检测区域的列数（只读，设备能力）

Region： 多个32位整形组成的字段（行数个），区域的每一行使用一个32位整型表示，整型的每一位对应一个小块，画面左边对应数字高位 协议上的行列与输入通道画面图像块坐标的对应关系如下： 画面列：左-->右; 对应协议列（数字位）：左（高位）-->右（低位）由于动检只有22列，对应到数字的低22位，高10位固定填0。 画面行：上-->下; 对应协议行：上-->下;

单通道设备和多通道设备，都[channel-id]都必须填写。
 */

typedef struct SetMotionDetectWindowRequest 
{
	HsviewRequest base;

	struct SetMotionDetectWindowRequestData
	{
		
		/** 设备ID */
		CSTR devId;
		/** 必须填写通道号 */
		CSTR optional;
		/** [cstr]POST */
		#define _STATIC_SetMotionDetectWindowRequestData_METHOD "POST"
		/** [cstr]motion-detect-window */
		#define _STATIC_SetMotionDetectWindowRequestData_CMD "motion-detect-window"
		/** struct of SetMotionDetectWindowRequestData_Body */
		struct SetMotionDetectWindowRequestData_Body {
			/** 4194303, 3216384, …  */
			CSTR Region;
		} body;

	} data;

} SetMotionDetectWindowRequest;

C_API SetMotionDetectWindowRequest *HSAPI_INIT(SetMotionDetectWindowRequest);

typedef struct SetMotionDetectWindowResponse 
{
	HsviewResponse base;

	struct SetMotionDetectWindowResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} SetMotionDetectWindowResponse;

C_API SetMotionDetectWindowResponse *HSAPI_INIT(SetMotionDetectWindowResponse);

#endif
