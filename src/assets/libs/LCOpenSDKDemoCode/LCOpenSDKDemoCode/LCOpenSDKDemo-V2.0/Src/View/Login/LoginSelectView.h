#ifndef _HOMEPAGE_H_
#define _HOMEPAGE_H_

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QHBoxLayout>
#include "Src/Utils/CommonView/BgColorBtn.h"
#include "Src/Utils/CommonView/IconTextBtn.h"

class LoginSelectView : public QWidget
{
	Q_OBJECT

public:
	LoginSelectView(QWidget* parent/* = nullptr*/);
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

signals:
	void sgnShowDevicesList();

private:
	QLabel*             m_LogoLbl;
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
	QWidget*            m_loginSelectWidget;
	QHBoxLayout*        m_loginSelectLayout;
	BgColorBtn*         m_AdminModelBtn;
	IconTextBtn*        m_ResumeBtn;
};

#endif /* _HOMEPAGE_H_ */
