#ifndef RECORDLISTVIEW_H
#define RECORDLISTVIEW_H

#include <QWidget>
#include <QDate>
#include "Model/RecordInfo.h"
#include "LCOpenSDK_Download.h"
#include "LCOpenSDK_DownloadListener.h"

class RecordListCtrl;
class IconTextBtn;
class RecordListScrollView;
class QLabel;
class SearchBar;
class Calendar;
class SplitLine;
class RecordListView : public QWidget, public LCOpenSDK_DownloadListener
{
	Q_OBJECT

public:
	RecordListView(QWidget *parent);
	~RecordListView();

    int init();
    void refreshLayout();
    inline QRect getPosition(){ return m_position; };
    inline int getDeviceIndex(){ return m_deviceIndex; };

    /**
/**
* Show device record list
* @param   [in] int deviceIndex Device index from device list
    */
    void showDeviceRecordListView(int deviceIndex);

    /**
/**
* Show cloud record list
* @param   [in] int deviceIndex Device index from device list
    */
    void showCloudRecordListView(int deviceIndex);

    void hide();

    void onDownloadReceiveData(int index, int datalen);
    void onDownloadState(int index, const char* code, int type);
	void onDownloadProgress(int index, float progress, int type);
	void onThumbnailState(int index, int code);

protected:
    virtual void paintEvent(QPaintEvent *paintEvent);

private:
    QRect           m_position;
    RecordListCtrl *m_viewCtrl;
    bool            m_isInit;
    QString         m_deviceId;
    int             m_channelId;
    RECORD_TYPE_E   m_recordType;
    int             m_deviceIndex;

    SplitLine              *m_splitLine;
    SplitLine              *m_splitLine2;
    IconTextBtn            *m_btnBack;
    RecordListScrollView   *m_scrollView;
    QLabel                 *m_labelChannelName;
    SearchBar              *m_searchBar;
    Calendar               *m_calendar;
    QDate                   m_searchDate;

    QLabel                 *m_showInfo;

    LCOpenSDK_Download*     m_lcopensdkDownloadInstance;
    int                     m_downloadingIndex;     /* Downloading record index, Demo limits single download, -1 means no download in progress */
    QString                 m_cloudRecordsDir;
    QString                 m_deviceRecordsDir;
    QByteArray              m_downloadingFilePath;  /* Local file path of the record being downloaded */
    long long               m_fileLength;
    long long               m_downloadLength;

/* Privatize show method, can only show via showDeviceRecordListView && showCloudRecordListView */
    inline virtual void show(){ QWidget::show(); };

    void fillBackGroundWithColor(QWidget *widget, const QColor& color);
    void setPosition(const QRect &position);

signals:
    void sgnPlayCloudRecord(int deviceIndex, int recordIndex);
    void sgnPlayDeviceRecord(int deviceIndex,int recordIndex);
    void sgnReturnToDevicesList(bool refreshDevicesList);
    void sgnDownloadPercent(int index, int percent);
    void sgnCancelDownload(int index);
    void sgnSetDownloadUI(int index, bool flag);
    void sgnSetShowInfo(QString info);

private slots:
    /**
/**
* Download record callback (including download progress)
* @param   [in] int result Less than 0 means download failed, greater than 0 means download progress
    */
    void slotRecordThreadResult(int result);

    /**
/**
* Clear record list and refresh UI
    * @return  void
    */
    void slotPlayBtnClicked(int recordIndex);
    void slotDownloadBtnClicked(int index);
    void slotCancelBtnClicked(int index);

    void slotBackBtnClicked();
    void slotSearch(QString date);
    void slotShowOrHideCalendar();
    void slotSetText(QDate date);

    void slotSetShowInfo(QString info);
};

#endif // RECORDLISTVIEW_H
