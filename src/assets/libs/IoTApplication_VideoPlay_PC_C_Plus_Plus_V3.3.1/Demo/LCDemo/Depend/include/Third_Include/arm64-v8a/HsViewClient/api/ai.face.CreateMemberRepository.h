/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_aiFace_CreateMemberRepository_H_
#define _HSVIEW_CLIENT_API_aiFace_CreateMemberRepository_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
绑定人脸库与库成员关联关系

参数错误使用SaaS协议的code返回。
用户名不存在:1111
参考http://paas.dahuatech.com/wiki/?p=%2FSaaS%2F%E9%94%99%E8%AF%AF%E7%A0%81.md&s=pj 人脸云段

【用户平台鉴权】
 */

typedef struct aiFace_CreateMemberRepositoryRequest 
{
	HsviewRequest base;

	struct aiFace_CreateMemberRepositoryRequestData
	{
		
		/** [int]家庭成员所属的服务类型，0表示时光相册 */
		int repositoryType;
		/** 文件上传的token */
		CSTR token;
		/** 家庭成员名称,最长20个字符（1个汉字两个字符） */
		CSTR name;

	} data;

} aiFace_CreateMemberRepositoryRequest;

C_API aiFace_CreateMemberRepositoryRequest *HSAPI_INIT(aiFace_CreateMemberRepositoryRequest);

typedef struct aiFace_CreateMemberRepositoryResponse 
{
	HsviewResponse base;

	struct aiFace_CreateMemberRepositoryResponseData
	{
		
		/** [long]成员id，成功时有效 */
		int64 memberId;
 
	} data;

} aiFace_CreateMemberRepositoryResponse;

C_API aiFace_CreateMemberRepositoryResponse *HSAPI_INIT(aiFace_CreateMemberRepositoryResponse);

#endif
