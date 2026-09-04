/**
 * Copyright (c) 2012, 浙江大华
 * All rights reserved.
 *
 * 文件名称：
 * 文件标识：
 * 摘　　要：Platform SDK的接口文件,报警子模块
 *
 * 当前版本：1.0
 * 原作者　：12760
 * 完成日期：
 * 修订记录：创建
 */

#ifndef INCLUDED_DPSDK_DPSDKALARM_H
#define INCLUDED_DPSDK_DPSDKALARM_H

#include "DPSDK.h"
#include "DPSDKPtz.h"
#include <string>

BEGIN_NAMESPACE_DPSDK
//////////////////////////////////////////////////////////////////////////

// 报警发生类型
typedef enum
{
	ALARM_EVENT_OCCUR					= 1,					// 报警产生
	ALARM_EVENT_DISAPPEAR,										// 报警消失
	ALARM_ENENT_PULSE,											// 脉冲状态
}dpsdk_event_type_e;

// 报警处理类型
typedef enum
{
	ALARM_DEALWITH_ALL					= -1,					// 全部状态报警
	ALARM_DEALWITH_PENDING				= 1,					// 处理中	1	-》 1
	ALARM_DEALWITH_RESOLVE				= 2,					// 已解决	2	-》 2
	ALARM_DEALWITH_SUGGESTTED			= 4,					// 误报		4	-》 3
	ALARM_DEALWITH_IGNORED				= 8,					// 忽略		8	-》 4
	ALARM_DEALWITH_UNPROCESSED			= 16,					// 未解决	16	-》 5
	ALARM_DEALWITH_TEST					= 32,					// 测试		32	-》 6
}dpsdk_alarm_dealwith_e;

// 报警类型
typedef enum
{
	ALARM_TYPE_Unknown					= 0,					// 未知(查询报警时可用于查询所有报警，即不过滤报警类型)
	ALARM_TYPE_VIDEO_LOST				= 1,					// 视频丢失
	ALARM_TYPE_EXTERNAL_ALARM			= 2,					// 外部报警
	ALARM_TYPE_MOTION_DETECT			= 3,					// 移动侦测
	ALARM_TYPE_VIDEO_SHELTER			= 4,					// 视频遮挡
	ALARM_TYPE_DISK_FULL				= 5,					// 硬盘满
	ALARM_TYPE_DISK_FAULT				= 6,					// 硬盘故障
	ALARM_TYPE_FIBER					= 7,					// 光纤报警
	ALARM_TYPE_GPS						= 8,					// GPS信息
	ALARM_TYPE_3G						= 9,					// 3G

	//设备巡检
	ALARM_TYPE_STATUS_RECORD			= 10,					// 设备录像状态
	ALARM_TYPE_STATUS_DEVNAME			= 11,					// 设备名
	ALARM_TYPE_STATUS_DISKINFO			= 12,					// 硬盘信息

	ALARM_TYPE_IPC_OFF					= 13,					// 前端IPC断线

	ALARM_TYPE_DEV_DISCONNECT			= 16,					//设备断线报警

	//景德镇华润燃气项目 
	ALARM_POWER_INTERRUPT				= 17,					// 市电中断报警 
	ALARM_POWER_ENABLED					= 18,					// 市电启用报警 
	ALARM_INFRARED_DETECT				= 19,					// 红外探测报警 
	ALARM_GAS_OVER_SECTION				= 20,					// 燃气浓度超过上限 
	ALARM_FLOW_OVER_SECTION				= 21,					// 瞬时流量超过上限 
	ALARM_TEMPERATURE_OVER_SECTION		= 22,					// 温度超过上限 
	ALARM_TEMPERATURE_UNDER_SECTION		= 23,					// 温度低于下限 
	ALARM_PRESSURE_OVER_SECTION			= 24,					// 压力超过上限 
	ALARM_PRESSURE_UNDER_SECTION		= 25,					// 压力低于下限
	
	ALARM_STATIC_DETECTION              = 26,					// 静态检测 
	ALARM_REGULAR						= 27,					// 定时报警
	ALARM_REMOTE_EXTERNAL_ALARM			= 28,					// 远程外部报警
	ALARM_BUTTON_EXTERNAL_ALARM			= 29,					// 报警按钮外部报警
	ALARM_POWER_INTERRUPT_EXTERNAL_ALARM = 30,					// 断电信号外部报警
	ALARM_RECORD_LOSS 					= 31,		            // 录像丢失事件，指硬盘完好的情况下，发生误删等原因引起
	ALARM_VIDEO_FRAME_LOSS				= 32,		            // 视频丢帧事件，比如网络不好或编码能力不足引起的丢帧
	ALARM_RECORD_VOLUME_FAILURE         = 33,                   // 由保存录像的磁盘卷发生异常，引起的录像异常

	//门禁
	ALARM_DOOR_BEGIN					= 40,					// 门禁设备报警起始
	ALARM_FORCE_CARD_OPENDOOR			= 41,					// 胁迫刷卡开门
	ALARM_VALID_PASSWORD_OPENDOOR		= 42,					// 合法密码开门
	ALARM_INVALID_PASSWORD_OPENDOOR		= 43,					// 非法密码开门
	ALARM_FORCE_PASSWORD_OPENDOOR		= 44,					// 胁迫密码开门
	ALARM_VALID_FINGERPRINT_OPENDOOR	= 45,					// 合法指纹开门
	ALARM_INVALID_FINGERPRINT_OPENDOOR  = 46,					// 非法指纹开门
	ALARM_FORCE_FINGERPRINT_OPENDOOR	= 47,					// 胁迫指纹开门
	ALARM_REMOTE_METHOD_OPENDOOR		= 48,					// 远程开门:室内机开门/平台远程开门
	ALARM_BUTTON_METHOD_OPENDOOR		= 49,					// 按钮开门
	ALARM_LOCKKEY_METHOD_OPENDOOR		= 50,					// 钥匙开门
	ALARM_TYPE_VALID_CARD_READ			= 51,					// 合法刷卡/开门
	ALARM_TYPE_INVALID_CARD_READ		= 52,					// 非法刷卡/开门
	ALARM_TYPE_DOOR_MAGNETIC_ERROR		= 53,					// 门磁
	ALARM_TYPE_DOOR_BREAK				= 54,					// 异常开门
	ALARM_TYPE_DOOR_ABNORMAL_CLOSED		= 55,					// 异常关门
	ALARM_TYPE_DOOR_NORMAL_CLOSED		= 56,					// 正常关门
	ALARM_TYPE_DOOR_OPEN				= 57,					// 正常开门
	ALARM_TALK_REQUEST				 	= 59,					//门禁对讲请求报警
	ALARM_DOOR_OPEN_TIME_OUT_BEG		= 60,
	ALARM_VALID_FACE_OPENDOOR			= 61,					// 合法人脸开门
	ALARM_INVALID_FACE_OPENDOOR			= 62,					// 非法人脸开门
	ALARM_DOOR_OPEN_TIME_OUT_THIRD      = 63,                   // 超时等级三
	ALARM_DOOR_OPEN_TIME_OUT_FOUR       = 64,                   // 超时等级四
	ALARM_DOOR_OPEN_TIME_OUT_FIVE       = 65,                   // 超时等级五
	ALARM_DOOR_OPEN_TIME_OUT_ONE        = 66,                   // 超时等级一
	ALARM_DOOR_OPEN_TIME_OUT_SECOND     = 67,                   // 超时等级二
	ALARM_DOOR_OPEN_TIME_OUT_END		= 70,
	ALARM_DOOR_INVALID_SECOND_OPEN		= 71,					// 文教卫河东幼儿园需求，同一孩子绑定的第二张卡刷卡报警
	//ALARM_DOOR_OPEN_FORCE				= 71,					// 门强制打开
	ALARM_OPEN_DOOR_OVERTIME			= 72,					// 开门超时
	ALARM_LEGAL_CARD_ILLEGAL_TIME		= 73,					// 合法卡非法时间
	ALARM_LEGAL_CARD_ILLEGAL_AREA		= 74,					// 合法卡非法区域
	ALARM_SWING_CARD_RULE_OPEN			= 75,					// 刷卡规则开门 = 75
	ALARM_SWING_CARD_RULE_REQUEST_OPEN	= 76,					// 刷卡规则请求开门 = 76
	ALARM_DOOR_ENTRY					= 77,					// 进门
	ALARM_DOOR_EXIT						= 78,					// 出门
	ALARM_AB_DOOR_DOUBLE_OPEN			= 79,					// AB门双开

	//报警主机
	ALARM_TYPE_ALARMHOST_BEGIN			= 80,
	ALARM_TYPE_ALARM_CONTROL_ALERT		= 81,					// 报警主机报警
	ALARM_TYPE_FIRE_ALARM				= 82,					// 火警
	ALARM_TYPE_ZONE_DISABLED			= 83,					// 防区失效
	ALARM_TYPE_BATTERY_EMPTY			= 84,					// 电池没电-设备报警
	ALARM_TYPE_AC_OFF					= 85,					// 市电断开-设备报警
	//大力高速报警平台报警（上行和下行）
	ALARM_DALI_UP						= 86,					// 上行报警 
	ALARM_DALI_DOWN						= 87,					// 下行报警

	//新增“晨鹰”厂商哨位机报警
	ALARM_PRISONERS_ESCAPE				= 88,					// 犯人逃跑
	ALARM_PRISONERS_RIOT				= 89,					// 犯人暴狱
	ALARM_TARGET_ATTACK					= 90,					// 目标遭袭
	ALARM_NATURAL_DISASTER				= 91,					// 自然灾害
	ALARM_ONEKEY_ALARM					= 92,					// 一键报警
	ALARM_EMERGENCY_BUTTON              = 93,                   // 紧急按钮
	//end 100
	ALARM_BREAKIN_ALARM					= 94,					//两个防区同时入侵
	ALARM_HOST_CHANNEL_OFFLINE			= 95,					// 报警主机通道离线报警
	ALARM_FLASH_LAMP_OFF				= 96,					// 闪光灯离线报警

	ALARM_DISABLE_ARM_ABNORMAL			= 97,					// 撤防异常
	ALARM_BYPASS_ABNORMAL				= 98,					// 旁路异常
	ALARM_ALARMHOST_EXTERNAL_ALARM		= 99,					// 报警主机外部报警

	ALARM_TYPE_ALARMHOST_END			= 100,	

	ALARM_FILESYSTEM				    = 100,					// 文件系统
	ALARM_RAID_FAULT					= 101,					// raid故障
	ALARM_RECORDCHANNELFUNCTION_ABNORMAL= 102,					// 录像通道功能异常
	SVR_HARDDISK_STATUS					= 103,					// 硬盘状态
	ALARM_RECORD_REPAIR                 = 104,					// 录像补全 -P3.0

	//begin电网报警类型
	ELECTRIC_WIRE_SHOCK					= 109,					// 电网触电
	ELECTRIC_WIRE_INTERRUPT				= 110,					// 电网断电
	ELECTRIC_WIRE_SHORT_CIRCUIT			= 111,					// 电网短路
	ELECTRIC_WIRE_BREAKDOWN				= 112,					// 电网故障
	ELECTRIC_WIRE_VOLTAGE_LOW			= 113,					// 电网电压低
	//end
	ALARM_TYPE_RECORD_WRITE_FAIL		= 114,					// 录像写入失败

	//电网报警类型新增begin add by hu_wenjuan
	ELECTRIC_ALARM_BEGIN_EX                         = 115, 
	ELECTRIC_BREAK_CIRCUIT                          = 115,                                  // 电网开路 
	ELECTRIC_SENSE_ALARM                            = 116,                                  // 电网传感报警 
	ELECTRIC_ALARM_END_EX                           = 150,                                  
	//电网报警类型新增end 
	ALARM_FIRE_WARNING                  = 151,                  // 火灾报警
	ALARM_WATER_GAUGE					= 152,					// 水尺报警
	ALARM_SMOKE_DETECTION				= 153,					// 烟感报警

	ALARM_VTT_URGENCY                   = 160,                  // VTT设备紧急按钮报警

	ALARM_APPROVE_LEAVE	                = 165,					// 请销假批准外出报警
	ALARM_DISAPPROVE_LEAVE				= 166, 					// 请销假未批准外出报警
	ALARM_NORMAL_BACK					= 167,					// 请销假正常归队报警
	ALARM_ABNORMAL_BACK					= 168,  				// 请销假异常归队报警

	ALARM_VEHICLE_INVASION				= 196,					//车辆入侵报警
	ALARM_CROSSLINE_DETECTION   		= 198,     				//绊线入侵报警 
	ALARM_CROSSREGION_DETECTION 		= 199,     				//区域入侵报警
	//-M的相关报警在这里添加
	ALARM_MOTOR_BEGIN					= 200,
	ALARM_OVERSPEED_OCCURE				= 201, 					// 超速报警产生
	ALARM_OVERSPEED_DISAPPEAR  			= 202,					// 超速报警消失
	ALARM_DRIVEROUT_DRIVERALLOW			= 203,					// 驶出行区
	ALARM_DRIVERIN_DRIVERALLOW			= 204,					// 驶入行区
	ALARM_DRIVEROUT_FORBIDDRIVE			= 205,					// 驶出禁入区
	ALARM_DRIVERIN_FORBIDDRIVE			= 206,					// 驶入禁入区
	ALARM_DRIVEROUT_LOADGOODS			= 207,					// 驶出装货区
	ALARM_DRIVERIN_LOADGOODS			= 208,					// 驶入装货区
	ALARM_DRIVEROUT_UNLOADGOODS			= 209,					// 驶出卸货区
	ALARM_DRIVERIN_UNLOADGOODS			= 210,					// 驶入卸货区
	ALARM_CAR_OVER_LOAD					= 211,					// 超载
	ALARM_SPEED_SOON_ZERO				= 212,					// 急刹车
	ALARM_3GFLOW						= 213,					// 3G流量
	ALARM_AAC_POWEROFF					= 214,					// ACC断电报警
	ALARM_SPEEDLIMIT_LOWERSPEED			= 215,					// 限速报警 LowerSpeed
	ALARM_SPEEDLIMIT_UPPERSPEED			= 216,					// 限速报警 UpperSpeed 
	ALARM_VEHICLEINFOUPLOAD_CHECKIN		= 217,					// 车载自定义信息上传 CheckIn
	ALARM_VEHICLEINFOUPLOAD_CHECKOUT	= 218,					// 车载自定义信息上传 CheckOut
	ALARM_GPS_REPARI					= 219,					// gps补传
	ALARM_URGENCY						= 220,					// 紧急报警
	ALARM_VEHICLE_LARGE_ANGLE 			= 224,    				// 车载摄像头大角度扭转事件
	ALARM_BATTERYLOWPOWER 				= 225,            		// 电池电量低报警 
	ALARM_TEMPERATURE 					= 226,                  // 温度过高报警 
	ALARM_DEV_VOICE_EX     				= 229,    				// 设备语音请求报警
	ALARM_POWER_OFF_EX     				= 230,    				// 断电报警
	ALARM_ROUTE_OFFSET_EX  				= 231,    				// 线路偏移报警
	ALARM_TYRE_PRESSURE_EX 				= 232,    				// 轮胎气压检测报警
	ALARM_FATIGUE_DRIVING				= 233,					// 疲劳驾驶报警
	ALARM_DRIVER_CHECKIN				= 234,					// 司机签入
	ALARM_DRIVER_CHECHOUT				= 235,					// 司机签出
	ALARM_GAS_LOWLEVEL					= 236,					// 油耗报警
	ALARM_GAS_INFO						= 237,					// 油耗信息
	ALARM_GETIN_STATION					= 238,					// 进站报警
	ALARM_GETOUT_STATION				= 239,					// 出站报警
	ALARM_STATION_BEGIN_IN				= 240,					// 始发站进站报警
	ALARM_STATION_BEGIN_OUT				= 241,					// 始发站出站报警
	ALARM_STATION_END_IN				= 242,					// 终点站进站报警
	ALARM_STATION_END_OUT				= 243,					// 终点站出站报警 <进出站类报警放在一起了>
	ALARM_STAY_STATION_OVERTIME			= 244,					// 停车超时报警
	ALARM_RECOVER_RUNNING				= 245,					// 恢复营运报警
	ALARM_MEAL							= 246,					// 吃饭报警
	ALARM_BLOCK							= 247,					// 路堵报警
	ALARM_CALL							= 248,					// 通话报警
	ALARM_CAR_BREAKDOWN					= 249, 					// 车坏报警
	ALARM_STOP_RUNNING					= 250,					// 停止营运报警
	ALARM_ROBING						= 251, 					// 盗抢报警
	ALARM_DISPUTE						= 252, 					// 纠纷报警
	ALARM_ACCIDENT						= 253, 					// 事故报警
	ALARM_OVER_SPEED					= 254, 					// 超速报警
	ALARM_RENTAL						= 255, 					// 包车报警
	ALARM_MAINTENANCE					= 256, 					// 车辆保养报警
	ALARM_CLOSURE						= 257, 					// 脱保停运报警
	ALARM_OPEN_OR_CLOSE_DOOR			= 258,					// 开关门报警
	ALARM_ILLEGALIN_OVERSPEED			= 259,					// 非法进入限速区报警
	ALARM_ILLEGALOUT_OVERSPEED			= 260,					// 非法驶出限速区报警
	ALARM_ILLEGALIN_DRIVERALLOW			= 261,					// 非法进入行使区报警
	ALARM_ILLEGALOUT_DRIVERALLOW		= 262,					// 非法驶出行使区报警
	ALARM_ILLEGALIN_FORBIDDRIVE			= 263,					// 非法进入禁入区报警
	ALARM_ILLEGALOUT_FORBIDDRIVE		= 264,					// 非法驶出禁入区报警
	ALARM_ILLEGALIN_LOADGOODS			= 265,					// 非法进入装货区报警
	ALARM_ILLEGALOUT_LOADGOODS			= 266,					// 非法驶出装货区报警
	ALARM_ILLEGALIN_UNLOADGOODS			= 267,					// 非法进入卸货区报警
	ALARM_ILLEGALOUT_UNLOADGOODS		= 268,					// 非法驶出卸货区报警
	ALARM_ILLEGALIN_GETIN_STATION		= 269,					// 非法进站报警
	ALARM_ILLEGALIN_GETOUT_STATION		= 270,					// 非法出站报警
    ALARM_DETAINED                      = 272,                  // 车辆滞留报警
    ALARM_DELAY                         = 273,                  // 托班报警，车辆班次拖延
	ALARM_SHAP_TURNING			 		= 274,					// 急转报警
	ALARM_SHAP_SPEEDUP					= 275,					// 急加速
	ALARM_SHAP_SLOWDOWN					= 276,					// 急减速

	ALARM_STOP_OVERTIME					= 277,					// 停车超时报警（辽宁油罐车项目）
	ALARM_RUN_NONWOKINGTIME				= 278,					// 非工作时间驾驶报警（辽宁油罐车项目）
	ALARM_PASSENGER_CHECK_CARD       	= 279,					// 乘客刷卡事件上报（黑龙江校车项目）

	ALARM_BUS_STEAL_OIL       			= 280,					// 偷油事件
	ALARM_BUS_LOW_OIL       			= 281,					// 低油量报警事件
	ALARM_BUS_CUR_OIL       			= 282,					// 当前油耗情况事件

	ALARM_SWIPE_OVERTIME                = 283,                  // 司机没有刷卡（泰国Usupply项目）
	ALARM_DRIVING_WITHOUTCARD           = 284,                  // 司机无卡驾驶（泰国Usupply项目）
	ALARM_NONPOWEROFF_CHECKOUT          = 285,                  // 司机签出没有关闭引擎（泰国Usupply项目)

	ALARM_VEHICLE_TAMPER_ALARM			= 286,					// 车载防拆报警
	ALARM_AAC_POWERON					= 287,					// ACC通电报警
	ALARM_DRIVER_NOTCONFIRM				= 288,					// 司机未确认报警
	ALARM_GPS_NOT_ALIGNED				= 289,					// gps异常报警
	ALARM_POWER_SWITCHER   				= 290,                  //（过流）供电电源开关状态异常报警(上海奉贤)

	ALARM_MOTOR_END						= 300,

	//智能报警
	ALARM_IVS_ALARM_BEGIN				= 300,					// 智能设备报警类型在dhnetsdk.h基础上+300（DMS服务中添加）
	ALARM_IVS_ALARM						= 0x00000001 + 300,		// 智能设备报警
	ALARM_CROSSLINEDETECTION			= 0x00000002 + 300,		// 警戒线事件
	ALARM_CROSSREGIONDETECTION			= 0x00000003 + 300,		// 警戒区事件
	ALARM_PASTEDETECTION				= 0x00000004 + 300,		// 贴条事件
	ALARM_LEFTDETECTION					= 0x00000005 + 300,		// 物品遗留事件
	ALARM_STAYDETECTION					= 0x00000006 + 300,		// 停留事件
	ALARM_WANDERDETECTION				= 0x00000007 + 300,		// 徘徊事件
	ALARM_PRESERVATION					= 0x00000008 + 300,		// 物品保全事件
	ALARM_MOVEDETECTION					= 0x00000009 + 300,		// 移动事件
	ALARM_TAILDETECTION					= 0x0000000A + 300,		// 尾随事件
	ALARM_RIOTERDETECTION				= 0x0000000B + 300,		// 聚众事件
	ALARM_FIREDETECTION					= 0x0000000C + 300,		// 火警事件
	ALARM_SMOKEDETECTION				= 0x0000000D + 300,		// 烟雾报警事件
	ALARM_FIGHTDETECTION				= 0x0000000E + 300,		// 斗殴事件
	ALARM_FLOWSTAT						= 0x0000000F + 300,		// 流量统计事件
	ALARM_NUMBERSTAT					= 0x00000010 + 300,		// 数量统计事件
	ALARM_CAMERACOVERDDETECTION			= 0x00000011 + 300,		// 摄像头覆盖事件
	ALARM_CAMERAMOVEDDETECTION			= 0x00000012 + 300,		// 摄像头移动事件
	ALARM_VIDEOABNORMALDETECTION		= 0x00000013 + 300,		// 视频异常事件
	ALARM_VIDEOBADDETECTION				= 0x00000014 + 300,		// 视频损坏事件
	ALARM_TRAFFICCONTROL				= 0x00000015 + 300,		// 交通管制事件
	ALARM_TRAFFICACCIDENT				= 0x00000016 + 300,		// 交通事故事件
	ALARM_TRAFFICJUNCTION				= 0x00000017 + 300,		// 交通路口事件
	ALARM_TRAFFICGATE					= 0x00000018 + 300,		// 交通卡口事件
	ALARM_TRAFFICSNAPSHOT				= 0x00000019 + 300,		// 交通抓拍事件
	ALARM_FACEDETECT					= 0x0000001A + 300,		// 人脸检测事件--正常人脸检测。mark:异常人脸检测（901）在下方定义，类型区分放在DMS,2013.12.10,18842)
	ALARM_TRAFFICJAM					= 0x0000001B + 300,		// 交通拥堵事件
	ALARM_STRANGE_FACEDETECT			= 0x0000001C + 300,		// 陌生人脸事件

	ALARM_TRAFFIC_RUNREDLIGHT			= 0x00000100 + 300,		// 交通违章-闯红灯事件
	ALARM_TRAFFIC_OVERLINE				= 0x00000101 + 300,		// 交通违章-压车道线事件
	ALARM_TRAFFIC_RETROGRADE			= 0x00000102 + 300,		// 交通违章-逆行事件
	ALARM_TRAFFIC_TURNLEFT				= 0x00000103 + 300,		// 交通违章-违章左转
	ALARM_TRAFFIC_TURNRIGHT			    = 0x00000104 + 300,		// 交通违章-违章右转
	ALARM_TRAFFIC_UTURN					= 0x00000105 + 300,		// 交通违章-违章掉头
	ALARM_TRAFFIC_OVERSPEED				= 0x00000106 + 300,		// 交通违章-超速
	ALARM_TRAFFIC_UNDERSPEED			= 0x00000107 + 300,		// 交通违章-低速
	ALARM_TRAFFIC_PARKING				= 0x00000108 + 300,		// 交通违章-违章停车
	ALARM_TRAFFIC_WRONGROUTE			= 0x00000109 + 300,		// 交通违章-不按车道行驶
	ALARM_TRAFFIC_CROSSLANE				= 0x0000010A + 300,		// 交通违章-违章变道
	ALARM_TRAFFIC_OVERYELLOWLINE		= 0x0000010B + 300,		// 交通违章-压黄线
	ALARM_TRAFFIC_DRIVINGONSHOULDER		= 0x0000010C + 300,		// 交通违章-路肩行驶事件  
	ALARM_TRAFFIC_YELLOWPLATEINLANE		= 0x0000010E + 300,		// 交通违章-黄牌车占道事件
	ALARM_CROSSFENCEDETECTION			= 0x0000011F + 300,		// 翻越围栏事件
	ALARM_ELECTROSPARKDETECTION			= 0X00000110 + 300,		// 电火花事件
	ALARM_TRAFFIC_NOPASSING				= 0x00000111 + 300,		// 交通违章-禁止通行事件
	ALARM_ABNORMALRUNDETECTION			= 0x00000112 + 300,		// 异常奔跑事件
	ALARM_RETROGRADEDETECTION			= 0x00000113 + 300,		// 人员逆行事件
	ALARM_INREGIONDETECTION				= 0x00000114 + 300,		// 区域内检测事件
	ALARM_TAKENAWAYDETECTION			= 0x00000115 + 300,		// 物品搬移事件
	ALARM_PARKINGDETECTION				= 0x00000116 + 300,		// 非法停车事件
	ALARM_FACERECOGNITION				= 0x00000117 + 300,		// 人脸识别事件
	ALARM_TRAFFIC_MANUALSNAP			= 0x00000118 + 300,		// 交通手动抓拍事件
	ALARM_TRAFFIC_FLOWSTATE				= 0x00000119 + 300,		// 交通流量统计事件
	ALARM_TRAFFIC_STAY					= 0x0000011A + 300,		// 交通滞留事件
	ALARM_TRAFFIC_VEHICLEINROUTE		= 0x0000011B + 300,		// 有车占道事件
	ALARM_MOTIONDETECT					= 0x0000011C + 300,		// 视频移动侦测事件
	ALARM_LOCALALARM					= 0x0000011D + 300,		// 外部报警事件
	ALARM_PRISONERRISEDETECTION			= 0X0000011E + 300,		// 看守所囚犯起身事件
	ALARM_IVS_B_ALARM_END,										// 以上报警都为IVS_B服务的报警类型，与SDK配合

	ALARM_VIDEODIAGNOSIS				= 0X00000120 + 300,		// 视频诊断结果事件
	ALARM_IVS_V_ALARM                   = ALARM_VIDEODIAGNOSIS,
	ALARM_IVS_DENSITYDETECTION			= 0X00000121 + 300,		// 人员密集度检测事件
	ALARM_IVS_QUEUEDETECTION			= 0x00000123 + 300,     // 排队检测报警事件
	ALARM_IVS_TRAFFIC_VEHICLEINBUSROUTE = 0x00000124 + 300,     // 占用公交车道事件
	ALARM_IVS_TRAFFIC_BACKING			= 0x00000125 + 300,     // 违章倒车事件
	ALARM_IVS_AUDIO_ABNORMALDETECTION   = 0x00000126 + 300,		// 声音异常检测
	ALARM_IVS_TRAFFIC_RUNYELLOWLIGHT    = 0x00000127 + 300,     // 交通违章-闯黄灯事件
	//福安看守所
	ALARM_CLIMB_UP						= 0x00000128 + 300,		// 攀高检测 
	ALARM_LEAVE_POST  					= 0x00000129 + 300,		// 离岗检测

	ALARM_IVS_TRAFFIC_PARKINGONYELLOWBOX= 0x0000012A + 300,        // 黄网格线抓拍事件
	ALARM_IVS_TRAFFIC_PARKINGSPACEPARKING = 0x0000012B + 300,        // 车位有车事件(对应 DEV_EVENT_TRAFFIC_PARKINGSPACEPARKING_INFO)
	ALARM_IVS_TRAFFIC_PARKINGSPACENOPARKING = 0x0000012C + 300,        // 车位无车事件(对应 DEV_EVENT_TRAFFIC_PARKINGSPACENOPARKING_INFO)    
	ALARM_IVS_TRAFFIC_PEDESTRAIN		= 0x0000012D + 300,        // 交通行人事件(对应 DEV_EVENT_TRAFFIC_PEDESTRAIN_INFO)
	ALARM_IVS_TRAFFIC_THROW				= 0x0000012E + 300,        // 交通抛洒物品事件(对应 DEV_EVENT_TRAFFIC_THROW_INFO)
	ALARM_IVS_TRAFFIC_IDLE				= 0x0000012F + 300,        // 交通空闲事件
	
	ALARM_VEHICLEACC 					= 0x00000130 + 300,		// 车载ACC断电报警事件 
	ALARM_VEHICLE_TURNOVER		 		= 0x00000131 + 300,     // 车辆侧翻报警事件
	ALARM_VEHICLE_COLLISION        		= 0x00000132 + 300,     // 车辆撞车报警事件

	ALARM_FIGHT							= 0x00000133 + 300,		//打架斗殴
	ALARM_VIDEO_ABNORMAL				= 0x00000136 + 300,		//视频异常
	ALARM_IVS_TRAFFIC_OVERSTOPLINE           = 0X00000137 + 300,        // 压停止线事件(对应 DEV_EVENT_TRAFFIC_OVERSTOPLINE)
	ALARM_IVS_TRAFFIC_WITHOUT_SAFEBELT       = 0x00000138 + 300,        // 交通未系安全带事件(对应 DEV_EVENT_TRAFFIC_WITHOUT_SAFEBELT)
	ALARM_IVS_TRAFFIC_DRIVER_SMOKING         = 0x00000139 + 300,        // 驾驶员抽烟事件(对应 DEV_EVENT_TRAFFIC_DRIVER_SMOKING)
	ALARM_IVS_TRAFFIC_DRIVER_CALLING         = 0x0000013A + 300,        // 驾驶员打电话事件(对应 DEV_EVENT_TRAFFIC_DRIVER_CALLING)
	ALARM_IVS_TRAFFIC_PEDESTRAINRUNREDLIGHT  = 0x0000013B + 300,        // 行人闯红灯事件(对应 DEV_EVENT_TRAFFIC_PEDESTRAINRUNREDLIGHT_INFO)
	ALARM_IVS_TRAFFIC_PASSNOTINORDER         = 0x0000013C + 300,        // 未按规定依次通行(对应DEV_EVENT_TRAFFIC_PASSNOTINORDER_INFO)
	ALARM_IVS_OBJECT_DETECTION               = 0x00000141 + 300,        // 物体特征检测事件

	ALARM_ALARM_ANALOGALARM                  = 0x00000150 + 300,        // 模拟量报警通道的报警事件(对应DEV_EVENT_ALARM_ANALOGALRM_INFO)
	ALARM_IVS_CROSSLINEDETECTION_EX          = 0x00000151 + 300,        // 警戒线扩展事件
	ALARM_ALARM_COMMON                       = 0x00000152 + 300,        // 普通录像
	ALARM_VIDEOBLIND						 = 0x00000153 + 300,        // 视频遮挡事件(对应 DEV_EVENT_ALARM_VIDEOBLIND)
	ALARM_ALARM_VIDEOLOSS                    = 0x00000154 + 300,        // 视频丢失事件
	ALARM_IVS_GETOUTBEDDETECTION             = 0x00000155 + 300,        // 看守所下床事件(对应 DEV_EVENT_GETOUTBED_INFO)
	ALARM_IVS_PATROLDETECTION                = 0x00000156 + 300,        // 巡逻检测事件(对应 DEV_EVENT_PATROL_INFO)
	ALARM_IVS_ONDUTYDETECTION                = 0x00000157 + 300,        // 站岗检测事件(对应 DEV_EVENT_ONDUTY_INFO)
	ALARM_IVS_NOANSWERCALL                   = 0x00000158 + 300,        // 门口机呼叫未响应事件
	ALARM_IVS_STORAGENOTEXIST                = 0x00000159 + 300,        // 存储组不存在事件
	ALARM_IVS_STORAGELOWSPACE                = 0x0000015A + 300,        // 硬盘空间低报警事件
	ALARM_IVS_STORAGEFAILURE                 = 0x0000015B + 300,        // 存储错误事件
	ALARM_IVS_PROFILEALARMTRANSMIT           = 0x0000015C + 300,       // 报警传输事件
	ALARM_IVS_VIDEOSTATIC                    = 0x0000015D + 300,        // 视频静态检测事件(对应 DEV_EVENT_ALARM_VIDEOSTATIC_INFO)
	ALARM_IVS_VIDEOTIMING                    = 0x0000015E + 300,        // 视频定时检测事件(对应 DEV_EVENT_ALARM_VIDEOTIMING_INFO)
	ALARM_IVS_HEATMAP                        = 0x0000015F + 300,        // 热度图(对应 CFG_IVS_HEATMAP_INFO)
	ALARM_IVS_CITIZENIDCARD                  = 0x00000160 + 300,        // 身份证信息读取事件(对应 DEV_EVENT_ALARM_CITIZENIDCARD_INFO)
	ALARM_IVS_PICINFO                        = 0x00000161 + 300,        // 图片信息事件(对应 DEV_EVENT_ALARM_PIC_INFO)
	ALARM_IVS_NETPLAYCHECK					 = 0x00000162 + 300,		  // 上网登记事件(对应 DEV_EVENT_ALARM_NETPLAYCHECK_INFO)
	ALARM_IVS_TRAFFIC_JAM_FORBID_INTO		 = 0x00000163 + 300,		// 车辆拥堵禁入事件(对应DEV_EVENT_ALARM_JAMFORBIDINTO_INFO)
	ALARM_IVS_SNAPBYTIME					 = 0x00000164 + 300,		// 定时抓图事件
	ALARM_IVS_PTZ_PRESET					 = 0x00000165 + 300,		// 云台转动到预置点事件
	ALARM_IVS_RFID_INFO						 = 0x00000166 + 300,		// 红外线检测信息事件
	ALARM_IVS_STANDUPDETECTION				 = 0x00000167 + 300,		// 人起立检测事件 
	ALARM_IVS_QSYTRAFFICCARWEIGHT			 = 0x00000168 + 300,		// 交通卡口称重事件(对应 DEV_EVENT_QSYTRAFFICCARWEIGHT_INFO)

	ALARM_IVS_NEAR_DISTANCE_DETECTION		 = 0x00000174 + 300,		// 近距离接触事件
	ALARM_IVS_OBJECTSTRUCTLIZE_PERSON		 = 0x00000175 + 300,		//行人特征检测事件
	ALARM_IVS_OBJECTSTRUCTLIZE_NONMOTOR		 = 0x00000176 + 300,		//非机动车特征检测事件
	ALARM_IVS_TUMBLE_DETECTION				 = 0x00000177 + 300,		// 倒地报警事件

	ALARM_IVS_ALIEN_INVASION				 = 0x00000179 + 300,		//外来人员入侵报警
	ALARM_IVS_BLACKLIST						 = 0x0000017A + 300,		//黑名单报警

	// 新增违章报警类型
	ALARM_VEHICLE_INBUSROUTE			= 700,					// 占用公交车道事件 41
	ALARM_BACKING						= 701,					// 违章倒车事件     42
	ALARM_RUN_YELLOWLIGHT				= 702,					// 闯黄灯事件       43
	ALARM_PARKINGSPACE_PARKING			= 703,					// 车位有车事件     44
	ALARM_PARKINGSPACE_NOPARKING		= 704,					// 车位无车事件     45
	ALARM_COVERINGPLATE					= 705,					// 遮挡号牌           49
	ALARM_PARKINGONYELLOWBOX			= 706,					// 黄网格违章停车     50
	ALARM_THROW							= 707,					// 交通抛洒物事件	  51
	ALARM_PEDESTRAIN					= 708,					// 交通行人事件		  52
	ALARM_HIGH_BEAM_OPEN				= 709,					// 远光灯开启违章	  68
	ALARM_ILLEGAL_WHISTLE				= 710,					// 违法鸣笛			  69
	ALARM_TURN_LEFT_AFTER_STRAIGHT		= 718,					// 左转未礼让直行	  77
	ALARM_NONMOTOR_CROSS_REDLIGHT		= 719,					// 非机动车闯红灯	  78
	ALARM_ILLEGALLY_PARKED_NOTPOINTS	= 720,					// 违章停车（不扣分） 79
	ALARM_BIG_END_SMALL_TURN			= 721,					// 大弯小转			  80
	ALARM_TURN_RIGHT_AFTER_STRAIGHT		= 722,					// 右转不礼让直行	  81
	ALARM_TURN_RIGHT_AFTER_PEOPLE		= 723,					// 右转不礼让直行行人 82
	ALARM_TRAFFIC_QUEUE_JUMP			= 724,					// 车辆加塞           83
	ALARM_COPILOT_UNSAFETY_BELT			= 725,					// 副驾驶未系安全带	  84

	//ALARM_COMPARE_PLATE					= 715,					// 车牌前后对比  79

	//以下为_m3.0新增
	ALARM_IVS_M_BEGIN                   = 800,					// _M3.0特殊的IVS报警开始

	ALARM_IVS_LINKSD					= 0x00000201 + 300,		//813:  球机轮训报警
	ALARM_IVS_TRAFFIC_TIREDPHYSIOLOGICAL= 0x00000207 + 300,        // 生理疲劳驾驶事件
	ALARM_IVS_TRAFFIC_BUSSHARPTURN      = 0x00000208 + 300,        // 车辆急转报警事件
	ALARM_IVS_TRAFFIC_TIREDLOWERHEAD    = 0x0000020A + 300,        // 开车低头报警事件
	ALARM_IVS_TRAFFIC_DRIVERLOOKAROUND  = 0x0000020B + 300,        // 开车左顾右盼事件
	ALARM_IVS_TRAFFIC_DRIVERLEAVEPOST   = 0x0000020C + 300,        // 开车离岗事件
	ALARM_IVS_MAN_STAND_DETECTION		= 0x0000020D + 300,        // 立体视觉站立事件
	ALARM_IVS_TRAFFIC_MAN_NUM_DETECTION = 0x0000020E + 300,        // 立体视觉区域内人数统计事件
	ALARM_IVS_TRAFFIC_DRIVERYAWN        = 0x00000210 + 300,        // 开车打哈欠事件
	ALARM_IVS_HUMANTRAIT				= 0x00000215 + 300,		// 人体特征事件
	ALARM_IVS_INSTALL_CARDREADER		= 0x00000220 + 300,		// 安装读卡器事件
	ALARM_IVS_XRAY_DETECTION			= 0x00000223 + 300,		// X光检测事件 
	ALARM_IVS_CROWDDETECTION			= 0x0000022C + 300,		// 人群密度检测事件
	ALARM_IVS_TRAFFIC_WAITINGAREA		= 0x00000234 + 300,		//违章进入待行区事件						

	ALARM_CROSSLINEDETECTION_HUMAN		= 0x00000235 + 300,		// 人穿越警戒线
	ALARM_CROSSLINEDETECTION_VEHICLE	= 0x00000236 + 300,		// 机动车穿越警戒线
	ALARM_IVS_STEREO_FIGHTDETECTION		= 0x00000237 + 300,		//ATM舱内打架事件
	ALARM_IVS_STEREO_TAILDETECTION		= 0x00000238 + 300,		//ATM舱内尾随事件
	ALARM_IVS_STEREO_STEREOFALLDETECTION= 0x00000239 + 300,		//ATM舱内跌倒事件
	ALARM_IVS_STEREO_STAYDETECTION		= 0x0000023A + 300,		//ATM舱内滞留事件
	ALARM_IVS_BANNER_DETECTION		    = 0x0000023B + 300,		//拉横幅事件
	ALARM_IVS_ELEVATOR_ABNORMAL			= 0x0000023D + 300,		//电动扶梯运行异常事件
	ALARM_IVS_NONMOTORDETECT			= 0x0000023E + 300,		//非机动车检测
	ALARM_IVS_SHOPPRESENCE			    = 0x00000246 + 300,        //商铺占道经营事件
	ALARM_IVS_WASTEDUMPED				= 0x00000247 + 300,        //垃圾违章倾倒事件
	ALARM_IVS_DISTANCE_DETECTION		=	0x0000024A + 300,		//距离异常事件
	ALARM_IVS_FLOWBUSINESS				=	0x0000024B + 300,		//游摊小贩
	//ALARM_ IVS_CITYPARKING			 	 =	0x0000024C + 300,		//城市违停  已扩展为机动车（893）和非机动车（894）违停，定义在后面，此处请勿增加

	ALARM_IVS_CITYPARKING_MOTOR			= 893,		//机动车违章停车
	ALARM_IVS_CITYPARKING_NOMOTOR		= 894,		//非机动车违章停车
	// 以上智能报警已经超过800了，定义值时请计算好之后在确定，请勿随意增加，车载平台请确认一下800是否有用到

	ALARM_IVS_ALARM_CAPTURPIC           = 897,					// 报警抓图
	ALARM_IVS_TIMING_CAPTURPIC          = 898,					// 定时抓图
	ALARM_IVS_CLIENT_CAPTURPIC          = 899,					// 客户端抓图
	ALARM_IVS_M_END                     = 900,					// _M3.0特殊的IVS报警结束

	ALARM_IVS_ABNORMAL_FACEDETECT       = 901,  				// 人脸检测事件--异常人脸检测
	ALARM_IVS_SIMILAR_FACEDETECT		= 902,					// 人脸检测事件--相邻人脸检测
	ALARM_IVS_HIDENOSE_FACEDETECT		= 903,					// 鼻子遮挡报警
	ALARM_IVS_HIDEMOUTH_FACEDETECT		= 904,					// 嘴部遮挡报警
	ALARM_IVS_HIDEEYE_FACEDETECT		= 905,					// 眼部遮挡报警

	ALARM_DETECTIONAREA_PASTEDETECTION	= 920,					// 检测区贴条检测
	ALARM_KEYBOARDAREA_PASTEDETECTION	= 921,					// 键盘区贴条检测
	ALARM_SPIGOTAREA_PASTEDETECTION		= 922,					// 插卡区贴条检测
	ALARM_AUDIO_MUTATION_ALARM			= 923,					// 声强突变报警

	ALARM_AUDIO_DETECT_ALARM			= 924,					// 音频检测报警
	ALARM_AUDIO_ANOMALY_ALARM			= 925,					// 音频异常报警
	ALARM_TRAFFICJUNCTION_NON_MOTOR		= 926,					// 非机动车报警


	// ---ALARM_VIDEOABNORMALDETECTION 报警子类型起始
	ALARM_IVS_VIDEOABNORMAL_SUBBEGIN	= 950,
	ALARM_IVS_VIDEOABNORMAL_LOST		= ALARM_IVS_VIDEOABNORMAL_SUBBEGIN,			// 视频异常事件:视频丢失
	ALARM_IVS_VIDEOABNORMAL_FREEZE		= ALARM_IVS_VIDEOABNORMAL_SUBBEGIN + 1,		// 视频异常事件:视频冻结
	ALARM_IVS_VIDEOABNORMAL_SHELTER		= ALARM_IVS_VIDEOABNORMAL_SUBBEGIN + 2,		// 视频异常事件:摄像头遮挡
	ALARM_IVS_VIDEOABNORMAL_MOTION		= ALARM_IVS_VIDEOABNORMAL_SUBBEGIN + 3,		// 视频异常事件:摄像头移动
	ALARM_IVS_VIDEOABNORMAL_HIGHDARK	= ALARM_IVS_VIDEOABNORMAL_SUBBEGIN + 4,		// 视频异常事件:过暗
	ALARM_IVS_VIDEOABNORMAL_HIGHBRIGHT	= ALARM_IVS_VIDEOABNORMAL_SUBBEGIN + 5,		// 视频异常事件:过亮
	ALARM_IVS_VIDEOABNORMAL_COLORCAST	= ALARM_IVS_VIDEOABNORMAL_SUBBEGIN + 6,		// 视频异常事件:图像偏色
	ALARM_IVS_VIDEOABNORMAL_NOISE		= ALARM_IVS_VIDEOABNORMAL_SUBBEGIN + 7,		// 视频异常事件:噪声干扰
	ALARM_IVS_VIDEOABNORMAL_SCENE_CHANGE = ALARM_IVS_VIDEOABNORMAL_SUBBEGIN + 8,	// 视频异常事件:场景变更
	ALARM_IVS_VIDEOABNORMAL_SUBEND		= 960,
	// ---ALARM_VIDEOABNORMALDETECTION 报警子类型终止
	ALARM_IVS_ZhouShanDrive_SUBBEGIN	       = 961,
	ALARM_IVS_ZhouShanDrive_TiredDriveCheck    = ALARM_IVS_ZhouShanDrive_SUBBEGIN,
	ALARM_IVS_ZhouShanDrive_CallingWhenDriving = ALARM_IVS_ZhouShanDrive_SUBBEGIN + 1,
	ALARM_IVS_ZhouShanDrive_SmokingAlarm       = ALARM_IVS_ZhouShanDrive_SUBBEGIN + 2,
	ALARM_IVS_ZhouShanDrive_SharpTurn          = ALARM_IVS_ZhouShanDrive_SUBBEGIN + 3,
	ALARM_IVS_ZhouShanDrive_LaneDeparture      = ALARM_IVS_ZhouShanDrive_SUBBEGIN + 4,
	ALARM_IVS_ZhouShanDrive_VehicleCollision   = ALARM_IVS_ZhouShanDrive_SUBBEGIN + 5,
	ALARM_IVS_ZhouShanDrive_VehicleTurnover    = ALARM_IVS_ZhouShanDrive_SUBBEGIN + 6,
	ALARM_IVS_ZhouShanDrive_LOOKAROUND         = ALARM_IVS_ZhouShanDrive_SUBBEGIN + 7,
	ALARM_IVS_ZhouShanDrive_LEAVEPOST          = ALARM_IVS_ZhouShanDrive_SUBBEGIN + 8,
	ALARM_IVS_ZhouShanDrive_SUBEND             = 970,

	ALARM_IVS_ALARM_END					= 1000,					// 智能设备报警类型的范围为300-1000

	ALARM_OSD,													// osd信息
	ALARM_CROSS_INFO,											// 十字路口

	ALARM_CLIENT_PLATFORM_BEGIN			= 1100,					// 客户端平台报警开始
	ALARM_DERELICTION					= 1101,					// 遗留检测[交通事件-抛洒物]
	ALARM_RETROGRADATION				= 1102,					// 逆行 [交通事件]
	ALARM_OVERSPEED						= 1103,					// 超速  [交通事件]
	ALARM_LACK_ALARM					= 1104,					// 欠速  [交通事件]
	ALARM_FLUX_COUNT					= 1105,					// 流量统计[交通事件]
	ALARM_PARKING						= 1106,					// 停车检测[交通事件]
	ALARM_PASSERBY						= 1107,					// 行人检测[交通事件]
	ALARM_JAM							= 1108,					// 拥堵检测[交通事件]
	ALARM_AREA_INBREAK					= 1109,					// 特殊区域入侵

	ALARM_OVERSPEED_MANUAL				= 1123,					// 卡口超速报警，PCS报给客户端，客户端触发手动报警给ADS

	//人脸检测事件细化事件（由于人脸检测的类型在DMS中进行区分，所以这两个定义值废弃，但仍保留）
	ALARM_TYPE_ALARM_FACEDETECT_NORMAL  = 1151,					// 人脸检测事件中－正常人脸
	ALARM_TYPE_ALARM_FACEDETECT_UNNORMAL= 1152,					// 人脸检测事件中－异常人脸

	ALARM_CLIENT_PLATFORM_END			= 1200,					// 客户端平台报警结束

	ALARM_SYSTEM_BEGIN					= 1200,					// 来自系统的报警
	ALARM_HOST_TEMPRATURER				= 1201,					// 主机温度过高
	ALARM_RAID_LOAD						= 1202,					// raid降级
	ALARM_SERVER_AUTO_MIGRATE			= 1203,					// 服务器自动迁移
	ALARM_SERVER_MANUAL_MIGRATE			= 1204,					// 服务器手动迁移
	ALARM_SERVER_STATUS_CHANGE			= 1205,					// 服务器状态变更 
	ALARM_MASTER_TO_BACKUP				= 1206,					// 双机热备主机切备机
	ALARM_BACKUP_TO_MASTER				= 1207,					// 双机热备备机切主机
	ALARM_BACKUP_ABNORMAL				= 1208,					// 双机热备备机故障
	ALARM_BACKUP_NORMAL					= 1209,					// 双机热备备机故障恢复
	ALARM_SYSTEM_POWER_OFF				= 1214,					// 系统断电报警【市电断开】
	ALARM_SYSTEM_POWER_ON				= 1215,					// 系统电源恢复报警【市电恢复】
	ALARM_SSD_LIFETIME_ABNORMAL			= 1217,					// SSD寿命异常
	ALARM_SSD_STATUS_ABNORMAL			= 1218,					// SSD状态异常
	ALARM_SYSTEM_END					= 1300,

	//-F 门禁设备报警新增区间（40-70不够用了）
	ALARM_DOOR_NEW_BEGIN				= 1411,
	ALARM_DOOR_FORCE_LOCKED				= 1411,					// 门禁强锁报警
	ALARM_DOOR_FORCE_OPEN				= 1412,					// 门禁强开报警
	ALARM_DOOR_RFID_ACTIVE              = 1421,                 // 有源RFID门禁刷卡报警
	ALARM_DOOR_RFID_PASSIVE             = 1422,                 // 无源RFID门禁刷卡报警
	ALARM_DOOR_VALID_CARD_OPENDOOR_IN	= 1428,					// 对接海康设备 进门刷卡成功
	ALARM_DOOR_VALID_CARD_OPENDOOR_OUT	= 1429,					// 对接海康设备 出门刷卡成功
	ALARM_DOOR_BREAK_IN					= 1430,  				// 门禁闯入事件
	ALARM_DOOR_ERR_NODOORRIGHT			= 1431,					// 该门没有权限
	ALARM_DOOR_ERR_CARDRIGHT_PWDERR		= 1432,					// 卡号正确但是密码错误
	ALARM_DOOR_BLACK_USER				= 1433,					// 黑名单用户
	ALARM_VALID_VRCODE_OPENDOOR			= 1434,					// 合法二维码开门
	ALARM_INVALID_VRCODE_OPENDOOR		= 1435,					// 非法二维码开门
	ALARM_VALID_IDCARD   				= 1436,					// 人证合法开门	
	ALARM_INVALID_IDCARD				= 1437,					// 人证非法开门
	ALARM_INVALID_IDCARD_AND_IC	 		= 1438,					// 人证和身份证非法开门
	ALARM_VALID_IDCARD_AND_IC			= 1439,					// 人证和身份证合法开门
	ALARM_PATROL_STATUS  				= 1440,					// 巡更状态报警
	ALARM_VALID_BT_OPENDOOR	 			= 1441,					// 蓝牙合法开门
	ALARM_INVALID_BT_OPENDOOR			= 1442,					// 蓝牙非法开门
	ALARM_DOOR_LOCAL_ALARM				= 1443,					// 门禁外部报警
	ALARM_DOOR_CHANL_MODEL				= 1444,					// 通道模式
	ALARM_DOOR_CHANL_AWAYS_STATUS		= 1445,					// 通道常开，常关状态
	ALARM_DOOR_MALICIOUT				= 1446,					// 二代门禁非法卡超次报警
	ALARM_DOOR_HEIGHTLIMIT              = 1447,                 // 门禁限高报警
	ALARM_DOOR_RFID						= 1448,					// RFID感应报警
	ALARM_DOOR_RFID_INVALID				= 1449,					// RFID非法感应报警
	ALARM_DOOR_RFID_LOCAL				= 1450,					// RFID外部报警(按键报警)
	ALARM_RFID_PEOPLE_UPPER_LIMIT		= 1451,					// RFID人数上限报警
	ALARM_DOOR_NEW_END					= 1499,

	// -E 视频质量诊断 新增12种报警类型
	ALARM_VQDS_VIDEO_LOST				= 1500,					// 视频质量诊断-视频丢失
	ALARM_VQDS_HIGHBRIGHT				= 1501,					// 高亮度警告
	ALARM_VQDS_HIGHBRIGHT_RED			= 1502,					// 高亮度红色报警
	ALARM_VQDS_LOWBRIGHT				= 1503,					// 低亮度警告
	ALARM_VQDS_LOWBRIGHT_RED			= 1504,					// 低亮度红色报警
	ALARM_VQDS_CONTRAST					= 1505,					// 对比度警告
	ALARM_VQDS_CONTRAST_RED				= 1506,					// 对比度红色报警
	ALARM_VQDS_CLARITY					= 1507,					// 清晰度警告
	ALARM_VQDS_CLARITY_RED				= 1508,					// 清晰度红色报警
	ALARM_VQDS_COLOR_OFFSET				= 1509,					// 色彩偏差警告
	ALARM_VQDS_COLOR_OFFSET_RED			= 1510,					// 偏色红色报警
	ALARM_VQDS_DIAGNOSE_FAIL			= 1511,					// 视频质量诊断失败
	
	ALARM_ALARMHOST_MEDICAL				 = 1604,				 // 医疗报警
	ALARM_ALARMHOST_URGENCY				 = 1605,				 // 报警主机紧急报警
	ALARM_ALARMHOST_CATCH				 = 1606,				 // 挟持报警
	ALARM_ALARMHOST_MENACE_SLIENCE       = 1607,				 // 无声威胁
	ALARM_ALARMHOST_PERIMETER            = 1608,				 // 周界报警
	ALARM_ALARMHOST_DEFENCEAREA_24H		 = 1609,				 // 24小时防区报警
	ALARM_ALARMHOST_DEFENCEAREA_DELAY	 = 1610,				 // 延时防区报警
	ALARM_ALARMHOST_DEFENCEAREA_INITIME  = 1611,				 // 及时防区报警
	ALARM_ALARMHOST_BREAK				 = 1612,				 // 防拆
	ALARM_ALARMHOST_AUX_OVERLOAD         = 1613,                 // AUX过流
	ALARM_ALARMHOST_AC_POWDOWN			 = 1614,                 // 交流电掉电
	ALARM_ALARMHOST_BAT_DOWN			 = 1615,                 // 电池欠压
	ALARM_ALARMHOST_SYS_RESET			 = 1616,                 // 系统复位
	ALARM_ALARMHOST_PROGRAM_CHG          = 1617,                 // 电池掉线
	ALARM_ALARMHOST_BELL_CUT			 = 1618,                 // 警号被切断或短路
	ALARM_ALARMHOST_PHONE_ILL			 = 1619,                 // 电话切断或失效
	ALARM_ALARMHOST_MESS_FAIL			 = 1620,				 // 通讯失败
	ALARM_ALARMHOST_WIRELESS_PWDOWN		 = 1621,				 // 无线探测器欠压
	ALARM_ALARMHOST_SIGNIN_FAIL			 = 1622,				 // 登录失败
	ALARM_ALARMHOST_ERR_CODE			 = 1623,				 // 错误密码登陆
	ALARM_ALARMHOST_MANAUL_TEST			 = 1624,				 // 手动测试
	ALARM_ALARMHOST_CYCLE_TEST			 = 1625,				 // 定期测试
	ALARM_ALARMHOST_SVR_REQ				 = 1626,				 // 服务请求
	ALARM_ALARMHOST_BUF_RST				 = 1627,				 // 报警缓冲复位
	ALARM_ALARMHOST_CLR_LOG				 = 1628,				 // 清除日志
	ALARM_ALARMHOST_TIME_RST			 = 1629,				 // 日期时间复位
	ALARM_ALARMHOST_NET_FAIL			 = 1630,				 // 网络错误
	ALARM_ALARMHOST_IP_CONFLICT			 = 1631,				 // IP冲突
	ALARM_ALARMHOST_KB_BREAK			 = 1632,				 // 键盘防拆
	ALARM_ALARMHOST_KB_ILL               = 1633,				 // 键盘问题
	ALARM_ALARMHOST_SENSOR_O			 = 1634,				 // 探测器开路
	ALARM_ALARMHOST_SENSOR_C			 = 1635,				 // 探测器短路
	ALARM_ALARMHOST_SENSOR_BREAK		 = 1636,				 // 探测器防拆
	ALARM_FIRE_ALARM					 = 1637,				 // 报警主机火警
	ALARM_CALL_ALARM_HOST				 = 1652,                 // 电话报警主机设备报警 
	ALARM_CALL_ALARM_HOST_CHN			 = 1653,				 // 电话报警主机通道报警


	
	//动环(PE)报警-(SCS_ALARM_SWITCH_START 取名直接来自SCS动环文档)
	//系统工程动环增加报警类型ALARM_SCS_BEGIN
	//开关量，不可控
	ALARM_SCS_SWITCH_START				= 1800,
	ALARM_SCS_INFRARED,											// 红外对射告警
	ALARM_SCS_SMOKE,											// 烟感告警
	ALARM_SCS_WATER,                							// 水浸告警
	ALARM_SCS_COMPRESSOR,           							// 压缩机故障告警
	ALARM_SCS_OVERLOAD,             							// 过载告警
	ALARM_SCS_BUS_ANOMALY,          							// 母线异常
	ALARM_SCS_LIFE,                 							// 寿命告警
	ALARM_SCS_SOUND,                							// 声音告警
	ALARM_SCS_TIME,                 							// 时钟告警
	ALARM_SCS_FLOW_LOSS,            							// 气流丢失告警
	ALARM_SCS_FUSING,               							// 熔断告警
	ALARM_SCS_BROWN_OUT,            							// 掉电告警
	ALARM_SCS_LEAKING,              							// 漏水告警
	ALARM_SCS_JAM_UP,               							// 堵塞告警
	ALARM_SCS_TIME_OUT,             							// 超时告警
	ALARM_SCS_REVERSE_ORDER,        							// 反序告警
	ALARM_SCS_NETWROK_FAILURE,      							// 组网失败告警
	ALARM_SCS_UNIT_CODE_LOSE,       							// 机组码丢失告警
	ALARM_SCS_UNIT_CODE_DISMATCH,   							// 机组码不匹配告警
	ALARM_SCS_FAULT,                							// 故障告警
	ALARM_SCS_UNKNOWN,              							// 未知告警
	ALARM_SCS_CUSTOM,               							// 自定义告警
	ALARM_SCS_NOPERMISSION,         							// 无权限告警
	ALARM_SCS_INFRARED_DOUBLE,      							// 红外双鉴告警
	ALARM_SCS_ELECTRONIC_FENCE,     							// 电子围栏告警
	ALARM_SCS_UPS_MAINS,            							// 市电正常市电异常
	ALARM_SCS_UPS_BATTERY,          							// 电池正常电池异常
	ALARM_SCS_UPS_POWER_SUPPLY,     							// UPS正常输出旁路供电
	ALARM_SCS_UPS_RUN_STATE,        							// UPS正常UPS故障
	ALARM_SCS_UPS_LINE_STYLE,       							// UPS类型为在线式UPS类  型为后备式
	ALARM_SCS_XC,                   							// 小车
	ALARM_SCS_DRQ,                  							// 断路器
	ALARM_SCS_GLDZ,                 							// 隔离刀闸
	ALARM_SCS_JDDZ,                								// 接地刀闸
	ALARM_SCS_IN_END,											// 请注意这个值，不用把他作为判断值；只标记说“开关量，不可控”结束；
	//因为接下来的“开关量，可控”没有开始标记如ALARM_SCS_DOOR_START

	//开关量，可控，请注意接下来的ALARM_SCS_DOOR_SWITCH这个不能作为BEGIN用
	ALARM_SCS_DOOR_SWITCH				= 1850,					// 门禁控制器开关告警
	ALARM_SCS_UPS_SWITCH,										// UPS开关告警,
	ALARM_SCS_DBCB_SWITCH,          							// 配电柜开关告警
	ALARM_SCS_ACDT_SWITCH,          							// 空调开关告警
	ALARM_SCS_DTPW_SWITCH,          							// 直流电源开关告警
	ALARM_SCS_LIGHT_SWITCH,         							// 灯光控制器开关告警
	ALARM_SCS_FAN_SWITCH,           							// 风扇控制器开关告警
	ALARM_SCS_PUMP_SWITCH,          							// 水泵开关告警
	ALARM_SCS_BREAKER_SWITCH,       							// 刀闸开关告警
	ALARM_SCS_RELAY_SWITCH,         							// 继电器开关告警
	ALARM_SCS_METER_SWITCH,        								// 电表开关告警
	ALARM_SCS_TRANSFORMER_SWITCH,   							// 变压器开关告警
	ALARM_SCS_SENSOR_SWITCH,        							// 传感器开关告警
	ALARM_SCS_RECTIFIER_SWITCH,     							// 整流器告警
	ALARM_SCS_INVERTER_SWITCH,      							// 逆变器告警
	ALARM_SCS_PRESSURE_SWITCH,      							// 压力开关告警
	ALARM_SCS_SHUTDOWN_SWITCH,      							// 关机告警
	ALARM_SCS_WHISTLE_SWITCH,	   								// 警笛告警
	ALARM_SCS_SWITCH_END,
	//模拟量
	ALARM_SCS_ANALOG_START				= 1880,
	ALARM_SCS_TEMPERATURE,										// 温度告警
	ALARM_SCS_HUMIDITY,             							// 湿度告警
	ALARM_SCS_CONCENTRATION,        							// 浓度告警
	ALARM_SCS_WIND,                 							// 风速告警
	ALARM_SCS_VOLUME,               							// 容量告警
	ALARM_SCS_VOLTAGE,              							// 电压告警
	ALARM_SCS_ELECTRICITY,          							// 电流告警
	ALARM_SCS_CAPACITANCE,          							// 电容告警
	ALARM_SCS_RESISTANCE,           							// 电阻告警
	ALARM_SCS_CONDUCTANCE,          							// 电导告警
	ALARM_SCS_INDUCTANCE,           							// 电感告警
	ALARM_SCS_CHARGE,               							// 电荷量告警
	ALARM_SCS_FREQUENCY,            							// 频率告警
	ALARM_SCS_LIGHT_INTENSITY,      							// 发光强度告警(坎)
	ALARM_SCS_PRESS,                							// 力告警（如牛顿，千克力）
	ALARM_SCS_PRESSURE,             							// 压强告警（帕，大气压）
	ALARM_SCS_HEAT_TRANSFER,        							// 导热告警（瓦每平米）
	ALARM_SCS_THERMAL_CONDUCTIVITY, 							// 热导告警（kcal/(m*h*℃)）
	ALARM_SCS_VOLUME_HEAT,          							// 比容热告（kcal/(kg*℃)）
	ALARM_SCS_HOT_WORK,             							// 热功告警（焦耳）
	ALARM_SCS_POWER,                							// 功率告警（瓦）
	ALARM_SCS_PERMEABILITY,         							// 渗透率告警（达西）
	ALARM_SCS_PROPERTION,										// 比例（包括电压电流变比，功率因素，负载单位为%） 
	ALARM_SCS_ENERGY,											// 电能（单位为J）
	ALARM_SCS_ANALOG_END,
	//ALARM_SCS_END,

	ALARM_IP_DEV_TALK					= 1907,					// IP设备对讲报警

	ALARM_TYPE_UNIFY_BEGIN				= 1908,					// 报警类型统一管理，不需要在EnumCenterRecType增加
	ALARM_VOICE_EXCEPTION				= 1909,					// 音频异常报警
	ALARM_RECORD_EXCEPTION				= 1910,					// 录像异常报警
	ALARM_VOICE_LOSE					= 1911,					// 音频丢失报警
	ALARM_WIFITERM_FIND					= 1912,					//WIFI终端发现报警
	ALARM_WIFITERM_SURVEY				= 1913,					//WIFI终端布控报警
	ALARM_PTZ_DIAGNOSES					= 1914,					// 云台诊断信息
	ALARM_SNAP_ALARM					= 1915,					// 通用抓图报警
	ALARM_NO_DISK						= 1916,					// 无硬盘报警	
	ALARM_DOUBLE_DEV_VERSION_ABNORMAL	= 1917,					// 双控设备主板与备板之间版本信息不一致异常事件
	ALARM_DCSSWITCH						= 1918,					// 主备切换事件/集群切换报警
	ALARM_DEV_RAID_FAILED				= 1919,					// 设备RAID错误报警
	ALARM_DEV_RAID_DEGRADED				= 1920,					// 设备RAID降级报警
	ALARM_BUF_DROP_FRAME				= 1921,					// 录像缓冲区丢帧报警

	ALARM_PATIENTDETECTION              = 1923,                 // 监控病人活动状态报警事件

	ALARM_WANDERDETECTION_EVENT			= 1994,					// 徘徊报警
	ALARM_RIOTERDETECTION_EVENT			= 1995,					// 人员聚集报警
	ALARM_SCENNE_CHANGE					= 1996,					// 场景变更报警
	ALARM_VIDEO_UNFOCUS					= 1997,					// 视频虚焦报警
	ALARM_DEV_AUDIO_MUTATION			= 1998,					// 声强突变报警
	ALARM_HEATIMG_TEMPER                = 1999,                 // 热成像测温点温度异常报警事件 

	//AE_ALARM_TYPE_BEGIN					= 2000,				
	ALARM_TYPE_RFID_BEGIN				= 2000,					//协议中RFID报警类型放在AE_ALARM_TYPE_BEGIN和AE_ALARM_TYPE_END定义之间，但RFID报警类型为RFID设备的报警，不是PE设备的报警，因此将RFID报警类型独立出来
	ALARM_TYPE_RFID_BATTERY_EMPTY		= 2010,					//射频设备低电量报警
	ALARM_TYPE_RFID_BUTTON				= 2011,					//射频设备按键报警
	ALARM_TYPE_RFID_DATA_EXCEPTION		= 2012,					//射频设备数据异常报警
	ALARM_TYPE_RFID_ENTER_RECEIVER		= 2013,					//射频设备接收器感应到手环报警
	ALARM_RFID_ILLEGAL_ENTER			= 2014,					//非法进入
	ALARM_RFID_ILLEGAL_LEAVE			= 2015,					//非法离开
	ALARM_RFID_ILLEGAL_GATHER			= 2016,					//非法聚集
	ALARM_RFID_WITHOUT_TUTELAGE			= 2017,					//无监护报警
	ALARM_RFID_STAY						= 2018,					//滞留报警
	ALARM_RFID_EXCEPTION				= 2019,					//异常报警
	ALARM_RFID_CUTOFF_LABEL				= 2021,					//人员标签剪断
	ALARM_RFID_GPS						= 2022,					//射频设备GPS上报
	ALARM_RFID_APPROACH					= 2024,					//接近边界管理器
	ALARM_RFID_LEAVEAWAY				= 2025,					//远离边界管理器
	ALARM_RFID_OFFLINE					= 2026,					//离线超时报警
	ALARM_RFID_SingleInterrogation      = 2027,                 //单人审讯报警
	ALARM_RFID_WaitingRoomTimeOut       = 2028,                 //候问室超时报警
	ALARM_RFID_Unattended				= 2029,                 //无人看管
	ALARM_RFID_InterrogationTimeout     = 2030,                 //审讯超时
	ALARM_RFID_Broken					= 2031,					//断开报警
	ALARM_RFID_HeartBeat				= 2032,					//心率信息
	ALARM_RFID_HeartBeatException		= 2033,					//心率异常报警
	ALARM_RFID_VEHICLE_NOT_ARRIVE_TIMEOUT	= 2035,				//车辆超时未达报警
	ALARM_RFID_NEAR_DISTANCE_DETECTION      = 2036,             //近距离接触定位报警
	ALARM_RFID_RIOTERDETECTION              = 2037,             //人员聚集定位报警
	ALARM_RFID_CO_CASE_CONTACTS				= 2038,				//同案接触定位报警
	ALARM_RFID_ILLEGAL_ENTRY				= 2039,				//非法闯禁
	ALARM_RFID_ILLEGAL_DEPART				= 2040,				//非法离开
	ALARM_RFID_ILLEGAL_DUTY_PERSON_LEAVE	= 2041,				//值班人员离岗
	ALARM_RFID_REVERSE					= 2100,					//逆向报警
	ALARM_RFID_InterrogationBegin       = 2101,                 //开始审讯
	ALARM_RFID_InterrogationEnd         = 2102,                 //结束审讯
	ALARM_TYPE_RFID_END,										

	AE_ALARM_TYPE_BEGIN,
	ALARM_DOOR_MAGNETISM				= 2200,					// 门磁
	ALARM_PASSIVE_INFRARED				= 2201,					// 被动红外
	ALARM_GAS							= 2202,					// 气感
	ALARM_INITIATIVE_INFRARED			= 2203,					// 主动红外
	ALARM_GLASS_CRASH					= 2204,					// 玻璃破碎
	ALARM_EXIGENCY_SWITCH				= 2205,					// 紧急开关
	ALARM_SHAKE							= 2206,					// 震动
	ALARM_BOTH_JUDGE					= 2207,					// 双鉴（红外+微波）
	ALARM_THREE_TECHNIC					= 2208,					// 三技术
	ALARM_CALL_BUTTON					= 2209,      			// 呼叫按钮
	ALARM_SENSE_OTHER					= 2210,	    			// 其他
	//模拟室内机报警类型
	ALARM_SENSE_OTHER_ANALOG			= 2211,					// 模拟室内机报警类型“其他”
	AE_ALARM_TYPE_END					= 2400,

	ALARM_ID_CARD_COMPARE_OK			= 2401,					//人证对比成功结果上报
	ALARM_ID_CARD_COMPARE_FAILED		= 2402,					//人证对比失败结果上报
	ALARM_IVSS_STRANGER_ALARM			= 2403,					//IVSS陌生人报警事件（不同于陌生人脸报警）
	ALARM_VTO_QRCODE_CHECK				= 2404,					//二维码上报事件
	ALARM_FACE_BLACK_LIST				= 2405,					//人脸黑名单报警
	ALARM_IVSS_VIP_ALARM				= 2406,					//招行项目-VIP客户报警

	//begin震动光纤报警类型
	ALARM_TYPE_VIBRATIONFIBER_BEGIN     = 2601,					// 震动光纤1
	ALARM_VIBRATIONFIBER_SNLALARM,                              // 开关量报警 
	ALARM_VIBRATIONFIBER_BOXALARM,                              // 开关盒报警 
	ALARM_VIBRATIONFIBER_INVALIDZONE,                           // 防区失效1106 
	ALARM_VIBRATIONFIBER_SIGNAL_OFF,                            // 光纤信号源停止 
	ALARM_VIBRATIONFIBER_FIBRE_BREAK,                           // 光纤断开
	ALARM_TYPE_VIBRATIONFIBER_END		= 2700,					// 震动光纤5
	//end
	//巡更报警
	ALARM_PATROL_BEGIN					 = 2701,
	ALARM_PATROL_EXCEPTION				 = 2702,				// 巡更异常报警
	ALARM_PATROL_ROUTINE_REQUEST		 = 2703,				// 请求路线报警,巡更轨迹通知，GPS通知
	ALARM_PATROL_LOCATION_REQUEST		 = 2704,				// 请求定位报警
	ALARM_PATROL_PROMPTING				 = 2705,				// 巡更提醒
	ALARM_PATROL_ROUTE_RESULT_NTF		 = 2706,				// 线路巡更结果通知
	ALARM_PATROL_ROUTE_PROMPTING		 = 2707,				// 线路巡更提醒
	ALARM_PATROL_REMIND_START_TASK		 = 2708,				// 巡更任务开始前提醒
	ALARM_PATROL_REMIND_END_TASK		 = 2709,				// 巡更任务结束前提醒
	ALARM_PATROL_END					 = 2800,
	// -F预留报警类型，自定义报警
	ALARM_TYPE_USERDEFINE_BEGIN			 = 3101,
	ALARM_TYPE_USERDEFINE_END			 = 3130,

	// 报警运营平台，扩展自定义报警类型
	ALARM_TYPE_USERDEFINEEX_BEGIN		 = 3201,
	ALARM_TYPE_USERDEFINEEX_END			 = 4200,

	ALARM_NODE_ACTIVE					= 4201,					// 主从切换报警
	ALARM_ISCSI_STATUS					= 4202,					// ISCSI存储状态变更报警
	ALARM_OUTDOOR_STATIC				= 4203,

	ALARM_FALLING						= 4204,					// 跌落事件报警 
	ALARM_ITC_OUTSIDE_CARNUM			= 4205,					// 出入口外部车报警
	ALARM_POS_TRANING_MODE				= 4206,					//POS机训练模式报警
	ALARM_REFUND_OVER_QUOTA				= 4207,					//退货限额报警
	ALARM_SWING_CARD_FREQUENTLY			= 4208,					//会员卡频繁出现报警
	ALARM_SIGNLE_COST_OVER_QUOTA		= 4209,					//销售单笔超额报警

	ALARM_BREAK_ONDUTY					= 4216,					//值班违章（室内违章改成值班违章)

	//DSS-H可视对讲设备室内机新增传感器报警类型
	ALARM_SENSE_BEGIN					= 4299,
	ALARM_SENSE_DOOR                    = 4300,                 //门磁
	ALARM_SENSE_PASSIVEINFRA            = 4301,                 //被动红外
	ALARM_SENSE_GAS                     = 4302,                 //气感
	ALARM_SENSE_SMOKING                 = 4303,                 //烟感
	ALARM_SENSE_WATER                   = 4304,                 //水感
	ALARM_SENSE_ACTIVEFRA               = 4305,                 //主动红外
	ALARM_SENSE_GLASS                   = 4306,                 //玻璃破碎
	ALARM_SENSE_EMERGENCYSWITCH         = 4307,                 //紧急开关
	ALARM_SENSE_SHOCK                   = 4308,                 //震动
	ALARM_SENSE_DOUBLEMETHOD            = 4309,                 //双鉴(红外+微波)
	ALARM_SENSE_THREEMETHOD             = 4310,                 //三技术
	ALARM_SENSE_TEMP                    = 4311,                 //温度
	ALARM_SENSE_HUMIDITY                = 4312,                 //湿度
	ALARM_SENSE_WIND                    = 4313,                 //风速
	ALARM_SENSE_CALLBUTTON              = 4314,                 //呼叫按钮
	ALARM_SENSE_GASPRESSURE             = 4315,                 //气体压力
	ALARM_SENSE_GASCONCENTRATION        = 4316,                 //燃气浓度
	ALARM_SENSE_GASFLOW                 = 4317,                 //气体流量
	ALARM_SENSE_OIL                     = 4319,                 //油量检测，汽油、柴油等车辆用油检测
	ALARM_SENSE_MILEAGE                 = 4320,                 //里程数检测
	ALARM_SENSE_URGENCYBUTTON           = 4321,                 //紧急按钮
	ALARM_SENSE_STEAL                   = 4322,                 //盗窃
	ALARM_SENSE_PERIMETER               = 4323,                 //周界
	ALARM_SENSE_PREVENTREMOVE           = 4324,                 //防拆
	ALARM_SENSE_DOORBELL                = 4325,                 //门铃
	ALARM_SENSE_LOCK_LOCKKEY            = 4326,                 //门锁钥匙报警
	ALARM_SENSE_LOCK_LOWPOWER           = 4327,                 //门锁低电压报警
	ALARM_SENSE_LOCK_PREVENTREMOVE      = 4328,                 //门锁防拆
	ALARM_SENSE_LOCK_FORCE		        = 4329,                 //门锁胁迫报警
	ALARM_SENSE_LOCK_OFFLINE			= 4330,					//门锁离线报警
	ALARM_SENSE_FIRE					= 4331,					//火警
	ALARM_SENSE_END						= 4399,

	ALARM_STORAGE_BEGIN					= 4400,
	ALARM_IO_QUEUE_FULL					= 4401,					// 磁盘读写高负荷
	ALARM_DISK_DESTROY					= 4402,					// 磁盘异常
	ALARM_IPSAN_OFF_LINE				= 4403,					// IPSan掉线
	ALARM_NO_DISK_STORAGE				= 4404,					// 没有磁盘			
	ALARM_GET_STREAM_ERROR				= 4405,					// 取码流错误
	ALARM_DISK_NEAR_FULL				= 4406,					// 磁盘接近满
	ALARM_STORAGE_END					= 4499,

	//DSSH出入口卡口黑名单报警类型新增
	ALARM_TRAFFIC_SUSPICIOUSCAR         = 4501,

	//大华出入口控制机报警类型
	ALARM_SLUICE_BEGIN								= 4502,
	ALARM_SLUICE_IC_CARD_STATUS_LOWCARD				= 4503,					//卡箱少卡报警
	ALARM_SLUICE_IC_CARD_STATUS_NOCARD				= 4504,					//卡箱无卡报警
	ALARM_SLUICE_IC_CARD_STATUS_FULLCARDS			= 4505,					//卡箱卡满报警
	ALARM_SLUICE_CAR_DETECTOR_STATE_OFFLINE			= 4506,					//车检器掉线报警
	ALARM_SLUICE_CAR_DETECTOR_STATE_LOOPOFFLINE		= 4507,					//地感线圈掉线报警
	ALARM_SLUICE_LED_DEV_STATE_OFFLINE				= 4508,					//LED掉线报警
	ALARM_SLUICE_SWIPING_CARD_DEV_STATE_OFFLINE		= 4509,					//面板刷卡板掉线报警
	ALARM_SLUICE_DELIVE_CARD_DEV_OFFLINE			= 4510,					//发卡刷卡板掉线报警
	ALARM_SLUICE_SPEAK_DEV_STATUS					= 4511,					//对讲事件报警
	ALARM_SLUICE_END								= 4550,

	//DSSH自助缴费机报警类型
	ALARM_SELFPAY_BEGIN								= 4551,
	ALARM_SELFPAY_NOPAPER							= 4552,//缺纸
	ALARM_SELFPAY_NOCASH50							= 4553,
	ALARM_SELFPAY_NOCASH20							= 4554,
	ALARM_SELFPAY_NOCASH10							= 4555,
	ALARM_SELFPAY_NOCASH1							= 4556,
	ALARM_SELFPAY_NOCOIN							= 4557,
	ALARM_SELFPAY_LOCKMONEY							= 4558,//卡币
	ALARM_SELFPAY_DISMANTLE							= 4559,//防拆
	ALARM_SELFPAY_UNPACK							= 4560,//开箱
	ALARM_SELFPAY_UNKONWN							= 4561,//纸币不识别
	ALARM_SELFPAY_CASHBOXOTHER						= 4562,					//钱箱识别器其他错误
	ALARM_SELFPAY_PRINTERERR						= 4563,					//热敏打印机械故障
	ALARM_SELFPAY_RECOGNITIONSELFCHECKERR			= 4564,					//硬币识别器自检错误
	ALARM_SELFPAY_RECOGNITIONPOLLONLINE				= 4565,					//硬币识别器轮询在线
	ALARM_SELFPAY_CHANGEONLINE						= 4566,					//硬币找零器是否在线
	ALARM_SELFPAY_END								= 4580,
	ALARM_ITC_BLACKLIST_CARNUM						= 4581,					//PES停车场模块黑名单车辆
	ALARM_ITC_RESERVE_OCCUPY						= 4582,					//停车场手机预定车位被占用

	//门禁设备扩展报警
	ALARM_DOOREX_BEGIN								= 4600,
	ALARM_VALID_CARD_OR_FINGERPRINT_OR_FACE			= 4601,				//卡或指纹或人脸合法开门
	ALARM_INVALID_CARD_OR_FINGERPRINT_OR_FACE		= 4602,				//卡或指纹或人脸非法开门
	ALARM_VALID_CARD_AND_FINGERPRINT_AND_FACE_AND_PWD		= 4603,		//卡+指纹+人脸+密码组合合法开门
	ALARM_INVALID_CARD_AND_FINGERPRINT_AND_FACE_AND_PWD	 	= 4604,		//卡+指纹+人脸+密码组合非法开门
	ALARM_VALID_CARD_OR_FINGERPRINT_OR_FACE_OR_PWD	= 4605,				//卡或指纹或人脸或密码合法开门
	ALARM_INVALID_CARD_OR_FINGERPRINT_OR_FACE_OR_PWD	= 4606,			//卡或指纹或人脸或密码非法开门
	ALARM_VALID_FACEIPCARDANDIDCARD_OR_CARD_OR_FACE		= 4607,			//(身份证+人证比对)或 刷卡 或 人脸合法开门
	ALARM_INVALID_FACEIPCARDANDIDCARD_OR_CARD_OR_FACE	= 4608,			//(身份证+人证比对)或 刷卡 或 人脸非法开门
	ALARM_VALID_FACEIDCARD_OR_CARD_OR_FACE			= 4609,				//人证比对 或 刷卡(二维码) 或 人脸合法开门
	ALARM_INVALID_FACEIDCARD_OR_CARD_OR_FACE		= 4610,				//人证比对 或 刷卡(二维码) 或 人脸非法开门
	ALARM_VALID_REMOTE_QRCODE						= 4611,				//远程二维码合法开门
	ALARM_INVALID_REMOTE_QRCODE						= 4612,				//远程二维码非法开门
	ALARM_VALID_REMOTE_FACE							= 4613,				//远程人脸合法开门
	ALARM_INVALID_REMOTE_FACE						= 4614,				//远程人脸非法开门
	ALARM_VALID_CITIZEN_FINGERPRINT					= 4615,				//人证比对(指纹)合法开门
	ALARM_INVALID_CITIZEN_FINGERPRINT				= 4616,				//人证比对(指纹)非法开门
	ALARM_RFID_PET_ABNORMAL_THROUGH					= 4617,				//宠物异常通行
	ALARM_RFID_ELECTROMBILE_UNIT_ENTER				= 4618,				//电动车进出单元报警
	ALARM_RFID_ELECTROMBILE_AREA_FORBID				= 4619,				//电动车区域禁停报警
	ALARM_RFID_ABNORMAL_IN_AND_OUT					= 4620,				//人员异常出入预警
	ALARM_VALID_PWD_FIRST							= 4621,				//先密码后刷卡合法开门
	ALARM_INVALID_PWD_FIRST							= 4622,				//先密码后刷卡非法开门
	ALARM_DOOROPEN_MALICE							= 4623,				//恶意开门事件
	ALARM_RFID_NOT_IN_AND_OUT						= 4624,				//人员未出入预警
	ALARM_ACTIVE_LOW_POWER							= 4625,				//有源RFID低电量报警
	ALARM_VALID_HELMET_OPEN_DOOR					= 4626,				//人脸安全帽合法开门
	ALARM_INVALID_HELMET_OPEN_DOOR					= 4627,				//人脸安全帽非法开门
	ALARM_DISCONN_TIMEOUT							= 4628,				//离线超时报警
	ALARM_TYPE_FREEZE								= 4629,				//冻结卡刷卡事件
	ALARM_DOOROPEN_OVERTEMP							= 4630,				//闸机开门人员超高温事件
	ALARM_TYPE_SELTTEST								= 4698,				//设备自检状态
	ALARM_DOOREX_END								= 4699,

	//客户端IP对讲报警
	ALARM_IP_DEV_BEGIN								= 4700,
	ALARM_IP_DEV_CALLIN								= 4701,		//分机呼叫
	ALARM_IP_DEV_CALLOUT							= 4702,		//拨打
	ALARM_IP_DEV_ANSWER								= 4703,		//接听
	ALARM_IP_DEV_EmergencyButton					= 4704,		//紧急按钮报警
	ALARM_IP_DEV_END								= 4800,
	
	//手机APP报警类型
	ALARM_MOBILEAPP_BEGIN							= 4900,
	ALARM_MOBILEAPP_GPS								= 4901,		//手机APP上传GPS
	ALARM_MOBILEAPP_ONE_CLICK						= 4902,		//手机APP一键报警
	ALARM_MOBILEAPP_MANUAL_ADD						= 4903,		//手机APP手动添加报警
	ALARM_MOBILEAPP_END								= 5000,

	//场景报警开始
	ALARM_SCENE_BEGIN								= 5001,
	ALARM_PEOPLE_UPPER_LIMIT						= 5002,		//人数上限
	ALARM_PEOPLE_LOWER_LIMIT						= 5003,		//人数下限
	ALARM_INFLUX_UPPER_LIMIT						= 5004,		//人流量超标（进）
	ALARM_OUTFLUX_UPPER_LIMIT						= 5005,		//人流量超标（出）
	ALARM_DENSITY_UPPER_LIMIT						= 5006,		//密度报警
	ALARM_SCENE_EXCEPTION							= 5007,		//场景异常报警
	ALARM_EXCEPTION_STAY							= 5008,		//异常滞留
	ALARM_SCENE_END									= 5100,
	//场景报警结束

	ALARM_THIRD_ACCESS  							= 5101,      //第三方接入设备报警
	ALARM_PC_REPORT									= 5102,		 //智能设备上报人数统计报警
	ALARM_THREE_IN_ONE								= 5103,		 //三台合一报警
	ALARM_HUMAM_NUMBER_STATISTIC					= 5104,		 //人流量统计相机客流量超过阀值报警事件
	ALARM_PERSON_COUNT_REPORT                       = 5105,      //人流量统计（以报警方式上报人流量统计信息）
	ALARM_MAN_NUM_DETECTION                         = 5106,      //立体视觉区域内人数统计报警

	// 热成像报警
	ALARM_RADIOMETRY_HEATIMG_TEMPER					= 5120,          //热成像测温点温度异常报警
	ALARM_RADIOMETRY_FIRE_WARNING					= 5121,          //热成像着火点报警
	ALARM_RADIOMETRY_FIREWARNING_INFO         		= 5122,          //热成像火情报警信息上报
	ALARM_RADIOMETRY_HOTSPOT_WARNING           		= 5123,          //热成像热点异常报警（高于温度阀值报警）
	ALARM_RADIOMETRY_COLDSPOT_WARNING          		= 5124,          //热成像冷点异常报警（低于温度阀值报警）
	ALARM_RADIOMETRY_BETWEENRULE_TEMP_DIFF			= 5125,          //热成像规则间温差异常报警
	ALARM_RADIOMETRY_SMOKE_DETECTION         		= 5126,          //热成像烟雾报警
	ALARM_RADIOMETRY_FACE_OVERHEATING           	= 5127,          //热成像人体发烧预警
	ALARM_RADIOMETRY_MAN_OVERHEATING                = 5128,          //人体高温报警
	ALARM_RADIOMETRY_MAN_LOWERHEATING               = 5129,          //人体低温报警
	ALARM_RADIOMETRY_MAN_BLACKHEATING               = 5130,          //黑体异常报警

	// 常州武进公安车载
	ALARM_SIM_CARD_FLUX_REPORT						= 5140,			// 车载MDVR上月历史流量报警

	// 海南福山油田
	ALARM_OIL_4G_OVERFLOW							= 5160,			// 4G流量超额报警

	// 长春地铁报警
	ALARM_SUB_WAY_DOOR_STATE 						= 5170,			// 地铁车厢门报警
	ALARM_SUB_WAY_PECE_SWITCH						= 5171,			// 地铁PECE柜门报警
	ALARM_SUB_WAY_FIRE_ALARM						= 5172,			// 地铁火警报警
	ALARM_SUB_WAY_EMER_HANDLE						= 5173,			// 地铁乘客紧急手柄动作报警
	ALARM_SUB_WAY_CAB_COVER							= 5174,			// 地铁司机室盖板报警
	ALARM_SUB_WAY_DERA_OBST							= 5175,			// 地铁检测到障碍物或脱轨报警
	ALARM_SUB_WAY_PECU_CALL							= 5176,			// 地铁客室报警器报警

	//客户端机顶盒设备定制报警
	ALARM_STB_BEGIN									= 5200,		
	ALARM_STB_FIRE									= 5201,		//火警
	ALARM_STB_CRIME									= 5202,		//匪警
	ALARM_STB_EMERGENCY								= 5203,		//急救中心
	ALARM_STB_OTHER									= 5204,		//其他报警
	ALARM_STB_END									= 5250,

	//-C/-P新增报警预留
	ALARM_DSSC_BEGIN										= 5300,
	ALARM_PATIENTDETECTION_TYPE_CROSS_REGION				= ALARM_DSSC_BEGIN + 1,	// 警戒区域报警，可能是病人离开或者有其他靠近病人
	ALARM_PATIENTDETECTION_TYPE_LIGHT_OFF					= ALARM_DSSC_BEGIN + 2,	// 病房电灯被熄灭
	ALARM_PATIENTDETECTION_TYPE_STOP_DETECTION				= ALARM_DSSC_BEGIN + 3,	// 撤防，不再监控病人
	ALARM_PATIENTDETECTION_TYPE_START_DETECTION				= ALARM_DSSC_BEGIN + 4,	// 开始布防
	ALARM_PATIENTDETECTION_TYPE_ESCAPE						= ALARM_DSSC_BEGIN + 5,	// 病人在押解过程中逃跑
	ALARM_PATIENTDETECTION_TYPE_SMOKE						= ALARM_DSSC_BEGIN + 6,	// 烟感报警
	ALARM_DSSC_END											= 5400,

	//VTA报警柱报警
	ALARM_U700_BEGIN										= 5401,
	ALARM_VTA_INSPECTION									= ALARM_U700_BEGIN + 1, // VTA报警柱巡检报警
	ALARM_VTA_OVERSPEED										= ALARM_U700_BEGIN + 2, // VTA报警柱超速报警
	ALARM_VTA_INSPECTION_SWING_CARD							= ALARM_U700_BEGIN + 3, //VTA巡检刷卡
	ALARM_VTA_PATROL_SWING_CARD								= ALARM_U700_BEGIN + 4, //VTA巡更刷卡
	ALARM_EXTERNAL_IVS										= ALARM_U700_BEGIN + 5,	// 外部智能报警
	ALARM_U700_END											= 5500,

	ALARM_REMOTE_CAMERA_STATE								= 5501,				//卡口设备相机状态上报报警

	ALARM_SHANGHAI_JIHENG									= 5502,				//上海迹恒上报报警
	ALARM_PATROL_REMIND										= 5503,				//巡更提醒报警
	ALARM_VTO_ACCESSIDENTIFY								= 5504,				//门口机人脸认证
	ALARM_CAR_SURVEY										= 5505,				//卡口布控报警
	ALARM_CHANNEL_TALK										= 5506,				//通道对讲报警
	ALARM_HEARTRATE_DETECT									= 5507,				//心率侦测
	//人行道闸报警定义 5640- 5680
	ALARM_ROADGATE_BEGIN									= 5640,

	ALARM_ROADGATE_VALID_PASSWORD_OPENDOOR					= 5642,
	ALARM_ROADGATE_INVALID_PASSWORD_OPENDOOR				= 5643,
	ALARM_ROADGATE_REMOTE_OPENDOOR							= 5648,
	ALARM_ROADGATE_VALID_CARD_OPENDOOR						= 5651,
	ALARM_ROADGATE_INVALID_CARD_OPENDOOR					= 5652,
	ALARM_ROADGATE_NORMAL_CLOSED							= 5656,
	ALARM_ROADGATE_OPEN										= 5657,
	ALARM_ROADGATE_OPEN_TIME_OUT_BEG						= 5660,
	ALARM_ROADGATE_OPEN_TIME_OUT_END						= 5670,

	ALARM_ROADGATE_END										= 5680,

	//-P 行业线 对接海康设备增加报警
	ALARM_AUDIO_ABNORMALDETECTION							= 5700,		
	ALARM_CLIMB_UP_DETECTION								= 5701,
	ALARM_CROSSRE_DETECTION									= 5702,
	ALARM_FIGHT_DETECTION									= 5703,
	//倍特卫视分析设备
	ALARM_RAISE_UP_DETECTION								= 5705,
	ALARM_WC_TIMEOUT_DETECTION								= 5706,
	ALARM_DUTY_DETECTION									= 5707,
	ALARM_OUTSIDE_STRANDED_DETECTION						= 5708,
	// 科大讯飞语音报警
	ALARM_KVOICE_ALARM										= 5709,

	//老动环报警扩展定义报警区间段
	ALARM_SCS_EXT_BEGIN										= 6000,
	ALARM_SCS_EXT_NOISE_INTENSITY							= 6001,						//噪声告警
	ALARM_SCS_EXT_END										= 6999,

	//雷达信息报警区间
	AlARM_RADAR_BEGIN										= 7000,
	AlARM_RADAR_TARGETINFO									= 7001,		// 雷达上传目标信息
	AlARM_RADAR_ALARM										= 7002,		// 雷达报警上传
	AlARM_RADAR_END											= 7100,

	//新动环报警定义报警区间段
	ALARM_NEW_SCS_BEGIN										= 8000,
	ALARM_NEW_SCS_END										= 9999,

	//平台业务报警区间段
	ALARM_BUSINESS_BEGIN									= 10001,
	ALARM_BUSINESS_POLICE_PATROL							= 10002,			//民警巡视业务报警	
	ALARM_BUSINESS_WAITING_ROOM_UNATTENDED					= 10003,			//候问室无人看管
	ALARM_BUSINESS_WASHROOM_UNATTENDED						= 10004,			//卫生间无人跟随
	ALARM_BUSINESS_MAN_NUM_DETECTION						= 10005,			//审讯室人数报警
	ALARM_BUSINESS_END										= 10500,

	ALARM_VEHICLE_SURVEY_EW									= 10501,			//车辆布控预警报警
	ALARM_FACE_EW											= 10502,			//人脸预警报警
	ALARM_VEHICLE_SCORE_EW									= 10503,			//车辆积分预警报警

	//CMS平台报警
	ALARM_DISTRIBUTE_SWITCHOVER								= 10600,			//N+M备份切换报警

	ALARM_HBSZZ_APP_BUTTON									= 10601,			//河北省综治项目APP一键报警
	ALARM_WIDE_VIEW_REGION_ALARM							= 10602,			// 全景区域报警，浙江二监定制
	ALARM_HIGH_DECIBEL										= 10603,			// 声音高分贝检测报警
	ALARM_SHAKE_DETECTION									= 10604,			// 摇晃检测报警
	ALARM_BATTERY_LOW_POWER									= 10605,			// 电池电量低报警

	//PTS新增报警
	ALARM_PTS_BEGIN											= 11000,
	//布控报警 begin
	ALARM_FORTIFY_OVERSPEED									= 11001,	// 布控超速车辆
	ALARM_FORTIFY_STOLEN									= 11002,	// 布控盗抢车辆
	ALARM_FORTIFY_ACCIDENT									= 11003,	// 布控肇事车辆
	ALARM_FORTIFY_SUSPICE									= 11004,	// 布控嫌疑车辆
	ALARM_FORTIFY_HEADOFF									= 11005,	// 布控拦截车辆
	ALARM_FORTIFY_CHECKED									= 11006,	// 布控检查盘查
	ALARM_FORTIFY_FOLLOWED									= 11007,	// 布控观察跟踪
	ALARM_FORTIFY_DANGER									= 11008,	// 布控高危车辆
	ALARM_FORTIFY_STRANDING									= 11009,	// 布控滞留车辆
	ALARM_FORTIFY_SPECIALEXCEPTION							= 11010,	// 特殊异常车辆
	ALARM_FORTIFY_EXHAUST									= 11011,	// 布控黄标车
	ALARM_FORTIFY_WHITELIST									= 11012,	// 布控白名单
	ALARM_FORTIFY_BLACKLIST									= 11013,	// 布控黑名单
	ALARM_FORTIFY_LASTNUMBER								= 11014,	// 布控尾号限行
	ALARM_FORTIFY_GRIDLINE									= 11015,	// 网格布控（车辆经过网内任意两个卡点）
	ALARM_FORTIFY_TIMEOUT									= 11016,	// 布控滞留超时车辆
	ALARM_FORTIFY_ILLEGALTIMEPASS							= 11017,	// 布控在白名单内，非法时间段通过车辆(暂定上海浦东垃圾场定制)
	ALARM_FORTIFY_NOTINWHITELIST							= 11018,	// 布控未在白名单内车辆(暂定上海浦东垃圾场定制)
	ALARM_FORTIFY_RECOGNISEFAIL								= 11019,	// 布控车牌无法识别车辆(暂定上海浦东垃圾场定制)
	//布控报警 end

	ALARM_NO_DRIVERROAD										= 11101,	//非机动车道
	ALARM_OFFEND_INTERDICTORYSIGN							= 11102,	//机动车违反禁令标志指示	
	ALARM_COVERING_PLATE									= 11103,	//遮挡号牌
	ALARM_ROUND_ITS											= 11104,	//绕行卡口
	ALARM_RESTRICT_DRIVING									= 11105,	//限行
	ALARM_PEDESTRAIN_PRIORITY								= 11106,	//斑马线行人优先
	ALARM_MNVR_PEC											= 11107,	//车辆黑名单事件
	ALARM_COMPARE_PLATE										= 11108,	//车牌前后对比	
	ALARM_TRAFFIC_CARWEIGHT									= 11109,	//超重
	ALARM_TRANSFINITE_PECCANCY								= 11110,	//超限违章
	ALARM_CHASSIS_CHECK										= 11111,	//底盘检查			
	ALARM_PREILLEGALLY_PARKED								= 11112,	//预违停
	ALARM_CAR_DETECTOR_FAULT								= 11113,	//线圈/车检器故障报警
	ALARM_REMOTE_HOST										= 11114,	//远程主机报警
	ALARM_TRAFFICLIGHTS_FAULT								= 11115,	//灯绿灯
	ALARM_TRAFFIC_INTERRUPT									= 11116,	//交通中断
	ALARM_DATABASE_FAULT									= 11117,	//数据库错误
	ALARM_PTS_END											= 11500,

	// 微云报警
	ALARM_MCS_GENERAL_CAPACITY_LOW							= 11600,// 微云常规容量事件
	ALARM_MCS_DATA_NODE_OFFLINE								= 11601,// 微云存储节点下线事件
	ALARM_MCS_DISK_OFFLINE									= 11602,// 微云磁盘下线事件
	ALARM_MCS_DISK_SLOW										= 11603,// 微云磁盘变慢事件
	ALARM_MCS_DISK_BROKEN									= 11604,// 微云磁盘损坏事件
	ALARM_MCS_DISK_UNKNOW_ERROR								= 11605,// 微云磁盘未知错误事件
	ALARM_MCS_METADATA_SERVER_ABNORMAL						= 11606,// 微云元数据服务器异常事件
	ALARM_MCS_CATALOG_SERVER_ABNORMAL						= 11607,// 微云目录服务器异常事件
	ALARM_MCS_GENERAL_CAPACITY_RESUME						= 11608,// 微云常规容量恢复事件
	ALARM_MCS_DATA_NODE_ONLINE								= 11609,// 微云存储节点上线事件
	ALARM_MCS_DISK_ONLINE									= 11610,// 微云磁盘上线事件
	ALARM_MCS_METADATA_SLAVE_ONLINE							= 11611,// 微云元数据备机上线事件
	ALARM_MCS_CATALOG_SERVER_ONLINE							= 11612,// 微云目录服务器上线事件

	ALARM_VITAL_SIGNS_ABNORMAL								= 11700,// 生命体征异常报警		

	//新增围栏报警 占用范围：12000-12200
	ALARM_DRIVERIN_FLYAREA									= 12000,// 驶入飞行区
	ALARM_DRIVEROUT_FLYAREA,									    // 驶出飞行区
	ALARM_DRIVERIN_MANUALBANFLYAREA,                                // 驶入禁飞区（手动配置）
	ALARM_DRIVEROUT_MANUALBANFLYAREA,                               // 驶出禁飞区（手动配置）
	ALARM_DRIVERIN_FIXEDBANFLYAREA,                                 // 驶入禁飞区（不可配置）
	ALARM_DRIVEROUT_FIXEDBANFLYAREA,                                // 驶出禁飞区（不可配置）
	ALARM_DRIVERIN_FiXEDLIMITFLY,                                   // 驶入限制飞行（不可配置）
	ALARM_DRIVEROUT_FiXEDLIMITFLY,                                  // 驶出限制飞行（不可配置）

	ALARM_ILLEGALIN_FLYAREA,					                    // 非法进入飞行区报警
	ALARM_ILLEGALOUT_FLYAREA,					                    // 非法驶出飞行区报警
	ALARM_ILLEGALIN_MANUALBANFLYAREA,					            // 非法进入禁飞区（手动配置）
	ALARM_ILLEGALOUT_MANUALBANFLYAREA,					            // 非法驶出禁飞区（手动配置）
	ALARM_ILLEGALIN_FIXEDBANFLYAREA,					            // 非法进入禁飞区（不可配置）
	ALARM_ILLEGALOUT_FIXEDBANFLYAREA,					            // 非法驶出禁飞区（不可配置）
	ALARM_ILLEGALIN_FiXEDLIMITFLY, 					                // 非法进入限制飞行
	ALARM_ILLEGALOUT_FiXEDLIMITFLY							= 12015,// 非法出驶出限制飞行

	//新增消防主机报警 占用范围：12300-12400
	ALARM_FIREENGINE_BEGIN				   = 12300,
	ALARM_FIREENGINE_FIRE,                                     		//火警报警
	ALARM_FIREENGINE_EQUIPMENT_FAILURE,                        		//设备故障报警
	ALARM_FIREENGINE_HOST_FAILURE,                         			//主电故障
	ALARM_FIREENGINE_BACKUP_FAILURE,                          		//备电故障
	ALARM_FIREENGINE_HOST_UNDERVOLTAGE,								//主电欠压
	ALARM_FIREENGINE_BACKUP_UNDERVOLTAGE,							//备电欠压
	ALARM_FIREENGINE_BUS_FAILURE,                            		//总线故障
	ALARM_FIREENGINE_HOST_OFFLINE,                          		//主机离线
	ALARM_FIREENGINE_MANUAL,                          				//手动报警
	ALARM_FIREENGINE_TEMPERATUAL,                            		//温度报警
	ALARM_FIREENGINE_LOW_WATERPRESSURE,								//水压过低
	ALARM_FIREENGINE_HIGH_WATERPRESSURE,							//水压过高
	ALARM_FIREENGINE_DETECTOR_FAULT,								//探测器故障

	ALARM_FIREENGINE_END				   = 12400,

	//新增消控报警 占用范围：12401-12500
	ALARM_FIRECONTROL_BEGIN								= 12401,
	ALARM_FIRECONTROL_NOBODY							= 12402,             //无人报警
	ALARM_FIRECONTROL_UPPER_LIMIT						= 12403,             //超过上限报警
	ALARM_FIRECONTROL_LOWER_LIMIT						= 12404,             //少于下限报警
	ALARM_FIRECONTROL_NOT_MATCH							= 12405,             //计划不符报警	
	ALARM_FIRECONTROL_END								= 12500, 

	ALARM_TYRE_PRESSURE_ABNORMAL						= 13000,				 //胎压异常
	ALARM_RETROGRADATION_DETECT							= 13003,              //逆行检测
	ALARM_TARGET_REMOVE_DETECT							= 13004,              //目标移除检测
	ALARM_GPS_MODULE_LOST			   					= 13005,				 //GPS异常
	ALARM_WIFI_MODULE_LOST			   					= 13006,				 //WIFI异常
	ALARM_3G4G_MODULE_LOST			   					= 13007,				 //3G/4G异常
	ALARM_POLICE_CHECK			   	   					= 13008,				 //单兵设备警员签到报警
	ALARM_WIFI_MODULE_OFFLINE							= 13009,				 //WIFI模块离线
	ALARM_CHASSIS_INTRUSION								= 13010,				 //报警柱防拆报警
	ALARM_WIFI_MODULE_ONLINE							= 13011,				 //WIFI模块在线



	//海外门禁报警新增:13100-13500
	ALARM_DOOR_UNAUTHORIZE								=13100,				//未授权(无效刷卡)
	ALARM_DOOR_LOST										=13101,               //卡挂失或注销(无效刷卡)
	ALARM_DOOR_NO_PERMISSION							=13102,               //没有该门权限(无效刷卡)	
	ALARM_DOOR_ERR_MODE               					=13103,               //开门模式错误(无效刷卡)
	ALARM_DOOR_ERR_VALIDITY								=13104,               //有效期错误(无效刷卡)
	ALARM_DOOR_ERR_REPEATENTERROUTE						=13105,               //防反潜模式(无效刷卡)
	ALARM_DOOR_FORCE_NOTOPEN							=13106,               //胁迫报警未打开(无效刷卡)
	ALARM_DOOR_ALWAYS_CLOSED							=13107,               //门常闭状态(无效刷卡)
	ALARM_DOOR_AB_CLOKED               					=13108,               //AB互锁状态(无效刷卡)
	ALARM_DOOR_PATROL_CARD								=13109,               //巡逻卡(无效刷卡)
	ALARM_DOOR_IN_BROKEN               					=13110,               //设备处于闯入报警状态(无效刷卡)
	ALARM_DOOR_ERR_TIMESECTION							=13111,               //时间段错误(无效刷卡)
	ALARM_DOOR_ERR_HOLIDAYTIMESECTION					=13112,               //假期内开门时间段错误(无效刷卡)
	ALARM_DOOR_NEED_FIRSTCARD_PERMISSION				=13113,               //需要先验证有首卡权限的卡片(无效刷卡)
	ALARM_DOOR_ERR_CARD_PASSWORD						=13114,               //卡片正确,输入密码错误(无效刷卡)
	ALARM_DOOR_INPUTCARDPWD_TIMEOUT						=13115,               //卡片正确,输入密码超时(无效刷卡)
	ALARM_DOOR_ERR_CARD_FINGERPRINT						=13116,               //卡片正确,输入指纹错误(无效刷卡)
	ALARM_DOOR_INPUTCARDFINGERPRINT_TIMEOUT				=13117,            //卡片正确,输入指纹超时(无效刷卡)
	ALARM_DOOR_ERR_FINGERPRINT_PASSWORD					=13118,              //指纹正确,输入密码错误(无效刷卡)
	ALARM_DOOR_INPUTFINGERPRINTPWD_TIMEOUT				=13119,              //指纹正确,输入密码超时(无效刷卡)
	ALARM_DOOR_ERR_GROUP               					=13120,              //组合开门顺序错误(无效刷卡)
	ALARM_DOOR_GROUPN_NEED_VERIFY						=13121,              //组合开门需要继续验证(无效刷卡)
	ALARM_DOOR_CONSOLE_UNAUTHORIZE						=13122,              //验证通过,控制台未授权(无效刷卡)
	ALARM_DOOR_CARD_PWD_OPENDOOR          				=13123,				//卡加密码开门
	ALARM_DOOR_CARD_FINGERPRINT_OPENDOOR				=13124,				//卡加指纹开门
	ALARM_DOOR_REMOTE_CONFIRM          					=13125,				//远程验证
	ALARM_DOOR_GROUP_OPENDOOR_CONFIRM					=13126,				//组合开门验证通过
	ALARM_ATTENDANCESTATE_SIGNIN						=13130,
	ALARM_ATTENDANCESTATE_SIGNOUT						=13131,
	ALARM_ATTENDANCESTATE_WORK_OVERTIME_SIGNIN			=13132,
	ALARM_ATTENDANCESTATE_WORK_OVERTIME_SIGNOUT			=13133,
	ALARM_ATTENDANCESTATE_GOOUT							=13134,
	ALARM_ATTENDANCESTATE_GOOUT_AND_RETRUN				=13135,

	ALARM_WORK_CHECK_IN									=13200,
	ALARM_WORK_CHECK_OUT								=13201,
	ALARM_OVERTIME_CHECK_IN								=13202,
	ALARM_OVERTIME_CHECK_OUT							=13203,
	ALARM_GO_OUT										=13204,
	ALARM_GO_BACK										=13205,
	ALARM_CUSTOM_PASSWORD_OPEN							=13300,			// 个性化密码开门

	ALARM_RECORD_DOWNLOADORPLAYBACK_END					= 13501,			// 录像文件下载、回放结束
	ALARM_TRAFFIC_JAM									= 13502,            // 交通拥堵事件

	ALARM_CUSTOMER_STATISTICIAN_OVERFLOW				= 13600,			// 客流统计报警 - 流量超限报警
	ALARM_CUSTOMER_STATISTICIAN_END						= 13700,			// 客流统计报警 - 结束
	// 综合能源产品线 报警 开始

	// 综合能源产品线 报警 开始
	// 14000 - 15000
	// 综合能源产品线 报警 结束

	//新增的车载报警类型  预留30个报警 15001 - 15030  其它请勿占用
	ALARM_BUS_LANE_DEPARTURE_WARNNING					= 15001,			// 车道偏离
	ALARM_BUS_FORWARD_COLLISION_WARNNING				= 15002,			// 前向碰撞预警	
	ALARM_VEHICLE_STATE_START							= 15003,            // 车辆状态上报 开始运动
	ALARM_VEHICLE_STATE_BEYOND_10						= 15004,            // 车辆状态上报 车速大于10km/h
	ALARM_VEHICLE_STATE_STOP 							= 15005,            // 车辆状态上报 停止
	ALARM_SERVICE_DISTANCE_BELOW_2000                   = 15006,            // 车辆保养距离小于2000km报警

	//新开辟的IVS智能报警 预留1500个 范围15500 - 17000
	ALARM_IVS_ALARM_NEW_BEGIN							= 15500,				// 智能设备报警类型在dhnetsdk.h基础上+15000（DMS服务中添加）,因为是从590+15000开始的
	ALARM_IVS_FLOW_BUSINESS								= 0x0000024E + 15000,	// 流动摊贩事件 
	ALARM_IVS_CITY_MOTORPARKING							= 0X0000024F + 15000,   // 城市机动车违停事件
	ALARM_IVS_CITY_NONMOTORPARKING						= 0x00000250 + 15000,	// 城市机非动车违停事件
	ALARM_IVS_LANEDEPARTURE_WARNNING					= 0X00000251 + 15000,   // 车道偏移预警    
	ALARM_IVS_FORWARDCOLLISION_WARNNING					= 0X00000252 + 15000,   // 前向碰撞预警
	ALARM_IVS_MATERIALSSTAY								= 0X00000253 + 15000,   // 物料堆放事件
	ALARM_STAYALONE_DETECTION							= 0X00000254 + 15000,	// 单人独处检测
	ALARM_IVS_FLOATINGOBJECT_DETECTION					= 0X00000257 + 15000,   // 漂浮物检测事件
	ALARM_IVS_PHONECALL_DETECT							= 0x0000025A + 15000,	// 打电话报警
	ALARM_IVS_SMOKING_DETECT							= 0x0000025B + 15000,	// 吸烟报警
	ALARM_IVS_QUEUESTAY_DETECTION						= 0X00000262 + 15000,   // 排队滞留时间报警事件
	ALARM_IVS_QUEUENUM_DETECTION						= 0X00000263 + 15000,   // 排队人数异常报警事件
	ALARM_IVS_VEHICLE_DISTANCE_NEAR						= 0x0000026B + 15000,   // 安全驾驶车距过近报警事件
	ALARM_IVS_TRAFFIC_DRIVER_ABNORMAL					= 0x0000026C + 15000,   // 驾驶员异常报警事件
	ALARM_IVS_TRAFFIC_DRIVER_CHANGE						= 0x0000026D + 15000,   // 驾驶员变更报警事件
	ALARM_IVS_WORKCLOTHES_DETECT						= 0x0000026E + 15000,   // 工装(安全帽/工作服等)检测事件
	ALARM_IVS_SECURITYGATE_PERSONALARM					= 0x0000026F + 15000,   // 安检门人员报警
	ALARM_IVS_STAY_ALONE_DETECTION						= 0x00000270 + 15000,	// 单人独处事件
	ALARM_IVS_INFRAREDBLOCK								= 0x00000275 + 15000,   // 红外阻断事件
	ALARM_IVS_PANORAMA_SHOT								= 0x00000278 + 15000,   // 全景抓拍事件
	ALARM_IVS_TAKE_OFF_DUTY								= 16993,                // 民警脱岗
	ALARM_IVS_LOW_WATER_LEVEL							= 16994,	            // 水位报警 低水位
	ALARM_IVS_HIGH_WATER_LEVEL							= 16995,	            // 水位报警 高水位
	ALARM_IVS_UNMANNED_INTERROGATE						= 16996,				// 无人审讯
	ALARM_IVS_SIGNAL_INTERROGATE						= 16997,                // 单人审讯  
	ALARM_IVS_TYPE_CROWD_DENSITY						= 16998,				// 区域人群密度报警   报警拆分, 为不影响原报警的 300+netSDK值,的代码结构, 所以报警从后面来
	ALARM_IVS_TYPE_NUMBER_EXCEED						= 16999,				// 全域人群密度报警
	ALARM_IVS_ALARM_NEW_END								= 17000,				// 智能设备报警类型在dhnetsdk.h基础上+15500（DMS服务中添加）
	ALARM_CONGESTION_DETECTION_JAM						= 17001,				// 道路场景车辆拥堵报警
	ALARM_CONGESTION_DETECTION_QUEUE					= 17002,				// 道路场景车辆排队报警
	ALARM_VEHICLELIMIT_DETECTION						= 17003,				// 停车场场景下停车车辆上限报警
	ALARM_IVS_ANATOMY_NOT_UPTEMP						= 17004,				// 人体温智能检测未超高温事件
	ALARM_IVS_STATE_NOMASK		  						= 17005,				// 人体未戴口罩事件

	//组合报警 预留100个 范围18000 - 18100
	ALARM_GROUP_ALARM_BEGIN								= 18000,
	ALARM_GROUP_IPC_PEOPLENUM_ONE						= 18001,			//组合报警-单人状态
	ALARM_GROUP_ARM_DISABLE								= 18002,			//组合报警-撤防状态
	ALARM_GROUP_ALARM_END								= 18100,

	ALARM_PERSON_STAY									= 18101,			//人员滞留
	ALARM_ZONE_STAY										= 18102,			//区域滞留
	ALARM_SINGLE_STAY									= 18103,			//单个人员滞留
	ALARM_VISITOR_STAY									= 18104,			//访客滞留
	ALARM_ABNORMAL_PERSON								= 18105,			//异常人员
	ALARM_ILLEGAL_ENTER									= 18106,			//非法进入
	ALARM_FIREWARNING									= 18107,            //热成像着火点

	//报警主机异常布撤防 预留100个 范围18200 - 18300
	DEV_MSG_TYPE_DELAYED_ARM							=18200,       		//延时布防


	// 增加的一些普通报警的报警值 19000~20000
	ALARM_CROWD_DETECTION								=19000,              //人群密度报警
	ALARM_VEHICLE_LOAD									=19001,              //车载NVR载重数据上传事件
	ALARM_VEHICLE_OILLEVEL								=19002,				 //车载NVR油位数据上传事件
	ALARM_IMSI_CHECK									=19003,              //IMSI校验事件
	ALARM_BLIND_ALARM									=19004,              //进入盲区报警
	ALARM_DISK_CHECK									=19005,              //磁盘检测
	ALARM_NAS_SERVER_STATE								=19006,				 //共享服务
	ALARM_VOLUME_GROUP_FAULT						 	=19007,				 //存储池异常
	ALARM_ANALOGALARM_EVENT_HARMFUL_GAS                 =19008,              //有毒气体
	ALARM_BUS_EXPORT_SITE                               =19009,              //离站事件
	ALARM_SMARTMOTION_HUMAN                             =19010,              //智能人动检
	ALARM_SMARTMOTION_VEHICLE                           =19011,              //智能车动检
	ALARM_SMARTMOTION_HUMAN_AND_VEHICLE                 =19012,              //智能人&&车动检
	// 增加的一些普通报警的报警值 19000~20000

	//机器人报警  预留200个报警 20001 - 20200  其它请勿占用
	RC_ALARM_COLLISION									= 20001,            //碰撞事件
	RC_ALARM_ROADBLOCKED								= 20002,			 //遇障
	RC_ALARM_FAULT										= 20003,			 //机器人本地错误
	RC_ALARM_BRAKE										= 20004,			 //紧急刹车
	RC_ALARM_CHARGING_ERROR								= 20005,			 //充电错误
	RC_ALARM_DERAILMENT									= 20006,			 //脱轨
	RC_ALARM_PREVENT_FALLING							= 20007,			 //防跌落

	//MCD 加报警  22000~23000
	ALARM_CALL_OUT                                      = 22000,             //呼叫按钮报警
	ALARM_CALL_THE_POLICE                               = 22001,             //报警按钮报警    

	//格力事件订阅
	ALARM_ABNORMAL_RUN									= 23001,			//停线异常
	ALARM_ABNORMAL_STOP									= 23002,			//点停异常

	// 车载ADAS报警，特殊定制，新增报警类型加以区分
	ALARM_EM_ADAS_BEGIN			= 49700,      // begin
	ALARM_EM_ADAS_TIRED_DRIVE_DISTANCE_NEAR				= 49701,			// 车距过近
	ALARM_EM_ADAS_TIRED_DRIVE_FORWARD_COLLISION			= 49702,			// 碰撞报警
	ALARM_EM_ADAS_TIRED_DRIVE_LEFTLANE_DEPARTURE		= 49703,			// 左车道线报警
	ALARM_EM_ADAS_TIRED_DRIVE_RIGHTLANE_DEPARTURE		= 49704,			// 右车道线报警
	ALARM_EM_ADAS_TIRED_DRIVE_SUDDENLY_ACCELER			= 49705,			// 急加速
	ALARM_EM_ADAS_TIRED_DRIVE_TRAFFIC_ADAS_BRAKES		= 49706,			// 急刹车
	ALARM_EM_ADAS_TIRED_DRIVE_SHARP_TURN_LEFT			= 49707,			// 急左转弯
	ALARM_EM_ADAS_TIRED_DRIVE_SHARP_TURN_RIGHT			= 49708,			// 急右转弯
	ALARM_EM_ADAS_TIRED_DRIVE_TURN_OVER					= 49709,			// 侧翻
	ALARM_EM_ADAS_TIRED_DRIVE_FRONT_SNAP				= 49710,			// 车前方抓拍
	ALARM_EM_ADAS_TIRED_DRIVE_DRIVER_SNAP				= 49711,			// 驾驶员抓拍
	ALARM_EM_ADAS_TIRED_DRIVE_DRIVER_LEAVE_POST			= 49712,			// 驾驶员离岗
	ALARM_EM_ADAS_TIRED_DRIVE_MILD_TIRED				= 49713,			// 疲劳一级报警
	ALARM_EM_ADAS_TIRED_DRIVE_TIRED						= 49714,			// 疲劳二级报警
	ALARM_EM_ADAS_TIRED_DRIVE_VIDEO_BLIND				= 49715,			// 摄像头遮挡
	ALARM_EM_ADAS_TIRED_DRIVE_DRIVER_CALLING			= 49716,			// 打电话
	ALARM_EM_ADAS_TIRED_DRIVE_DRIVER_YAWN				= 49717,			// 打哈欠
	ALARM_EM_ADAS_TIRED_DRIVE_DRIVER_SMOKING			= 49718,			// 抽烟
	ALARM_EM_ADAS_TIRED_DRIVE_DRIVER_LOOKAROUND			= 49719,			// 左顾右盼
	ALARM_EM_ADAS_TIRED_DRIVE_OVER_SPEED				= 49720,			// 超速
	ALARM_EM_ADAS_TIRED_DRIVE_SUBSTITUTION				= 49721,			// 换人报警
	ALARM_EM_ADAS_TIRED_DRIVE_ABNORMAL					= 49722,			// 驾驶员异常报警
	ALARM_EM_ADAS_END			= 49999,      // end
	// 车载ADAS报警end


	// 交通事件检测类型									//对应EnumCarRule中违章类型
	ALARM_TRAFFIC_ACTION_BENGIN							= 50000,
	ALARM_TRAFFIC_ACTION_PARKING						= 50001,			// 交通事件检测停车
	ALARM_TRAFFIC_ACTION_PEDESTRAIN						= 50002,			// 交通事件检测行人
	ALARM_TRAFFIC_ACTION_CONVERSE_RUN					= 50003,			// 交通事件检测逆行
	ALARM_TRAFFIC_ACTION_JAM							= 50004,			// 交通事件检测拥堵
	ALARM_TRAFFIC_ACTION_OMISSION						= 50005,			// 交通事件检测遗落物
	ALARM_TRAFFIC_ACTION_FOG							= 50006,			// 交通事件检测烟雾
	ALARM_TRAFFIC_ACTION_BLAZE 							= 50007,			// 交通事件检测火焰
	ALARM_TRAFFIC_ACTION_SPEED							= 50008,			// 交通事件检测超速
	ALARM_TRAFFIC_ACTION_LOWSPEED						= 50009,			// 交通事件检测低速
	ALARM_TRAFFIC_ACTION_ONLINE							= 50010,			// 交通事件检测压线
	ALARM_TRAFFIC_ACTION_SUDDEN_DECELE_RATION			= 50011,			// 交通事件检测突然减速
	ALARM_TRAFFIC_ACTION_PASSERBY						= 50012,			// 交通事件检测行人穿越
	ALARM_TRAFFIC_ACTION_BACK							= 50013,			// 交通事件检测倒车
	ALARM_TRAFFIC_ACTION_RUN_FORBIDDEN_AREA				= 50014,			// 交通事件检测禁行区行驶
	ALARM_TRAFFIC_ACTION_TRAIL_ANOMALY					= 50015,			// 交通事件检测轨迹异常
	ALARM_TRAFFIC_ACTION_END							= 59999,
	ALARM_VEHICLE_IMPORT_SITE							= 600000,			// 车载进站报警
	ALARM_VEHICLE_EXPORT_SITE							= 600001,			// 车载离站报警
	ALARM_VEHICLE_CIRCUIT_SHIFT							= 600002,			// 车载路线偏移报警
	ALARM_VEHICLE_ROUTE_OVERTIME						= 600003,			// 车载路线超时报警
	ALARM_BULLDOZE_FORCE								= 600004,			// 强拆报警
	ALARM_VAILID_FACE_OPEN								= 600005,			// 合法人脸开门报警
	ALARM_INVAILID_FACE_OPEN							= 600006,			// 非法人脸开门报警
	ALARM_CARD_AND_FACE_TIMEOUT							= 600011,			// 卡和人脸超时报警
	ALARM_CARD_AND_FACE_ERROR							= 600012,			// 卡和人脸错误报警
	ALARM_CARD_AND_FACE_OPEN							= 600013,			// 卡和人脸正确开门报警

	ALARM_DOOR_FINGERPRINT_AND_PWD_OPENDOOR				= 700000,			// 指纹+密码开锁
	ALARM_DOOR_FINGERPRINT_AND_FACE_OPENDOOR			= 700001,			// 指纹+人脸开锁
	ALARM_DOOR_FACE_AND_PWD_OPENDOOR					= 700002,			// 人脸+密码开锁
	ALARM_DOOR_CARD_AND_FINGERPRINT_AND_PWD_OPENDOOR	= 700003,			// 刷卡+指纹+密码开锁
	ALARM_DOOR_CARD_AND_FINGERPRINT_AND_FACE_OPENDOOR	= 700004,			// 刷卡+指纹+人脸开锁
	ALARM_DOOR_FINGERPRINT_AND_FACE_AND_PWD_OPENDOOR	= 700005,			// 指纹+人脸+密码
	ALARM_DOOR_CARD_AND_FACE_AND_PWD_OPENDOOR			= 700006,			// 刷卡+人脸+密码开锁
	ALARM_DOOR_CARD_AND_FINGERPRINT_AND_FACE_AND_PWD_OPENDOOR			= 700007,			// 卡+指纹+人脸+密码开锁
	//---预留到701000
	// 智能电源报警
	ALARM_POWERSRC_SHORT_CIRCUIT  						= 701001, //通道短路故障
	ALARM_POWERSRC_MAIN_POWER_OUTPUT 					= 701002, //主电源输出故障报警
	ALARM_POWERSRC_MAINS_INPUT 							= 701003, //市电输入故障报警
	ALARM_POWERSRC_FAN									= 701004, //风扇故障报警	
	ALARM_POWERSRC_TEMPERATURE  						= 701005, //温度告警
	ALARM_POWERSRC_VOLTAGE  							= 701006, //电压告警
	ALARM_POWERSRC_OFFLINE 								= 701007, //电源设备离线告警
	ALARM_HEARTRATE_TOOHIGHT 							= 701008, //心率过高报警
	ALARM_HEARTRATE_TOOLOW 								= 701009, //心率过低报警
	ALARM_BREATHRATE_TOOHIGHT 							= 701010, //呼吸过高报警
	ALARM_BREATHRATE_TOOLOW 							= 701011, //呼吸过低报警
	ALARM_NOTONBED_TOOLONG 								= 701012, //离床报警
	ALARM_ONBED_TOOLONG									= 701013, //在床报警

	//新接带图片门禁
	//701500-702000
	ALARM_FACE_DOOR_TYPE_ENABLEUSERCARD 				=701500,  //合法卡
	ALARM_FACE_DOOR_TYPE_ENABLEUSERCARD_VALID_FACE_OPEN =701501,  //合法人脸
	ALARM_FACE_DOOR_TYPE_VALID_FINGERPRINT 				=701502,  //合法指纹
	ALARM_FACE_DOOR_TYPE_VALID_PASSWORD 				=701503,  //合法密码

	ALARM_FACE_DOOR_TYPE_NOCARD 						=701504,  //非法卡
	ALARM_FACE_DOOR_TYPE_ENABLEUSERCARD_INVALID_FACE 	=701505,  //非法人脸
	ALARM_FACE_DOOR_TYPE_INVALID_FINGERPRINT 			=701506,  //非法指纹
	ALARM_FACE_DOOR_TYPE_INVALID_PASSWORD 				=701507,  //非法密码

	ALARM_FACE_DOOR_REMOTE_CONFIRM_OPEN					=701508,  //远程验证	

}dpsdk_alarm_type_e;

// 报警来源
typedef enum
{
	ALARM_SOURCE_ALL					= 1,				// 所有
	ALARM_SOURCE_DEV,										// 设备
	ALARM_SOURCE_PLATFORM,									// 平台
}dpsdk_alarm_source_e;

// 预案状态
typedef enum
{
	ALARM_SCHEME_STATUS_CLOSE			= 0,				// 关闭
	ALARM_SCHEME_STATUS_OPEN,								// 打开
}dpsdk_alarmScheme_status_e;

// 预案获取模式
typedef enum
{
	ALARM_SCHEME_USER_MODE			= 0,					// 默认，获取指定用户的预案
	ALARM_SCHEME_ALL_MODE,									// 获取所有的预案
	ALARM_SCHEME_DEPARTMENT_MODE,							// 根据管辖区域获取预案
}dpsdk_alarmScheme_query_mode_e;

// cms消息通知类型
typedef enum
{
	ALARM_MSGTYPE_UnKnown				= 0,				// 未知
	ALARM_MSGTYPE_TIMETEMPLATE_ADD,							// 时间模板添加
	ALARM_MSGTYPE_TIMETEMPLATE_UPDATE,						// 时间模板更新
	ALARM_MSGTYPE_TIMETEMPLATE_DELETE,						// 时间模板删除
	ALARM_MSGTYPE_ALARMSCHEME_ADD,							// 报警预案添加
	ALARM_MSGTYPE_ALARMSCHEME_UPDATE,						// 报警预案更新
	ALARM_MSGTYPE_ALARMSCHEME_DELETE,						// 报警预案删除
	ALARM_MSGTYPE_ALARMSCHEMESHARE_GET,						// 重新获取预案报警关系
}dpsdk_alarm_msgType_e;

// 获取自定义报警类型信息请求语言类型
typedef enum
{ 
	ALARM_LANGUAGE_UNKNOWN				= 0,				// 未设置语言
	ALARM_LANGUAGE_EN,										// 英文
	ALARM_LANGUAGE_CHS,										// 简体中文
	ALARM_LANGUAGE_CHT,										// 繁体中文
}dpsdk_alarm_language_type_e;

// 报警查询信息
typedef struct DPSDK_API AlarmQueryInfo
{
	char					cameraID[DPSDK_CHL_ID_LEN];		// 通道ID
	int64_t					startTime;						// 开始时间
	int64_t					endTime;						// 结束时间
	int						dealWith;						// 处理意见类型（参见dpsdk_alarm_dealwith_e枚举）
	dpsdk_alarm_source_e	source;							// 报警来源。(参见dpsdk_alarm_source_e枚举)
	dpsdk_alarm_type_e		alarmType;						// 报警类型。(参见dpsdk_alarm_type_e枚举)
	uint32_t				deviceType;						// 设备类型。1 编码器, 2 报警主机, 3 控制器, 4 IVS-B, 5 IVS-V
    int		                channelAlarmType;			    // 视频报警主机报警查询时查询类型.add by djm 20131028 该类型可能为用户自定义
	int						expandFlag;						// 扩展标志，默认为0
															// 如果为0 则走旧协议查询CFLCUQueryAlarmRequest
															// 如果为1 则走新协议查询CFLCUQueryAlarmRequestEx
	bool					bzhbj;                          // -P750综合报警查询使用
	int                     unitType;     // 单元类型
	AlarmQueryInfo();
}AlarmQueryInfo_t;

// ADS查询综合报警信息
typedef struct DPSDK_API ADSZhAlarmInfo
{
	int         alarmType;                          //报警类型 
	int         status;                             //报警状态，产生；消失 
	char        devId[DPSDK_DEV_ID_LEN];            //报警设备ID 
	int         channel;                            //报警通道 
	uint32_t    planId;								//报警策略ID 
	uint32_t    dbId;								//通用报警增加 
	uint32_t    alarmTime;                          //报警时间 
	char        source;                             //报警来源 
	uint32_t    level;                              //报警级别 
	char        message[DPSDK_ALARM_MSG_LEN];		//消息处理信息 
	char        title[DPSDK_ALARM_TITLE_LEN];       //名称 
	int         devType;                            //设备类型 
	int         dealState;							//处理状态 
	char		alarmId[DPSDK_ALARMCODE_LEN];       //报警ID     
	char		deviceName[256]; 
	char		picPath[256];						//
	//巡更相关
	char        lineName[256];						 //线路名称
	uint32_t    watchDate;							 //巡更日期
	char    watchTurn[256];							 //巡更班次 
	uint32_t    planBeginTime;						 //计划开始时间 
	uint32_t    turnTime;							 //班次时长 
	uint32_t    RealTurnTime;						 //实际巡更时长
	char    chargePerson[64];						 //责任人
	//char    detailInfo[1024*4];					 //详细信息（每个巡更点的状态）
	ADSZhAlarmInfo();
}ADSZhAlarmInfo_t;

// 报警确认信息
typedef struct DPSDK_API AlarmConfirmInfo
{
	char				szDeviceID[DPSDK_DEV_ID_LEN];		// 设备ID
	int					iChannelNo;							// 通道号

	char				cameraID[DPSDK_CHL_ID_LEN];			// 通道ID
	int64_t				alarmTime;							// 报警时间
	int64_t				confirmTime;						// 确认时间
	int64_t				dealWith;							// 处理意见类型（参见dpsdk_alarm_dealwith_e枚举）
	dpsdk_alarm_type_e	alarmType;							// 报警类型。(参见dpsdk_alarm_type_e枚举)
	char				alarmMessage[DPSDK_ALARM_INFO_LEN];	// 处理意见信息
	dpsdk_event_type_e	eventType;							// 事件状态
	char				alarmId[DPSDK_ALARMCODE_LEN];		// 报警code
	char                username[64];                       // 增加用户名字段，-F报警确认时，需要传用户名。
	bool				bAlarmFlag;							// true-报警运营平台 false-其他
	
	//报警运营平台
	char				dealPeople[DPSDK_ALARM_INFO_LEN];	// 处理人
	char				dealSubMess[DPSDK_ALARM_INFO_LEN];	// 处理意见子选项
	char				dealMemo[DPSDK_ALARM_INFO_LEN];		// 备注
	char				dealSubMess2[DPSDK_ALARM_INFO_LEN];	// 处理意见子选项2
	char				dealPeople2[DPSDK_ALARM_INFO_LEN];	// 处理人2
	char				dealMemo2[DPSDK_ALARM_INFO_LEN];	// 备注2
	char				alarmMessage2[DPSDK_ALARM_INFO_LEN];// 处理意见信息2

	int64_t				chnlAlarmLevel;						// 通道报警等级
	bool				bCurtainSignal;						// 是否为幕帘信号
	int					handleMode;							//处理模式 0手动,1自动,2系统
	AlarmConfirmInfo();
}AlarmConfirmInfo_t;	

// ADS查询报警信息
typedef struct DPSDK_API ADSAlarmInfo
{
	dpsdk_alarm_type_e		alarmType;						// 报警类型
	dpsdk_event_type_e		eventType;						// 事件状态
	char					devId[DPSDK_DEV_ID_LEN];		// 报警设备ID
	uint32_t				channel;						// 报警通道
	uint32_t				planId;							// 报警策略ID
	int64_t					alarmTime;						// 报警时间
	char					source;							// 报警来源,为兼容服务器使用char类型
	uint32_t				level;							// 报警级别
	char					message[DPSDK_ALARM_MSG_LEN]; 	// 支持GPS
	char					title[DPSDK_ALARM_TITLE_LEN];	// 名称
	uint32_t				devType;						// 设备类型
	dpsdk_alarm_dealwith_e	dealWith;						// 处理意见
	char					alarmId[DPSDK_ALARMCODE_LEN];	// 报警code 报警联动录像查询作为参数
	char					szPicUrl[256];					// 报警图片url
	//char					user[256];                      // 处理人
	//int64_t					processTime;				    // 报警处理时间
	char					position[4*1024];				

	ADSAlarmInfo();
}ADSAlarmInfo_t;

// ADS查询视频报警主机报警信息 add by djm 20131031
typedef struct DPSDK_API ADSAlarmHostInfo
{
	dpsdk_alarm_type_e		alarmType;						// 报警类型
	dpsdk_event_type_e		eventType;						// 事件状态
	char					devId[DPSDK_DEV_ID_LEN];		// 报警设备ID
	uint32_t				channel;						// 报警通道
	int                     channelAlarmType;               // 报警通道报警类型报警主机通道有效 add by djm 20131028
	uint32_t				planId;							// 报警策略ID
	int64_t					alarmTime;						// 报警时间
	char					source;							// 报警来源,为兼容服务器使用char类型
	uint32_t				level;							// 报警级别
	char					message[DPSDK_ALARM_MSG_LEN]; 	// 支持GPS
	char					title[DPSDK_ALARM_TITLE_LEN];	// 名称
	uint32_t				devType;						// 设备类型
	dpsdk_alarm_dealwith_e	dealWith;						// 处理意见
	char					alarmId[DPSDK_ALARMCODE_LEN];	// 报警code 报警联动录像查询作为参数
	char					szPicUrl[256];					// 报警图片url

	ADSAlarmHostInfo();
}ADSAlarmHostInfo_t;

// ADS查询视频报警主机报警信息 add by 21548新增字段
typedef struct DPSDK_API ADSAlarmHostInfo_new
{
	dpsdk_alarm_type_e		alarmType;						// 报警类型
	dpsdk_event_type_e		eventType;						// 事件状态
	char					devId[DPSDK_DEV_ID_LEN];		// 报警设备ID
	uint32_t				channel;						// 报警通道
	int                     channelAlarmType;               // 报警通道报警类型报警主机通道有效 add by djm 20131028
	uint32_t				planId;							// 报警策略ID
	int64_t					alarmTime;						// 报警时间
	char					source;							// 报警来源,为兼容服务器使用char类型
	uint32_t				level;							// 报警级别
	char					message[DPSDK_ALARM_MSG_LEN]; 	// 支持GPS
	char					title[DPSDK_ALARM_TITLE_LEN];	// 名称
	uint32_t				devType;						// 设备类型
	dpsdk_alarm_dealwith_e	dealWith;						// 处理意见
	char					alarmId[DPSDK_ALARMCODE_LEN];	// 报警code 报警联动录像查询作为参数
	char					szPicUrl[256];					// 报警图片url
	char					handleUser[DPSDK_DEV_ID_LEN];   // 报警处理人 
	char					defenceCode[DPSDK_DEV_ID_LEN];	// 防区编号  
}ADSAlarmHostInfo_t_New;


// ADS查询车载报警信息
typedef struct DPSDK_API ADSMAlarmInfo 
{ 
	int						areaId;							// 围栏ID	3.0废弃 
	int						areatype;                       // 围栏类型	3.0废弃 
	int						overSpeed;                      // 超速，.0为当前速度 
	int						maxSpeed;                       // 限速值 
	char					driverId[DPSDK_DRIVER_ID_LEN];  // 司机工号 
	char					deviceId[DPSDK_DEV_ID_LEN];     // 设备ID 
	int						alarmType;                      // 报警类型 
	uint32_t				alarmTime;                      // 报警发生时间,精度为秒，值为time(NULL)值 
	char					message[DPSDK_ALARM_MSG_LEN];   // 备注信息 
	int						diffSpeed;                      // 当前速度-上次速度 
	int						diffAlarmTime;                  // 当前报警时间-上次报警时间（秒） 
	int						planid;                         // 报警策略ID	3.0废弃 
	char					areaCode[DPSDK_AREA_CODE_LEN];	// 围栏码 
	//double				dbLongitude;					// 经度 
	//double				dbLatitude;						// 纬度 
	int						alarmStat;						// 报警状态 
	int						channelSeq;						// 通道序号 
	char					deviceName[DPSDK_DEV_ID_LEN];	// 设备名称 
	char					alarmId[DPSDK_ALARMCODE_LEN];	// 报警的guid 
	int						dealState;						// 处理状态 
	char					areaType[DPSDK_AREA_TYPE_LEN];	// 围栏类型 
	double					dbLongitude;					// 经度 
	double					dbLatitude;						// 纬度 

	ADSMAlarmInfo();
}ADSMAlarmInfo_t;


// 预案列表信息
typedef struct DPSDK_API SchemeListInfo
{
	dpsdk_alarmScheme_status_e	status;								// 预案状态
	uint32_t					id;									// 预案数据库id
	char						schemeName[DPSDK_SCHEME_NAME_LEN];	// 预案名称
	uint32_t					templateId;							// 预案时间模板ID
	char						desc[DPSDK_SCHEME_DESC_LEN];		// 预案描述

	SchemeListInfo();
}SchemeListInfo_t;

// 自定义时间模板信息
typedef struct DPSDK_API Customs_TimeTemplate_Info
{
	uint32_t 	id;											// 序号
	char		name[DPSDK_TEMPLATE_NAME_LEN];				// 模板名称
	char		remark[DPSDK_TEMPLATE_REMARK_LEN];			// 时间模板的说明
	char		flag[DPSDK_TEMPLATE_FLAG_LEN];				// 具体包含全天的、还是周一到周日

	Customs_TimeTemplate_Info();
}Customs_TimeTemplate_Info_t;

// 报警消息
typedef struct DPSDK_API AlarmMessageInfo
{
	int						nChannel;									// 通道 
	char					deviceId[DPSDK_DEV_ID_LEN];                 // 设备ID（DVR+通道） 
	char                    LinkdeviceId[DPSDK_DEV_ID_LEN];				// 关联设备ID
	dpsdk_alarm_type_e		nType;                                      // 类型。视频丢失，外部报警，移动侦测 
	uint8_t					status;                                     // 状态。发生，消失 
	int						nAlarmLevel;                                // 报警级别 
	uint32_t				nAlarmTime;                                 // 报警发生时间,精度为秒，值为time(NULL)值 
	int						nDeviceType;                                // 设备类型。编码器，报警主机 
	char					message[DPSDK_ALARM_MSG_LEN];				// 报警附加信息，支持GPS上报
	int						nGpsType;                                   // gps上报类型(正常、补传) 
	char					picPath[DPSDK_FILENAME_LEN];				//手抓图片的图片路径，取路径长度为256

}AlarmMessageInfo_t;

// ADS查询RFID报警信息
typedef struct DPSDK_API ADSRFIDAlarmInfo
{
	dpsdk_alarm_type_e		alarmType;						// 报警类型
	dpsdk_event_type_e		eventType;						// 事件状态
	char					devId[DPSDK_DEV_ID_LEN];		// 报警设备ID
	uint32_t				channel;						// 报警通道
	uint32_t				planId;							// 报警策略ID
	int64_t					alarmTime;						// 报警时间
	char					source;							// 报警来源,为兼容服务器使用char类型
	uint32_t				level;							// 报警级别
	char					message[DPSDK_ALARM_MSG_LEN]; 	// 支持GPS
	char					title[DPSDK_ALARM_TITLE_LEN];	// 名称
	uint32_t				devType;						// 设备类型
	dpsdk_alarm_dealwith_e	dealWith;						// 处理意见
	char					alarmId[DPSDK_ALARMCODE_LEN];	// 报警code 报警联动录像查询作为参数
	char					szPicUrl[256];					// 报警图片url
	char					szSwLabel[DPSDK_CHAR_LEN_32];	// 超声波探测标签
	char					szElecLabel[DPSDK_CHAR_LEN_32];	// 车用电子标签

	ADSRFIDAlarmInfo();
}ADSRFIDAlarmInfo_t;
//////////////////////////////////////////////////////////////////////////

// 获取预案列表消息
class DPSDK_API GetSchemeListMsg : public DPSDKCBMessage
{
public:
	GetSchemeListMsg(void);
	virtual ~GetSchemeListMsg(void);

public:
	// response
	uint32_t			count;								// 预案个数
	SchemeListInfo_t*	pInfo;								// 预案列表数据
	int					param;								// 1：获取所有的预案；0：获取指定用户的预案（默认）
};

// 获取预案文件消息
class DPSDK_API GetSchemeFileMsg : public DPSDKCBMessage
{
public:
	GetSchemeFileMsg(void);
	virtual ~GetSchemeFileMsg(void);

public:
	// request
	uint32_t					id;									// 预案数据库id

	// response
	dpsdk_alarmScheme_status_e	status;								// 预案状态
	char						schemeName[DPSDK_SCHEME_NAME_LEN];	// 预案名称
	uint32_t					templateId;							// 时间模板ID
	char						desc[DPSDK_SCHEME_DESC_LEN];		// 预案描述
	char*						data;								// 预案数据
	uint32_t					len;								// 预案数据长度
};

// 保存预案文件消息
class DPSDK_API SaveSchemeFileMsg : public DPSDKCBMessage
{
public:
	SaveSchemeFileMsg(void);
	virtual ~SaveSchemeFileMsg(void);

public:	
	// request
	SchemeListInfo_t	info;								// 预案列表信息
	char*				data;								// 预案数据
	uint32_t			len;								// 预案数据长度
	int					param;								// 1：保存预案通知所有用户，0:仅通知复用用户
};

// 删除预案文件消息
class DPSDK_API DelSchemeFileMsg : public DPSDKCBMessage
{
public:
	DelSchemeFileMsg(void);
	virtual ~DelSchemeFileMsg(void){}

public:	
	// request
	uint32_t			id;									// 预案数据库id
	int					param;								// 1：删除预案通知所有用户，0:仅通知复用用户
};

// 设置报警联动消息
class DPSDK_API SetAlarmEnableMsg : public DPSDKCBMessage
{
public:
	SetAlarmEnableMsg(void);
	virtual ~SetAlarmEnableMsg(void);

public:
	// request
	char*		alarmEnable;								// 报警源信息
	int			nDatalen;									// 长度
};

// 设置报警接收能力
class DPSDK_API SetAlarmAcceptCapacityMsg : public DPSDKCBMessage
{
public:
	SetAlarmAcceptCapacityMsg(void);
	virtual ~SetAlarmAcceptCapacityMsg(void);

public:
	// request
	int nAlarmAcceptNum;									//0：不能接收，>0：能接受的条数
};

// 查询时间模板消息
class DPSDK_API TimeTemplateMsg : public DPSDKCBMessage
{
public:
	TimeTemplateMsg(void);
	virtual ~TimeTemplateMsg(void);

public:
	// request
	uint32_t						id;						// 时间模板id

	// response
	uint32_t						count;					// 时间模板个数
	Customs_TimeTemplate_Info_t*	pTemplateInfo;			// 一组时间模板数据
};

// 查询报警类型显示等级消息
class DPSDK_API ShowLevelAlarmTypeMsg : public DPSDKCBMessage
{
public:
	ShowLevelAlarmTypeMsg(void);
	virtual ~ShowLevelAlarmTypeMsg(void);

public:
	// response
	char*		pShowLevelAlarmTypeData;
	int			nDataLen;
};

// 自定义报警类型消息
class DPSDK_API CustomAlarmTypeMsg : public DPSDKCBMessage
{
public:
	CustomAlarmTypeMsg(void);
	virtual ~CustomAlarmTypeMsg(void);

public:
	// request
	dpsdk_alarm_language_type_e	nLanguageType;				// 请求语言类型

	// response
	char*		pCustomAlarmTypeData;
	int			nDataLen;
};

// 系统报警类型消息
class DPSDK_API SystemAlarmTypeMsg : public DPSDKCBMessage
{
public:
	SystemAlarmTypeMsg(void);
	virtual ~SystemAlarmTypeMsg(void);

public:
	// response
	char*		pSystemAlarmTypeData;
	int			nDataLen;
};

// CMS报警预案相关通知消息
class DPSDK_API CMSAlarmNotifyMsg : public DPSDKCBMessage
{
public:
	CMSAlarmNotifyMsg(void);
	virtual ~CMSAlarmNotifyMsg(void){};

public:
	dpsdk_alarm_msgType_e	type;							// 消息类型,预案通知、时间模板通知使用
	uint64_t				id;								// 数据库id,预案通知使用
	uint64_t				nParam1;						// 修改预案通知时表示时间模板id
	uint64_t				nParam2;						// 修改预案通知时表示预案开关
	char					szMsg[2048];					// 修改预案通知时表示修改者ip;时间模板存在批量删除情况，故使用str类型标识id
};

// ADS实时报警通知消息
class DPSDK_API ADSReportAlarmMsg : public DPSDKCBMessage
{
public:
	ADSReportAlarmMsg(void) ;
	virtual ~ADSReportAlarmMsg(void);

public:
	char				cameraID[DPSDK_CHL_ID_LEN];			// 通道id
	char				deviceName[DPSDK_DEVICE_NAME_LEN];	// 设备名称
	char				channelName[DPSDK_DEVICE_NAME_LEN];	// 通道名称
	dpsdk_alarm_type_e	alarmType;							// 报警类型
	int                 nChnAlarmType;                      // 通道报警类型 针对报警主机增加 add by djm 201310128
	dpsdk_event_type_e	eventType;							// 事件状态
	int64_t				time;								// 发送时间，单位毫秒
	uint32_t			deviceType;							// 设备类型
	char				coding[DPSDK_ALARM_INFO_LEN];		// 组织结构
	uint32_t			level;								// 报警等级
	char				message[DPSDK_ALARM_MSG_LEN];		// 报警附加信息,存放的有GPS信息
	char				msgExtra[DPSDK_ALARM_MSGEXTRA_LEN];	// 滕州监狱需求，上传报警需要增加的信息 add by huwenjuan20140524
	char				alarmID[DPSDK_ALARM_ID_LEN];		// 数据库id
	char*				pAlarmData;							// 智能信息数据
	uint32_t			nAlarmDataLen;						// 智能信息数据长度
	char*				pPicData;							// 图片数据
	uint32_t			nPicDataLen;						// 图片数据长度
	char				netName[DPSDK_DEVICE_NAME_LEN];		// 网点名称
	char				customName[DPSDK_DEVICE_NAME_LEN];	// 客户名称
	uint32_t			netCode;							// 网点编码
	uint32_t			customCode;							// 客户名称

	//电网设备特有上报电流电压
	int32_t				nCurrent;							// 电流
	int32_t				nVoltage;							// 电压
	//巡更相关
	char        lineName[DPSDK_CHAR_256];					 //线路名称
	uint32_t    watchDate;									 //巡更日期
	char    watchTurn[DPSDK_CHAR_256];						 //巡更班次 
	uint32_t    planBeginTime;								 //计划开始时间 
	uint32_t    turnTime;									 //班次时长 
	uint32_t    RealTurnTime;								 //实际巡更时长
	char    chargePerson[DPSDK_CHAR_64];					 //责任人
	//char    detailInfo[DPSDK_CHAR_1024*4];				 //详细信息（每个巡更点的状态）
	char	strGasLevel[DPSDK_CHAR_256];					 //剩余油量（百分百）

	char		          strDeviceID[DPSDK_CHAR_256];		// 设备ID
	uint32_t		      nChannel;		// 通道号
	int                   unitType;     // 单元类型
};

// 新ADS实时报警通知消息
class DPSDK_API NewADSReportAlarmMsg : public DPSDKCBMessage
{
public:
	NewADSReportAlarmMsg(void) ;
	virtual ~NewADSReportAlarmMsg(void);

public:
	//char				cameraID[DPSDK_CHL_ID_LEN];			// 通道id
	char				szDeviceID[DPSDK_CHL_ID_LEN];		// 设备id
	int					iChannelNo;							// 通道号
	char				deviceName[DPSDK_DEVICE_NAME_LEN];	// 设备名称
	char				channelName[DPSDK_DEVICE_NAME_LEN];	// 通道名称
	dpsdk_alarm_type_e	alarmType;							// 报警类型
	int                 nChnAlarmType;                      // 通道报警类型 针对报警主机增加 add by djm 201310128
	dpsdk_event_type_e	eventType;							// 事件状态
	int64_t				time;								// 发送时间，单位毫秒
	uint32_t			deviceType;							// 设备类型
	char				coding[DPSDK_ALARM_INFO_LEN];		// 组织结构
	uint32_t			level;								// 报警等级
	char				message[DPSDK_ALARM_MSG_LEN];		// 报警附加信息,存放的有GPS信息
	char				msgExtra[DPSDK_ALARM_MSGEXTRA_LEN];	// 滕州监狱需求，上传报警需要增加的信息 add by huwenjuan20140524
	char				alarmID[DPSDK_ALARM_ID_LEN];		// 数据库id
	char*				pAlarmData;							// 智能信息数据
	uint32_t			nAlarmDataLen;						// 智能信息数据长度
	char*				pPicData;							// 图片数据
	uint32_t			nPicDataLen;						// 图片数据长度
	char				netName[DPSDK_DEVICE_NAME_LEN];		// 网点名称
	char				customName[DPSDK_DEVICE_NAME_LEN];	// 客户名称
	uint32_t			netCode;							// 网点编码
	uint32_t			customCode;							// 客户名称

	//电网设备特有上报电流电压
	int32_t				nCurrent;							// 电流
	int32_t				nVoltage;							// 电压
	//巡更相关
	char        lineName[DPSDK_CHAR_256];					 //线路名称
	uint32_t    watchDate;									 //巡更日期
	char    watchTurn[DPSDK_CHAR_256];						 //巡更班次 
	uint32_t    planBeginTime;								 //计划开始时间 
	uint32_t    turnTime;									 //班次时长 
	uint32_t    RealTurnTime;								 //实际巡更时长
	char    chargePerson[DPSDK_CHAR_64];					 //责任人
	//char    detailInfo[DPSDK_CHAR_1024*4];				 //详细信息（每个巡更点的状态）
	char	strGasLevel[DPSDK_CHAR_256];					 //剩余油量（百分百）

};


//报警转移信息
class DPSDK_API ADSTransferAlarmMsg:public ADSReportAlarmMsg
{
public:
	ADSTransferAlarmMsg(void);
	virtual ~ADSTransferAlarmMsg(void);

public:   
	char                srcUserName[DPSDK_CLIENT_NAME_LEN]; // 组员的名称
	uint32_t            nSrcID;                              
	uint32_t            nDstID;
	int                 nHandleState;						// 报警信息处理状态
	char                alarmMessage[DPSDK_ALARM_INFO_LEN]; // 报警信息处理意见
	char				szDeviceId[DPSDK_DEV_ID_LEN];		// 设备id
	int					iChannelNo;							// 通道号
	int					iAlarmSourceType;					// 报警源类型，参见协议库EnumAlarmSourceType
	char				szAlarmID[64];						// 报警ID，32位GUID
	char				szImageUrl[DPSDK_TAG_URL_LEN];		// 图片URL
};

// ADS实时报警通知消息
class DPSDK_API ADSPeccancyAlarmMsg : public DPSDKCBMessage
{
public:
	ADSPeccancyAlarmMsg(void) ;
	virtual ~ADSPeccancyAlarmMsg(void){};

public:
	int					areaId;								// 围栏ID   3.0废弃
	int					areatype;							// 围栏类型
	int					currrentSpeed;						// 当前速度
	int					maxSpeed;						    // 限速值
	char				driverId[DPSDK_DRIVER_ID_LEN];		// 司机工号
	char				deviceId[DPSDK_DEV_ID_LEN];			// 设备ID
	int					alarmType;							// 报警类型
	int64_t				alarmTime;							// 报警发生时间,精度为秒，值为time(NULL)值
	char				message[DPSDK_ALARM_MSG_LEN];		// 备注信息
	int					diffSpeed;							// 当前速度与限速值的差
	int					diffAlarmTime;						// 当前报警时间-上次报警时间（秒）
	char				areaCode[DPSDK_AREA_CODE_LEN];		// 围栏码
	char				dbLongitude[DPSDK_AREA_DB_LEN];		// 经度
	char				dbLatitude[DPSDK_AREA_DB_LEN];		// 纬度
	int					alarmStat;							// 报警状态
	int					channelSeq;							// 通道序号
	char				deviceName[DPSDK_DEV_ID_LEN];		// 设备名称
	char				alarmID[DPSDK_ALARMCODE_LEN];		// 报警id，guid
};

// 查询报警个数消息
class DPSDK_API QueryAlarmCountMsg : public DPSDKCBMessage
{
public:
	QueryAlarmCountMsg(void);
	virtual ~QueryAlarmCountMsg(void);

public:
	// request
	AlarmQueryInfo_t	queryInfo;							// 报警查询信息结构体
	uint32_t			queryType;							// 查询类型：=0查询数量 =1查询计划名称(IVS-V))
	char				planName[DPSDK_PLAN_NAME_LEN];		// 计划名称（IVS-V）

	// response
	uint32_t			count;								// 报警数量
	int typeCount[DPSDK_ZHALARM_TYPE_COUNT];				// dss-p750综合报警大类数量
};

// ADS查询报警信息扩展
typedef struct DPSDK_API ADSAlarmInfoEx
{
	dpsdk_alarm_type_e		alarmType;						// 报警类型
	dpsdk_event_type_e		eventType;						// 事件状态
	char					devId[DPSDK_DEV_ID_LEN];		// 报警设备ID
	uint32_t				channel;						// 报警通道
	uint32_t				planId;							// 报警策略ID
	int64_t					alarmTime;						// 报警时间
	char					source;							// 报警来源,为兼容服务器使用char类型
	char					salt1[3];						// 配套服务器进行字节填充
	uint32_t				level;							// 报警级别
	char					message[DPSDK_ALARM_MSG_LEN]; 	// 支持GPS
	char					title[DPSDK_ALARM_TITLE_LEN];	// 名称
	uint32_t				devType;						// 设备类型
	dpsdk_alarm_dealwith_e	dealWith;						// 处理意见
	char					alarmId[DPSDK_ALARMCODE_LEN];	// 报警code 报警联动录像查询作为参数
	char					deviceName[256];				// DB3.0 add 
	char					szPicUrl[256];					// 报警图片url

	char					handle_user[50];				// 处理的用户 
	char					salt2[6];						// 配套服务器进行字节填充
	int64_t					handle_date;                    // 处理的时间 					

	ADSAlarmInfoEx();
}ADSAlarmInfoEx_t;

// 向ADS查询报警消息
class DPSDK_API QueryAlarmMsg : public DPSDKCBMessage
{
public:
	QueryAlarmMsg(void);  
	virtual ~QueryAlarmMsg(void);

public:
	// request
	AlarmQueryInfo_t	queryInfo;							// 报警查询信息
	uint32_t			firstNum;							// 开始序号
	uint32_t			queryCount;							// 查询数量
	char				planName[DPSDK_PLAN_NAME_LEN];		// 计划名称（IVS-V）

	// response
	uint32_t			infoCount;							// 返回实际报警条数
	ADSAlarmInfo_t*		pAlarmInfo;							// 指向报警信息数据
	ADSMAlarmInfo_t*	pAlarmMInfo;						// 指向车载报警信息数据
	ADSAlarmHostInfo_t *pAlarmHostInfo;                     // 指向报警主机报警数据 add by djm 20131031
	ADSAlarmInfoEx_t*	pAlarmInfoEx;						// 扩展协议的报警结构体 from DSS-B
};

// 向ADS查询出入门禁消息 add by huwenjuan 20140520
class DPSDK_API QueryDoorInAndOutMsg : public DPSDKCBMessage
{
public:
	QueryDoorInAndOutMsg(void);  
	virtual ~QueryDoorInAndOutMsg(void);

public:
	// request
	char				szDepId[DPSDK_CHL_ID_LEN];		// 组织节点Id
	int64_t				timeBegin;					// 开始时间
	int64_t				timeEnd;					// 结束时间

	// response
	uint32_t			inDoorCount;				// 入门总数
	uint32_t			outDoorCount;				// 出门总数
};

// DSS-P750向ADS查询综合报警消息 
class DPSDK_API QueryZhAlarmMsg : public DPSDKCBMessage
{
public:
	QueryZhAlarmMsg(void);  
	virtual ~QueryZhAlarmMsg(void);

public:
	// request
	AlarmQueryInfo_t	queryInfo;							// 报警查询信息
	uint32_t			firstNum;							// 开始序号
	uint32_t			queryCount;							// 查询数量
	int					alarmType;							// 大类类型
	int					dbsn;								// 过滤值
	// response
	uint32_t			infoCount;							// 返回实际报警条数
	ADSZhAlarmInfo_t*		pAlarmInfo;						// 指向报警信息数据
};

// 通知预案刷新消息
class DPSDK_API NotifySchemeInvalidateMsg : public DPSDKCBMessage
{
public:
	NotifySchemeInvalidateMsg(void); 
	virtual ~NotifySchemeInvalidateMsg(void){}

public:
	int64_t 	schemeID;							// 预案ID
	uint32_t 	notifyType; 						// 变更类型为时间段索引（1）、报警源（2），动作（4）或他们的组合.
};

// 确认报警消息
class DPSDK_API ConfirmAlarmMsg : public DPSDKCBMessage
{
public:
	ConfirmAlarmMsg(void);  
	virtual ~ConfirmAlarmMsg(void){}

public:
	AlarmConfirmInfo_t	confirmInfo;				// 报警确认数据	
};

// ADS状态通知消息
class DPSDK_API ADSCommStatusMsg : public DPSDKCBMessage
{
public:
	ADSCommStatusMsg(void);  
	virtual ~ADSCommStatusMsg(void){}

public:
	char		serverId[SERVER_ID_LEN];			// 服务器ID			
	char		serverIp[DPSDK_IP_LEN];				// 服务器IP
	uint32_t	status;								// 0不在线 1重登陆ADS成功 2断线
};

// 查询智能报警图片消息
class DPSDK_API QueryIvsbAlarmPicMsg : public DPSDKCBMessage
{
public:
	QueryIvsbAlarmPicMsg(void);
	virtual ~QueryIvsbAlarmPicMsg(void);

public:
	dpsdk_operator_ftp_type_e	opType;						// 操作类型，请参考dpsdk_operator_ftp_type_e
	char						cameraId[DPSDK_CHL_ID_LEN];	// 摄像头ID
	char						url[DPSDK_TAG_URL_LEN];		// ftp服务器存储数据的相对url
	char						path[DPSDK_TAG_PATH_LEN];	// 本地上传或者下载后的图片的地址
	dpsdk_ftp_transport_mode_e  mode;						// 文件传输模式
	char						szUserName[DPSDK_CHAR_LEN_64];	// 用户名
	char						szPwd[DPSDK_CHAR_LEN_64];	// 密码
};

//fcj.add:人脸识别相关-黑白名单管理，历史人脸库查询，人脸小图抽取
class DPSDK_API FaceBaseMsg : public DPSDKCBMessage
{
public:
	FaceBaseMsg( int cmd = DPSDK_CMD_UNKNOWN,int msgType = DPSDK_MSG_REQUEST);
	~FaceBaseMsg(){}

	char	serverId[SERVER_ID_LEN];		// 服务ID
	char	cameraId[DPSDK_CHL_ID_LEN];		// 摄像头ID
	char	devId[DPSDK_DEV_ID_LEN];		// 设备ID
};

//大图检测消息
class DPSDK_API ExtractFacePicMsg : public FaceBaseMsg
{
public:
	ExtractFacePicMsg();
	virtual ~ExtractFacePicMsg();

public:
	// in: request
	long			bigPicLength;		// 原始图片大小
	char*			bigPicData;			// 原始图片数据
	uint32_t		picWidth;			// 原始图片宽度
	uint32_t		picHeight;			// 原始图片高度
	long			requestFlag;		// 请求标记 一般为请求源的指针

	// out: response
	char*			faceData;			// 返回的人脸数据
	long			faceDataLength;		// 返回数据长度
};

//查询人脸匹配数量
class DPSDK_API QueryFaceCountMsg : public FaceBaseMsg
{
public:
	QueryFaceCountMsg();
	virtual ~QueryFaceCountMsg();

public:
	// in: request
	char*				queryInfo;		// 查询条件
	long				infoDataLength;	// 查询条件信息长度
	long				requestFlag;	// 请求标记 一般为请求源的指针

	//response
	int					count;			// 匹配总数
	uint32_t			querySession;	// 查询会话
};

//查询人脸匹配具体信息
class DPSDK_API QueryFaceDataMsg : public FaceBaseMsg
{
public:
	QueryFaceDataMsg();
	virtual ~QueryFaceDataMsg();

public:
	//request
	uint32_t			querySession;	// 查询会话
	uint32_t			startIndex;		// 开始索引
	uint32_t			queryNum;		// 获取数目

	//response
	char*				personData;		// 返回的具体数据
	uint32_t			dataLength;		// 返回的数据长度
	std::string         strPicServerIp; //图片服务器ip
};

//操作人脸库(增删改)
class DPSDK_API OperateFaceLibMsg : public FaceBaseMsg
{
public:
	OperateFaceLibMsg();
	virtual ~OperateFaceLibMsg();

public:
	//request
	uint32_t			operateType;	// 1.modify 2.delete 3.add
	char*				personRegData;	// 人员信息
	uint32_t			dataLength;		// 信息长度

	long				requestFlag;	// 请求标记 一般为请求源的指针
};

//关闭查询会话
class DPSDK_API StopFaceQueryMsg: public FaceBaseMsg
{
public:
	StopFaceQueryMsg();
	virtual ~StopFaceQueryMsg();

public:
	uint32_t	querySession;			// 查询会话
};

//查询人脸报警数量
class DPSDK_API QueryIvsfAlarmCountMsg : public FaceBaseMsg
{
public:
	QueryIvsfAlarmCountMsg();
	virtual ~QueryIvsfAlarmCountMsg();

public:
	// in: request
	int64_t				startTime;							// 开始时间
	int64_t				endTime;							// 结束时间
	char				address[DPSDK_FACE_LOCATION_LEN];	// 抓拍地点
	uint32_t			alarmType;							// 报警类型 黑-白
	long				requestFlag;						// 请求标记 一般为请求源的指针
	//response
	int					count;								// 匹配总数
	uint32_t			querySession;						// 查询会话
};

//请求人脸报警具体信息
class DPSDK_API QueryIvsfAlarmDataMsg : public FaceBaseMsg
{
public:
	QueryIvsfAlarmDataMsg();
	virtual ~QueryIvsfAlarmDataMsg();

public:
	//request
	uint32_t			querySession;				// 查询会话
	uint32_t			startIndex;					// 开始索引
	uint32_t			queryNum;					// 获取数目

	//response
	char*				personData;					// 返回的具体数据
	uint32_t			dataLength;					// 返回的数据长度
};
//关闭人脸报警查询会话
class DPSDK_API StopIvsfAlarmQueryMsg: public FaceBaseMsg
{
public:
	StopIvsfAlarmQueryMsg();
	virtual ~StopIvsfAlarmQueryMsg();

public:
	uint32_t	querySession;						// 查询会话
};

//获取人脸报警指定的图片
class DPSDK_API GetIvsfAlarmPicMsg: public FaceBaseMsg
{
public:
	GetIvsfAlarmPicMsg();
	virtual ~GetIvsfAlarmPicMsg();

public:
	//request
	char*				queryInfo;					// 查询条件
	long				infoDataLength;				// 查询条件信息长度
	long				requestFlag;				// 请求标记 一般为请求源的指针

	//response
	char*				picFullData;				// 返回的完整图片数据(多个图片及其描述)
	long				picFullDataLength;			// 数据长度
};

//通过URL获取图片
class DPSDK_API RequestPicByUrlMsg : public DPSDKCBMessage
{
public:
	RequestPicByUrlMsg();
	virtual ~RequestPicByUrlMsg();
	dpsdk_operator_ftp_type_e	opType;				// 操作类型，请参考dpsdk_operator_ftp_type_e
	long	Requestgflg;
	char	url[DPSDK_TAG_URL_LEN];					// ftp服务器存储数据的相对url
	char	path[DPSDK_TAG_PATH_LEN];				// 本地上传或者下载后的图片的地址
};

//查询人脸进度上报
class DPSDK_API StartFindFaceProgressMsg : public DPSDKCBMessage
{
public:
	StartFindFaceProgressMsg();
	~StartFindFaceProgressMsg(){}

public:
	uint32_t	querySession;						// 查询会话
	int			nProgress;							// 进度（1-100）
	int			nCurrentCount;						// 当前条数
	std::string strDevId;							// 设备ID
};

// 客户端报警到服务
class DPSDK_API ClientAlarmToServerMsg : public DPSDKCBMessage
{
public:
	ClientAlarmToServerMsg(void);
	virtual ~ClientAlarmToServerMsg(void){}

public:
	char szCameraId[DPSDK_CHL_ID_LEN];		// 摄像头ID
	dpsdk_alarm_type_e enAlarmType;			// 报警类型
	dpsdk_event_type_e enStatus;			// 报警状态
	int64_t nAlarmTime;						// 报警时间
	char szMsg[DPSDK_ALARM_MSG_LEN];		// 额外信息
};

// 报警消息发送 add by minjie 2014-03-28
class DPSDK_API RequestAlarmMsg : public DPSDKCBMessage
{
public:
	RequestAlarmMsg(void) ;
	virtual ~RequestAlarmMsg(void);

public:
	char				serverId[SERVER_ID_LEN];					// 服务ID
	char				cameraId[DPSDK_CHL_ID_LEN];					// 摄像头ID

	int					nChannel;                                   // 通道 
	char				deviceId[DPSDK_DEV_ID_LEN];                 // 设备ID（DVR+通道） 
	char                LinkdeviceId[DPSDK_DEV_ID_LEN];				// 关联设备ID
	int					nType;                                      // 类型。视频丢失，外部报警，移动侦测 
	uint8_t				status;                                     // 状态。发生，消失 
	int					nAlarmLevel;                                // 报警级别 
	uint32_t			nAlarmTime;                                 // 报警发生时间,精度为秒，值为time(NULL)值 
	int					nDeviceType;                                // 设备类型。编码器，报警主机 
	char				message[DPSDK_ALARM_MSG_LEN];				// 报警附加信息，支持GPS上报
	int					nGpsType;                                   // gps上报类型(正常、补传) 

	char				picPath[DPSDK_FILENAME_LEN];				//手抓图片的图片路径，取路径长度为256									
};

// 手动抓图图片路径发送消息，江西戒毒所需求
class DPSDK_API AlarmPicPathMsg : public DPSDKCBMessage
{
public:
	AlarmPicPathMsg(void);
	virtual ~AlarmPicPathMsg(void);

public:	
	// request
	char			alarmId[DPSDK_ALARMCODE_LEN];                //报警ID 
	char			picPath[DPSDK_FILENAME_LEN];				//手抓图片的图片路径，取路径长度为256
};

// 获取所有用户通讯录
class QueryAllUserExtInfoMsg : public DPSDKCBMessage
{
public:
	QueryAllUserExtInfoMsg(void);
	virtual ~QueryAllUserExtInfoMsg(void);

public:
	// request
	//response
	//#include "XMLHelper/UserExtInfoHelper.hpp"
	char* szMessage;
	int nLen;

};

// 由客户端发出报警联动信息
class DPSDK_API SendAppAlarmMsg : public DPSDKCBMessage
{
public:
	SendAppAlarmMsg(void);
	virtual ~SendAppAlarmMsg(void);

public:
	// request
	//请参考#include "XMLHelper/AppAlarmHelper.hpp" 进行编码操作
	char*		szMessage;								// 正文
};

//查询RFID报警
class DPSDK_API QueryRFIDAlarmMsg : public ServerBaseMsg
{
public:
	QueryRFIDAlarmMsg();
	virtual ~QueryRFIDAlarmMsg();

public:
	//request
	AlarmQueryInfo_t	queryInfo;							// 报警查询信息
	uint32_t			firstNum;							// 开始序号
	uint32_t			queryCount;							// 查询数量
	char				szSwLabel[DPSDK_CHAR_LEN_32];		// 超声波探测标签
	char				szElecLabel[DPSDK_CHAR_LEN_32];		// 车用电子标签

	//response
	uint32_t			infoCount;							// 返回实际报警条数
	ADSRFIDAlarmInfo_t*	pAlarmInfo;							// 指向报警信息数据
};

typedef struct DPSDK_API tagFaceAttendanceRequest
{
	char					 szCameraId[DPSDK_CHL_ID_LEN];		// 人脸识别设备的指定通道ID
	long					 requestFlag;						// 用户自定义的请求标记，无特殊限制
	uint32_t				 operateType;						// 操作类型（添加/修改及删除）1.modify 2.delete 3.add
	char*					 data;								// 操作的数据
	uint32_t				 len;								// 数据长度

	int						 chanId;                            //通道号
	char					 szStaffId[DPSDK_CHL_ID_LEN ];		//工号


	tagFaceAttendanceRequest()
	{
		memset(szCameraId, 0, sizeof(szCameraId));
		memset(szStaffId, 0, sizeof(szStaffId));

		requestFlag = 0;
		operateType = 0;
		data = NULL;
		len = 0;
		chanId = 0;
	}
}FaceAttendanceRequest_t;

//操作人脸库(增删改)
class DPSDK_API OperateFaceCongnitionAttendanceMsg : public FaceBaseMsg
{
public:
	OperateFaceCongnitionAttendanceMsg();
	virtual ~OperateFaceCongnitionAttendanceMsg();

public:
	//request
	uint32_t			operateType;	// 1.modify 2.delete 3.add
	char*				personRegData;	// 人员信息
	uint32_t			dataLength;		// 信息长度

	long				requestFlag;	// 请求标记 一般为请求源的指针

	int					chanId;                            //通道号
	char				szStaffId[DPSDK_CHL_ID_LEN ];		//工号
};

//////////////////////////////////////////////////////////////////////////

class DPSDK_API IDPSDKAlarm : public IDPSDKFuncBase
{															
public:
	/** 获取预案列表.
		@return												异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int GetSchemeList(bool bGetAllScheme = false) = 0;

	/** 获取预案列表.
		@param dpsdk_alarmScheme_query_mode_e nParam		预案获取模式							
		@return												异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int GetSchemeListEx(dpsdk_alarmScheme_query_mode_e nParam  = ALARM_SCHEME_USER_MODE  ) = 0;

	/** 获取报警预案文件.
		@param uint32_t id									预案数据库id
		@return												异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int GetSchemeFile(uint32_t id) = 0;

	/** 删除报警预案.
		@param uint32_t id									预案数据库id
		@return												异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int DelSchemeFile(uint32_t id, bool bNotifyAll=false) = 0;

	/** 保存报警预案信息.
		@param uint32_t id									预案数据库id,第一次传0
		@param const char* schemeName						预案名称	
		@param dpsdk_alarmScheme_status_e status			预案开关
		@param uint32_t templateId							时间模板id
		@param const char* desc								预案描述
		@param const char* data								预案内容
		@param uint32_t len									
		@return												异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int SaveSchemeFile(uint32_t id, const char* schemeName, dpsdk_alarmScheme_status_e status, uint32_t templateId, const char* desc, const char* data, uint32_t len,bool bNotifyAll = false) = 0;
	
	/**	获取自定义日期模板.
		@param uint32_t id									时间模板id，默认0表示获取所有
		@return												异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int GetCustomTimeTemplate(uint32_t id = 0) = 0;

	/**	获取显示等级报警类型信息
		@return												异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int GetShowLevelAlarmType() = 0;
	
	/**	获取自定义报警类型信息
		@param dpsdk_alarm_language_type_e nLanguage		请求语言类型
		@return												异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int GetCustomAlarmType(dpsdk_alarm_language_type_e nLanguage = ALARM_LANGUAGE_UNKNOWN) = 0;

	/**	获取系统报警类型信息
		@return												异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int GetSystemAlarmType() = 0;

	/** 推送报警源信息.
		@param const char* alarmEnable						报警源信息
		@param uint32_t len									报警源信息长度
		@return												异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int SetAlarmEnable(const char* alarmEnable, uint32_t len) = 0;

	/** 设置报警接收能力.
		@param int nAlarmAcceptNum							报警接收条数设置：0：不能接收，>0：能接受的条数
		@return												异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int SetAlarmAcceptCapacity( int nAlarmAcceptNum ) = 0;

	/** 查询报警信息数量.
		@param AlarmQueryInfo_t& queryInfo					报警查询基本信息
		@param uint32_t queryType							查询类型(0:查询数量，1:查询计划名称(IVS-V))
		@param const char* planName							计划名称（IVS-V）
		@return												异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int QueryAlarmCount(AlarmQueryInfo_t& queryInfo, uint32_t queryType, const char* planName) = 0;

	/** 查询报警.
		@param AlarmQueryInfo_t& queryInfo					报警查询基本信息
		@param uint32_t firstNum							开始序号
		@param uint32_t queryCount							查询数量
		@param const char* planName							计划名称（IVS-V）
		@return												异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int QueryAlarm(AlarmQueryInfo_t& queryInfo, uint32_t firstNum, uint32_t queryCount, const char* planName) = 0;

	/** 查询综合报警 DSS-P750.
	@param AlarmQueryInfo_t& queryInfo						报警查询基本信息
		@param uint32_t alarmType							报警大类类型
		@param uint32_t snIndex								过滤值
		@param uint32_t firstNum							开始序号
		@param uint32_t queryCount							查询数量
		@return												异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int QueryZhAlarm(AlarmQueryInfo_t& queryInfo, uint32_t alarmType, uint32_t snIndex,uint32_t firstNum, uint32_t queryCount)= 0;

	/** 出入门禁查询.
		@param const char* szDepId							组织节点Id
		@param int64_t timeBegin							开始时间
		@param int64_t timeEnd								结束时间
		@return												异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int QueryDoorInAndOutInfo(const char* szDepId, int64_t timeBegin, int64_t timeEnd) = 0;

	/** 通知预案失效.
		@param int64_t schemeID								预案ID
		@param uint32_t notifyType							变更类型： (7)所有信息（时间段索引、报警源、动作）,(1)时间段索引,(2)报警源,(4)动作或其他组合.
		@return												异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int NotifySchemeInvalidate(int64_t schemeID, uint32_t notifyType) = 0;

	/** 报警确认.
		@param AlarmConfirmInfo_t& confirmInfo				报警确认信息
		@return												异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int NotifyConfirmAlarm(AlarmConfirmInfo_t& confirmInfo) = 0;

	/** 查询智能报警图片.
		@param dpsdk_operator_ftp_type_e optype				ftp操作类型
		@param const char* szCameraId						摄像头ID
		@param const char* url								图片所在ftp路径
		@param const char* path								本地存储图片路径
		@param const char* pUsername						用户名
		@param const char* pPwd								密码
		@return												异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int QueryIvsbAlarmPic(dpsdk_operator_ftp_type_e optype, const char* szCameraId, const char* url, const char* path, dpsdk_ftp_transport_mode_e mode = MODE_EPSV, const char* pUserName = NULL, const char* pPwd = NULL) = 0;

	//*******************************************人脸识别相关*********************************************
	/** 大图抽取人脸图片
		@param const char* szCameraId						人脸识别设备的指定通道ID
		@param long requestFlag								用户自定义的请求标记，无特殊限制
		@param char* picData								图片数据
		@param uint32_t nFileLength							图片文件大小
		@param uint32_t nPicWidth							图片宽度
		@param uint32_t nPicHeight							图片高度
		@return												异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int ExtractFacePic(const char* szCameraId, long requestFlag, char* picData, uint32_t nFileLength, uint32_t nPicWidth, uint32_t nPicHeight) = 0;

	/** 根据查询条件，获取人脸库中匹配的数量
		@param const char* szCameraId						人脸识别设备的指定通道ID
		@param long requestFlag								用户自定义的请求标记，无特殊限制
		@param const char* data								查询条件
		@param uint32_t len									查询条件的数据长度
		@return												异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int QueryFaceCount(const char* szCameraId, long requestFlag, const char* data, uint32_t len) = 0;

	/** 根据查询人脸库后获取到的Session，获取指定区间的匹配数据
		@param const char* szCameraId						人脸识别设备的指定通道ID
		@param uint32_t nQuerySession						查询匹配数目时获取到的Session
		@param uint32_t nStartIndex							起始数据索引
		@param uint32_t nQueryNum							数据条数
		@return												异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int QueryFaceData(const char* szCameraId, uint32_t nQuerySession, uint32_t nStartIndex, uint32_t nQueryNum) = 0;

	/** 人脸注册数据操作
		@param const char* szCameraId						人脸识别设备的指定通道ID
		@param long requestFlag								用户自定义的请求标记，无特殊限制
		@param uint32_t operateType,						操作类型（添加/修改及删除）
		@param const char* data								操作的数据
		@param uint32_t len									数据长度
		@return												异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int OperateFaceLib(const char* szCameraId, long requestFlag, uint32_t operateType, const char* data, uint32_t len) = 0;

	/** 断开指定的人脸库查询Session
		@param const char* szCameraId						人脸识别设备的指定通道ID
		@param uint32_t nQuerySession						查询匹配数目时获取到的Session
		@return												异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int StopFaceQuery(const char* szCameraId, uint32_t nQuerySession) = 0;

	/** 根据查询条件，获取人脸识别报警的匹配数量
		@param const char* szCameraId						人脸识别设备的指定通道ID
		@param long requestFlag								用户自定义的请求标记，无特殊限制
		@param int64_t nStartTime							报警时间的开始区间
		@param int64_t nEndTime								报警时间的结束区间
		@param const char* szAddress						报警地点
		@param uint32_t nAlarmType							报警类型（黑白名单报警）
		@return												异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int QueryIvsfAlarmCount(const char* szCameraId, long requestFlag, int64_t nStartTime, int64_t nEndTime, const char* szAddress, uint32_t nAlarmType) = 0;

	/** 根据查询人脸识别报警获取到的Session，获取指定区间的匹配数据
		@param const char* szCameraId						人脸识别设备的指定通道ID
		@param uint32_t nQuerySession						查询匹配数目时获取到的Session
		@param uint32_t nStartIndex							起始数据索引
		@param uint32_t nQueryNum							数据条数
		@return												异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int QueryIvsfAlarmData(const char* szCameraId, uint32_t nQuerySession, uint32_t nStartIndex, uint32_t nQueryNum) = 0;

	/** 断开指定的人脸识别报警查询Session
		@param const char* szCameraId						人脸识别设备的指定通道ID
		@param uint32_t nQuerySession						查询匹配数目时获取到的Session
		@return												异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int StopIvsfAlarmQuery(const char* szCameraId, uint32_t nQuerySession) = 0;

	/** 获取单条人脸识别报警的所有图片数据
		@param const char* szCameraId						人脸识别设备的指定通道ID
		@param long requestFlag								用户自定义的请求标记，无特殊限制
		@param const char* data								单条人脸识别报警的所有图片信息
		@param uint32_t len									图片信息长度
		@return												异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int GetIvsfAlarmPic(const char* szCameraId, long requestFlag, const char* data, uint32_t len) = 0;

	/** 通过URL获取图片
		@param long RequestFlag								
		@param const char* szUrl							ftp服务器存储数据的相对url
		@param const char* szPath							本地上传或者下载后的图片的地址
		@return												异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int GetIvsfPicByUrl(long RequestFlag, const char* szUrl, const char* szPath) = 0;

	/** 人脸注册数据操作
		@param FaceAttendanceRequest_t						请求数据
		@return												异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int OperateFaceCongnitionAttendance(FaceAttendanceRequest_t* pFaceRequest) = 0;
	//*******************************************人脸识别相关 end*********************************************

    /** 客户端主动发起报警.
		@param const char* szCameraId						摄像头ID
		@param dpsdk_alarm_type_e enAlarmType				报警类型
		@param dpsdk_event_type_e enStatus					报警状态
		@param int64_t nAlarmTime							报警时间
		@param const char* szMsg							额外信息
		@return												异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int SendAlarmToServer(const char* szCameraId, dpsdk_alarm_type_e enAlarmType, dpsdk_event_type_e enStatus, int64_t nAlarmTime, const char* szMsg) = 0;
	
	/** 报警消息发送.
		@param AlarmMessageInfo_t& message					报警信息
		@return												异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int RequestAlarmMessage(AlarmMessageInfo_t& message) = 0;
	
	/**组员将报警转移给组长处理
	*/
	virtual int TranferAlarmToLeads(ADSTransferAlarmMsg* pMsg) = 0;

	/** 手动抓图报警信息发送.
	@param uint32_t		alarmId								报警ID
	@param char			picPath[DPSDK_FILENAME_LEN]			手抓图片的图片路径
	@return													异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int UpdateAlarmPicPath(const char* alarmId, const char* picPath) = 0; 

	/** 查询用户信息
	@return												用户信息XML,使用UserExtInfoHelper::UserExtInfoList解析
	*/
	virtual int QueryAllUserExtInfo() = 0;
	/** 发送报警（短信）.
		@param szXml										发送的短信，使用AppAlarmHelper编码
		@return												异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int SendAppAlarm(const char* szXml) = 0;

	/** 查询RFID报警.
		@param AlarmQueryInfo_t& queryInfo					报警查询基本信息
		@param uint32_t firstNum							开始序号
		@param uint32_t queryCount							查询数量
		@param const char* pSwLabel							超声波探测标签
		@param const char* pElecLabel						车用电子标签
		@return												异步顺序码,用于事件回调时,与应答事件匹配
	*/
	virtual int QueryRFIDAlarm(AlarmQueryInfo_t& queryInfo, uint32_t firstNum, uint32_t queryCount, const char* pSwLabel, const char* pElecLabel) = 0;

protected:
	virtual ~IDPSDKAlarm(void){}
};
//////////////////////////////////////////////////////////////////////////

END_NAMESPACE_DPSDK

#endif
