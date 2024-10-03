#ifndef GAMEGRID_H
#define GAMEGRID_H

#include <QPushButton>
#include "qwidget.h"
#include "observer.h"
#include "level.h"
#include "qstackedlayout.h"
#include "objectgame.h"
#include "QGridLayout"

class GameGrid : public QWidget, public Observer {

    Q_OBJECT

public:
    /**
     * @brief Constructor for the GameGrid class.
     * @param model A pointer to an object of the Level class.
     * @param parent A pointer to the parent widget of the GameGrid class.
     *               Its default value is nullptr.
     */
    GameGrid(Level *model, QWidget* parent = nullptr);

    /**
     * @brief Initializes the game objects and places them on the grid.
     */
    void setObjects();

    /**
     * @brief Updates the game's user interface.
     */
    void updateUi() override;

    /**
     * @brief Displays the current game.
     */
    void showGame();

    /**
     * @brief Displays the game that has been saved.
     */
    void showSaveGame();

    /**
     * @brief Displays the game-over screen.
     */
    void gameOver();

    /**
     * @brief Quits the Game.
     */
    void quit();

    /**
     * @brief Restarts the game from the beginning.
     */
    void startAgain();

private:
    QGridLayout* gridLayout;
    Level* model;
    QWidget* gameOverWidget;

    /**
     * @brief Places a game object on the grid at a specified position.
     * @param objectGame The game object to place (ObjectGame class object).
     * @param row The row of the grid where to place the object.
     * @param col The column of the grid where to place the object.
     */
    void placeObject(ObjectGame objectGame, int row, int col);

    /**
     * @brief Clears the grid by removing all objects from it.
     */
    void clearGrid();

    /**
     * @brief Applies a button style with a specified background color.
     * @param button The button to apply the style to (QPushButton).
     * @param backgroundColor The background color for the button (QString).
     */
    void applyButtonStyle(QPushButton* button, const QString& backgroundColor);
};

#endif // GAMEGRID_H
