#include "DevicesListView.h"

extern bool g_isReleasedForOverseas;

DevicesListView::DevicesListView(QWidget* parent)
	: QWidget(parent)
{
	m_SeparatorLbl = NULL;
	m_SeparatorLb2 = NULL;
	m_SeparatorLb3 = NULL;
	m_ToolBar = NULL;
	m_ReturnToLoginBtn = NULL;
	m_AddDeviceBtn = NULL;
	m_ScrollView = NULL;
	m_DevicesListCtrlInstance = NULL;
	m_ThreadCtrl = NULL;
	m_ChannelInfoList = NULL;
	m_decryptKeyBox = NULL;
	m_decryptKeyIndex = -1;
	m_searchDeviceBar = NULL;
	m_workBar = NULL;
	m_HintLbl = NULL;
	m_HintIcon = NULL;
	m_FindDeviceBtn = NULL;
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
		//分割线
		m_SeparatorLbl = new (std::nothrow) QLabel(this);
		if (NULL == m_SeparatorLbl)
		{
			ret = -1;
			break;
		}
		m_SeparatorLbl->resize(this->width(), 1);
		m_SeparatorLbl->move(0, 0);
		m_SeparatorLbl->setStyleSheet("background-color:#fd8b30;");
		//
		m_ToolBar = new (std::nothrow) QWidget(this);
		if (NULL == m_ToolBar)
		{
			ret = -1;
			break;
		}
		m_ToolBar->resize(this->width(), 38);//ToolBar高度：38
		m_ToolBar->move(0, 1);
		m_ToolBar->setStyleSheet("background-color:#2c2d30;");
		//返回按钮
		m_ReturnToLoginBtn = new (std::nothrow) IconTextBtn(m_ToolBar);
		if (NULL == m_ReturnToLoginBtn)
		{
			ret = -1;
			break;
		}
		m_ReturnToLoginBtn->setBtnAttribute("Skin/common_icon_back", tr("Back"), 11, QColor(0xb0, 0xaf, 0xaf));
		m_ReturnToLoginBtn->move(22, 6);
		connect(m_ReturnToLoginBtn, SIGNAL(clicked()), this, SLOT(slotReturnToLogin()));

		//绑定设备按钮
		m_AddDeviceBtn = new (std::nothrow) IconTextBtn(m_ToolBar);
		if (NULL == m_AddDeviceBtn)
		{
			ret = -1;
			break;
		}
		m_AddDeviceBtn->setBtnAttribute("Skin/common_icon_add", tr("Bind Device"), 11, QColor(0xb0, 0xaf, 0xaf));
		m_AddDeviceBtn->move(this->width() - m_AddDeviceBtn->width() - 30, 6);
		connect(m_AddDeviceBtn, SIGNAL(clicked()), this, SLOT(slotShowAddDevice()));
		//根据设备ID搜索设备
		m_workBar = new (std::nothrow) QWidget(this);
		if (NULL == m_workBar)
		{
			ret = -1;
			break;
		}
		m_workBar->resize(this->width(), 46);//搜索栏高度：46
		m_workBar->move(0, 39);
		m_workBar->setAutoFillBackground(true);
		QPalette bgPalette;
		bgPalette.setBrush(QPalette::Window, QColor(0x20, 0x22, 0x24));
		m_workBar->setPalette(bgPalette);

		m_searchDeviceBar = new (std::nothrow) SearchDeviceBar(m_workBar);
		if (NULL == m_searchDeviceBar)
		{
			ret = -1;
			break;
		}
		m_searchDeviceBar->init();
		m_searchDeviceBar->move(280, 7);
		connect(m_searchDeviceBar, SIGNAL(sgnSearchDevice(QString)), this, SLOT(slotSearchDevice(QString)));

		//输入为空校验并提示信息
		m_HintLbl = new (std::nothrow) QLabel(m_workBar);
		if (NULL == m_HintLbl)
		{
			ret = -1;
			break;
		}
		m_HintLbl->setAlignment(Qt::AlignTop);
		m_HintLbl->setWordWrap(true);
		m_HintLbl->setStyleSheet("color:#fe3e3e;font:9pt;font-family:Microsoft YaHei;");
		m_HintLbl->resize(250, 20);
		m_HintLbl->move(60, 16);
		m_HintLbl->hide();

		m_HintIcon = new (std::nothrow) QLabel(m_workBar);
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

		//分隔线
		m_SeparatorLb2 = new (std::nothrow) QLabel(m_workBar);
		if (NULL == m_SeparatorLb2)
		{
			ret = -1;
			break;
		}
		m_SeparatorLb2->resize(m_workBar->width(), 1);
		m_SeparatorLb2->move(0, 85);
		m_SeparatorLb2->setStyleSheet("background-color:#323436;");

		m_SeparatorLb3 = new (std::nothrow) QLabel(m_workBar);
		if (NULL == m_SeparatorLb3)
		{
			ret = -1;
			break;
		}
		m_SeparatorLb3->resize(m_workBar->width(), 1);
		m_SeparatorLb3->move(0, 86);
		m_SeparatorLb3->setStyleSheet("background-color:#561c12;");

		//设备信息列表展示
		m_ScrollView = new (std::nothrow) BaseScrollView(this);
		if (NULL == m_ScrollView)
		{
			ret = -1;
			break;
		}
		m_ScrollView->resize(this->width(), this->height() - 86);//列表展示部分宽高86
		m_ScrollView->move(0, 86);


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

		m_ThreadCtrlGetP2PPort = new (std::nothrow) ThreadCtrl(this, PROTO_GET_DEVICE_P2PPORT);
		if (NULL == m_ThreadCtrlGetP2PPort)
		{
			ret = -1;
			break;
		}
		connect(m_ThreadCtrlGetP2PPort, SIGNAL(resultReady(int)), this, SLOT(slotGetP2PPortResult(int)));

		m_decryptKeyBox = new (std::nothrow) MyEditBox(this);
		if (NULL == m_decryptKeyBox)
		{
			ret = -1;
			break;
		}
		ret = m_decryptKeyBox->init(tr("Please Input Decrypt Key"));
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

	if (NULL != m_ThreadCtrlGetP2PPort)
	{
		m_ThreadCtrlGetP2PPort->quit();
		m_ThreadCtrlGetP2PPort->deleteLater();
	}
	

	if (NULL != m_ScrollView)
	{
		delete m_ScrollView;
		m_ScrollView = NULL;
	}
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
	if (NULL != m_SeparatorLb3)
	{
		delete m_SeparatorLb3;
		m_SeparatorLb3 = NULL;
	}

	if (NULL != m_SeparatorLb2)
	{
		delete m_SeparatorLb2;
		m_SeparatorLb2 = NULL;
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

	if (NULL != m_searchDeviceBar)
	{
		delete m_searchDeviceBar;
		m_searchDeviceBar = NULL;
	}

	if (NULL != m_workBar)
	{
		delete m_workBar;
		m_workBar = NULL;
	}
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
void DevicesListView::slotSearchDevice(QString deviceID)
{

	printf("\n==DevicesListView::slotSearchDevice deviceID=%s\n", deviceID.toStdString().c_str());
	if (deviceID.isEmpty())
	{
		//m_HintLbl->setText(tr("Please input the device serial number!"));
		//m_HintLbl->show();
		//m_HintIcon->show();

		slotGetDevicesList();
	}
	else
	{
		m_HintLbl->hide();
		m_HintIcon->hide();
		//根据设备ID获取设备信息
		m_DevicesListCtrlInstance = DevicesListCtrl::getInstance();
		m_ChannelInfoList = m_DevicesListCtrlInstance->getChannelInfoList();

		if (NULL != m_DevicesListCtrlInstance)
		{
			m_DevicesListCtrlInstance->clearChannelInfoList();
			if (NULL != m_ThreadCtrl)
			{
				m_ThreadCtrl->quit();
			}
			m_ThreadCtrl->setProtoType(PROTO_GET_DEVICE_BYID);
			QByteArray ba = deviceID.toLatin1();
			char *tmp = ba.data();
			char *buf = new char[strlen(tmp) + 1];
			memset(buf, 0, strlen(tmp) + 1);
			strcpy(buf, tmp);
			m_ThreadCtrl->setParamter((void*)buf, m_ChannelInfoList);
			m_ThreadCtrl->start();

		}
		connect(m_ThreadCtrl, SIGNAL(resultReady(int)), this, SLOT(slotSearchResult(int)));
	}
}

void DevicesListView::slotSearchResult(int result)
{
	if (1 == result)
	{
		int channelNum = m_ChannelInfoList->size();
		printf("\n DevicesListView::slotSearchResult channelNum = %d\n", channelNum);
		connect(m_ThreadCtrl, SIGNAL(resultReady(int)), this, SLOT(slotHandleResult(int)));
	}
	else
	{
		printf("\n DevicesListView::slotSearchResult result != 1\n");
	}

	return;
}
void DevicesListView::slotGetDevicesList()
{
	/* 不使能加载设备封面图，防止设备列表被清空后引发的数组访问越界问题 */
	m_DevicesListCtrlInstance->enableLoadChannelPic(false);

	clearDeviceViewVector();
	m_ScrollView->m_rootWidget->setFixedHeight(m_ScrollView->height());

	m_DevicesListCtrlInstance->clearChannelInfoList();
	m_ChannelInfoList = m_DevicesListCtrlInstance->getChannelInfoList();
	if (m_ThreadCtrl->isRunning())
	{
		m_ThreadCtrl->quit();
	}
	m_ThreadCtrl->setProtoType(PROTO_GET_DEVICES_LIST);
	m_ThreadCtrl->setParamter(NULL, m_ChannelInfoList);
	m_ThreadCtrl->start();

	return;
}

void DevicesListView::onGetDevicesListP2PPort()
{
	if (m_DeviceViewVector.size() > 0)
	{
		//异步获取P2P端口号
		if (m_ThreadCtrlGetP2PPort->isRunning())
		{
			m_ThreadCtrlGetP2PPort->quit();
		}
		m_ThreadCtrlGetP2PPort->setProtoType(PROTO_GET_DEVICE_P2PPORT);
		m_ThreadCtrlGetP2PPort->setParamter(NULL, m_ChannelInfoList);
		m_ThreadCtrlGetP2PPort->start();
	}
}

void DevicesListView::slotGetP2PPortResult(int result)
{
	for (int i = 0; i < m_ChannelInfoList->size(); ++i)
	{
		printf("\n DevicesListView::slotGetP2PPortResult deviceId = [%s] , P2PPort = [%d] \n", m_ChannelInfoList->at(i)->deviceId.toStdString().c_str(), m_ChannelInfoList->at(i)->p2pPort);
	}
}

void DevicesListView::slotReturnToLogin()
{
	emit sgnReturnToLogin();
	return;
}

void DevicesListView::slotShowAddDevice()
{
	emit sgnShowAddDevice();
	return;
}

void DevicesListView::slotShowSearchDevice()
{
	emit sgnShowSearchDevice();
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
	emit sgnShowDeviceOperate(deviceIndex);
	return;
}

void DevicesListView::slotPlay(int deviceIndex)
{
	emit sgnPlay(deviceIndex);
	return;
}

void DevicesListView::slotShowLocalRecord(int deviceIndex)
{
	emit sgnShowLocalRecord(deviceIndex);
	return;
}

void DevicesListView::slotShowCloudRecord(int deviceIndex)
{
	emit sgnShowCloudRecord(deviceIndex);
	return;
}

void DevicesListView::slotShowAlarmMsgsListView(int deviceIndex)
{
	emit sgnShowAlarmMsgsListView(deviceIndex);
	return;
}

void DevicesListView::slotHandleResult(int result)
{
	clearDeviceViewVector();
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
		for (int i = 0; i < m_ChannelInfoList->size() && i < 10; i++)
		{
			if (m_ScrollView->m_rootWidget->height() < i / 3 * deviceViewHeight + deviceViewHeight + 28)
			{
				m_ScrollView->m_rootWidget->setFixedHeight(i / 3 * deviceViewHeight + deviceViewHeight + 28);
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
			deviceView->setDeviceIndex(i);
			if (m_ChannelInfoList->at(i)->multiFlag)
			{
				QString MultiShowName = "";

				if (m_ChannelInfoList->at(i)->movable)
				{
					MultiShowName = QString("[") + m_ChannelInfoList->at(i)->deviceName + QString("]-") + tr("MovingLens");
				}
				else
				{
					MultiShowName = QString("[") + m_ChannelInfoList->at(i)->deviceName + QString("]-") + tr("FixedLens");
				}
				deviceView->setChannelName(MultiShowName);
			}
			else
			{
				deviceView->setChannelName(m_ChannelInfoList->at(i)->channelName);
			}
			
			deviceView->setChannelPic(channelPixmap);
			if (m_ChannelInfoList->at(i)->channelStatus != "online")
			{
				deviceView->setOfflineStatus();
			}
			else if (("1" == m_ChannelInfoList->at(i)->encryptMode) && (!(m_ChannelInfoList->at(i)->deviceAbility.contains("TCM"))))
			{
				deviceView->setDecryptStatus(true);
			}
			connect(deviceView, SIGNAL(sgnShowDeviceOperate(int)), this, SLOT(slotShowDeviceOperate(int)));
			connect(deviceView, SIGNAL(sgnPlay(int)), this, SLOT(slotPlay(int)));
			connect(deviceView, SIGNAL(sgnShowLocalRecord(int)), this, SLOT(slotShowLocalRecord(int)));
			connect(deviceView, SIGNAL(sgnShowCloudRecord(int)), this, SLOT(slotShowCloudRecord(int)));
			connect(deviceView, SIGNAL(sgnShowAlarmMsgsListView(int)), this, SLOT(slotShowAlarmMsgsListView(int)));
			connect(deviceView, SIGNAL(sgnGetDevicesList()), this, SLOT(slotGetDevicesList()));
			connect(deviceView, SIGNAL(sgnDecryptShadeClicked(int)), this, SLOT(slotShowDecryptKeyBox(int)));
			deviceView->move(28 + 326 * (i % 3), 28 + deviceViewHeight * (i / 3));
			deviceView->show();

			m_DeviceViewVector.push_back(deviceView);
		}
	}
	else
	{
		/* 提示获取设备列表失败 */
	}

	if (m_DeviceViewVector.size() > 0)
	{
		/* 使能加载设备封面图 */
		m_DevicesListCtrlInstance->enableLoadChannelPic(true);

		emit sgnGetChannelPic(0);
	}

	onGetDevicesListP2PPort();
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
	m_ChannelInfoList->at(m_decryptKeyIndex)->decryptKey = decryptKey;
	m_DeviceViewVector.at(m_decryptKeyIndex)->setDecryptStatus(false);
}
