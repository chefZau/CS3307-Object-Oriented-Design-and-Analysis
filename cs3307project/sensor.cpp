//
// Created by MingCong Zhou
//

#include "sensor.h"


sensor::sensor() {
	this->activation = false;
}

bool sensor::sendUpdate() {
	return this->activation;
}

void sensor::getState(int signal) {
    this->activation = (signal == 100);
}
