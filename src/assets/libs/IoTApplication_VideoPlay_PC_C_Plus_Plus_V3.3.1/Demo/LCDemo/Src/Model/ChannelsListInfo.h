#ifndef _CHANNELSLISTINFO_H_
#define _CHANNELSLISTINFO_H_

#include <QString>
#include <QList>

typedef struct _ChannelInfo_
{
    QString     deviceId;                   /** 设备ID */
    QString     name;                       /** 设备名称 */
    QString     deviceModel;                /** [O]设备型号 */
    int         status;                     /** [int]当前状态：0-离线�?-在线�?-升级�?*/
    QString     ability;                    /** [O]设备能力项，逗号隔开，如AlarmMD,AudioTalk,AlarmPIR,WLAN,VVP2P，详见乐橙开放平台设备协�?*/
    QString     version;                    /** 设备软件版本�?*/
    bool        canBeUpgrade;               /** [bool]是否有新版本可以升级 */
    int         encryptMode;                /** [int]加密模式 */
    QString     decryptKey;                 /** 加密秘钥 */

    int         platForm;                   /** [int]平台类型 */
    int         alarmStatus;                /** [int]报警布撤防状态，0-撤防�?-布防 */
    QString     channelName;                /** 通道名称 */
    QString     channelPicUrl;              /** 缩略图URL */
    QString     channelAbility;             /** 通道能力项，逗号隔开，如AlarmMD,AudioTalk,AlarmPIR,WLAN,VVP2P，详见乐橙开放平台设备协�?*/
    int         channelId;                  /** [int]通道�?*/
    bool        channelOnline;              /** [bool]是否在线 */
    int         csStatus;                   /** [int]云存储状态：-1-未开�?0-已失�?1-使用�?2-套餐暂停 */

    _ChannelInfo_()
    {
        status          = 0;
        canBeUpgrade    = false;
        encryptMode     = 0;
        platForm        = 0;
        alarmStatus     = 0;
        channelId       = 0;
        channelOnline   = false;
        csStatus        = 0;
    }
}ChannelInfo;


typedef struct _IOTChannels_
{
	std::string channelPicUrl;
	std::string csStatus;
	std::string shareFunctions;
	std::string channelId;
	std::string channelName;
	std::string channelAbility;
	std::string lastOffLineTime;
	std::string channelStatus;

	_IOTChannels_()
	{
		csStatus = "";
		shareFunctions = "";
		lastOffLineTime = "";
	}
}IOTChannels;


typedef struct _IOTDeviceList_
{
	std::string deviceId;
	std::string productId;
	bool		canBeUpgrade;
	std::string accessType;
	std::string deviceVersion;
	std::string brand;
	std::string encryptMode;
	std::string lastOffLineTime;
	std::string deviceName;
	std::string deviceStatus;
	std::string deviceModel;
	std::string catalog;
	std::string deviceAbility;
	int			channelNum;
	std::string source;
	std::string upgradeInfoVO;
	int			platForm;
	std::string decryptKey;
	std::string playInfo;
	QList<IOTChannels*> iotChannel;

	_IOTDeviceList_()
	{
		productId		= "";
		accessType		= "";
		brand			= "";
		lastOffLineTime = "";
		catalog			= "";
		channelNum		= 0;
		source			= "";
		upgradeInfoVO	= "";
	}
}IOTDeviceList;

typedef struct deviceAbility
{
    bool supportAudioTalk;
    bool supportPTZ;

    deviceAbility()
    {
        supportAudioTalk = false;
        supportPTZ = false;
    }
}DEVICE_ABILITY;

typedef QList<ChannelInfo*> ChannelInfoList;
typedef QList<IOTDeviceList*> IOTDeviceInfoList;

/** Mapping from view index to device index and channel index in the device list page */
typedef struct _ViewDeviceInfo_
{
	int deviceListIndex;  /** Index in m_IOTDeviceInfoList */
	int channelIndex;     /** Index in iotChannel, -1 means single-channel device (no specific channel) */
}ViewDeviceInfo;

#endif /* _CHANNELSLISTINFO_H_ */
