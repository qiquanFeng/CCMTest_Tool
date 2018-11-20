#ifndef WIDIMAGELIST_H
#define WIDIMAGELIST_H

#include <QWidget>
#include "ui_widimagelist.h"
#include "opencv.hpp"
#include "QVBoxLayout"
#include <QTableWidget>
#include <QLabel>

class DualLabel : public QWidget
{
	Q_OBJECT

public:
	DualLabel(QWidget *parent = 0);
	~DualLabel();

};


class WidImageList : public QTableWidget
{
	Q_OBJECT

public:
	WidImageList(QWidget *parent = 0);
	~WidImageList();

	int addPair(std::vector<cv::Mat> m_Mats[2]);

	void mousePressEvent(QMouseEvent *event);
	public slots:
	void selectRowCol(int, int);
protected:
	void resizeEvent(QResizeEvent *event);
private:
	Ui::WidImageList ui;

	int activeRow;
	int activeCol;
};

#endif // WIDIMAGELIST_H
