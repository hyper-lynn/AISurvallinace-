#ifndef TIMEHELPER_H
#define TIMEHELPER_H

#include <QString>

class TimeHelper
{
public:
    TimeHelper();
    ~TimeHelper();

public:
    static QString GetBeginDateTime();
    static QString GetCurrentDateTime();
    static uint    GetCurrentTimeStamp();
    static QString GetDataTimeByTimeStamp(uint timeStamp);

};

#endif // TIMEHELPER_H
