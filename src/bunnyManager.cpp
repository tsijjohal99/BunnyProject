#include "bunnyManager.h"

#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <memory>
#include <random>

BunnyManager::BunnyManager() {
    gridOfBunnys.resize(gridSize, std::vector<std::shared_ptr<Bunny>>(gridSize));
    for (int i = 0; i < 5; i++) {
        // listOfBunnys.push_back(std::make_shared<Bunny>());
        std::pair<int, int> random = {rand() % 80, rand() % 80};
        if (gridOfBunnys[random.first][random.second] == nullptr) {
            gridOfBunnys[random.first][random.second] = std::make_shared<Bunny>(random);
            noOfBunnys++;
        } else {
            i--;
        }
    }
}

bool BunnyManager::turnComplete() {
    bool maleExistsOfAge = false, femaleCountGreaterThanZero = false;
    listOfBunnys.clear();
    locationOfMothers.clear();
    locationOfInfected.clear();

    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridSize; j++) {
            if (gridOfBunnys[i][j] != nullptr) {
                bool dead = gridOfBunnys[i][j]->incrementAge();  // increase age by 1
                if (dead) {
                    gridOfBunnys[i][j] = nullptr;  // makes dead rabbits
                    noOfBunnys--;
                } else {
                    if (!maleExistsOfAge && gridOfBunnys[i][j]->getSex() == SEX::MALE && !gridOfBunnys[i][j]->getInfected() && gridOfBunnys[i][j]->getAge() >= 2) {  // checks thats there is a male that can reproduce
                        maleExistsOfAge = true;
                    }
                    listOfBunnys.push_back(movement(i, j));
                }
            }
        }
    }

    for (const auto& rabbit : listOfBunnys) {
        if (!rabbit->getInfected() && rabbit->getAge() >= 2 && rabbit->getSex() == SEX::FEMALE) {  // checks how many female can reproduce
            femaleCountGreaterThanZero = true;
            locationOfMothers.push_back(rabbit->getLocation());
        } else if (rabbit->getInfected()) {
            locationOfInfected.push_back(rabbit->getLocation());
        }
    }

    if (maleExistsOfAge && femaleCountGreaterThanZero) {  // newborns
        born();
    }

    infect();

    if (listOfBunnys.size() > 1000) {
        halfPopulation();
    }

    createList();

    if (!listOfBunnys.empty()) {
        listOfBunnys.sort(sortList);  // sorts list
        displayGrid();
        std::cout << noOfBunnys << " bunnys are alive." << std::endl;
        return true;
    } else {
        return false;
    }
}

void BunnyManager::halfPopulation() {
    std::vector<std::shared_ptr<Bunny>> vectorOfBunny(listOfBunnys.size());
    int i = 0;
    for (const auto& rabbit : listOfBunnys) {
        vectorOfBunny[i] = rabbit;
        i++;
    }
    std::random_shuffle(vectorOfBunny.begin(), vectorOfBunny.end());
    for (int j = noOfBunnys / 2; j < noOfBunnys; j++) {
        vectorOfBunny[i]->dead();
    }
    vectorOfBunny.resize(int(noOfBunnys / 2));
    listOfBunnys.clear();
    noOfBunnys = vectorOfBunny.size();
    for (const auto& rabbit : vectorOfBunny) {
        listOfBunnys.push_back(rabbit);
    }
    /*for (int i = 0; i < noOfBunnys / 2; i++) {
        std::list<std::shared_ptr<Bunny>>::iterator it = listOfBunnys.begin();
        advance(it, rand() % listOfBunnys.size());
        (*it)->dead();
        std::pair<int, int> location = (*it)->getLocation();
        gridOfBunnys[location.first][location.second] = nullptr;
        listOfBunnys.erase(it);
    }*/
}

bool BunnyManager::sortList(const std::shared_ptr<Bunny>& a, const std::shared_ptr<Bunny>& b) {
    return a->getAge() < b->getAge();
}

std::vector<std::pair<int, int>> BunnyManager::checkSpace(std::pair<int, int> location, bool clear) {
    std::vector<std::pair<int, int>> coords;
    for (int x = -1; x < 2 && x + location.first >= 0 && x + location.first < 80; x++) {
        for (int y = -1; y < 2 && y + location.second >= 0 && y + location.second < 80; y++) {
            std::pair<int, int> newLocation = {x + location.first, y + location.second};
            if (!(x == 0 && y == 0) &&
                ((gridOfBunnys[newLocation.first][newLocation.second] == nullptr && clear) ||
                 (gridOfBunnys[newLocation.first][newLocation.second] != nullptr && !gridOfBunnys[newLocation.first][newLocation.second]->getInfected() && !clear))) {
                coords.push_back(newLocation);
            }
        }
    }
    return coords;
}

void BunnyManager::displayGrid() {
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridSize; j++) {
            if (gridOfBunnys[i][j] != nullptr) {
                std::cout << gridOfBunnys[i][j]->getSymbol();
            } else {
                std::cout << ".";
            }
            std::cout << " ";
        }
        std::cout << std::endl;
    }
}

void BunnyManager::born() {
    for (const auto& mother : locationOfMothers) {
        std::vector<std::pair<int, int>> spacesFree = checkSpace(mother, true);
        std::random_shuffle(spacesFree.begin(), spacesFree.end());
        try {
            gridOfBunnys[spacesFree[0].first][spacesFree[0].second] = std::make_shared<Bunny>(spacesFree[0]);
            gridOfBunnys[spacesFree[0].first][spacesFree[0].second]->setColour(gridOfBunnys[mother.first][mother.second]->getColour());
            noOfBunnys++;
        } catch (const std::exception& e) {
        }
    }
}

void BunnyManager::infect() {
    for (const auto& infected : locationOfInfected) {
        std::vector<std::pair<int, int>> spacesConvert = checkSpace(infected, false);
        std::random_shuffle(spacesConvert.begin(), spacesConvert.end());
        try {
            gridOfBunnys[spacesConvert[0].first][spacesConvert[0].second]->setInfected(true);
        } catch (const std::exception& e) {
        }
    }
}

void BunnyManager::createList() {
    listOfBunnys.clear();
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridSize; j++) {
            if (gridOfBunnys[i][j] != nullptr) {
                listOfBunnys.push_back(gridOfBunnys[i][j]);
            }
        }
    }
}

std::shared_ptr<Bunny> BunnyManager::movement(int i, int j) {
    std::pair<int, int> location = {i, j};
    std::vector<std::pair<int, int>> spacesFree = checkSpace(location, true);
    std::random_shuffle(spacesFree.begin(), spacesFree.end());
    try {
        gridOfBunnys[spacesFree[0].first][spacesFree[0].second] = gridOfBunnys[location.first][location.second];
        gridOfBunnys[location.first][location.second] = nullptr;
        gridOfBunnys[spacesFree[0].first][spacesFree[0].second]->setLocation(spacesFree[0]);
        return gridOfBunnys[spacesFree[0].first][spacesFree[0].second];
    } catch (const std::exception& e) {
        return gridOfBunnys[i][j];
    }
}