#include "SearchBar.h"

SearchBar::SearchBar(QWidget *parent)
	: QWidget(parent)
{
	m_textEdit      = NULL;
	m_searchBtn     = NULL;
	m_layout        = NULL;
	searchBtnBGArea = NULL;
}

SearchBar::~SearchBar()
{
	if (m_textEdit)
	{
		delete m_textEdit;
		m_textEdit = NULL;
	}
	if (m_searchBtn)
	{
		delete m_searchBtn;
		m_searchBtn = NULL;
	}
	if (m_layout)
	{
		delete m_layout;
		m_layout = NULL;
	}
	if (searchBtnBGArea)
	{
		delete searchBtnBGArea;
		searchBtnBGArea = NULL;
	}
}

int SearchBar::init()
{
	this->resize(348, 34);
	this->setLayoutDirection(Qt::LeftToRight);

	QPixmap  backGroundPix;
	backGroundPix.load("Skin/alarm-message_search_bg_n.png");

	this->setAutoFillBackground(true);
	QPalette palette;
	palette.setBrush(QPalette::Window, QBrush(backGroundPix));
	this->setPalette(palette);

	m_textEdit  = new QLineEdit(this);
	m_textEdit->installEventFilter(this);

	m_textEdit->resize(238, 34);
	m_textEdit->move(30, 0);
	m_textEdit->setPlaceholderText(tr("--Please Choose--"));
	m_textEdit->setAlignment(Qt::AlignHCenter);
	m_textEdit->setStyleSheet(
		"border: 0px;"
		"background: transparent;"
		"selection-background-color: white;"
		"color:#a8a9a9;""Microsoft YaHei"";"
		"font-size: 14px;"
		);

	/**设置不支持键盘输入*/
	m_textEdit->setReadOnly(true);

	searchBtnBGArea = new QWidget(this);
	QPixmap  searchBtnbackGroundPix;
	searchBtnbackGroundPix.load("Skin/alarm-message_add_bg_n.png");

	searchBtnBGArea->setAutoFillBackground(true);
	QPalette searchBtnPalette;
	searchBtnPalette.setBrush(QPalette::Window, QBrush(searchBtnbackGroundPix));
	searchBtnBGArea->setPalette(searchBtnPalette);

	m_searchBtn   = new IconTextBtn(searchBtnBGArea);
	m_searchBtn->setBtnAttribute("Skin/video_icon_search", tr("Query"), 11, QColor(0xB0AFAF));
	connect(m_searchBtn, SIGNAL(clicked()), this, SLOT(slotSearch()));

	searchBtnBGArea->move(266, 3);
	searchBtnBGArea->setFixedWidth(78);

	return 0;
}

void SearchBar::setDate(QString dateTime)
{
    m_textEdit->setText(dateTime);
}

void SearchBar::slotSearch()
{
	QString dateTime = m_textEdit->text();
    emit sgnSearch(dateTime);
}

bool SearchBar::eventFilter( QObject *obj, QEvent *event )
{
	if (obj != this->m_textEdit )
	{
		return QObject::eventFilter( obj, event );
	}
    if (obj == this->m_textEdit)
    {
		if (event->type() == QEvent::MouseButtonRelease)
		{
            emit sgnFocusIn();
		}

		if (event->type() == QEvent::FocusOut)
		{
             emit sgnFocusOut();
		}
    }

	return QWidget::eventFilter(obj, event);
}

QString SearchBar::getDate()
{
    return m_textEdit->text();
}

