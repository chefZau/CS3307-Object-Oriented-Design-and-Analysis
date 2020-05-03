//
// Created by MingCong Zhou
//

#include "room.h"

static std::default_random_engine e;
static std::uniform_int_distribution<unsigned > u(0,200);
using namespace std;

std::vector<unsigned >* good_randVec()
{
    auto* ret = new std::vector<unsigned>;
    for(size_t i=0; i<1000; ++i)
        ret->push_back(u(e));
    return ret;
}

room::room(int roomNumber) {
    this->light = new roomLight();
    this->detector = new sensor();
    this->light->update_roomNum(roomNumber);
    this->signal = good_randVec();
}

void room::autoSwitchLight(int s) {
    this->detector->getState(s);
    if(this->detector->sendUpdate()){
        cout<<"Sensor detected..."<<endl;
        if(this->light->getLightState()){
            this->light->turnOffLight();
            cout<<"Light "<<this->light->get_roomNum()<<" Off..."<<endl;
        } else{
            this->light->turnOnLight();
            cout<<"Light "<<this->light->get_roomNum()<<" On..."<<endl;
        }
    }
}

int room::getSignal() {
    if(this->signal->empty()){
        for(size_t i=0; i<1000; ++i){
            this->signal->push_back(u(e));
        }
    }
    int result = this->signal->at(this->signal->size()-1);
    this->signal->pop_back();
    return result;

}