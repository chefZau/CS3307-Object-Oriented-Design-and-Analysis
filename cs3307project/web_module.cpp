//
// Created by MingCong Zhou
//

#include "web_module.h"

using namespace std;

string status;
int sign = 0;

/**
 * Constructor
 * @param total_rooms  need to know how many rooms in total
 */
web_module::web_module(int total_rooms) {
    this->alarmMsg = "";
    this->alm = new class alarm();
    setRooms(total_rooms);
}

/**
 * This method is a helper method for init the web_module
 * Used to init all the lights
 * @param total_rooms
 */
void web_module::setRooms(int total_rooms) {
    for(int i=0; i<total_rooms; i++){
        this->roomLights.push_back(*new room(i+1));
    }
}

void* web_module::openAlarm(void* __this) {
    auto* _this = (web_module*)__this;
    cout<<"Alarm is now open!"<<endl;
    while (status != "Quit") {
        status = _this->alm->turnOnAlarm(sign);
        if (status == "Yellow") {
            _this->alarmMsg = "Someone comes back!";
            cout << _this->alarmMsg << endl;
            cout << _this->alm->getCurrentStatus()<<" : "<<_this->alm->getAlarmLight()->lightToString()<<endl;
            sleep(1);
            _this->alm->getAlarmLight()->turnOffLight();
            cout << _this->alm->getCurrentStatus()<<" : "<<_this->alm->getAlarmLight()->lightToString()<<endl;
            _this->alm->getAlarmLight()->setColor(0);
            status = _this->alm->getCurrentStatus();
            _this->alm->getAlarmLight()->turnOnLight();
            cout << _this->alm->getCurrentStatus()<<" : "<<_this->alm->getAlarmLight()->lightToString()<<endl;
            sign = 0;
            _this->alm->resetSensor();

        } else if (status == "Red") {
            _this->alarmMsg = "Unauthorized person entered the house!";
            cout << _this->alarmMsg << endl;
            cout << _this->alm->getCurrentStatus()<<" : "<<_this->alm->getAlarmLight()->lightToString()<<endl;
            cout << "Raise Alarm!" << endl;
            cout << "Waiting user's response"<<endl;
            cout << "Enter 1 to close alarm, 2 to reset alarm" << endl;
            time_t current = time(nullptr);
            pthread_t p1;
            pthread_create(&p1, nullptr, waiting_time,&current);
            pthread_join(p1, nullptr);
            if(sign==1){
                cout<<"Choose to close alarm..."<<endl;
                _this->closeAlarm();
                cout<<"Alarm closed. Current status: "<<status<<endl;
            }else if(sign==2){
                cout<<"Choose to reset alarm..."<<endl;
                _this->resetAlarm();
                cout<<"OK. Current status: "<<status<<endl;
            }else{
                _this->closeAlarm();
                _this->alarmMsg = "No response! Calling 911......";
                cout<<_this->alarmMsg<<endl;
            }
            sign = 0;
        }
    }
    return nullptr;
}

void web_module::setAlarmMode(bool m) {
    this->alm->updateUserMode(m);
}

void web_module::closeAlarm() {
    status = "Quit";
    this->alm->reset();
}

void web_module::resetAlarm() {
    this->alm->reset();
    status = this->alm->getCurrentStatus();
}

void web_module::lightAutoOn() {
    for(auto i : this->roomLights) {
        i.light->update_autoSwitch(true);
    }
    pthread_t pth;
    pthread_create(&pth, nullptr,monitor,(void*)this);
}

void web_module::lightAutoOff() {
    for(auto i : this->roomLights) {
        i.light->update_autoSwitch(false);
    }
}

void web_module::manualSetLight(int roomNumber, bool d) {
    if(d) {
        roomLights[roomNumber - 1].light->turnOnLight();
    }else{
        roomLights[roomNumber - 1].light->turnOffLight();
    }
}

void web_module::launchAlarm() {
    pthread_t pth;
    pthread_create(&pth, nullptr,openAlarm,(void*)this);
}

void * web_module::monitor(void* __this) {
    auto * _this = (web_module*)__this;
    int total_lights = _this->roomLights.size();
    bool decision = true;
    while(decision){
        int temp_count = 0;
        for(auto i : _this->roomLights){
            if(!i.light->get_autoSwitch()){
                temp_count++;
                continue;
            } else{
                i.autoSwitchLight(i.getSignal());
            }
        }
        if(temp_count==total_lights){
            cout<<"Light auto switch : OFF! "<<endl;
            decision = false;
        }
    }
    return nullptr;
}


void web_module::getAllAppliances() {
    for(auto i : this->roomLights){
        cout<<"Room number: "<<i.light->get_roomNum()<<" ,Current light state is : "<<i.light->lightToString()
        <<", Light mode is : "<<i.light->lightModeToStirng()<<endl;
    }
    cout<<"Current Alarm color is : " <<this->alm->getCurrentStatus()<<" and status : "
    <<this->alm->getAlarmLight()->lightToString()<<endl;
    cout<<"Last alarm message is: "<<this->alarmMsg<<endl;
}

void* web_module::waiting_time(void* current) {
    auto* c = (time_t*)current;
    time_t temp = time(nullptr);
    while((temp - *c)<30){
        if(sign==1 || sign==2){
            return nullptr;
        }
        temp = time(nullptr);
    }

    return nullptr;
}