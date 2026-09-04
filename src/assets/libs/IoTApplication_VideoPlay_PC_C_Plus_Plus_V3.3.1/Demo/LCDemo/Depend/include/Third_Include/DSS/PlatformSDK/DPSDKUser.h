/**
 * Copyright (c) 2012, 浙江大华
 * All rights reserved.
 *
 * 文件名称：
 * 文件标识：
 * 摘　　要：Platform SDK的接口文件,用户管理子模块
 *
 * 当前版本：1.0
 * 原作者　：汪文军
 * 完成日期：2012年11月12日
 * 修订记录：创建

 --------------------------------------
 * auth: minchieh
 * brief: 这个文件是给pss用的,不知道是否有行业线在用这个头文件
 * date: 2014年3月1日
 --------------------------------------
 */

#ifndef INCLUDED_DPSDK_DPSDKUSER_H
#define INCLUDED_DPSDK_DPSDKUSER_H

#include "DPSDK.h"

BEGIN_NAMESPACE_DPSDK
//////////////////////////////////////////////////////////////////////////

// 
typedef enum 
{
	USER_ADMIN,												// 管理员
	USER_OPER,												// 操作员
}user_type_e;

// 
typedef enum 
{
	SYS_RIGHT_DEV_CFG				= 0x0001,				// 设备配置
	SYS_RIGHT_TVWALL_CFG			= 0x0002,				// 电视墙配置
	SYS_RIGHT_TVWALL_OPER			= 0x0004,				// 电视墙操作
	SYS_RIGHT_EMAP_CFG				= 0x0008,				// 电子地图配置
	SYS_RIGHT_EMAP_OPRR				= 0x0010,				// 电子地图操作
	SYS_RIGHT_LOGVIEW				= 0x0020,				// 日志查看
	SYS_RIGHT_ALARM_CFG				= 0x0040,				// 报警配置
	SYS_RIGHT_USER_CFG				= 0x0080,				// 用户配置
	SYS_RIGHT_BASE_CFG				= 0x0100,				// 基本配置
	SYS_RIGHT_PCNVR_MGR				= 0x0200,				// PC-NVR管理
	SYS_RIGHT_COUNT					= 0x0400,				// 人数统计
	SYS_RIGHT_BHV_ANZ				= 0x0800,				// 行为分析
	SYS_RIGHT_FACE_DETECT			= 0x1000,				// 人脸检测
}user_system_e;

// 
typedef enum 
{
	SYS_CHNL_REALVIEW				= 0x10,					// 实时视频
	SYS_CHNL_ALARM					= 0x20,					// 报警
	SYS_CHNL_PLAYBACK				= 0x40,					// 回放
	SYS_CHNL_DOWNLOAD				= 0x80,					// 下载
	SYS_CHNL_RECORD					= 0x01,					// 录像：针对监视和回放页面上的录像操作
	//SYS_CHNL_PIC					= 0x02,					// 抓图：针对监视和回放页面上的抓图操作
	SYS_CHNL_PTZ_CTL				= 0x04,					// 云台控制
	SYS_CHNL_DEV_CFG				= 0x08,					// 设备参数配置
}user_chnl_e;

// 
typedef struct DPSDK_API tagUserInfo
{
	user_type_e		nUserType;								// 用户类型
	int				nUserID;								// 用户ID
	char			szUserName[60];							// 用户名
	char			szPassword[60];							// 用户密码
	char			szDesc[256];							// 用户描述

	tagUserInfo(void);
}UserInfo;
//////////////////////////////////////////////////////////////////////////

class DPSDK_API IDPSDKUser : public IDPSDKFuncBase
{
public:
	/** 添加用户
	    @param const UserInfo* pUser						用户数据结构
	    @return												
	*/
	virtual int32_t AddUser(const UserInfo* pUser) = 0;

	/** 删除用户
	    @param int32_t nUserID								用户ID，ID=-1表示删除所有用户
	    @return												
	*/
	virtual int32_t DelUser(int32_t nUserID) = 0;

	/** 根据用户名得到用户ID
	    @param const char* userName							用户名
	    @return												
	*/
	virtual int32_t GetUserId(const char* userName) = 0;

	/** 修改用户信息
	    @param int32_t nUserID								用户ID
		@param const UserInfo* pUserInfo					用户信息
	    @return												
	*/
	virtual int32_t ModifyUserInfo(int32_t nUserID, const UserInfo* pUserInfo) = 0;

	/** 获取用户信息
	    @param int32_t nUserID								用户ID
		@param UserInfo* pUserInfo							用户信息
	    @return												
	*/
	virtual int32_t GetUserInfo(int32_t nUserID, UserInfo* pUserInfo) = 0;

	/** 设置模块打开权限（针对操作员有效）
	    @param int32_t nUserID								用户ID
		@param int32_t nSysRights							系统模块打开权限(user_system_e)
	    @return												
	*/
	virtual int32_t ModifyOperMoudleRight(int32_t nUserID, int32_t nSysRights) = 0;

	/** 获取模块打开权限（针对操作员有效）
	    @param int32_t nUserID								用户ID
		@param int32_t& nSysRights							系统模块打开权限(user_system_e)
	    @return												
	*/
	virtual int32_t GetOperMoudleRight(int32_t nUserID, int32_t& nSysRights) = 0;

	/** 模块打开权限判断（针对操作员有效）
	    @param int32_t nUserID								用户ID
		@param user_system_e nRight							系统模块打开权限
	    @return												
	*/
	virtual bool IsOperMoudleRight(int32_t nUserID, user_system_e nRight) = 0;

	/** 设置通道权限（针对操作员有效）
	    @param int32_t nUserID								用户ID
		@param char* szChnlID								通道ID
		@param int32_t nChnlRight							通道打开权限(user_chnl_e)
	    @return												
	*/
	virtual int32_t ModifyChnlOperRight(int32_t nUserID, char* szChnlID, int32_t nChnlRight) = 0;

	/** 获取通道权限（针对操作员有效）
	    @param int32_t nUserID								用户ID
		@param char* szChnlID								通道ID
		@param int32_t& nChnlRight							通道打开权限(user_chnl_e)
	    @return												
	*/
	virtual int32_t GetChnlOperRight(int32_t nUserID, char* szChnlID, int32_t& nChnlRight) = 0;

	/** 判断某个通道是否具有相应权限（针对操作员有效）
	    @param int32_t nUserID								用户ID
		@param char* szChnlID								通道ID
		@param user_chnl_e nChnlRight						通道打开权限
	    @return												
	*/
	virtual bool IsChnlOperRight(int32_t nUserID, char* szChnlID, user_chnl_e nChnlRight) = 0;

	/** 获取所有用户ID数目
	    @return												
	*/
	virtual int32_t GetAllUserIDNum(void) = 0;

	/** 获取所有用户ID
	    @param int32_t* pIDs								用户ID数组
		@param int32_t nNum									上述数组的大小
	    @return												
	*/
	virtual int32_t GetAllUserID(int32_t* pIDs, int32_t nNum) = 0;

	/** 更新
	    @return												
	*/
	virtual int32_t FinshUpdate(void)=0;

protected:
	virtual ~IDPSDKUser(void){}
};
//////////////////////////////////////////////////////////////////////////

END_NAMESPACE_DPSDK

#endif
