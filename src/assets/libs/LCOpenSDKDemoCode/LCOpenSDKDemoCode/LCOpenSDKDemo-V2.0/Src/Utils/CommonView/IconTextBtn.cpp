#include "IconTextBtn.h"

IconTextBtn::IconTextBtn(QWidget* parent)
	:QLabel(parent)
{
	m_IconLabel = NULL;
	m_TextLabel = NULL;
	init();
}

IconTextBtn::~IconTextBtn()
{
	release();
}

void IconTextBtn::setBtnAttribute(QString iconPath, QString text, unsigned int fontSize, QColor fontColor, QString fontStyle)
{
	if (NULL == m_IconLabel || NULL == m_TextLabel)
	{
		return;
	}

	m_IconPath = iconPath;

	QPixmap pixmap;
	pixmap.load(m_IconPath + "_n.png");
	m_IconLabel->resize(pixmap.size());
	m_IconLabel->move(0, 0);
	m_IconLabel->setPixmap(pixmap);

	m_TextLabel->setFixedHeight(pixmap.height());
	m_TextLabel->move(pixmap.width() + 6, 0);
	QString styleSheet = QString("color:#") + QString::number(fontColor.red(), 16) + QString::number(fontColor.green(), 16) + QString::number(fontColor.blue(), 16) + QString(";");
	styleSheet += QString("font:") + QString::number(fontSize, 10) + QString("pt;");
	styleSheet += (QString("font-family:") + fontStyle + QString(";"));
	m_TextLabel->setStyleSheet(styleSheet);
	m_TextLabel->setText(text);
	m_TextLabel->adjustSize();

	this->resize(m_IconLabel->width() + m_TextLabel->width() + 6, pixmap.height());

	return;
}

void IconTextBtn::enterEvent(QEvent* ev)
{
	if (NULL == m_IconLabel)
	{
		return;
	}
	QPixmap pixmap;
	pixmap.load(m_IconPath + "_p.png");
	m_IconLabel->setPixmap(pixmap);

	this->setCursor(QCursor(Qt::PointingHandCursor));

	return;
}

void IconTextBtn::leaveEvent(QEvent* ev)
{
	if (NULL == m_IconLabel)
	{
		return;
	}
	QPixmap pixmap;
	pixmap.load(m_IconPath + "_n.png");
	m_IconLabel->setPixmap(pixmap);

	this->setCursor(QCursor(Qt::ArrowCursor));

	return;
}

void IconTextBtn::mousePressEvent(QMouseEvent* ev)
{
	if (NULL == m_IconLabel)
	{
		return;
	}

	QPixmap pixmap;
	pixmap.load(m_IconPath + "_h.png");
	m_IconLabel->setPixmap(pixmap);

	return;
}

void IconTextBtn::mouseReleaseEvent(QMouseEvent* ev)
{
	if (!rect().contains(ev->pos()))
	{
		return;
	}

	if (Qt::LeftButton == ev->button())
	{
		QPixmap pixmap;
		pixmap.load(m_IconPath + "_p.png");
		m_IconLabel->setPixmap(pixmap);

		emit clicked();
	}

	return;
}

int IconTextBtn::init()
{
	int ret = 0;

	do
	{
		m_IconLabel = new (std::nothrow) QLabel(this);
		if (NULL == m_IconLabel)
		{
			ret = -1;
			break;
		}

		m_TextLabel = new (std::nothrow) QLabel(this);
		if (NULL == m_TextLabel)
		{
			ret = -1;
			break;
		}

	} while (0);

	if (0 != ret)
	{
		release();
	}

	return ret;
}

void IconTextBtn::release()
{
	if (NULL != m_IconLabel)
	{
		delete m_IconLabel;
		m_IconLabel = NULL;
	}

	if (NULL != m_TextLabel)
	{
		delete m_TextLabel;
		m_TextLabel = NULL;
	}

	return;
}
