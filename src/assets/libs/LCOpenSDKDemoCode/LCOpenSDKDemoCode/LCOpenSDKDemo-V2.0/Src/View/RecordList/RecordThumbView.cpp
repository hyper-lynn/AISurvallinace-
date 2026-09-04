#include <QLabel>

#include "Src/Utils/global.h"
#include "Src/Utils/CommonView/IconBtn.h"
#include "Src/Utils/CommonView/BaseWidget.h"
#include "RecordThumbView.h"

extern bool g_isReleasedForOverseas;

RecordThumbView::RecordThumbView(QWidget *parent, QRect position, RECORD_CHILD* info)
	: QWidget(parent)
	, m_position(position)
	, m_isInit(false)
	, m_recordType(info->recordType)
	, m_thumbPic(NULL)
	, m_playBtn(NULL)
	, m_downloadBtn(NULL)
	, m_shade(NULL)
	, m_cancelBtn(NULL)
	, m_progressBar(NULL)
	, m_beginTimeText(NULL)
	, m_endTimeText(NULL)
{
	if (info)
	{
		/*this赋给info info释放时会同时释放当前对象*/
		info->view = this;

		m_info.beginTime = info->beginTime;
		m_info.endTime = info->endTime;
		m_info.thumbUrl = info->thumbUrl;
		m_info.view = info->view;
		m_info.index = info->index;
	}

	setPosition(m_position);
	fillBackGroundWithColor(this, QColor(0, 0, 0));
	init();
}

RecordThumbView::~RecordThumbView()
{
	SAFE_DELETE(m_endTimeText);
	SAFE_DELETE(m_beginTimeText);
	SAFE_DELETE(m_progressBar);
	SAFE_DELETE(m_cancelBtn);
	SAFE_DELETE(m_shade);
	SAFE_DELETE(m_downloadBtn);
	SAFE_DELETE(m_playBtn);
	SAFE_DELETE(m_thumbPic);
}

void RecordThumbView::setPosition(const QRect &position)
{
	m_position = position;

	this->setFixedSize(m_position.width(), m_position.height());
	this->move(m_position.left(), m_position.top());

	refreshLayout();
}

void RecordThumbView::init()
{
	do
	{
		m_thumbPic = new (std::nothrow) BaseWidget(this);
		if (NULL == m_thumbPic)
		{
			break;
		}
		m_thumbPic->setScaledContents(true);
		connect(m_thumbPic, SIGNAL(sgnMouseEvent(void*, bool)), this, SLOT(slotMouseEvent(void*, bool)));

		m_playBtn = new (std::nothrow) IconBtn(m_thumbPic, "Skin/common_icon_btn_play");
		if (NULL == m_playBtn)
		{
			break;
		}
		connect(m_playBtn, SIGNAL(clicked()), this, SLOT(slotPlayBtnClicked()));
		m_playBtn->hide();

		QString iconPathDownloadBtn = g_isReleasedForOverseas ? "Skin/cloud_record_download_en" : "Skin/cloud_record_download";
		m_downloadBtn = new (std::nothrow) IconBtn(m_thumbPic, iconPathDownloadBtn);
		if (NULL == m_downloadBtn)
		{
			break;
		}
		connect(m_downloadBtn, SIGNAL(clicked()), this, SLOT(slotDownloadBtnClicked()));
		m_downloadBtn->hide();

		m_shade = new (std::nothrow) QWidget(this);
		if (NULL == m_shade)
		{
			break;
		}
		m_shade->setStyleSheet("background-color:rgba(0, 0, 0, 30%);");
		m_shade->hide();

		QString iconPathCancelBtn = g_isReleasedForOverseas ? "Skin/cloud_record_cancel_en" : "Skin/cloud_record_cancel";
		m_cancelBtn = new (std::nothrow) IconBtn(m_shade, iconPathCancelBtn);
		if (NULL == m_cancelBtn)
		{
			break;
		}
		connect(m_cancelBtn, SIGNAL(clicked()), this, SLOT(slotCancelBtnClicked()));
		m_cancelBtn->hide();

		m_progressBar = new (std::nothrow) QProgressBar(m_shade);
		if (NULL == m_progressBar)
		{
			break;
		}
		m_progressBar->setRange(0, 100);
		m_progressBar->setTextVisible(false);
		m_progressBar->setStyleSheet("QProgressBar{background-color:#dedede;border-radius:3px;}"
			"QProgressBar::chunk{background-color:#fd8b30;border-radius:3px;}");
		m_progressBar->hide();

		m_beginTimeText = new (std::nothrow) QLabel(this);
		if (NULL == m_beginTimeText)
		{
			break;
		}
		m_beginTimeText->setText(tr("Record begin time:") + m_info.beginTime);

		m_endTimeText = new (std::nothrow) QLabel(this);
		if (NULL == m_endTimeText)
		{
			break;
		}
		m_endTimeText->setText(tr("Record end time:") + m_info.endTime);

		m_isInit = true;
	} while (0);

	refreshLayout();
}

void RecordThumbView::refreshLayout()
{
	if (!m_isInit)
	{
		return;
	}

	m_thumbPic->setFixedSize(this->width(), 132);
	m_thumbPic->move(0, 0);
	QPixmap pix;
	if (g_isReleasedForOverseas)
	{
		pix.load("Skin/small_morenfengmian_en.png");
	}
	else
	{
		pix.load("Skin/small_morenfengmian.png");
	}
	m_thumbPic->setPixmap(pix);
	m_thumbPic->show();

	m_playBtn->move((m_thumbPic->width() - m_playBtn->width()) / 2, (m_thumbPic->height() - m_playBtn->height()) / 2);

	m_downloadBtn->move(m_thumbPic->width() - m_downloadBtn->width() - 6, m_thumbPic->height() - m_downloadBtn->height() - 6);

	m_shade->resize(m_thumbPic->size());
	m_shade->move(0, 0);

	m_cancelBtn->move(m_thumbPic->width() - m_cancelBtn->width() - 6, m_thumbPic->height() - m_cancelBtn->height() - 6);

	m_progressBar->resize(210, 8);
	m_progressBar->move(10, 62);

	m_beginTimeText->move(0, m_thumbPic->height());
	m_beginTimeText->setFixedSize(this->width(), 28);
	fillBackGroundWithColor(m_beginTimeText, QColor(44, 45, 48));
	m_beginTimeText->setStyleSheet("color:#A4A4A5;font:12px; ""Microsoft YaHei""");
	m_beginTimeText->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	m_beginTimeText->show();

	m_endTimeText->move(0, m_thumbPic->height() + m_beginTimeText->height());
	m_endTimeText->setFixedSize(this->width(), 28);
	fillBackGroundWithColor(m_endTimeText, QColor(44, 45, 48));
	m_endTimeText->setStyleSheet("color:#A4A4A5;font:12px; ""Microsoft YaHei""");
	m_endTimeText->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	m_endTimeText->show();

	this->show();
}

void RecordThumbView::fillBackGroundWithColor(QWidget *widget, QColor& color)
{
	if (NULL == widget)
	{
		return;
	}

	widget->setAutoFillBackground(true);
	QPalette palette;
	palette.setColor(QPalette::Background, color);
	widget->setPalette(palette);
}

void RecordThumbView::setThumbPic(QPixmap pic)
{
	if (!m_isInit)
	{
		return;
	}

	m_thumbPic->setPixmap(pic);
}

void RecordThumbView::slotPlayBtnClicked()
{
	emit sgnPlayBtnClicked(m_info.index);
}

void RecordThumbView::slotDownloadBtnClicked()
{
	emit sgnDownloadBtnClicked(m_info.index);
}

void RecordThumbView::slotCancelBtnClicked()
{
	emit sgnCancelBtnClicked(m_info.index);
}

void RecordThumbView::slotMouseEvent(void *widget, bool isEnter)
{
	if (m_thumbPic == widget)
	{
		if (isEnter)
		{
			m_playBtn->show();
			m_downloadBtn->show();
		}
		else
		{
			m_playBtn->hide();
			m_downloadBtn->hide();
		}
	}
}

void RecordThumbView::slotDownloadPercent(int index, int percent)
{
	if (index == m_info.index)
	{
		m_progressBar->setValue(percent);
	}
}

void RecordThumbView::slotCancelDownload(int index)
{
	if (index == m_info.index)
	{
		slotCancelBtnClicked();
	}
}

void RecordThumbView::slotSetDownloadUI(int index, bool flag)
{
	if (index == m_info.index)
	{
		if (flag)
		{
			m_playBtn->hide();
			m_downloadBtn->hide();
			m_shade->show();
			m_cancelBtn->show();

			/* easy4ip云录像下载不显示进度 */
			if (!g_isReleasedForOverseas)
			{
				m_progressBar->show();
				m_progressBar->setValue(0);
			}
		}
		else
		{
			m_shade->hide();
			m_cancelBtn->hide();
			m_progressBar->hide();
		}
	}
}
