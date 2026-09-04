#ifdef TEST_MODEL
#include <fstream>
#endif
#include "Src/Ctrl/OpenApiCtrl.h"
#include "LoginSelectView.h"

extern bool g_isReleasedForOverseas;

LoginSelectView::LoginSelectView(QWidget* parent)
	: QWidget(parent)
{
	m_LogoLbl = NULL;
#ifdef TEST_MODEL
	m_hostLbl = NULL;
	m_hostEdt = NULL;
	m_portLbl = NULL;
	m_portEdt = NULL;
#endif
	m_AppIdLbl = NULL;
	m_AppIdEdt = NULL;
	m_AppSecretLbl = NULL;
	m_AppSecretEdt = NULL;
	m_HintLbl1 = NULL;
	m_HintLbl2 = NULL;
	m_loginSelectWidget = NULL;
	m_loginSelectLayout = NULL;
	m_AdminModelBtn = NULL;
	m_ResumeBtn = NULL;
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
		palette.setColor(QPalette::Background, QColor(0x20, 0x22, 0x24));
		this->setPalette(palette);

		m_LogoLbl = new (std::nothrow) QLabel(this);
		if (NULL == m_LogoLbl)
		{
			ret = -1;
			break;
		}
		QPixmap logoPixmap;
		if (g_isReleasedForOverseas)
		{
			logoPixmap.load("Skin/home_logo_en.png");
		}
		else
		{
			logoPixmap.load("Skin/home_logo.png");
		}
		m_LogoLbl->resize(logoPixmap.size());
		m_LogoLbl->move((646 - logoPixmap.width()) / 2, 54);
		m_LogoLbl->setPixmap(logoPixmap);

#ifdef TEST_MODEL
		std::ifstream ifs;
		if (g_isReleasedForOverseas)
		{
			ifs.open("LoginInfo_en.cfg");
		}
		else
		{
			ifs.open("LoginInfo.cfg");
		}
		

		m_hostLbl = new (std::nothrow) QLabel(this);
		if (NULL == m_hostLbl)
		{
			ret = -1;
			break;
		}
		m_hostLbl->setFixedHeight(24);
		m_hostLbl->move(0, 149);
		m_hostLbl->setStyleSheet("color:#ffffff;font:12pt;font-family:Microsoft YaHei;");
		m_hostLbl->setText("HOST:");
		m_hostLbl->adjustSize();

		m_hostEdt = new (std::nothrow) QLineEdit(this);
		if (NULL == m_hostEdt)
		{
			ret = -1;
			break;
		}
		m_hostEdt->resize(323 - m_hostLbl->width(), 24);
		m_hostEdt->move(m_hostLbl->width(), 149);
		m_hostEdt->setStyleSheet("background-color:#202224;color:#a8a9a9;font:12pt;border:0px;font-family:Microsoft YaHei;");
		if (ifs.is_open())
		{
			std::string host;
			ifs >> host;
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

		m_portLbl = new (std::nothrow) QLabel(this);
		if (NULL == m_portLbl)
		{
			ret = -1;
			break;
		}
		m_portLbl->setFixedHeight(24);
		m_portLbl->move(323, 149);
		m_portLbl->setStyleSheet("color:#ffffff;font:12pt;font-family:Microsoft YaHei;");
		m_portLbl->setText("PORT:");
		m_portLbl->adjustSize();

		m_portEdt = new (std::nothrow) QLineEdit(this);
		if (NULL == m_portEdt)
		{
			ret = -1;
			break;
		}
		m_portEdt->resize(323 - m_portLbl->width(), 24);
		m_portEdt->move(323 + m_portLbl->width(), 149);
		m_portEdt->setStyleSheet("background-color:#202224;color:#a8a9a9;font:12pt;border:0px;font-family:Microsoft YaHei;");
		if (ifs.is_open())
		{
			int port;
			ifs >> port;
			m_portEdt->setText(QString::number(port, 10));
		}
		else
		{
			m_portEdt->setText("443");
		}

#endif

		m_AppIdLbl = new (std::nothrow) QLabel(this);
		if (NULL == m_AppIdLbl)
		{
			ret = -1;
			break;
		}
		m_AppIdLbl->setFixedHeight(24);
		m_AppIdLbl->move(138, 184);
		m_AppIdLbl->setStyleSheet("color:#ffffff;font:12pt;font-family:Microsoft YaHei;");
		m_AppIdLbl->setText("APP ID:");
		m_AppIdLbl->adjustSize();

		m_AppIdEdt = new (std::nothrow) QLineEdit(this);
		if (NULL == m_AppIdEdt)
		{
			ret = -1;
			break;
		}
		m_AppIdEdt->resize(370 - m_AppIdLbl->width(), 24);
		m_AppIdEdt->move(138 + m_AppIdLbl->width(), 184);
		m_AppIdEdt->setStyleSheet("background-color:#202224;color:#a8a9a9;font:12pt;border:0px;font-family:Microsoft YaHei;");
#ifdef TEST_MODEL
		if (ifs.is_open())
		{
			std::string appId;
			ifs >> appId;
			m_AppIdEdt->setText(appId.c_str());
		}
#endif

		m_AppSecretLbl = new (std::nothrow) QLabel(this);
		if (NULL == m_AppSecretLbl)
		{
			ret = -1;
			break;
		}
		m_AppSecretLbl->setFixedHeight(24);
		m_AppSecretLbl->move(138, 224);
		m_AppSecretLbl->setStyleSheet("color:#ffffff;font:12pt;font-family:Microsoft YaHei;");
		m_AppSecretLbl->setText("APP SECRET:");
		m_AppSecretLbl->adjustSize();

		m_AppSecretEdt = new (std::nothrow) QLineEdit(this);
		if (NULL == m_AppSecretEdt)
		{
			ret = -1;
			break;
		}
		m_AppSecretEdt->resize(370 - m_AppSecretLbl->width(), 24);
		m_AppSecretEdt->move(138 + m_AppSecretLbl->width(), 224);
		m_AppSecretEdt->setStyleSheet("background-color:#202224;color:#a8a9a9;font:12pt;border:0px;font-family:Microsoft YaHei;");
#ifdef TEST_MODEL
		if (ifs.is_open())
		{
			std::string appSecret;
			ifs >> appSecret;
			ifs.close();
			m_AppSecretEdt->setText(appSecret.c_str());
		}
#endif

		m_HintLbl1 = new (std::nothrow) QLabel(this);
		if (NULL == m_HintLbl1)
		{
			ret = -1;
			break;
		}
		m_HintLbl1->move(24, 298);
		m_HintLbl1->setStyleSheet("color:#fe3e3e;font:11pt;font-family:Microsoft YaHei;");
		m_HintLbl1->setText(tr("Prompt: "));
		m_HintLbl1->adjustSize();
		m_HintLbl1->hide();

		m_HintLbl2 = new (std::nothrow) QLabel(this);
		if (NULL == m_HintLbl2)
		{
			ret = -1;
			break;
		}
		m_HintLbl2->move(m_HintLbl1->x() + m_HintLbl1->width(), 298);
		m_HintLbl2->resize(646 - 24 - m_HintLbl1->x() - m_HintLbl1->width(), 60);
		m_HintLbl2->setStyleSheet("color:#fe3e3e;font:11pt;font-family:Microsoft YaHei;");
		m_HintLbl2->setAlignment(Qt::AlignTop);
		m_HintLbl2->setWordWrap(true);
		m_HintLbl2->hide();

		m_loginSelectWidget = new (std::nothrow) QWidget(this);
		if (NULL == m_loginSelectWidget)
		{
			ret = -1;
			break;
		}
		m_loginSelectWidget->resize(this->width(), 72);
		m_loginSelectWidget->move(0, 304);

		m_loginSelectLayout = new (std::nothrow) QHBoxLayout;
		if (NULL == m_loginSelectLayout)
		{
			ret = -1;
			break;
		}
		m_loginSelectLayout->setMargin(0);
		m_loginSelectLayout->setSpacing(2);
		m_loginSelectWidget->setLayout(m_loginSelectLayout);

		m_AdminModelBtn = new (std::nothrow) BgColorBtn(this);
		if (NULL == m_AdminModelBtn)
		{
			ret = -1;
			break;
		}
		m_AdminModelBtn->setBtnAttribute(QColor(0x2c, 0x2d, 0x30), QColor(0x31, 0x32, 0x35), QColor(0xfd, 0x8b, 0x30), 11);
		m_AdminModelBtn->setText(tr("Click to Enter Administrator Model"));
		m_AdminModelBtn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
		m_loginSelectLayout->addWidget(m_AdminModelBtn);
		connect(m_AdminModelBtn, SIGNAL(clicked()), this, SLOT(slotAdminModel()));

		m_ResumeBtn = new (std::nothrow) IconTextBtn(this);
		if (NULL == m_ResumeBtn)
		{
			ret = -1;
			break;
		}
		m_ResumeBtn->setBtnAttribute("Skin/common_icon_back", tr("Back"), 11, QColor(0xb0, 0xaf, 0xaf));
		m_ResumeBtn->move(22, 6);
		m_ResumeBtn->hide();
		connect(m_ResumeBtn, SIGNAL(clicked()), this, SLOT(slotResume()));

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

#ifdef TEST_MODEL

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

	if (NULL != m_loginSelectLayout)
	{
		delete m_loginSelectLayout;
		m_loginSelectLayout = NULL;
	}

	if (NULL != m_loginSelectWidget)
	{
		delete m_loginSelectWidget;
		m_loginSelectWidget = NULL;
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
	std::ofstream ofs;
	if (g_isReleasedForOverseas)
	{
		ofs.open("LoginInfo_en.cfg");
	}
	else
	{
		ofs.open("LoginInfo.cfg");
	}
	if (!ofs.is_open())
	{
		return;
	}
	ofs << getHost().toLatin1().data() << std::endl;
	ofs << getPort() << std::endl;
	ofs << getAppId().toLatin1().data() << std::endl;
	ofs << getAppSecret().toLatin1().data() << std::endl;
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
	saveLoginInfoToLocal();

	if (m_AppIdEdt->text().isEmpty())
	{
		m_HintLbl2->setText(tr("The appId or appSecret isn't configured correctly, please login open platform website, create application and you will get the appId and appSecret."));
		showHint();
	}
	else if (m_AppSecretEdt->text().isEmpty())
	{
		m_HintLbl2->setText(tr("The appId or appSecret isn't configured correctly, please login open platform website, create application and you will get the appId and appSecret."));
		showHint();
	}
	else
	{
		OPEN_API_INIT_PARAM openApiInitParam;
		//openApiInitParam.caPath = g_isReleasedForOverseas ? QString(CA_PATH_EN) : QString(CA_PATH);
		openApiInitParam.caPath = "";
#ifdef TEST_MODEL
		openApiInitParam.host = m_hostEdt->text();
		openApiInitParam.port = m_portEdt->text().toInt();
		openApiInitParam.appID = m_AppIdEdt->text();
		openApiInitParam.appSecret = m_AppSecretEdt->text();
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
		openApiInitParam.appID = m_AppIdEdt->text();
		openApiInitParam.appSecret = m_AppSecretEdt->text();
#endif


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
		ret = OpenApiCtrl::getInstance()->getAccessToken(&tokenParam, ret_code, ret_msg);
		if (RET_OK == ret)
		{
			//this->hide();
			OpenApiCtrl::getInstance()->init(&openApiInitParam);
			emit sgnShowDevicesList();
		}
		else
		{
			m_HintLbl2->setText(ret_msg);
			showHint();
		}
	}
}

void LoginSelectView::slotResume()
{
	hideHint();
}
