#include "MylistWidget.h"

#include <QtWidgets>

MylistWidget::MylistWidget(MyListTableModel* model, QWidget *parent)
	: QWidget(parent), model( model ) 
{
	ui.setupUi(this);
	
	ui.MyListTableView->setModel(model);
}

MylistWidget::~MylistWidget()
{
}
