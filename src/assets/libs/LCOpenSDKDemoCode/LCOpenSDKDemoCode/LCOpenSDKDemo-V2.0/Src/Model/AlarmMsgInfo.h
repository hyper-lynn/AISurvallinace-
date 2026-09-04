#ifndef ALARMMSGINFO_H
#define ALARMMSGINFO_H

#include <QList>
#include <QStringList>

#define MAX_ALARM_MSG   10

typedef struct _AlarmMsgParameter_
{
	QString deviceId;
	int     channelId;
	QString beginTime;
	QString endTime;
	int     maxCount;

	_AlarmMsgParameter_()
	{
		channelId = 0;
		maxCount = 10;
	}

}AlarmMsgParameter;

typedef struct _AlarmMsgInfo_
{
	/** [int]报警类型 */
	int type;
	/** 缩略图URL */
	QString thumbUrl;
	/** 设备ID */
	QString deviceId;
	/** [long]消息ID */
	QString alarmId;
	/** [long]报警时间UNIX时间戳秒 */
	long long time;
	/** 报警图片url */
	QStringList picurlArray;
	/** 通道号 */
	int channelId;
	/** 设备或通道的名称 */
	QString Channelname;
	/** 报警时设备本地时间，格式如2014-12-12 12:12:12 */
	QString localDate;
	/** 镜头名称 */
	QString cname;
	/** 设备上报的信息 */
	QString message;
}AlarmMsgInfo;

typedef QList<AlarmMsgInfo*> AlarmMsgInfoList;

#endif // ALARMMSGINFO_H
