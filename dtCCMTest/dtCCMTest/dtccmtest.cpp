#include "dtccmtest.h"
#include "QLabel"

dtCCMTest::dtCCMTest(QWidget *parent)
	: QMainWindow(parent),m_pImgView(new CCMViewBar), m_pConfigDlg(new CCMConfigDlg(this)),\
	m_pCCMLog(new CCMLogBar()), m_pLabStatus(new QLabel("")),m_pConfigSelect(new QPushButton("...")),m_pConfigSelectDlg(new CCMConfigSelectDlg(this)),\
	m_labConfigName(new QLabel("..."))
{
	ui.setupUi(this);
	setWindowIcon(QIcon(":/dtCCMTest/Resources/Login.ico"));
	// set object name
	m_labConfigName->setObjectName("rulelable");
	m_pConfigSelect->setObjectName("configselectbutton");

	//initial database
	connectConfigDatabase();

	createMenuBar();
	createToolBar();
	createView();
	loadStyleFile("./style.qss");
	connect(this, SIGNAL(sgl_addLog(QString, QColor)), m_pCCMLog, SLOT(slot_addLog(QString, QColor)));
	connect(m_pConfigDlg, SIGNAL(sgl_addLog(QString, QColor)), m_pCCMLog, SLOT(slot_addLog(QString, QColor)));
	connect(m_pButAddConfig, SIGNAL(clicked()), this, SLOT(slot_butNewConfig()));

	//add config button 
	m_pAddConfigDlg = new QDialog();
	m_pAddConfig_Layout = new QVBoxLayout();
	m_pAddConfigDlg->setLayout(m_pAddConfig_Layout);

	m_pAddConfig_LineEdit = new QLineEdit();
	m_pAddConfig_But = new QPushButton(tr("add config"));
	m_pAddConfig_Layout->addWidget(m_pAddConfig_But);
	connect(m_pConfigSelect, SIGNAL(clicked()), this, SLOT(slot_butSelectConfig()));
	
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
void dtCCMTest::setConfigName(QString strName) {
	m_strConfigName = strName;
	m_labConfigName->setText(m_strConfigName);
}
QString dtCCMTest::getConfigName() {
	return m_strConfigName;
}
void dtCCMTest::createView() {
	//head
	setConfigName(getConfigNameFromDB(m_configDatabase));

	//body
	addDockWidget(Qt::BottomDockWidgetArea, m_pCCMLog);

	CCMConnectStatusBar *status = new CCMConnectStatusBar();
	connect(status, SIGNAL(sig_statuschange(int)), this, SLOT(slot_connectStatus(int)));
	status->start();

	QHBoxLayout *hlayout = new QHBoxLayout;
	m_pLabStatus->setFixedSize(30, 30);
	hlayout->addWidget(m_pLabStatus);
	hlayout->addWidget(m_pConfigSelect);
	hlayout->addWidget(m_labConfigName,5);
	
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

//Database
int dtCCMTest::connectConfigDatabase() {
	m_configDatabase = QSqlDatabase::addDatabase("QSQLITE", "configquery");
	m_configDatabase.setDatabaseName(QDir::currentPath() + "/configDatabase");
	if (!m_configDatabase.open()) {
		emit sgl_addLog("config database connect fail!");
		QSqlDatabase::removeDatabase("configquery");
		return -1;
	}
	else {
		emit sgl_addLog("config database connect success!", QColor(0, 255, 0));
	}

	bool bExists = false;
	QStringList list = getConfigList();
	for each (QString var in list)
	{
		if (var == "ACTIVECONFIG") {
			bExists = true;
			break;
		}
	}
	if (!bExists) {
		QSqlQuery query(m_configDatabase);
		query.prepare("create table [activeconfig] (name varchar(1,20) not null primary key)");
		if (!query.exec()) {
			emit sgl_addLog(query.lastError().text());
			return query.lastError().number();
		}
	}

	return 0;
}
QStringList dtCCMTest::getConfigList(QString DatabaseType) {
	QStringList list;
	QSqlQuery query(m_configDatabase);
	query.prepare("select name from SQLITE_MASTER where type='table'");
	query.exec();
	while (query.next()) {
		if(query.value(0).toString().toUpper().trimmed()=="ACTIVECONFIG")
			continue;
		list.append(query.value(0).toString().toUpper().trimmed());
	}
	return list;
}
QString dtCCMTest::getConfigNameFromDB(QSqlDatabase &database,QString DatabaseType) {
	QString str;
	QSqlQuery query(database);
	query.prepare("select name from activeconfig where 1");
	query.exec();
	while (query.next()) {
		str=query.value(0).toString().toUpper().trimmed();
	}

	//if (str.isEmpty())
	//	return "";
	return str;
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
	if (getConfigNameFromDB(m_configDatabase).isEmpty()) {
		QMessageBox::warning(this, tr("error"), tr("active config is empty"));
		return;
	}

	m_pConfigDlg->exec();
	m_pConfigDlg->raise();
	m_pConfigDlg->activateWindow();
}
void dtCCMTest::slot_butPlay() {
	emit sgl_addLog("Play");
}
void dtCCMTest::slot_butSelectConfig() {
	m_pConfigSelectDlg->m_comboRule->clear();
	m_pConfigSelectDlg->m_comboRule->addItems(getConfigList());
	m_pConfigSelectDlg->exec();
}
void dtCCMTest::slot_butNewConfig_Add() {

	if (m_pAddConfig_LineEdit->text().isEmpty()|| m_pAddConfig_LineEdit->text().trimmed().isEmpty()) {
		QMessageBox::warning(m_pAddConfigDlg, "error", "name is empty!");
		return;
	}

	QSqlQuery query(m_configDatabase);
	query.exec("select name from SQLITE_MASTER where type='table'");
	while (query.next()) {
		QString str = query.value(0).toString();
		if (query.value(0).toString().toUpper().trimmed() == m_pAddConfig_LineEdit->text().toUpper().trimmed()) {
			QMessageBox::warning(m_pAddConfigDlg, "error", "name already exists!");
			return ;
		}
	}

	query.prepare("create table [" + m_pAddConfig_LineEdit->text().toUpper().trimmed() + "] (class varchar(1,20) not null primary key,data text(1,10000) not null); ");
	if (!query.exec()) {
		emit sgl_addLog("sql executed fail!",QColor(255,0,0));
	}

	m_pAddConfig_LineEdit->clear();
	m_pAddConfigDlg->close();
}


void dtCCMTest::closeEvent(QCloseEvent *event) {
	QSettings settings("Software Inc.", "Icon Editor");
	settings.beginGroup("mainWindow");
	settings.setValue("geometry", saveGeometry());
	settings.setValue("state", saveState());
	settings.endGroup();
}