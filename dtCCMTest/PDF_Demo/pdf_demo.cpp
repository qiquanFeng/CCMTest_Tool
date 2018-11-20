#include "pdf_demo.h"
#include "QLayout"
#include "QFileDialog"
//#include "./poppler/include/poppler.h"

#include <QUrl>
#include <QDesktopServices>

using namespace cv;
using namespace std;
//using namespace Poppler;

PDF_Demo::PDF_Demo(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	createMenu();
	createView();
}

PDF_Demo::~PDF_Demo()
{

}

void PDF_Demo::createMenu() {
	QMenu *menuFile = new QMenu(tr("File"));
	QAction *actionOpen = menuFile->addAction("LoadImage_Left");
	QAction *actionOpen2 = menuFile->addAction("LoadImage_Right");
	QAction *actionClose = menuFile->addAction(tr("close"));

	QMenu *menuTool = new QMenu(tr("Tool"));
	QAction *actionCalibration = menuTool->addAction(tr("calibration"));
	QAction *actionDualCalibration = menuTool->addAction(tr("dual calibration"));

	QMenu *menuHelp = new QMenu(tr("Help"));
	QAction *actionHelp = menuHelp->addAction(tr("help"));

	menuBar()->addMenu(menuFile);
	menuBar()->addMenu(menuTool);
	menuBar()->addMenu(menuHelp);

	connect(actionOpen, SIGNAL(triggered(bool)), this, SLOT(slot_LoadLeftImgage(bool)));
	connect(actionOpen2, SIGNAL(triggered(bool)), this, SLOT(slot_LoadRightImgage(bool)));
	connect(actionCalibration, SIGNAL(triggered(bool)), this, SLOT(slot_calibration(bool)));
}
void PDF_Demo::createView() {
	QHBoxLayout *hLayout = new QHBoxLayout();
	wid_list = new WidImageList();
	wid_list->setHorizontalHeaderLabels(QStringList() << "Image");
	wid_list->setObjectName("tab");
	connect(wid_list, SIGNAL(cellDoubleClicked(int,int)), \
		this,SLOT(slot_showImage(int,int)));
	
	lab_MainViewLeft = new QLabel();
	lab_MainViewRight = new QLabel();
	lab_MainViewLeft->setObjectName("imgview1");
	lab_MainViewRight->setObjectName("imgview2");
	lab_MainViewLeft->setScaledContents(true);
	lab_MainViewRight->setScaledContents(true);

	hLayout->addWidget(wid_list);
	hLayout->addWidget(lab_MainViewLeft,5);
	hLayout->addWidget(lab_MainViewRight,5);
	hLayout->setMargin(0);
	hLayout->setSpacing(0);
	centralWidget()->setLayout(hLayout);

	QFile file("./style.qss");
	if (!file.open(QIODevice::ReadOnly)) {
		QMessageBox::warning(this, "Error", "style.qss read fail!");
		return;
	}
	QString strStyle=QString(file.readAll());
	setStyleSheet(strStyle);
	file.close();
}
void PDF_Demo::slot_LoadLeftImgage(bool bStatus) {
	QStringList filelist=QFileDialog::getOpenFileNames(this, tr("select files"), "", "all files(*.bmp;*.jpg;*.tif;*.png)\nraw file(*.raw)");
	m_Mats[0].clear();
	for each (QString var in filelist){
		m_Mats[0].push_back(imread(var.toLatin1().data()));
	}
	wid_list->addPair(m_Mats);
}
void PDF_Demo::slot_LoadRightImgage(bool bStatus) {
	QStringList filelist = QFileDialog::getOpenFileNames(this, tr("select files"), "", "all files(*.bmp;*.jpg;*.tif;*.png)\nraw file(*.raw)");
	m_Mats[1].clear();
	for each (QString var in filelist) {
		m_Mats[1].push_back(imread(var.toLatin1().data()));
	}
	wid_list->addPair(m_Mats);

}
void PDF_Demo::slot_showImage(int index, int col) {
	cv::Mat mat;
	if (m_Mats[0].size() > index) {
		cv::cvtColor(m_Mats[0][index], mat, COLOR_BGR2RGB);
		lab_MainViewLeft->setPixmap(QPixmap::fromImage(\
			QImage(mat.data, mat.cols, mat.rows, mat.step, QImage::Format_RGB888).scaled(lab_MainViewLeft->size())));
	}
	else {
		lab_MainViewLeft->clear();
	}
	if (m_Mats[1].size() > index) {
		cv::cvtColor(m_Mats[1][index], mat, COLOR_BGR2RGB);
		lab_MainViewRight->setPixmap(QPixmap::fromImage(\
			QImage(mat.data, mat.cols, mat.rows, mat.step, QImage::Format_RGB888).scaled(lab_MainViewRight->size())));
	}
	else {
		lab_MainViewRight->clear();
	}
}
void PDF_Demo::slot_calibration(bool bStatus) {
	
	if (m_Mats[0].size() > wid_list->currentRow()){
		Mat mat = m_Mats[0][wid_list->currentRow()];
		vector<Point2f> pointBuf;
		bool found=findChessboardCorners(mat, Size(9, 6), pointBuf);
		if (found) {
			Mat viewGray;
			cvtColor(mat, viewGray, COLOR_BGR2GRAY);
			cornerSubPix(viewGray, pointBuf, Size(9, 6),
				Size(-1, -1), TermCriteria(TermCriteria::EPS + TermCriteria::COUNT, 30, 0.1));
		}
		drawChessboardCorners(mat, Size(9, 6), Mat(pointBuf), found);
	}

	if (m_Mats[1].size() > wid_list->currentRow()) {
		Mat mat = m_Mats[1][wid_list->currentRow()];
		vector<Point2f> pointBuf;
		bool found = findChessboardCorners(mat, Size(9, 6), pointBuf);
		if (found) {
			Mat viewGray;
			cvtColor(mat, viewGray, COLOR_BGR2GRAY);
			cornerSubPix(viewGray, pointBuf, Size(11, 11),
				Size(-1, -1), TermCriteria(TermCriteria::EPS + TermCriteria::COUNT, 30, 0.1));
		}
		drawChessboardCorners(mat, Size(9, 6), Mat(pointBuf), found);
	}

	slot_showImage(wid_list->currentRow(), wid_list->currentColumn());

}
void PDF_Demo::slot_test(int x,int y) {
	//QMessageBox::warning(this, "test", QString::number(x));
}