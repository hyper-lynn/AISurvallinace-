#include <QLocale>
#include <QTextCharFormat>
#include "Calendar.h"

Calendar::Calendar(QWidget* parent)
: QCalendarWidget(parent)
{

}

Calendar::~Calendar()
{

}

void Calendar::init()
{
    connect(this, SIGNAL(clicked(QDate)), this, SIGNAL(sgnClicked(QDate)));
    this->setVerticalHeaderFormat(NoVerticalHeader);
    this->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
    this->setHorizontalHeaderFormat(SingleLetterDayNames);
    this->setMinimumDate(QDate(2010, 01, 01));

    QTextCharFormat headerTextFmt;
    headerTextFmt.setBackground(QColor(0x2c, 0x2d, 0x30));
    headerTextFmt.setFontPointSize(11);
    this->setHeaderTextFormat(headerTextFmt);

    /* 设置日历样式表 */
    this->setStyleSheet(
        "background-color:#2C2D30;"
        """Microsoft YaHei"";"
        "font-size: 14px;"
        );

    /* 更换上、下个月导航按钮图标 
    QToolButton *preMonthButton = this->findChild<QToolButton*>("qt_calendar_prevmonth");
    if (NULL != preMonthButton)
    {
        QIcon preIcon;
        preIcon.addFile("", preMonthButton->size());
        preMonthButton->setIcon(preIcon);
    }

    QToolButton *nextMonthButton = this->findChild<QToolButton*>("qt_calendar_prevmonth");
    if (NULL != nextMonthButton)
    {
        QIcon nextIcon;
        nextIcon.addFile("", nextMonthButton->size());
        nextMonthButton->setIcon(nextIcon);
    } */

    return;
}
