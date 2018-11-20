#include "ccmviewcontrols.h"

CCMLogBar::CCMLogBar(QWidget *parent)
	: QDockWidget(parent)
{
	setFeatures(QDockWidget::DockWidgetMovable);
	setWindowTitle(tr("System Output Log"));

	m_pEditBar = new QTextEdit();
	m_pEditBar->setReadOnly(true);
	setWidget(m_pEditBar);
}
CCMLogBar::~CCMLogBar()
{

}
void CCMLogBar::slot_addLog(QString str, QColor c) {
	m_pEditBar->setTextColor(c);
	m_pEditBar->append(QDateTime::currentDateTime().toString("MM-dd hh:mm:ss:zzz ")+str);
}

CCMViewBar::CCMViewBar(QWidget *parent) :QWidget(parent) {
	m_pImgView = new QLabel();
	m_pImgView->setObjectName("ImgView");

	QVBoxLayout *vlayout = new QVBoxLayout();
	vlayout->addWidget(m_pImgView);
	setLayout(vlayout);

}
CCMViewBar::~CCMViewBar()
{

}

CCMConnectStatusBar::CCMConnectStatusBar(QObject *parent)
	: QThread(parent), nDevNum(0xFFFF)
{
	//moveToThread(this);
}
CCMConnectStatusBar::~CCMConnectStatusBar()
{

}

void CCMConnectStatusBar::run() {

	while (1) {
		int DevNum = 0;
		char* pDeviceName[8] = { NULL };

		//¶ÈÐÅ
		EnumerateDevice(pDeviceName, 8, &DevNum);
		/*QStringList strlistDev;
		for (int i=0;i<DevNum;i++)
		{
			strlistDev.append(QString(pDeviceName[i]));
		}*/

		if (nDevNum != DevNum) {
			nDevNum = DevNum;
			emit sig_statuschange(DevNum);
		}

		::Sleep(1000);
	}
}