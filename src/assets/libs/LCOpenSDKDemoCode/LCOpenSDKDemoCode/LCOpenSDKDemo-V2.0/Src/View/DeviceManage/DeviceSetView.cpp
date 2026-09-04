#include "DeviceSetView.h"

extern bool g_isReleasedForOverseas;

DeviceSetView::DeviceSetView(QWidget *parent)
	: QWidget(parent)
{
	m_SeparatorLbl = NULL;
	m_ToolBar = NULL;
	m_ReturnToDevicesListBtn = NULL;
	m_statusLbl = NULL;
	m_WorkBar = NULL;
	m_AlarmStatusLbl = NULL;
	m_AlarmStatusBtn = NULL;
	m_SeparatorAlarmStatusLbl = NULL;
	m_CloudStorageStatusLbl = NULL;
	m_CloudStorageStatusBtn = NULL;
	m_SeparatorCloudStorageStatusLbl = NULL;
	m_modifyPasswordLbl = NULL;
	m_modifyPasswordBtn = NULL;
	m_separatorModifyPasswordLbl = NULL;
	m_modifyPasswordBox = NULL;
	m_cloudUpgradeLbl = NULL;
	m_cloudUpgradeBtn = NULL;
	m_separatorCloudUpgradeLbl = NULL;
	m_OpenApiCtrlInstance = NULL;
	m_DevicesListCtrlInstance = NULL;
	m_DeviceIndex = -1;
}

DeviceSetView::~DeviceSetView()
{
	release();
}

int DeviceSetView::init()
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

		m_statusLbl = new (std::nothrow) QLabel(m_ToolBar);
		if (NULL == m_statusLbl)
		{
			ret = -1;
			break;
		}
		m_statusLbl->resize(m_ToolBar->width() - m_ReturnToDevicesListBtn->x() - m_ReturnToDevicesListBtn->width() - 10, m_ToolBar->height());
		m_statusLbl->move(m_ReturnToDevicesListBtn->x() + m_ReturnToDevicesListBtn->width() + 10, 0);
		m_statusLbl->setStyleSheet("color:#ffffff;font:10pt;font-family:Microsoft YaHei;");
		m_statusLbl->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

		m_WorkBar = new (std::nothrow) QWidget(this);
		if (NULL == m_WorkBar)
		{
			ret = -1;
			break;
		}
		m_WorkBar->resize(this->width(), this->height() - 43);
		m_WorkBar->move(0, 43);
		m_WorkBar->setStyleSheet("background-color:#323436;");

		m_AlarmStatusLbl = new (std::nothrow) QLabel(m_WorkBar);
		if (NULL == m_AlarmStatusLbl)
		{
			ret = -1;
			break;
		}
		m_AlarmStatusLbl->setFixedHeight(50);
		m_AlarmStatusLbl->move(52, 6);
		m_AlarmStatusLbl->setStyleSheet("color:#ffffff;font:12pt;font-family:Microsoft YaHei;");
		m_AlarmStatusLbl->setText(tr("Alarm Status"));
		m_AlarmStatusLbl->adjustSize();

		m_AlarmStatusBtn = new (std::nothrow) CheckBtn(m_WorkBar);
		if (NULL == m_AlarmStatusBtn)
		{
			ret = -1;
			break;
		}
		m_AlarmStatusBtn->resize(53, 32);
		m_AlarmStatusBtn->move(m_WorkBar->width() - 53 - 48, 15);
		connect(m_AlarmStatusBtn, SIGNAL(clicked()), this, SLOT(slotChangeAlarmStatus()));

		m_SeparatorAlarmStatusLbl = new (std::nothrow) QLabel(m_WorkBar);
		if (NULL == m_SeparatorAlarmStatusLbl)
		{
			ret = -1;
			break;
		}
		m_SeparatorAlarmStatusLbl->resize(this->width(), 1);
		m_SeparatorAlarmStatusLbl->move(0, 62);
		m_SeparatorAlarmStatusLbl->setStyleSheet("background-color:#000000;");

		m_CloudStorageStatusLbl = new (std::nothrow) QLabel(m_WorkBar);
		if (NULL == m_CloudStorageStatusLbl)
		{
			ret = -1;
			break;
		}
		m_CloudStorageStatusLbl->setFixedHeight(50);
		m_CloudStorageStatusLbl->move(52, 69);
		m_CloudStorageStatusLbl->setStyleSheet("color:#ffffff;font:12pt;font-family:Microsoft YaHei;");
		m_CloudStorageStatusLbl->setText(tr("Cloud Storage Status"));
		m_CloudStorageStatusLbl->adjustSize();

		m_CloudStorageStatusBtn = new (std::nothrow) CheckBtn(m_WorkBar);
		if (NULL == m_CloudStorageStatusBtn)
		{
			ret = -1;
			break;
		}
		m_CloudStorageStatusBtn->resize(53, 32);
		m_CloudStorageStatusBtn->move(m_WorkBar->width() - 53 - 48, 78);
		connect(m_CloudStorageStatusBtn, SIGNAL(clicked()), this, SLOT(slotChangeCloudStorageStatus()));

		m_SeparatorCloudStorageStatusLbl = new (std::nothrow) QLabel(m_WorkBar);
		if (NULL == m_SeparatorCloudStorageStatusLbl)
		{
			ret = -1;
			break;
		}
		m_SeparatorCloudStorageStatusLbl->resize(this->width(), 1);
		m_SeparatorCloudStorageStatusLbl->move(0, 125);
		m_SeparatorCloudStorageStatusLbl->setStyleSheet("background-color:#000000;");

		/* 国内版本无修改密码框，海外版本有 */
		if (g_isReleasedForOverseas)
		{
			m_modifyPasswordLbl = new (std::nothrow) QLabel(m_WorkBar);
			if (NULL == m_modifyPasswordLbl)
			{
				ret = -1;
				break;
			}
			m_modifyPasswordLbl->move(52, 132);
			m_modifyPasswordLbl->setStyleSheet("color:#ffffff;font:12pt;font-family:Microsoft YaHei;");
			m_modifyPasswordLbl->setText(tr("Modify Password"));
			m_modifyPasswordLbl->adjustSize();

			QString modifyPasswordBtnIconPath = g_isReleasedForOverseas ? "Skin/modify_password_en" : "Skin/modify_password";
			m_modifyPasswordBtn = new (std::nothrow) IconBtn(m_WorkBar, modifyPasswordBtnIconPath);
			if (NULL == m_modifyPasswordBtn)
			{
				ret = -1;
				break;
			}
			m_modifyPasswordBtn->move(m_WorkBar->width() - m_modifyPasswordBtn->width() - 48, 141);
			connect(m_modifyPasswordBtn, SIGNAL(clicked()), this, SLOT(slotModifyPassword()));

			m_separatorModifyPasswordLbl = new (std::nothrow) QLabel(m_WorkBar);
			if (NULL == m_separatorModifyPasswordLbl)
			{
				ret = -1;
				break;
			}
			m_separatorModifyPasswordLbl->resize(this->width(), 1);
			m_separatorModifyPasswordLbl->move(0, 188);
			m_separatorModifyPasswordLbl->setStyleSheet("background-color:#000000;");

			m_modifyPasswordBox = new (std::nothrow) MyEditBox2(this);
			if (NULL == m_modifyPasswordBox)
			{
				ret = -1;
				break;
			}
			ret = m_modifyPasswordBox->init(tr("Please Input New Password"), tr("Old Password : "), tr("New Password : "));
			if (0 != ret)
			{
				break;
			}
			connect(m_modifyPasswordBox, SIGNAL(sgnOK(QString, QString)), this, SLOT(slotModifyPasswordBoxOK(QString, QString)));
			m_modifyPasswordBox->hide();
		}

		m_cloudUpgradeLbl = new (std::nothrow) QLabel(m_WorkBar);
		if (NULL == m_cloudUpgradeLbl)
		{
			ret = -1;
			break;
		}
		m_cloudUpgradeLbl->setFixedHeight(50);
		if (g_isReleasedForOverseas)
		{
			m_cloudUpgradeLbl->move(52, 195);
		}
		else
		{
			m_cloudUpgradeLbl->move(52, 132);
		}
		m_cloudUpgradeLbl->setStyleSheet("color:#ffffff;font:12pt;font-family:Microsoft YaHei;");
		m_cloudUpgradeLbl->setText(tr("Cloud Upgrade"));
		m_cloudUpgradeLbl->adjustSize();

		QString cloudUpgradeBtnIconPath = g_isReleasedForOverseas ? "Skin/cloud_upgrade_en" : "Skin/cloud_upgrade";
		m_cloudUpgradeBtn = new (std::nothrow) IconBtn(m_WorkBar, cloudUpgradeBtnIconPath);
		if (NULL == m_cloudUpgradeBtn)
		{
			ret = -1;
			break;
		}
		if (g_isReleasedForOverseas)
		{
			m_cloudUpgradeBtn->move(m_WorkBar->width() - m_cloudUpgradeBtn->width() - 48, 204);
		}
		else
		{
			m_cloudUpgradeBtn->move(m_WorkBar->width() - m_cloudUpgradeBtn->width() - 48, 141);
		}
		connect(m_cloudUpgradeBtn, SIGNAL(clicked()), this, SLOT(slotCloudUpgrade()));

		m_separatorCloudUpgradeLbl = new (std::nothrow) QLabel(m_WorkBar);
		if (NULL == m_separatorCloudUpgradeLbl)
		{
			ret = -1;
			break;
		}
		m_separatorCloudUpgradeLbl->resize(this->width(), 1);
		if (g_isReleasedForOverseas)
		{
			m_separatorCloudUpgradeLbl->move(0, 251);
		}
		else
		{
			m_separatorCloudUpgradeLbl->move(0, 188);
		}
		m_separatorCloudUpgradeLbl->setStyleSheet("background-color:#000000;");

		m_OpenApiCtrlInstance = OpenApiCtrl::getInstance();
		m_DevicesListCtrlInstance = DevicesListCtrl::getInstance();
	} while (0);



	if (0 != ret)
	{
		release();
	}
	return ret;
}

void DeviceSetView::release()
{
	if (NULL != m_separatorCloudUpgradeLbl)
	{
		delete m_separatorCloudUpgradeLbl;
		m_separatorCloudUpgradeLbl = NULL;
	}

	if (NULL != m_cloudUpgradeBtn)
	{
		delete m_cloudUpgradeBtn;
		m_cloudUpgradeBtn = NULL;
	}

	if (NULL != m_cloudUpgradeLbl)
	{
		delete m_cloudUpgradeLbl;
		m_cloudUpgradeLbl = NULL;
	}

	if (g_isReleasedForOverseas)
	{
		if (NULL != m_modifyPasswordBox)
		{
			delete m_modifyPasswordBox;
			m_modifyPasswordBox = NULL;
		}

		if (NULL != m_separatorModifyPasswordLbl)
		{
			delete m_separatorModifyPasswordLbl;
			m_separatorModifyPasswordLbl = NULL;
		}

		if (NULL != m_modifyPasswordBtn)
		{
			delete m_modifyPasswordBtn;
			m_modifyPasswordBtn = NULL;
		}

		if (NULL != m_modifyPasswordLbl)
		{
			delete m_modifyPasswordLbl;
			m_modifyPasswordLbl = NULL;
		}
	}

	if (NULL != m_SeparatorCloudStorageStatusLbl)
	{
		delete m_SeparatorCloudStorageStatusLbl;
		m_SeparatorCloudStorageStatusLbl = NULL;
	}

	if (NULL != m_CloudStorageStatusBtn)
	{
		delete m_CloudStorageStatusBtn;
		m_CloudStorageStatusBtn = NULL;
	}

	if (NULL != m_CloudStorageStatusLbl)
	{
		delete m_CloudStorageStatusLbl;
		m_CloudStorageStatusLbl = NULL;
	}

	if (NULL != m_SeparatorAlarmStatusLbl)
	{
		delete m_SeparatorAlarmStatusLbl;
		m_SeparatorAlarmStatusLbl = NULL;
	}

	if (NULL != m_AlarmStatusBtn)
	{
		delete m_AlarmStatusBtn;
		m_AlarmStatusBtn = NULL;
	}

	if (NULL != m_AlarmStatusLbl)
	{
		delete m_AlarmStatusLbl;
		m_AlarmStatusLbl = NULL;
	}

	if (NULL != m_WorkBar)
	{
		delete m_WorkBar;
		m_WorkBar = NULL;
	}

	if (NULL != m_statusLbl)
	{
		delete m_statusLbl;
		m_statusLbl = NULL;
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

void DeviceSetView::setDeviceIndex(int deviceIndex)
{
	m_DeviceIndex = deviceIndex;
}

void DeviceSetView::show()
{
	ChannelInfo* channelInfo = m_DevicesListCtrlInstance->getChannelInfo(m_DeviceIndex);
	if (NULL != channelInfo)
	{
		QString alarmStatus = "";
		QString sRet = OpenApiCtrl::getInstance()->getDeviceCameraStatus(channelInfo->deviceId, channelInfo->channelId, "motionDetect", alarmStatus);
		if ("OK" != sRet)
		{
			m_statusLbl->setText(tr("Status>>>Get device alarm status failed") + "[" + sRet + "]");
		}
		//获取报警状态
		channelInfo->channelAlarmStatus = ("on" == alarmStatus) ? true : false;
		setAlarmStatusBtnPixmap(("on" == alarmStatus) ? true : false);

		int retCloudStorageStatus = OpenApiCtrl::getInstance()->getStorageStrategy(channelInfo->deviceId, channelInfo->channelId);
		setCloudStorageStatusBtnPixmap((retCloudStorageStatus == 1) ? true : false);

		m_cloudUpgradeBtn->show();
		bool ret = OpenApiCtrl::getInstance()->getDeviceVersionList(channelInfo->deviceId);
		if (!ret)
		{
			m_cloudUpgradeBtn->hide();
		}
	}

	m_statusLbl->setText("");

	return;
}

void DeviceSetView::setAlarmStatusBtnPixmap(bool flag)
{
	QPixmap alarmStatusPixmap;
	if (flag)
	{
		alarmStatusPixmap.load("Skin/common_switch_on.png");
	}
	else
	{
		alarmStatusPixmap.load("Skin/common_switch_off.png");
	}
	m_AlarmStatusBtn->setPixmap(alarmStatusPixmap);
}

void DeviceSetView::setCloudStorageStatusBtnPixmap(bool flag)
{
	QPixmap cloudStorageStatusPixmap;
	if (flag)
	{
		cloudStorageStatusPixmap.load("Skin/common_switch_on.png");
	}
	else
	{
		cloudStorageStatusPixmap.load("Skin/common_switch_off.png");
	}
	m_CloudStorageStatusBtn->setPixmap(cloudStorageStatusPixmap);
}

void DeviceSetView::slotChangeAlarmStatus()
{
	ChannelInfo* channelInfo = m_DevicesListCtrlInstance->getChannelInfo(m_DeviceIndex);
	if (NULL != channelInfo)
	{
		//获取报警状态
		bool alarmStatusFlag = (true == channelInfo->channelAlarmStatus) ? false : true;
		QString ret = m_OpenApiCtrlInstance->setDeviceCameraStatus(channelInfo->deviceId, channelInfo->channelId, "motionDetect", alarmStatusFlag);
		if ("OK" == ret)
		{
			channelInfo->channelAlarmStatus = alarmStatusFlag ? true : false;
			setAlarmStatusBtnPixmap(alarmStatusFlag);
			m_statusLbl->setText(tr("Status>>>Modify device alarm status succeed"));
		}
		else
		{
			m_statusLbl->setText(tr("Status>>>Modify device alarm status failed") + "[" + ret + "]");
		}
	}
	return;
}

void DeviceSetView::slotChangeCloudStorageStatus()
{
	ChannelInfo* channelInfo = m_DevicesListCtrlInstance->getChannelInfo(m_DeviceIndex);
	int retCloudStorageStatus = OpenApiCtrl::getInstance()->getStorageStrategy(channelInfo->deviceId, channelInfo->channelId);
	if (NULL != channelInfo)
	{
		bool cloudStorageStatusFlag = (1 == retCloudStorageStatus) ? false : true;
		QString ret = m_OpenApiCtrlInstance->setStorageStrategy(channelInfo->deviceId, channelInfo->channelId, cloudStorageStatusFlag);
		if ("OK" == ret)
		{
			channelInfo->csStatus = cloudStorageStatusFlag ? 1 : 0;
			setCloudStorageStatusBtnPixmap(cloudStorageStatusFlag);
			m_statusLbl->setText(tr("Status>>>Set cloud storage status succeed"));
		}
		else
		{
			m_statusLbl->setText(tr("Status>>>Set cloud storage status failed") + "[" + ret + "]");
		}
	}
	return;
}

void DeviceSetView::slotModifyPassword()
{
	m_modifyPasswordBox->show();
	return;
}

void DeviceSetView::slotModifyPasswordBoxOK(QString oldPwd, QString newPwd)
{
	ChannelInfo* channelInfo = m_DevicesListCtrlInstance->getChannelInfo(m_DeviceIndex);
	if (NULL != channelInfo)
	{
		QString ret = m_OpenApiCtrlInstance->modifyDevicePassword(channelInfo->deviceId, oldPwd, newPwd);
		if ("OK" == ret)
		{
			m_statusLbl->setText(tr("Status>>>Modify password succeed"));
		}
		else
		{
			m_statusLbl->setText(tr("Status>>>Modify password failed") + "[" + ret + "]");
		}
	}
	return;
}

void DeviceSetView::slotCloudUpgrade()
{
	ChannelInfo* channelInfo = m_DevicesListCtrlInstance->getChannelInfo(m_DeviceIndex);
	if (NULL != channelInfo)
	{
		QString ret = m_OpenApiCtrlInstance->upgradeDevice(channelInfo->deviceId);
		if ("OK" == ret)
		{
			m_statusLbl->setText(tr("Status>>>Cloud upgrade..."));
		}
		else
		{
			m_statusLbl->setText(tr("Status>>>Cloud upgrade failed") + "[" + ret + "]");
		}
	}
	return;
}

void DeviceSetView::slotReturnToDevicesList()
{
	//this->hide();
	emit sgnReturnToDevicesList(false);
	return;
}
