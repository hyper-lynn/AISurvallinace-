#ifndef PAGETITLE_H
#define PAGETITLE_H

#include <QWidget>
#include <QMainWindow>
#include <QPushButton>
#include <QToolButton>
#include <QLayout>
#include <QStyle>
#include <QLabel>
#include <QMouseEvent>
#include "../IconBtn.h"

class PageTitle : public QWidget
{
	Q_OBJECT

public:
	PageTitle(QWidget *parent);
	~PageTitle();

public:
	int init();
	void setTitleText(QString titleName);
	void setMaxmizeBtnVisible(bool visible);

signals:
	void sgnCloseWin();
	void sgnMinimize();

private slots:
	void slotShowMinimize();
	void slotShowMaxRestore();
	void slotCloseWin();

protected:
	//void mousePressEvent(QMouseEvent *e);
	//void mouseMoveEvent(QMouseEvent *e);

private:
	IconBtn     *m_minimizeBtn;
	IconBtn     *m_maxmizeBtn;
	IconBtn     *m_closeBtn;
	QLabel      *m_titleTextLbl;
	QHBoxLayout *m_layout;
	bool        m_isMaxSize;

	//bool   m_maxNormal;
	//QPoint m_startPos;
	//QPoint m_clickPos;
};

#endif // PAGETITLE_H
