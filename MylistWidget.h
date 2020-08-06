#pragma once

#include <QWidget>
#include "ui_MylistWidget.h"
#include "MyListTableModel.h"

class MylistWidget : public QWidget
{
	Q_OBJECT

public:
	MylistWidget(MyListTableModel* model ,QWidget *parent = Q_NULLPTR);
	~MylistWidget();

private:
	Ui::MylistWidget ui;
	MyListTableModel* model;
};
