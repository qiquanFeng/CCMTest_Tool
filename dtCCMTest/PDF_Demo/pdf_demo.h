#ifndef PDF_DEMO_H
#define PDF_DEMO_H

#include <QtWidgets/QMainWindow>
#include "ui_pdf_demo.h"
#include "opencv.hpp"
#include "widimagelist.h"

#ifdef _DEBUG
#pragma comment(lib,"opencv_world330d.lib")
#else
#pragma comment(lib,"opencv_world330.lib")
#endif
#include <QLabel>
#include <QAction>
#include <QResizeEvent>
#include <QMessageBox>

class PDF_Demo : public QMainWindow
{
	Q_OBJECT

public:
	PDF_Demo(QWidget *parent = 0);
	~PDF_Demo();
	
	WidImageList *wid_list;
	QLabel *lab_MainViewLeft;
	QLabel *lab_MainViewRight;
	std::vector<cv::Mat> m_Mats[2];
	int openCount = 0;
	void createMenu();
	void createView();

	public slots:
	void slot_LoadLeftImgage(bool);
	void slot_LoadRightImgage(bool);
	void slot_calibration(bool);
	void slot_showImage(int,int);
	void slot_test(int,int);

protected:
	//virtual void resizeEvent(QResizeEvent *event);

private:
	Ui::PDF_DemoClass ui;
};

#endif // PDF_DEMO_H
