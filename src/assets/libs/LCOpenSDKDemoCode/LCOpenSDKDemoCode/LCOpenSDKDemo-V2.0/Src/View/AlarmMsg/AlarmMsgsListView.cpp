#include "lcopensdk_utils/LCOpenSdk_Utils.h"
#include "Src/Utils/TimeHelper.h"
#include "AlarmMsgsListView.h"
#include "Src/Ctrl/OpenApiCtrl.h"

#define DEC_IMG_MAX_SIZE (1024 * 1024 * 5)
#define PNG_IMG_MAX_SIZE (1024 * 1024 * 5)

extern bool g_isReleasedForOverseas;

AlarmMsgsListView::AlarmMsgsListView(QWidget* parent)
	: QWidget(parent)
{
	m_deviceIndex = -1;
	m_separatorLbl = NULL;
	m_toolBar = NULL;
	m_returnToDevicesListBtn = NULL;
	m_workBar = NULL;
	m_channelNameLbl = NULL;
	m_statusLbl = NULL;
	m_searchBar = NULL;
	m_calendar = NULL;
	m_separatorLbl1 = NULL;
	m_separatorLbl2 = NULL;
	m_scrollView = NULL;
	m_alarmMsgBigPicView = NULL;
	m_CurlDownloadS = NULL;
	m_CurlDownloadB = NULL;
	m_alarmMsgSmallPicIndex = -1;
	m_alarmMsgBigPicIndex = -1;
	m_threadCtrl = NULL;
	m_isOpenApiRunning = false;
	m_decryptPicBuf = NULL;
	m_isCurlDownLoadEnabled = false;
}

AlarmMsgsListView::~AlarmMsgsListView()
{
	release();
}

int AlarmMsgsListView::init()
{
	int ret = 0;

	do
	{
		this->resize(1022, 616);
		this->move(0, 0);

		m_decryptPicBuf = (unsigned char*)malloc(DEC_IMG_MAX_SIZE);
		if (NULL == m_decryptPicBuf)
		{
			ret = -1;
			break;
		}

		m_separatorLbl = new (std::nothrow) QLabel(this);
		if (NULL == m_separatorLbl)
		{
			ret = -1;
			break;
		}
		m_separatorLbl->resize(this->width(), 1);
		m_separatorLbl->move(0, 0);
		m_separatorLbl->setStyleSheet("background-color:#fd8b30;");

		m_toolBar = new (std::nothrow) QWidget(this);
		if (NULL == m_toolBar)
		{
			ret = -1;
			break;
		}
		m_toolBar->resize(this->width(), 42);
		m_toolBar->move(0, 1);
		m_toolBar->setStyleSheet("background-color:#2c2d30;");

		m_returnToDevicesListBtn = new (std::nothrow) IconTextBtn(m_toolBar);
		if (NULL == m_returnToDevicesListBtn)
		{
			ret = -1;
			break;
		}
		m_returnToDevicesListBtn->setBtnAttribute("Skin/common_icon_back", tr("Back to Devices List"), 11, QColor(0xb0, 0xaf, 0xaf));
		m_returnToDevicesListBtn->move(22, 6);
		connect(m_returnToDevicesListBtn, SIGNAL(clicked()), this, SLOT(slotReturnToDevicesList()));

		m_statusLbl = new (std::nothrow) QLabel(m_toolBar);
		if (NULL == m_statusLbl)
		{
			ret = -1;
			break;
		}
		m_statusLbl->resize(600, 50);
		m_statusLbl->move(m_toolBar->width() - m_statusLbl->width(), 6);
		m_statusLbl->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
		m_statusLbl->setWordWrap(true);
		m_statusLbl->setStyleSheet("color:#b0afaf;font:11pt;font-family:Microsoft YaHei;");

		m_workBar = new (std::nothrow) QWidget(this);
		if (NULL == m_workBar)
		{
			ret = -1;
			break;
		}
		m_workBar->resize(this->width(), this->height() - 43);
		m_workBar->move(0, 43);
		m_workBar->setAutoFillBackground(true);
		QPalette bgPalette;
		bgPalette.setBrush(QPalette::Window, QColor(0x20, 0x22, 0x24));
		m_workBar->setPalette(bgPalette);

		m_channelNameLbl = new (std::nothrow) QLabel(m_workBar);
		if (NULL == m_channelNameLbl)
		{
			ret = -1;
			break;
		}
		m_channelNameLbl->setFixedHeight(50);
		m_channelNameLbl->move(30, 6);
		m_channelNameLbl->setStyleSheet("color:#ffffff;font:12pt;font-family:Microsoft YaHei;");

		m_searchBar = new (std::nothrow) SearchBar(m_workBar);
		if (NULL == m_searchBar)
		{
			ret = -1;
			break;
		}
		m_searchBar->init();
		m_searchBar->move(337, 14);
		connect(m_searchBar, SIGNAL(sgnSearch(QString)), this, SLOT(slotSearch(QString)));
		connect(m_searchBar, SIGNAL(sgnFocusIn()), this, SLOT(slotShowOrHideCalendar()));

		m_calendar = new (std::nothrow) Calendar(m_workBar);
		if (NULL == m_calendar)
		{
			ret = -1;
			break;
		}
		m_calendar->init();
		m_calendar->resize(348, 300);
		m_calendar->move(337, 50);
		connect(m_calendar, SIGNAL(sgnClicked(QDate)), this, SLOT(slotSetSearchData(QDate)));
		m_calendar->hide();

		m_separatorLbl1 = new (std::nothrow) QLabel(m_workBar);
		if (NULL == m_separatorLbl1)
		{
			ret = -1;
			break;
		}
		m_separatorLbl1->resize(m_workBar->width(), 1);
		m_separatorLbl1->move(0, 62);
		m_separatorLbl1->setStyleSheet("background-color:#000000;");

		m_separatorLbl2 = new (std::nothrow) QLabel(m_workBar);
		if (NULL == m_separatorLbl2)
		{
			ret = -1;
			break;
		}
		m_separatorLbl2->resize(m_workBar->width(), 1);
		m_separatorLbl2->move(0, 63);
		m_separatorLbl2->setStyleSheet("background-color:#323436;");

		m_scrollView = new (std::nothrow) BaseScrollView(m_workBar);
		if (NULL == m_scrollView)
		{
			ret = -1;
			break;
		}
		m_scrollView->resize(m_workBar->width(), m_workBar->height() - 64);
		m_scrollView->move(0, 64);

		m_alarmMsgBigPicView = new (std::nothrow) AlarmMsgBigPicView(this);
		if (NULL == m_alarmMsgBigPicView)
		{
			ret = -1;
			break;
		}
		ret = m_alarmMsgBigPicView->init();
		if (0 != ret)
		{
			break;
		}
		connect(this, SIGNAL(sgnReply(const QPixmap&)), m_alarmMsgBigPicView, SLOT(slotReply(const QPixmap&)));
		connect(m_alarmMsgBigPicView, SIGNAL(sgnLast()), this, SLOT(slotLast()));
		connect(m_alarmMsgBigPicView, SIGNAL(sgnNext()), this, SLOT(slotNext()));
		m_alarmMsgBigPicView->hide();

		m_CurlDownloadS = new (std::nothrow) CurlDownload(this);
		if (NULL == m_CurlDownloadS)
		{
			ret = -1;
			break;
		}
		connect(m_CurlDownloadS, SIGNAL(sgnFinished(unsigned char*, unsigned int, QString)), this, SLOT(slotCurlDownloadFinishedS(unsigned char*, unsigned int, QString)));

		m_CurlDownloadB = new (std::nothrow) CurlDownload(this);
		if (NULL == m_CurlDownloadB)
		{
			ret = -1;
			break;
		}
		connect(m_CurlDownloadB, SIGNAL(sgnFinished(unsigned char*, unsigned int, QString)), this, SLOT(slotCurlDownloadFinishedB(unsigned char*, unsigned int, QString)));

		m_threadCtrl = new (std::nothrow) ThreadCtrl(this, PROTO_GET_ALARM_MSG);
		if (NULL == m_threadCtrl)
		{
			ret = -1;
			break;
		}
		connect(m_threadCtrl, SIGNAL(resultReady(int)), this, SLOT(slotHandleResult(int)), Qt::QueuedConnection);

	} while (0);

	if (0 != ret)
	{
		release();
	}

	return ret;
}

void AlarmMsgsListView::release()
{
	clearAlarmMsg();

	if (NULL != m_threadCtrl)
	{
		m_threadCtrl->quit();
		m_threadCtrl->deleteLater();
	}

	if (NULL != m_CurlDownloadB)
	{
		delete m_CurlDownloadB;
		m_CurlDownloadB = NULL;
	}

	if (NULL != m_CurlDownloadS)
	{
		delete m_CurlDownloadS;
		m_CurlDownloadS = NULL;
	}

	if (NULL != m_alarmMsgBigPicView)
	{
		delete m_alarmMsgBigPicView;
		m_alarmMsgBigPicView = NULL;
	}

	if (NULL != m_scrollView)
	{
		delete m_scrollView;
		m_scrollView = NULL;
	}

	if (NULL != m_separatorLbl2)
	{
		delete m_separatorLbl2;
		m_separatorLbl2 = NULL;
	}

	if (NULL != m_separatorLbl1)
	{
		delete m_separatorLbl1;
		m_separatorLbl1 = NULL;
	}

	if (NULL != m_calendar)
	{
		delete m_calendar;
		m_calendar = NULL;
	}

	if (NULL != m_searchBar)
	{
		delete m_searchBar;
		m_searchBar = NULL;
	}

	if (NULL != m_channelNameLbl)
	{
		delete m_channelNameLbl;
		m_channelNameLbl = NULL;
	}

	if (NULL != m_workBar)
	{
		delete m_workBar;
		m_workBar = NULL;
	}

	if (NULL != m_statusLbl)
	{
		delete m_statusLbl;
		m_statusLbl = NULL;
	}

	if (NULL != m_returnToDevicesListBtn)
	{
		delete m_returnToDevicesListBtn;
		m_returnToDevicesListBtn = NULL;
	}

	if (NULL != m_toolBar)
	{
		delete m_toolBar;
		m_toolBar = NULL;
	}

	if (NULL != m_separatorLbl)
	{
		delete m_separatorLbl;
		m_separatorLbl = NULL;
	}

	if (NULL != m_decryptPicBuf)
	{
		free(m_decryptPicBuf);
		m_decryptPicBuf = NULL;
	}
	return;
}

void AlarmMsgsListView::setDeviceIndex(int deviceIndex)
{
	m_deviceIndex = deviceIndex;
}

void AlarmMsgsListView::show()
{
	ChannelInfo* channelInfo = DevicesListCtrl::getInstance()->getChannelInfo(m_deviceIndex);
	if (NULL != channelInfo)
	{
		m_channelNameLbl->setText(channelInfo->channelName);
	}

	QDate curDate = QDate::currentDate();
	m_searchBar->setDate(curDate.toString("yyyy-MM-dd"));
	m_calendar->setSelectedDate(curDate);
	m_calendar->hide();
	m_statusLbl->setText("");

	return;
}

void AlarmMsgsListView::clearAlarmMsg()
{
	m_isCurlDownLoadEnabled = false;
	for (int i = 0; i < m_alarmMsgViewVector.size(); i++)
	{
		delete m_alarmMsgViewVector.at(i);
	}
	m_alarmMsgViewVector.clear();
	m_scrollView->m_rootWidget->setFixedHeight(m_scrollView->height());

	for (int i = 0; i < m_alarmMsgInfoList.size(); i++)
	{
		delete m_alarmMsgInfoList.at(i);
	}
	m_alarmMsgInfoList.clear();

	return;
}

void AlarmMsgsListView::getAlarmMsgByTime(QString beginTime, QString endTime)
{
	clearAlarmMsg();

	m_alarmMsgParam.beginTime = beginTime;
	m_alarmMsgParam.endTime = endTime;
	ChannelInfo* channelInfo = DevicesListCtrl::getInstance()->getChannelInfo(m_deviceIndex);
	if (NULL == channelInfo)
	{
		return;
	}
	m_alarmMsgParam.deviceId = channelInfo->deviceId;
	m_decryptKey = channelInfo->decryptKey;
	m_alarmMsgParam.channelId = channelInfo->channelId;
	m_alarmMsgParam.maxCount = MAX_ALARM_MSG;

	m_isOpenApiRunning = true;
	m_threadCtrl->setProtoType(PROTO_GET_ALARM_MSG);
	m_threadCtrl->setParamter(&m_alarmMsgParam, &m_alarmMsgInfoList);
	m_threadCtrl->start();

	return;
}

void AlarmMsgsListView::loadAlarmMsgSmallPic(int alarmMsgIndex)
{
	if (alarmMsgIndex >= m_alarmMsgInfoList.size())
	{
		return;
	}

	AlarmMsgInfo* alarmMsgInfo = m_alarmMsgInfoList.at(alarmMsgIndex);
	if (NULL == alarmMsgInfo)
	{
		return;
	}

	m_CurlDownloadS->get(alarmMsgInfo->thumbUrl, alarmMsgInfo->deviceId);

	return;
}

void AlarmMsgsListView::loadAlarmMsgBigPic()
{
	if (m_alarmMsgBigPicIndex >= m_alarmMsgInfoList.size())
	{
		return;
	}

	AlarmMsgInfo* alarmMsgInfo = m_alarmMsgInfoList.at(m_alarmMsgBigPicIndex);
	if (NULL == alarmMsgInfo)
	{
		return;
	}

	QString url;
	if (alarmMsgInfo->picurlArray.size() > 0)
	{
		url = alarmMsgInfo->picurlArray[0];
	}
	m_CurlDownloadB->get(url, alarmMsgInfo->deviceId);

	return;
}

void AlarmMsgsListView::refreshAlarmMsgBigPicView()
{
	if (m_alarmMsgViewVector.at(m_alarmMsgBigPicIndex)->getAlarmMsgBigPic().isNull())
	{
		QPixmap alarmMsgBigPicDefaultPixmap;
		if (g_isReleasedForOverseas)
		{
			alarmMsgBigPicDefaultPixmap.load("Skin/small_morenfengmian_en.png");
		}
		else
		{
			alarmMsgBigPicDefaultPixmap.load("Skin/small_morenfengmian.png");
		}
		m_alarmMsgBigPicView->setAlarmMsgBigPic(alarmMsgBigPicDefaultPixmap);
		/* 下载大图的过程中不使能last和next按钮 */
		m_alarmMsgBigPicView->setLastBtnNoAbled(true);
		m_alarmMsgBigPicView->setNextBtnNoAbled(true);
		loadAlarmMsgBigPic();
	}
	else
	{
		if (m_alarmMsgBigPicIndex > 0)
		{
			m_alarmMsgBigPicView->setLastBtnNoAbled(false);
		}
		else
		{
			m_alarmMsgBigPicView->setLastBtnNoAbled(true);
		}

		if (m_alarmMsgBigPicIndex + 1 < m_alarmMsgViewVector.size())
		{
			m_alarmMsgBigPicView->setNextBtnNoAbled(false);
		}
		else
		{
			m_alarmMsgBigPicView->setNextBtnNoAbled(true);
		}

		m_alarmMsgBigPicView->setAlarmMsgBigPic(m_alarmMsgViewVector.at(m_alarmMsgBigPicIndex)->getAlarmMsgBigPic());
	}

	return;
}

void AlarmMsgsListView::slotReturnToDevicesList()
{
	//this->hide();
	emit sgnReturnToDevicesList(false);
	return;
}

void AlarmMsgsListView::slotGetCurrentAlarmMsgs()
{
	/* 防止频繁点击“报警消息”按钮->进入报警消息列表页面->查询当前报警消息 */
	if (m_isOpenApiRunning)
	{
		return;
	}

	getAlarmMsgByTime(TimeHelper::GetBeginDateTime(), TimeHelper::GetCurrentDateTime());

	return;
}

void AlarmMsgsListView::slotHandleResult(int result)
{
	m_isOpenApiRunning = false;

	if (PROTO_GET_ALARM_MSG == m_threadCtrl->getProtoType())
	{
		if (result < 0)
		{
			m_statusLbl->setText(tr("Status>>>Get Alarm Messages List Failed!"));
		}
		else if (result == 0)
		{
			m_statusLbl->setText(tr("Status>>>There is no Alarm Message for Current Date!"));
		}
		else
		{
			m_statusLbl->setText(tr("Status>>>Get[") + QString::number(result, 10) + tr("]Alarm Messages."));

			QPixmap alarmMsgSmallPicDefaultPixmap;
			if (g_isReleasedForOverseas)
			{
				alarmMsgSmallPicDefaultPixmap.load("Skin/small_morenfengmian_en.png");
			}
			else
			{
				alarmMsgSmallPicDefaultPixmap.load("Skin/small_morenfengmian.png");
			}
			for (int i = 0; i < m_alarmMsgInfoList.size(); i++)
			{
				if (m_scrollView->m_rootWidget->height() < i / 4 * 186 + 204)
				{
					m_scrollView->m_rootWidget->setFixedHeight(i / 4 * 186 + 204);
				}
				AlarmMsgView* alarmMsgView = new (std::nothrow) AlarmMsgView(m_scrollView->m_rootWidget);
				if (NULL == alarmMsgView)
				{
					return;
				}
				if (0 != alarmMsgView->init())
				{
					return;
				}
				alarmMsgView->setAlarmMsgIndex(i);
				alarmMsgView->setAlarmMsgSmallPic(alarmMsgSmallPicDefaultPixmap);
				alarmMsgView->setAlarmTime(m_alarmMsgInfoList.at(i)->localDate);
				connect(alarmMsgView, SIGNAL(sgnRemoveAlarmMsg(int)), this, SLOT(slotRemoveAlarmMsg(int)));
				connect(alarmMsgView, SIGNAL(sgnAlarmSmallPicLblDblClicked(int)), this, SLOT(slotAlarmSmallPicLblDblClicked(int)));
				alarmMsgView->move(20 + 248 * (i % 4), 18 + 186 * (i / 4));
				alarmMsgView->show();

				m_alarmMsgViewVector.push_back(alarmMsgView);
			}
		}

		if (m_alarmMsgViewVector.size() > 0)
		{
			m_alarmMsgSmallPicIndex = 0;
			m_isCurlDownLoadEnabled = true;
			loadAlarmMsgSmallPic(m_alarmMsgSmallPicIndex);
		}
	}
	else if (PROTO_DELETE_ALARM_MSG == m_threadCtrl->getProtoType())
	{
		if (0 == result)
		{
			m_statusLbl->setText(tr("Status>>>Delete Alarm Message Failed!"));
		}
		else if (1 == result)
		{
			m_statusLbl->setText(tr("Status>>>Delete Alarm Message Succeed!"));

			/* 重新加载报警消息 */
			slotSearch(m_searchBar->getDate());
		}
	}
	return;
}

void AlarmMsgsListView::slotCurlDownloadFinishedS(unsigned char* data, unsigned int dataLen, QString deviceId)
{
	/* 防止刷新报警消息列表->清空报警消息列表，引起的越界&空指针的错误 */
	if (!m_isCurlDownLoadEnabled)
	{
		return;
	}

	if (NULL != data && dataLen > 0)
	{
		/* 图片解密 */
		int decryptPicBufLen = DEC_IMG_MAX_SIZE;
		LCOpenSdk_Utils::DecryptPicEx((const char*)data, dataLen, m_decryptKey.toLatin1().data(), OpenApiCtrl::getInstance()->getToken().toLatin1().data(), deviceId.toLatin1().data(), (char*)m_decryptPicBuf, decryptPicBufLen);
		int pngImgSize = PNG_IMG_MAX_SIZE;
		QPixmap alarmMsgSmallPicPixmap;
		alarmMsgSmallPicPixmap.loadFromData(m_decryptPicBuf, pngImgSize, "JPG");
		/* 考虑一种情况：获取某一张报警消息小图很慢，当slotLoadAlarmMsgSmallPicFinished响应时，报警消息列表已被清空，此时若不加判断... */
		/* 访问m_alarmMsgViewVector会越界 */
		if (m_alarmMsgViewVector.at(m_alarmMsgSmallPicIndex))
		{
			m_alarmMsgViewVector.at(m_alarmMsgSmallPicIndex)->setAlarmMsgSmallPic(alarmMsgSmallPicPixmap);
		}
	}

	if (++m_alarmMsgSmallPicIndex < m_alarmMsgViewVector.size())
	{
		loadAlarmMsgSmallPic(m_alarmMsgSmallPicIndex);
	}

	return;
}

void AlarmMsgsListView::slotCurlDownloadFinishedB(unsigned char* data, unsigned int dataLen, QString deviceId)
{
	if (NULL != data && dataLen > 0)
	{
		/* 图片解密 */
		int decryptPicBufLen = DEC_IMG_MAX_SIZE;
		LCOpenSdk_Utils::DecryptPicEx((const char*)data, dataLen, m_decryptKey.toLatin1().data(), OpenApiCtrl::getInstance()->getToken().toLatin1().data(), deviceId.toLatin1().data(), (char*)m_decryptPicBuf, decryptPicBufLen);

		/* Jpg转Png、显示 */
		int pngImgSize = PNG_IMG_MAX_SIZE;

		QPixmap alarmMsgBigPic;
		alarmMsgBigPic.loadFromData(m_decryptPicBuf, pngImgSize);
		/* 考虑一种情况：获取某一张报警消息大图很慢，当slotLoadAlarmMsgBigPicFinished响应时，报警消息列表已被清空，此时若不加判断... */
		/* 访问m_alarmMsgViewVector会越界 */
		if (m_alarmMsgViewVector.at(m_alarmMsgBigPicIndex))
		{
			/* 存储在AlarmMsgView中 */
			m_alarmMsgViewVector.at(m_alarmMsgBigPicIndex)->setAlarmMsgBigPic(alarmMsgBigPic);

			emit sgnReply(alarmMsgBigPic);
		}

	}

	/* 在报警消息大图页面中设置图片，使能last和next按钮 */
	if (m_alarmMsgBigPicIndex > 0)
	{
		m_alarmMsgBigPicView->setLastBtnNoAbled(false);
	}
	if (m_alarmMsgBigPicIndex + 1 < m_alarmMsgViewVector.size())
	{
		m_alarmMsgBigPicView->setNextBtnNoAbled(false);
	}

	return;
}

void AlarmMsgsListView::slotAlarmSmallPicLblDblClicked(int alarmMsgIndex)
{
	/* 当正在执行删除报警消息的操作时，不允许去获取报警消息大图 */
	if (m_isOpenApiRunning)
	{
		return;
	}

	m_alarmMsgBigPicIndex = alarmMsgIndex;
	refreshAlarmMsgBigPicView();
	m_alarmMsgBigPicView->show();
}

void AlarmMsgsListView::slotLast()
{
	if (--m_alarmMsgBigPicIndex >= 0)
	{
		refreshAlarmMsgBigPicView();
	}
}

void AlarmMsgsListView::slotNext()
{
	if (++m_alarmMsgBigPicIndex < m_alarmMsgViewVector.size())
	{
		refreshAlarmMsgBigPicView();
	}
}

void AlarmMsgsListView::slotRemoveAlarmMsg(int alarmMsgIndex)
{
	m_isOpenApiRunning = true;
	m_threadCtrl->setProtoType(PROTO_DELETE_ALARM_MSG);
	//m_threadCtrl->setParamter(&(m_alarmMsgInfoList.at(alarmMsgIndex)->alarmId), NULL);
	m_threadCtrl->setParamter(m_alarmMsgInfoList.at(alarmMsgIndex), NULL);
	m_threadCtrl->start();
	return;
}

void AlarmMsgsListView::slotShowOrHideCalendar()
{
	if (m_calendar->isVisible())
	{
		m_calendar->hide();
	}
	else
	{
		m_calendar->raise();
		m_calendar->show();
	}
	return;
}

void AlarmMsgsListView::slotSetSearchData(QDate date)
{
	m_searchBar->setDate(date.toString("yyyy-MM-dd"));
	m_calendar->hide();
	return;
}

void AlarmMsgsListView::slotSearch(QString date)
{
	if (m_isOpenApiRunning)
	{
		m_statusLbl->setText(tr("Status>>>OpenApi request too frequently!"));
		return;
	}
	m_statusLbl->setText(tr("Status>>>Querying alarm message..."));

	QString beginTime = date + " 00:00:00";
	QString endTime = date + " 23:59:59";
	getAlarmMsgByTime(beginTime, endTime);

	return;
}
