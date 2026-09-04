#ifndef SEARCHDEVICEBAR_H
#define SEARCHDEVICEBAR_H

#include <QWidget>
#include <QLayout>
#include <QEvent>
#include <QLineEdit>
#include "IconTextBtn.h"

class SearchDeviceBar : public QWidget
{
	Q_OBJECT

public:
	SearchDeviceBar(QWidget *parent);
	~SearchDeviceBar();

public:
	int init();
	void setDeviceID(QString deviceID);
	QString getDeviceID();

signals:
	void sgnFocusIn();
	void sgnFocusOut();
	void sgnSearchDevice(QString deviceID);

private slots:
	void slotSearchDevice();

protected:
	virtual bool eventFilter(QObject *obj, QEvent *event);
private:


	IconTextBtn *m_searchBtn;
	QHBoxLayout *m_layout;
	QLineEdit   *m_textEdit;
	QWidget     *searchBtnBGArea;

};

#endif // SEARCHDEVICEBAR_H
