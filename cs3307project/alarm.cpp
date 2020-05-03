//
// Created by MingCong Zhou
//

#include "alarm.h"

using namespace std;
/**
 * Constructor
 */
alarm::alarm() {
    this->alarm_lt = new alarmLight();
    this->alarm_sensor = new sensor();
    this->user_mode = false;
}
/**
 * Update User mode
 * @param s
 */
void alarm::updateUserMode(bool m) {
    this->user_mode = m;
}

bool alarm::getUserMode() {
    return this->user_mode;
}

string alarm::turnOnAlarm(int& signal) {
    while(!this->alarm_sensor->sendUpdate()){
        int temp = signal;
        selfUpdate(temp);
    }
    return getCurrentStatus();
}

void alarm::reset() {
    this->alarm_lt->setColor(0);
    this->alarm_lt->turnOnLight();
    this->resetSensor();
}

string alarm::getCurrentStatus() {
    int color = this->alarm_lt->getColor();
    if(color==0){
        return "Green";
    }else if(color==1){
        return "Red";
    } else{
        return "Yellow";
    }
}
alarmLight* alarm::getAlarmLight() {
    return this->alarm_lt;
}

void alarm::selfUpdate(int s) {
    this->alarm_sensor->getState(s);
    if(this->alarm_sensor->sendUpdate()){
        if(user_mode){
            this->alarm_lt->setColor(1);
        }else{
            this->alarm_lt->setColor(2);
        }
        this->alarm_lt->turnOnLight();
    }
}

void alarm::resetSensor() {
    this->alarm_sensor->getState(0);
}
