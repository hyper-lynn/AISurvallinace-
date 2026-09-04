#include "MyEditBox2.h"

MyEditBox2::MyEditBox2(QWidget* parent)
: QDialog(parent)
{
    m_toolBar                   = NULL;
    m_titleLbl                  = NULL;
    m_closeBtn                  = NULL;
    m_workBar                   = NULL;
    m_inputLbl1                 = NULL;
    m_inputLbl2                 = NULL;
    m_inputEdt1                 = NULL;
    m_inputEdt2                 = NULL;
    m_okBtn                     = NULL;
    m_cancelBtn                 = NULL;
    m_isMousePressedInToolBar   = false;
}

MyEditBox2::~MyEditBox2()
{
    release();
}

int MyEditBox2::init(QString titleText, QString lbl1Text, QString lbl2Text)
{
    int ret = 0;

    do 
    {
        this->resize(250, 160);
        this->setModal(true);
        this->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);

        m_toolBar = new (std::nothrow) QWidget(this);
        if (NULL == m_toolBar)
        {
            ret = -1;
            break;
        }
        m_toolBar->resize(this->width(), 30);
        m_toolBar->move(0, 0);
        m_toolBar->setStyleSheet("background-color:#2c2d30;");

        m_titleLbl = new (std::nothrow) QLabel(m_toolBar);
        if (NULL == m_titleLbl)
        {
            ret = -1;
            break;
        }
        m_titleLbl->setFixedHeight(m_toolBar->height());
        m_titleLbl->move(0, 0);
        m_titleLbl->setStyleSheet("color:#ffffff;font:10pt;font-family:Microsoft YaHei;");
        m_titleLbl->setText(titleText);
        m_titleLbl->adjustSize();

        m_closeBtn = new (std::nothrow) IconBtn(m_toolBar, "Skin/conmmon_icon_close");
        if (NULL == m_closeBtn)
        {
            ret = -1;
            break;
        }
        m_closeBtn->move(m_toolBar->width() - m_closeBtn->width(), 0);
        connect(m_closeBtn, SIGNAL(clicked()), this, SLOT(slotClose()));

        m_workBar = new (std::nothrow) QWidget(this);
        if (NULL == m_workBar)
        {
            ret = -1;
            break;
        }
        m_workBar->resize(this->width(), this->height() - m_toolBar->height());
        m_workBar->move(0, m_toolBar->height());
        m_workBar->setStyleSheet("background-color:#323436;");

        m_inputLbl1 = new (std::nothrow) QLabel(m_workBar);
        if (NULL == m_inputLbl1)
        {
            ret = -1;
            break;
        }
        m_inputLbl1->setFixedHeight(20);
        m_inputLbl1->move(10, 20);
        m_inputLbl1->setStyleSheet("color:#ffffff;font:11pt;font-family:Microsoft YaHei;");
        m_inputLbl1->setText(lbl1Text);
        m_inputLbl1->adjustSize();

        m_inputLbl2 = new (std::nothrow) QLabel(m_workBar);
        if (NULL == m_inputLbl2)
        {
            ret = -1;
            break;
        }
        m_inputLbl2->setFixedHeight(20);
        m_inputLbl2->move(10, 60);
        m_inputLbl2->setStyleSheet("color:#ffffff;font:11pt;font-family:Microsoft YaHei;");
        m_inputLbl2->setText(lbl2Text);
        m_inputLbl2->adjustSize();

        int maxWidth = (m_inputLbl1->width() > m_inputLbl2->width()) ? m_inputLbl1->width() : m_inputLbl2->width();

        m_inputEdt1 = new (std::nothrow) QLineEdit(m_workBar);
        if (NULL == m_inputEdt1)
        {
            ret = -1;
            break;
        }
        m_inputEdt1->resize(m_workBar->width() - maxWidth - 20, 20);
        m_inputEdt1->move(10 + maxWidth, 20);
        m_inputEdt1->setStyleSheet("background-color:#424446;color:#a8a9a9;font:11pt;font-family:Microsoft YaHei;border:0px;");

        m_inputEdt2 = new (std::nothrow) QLineEdit(m_workBar);
        if (NULL == m_inputEdt2)
        {
            ret = -1;
            break;
        }
        m_inputEdt2->resize(m_workBar->width() - maxWidth - 20, 20);
        m_inputEdt2->move(10 + maxWidth, 60);
        m_inputEdt2->setStyleSheet("background-color:#424446;color:#a8a9a9;font:11pt;font-family:Microsoft YaHei;border:0px;");

        m_okBtn = new (std::nothrow) BgColorBtn(m_workBar);
        if (NULL == m_okBtn)
        {
            ret = -1;
            break;
        }
        m_okBtn->resize(m_workBar->width() / 2, 30);
        m_okBtn->move(0, m_workBar->height() - 30);
        m_okBtn->setBtnAttribute(QColor(0x32, 0x34, 0x36), QColor(0x42, 0x44, 0x46), QColor(0xff, 0xff, 0xff), 10);
        m_okBtn->setText(tr("OK"));
        connect(m_okBtn, SIGNAL(clicked()), this, SLOT(slotOK()));

        m_cancelBtn = new (std::nothrow) BgColorBtn(m_workBar);
        if (NULL == m_cancelBtn)
        {
            ret = -1;
            break;
        }
        m_cancelBtn->resize(m_workBar->width() / 2, 30);
        m_cancelBtn->move(m_workBar->width() / 2, m_workBar->height() - 30);
        m_cancelBtn->setBtnAttribute(QColor(0x32, 0x34, 0x36), QColor(0x42, 0x44, 0x46), QColor(0xff, 0xff, 0xff), 10);
        m_cancelBtn->setText(tr("Cancel"));
        connect(m_cancelBtn, SIGNAL(clicked()), this, SLOT(slotCancel()));

    } while (0);

    if (0 != ret)
    {
        release();
    }

    return ret;
}

void MyEditBox2::release()
{
    if (NULL != m_cancelBtn)
    {
        delete m_cancelBtn;
        m_cancelBtn = NULL;
    }

    if (NULL != m_okBtn)
    {
        delete m_okBtn;
        m_okBtn = NULL;
    }

    if (NULL != m_inputEdt2)
    {
        delete m_inputEdt2;
        m_inputEdt2 = NULL;
    }

    if (NULL != m_inputEdt1)
    {
        delete m_inputEdt1;
        m_inputEdt1 = NULL;
    }

    if (NULL != m_inputLbl2)
    {
        delete m_inputLbl2;
        m_inputLbl2 = NULL;
    }

    if (NULL != m_inputLbl1)
    {
        delete m_inputLbl1;
        m_inputLbl1 = NULL;
    }

    if (NULL != m_workBar)
    {
        delete m_workBar;
        m_workBar = NULL;
    }

    if (NULL != m_closeBtn)
    {
        delete m_closeBtn;
        m_closeBtn = NULL;
    }

    if (NULL != m_titleLbl)
    {
        delete m_titleLbl;
        m_titleLbl = NULL;
    }

    if (NULL != m_toolBar)
    {
        delete m_toolBar;
        m_toolBar = NULL;
    }

    return;
}

void MyEditBox2::show()
{
    m_inputEdt1->setText("");
    m_inputEdt2->setText("");
    QDialog::show();
}

void MyEditBox2::mousePressEvent(QMouseEvent* ev)
{
    m_oldPos = ev->pos();

    if (m_toolBar->rect().contains(ev->pos()))
    {
        if (Qt::LeftButton == ev->button())
        {
            m_isMousePressedInToolBar = true;
        }
    }

    return;
}

void MyEditBox2::mouseMoveEvent(QMouseEvent* ev)
{
    if (m_isMousePressedInToolBar)
    {
        int dx = ev->x() - m_oldPos.x();
        int dy = ev->y() - m_oldPos.y();
        move(x() + dx, y() + dy);
    }

    return;
}

void MyEditBox2::mouseReleaseEvent(QMouseEvent* ev)
{
    m_isMousePressedInToolBar = false;
    return;
}

void MyEditBox2::slotClose()
{
    hide();
    return;
}

void MyEditBox2::slotOK()
{
    hide();
    emit sgnOK(m_inputEdt1->text(), m_inputEdt2->text());
    return;
}

void MyEditBox2::slotCancel()
{
    hide();
    return;
}
