#include <QScrollBar>
#include <QPainter>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include <QImage.h>
#include <math.h>

#include "Src/Utils/global.h"
#include "lcopensdk_utils/LCOpenSdk_Utils.h"
#include "Src/View/RecordList/RecordThumbView.h"
#include "ScrollView.h"
#include "Src/Ctrl/OpenApiCtrl.h"


#define DEC_IMG_MAX_SIZE (1024 * 1024 * 5)
#define PNG_IMG_MAX_SIZE (1024 * 1024 * 5)

RecordListScrollView::RecordListScrollView(QWidget *parent)
	: BaseScrollView(parent)
	, m_isCurlDownLoadEnabled(false)
{
	m_decryptPicBuf = (unsigned char*)malloc(DEC_IMG_MAX_SIZE);
	m_CurlDownload = new (std::nothrow) CurlDownload(this);
	connect(m_CurlDownload, SIGNAL(sgnFinished(unsigned char*, unsigned int, QString)), this, SLOT(slotCurlDownloadFinished(unsigned char*, unsigned int, QString)));
}

RecordListScrollView::~RecordListScrollView()
{
	reset();

	if (NULL != m_CurlDownload)
	{
		delete m_CurlDownload;
		m_CurlDownload = NULL;
	}

	if (NULL != m_decryptPicBuf)
	{
		free(m_decryptPicBuf);
		m_decryptPicBuf = NULL;
	}
}

void RecordListScrollView::setPosition(const QRect &position)
{
	this->setFixedSize(position.width(), position.height());
	this->move(position.left(), position.top());

	refreshLayout();
}

void RecordListScrollView::reset()
{
	m_isCurlDownLoadEnabled = false;
	RECORD_CHILD *info = NULL;
	while (!m_recordChildList.empty())
	{
		info = m_recordChildList.back();
		m_recordChildList.pop_back();
		if (NULL == info)
		{
			continue;
		}

		if (info->view)
		{
			info->view->hide();
			SAFE_DELETE(info->view);
		}
		SAFE_DELETE(info);
	}
}

void RecordListScrollView::setChildSize(int width, int height, int colume, int rowPitch)
{
	m_childSize.width = width;
	m_childSize.height = height;
	m_childSize.column = colume;
	m_childSize.rowPitch = rowPitch;
}

void RecordListScrollView::addChild(RECORD_CHILD *info)
{
	m_recordChildList.push_back(info);
}

void RecordListScrollView::refresh(QString decryptKey, QString deviceId)
{
	m_decryptKey = decryptKey;

	int widgetW = this->width() - 8;
	int rowNum = ceil((double)m_recordChildList.size() / (double)m_childSize.column);
	int widgetH = rowNum * m_childSize.height + (rowNum + 1) * m_childSize.rowPitch;
	widgetH = max(this->height(), widgetH);

	/*调整rootWidget尺寸以容纳所有childView*/
	m_rootWidget->setFixedSize(widgetW, widgetH);

	/*创建缩略图窗口*/
	RecordThumbView *thumbView = NULL;
	RECORD_CHILD    *info = NULL;
	QRect position(20, m_childSize.rowPitch, m_childSize.width, m_childSize.height);
	for (int i = 0; i < m_recordChildList.size(); )
	{
		info = m_recordChildList[i];
		if (NULL == info)
		{
			continue;
		}

		thumbView = new RecordThumbView(m_rootWidget, position, info);
		if (NULL == thumbView)
		{
			break;
		}
		connect(thumbView, SIGNAL(sgnPlayBtnClicked(int)), this, SIGNAL(sgnPlayBtnClicked(int)));
		connect(thumbView, SIGNAL(sgnDownloadBtnClicked(int)), this, SIGNAL(sgnDownloadBtnClicked(int)));
		connect(thumbView, SIGNAL(sgnCancelBtnClicked(int)), this, SIGNAL(sgnCancelBtnClicked(int)));
		connect(this, SIGNAL(sgnDownloadPercent(int, int)), thumbView, SLOT(slotDownloadPercent(int, int)));
		connect(this, SIGNAL(sgnCancelDownload(int)), thumbView, SLOT(slotCancelDownload(int)));
		connect(this, SIGNAL(sgnSetDownloadUI(int, bool)), thumbView, SLOT(slotSetDownloadUI(int, bool)));
		if (0 == (++i % m_childSize.column))
		{
			position.setLeft(20);
			position.setTop(position.top() + m_childSize.height + m_childSize.rowPitch);
		}
		else
		{
			position.setLeft(position.left() + m_childSize.width + m_childSize.rowPitch);
		}
		position.setWidth(m_childSize.width);
		position.setHeight(m_childSize.height);
	}
	if (m_recordChildList.size() > 0)
	{
		m_downloadIndex = 0;
		m_isCurlDownLoadEnabled = true;
		m_CurlDownload->get(m_recordChildList[m_downloadIndex]->thumbUrl, deviceId);
	}
}

void RecordListScrollView::slotCurlDownloadFinished(unsigned char* data, unsigned int dataLen, QString deviceId)
{
	///* 防止刷新云录像列表->清空云录像列表，引起的越界&空指针的错误 */
	if (!m_isCurlDownLoadEnabled)
	{
		return;
	}

	if (NULL != data && dataLen > 0)
	{
		int decryptPicBufLen = DEC_IMG_MAX_SIZE;
		/* 解密图片 */
		//int ret = LCOpenSdk_Utils::DecryptPicEx((const char*)data, dataLen, m_decryptKey.toLocal8Bit().data(), OpenApiCtrl::getInstance()->getToken().toLatin1().data(), deviceId.toLatin1().data(), (char*)m_decryptPicBuf, decryptPicBufLen);
		int ret = LCOpenSdk_Utils::DecryptPicEx((const char*)data, dataLen, "L23952D2", OpenApiCtrl::getInstance()->getToken().toLatin1().data(), deviceId.toLatin1().data(), (char *)m_decryptPicBuf, decryptPicBufLen);
		if (0 == ret)
		{
			int pngImgSize = PNG_IMG_MAX_SIZE;
			QPixmap pixmap;
			pixmap.loadFromData(m_decryptPicBuf, pngImgSize, "JPG");
			m_recordChildList[m_downloadIndex]->view->setThumbPic(pixmap);
		}
	}

	if (++m_downloadIndex < m_recordChildList.size())
	{
		m_CurlDownload->get(m_recordChildList[m_downloadIndex]->thumbUrl, deviceId);
	}

	return;
}
