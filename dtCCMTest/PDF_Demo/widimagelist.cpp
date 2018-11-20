#include "widimagelist.h"
#include <QStringList>

DualLabel::DualLabel(QWidget *parent)
	: QWidget(parent) {
	QHBoxLayout *hlayout = new QHBoxLayout();
	QLabel *lab1 = new QLabel("left");
	QLabel *lab2 = new QLabel("right");
	lab1->setFixedSize(80, 50);
	lab2->setFixedSize(80, 50);
	hlayout->addWidget(lab1);
	hlayout->addWidget(lab2);
	hlayout->setSpacing(0);
	setLayout(hlayout);
}
DualLabel::~DualLabel() {

}

WidImageList::WidImageList(QWidget *parent)
	: QTableWidget(parent),activeRow(0),activeCol(0)
{
	ui.setupUi(this);
	setColumnCount(1);
	horizontalHeader()->setStretchLastSection(true);
	setEditTriggers(QAbstractItemView::NoEditTriggers);
	setSelectionBehavior(QAbstractItemView::SelectRows);
	setSelectionMode(QAbstractItemView::NoSelection);
	
	horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
	verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
	//this->setSelectionModel()
	connect(this, SIGNAL(cellDoubleClicked(int, int)), this, SLOT(selectRowCol(int, int)));

}

WidImageList::~WidImageList()
{
	
}

int WidImageList::addPair(std::vector<cv::Mat> m_Mats[2]) {
	int maxrow = m_Mats[0].size() > m_Mats[1].size() ? m_Mats[0].size() : m_Mats[1].size();
	setRowCount(0);
	for (int i = 0; i < maxrow; i++)
	{
		QWidget *wid = new QWidget();
		QLabel *lab1 = new QLabel("");
		lab1->setFixedSize(80, 50);
		cv::Mat mat;
		if(m_Mats[0].size()>i){
			cv::cvtColor(m_Mats[0][i], mat, cv::COLOR_BGR2RGB);
			lab1->setPixmap(QPixmap::fromImage(QImage(mat.data,mat.cols,mat.rows,mat.step,QImage::Format_RGB888)).scaled(lab1->size()));
		}

		QLabel *lab2 = new QLabel("");
		lab2->setFixedSize(80, 50);
		if (m_Mats[1].size()>i) {
			cv::cvtColor(m_Mats[1][i], mat, cv::COLOR_BGR2RGB);
			lab2->setPixmap(QPixmap::fromImage(QImage(mat.data, mat.cols, mat.rows, mat.step, QImage::Format_RGB888)).scaled(lab1->size()));
		}
		
		QHBoxLayout *hLayout = new QHBoxLayout();
		hLayout->setSpacing(0);
		hLayout->setMargin(0);
		hLayout->setSpacing(0);
		hLayout->addWidget(lab1);
		hLayout->addWidget(lab2);
		wid->setLayout(hLayout);
		this->setRowCount(rowCount() + 1);
		setCellWidget(rowCount() - 1, 0, wid);
	}
	resizeRowsToContents();
	resizeColumnsToContents();
	setFixedWidth(columnWidth(0)+50);
	return 0;
}

void WidImageList::mousePressEvent(QMouseEvent *event) {
	QTableWidget::mousePressEvent(event);
}

void WidImageList::selectRowCol(int row, int col) {
	cellWidget(activeRow, activeCol)->setStyleSheet("");

	this->resizeRowsToContents();
	this->setRowHeight(row, 70);
	cellWidget(row, col)->setStyleSheet("background-color:lightgreen;border:2px solid black;");
	activeRow = row; activeCol = col;
}

void WidImageList::resizeEvent(QResizeEvent *event) {
	resizeColumnsToContents();
}