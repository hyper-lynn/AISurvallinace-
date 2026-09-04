#ifndef _ALARMMSGVIEW_H_
#define _ALARMMSGVIEW_H_

#include <QWidget>
#include <QLabel>
#include "Src/Utils/CommonView/IconBtn.h"

class AlarmMsgView: public QWidget
{
    Q_OBJECT

public:
    AlarmMsgView(QWidget* parent);
    ~AlarmMsgView();

    int init();
    void release();

    void setAlarmMsgIndex(int alarmMsgIndex);
    void setAlarmMsgSmallPic(const QPixmap& alarmMsgSmallPic);
    void setAlarmTime(const QString& alarmTime);
    void setAlarmMsgBigPic(const QPixmap& alarmMsgBigPic);
    const QPixmap& getAlarmMsgBigPic();

protected:
    virtual bool eventFilter(QObject* watched, QEvent* ev);

signals:
    void sgnRemoveAlarmMsg(int alarmMsgIndex);
    void sgnAlarmSmallPicLblDblClicked(int alarmMsgIndex);

private slots:
    void slotRemoveAlarmMsg();

private:
    int                 m_alarmMsgIndex;
    QLabel*             m_alarmSmallPicLbl;
    QWidget*            m_labelArea;
    QLabel*             m_alarmTimeNameLbl;
    QLabel*             m_alarmTimeLbl;
    IconBtn*            m_removeAlarmMsgBtn;
    QPixmap             m_alarmMsgBigPic;
};

#endif /* _ALARMMSGVIEW_H_ */
