/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetMallGoods_H_
#define _HSVIEW_CLIENT_API_GetMallGoods_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
分页获取发现页展示商品列表

【不鉴权】
 */

typedef struct GetMallGoodsRequest 
{
	HsviewRequest base;

	struct GetMallGoodsRequestData
	{
		
		/** [int]需要查的最大条数 */
		int count;

	} data;

} GetMallGoodsRequest;

C_API GetMallGoodsRequest *HSAPI_INIT(GetMallGoodsRequest);

typedef struct GetMallGoodsResponse 
{
	HsviewResponse base;

	struct GetMallGoodsResponseData
	{
		
		/** define a list with struct of GetMallGoodsResponseData_ProductsElement */
		DECLARE_LIST(struct GetMallGoodsResponseData_ProductsElement
		{
			/** 介绍文案 */
			CSTR desc;
			/** 跳转链接 */
			CSTR linkUrl;
			/** 标题 */
			CSTR title;
			/** 商品展示图url */
			CSTR coverUrl;
		}) products;
 
	} data;

} GetMallGoodsResponse;

C_API GetMallGoodsResponse *HSAPI_INIT(GetMallGoodsResponse);

#endif
