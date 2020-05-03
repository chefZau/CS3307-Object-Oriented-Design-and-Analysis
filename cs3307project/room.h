//
// Created by MingCong Zhou
//

#ifndef CS3307MOCK_ROOM_H
#define CS3307MOCK_ROOM_H

#include <iostream>
#include <vector>
#include <string>
#include <random>
#include "roomLight.h"
#include "sensor.h"

class room {
private:
    std::vector<unsigned>* signal;
    sensor* detector;
public:
    explicit room(int);
    roomLight* light;
    int getSignal();
    void autoSwitchLight(int);
};


#endif //CS3307MOCK_ROOM_H
