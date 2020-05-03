//
// Created by MingCong Zhou
//

#ifndef CS3307MOCK_LIGHT_H
#define CS3307MOCK_LIGHT_H

#include <iostream>

class light {
protected:
    bool lightState;

public:
    light();
    void turnOnLight();
    void turnOffLight();
    bool getLightState();
    std::string lightToString();
};


#endif //CS3307MOCK_LIGHT_H
