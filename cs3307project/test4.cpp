//
// Created by MingCong Zhou
//

#include "web_module.h"

using namespace std;

int main(){
    auto* home = new web_module(5);
    home->getAllAppliances();
    return 0;
}