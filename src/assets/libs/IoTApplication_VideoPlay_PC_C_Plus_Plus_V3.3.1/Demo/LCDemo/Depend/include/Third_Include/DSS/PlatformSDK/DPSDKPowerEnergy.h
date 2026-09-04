/**
动环设备接入
*/

#ifndef	DPSDKPOWERENERGY_H
#define DPSDKPOWERENERGY_H

#include "DPSDK.h"
#include <vector>

BEGIN_NAMESPACE_DPSDK

// 动环主机资源（传感器）类型平台定义，即动环外接传感器类型和EnumPESourceType协议保持一致
typedef enum
{
	// 景德镇华润燃气项目
	PE_POWER_INTERRUPT           = 1700,			// 市电中断
	PE_POWER_ENABLED             = 1701,			// 市电启用
	PE_INFRARED_DETECT           = 1702,			// 红外探测 
	PE_GAS_OVER_SECTION          = 1703,			// 燃气浓度
	PE_FLOW_OVER_SECTION         = 1704,			// 瞬时流量
	PE_TEMPERATURE_SECTION		 = 1705,			// 管道温度 
	PE_PRESSURE_SECTION			 = 1706,			// 管道压力

	// 系统工程动环增加报警类型
	// 开关量，不可控
	PE_SCS_SWITCH_START=1800,
	PE_SCS_INFRARED,								// 红外对射
	PE_SCS_SMOKE,									// 烟感
	PE_SCS_WATER,									// 水浸
	PE_SCS_COMPRESSOR,								// 压缩机故障
	PE_SCS_OVERLOAD,								// 过载
	PE_SCS_BUS_ANOMALY,								// 母线异常
	PE_SCS_LIFE,									// 寿命
	PE_SCS_SOUND,									// 声音
	PE_SCS_TIME,									// 时钟
	PE_SCS_FLOW_LOSS,								// 气流丢失
	PE_SCS_FUSING,									// 熔断
	PE_SCS_BROWN_OUT,								// 掉电
	PE_SCS_LEAKING,									// 漏水
	PE_SCS_JAM_UP,									// 堵塞
	PE_SCS_TIME_OUT,								// 超时
	PE_SCS_REVERSE_ORDER,							// 反序
	PE_SCS_NETWROK_FAILURE,							// 组网失败
	PE_SCS_UNIT_CODE_LOSE,							// 机组码丢失
	PE_SCS_UNIT_CODE_DISMATCH,						// 机组码不匹配
	PE_SCS_FAULT,									// 故障
	PE_SCS_UNKNOWN,									// 未知
	PE_SCS_CUSTOM,									// 自定义
	PE_SCS_NOPERMISSION,							// 无权限
	PE_SCS_INFRARED_DOUBLE,							// 红外双鉴
	PE_SCS_ELECTRONIC_FENCE,						// 电子围栏
	PE_SCS_UPS_MAINS,								// 市电正常市电异常
	PE_SCS_UPS_BATTERY,								// 电池正常电池异常
	PE_SCS_UPS_POWER_SUPPLY,						// UPS正常输出旁路供电
	PE_SCS_UPS_RUN_STATE,							// UPS正常UPS故障
	PE_SCS_UPS_LINE_STYLE,							// UPS类型为在线式UPS类  型为后备式
	PE_SCS_XC,										// 小车
	PE_SCS_DRQ,										// 断路器
	PE_SCS_GLDZ,									// 隔离刀闸
	PE_SCS_JDDZ,									// 接地刀闸
	PE_SCS_IN_END,

	// 开关量，可控
	PE_SCS_DOOR_SWITCH = 1850,						// 门禁控制器开关
	PE_SCS_UPS_SWITCH,								// UPS开关
	PE_SCS_DBCB_SWITCH,								// 配电柜开关
	PE_SCS_ACDT_SWITCH,								// 空调开关
	PE_SCS_DTPW_SWITCH,								// 直流电源开关
	PE_SCS_LIGHT_SWITCH,							// 灯光控制器开关
	PE_SCS_FAN_SWITCH,								// 风扇控制器开关
	PE_SCS_PUMP_SWITCH,								// 水泵开关
	PE_SCS_BREAKER_SWITCH,							// 刀闸开关
	PE_SCS_RELAY_SWITCH,							// 继电器开关
	PE_SCS_METER_SWITCH,							// 电表开关
	PE_SCS_TRANSFORMER_SWITCH,						// 变压器开关
	PE_SCS_SENSOR_SWITCH,							// 传感器开关
	PE_SCS_RECTIFIER_SWITCH,						// 整流器
	PE_SCS_INVERTER_SWITCH,							// 逆变器
	PE_SCS_PRESSURE_SWITCH,							// 压力开关
	PE_SCS_SHUTDOWN_SWITCH,							// 关机
	PE_SCS_WHISTLE_SWITCH,							// 警笛
	PE_SCS_SWITCH_END,

	// 模拟量
	PE_SCS_ANALOG_START = 1880,
	PE_SCS_TEMPERATURE,								// 温度
	PE_SCS_HUMIDITY,								// 湿度
	PE_SCS_CONCENTRATION,							// 浓度
	PE_SCS_WIND,									// 风速
	PE_SCS_VOLUME,									// 容量
	PE_SCS_VOLTAGE,									// 电压
	PE_SCS_ELECTRICITY,								// 电流
	PE_SCS_CAPACITANCE,								// 电容
	PE_SCS_RESISTANCE,								// 电阻
	PE_SCS_CONDUCTANCE,								// 电导
	PE_SCS_INDUCTANCE,								// 电感
	PE_SCS_CHARGE,									// 电荷量
	PE_SCS_FREQUENCY,								// 频率
	PE_SCS_LIGHT_INTENSITY,							// 发光强度(坎)
	PE_SCS_PRESS,									// 力（如牛顿，千克力）
	PE_SCS_PRESSURE,								// 压强（帕，大气压）
	PE_SCS_HEAT_TRANSFER,							// 导热（瓦每平米）
	PE_SCS_THERMAL_CONDUCTIVITY,					// 热导（kcal/(m*h*℃)）
	PE_SCS_VOLUME_HEAT,								// 比容热（kcal/(kg*℃)）
	PE_SCS_HOT_WORK,								// 热功（焦耳）
	PE_SCS_POWER,									// 功率（瓦）
	PE_SCS_PERMEABILITY,							// 渗透率（达西）
	PE_SCS_PROPERTION,								// 比例（包括电压电流变比，功率因素，负载单位为%） 
	PE_SCS_ENERGY,									// 电能（单位为J）
	PE_SCS_ANALOG_END,

	AE_PE_TYPE_BEGIN               = 2000,

	PE_DOOR_MAGNETISM			   = 2200,			// 门磁
	PE_PASSIVE_INFRARED			   = 2201,			// 被动红外
	PE_GAS						   = 2202,			// 气感
	PE_INITIATIVE_INFRARED		   = 2203,			// 主动红外
	PE_GLASS_CRASH				   = 2204,			// 玻璃破碎
	PE_EXIGENCY_SWITCH			   = 2205,			// 紧急开关
	PE_SHAKE					   = 2206,			// 震动
	PE_BOTH_JUDGE				   = 2207,			// 双鉴（红外+微波）
	PE_THREE_TECHNIC			   = 2208,			// 三技术
	PE_CALL_BUTTON                 = 2209,			// 呼叫按钮
	PE_SENSE_OTHER                 = 2210,			// 其他
	AE_PE_TYPE_END                 = 2400,

	// 以下三种为程序自定义，和协议定义的动环类型没有关系，如果需要加入新的动环类型，在这个前面增加
	PE_TYPE_UNKNOWN,								// 未知动环类型==>程序上定义的
	PE_TYPE_ALL,									// 所有的动环==>程序上定义,勿用
	PE_TYPE_OTHERS,									// 其他的动环==>程序上定义,勿用
}EnumPEType;

// 动环上报数据状态
typedef enum
{
	PE_STATUE_UNKNOWN				= -1,			// 未知
	PE_STATUE_NORMAL				= 0,			// 正常
	PE_STATUE_EXCEPTION				= 1,			// 异常，包括：2:超过阈值1；3:超过阈值2；4:超过阈值3；5:超过阈值4；
	PE_STATUE_USELESS				= 2,			// 无效
}Pe_Date_Statue;

typedef struct DPSDK_API _PowerEnergyDataReport				// 实时数据
{
	char        chnId[DPSDK_CHL_ID_LEN];
	char        time[DPSDK_CHL_ID_LEN];
	int         isAlarm;							// 0实时数据，1告警
	double      dataVal;
	int			level;								// 告警级别
	char        desc[DPSDK_PE_DESC];				// 根据不同数据类型填不同的值
	char		unit[DPSDK_CHL_ID_LEN];				// 单位符号，如，湿度 “%”，温度“℃”；若值为“1”，表示日志信息（如门禁控制器开门动作）；若值为“2”，表示门等开关设备状态的数据，此时val若为“1”为开，若为0表关。
	int64_t		_time;								// 采集时间，int64_t类型，如果time为空，则采集时间采用这个字段，为兼容以前版本
	char		url[DPSDK_TAG_URL_LEN];				// 实时数据、报警图片url
	_PowerEnergyDataReport()
	{
		memset(chnId, 0, DPSDK_CHL_ID_LEN);
		memset(time, 0, DPSDK_CHL_ID_LEN);
		isAlarm = 0;
		dataVal = 0;
		level = 0;
		memset(desc, 0, DPSDK_PE_DESC);
		memset(unit, 0, DPSDK_CHL_ID_LEN);
		_time = 0;
		memset(url, 0, DPSDK_TAG_URL_LEN);
	}
}PowerEnergyDataReport;

// 动环实时数据上报
class DPSDK_API PowerEnergyDataReportMsg : public DPSDKCBMessage
{
public:
	PowerEnergyDataReportMsg(void);
	virtual ~PowerEnergyDataReportMsg(void){}

public:

	std::string	_devId;								// 设备类型
	int			_devTypeId;							// 资产类型  能源线这个值类型参考：EnumPEType枚举，基线参考DCMUI定义的枚举
	char		szId[DPSDK_CHL_ID_LEN];				// 可以暂时不用

	std::vector<PowerEnergyDataReport> vecRealdata;	// 动环实时数据
};

// 动环走PES下发命令的消息 的基类
class DPSDK_API PowerEnergyPEScmdBaseMsg : public DPSDKCBMessage
{
public:
	PowerEnergyPEScmdBaseMsg( int cmd = DPSDK_CMD_UNKNOWN,int msgType = DPSDK_MSG_REQUEST);
	~PowerEnergyPEScmdBaseMsg(){}

	char _ChnId[DPSDK_CHL_ID_LEN];					// 通道ID
};

// 动环开关控制
class DPSDK_API PowerEnergyCtrlMsg : public PowerEnergyPEScmdBaseMsg
{
public:
	PowerEnergyCtrlMsg(void);
	virtual ~PowerEnergyCtrlMsg(void){}
public:
	char	szId[DPSDK_CHL_ID_LEN];					// 设备/通道ID==>应该是设备id
	int		_op;									// 控制开(1)或关(0)
	int		_label;									// 表示控制的对象0：id为资产，1：id为资源

	// respone
};

// 动环开或者关状态获取
class DPSDK_API PowerEnergyGetStatusMsg : public PowerEnergyPEScmdBaseMsg
{
public:
	PowerEnergyGetStatusMsg(void);
	virtual ~PowerEnergyGetStatusMsg(void){}

public:
	// _ChnId在PowerEnergyPEScmdBaseMsg中
	char	_devId[DPSDK_DEV_ID_LEN];				// 应该是设备id
	int		_label;									// 表示控制的对象0：id为资产，1：id为资源

	// respone
	int		_res;									// 0表成功， 1表示获取失败
	int		_devType;								// 资产类型
	char	_time[DPSDK_PE_TIME];					// 时间
	int		_var;									// 状态值 1表示开， 0表示关
	char	_des[DPSDK_FILENAME_LEN];				// 描述 
};

// 查询动环数据上报图片
class DPSDK_API QueryPEPicMsg : public DPSDKCBMessage
{
public:
	QueryPEPicMsg(void);
	virtual ~QueryPEPicMsg(void) {}

public:
	dpsdk_operator_ftp_type_e	opType;						// 操作类型，请参考dpsdk_operator_ftp_type_e
	char						cameraId[DPSDK_CHL_ID_LEN];	// 摄像头ID
	char						url[DPSDK_TAG_URL_LEN];		// ftp服务器存储数据的相对url
	char						path[DPSDK_TAG_PATH_LEN];	// 本地上传或者下载后的图片的地址
	dpsdk_ftp_transport_mode_e	mode;						// 文件传输模式
};

// 查询动环历史数据数量
class DPSDK_API QueryPEDataCountMsg : public DPSDKCBMessage
{
public:
	QueryPEDataCountMsg(void);
	virtual ~QueryPEDataCountMsg(void) {}

public:
	char		_devCode[DPSDK_DEV_ID_LEN];			// 设备ID
	int			_chnnelNo;							// 通道序号，==-1时表示是查询这个设备下所有通道的历史数据
	int64_t		_begTime;							// 开始时间
	int64_t		_endTime;							// 结束时间
	int			_type;								// 传感器类型EnumPEType
	int			_count;								// 数量
};

// 历史数据结构体
typedef struct DPSDK_API PeData
{
	char		devCode[DPSDK_DEV_ID_LEN];
	int			unitSeq;
	int			channelSeq;
	int			type;								// 探测器类型，参考EnumPEType类型
	float		value;								// 探测器数值
	char		picUrl[DPSDK_TAG_URL_LEN];			// 图片Url
	int			dataStatus;							// 数据状态。 -1:未知；0:正常；1:数据无效(超过量程)；2:超过阈值1；3:超过阈值2；4:超过阈值3；5:超过阈值4；
	int64_t		date;								// 记录日期
}PeData_t;

// 查询动环历史数据(走新协议)
class DPSDK_API QueryPEDataMsg : public DPSDKCBMessage
{
public:
	QueryPEDataMsg(void);
	virtual ~QueryPEDataMsg(void) {}

public:
	char		_devCode[DPSDK_DEV_ID_LEN];			// 设备ID
	int			_chnnelNo;							// 通道序号，==-1时表示是查询这个设备下所有通道的历史数据
	int64_t		_begTime;							// 开始时间
	int64_t		_endTime;							// 结束时间
	int			_type;								// 传感器类型EnumPEType
	int			_startIndex;						// 查询开始索引号
	int			_count;								// 要获取的数据记录数

	std::vector<PeData_t> _infoVec;					// 返回的数据集
};

class DPSDK_API IDPSDKPowerEnergy : public IDPSDKFuncBase
{
public:
	/**	动环开关控制
	@param char* devId								设备id
	@param char* chnId								通道id
	@param int cmd									控制开(1)或关(0)
	@param int label								表示控制的对象0：id为资产，1：id为资源
	==>动环概念 
	资产：对应7016中单元概念
	资源：对应通道
	*/
	virtual int SetSCSDevOrder(char* devId, char*chnId, int cmd, int label = 1) = 0;

	/**获取动环的当前状态，开或者关
	@param char* devId								设备id
	@param char* chnId								通道id
	@param int label								表示控制的对象0：id为资产，1：id为资源
	==>动环概念 
	资产：对应7016中单元概念
	资源：对应通道
	*/
	virtual int GetPeChnlStatus(const char* devId, const char*chnId, int label) = 0;

	/**查询动环图片.
	@param dpsdk_operator_ftp_type_e optype			ftp操作类型
	@param const char* szCameraId					摄像头ID
	@param const char* url							图片所在ftp路径
	@param const char* path							本地存储图片路径
	@return		
	*/
	virtual int QueryPePic(dpsdk_operator_ftp_type_e optype, const char* szCameraId, const char* url, const char* path, dpsdk_ftp_transport_mode_e mode = MODE_EPSV) = 0;

	/**查询动环历史数据数据量
	@param const char* devId						设备ID
	@param int channelNo							通道号
	@param int64_t begDate							开始时间
	@param int64_t endDate							结束时间
	@param int type = -1							探测器类型，默认值表示获取所有探测器的数据
	@return
	*/
	virtual int QueryPeDataCount(const char* devId, int channelNo, int64_t begDate, int64_t endDate, int type = -1) = 0;

	/**查询动环历史数据
	@param const char* devId						设备ID
	@param int channelNo							通道号
	@param int64_t begDate							开始时间
	@param int64_t endDate							结束时间
	@param int nStartIndex							查询起始序号
	@param int nCount								查询数据量
	@param int type = -1							探测器类型，默认值表示获取所有探测器的数据
	@return
	*/
	virtual int QueryPeData(const char* devId, int channelNo, int64_t begDate, int64_t endDate, int nStartIndex, int nCount, int type = -1) = 0;
};

END_NAMESPACE_DPSDK

#endif

