#ifndef CALENDAR_H
#define CALENDAR_H

#include <QCalendarWidget>

class Calendar : public QCalendarWidget
{
    Q_OBJECT

public:
    Calendar(QWidget* parent);
    ~Calendar();
    void init();

signals:
    void sgnClicked(QDate);

};

#endif // CALENDAR_H
