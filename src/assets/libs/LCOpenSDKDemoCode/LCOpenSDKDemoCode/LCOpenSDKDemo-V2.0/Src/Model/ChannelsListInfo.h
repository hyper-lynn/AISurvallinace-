#ifndef _CHANNELSLISTINFO_H_
#define _CHANNELSLISTINFO_H_

#include <QString>
#include <QList>


typedef struct _ChannelInfo_
{
	/* 设备信息 */
	QString     deviceId;                   //设备序列号
	QString     productId;                  //产品编号
	bool        canBeUpgrade;               //设备软件程序是否有新版本可以升级
	QString     accessType;                 //设备接入类型，PaaS-表示Paas程序接入、Lechange-表示乐橙非PaaS设备、Easy4IP表示Easy4IP程序设备、P2P表示P2P程序设备
	QString     deviceVersion;              //设备版本号
	QString     playToken;                  //设备播放码，opensdk使用
	QString     brand;                      //设备品牌信息：lechange-乐橙设备，general-通用设备
	QString     encryptMode;                //设备加密模式：0-设备默认加密 1-用户自定义加密
	QString     decryptKey;                 //加密秘钥
	QString     lastOffLineTime;            //设备最后离线时间
	QString     deviceName;                 //设备名称
	QString     devicePassword;             //设备密码
	QString     deviceStatus;               //设备状态
	QString     deviceModel;                //设备型号
	QString     catalog;                    //设备大类【NVR/DVR/HCVR/IPC/SD/IHG/ARC】
	QString     deviceAbility;              //设备能力集，逗号隔开
	int         channelNum;                 //设备最大支持接入的通道数
	QString     source;                     //权限类型：bind、 share
	bool        isSubDevice;                //是否为子设备
	QString     sdcardStatus;
	bool        tlsEnable;                  //是否开启TLS

	/* 通道信息 */
	QString     channelPicUrl;              //设备通道封面图，新设备可能不存在封面图，可上传设备通道封面图或者刷新设备封面图
	QString     csStatus;                   //云存储状态，notExist：未开通套餐，using：开通云存储且没有过期，expired：套餐过期
	QString     shareFunctions;             //分享权限下的权限字符串，逗号隔开
	int         channelId;                  //通道号
	QString     channelName;                //通道名称
	QString     channelAbility;             //通道能力集，逗号隔开
	QString     channelStatus;              //通道状态，online：在线，offline：离线，sleep：休眠，upgrading升级中
	QString     channelLastOffLineTime;     //通道最后离线时间
	bool        channelAlarmStatus;
	bool		multiFlag;					//是否是双目相机
	bool		movable;					//是否是移动镜头

	unsigned short  p2pPort;                //设备P2P端口号

	_ChannelInfo_()
	{
		canBeUpgrade = false;
		channelNum = 0;
		isSubDevice = false;
		channelId = 0;
		channelAlarmStatus = false;
		tlsEnable = false; 
		p2pPort = -1;
		multiFlag = false;
		movable = false;
	}
}ChannelInfo;

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

#endif /* _CHANNELSLISTINFO_H_ */