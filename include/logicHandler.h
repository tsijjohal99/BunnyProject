#pragma once
#include "bunnyManager.h"

class LogicHandler {
   public:
    LogicHandler();

    bool runSimulation(BunnyManager &theBunnies);
    char waitForCharInput(int seconds);
};