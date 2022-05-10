#include "logicHandler.h"

#include <conio.h>
#include <windows.h>

LogicHandler::LogicHandler() {
    srand(time(NULL));
    system("cls");
    BunnyManager theBunnies;  // creates an instance of 5 new rabbits
    while (runSimulation(theBunnies)) {
    }
    std::cout << "Simulation has terminated." << std::endl;
}

bool LogicHandler::runSimulation(BunnyManager &theBunnies) {
    std::cout << "Press k to remove half of the population." << std::endl;
    std::cout << "Press 0 to exit" << std::endl;

    char input = waitForCharInput(2);
    switch (input) {
        case '0': {
            system("cls");
            return false;
        }
        case 'k': {
            theBunnies.halfPopulation();
        }
        default: {
            system("cls");
            return theBunnies.turnComplete();
        }
    }
}

char LogicHandler::waitForCharInput(int seconds) {
    char c = '1';
    while (seconds != 0) {
        if (_kbhit()) {
            c = getch();
            break;
        }

        Sleep(1000);
        --seconds;
    }
    return c;
}