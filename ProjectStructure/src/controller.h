#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "level.h"
#include "view.h"

/**
 * @brief The Controller class is responsible for controlling the game flow and managing the interactions between
 * the Level class and the View class.
 */
class Controller {

private:
    Level facade; /**< The facade object provides a simplified interface to the underlying game state. */
    View view; /**< The view object manages the user interface for the game. */

public:

    /**
     * @brief Constructs a new Controller object.
     */
    Controller();

    /**
     * @brief Starts the game by initializing the Level and View objects and running the game loop.
     */
    void start();

};

#endif // CONTROLLER_H
