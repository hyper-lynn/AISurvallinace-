#include <QPainter>
#include <QLabel>
#include <QDir>
#include <QJsonDocument>
#include <QJsonObject>
#include "Ctrl/RecordListCtrl.h"
#include "Ctrl/OpenApiCtrl.h"
#include "Ctrl/DevicesListCtrl.h"
#include "Utils/global.h"
#include "Utils/CommonView/ScrollView.h"
#include "Utils/CommonView/IconTextBtn.h"
#include "Utils/CommonView/SearchBar.h"
#include "Utils/CommonView/Calendar.h"
#include "Utils/CommonView/SplitLine.h"
#include "RecordListView.h"
#include <QJsonObject>

extern bool g_isReleasedForOverseas;

RecordListView::RecordListView(QWidget *parent)
	: QWidget(parent)
    , m_viewCtrl(NULL)
    , m_isInit(false)
    , m_deviceId("")
    , m_channelId(0)
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
/* Set listener, refresh UI when data is ready */
    m_lcopensdkDownloadInstance->setDownloadListener(NULL);

/* Get record list, if data is not ready it will be fetched asynchronously and callback when ready */
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
        //m_btnBack->setBtnAttribute("Skin/common_icon_back", tr("Back to Devices List"), 11, QColor(0xb0, 0xaf, 0xaf));
		m_btnBack->setBtnAttribute("Skin/common_icon_back", "Back to Devices List", 11, QColor(0xb0, 0xaf, 0xaf));
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
        connect(m_searchBar, SIGNAL(sgnSearch(QString)), this, SLOT(slotSearch( QString)));

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

void RecordListView::fillBackGroundWithColor(QWidget *widget, const QColor& color)
{
    if (NULL == widget)
    {
        return;
    }

    widget->setAutoFillBackground(true);
    QPalette palette;
    palette.setColor(QPalette::Window, color);
    widget->setPalette(palette);
}

void RecordListView::refreshLayout()
{
    if (!m_isInit)
    {
        DLOG("please call init() first!!!\n");
        return;
    }

/*Get device record list*/
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
/*clear child view. If not cleared, the next clear may cause repeated deletion*/
        m_scrollView->reset();
    }
}

void RecordListView::onDownloadReceiveData(int index, int datalen)
{
    m_downloadLength += datalen;
/* easy4ip get record list interface */
    if (g_isReleasedForOverseas)
    {
        return;
    }
    emit sgnDownloadPercent(index, m_downloadLength * 100 / m_fileLength);
    return;
}

void RecordListView::onDownloadState(int index, const char* code, int type)
{
    QString strInfo;
    if (99 == type)
    {
        emit sgnCancelDownload(index);
        strInfo = ("OpenApi request failed[") + 
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
            strInfo = ("Download failed and stopped[") + 
                      QString::number(index, 10) + 
                      QString("]!");
        } 
        else if (0 == strcmp("1", code))
        {
            strInfo = ("Start to download! index[") + 
                      QString::number(index, 10) + 
                      QString("]!");
        }
        else if (0 == strcmp("2", code))
        {
            m_downloadingIndex = -1;
            strInfo = ("Download finished[") + QString::number(index, 10) + QString("]!");
            emit sgnSetDownloadUI(index, false);
        }
        else if (0 == strcmp("7", code))
        {
            emit sgnCancelDownload(index);
            remove(m_downloadingFilePath.data());
            strInfo = ("Download timed out and stopped[") + 
                      QString::number(index, 10) + 
                      QString("]!");
        }
		else if (0 == strcmp("9", code))
		{
			DLOG(" download slice finished !!!\n");
			return;
		}
        else if (0 == strcmp("11", code))
        {
            emit sgnCancelDownload(index);
            remove(m_downloadingFilePath.data());
            strInfo = ("Decrypt key error and download stopped[") + 
                QString::number(index, 10) + 
                QString("]!");
        }
    }
    else if (0 == type)
    {
        if (0 == strcmp("1", code))
        {
            emit sgnCancelDownload(index);
            remove(m_downloadingFilePath.data());
            strInfo = ("Download failed and stopped[") + 
                QString::number(index, 10) + 
                QString("]!");
        } 
        else if (0 == strcmp("4", code))
        {
            strInfo = ("Start to download! index[") + 
                QString::number(index, 10) + 
                QString("]!");
        }
        else if (0 == strcmp("5", code))
        {
            m_downloadingIndex = -1;
            strInfo = ("Download finished[") + QString::number(index, 10) + QString("]!");
            emit sgnSetDownloadUI(index, false);
        }
        else if (0 == strcmp("7", code))
        {
            emit sgnCancelDownload(index);
            remove(m_downloadingFilePath.data());
            strInfo = ("Decrypt key error and download stopped[") + 
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
			strInfo = ("Download failed code -1 and stopped[") +
				QString::number(index, 10) +
				QString("]!");
		}
		else if (0 == strcmp("408000", code))
		{
			emit sgnCancelDownload(index);
			remove(m_downloadingFilePath.data());
			strInfo = ("Download failed 408000 and stopped[") +
				QString::number(index, 10) +
				QString("]!");
		}
		else if (0 == strcmp("1000", code))
		{
			strInfo = ("Start to download[") +
				QString::number(index, 10) +
				QString("]!");
		}
		else if (0 == strcmp("2000", code))
		{
			m_downloadingIndex = -1;
			strInfo = ("Download finished! index[") + QString::number(index, 10) + QString("]!");
			emit sgnSetDownloadUI(index, false);
		}

	}
    emit sgnSetShowInfo(strInfo);
}

void RecordListView::onDownloadProgress(int index, float progress, int type)
{
	QString strInfo = QString("Download index[%1] Progress: %2%")
		.arg(index)
		.arg(progress * 100, 0, 'f', 2);
	emit sgnSetShowInfo(strInfo);
	//if (progress >= 0.999)
	//{
	//	emit sgnSetDownloadUI(index, false);
	//	m_lcopensdkDownloadInstance->stopDownload(index);
	//	m_downloadingIndex = -1;
	//	strInfo = ("Download finished! index[") + QString::number(index, 10) + QString("]!");
	//	//emit sgnSetShowInfo(strInfo);
	//}

}

void RecordListView::onThumbnailState(int index, int code)
{
	if (code == 0) 
	{
		DLOG("thumbnail fail!!!\n");
	}
	else
	{
		DLOG("thumbnail success!!!\n");
	}
}

void RecordListView::slotSetShowInfo(QString info)
{
    if (!m_isInit)
    {
        DLOG("please call init() first!!!\n");
        return;
    }

    m_showInfo->setText("Status>>>" + info);
	//m_showInfo->setText(tr("Status>>>") + info);
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
    this->show();

/* Set cloud record list */
    m_viewCtrl->setRecordType(m_recordType);
    m_calendar->setSelectedDate(m_searchDate);
    int ret = m_viewCtrl->getRecordInfoAsyn(m_deviceIndex, m_searchDate);
    if (RecordListCtrl::ERR_SEARCHING == ret)
    {
        slotSetShowInfo("Query too frequently!");
    }
    else if (RecordListCtrl::ERR_GET_CHANNELINFO == ret)
    {
        //slotSetShowInfo(tr("Get device information failed!"));
		slotSetShowInfo("Get device information failed!");
    }
    else if (RecordListCtrl::ERR_SUCCESS == ret)
    {
        slotSetText(m_searchDate);
        m_deviceId = m_viewCtrl->getDeviceId();

        //slotSetShowInfo(tr("Getting device records list..."));
		slotSetShowInfo("Device records list");

/* Add record item (cloud or device record...) */
        QString text = m_labelChannelName->fontMetrics().elidedText("Channel Name : " + RecordListCtrl::getInstance()->getChannelName(),
            Qt::ElideRight, 300, Qt::TextShowMnemonic);
        m_labelChannelName->setText(text);
        m_labelChannelName->adjustSize();
    }
    else
    {
        //slotSetShowInfo(tr("Unknown error!"));
		slotSetShowInfo("Unknown error!");
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
    this->show();

/* Set device record list */
    m_viewCtrl->setRecordType(m_recordType);
    m_calendar->setSelectedDate(m_searchDate);
    int ret = m_viewCtrl->getRecordInfoAsyn(m_deviceIndex, m_searchDate);
    if (RecordListCtrl::ERR_SEARCHING == ret)
    {
        slotSetShowInfo("Query too frequently!");
    }
    else if (RecordListCtrl::ERR_GET_CHANNELINFO == ret)
    {
        slotSetShowInfo("Get device information failed!");
    }
    else if (RecordListCtrl::ERR_SUCCESS == ret)
    {
        slotSetText(m_searchDate);
        m_deviceId = m_viewCtrl->getDeviceId();

        slotSetShowInfo("Getting cloud records list...");

/* Add record item (cloud or device record...) */
        QString text = m_labelChannelName->fontMetrics().elidedText("Channel Name : " + RecordListCtrl::getInstance()->getChannelName(),
            Qt::ElideRight, 300, Qt::TextShowMnemonic);
        m_labelChannelName->setText(text);
        m_labelChannelName->adjustSize();
    }
    else
    {
        slotSetShowInfo("Unknown error!");
    }
}

void RecordListView::slotBackBtnClicked()
{
    DLOG("slotBackBtnClicked\n");

/* Clear and refresh all record items */
    if (m_downloadingIndex >= 0)
    {
        emit sgnCancelDownload(m_downloadingIndex);
        remove(m_downloadingFilePath.data());
    }

    m_searchDate = QDate::currentDate();

    this->hide();
/* Get device list */
    emit sgnReturnToDevicesList(false);
}

void RecordListView::slotRecordThreadResult(int result)
{
    if (!m_isInit)
    {
        DLOG("please call init() first!!!\n");
        return;
    }

/* Clear scrollwView */
    m_scrollView->reset();

    QString strInfo;
    if (result > 0)
    {
        strInfo = "Get records list succeed[" + 
                  QString::number(result, 10) + 
                  QString("]!");
    }
    else if (0 == result)
    {
        //strInfo = tr("There is no record for current date!");
		strInfo = "There is no record for current date!";
    }
    else
    {
        strInfo = "Get records list failed[" + 
                  QString::number(result, 10) + 
                  QString("]!");
    }
    slotSetShowInfo(strInfo);
    if (result <= 0)
    {
/* result download progress */
        return;
    }

/* Clear current scrollview */
    RECORD_CHILD *info = NULL;
    const RECORD_INFO_LIST *infoList = m_viewCtrl->getRecordInfoList();
    RECORD_INFO_LIST::const_iterator iter = infoList->begin();
    for ( ; iter != infoList->end(); ++iter)
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

/* Download status update */
    QString decryptKey = DevicesListCtrl::getInstance()->getDecryptKeyByDeviceID(m_deviceId);
    m_scrollView->refresh(decryptKey);
}

void RecordListView::slotPlayBtnClicked(int recordIndex)
{
    if (m_downloadingIndex >= 0)
    {
        slotSetShowInfo("Downloading record!");
        return;
    }

    this->hide();

    if (DEVICE_RECORD == m_recordType)
    {
        emit sgnPlayDeviceRecord(m_deviceIndex, recordIndex);
    }
    else if (CLOUD_RECORD == m_recordType)
    {
        emit sgnPlayCloudRecord(m_deviceIndex, recordIndex);
    }
}

void RecordListView::slotDownloadBtnClicked(int index)
{
/* Start downloading record storage */
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
        slotSetShowInfo("Downloading record!");
        return;
    }

    m_downloadingIndex = index;

    QByteArray token = OpenApiCtrl::getInstance()->getToken().toLatin1();

	const RECORD_INFO* record_info =  RecordListCtrl::getInstance()->getRecordInfoByIndex(index);
    // const RECORD_INFO* record_info = m_viewCtrl->getRecordInfoByIndex(index);

///* Convert beginTime to string strBeginTime */
    //QString beginTime = record_info->beginTime;
    QString strBeginTime;
    for (int i = 0; i < record_info->beginTime.length(); i++)
    {
        if (record_info->beginTime.at(i).toLatin1() >= '0' && record_info->beginTime.at(i).toLatin1() <= '9')
        {
            strBeginTime.append(record_info->beginTime.at(i));
        }
    }

	QDateTime beginTime = QDateTime::fromString(record_info->beginTime, "yyyy-MM-dd HH:mm:ss");
	QDateTime endTime = QDateTime::fromString(record_info->endTime, "yyyy-MM-dd HH:mm:ss");

    QByteArray deviceId = record_info->deviceId.toLatin1();
	QByteArray decryptKey = deviceId;
    m_fileLength = record_info->fileLength;
    m_downloadLength = 0;

/* Get device channel info nvr getIOTChannelInfo 1*/
	IOTDeviceList *iotDeviceList;
	iotDeviceList = DevicesListCtrl::getInstance()->getIOTChannelInfo(m_deviceIndex);
	if (NULL == iotDeviceList)
	{
		return;
	}
	std::string playInfo = iotDeviceList->playInfo;

/* May need to reload record list and refresh UI */
    //QString decryptKey = DevicesListCtrl::getInstance()->getDecryptKeyByDeviceID(deviceId);
    if (CLOUD_RECORD == m_recordType)
    {
        m_downloadingFilePath = QString(m_cloudRecordsDir + "/" + strBeginTime + "_download_" + record_info->recId + ".mp4").toLatin1();

		m_lcopensdkDownloadInstance->startCloudDownload(index, m_downloadingFilePath.data(), deviceId.data(), record_info->channelId, record_info->recId.toStdString().c_str(),
			beginTime.toTime_t(), endTime.toTime_t(),0, playInfo.c_str(), record_info->signatureUrl.toStdString().c_str(), record_info->recordPath.toStdString().c_str(), record_info->recordRegionId.toStdString().c_str());

        slotSetShowInfo("Cloud record downloading...");
    }

    else if (DEVICE_RECORD == m_recordType)
    {
		
		/*QDateTime beginTime = QDateTime::fromString(record_info->beginTime, "yyyy-MM-dd HH:mm:ss");
		QDateTime endTime = QDateTime::fromString(record_info->endTime, "yyyy-MM-dd HH:mm:ss")*/;
		// playInfo
		
        m_downloadingFilePath = QString(m_deviceRecordsDir + "/" + record_info->deviceId + "_download_" + strBeginTime + ".mp4").toLatin1();

        m_lcopensdkDownloadInstance->startDownload(index, record_info->token.toStdString().c_str(), m_downloadingFilePath.data(), deviceId.data(),
			 iotDeviceList->decryptKey.c_str(), record_info->name.toStdString().c_str(), beginTime.toTime_t(), endTime.toTime_t(), playInfo.c_str(), record_info->channelId);
        slotSetShowInfo("Device record downloading...");
    }
    emit sgnSetDownloadUI(index, true);
}

void RecordListView::slotCancelBtnClicked(int index)
{
    m_lcopensdkDownloadInstance->stopDownload(index);
    remove(m_downloadingFilePath.data());
    m_downloadingIndex = -1;
    QString strInfo = "Cancel downloading[" + 
                      QString::number(index, 10) + 
                      QString("]!");
    slotSetShowInfo(strInfo);
    emit sgnSetDownloadUI(index, false);
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

/* Download completed, update item status */
    if (m_downloadingIndex >= 0)
    {
        emit sgnCancelDownload(m_downloadingIndex);
        remove(m_downloadingFilePath.data());
    }

    /*clear-child view*/
    m_scrollView->reset();
/* Clear items */
    m_viewCtrl->clearRecordList();

/* Clear record list and refresh UI */
    m_searchDate = QDate::fromString(date, "yyyy-MM-dd");
    m_calendar->setSelectedDate(m_searchDate);
    int ret = m_viewCtrl->getRecordInfoAsyn(m_deviceIndex, m_searchDate);
    if (RecordListCtrl::ERR_SEARCHING == ret)
    {
        //slotSetShowInfo(tr("Query too frequently!"));
		slotSetShowInfo("Query too frequently!");
    }
    else if (RecordListCtrl::ERR_GET_CHANNELINFO == ret)
    {
        //slotSetShowInfo(tr("Get device information failed!"));
		slotSetShowInfo("Get device information failed!");
    }
    else if (RecordListCtrl::ERR_SUCCESS == ret)
    {
        //slotSetShowInfo(tr("Getting records list..."));
		slotSetShowInfo("Getting records list...");
    }
    else
    {
        //slotSetShowInfo(tr("Unknown error!"));
		slotSetShowInfo("Unknown error!");
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

