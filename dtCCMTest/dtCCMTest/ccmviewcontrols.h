#ifndef CCMTEST_H
#define CCMTEST_H

#include <QDockWidget>
#include "ui_ccmtest.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QDateTime>
#include <QThread>
#include "global_default.h"

class CCMLogBar : public QDockWidget
{
	Q_OBJECT

public:
	CCMLogBar(QWidget *parent = 0);
	~CCMLogBar();

	QTextEdit *m_pEditBar;

	public slots:
	void slot_addLog(QString, QColor);

	
};
class CCMViewBar :public QWidget {
	Q_OBJECT
public:
	CCMViewBar(QWidget *parent = 0);
	~CCMViewBar();
protected:
	QLabel *m_pImgView;
};
class CCMConnectStatusBar : public QThread
{
	Q_OBJECT
public:
	CCMConnectStatusBar(QObject *parent = 0);
	~CCMConnectStatusBar();

signals:
	void sig_statuschange(int);
protected:
	virtual void run();

private:
	int nDevNum;
};

#endif // CCMTEST_H
