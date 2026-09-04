/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_squareVideo_GetSquareVideoCategory_H_
#define _HSVIEW_CLIENT_API_squareVideo_GetSquareVideoCategory_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
获取视频类型列表
【使用平台账号签名】
 */

typedef struct squareVideo_GetSquareVideoCategoryRequest 
{
	HsviewRequest base;

	struct squareVideo_GetSquareVideoCategoryRequestData
	{
		
		/** [int][O]保留 */
		int _nouse;

	} data;

} squareVideo_GetSquareVideoCategoryRequest;

C_API squareVideo_GetSquareVideoCategoryRequest *HSAPI_INIT(squareVideo_GetSquareVideoCategoryRequest);

typedef struct squareVideo_GetSquareVideoCategoryResponse 
{
	HsviewResponse base;

	struct squareVideo_GetSquareVideoCategoryResponseData
	{
		
		/** define a list with struct of squareVideo_GetSquareVideoCategoryResponseData_CategoryInfosElement */
		DECLARE_LIST(struct squareVideo_GetSquareVideoCategoryResponseData_CategoryInfosElement
		{
			/** [long]视频类型id */
			int64 categoryId;
			/** 视频分类名称 */
			CSTR categoryName;
			/** 封图片url */
			CSTR coverPicUrl;
		}) categoryInfos;
 
	} data;

} squareVideo_GetSquareVideoCategoryResponse;

C_API squareVideo_GetSquareVideoCategoryResponse *HSAPI_INIT(squareVideo_GetSquareVideoCategoryResponse);

#endif
