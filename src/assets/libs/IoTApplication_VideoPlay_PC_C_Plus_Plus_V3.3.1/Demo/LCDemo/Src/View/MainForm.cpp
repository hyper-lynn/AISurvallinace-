#include <QApplication>
#include <QDesktopWidget>
#include "LCOpenSDK_Api.h"
#include "LCOpenSdk_Utils.h"
#include "MainForm.h"

MainForm::MainForm(QWidget *parent)
    : QFrame(parent)
{
    m_HomePage                      = NULL;
    m_DevicesList                   = NULL;
    m_AddDevice                     = NULL;
    m_DeviceSet                     = NULL;
    m_realPlayView                  = NULL;
    m_recordListView                = NULL;
    m_recordPlayView                = NULL;
	m_content                       = NULL; 
	m_titleBar                      = NULL;
	m_mouseDown = false;
}

MainForm::~MainForm()
{
    release();
}

int MainForm::init()
{
    int ret = 0;

    do 
    {
        /** Set main window size */
        this->setFixedSize(646, 424);
        this->adjustSize();

		/** Remove system default title bar */
        this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint);

		/** Set window borderless */
		//setFrameShape(NoFrame);

		/** Use custom title bar */
		m_titleBar = new (std::nothrow)PageTitle(this);
		if (NULL == m_titleBar)
		{
			ret = -1;
			break;
		}
		ret = m_titleBar->init();
		if (0 != ret)
		{
			break;
		}
		//m_titleBar->setTitleText(tr("Home Page"));/** Default show home page */
		m_titleBar->setTitleText("Home Page");/** Default show home page */
		m_titleBar->setMaxmizeBtnVisible(false);
		m_titleBar->setFixedHeight(54);
		connect(m_titleBar, SIGNAL(sgnCloseWin()), this, SLOT(slotCloseWin()));

		/** Layout main page */
		m_content = new (std::nothrow)QWidget(this);
		if (NULL == m_content)
		{
			ret = -1;
			break;
		}

		QVBoxLayout *mlayout = new (std::nothrow)QVBoxLayout(this);
		if (NULL == mlayout)
		{
			ret = -1;
			break;
		}
		mlayout->addWidget(m_titleBar);
		mlayout->addWidget(m_content);
		mlayout->setMargin(0);
		mlayout->setSpacing(0);
		mlayout->setStretchFactor(m_content, 1);
		this->setLayout(mlayout);

		/** Initialize home page */
        m_HomePage = new LoginSelectView(m_content);
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
        connect(m_HomePage, &LoginSelectView::sgnShowDevicesList, this, &MainForm::slotShowDevicesList);
        m_HomePage->show();

		/** Initialize device list page */
        m_DevicesList = new (std::nothrow) DevicesListView(m_content);
        if (NULL == m_DevicesList)
        {
            ret = -1;
            break;
        }
        ret = m_DevicesList->init();
        if (0 != ret)
        {
            break;
        }
        connect(this, SIGNAL(sgnGetDevicesList()), m_DevicesList, SLOT(slotGetDevicesList()));
        connect(m_DevicesList, SIGNAL(sgnReturnToLogin()), this, SLOT(slotReturnToLogin()));
        connect(m_DevicesList, SIGNAL(sgnShowAddDevice()), this, SLOT(slotShowAddDevice()));
        connect(m_DevicesList, SIGNAL(sgnShowDeviceOperate(int)), this, SLOT(slotShowDeviceOperate(int)));
        connect(m_DevicesList, SIGNAL(sgnPlay(int)), this, SLOT(slotPlay(int)));
        connect(m_DevicesList, SIGNAL(sgnShowLocalRecord(int)), this, SLOT(slotShowLocalRecordList(int)));
        connect(m_DevicesList, SIGNAL(sgnShowCloudRecord(int)), this, SLOT(slotShowCloudRecordList(int)));

        m_DevicesList->hide();

		/** Initialize device add page */
        m_AddDevice = new (std::nothrow) DeviceAddView(m_content);
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
        m_AddDevice->hide();

		/** Initialize device setting page */
        m_DeviceSet = new (std::nothrow) DeviceSetView(m_content);
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
        m_DeviceSet->hide();




		/** Initialize real-time video preview page */
        m_realPlayView = new (std::nothrow)RealPlayView(m_content);
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

		/** Initialize record list (cloud record and device record shared) page */
        m_recordListView = new (std::nothrow)RecordListView(m_content);
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
        connect(m_recordListView, SIGNAL(sgnPlayCloudRecord(int,int)), this, SLOT(slotPlayCloudRecord(int,int)));
        connect(m_recordListView, SIGNAL(sgnPlayDeviceRecord(int, int)), this, SLOT(slotPlayDeviceRecord(int, int)));
        connect(m_recordListView, SIGNAL(sgnReturnToDevicesList(bool)), this, SLOT(slotReturnToDevicesList(bool)));

		/** Initialize record playback (cloud record and device record shared) page */
        m_recordPlayView = new RecordPlayView(m_content);
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

		/** Enable OpenSDK log switch */
		LCOpenSdk_Utils::SetLogInfo(LCOpenSdk_Utils::All, "DEMO", 10*1024*1024, LCOpenSdk_Utils::RollFile);
		//LCOpenSdk_Utils::SetMobileLogFile("D:\LCOpenSDK0325.txt");
		//LCOpenSdk_Utils::SetMobileLogLevel(LCOpenSdk_Utils::All);
		// saveStream
		// LCOpenSdk_Utils::setSaveStreamFlag(true);// Save audio/video after collection and encoding (before streaming)
		const char* path=LCOpenSdk_Utils::getSaveStreamPath();
		LCOpenSDK_Api::GetInstance()->setLoggerStatus(true);
    } while (0);

    if (0 != ret)
    {
        release();
    }
	LCOpenSdk_Utils::loadSubModules();
    return ret;
}

void MainForm::release()
{
    if (NULL != m_HomePage)
    {
        delete m_HomePage;
        m_HomePage = NULL;
    }

    if (NULL != m_DevicesList)
    {
        delete m_DevicesList;
        m_DevicesList = NULL;
    }

    if (NULL != m_AddDevice)
    {
        delete m_AddDevice;
        m_AddDevice = NULL;
    }

	if (m_titleBar)
	{
		delete m_titleBar;
		m_titleBar = NULL;
	}

    if (NULL != m_DeviceSet)
    {
        delete m_DeviceSet;
        m_DeviceSet = NULL;
    }

    if (m_realPlayView)
    {
        delete m_realPlayView;
        m_realPlayView = NULL;
    }

    if (m_recordListView)
    {
        delete m_recordListView;
        m_recordListView = NULL;
    }

    if (m_recordPlayView)
    {
        delete m_recordPlayView;
        m_recordPlayView = NULL;
    }

	if (m_content)
	{
		delete m_content;
		m_content = NULL;
	}

    return;
}

void MainForm::slotShowDevicesList()
{
    QPoint desktopCenter = QApplication::desktop()->geometry().center();
    this->setFixedSize(1022, 670);
    this->move(desktopCenter.x() - 511, desktopCenter.y() - 335);
    //m_titleBar->setTitleText(tr("Devices List Page"));
	m_titleBar->setTitleText("Devices List Page");
    m_DevicesList->show();
    emit sgnGetDevicesList();
    return;
}

void MainForm::slotReturnToLogin()
{
    QPoint desktopCenter = QApplication::desktop()->geometry().center();
    this->setFixedSize(646, 424);
    this->move(desktopCenter.x() - 323, desktopCenter.y() - 212);
    m_titleBar->setTitleText("Home Page");
    m_HomePage->show();
    return;
}

void MainForm::slotShowAddDevice()
{
	m_titleBar->setTitleText(tr("Device Binding Page"));
    m_AddDevice->show();
    return;
}

void MainForm::slotReturnToDevicesList(bool refreshDevicesList)
{
	//m_titleBar->setTitleText(tr("Devices List Page"));
	m_titleBar->setTitleText("Devices List Page");
    m_DevicesList->show();
    if (refreshDevicesList)
    {
        emit sgnGetDevicesList();
    }
}

void MainForm::slotShowDeviceOperate(int deviceIndex)
{
	m_titleBar->setTitleText(tr("Device Setting Page"));
    m_DeviceSet->setDeviceIndex(deviceIndex);
    m_DeviceSet->show();
    return;
}


void MainForm::slotPlay(int deviceIndex)
{
    //m_titleBar->setTitleText(tr("Real Video Page"));
	m_titleBar->setTitleText("Real Video Page");
    this->setFixedSize(1022, 670);
    this->adjustSize();

    m_realPlayView->refreshLayout();
    m_realPlayView->showRealPlayView(deviceIndex);
    return;
}

void MainForm::slotShowLocalRecordList(int deviceIndex)
{
    //m_titleBar->setTitleText(tr("Device Records List Page"));
	m_titleBar->setTitleText("Device Records List Page");
    this->setFixedSize(1022, 670);
    this->adjustSize();

    m_recordListView->refreshLayout();
    m_recordListView->showDeviceRecordListView(deviceIndex);
    return;
}

void MainForm::slotShowCloudRecordList(int deviceIndex)
{
    m_titleBar->setTitleText("Cloud Records List Page");
    this->setFixedSize(1022, 670);
    this->adjustSize();

    m_recordListView->refreshLayout();
    m_recordListView->showCloudRecordListView(deviceIndex);
    return;
}

void MainForm::slotPlayCloudRecord(int deviceIndex, int recordIndex)
{
    m_titleBar->setTitleText("Cloud Records Playback Page");
    this->setFixedSize(1022, 670);
    this->adjustSize();

    m_recordPlayView->refreshLayout();
    m_recordPlayView->showCloudRecordPlayView(deviceIndex, recordIndex);
}

void MainForm::slotPlayDeviceRecord(int deviceIndex, int recordIndex)
{
    //m_titleBar->setTitleText(tr("Device Records Playback Page"));
	m_titleBar->setTitleText("Device Records Playback Page");
    this->setFixedSize(1022, 670);
    this->adjustSize();

    m_recordPlayView->refreshLayout();
    m_recordPlayView->showDeviceRecordPlayView(deviceIndex, recordIndex);
}

void MainForm::slotBackToRecordList(int recordType)
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

void MainForm::mousePressEvent( QMouseEvent *e )
{
	m_oldPos = e->pos();

	if (this->m_titleBar->rect().contains(e->pos()))
	{
		m_mouseDown = e->button() == Qt::LeftButton;
	}
}

void MainForm::mouseMoveEvent( QMouseEvent *e )
{
	int x = e->x();
	int y = e->y();

	bool left = true;
	bool bottom = true;
	bool right  = true;
	bool top    = true; 

	if (m_mouseDown) 
	{
		/** Move window by dragging title bar */
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
		/** Set mouse focus cursor, mainly for window stretch, since window stretch and maximize are not supported, commented out */
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

void MainForm::mouseReleaseEvent( QMouseEvent *e )
{
	m_mouseDown = false;
}

void MainForm::closeEvent(QCloseEvent *event) {

	// if (userWantsToSave) {
	//     saveData();
	// }

	m_realPlayView->stopAllPlay();

	//LCOpenSdk_Utils::destroyThreadPool();

	event->accept();
	// event->ignore();
}

void MainForm::slotCloseWin()
{
    LCOpenSDK_Api::GetInstance()->uninitOpenApi();
	this->close();
}
