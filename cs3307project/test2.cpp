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

web_module* home;

void signalHandler( int signum )
{
    cout<<"change mode!"<<endl;
    home->setAlarmMode(true);

}
int main(){
    home = new web_module(5);
    status = "null";
    home->launchAlarm();
    signal(SIGINT, signalHandler);
    while (status!="Quit"){
        cin>>sign;
    }

    return 0;
}
