#ifndef CONTROLLERGUI_H
#define CONTROLLERGUI_H
#include "level.h"
#include "mainwindow.h"

class ControllerGui{
private:
    QApplication* application;
    Level facade; /**< The facade object provides a simplified interface to the underlying game state. */

public:
    /**
     * @brief Constructs a new Controller object.
     */
    ControllerGui(QApplication* app);

    /**
     * @brief Starts the game by initializing the Level and View objects and running the game loop.
     */
    void start();

};

#endif // CONTROLLERGUI_H
