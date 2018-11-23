#ifndef CCMTEST_H
#define CCMTEST_H

#include <QDockWidget>
#include "ui_ccmtest.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QDateTime>
#include <QThread>
#include <QDialog>
#include <QComboBox>
#include <QPushButton>

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

class CCMConfigAddDlg :public QDialog {
	Q_OBJECT
public:
	CCMConfigAddDlg(QSqlDatabase *database, QWidget *parent = 0);
	~CCMConfigAddDlg();

	QPushButton *m_pbutCommit;
	QPushButton *m_pbutCancel;
	QLabel *m_plabConfigName;
	QLineEdit *m_pledConfigName;


	public slots:
	void slot_butCommit();
	void slot_butCancel();
};

class CCMConfigSelectDlg :public QDialog {
	Q_OBJECT
public:
	CCMConfigSelectDlg(QWidget *parent);
	~CCMConfigSelectDlg();

	QLabel *m_plabRule;
	QComboBox *m_pcomboRule;
	QPushButton *m_pbutSelect, *m_pbutAdd;
	QVBoxLayout *m_pvlayMain;
protected:
	CCMConfigAddDlg *m_pConfigAddDlg;

	public slots:
	void slot_butSelect();
	void slot_butAdd();
};

#endif // CCMTEST_H
