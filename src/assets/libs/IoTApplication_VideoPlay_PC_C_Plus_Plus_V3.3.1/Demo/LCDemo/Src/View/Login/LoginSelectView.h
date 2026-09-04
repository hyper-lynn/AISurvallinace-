#ifndef _HOMEPAGE_H_
#define _HOMEPAGE_H_

#include <QtWidgets/QWidget>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include "Utils/CommonView/BgColorBtn.h"
#include "Utils/CommonView/IconTextBtn.h"

class LoginSelectView : public QWidget
{
    Q_OBJECT

public:
    LoginSelectView(QWidget* parent);
    ~LoginSelectView();

    int init();
    void release();

    QString getAppId();
    QString getAppSecret();
#ifdef TEST_MODEL
    QString getHost();
    int     getPort();
    void saveLoginInfoToLocal();
#endif

private:
    void showHint();
    void hideHint();

private slots:
    void slotAdminModel();
    void slotResume();
    void slotGetPlayInfoResult(bool bSucceed);
    void slotGetP2pInfoResult(bool bSucceed);
signals:
    void sgnShowDevicesList();
private:
    QLabel*             m_LogoLbl;
    QLabel*             m_TitleLbl;
#ifdef TEST_MODEL
    QLabel*             m_hostLbl;
    QLineEdit*          m_hostEdt;
    QLabel*             m_portLbl;
    QLineEdit*          m_portEdt;
#endif
    QLabel*             m_AppIdLbl;
    QLineEdit*          m_AppIdEdt;
    QLabel*             m_AppSecretLbl;
    QLineEdit*          m_AppSecretEdt;
    QLabel*             m_HintLbl1;
    QLabel*             m_HintLbl2;
    BgColorBtn*         m_AdminModelBtn;
    IconTextBtn*        m_ResumeBtn;
};

#endif /* _HOMEPAGE_H_ */
