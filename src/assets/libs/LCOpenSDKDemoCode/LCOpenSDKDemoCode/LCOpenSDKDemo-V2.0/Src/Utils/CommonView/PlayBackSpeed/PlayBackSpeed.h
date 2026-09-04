#ifndef PLAYBACKSPEED_H
#define PLAYBACKSPEED_H

#include <QWidget>
#include <QPushButton>
namespace Ui { class PlayBackSpeed; };

//快放菜单
class PlayBackSpeed : public QWidget
{
	Q_OBJECT

public:
	PlayBackSpeed(QWidget *parent = Q_NULLPTR);
	~PlayBackSpeed();
	// 获取快放速率(1,4,8,16,32倍数)
	int GetCheckedSpeed();
	// 设置快放速率（1,4,8,16,32倍数）
	void SetCheckedSpeed(int iSpeed);

	//初始化快进快退界面
	void InitUI(int iforward = 32);
signals:
	void SignalPlaybackSpeedChanged();

private:
	// 用于获取鼠标点击菜单事件
	virtual bool eventFilter(QObject *watched, QEvent *event);
	// 
	virtual void resizeEvent(QResizeEvent *event);
	// 
	virtual void paintEvent(QPaintEvent *event);

	// 设置快放速率（0,1,2,3,4下标）
	void SetChecked(int iIndex);

	//获取选中的倍速下标
	int  GetCheckedId(int iSpeed);
	//设置显示按钮
	void ShowAllBtn();
private:
	Ui::PlayBackSpeed*		ui;
	QPixmap*				m_pPicBackgroundNormal;
	QVector<QPushButton*>	m_vecBtnPtr;
	int						m_iChecked;	//选中的下标
	int                     m_iMaxSpeedUp; //正放2的幂数量,支持最大正放倍数		
};

#endif