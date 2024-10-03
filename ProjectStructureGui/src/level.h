#ifndef LEVEL_H
#define LEVEL_H
#include "board.h"
#include "fileloader.h"
#include "Observable.h"
#include <vector>

/**
 * The `Level` class represents a game level with a board and game objects.
 * It inherits from the `Observable` class and can notify observers of changes.
 */
class Level : public Observable
{
private:
    int level; // The level number
    FileLoader file; // The file loader for loading level files
    bool isSave; // A flag indicating if the game has been saved
public:
    Board board; // The game board
    /**
     * Constructs a new `Level` object with the given level number.
     * @param l The level number to load.
     */
    Level(int l);
    /**
     * Default constructor for the `Level` class.
     */
    Level() {
        this->level = 0;
    }
    /**
     * Restarts the current level by reloading the level file and resetting the board and game objects.
     */
    void restart();
    /**
     * Starts the level by initializing the board and game objects.
     */
    void start();
    void startUi();

    /**
     * Returns the game board.
     * @return A reference to the game board.
     */
    Board& getBoard();
    /**
     * Returns the level number.
     * @return The level number.
     */
    int getLevel() const;
    /**
     * Increases the level number by 1.
     */
    void upLevel();
    /**
     * Sets the `isSave` flag to true, indicating that the game has been saved.
     */
    void IsSave();
    /**
     * Moves the player object in the given direction on the game board.
     * @param d The direction to move the player object.
     */
    void movement(Direction d);
    void movementUi(Direction d);

    /**
     * Initializes the game board by loading the level file and creating game objects.
     */
    void initBoard();
    void setLevel(int l);
};

#endif // LEVEL_H
