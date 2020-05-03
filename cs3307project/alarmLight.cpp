//
// Created by MingCong Zhou
//

#include "alarmLight.h"
using namespace std;

alarmLight::alarmLight() {
    this->lightState = false;
    this->color = 0;
}
void alarmLight::setColor(int c) {
	this->color = c;
}

int alarmLight::getColor() {
	return this->color;
}