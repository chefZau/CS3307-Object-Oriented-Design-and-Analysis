//
// Created by MingCong Zhou
//

#ifndef CS3307MOCK_ALARMLIGHT_H
#define CS3307MOCK_ALARMLIGHT_H

#include "light.h"

class alarmLight : public light
{
private:
    // color: green:0   red:1   yellow:2
	int color;

public:
    alarmLight();
	void setColor(int);
	int getColor();
};

#endif //CS3307MOCK_ALARMLIGHT_H