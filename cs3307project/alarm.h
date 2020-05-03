//
// Created by MingCong Zhou
//

#ifndef CS3307MOCK_ALARM_H
#define CS3307MOCK_ALARM_H

#include <string>
#include "sensor.h"
#include "alarmLight.h"

class alarm {

private:
    sensor* alarm_sensor;
    alarmLight* alarm_lt;
    bool user_mode;

public:
    alarm();
    void updateUserMode(bool);
    bool getUserMode();
    std::string turnOnAlarm(int&);
    void reset();
    std::string getCurrentStatus();
    alarmLight* getAlarmLight();
    void resetSensor();
protected:
    void selfUpdate(int);
};


#endif //CS3307MOCK_ALARM_H
