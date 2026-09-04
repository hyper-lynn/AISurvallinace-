/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetMotionDetectWindow_H_
#define _HSVIEW_CLIENT_API_GetMotionDetectWindow_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取动检范围

Raw：动态检测区域的行数（只读，设备能力）

Col：动态检测区域的列数（只读，设备能力）

Region： 多个32位整形组成的字段（行数个），区域的每一行使用一个32位整型表示，整型的每一位对应一个小块，画面左边对应数字高位 协议上的行列与输入通道画面图像块坐标的对应关系如下： 画面列：左-->右; 对应协议列（数字位）：左（高位）-->右（低位）由于动检只有22列，对应到数字的低22位，高10位固定填0。 画面行：上-->下; 对应协议行：上-->下;

单通道设备和多通道设备，都[channel-id]都必须填写。
 */

typedef struct GetMotionDetectWindowRequest 
{
	HsviewRequest base;

	struct GetMotionDetectWindowRequestData
	{
		
		/** 设备ID */
		CSTR devId;
		/** 填写通道号 */
		CSTR optional;
		/** [cstr]GET */
		#define _STATIC_GetMotionDetectWindowRequestData_METHOD "GET"
		/** [cstr]motion-detect-window */
		#define _STATIC_GetMotionDetectWindowRequestData_CMD "motion-detect-window"
		/** struct of GetMotionDetectWindowRequestData_Body */
		struct GetMotionDetectWindowRequestData_Body {
			/** [int][O]保留 */
			int _nouse;
		} body;

	} data;

} GetMotionDetectWindowRequest;

C_API GetMotionDetectWindowRequest *HSAPI_INIT(GetMotionDetectWindowRequest);

typedef struct GetMotionDetectWindowResponse 
{
	HsviewResponse base;

	struct GetMotionDetectWindowResponseData
	{
		
		/** [int]使能, 1-开启 0-关闭 */
		int Raw;
		/** 4194303, 3216384, …  */
		CSTR Region;
		/** [int]使能, 1-开启 0-关闭 */
		int Col;
 
	} data;

} GetMotionDetectWindowResponse;

C_API GetMotionDetectWindowResponse *HSAPI_INIT(GetMotionDetectWindowResponse);

#endif
