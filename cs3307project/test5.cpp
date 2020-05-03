//
// Created by MingCong Zhou
//

//
// Created by MingCong Zhou
// This is used to test alarm with different user mode
//
#include <csignal>
#include <unistd.h>
#include "web_module.h"

extern int sign;
extern std::string status;

using namespace std;

int main(){

    web_module* home = new web_module(5);
    home->launchAlarm();
    while (true){
        cin>>sign;
        home->getAllAppliances();
    }

}