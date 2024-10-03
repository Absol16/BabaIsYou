#include"controller.h"

Controller::Controller(){
}


void Controller::start(){

    int level =0;
    this->facade=Level(level);
    view=View(facade);
    if(view.askSaveGame()){
        facade.IsSave();
    }
    this->facade.addObserver(view);
    this->facade.start();
}
