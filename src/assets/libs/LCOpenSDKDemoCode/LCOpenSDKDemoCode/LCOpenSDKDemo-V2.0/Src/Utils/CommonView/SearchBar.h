#ifndef SEARCHBAR_H
#define SEARCHBAR_H

#include <QWidget>
#include <QLayout>
#include <QEvent>
#include <QLineEdit>
#include "IconTextBtn.h"

class SearchBar : public QWidget
{
	Q_OBJECT

public:
	SearchBar(QWidget *parent);
	~SearchBar();

public:
	int init();
	void setDate(QString dateTime);
	QString getDate();

signals:
	void sgnFocusIn();
    void sgnFocusOut();
	void sgnSearch(QString dateTime);

private slots:
	void slotSearch();

protected:
    virtual bool eventFilter(QObject *obj, QEvent *event);
private:

	QLineEdit   *m_textEdit;
	IconTextBtn *m_searchBtn;
	QHBoxLayout *m_layout;
	QWidget     *searchBtnBGArea;
	
};

#endif // SEARCHBAR_H
