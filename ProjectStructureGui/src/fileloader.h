#ifndef FILELOADER_H
#define FILELOADER_H

#include "objectgame.h"
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

class FileLoader {
    public:
        /**
         * @brief Loads the file for the given level.
         *
         * @param level The level number.
         * @param isSave Flag indicating if the file is a saved game file.
         * @return A vector of ObjectGame representing the game objects in the level.
         */
        static std::vector<ObjectGame> loadFile(int level,bool isSave);

        /**
         * @brief Writes the game state to a file.
         *
         * @param tabBoard A 3D vector representing the game board.
         */
        void writeToFile(vector<vector<vector<ObjectGame>>> tabBoard);
};

#endif // FILELOADER_H
