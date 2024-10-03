#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include "objectgame.h"
#include "Enum.h"
#include "rules.h"
#include <memory>
#include <algorithm>
#include <set>
#include <iostream>

using namespace std;
using namespace block;

class Board {

    vector<std::vector<std::vector<ObjectGame>>> tabBoard; // game array that contains game objects
    vector<ObjectGame*> objectYou; // vector of "You" game objects
    vector<Rules> rule; // vector of game rules
    vector<ObjectGame*> subjectRule; // vector of game objects for rules
    vector<Material> aspectRule; // vector of aspects for rules

    /**
     * for a test
     * @brief testObjectYou
     * @param obj
     */
    friend void testObjectYou(Board & obj);

public:
    Board();
    /**
     * Getter method that returns the game array.
     * @return The game array.
     */
    vector<std::vector<std::vector<ObjectGame>>> getTabBoard();

    /**
     * for a test
     * @brief testObjectYou
     * @param obj
     */
    vector<ObjectGame*> testObjectYou(Board& obj){
        return obj.objectYou;
    }

    /**
     * Method that sets a game object in the game array at a certain position.
     * @param element The game object to set.
     * @param pos The position to set the object at.
     */
    void setTabGame(vector<ObjectGame> &element, Position& pos) ;

    /**
     * @brief setRule method is used to set a vector of Rules for the game board. The
     * @param r
     */
    void setRule(vector<Rules> r);

    /**
     * @brief getRule method is used to retrieve the vector of Rules set for the game board.
     * @return vector of Rules
     */
    vector<Rules> getRule();

    /**
     * @brief clearRule method that clear the rule.
     */
    void clearRule();

    /**
     * Method that checks if a position is inside the game array.
     * @param pos The position to check.
     * @return true if the position is inside the array, false otherwise.
     */
    bool isInside(const Position &pos);

    /**
     * Method that moves all game objects in a certain direction.
     * @param d The direction to move the game objects in.
     */
    void move(Direction d);

    /**
     * Method that checks if the player has won the game.
     * @return true if the player has won, false otherwise.
     */
    bool gameIsWin();

    /**
     * Method that checks if the player has lost the game.
     * @return true if the player has lost, false otherwise.
     */
    bool gameIsLoose();
    /**
     * Method that checks if any rules can be built from the current game state and adds them to the vector of rules.
     */
    void checkBuildRule();

private:
    /**
    * Method that changes the position of a game object in a certain direction.
    * @param d The direction to move the game object in.
    * @param pos The current position of the game object.
    */
    void changePositionObject(Direction d, const Position &pos);
    /**
     * Method that checks if a game object can be moved in a certain direction.
     * @param d The direction to move the game object in.
     * @return true if the game object can be moved, false otherwise.
     */
    bool canBeMoved(Direction d);

    /**
     * Method that adds a rule to the vector of rules.
     * @param rule The rule to add.
     */
    void putRules(const Rules &rule);

    /**
     * Method that removes a rule with a certain material from the vector of rules.
     * @param mat The material of the rule to remove.
     */
    void removeRule(Material mat);

    /**
     * Method that checks if a certain material is inside the vector of rules.
     * @param mat The material to check.
     * @return true if the material is inside the vector of rules, false otherwise.
     */
    bool isInsideRule(Material mat);

    /**
     * Method that executes the rules.
     */
    void executeRule();

    /**
     * Method that checks if a position is free of game objects.
     * @param pos The position to check.
     * @return true if the position is free, false otherwise.
     */
    bool checkIsFree(const Position &pos);

    /**
     * Method that checks if a game object can be pushed to a target position in a certain direction.
     * @param pos The current position of the game object.
     * @param targetPos The target position to move the game object to.
     * @param d The direction to move the game object in.
     * @return true if the game object can be pushed, false otherwise.
     */
    bool checkIsPush(const Position &pos, const Position &targetPos, Direction d);

    /**
     * Method that moves a game object to a new position.
     * @param obj The game object to move.
     */
    void moveDelete(ObjectGame &obj);

    /**
     * Method that removes the aspect of a rule.
     * @param rule The rule to remove the aspect from.
     */
    void removeAspect(Rules &rule);

    /**
     * Method that checks if a game object is an "is" object.
     * @param obj The game object to check.
     */
    void ifAnIs(ObjectGame &elemGame);

    /**
     * Method that checks if a position has no aspects.
     * @param pos The position to check.
     * @return true if the position has no aspects, false otherwise.
     */
    bool checkIsAspectNone(const Position &pos);

    /**

     *This method checks if an object of type "Aspect" can kill an object at a specified position on the game board.
     *@param pos The position of the object to test.
     *@param AspectToBeChecked The aspect that will be checked for its ability to kill.
     *@return A boolean indicating if the object at the specified position can be killed by the specified aspect.
     */
    bool killYou(const Position &pos, Aspect AspectToBeChecked);

    /**
     * Method that removes a "You" game object from the vector of "You" game objects.
     * @param you The "You" game object to remove.
     */
    void removeYou(const ObjectGame &you);


};

#endif // BOARD_H
