#ifndef RECORDLISTCTRL_H
#define RECORDLISTCTRL_H

#include <QObject>
#include <QDate>
#include "Model/RecordInfo.h"
#include "Utils/global.h"
#include "Ctrl/DevicesListCtrl.h"
#include "Model/ThreadInfo.h"
#include <QJsonObject>

class ThreadCtrl;
class RecordListCtrl : public QObject
{
    Q_OBJECT

public:
    typedef enum{ERR_SUCCESS = 0, ERR_SEARCHING = -1, ERR_GET_CHANNELINFO = -2,}GET_RECORD_ERR_E;
public:
    ~RecordListCtrl();
    static RecordListCtrl* getInstance();

    inline void setRecordType(RECORD_TYPE_E type){ m_recordType = type; };
    inline RECORD_TYPE_E getRecordType(){ return m_recordType; };
    void clearRecordList();

    /**
/**
* Get device cloud record list
* @param   [in] int deviceIndex     Device index from device list
* @param   [in] const QDate & date  Query date
    */
    int getRecordInfoAsyn(int deviceIndex, const QDate &date);
	int getRecordInfo(const QString &deviceId, int channelId, std::string playInfo, const QDate &date, ThreadCtrl* ptr);

	void setRecordInfoList(RECORD_INFO_LIST recordInfoList, int recordSize);

    inline const RECORD_INFO_LIST* getRecordInfoList(){ return &m_recordInfoList; };
    inline QString getDeviceId()
    {
        if (NULL == m_channelInfo)
        {
            return "";
        }
        return m_channelInfo->deviceId;
    }

    inline QString getChannelName()
    {
        if (NULL == m_channelInfo)
        {
            return "";
        }
        return m_channelInfo->channelName;
    };
    const RECORD_INFO* getRecordInfoByIndex(int index);

private:
    RecordListCtrl();

    RECORD_TYPE_E           m_recordType;
    QString                 m_token;
    RECORD_INFO_LIST        m_recordInfoList;
    const ChannelInfo      *m_channelInfo;
	const IOTDeviceList	   *m_iotDevList;
    ThreadCtrl             *m_threadCtrl;

    /**
/**
* Get device record list by date
* @param   [in] QDate date          Query date
    * @param   [OUT] QString & endTime
    * @return  void
    */
    void getBeginTimeAndEndTime(QDate date, QString &beginTime, QString &endTime);

signals:
    void sgnRecordThreadResult(int result);
};

#endif // RECORDLISTCTRL_H
