#include "dtccmtest.h"
#include "QLabel"

dtCCMTest::dtCCMTest(QWidget *parent)
	: QMainWindow(parent),m_pImgView(new CCMViewBar), m_pConfigDlg(new CCMConfigDlg(this)),\
	m_pCCMLog(new CCMLogBar()), m_pLabStatus(new QLabel("")), m_pConfigCombox(new QComboBox()),m_pButAddConfig(new QPushButton("New"))
{
	ui.setupUi(this);
	setWindowIcon(QIcon(":/dtCCMTest/Resources/Login.ico"));

	createMenuBar();
	createToolBar();
	createView();
	loadStyleFile("./style.qss");
	connect(this, SIGNAL(sgl_addLog(QString, QColor)), m_pCCMLog, SLOT(slot_addLog(QString, QColor)));
	connect(m_pConfigDlg, SIGNAL(sgl_addLog(QString, QColor)), m_pCCMLog, SLOT(slot_addLog(QString, QColor)));

	//initial database
	m_configDatabase = QSqlDatabase::addDatabase("QSQLITE", "configquery");
	m_configDatabase.setDatabaseName("./configDatabase");
	if (!m_configDatabase.open()) {
		emit sgl_addLog("config database connect fail!");
		QSqlDatabase::removeDatabase("configquery");
		return ;
	}
	else {
		emit sgl_addLog("config database connect success!",QColor(0,255,0));
	}

}
dtCCMTest::~dtCCMTest()
{

}

void dtCCMTest::createMenuBar() {
	QMenu *menu_Config = menuBar()->addMenu(tr("config"));
	QAction *act_showconfig=menu_Config->addAction(QIcon(":/dtCCMTest/Resources/Login.ico"), "config");
	QAction *act_loadconfig = menu_Config->addAction("load");

	QMenu *menu_Config1 = menuBar()->addMenu("menu1");
	
	connect(act_showconfig, SIGNAL(triggered(bool)), this, SLOT(slot_showConfig()));
}
void dtCCMTest::createToolBar() {
	 QToolBar *toolbar= addToolBar("tool");
	 QPushButton *but = new QPushButton("Play");
	 but->setObjectName("butPlay");
	 toolbar->addWidget(but);
	 loadToolBarLayout();

	 connect(but, SIGNAL(clicked()), this, SLOT(slot_butPlay()));
}
void dtCCMTest::createView() {
	addDockWidget(Qt::BottomDockWidgetArea, m_pCCMLog);

	CCMConnectStatusBar *status = new CCMConnectStatusBar();
	connect(status, SIGNAL(sig_statuschange(int)), this, SLOT(slot_connectStatus(int)));
	status->start();

	QHBoxLayout *hlayout = new QHBoxLayout;
	m_pLabStatus->setFixedSize(30, 30);
	hlayout->addWidget(m_pLabStatus);
	hlayout->addWidget(m_pButAddConfig);
	hlayout->addWidget(m_pConfigCombox,5);
	m_pConfigCombox->addItem("add new rule");

	QVBoxLayout *vlayout = new QVBoxLayout();
	vlayout->addLayout(hlayout);
	vlayout->addWidget(m_pImgView,5);
	centralWidget()->setLayout(vlayout);
}
void dtCCMTest::loadStyleFile(QString fileName) {
	QFile file(fileName);
	if (!file.exists())
		return;
	file.open(QIODevice::ReadOnly);
	this->setStyleSheet(QString(file.readAll()));
	file.close();
}
void dtCCMTest::loadToolBarLayout() {
	QSettings settings("Software Inc.", "Icon Editor");
	settings.beginGroup("mainWindow");
	restoreGeometry(settings.value("geometry").toByteArray());
	restoreState(settings.value("state").toByteArray());
	settings.endGroup();
}

void dtCCMTest::slot_connectStatus(int nStatus) {
	
	m_pLabStatus->setText(QString::number(nStatus));
	if (nStatus > 0) {
		m_pLabStatus->setStyleSheet("background-color:green;");
		emit sgl_addLog(tr("Device Connect Success"),QColor(0,255,0));
	}
	else {
		m_pLabStatus->setStyleSheet("background-color:red;");
		emit sgl_addLog(tr("Device is not connected"), QColor(255, 0, 0));
	}
	
}
void dtCCMTest::slot_showConfig() {
	m_pConfigDlg->show();
	m_pConfigDlg->raise();
	m_pConfigDlg->activateWindow();
}
void dtCCMTest::slot_butPlay() {
	emit sgl_addLog("Play");
}
void dtCCMTest::closeEvent(QCloseEvent *event) {
	QSettings settings("Software Inc.", "Icon Editor");
	settings.beginGroup("mainWindow");
	settings.setValue("geometry", saveGeometry());
	settings.setValue("state", saveState());
	settings.endGroup();
}