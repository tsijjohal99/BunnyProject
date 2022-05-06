#include <conio.h>
#include <windows.h>

#include <cstdio>
#include <cstdlib>
#include <ctime>

#include "bunnyManager.h"

char waitForCharInput(int seconds) {
    char c = '1';
    while (seconds != 0) {
        if (kbhit()) {
            c = getch();
            break;
        }

        Sleep(1000);
        --seconds;
    }
    return c;
}

bool runSimulation(BunnyManager &theBunnys) {
    std::cout << "Press k to snap your fingers." << std::endl;
    std::cout << "Press 0 to exit" << std::endl;

    char input = waitForCharInput(2);
    switch (input) {
        case '0': {
            system("cls");
            return false;
        }
        case 'k': {
            theBunnys.thanos();
        }
        default: {
            system("cls");
            return theBunnys.turnComplete();
        }
    }
}

int main() {
    srand(time(NULL));
    BunnyManager theBunnys;
    while (runSimulation(theBunnys)) {
    }
    std::cout << "Simulation has terminated." << std::endl;
    return 0;
}