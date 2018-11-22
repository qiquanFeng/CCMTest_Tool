#ifndef DTCCMTEST_H
#define DTCCMTEST_H

#include <QtWidgets/QMainWindow>
#include "ui_dtccmtest.h"
#include "global_default.h"
#include <QFile>
#include "ccmviewcontrols.h"
#include <QHBoxLayout>
#include "ccmconfigdlg.h"
#include <QToolBar>
#include <QPushButton>
#include <QDateTime>
#include <QComboBox>
#include <QLineEdit>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QStringList>

class dtCCMTest : public QMainWindow
{
	Q_OBJECT

public:
	dtCCMTest(QWidget *parent = 0);
	~dtCCMTest();

	//Database
	QSqlDatabase m_configDatabase;
	int connectConfigDatabase();
	QStringList getConfigList(QString DatabaseType=QString("QSQLITE"));
	static QString getConfigNameFromDB(QSqlDatabase &database,QString DatabaseType = QString("QSQLITE"));

	QString getConfigName();
	void setConfigName(QString);
signals:
	void sgl_addLog(QString, QColor = QColor(0, 0, 0));
protected:
	QLabel *m_pLabStatus;
	QPushButton *m_pButAddConfig;

	CCMLogBar *m_pCCMLog;
	CCMViewBar *m_pImgView;
	CCMConfigDlg *m_pConfigDlg;

	virtual void closeEvent(QCloseEvent *event);

private:
	void createMenuBar();
	void createToolBar();
	void createView();

	void loadStyleFile(QString fileName);
	void loadToolBarLayout();

	CCMConfigSelectDlg *m_pConfigSelectDlg;
	QPushButton *m_pConfigSelect;

	QDialog *m_pAddConfigDlg;
	QLabel *m_labConfigName;
	QLineEdit *m_pAddConfig_LineEdit;
	QPushButton *m_pAddConfig_But;
	QVBoxLayout *m_pAddConfig_Layout;

	public slots:
	void slot_connectStatus(int);
	void slot_showConfig();
	void slot_butPlay();
	void slot_butSelectConfig();
	void slot_butNewConfig_Add();
	
private:
	Ui::dtCCMTestClass ui;

	QString m_strConfigName;
};

#endif // DTCCMTEST_H
