#include "bunny.h"

#include <windows.h>

#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <map>
#include <string>

Bunny::Bunny(std::pair<int, int> loc) : location(loc) {
    sex = rand() % 2 ? SEX::MALE : SEX::FEMALE;
    colour = (COLOUR)(rand() % 4);
    age = 0;
    infected = rand() % 100 < 2 ? true : false;
    if (!infected) {
        symbol = sex == SEX::MALE ? 'm' : 'f';
    } else {
        symbol = 'X';
    }
    name = sex == SEX::MALE ? maleBunnyNames[rand() % maleBunnyNames.size()] : femaleBunnyNames[rand() % femaleBunnyNames.size()];
    std::string born = (infected) ? "Infected Bunny " : "";
    std::cout << born << name << " was born!" << std::endl;
    Sleep(100);
}

Bunny::Bunny(std::pair<int, int> loc, int old) : location(loc), age(old) {
    sex = rand() % 2 ? SEX::MALE : SEX::FEMALE;
    colour = (COLOUR)(rand() % 4);
    infected = rand() % 100 < 2 ? true : false;
    if (!infected) {
        symbol = sex == SEX::MALE ? (age >= 2 ? 'M' : 'm') : (age >= 2 ? 'F' : 'f');
    } else {
        symbol = 'X';
    }
    name = sex == SEX::MALE ? maleBunnyNames[rand() % maleBunnyNames.size()] : femaleBunnyNames[rand() % femaleBunnyNames.size()];
    std::string born = (infected) ? "Infected Bunny " : "";
    std::cout << born << name << " was born!" << std::endl;
    Sleep(100);
}

Bunny::Bunny(std::pair<int, int> loc, COLOUR motherColour) : location(loc), colour(motherColour) {
    sex = rand() % 2 ? SEX::MALE : SEX::FEMALE;
    age = 0;
    infected = rand() % 100 < 2 ? true : false;
    if (!infected) {
        symbol = sex == SEX::MALE ? 'm' : 'f';
    } else {
        symbol = 'X';
    }
    name = sex == SEX::MALE ? maleBunnyNames[rand() % maleBunnyNames.size()] : femaleBunnyNames[rand() % femaleBunnyNames.size()];
    std::string born = (infected) ? "Infected Bunny " : "";
    std::cout << born << name << " was born!" << std::endl;
    Sleep(100);
}

char Bunny::getSymbol() {
    return symbol;
}

void Bunny::setSymbol(char sym) {
    symbol = sym;
}

std::pair<int, int> Bunny::getLocation() {
    return location;
}

void Bunny::setLocation(std::pair<int, int> loc) {
    location = loc;
}

SEX Bunny::getSex() {
    return sex;
}

COLOUR Bunny::getColour() {
    return colour;
}

void Bunny::setColour(COLOUR col) {
    colour = col;
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
    if ((age >= 10 && !infected) || (age >= 50 && infected)) {
        dead();
        return true;
    } else {
        if (age == 2 && !infected) {
            symbol = sex == SEX::MALE ? 'M' : 'F';
        }
        return false;
    }
}

void Bunny::printInfo() {
    std::string radio = (infected) ? " Infected Bunny " : " Bunny ";
    std::cout << "Name: " << name << ", " << age << " year old, " << sexString() << ", " << colourString() << radio << std::endl;
}

void Bunny::dead() {
    std::string died = (infected) ? "Infected Bunny " : "";
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