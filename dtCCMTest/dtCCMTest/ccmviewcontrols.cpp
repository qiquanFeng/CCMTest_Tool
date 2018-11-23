#include "ccmviewcontrols.h"
#include "dtccmtest.h"


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

CCMConfigSelectDlg::CCMConfigSelectDlg(QWidget *parent) 
	:QDialog(parent),m_pvlayMain(new QVBoxLayout()),m_pcomboRule(new QComboBox()),m_pbutAdd(new QPushButton(tr("Add"))),\
	m_pbutSelect(new QPushButton(tr("select"))),m_plabRule(new QLabel(tr("Config Rule:"))), m_pConfigAddDlg(new CCMConfigAddDlg(this))
{
	setLayout(m_pvlayMain);
	
	m_pvlayMain->addWidget(m_plabRule);
	m_pvlayMain->addWidget(m_pcomboRule);
	m_pvlayMain->addWidget(m_pbutSelect);
	m_pvlayMain->addWidget(m_pbutAdd);
	m_pvlayMain->addStretch(5);

	setFixedSize(300, 150);
	connect(m_pbutSelect, SIGNAL(clicked()), this, SLOT(slot_butSelect()));
	connect(m_pbutAdd, SIGNAL(clicked()), this, SLOT(slot_butAdd()));
}
CCMConfigSelectDlg::~CCMConfigSelectDlg() {

}
void CCMConfigSelectDlg::slot_butSelect() {
	dtCCMTest *pdtCCMTest = (dtCCMTest *)parent();
	QSqlQuery query(pdtCCMTest->m_configDatabase);
	query.prepare("update activeconfig set name = :name where 1");
	query.bindValue(0, m_pcomboRule->currentText());
	if (!query.exec()) {
		QMessageBox::warning(this, "fail", tr("select rule fail!"));
		emit pdtCCMTest->sgl_addLog(tr("select rule fail!"));
	}
}
void CCMConfigSelectDlg::slot_butAdd() {
	m_pConfigAddDlg->exec();
}

CCMConfigAddDlg::CCMConfigAddDlg(QSqlDatabase *database,QWidget *parent /* = 0 */) {

}
CCMConfigAddDlg::~CCMConfigAddDlg() {

}
void CCMConfigAddDlg::slot_butCommit() {

}
void CCMConfigAddDlg::slot_butCancel() {

}