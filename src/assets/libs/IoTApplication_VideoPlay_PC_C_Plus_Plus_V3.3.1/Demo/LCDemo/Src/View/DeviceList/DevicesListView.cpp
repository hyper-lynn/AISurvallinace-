#include "DevicesListView.h"
#include <QDebug>

extern bool g_isReleasedForOverseas;

DevicesListView::DevicesListView(QWidget* parent)
: QWidget(parent)
{
    m_SeparatorLbl              = NULL;
    m_ToolBar                   = NULL;
    m_ReturnToLoginBtn          = NULL;
    m_AddDeviceBtn              = NULL;
    m_ScrollView                = NULL;
    m_DevicesListCtrlInstance   = NULL;
    m_ThreadCtrl                = NULL;
    m_ChannelInfoList           = NULL;
	m_IOTDeviceInfoList			= NULL;
    m_decryptKeyBox             = NULL;
    m_decryptKeyIndex           = -1;
}

DevicesListView::~DevicesListView()
{
    release();
}

int DevicesListView::init()
{
    int ret = 0;

    do 
    {
        this->resize(1022, 616);
        this->move(0, 0);

        m_SeparatorLbl = new (std::nothrow) QLabel(this);
        if (NULL == m_SeparatorLbl)
        {
            ret = -1;
            break;
        }
        m_SeparatorLbl->resize(this->width(), 1);
        m_SeparatorLbl->move(0, 0);
        m_SeparatorLbl->setStyleSheet("background-color:#fd8b30;");

        m_ToolBar = new (std::nothrow) QWidget(this);
        if (NULL == m_ToolBar)
        {
            ret = -1;
            break;
        }
        m_ToolBar->resize(this->width(), 42);
        m_ToolBar->move(0, 1);
        m_ToolBar->setStyleSheet("background-color:#2c2d30;");

        m_ReturnToLoginBtn = new (std::nothrow) IconTextBtn(m_ToolBar);
        if (NULL == m_ReturnToLoginBtn)
        {
            ret = -1;
            break;
        }
        //m_ReturnToLoginBtn->setBtnAttribute("Skin/common_icon_back", tr("Back"), 11, QColor(0xb0, 0xaf, 0xaf));
		m_ReturnToLoginBtn->setBtnAttribute("Skin/common_icon_back", "Back", 11, QColor(0xb0, 0xaf, 0xaf));
        m_ReturnToLoginBtn->move(22, 6);
        connect(m_ReturnToLoginBtn, SIGNAL(clicked()), this, SLOT(slotReturnToLogin()));

        m_AddDeviceBtn = new (std::nothrow) IconTextBtn(m_ToolBar);
        if (NULL == m_AddDeviceBtn)
        {
            ret = -1;
            break;
        }
        m_AddDeviceBtn->setBtnAttribute("Skin/common_icon_add", tr("Bind Device"), 11, QColor(0xb0, 0xaf, 0xaf));
        m_AddDeviceBtn->move(this->width() - m_AddDeviceBtn->width() - 30, 6);
		m_AddDeviceBtn->setVisible(false);
        connect(m_AddDeviceBtn, SIGNAL(clicked()), this, SLOT(slotShowAddDevice()));

        m_ScrollView = new (std::nothrow) BaseScrollView(this);
        if (NULL == m_ScrollView)
        {
            ret = -1;
            break;
        }
        m_ScrollView->resize(this->width(), this->height() - 43);
        m_ScrollView->move(0, 43);

        m_DevicesListCtrlInstance = DevicesListCtrl::getInstance();
        connect(this, SIGNAL(sgnGetChannelPic(int)), m_DevicesListCtrlInstance, SLOT(slotGetChannelPic(int)));
        connect(m_DevicesListCtrlInstance, SIGNAL(sgnGetChannelPicFinished(int, QPixmap)), this, SLOT(slotGetChannelPicFinished(int, QPixmap)));

        m_ThreadCtrl = new (std::nothrow) ThreadCtrl(this, PROTO_GET_DEVICES_LIST);
        if (NULL == m_ThreadCtrl)
        {
            ret = -1;
            break;
        }
        connect(m_ThreadCtrl, SIGNAL(resultReady(int)), this, SLOT(slotHandleResult(int)));

        m_decryptKeyBox = new (std::nothrow) MyEditBox(this);
        if (NULL == m_decryptKeyBox)
        {
            ret = -1;
            break;
        }
        //ret = m_decryptKeyBox->init(tr("Please Input Decrypt Key"));
		ret = m_decryptKeyBox->init("Please Input Decrypt Key");
        if (0 != ret)
        {
            break;
        }
        connect(m_decryptKeyBox, SIGNAL(sgnOK(QString)), this, SLOT(slotDecryptKeyBoxOK(QString)));
        m_decryptKeyBox->hide();

    } while (0);

    if (0 != ret)
    {
        release();
    }

    return ret;
}

void DevicesListView::release()
{
    clearDeviceViewVector();

    if (NULL != m_decryptKeyBox)
    {
        delete m_decryptKeyBox;
        m_decryptKeyBox = NULL;
    }

    if (NULL != m_ThreadCtrl)
    {
        m_ThreadCtrl->quit();
        m_ThreadCtrl->deleteLater();
    }

    if (NULL != m_ScrollView)
    {
        delete m_ScrollView;
        m_ScrollView = NULL;
    }

    if (NULL != m_AddDeviceBtn)
    {
        delete m_AddDeviceBtn;
        m_AddDeviceBtn = NULL;
    }

    if (NULL != m_ReturnToLoginBtn)
    {
        delete m_ReturnToLoginBtn;
        m_ReturnToLoginBtn = NULL;
    }

    if (NULL != m_ToolBar)
    {
        delete m_ToolBar;
        m_ToolBar = NULL;
    }

    if (NULL != m_SeparatorLbl)
    {
        delete m_SeparatorLbl;
        m_SeparatorLbl = NULL;
    }

	/*if (NULL != m_DevicesListCtrlInstance)
	{
		delete m_DevicesListCtrlInstance;
		m_DevicesListCtrlInstance = NULL;
	}

	if (NULL != m_IOTDeviceInfoList)
	{
		delete m_IOTDeviceInfoList;
		m_IOTDeviceInfoList = NULL;
	}*/

    return;
}

void DevicesListView::clearDeviceViewVector()
{
    for (int i = 0; i < m_DeviceViewVector.size(); i++)
    {
        delete m_DeviceViewVector.at(i);
    }
    m_DeviceViewVector.clear();

    return;
}

void DevicesListView::slotGetDevicesList()
{
    /* 涓嶄娇鑳藉姞杞借澶囧皝闈㈠浘锛岄槻姝㈣澶囧垪琛ㄨ娓呯┖鍚庡紩鍙戠殑鏁扮粍璁块棶瓒婄晫闂 */
    m_DevicesListCtrlInstance->enableLoadChannelPic(false);

    clearDeviceViewVector();
    m_ScrollView->m_rootWidget->setFixedHeight(m_ScrollView->height());

    m_DevicesListCtrlInstance->clearChannelInfoList();
	m_DevicesListCtrlInstance->clearIOTDeviceInfoList();
	m_DevicesListCtrlInstance->clearViewDeviceInfoList();
    m_IOTDeviceInfoList = m_DevicesListCtrlInstance->getIOTChannelInfoList();
    if (m_ThreadCtrl->isRunning())
    {
        m_ThreadCtrl->quit();
    }
    m_ThreadCtrl->setParamter(NULL, m_IOTDeviceInfoList);
    m_ThreadCtrl->start();

    return;
}

void DevicesListView::slotReturnToLogin()
{
    this->hide();
    emit sgnReturnToLogin();
    return;
}

void DevicesListView::slotShowAddDevice()
{
    this->hide();
    emit sgnShowAddDevice();
    return;
}

void DevicesListView::slotGetChannelPicFinished(int deviceIndex, QPixmap pixmap)
{
    if (!pixmap.isNull())
    {
        m_DeviceViewVector.at(deviceIndex)->setChannelPic(pixmap);
    }

    if (++deviceIndex < m_DeviceViewVector.size())
    {
        emit sgnGetChannelPic(deviceIndex);
    }

    return;
}

void DevicesListView::slotShowDeviceOperate(int deviceIndex)
{
    this->hide();
    emit sgnShowDeviceOperate(deviceIndex);
    return;
}

void DevicesListView::slotPlay(int deviceIndex)
{
    this->hide();
    emit sgnPlay(deviceIndex);
    return;
}

void DevicesListView::slotShowLocalRecord(int deviceIndex)
{
    this->hide();
    emit sgnShowLocalRecord(deviceIndex);
    return;
}

void DevicesListView::slotShowCloudRecord(int deviceIndex)
{
    this->hide();
    emit sgnShowCloudRecord(deviceIndex);
    return;
}



void DevicesListView::slotHandleResult(int result)
{
    if (1 == result)
    {
        QPixmap channelPixmap;
        int deviceViewHeight = 0;
        if (g_isReleasedForOverseas)
        {
            channelPixmap.load("Skin/big_morenfengmian_en.png");
            deviceViewHeight = 288;
        } 
        else
        {
            channelPixmap.load("Skin/big_morenfengmian.png");
            deviceViewHeight = 256;
        }
		if (m_IOTDeviceInfoList->size() > 0)
		{
			int viewIndex = 0; // Global index for positioning in grid
			for (int k = 0; k < m_IOTDeviceInfoList->size(); k++)
			{
				IOTDeviceList* deviceInfo = m_IOTDeviceInfoList->at(k);
				if (deviceInfo->iotChannel.size() > 1)
				{
					// Multi-channel device (e.g. NVR): show each channel as a separate card
					for (int i = 0; i < deviceInfo->iotChannel.size(); i++)
					{
						if (m_ScrollView->m_rootWidget->height() < viewIndex / 3 * deviceViewHeight + deviceViewHeight + 28)
						{
							m_ScrollView->m_rootWidget->setFixedHeight(viewIndex / 3 * deviceViewHeight + deviceViewHeight + 28);
						}
						DeviceView* deviceView = new (std::nothrow) DeviceView(m_ScrollView->m_rootWidget);
						if (NULL == deviceView)
						{
							return;
						}
						if (0 != deviceView->init())
						{
							return;
						}
						deviceView->setDeviceIndex(viewIndex);
						QString chanName = QString::fromStdString(deviceInfo->deviceId)
							+ "(" + QString::fromStdString(deviceInfo->iotChannel.at(i)->channelId) + ")";
						deviceView->setChannelName(chanName);
						std::string isOnline = deviceInfo->iotChannel.at(i)->channelStatus;

						qDebug() << "isOnline: " << isOnline.c_str();
						deviceView->setChannelPic(channelPixmap);

						if (isOnline == "sleep")
						{
							qDebug() << "sleep: " << isOnline.c_str();
							deviceView->setSleepStatus();
						}
						else if (isOnline != "online")
						{
							qDebug() << "offline: " << isOnline.c_str();
							deviceView->setOfflineStatus();
						}
						else if ("1" == deviceInfo->encryptMode)
						{
							//deviceView->setDecryptStatus(true);
						}
						connect(deviceView, SIGNAL(sgnShowDeviceOperate(int)), this, SLOT(slotShowDeviceOperate(int)));
						connect(deviceView, SIGNAL(sgnPlay(int)), this, SLOT(slotPlay(int)));
						connect(deviceView, SIGNAL(sgnShowLocalRecord(int)), this, SLOT(slotShowLocalRecord(int)));
						connect(deviceView, SIGNAL(sgnShowCloudRecord(int)), this, SLOT(slotShowCloudRecord(int)));
						connect(deviceView, SIGNAL(sgnGetDevicesList()), this, SLOT(slotGetDevicesList()));
						connect(deviceView, SIGNAL(sgnDecryptShadeClicked(int)), this, SLOT(slotShowDecryptKeyBox(int)));
						deviceView->move(28 + 326 * (viewIndex % 3), 28 + deviceViewHeight * (viewIndex / 3));
						deviceView->show();

						m_DeviceViewVector.push_back(deviceView);
					m_DevicesListCtrlInstance->addViewDeviceInfo(k, i);
					viewIndex++;
					}
				}
				else
				{
					// Single-channel or no-channel device (e.g. IPC): show device as one card
					if (m_ScrollView->m_rootWidget->height() < viewIndex / 3 * deviceViewHeight + deviceViewHeight + 28)
					{
						m_ScrollView->m_rootWidget->setFixedHeight(viewIndex / 3 * deviceViewHeight + deviceViewHeight + 28);
					}
					DeviceView* deviceView = new (std::nothrow) DeviceView(m_ScrollView->m_rootWidget);
					if (NULL == deviceView)
					{
						return;
					}
					if (0 != deviceView->init())
					{
						return;
					}
					deviceView->setDeviceIndex(viewIndex);
					QString chanName = QString::fromStdString(deviceInfo->deviceId);
					deviceView->setChannelName(chanName);
					std::string isOnline = deviceInfo->deviceStatus;

					qDebug() << "isOnline: " << isOnline.c_str();
					deviceView->setChannelPic(channelPixmap);

					if (isOnline == "sleep")
					{
						qDebug() << "sleep: " << isOnline.c_str();
						deviceView->setSleepStatus();
					}
					else if (isOnline != "online")
					{
						qDebug() << "offline: " << isOnline.c_str();
						deviceView->setOfflineStatus();
					}
					else if ("1" == deviceInfo->encryptMode)
					{
						//deviceView->setDecryptStatus(true);
					}
					connect(deviceView, SIGNAL(sgnShowDeviceOperate(int)), this, SLOT(slotShowDeviceOperate(int)));
					connect(deviceView, SIGNAL(sgnPlay(int)), this, SLOT(slotPlay(int)));
					connect(deviceView, SIGNAL(sgnShowLocalRecord(int)), this, SLOT(slotShowLocalRecord(int)));
					connect(deviceView, SIGNAL(sgnShowCloudRecord(int)), this, SLOT(slotShowCloudRecord(int)));
					connect(deviceView, SIGNAL(sgnGetDevicesList()), this, SLOT(slotGetDevicesList()));
					connect(deviceView, SIGNAL(sgnDecryptShadeClicked(int)), this, SLOT(slotShowDecryptKeyBox(int)));
					deviceView->move(28 + 326 * (viewIndex % 3), 28 + deviceViewHeight * (viewIndex / 3));
					deviceView->show();

					m_DeviceViewVector.push_back(deviceView);
					m_DevicesListCtrlInstance->addViewDeviceInfo(k, -1);
					viewIndex++;
				}
			}
		}
		else 
		{
			qDebug() << "no device ! ";
		}
    }
    else
    {
        /* 鎻愮ず鑾峰彇璁惧鍒楄〃澶辫触 */
    }

    if (m_DeviceViewVector.size() > 0)
    {
        /* 浣胯兘鍔犺浇璁惧灏侀潰鍥?*/
        m_DevicesListCtrlInstance->enableLoadChannelPic(true);

        emit sgnGetChannelPic(0);
    }

    return;
}

void DevicesListView::slotShowDecryptKeyBox(int decryptKeyIndex)
{
    m_decryptKeyIndex = decryptKeyIndex;
    m_decryptKeyBox->show();
}

void DevicesListView::slotDecryptKeyBoxOK(QString decryptKey)
{
    if (decryptKey.isEmpty())
    {
        return;
    }
    if (m_DeviceViewVector.size() < m_decryptKeyIndex + 1)
    {
        return;
    }
    m_IOTDeviceInfoList->at(m_decryptKeyIndex)->decryptKey = decryptKey.toStdString();
    m_DeviceViewVector.at(m_decryptKeyIndex)->setDecryptStatus(false);
}
