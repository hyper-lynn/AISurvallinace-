#ifndef RECORDLISTCTRL_H
#define RECORDLISTCTRL_H

#include <QObject>
#include <QDate>
#include "Src/Model/RecordInfo.h"
#include "Src/Utils/global.h"
#include "Src/Ctrl/DevicesListCtrl.h"
#include "Src/Model/ThreadInfo.h"

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
    * 异步查询指定设备指定日期录像信息
    * @param   [in] int deviceIndex     设备index，由设备列表页提供
    * @param   [in] const QDate & date  待查询时间
    * @return  int
    */
    int getRecordInfoAsyn(int deviceIndex, const QDate &date);
    int getRecordInfo(const QString &deviceId, int channelId, const QDate &date);

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
    ThreadCtrl             *m_threadCtrl;

    /**
    * 获取某个日期的开始时间和结束时间
    * @param   [in] QDate date          待查询日期
    * @param   [OUT] QString & beginTime
    * @param   [OUT] QString & endTime
    * @return  void
    */
    void getBeginTimeAndEndTime(QDate date, QString &beginTime, QString &endTime);

signals:
    void sgnRecordThreadResult(int result);
};

#endif // RECORDLISTCTRL_H
