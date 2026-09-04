#ifndef __THREADINFO_H__
#define __THREADINFO_H__

#include <QObject>
#include <QDate>
#include "Model/PtzControlInfo.h"

typedef struct RecordListThreadParam 
{
    QString deviceId;
    int     channelId;
    QDate   date;
	std::string playInfo;

    RecordListThreadParam()
    {
        channelId = 0;
    }
}RECORD_LIST_THREAD_PARAM;

typedef struct PtzControlThreadParam 
{
    QString                 deviceId;
    int                     channelId;
    PTZ_CONTROL_DIRECTION_E direction;
    PTZ_CTRL_TYPE_E         type;
    void                   *user;
	std::string				playInfo;

    PtzControlThreadParam()
    {
        user = NULL;
        channelId = 0;
		playInfo = "";
    }
}PTZ_CONTROL_THREAD_PARAM;

#endif //__THREADINFO_H__