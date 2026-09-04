#ifndef RECORDTHUMBVIEW_H
#define RECORDTHUMBVIEW_H

#include <QWidget>
#include <QLabel>
#include <QProgressBar>
#include "Utils/CommonView/ScrollView.h"
#include "Model/RecordInfo.h"

class IconBtn;
class BaseWidget;
class RecordThumbView : public QWidget
{
    Q_OBJECT

public:
    RecordThumbView(QWidget *parent, QRect position, RECORD_CHILD* info);
    ~RecordThumbView();

    /**
/**
* Download thumbnail
    * @return  void
    */
    void setThumbPic(QPixmap pic);

private:
    bool            m_isInit;
    QRect           m_position;
    RECORD_CHILD    m_info;
    RECORD_TYPE_E   m_recordType;
    BaseWidget      *m_thumbPic;
    IconBtn         *m_playBtn;
    IconBtn         *m_downloadBtn;
    QWidget         *m_shade;
    IconBtn         *m_cancelBtn;
    QProgressBar    *m_progressBar;
    QLabel          *m_beginTimeText;
    QLabel          *m_endTimeText;
	int				m_deviceIndex;

    void init();
    void refreshLayout();
    void fillBackGroundWithColor(QWidget *widget, const QColor& color);
    void setPosition(const QRect &position);

signals:
    void sgnPlayBtnClicked(int index);
    void sgnDownloadBtnClicked(int index);
    void sgnCancelBtnClicked(int index);

public slots:
    void slotPlayBtnClicked();
    void slotDownloadBtnClicked();
    void slotCancelBtnClicked();
    void slotMouseEvent(void* widget, bool isEnter);
    void slotDownloadPercent(int index, int percent);
    void slotCancelDownload(int index);
    void slotSetDownloadUI(int index, bool flag);

};

#endif // RECORDTHUMBVIEW_H
