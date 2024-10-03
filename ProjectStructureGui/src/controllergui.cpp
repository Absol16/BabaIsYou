#include "controllergui.h"
#include <QApplication>


ControllerGui::ControllerGui(QApplication* app)
{
    this->application = app;
    int level = 0;
    this->facade = Level(level);
}

void ControllerGui::start()
{
    MainWindow mainWindow(&facade);
    mainWindow.show();
    application->exec();
}

