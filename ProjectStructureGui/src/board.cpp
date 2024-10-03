#include "board.h"

Board::Board(){
    // Initialisation du tableau 2D de ObjectGame
    this->tabBoard = vector<vector<vector<ObjectGame>>>(18, vector<vector<ObjectGame>>(18, vector<ObjectGame>(2)));;
    // Initialisation des autres membres
    this->objectYou = vector<ObjectGame*>();
    this->rule = vector<Rules>();
    this->subjectRule = vector<ObjectGame*>();
    this->aspectRule = vector<Material>();
}

bool Board::isInside(const Position& pos){
    int x = pos.getX();
    int y = pos.getY();
    return x >= 0 && x < tabBoard.size() && y >= 0 && y < tabBoard[x].size();
}

bool Board::gameIsWin(){
    int x = 0;
    int y = 0;
    for(auto objYou:this->objectYou){
        x = objYou->getCoordonnee().getX();
        y = objYou->getCoordonnee().getY();
        for(auto elemGame:tabBoard[x][y]){
            if(elemGame.getAspectObject()==Aspect::WIN){
                this->rule.clear();
                return true;
            }
        }
    }
    return false;
}

bool Board::gameIsLoose(){
    if(this->objectYou.empty()){
        this->rule.clear();
        return true;
    }else{
        return false;
    }
}

bool Board::canBeMoved(Direction d){
    int dx = 0, dy = 0;
    if (d == Direction::UP) {
        dy = -1;
    } else if (d == Direction::DOWN) {
        dy = 1;
    } else if (d == Direction::LEFT) {
        dx = -1;
    } else if (d == Direction::RIGHT) {
        dx = 1;
    }
    for (ObjectGame *obj : objectYou) {
        Position pos = obj->getCoordonnee();
        int x = pos.getX() + dx;
        int y = pos.getY() + dy;
        Position p(x, y);
        if (isInside(p)) {
            if(tabBoard[x][y].size()==0){
                return true;
            }
            for(ObjectGame& o:tabBoard[x][y]){
                ObjectGame* objAtPos = &o;
                if ( objAtPos->getAspectObject() != Aspect::STOP) {
                    return true;
                }
            }
        }
    }
    return false;
}

void Board::move(Direction d){
    Position targetPos;
    if (d == Direction::UP) {
        targetPos = Position(0, -1);
    } else if (d == Direction::DOWN) {
        targetPos = Position(0, 1);
    } else if (d == Direction::LEFT) {
        targetPos = Position(-1, 0);
    } else if (d == Direction::RIGHT) {
        targetPos = Position(1, 0);
    }
    changePositionObject(d,targetPos);
}

void Board::moveDelete(ObjectGame& obj) {
    int x = obj.getCoordonnee().getX();
    int y = obj.getCoordonnee().getY();
    vector<ObjectGame>* vectorCaseElement = &tabBoard[x][y];
    // Recherche de l'objet à supprimer dans le vecteur
    auto it = vectorCaseElement->begin();
    while (it != vectorCaseElement->end()) {
        if (*it == obj) {
            // Suppression de l'objet trouver
            it = vectorCaseElement->erase(it);
        } else {
            ++it;
        }
    }
}

bool Board::killYou(const Position& pos, Aspect aspectToBeChecked) {
    if (!isInside(pos) || !checkIsFree(pos)) {
        return false;
    }
    int x= pos.getX();
    int y= pos.getY();
    for (auto it = tabBoard[x][y].begin(); it != tabBoard[x][y].end(); ++it) {
        ObjectGame& element = *it;
        if ((aspectToBeChecked == Aspect::SINK && element.getAspectObject() == Aspect::SINK) ||
                (aspectToBeChecked != Aspect::SINK && element.getAspectObject() == Aspect::KILL)) {
            if (aspectToBeChecked == Aspect::SINK) {
                moveDelete(element);
                --it;
            }
            return true;
        }
    }
    return false;
}



void Board::removeYou(const ObjectGame& you) {
    for (ObjectGame* objPtr : objectYou) {
            if(objPtr == &you){
                delete objPtr;
                objPtr = nullptr;
            }
        }
}

void Board::changePositionObject(Direction d, const Position& targetPos) {
    if (!canBeMoved(d)) {
        return;
    }
    for (ObjectGame* elemYou : objectYou) {
        Position posObjYou = elemYou->getCoordonnee();
        Position after = posObjYou + (targetPos);
        if (killYou(after, Aspect::KILL) || killYou(after, Aspect::SINK)) {
            this->moveDelete(*elemYou);
        } else if (checkIsPush(elemYou->getCoordonnee(), targetPos, d)) {
            this->moveDelete(*elemYou);
            if (d == Direction::UP) {
                elemYou->moveUp();
            } else if (d == Direction::DOWN) {
                elemYou->moveDown();
            } else if (d == Direction::LEFT) {
                elemYou->moveLeft();
            } else if (d == Direction::RIGHT) {
                elemYou->moveRight();
            }
            int x = elemYou->getCoordonnee().getX();
            int y = elemYou->getCoordonnee().getY();
            tabBoard[x][y].push_back(*elemYou);
        }
    }
}

bool Board::checkIsAspectNone(const Position &pos){
    Position after = pos;
    if( this->isInside(after)){
        for(auto elemGame:tabBoard[after.getX()][after.getY()]){
            if(elemGame.getAspectObject()== Aspect::PUSH){
                return false;
            }
        }
        return true;
    }
    return false;
}

bool Board::checkIsFree(const Position &after){
    if( this->isInside(after)){
        for(auto elemGame : tabBoard[after.getX()][after.getY()]){
            if(elemGame.getAspectObject() == Aspect::STOP ){
                return false;
            }
        }
        return true;
    }
    return false;
}

void Board::clearRule(){
    this->rule.clear();
}


bool Board::checkIsPush(const Position &pos, const Position &targetPos, Direction d) {
    int matIs = MaterialUtils::materialToInt(Material::ASPECT_IS);
    int x=0;
    int y=0;
    Position afterPosition = pos + targetPos;
    if (!isInside(afterPosition) || !checkIsFree(afterPosition)) {
        return false;
    }
    for (auto& elemGame : tabBoard[afterPosition.getX()][afterPosition.getY()]) {
        if (elemGame.getAspectObject() != Aspect::PUSH) {
            continue;
        }
        if (!checkIsPush(afterPosition, targetPos, d)) {
            continue;
        }
        afterPosition = afterPosition + targetPos;
        if (killYou(afterPosition, Aspect::SINK)) {
            moveDelete(elemGame);
            break;
        }
        int material = MaterialUtils::materialToInt(elemGame.getTypeObject());
        if (isInsideRule(elemGame.getTypeObject())) {
            removeRule(elemGame.getTypeObject());
        } else if (material == matIs) {
            ifAnIs(elemGame);
        }
        moveDelete(elemGame);
        switch (d) {
        case Direction::UP:
            elemGame.moveUp();
            break;
        case Direction::DOWN:
            elemGame.moveDown();
            break;
        case Direction::LEFT:
            elemGame.moveLeft();
            break;
        case Direction::RIGHT:
            elemGame.moveRight();
            break;
        }
        x= elemGame.getCoordonnee().getX();
        y= elemGame.getCoordonnee().getY();
        tabBoard[x][y].push_back(elemGame);
        return true;
    }
    return isInside(afterPosition) && checkIsFree(afterPosition) && checkIsAspectNone(afterPosition);
}

void Board::ifAnIs(ObjectGame &elemGame){
    int MaterialEnd = MaterialUtils::materialToInt(Material::MaterialEnd);
    int TextMaterialEnd = MaterialUtils::materialToInt(Material::TextMaterialEnd);
    Position pos=elemGame.getCoordonnee();
    for(auto a : tabBoard[pos.getX()-1][pos.getY()]) {
        int nbMaterial = MaterialUtils::materialToInt(a.getTypeObject());
        if(nbMaterial > MaterialEnd && nbMaterial < TextMaterialEnd){
            Material currMaterial = a.getTypeObject();
            if(isInsideRule(currMaterial)){
                removeRule(currMaterial);
            }
        }
    }
    for(auto a : tabBoard[pos.getX()][pos.getY()-1]){
        int nbMaterial = MaterialUtils::materialToInt(a.getTypeObject());
        if(nbMaterial > MaterialEnd && nbMaterial < TextMaterialEnd){
            Material currMaterial = a.getTypeObject();
            if(isInsideRule(currMaterial)){
                removeRule(currMaterial);
            }
        }
    }
}

void Board::removeAspect(Rules &rule){
    for(auto subject : this->subjectRule){
        if(subject->getTypeObject()==  MaterialUtils::materialToState(rule.getSubject()) )
        {
            subject->setAspectObject(Aspect::NONE);
        }
    }
}

void Board::putRules(const Rules&rule){
    this->rule.push_back(rule);
}

void Board::removeRule( Material mat){
    int compt=0;
    for(auto r : rule){
        if(r.getSubject()== mat || r.getRuleAspect()==mat)
        {
            this->removeAspect(r);
            rule.erase(rule.begin()+compt);
            break;
        }
        compt++;
    }
}

bool Board::isInsideRule(Material mat){
    for(auto r: rule){
        if(r.getSubject()==mat || r.getRuleAspect()==mat ){
            return true;
        }
    }
    return false;
}



void Board::executeRule(){
    Material subject ;
    Material newMaterial;
    bool changeState = false;
    int TextMaterialEnd = MaterialUtils::materialToInt(Material::TextMaterialEnd);
    objectYou.clear();
    for(Rules r : this->rule){

        subject = MaterialUtils::materialToState(r.getSubject());
        newMaterial = r.getRuleAspect();
        int nbMaterial = MaterialUtils::materialToInt(newMaterial);
        //if the rule say that the subject change his state or not.
        if(nbMaterial < TextMaterialEnd){
            changeState = true;
        }
        for (int x = 0; x < tabBoard.size(); ++x) {
            for (int y = 0; y < tabBoard[0].size(); ++y) {
                for(auto & elemGame : tabBoard[x][y]){
                    if(elemGame.getTypeObject() == subject){
                        if(changeState){
                            elemGame.setTypeObject(MaterialUtils::materialToState(newMaterial));
                        }else{
                            elemGame.setAspectObject(MaterialUtils::materialToAspect(newMaterial));
                            if(newMaterial == Material::ASPECT_YOU){
                                objectYou.push_back(&elemGame);
                            }
                        }
                        this->subjectRule.push_back(&elemGame);
                    }
                }
            }
        }
    }
}

void Board::checkBuildRule() {

    int MaterialEnd = MaterialUtils::materialToInt(Material::MaterialEnd);
    int TextMaterialEnd = MaterialUtils::materialToInt(Material::TextMaterialEnd);
    int isAspect = MaterialUtils::materialToInt(Material::ASPECT_IS);

    for (int x = 0; x < tabBoard.size(); x++) {
        for (int y = 0; y < tabBoard[0].size(); y++) {
            for (auto& objectIs : tabBoard[x][y]) {
                if (objectIs.getTypeObject() != Material::ASPECT_IS) {
                    continue;
                }
                // verifie les element à gauche
                if (x > 0) {
                    for (auto& subject : tabBoard[x - 1][y]) {
                        int Material = MaterialUtils::materialToInt(subject.getTypeObject());
                        // verifie si l'element est une regle
                        if (Material > MaterialEnd && Material< TextMaterialEnd &&
                                !isInsideRule(subject.getTypeObject())) {
                            // verifie les element à droite
                            if (x < tabBoard.size() - 1) {
                                for (auto& objectAspect : tabBoard[x + 1][y]) {
                                    int materialAspect = MaterialUtils::materialToInt(objectAspect.getTypeObject());
                                    // verifie si c'est un text aspect
                                    if (materialAspect > isAspect) {
                                        Rules r(subject.getTypeObject(),
                                                objectIs.getTypeObject(),
                                                objectAspect.getTypeObject());
                                        this->putRules(r);
                                    }
                                }
                            }
                        }
                    }
                }

                // Check les elements au dessus
                if (y > 0) {
                    for (auto& subject : tabBoard[x][y - 1]) {
                        int Material = MaterialUtils::materialToInt(subject.getTypeObject());
                        if (Material > MaterialEnd && Material< TextMaterialEnd &&
                                !isInsideRule(subject.getTypeObject())) {
                            // Check les elements en bas
                            if (y < tabBoard[0].size() - 1) {
                                for (auto& objectAspect : tabBoard[x][y + 1]) {
                                    int materialAspect = MaterialUtils::materialToInt(objectAspect.getTypeObject());
                                    if (materialAspect > isAspect) {
                                        Rules r(subject.getTypeObject(),
                                                objectIs.getTypeObject(),
                                                objectAspect.getTypeObject());
                                        this->putRules(r);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    this->executeRule();
}

vector<std::vector<std::vector<ObjectGame>>> Board::getTabBoard(){
    return tabBoard;
}


void Board::setTabGame (vector<ObjectGame>& element, Position& pos) {

    if (isInside(pos)) {
        this->tabBoard[pos.getX()][pos.getY()]=element;
    }
    else {
        throw std::invalid_argument("Error position, not on the board");
    }
}

void Board::setRule(vector<Rules> r){
    this->rule = r;
}

vector<Rules> Board::getRule(){
    return this->rule;
}


