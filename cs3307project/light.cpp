//
// Created by MingCong Zhou
//

#include "light.h"

using namespace std;

light::light() {
   this->lightState = false;
}

void light::turnOnLight() {
    this->lightState = true;
}

void light::turnOffLight() {
    this->lightState = false;
}

bool light::getLightState() {
    return this->lightState;
}

std::string light::lightToString() {
    if(this->lightState){
        return " ON ";
    }else{
        return " OFF ";
    }
}