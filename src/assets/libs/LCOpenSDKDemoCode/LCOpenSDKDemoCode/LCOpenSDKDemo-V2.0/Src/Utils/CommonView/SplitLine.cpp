#include "SplitLine.h"
#include <math.h>

SplitLine::SplitLine(QWidget *parent)
    : QWidget(parent)
{
    init();
    createSplitLine(QColor(0x00, 0x00, 0x00), QColor(0x32, 0x34, 0x36), 2);
}

SplitLine::SplitLine(QWidget *parent, QColor &colorOver, QColor &colorBelow, int height)
    : QWidget(parent)
{
    init();
    createSplitLine(colorOver, colorBelow, height);
}

SplitLine::SplitLine(QWidget *parent, QColor &color, int height)
: QWidget(parent)
{
    init();
    createSplitLine(color, height);
}

SplitLine::~SplitLine()
{
    if (m_topLine)
    {
        delete m_topLine;
        m_topLine = NULL;
    }

    if(m_bottomLine)
    {
        delete m_bottomLine;
        m_bottomLine = NULL;
    }
}

void SplitLine::init()
{
    m_topLine =     NULL;
    m_bottomLine =  NULL;
}

void SplitLine::createSplitLine(QColor &colorOver, QColor &colorBelow, int height)
{
    int halfHeight = ceil((double)height / (double)2);
    this->resize(parentWidget()->width(), halfHeight * 2);
    m_topLine    = new QWidget(this);
    m_topLine->setAutoFillBackground(true);
    m_bottomLine = new QWidget(this);
    m_bottomLine->setAutoFillBackground(true);

    QPalette palette;

    palette.setColor(QPalette::Background, colorOver);
    m_topLine->setPalette(palette);
    m_topLine->resize(this->width(), halfHeight);
    m_topLine->move(0, 0);

    palette.setColor(QPalette::Background, colorBelow);
    m_bottomLine->setPalette(palette);
    m_bottomLine->resize(this->width(), halfHeight);
    m_bottomLine->move(0, halfHeight);
}

void SplitLine::createSplitLine(QColor &color, int height)
{
    this->resize(parentWidget()->width(), height);
    m_topLine = new QWidget(this);
    m_topLine->setAutoFillBackground(true);

    QPalette palette;

    palette.setColor(QPalette::Background, color);
    m_topLine->setPalette(palette);
    m_topLine->resize(this->width(), height);
    m_topLine->move(0, 0);
}

void SplitLine::resizeEvent(QResizeEvent *ev)
{
    QWidget::resizeEvent(ev);

    if (m_topLine)
    {
        m_topLine->setFixedWidth(this->width());
    }

    if (m_bottomLine)
    {
        m_bottomLine->setFixedWidth(this->width());
    }
}

