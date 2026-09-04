#include "lcopensdk_deviceinit/LCOpenSDK_DeviceInit.h"
#include "DeviceAddView.h"


extern bool g_isReleasedForOverseas;

DeviceAddView::DeviceAddView(QWidget *parent)
	: QWidget(parent)
{
	m_SeparatorLbl = NULL;
	m_ToolBar = NULL;
	m_ReturnToDevicesListBtn = NULL;
	m_WorkBar = NULL;
	m_DeviceIdLbl = NULL;
	m_deviceIdCircularLbl = NULL;
	m_DeviceIdEdt = NULL;
	m_deviceKeyLbl = NULL;
	m_deviceKeyCircularLbl = NULL;
	m_deviceKeyEdt = NULL;
	m_bindDeviceBtn = NULL;
	m_HintLbl = NULL;
	m_HintIcon = NULL;
	m_OpenApiCtrlInstance = NULL;
	m_decryptKeyBox = NULL;
	m_devSafeCodeBox = NULL;
}
DeviceAddView::~DeviceAddView()
{
	release();
}

int DeviceAddView::init()
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

		m_ReturnToDevicesListBtn = new (std::nothrow) IconTextBtn(m_ToolBar);
		if (NULL == m_ReturnToDevicesListBtn)
		{
			ret = -1;
			break;
		}
		m_ReturnToDevicesListBtn->setBtnAttribute("Skin/common_icon_back", tr("Back to Devices List"), 11, QColor(0xb0, 0xaf, 0xaf));
		m_ReturnToDevicesListBtn->move(22, 6);
		connect(m_ReturnToDevicesListBtn, SIGNAL(clicked()), this, SLOT(slotReturnToDevicesList()));

		m_WorkBar = new (std::nothrow) QWidget(this);
		if (NULL == m_WorkBar)
		{
			ret = -1;
			break;
		}
		m_WorkBar->resize(this->width(), this->height() - 43);
		m_WorkBar->move(0, 43);
		m_WorkBar->setStyleSheet("background-color:#323436;");

		m_DeviceIdLbl = new (std::nothrow) QLabel(m_WorkBar);
		if (NULL == m_DeviceIdLbl)
		{
			ret = -1;
			break;
		}
		m_DeviceIdLbl->setStyleSheet("color:#b0afaf;font:11pt;font-family:Microsoft YaHei;");
		m_DeviceIdLbl->setFixedHeight(14);
		m_DeviceIdLbl->move(279, 82);
		m_DeviceIdLbl->setText(tr("Please input the device serial number to bind"));
		m_DeviceIdLbl->adjustSize();

		m_deviceIdCircularLbl = new (std::nothrow) QLabel(m_WorkBar);
		if (NULL == m_deviceIdCircularLbl)
		{
			ret = -1;
			break;
		}
		QPixmap circularLblPixmap;
		circularLblPixmap.load("Skin/adddevice_search_bg_n.png");
		m_deviceIdCircularLbl->resize(circularLblPixmap.size());
		m_deviceIdCircularLbl->setPixmap(circularLblPixmap);
		m_deviceIdCircularLbl->move((1022 - circularLblPixmap.width()) / 2, 107);
		m_deviceIdCircularLbl->show();

		m_DeviceIdEdt = new (std::nothrow) QLineEdit(m_deviceIdCircularLbl);
		if (NULL == m_DeviceIdEdt)
		{
			ret = -1;
			break;
		}
		m_DeviceIdEdt->resize(m_deviceIdCircularLbl->width() - m_deviceIdCircularLbl->height(), 20);
		m_DeviceIdEdt->move(22, 12);
		m_DeviceIdEdt->setStyleSheet("background-color:#323436;color:#a8a9a9;font:11pt;font-family:Microsoft YaHei;border:0px;");

		m_decryptKeyBox = new (std::nothrow) MyEditBox(this);
		if (NULL == m_decryptKeyBox)
		{
			ret = -1;
			break;
		}
		ret = m_decryptKeyBox->init(tr(""));
		if (0 != ret)
		{
			break;
		}
		connect(m_decryptKeyBox, SIGNAL(sgnOK(QString)), this, SLOT(slotDecryptKeyBoxOK(QString)));

		QString bindDeviceBtnIconPath = g_isReleasedForOverseas ? "Skin/bind_device_en" : "Skin/bind_device";
		m_bindDeviceBtn = new (std::nothrow) IconBtn(m_WorkBar, bindDeviceBtnIconPath);
		if (NULL == m_bindDeviceBtn)
		{
			ret = -1;
			break;
		}
		m_bindDeviceBtn->move((m_WorkBar->width() - m_bindDeviceBtn->width()) / 2, m_deviceIdCircularLbl->y() + m_deviceIdCircularLbl->height() + 25);
		connect(m_bindDeviceBtn, SIGNAL(clicked()), this, SLOT(slotAddDevice()));

		m_devSafeCodeBox = new (std::nothrow) MyEditBox(this);
		if (NULL == m_devSafeCodeBox)
		{
			ret = -1;
			break;
		}
		ret = m_devSafeCodeBox->init(tr("please input device safe code"));
		if (0 != ret)
		{
			break;
		}
		connect(m_devSafeCodeBox, SIGNAL(sgnOK(QString)), this, SLOT(slotDevSafeCodeBox(QString)));

		m_HintLbl = new (std::nothrow) QLabel(m_WorkBar);
		if (NULL == m_HintLbl)
		{
			ret = -1;
			break;
		}
		m_HintLbl->setAlignment(Qt::AlignTop);
		m_HintLbl->setWordWrap(true);
		m_HintLbl->setStyleSheet("color:#fe3e3e;font:9pt;font-family:Microsoft YaHei;");
		m_HintLbl->resize(m_deviceIdCircularLbl->width() - m_deviceIdCircularLbl->height(), 60);
		m_HintLbl->move(m_deviceIdCircularLbl->x() + m_deviceIdCircularLbl->height() / 2, m_bindDeviceBtn->y() + m_bindDeviceBtn->height() + 12);
		m_HintLbl->hide();

		m_HintIcon = new (std::nothrow) QLabel(m_WorkBar);
		if (NULL == m_HintIcon)
		{
			ret = -1;
			break;
		}
		QPixmap hintIconPixmap;
		hintIconPixmap.load("Skin/home_fault_hint.png");
		m_HintIcon->resize(hintIconPixmap.size());
		m_HintIcon->setPixmap(hintIconPixmap);
		m_HintIcon->move(m_HintLbl->x() - m_HintIcon->width() - 8, m_HintLbl->y());
		m_HintIcon->hide();

		m_OpenApiCtrlInstance = OpenApiCtrl::getInstance();
	} while (0);

	if (0 != ret)
	{
		release();
	}

	return ret;
}

void DeviceAddView::release()
{
	if (NULL != m_HintIcon)
	{
		delete m_HintIcon;
		m_HintIcon = NULL;
	}

	if (NULL != m_HintLbl)
	{
		delete m_HintLbl;
		m_HintLbl = NULL;
	}

	if (NULL != m_devSafeCodeBox)
	{
		delete m_devSafeCodeBox;
		m_devSafeCodeBox = NULL;
	}

	if (NULL != m_bindDeviceBtn)
	{
		delete m_bindDeviceBtn;
		m_bindDeviceBtn = NULL;
	}

	if (NULL != m_decryptKeyBox)
	{
		delete m_decryptKeyBox;
		m_decryptKeyBox = NULL;
	}

	if (NULL != m_DeviceIdEdt)
	{
		delete m_DeviceIdEdt;
		m_DeviceIdEdt = NULL;
	}

	if (NULL != m_deviceIdCircularLbl)
	{
		delete m_deviceIdCircularLbl;
		m_deviceIdCircularLbl = NULL;
	}

	if (NULL != m_DeviceIdLbl)
	{
		delete m_DeviceIdLbl;
		m_DeviceIdLbl = NULL;
	}

	if (NULL != m_WorkBar)
	{
		delete m_WorkBar;
		m_WorkBar = NULL;
	}

	if (NULL != m_ReturnToDevicesListBtn)
	{
		delete m_ReturnToDevicesListBtn;
		m_ReturnToDevicesListBtn = NULL;
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

	return;
}

void DeviceAddView::showEvent(QShowEvent *e)
{
	QWidget::showEvent(e);
	m_HintLbl->clear();
	m_HintLbl->hide();
	m_HintIcon->hide();
}

void DeviceAddView::slotAddDevice()
{
	QString sRet;
	int iRet;

	m_deviceId = m_DeviceIdEdt->text();
	if (m_deviceId.isEmpty())
	{
		m_HintLbl->setText(tr("Please input the device serial number!"));
		m_HintLbl->show();
		m_HintIcon->show();
		return;
	}
	else
	{
		m_HintLbl->hide();
		m_HintIcon->hide();
	}

	// 	/* search device init info */
		/*添加设备初始化局域网搜索*/
	iRet = LCOpenSDK_DeviceInit::getInstance()->searchDeviceInitInfo(m_deviceId.toLatin1().data(), m_devInitInfo, 20000);
	if (-2 == iRet)
	{
		m_HintLbl->setText(tr("Search device init info failed!"));
		m_HintLbl->show();
		m_HintIcon->show();
		return;
	}
	else
	{
		m_HintLbl->hide();
		m_HintIcon->hide();
	}

	if ((m_devInitInfo.initStatus == 0) && (!g_isReleasedForOverseas))
	{
		restApiBind("");
		return;
	}
	else if (m_devInitInfo.initStatus == 1)
	{
		m_decryptKeyBox->setTitle(tr("Please input the new key to init"));
	}
	else if (m_devInitInfo.initStatus == 2)
	{
		m_decryptKeyBox->setTitle(tr("Please input device key"));
	}
	else if ((m_devInitInfo.initStatus == 0) && g_isReleasedForOverseas)
	{
		m_decryptKeyBox->setTitle(tr("Please input device key"));
	}

	m_decryptKeyBox->show();

	return;
}

void DeviceAddView::slotReturnToDevicesList()
{
	//this->hide();
	emit sgnReturnToDevicesList(true);
	return;
}

void DeviceAddView::slotDecryptKeyBoxOK(QString deviceKey)
{
	int iRet = 0;
	QString sRet;

	if (m_devInitInfo.initStatus == 2 && g_isReleasedForOverseas)
	{
		//iRet = LCOpenSDK_DeviceInit::getInstance()->checkPwdValidity(m_OpenApiCtrlInstance->getToken().toLatin1().data(), m_deviceId.toLatin1().data(), deviceKey.toLatin1().data());
		iRet = LCOpenSDK_DeviceInit::getInstance()->checkPwdValidity(m_deviceId.toLatin1().data(), m_devInitInfo.szIp, m_devInitInfo.port, deviceKey.toLatin1().data());
		if (0 != iRet)
		{
			m_HintLbl->setText(tr("Check device password failed!"));
			m_HintLbl->show();
			m_HintIcon->show();
			return;
		}
		else
		{
			m_HintLbl->hide();
			m_HintIcon->hide();
		}
	}
	restApiBind(deviceKey);

	return;
}

void DeviceAddView::restApiBind(QString deviceKey)
{
	//initDevice
	QString ability;
	QString productId;
	QString sRet;
	sRet = m_OpenApiCtrlInstance->unBindDeviceInfo(m_deviceId, ability, productId);
	if ("OK" == sRet)
	{
		m_HintLbl->setText(tr("get ability succeed!"));
		m_HintLbl->show();
		m_HintIcon->show();
	}
	else
	{
		m_HintLbl->setText(tr("get ability error") + "[" + sRet + "]");
		m_HintLbl->show();
		m_HintIcon->show();
	}

	if (productId.isEmpty() && m_devInitInfo.initStatus == 1 && ability.indexOf("SCCode") < 0)
 	{
 		/* 不需要检测密码是否正确，直接初始化 */
 		int iRet = LCOpenSDK_DeviceInit::getInstance()->initDevice(m_devInitInfo.szMac, deviceKey.toLatin1().data(), m_devInitInfo.szIp);
 		if (-2 == iRet)
 		{
 			m_HintLbl->setText(tr("Init device failed!"));
 			m_HintLbl->show();
 			m_HintIcon->show(); 
 			return;
 		}
 		else
 		{
 			m_HintLbl->hide();
 			m_HintIcon->hide();
 		}
 	}

	/* CheckDeviceBindOrNot */
	bool isMine = false;
	bool isBind = false;
	sRet = m_OpenApiCtrlInstance->checkDeviceBindOrNot(m_deviceId, isMine, isBind);
	if ("OK" != sRet)
	{
		m_HintLbl->setText(tr("OpenApi CheckDeviceBindOrNot error") + "[" + sRet + "]");
		m_HintLbl->show();
		m_HintIcon->show();
		return;
	}
	else
	{
		m_HintLbl->hide();
		m_HintIcon->hide();
	}

	if (isMine)
	{
		m_HintLbl->setText(tr("The device is already bound to this account!"));
		m_HintLbl->show();
		m_HintIcon->show();
		return;
	}
	else if (isBind)
	{
		m_HintLbl->setText(tr("The device is already bound to other account!"));
		m_HintLbl->show();
		m_HintIcon->show();
		return;
	}
	else
	{
		m_HintLbl->hide();
		m_HintIcon->hide();
	}
	/* CheckDeviceBindOrNot */

	/* CheckDeviceOnlineOrNot */
	bool isDeviceOnline = false;
	/* 修复因为开放平台延时导致设备绑定失败的问题：多次检查设备是否在线 */
	for (int checkOnlineCount = 0; checkOnlineCount < 12; checkOnlineCount++)
	{
		sRet = m_OpenApiCtrlInstance->checkDeviceOnlineOrNot(m_deviceId, isDeviceOnline);
		if ("OK" != sRet)
		{
			m_HintLbl->setText(tr("OpenApi DeviceOnline error") + "[" + sRet + "]");
			m_HintLbl->show();
			m_HintIcon->show();
			return;
		}
		else
		{
			if (true == isDeviceOnline)
			{
				break;
			}
#ifdef _WIN32
			Sleep(5000);
#endif
		}
	}
	if (false == isDeviceOnline)
	{
		m_HintLbl->setText(tr("The device is offline!"));
		m_HintLbl->show();
		m_HintIcon->show();
		return;
	}
	/* CheckDeviceOnlineOrNot */

	if (ability.indexOf("Auth") >= 0)
	{
		/* BindDevice */
		sRet = m_OpenApiCtrlInstance->bindDevice(m_deviceId, deviceKey);
		if ("OK" == sRet)
		{
			m_HintLbl->setText(tr("Bind device succeed!"));
			m_HintLbl->show();
			m_HintIcon->show();
		}
		else
		{
			m_HintLbl->setText(tr("OpenApi BindDevice error") + "[" + sRet + "]");
			m_HintLbl->show();
			m_HintIcon->show();
		}
		/* BindDevice */
	}
	else if (ability.indexOf("RegCode") >= 0)
	{
		//弹框输入安全码
		m_devSafeCodeBox->show();
	}
	else
	{
		sRet = m_OpenApiCtrlInstance->bindDevice(m_deviceId, "");
		if ("OK" == sRet)
		{
			m_HintLbl->setText(tr("Bind device succeed!"));
			m_HintLbl->show();
			m_HintIcon->show();
		}
		else
		{
			m_HintLbl->setText(tr("OpenApi BindDevice error") + "[" + sRet + "]");
			m_HintLbl->show();
			m_HintIcon->show();
		}
	}

	return;
}

void DeviceAddView::slotDevSafeCodeBox(QString deviceSafeCode)
{
	QString sRet = m_OpenApiCtrlInstance->bindDevice(m_deviceId, deviceSafeCode);
	if ("OK" == sRet)
	{
		m_HintLbl->setText(tr("Bind device succeed!"));
		m_HintLbl->show();
		m_HintIcon->show();
	}
	else
	{
		m_HintLbl->setText(tr("OpenApi BindDevice error") + "[" + sRet + "]");
		m_HintLbl->show();
		m_HintIcon->show();
	}
}