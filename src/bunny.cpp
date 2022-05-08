#include "bunny.h"

#include <windows.h>

#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>

Bunny::Bunny() {
    sex = rand() % 2 ? SEX::MALE : SEX::FEMALE;
    colour = (COLOUR)(rand() % 4);
    name = punnyBunnyNames[rand() % punnyBunnyNames.size()];
    infected = rand() % 100 < 2 ? true : false;
    std::string born = (infected) ? "Infected " : "";
    std::cout << born << name << " was born!" << std::endl;
    Sleep(100);
}

Bunny::Bunny(COLOUR motherColour) : colour(motherColour) {
    sex = rand() % 2 ? SEX::MALE : SEX::FEMALE;
    name = punnyBunnyNames[rand() % punnyBunnyNames.size()];
    infected = rand() % 100 < 2 ? true : false;
    std::string born = (infected) ? "Infected " : "";
    std::cout << born << name << " was born!" << std::endl;
    Sleep(100);
}

SEX Bunny::getSex() {
    return sex;
}

COLOUR Bunny::getColour() {
    return colour;
}

int Bunny::getAge() {
    return age;
}

bool Bunny::getInfected() {
    return infected;
}

void Bunny::setInfected(bool inf) {
    infected = inf;
    std::cout << name << " is a Infected Bunny!" << std::endl;
    Sleep(100);
}

bool Bunny::incrementAge() {
    age++;
    if ((age == 10 && !infected) || (age == 50 && infected)) {
        dead();
        return true;
    } else {
        return false;
    }
}

void Bunny::printInfo() {
    std::string radio = (infected) ? " Infected " : " Bunny ";
    std::cout << "Name: " << name << ", " << age << " year old, ";
    switch (sex) {
        case SEX::MALE: {
            std::cout << "Male";
            break;
        }
        case SEX::FEMALE: {
            std::cout << "Female";
            break;
        }
    }
    std::cout << ", ";
    switch (colour) {
        case COLOUR::BLACK: {
            std::cout << "Black";
            break;
        }
        case COLOUR::BROWN: {
            std::cout << "Brown";
            break;
        }
        case COLOUR::SPOTTED: {
            std::cout << "Spotted";
            break;
        }
        case COLOUR::WHITE: {
            std::cout << "White";
            break;
        }
    }
    std::cout << radio << std::endl;
}

void Bunny::dead() {
    std::string died = (infected) ? "Infected " : "";
    std::cout << died << name << " has died!" << std::endl;
    Sleep(100);
}