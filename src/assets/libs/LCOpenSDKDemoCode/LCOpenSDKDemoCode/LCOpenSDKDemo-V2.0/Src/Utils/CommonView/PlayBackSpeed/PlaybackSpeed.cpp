#include "PlayBackSpeed.h"
#include "ui_PlayBackSpeed.h"
#include <QPainter>
#include <QtCore/qmath.h>  
#include <qdrawutil.h>
#include <QFile>

#define SPEED_DLG_WIDHT 60
#define SPEED_DLG_HEIGHT 150

PlayBackSpeed::PlayBackSpeed(QWidget *parent)
	: QWidget(parent)
	, m_pPicBackgroundNormal(NULL)
	, m_iChecked(0)
	, m_iMaxSpeedUp(5)
{
	ui = new Ui::PlayBackSpeed();
	ui->setupUi(this);
	setFixedSize(QSize(SPEED_DLG_WIDHT, SPEED_DLG_HEIGHT));
	setWindowFlags(Qt::Popup | Qt::FramelessWindowHint);
}

PlayBackSpeed::~PlayBackSpeed()
{
	delete ui;
}

int PlayBackSpeed::GetCheckedSpeed()
{
	if (m_vecBtnPtr[m_iChecked] == ui->btn01X)
	{
		return 1;
	}
	else if (m_vecBtnPtr[m_iChecked] == ui->btn04X)
	{
		return 4;
	}
	else if (m_vecBtnPtr[m_iChecked] == ui->btn08X)
	{
		return 8;
	}
	else if (m_vecBtnPtr[m_iChecked] == ui->btn16X)
	{
		return 16;
	}
	else if (m_vecBtnPtr[m_iChecked] == ui->btn32X)
	{
		return 32;
	}
	else // impossible
	{
		return 1;
	}
}

void PlayBackSpeed::SetCheckedSpeed(int iSpeed)
{
	int checkId = GetCheckedId(iSpeed);
	if (checkId < 0)
	{
		return;
	}

	SetChecked(checkId);
}

void PlayBackSpeed::SetChecked(int iChecked)
{
	if (iChecked >= 0 && iChecked < m_vecBtnPtr.size())
	{
		m_iChecked = iChecked;
		for (int i = 0; i < m_vecBtnPtr.size(); i++)
		{
			m_vecBtnPtr[i]->setChecked(i == m_iChecked);
		}
		update();
	}
}

bool PlayBackSpeed::eventFilter(QObject *watched, QEvent *event)
{
	for (int i = 0; i < m_vecBtnPtr.size(); i++)
	{
		if (watched == m_vecBtnPtr.at(i) && QEvent::MouseButtonRelease == event->type())
		{
			SetChecked(i);
			emit SignalPlaybackSpeedChanged();
			hide();
			return true;
		}
	}
	return false;
}

void PlayBackSpeed::resizeEvent(QResizeEvent *event)
{
}

void PlayBackSpeed::paintEvent(QPaintEvent *event)
{
	QWidget::paintEvent(event);

	//	QPainter painter(this);

		//绘制菜单背景（灰色）
		// 绘制中心区域的背景色（不然会是透明的）
	// 	if (ui->btn_02X->isVisible() || ui->btn01X->isVisible())
	// 	{
	// 		qDrawBorderPixmap(&painter, this->rect(), QMargins(10, 10, 10, 10), *m_pPicBackgroundNormal);
	// 	}
	// 	if (ui->btn_04X->isVisible() || ui->btn_02X->isVisible() ||
	// 		ui->btn_08X->isVisible() || ui->btn_16X->isVisible() || ui->btn_32X->isVisible())
	// 	{
	// 		QPen pen;                                 //创建一个画笔  
	// 		pen.setColor(Qt::black);
	// 		pen.setWidth(2);
	// 		painter.setPen(pen);
	// 
	// 		painter.drawLine((this->width() / 2), this->height()*0.28, (this->width() / 2), this->height()*0.7);
	// 
	// 
	// 	}

}

void PlayBackSpeed::InitUI(int iforward)
{
	switch (32 > iforward ? iforward : 32)
	{
	case 1:
		m_vecBtnPtr.push_back(ui->btn01X);
		ui->btn04X->hide();
		ui->btn08X->hide();
		ui->btn16X->hide();
		ui->btn32X->hide();
		break;
	case 4:
		m_vecBtnPtr.push_back(ui->btn01X);
		m_vecBtnPtr.push_back(ui->btn04X);
		ui->btn08X->hide();
		ui->btn16X->hide();
		ui->btn32X->hide();
		break;
	case 8:
		m_vecBtnPtr.push_back(ui->btn01X);
		m_vecBtnPtr.push_back(ui->btn04X);
		m_vecBtnPtr.push_back(ui->btn08X);
		ui->btn16X->hide();
		ui->btn32X->hide();
		break;
	case 16:
		m_vecBtnPtr.push_back(ui->btn01X);
		m_vecBtnPtr.push_back(ui->btn04X);
		m_vecBtnPtr.push_back(ui->btn08X);
		m_vecBtnPtr.push_back(ui->btn16X);
		ui->btn32X->hide();
		break;
	case 32:
		m_vecBtnPtr.push_back(ui->btn01X);
		m_vecBtnPtr.push_back(ui->btn04X);
		m_vecBtnPtr.push_back(ui->btn08X);
		m_vecBtnPtr.push_back(ui->btn16X);
		m_vecBtnPtr.push_back(ui->btn32X);
		break;
	default:
		m_vecBtnPtr.push_back(ui->btn01X);
		m_vecBtnPtr.push_back(ui->btn04X);
		m_vecBtnPtr.push_back(ui->btn08X);
		m_vecBtnPtr.push_back(ui->btn16X);
		m_vecBtnPtr.push_back(ui->btn32X);
	}

	for (int i = 0; i < m_vecBtnPtr.size(); i++)
	{
		m_vecBtnPtr[i]->setCheckable(true);
		m_vecBtnPtr[i]->installEventFilter(this);
	}
	update();
}

int PlayBackSpeed::GetCheckedId(int iSpeed)
{
	QPushButton* pTempPush = NULL;
	int iCheckid = -1;
	switch (iSpeed)
	{
	case 1:
		pTempPush = ui->btn01X;
		break;
	case 4:
		pTempPush = ui->btn04X;
		break;
	case 8:
		pTempPush = ui->btn08X;
		break;
	case 16:
		pTempPush = ui->btn16X;
		break;
	case 32:
		pTempPush = ui->btn32X;
		break;
	}
	for (int i = 0; i < m_vecBtnPtr.size(); i++)
	{
		if (m_vecBtnPtr[i] == pTempPush)
		{
			iCheckid = i;
			break;
		}
	}
	return iCheckid;
}

void PlayBackSpeed::ShowAllBtn()
{
	ui->btn01X->show();
	ui->btn04X->show();
	ui->btn08X->show();
	ui->btn16X->show(); //当前需求只放开快进倍速，后面需要可以直接放开倒退功能
	ui->btn32X->show();
	m_vecBtnPtr.clear();
	setFixedSize(QSize(SPEED_DLG_WIDHT, SPEED_DLG_HEIGHT));
	m_iMaxSpeedUp = 5;
}
