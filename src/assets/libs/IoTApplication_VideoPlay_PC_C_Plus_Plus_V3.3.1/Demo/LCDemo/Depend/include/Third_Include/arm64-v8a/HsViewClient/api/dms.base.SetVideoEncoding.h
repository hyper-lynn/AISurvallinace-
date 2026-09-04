/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_SetVideoEncoding_H_
#define _HSVIEW_CLIENT_API_SetVideoEncoding_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
修改设备的视频编码参数。说明如下：
1、可对具体某个通道设置。若不指定通道，则对所有通道设置。
2、设置的参数是Stream数组，也就是说，一次可同时设置主辅码流的编码参数。当然也可以只修改主码流，或只修改辅码流。
3、设备不一定接受请求中的编码参数。若请求的参数无法设置到设备中，则本接口返回400 Bad Request错误。
 */

typedef struct SetVideoEncodingRequest 
{
	HsviewRequest base;

	struct SetVideoEncodingRequestData
	{
		
		/** 设备ID */
		CSTR devId;
		/** 设备通道号。若填空表示设置该设备下所有通道。 */
		CSTR optional;
		/** [cstr]POST */
		#define _STATIC_SetVideoEncodingRequestData_METHOD "POST"
		/** [cstr]video-encoding */
		#define _STATIC_SetVideoEncodingRequestData_CMD "video-encoding"
		/** struct of SetVideoEncodingRequestData_Body */
		struct SetVideoEncodingRequestData_Body {
			/** define a list with struct of SetVideoEncodingRequestData_Body_StreamStructElement */
			DECLARE_LIST(struct SetVideoEncodingRequestData_Body_StreamStructElement
			{
				/** [int]关键帧间隔 */
				int IFrameIntv;
				/** [int]流ID：0,1,2依次代表主码流、辅码流、辅码流2，以此类推。 */
				int ID;
				/** [int]帧率 */
				int Fps;
				/** [int]码率，单位kbps */
				int BitRate;
				/** 分辨率，可选：1080P，720P，D1，CIF，QCIF */
				CSTR Resolution;
			}) Stream;
		} body;

	} data;

} SetVideoEncodingRequest;

C_API SetVideoEncodingRequest *HSAPI_INIT(SetVideoEncodingRequest);

typedef struct SetVideoEncodingResponse 
{
	HsviewResponse base;

	struct SetVideoEncodingResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} SetVideoEncodingResponse;

C_API SetVideoEncodingResponse *HSAPI_INIT(SetVideoEncodingResponse);

#endif
