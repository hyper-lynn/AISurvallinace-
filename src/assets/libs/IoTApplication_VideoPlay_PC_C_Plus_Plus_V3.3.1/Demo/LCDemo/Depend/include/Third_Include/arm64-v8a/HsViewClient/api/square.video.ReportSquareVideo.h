/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_squareVideo_ReportSquareVideo_H_
#define _HSVIEW_CLIENT_API_squareVideo_ReportSquareVideo_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
举报被分享的视频或摄像头
【使用平台账号签名】
 */

typedef struct squareVideo_ReportSquareVideoRequest 
{
	HsviewRequest base;

	struct squareVideo_ReportSquareVideoRequestData
	{
		
		/** 对举报内容的描述 */
		CSTR remark;
		/** [long]被分享的视频或摄像头ID */
		int64 shareVideoId;
		/** [int]举报类型 */
		int reportType;

	} data;

} squareVideo_ReportSquareVideoRequest;

C_API squareVideo_ReportSquareVideoRequest *HSAPI_INIT(squareVideo_ReportSquareVideoRequest);

typedef struct squareVideo_ReportSquareVideoResponse 
{
	HsviewResponse base;

	struct squareVideo_ReportSquareVideoResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} squareVideo_ReportSquareVideoResponse;

C_API squareVideo_ReportSquareVideoResponse *HSAPI_INIT(squareVideo_ReportSquareVideoResponse);

#endif
