#include "StatuesMainWindow.h"
#include "Service.h"
#include "Tests.h"
#include "Settings.h"
#include "FileRepository.h"
#include "SqlRepository.h"
#include "BaseRepository.h"
#include <QtWidgets/QApplication>
#include <memory>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	Settings settings { "settings.properties" };

	std::unique_ptr<BaseRepository> repository { settings.SetConfiguration() };
	Service<BaseRepository> service { *repository };
	
	StatuesMainWindow mainWindow { service };
	mainWindow.show();

	return a.exec();
}
