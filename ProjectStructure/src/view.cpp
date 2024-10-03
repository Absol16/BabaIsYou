#include "view.h"

View::View( Level &m): model(&m) {}

char View::getSymbol(Material mat) {
    switch (mat) {
    case Material::BABA:
        return 'B';
    case Material::WALL:
        return '#';
    case Material::LAVA:
        return 'L';
    case Material::FLAG:
        return 'F';
    case Material::METAL:
        return '.';
    case Material::ROCK:
        return 'R';
    case Material::NOTHING:
        return ' ';
    case Material::GRASS:
        return 'G';
    case Material::WATER:
        return '~';
    case Material::ASPECT_BABA:
        return 'b';
    case Material::ASPECT_WALL:
        return 'w';
    case Material::ASPECT_ROCK:
        return 'r';
    case Material::ASPECT_FLAG:
        return 'f';
    case Material::ASPECT_BEST:
        return 't';
    case Material::ASPECT_LAVA:
        return 'l';
    case Material::ASPECT_WATER:
        return 'g';
    case Material::ASPECT_IS:
        return 'i';
    case Material::ASPECT_YOU:
        return 'u';
    case Material::ASPECT_STOP:
        return 's';
    case Material::ASPECT_SINK:
        return 'k';
    case Material::ASPECT_PUSH:
        return 'p';
    case Material::ASPECT_KILL:
        return 'x';
    case Material::ASPECT_WIN:
        return 'w';
    default:
        return ' ';
    }
}

void View::displayBoard() {

    int numRows = this->model->getBoard().getBoard().size();
    int numCols = this->model->getBoard().getBoard()[0].size();
    vector<vector<vector<ObjectGame>>> b = model->getBoard().getBoard();

    // Afficher les délimiteurs de ligne supérieurs
    cout << "   ";
    for (int i = 0; i < numCols; i++) {
        cout << setw(2) << i << " ";
    }
    cout << endl;
    cout << "  ";
    for (int i = 0; i < numCols; i++) {
        cout << "___";
    }
    cout << endl;

    // Afficher le plateau de jeu
    for (int i = 0; i < numRows; i++) {
        if (i < 10) {
            cout << i << " |";
        } else {
            cout << i << "|";
        }
        for (int j = 0; j < numCols; j++) {
            vector<ObjectGame> obj = b[j][i];
            bool objectFound = false;
            for (auto o : obj) {

                for(auto o2:obj){
                    if(o2.getAspectObject()==Aspect::YOU | MaterialUtils::materialToInt(o2.getTypeObject())>4) {
                        cout << " " << setw(2) << getSymbol(o2.getTypeObject());
                        objectFound = true;
                        break;
                    }
                }

                if(objectFound){
                    break;
                }

                Material mat = o.getTypeObject();

                if(mat ==Material::ROCK){
                    cout << " " << setw(2) << getSymbol(mat);
                    objectFound = true;
                    break;
                }

                if (mat != Material::NOTHING) {
                    cout << " " << setw(2) << getSymbol(mat);
                    objectFound = true;
                    break;
                }
            }
            if (!objectFound) {
                cout << "   ";
            }
        }
        cout << "|" << endl;
    }

    // Afficher les délimiteurs de ligne inférieurs
    cout << "  ";
    for (int i = 0; i < numCols; i++) {
        cout << "---";
    }
    cout << endl;
}

void View::displayWin(string text){
    cout << "      --------" << endl;
    cout << "      You won!" << endl;
    cout << "      --------" << endl;
    cout<< "" <<text<<""<<endl;
}

void displayStart(){
    cout << "     00      -----------        00" << endl;
    cout << "   00  | Welcom to BABA IS YOU |  00" << endl;
    cout << "     00      -----------        00" << endl;
}


Direction View::askMovement(){
    string input;
    cout << "Enter a Direction (z, s, q, d):";
    cin >> input;

    if (strcmp(input.c_str(), "z") == 0) {
        return Direction::UP;
    } else if (strcmp(input.c_str(), "s") == 0) {
        return Direction::DOWN;
    } else if (strcmp(input.c_str(), "d") == 0) {
        return Direction::RIGHT;
    } else if (strcmp(input.c_str(), "q") == 0) {
        return Direction::LEFT;
    } else {
        return askMovement();
    }
}

bool View::askSaveGame(){
    displayStart();
    string input;
    cout<< endl;
    cout<< endl;

    cout << "You want to start a new game ?" << endl;
    cout << "y/n";
    cin >> input;

    if (strcmp(input.c_str(), "y") == 0) {
        return false;
    } else if (strcmp(input.c_str(), "n") == 0){
        return true;
    } else return askSaveGame();
}



void View::update(){

    system("cls");
    this->model->getBoard().checkBuildRule();
    if(model->getBoard().gameIsLoose()){
        this->model->start();
    }
    else if(!model->getBoard().gameIsWin()){
        displayBoard();
        model->movement(askMovement());
    }else{
        if(model->getLevel()<4){
            displayWin("next Level");
            model->getBoard().clearRuleAfterWin();
            model->upLevel();
            model->start();
        }else{
            displayWin("GAME OVER");
            exit(0);
        }

    }

}

