#ifndef RECORDINFO_H
#define RECORDINFO_H

#include <QString>

typedef enum
{
    DEVICE_RECORD,
    CLOUD_RECORD
}RECORD_TYPE_E;

typedef struct RecordParameters
{
    QString         deviceId;
    int             channelId;
    QString         beginTime;
    QString         endTime;
    int             beginIndex;
    int             endIndex;
	std::string		playInfo;

	QString         signatureUrl;
	QString         recordPath;
	QString         recordRegionId;

    RecordParameters()
    {
        channelId = 0;
        beginIndex = 0;
        endIndex = 0;
		signatureUrl = "";
    }
}RECORD_PARAMETERS;

typedef struct recInfo
{
    QString         name;
    QString         beginTime;
    QString         endTime;
    QString         deviceId;
    QString         thumbUrl;
    QString         token;
    int             channelId;
    QString         recId;
    long long       fileLength;

    int             index;

	QString         signatureUrl;
	QString         recordPath;
	QString         recordRegionId;

    recInfo()
    {
        channelId = 0;
        fileLength = 0;
        token = "";
        index = -1;
		signatureUrl = "";
    }

    recInfo& operator=(const recInfo& right)
    {
        this->name = right.name;
        this->beginTime = right.beginTime;
        this->endTime = right.endTime;
        this->deviceId = right.deviceId;
        this->thumbUrl = right.thumbUrl;

        this->channelId = right.channelId;
        this->recId = right.recId;
        this->fileLength = right.fileLength;

        this->index = right.index;
        this->token = right.token;

		this->signatureUrl = right.signatureUrl;
		this->recordPath = right.recordPath;
		this->recordRegionId = right.recordRegionId;

        return *this;
    }
}RECORD_INFO;

typedef std::list<RECORD_INFO*> RECORD_INFO_LIST;

#endif // RECORDINFO_H
