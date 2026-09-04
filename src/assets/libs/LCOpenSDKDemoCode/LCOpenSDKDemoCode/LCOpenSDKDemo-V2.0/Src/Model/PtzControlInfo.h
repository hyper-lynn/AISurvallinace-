#ifndef PTZCONTROLINFO_H
#define PTZCONTROLINFO_H

#include <QObject>


typedef struct PtzCtrlParameters
{
	QString         deviceId;
	int             channelId;
	QString         operate;
	long            duration;
	QString         playToken;
}PTZ_CONTROL_PARAMETERS;

typedef enum
{
	PTZ_CONTROL_UP,
	PTZ_CONTROL_LEFT,
	PTZ_CONTROL_DOWN,
	PTZ_CONTROL_RIGHT,
	PTZ_CONTROL_LEFTUP,
	PTZ_CONTROL_LEFTDOWN,
	PTZ_CONTROL_RIGHTUP,
	PTZ_CONTROL_RIGHTDOWN,
}PTZ_CONTROL_DIRECTION_E;

typedef enum
{
	/* 单步控制 */
	TYPE_SINGLE_STEP,

	/* 开始长按 */
	TYPE_LONGPRESS_PRESS,

	/* 结束长按 */
	TYPE_LONGPRESS_RELEASE,
}PTZ_CTRL_TYPE_E;

class PtzControlInfo : public QObject
{
	Q_OBJECT

public:
	PtzControlInfo(QObject *parent);
	~PtzControlInfo();

private:

};

#endif // PTZCONTROLINFO_H
