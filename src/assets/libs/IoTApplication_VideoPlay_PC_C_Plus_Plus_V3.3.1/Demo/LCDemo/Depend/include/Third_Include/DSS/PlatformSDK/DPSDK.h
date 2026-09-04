/**
 * Copyright (c) 2012, 浙江大华
 * All rights reserved.
 *
 * 文件名称：
 * 文件标识：
 * 摘　　要：Platform SDK 接口文件 
 *
 * 当前版本：1.0
 * 原作者　：俞露
 * 完成日期：2012年6月6日
 * 修订记录：创建
 */

#ifndef INCLUDED_DPSDK_DPSDK_H
#define INCLUDED_DPSDK_DPSDK_H

#include "DPSDKDefine.h"


BEGIN_NAMESPACE_DPSDK
//////////////////////////////////////////////////////////////////////////

/** 业务子模块基类. */
class DPSDK_API IDPSDKFuncBase
{
public:
	/** 获取模块类型.
		@return					模块类型值，请参照dpsdk_func_mdl_e			
	*/
	virtual dpsdk_func_mdl_e GetFuncType() const = 0;

	/** 添加事件监听.
	    @param	cb				上层的函数指针
	    @param  userParam		回调用户参数
		@return					=0成功 其他失败	
		@remark					注意不允许在事件回调中进行Add/DelCallback操作.
	*/
	virtual int AddCallbackInfo( fDPSDKCallback cb, void* userParam ) = 0;

	/** 取消事件监听.
		@param	cb				上层的函数指针
		@return		            =0成功 其他失败	
		@remark					注意不允许在事件回调中进行Add/DelCallback操作.
	*/
	virtual int DelCallbackInfo( fDPSDKCallback cb, void* userParam ) = 0;

protected:
	virtual ~IDPSDKFuncBase(){}  // 业务子模块不需要释放
};

/** SDK接口抽象. */
class DPSDK_API IDPSDKEntity
{
public:
	
	/** SDK初始化.
		@return					=0成功 其他失败			
	*/
	virtual int Init() = 0;
	
	/** SDK释放.
		@return					=0成功 其他失败			
	*/
	virtual int UnInit() = 0;

	/** 获取子模块对象.
		@param	mdlId			模块类型值，请参照dpsdk_func_mdl_e
		@return					子模块指针，使用时可强转			
	*/
	virtual IDPSDKFuncBase* GetFuncMdl( dpsdk_func_mdl_e mdlId ) = 0;
	
	/** SDK配置.
		@param  bAutoConnectServerList true:由DPSDK负责连接服务列表，false:上层主动出发连接服务列表，需要调用DPSDKGeneral中的QueryServerList()
		@return					=0成功 其他失败			
	*/
	virtual int SetConfig( dpsdk_config_deviceid_type_e typeDevId = CFG_DEVICE_NORMAL,
							dpsdk_check_right_e right = DPSDK_CHECK_RIGHT,
							dpsdk_get_alarm_e alarm = DPSDK_NEED_ALARM,
							dpsdk_get_devid_type_e getDevIdType = DPSDK_GET_DEVID_BY_DGP,
							dpsdk_group_cache_type_e enmuGroupCache = DPSDK_GROUP_CACHE,
							dpsdk_group_filter_e enumGroupFilter = DPSDK_NO_GROUP_FILTER,
							dpsdk_scs_transport_mode enumScsTransportMode = DPSDK_SCS_TRANSPORT_MODE_SIP,
							bool bAutoConnectServerList = true) = 0;


	virtual void IgnoreGroupChange( bool bIgnore ) = 0;

	/** 设置是否采用压缩格式获取组织结构信息.
		@return					=0成功 其他失败			
	*/
	virtual int SetDevInfoCompressType(dpsdk_get_devinfo_compress_type_e nCompressType = DPSDK_GET_DEVINFO_BY_UNCOMPRESS) = 0;

	/**	设置SCS服务消息传输模式
	*/
	virtual int SetScsTransportMode(dpsdk_scs_transport_mode nScsTransportMode = DPSDK_SCS_TRANSPORT_MODE_SIP) = 0;

	//add by feng_jian 获得SDK生命周期内唯一的顺序
	virtual int GetSequence() = 0;

	/** 设置压缩获取后 开辟解压控件的大小.
		@param	nDataLen		空间大小，单位MB		
	*/
	virtual void SetUncompressDataLen( int nDataLen ) = 0;

	/** 设置压缩获取后 开辟Base64解密控件的大小.
		@param	nDataLen		空间大小，单位MB		
	*/
	virtual void SetUnBaseDataLen(int nDataLen) = 0;

	/** 设置SDK参数.
		@return					=0成功 其他失败			
	*/
	virtual int SetDPSDKParam(DPSDK_Param_t* pDPSDKParam = NULL) = 0;

	/** 设置分布式离线情况下向CMS查询设备状态使能和定时检测的时间间隔.
		@param	bEnable			使能开关，true开启，false不启用
		@param	nTimeInterval	DMS离线情况下，定时向CMS查询设备状态的时间间隔，单位分
	*/
	virtual void SetQueryDevStatusByCmsInfo(bool bEnable, int nTimeInterval) = 0;

protected:
	virtual ~IDPSDKEntity(){} // 不能直接释放，使用工厂接口释放
};

/** SDK对象创建工厂. */
class DPSDK_API DPSDKFactory
{
public:
	/** 创建SDK对象. 
	    @return					对象实例指针  
	*/
	static IDPSDKEntity * CreateSDKEntity(DPSDK_CreateParam_t* pDPSDKParam = NULL);

	/** 释放SDK对象.
	    @param  pEntiy			对象指针
		@return					=0成功 其他失败
	*/
	static int ReleaseSDKEntity( IDPSDKEntity * pEntity );
};
//////////////////////////////////////////////////////////////////////////

END_NAMESPACE_DPSDK

#endif
