#include "OpenApiCtrl.h"
#include "Model/ThreadInfo.h"

#include "Ctrl/RecordListCtrl.h"
#include "Ctrl/RealPlayCtrl.h"
#include "ThreadCtrl.h"
#include <QJsonParseError>
#include <QJsonDocument>


ThreadCtrl::ThreadCtrl(QObject *parent, PROTOTYPE_E type)
: QThread(parent)
,m_protoType(type)
{
    m_inputParam = NULL;
    m_outputparam = NULL;
	connect(this, SIGNAL(sendDeviceRecords(QJsonObject)), this, SLOT(slotDeviceRecords(QJsonObject)));
	connect(this, SIGNAL(sendCloudRecords(QJsonObject)), this, SLOT(slotCloudRecords(QJsonObject)));
}

ThreadCtrl::~ThreadCtrl()
{

}

void ThreadCtrl::run()
{
	int ret = 0;
	switch (m_protoType)
	{

        case PROTO_GET_DEVICES_LIST :
            {
                // if (OpenApiCtrl::getInstance()->getDevicesList((ChannelInfoList*)m_outputparam))
				if (OpenApiCtrl::getInstance()->getIOTDevicesList((IOTDeviceInfoList*)m_outputparam))
                {
                    emit resultReady(1);
                } 
                else
                {
                    emit resultReady(0);
                }
            }
            break;

        case PROTO_RECORDLIST:
            {
                RECORD_LIST_THREAD_PARAM *recordListPar = (RECORD_LIST_THREAD_PARAM*)m_inputParam;
                if (recordListPar)
                {
                    /* 获取录像列表 */
                    ret = RecordListCtrl::getInstance()->getRecordInfo(recordListPar->deviceId, recordListPar->channelId, recordListPar->playInfo, recordListPar->date, this);

					QJsonParseError jsonError;
					QJsonDocument json = QJsonDocument::fromJson(recordListPar->playInfo.c_str(), &jsonError);
					if (jsonError.error != QJsonParseError::NoError)
					{
						QString strError = jsonError.errorString();
					}

					if (!json.isObject())
					{
						return;
					}
					std::string sourceType = json.object().value("sourceType").toString().toStdString();
					if (sourceType == "paas") //adapter for DHPaaS
					{
						emit resultReady(ret);
						// wait for response querylocaldeviceRecords
					}
					else
					{
						emit resultReady(ret);
					}
                }
                else
                {
                    emit resultReady(-1);
                }
                //SAFE_DELETE(m_inputParam);
            }
            break;

        case PROTO_PTZ_CTRL:
            {
                PTZ_CONTROL_THREAD_PARAM *ptzCtrlPar = (PTZ_CONTROL_THREAD_PARAM*)m_inputParam;
                if (ptzCtrlPar && ptzCtrlPar->user)
                {
                    RealPlayCtrl *realPlayCtrl = (RealPlayCtrl*)(ptzCtrlPar->user);
                    /* 通过OpenAPI接口发命令给设备进行云台控制 */
                    switch (ptzCtrlPar->type)
                    {
                    case TYPE_SINGLE_STEP:
                        ret = realPlayCtrl->ptzSingleStepControl(ptzCtrlPar->deviceId, ptzCtrlPar->channelId, ptzCtrlPar->playInfo, ptzCtrlPar->direction);
                        break;
                    case TYPE_LONGPRESS_PRESS:
                        ret = realPlayCtrl->ptzLongPressBeginControl(ptzCtrlPar->deviceId, ptzCtrlPar->channelId, ptzCtrlPar->playInfo, ptzCtrlPar->direction);
                        break;
                    case TYPE_LONGPRESS_RELEASE:
                        ret = realPlayCtrl->ptzLongPressEndControl(ptzCtrlPar->deviceId, ptzCtrlPar->channelId, ptzCtrlPar->playInfo, ptzCtrlPar->direction);
                        break;
                    default:
                        /* unSupported */
                        ret = -2;
                        break;
                    }

                    DLOG("ptzControl[%d]>direction:%d>type:%d\n", ret, ptzCtrlPar->direction, ptzCtrlPar->type);
                    emit resultReady(ret);
                }
                else
                {
                    emit resultReady(-1);
                }
                SAFE_DELETE(m_inputParam);
            }
            break;

        default:/**to be added*/
        break;
    }
}

void ThreadCtrl::setParamter( void *inputParam, void *outParam )
{
    m_inputParam = inputParam;
	m_outputparam = outParam;
}

void ThreadCtrl::startBusiness()
{
	//The service requested by the QT network will have problems in the child thread and will be moved to the main thread for service.
	run();
}

void ThreadCtrl::slotDeviceRecords(QJsonObject root)
{
	RECORD_INFO_LIST recordList;
	std::string token = "";
	RECORD_LIST_THREAD_PARAM *recordListPar = (RECORD_LIST_THREAD_PARAM*)m_inputParam;
	if (recordListPar)
	{
		std::string playInfo = recordListPar->playInfo;
		QJsonParseError jsonError;
		QJsonDocument json = QJsonDocument::fromJson(playInfo.c_str(), &jsonError);
		if (jsonError.error != QJsonParseError::NoError)
		{
			QString strError = jsonError.errorString();
			return;
		}

		if (!json.isObject())
		{
			return;
		}
		token = json.object().value("userToken").toString().toStdString();
	}
	int index = 0;
	int size = 0;
	if (root.contains("success") && root["success"].toBool())
	{
		if (!root.contains("data") || !root["data"].isObject()) {
			qDebug() << "Missing or invalid 'data' field";
			return;
		}
		QJsonObject dataObj = root["data"].toObject();

		if (!dataObj.contains("records") || !dataObj["records"].isArray()) {
			qDebug() << "Missing or invalid 'records' array";
			return;
		}
		QJsonArray recordsArray = dataObj["records"].toArray();
		size = recordsArray.size();

		RECORD_INFO *info = NULL;
		for (const QJsonValue &recordValue : recordsArray) 
		{
			if (!recordValue.isObject()) continue;

			QJsonObject recordObj = recordValue.toObject();

			info = new(std::nothrow)RECORD_INFO;
			if (NULL == info)
			{
				break;
			}
			info->name = recordObj["recordFileName"].toString();
			info->beginTime = recordObj["beginTime"].toString();
			info->endTime = recordObj["endTime"].toString();
			info->channelId = recordObj["channelId"].toString().toInt();
			info->fileLength = recordObj["fileLength"].toVariant().toLongLong();
			info->index = index;
			index = index + 1;
			info->deviceId = recordListPar->deviceId;
			info->token = token.c_str();

			recordList.push_front(info);
		}
	}
	else
	{
		qDebug() << "success is not exist or response failed !";
		return;
	}

	RecordListCtrl::getInstance()->setRecordInfoList(recordList, size);

}

void ThreadCtrl::slotCloudRecords(QJsonObject root)
{
	RECORD_INFO_LIST recordList;
	std::string token = "";
	RECORD_LIST_THREAD_PARAM *recordListPar = (RECORD_LIST_THREAD_PARAM*)m_inputParam;
	if (recordListPar)
	{
		std::string playInfo = recordListPar->playInfo;
		QJsonParseError jsonError;
		QJsonDocument json = QJsonDocument::fromJson(playInfo.c_str(), &jsonError);
		if (jsonError.error != QJsonParseError::NoError)
		{
			QString strError = jsonError.errorString();
			return;
		}

		if (!json.isObject())
		{
			return;
		}
		token = json.object().value("userToken").toString().toStdString();
	}
	int index = 0;
	int size = 0;
	if (root.contains("success") && root["success"].toBool())
	{
		if (!root.contains("data") || !root["data"].isObject()) {
			qDebug() << "Missing or invalid 'data' field";
			return;
		}
		QJsonObject dataObj = root["data"].toObject();

		if (!dataObj.contains("records") || !dataObj["records"].isArray()) {
			qDebug() << "Missing or invalid 'records' array";
			return;
		}
		QJsonArray recordsArray = dataObj["records"].toArray();
		size = recordsArray.size();

		RECORD_INFO *info = NULL;
		for (const QJsonValue &recordValue : recordsArray)
		{
			if (!recordValue.isObject()) continue;

			QJsonObject recordObj = recordValue.toObject();

			info = new(std::nothrow)RECORD_INFO;
			if (NULL == info)
			{
				break;
			}
			//info->name = recordObj["recordFileName"].toString();
			info->beginTime = recordObj["beginTime"].toString();
			info->endTime = recordObj["endTime"].toString();
			info->channelId = recordObj["channelId"].toString().toInt();
			//info->fileLength = recordObj["fileLength"].toVariant().toLongLong();
			info->index = index;
			index = index + 1;
			info->deviceId = recordListPar->deviceId;
			//info->token = token.c_str();

			info->recId = recordObj["recordId"].toString();
			info->recordRegionId = recordObj["recordRegionId"].toString();
			info->recordPath = recordObj["recordPath"].toString();

			recordList.push_front(info);
		}
	}
	else
	{
		qDebug() << "success is not exist or response failed !";
		return;
	}

	RecordListCtrl::getInstance()->setRecordInfoList(recordList, size);

}

void ThreadCtrl::setProtoType( PROTOTYPE_E type )
{
    m_protoType = type;
}

PROTOTYPE_E ThreadCtrl::getProtoType()
{
    return m_protoType;
}
