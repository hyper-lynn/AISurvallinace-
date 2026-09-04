#ifndef _ALARMMSGBIGPICVIEW_H_
#define _ALARMMSGBIGPICVIEW_H_

#include <QWidget>
#include <QDialog>
#include <QLabel>
#include <QMouseEvent>
#include "Src/Utils/CommonView/IconBtn.h"

class AlarmMsgBigPicView : public QDialog
{
	Q_OBJECT

public:
	AlarmMsgBigPicView(QWidget* parent);
	~AlarmMsgBigPicView();

	int init();
	void release();

	void setAlarmMsgBigPic(const QPixmap& alarmMsgBigPic);

	void setLastBtnNoAbled(bool ability);
	void setNextBtnNoAbled(bool ability);

protected:
	/* 为支持窗口可拖动 */
	void mousePressEvent(QMouseEvent* ev);
	void mouseMoveEvent(QMouseEvent* ev);
	void mouseReleaseEvent(QMouseEvent* ev);
	void resizeEvent(QResizeEvent* ev);

signals:
	void sgnLast();
	void sgnNext();

private slots:
	void slotMaxOrRestore();
	void slotClose();
	void slotLast();
	void slotNext();
	void slotReply(const QPixmap& alarmMsgBigPic);  /* 点击last和next按钮的响应 */

private:
	QWidget*            m_titleBar;
	QLabel*             m_titleLbl;
	IconBtn*            m_maxOrRestoreBtn;
	IconBtn*            m_closeBtn;
	QLabel*             m_alarmMsgBigPicLbl;
	IconBtn*            m_lastBtn;
	IconBtn*            m_nextBtn;
	QPoint              m_oldPos;                   /* 鼠标按下去时的位置 */
	bool                m_isMousePressedInTitleBar; /* 鼠标是否在标题栏中被按下 */
	bool                m_isMaximized;
};

#endif /* _ALARMMSGBIGPICVIEW_H_ */
