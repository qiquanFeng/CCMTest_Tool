#ifndef CCMCONFIGDLG_H
#define CCMCONFIGDLG_H

#include <QDialog>
#include <QDockWidget>
#include <QSettings>
#include <QFile>
#include <QTextStream>
#include <qregularexpression.h>
#include <QMap>
#include <QTabWidget>
#include <QLayout>
#include <QTextEdit>
#include <QPushButton>
#include <QPair>
#include "global_default.h"



class CCMConfigDlg : public QDialog
{
	Q_OBJECT

public:
	CCMConfigDlg(QWidget *parent = 0);
	~CCMConfigDlg();

	QTabWidget *m_pTabGroup;
	/*
	0: origin is FileName
	1: origin is Data
	*/
	static PAIRLIST loadINIGroup(QString group,QString origin,int format=0);
	QSettings *m_pSetting;

private:
	QWidget *m_pWidGro0;
	QWidget *m_pWidGro1;
	QWidget *m_pWidGro2;
	QWidget *m_pWidGro3;
	QWidget *m_pWidGro4;
	QWidget *m_pWidGro5;

	QTextEdit *m_pTxtEdit_Gro1;
	QPushButton *m_pButCommit_Gro1;
	void createUI();
};

#endif // CCMCONFIGDLG_H
