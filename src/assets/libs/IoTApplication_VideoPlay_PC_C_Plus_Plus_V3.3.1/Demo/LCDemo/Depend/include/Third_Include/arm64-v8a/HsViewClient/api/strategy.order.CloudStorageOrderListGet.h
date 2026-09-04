/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_strategyOrder_CloudStorageOrderListGet_H_
#define _HSVIEW_CLIENT_API_strategyOrder_CloudStorageOrderListGet_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 

查询订单列表

 */

typedef struct strategyOrder_CloudStorageOrderListGetRequest 
{
	HsviewRequest base;

	struct strategyOrder_CloudStorageOrderListGetRequestData
	{
		
		/** [int][O]保留 */
		int _nouse;

	} data;

} strategyOrder_CloudStorageOrderListGetRequest;

C_API strategyOrder_CloudStorageOrderListGetRequest *HSAPI_INIT(strategyOrder_CloudStorageOrderListGetRequest);

typedef struct strategyOrder_CloudStorageOrderListGetResponse 
{
	HsviewResponse base;

	struct strategyOrder_CloudStorageOrderListGetResponseData
	{
		
		/** define a list with struct of strategyOrder_CloudStorageOrderListGetResponseData_OrderListElement */
		DECLARE_LIST(struct strategyOrder_CloudStorageOrderListGetResponseData_OrderListElement
		{
			/** [int]订单类型,0-云存储订单，1-视频VIP订单 */
			int orderType;
			/** UTC时间戳,精确到秒 */
			CSTR createTime;
			/** 订单号 */
			CSTR orderNo;
			/** $,￥ */
			CSTR currencySymbol;
			/** [O]自动续费状态，zencam必须 */
			CSTR autoRenewalStatus;
			/** [int] 订单状态  0-待支付 1-交易完成 2-已关闭 (只有0可以pay或者cancel) */
			int orderStatus;
			/** paypal 支付方式名称 */
			CSTR payName;
			/** USD美元,AUD澳元 */
			CSTR currency;
			/** [O]只有payAppId为2和3时才有值 */
			CSTR apiKey;
			/** [int]支付方式id,1是paypal 2是card 3是adyen */
			int payAppId;
			/** [O]设备序列号，从设备入口进来才有 */
			CSTR deviceId;
			/** [O]通道号,从设备入口进来才有 */
			CSTR channelId;
			/** define a list with struct of strategyOrder_CloudStorageOrderListGetResponseData_OrderListElement_GoodListElement */
			DECLARE_LIST(struct strategyOrder_CloudStorageOrderListGetResponseData_OrderListElement_GoodListElement
			{
				/** [O]商品标签图 */
				CSTR labelImg;
				/** [int]存储时长,单位天 */
				int remainDay;
				/** [O]商品主图 */
				CSTR mainImg;
				/** [int]商品类型 */
				int goodTypeId;
				/** [int][O]窗口编号，如果是16分屏，取值为1~16 */
				int windowNum;
				/** [int]商品数量 */
				int goodNum;
				/** [int]服务时长,单位秒 */
				int serviceTime;
				/** [double]市场价,两位小数 */
				double mktPrice;
				/** [int]商品id */
				int goodId;
				/** 商品名称 */
				CSTR goodName;
				/** [double]销售价,两位小数 */
				double salePrice;
			}) goodList;
			/** [double]订单总金额,两位小数，如100.68 */
			double orderAmount;
		}) orderList;
 
	} data;

} strategyOrder_CloudStorageOrderListGetResponse;

C_API strategyOrder_CloudStorageOrderListGetResponse *HSAPI_INIT(strategyOrder_CloudStorageOrderListGetResponse);

#endif
