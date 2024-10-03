#ifndef VIEW_H
#define VIEW_H
#include "level.h"
#include "Enum.h"
#include "Observer.h"
#include <iostream>
#include <iomanip>
#include <cstring>

using namespace Enum;
using namespace std;

class View : public Observer
{

public:
    /**
     * @brief Constructs a View object with a reference to a Level object.
     *
     * @param m A reference to the Level object to be used by the View.
     */
    View( Level & m);
    /**
     * @brief Default constructor for the View class.
     */
    View(){};
    /**
     * @brief Displays the current state of the board.
     */
    void displayBoard();
    /**
     * @brief Displays a message indicating that the player has won the game.
     */
    void displayWin(string text);
    /**
     * @brief Asks the player for a movement direction.
     *
     * @return The Direction entered by the player.
     */
    Direction askMovement();
    /**
     * @brief Asks the player if they want to save the current game.
     *
     * @return true if the player wants to save the game, false otherwise.
     */
    bool askSaveGame();
    /**
     * @brief Updates the View to reflect changes in the Level object.
     */
    void update() override;

private:
    Level *model;
    /**
     * @brief Returns the symbol associated with a given Material.
     *
     * @param mat The Material to get the symbol for.
     * @return The symbol associated with the given Material.
     */
    char getSymbol(Material mat);
};

#endif // VIEW_H
