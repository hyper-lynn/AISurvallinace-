#include <QLabel>
#include <QPainter>

#include "Src/Utils/global.h"
#include "Src/Utils/CommonView/IconBtn.h"
#include "Src/Model/PtzControlInfo.h"
#include "PtzControlView.h"

PtzControlView::PtzControlView(QWidget *parent)
	: QWidget(parent)
	, m_labelTitle(NULL)
	, m_btnArrow(NULL)
	, m_showWhole(false)
	, m_labelShadow(NULL)
	, m_labelCircle(NULL)
	, m_btnUp(NULL)
	, m_btnLeft(NULL)
	, m_btnDown(NULL)
	, m_btnRight(NULL)
	, m_btnLeftUp(NULL)
	, m_btnLeftDown(NULL)
	, m_btnRightUp(NULL)
	, m_btnRightDown(NULL)
{
}

PtzControlView::~PtzControlView()
{
	SAFE_DELETE(m_labelTitle);
	SAFE_DELETE(m_btnArrow);

	SAFE_DELETE(m_btnUp);
	SAFE_DELETE(m_btnLeft);
	SAFE_DELETE(m_btnDown);
	SAFE_DELETE(m_btnRight);
	SAFE_DELETE(m_btnLeftUp);
	SAFE_DELETE(m_btnLeftDown);
	SAFE_DELETE(m_btnRightUp);
	SAFE_DELETE(m_btnRightDown);

	SAFE_DELETE(m_labelCircle);
	SAFE_DELETE(m_labelShadow);
}

int PtzControlView::init()
{
	int ret = 0;
	do
	{
		m_labelTitle = new QLabel(this);
		if (NULL == m_labelTitle)
		{
			ret = -1;
			break;
		}

		m_btnArrow = new IconBtn(this, "Skin/real-time video/PTZ/yuntai_icon_unfold_up");
		if (NULL == m_btnArrow)
		{
			ret = -1;
			break;
		}
		connect(m_btnArrow, SIGNAL(clicked()), this, SLOT(slotArrowClicked()));

		m_labelShadow = new QLabel(this);
		if (NULL == m_labelShadow)
		{
			ret = -1;
			break;
		}

		m_labelCircle = new QLabel(m_labelShadow);
		if (NULL == m_labelCircle)
		{
			ret = -1;
			break;
		}

		m_btnUp = new IconBtn(m_labelShadow, "Skin/real-time video/PTZ/up", ICON_STATUS_DEFAULT | ICON_TYPE_MASK | ICON_TYPE_LONGPRESS);
		m_btnLeft = new IconBtn(m_labelShadow, "Skin/real-time video/PTZ/left", ICON_STATUS_DEFAULT | ICON_TYPE_MASK | ICON_TYPE_LONGPRESS);
		m_btnDown = new IconBtn(m_labelShadow, "Skin/real-time video/PTZ/down", ICON_STATUS_DEFAULT | ICON_TYPE_MASK | ICON_TYPE_LONGPRESS);
		m_btnRight = new IconBtn(m_labelShadow, "Skin/real-time video/PTZ/right", ICON_STATUS_DEFAULT | ICON_TYPE_MASK | ICON_TYPE_LONGPRESS);
		m_btnLeftUp = new IconBtn(m_labelShadow, "Skin/real-time video/PTZ/upl", ICON_STATUS_DEFAULT | ICON_TYPE_MASK | ICON_TYPE_LONGPRESS);
		m_btnLeftDown = new IconBtn(m_labelShadow, "Skin/real-time video/PTZ/downl", ICON_STATUS_DEFAULT | ICON_TYPE_MASK | ICON_TYPE_LONGPRESS);
		m_btnRightUp = new IconBtn(m_labelShadow, "Skin/real-time video/PTZ/upr", ICON_STATUS_DEFAULT | ICON_TYPE_MASK | ICON_TYPE_LONGPRESS);
		m_btnRightDown = new IconBtn(m_labelShadow, "Skin/real-time video/PTZ/downr", ICON_STATUS_DEFAULT | ICON_TYPE_MASK | ICON_TYPE_LONGPRESS);

		connect(m_btnUp, SIGNAL(clicked()), this, SLOT(slotPtzUpClicked()));
		connect(m_btnLeft, SIGNAL(clicked()), this, SLOT(slotPtzLeftClicked()));
		connect(m_btnDown, SIGNAL(clicked()), this, SLOT(slotPtzDownClicked()));
		connect(m_btnRight, SIGNAL(clicked()), this, SLOT(slotPtzRightClicked()));
		connect(m_btnLeftUp, SIGNAL(clicked()), this, SLOT(slotPtzLeftUpClicked()));
		connect(m_btnLeftDown, SIGNAL(clicked()), this, SLOT(slotPtzLeftDownClicked()));
		connect(m_btnRightUp, SIGNAL(clicked()), this, SLOT(slotPtzRightUpClicked()));
		connect(m_btnRightDown, SIGNAL(clicked()), this, SLOT(slotPtzRightDownClicked()));

		connect(m_btnUp, SIGNAL(longPressTrigger(bool)), this, SLOT(slotPtzUpLongPress(bool)));
		connect(m_btnLeft, SIGNAL(longPressTrigger(bool)), this, SLOT(slotPtzLeftLongPress(bool)));
		connect(m_btnDown, SIGNAL(longPressTrigger(bool)), this, SLOT(slotPtzDownLongPress(bool)));
		connect(m_btnRight, SIGNAL(longPressTrigger(bool)), this, SLOT(slotPtzRightLongPress(bool)));
		connect(m_btnLeftUp, SIGNAL(longPressTrigger(bool)), this, SLOT(slotPtzLeftUpLongPress(bool)));
		connect(m_btnLeftDown, SIGNAL(longPressTrigger(bool)), this, SLOT(slotPtzLeftDownLongPress(bool)));
		connect(m_btnRightUp, SIGNAL(longPressTrigger(bool)), this, SLOT(slotPtzRightUpLongPress(bool)));
		connect(m_btnRightDown, SIGNAL(longPressTrigger(bool)), this, SLOT(slotPtzRightDownLongPress(bool)));

		ret = 0;
	} while (0);

	refreshLayout();
	return ret;
}

void PtzControlView::paintEvent(QPaintEvent *ev)
{
	QPainter painter(this);

	int y = 0;
	painter.fillRect(0, y, this->width(), this->height(), QColor(0x2d, 0x2e, 0x31));
	y += 32;

	if (m_showWhole)
	{
		painter.fillRect(0, y, this->width(), this->height() - y, QColor(0x26, 0x27, 0x2a));
	}
}

void PtzControlView::refreshLayout()
{
	this->setFixedSize(246, 209);

	QFont font("Microsoft YaHei", 11);
	m_labelTitle->setFont(font);
	m_labelTitle->setStyleSheet("color:#b0afaf;");
	m_labelTitle->setText(tr("PTZ"));
	m_labelTitle->adjustSize();
	m_labelTitle->move(12, (32 - m_labelTitle->height()) / 2);

	m_btnArrow->setIconPath("Skin/real-time video/PTZ/yuntai_icon_unfold_" + (m_showWhole ? QString("down") : QString("up")));
	m_btnArrow->setPosition(QPoint(this->width() - 6 - m_btnArrow->width(), (32 - m_btnArrow->height()) / 2));

	QPixmap pixmap;
	pixmap.load("Skin/real-time video/PTZ/shadow.png");
	m_labelShadow->setPixmap(pixmap);
	m_labelShadow->adjustSize();
	m_labelShadow->move((this->width() - m_labelShadow->width()) / 2, 32 + (this->height() - 32 - m_labelShadow->height()) / 2);

	pixmap.load("Skin/real-time video/PTZ/circle.png");
	m_labelCircle->setPixmap(pixmap);
	m_labelCircle->adjustSize();
	int i = (m_labelShadow->width() - m_labelCircle->width()) / 2;
	m_labelCircle->move(35, 40);

	m_btnUp->move((m_labelShadow->width() - m_btnUp->width()) / 2 + 3, 18);
	m_btnLeft->move(16, (m_labelShadow->height() - m_btnLeft->height()) / 2 + 4);
	m_btnDown->move((m_labelShadow->width() - m_btnDown->width()) / 2 + 3, m_btnUp->y() + m_btnUp->height() + 60);
	m_btnRight->move(m_btnLeft->x() + m_btnLeft->width() + 60, (m_labelShadow->height() - m_btnRight->height()) / 2 + 6);

	m_btnLeftUp->move(m_btnLeft->x() + 6, m_btnUp->y() + 6);
	m_btnLeftDown->move(m_btnLeft->x() + 6, m_btnDown->y() - 18);
	m_btnRightUp->move(m_btnRight->x() - 18, m_btnUp->y() + 6);
	m_btnRightDown->move(m_btnRight->x() - 16, m_btnDown->y() - 17);
}


void PtzControlView::slotArrowClicked()
{
	m_showWhole = !m_showWhole;
	m_btnArrow->setIconPath("Skin/real-time video/PTZ/yuntai_icon_unfold_" + (m_showWhole ? QString("down") : QString("up")));
	emit sgnShowWhole(m_showWhole);
}

void PtzControlView::slotPtzUpClicked()
{
	emit sgnPtzControl(PTZ_CONTROL_UP, TYPE_SINGLE_STEP);
}

void PtzControlView::slotPtzLeftClicked()
{
	emit sgnPtzControl(PTZ_CONTROL_LEFT, TYPE_SINGLE_STEP);
}

void PtzControlView::slotPtzDownClicked()
{
	emit sgnPtzControl(PTZ_CONTROL_DOWN, TYPE_SINGLE_STEP);
}

void PtzControlView::slotPtzRightClicked()
{
	emit sgnPtzControl(PTZ_CONTROL_RIGHT, TYPE_SINGLE_STEP);
}

void PtzControlView::slotPtzLeftUpClicked()
{
	emit sgnPtzControl(PTZ_CONTROL_LEFTUP, TYPE_SINGLE_STEP);
}

void PtzControlView::slotPtzLeftDownClicked()
{
	emit sgnPtzControl(PTZ_CONTROL_LEFTDOWN, TYPE_SINGLE_STEP);
}

void PtzControlView::slotPtzRightUpClicked()
{
	emit sgnPtzControl(PTZ_CONTROL_RIGHTUP, TYPE_SINGLE_STEP);
}

void PtzControlView::slotPtzRightDownClicked()
{
	emit sgnPtzControl(PTZ_CONTROL_RIGHTDOWN, TYPE_SINGLE_STEP);
}

/* 长按处理 */
void PtzControlView::slotPtzUpLongPress(bool isPress)
{
	DLOG("slotPtzUpLongPress-%s\n", isPress ? "press" : "release");
	emit sgnPtzControl(PTZ_CONTROL_UP, isPress ? TYPE_LONGPRESS_PRESS : TYPE_LONGPRESS_RELEASE);
}

void PtzControlView::slotPtzLeftLongPress(bool isPress)
{
	DLOG("slotPtzLeftLongPress-%s\n", isPress ? "press" : "release");
	emit sgnPtzControl(PTZ_CONTROL_LEFT, isPress ? TYPE_LONGPRESS_PRESS : TYPE_LONGPRESS_RELEASE);
}

void PtzControlView::slotPtzDownLongPress(bool isPress)
{
	DLOG("slotPtzDownLongPress-%s\n", isPress ? "press" : "release");
	emit sgnPtzControl(PTZ_CONTROL_DOWN, isPress ? TYPE_LONGPRESS_PRESS : TYPE_LONGPRESS_RELEASE);
}

void PtzControlView::slotPtzRightLongPress(bool isPress)
{
	DLOG("slotPtzRightLongPress-%s\n", isPress ? "press" : "release");
	emit sgnPtzControl(PTZ_CONTROL_RIGHT, isPress ? TYPE_LONGPRESS_PRESS : TYPE_LONGPRESS_RELEASE);
}

void PtzControlView::slotPtzLeftUpLongPress(bool isPress)
{
	DLOG("slotPtzLeftUpLongPress-%s\n", isPress ? "press" : "release");
	emit sgnPtzControl(PTZ_CONTROL_LEFTUP, isPress ? TYPE_LONGPRESS_PRESS : TYPE_LONGPRESS_RELEASE);
}

void PtzControlView::slotPtzLeftDownLongPress(bool isPress)
{
	DLOG("slotPtzLeftDownLongPress-%s\n", isPress ? "press" : "release");
	emit sgnPtzControl(PTZ_CONTROL_LEFTDOWN, isPress ? TYPE_LONGPRESS_PRESS : TYPE_LONGPRESS_RELEASE);
}

void PtzControlView::slotPtzRightUpLongPress(bool isPress)
{
	DLOG("slotPtzRightUpLongPress-%s\n", isPress ? "press" : "release");
	emit sgnPtzControl(PTZ_CONTROL_RIGHTUP, isPress ? TYPE_LONGPRESS_PRESS : TYPE_LONGPRESS_RELEASE);
}

void PtzControlView::slotPtzRightDownLongPress(bool isPress)
{
	DLOG("slotPtzRightDownLongPress-%s\n", isPress ? "press" : "release");
	emit sgnPtzControl(PTZ_CONTROL_RIGHTDOWN, isPress ? TYPE_LONGPRESS_PRESS : TYPE_LONGPRESS_RELEASE);
}

