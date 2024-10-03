#include "objectgame.h"


#include <sstream>
using namespace block;

ObjectGame::ObjectGame(Position coord, Material type, Aspect aspect)
{
    this->coordonnee = coord;
    this->typeObject = type;
    this->aspectObject = aspect;
}

ObjectGame::ObjectGame(){}



void ObjectGame::moveUp(){
    int y = coordonnee.getY();
    y--;
    coordonnee.setY(y);
}

void ObjectGame::moveDown(){
    int y = coordonnee.getY();
    y++;
    coordonnee.setY(y);
}

void ObjectGame::moveRight(){
    int x = coordonnee.getX();
    x++;
    coordonnee.setX(x);
}

void ObjectGame::moveLeft(){
    int x = coordonnee.getX();
    x--;
    coordonnee.setX(x);
}

Aspect ObjectGame::getAspectObject(){
    return aspectObject;
}

Position ObjectGame::getCoordonnee(){
    return coordonnee;
}

Material ObjectGame::getTypeObject(){
    return typeObject;
}

void ObjectGame::setAspectObject(Aspect newAspect){
    this->aspectObject = newAspect;
}

void ObjectGame::setTypeObject(Material newType){
    this->typeObject = newType;
}

void ObjectGame::setCoordonnee(Position pos){
    coordonnee.setX(pos.getX());
    coordonnee.setY(pos.getY());
}

string ObjectGame::toString() const {
    string coordStr = "(" + to_string(coordonnee.getX()) + ", " + to_string(coordonnee.getY()) + ")";
    string typeStr = "Type: " + MaterialUtils::materialToString(this->typeObject);
    string aspectStr = "Aspect: " + MaterialUtils::aspectToString(this->aspectObject);
    return coordStr + " " + typeStr + " " + aspectStr;
}

int ObjectGame::materialToInt(){
    return static_cast<int>(typeObject);
}

