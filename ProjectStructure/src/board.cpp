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

vector<std::vector<std::vector<ObjectGame>>> Board::getBoard(){
    return tabBoard;
}


void Board::setTabGame (vector<ObjectGame>& element, Position& pos) {
    if (isInside(pos)) {

        this->tabBoard[pos.getX()][pos.getY()]=element;


    }
    else {
        throw std::invalid_argument("Erreur position, pas dans le tableau");
    }
}

void Board::setRule(vector<Rules> r){
    this->rule = r;
}

vector<Rules> Board::getRule(){
    return this->rule;
}

bool Board::isInside(Position& pos){
    int x = pos.getX();
    int y = pos.getY();
    return x >= 0 && x < tabBoard.size() && y >= 0 && y < tabBoard[x].size();
}



bool Board::gameIsWin(){

    for(auto o:this->objectYou){
        for(auto p:tabBoard[o->getCoordonnee().getX()][o->getCoordonnee().getY()]){
            if(p.getAspectObject()==Enum::Aspect::WIN)


                return true;
        }
    }

    return false;
}

bool Board::gameIsLoose(){

    if(this->objectYou.empty()){
        return true;
    }else{
        return false;
    }
}

void Board::clearRuleAfterWin(){
    this->rule.clear();
}


bool Board::canBeMoved(const Direction& d){
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

void Board::move(const Direction &d){
    Position targetPos;
    if (d == Direction::UP) {

        targetPos = Position(0, -1);
        changePositionObject(d,targetPos);

    } else if (d == Direction::DOWN) {

        targetPos = Position(0, 1);
        changePositionObject(d,targetPos);
    } else if (d == Direction::LEFT) {

        targetPos = Position(-1, 0);
        changePositionObject(d,targetPos);

    } else if (d == Direction::RIGHT) {

        targetPos = Position(1, 0);
        changePositionObject(d,targetPos);

    }
}

void Board::moveDelete(ObjectGame &obj){

    auto vectorCaseElement= &this->tabBoard[obj.getCoordonnee().getX()][obj.getCoordonnee().getY()];
    int compt=0;
    for(auto elementGame:*vectorCaseElement){

        if(elementGame.getAspectObject()==obj.getAspectObject()){


            vectorCaseElement->erase(vectorCaseElement->begin()+compt);

            if(obj.getAspectObject()==Enum::Aspect::YOU){
                removeYou(obj);
            }
            break;
        }
        compt++;

    }


}

bool Board::killYou(Position &pos,Enum::Aspect AspectToBeChecked ){



    if( this->isInside(pos) && this->checkIsFree(pos)){


        for(auto &vecteurCaseElement: tabBoard[pos.getX()][pos.getY()]){

            if(AspectToBeChecked==Enum::Aspect::SINK){

                if (vecteurCaseElement.getAspectObject()==Enum::Aspect::SINK )
                {
                    this->moveDelete(vecteurCaseElement);
                    return true;
                }
            }else{
                if(vecteurCaseElement.getAspectObject()==Enum::Aspect::KILL ) {

                    return true;

                }
            }

        }

    }
    return false;
}



void Board::removeYou(const ObjectGame &you){
    int compt=0;
    for(auto isYouElement:this->objectYou)
    {
        if(isYouElement == &you){
            objectYou.erase(objectYou.begin()+compt);
            break;
        }
        compt++;

    }
}

void Board::changePositionObject(const Direction &d, const Position &targetPos){
    Position after ;

    if(canBeMoved(d)){

        for (ObjectGame *obj : objectYou) {

            after = obj->getCoordonnee() + targetPos;

            if (d == Direction::UP) {


                if(killYou(after,Aspect::KILL) ||killYou(after,Aspect::SINK)  ){
                    this->moveDelete(*obj);
                }else{
                    if(checkIsPush(obj->getCoordonnee(),targetPos,d)){
                        this->moveDelete(*obj);
                        obj->moveUp();
                        tabBoard[obj->getCoordonnee().getX()][obj->getCoordonnee().getY()].push_back(*obj);
                    }
                }

            } else if (d == Direction::DOWN) {

                if(killYou(after,Aspect::KILL) ||killYou(after,Aspect::SINK) ){
                    this->moveDelete(*obj);
                }else{

                    if(checkIsPush(obj->getCoordonnee(),targetPos,d)){
                        this->moveDelete(*obj);
                        obj->moveDown();
                        tabBoard[obj->getCoordonnee().getX()][obj->getCoordonnee().getY()].push_back(*obj);

                    }
                }

            } else if (d == Direction::LEFT ) {

                if(killYou(after,Aspect::KILL)||killYou(after,Aspect::SINK) ){
                    this->moveDelete(*obj);
                }else{

                    if(checkIsPush(obj->getCoordonnee(),targetPos,d)){
                        this->moveDelete(*obj);
                        obj->moveLeft();
                        tabBoard[obj->getCoordonnee().getX()][obj->getCoordonnee().getY()].push_back(*obj);

                    }
                }
            } else if (d == Direction::RIGHT) {

                if(killYou(after,Aspect::KILL)||killYou(after,Aspect::SINK) ){
                    this->moveDelete(*obj);
                }else{


                    if(checkIsPush(obj->getCoordonnee(),targetPos,d)){
                        this->moveDelete(*obj);
                        obj->moveRight();
                        tabBoard[obj->getCoordonnee().getX()][obj->getCoordonnee().getY()].push_back(*obj);

                    }
                }
            }
        }
    }



}

bool Board::checkIsAspectNone(const Position &pos){

    Position after = pos;

    if( this->isInside(after)){

        for(auto o:tabBoard[after.getX()][after.getY()]){


            if(o.getAspectObject()==Enum::Aspect::PUSH){



                return false;
            }
        }

        return true;
    }

    return false;


}

bool Board::checkIsFree(const Position &pos){

    Position after = pos;

    if( this->isInside(after)){

        for(auto o:tabBoard[after.getX()][after.getY()]){

            if(o.getAspectObject()==Enum::Aspect::STOP ){
                return false;
            }
        }

        return true;
    }

    return false;


}


bool Board::checkIsPush(const Position &pos,const Position &targetPos, const Direction &d){
    Position afterPosition = pos + targetPos;
    if( this->isInside(afterPosition) && this->checkIsFree(afterPosition)){


        for(auto o:tabBoard[afterPosition.getX()][afterPosition.getY()]){

            if(o.getAspectObject()==Enum::Aspect::PUSH && checkIsPush( afterPosition,targetPos,d)){

                afterPosition = afterPosition + targetPos;
                if(this->killYou(afterPosition,Aspect::SINK)){
                    this->moveDelete(o);
                    break;
                }

                if(isInsideRule(o.getTypeObject())){

                    removeRule(o.getTypeObject());

                }else if(MaterialUtils::materialToInt(o.getTypeObject()) == 15){

                    this->ifAnIs(o);
                }
                switch (d) {
                case Direction::UP:
                    this->moveDelete(o);

                    o.moveUp();

                    tabBoard[o.getCoordonnee().getX()][o.getCoordonnee().getY()].push_back(o);
                    break;
                case Direction::DOWN:
                    this->moveDelete(o);
                    o.moveDown();
                    tabBoard[o.getCoordonnee().getX()][o.getCoordonnee().getY()].push_back(o);
                    break;
                case Direction::LEFT:
                    this->moveDelete(o);
                    o.moveLeft();
                    tabBoard[o.getCoordonnee().getX()][o.getCoordonnee().getY()].push_back(o);
                    break;
                case Direction::RIGHT:


                    this->moveDelete(o);

                    o.moveRight();
                    tabBoard[o.getCoordonnee().getX()][o.getCoordonnee().getY()].push_back(o);

                    break;
                }

                return true;
            }

        }


        if( this->isInside(afterPosition) && this->checkIsFree(afterPosition) && checkIsAspectNone(afterPosition)){

            return true;
        }else{
            return false;
        }

    }
    return false;

}

void Board::ifAnIs(ObjectGame &obj){

    Position pos=obj.getCoordonnee();
    for( auto a: tabBoard[pos.getX()-1][pos.getY()]) {
        if(MaterialUtils::materialToInt(a.getTypeObject()) >8 && MaterialUtils::materialToInt(a.getTypeObject()) <= 14){
            if(isInsideRule(a.getTypeObject())){
                removeRule(a.getTypeObject());
            }
        }
        for( auto a: tabBoard[pos.getX()][pos.getY()-1]) {
            if(MaterialUtils::materialToInt(a.getTypeObject()) >8 && MaterialUtils::materialToInt(a.getTypeObject()) <= 14){
                if(isInsideRule(a.getTypeObject())){

                    removeRule(a.getTypeObject());

                }
            }
        }

    }}

void Board::removeAspect(Rules &rule){

    for(auto sub: this->subjectRule){

        if(sub->getTypeObject()==  MaterialUtils::materialToState(rule.getSubject()) )
        {

            sub->setAspectObject(Enum::Aspect::NONE);

        }
    }
}

void Board::putRules(const Rules&rule){

    this->rule.push_back(rule);

}

void Board::removeRule( Enum::Material mat){

    int compt=0;
    for(auto i:rule){
        if(i.getSubject()==mat || i.getRuleAspect()==mat)
        {

            this->removeAspect(i);
            rule.erase(rule.begin()+compt);
            break;
        }
        compt++;
    }

}

bool Board::isInsideRule(const Enum::Material& mat){



    for(auto regle: rule){
        if(regle.getSubject()==mat || regle.getRuleAspect()==mat ){

            return true;
        }
    }
    return false;
}



void Board::executeRule(){

    ObjectGame obj;
    Material subject ;
    Material newMaterial;
    bool changeState = false;

    objectYou.clear();



    for(Rules r : this->rule){

        subject = MaterialUtils::materialToState(r.getSubject());
        newMaterial = r.getRuleAspect();

        //if the rule say that the subject change his state or not.
        if(MaterialUtils::materialToInt(newMaterial) <= 14){
            changeState = true;
        }
        for (int x = 0; x < tabBoard.size(); ++x) {
            for (int y = 0; y < tabBoard[0].size(); ++y) {
                for(auto &o:tabBoard[x][y]){

                    if(o.getTypeObject()==subject){

                        if(changeState){
                            o.setTypeObject(MaterialUtils::materialToState(newMaterial));

                        }else{
                            o.setAspectObject(MaterialUtils::materialToAspect(newMaterial));
                            if(newMaterial == Material::ASPECT_YOU){
                                objectYou.push_back(&o);
                            }
                        }
                        this->subjectRule.push_back(&o);
                    }
                }

            }
        }
    }
}

void Board::checkBuildRule(){
    ObjectGame objIs;
    ObjectGame *subject;
    ObjectGame aspect;
    Position p;

    for(int x=0; x<tabBoard.size();x++){
        for(int y=0; y<tabBoard[0].size();y++){
            for(auto A:tabBoard[x][y])
            {
                p.setX(x);
                p.setY(y);

                objIs = A;

                if(objIs.getTypeObject()== Material::ASPECT_IS){
                    p.setX(x-1);

                    if(this->isInside(p)){

                        for(auto B : tabBoard[x-1][y]){
                            subject = &B;

                            if(MaterialUtils::materialToInt(subject->getTypeObject()) >8 && MaterialUtils::materialToInt(subject->getTypeObject()) <= 14 && !isInsideRule(subject->getTypeObject())){
                                p.setX(x+1);

                                if(this->isInside(p)){

                                    for(auto C:tabBoard[x+1][y]){
                                        aspect = C;
                                        if(MaterialUtils::materialToInt(aspect.getTypeObject()) >=16){
                                            Rules r (subject->getTypeObject(),objIs.getTypeObject(),aspect.getTypeObject());


                                            this->putRules(r);
                                        }
                                    }
                                }
                            }
                        }
                    }

                    p.setX(x);
                    p.setY(y-1);

                    if(this->isInside(p)){
                        for(auto B2:tabBoard[x][y-1])
                        {
                            subject = &B2;

                            if(MaterialUtils::materialToInt(subject->getTypeObject()) >8 && MaterialUtils::materialToInt(subject->getTypeObject()) <= 14 && !isInsideRule(subject->getTypeObject())){
                                p.setY(y+1);

                                if(this->isInside(p)){
                                    for(auto C2:tabBoard[x][y+1])
                                    {
                                        aspect = C2;
                                        if(MaterialUtils::materialToInt(aspect.getTypeObject()) >=16){
                                            Rules r (subject->getTypeObject(),objIs.getTypeObject(),aspect.getTypeObject());


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
    }

    this->executeRule();
}
