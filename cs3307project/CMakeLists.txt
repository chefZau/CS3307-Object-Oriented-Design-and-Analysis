cmake_minimum_required(VERSION 3.14)
project(cs3307mock)

set(CMAKE_CXX_STANDARD 14)

add_executable(cs3307mock sensor.h sensor.cpp light.h light.cpp alarmLight.h
        alarmLight.cpp roomLight.cpp roomLight.h alarm.h alarm.cpp web_module.h web_module.cpp
        room.cpp room.h test3.cpp)