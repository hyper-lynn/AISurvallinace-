#ifndef ICONBTN_H
#define ICONBTN_H

#include <QLabel>

typedef enum
{
	ICON_STATUS_NORMAL = 0x00000001,
	ICON_STATUS_HOVER = 0x00000002,
	ICON_STATUS_PRESS = 0x00000004,
	ICON_STATUS_NOABLE = 0x00000008,
	ICON_STATUS_ING = 0x00000010,

	/* 不规则按钮 */
	ICON_TYPE_MASK = 0x00000020,

	/* 不重绘已绘制区域(建议尽量不要使用该参数) */
	ICON_TYPE_OPAQUEPAINT = 0x00000040,

	/* 长按功能 */
	ICON_TYPE_LONGPRESS = 0x00000080,

	ICON_STATUS_DEFAULT = ICON_STATUS_NORMAL | ICON_STATUS_HOVER | ICON_STATUS_PRESS,
}ICON_STATUS_E;

class QTimer;
class IconBtn : public QLabel
{
	Q_OBJECT

public:
	IconBtn(QWidget *parent, QString iconPath, unsigned long stateSets = ICON_STATUS_DEFAULT);
	~IconBtn();

	void setPosition(const QPoint &position);
	void setIconPath(const QString &iconPath);
	void setBtnEnable(bool enable);
	void setIngStatus(bool isIng);

protected:
	void enterEvent(QEvent*);
	void leaveEvent(QEvent*);
	void mousePressEvent(QMouseEvent*);
	void mouseReleaseEvent(QMouseEvent*);

private:
	unsigned long     m_stateSets;
	QString           m_iconPath;
	bool              m_isEnable;
	bool              m_isIngStatus;

	bool              m_isMouseHover;
	bool              m_isMousePress;
	QTimer           *m_longPressTimer;
	bool              m_isLongPress;

	void refreshIconStatu();

signals:
	/**
	* 单击通知
	* @return  void
	*/
	void clicked();

	/**
	* 长按通知
	* @param   [in] bool isPress    ture/false 长按开始/长按结束
	* @return  void
	*/
	void longPressTrigger(bool isPress);

private slots:
	void longPressTimeOut();
};

#endif // ICONBTN_H
