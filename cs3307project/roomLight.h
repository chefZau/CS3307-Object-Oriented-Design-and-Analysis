//
// Created by MingCong Zhou
//

#ifndef CS3307MOCK_ROOMLIGHT_H
#define CS3307MOCK_ROOMLIGHT_H

#include "light.h"

class roomLight : public light {

private:
    bool autoSwitch;
    int roomNum;

public:
    roomLight();
    void update_autoSwitch(bool);
    void update_roomNum(int);
    bool get_autoSwitch();
    int get_roomNum();
    std::string lightModeToStirng();
};


#endif //CS3307MOCK_ROOMLIGHT_H
