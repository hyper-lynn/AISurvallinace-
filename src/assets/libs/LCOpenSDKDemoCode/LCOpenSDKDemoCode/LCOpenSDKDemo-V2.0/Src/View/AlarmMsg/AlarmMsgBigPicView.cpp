#include "AlarmMsgBigPicView.h"

AlarmMsgBigPicView::AlarmMsgBigPicView(QWidget* parent)
	: QDialog(parent)
{
	m_titleBar = NULL;
	m_titleLbl = NULL;
	m_maxOrRestoreBtn = NULL;
	m_closeBtn = NULL;
	m_alarmMsgBigPicLbl = NULL;
	m_lastBtn = NULL;
	m_nextBtn = NULL;
	m_isMousePressedInTitleBar = false;
	m_isMaximized = false;
}

AlarmMsgBigPicView::~AlarmMsgBigPicView()
{
	release();
}

int AlarmMsgBigPicView::init()
{
	int ret = 0;

	do
	{
		this->resize(926, 546);
		this->setModal(true);
		this->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);

		m_titleBar = new (std::nothrow) QWidget(this);
		if (NULL == m_titleBar)
		{
			ret = -1;
			break;
		}
		m_titleBar->resize(this->width(), 48);
		m_titleBar->move(0, 0);
		m_titleBar->setStyleSheet("background-color:#2c2d30;");

		m_titleLbl = new (std::nothrow) QLabel(m_titleBar);
		if (NULL == m_titleLbl)
		{
			ret = -1;
			break;
		}
		m_titleLbl->setFixedHeight(36);
		m_titleLbl->move(16, 6);
		m_titleLbl->setStyleSheet("color:#aaaaaa;font:12pt;font-family:Microsoft YaHei;");
		m_titleLbl->setText(tr("Alarm Message Picture"));
		m_titleLbl->adjustSize();

		m_maxOrRestoreBtn = new (std::nothrow) IconBtn(m_titleBar, "Skin/conmmon_icon_max");
		if (NULL == m_maxOrRestoreBtn)
		{
			ret = -1;
			break;
		}
		m_maxOrRestoreBtn->move(m_titleBar->width() - 70, 9);
		connect(m_maxOrRestoreBtn, SIGNAL(clicked()), this, SLOT(slotMaxOrRestore()));

		m_closeBtn = new (std::nothrow) IconBtn(m_titleBar, "Skin/conmmon_icon_close");
		if (NULL == m_closeBtn)
		{
			ret = -1;
			break;
		}
		m_closeBtn->move(m_titleBar->width() - 38, 9);
		connect(m_closeBtn, SIGNAL(clicked()), this, SLOT(slotClose()));

		m_alarmMsgBigPicLbl = new (std::nothrow) QLabel(this);
		if (NULL == m_alarmMsgBigPicLbl)
		{
			ret = -1;
			break;
		}
		m_alarmMsgBigPicLbl->resize(this->width(), this->height() - 48);
		m_alarmMsgBigPicLbl->move(0, 48);
		m_alarmMsgBigPicLbl->setScaledContents(true);

		m_lastBtn = new (std::nothrow) IconBtn(m_alarmMsgBigPicLbl, "Skin/icon_left");
		if (NULL == m_lastBtn)
		{
			ret = -1;
			break;
		}
		m_lastBtn->move(0, (m_alarmMsgBigPicLbl->height() - m_lastBtn->height()) / 2);
		connect(m_lastBtn, SIGNAL(clicked()), this, SLOT(slotLast()));

		m_nextBtn = new (std::nothrow) IconBtn(m_alarmMsgBigPicLbl, "Skin/icon_right");
		if (NULL == m_nextBtn)
		{
			ret = -1;
			break;
		}
		m_nextBtn->move(m_alarmMsgBigPicLbl->width() - m_nextBtn->width(), (m_alarmMsgBigPicLbl->height() - m_nextBtn->height()) / 2);
		connect(m_nextBtn, SIGNAL(clicked()), this, SLOT(slotNext()));

	} while (0);

	if (0 != ret)
	{
		release();
	}

	return ret;
}

void AlarmMsgBigPicView::release()
{
	if (NULL != m_nextBtn)
	{
		delete m_nextBtn;
		m_nextBtn = NULL;
	}

	if (NULL != m_lastBtn)
	{
		delete m_lastBtn;
		m_lastBtn = NULL;
	}

	if (NULL != m_alarmMsgBigPicLbl)
	{
		delete m_alarmMsgBigPicLbl;
		m_alarmMsgBigPicLbl = NULL;
	}

	if (NULL != m_closeBtn)
	{
		delete m_closeBtn;
		m_closeBtn = NULL;
	}

	if (NULL != m_maxOrRestoreBtn)
	{
		delete m_maxOrRestoreBtn;
		m_maxOrRestoreBtn = NULL;
	}

	if (NULL != m_titleLbl)
	{
		delete m_titleLbl;
		m_titleLbl = NULL;
	}

	if (NULL != m_titleBar)
	{
		delete m_titleBar;
		m_titleBar = NULL;
	}

	return;
}

void AlarmMsgBigPicView::setAlarmMsgBigPic(const QPixmap& alarmMsgBigPic)
{
	m_alarmMsgBigPicLbl->setPixmap(alarmMsgBigPic);
}

void AlarmMsgBigPicView::setLastBtnNoAbled(bool ability)
{
	m_lastBtn->setDisabled(ability);
}

void AlarmMsgBigPicView::setNextBtnNoAbled(bool ability)
{
	m_nextBtn->setDisabled(ability);
}

void AlarmMsgBigPicView::mousePressEvent(QMouseEvent* ev)
{
	m_oldPos = ev->pos();

	if (m_titleBar->rect().contains(ev->pos()))
	{
		if (Qt::LeftButton == ev->button())
		{
			m_isMousePressedInTitleBar = true;
		}
	}

	return;
}

void AlarmMsgBigPicView::mouseMoveEvent(QMouseEvent* ev)
{
	if (m_isMousePressedInTitleBar)
	{
		int dx = ev->x() - m_oldPos.x();
		int dy = ev->y() - m_oldPos.y();
		move(x() + dx, y() + dy);
	}

	return;
}

void AlarmMsgBigPicView::mouseReleaseEvent(QMouseEvent* ev)
{
	m_isMousePressedInTitleBar = false;
	return;
}

void AlarmMsgBigPicView::resizeEvent(QResizeEvent* ev)
{
	m_titleBar->resize(this->width(), 48);
	m_maxOrRestoreBtn->move(m_titleBar->width() - 70, 9);
	m_closeBtn->move(m_titleBar->width() - 38, 9);
	m_alarmMsgBigPicLbl->resize(this->width(), this->height() - 48);
	m_lastBtn->move(0, (m_alarmMsgBigPicLbl->height() - m_lastBtn->height()) / 2);
	m_nextBtn->move(m_alarmMsgBigPicLbl->width() - m_nextBtn->width(), (m_alarmMsgBigPicLbl->height() - m_nextBtn->height()) / 2);
	return;
}

void AlarmMsgBigPicView::slotMaxOrRestore()
{
	if (m_isMaximized)
	{
		this->showNormal();
		m_isMaximized = false;
		m_maxOrRestoreBtn->setIconPath("Skin/conmmon_icon_max");
	}
	else
	{
		this->showMaximized();
		m_isMaximized = true;
		m_maxOrRestoreBtn->setIconPath("Skin/conmmon_icon_huanyuan");
	}
	return;
}

void AlarmMsgBigPicView::slotClose()
{
	this->hide();
}

void AlarmMsgBigPicView::slotLast()
{
	emit sgnLast();
}

void AlarmMsgBigPicView::slotNext()
{
	emit sgnNext();
}

void AlarmMsgBigPicView::slotReply(const QPixmap& alarmMsgBigPic)
{
	m_alarmMsgBigPicLbl->setPixmap(alarmMsgBigPic);
}
