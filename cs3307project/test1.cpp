//
// Created by MingCong Zhou
//

#include <pthread.h>
#include "roomLight.h"
#include "alarm.h"
#include <vector>

extern int sign;
extern std::string status;

using namespace std;

auto * room_alm = new alarm();
vector<roomLight> roomLights;


void* openAlm(void*) {
    cout<<"Alarm is open!"<<endl;
    status = room_alm->turnOnAlarm(sign);
    cout<<"Detection: "<<status<<" light!"<<endl;
    return nullptr;
}

int main(){
    status = "null";
    pthread_t p1,p2;
    //suppose there are 5 rooms
    for(int i=0;i<5;i++){
        roomLights.push_back(*new roomLight());
        roomLights[i].update_roomNum(i+1);
    }

    //test all the room light have been set
    for(auto i: roomLights){
        cout<<"This is room number "<<i.get_roomNum()<<", Current light state is "<<i.getLightState()<<endl;
    }

    //test alarm(current user mode is set to off(false)
    cout<<"Current User Mode is "<<room_alm->getUserMode()<<", and current light color is "<<room_alm->getCurrentStatus()<<endl;

    pthread_create(&p1, nullptr, openAlm, nullptr);
    while(status == "null"){
        cin >> sign;
    }
    pthread_join(p1,nullptr);

    // set user mode to open(true) and test again
    status = "null";
    room_alm->updateUserMode(true);
    room_alm->reset();
    pthread_create(&p2, nullptr, openAlm, nullptr);
    while(status == "null"){
        cin >> sign;
    }
    pthread_join(p2,nullptr);

    return 0;
}
