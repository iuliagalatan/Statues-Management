#pragma once
#include <QtWidgets/QMainWindow>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QWidget>
#include <qradiobutton.h>
#include <QFileDialog>
#include <QShortcut>
#include "Service.h"
#include <cstring>
#include "MyListTableModel.h"
#include <iostream>
#include <vector>

#include "MylistWidget.h"
class StatuesMainWindow : public QMainWindow
{
	Q_OBJECT

private:
	Service<BaseRepository>& service;
	bool modeA = false;
	bool modeB = false;
	bool csv_type = false;
	bool html_type = false;
	bool filtered = false;
	std::string powerwordname;
	std::string material;
	int age = 0;
	std::string corporealform;
	int position = -1;
	bool isMemoryRepository;
	// interface fields
	QWidget* centralWidget;
	QVBoxLayout* mainVerticalLayout;
	QHBoxLayout* listLocationHorizontalLayout;
	QFormLayout* listLocationFormLayout;
	QLineEdit* fileLocationEdit;
	QLineEdit* listLocationEdit;
	QRadioButton* InMemoryButton;
	QVBoxLayout* browseButtonVerticalLayout;
	QPushButton* fileLocationButton;
	QPushButton* modeButton;
	QPushButton* myListLocationButton;
	QHBoxLayout* mainHorizontalLayout;
	QVBoxLayout* leftVerticalLayout;
	QFormLayout* formLayout;
	QLabel* allStatuesLabel;
	QListWidget* allStatuesListWidget;
	QLineEdit* powerwordEdit;
	QLineEdit* materialEdit;
	QLineEdit* ageEdit;
	QLineEdit* corporealEdit;
	QGridLayout* gridLayout;
	QPushButton* deleteButton;
	QPushButton* filterButton;
	QPushButton* redoButton;
	QPushButton* undoButton;
	QPushButton* addButton;
	QPushButton* updateButton;
	QPushButton* saveButton;
	QPushButton* toMyList;
	QVBoxLayout* rightVerticalLayout;
	QListWidget* myListWidget;
	QPushButton* openAppButton;
	QHBoxLayout* horizontalNextOpenLayout;
	QLabel* myStatuesLabel;
	QHBoxLayout* launchHorizontalLayout;
	QPushButton* launchButton;
	QPushButton* nextButton;
	QMenuBar* menuBar;
	QToolBar* mainToolBar;
	QStatusBar* statusBar;
	QLabel* statusLabel;
	QAction* chartAction;

	QShortcut* undoshortcut; 
	QShortcut* redoshortcut; 
	QString filteredText;

	MylistWidget* mylistwidget;

	//MylistTableView* mylistTableView;
public:
	StatuesMainWindow(Service<BaseRepository>& service, QWidget* parent = 0);

	void ConnectSignalsAndSlots();

	void List(std::vector<TElems>);
	void ListAll();
	void Next(int);
	void SaveStatue(std::string);
	void filterAfterMaterialAndAge(std::string material, int age);
	
	void ListMyList();
	bool CheckFields();
	bool GetFields(std::string& powerwordname, std::string& material, int& age, std::string& corporealform);

	void AddStatueUI();
	void UpdateStatueUI();
	void DeleteStatueUI();
	void SaveStatueUI();

	void BuildGui();
public slots:
	void ModeButton();
	void ChooseFileLocation();
	void ChooseMyListLocation();
	void ChooseMemoryRepository();
	void OnStatueSelectionChanged();
	void OnSaveButtonClicked();
	void OnChartActionTriggered();
	void NextInMyList();
	void OpenInApp();
	void ListUI();
	void undoGUI();
	void redoGUI();
	void execMyListWidget();
};
