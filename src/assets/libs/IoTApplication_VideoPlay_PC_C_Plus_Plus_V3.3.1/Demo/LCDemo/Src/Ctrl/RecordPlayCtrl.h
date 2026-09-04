#ifndef RECORDPLAYCTRL_H
#define RECORDPLAYCTRL_H

#include <QObject>
#include "Ctrl/PlayCtrl.h"
#include "Model/RecordInfo.h"

class RecordPlayCtrl : public PlayCtrl
{
    Q_OBJECT

public:
    RecordPlayCtrl();
    ~RecordPlayCtrl();

    int playCloudRecord(int deviceIndex, int recordIndex);
    int playDeviceRecord(int deviceIndex, int recordIndex);
    int stopPlay();

    int seek(long seconds);
	int setPlaySpeed(float speed);
    int pause();
    int resume();

    inline void setRecordType(RECORD_TYPE_E type){ m_recordType = type; };
    inline RECORD_TYPE_E getRecordType(){ return m_recordType; };

    inline QString getRecordBeginTime()
    {
        if (NULL == m_recordInfo)
        {
            return "";
        }
        return m_recordInfo->beginTime;
    }

    inline QString getRecordEndTime()
    {
        if (NULL == m_recordInfo)
        {
            return "";
        }
        return m_recordInfo->endTime;
    }

protected:
    virtual void onPlayCloudRecordResult(int index, int code, int resultSource);

    virtual void onPlayFinished(int index);
    virtual void onPlayerTime(int index, long time);

private:
    RECORD_TYPE_E      m_recordType;
    const RECORD_INFO *m_recordInfo;

signals:
    void sgnPlayerTime(long time);
};

#endif // RECORDPLAYCTRL_H
