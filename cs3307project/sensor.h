//
// Created by MingCong Zhou
//

#ifndef CS3307MOCK_SENSOR_H
#define CS3307MOCK_SENSOR_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cstring>

/*
 * This class used to represent a sensor which can detect events
 */
class sensor
{
private:
    bool activation;  // indicate whether the sensor is activated
public:
    /*
     * constructor
     */
    sensor();
    /*
     * send current value to user
     */
    bool sendUpdate();
    /*
     * get current value
     */
    void getState(int);
};

#endif //CS3307MOCK_SENSOR_H