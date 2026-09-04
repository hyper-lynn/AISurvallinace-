/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_strategyOrder_CloudStorageOrderCreate_H_
#define _HSVIEW_CLIENT_API_strategyOrder_CloudStorageOrderCreate_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
创建订单

备注：前端根据支付方式分别去请求对应的接口。
如果是paypal，则在点击完支付方式下面的ok时，请求  pcs/v1/strategy.pay.getPaypalJumpUrl接口
如果是card，则在信用卡支付完成时，即点击pay，请求  pcs/v1/strategy.order.getPayStatus  接口
zencam的failBalanceOrderNo场景：订单页面会显示续费失败，autoRenewal为failBalance,此时页面显示续费失败，点击下一步会调用该接口进行续费
adyen支付，加密值由前端调用adyen提供的js集成
 */

typedef struct strategyOrder_CloudStorageOrderCreateRequest 
{
	HsviewRequest base;

	struct strategyOrder_CloudStorageOrderCreateRequestData
	{
		
		/** [O]adyen信用卡支付，cvc码的加密值 */
		CSTR encryptedSecurityCode;
		/** [O]消费者的全名，IntelBras必须 */
		CSTR customerFullName;
		/** 123456789,本地时间 UTC时间戳,精确到秒 */
		CSTR orderTimestamp;
		/** [O]消费者的身份ID，IntelBras必须 */
		CSTR customerCPF;
		/** [O]www.baidu.com，如果是paypal支付 则必填 */
		CSTR cancelUrl;
		/** 精确到地区,en_US zh_HK */
		CSTR language;
		/** [O]adyen信用卡支付，卡的有效年份加密值 */
		CSTR encryptedExpiryYear;
		/** [O]adyen信用卡支付，卡号的加密值 */
		CSTR encryptedCardNumber;
		/** [O]消费者的CEP，IntelBras必须 */
		CSTR customerZipcode;
		/** $,￥ */
		CSTR currencySymbol;
		/** [O]消费者的国家，IntelBras必须 */
		CSTR customerCountry;
		/** [O]www.baidu.com，如果是paypal/adyen支付 则必填 */
		CSTR returnUrl;
		/** [O]通道id */
		CSTR channelId;
		/** [O]stripe 的token值，如果是stripe支付 则必填 */
		CSTR stripeToken;
		/** 云存储套餐名,统一使用[云存储套餐],根据语言传入,paypal页面需要展示 */
		CSTR itemName;
		/** [int][O]订单状态，0-云存储订单，1-视频VIP，可选，不传默认为：0-云存储订单 */
		int orderType;
		/** [O]消费者的具体住宅单元，IntelBras必须 */
		CSTR customerComplement;
		/** [O]自动续费状态，zencam必须，on和off */
		CSTR autoRenewalStatus;
		/** USD美元,AUD澳元 */
		CSTR currency;
		/** 2018-12-09 00:00:00 */
		CSTR localOrderTime;
		/** [int]支付方式id值,0免费（napco），1是paypal，2是card，3是adyen，4是momopay */
		int payAppId;
		/** [double]16.00，支付总金额 */
		double orderAmount;
		/** [O]信用卡的收据邮箱，zencam必须 */
		CSTR receiptEmail;
		/** [O]消费者的邮箱账号，IntelBras必须 */
		CSTR customerEmail;
		/** [O]信用卡的账单地址，zencam必须 */
		CSTR billAddress;
		/** [O] zencam续费失败的订单号，订单页面续费失败状态下使用 */
		CSTR failBalanceOrderNo;
		/** [O]消费者的电话号码，IntelBras必须 */
		CSTR customerPhoneNumber;
		/** [O]消费者的号码，IntelBras必须 */
		CSTR customerNumber;
		/** [O]adyen信用卡支付，卡的有效月份加密值 */
		CSTR encryptedExpiryMonth;
		/** [O]消费者的（街道）地址，IntelBras必须 */
		CSTR customerAddress;
		/** [O]消费者的附近地址，IntelBras必须 */
		CSTR customerNeighborhood;
		/** [O]消费者的城市，IntelBras必须 */
		CSTR customerCity;
		/** [O]消费者的区域，IntelBras必须 */
		CSTR customerState;
		/** define a list with struct of strategyOrder_CloudStorageOrderCreateRequestData_GoodListElement */
		DECLARE_LIST(struct strategyOrder_CloudStorageOrderCreateRequestData_GoodListElement
		{
			/** [int]商品类型 */
			int goodTypeId;
			/** [int][O]窗口编号，如果是16分屏，取值为1~16 */
			int windowNum;
			/** [int]商品id值 */
			int goodId;
			/** 商品名称 */
			CSTR goodName;
			/** [int]商品数量 大于等于1 */
			int goodNum;
		}) goodList;
		/** [O]设备序列号 */
		CSTR deviceId;

	} data;

} strategyOrder_CloudStorageOrderCreateRequest;

C_API strategyOrder_CloudStorageOrderCreateRequest *HSAPI_INIT(strategyOrder_CloudStorageOrderCreateRequest);

typedef struct strategyOrder_CloudStorageOrderCreateResponse 
{
	HsviewResponse base;

	struct strategyOrder_CloudStorageOrderCreateResponseData
	{
		
		/** 123456 */
		CSTR orderNo;
 
	} data;

} strategyOrder_CloudStorageOrderCreateResponse;

C_API strategyOrder_CloudStorageOrderCreateResponse *HSAPI_INIT(strategyOrder_CloudStorageOrderCreateResponse);

#endif
