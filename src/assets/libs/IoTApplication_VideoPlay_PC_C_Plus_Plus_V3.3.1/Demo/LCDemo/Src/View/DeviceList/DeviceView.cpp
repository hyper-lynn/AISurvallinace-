#include "DeviceView.h"
#include "Utils/CommonView/MyMessageBox.h"

extern bool g_isReleasedForOverseas;

DeviceView::DeviceView(QWidget* parent)
:QWidget(parent)
{
    m_ChannelPicLbl             = NULL;
    m_PlayBtn                   = NULL;
    m_OfflineLbl                = NULL;
    m_ChannelNameLbl            = NULL;
    m_DeviceRemoveBtn           = NULL;
    m_DeviceRecordBtn            = NULL;
    m_CloudRecordBtn            = NULL;

    m_DeviceOperateBtn          = NULL;
    m_TopShade                  = NULL;
    m_BottomShade               = NULL;
    m_DeviceIndex               = -1;
    m_OpenApiCtrlInstance       = NULL;
    m_DevicesListCtrlInstance   = NULL;
    m_decryptShade              = NULL;
}

DeviceView::~DeviceView()
{
    release();
}

int DeviceView::init()
{
    int ret = 0;

    do 
    {
        if (g_isReleasedForOverseas)
        {
            this->resize(306, 268);
        } 
        else
        {
            this->resize(306, 236);
        }
        this->setAutoFillBackground(true);
        QPalette palette;
        palette.setColor(QPalette::Window, QColor(0x2c, 0x2d, 0x30));
        this->setPalette(palette);

        m_ChannelPicLbl = new (std::nothrow) QLabel(this);
        if (NULL == m_ChannelPicLbl)
        {
            ret = -1;
            break;
        }
        m_ChannelPicLbl->resize(this->width(), 172);
        m_ChannelPicLbl->move(0, 0);
        m_ChannelPicLbl->setScaledContents(true);

        m_PlayBtn = new (std::nothrow) IconBtn(m_ChannelPicLbl, "Skin/common_icon_btn_play");
        if (NULL == m_PlayBtn)
        {
            ret = -1;
            break;
        }
        m_PlayBtn->setAttribute(Qt::WA_TranslucentBackground);
        m_PlayBtn->move((m_ChannelPicLbl->width() - m_PlayBtn->width()) / 2, (m_ChannelPicLbl->height() - m_PlayBtn->height()) / 2);
        connect(m_PlayBtn, SIGNAL(clicked()), this, SLOT(slotPlay()));

        m_OfflineLbl = new (std::nothrow) QLabel(m_ChannelPicLbl);
        if (NULL == m_OfflineLbl)
        {
            ret = -1;
            break;
        }
        m_OfflineLbl->resize(m_ChannelPicLbl->width(), 40);
        m_OfflineLbl->move(0, (m_ChannelPicLbl->height() - m_OfflineLbl->height()) / 2);
        m_OfflineLbl->setStyleSheet("background:transparent;color:#d7d5d5;font:18pt;font-family:Microsoft YaHei;");
        //m_OfflineLbl->setText(tr("Offline"));
		m_OfflineLbl->setText("Offline");
        m_OfflineLbl->setAlignment(Qt::AlignCenter);
        m_OfflineLbl->hide();

        m_ChannelNameLbl = new (std::nothrow) QLabel(this);
        if (NULL == m_ChannelNameLbl)
        {
            ret = -1;
            break;
        }
        m_ChannelNameLbl->resize(258, 16);
        m_ChannelNameLbl->move(12, 180);
        m_ChannelNameLbl->setStyleSheet("color:#d7d5d5;font:11pt;font-family:Microsoft YaHei;");

        m_DeviceRemoveBtn = new (std::nothrow) IconBtn(this, "Skin/devicelist_icon_delete");
        if (NULL == m_DeviceRemoveBtn)
        {
            ret = -1;
            break;
        }
        m_DeviceRemoveBtn->move(this->width() - m_DeviceRemoveBtn->width() - 8, 174);
		m_DeviceRemoveBtn->setVisible(false); //no remove device business, set button invisible.
        connect(m_DeviceRemoveBtn, SIGNAL(clicked()), this, SLOT(slotDeviceRemove()));

        m_DeviceRecordBtn = new (std::nothrow) RoundRectTextBtn(this);
        if (NULL == m_DeviceRecordBtn)
        {
            ret = -1;
            break;
        }
        if (g_isReleasedForOverseas)
        {
            m_DeviceRecordBtn->setBtnAttribute(QString("Skin/devicelist_btn_en"), QColor(0x83, 0x83, 0x83), QColor(0xbb, 0xbb, 0xbb), 9);
        } 
        else
        {
            m_DeviceRecordBtn->setBtnAttribute(QString("Skin/devicelist_btn"), QColor(0x83, 0x83, 0x83), QColor(0xbb, 0xbb, 0xbb), 9);
        }
        m_DeviceRecordBtn->move(12, 204);

        //m_DeviceRecordBtn->setText(tr("Device Record"));
		m_DeviceRecordBtn->setText("Device Record");
        connect(m_DeviceRecordBtn, SIGNAL(clicked()), this, SLOT(slotShowLocalRecord()));

        m_CloudRecordBtn = new (std::nothrow) RoundRectTextBtn(this);
        if (NULL == m_CloudRecordBtn)
        {
            ret = -1;
            break;
        }
        if (g_isReleasedForOverseas)
        {
            m_CloudRecordBtn->setBtnAttribute(QString("Skin/devicelist_btn_en"), QColor(0x83, 0x83, 0x83), QColor(0xbb, 0xbb, 0xbb), 9);
            m_CloudRecordBtn->move(157, 204);
			//m_CloudRecordBtn->setVisible(false);//no cloud record business, set button invisible.
        } 
        else
        {
            m_CloudRecordBtn->setBtnAttribute(QString("Skin/devicelist_btn"), QColor(0x83, 0x83, 0x83), QColor(0xbb, 0xbb, 0xbb), 9);
            m_CloudRecordBtn->move(86, 204);
			//m_CloudRecordBtn->setVisible(false);//no cloud record business, set button invisible.
        }
        m_CloudRecordBtn->setText("Cloud Record");
        connect(m_CloudRecordBtn, SIGNAL(clicked()), this, SLOT(slotShowCloudRecord()));



        m_DeviceOperateBtn = new (std::nothrow) RoundRectTextBtn(this);
        if (NULL == m_DeviceOperateBtn)
        {
            ret = -1;
            break;
        }
        if (g_isReleasedForOverseas)
        {
            m_DeviceOperateBtn->setBtnAttribute(QString("Skin/devicelist_btn_en"), QColor(0x83, 0x83, 0x83), QColor(0xbb, 0xbb, 0xbb), 9);
            m_DeviceOperateBtn->move(157, 236);
        } 
        else
        {
            m_DeviceOperateBtn->setBtnAttribute(QString("Skin/devicelist_btn"), QColor(0x83, 0x83, 0x83), QColor(0xbb, 0xbb, 0xbb), 9);
            m_DeviceOperateBtn->move(234, 204);
        }
		m_DeviceOperateBtn->setVisible(false);// no operation device business, so set button invisible.
        m_DeviceOperateBtn->setText(tr("Device Setting"));
        connect(m_DeviceOperateBtn, SIGNAL(clicked()), this, SLOT(slotShowDeviceOperate()));

        m_TopShade = new (std::nothrow) QWidget(this);
        if (NULL == m_TopShade)
        {
            ret = -1;
            break;
        }
        m_TopShade->resize(m_ChannelPicLbl->size());
        m_TopShade->move(0, 0);
        m_TopShade->setStyleSheet("background-color:rgba(0, 0, 0, 20%);");
        m_TopShade->setAttribute(Qt::WA_TransparentForMouseEvents);
        m_TopShade->hide();

        m_BottomShade = new (std::nothrow) QWidget(this);
        if (NULL == m_BottomShade)
        {
            ret = -1;
            break;
        }
        if (g_isReleasedForOverseas)
        {
            m_BottomShade->resize(this->width(), 68);
        } 
        else
        {
            m_BottomShade->resize(this->width(), 36);
        }
        m_BottomShade->move(0, 200);
        m_BottomShade->setStyleSheet("background-color:rgba(0, 0, 0, 20%);");
        m_BottomShade->hide();

        m_OpenApiCtrlInstance = OpenApiCtrl::getInstance();
        m_DevicesListCtrlInstance = DevicesListCtrl::getInstance();

        m_decryptShade = new (std::nothrow) CheckBtn(this);
        if (NULL == m_decryptShade)
        {
            ret = -1;
            break;
        }
        m_decryptShade->resize(m_ChannelPicLbl->size());
        m_decryptShade->move(0, 0);
        m_decryptShade->setStyleSheet("background-color:rgba(0, 0, 0, 20%);color:#d7d5d5;font:14pt;font-family:Microsoft YaHei;");
        m_decryptShade->setText(tr("Please Click to Input Decrypt Key"));
        m_decryptShade->setAlignment(Qt::AlignCenter);
        m_decryptShade->hide();
        connect(m_decryptShade, SIGNAL(clicked()), this, SLOT(slotDecryptShadeClicked()));

    } while (0);

    if (0 != ret)
    {
        release();
    }

    return ret;
}

void DeviceView::release()
{
    if (NULL != m_decryptShade)
    {
        delete[] m_decryptShade;

        m_decryptShade = NULL;
    }

    if (NULL != m_BottomShade)
    {
        delete[] m_BottomShade;
        m_BottomShade = NULL;
    }

    if (NULL != m_TopShade)
    {
        delete[] m_TopShade;
        m_TopShade = NULL;
    }

    if (NULL != m_DeviceOperateBtn)
    {
        delete[] m_DeviceOperateBtn;
        m_DeviceOperateBtn = NULL;
    }



    if (NULL != m_CloudRecordBtn)
    {
        delete[] m_CloudRecordBtn;
        m_CloudRecordBtn = NULL;
    }

    if (NULL != m_DeviceRecordBtn)
    {
        delete[] m_DeviceRecordBtn;
        m_DeviceRecordBtn = NULL;
    }

    if (NULL != m_DeviceRemoveBtn)
    {
        delete[] m_DeviceRemoveBtn;
        m_DeviceRemoveBtn = NULL;
    }

    if (NULL != m_ChannelNameLbl)
    {
        delete[] m_ChannelNameLbl;
        m_ChannelNameLbl = NULL;
    }

    if (NULL != m_OfflineLbl)
    {
        delete[] m_OfflineLbl;
        m_OfflineLbl = NULL;
    }

    if (NULL != m_PlayBtn)
    {
        delete[] m_PlayBtn;
        m_PlayBtn = NULL;
    }

    if (NULL != m_ChannelPicLbl)
    {
        delete[] m_ChannelPicLbl;
        m_ChannelPicLbl = NULL;
    }

    return;
}

void DeviceView::setDeviceIndex(int deviceIndex)
{
    m_DeviceIndex = deviceIndex;
}

void DeviceView::setChannelName(const QString& channelName)
{
    m_ChannelNameLbl->setText(channelName);
}

void DeviceView::setChannelPic(const QPixmap& pixmap)
{
    m_ChannelPicLbl->setPixmap(pixmap);
}

void DeviceView::setOfflineStatus()
{
    m_PlayBtn->hide();
    m_OfflineLbl->setText("Offline");
    m_OfflineLbl->resize(70, 24);
    m_OfflineLbl->move(8, 8);
    m_OfflineLbl->setStyleSheet("background-color:rgba(0, 0, 0, 150);color:#aaaaaa;font:10pt;font-family:Microsoft YaHei;border-radius:4px;");
    m_OfflineLbl->setAlignment(Qt::AlignCenter);
    m_OfflineLbl->show();
    m_TopShade->show();
    m_BottomShade->show();
}

void DeviceView::setSleepStatus()
{
    /* Sleep device: show "Sleep" tag at top-left, keep play button visible for wake-up */
    m_OfflineLbl->setText("Sleep");
    m_OfflineLbl->resize(60, 24);
    m_OfflineLbl->move(8, 8);
    m_OfflineLbl->setStyleSheet("background-color:rgba(0, 0, 0, 150);color:#ffa500;font:10pt;font-family:Microsoft YaHei;border-radius:4px;");
    m_OfflineLbl->setAlignment(Qt::AlignCenter);
    m_OfflineLbl->show();
    m_TopShade->show();
    /* Play button remains visible, device can be woken up by streaming */
}

void DeviceView::setDecryptStatus(bool flag)
{
    if (flag)
    {
        m_PlayBtn->hide();
        m_decryptShade->show();
        m_BottomShade->show();
    } 
    else
    {
        m_BottomShade->hide();
        m_decryptShade->hide();
        m_PlayBtn->show();
    }
}

void DeviceView::slotShowDeviceOperate()
{
    emit sgnShowDeviceOperate(m_DeviceIndex);
    return;
}

void DeviceView::slotDeviceRemove()
{
    if (MyMessageBox::Accepted == MyMessageBox::warning(this, tr("Prompt"), tr("Be Sure to Delete This Device?")))
    {
        ChannelInfo* channelInfo = m_DevicesListCtrlInstance->getChannelInfo(m_DeviceIndex);
        if (NULL != channelInfo)
        {
            QString deviceId = channelInfo->deviceId;
            if (m_OpenApiCtrlInstance->unBindDevice(deviceId))
            {
                emit sgnGetDevicesList();
            }
        }
    }
    return;
}

void DeviceView::slotPlay()
{
    emit sgnPlay(m_DeviceIndex);
    return;
}

void DeviceView::slotShowLocalRecord()
{
    emit sgnShowLocalRecord(m_DeviceIndex);
    return;
}

void DeviceView::slotShowCloudRecord()
{
    emit sgnShowCloudRecord(m_DeviceIndex);
    return;
}



void DeviceView::slotDecryptShadeClicked()
{
    emit sgnDecryptShadeClicked(m_DeviceIndex);
    return;
}
