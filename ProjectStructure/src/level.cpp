#include "level.h"


Level::Level(int l)
{
    this->board =Board();
    this->level = l;
    this->isSave = false;

}
void Level::start(){
    initBoard();
    this->notify();
}






void Level::initBoard(){

    vector<ObjectGame> listObject = file.loadFile(level,isSave);
    vector<ObjectGame> objCurr;
    Position pos;
    bool test;
    for (int i = 0; i < board.getBoard().size();++i) {
        for (int j = 0; j < board.getBoard()[0].size();++j) {
            test=false;
            for (auto obj : listObject) {
                pos = obj.getCoordonnee();
                if(pos.getX()==i && pos.getY()==j){
                    test=true;
                    objCurr.push_back(obj);
                    board.setTabGame(objCurr,pos);
                    objCurr.clear();
                }

            }

            if(!test){
                Position pos(i,j);
                ObjectGame obj(pos,Material::NOTHING,Aspect::NONE);
                objCurr.push_back(obj);
                board.setTabGame(objCurr,pos);
                objCurr.clear();
            }
        }
    }
}

Board& Level::getBoard() {
    return this->board;
}

int Level::getLevel() const{
    return level;
}

void Level::upLevel(){
    this->level++;
}

void Level::IsSave(){
    if(isSave){
        isSave = false;
    }else isSave = true;
}

void Level::movement(Direction d){
    board.move(d);
    file.writeToFile(board.getBoard());
    this->notify();
}
