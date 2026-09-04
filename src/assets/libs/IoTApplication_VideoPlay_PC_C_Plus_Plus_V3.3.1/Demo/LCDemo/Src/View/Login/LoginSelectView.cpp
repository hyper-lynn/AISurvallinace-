#ifdef TEST_MODEL
#include <fstream>
#endif
#include <libdsl/DPrintLog.h>
#include "Ctrl/OpenApiCtrl.h"
#include "LoginSelectView.h"

extern bool g_isReleasedForOverseas;

LoginSelectView::LoginSelectView(QWidget* parent)
: QWidget(parent)
{
    m_LogoLbl                   = NULL;
    m_TitleLbl                  = NULL;
#ifdef TEST_MODEL
    m_hostLbl                   = NULL;
    m_hostEdt                   = NULL;
    m_portLbl                   = NULL;
    m_portEdt                   = NULL;
#endif
    m_AppIdLbl                  = NULL;
    m_AppIdEdt                  = NULL;
    m_AppSecretLbl              = NULL;
    m_AppSecretEdt              = NULL;
    m_HintLbl1                  = NULL;
    m_HintLbl2                  = NULL;
    m_AdminModelBtn             = NULL;
    m_ResumeBtn                 = NULL;
}

LoginSelectView::~LoginSelectView()
{
    release();
}

int LoginSelectView::init()
{
    int ret = 0;

    do 
    {
        this->resize(646, 376);
        this->move(0, 0);
        this->setAutoFillBackground(true);
        QPalette palette;
        palette.setColor(QPalette::Window, QColor(0x1a, 0x1c, 0x20));
        this->setPalette(palette);

        // Logo (pure color rectangle)
        m_LogoLbl = new QLabel(this);
        if (NULL == m_LogoLbl)
        {
            ret = -1;
            break;
        }
        QPixmap logoPixmap(646, 80);
        logoPixmap.fill(QColor(0x1a, 0x1c, 0x20));
        m_LogoLbl->resize(646, 80);
        m_LogoLbl->move(0, 0);
        m_LogoLbl->setPixmap(logoPixmap);

        // Title
        m_TitleLbl = new QLabel(this);
        if (NULL == m_TitleLbl)
        {
            ret = -1;
            break;
        }
        m_TitleLbl->setStyleSheet("color:#e0e0e0;font:14pt;font-family:Microsoft YaHei;");
        m_TitleLbl->setText(tr("Device Management Platform"));
        m_TitleLbl->adjustSize();
        m_TitleLbl->move((646 - m_TitleLbl->width()) / 2, 58);

        // Common input style
        QString inputStyle =
            "QLineEdit {"
                "background-color:#2a2d32;"
                "color:#d0d0d0;"
                "font:11pt;"
                "font-family:Microsoft YaHei;"
                "border:1px solid #3a3d42;"
                "border-radius:4px;"
                "padding:4px 8px;"
            "}"
            "QLineEdit:focus {"
                "border:1px solid #fd8b30;"
            "}"
            "QLineEdit::placeholder {"
                "color:#666666;"
            "}";

        QString labelStyle = "color:#b0b0b0;font:11pt;font-family:Microsoft YaHei;";

        // Layout constants for label/input alignment
        const int cLabelX = 80;
        const int cLabelWidth = 120;
        const int cInputX = cLabelX + cLabelWidth + 8;
        const int cInputWidth = 358;

#ifdef TEST_MODEL
        std::ifstream ifs("LoginInfo.cfg");

        // HOST row
        m_hostLbl = new QLabel(this);
        if (NULL == m_hostLbl)
        {
            ret = -1;
            break;
        }
        m_hostLbl->setFixedSize(cLabelWidth, 30);
        m_hostLbl->move(cLabelX, 126);
        m_hostLbl->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
        m_hostLbl->setStyleSheet(labelStyle);
        m_hostLbl->setText("HOST:");

        m_hostEdt = new QLineEdit(this);
        if (NULL == m_hostEdt)
        {
            ret = -1;
            break;
        }
        m_hostEdt->resize(cInputWidth, 30);
        m_hostEdt->move(cInputX, 126);
        m_hostEdt->setStyleSheet(inputStyle);
        m_hostEdt->setPlaceholderText(tr("Enter Host Address"));
        if (ifs.is_open())
        {
            std::string host;
            ifs>>host;
            m_hostEdt->setText(host.c_str());
        } 
        else
        {
            if (g_isReleasedForOverseas)
            {
                m_hostEdt->setText(HOST_EN);
            } 
            else
            {
                m_hostEdt->setText(HOST);
            }
        }

        // PRODUCT ID row
        m_portLbl = new QLabel(this);
        if (NULL == m_portLbl)
        {
            ret = -1;
            break;
        }
        m_portLbl->setFixedSize(cLabelWidth, 30);
        m_portLbl->move(cLabelX, 164);
        m_portLbl->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
        m_portLbl->setStyleSheet(labelStyle);
        m_portLbl->setText("PRODUCT ID:");

        m_portEdt = new QLineEdit(this);
        if (NULL == m_portEdt)
        {
            ret = -1;
            break;
        }
        m_portEdt->resize(cInputWidth, 30);
        m_portEdt->move(cInputX, 164);
        m_portEdt->setStyleSheet(inputStyle);
        m_portEdt->setPlaceholderText(tr("Enter Product ID"));
        if (ifs.is_open())
        {
            int port;
            ifs>>port;
            m_portEdt->setText(QString::number(port, 10));
        } 
        else
        {
            m_portEdt->setText("443");
        }
#endif

        // APP ID row
        m_AppIdLbl = new QLabel(this);
        if (NULL == m_AppIdLbl)
        {
            ret = -1;
            break;
        }
        m_AppIdLbl->setFixedSize(cLabelWidth, 30);
        m_AppIdLbl->move(cLabelX, 202);
        m_AppIdLbl->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
        m_AppIdLbl->setStyleSheet(labelStyle);
        m_AppIdLbl->setText("APP ID:");

        m_AppIdEdt = new QLineEdit(this);
        if (NULL == m_AppIdEdt)
        {
            ret = -1;
            break;
        }
        m_AppIdEdt->resize(cInputWidth, 30);
        m_AppIdEdt->move(cInputX, 202);
        m_AppIdEdt->setStyleSheet(inputStyle);
        m_AppIdEdt->setPlaceholderText(tr("Enter App ID"));
#ifdef TEST_MODEL
        if (ifs.is_open())
        {
            std::string appId;
            ifs>>appId;
            m_AppIdEdt->setText(appId.c_str());
        }
#endif

        // APP SECRET row
        m_AppSecretLbl = new QLabel(this);
        if (NULL == m_AppSecretLbl)
        {
            ret = -1;
            break;
        }
        m_AppSecretLbl->setFixedSize(cLabelWidth, 30);
        m_AppSecretLbl->move(cLabelX, 240);
        m_AppSecretLbl->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
        m_AppSecretLbl->setStyleSheet(labelStyle);
        m_AppSecretLbl->setText("APP SECRET:");

        m_AppSecretEdt = new QLineEdit(this);
        if (NULL == m_AppSecretEdt)
        {
            ret = -1;
            break;
        }
        m_AppSecretEdt->resize(cInputWidth, 30);
        m_AppSecretEdt->move(cInputX, 240);
        m_AppSecretEdt->setStyleSheet(inputStyle);
        m_AppSecretEdt->setPlaceholderText(tr("Enter App Secret"));
#ifdef TEST_MODEL
        if (ifs.is_open())
        {
            std::string appSecret;
            ifs>>appSecret;
            ifs.close();
            m_AppSecretEdt->setText(appSecret.c_str());
        }
#endif

        // Hint labels
        m_HintLbl1 = new QLabel(this);
        if (NULL == m_HintLbl1)
        {
            ret = -1;
            break;
        }
        m_HintLbl1->move(80, 278);
        m_HintLbl1->setStyleSheet("color:#fe3e3e;font:10pt;font-family:Microsoft YaHei;");
        m_HintLbl1->setText(tr("Prompt: "));
        m_HintLbl1->adjustSize();
        m_HintLbl1->hide();

        m_HintLbl2 = new QLabel(this);
        if (NULL == m_HintLbl2)
        {
            ret = -1;
            break;
        }
        m_HintLbl2->move(m_HintLbl1->x() + m_HintLbl1->width(), 278);
        m_HintLbl2->resize(486 - m_HintLbl1->width(), 60);
        m_HintLbl2->setStyleSheet("color:#fe3e3e;font:10pt;font-family:Microsoft YaHei;");
        m_HintLbl2->setAlignment(Qt::AlignTop);
        m_HintLbl2->setWordWrap(true);
        m_HintLbl2->hide();

        // Login button
        m_AdminModelBtn = new BgColorBtn(this);
        if (NULL == m_AdminModelBtn)
        {
            ret = -1;
            break;
        }
        m_AdminModelBtn->resize(460, 42);
        m_AdminModelBtn->move(93, 296);
        m_AdminModelBtn->setBtnAttribute(QColor(0xfd, 0x8b, 0x30), QColor(0xff, 0xa0, 0x50), QColor(0xff, 0xff, 0xff), 11);
        m_AdminModelBtn->setText(tr("Login"));
        m_AdminModelBtn->setStyleSheet(
            "QPushButton {"
                "background-color:#fd8b30;"
                "color:#ffffff;"
                "font:11pt;"
                "font-family:Microsoft YaHei;"
                "border:none;"
                "border-radius:4px;"
            "}"
            "QPushButton:hover {"
                "background-color:#ffa050;"
            "}"
            "QPushButton:pressed {"
                "background-color:#e07828;"
            "}"
        );
        m_AdminModelBtn->setCursor(Qt::PointingHandCursor);
        connect(m_AdminModelBtn, &BgColorBtn::clicked, this, &LoginSelectView::slotAdminModel);

        // Back/Resume button
        m_ResumeBtn = new IconTextBtn(this);
        if (NULL == m_ResumeBtn)
        {
            ret = -1;
            break;
        }
        m_ResumeBtn->setBtnAttribute("Skin/common_icon_back", tr("Back"), 11, QColor(0xb0, 0xaf, 0xaf));
        m_ResumeBtn->move(22, 6);
        m_ResumeBtn->hide();
        connect(m_ResumeBtn, &IconTextBtn::clicked, this, &LoginSelectView::slotResume);
    } while (0);

    if (0 != ret)
    {
        release();
    }

    return ret;
}

void LoginSelectView::release()
{
    if (NULL != m_LogoLbl)
    {
        delete m_LogoLbl;
        m_LogoLbl = NULL;
    }

    if (NULL != m_TitleLbl)
    {
        delete m_TitleLbl;
        m_TitleLbl = NULL;
    }

#ifdef TEST_MODEL

    saveLoginInfoToLocal();

    if (NULL != m_hostLbl)
    {
        delete m_hostLbl;
        m_hostLbl = NULL;
    }

    if (NULL != m_hostEdt)
    {
        delete m_hostEdt;
        m_hostEdt = NULL;
    }

    if (NULL != m_portLbl)
    {
        delete m_portLbl;
        m_portLbl = NULL;
    }

    if (NULL != m_portEdt)
    {
        delete m_portEdt;
        m_portEdt = NULL;
    }

#endif

    if (NULL != m_AppIdLbl)
    {
        delete m_AppIdLbl;
        m_AppIdLbl = NULL;
    }

    if (NULL != m_AppIdEdt)
    {
        delete m_AppIdEdt;
        m_AppIdEdt = NULL;
    }

    if (NULL != m_AppSecretLbl)
    {
        delete m_AppSecretLbl;
        m_AppSecretLbl = NULL;
    }

    if (NULL != m_AppSecretEdt)
    {
        delete m_AppSecretEdt;
        m_AppSecretEdt = NULL;
    }

    if (NULL != m_HintLbl1)
    {
        delete m_HintLbl1;
        m_HintLbl1 = NULL;
    }

    if (NULL != m_HintLbl2)
    {
        delete m_HintLbl2;
        m_HintLbl2 = NULL;
    }

    if (NULL != m_AdminModelBtn)
    {
        delete m_AdminModelBtn;
        m_AdminModelBtn = NULL;
    }

    if (NULL != m_ResumeBtn)
    {
        delete m_ResumeBtn;
        m_ResumeBtn = NULL;
    }

    return;
}

QString LoginSelectView::getAppId()
{
    return m_AppIdEdt->text();
}

QString LoginSelectView::getAppSecret()
{
    return m_AppSecretEdt->text();
}

#ifdef TEST_MODEL

QString LoginSelectView::getHost()
{
    return m_hostEdt->text();
}

int LoginSelectView::getPort()
{
    return m_portEdt->text().toInt();
}

void LoginSelectView::saveLoginInfoToLocal()
{
    std::ofstream ofs("LoginInfo.cfg");
    if (!ofs.is_open())
    {
        return;
    }
    ofs<<getHost().toLatin1().data()<<std::endl;
    ofs<<getPort()<<std::endl;
    ofs<<getAppId().toLatin1().data()<<std::endl;
    ofs<<getAppSecret().toLatin1().data()<<std::endl;
    ofs.close();
    return;
}

#endif

void LoginSelectView::showHint()
{
    if (NULL != m_HintLbl1)
    {
        m_HintLbl1->show();
    }

    if (NULL != m_HintLbl2)
    {
        m_HintLbl2->show();
    }

    if (NULL != m_AdminModelBtn)
    {
        m_AdminModelBtn->hide();
    }

    if (NULL != m_ResumeBtn)
    {
        m_ResumeBtn->show();
    }

    return;
}

void LoginSelectView::hideHint()
{
    if (NULL != m_HintLbl1)
    {
        m_HintLbl1->hide();
    }

    if (NULL != m_HintLbl2)
    {
        m_HintLbl2->hide();
    }

    if (NULL != m_AdminModelBtn)
    {
        m_AdminModelBtn->show();
    }

    if (NULL != m_ResumeBtn)
    {
        m_ResumeBtn->hide();
    }

    return;
}

void LoginSelectView::slotAdminModel()
{
    if (NULL == m_AppIdEdt || NULL == m_AppSecretEdt)
    {
        return;
    }

    if (m_AppIdEdt->text().isEmpty())
    {
        m_HintLbl2->setText(tr("The appId or appSecret isn't configured correctly, please login open platform website, create application and you will get the appId and appSecret."));
        showHint();
        m_AppIdEdt->setFocus();
    } 
    else if (m_AppSecretEdt->text().isEmpty())
    {
        m_HintLbl2->setText(tr("The appId or appSecret isn't configured correctly, please login open platform website, create application and you will get the appId and appSecret."));
        showHint();
        m_AppSecretEdt->setFocus();
    }
    else
    {
        OPEN_API_INIT_PARAM openApiInitParam;
        openApiInitParam.caPath = g_isReleasedForOverseas ? QString(CA_PATH_EN) : QString(CA_PATH);
#ifdef TEST_MODEL
        openApiInitParam.host = m_hostEdt->text();
        openApiInitParam.port = m_portEdt->text().toInt();
#else
        if (g_isReleasedForOverseas)
        {
            openApiInitParam.host = QString(HOST_EN);
        } 
        else
        {
            openApiInitParam.host = QString(HOST);
        }
        openApiInitParam.port = PORT;
#endif
        OpenApiCtrl::getInstance()->init(openApiInitParam);


        TOKEN_PARAMETERS tokenParam;
        tokenParam.appId = m_AppIdEdt->text();
        tokenParam.appSecret = m_AppSecretEdt->text();
#ifdef TEST_MODEL
        tokenParam.host = m_hostEdt->text();
        tokenParam.port = m_portEdt->text().toInt();
#else
        if (g_isReleasedForOverseas)
        {
            tokenParam.host = QString(HOST_EN);
        } 
        else
        {
            tokenParam.host = QString(HOST);
        }
        tokenParam.port = PORT;
#endif

        int ret = RET_OK;
        QString ret_code;
        QString ret_msg;
		//QString host = tokenParam.host + ":" + QString::number(tokenParam.port);
		QString host = tokenParam.host + ":" + "443";
		// QString token = "";
		QString AccessKey = tokenParam.appId;
		QString SecretKey = tokenParam.appSecret;
		QString productId = QString::number(tokenParam.port);
        connect(OpenApiCtrl::getInstance(), &OpenApiCtrl::sgnGetPlayInfoReslut, this, &LoginSelectView::slotGetPlayInfoResult);
		connect(OpenApiCtrl::getInstance(), &OpenApiCtrl::sgnGetP2pInfoReslut, this, &LoginSelectView::slotGetP2pInfoResult);
		//ret = OpenApiCtrl::getInstance()->getIOTToken(host, AccessKey);
		OpenApiCtrl::getInstance()->getIOTToken(host, AccessKey, productId, SecretKey);
		//OpenApiCtrl::getInstance()->getIOTPlayInfo(host, AccessKey, productId, SecretKey);
		//OpenApiCtrl::getInstance()->getP2PServerInfo(host, AccessKey, productId, SecretKey);

        //if (RET_OK == ret)
        //{
        //    this->hide();
        //    emit sgnShowDevicesList();
        //}
        //else 
        //{
        //    m_HintLbl2->setText(tr("getIOTToken ret failed!"));
        //    showHint();
        //}
    }
}

void  LoginSelectView::slotGetPlayInfoResult(bool bSucceed)
{
	if (bSucceed == true)
	{
	    this->hide();
	    emit sgnShowDevicesList();
	}
	else 
	{
	    m_HintLbl2->setText(tr("getIOTToken ret failed!"));
	    showHint();
	}
}

void  LoginSelectView::slotGetP2pInfoResult(bool bSucceed)
{
	if (bSucceed == true)
	{
		this->hide();
		emit sgnShowDevicesList();
	}
	else
	{
		m_HintLbl2->setText(tr("getP2pInfo ret failed!"));
		//showHint();
		this->hide();
		emit sgnShowDevicesList();
	}
}

void LoginSelectView::slotResume()
{
    hideHint();
}
