#include "ccmconfigdlg.h"

CCMConfigDlg::CCMConfigDlg(QWidget *parent)
	: QDialog(parent), m_pTabGroup(new QTabWidget())
{
	createUI();
	m_pSetting = new QSettings("D:/sensor.ini", QSettings::IniFormat);
	bool bstatus = m_pSetting->contains("Sensor/width");
	int i = 1;
	
	

	return;
}

CCMConfigDlg::~CCMConfigDlg()
{

}

QList<QPair<int, int>> CCMConfigDlg::loadINIGroup(QString group, QString origin, int format) {
	QString IniBuffer;
	PAIRLIST map;
	if (!format) {
		QFile file(origin);
		file.open(QIODevice::ReadOnly);
		IniBuffer = QString(file.readAll());
		file.close();
	}
	else {
		IniBuffer = origin;
	}
	
	QTextStream stream(&IniBuffer);
	stream.setCodec("UTF-8");
	QString str;
	do{
		str = stream.readLine().trimmed();
		if (!str.indexOf(QString("[%1]").arg(group))) {
			do {
				str = stream.readLine().trimmed();
				QRegExp reg("^[\\s]*0x([0-9a-fA-F]+),[\\s]*0x([0-9a-fA-F]+).*$");
				reg.setCaseSensitivity(Qt::CaseInsensitive);
				if (reg.exactMatch(str)) {
					QString key = reg.cap(1);
					QString val = reg.cap(2);
					QPair<int,int> pair(key.toInt(NULL, 16), val.toInt(NULL, 16));
					map.append(pair);
				}

			} while (str.left(1)!="["&& !str.isNull());
		}
	} while (!str.isNull());

	
	return map;
}

void CCMConfigDlg::createUI() {
	m_pWidGro1 = new QWidget;
	m_pWidGro2 = new QWidget;
	m_pWidGro3 = new QWidget;
	m_pWidGro4 = new QWidget;
	m_pWidGro5 = new QWidget;

	//*   TabGroup 1
	m_pTxtEdit_Gro1=new QTextEdit;
	m_pButCommit_Gro1=new QPushButton(tr("commit"));
	QVBoxLayout *vlay1 = new QVBoxLayout();
	vlay1->addWidget(m_pTxtEdit_Gro1,50);
	vlay1->addWidget(m_pButCommit_Gro1);
	m_pWidGro1->setLayout(vlay1);
	m_pTabGroup->addTab(m_pWidGro1, "Initial");
	
	//*   TabGroup 2
	m_pTabGroup->addTab(m_pWidGro2, "White");

	QHBoxLayout *hlay = new QHBoxLayout();
	hlay->addWidget(m_pTabGroup,50);
	setLayout(hlay);

	setFixedSize(480, 320);
	

}