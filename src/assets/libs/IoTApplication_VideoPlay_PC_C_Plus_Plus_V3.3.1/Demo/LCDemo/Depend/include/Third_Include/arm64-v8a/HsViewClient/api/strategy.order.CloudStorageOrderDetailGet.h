/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_strategyOrder_CloudStorageOrderDetailGet_H_
#define _HSVIEW_CLIENT_API_strategyOrder_CloudStorageOrderDetailGet_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
海外云存储查询订单详情
 */

typedef struct strategyOrder_CloudStorageOrderDetailGetRequest 
{
	HsviewRequest base;

	struct strategyOrder_CloudStorageOrderDetailGetRequestData
	{
		
		/** 订单id */
		CSTR orderNo;

	} data;

} strategyOrder_CloudStorageOrderDetailGetRequest;

C_API strategyOrder_CloudStorageOrderDetailGetRequest *HSAPI_INIT(strategyOrder_CloudStorageOrderDetailGetRequest);

typedef struct strategyOrder_CloudStorageOrderDetailGetResponse 
{
	HsviewResponse base;

	struct strategyOrder_CloudStorageOrderDetailGetResponseData
	{
		
		/** [int]订单类型,0-云存储订单，1-视频VIP订单 */
		int orderType;
		/** 订单号 */
		CSTR orderNo;
		/** [O]自动续费状态，zencam必须，on和off */
		CSTR autoRenewalStatus;
		/** [int] 订单状态  0-待支付 1-交易完成 2-已关闭 (只有0可以pay或者cancel) */
		int orderStatus;
		/** USD美元,AUD澳元 */
		CSTR currency;
		/** [int]支付方式id,1是paypal 2是card 3是adyen */
		int payAppId;
		/** [double]100.68 订单总金额,两位小数 */
		double orderAmount;
		/** 123456789 自动关闭时间 UTC时间戳,精确到秒 */
		CSTR autoCancelTime;
		/** [O]设备序列号，从设备入口进来才有 */
		CSTR deviceId;
		/** paypal 支付方式名称 */
		CSTR payName;
		/** [int]是否续费失败，1表示续费失败，0表示续费成功，zencam必须 */
		int isFailBalance;
		/** 只有payAppId为2和3时才有值 */
		CSTR apiKey;
		/** 123456789,UTC时间戳,精确到秒 */
		CSTR createTime;
		/** [int][O]是否为该设备下的最新订单，若为最新，订单详情页展示三个按钮（取消续费，更换信用卡，升级套餐），1表示是最新的，0表示不为最新的，zencam必须 */
		int isLatestOrder;
		/** [O]通道号,从设备入口进来才有 */
		CSTR channelId;
		/** define a list with struct of strategyOrder_CloudStorageOrderDetailGetResponseData_GoodListElement */
		DECLARE_LIST(struct strategyOrder_CloudStorageOrderDetailGetResponseData_GoodListElement
		{
			/** [O]商品标签图 */
			CSTR labelImg;
			/** [O][int]存储时长,单位天 */
			CSTR remainDay;
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
			/** [Double]销售价,两位小数 */
			CSTR salePrice;
		}) goodList;
		/** $,￥ */
		CSTR currencySymbol;
 
	} data;

} strategyOrder_CloudStorageOrderDetailGetResponse;

C_API strategyOrder_CloudStorageOrderDetailGetResponse *HSAPI_INIT(strategyOrder_CloudStorageOrderDetailGetResponse);

#endif
