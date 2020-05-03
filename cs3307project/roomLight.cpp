//
// Created by MingCong Zhou
//

#include "roomLight.h"

roomLight::roomLight() {
    this->lightState = false;
    this->autoSwitch = false;
    this->roomNum = -1;
}

void roomLight::update_autoSwitch(bool s) {
    this->autoSwitch = s;
}

void roomLight::update_roomNum(int n) {
    this->roomNum = n;
}

bool roomLight::get_autoSwitch() {
    return this->autoSwitch;
}

int roomLight::get_roomNum() {
    return this->roomNum;
}

std::string roomLight::lightModeToStirng() {
    if(this->get_autoSwitch()){
        return " AUTO ";
    }else{
        return " MANUAL ";
    }
}

