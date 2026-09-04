#include <QPainter>
#include <QLabel>
#include <QDir>
#include "Src/Ctrl/RecordListCtrl.h"
#include "Src/Ctrl/OpenApiCtrl.h"
#include "Src/Ctrl/DevicesListCtrl.h"
#include "Src/Utils/global.h"
#include "Src/Utils/CommonView/ScrollView.h"
#include "Src/Utils/CommonView/IconTextBtn.h"
#include "Src/Utils/CommonView/SearchBar.h"
#include "Src/Utils/CommonView/Calendar.h"
#include "Src/Utils/CommonView/SplitLine.h"
#include "RecordListView.h"
#include <qinputdialog.h>

extern bool g_isReleasedForOverseas;

RecordListView::RecordListView(QWidget *parent)
	: QWidget(parent)
	, m_viewCtrl(NULL)
	, m_isInit(false)
	, m_deviceId("")
	, m_channelId(0)
	, m_nstate(0)
	, m_btnBack(NULL)
	, m_scrollView(NULL)
	, m_labelChannelName(NULL)
	, m_searchBar(NULL)
	, m_calendar(NULL)
	, m_showInfo(NULL)
	, m_splitLine(NULL)
	, m_splitLine2(NULL)
	, m_downloadingIndex(-1)
	, m_cloudRecordsDir("./data/cloudRecords")
	, m_deviceRecordsDir("./data/deviceRecords")
{
	m_searchDate = QDate::currentDate();
	hide();
}

RecordListView::~RecordListView()
{
	/* 将listener断开，否则底层回调函数会崩溃 */
	m_lcopensdkDownloadInstance->setDownloadListener(NULL);

	/* 直接关闭应用程序时，如果当前正在下载，先取消下载 */
	if (m_downloadingIndex >= 0)
	{
		emit sgnCancelDownload(m_downloadingIndex);
		remove(m_downloadingFilePath.data());
	}

	SAFE_DELETE(m_scrollView);
	SAFE_DELETE(m_btnBack);
	SAFE_DELETE(m_labelChannelName);
	SAFE_DELETE(m_searchBar);
	SAFE_DELETE(m_calendar);
	SAFE_DELETE(m_showInfo);
	SAFE_DELETE(m_splitLine);
	SAFE_DELETE(m_splitLine2);
}

int RecordListView::init()
{
	int ret = 0;

	do
	{
		connect(this, SIGNAL(sgnSetShowInfo(QString)), this, SLOT(slotSetShowInfo(QString)));

		m_viewCtrl = RecordListCtrl::getInstance();
		connect(m_viewCtrl, SIGNAL(sgnRecordThreadResult(int)), this, SLOT(slotRecordThreadResult(int)));

		m_scrollView = new RecordListScrollView(this);
		if (NULL == m_scrollView)
		{
			ret = -1;
			break;
		}
		m_scrollView->setChildSize(230, 188, 4, 18);
		connect(m_scrollView, SIGNAL(sgnPlayBtnClicked(int)), this, SLOT(slotPlayBtnClicked(int)));
		connect(m_scrollView, SIGNAL(sgnDownloadBtnClicked(int)), this, SLOT(slotDownloadBtnClicked(int)));
		connect(m_scrollView, SIGNAL(sgnCancelBtnClicked(int)), this, SLOT(slotCancelBtnClicked(int)));
		connect(this, SIGNAL(sgnDownloadPercent(int, int)), m_scrollView, SIGNAL(sgnDownloadPercent(int, int)));
		connect(this, SIGNAL(sgnCancelDownload(int)), m_scrollView, SIGNAL(sgnCancelDownload(int)));
		connect(this, SIGNAL(sgnSetDownloadUI(int, bool)), m_scrollView, SIGNAL(sgnSetDownloadUI(int, bool)));

		m_splitLine = new SplitLine(this, QColor(0xfd, 0x8b, 0x30), 1);
		if (NULL == m_splitLine)
		{
			ret = -1;
			break;
		}

		m_splitLine2 = new SplitLine(this, QColor(0x00, 0x00, 0x00), QColor(0x32, 0x34, 0x36));
		if (NULL == m_splitLine2)
		{
			ret = -1;
			break;
		}

		m_btnBack = new IconTextBtn(this);
		if (NULL == m_btnBack)
		{
			ret = -1;
			break;
		}
		m_btnBack->setBtnAttribute("Skin/common_icon_back", tr("Back to Devices List"), 11, QColor(0xb0, 0xaf, 0xaf));
		connect(m_btnBack, SIGNAL(clicked()), this, SLOT(slotBackBtnClicked()));

		m_labelChannelName = new QLabel(this);
		if (NULL == m_labelChannelName)
		{
			ret = -1;
			break;
		}

		m_searchBar = new SearchBar(this);
		ret = m_searchBar->init();
		if (NULL == m_searchBar)
		{
			ret = -1;
			break;
		}
		connect(m_searchBar, SIGNAL(sgnFocusIn()), this, SLOT(slotShowOrHideCalendar()));
		connect(m_searchBar, SIGNAL(sgnSearch(QString)), this, SLOT(slotSearch(QString)));

		m_calendar = new (std::nothrow) Calendar(this);
		if (NULL == m_calendar)
		{
			ret = -1;
			break;
		}
		m_calendar->init();
		connect(m_calendar, SIGNAL(sgnClicked(QDate)), this, SLOT(slotSetText(QDate)));
		m_calendar->hide();

		m_showInfo = new QLabel(this);
		if (NULL == m_showInfo)
		{
			ret = -1;
			break;
		}

		m_lcopensdkDownloadInstance = LCOpenSDK_Download::getInstance();
		m_lcopensdkDownloadInstance->setDownloadListener(this);

		m_isInit = true;
	} while (0);

	refreshLayout();
	fillBackGroundWithColor(this, QColor(32, 34, 36));
	return ret;
}

void RecordListView::setPosition(const QRect &position)
{
	m_position = position;

	this->setFixedSize(m_position.width(), m_position.height());
	this->move(m_position.left(), m_position.top());
}

void RecordListView::fillBackGroundWithColor(QWidget *widget, QColor& color)
{
	if (NULL == widget)
	{
		return;
	}

	widget->setAutoFillBackground(true);
	QPalette palette;
	palette.setColor(QPalette::Background, color);
	widget->setPalette(palette);
}

void RecordListView::refreshLayout()
{
	if (!m_isInit)
	{
		DLOG("please call init() first!!!\n");
		return;
	}

	/*调整控件布局*/
	QWidget *parent = (QWidget*)this->parent();
	if (parent)
	{
		setPosition(QRect(0, 0, parent->width(), parent->height()));
	}

	m_splitLine->move(0, 0);
	m_splitLine->setFixedWidth(this->width());

	m_splitLine2->move(0, 42 + 62);
	m_splitLine2->setFixedWidth(this->width());

	m_btnBack->move(22, 6);

	int y = 2 + 42 + 62;
	m_scrollView->setPosition(QRect(0, y, this->width(), this->height() - y));
	m_btnBack->move(10, 10);

	QFont font("Microsoft YaHei", 12);
	m_labelChannelName->setFont(font);
	m_labelChannelName->setStyleSheet("color:#ffffff;");
	m_labelChannelName->move(30, 2 + 42 + (62 - m_labelChannelName->height()) / 2);

	m_searchBar->move(337, 2 + 42 + (62 - 34) / 2);

	m_calendar->move(337, m_searchBar->y() + m_searchBar->height() + 2);
	m_calendar->resize(348, 300);

	QFont fontShowInfo("Microsoft YaHei", 11);
	m_showInfo->setFont(fontShowInfo);
	m_showInfo->setStyleSheet("color:#B0AFAF;");
	m_showInfo->adjustSize();
	m_showInfo->move(this->width() - 16 - m_showInfo->width(), (42 - m_showInfo->height()) / 2);
}

void RecordListView::paintEvent(QPaintEvent *paintEvent)
{
	QWidget::paintEvent(paintEvent);

	QPainter painter(this);

	int y = 2;
	painter.fillRect(0, y, this->width(), 42, QColor(0x2c, 0x2d, 0x30));
}

void RecordListView::hide()
{
	QWidget::hide();

	if (m_isInit)
	{
		/*clear child view. 注意这里不能clear数据, 录像回放页面会用到这里的数据*/
		m_scrollView->reset();
	}
}


void RecordListView::onDownloadReceiveData(int index, int datalen)
{
	m_downloadLength += datalen;


	emit sgnDownloadPercent(index, m_downloadLength * 100 / m_fileLength);
	return;
}

void RecordListView::onDownloadState(int index, const char* code, int type)
{
	QString strInfo;
	if (99 == type)
	{
		emit sgnCancelDownload(index);
		strInfo = tr("OpenApi request failed[") +
			QString::number(index, 10) +
			QString("]:") +
			QString(QLatin1String(code));
	}

	else if (1 == type)
	{
		if (0 == strcmp("0", code))
		{
			emit sgnCancelDownload(index);
			remove(m_downloadingFilePath.data());
			strInfo = tr("Download failed and stopped[") +
				QString::number(index, 10) +
				QString("]!");
		}
		else if (0 == strcmp("1", code))
		{
			strInfo = tr("Start to download[") +
				QString::number(index, 10) +
				QString("]!");
		}
		else if (0 == strcmp("2", code))
		{
			m_downloadingIndex = -1;
			strInfo = tr("Download finished[") + QString::number(index, 10) + QString("]!");
			emit sgnSetDownloadUI(index, false);
		}
		else if (0 == strcmp("7", code))
		{
			emit sgnCancelDownload(index);
			remove(m_downloadingFilePath.data());
			strInfo = tr("Download timed out and stopped[") +
				QString::number(index, 10) +
				QString("]!");
		}
		else if (0 == strcmp("11", code))
		{
			emit sgnCancelDownload(index);
			//remove(m_downloadingFilePath.data());
			strInfo = tr("Decrypt key error and download stopped[") +
				QString::number(index, 10) +
				QString("]!");
			m_nstate = 11;
		}
		else if (0 == strcmp("14", code))
		{
			emit sgnCancelDownload(index);
			//remove(m_downloadingFilePath.data());
			strInfo = tr("Decrypt key error and download stopped[") +
				QString::number(index, 10) +
				QString("]!");
			m_nstate = 14;
		}
	}
	else if (0 == type)
	{
		if (0 == strcmp("1", code))
		{
			emit sgnCancelDownload(index);
			remove(m_downloadingFilePath.data());
			strInfo = tr("Download failed and stopped[") +
				QString::number(index, 10) +
				QString("]!");
		}
		else if (0 == strcmp("4", code))
		{
			strInfo = tr("Start to download[") +
				QString::number(index, 10) +
				QString("]!");
		}
		else if (0 == strcmp("5", code))
		{
			m_downloadingIndex = -1;
			strInfo = tr("Download finished[") + QString::number(index, 10) + QString("]!");
			emit sgnSetDownloadUI(index, false);
		}
		else if (0 == strcmp("7", code))
		{
			emit sgnCancelDownload(index);
			remove(m_downloadingFilePath.data());
			strInfo = tr("Decrypt key error and download stopped[") +
				QString::number(index, 10) +
				QString("]!");
		}
	}
	else if (5 == type)
	{
		if (0 == strcmp("-1", code))
		{
			emit sgnCancelDownload(index);
			remove(m_downloadingFilePath.data());
			strInfo = tr("Download failed and stopped[") +
				QString::number(index, 10) +
				QString("]!");
		}
		else if (0 == strcmp("1000", code))
		{
			strInfo = tr("Start to download[") +
				QString::number(index, 10) +
				QString("]!");
		}
		else if (0 == strcmp("2000", code))
		{
			m_downloadingIndex = -1;
			strInfo = tr("Download finished[") + QString::number(index, 10) + QString("]!");
			emit sgnSetDownloadUI(index, false);
		}
		else if (0 == strcmp("1000005", code))
		{
			emit sgnCancelDownload(index);
			remove(m_downloadingFilePath.data());
			strInfo = tr("Decrypt key error and download stopped[") +
				QString::number(index, 10) +
				QString("]!");
		}
		
	}
	emit sgnSetShowInfo(strInfo);
}

void RecordListView::slotSetShowInfo(QString info)
{
	if (!m_isInit)
	{
		DLOG("please call init() first!!!\n");
		return;
	}

	m_showInfo->setText(tr("Status>>>") + info);
	m_showInfo->adjustSize();
	m_showInfo->show();

	m_showInfo->move(this->width() - 16 - m_showInfo->width(), m_showInfo->y());
}

void RecordListView::showDeviceRecordListView(int deviceIndex)
{
	if (!m_isInit)
	{
		DLOG("please call init() first!!!\n");
		return;
	}

	m_recordType = DEVICE_RECORD;
	m_deviceIndex = deviceIndex;
	/* 重置scrollwView */
	m_scrollView->reset();

	/* 调用录像查询异步接口 */
	m_viewCtrl->setRecordType(m_recordType);
	m_calendar->setSelectedDate(m_searchDate);
	int ret = m_viewCtrl->getRecordInfoAsyn(m_deviceIndex, m_searchDate);
	if (RecordListCtrl::ERR_SEARCHING == ret)
	{
		slotSetShowInfo(tr("Query too frequently!"));
	}
	else if (RecordListCtrl::ERR_GET_CHANNELINFO == ret)
	{
		slotSetShowInfo(tr("Get device information failed!"));
	}
	else if (RecordListCtrl::ERR_SUCCESS == ret)
	{
		slotSetText(m_searchDate);
		m_deviceId = m_viewCtrl->getDeviceId();

		slotSetShowInfo(tr("Getting device records list..."));

		/* 设置通道名称(超出部分用...代替) */
		QString text = m_labelChannelName->fontMetrics().elidedText(tr("Channel Name : ") + RecordListCtrl::getInstance()->getChannelName(),
			Qt::ElideRight, 300, Qt::TextShowMnemonic);
		m_labelChannelName->setText(text);
		m_labelChannelName->adjustSize();
	}
	else
	{
		slotSetShowInfo(tr("Unknown error!"));
	}
}

void RecordListView::showCloudRecordListView(int deviceIndex)
{
	if (!m_isInit)
	{
		DLOG("please call init() first!!!\n");
		return;
	}

	m_recordType = CLOUD_RECORD;
	m_deviceIndex = deviceIndex;
	/* 重置scrollwView */
	m_scrollView->reset();

	/* 调用录像查询异步接口 */
	m_viewCtrl->setRecordType(m_recordType);
	m_calendar->setSelectedDate(m_searchDate);
	int ret = m_viewCtrl->getRecordInfoAsyn(m_deviceIndex, m_searchDate);
	if (RecordListCtrl::ERR_SEARCHING == ret)
	{
		slotSetShowInfo(tr("Query too frequently!"));
	}
	else if (RecordListCtrl::ERR_GET_CHANNELINFO == ret)
	{
		slotSetShowInfo(tr("Get device information failed!"));
	}
	else if (RecordListCtrl::ERR_SUCCESS == ret)
	{
		slotSetText(m_searchDate);
		m_deviceId = m_viewCtrl->getDeviceId();

		slotSetShowInfo(tr("Getting cloud records list..."));

		/* 设置通道名称(超出部分用...代替) */
		QString text = m_labelChannelName->fontMetrics().elidedText(tr("Channel Name : ") + RecordListCtrl::getInstance()->getChannelName(),
			Qt::ElideRight, 300, Qt::TextShowMnemonic);
		m_labelChannelName->setText(text);
		m_labelChannelName->adjustSize();
	}
	else
	{
		slotSetShowInfo(tr("Unknown error!"));
	}
}

void RecordListView::slotBackBtnClicked()
{
	DLOG("slotBackBtnClicked\n");

	/* 如果当前正在下载，先取消下载 */
	if (m_downloadingIndex >= 0)
	{
		emit sgnCancelDownload(m_downloadingIndex);
		remove(m_downloadingFilePath.data());
	}

	m_searchDate = QDate::currentDate();

	//this->hide();
	/* 回到设备列表页 */
	emit sgnReturnToDevicesList(false);
}

void RecordListView::slotRecordThreadResult(int result)
{
	if (!m_isInit)
	{
		DLOG("please call init() first!!!\n");
		return;
	}

	QString strInfo;
	if (result > 0)
	{
		strInfo = tr("Get records list succeed[") +
			QString::number(result, 10) +
			QString("]!");
	}
	else if (0 == result)
	{
		strInfo = tr("There is no record for current date!");
	}
	else if (-99 == result)
	{
		strInfo = tr("The device has no storage media!");
	}
	else
	{
		strInfo = tr("Get records list failed[") +
			QString::number(result, 10) +
			QString("]!");
	}
	slotSetShowInfo(strInfo);
	if (result <= 0)
	{
		/* result值为录像数量 */
		return;
	}

	/* 录像信息压入scrollview */
	RECORD_CHILD *info = NULL;
	const RECORD_INFO_LIST *infoList = m_viewCtrl->getRecordInfoList();
	RECORD_INFO_LIST::const_iterator iter = infoList->begin();
	for (; iter != infoList->end(); ++iter)
	{
		info = new RECORD_CHILD;
		if (NULL == info)
		{
			continue;
		}

		info->index = (*iter)->index;
		info->beginTime = (*iter)->beginTime;
		info->endTime = (*iter)->endTime;
		info->thumbUrl = (*iter)->thumbUrl;
		info->recordType = m_recordType;

		m_scrollView->addChild(info);
	}

	/* 使压入信息生效显示 */
	QString decryptKey = DevicesListCtrl::getInstance()->getDecryptKeyByDeviceID(m_deviceId);
	m_scrollView->refresh(decryptKey, m_deviceId);
}

void RecordListView::slotPlayBtnClicked(int index)
{
	if (m_downloadingIndex >= 0)
	{
		slotSetShowInfo(tr("Downloading record!"));
		return;
	}

	//this->hide();

	DLOG("slotPlayBtnClicked-%d\n", index);
	if (DEVICE_RECORD == m_recordType)
	{
		emit sgnPlayDeviceRecord(m_deviceIndex, index);
	}
	else if (CLOUD_RECORD == m_recordType)
	{
		emit sgnPlayCloudRecord(m_deviceIndex, index);
	}
}

void RecordListView::slotDownloadBtnClicked(int index)
{
	/* 创建录像文件存储目录 */
	if (CLOUD_RECORD == m_recordType && !QDir(m_cloudRecordsDir).exists())
	{
		QDir dir;
		dir.mkpath(m_cloudRecordsDir);
	}
	else if (DEVICE_RECORD == m_recordType && !QDir(m_deviceRecordsDir).exists())
	{
		QDir dir;
		dir.mkpath(m_deviceRecordsDir);
	}

	if (m_downloadingIndex >= 0)
	{
		slotSetShowInfo(tr("Downloading record!"));
		return;
	}

	m_downloadingIndex = index;

	QByteArray token = OpenApiCtrl::getInstance()->getToken().toLatin1();
	const RECORD_INFO* record_info = m_viewCtrl->getRecordInfoByIndex(index);

	/* 将beginTime中的非数字字符滤去，保存在strBeginTime中 */
	QString beginTime = record_info->beginTime;
	QString strBeginTime;
	for (int i = 0; i < beginTime.length(); i++)
	{
		if (beginTime.at(i).toLatin1() >= '0' && beginTime.at(i).toLatin1() <= '9')
		{
			strBeginTime.append(beginTime.at(i));
		}
	}

	QByteArray deviceId = m_deviceId.toLatin1();
	m_fileLength = record_info->fileLength;
	m_downloadLength = 0;

	/* 执行开始下载业务，设置录像视图中的UI */
	QString decryptKey = DevicesListCtrl::getInstance()->getDecryptKeyByDeviceID(m_deviceId);
	if (CLOUD_RECORD == m_recordType)
	{
		//m_downloadingFilePath = QString(m_cloudRecordsDir + "/" + strBeginTime + "_download_" + record_info->recId + ".mp4").toLatin1();
		m_downloadingFilePath = QString(m_cloudRecordsDir + "/" + strBeginTime + "_download_" + ".mp4").toLatin1();
		m_lcopensdkDownloadInstance->startDownload(index, token.data(), m_downloadingFilePath.data(), deviceId.data(), record_info->channelId, "123", record_info->recordRegionId.toStdString().c_str(), 1000, 5000);
		slotSetShowInfo(tr("Cloud record downloading OpenApi requesting..."));
	}
	else if (DEVICE_RECORD == m_recordType)
	{
		//m_downloadingFilePath = QString(m_deviceRecordsDir + "/" + record_info->deviceId + "_download_" + strBeginTime + ".mp4").toLatin1();
		m_downloadingFilePath = QString(m_deviceRecordsDir + "/" + "_download_" + strBeginTime + ".mp4").toLatin1();

		QDateTime beginTime = QDateTime::fromString(record_info->beginTime, "yyyy-MM-dd HH:mm:ss");
		QDateTime endTime = QDateTime::fromString(record_info->endTime, "yyyy-MM-dd HH:mm:ss");

		long beginTimeTmp = beginTime.toTime_t();
		long endTimeTmp = endTime.toTime_t();

		m_lcopensdkDownloadInstance->startDownload(index, token.data(), m_downloadingFilePath.data(), deviceId.data(),
			decryptKey.toStdString().c_str(), record_info->channelId, beginTimeTmp, endTimeTmp,false, 16);
		
		/*m_lcopensdkDownloadInstance->startDownload(index, token.data(), m_downloadingFilePath.data(), deviceId.data(),
			decryptKey.toStdString().c_str(), record_info->name.toStdString().c_str(), false, 16);*/
		slotSetShowInfo(tr("Device record downloading OpenApi requesting..."));
	}
	emit sgnSetDownloadUI(index, true);
}

void RecordListView::slotCancelBtnClicked(int index)
{
	m_lcopensdkDownloadInstance->stopDownload(index);
	remove(m_downloadingFilePath.data());
	QString strInfo = tr("Cancel downloading[") +
		QString::number(index, 10) +
		QString("]!");
	slotSetShowInfo(strInfo);
	emit sgnSetDownloadUI(index, false);
	if (m_nstate == 11 || m_nstate == 14)
	{
		slotDownloadError(m_nstate);
	}
	else {
		m_downloadingIndex = -1;
	}

	return;
}

void RecordListView::slotSearch(QString date)
{
	DLOG("slotSearch[%s]\n", date.toStdString().c_str());
	if (!m_isInit)
	{
		DLOG("please call init() first!!!\n");
		return;
	}

	/* 如果当前正在下载，先取消下载 */
	if (m_downloadingIndex >= 0)
	{
		emit sgnCancelDownload(m_downloadingIndex);
		remove(m_downloadingFilePath.data());
	}

	/*clear-child view*/
	m_scrollView->reset();
	/* clear 数据 */
	m_viewCtrl->clearRecordList();

	/* 异步查询日历指定日期录像信息 */
	m_searchDate = QDate::fromString(date, "yyyy-MM-dd");
	m_calendar->setSelectedDate(m_searchDate);
	int ret = m_viewCtrl->getRecordInfoAsyn(m_deviceIndex, m_searchDate);
	if (RecordListCtrl::ERR_SEARCHING == ret)
	{
		slotSetShowInfo(tr("Query too frequently!"));
	}
	else if (RecordListCtrl::ERR_GET_CHANNELINFO == ret)
	{
		slotSetShowInfo(tr("Get device information failed!"));
	}
	else if (RecordListCtrl::ERR_SUCCESS == ret)
	{
		slotSetShowInfo(tr("Getting records list..."));
	}
	else
	{
		slotSetShowInfo(tr("Unknown error!"));
	}
}

void RecordListView::slotShowOrHideCalendar()
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

void RecordListView::slotSetText(QDate date)
{
	m_searchBar->setDate(date.toString("yyyy-MM-dd"));
	m_calendar->hide();
	return;
}
void RecordListView::slotDownloadError(int status)
{
	bool ok;
	QString text = QInputDialog::getText(this, tr("key changed"), status == 11 ? tr("mobile_common_input_video_Key_tip") : tr("mobile_common_input_video_password_tip"), QLineEdit::Normal, 0, &ok);
	if (ok && !text.isEmpty())
	{
		QByteArray token = OpenApiCtrl::getInstance()->getToken().toLatin1();
		QByteArray deviceId = m_deviceId.toLatin1();
		const RECORD_INFO* record_info = m_viewCtrl->getRecordInfoByIndex(m_downloadingIndex);
		QString beginTime = record_info->beginTime;
		QString strBeginTime;
		for (int i = 0; i < beginTime.length(); i++)
		{
			if (beginTime.at(i).toLatin1() >= '0' && beginTime.at(i).toLatin1() <= '9')
			{
				strBeginTime.append(beginTime.at(i));
			}
		}
		m_downloadingFilePath = QString(m_cloudRecordsDir + "/" + strBeginTime + "_download_" + ".mp4").toLatin1();	
		m_lcopensdkDownloadInstance->startDownload(m_downloadingIndex, token.data(), m_downloadingFilePath.data(), deviceId.data(), record_info->channelId, text.toStdString().c_str(), record_info->recordRegionId.toStdString().c_str(), 1000, 5000);
		slotSetShowInfo(tr("Cloud record downloading OpenApi requesting..."));
		emit sgnSetDownloadUI(m_downloadingIndex, true);
	}
	else {
		m_downloadingIndex = -1;
	}
}
