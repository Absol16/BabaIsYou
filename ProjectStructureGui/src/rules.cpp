#include"rules.h"

Rules::Rules(Material subject, Material is, Material aspect){
    this->subject=subject;
    this->is=is;
    this->aspect=aspect;
}

Material Rules::getRuleAspect(){
    return this->aspect;
}

Material Rules::getSubject(){
    return this->subject;
}
