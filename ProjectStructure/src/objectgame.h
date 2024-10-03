#ifndef OBJECTGAME_H
#define OBJECTGAME_H

#include "position.h"
#include "Enum.h"
#include <iostream>
#include <vector>

using namespace std;
using namespace Enum;

class ObjectGame {
    private:
        Position coordonnee;
        Material typeObject;
        Aspect aspectObject;

    public:
        /**
         * @brief ObjectGame constructor
         *
         * @param coord Position of the object on the game board
         * @param type Type of the object (Material enum)
         * @param aspect Aspect of the object (Aspect enum)
         */
        ObjectGame(Position coord, Material type, Aspect aspect);

        /**
         * @brief ObjectGame default constructor
         */
        ObjectGame();

        /**
         * @brief Moves the object down
         */
        void moveDown();

        /**
         * @brief Moves the object up
         */
        void moveUp();

        /**
         * @brief Moves the object right
         */
        void moveRight();

        /**
         * @brief Moves the object left
         */
        void moveLeft();

        /**
         * @brief Gets the position of the object on the game board
         *
         * @return Position of the object on the game board
         */
        Position getCoordonnee();

        /**
         * @brief Gets the type of the object
         *
         * @return Type of the object (Material enum)
         */
        Material getTypeObject();

        /**
         * @brief Gets the aspect of the object
         *
         * @return Aspect of the object (Aspect enum)
         */
        Aspect getAspectObject();

        /**
         * @brief Sets the type of the object
         *
         * @param newType New type of the object (Material enum)
         */
        void setTypeObject(Material newType);

        /**
         * @brief Sets the aspect of the object
         *
         * @param newAspect New aspect of the object (Aspect enum)
         */
        void setAspectObject(Aspect newAspect);

        /**
         * @brief Sets the position of the object on the game board
         *
         * @param pos New position of the object on the game board
         */
        void setCoordonnee(Position pos);

        /**
         * @brief Returns a string representation of the object
         *
         * @return String representation of the object
         */
        string toString() const;

        /**
         * @brief Returns the integer value associated with the object's type (Material enum)
         *
         * @return Integer value associated with the object's type
         */
        int materialToInt();

        /**
         * @brief Overloaded stream insertion operator for ObjectGame
         *
         * @param os Output stream
         * @param obj Object to insert into the stream
         * @return Reference to the output stream
         */
        friend std::ostream& operator<<(std::ostream& os, const ObjectGame& obj) {
                os << "ObjectGame: " << obj.toString();
                return os;
        }

        bool operator==(const ObjectGame& other) const {
            return (this->aspectObject == other.aspectObject) && (this->typeObject == other.typeObject);
        }
};

#endif // OBJECTGAME_H
