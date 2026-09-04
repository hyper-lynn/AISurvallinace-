#include "Src/Utils/global.h"
#include "Src/Model/ThreadInfo.h"
#include "Src/Ctrl/OpenApiCtrl.h"
#include "Src/Ctrl/ThreadCtrl.h"
#include "RecordListCtrl.h"

RecordListCtrl::RecordListCtrl()
	: m_recordType(CLOUD_RECORD)
	, m_threadCtrl(NULL)
{
	m_threadCtrl = new ThreadCtrl(this, PROTO_RECORDLIST);
	connect(m_threadCtrl, SIGNAL(resultReady(int)), this, SIGNAL(sgnRecordThreadResult(int)));
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
		/* 之前查询还未结束则本次不响应 */
		//m_threadCtrl->quit();
		return (int)ERR_SEARCHING;
	}

	/* 查询设备详细信息 */
	m_channelInfo = DevicesListCtrl::getInstance()->getChannelInfo(deviceIndex);
	if (NULL == m_channelInfo)
	{
		return (int)ERR_GET_CHANNELINFO;
	}

	/* threadParam变量由线程执行完后负责释放 */
	RECORD_LIST_THREAD_PARAM *threadParam = new RECORD_LIST_THREAD_PARAM;
	threadParam->deviceId = m_channelInfo->deviceId;
	threadParam->channelId = m_channelInfo->channelId;
	threadParam->date = date;


	m_threadCtrl->setParamter(threadParam, NULL);
	m_threadCtrl->start();

	return (int)ERR_SUCCESS;
}

int RecordListCtrl::getRecordInfo(const QString &deviceId, int channelId, const QDate &date)
{
	clearRecordList();

	QString beginTime = "";
	QString endTime = "";
	getBeginTimeAndEndTime(date, beginTime, endTime);
	RECORD_PARAMETERS parameters;
	parameters.deviceId = deviceId;
	parameters.channelId = channelId;
	parameters.beginTime = beginTime;
	parameters.endTime = endTime;
// 	int totalRecNum = 0;
// 	if (DEVICE_RECORD == m_recordType)
// 	{
// 		totalRecNum = OpenApiCtrl::getInstance()->getDeviceRecordNum(&parameters);
// 	}
// 	else
// 	{
// 		totalRecNum = OpenApiCtrl::getInstance()->getCloudRecordNum(&parameters);
// 	}

	//totalRecNum = 10;

	int ret = 0;
	/* demo只取最新10条录像展示 */
	parameters.beginIndex = 1;
	parameters.endIndex = 10;
	if (DEVICE_RECORD == m_recordType)
	{
		ret = OpenApiCtrl::getInstance()->getDeviceRecords(&parameters, &m_recordInfoList);
	}
	else
	{
		ret = OpenApiCtrl::getInstance()->getCloudRecords(&parameters, &m_recordInfoList);
	}

	return ret;
}

void RecordListCtrl::getBeginTimeAndEndTime(QDate date, QString &beginTime, QString &endTime)
{
	beginTime.sprintf("%d-%02d-%02d 00:00:00", date.year(), date.month(), date.day());
	endTime.sprintf("%d-%02d-%02d 23:59:59", date.year(), date.month(), date.day());
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
