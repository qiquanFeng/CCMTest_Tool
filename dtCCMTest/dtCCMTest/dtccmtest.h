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

class dtCCMTest : public QMainWindow
{
	Q_OBJECT

public:
	dtCCMTest(QWidget *parent = 0);
	~dtCCMTest();

signals:
	void sgl_addLog(QString, QColor = QColor(0, 0, 0));
protected:
	QLabel *m_pLabStatus;
	QComboBox *m_pConfigCombox;

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



	public slots:
	void slot_connectStatus(int);
	void slot_showConfig();
	void slot_butPlay();
private:
	Ui::dtCCMTestClass ui;
};

#endif // DTCCMTEST_H
