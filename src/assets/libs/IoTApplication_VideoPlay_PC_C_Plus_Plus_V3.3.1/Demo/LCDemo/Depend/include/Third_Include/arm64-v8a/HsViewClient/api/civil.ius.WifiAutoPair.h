/**
 *  Auto created by ApiCreator Tool.
 *  SVN Rev: 0, Author: unknown, Date: unknown
 *  SHOULD NOT MODIFY!
 */
 
#ifndef _HSVIEW_CLIENT_API_WifiAutoPair_H_
#define _HSVIEW_CLIENT_API_WifiAutoPair_H_

#include "HsviewClientSdk.h"

/** DESCRIPTION: 
routeInfo：格式按照键值对，分号分隔无回车或换行：
		SSID：热点名称;
		Key：密码;
		Mac：路由器MAC地址;
		Chn：通道号;
		Encryption：鉴权及加密方式;
		WorkMode：工作模式;
		DataRate：传输速率;
		RSSI：信号强度;
		RouteModel：路由器型号;
		无法获取的字段值填"Unkown"

 */

typedef struct WifiAutoPairRequest 
{
	HsviewRequest base;

	struct WifiAutoPairRequestData
	{
		
		/** WIFI_AUTOPAIR，类型 */
		CSTR type;
		/** [int]本地信息索引 */
		int index;
		/** iOS 9.3.5，String 手机系统版本，无法获取时填Unkown */
		CSTR phoneVer;
		/** 2016-09-13 15:53:30，操作结束时间 */
		CSTR endTime;
		/** SSID=AAA;key=123;Mac=AA:BB:CC::DD:EE:FF;Chn=6;Encryption=WPA2-PSK-AES;WorkMode=11b/g/n;DataRate=54m/bps;RSSI=70;RouteModel=TL-WR855N，路由器信息 */
		CSTR routeInfo;
		/** AABBCCDDEEFFGGHHIIJJKKLL，发送的数据，十六进制 */
		CSTR Data;
		/** CE-A-TP1，设备型号 */
		CSTR deviceType;
		/** 13012345678，账号信息 */
		CSTR userName;
		/** YPC4TEST00A0003，设备序列号 */
		CSTR deviceSN;
		/** [bool]false，是否存在人为中断 */
		BOOL interruption;
		/** [bool]true，是否搜到设备应答 */
		BOOL getDevRsp;
		/** 2016-09-13 15:52:00，操作开始时间 */
		CSTR startTime;
		/** Success，操作结果 */
		CSTR result;
		/** iPhone 6，手机类型，无法获取时填Unkown */
		CSTR phoneType;

	} data;

} WifiAutoPairRequest;

C_API WifiAutoPairRequest *HSAPI_INIT(WifiAutoPairRequest);

typedef struct WifiAutoPairResponse 
{
	HsviewResponse base;

	struct WifiAutoPairResponseData
	{
		
		/** [int][O]保留 */
		int _nouse;
 
	} data;

} WifiAutoPairResponse;

C_API WifiAutoPairResponse *HSAPI_INIT(WifiAutoPairResponse);

#endif
