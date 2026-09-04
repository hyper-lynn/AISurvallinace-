#include "Utils/global.h"
#include "Model/ThreadInfo.h"
#include "Ctrl/OpenApiCtrl.h"
#include "Ctrl/ThreadCtrl.h"
#include <sstream>
#include "RecordListCtrl.h"

RecordListCtrl::RecordListCtrl()
    : m_recordType(CLOUD_RECORD)
    , m_threadCtrl(NULL)
{
    m_threadCtrl = new ThreadCtrl(this, PROTO_RECORDLIST);
    connect(m_threadCtrl, SIGNAL(resultReady(int)), this, SIGNAL(sgnRecordThreadResult(int)));

	//connect(m_threadCtrl, SIGNAL(sendDeviceRecords(QJsonObject)), this, SLOT(slotDeviceRecords(QJsonObject)));
}

RecordListCtrl::~RecordListCtrl()
{
    if (m_threadCtrl)
    {
        m_threadCtrl->quit();
        m_threadCtrl->deleteLater();
    }

    clearRecordList();
}

RecordListCtrl* RecordListCtrl::getInstance()
{
    static RecordListCtrl instance;
    return &instance;
}

void RecordListCtrl::clearRecordList()
{
    recInfo *info = NULL;
    while (!m_recordInfoList.empty())
    {
        info = m_recordInfoList.front();
        m_recordInfoList.pop_front();
        if (NULL == info)
        {
            continue;
        }

        SAFE_DELETE(info);
    }
}

int RecordListCtrl::getRecordInfoAsyn(int deviceIndex, const QDate &date)
{
    if (m_threadCtrl->isRunning())
    {
/* Ensure thread is not joinable before destruction */
        //m_threadCtrl->quit();
        return (int)ERR_SEARCHING;
    }

/* threadParam may be accessed by other threads, do not modify it here */
	RECORD_LIST_THREAD_PARAM *threadParam = new RECORD_LIST_THREAD_PARAM;

	int deviceNum = DevicesListCtrl::getInstance()->getIOTChannelInfoList()->size();
	if (deviceNum == 1)
	{  //nvr or dahuaPaaS device
		m_iotDevList = DevicesListCtrl::getInstance()->getIOTChannelInfo(0);
		if (NULL == m_iotDevList)
		{
			return (int)ERR_GET_CHANNELINFO;
		}

		int iotChannels = m_iotDevList->iotChannel.size();

		if (iotChannels > 1)
{  // Cloud record
			std::string chanID = m_iotDevList->iotChannel[deviceIndex]->channelId;
			std::stringstream ss;
			ss << chanID;
			int channID;
			ss >> channID;
			threadParam->deviceId = QString::fromStdString(m_iotDevList->deviceId);
			threadParam->channelId = channID;
			threadParam->date = date;
			threadParam->playInfo = m_iotDevList->playInfo;

			m_threadCtrl->setParamter(threadParam, NULL);
			//m_threadCtrl->start();
			m_threadCtrl->startBusiness();

			return (int)ERR_SUCCESS;
		}
		else if (iotChannels == 1)
		{
			std::string chanID = m_iotDevList->iotChannel[0]->channelId;
			std::stringstream ss;
			ss << chanID;
			int channID;
			ss >> channID;
			threadParam->deviceId = QString::fromStdString(m_iotDevList->deviceId);
			threadParam->channelId = channID;
			threadParam->date = date;
			threadParam->playInfo = m_iotDevList->playInfo;

			m_threadCtrl->setParamter(threadParam, NULL);
			//m_threadCtrl->start();
			m_threadCtrl->startBusiness();

			return (int)ERR_SUCCESS;
		}
		else
		{
			qDebug() << "iotChannels == 0, no device ! ";
		}
	}
	else
	{   // deviceNum != 1
		m_iotDevList = DevicesListCtrl::getInstance()->getIOTChannelInfo(deviceIndex);
		if (NULL == m_iotDevList)
		{
			return (int)ERR_GET_CHANNELINFO;
		}

		int iotChannels = m_iotDevList->iotChannel.size();

		if (iotChannels > 1)
{  // Device record
			std::string chanID = m_iotDevList->iotChannel[deviceIndex]->channelId;
			std::stringstream ss;
			ss << chanID;
			int channID;
			ss >> channID;
			threadParam->deviceId = QString::fromStdString(m_iotDevList->deviceId);
			threadParam->channelId = channID;
			threadParam->date = date;
			threadParam->playInfo = m_iotDevList->playInfo;

			m_threadCtrl->setParamter(threadParam, NULL);
			//m_threadCtrl->start();
			m_threadCtrl->startBusiness();

			return (int)ERR_SUCCESS;
		}
		else if (iotChannels == 1)
		{
			std::string chanID = m_iotDevList->iotChannel[0]->channelId;
			std::stringstream ss;
			ss << chanID;
			int channID;
			ss >> channID;
			threadParam->deviceId = QString::fromStdString(m_iotDevList->deviceId);
			threadParam->channelId = channID;
			threadParam->date = date;
			threadParam->playInfo = m_iotDevList->playInfo;

			m_threadCtrl->setParamter(threadParam, NULL);
			//m_threadCtrl->start();
			m_threadCtrl->startBusiness();

			return (int)ERR_SUCCESS;
		}
		else
		{
			qDebug() << "iotChannels == 0, no device ! ";
		}

	}
}

void RecordListCtrl::setRecordInfoList(RECORD_INFO_LIST recordInfoList, int recordSize)
{
	// clear old m_recordInfoList
	m_recordInfoList.clear();

	m_recordInfoList = recordInfoList;
	emit m_threadCtrl->resultReady(recordSize);
}

int RecordListCtrl::getRecordInfo(const QString &deviceId, int channelId, std::string playInfo, const QDate &date, ThreadCtrl* ptr)
{
    clearRecordList();

    QString beginTime = date.toString("yyyy-MM-dd").append(" 00:00:00");
    QString endTime = date.toString("yyyy-MM-dd").append(" 23:59:59");

	/*QDateTime currentDateTime = QDateTime::currentDateTime();
	QString currentTimeString = currentDateTime.toString("yyyy-MM-dd hh:mm:ss");

	QDateTime oneHourEarlier = currentDateTime.addSecs(-3600);
	QString oneHourEarlierString = oneHourEarlier.toString("yyyy-MM-dd hh:mm:ss");*/

    RECORD_PARAMETERS parameters;
    parameters.deviceId = deviceId;
    parameters.channelId = channelId;
    parameters.beginTime = beginTime;
    parameters.endTime = endTime;
	/*parameters.beginTime = oneHourEarlierString;
	parameters.endTime = currentTimeString;*/

	parameters.playInfo = playInfo;

    /*int totalRecNum = 0;
    if (DEVICE_RECORD == m_recordType)
    {
        totalRecNum = OpenApiCtrl::getInstance()->getDeviceRecordNum(parameters);
    }
    else
    {
        totalRecNum = OpenApiCtrl::getInstance()->getCloudRecordNum(parameters);
    }*/

    /*int ret = totalRecNum;*/
   /* if (totalRecNum > 0)
    {*/
/* Demo limits to 10 records per page */
	int ret = 0;
        /*parameters.beginIndex = max(1, totalRecNum - 9);
        parameters.endIndex = totalRecNum;*/
        if (DEVICE_RECORD == m_recordType)
        {
            ret = OpenApiCtrl::getInstance()->getDeviceRecords(parameters, &m_recordInfoList, ptr);
        }
        else
        {
            ret = OpenApiCtrl::getInstance()->getCloudRecords(parameters, &m_recordInfoList, ptr);
        }
    //}

    return ret;
}

void RecordListCtrl::getBeginTimeAndEndTime(QDate date, QString &beginTime, QString &endTime)
{
    beginTime.asprintf("%d-%02d-%02d 00:00:00", date.year(), date.month(), date.day());
    endTime.asprintf("%d-%02d-%02d 23:59:59", date.year(), date.month(), date.day());
}

const RECORD_INFO* RecordListCtrl::getRecordInfoByIndex(int index)
{
    RECORD_INFO_LIST::const_iterator iter = m_recordInfoList.begin();
    const RECORD_INFO *info = NULL;
    for (; iter != m_recordInfoList.end(); ++iter)
    {
        if (NULL != (*iter) && index == (*iter)->index)
        {
            info = (*iter);
            break;
        }
    }

    return info;
}
