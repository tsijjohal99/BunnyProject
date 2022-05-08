#include "bunnyManager.h"

#include <cstdio>
#include <cstdlib>
#include <ctime>

BunnyManager::BunnyManager() {
    for (int i = 0; i < 5; i++) {
        listOfBunnys.push_back(std::make_shared<Bunny>());
    }
}

bool BunnyManager::turnComplete() {
    bool maleExistsOfAge = false;
    int femaleCount = 0, radioactiveCount = 0;
    std::list<std::shared_ptr<Bunny>> deadBunnys;

    for (std::shared_ptr<Bunny> rabbit : listOfBunnys) {
        bool dead = rabbit->incrementAge();  // increase age by 1
        if (dead) {
            deadBunnys.push_back(rabbit);  // makes a list of dead rabbits
        } else {
            if (!rabbit->getInfected() && rabbit->getAge() >= 2) {
                if (!maleExistsOfAge && rabbit->getSex() == SEX::MALE) {  // checks thats there is a male that can reproduce
                    maleExistsOfAge = true;
                } else if (rabbit->getSex() == SEX::FEMALE) {  // checks how many female can reproduce
                    femaleCount++;
                }
            } else if (rabbit->getInfected()) {
                radioactiveCount++;
            }
        }
    }

    for (const std::shared_ptr<Bunny>& rabbit : deadBunnys) {  // removes dead rabbits
        std::list<std::shared_ptr<Bunny>>::iterator it = listOfBunnys.begin();
        while (it != listOfBunnys.end()) {
            if (*it == rabbit) {
                listOfBunnys.erase(it);
                break;
            } else {
                ++it;
            }
        }
    }

    if (maleExistsOfAge && femaleCount > 0) {
        for (std::shared_ptr<Bunny> rabbit : listOfBunnys) {
            if (--femaleCount >= 0) {
                listOfBunnys.push_back(std::make_shared<Bunny>(rabbit->getColour()));
            }
        }
    }

    for (int i = 0; i < radioactiveCount; i++) {
        for (std::shared_ptr<Bunny> rabbit : listOfBunnys) {
            if (!rabbit->getInfected()) {
                rabbit->setInfected(true);
                break;
            }
        }
    }

    if (listOfBunnys.size() > 1000) {
        halfPopulation();
    }

    if (!listOfBunnys.empty()) {
        listOfBunnys.sort();  // sorts list
        for (const std::shared_ptr<Bunny>& rabbit : listOfBunnys) {
            rabbit->printInfo();
        }
        std::cout << listOfBunnys.size() << " bunnys are alive." << std::endl;
        return true;
    } else {
        return false;
    }
}

void BunnyManager::halfPopulation() {
    for (int i = 0; i < listOfBunnys.size() / 2; i++) {
        std::list<std::shared_ptr<Bunny>>::iterator it = listOfBunnys.begin();
        advance(it, rand() % listOfBunnys.size());
        (*it)->dead();
        listOfBunnys.erase(it);
    }
}