#include "PageTitle.h"

#define TITLE_BACKGROUND_COLOR 0x2C2D30
#define TITLE_MIN_HEIGHT       10 

PageTitle::PageTitle(QWidget *parent)
	: QWidget(parent)
{
	m_minimizeBtn  = NULL;
	m_maxmizeBtn   = NULL;
	m_closeBtn     = NULL;
	m_titleTextLbl = NULL;
	m_layout       = NULL;
	m_isMaxSize    = false;
}

PageTitle::~PageTitle()
{
	if (m_titleTextLbl)
	{
		delete m_titleTextLbl;
		m_titleTextLbl = NULL;
	}
	if(m_minimizeBtn)
	{
		delete m_minimizeBtn;
		m_minimizeBtn = NULL;
	}
	if (m_closeBtn)
	{
		delete m_closeBtn;
		m_closeBtn = NULL;
	}
	if (m_maxmizeBtn)
	{
		delete m_maxmizeBtn;
		m_maxmizeBtn = NULL;
	}
	if (m_layout)
	{
		delete m_layout;
		m_layout = NULL;
	}
}

int PageTitle::init()
{
	/**不继承父窗口的背景色*/
	setAutoFillBackground(true);

	/**设置默认背景色*/
	QPalette pal = palette(); 
	pal.setColor(QPalette::Window, QColor(TITLE_BACKGROUND_COLOR));
	setPalette(pal);

	m_minimizeBtn = new IconBtn(this, "Skin/conmmon_icon_mini");
	if(NULL == m_minimizeBtn)
	{
		return -1;
	}

	m_maxmizeBtn  = new IconBtn(this, "Skin/conmmon_icon_max");
	if(NULL == m_maxmizeBtn)
	{
		return -1;
	}

	m_closeBtn    = new IconBtn(this, "Skin/conmmon_icon_close");
	if(NULL == m_closeBtn)
	{
		return -1;
	}

	connect(m_minimizeBtn, SIGNAL(clicked()), this, SLOT(slotShowMinimize()));
	connect(m_maxmizeBtn, SIGNAL(clicked()), this, SLOT(slotShowMaxRestore()));
	connect(m_closeBtn, SIGNAL(clicked()), this, SLOT(slotCloseWin()));

	/**设置标题字体的默认样式*/
	m_titleTextLbl = new (std::nothrow)QLabel(this);
	if(NULL == m_titleTextLbl)
	{
		return -1;
	}
	QFont txtFont("Microsoft YaHei",12);
	m_titleTextLbl->setFont(txtFont);
	m_titleTextLbl->setStyleSheet("color:#aaaaaa;");

	m_layout = new QHBoxLayout(this);
	if(NULL == m_layout)
	{
		return -1;
	}
	m_layout->addWidget(m_titleTextLbl);
	m_layout->addWidget(m_minimizeBtn);
	m_layout->addWidget(m_maxmizeBtn);
	m_layout->addWidget(m_closeBtn);

	m_layout->insertStretch(1, 500);
	m_layout->setSpacing(0);
	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	this->setMinimumHeight(TITLE_MIN_HEIGHT);

	return 0;

}

void PageTitle::setTitleText( QString titleName )
{
	m_titleTextLbl->setText(titleName);
}

void PageTitle::setMaxmizeBtnVisible(bool visible)
{
	if (visible)
	{
		m_maxmizeBtn->show();
	}
	else
	{
		m_maxmizeBtn->hide();
	}
}

void PageTitle::slotShowMinimize()
{
	this->parentWidget()->showMinimized();
}

void PageTitle::slotShowMaxRestore()
{
	if (m_isMaxSize) 
	{
	    m_maxmizeBtn->setIconPath("Skin/conmmon_icon_max");
		this->parentWidget()->showNormal();
		m_isMaxSize = false;
	} 
	else 
	{
		m_maxmizeBtn->setIconPath("Skin/conmmon_icon_huanyuan");
		this->parentWidget()->showMaximized();
		m_isMaxSize = true;
	}
}

/**若鼠标移动和点击事件在PageTitle内处理，则开启函数*/
//void PageTitle::mousePressEvent( QMouseEvent *e )
//{
//	m_startPos = e->globalPos();
//	m_clickPos = mapToParent(e->pos());
//}
//
//void PageTitle::mouseMoveEvent( QMouseEvent *e )
//{
//	if (m_maxNormal)
//	{
//		return;
//	}
//
//	this->parentWidget()->move(e->globalPos() - m_clickPos);
//}

void PageTitle::slotCloseWin()
{
    emit this->sgnCloseWin();
}


