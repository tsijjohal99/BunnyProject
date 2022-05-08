#pragma once
#include <iostream>
#include <vector>

#include "colour.h"
#include "sex.h"

class Bunny {
   private:
    SEX sex;
    COLOUR colour;
    int age = 0;
    std::string name;
    bool infected;
    std::vector<std::string> punnyBunnyNames = {
        "Spartacus",
        "Babbity",
        "Nicholas Cage",
        "Harey Biker",
        "Hyacinth Bucket",
        "A New Hop",
        "Bugsey Malone",
        "Hare E. Potter",
        "Thumper",
        "Bugs Bunny",
        "Roger Rabbit",
        "Lola bunny",
        "Rabbit",
        "Oswald the Lucky Rabbit",
        "Peter Rabbit",
        "Buster Baxter",
        "Snowball",
        "Buster Bunny",
        "Bre\'er rabbit",
        "Hazel",
        "E.Aster Bunnymund",
        "Skippy Bunny",
        "Swift Heart rabbit",
        "Vanilla the rabbit",
        "Luke Skyhopper",
        "Cinnabun",
        "Harry Hopper",
        "Rabbit Downey Jnr",
        "Obi Bun Kenobi",
        "David Hasselhop",
        "Nibbler",
        "Barak O\'Bunny",
        "Napoleon Bunnyparte",
        "Rabbit DeNiro",
        "Leonardo DeRabbito",
        "Atilla the Bun",
        "Benedict Cumberbunny",
        "Bun Affleck",
        "Dennis Hopper",
        "Ears McKenzie",
        "Bunny and Clyde",
        "Jumposaurus Rex",
        "Lop Lop",
        "Santa Paws"};

   public:
    Bunny();
    explicit Bunny(COLOUR motherColour);

    SEX getSex();
    COLOUR getColour();
    int getAge();
    bool getInfected();
    void setInfected(bool inf);

    bool incrementAge();
    void printInfo();
    void dead();
    std::string colourString();
    std::string sexString();
};