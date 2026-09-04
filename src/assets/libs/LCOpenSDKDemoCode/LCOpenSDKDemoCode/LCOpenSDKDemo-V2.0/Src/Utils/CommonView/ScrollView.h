#ifndef SCROLLVIEW_H
#define SCROLLVIEW_H

#include "Src/Utils/CommonView/BaseScrollView.h"
#include "Src/Model/RecordInfo.h"
#include "Src/Utils/CurlDownload.h"

typedef struct childSize
{
	int width;
	int height;
	int column;
	int rowPitch;

	childSize()
	{
		memset(this, 0, sizeof(childSize));
	}
}CHILD_SIZE;

class RecordThumbView;
typedef struct recordChild
{
	QString             beginTime;
	QString             endTime;
	QString             thumbUrl;
	RecordThumbView*    view;
	RECORD_TYPE_E       recordType;
	int                 index;

	recordChild()
	{
		view = NULL;
		index = 0;
	}
}RECORD_CHILD;


typedef std::vector<RECORD_CHILD*> RECORD_CHILD_LIST;
class RecordListScrollView : public BaseScrollView
{
	Q_OBJECT

public:
	RecordListScrollView(QWidget *parent);
	~RecordListScrollView();

	/**
	* 重置(清理子单元信息和界面)
	* @return  void
	*/
	void reset();

	/**
	* 设置单个子单元的尺寸和间隔
	* @param   [in] int width       宽
	* @param   [in] int height      高
	* @param   [in] int colume      列数
	* @param   [in] int rowPitch    间隔大小(横向和纵向一致)
	* @return  void
	*/
	void setChildSize(int width, int height, int colume, int rowPitch);

	/**
	* 压入子单元信息
	* @param   [in] RECORD_CHILD * info
	* @return  void
	*/
	void addChild(RECORD_CHILD *info);

	/**
	* 使子单元信息生效显示
	* @param   [in] QString decryptKey  图片解密秘钥(目前为设备序列号)
	* @return  void
	*/
	void refresh(QString decryptKey, QString deviceId);

	void setPosition(const QRect &position);

private:
	CHILD_SIZE           m_childSize;
	RECORD_CHILD_LIST    m_recordChildList;
	bool                 m_isInit;
	QByteArray           m_decryptPicBufBa;
	unsigned char*       m_decryptPicBuf;
	QString              m_decryptKey;

	CurlDownload*        m_CurlDownload;

	/* 云录像封面图下载index */
	unsigned int                m_downloadIndex;

	bool                        m_isCurlDownLoadEnabled;

signals:
	void sgnPlayBtnClicked(int index);
	void sgnDownloadBtnClicked(int index);
	void sgnCancelBtnClicked(int index);
	void sgnDownloadPercent(int index, int percent);
	void sgnCancelDownload(int index);
	void sgnSetDownloadUI(int index, bool flag);

private slots:
	void slotCurlDownloadFinished(unsigned char* data, unsigned int dataLen, QString deviceId);
};

#endif // SCROLLVIEW_H
