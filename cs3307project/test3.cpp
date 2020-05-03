//
// Created by MingCong Zhou
//

#include <csignal>
#include <unistd.h>
#include "web_module.h"

using namespace std;

int main(){
    auto* home = new web_module(5);
    home->lightAutoOn();
    sleep(2);
    home->getAllAppliances();
    home->lightAutoOff();
    sleep(2);
    home->getAllAppliances();
    return 0;

}
