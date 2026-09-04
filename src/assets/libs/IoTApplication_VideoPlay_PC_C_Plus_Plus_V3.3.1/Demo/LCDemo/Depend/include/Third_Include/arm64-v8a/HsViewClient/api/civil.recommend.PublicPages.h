/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_PublicPages_H_
#define _HSVIEW_CLIENT_API_PublicPages_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 

获取云存储h5

type 页面类型：storagestrategydetail-云存储详情，storagestrategy-云存储购买，userstoragestrategy-我的云存储

【不需要鉴权】
 */

typedef struct PublicPagesRequest 
{
	HsviewRequest base;

	struct PublicPagesRequestData
	{
		
		/** [int][O]保留 */
		int _nouse;

	} data;

} PublicPagesRequest;

C_API PublicPagesRequest *HSAPI_INIT(PublicPagesRequest);

typedef struct PublicPagesResponse 
{
	HsviewResponse base;

	struct PublicPagesResponseData
	{
		
		/** define a list with struct of PublicPagesResponseData_PagesElement */
		DECLARE_LIST(struct PublicPagesResponseData_PagesElement
		{
			/** 页面的访问地址url */
			CSTR url;
			/** 页面类型 */
			CSTR type;
		}) pages;
 
	} data;

} PublicPagesResponse;

C_API PublicPagesResponse *HSAPI_INIT(PublicPagesResponse);

#endif
