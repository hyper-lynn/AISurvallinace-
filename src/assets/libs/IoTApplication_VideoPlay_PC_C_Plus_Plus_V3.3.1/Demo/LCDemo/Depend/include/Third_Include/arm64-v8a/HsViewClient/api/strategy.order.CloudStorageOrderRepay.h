/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_strategyOrder_CloudStorageOrderRepay_H_
#define _HSVIEW_CLIENT_API_strategyOrder_CloudStorageOrderRepay_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
海外云存储订单页面再次支付

备注：前端根据支付方式分别去请求对应的接口。
如果是paypal，则在点击完支付方式下面的ok时，请求  pcs/v1/strategy.pay.getPaypalJumpUrl接口
如果是card，则在信用卡支付完成时，即点击pay，请求  pcs/v1/strategy.order.getPayStatus  接口
adyen支付，加密值由前端调用adyen提供的js集成
 */

typedef struct strategyOrder_CloudStorageOrderRepayRequest 
{
	HsviewRequest base;

	struct strategyOrder_CloudStorageOrderRepayRequestData
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
		/** 订单号 */
		CSTR orderNo;
		/** [O]自动续费状态，zencam必须 */
		CSTR autoRenewalStatus;
		/** [O]消费者的附近地址，IntelBras必须 */
		CSTR customerNeighborhood;
		/** 2018-12-09 00:00:00 */
		CSTR localOrderTime;
		/** [int]支付方式id值,1是paypal 2是card，3是adyen */
		int payAppId;
		/** [O]消费者的城市，IntelBras必须 */
		CSTR customerCity;
		/** [O]信用卡的收据邮箱，zencam必须 */
		CSTR receiptEmail;
		/** [O]消费者的邮箱账号，IntelBras必须 */
		CSTR customerEmail;
		/** [O]信用卡的账单地址，zencam必须 */
		CSTR billAddress;
		/** [O]消费者的电话号码，IntelBras必须 */
		CSTR customerPhoneNumber;
		/** [O]消费者的具体住宅单元，IntelBras必须 */
		CSTR customerComplement;
		/** [O]adyen信用卡支付，卡的有效月份加密值 */
		CSTR encryptedExpiryMonth;
		/** [O]消费者的（街道）地址，IntelBras必须 */
		CSTR customerAddress;
		/** [O]消费者的号码，IntelBras必须 */
		CSTR customerNumber;
		/** USD美元,AUD澳元 */
		CSTR currency;
		/** [O]消费者的区域，IntelBras必须 */
		CSTR customerState;
		/** [double]16.00，支付总金额 */
		double orderAmount;
		/** [O]设备序列号 */
		CSTR deviceId;

	} data;

} strategyOrder_CloudStorageOrderRepayRequest;

C_API strategyOrder_CloudStorageOrderRepayRequest *HSAPI_INIT(strategyOrder_CloudStorageOrderRepayRequest);

typedef struct strategyOrder_CloudStorageOrderRepayResponse 
{
	HsviewResponse base;

	struct strategyOrder_CloudStorageOrderRepayResponseData
	{
		
		/** 订单号 */
		CSTR orderNo;
 
	} data;

} strategyOrder_CloudStorageOrderRepayResponse;

C_API strategyOrder_CloudStorageOrderRepayResponse *HSAPI_INIT(strategyOrder_CloudStorageOrderRepayResponse);

#endif
