#include <iostream>
#include <QApplication>
#include "controllergui.h"

int main(int argc, char* argv[])
{
    QApplication application(argc, argv);
    ControllerGui cntrl(&application);
    cntrl.start();
    return 0;
}

