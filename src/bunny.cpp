#include "bunny.h"

#include <windows.h>

#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <map>
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
    std::string radio = (infected) ? " Infected " : " ";
    std::cout << "Name: " << name << ", " << age << " year old, " << sexString() << ", " << colourString() << radio << "Bunny" << std::endl;
}

void Bunny::dead() {
    std::string died = (infected) ? "Infected " : "";
    std::cout << died << name << " has died!" << std::endl;
    Sleep(100);
}

std::string Bunny::colourString() {
    static const std::map<COLOUR, std::string> ColourMap = {
        {COLOUR::BLACK, "Black"},
        {COLOUR::BROWN, "Brown"},
        {COLOUR::SPOTTED, "Spotted"},
        {COLOUR::WHITE, "White"}};
    return ColourMap.at(colour);
}

std::string Bunny::sexString() {
    static const std::map<SEX, std::string> SexMap = {
        {SEX::MALE, "Male"},
        {SEX::FEMALE, "Female"}};
    return SexMap.at(sex);
}