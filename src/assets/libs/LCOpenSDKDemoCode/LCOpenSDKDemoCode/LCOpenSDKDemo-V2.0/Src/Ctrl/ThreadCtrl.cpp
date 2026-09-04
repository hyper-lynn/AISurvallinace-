#include "OpenApiCtrl.h"
#include "Src/Model/ThreadInfo.h"
#include "Src/Model/AlarmMsgInfo.h"
#include "Src/Ctrl/RecordListCtrl.h"
#include "Src/Ctrl/RealPlayCtrl.h"
#include "ThreadCtrl.h"

ThreadCtrl::ThreadCtrl(QObject *parent, PROTOTYPE_E type)
	: QThread(parent)
	, m_protoType(type)
{
	m_inputParam = NULL;
	m_outputparam = NULL;
}

ThreadCtrl::~ThreadCtrl()
{

}

void ThreadCtrl::run()
{
	int ret = 0;
	switch (m_protoType)
	{
	case PROTO_GET_DEVICE_P2PPORT:
	{
		ret = OpenApiCtrl::getInstance()->getDevicesListP2PPort((ChannelInfoList*)m_outputparam);
		emit resultReady(ret);
	}
	break;
	case PROTO_GET_ALARM_MSG:
	{
		ret = OpenApiCtrl::getInstance()->getAlarmMsg((AlarmMsgParameter*)m_inputParam, (AlarmMsgInfoList*)m_outputparam);
		emit resultReady(ret);
	}
	break;
	case PROTO_DELETE_ALARM_MSG:
	{
		//if (OpenApiCtrl::getInstance()->deleteAlarmMsg(*((long long *)m_inputParam)))
		if (OpenApiCtrl::getInstance()->deleteAlarmMsg((AlarmMsgInfo*)m_inputParam))
		{
			emit resultReady(1);
		}
		else
		{
			emit resultReady(0);
		}
	}
	break;
	case PROTO_GET_DEVICES_LIST:
	{
		if (OpenApiCtrl::getInstance()->getDevicesList((ChannelInfoList*)m_outputparam))
		{
			emit resultReady(1);
		}
		else
		{
			emit resultReady(0);
		}
	}
	break;
	/*根据设备ID获取设备*/
	case PROTO_GET_DEVICE_BYID:
	{
		char *param = (char*)m_inputParam;
		printf("==ThreadCtrl::searchDeviceByID param = %s\n", param);
		if (OpenApiCtrl::getInstance()->searchDeviceByID(QString(QLatin1String(param)), (ChannelInfoList*)m_outputparam))
		{
			emit resultReady(1);
		}
		else
		{
			emit resultReady(0);
		}
		//释放
		if (NULL != param)
		{
			delete param;
			param = NULL;
		}
	}
	break;
	case PROTO_RECORDLIST:
	{
		RECORD_LIST_THREAD_PARAM *recordListPar = (RECORD_LIST_THREAD_PARAM*)m_inputParam;
		if (recordListPar)
		{
			/* 获取录像列表 */
			ret = RecordListCtrl::getInstance()->getRecordInfo(recordListPar->deviceId, recordListPar->channelId, recordListPar->date);
			emit resultReady(ret);
		}
		else
		{
			emit resultReady(-1);
		}
		SAFE_DELETE(m_inputParam);
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
				ret = realPlayCtrl->ptzSingleStepControl(ptzCtrlPar->deviceId, ptzCtrlPar->productId, ptzCtrlPar->channelId, ptzCtrlPar->direction);
				break;
			case TYPE_LONGPRESS_PRESS:
				ret = realPlayCtrl->ptzLongPressBeginControl(ptzCtrlPar->deviceId, ptzCtrlPar->productId, ptzCtrlPar->channelId, ptzCtrlPar->direction);
				break;
			case TYPE_LONGPRESS_RELEASE:
				ret = realPlayCtrl->ptzLongPressEndControl(ptzCtrlPar->deviceId, ptzCtrlPar->productId, ptzCtrlPar->channelId, ptzCtrlPar->direction);
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

void ThreadCtrl::setParamter(void *inputParam, void *outParam)
{
	m_inputParam = inputParam;
	m_outputparam = outParam;
}

void ThreadCtrl::setProtoType(PROTOTYPE_E type)
{
	m_protoType = type;
}

PROTOTYPE_E ThreadCtrl::getProtoType()
{
	return m_protoType;
}
