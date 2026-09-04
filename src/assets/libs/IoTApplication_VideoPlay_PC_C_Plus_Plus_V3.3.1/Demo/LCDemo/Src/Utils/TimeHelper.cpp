#include <QDateTime>
#include "TimeHelper.h"

TimeHelper::TimeHelper()
{

}

TimeHelper::~TimeHelper()
{

}


QString TimeHelper::GetBeginDateTime()
{
    return QDate::currentDate().toString("yyyy-MM-dd") + " 00:00:00";
}

QString TimeHelper::GetCurrentDateTime()
{
    return QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
}


uint TimeHelper::GetCurrentTimeStamp()
{
    return QDateTime::currentDateTime().toTime_t();
}

QString TimeHelper::GetDataTimeByTimeStamp(uint timeStamp)
{
    return QDateTime::fromTime_t(timeStamp).toString("yyyy-MM-dd hh:mm:ss");
}
