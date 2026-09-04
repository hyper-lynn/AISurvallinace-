#include "LCOpenSDKDemo.h"
#include <QDesktopWidget>
#include "lcopensdk_api/LCOpenSDK_Api.h"
#include "lcopensdk_utils/LCOpenSdk_Utils.h"
LCOpenSDKDemo::LCOpenSDKDemo(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	init();
	this->installEventFilter(this);
	connect(this, SIGNAL(showEvent(QShowEvent*)), this, SLOT(onShow()));
}

int LCOpenSDKDemo::init()
{
	int ret = 0;
	do {
		/**设置主窗口大小*/
		this->setFixedSize(646, 424);
		this->adjustSize();

		/**将系统自带的标题栏去掉*/
		this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint);

		//加载css样式表
		QString strCssPath = QString("Skin/demo.css");
		QString strStyle = "";
		QFile fpSytle(strCssPath);
		if (fpSytle.open(QIODevice::ReadOnly | QIODevice::Text))
		{
			strStyle = fpSytle.readAll();
		}

		if (!strStyle.isEmpty())
		{
			this->setStyleSheet(strStyle);
		}

		// 自定义标题头
		ui.titleBar->init();
		ui.titleBar->setTitleText(tr("Home Page"));/**默认显示首页*/
		ui.titleBar->setMaxmizeBtnVisible(false);
		connect(ui.titleBar, SIGNAL(sgnCloseWin()), this, SLOT(slotCloseWin()));
		connect(ui.titleBar, SIGNAL(sgnMinimize()), this, SLOT(slotMinimize()));

		// 将下面的页面添加到stackWidget中
		/**初始化首页*/
		m_HomePage = new (std::nothrow) LoginSelectView(ui.stackedWidget);
		m_HomePage->resize(m_HomePage->parentWidget()->size());
		m_HomePage->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
		if (NULL == m_HomePage)
		{
			ret = -1;
			break;
		}
		ret = m_HomePage->init();
		if (0 != ret)
		{
			break;
		}
		connect(m_HomePage, SIGNAL(sgnShowDevicesList()), this, SLOT(slotShowDevicesList()));
		ui.stackedWidget->addWidget(m_HomePage);
		//int stackedIndex = ui.stackedWidget->insertWidget(E_Widget_HomePage, m_HomePage);
		//ui.stackedWidget->setCurrentIndex(E_Widget_HomePage);

		/**初始化设备列表页*/
		m_DevicesList = new (std::nothrow) DevicesListView(ui.stackedWidget);
		if (NULL == m_DevicesList)
		{
			ret = -1;
			break;
		}
		ret = m_DevicesList->init();
		m_DevicesList->setFocusPolicy(Qt::ClickFocus);
		if (0 != ret)
		{
			break;
		}
		connect(this, SIGNAL(sgnGetDevicesList()), m_DevicesList, SLOT(slotGetDevicesList()));
		connect(m_DevicesList, SIGNAL(sgnReturnToLogin()), this, SLOT(slotReturnToHomePage()));
		connect(m_DevicesList, SIGNAL(sgnShowAddDevice()), this, SLOT(slotShowAddDevice()));
		connect(m_DevicesList, SIGNAL(sgnShowDeviceOperate(int)), this, SLOT(slotShowDeviceOperate(int)));
		connect(m_DevicesList, SIGNAL(sgnPlay(int)), this, SLOT(slotPlay(int)));
		connect(m_DevicesList, SIGNAL(sgnShowLocalRecord(int)), this, SLOT(slotShowLocalRecordList(int)));
		connect(m_DevicesList, SIGNAL(sgnShowCloudRecord(int)), this, SLOT(slotShowCloudRecordList(int)));
		connect(m_DevicesList, SIGNAL(sgnShowAlarmMsgsListView(int)), this, SLOT(slotShowAlarmMsgsListView(int)));
		//stackedIndex = ui.stackedWidget->insertWidget(E_Widget_DevicesListView, m_DevicesList);
		ui.stackedWidget->addWidget(m_DevicesList);

		/**初始化设备添加页*/
		m_AddDevice = new (std::nothrow) DeviceAddView(ui.stackedWidget);
		if (NULL == m_AddDevice)
		{
			ret = -1;
			break;
		}
		ret = m_AddDevice->init();
		if (0 != ret)
		{
			break;
		}
		connect(m_AddDevice, SIGNAL(sgnReturnToDevicesList(bool)), this, SLOT(slotReturnToDevicesList(bool)));
		//stackedIndex = ui.stackedWidget->insertWidget(E_Widget_DeviceAddView, m_AddDevice);
		ui.stackedWidget->addWidget(m_AddDevice);

		/**初始化设备设置页*/
		m_DeviceSet = new (std::nothrow) DeviceSetView(ui.stackedWidget);
		if (NULL == m_DeviceSet)
		{
			ret = -1;
			break;
		}
		ret = m_DeviceSet->init();
		if (0 != ret)
		{
			break;
		}
		connect(m_DeviceSet, SIGNAL(sgnReturnToDevicesList(bool)), this, SLOT(slotReturnToDevicesList(bool)));
		//stackedIndex = ui.stackedWidget->insertWidget(E_Widget_DeviceSetView, m_DeviceSet);
		ui.stackedWidget->addWidget(m_DeviceSet);

		/**初始化报警消息页*/
		m_alarmMsgsListView = new (std::nothrow) AlarmMsgsListView(ui.stackedWidget);
		if (NULL == m_alarmMsgsListView)
		{
			ret = -1;
			break;
		}
		ret = m_alarmMsgsListView->init();
		if (0 != ret)
		{
			ret = -1;
			break;
		}
		connect(m_alarmMsgsListView, SIGNAL(sgnReturnToDevicesList(bool)), this, SLOT(slotReturnToDevicesList(bool)));
		connect(this, SIGNAL(sgnGetCurrentAlarmMsgs()), m_alarmMsgsListView, SLOT(slotGetCurrentAlarmMsgs()));
		//stackedIndex = ui.stackedWidget->insertWidget(E_Widget_AlarmMsgListView, m_alarmMsgsListView);
		ui.stackedWidget->addWidget(m_alarmMsgsListView);

		/**初始化实时视频预览页*/
		m_realPlayView = new (std::nothrow)RealPlayView(ui.stackedWidget);
		if (NULL == m_realPlayView)
		{
			ret = -1;
			break;
		}
		ret = m_realPlayView->init();
		if (0 != ret)
		{
			break;
		}
		connect(m_realPlayView, SIGNAL(sgnReturnToDevicesList(bool)), this, SLOT(slotReturnToDevicesList(bool)));
		//stackedIndex = ui.stackedWidget->insertWidget(E_Widget_RealPlayView, m_realPlayView);
		ui.stackedWidget->addWidget(m_realPlayView);

		/**初始化录像列表（云录像和设备录像共用）页*/
		m_recordListView = new (std::nothrow)RecordListView(ui.stackedWidget);
		if (NULL == m_recordListView)
		{
			ret = -1;
			break;
		}
		ret = m_recordListView->init();
		if (0 != ret)
		{
			break;
		}
		connect(m_recordListView, SIGNAL(sgnPlayCloudRecord(int, int)), this, SLOT(slotPlayCloudRecord(int, int)));
		connect(m_recordListView, SIGNAL(sgnPlayDeviceRecord(int, int)), this, SLOT(slotPlayDeviceRecord(int, int)));
		connect(m_recordListView, SIGNAL(sgnReturnToDevicesList(bool)), this, SLOT(slotReturnToDevicesList(bool)));
		//stackedIndex = ui.stackedWidget->insertWidget(E_Widget_RecordListView, m_recordListView);
		ui.stackedWidget->addWidget(m_recordListView);

		/**初始化录像播放（云录像和设备录像共用）页*/
		m_recordPlayView = new RecordPlayView(ui.stackedWidget);
		if (NULL == m_recordPlayView)
		{
			ret = -1;
			break;
		}
		ret = m_recordPlayView->init();
		if (0 != ret)
		{
			break;
		}
		connect(m_recordPlayView, SIGNAL(sgnBackToRecordList(int)), this, SLOT(slotBackToRecordList(int)));
		ui.stackedWidget->insertWidget(E_Widget_RecordPlayView, m_recordPlayView);

		/**打开OpenSDK日志开关*/
		LCOpenSdk_Utils::SetLogInfo(LCOpenSdk_Utils::All, "LCOpenSDK", 10 * 1024 * 1024, LCOpenSdk_Utils::RollFile);

	} while (0);

	return ret;
}


void LCOpenSDKDemo::slotShowDevicesList()
{
	QPoint desktopCenter = QApplication::desktop()->geometry().center();
	this->setFixedSize(1022, 670);
	this->move(desktopCenter.x() - 511, desktopCenter.y() - 335);
	ui.titleBar->setTitleText(tr("Devices List Page"));
	ui.stackedWidget->setCurrentIndex(E_Widget_DevicesListView);
	emit sgnGetDevicesList();
	return;
}

void LCOpenSDKDemo::slotReturnToHomePage()
{
	ui.titleBar->setTitleText(tr("Home Page"));
	QPoint desktopCenter = QApplication::desktop()->geometry().center();
	this->setFixedSize(646, 424);
	this->move(desktopCenter.x() - 323, desktopCenter.y() - 212);
	ui.stackedWidget->setCurrentIndex(E_Widget_HomePage);
	//返回主页反初始化
	LCOpenSDK_Api::GetInstance()->uninitOpenApi();
	return;
}

void LCOpenSDKDemo::slotShowAddDevice()
{
	ui.titleBar->setTitleText(tr("Device Binding Page"));
	ui.stackedWidget->setCurrentIndex(E_Widget_DeviceAddView);
	return;
}

void LCOpenSDKDemo::slotReturnToDevicesList(bool refreshDevicesList)
{
	ui.titleBar->setTitleText(tr("Devices List Page"));
	ui.stackedWidget->setCurrentIndex(E_Widget_DevicesListView);
	if (refreshDevicesList)
	{
		emit sgnGetDevicesList();
	}
}

void LCOpenSDKDemo::slotShowDeviceOperate(int deviceIndex)
{
	ui.titleBar->setTitleText(tr("Device Setting Page"));
	m_DeviceSet->setDeviceIndex(deviceIndex);
	m_DeviceSet->show();
	ui.stackedWidget->setCurrentIndex(E_Widget_DeviceSetView);
	return;
}

void LCOpenSDKDemo::slotShowAlarmMsgsListView(int deviceIndex)
{
	ui.titleBar->setTitleText(tr("Alarm Messages List Page"));
	m_alarmMsgsListView->setDeviceIndex(deviceIndex);
	m_alarmMsgsListView->show();
	ui.stackedWidget->setCurrentIndex(E_Widget_AlarmMsgListView);
	emit sgnGetCurrentAlarmMsgs();
}

void LCOpenSDKDemo::slotPlay(int deviceIndex)
{
	ui.titleBar->setTitleText(tr("Real Video Page"));
	this->setFixedSize(1022, 670);
	this->adjustSize();

	m_realPlayView->refreshLayout();
	m_realPlayView->showRealPlayView(deviceIndex);
	ui.stackedWidget->setCurrentIndex(E_Widget_RealPlayView);
	return;
}

void LCOpenSDKDemo::slotShowLocalRecordList(int deviceIndex)
{
	ui.titleBar->setTitleText(tr("Device Records List Page"));
	this->setFixedSize(1022, 670);
	this->adjustSize();

	m_recordListView->refreshLayout();
	m_recordListView->showDeviceRecordListView(deviceIndex);
	ui.stackedWidget->setCurrentIndex(E_Widget_RecordListView);
	return;
}

void LCOpenSDKDemo::slotShowCloudRecordList(int deviceIndex)
{
	ui.titleBar->setTitleText(tr("Cloud Records List Page"));
	this->setFixedSize(1022, 670);
	this->adjustSize();

	m_recordListView->refreshLayout();
	m_recordListView->showCloudRecordListView(deviceIndex);
	ui.stackedWidget->setCurrentIndex(E_Widget_RecordListView);
	return;
}

void LCOpenSDKDemo::slotPlayCloudRecord(int deviceIndex, int index)
{
	ui.titleBar->setTitleText(tr("Cloud Records Playback Page"));
	this->setFixedSize(1022, 670);
	this->adjustSize();

	m_recordPlayView->refreshLayout();
	m_recordPlayView->showCloudRecordPlayView(deviceIndex, index);
	ui.stackedWidget->setCurrentIndex(E_Widget_RecordPlayView);
}

void LCOpenSDKDemo::slotPlayDeviceRecord(int deviceIndex, int index)
{
	ui.titleBar->setTitleText(tr("Device Records Playback Page"));
	this->setFixedSize(1022, 670);
	this->adjustSize();
	m_recordPlayView->raise();

	m_recordPlayView->refreshLayout();
	m_recordPlayView->showDeviceRecordPlayView(deviceIndex, index);
	ui.stackedWidget->setCurrentIndex(E_Widget_RecordPlayView);
}

void LCOpenSDKDemo::slotBackToRecordList(int recordType)
{
	if (DEVICE_RECORD == recordType)
	{
		slotShowLocalRecordList(m_recordListView->getDeviceIndex());
	}
	else
	{
		slotShowCloudRecordList(m_recordListView->getDeviceIndex());
	}
}

void LCOpenSDKDemo::mousePressEvent(QMouseEvent *e)
{
	m_oldPos = e->pos();

	if (this->ui.titleBar->rect().contains(e->pos()))
	{
		m_mouseDown = e->button() == Qt::LeftButton;
	}
}

void LCOpenSDKDemo::mouseMoveEvent(QMouseEvent *e)
{
	int x = e->x();
	int y = e->y();

	bool left = true;
	bool bottom = true;
	bool right = true;
	bool top = true;

	if (m_mouseDown)
	{
		/**标题栏点击移动窗口*/
		int dx = x - m_oldPos.x();
		int dy = y - m_oldPos.y();

		QRect g = geometry();
		g.setLeft(g.left() + dx);
		g.setRight(g.right() + dx);
		g.setBottom(g.bottom() + dy);
		g.setTop(g.top() + dy);
		setGeometry(g);

		m_oldPos = QPoint(!left ? e->x() : m_oldPos.x(), !bottom ? e->y() : m_oldPos.y());
	}
	else
	{
		/**设置鼠标焦点的Cursor, 主要用于拉伸拉伸窗口用，由于目前不支持窗口拉伸和最大化，所以注释掉*/
		/*QRect r  = rect();
		left     = qAbs(x - r.left()) <= 5;
		right    = qAbs(x - r.right()) <= 5;
		bottom   = qAbs(y - r.bottom()) <= 5;
		top      = qAbs(y - r.top()) <= 5;
		bool hor = left | right;
		bool ver = bottom | top;

		if (hor && ver)
		{
		if (left)
		{
		setCursor(Qt::SizeBDiagCursor);
		}
		else
		{
		setCursor(Qt::SizeFDiagCursor);
		}
		}
		else if (hor)
		{
		setCursor(Qt::SizeHorCursor);
		}
		else if (ver)
		{
		setCursor(Qt::SizeVerCursor);
		}
		else
		{
		setCursor(Qt::ArrowCursor);
		}*/
	}
}

void LCOpenSDKDemo::mouseReleaseEvent(QMouseEvent *e)
{
	m_mouseDown = false;
}

void LCOpenSDKDemo::slotCloseWin()
{
	LCOpenSDK_Api::GetInstance()->uninitOpenApi();
	this->close();
}

void LCOpenSDKDemo::slotMinimize()
{
	showMinimized();
}


bool LCOpenSDKDemo::eventFilter(QObject *watched, QEvent *event)
{
	if (watched == this && event->type() == QEvent::WindowStateChange)
	{
		int i = this->windowState();
		if (this->windowState() == Qt::WindowNoState)
		{
			// 窗口恢复正常大小，触发重绘事件
			this->setFixedSize(1021, 670);
			this->setFixedSize(1022, 670);
		}
	}
	return QMainWindow::eventFilter(watched, event);
}
