#include "BaseScrollView.h"
#include <QScrollBar>

BaseScrollView::BaseScrollView(QWidget *parent)
	: QScrollArea(parent)
{
    m_rootWidget = NULL;
    m_isInit = false;
    init();
}

BaseScrollView::~BaseScrollView()
{
    release();
}

int BaseScrollView::init()
{
	/*去除边框*/
	this->setFrameShape(QFrame::NoFrame);

	/*自定义滚动条样式*/
	setScrollBarStyle();

	/*填充背景色*/
	fillBackGroundWithColor(this, QColor(0x20, 0x22, 0x24));

	int ret = 0;
	do 
	{
        m_rootWidget = new (std::nothrow) QWidget(this);
		if (NULL == m_rootWidget)
		{
			ret = -1;
			break;
		}
		this->setWidget(m_rootWidget);

		m_isInit = true;
	} while (0);

	refreshLayout();
	return ret;
}

void BaseScrollView::release()
{
    if (NULL != m_rootWidget)
    {
        delete m_rootWidget;
        m_rootWidget = NULL;
    }

    return;
}

void BaseScrollView::setScrollBarStyle()
{
	this->verticalScrollBar()->setStyleSheet("QScrollBar:vertical"
		"{"
		"width:8px;"
		"background:rgba(0,0,0,0%);"
		"margin:0px,0px,0px,0px;"
		"padding-top:0px;"
		"padding-bottom:0px;"
		"}"
		"QScrollBar::handle:vertical"
		"{"
		"width:8px;"
		"background:#444547;"
		" border-radius:4px;"
		"min-height:20;"
		"}"
		"QScrollBar::handle:vertical:hover"
		"{"
		"width:8px;"
		"background:#444547;"
		" border-radius:4px;"
		"min-height:20;"
		"}"
		"QScrollBar::add-line:vertical"
		"{"
		"height:9px;width:8px;"
		"border-image:url(:/images/a/3.png);"
		"subcontrol-position:bottom;"
		"}"
		"QScrollBar::sub-line:vertical"
		"{"
		"height:9px;width:8px;"
		"border-image:url(:/images/a/1.png);"
		"subcontrol-position:top;"
		"}"
		"QScrollBar::add-line:vertical:hover"
		"{"
		"height:9px;width:8px;"
		"border-image:url(:/images/a/4.png);"
		"subcontrol-position:bottom;"
		"}"
		"QScrollBar::sub-line:vertical:hover"
		"{"
		"height:9px;width:8px;"
		"border-image:url(:/images/a/2.png);"
		"subcontrol-position:top;"
		"}"
		"QScrollBar::add-page:vertical,QScrollBar::sub-page:vertical"
		"{"
		"background:rgba(0,0,0,10%);"
		"border-radius:4px;"
		"}"
		);
}

void BaseScrollView::refreshLayout()
{
	if (!m_isInit)
	{
		qDebug("please call init() first!!!\n");
		return;
	}

	m_rootWidget->move(0, 0);
	m_rootWidget->resize(this->width() - 8, qMax(this->height(), m_rootWidget->height()));
	fillBackGroundWithColor(m_rootWidget, QColor(32, 34, 36));
}

void BaseScrollView::fillBackGroundWithColor( QWidget *widget,const QColor& color )
{
	if (NULL == widget)
	{
		return;
	}

	widget->setAutoFillBackground(true);
	QPalette palette;
	palette.setColor(QPalette::Window, color);
	widget->setPalette(palette);
}

void BaseScrollView::resizeEvent(QResizeEvent* ev)
{
    m_rootWidget->resize(this->width() - 8, qMax(this->height(), m_rootWidget->height()));
}
