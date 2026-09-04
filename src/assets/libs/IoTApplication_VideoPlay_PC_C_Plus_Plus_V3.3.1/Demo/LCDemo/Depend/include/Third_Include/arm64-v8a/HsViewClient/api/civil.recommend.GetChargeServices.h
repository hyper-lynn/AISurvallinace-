/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_GetChargeServices_H_
#define _HSVIEW_CLIENT_API_GetChargeServices_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 

分页获取发现页增值服务列表
请求体
count等于0时表示 获取全部
当type=0 获取 lccloudstorage、lcpassengerflow、lcsharestrategy、lcnas
当type=1 获取的是lccloudstorage、lcpassengerflow、lcsharestrategy、lcnas中的两个

响应体
type=lccloudstorage  云存储
type=pcscloudstorage 新云存储
type=lcpassengerflow 客流统计
type=lcsharestrategy 设备分享
type=lcnas 私有云页面
type=phonealarm 电话报警提醒
type=devShareStrategy 设备分享套餐
type=timeAlbum 时光相册
type=humanMotionStrategy  智能人形检测套餐
type=default 默认
groupName传中文 增值服务 合作服务

【不鉴权】
 */

typedef struct GetChargeServicesRequest 
{
	HsviewRequest base;

	struct GetChargeServicesRequestData
	{
		
		/** [int] 0 :获取全部（app3.8之后废弃） ， 1: 获取推荐（app3.8之后废弃） 2:获取增值服务 */
		int type;
		/** [int]需要查的最大条数 */
		int count;
		/** 获取types指定的增值服务员类型 为空 默认获取lccloudstorage、lcpassengerflow、lcsharestrategy、lcnas */
		DECLARE_LIST(CSTR) types;

	} data;

} GetChargeServicesRequest;

C_API GetChargeServicesRequest *HSAPI_INIT(GetChargeServicesRequest);

typedef struct GetChargeServicesResponse 
{
	HsviewResponse base;

	struct GetChargeServicesResponseData
	{
		
		/** define a list with struct of GetChargeServicesResponseData_ServicesElement */
		DECLARE_LIST(struct GetChargeServicesResponseData_ServicesElement
		{
			/** 标识 */
			CSTR type;
			/** 标题 */
			CSTR title;
			/** 展示图url */
			CSTR coverUrl;
			/** [O]跳转链接 */
			CSTR linkUrl;
			/** 服务类别 */
			CSTR groupName;
			/** 描述 */
			CSTR desc;
		}) services;
 
	} data;

} GetChargeServicesResponse;

C_API GetChargeServicesResponse *HSAPI_INIT(GetChargeServicesResponse);

#endif
