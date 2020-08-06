#include "StatuesMainWindow.h"
#include "Validator.h"
#include "RepositoryException.h"
#include <iostream>
#include <string>
#include <QMessageBox>
#include <QHBoxLayout>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include <map>

QT_CHARTS_USE_NAMESPACE

StatuesMainWindow::StatuesMainWindow(Service<BaseRepository>& service, QWidget *parent)
	: QMainWindow(parent), service {service}
{
	BuildGui();
	ConnectSignalsAndSlots();

}

void StatuesMainWindow::ConnectSignalsAndSlots()
{
//	connect(fileLocationButton, SIGNAL(clicked()), this, SLOT(ChooseFileLocation));
	connect(fileLocationButton, &QPushButton::clicked, this,  &StatuesMainWindow::ChooseFileLocation);
	connect(myListLocationButton, &QPushButton::clicked, this, &StatuesMainWindow::ChooseMyListLocation);
	connect(filterButton, &QPushButton::clicked, this, &StatuesMainWindow::ListUI);
	connect(updateButton, &QPushButton::clicked, this, &StatuesMainWindow::UpdateStatueUI);
	connect(addButton, &QPushButton::clicked, this, &StatuesMainWindow::AddStatueUI);
	connect(deleteButton, &QPushButton::clicked, this, &StatuesMainWindow::DeleteStatueUI);
	connect(allStatuesListWidget, &QListWidget::itemSelectionChanged, this, &StatuesMainWindow::OnStatueSelectionChanged);	
	connect(chartAction, &QAction::triggered, this, &StatuesMainWindow::OnChartActionTriggered);
	connect(saveButton, &QPushButton::clicked, this, &StatuesMainWindow::OnSaveButtonClicked);
	connect(InMemoryButton, &QPushButton::clicked, this, &StatuesMainWindow::ChooseMemoryRepository);
	connect(nextButton, &QPushButton::clicked, this, &StatuesMainWindow::NextInMyList);
	connect(openAppButton, &QPushButton::clicked, this, &StatuesMainWindow::OpenInApp);
	connect(modeButton, &QPushButton::clicked, this, &StatuesMainWindow::ModeButton);
	connect(undoButton, &QPushButton::clicked, this, &StatuesMainWindow::undoGUI);
	connect(redoButton, &QPushButton::clicked, this, &StatuesMainWindow::redoGUI);
	connect(undoshortcut, &QShortcut::activated, this, &StatuesMainWindow::undoGUI);
	connect(redoshortcut, &QShortcut::activated, this, &StatuesMainWindow::redoGUI);
	connect(toMyList, &QPushButton::clicked, this, &StatuesMainWindow::execMyListWidget);


}

void StatuesMainWindow::BuildGui()
{
	setWindowTitle(tr("Statues"));
	setWindowIcon(QIcon("statue-icon.png"));
	resize(900, 753);
	centralWidget = new QWidget(this);
	
	

	listLocationFormLayout = new QFormLayout();
	InMemoryButton = new QRadioButton();
	fileLocationEdit = new QLineEdit();
	listLocationEdit = new QLineEdit();
	QLabel* fileLocationLabel = new QLabel(tr("File location:         "));
	listLocationFormLayout->addRow(fileLocationLabel, fileLocationEdit);
	QLabel* myListLocationLabel = new QLabel(tr("My list location:   "));
	listLocationFormLayout->addRow(myListLocationLabel, listLocationEdit);
	

	listLocationHorizontalLayout = new QHBoxLayout();
	listLocationHorizontalLayout->addLayout(listLocationFormLayout);

	fileLocationButton = new QPushButton();
	fileLocationButton->setText(tr("Browse"));
	browseButtonVerticalLayout = new QVBoxLayout();
	browseButtonVerticalLayout->addWidget(fileLocationButton);

	myListLocationButton = new QPushButton();
	myListLocationButton->setText(tr("Browse"));
	browseButtonVerticalLayout->addWidget(myListLocationButton);
	browseButtonVerticalLayout->setSpacing(3);
	listLocationHorizontalLayout->addLayout(browseButtonVerticalLayout);

	mainVerticalLayout = new QVBoxLayout(centralWidget);
	if (service.RepositoryType() == BaseRepository::InMemoryRepo)
	{
		fileLocationEdit->setEnabled(false);
		fileLocationButton->setEnabled(false);
	}
	mainVerticalLayout->addLayout(listLocationHorizontalLayout);
	
	modeButton = new QPushButton("mode A");
	mainVerticalLayout->addWidget(modeButton);


	allStatuesLabel = new QLabel(tr("All Statues"));
	allStatuesListWidget = new QListWidget();
	powerwordEdit = new QLineEdit();
	materialEdit = new QLineEdit();
	ageEdit = new QLineEdit();
	corporealEdit = new QLineEdit();

	formLayout = new QFormLayout();
	formLayout->addRow("", allStatuesLabel);
	formLayout->addRow("", allStatuesListWidget);
	formLayout->addRow(tr("Powerword name : "), powerwordEdit);
	formLayout->addRow(tr("Material:"), materialEdit);
	formLayout->addRow(tr("Age:"), ageEdit);
	formLayout->addRow(tr("Corporeal form:"), corporealEdit);

	leftVerticalLayout = new QVBoxLayout();
	leftVerticalLayout->addLayout(formLayout);

	gridLayout = new QGridLayout();

	deleteButton = new QPushButton(tr("&Delete"), centralWidget);
	filterButton = new QPushButton(tr("&View All"), centralWidget);
	undoButton = new QPushButton(tr("&Undo"), centralWidget);
	redoButton = new QPushButton(tr("&Redo"), centralWidget);
	addButton = new QPushButton(tr("&Add"), centralWidget);
	updateButton = new QPushButton(tr("&Update"), centralWidget);

	gridLayout->addWidget(deleteButton, 0, 1, 1, 1);
	gridLayout->addWidget(filterButton, 1, 0, 1, 1);
	gridLayout->addWidget(undoButton, 1, 1, 1, 1);
	gridLayout->addWidget(redoButton, 1, 2, 1, 1);

	gridLayout->addWidget(addButton, 0, 0, 1, 1);
	gridLayout->addWidget(updateButton, 0, 2, 1, 1);
	leftVerticalLayout->addLayout(gridLayout);

	mainHorizontalLayout = new QHBoxLayout();
	mainHorizontalLayout->addLayout(leftVerticalLayout);
	saveButton = new QPushButton(">");
	toMyList = new QPushButton("Mylist");
	mainHorizontalLayout->addWidget(toMyList);
	mainHorizontalLayout->addWidget(saveButton);

	/**/rightVerticalLayout = new QVBoxLayout();
	myStatuesLabel = new QLabel(tr("My Statues"));
	rightVerticalLayout->addWidget(myStatuesLabel);

	myListWidget = new QListWidget();
	rightVerticalLayout->addWidget(myListWidget);

	nextButton = new QPushButton("Next");
	openAppButton = new QPushButton("Open");

	horizontalNextOpenLayout = new QHBoxLayout();
	horizontalNextOpenLayout->addWidget(nextButton);
	horizontalNextOpenLayout->addWidget(openAppButton);

	rightVerticalLayout->addLayout(horizontalNextOpenLayout);
	/*
	*/
	mainHorizontalLayout->addLayout(rightVerticalLayout);
	mainVerticalLayout->addLayout(mainHorizontalLayout);



	setCentralWidget(centralWidget);

	menuBar = new QMenuBar(this);
	
	chartAction = new QAction(tr("Bar Chart"), this);
	menuBar->addAction(chartAction);
	setMenuBar(menuBar);
	mainToolBar = new QToolBar(this);
	addToolBar(Qt::TopToolBarArea, mainToolBar);
	statusBar = new QStatusBar(this);
	setStatusBar(statusBar);
	undoshortcut = new QShortcut(QKeySequence("Ctrl+Z"), undoButton);
	redoshortcut = new QShortcut(QKeySequence("Ctrl+Y"), redoButton);
	QString statusText;
	switch (service.RepositoryType())
	{
	case BaseRepository::InMemoryRepo:
		statusText = "In-Memory repository";
		break;

	case BaseRepository::FileRepo:
		statusText = "File backed repository";
		filteredText = "Text Files (*.txt);;All Files (*.*)";
		break;

	case BaseRepository::CsvRepo:
		statusText = "Csv backed repository";
		filteredText = "CSV Files (*.csv);;All Files (*.*)";
		break;

	case BaseRepository::SqlRepo:
		statusText = "Sql backed repository";
		filteredText = "SQLite Files (*.sqlite *.db);;All Files (*.*)";
		break;

	case BaseRepository::HtmlRepo:
		statusText = "Html repository";
		filteredText =  "HTML Files (*.html *.htm);;All Files (*.*)";
		break;
	default:
		break;
	}
	statusLabel = new QLabel(statusText, this);
	statusBar->addWidget(statusLabel);
}

void StatuesMainWindow::SaveStatueUI()
{
	if (!modeB)
		return;
	std::string powerWordName = powerwordEdit->text().toStdString();
	this->SaveStatue(powerWordName);
	ListMyList();
}

void StatuesMainWindow::ModeButton()
{
	if (modeA == false)
	{
		modeB = false;
		modeA = true;
		modeButton->setText("mode B");

	}
	else
	{
		if (modeB == false)
		{
			modeB = true;
			modeA = false;
			modeButton->setText("mode A");
		}
	}
}

void StatuesMainWindow::ChooseMemoryRepository()
{
	ListMyList();
}

void StatuesMainWindow::ChooseFileLocation()
{
	QString filePath = QFileDialog::getOpenFileName(this,
		tr("Choose Database File"), QDir::currentPath(), filteredText);
	if (filePath == QString::null)
		return;
	fileLocationEdit->setText(filePath);
	service.SetFilePath(filePath.toStdString());
	
	ListUI();
}


void StatuesMainWindow::ChooseMyListLocation()
{
	QString filteredText = "SQLite Files (*.sqlite *.db);;Text Files (*.txt);;CSV Files (*.csv);;HTML Files (*.html *.htm);;All Files (*.*)";
	QString file = QFileDialog::getOpenFileName(this,
		tr("Choose Database File"), QDir::currentPath(), filteredText);
	
	listLocationEdit->setText(file);

	std::string filePath = file.toStdString();
	if (filePath == "")
	{
		this->service.setSaveList("memory");
		
	}
	
	if (filePath.find(".txt") != std::string::npos)
	{
		//sql_type = true;
		this->service.setSaveList("txt");
	}

	if (filePath.find(".csv") != std::string::npos)
	{
		csv_type = true;
		this->service.setSaveList("csv");
	}
	if (filePath.find(".html") != std::string::npos)
	{
		html_type = true;
		this->service.setSaveList("html");
	}

	if (filePath.find(".sqlite") != std::string::npos)
	{
		//sql_type = true;
		this->service.setSaveList("sql");
	}

	this->service.setSaveListPath(filePath);

	ListMyList();
}

void StatuesMainWindow::OnStatueSelectionChanged()
{
	powerwordname =  allStatuesListWidget->currentItem()->text().toStdString();
	TElems statue = service.GetStatueByPowerWordName(powerwordname);

	powerwordEdit->setText(QString::fromStdString(statue.GetPowerWordName()));
	materialEdit->setText(QString::fromStdString(statue.GetMaterial()));
	ageEdit->setText(QString::number(statue.GetAge()));
	corporealEdit->setText(QString::fromStdString(statue.GetCorporealForm()));
}


void StatuesMainWindow::OnChartActionTriggered()
{
	QDialog dlg;
	dlg.setWindowTitle("Number of Statues by materials");
	dlg.resize(500, 400);
	QBarSet* set0 = new QBarSet("Materials used");

	QBarSeries* series = new QBarSeries();
	series->append(set0);

	QChart* chart = new QChart();

	chart->addSeries(series);
	chart->setTitle("Statues Frequency");
	chart->setAnimationOptions(QChart::SeriesAnimations);

	QStringList categories;
	std::vector<TElems> toprint;
	try {
		 toprint = this->service.GetElementsVector();
	}
	catch (FileException ex)
	{
	}
	std::map<std::string, int> map;
	for (auto statue : toprint)
		map[statue.GetMaterial()]++;
	
	for (auto it = map.begin(); it != map.end(); ++it)
	{
		categories << QString::fromStdString(it->first);
		*set0 << it->second;
	}
	QBarCategoryAxis* axisX = new QBarCategoryAxis();
	axisX->append(categories);
	chart->addAxis(axisX, Qt::AlignBottom);
	series->attachAxis(axisX);

	QValueAxis* axisY = new QValueAxis();
	axisY->setRange(0, 5);
	chart->addAxis(axisY, Qt::AlignLeft);
	series->attachAxis(axisY);

	chart->legend()->setVisible(true);
	chart->legend()->setAlignment(Qt::AlignBottom);
	chart->legend()->setBorderColor(Qt::red);
	chart->legend()->resize(60, 50);
	chart->legend()->update();
	QChartView* chartView = new QChartView(chart);
	chartView->setRenderHint(QPainter::Antialiasing);
	
	QHBoxLayout* hLayout = new QHBoxLayout;
	hLayout->addWidget(chartView);

	dlg.setLayout(hLayout);
	dlg.exec();
}

void StatuesMainWindow::NextInMyList()
{
	if (!modeB)
		return;
	myListWidget->setFocus();
	
	if (position == myListWidget->count())
	{
		position = -1;
	}
	position++;
	this->myListWidget->setCurrentRow(position);
}

void StatuesMainWindow::OpenInApp()
{
	if (!modeB)
		return;
	this->service.openExternApp();
}

void StatuesMainWindow::ListUI()
{
	if (filterButton->text() == "Filter")
	{
		// remove all items
		allStatuesListWidget->clear();
		material = materialEdit->text().toStdString();
		bool ok;
		age = ageEdit->text().toInt(&ok, 10);

		if (!ok || material == "")
		{
			QMessageBox::critical(this, "Wrong Value!", "Age must be an integer value");
			filterButton->setText(tr(""));
			filterButton->setText(tr("View All"));
			return;
		}
		filterAfterMaterialAndAge(material, age);
		filterButton->setText(tr("View All"));
	}
	else
	{
		// remove all items
		filterButton->setText("Filter");
		ListAll();
	}
}

bool StatuesMainWindow::CheckFields()
{
	bool ok;
	age = ageEdit->text().toInt(&ok, 10);

	if (powerwordEdit->text() == "" || materialEdit->text() == ""
		|| ageEdit->text() == "" || corporealEdit->text() == "")
	{
		QMessageBox::critical(this, tr("Missing fields!"), tr("All fields must be filled!"));
		return false;
	}
	if (!ok)
	{
		QMessageBox::critical(this, "Wrong Value!", "Age must be an integer value");
		return false;
	}

	return true;
}

bool StatuesMainWindow::GetFields(std::string& powerwordname, std::string& material, int& age, std::string& corporealform)
{
	bool ok = CheckFields();
	if (!ok) return false;

	powerwordname = powerwordEdit->text().toStdString();
	material = materialEdit->text().toStdString();
	age = ageEdit->text().toInt(&ok, 10);
	corporealform = corporealEdit->text().toStdString();

	return true;
}

void StatuesMainWindow::AddStatueUI()
{
	if (!modeA)
		return;
	if (!GetFields(powerwordname, material, age, corporealform))
		return;

	try
	{
		this->service.AddStatueService(powerwordname, material, age, corporealform);
		ListAll();
	}
	catch (FileException& exception)
	{
		QMessageBox::critical(this, tr("File Exception!"), exception.what());
	}
	catch (DuplicateStatueException& exception)
	{
		QMessageBox::critical(this, tr("Duplicate Statue Exception!"), exception.what());
	}
	catch (StatueException& statueException)
	{
		std::cout << statueException.what() << '\n';
	}
	catch (...)
	{
		QMessageBox::critical(this, tr("Exception!"), tr("Runtime Exception!"));
	}
}

void StatuesMainWindow::UpdateStatueUI()
{
	if (!modeA)
		return;
	if (!GetFields(powerwordname, material, age, corporealform))
		return;

	this->service.UpdateStatueService(powerwordname, material, age, corporealform);
}

void StatuesMainWindow::DeleteStatueUI()
{
	if (!modeA)
		return;
	if (!GetFields(powerwordname, material, age, corporealform))
	{
		return;
	}
	this->service.DeleteStatueService(powerwordname);
	ListAll();
}

void StatuesMainWindow::ListAll()
{
	this->List(this->service.GetElementsVector());
}

void StatuesMainWindow::List(std::vector<TElems> toprint)
{
	allStatuesListWidget->clear();
	for (auto statue : toprint)
	{
		allStatuesListWidget->addItem(QString::fromStdString(statue.GetPowerWordName()));
	}
}

void StatuesMainWindow::Next(int position)
{
	if (!modeB)
		return;
	if (position >= this->service.GetSize())
		std::cout << "NO";
	else
	{
		Statue nextstatue = this->service.GetElement(position);
		std::cout << nextstatue.ToString() << '\n';
	}
}

void StatuesMainWindow::SaveStatue(std::string PowerWordName)
{
	if (!modeB)
		return;
	this->service.SaveStatue(PowerWordName);
}

void StatuesMainWindow::ListMyList()
{
	myListWidget->clear();
	std::vector<TElems> toprint = this->service.GetSavedElementsVector();
	for (auto statue : toprint)
	{
		myListWidget->addItem(QString::fromStdString(statue.GetPowerWordName()));
	}

//	this->service.openExternApp();
}

void StatuesMainWindow::filterAfterMaterialAndAge(std::string material, int age)
{
	if (!modeA)
		return;
	std::vector<TElems> toprint = this->service.GetFilteredList(material, age);
	
	this->List(toprint);
}


void StatuesMainWindow::OnSaveButtonClicked()
{
	if (!GetFields(powerwordname, material, age, corporealform))
		return;
	Statue statue = Statue(powerwordname, material, age, corporealform);
	SaveStatue(powerwordname);
	ListMyList();
}


void StatuesMainWindow::undoGUI()
{
	bool result = this->service.Undo();
	if (result == false)
	{
		QMessageBox msg;
		msg.setText("No more Undo's");
		msg.exec();
	}
	else
	{
		ListAll();
	}
}

void StatuesMainWindow::redoGUI()
{
	bool result = this->service.Redo();
	if (result == false)
	{
		QMessageBox msg;
		msg.setText("No more Redo's");
		msg.exec();
	}
	else
	{
		ListAll();
	}
}


void StatuesMainWindow::execMyListWidget()
{
	MyListTableModel* model = new MyListTableModel(this->service);

	QWidget* newwindow = new MylistWidget(model);
	
	newwindow->setUpdatesEnabled(true);newwindow->show();
	//this->mylistwidget->show();
	//this->hide();
}