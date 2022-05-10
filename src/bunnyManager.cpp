#include "bunnyManager.h"

#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <memory>
#include <random>

BunnyManager::BunnyManager() {
    gridOfBunnies.resize(gridSize, std::vector<std::shared_ptr<Bunny>>(gridSize));
    for (int i = 0; i < 5; i++) {
        std::pair<int, int> random = {rand() % gridSize, rand() % gridSize};
        if (std::any_of(listOfBunnies.begin(), listOfBunnies.end(), [random](std::shared_ptr<Bunny> rabbit) { return rabbit->getLocation() == random; })) {
            i--;
        } else {
            listOfBunnies.push_back(std::make_shared<Bunny>(random, rand() % 10));
            noOfBunnies++;
        }
    }
    createGrid();
    printList();
    displayGrid();
}

bool BunnyManager::turnComplete() {
    bool maleExistsOfAge = false;

    std::list<std::shared_ptr<Bunny>> deadRabbits;

    for (auto rabbit : listOfBunnies) {
        bool dead = rabbit->incrementAge();  // increase age by 1
        if (dead) {
            deadRabbits.push_back(rabbit);
            rabbit = nullptr;  // makes dead rabbits
            noOfBunnies--;
        } else {
            if (rabbit->getSymbol() == 'M' && !maleExistsOfAge) {  // checks thats there is a male that can reproduce
                maleExistsOfAge = true;
            }
            rabbit->setLocation(movement(rabbit));
        }
    }

    for (const auto& dead : deadRabbits) {
        auto it = std::find(listOfBunnies.begin(), listOfBunnies.end(), dead);
        if (it != listOfBunnies.end()) {
            listOfBunnies.erase(it);
        }
        gridOfBunnies[dead->getLocation().first][dead->getLocation().second] = nullptr;
    }

    std::list<std::shared_ptr<Bunny>> listOfNewInfected;

    for (auto rabbit : listOfBunnies) {
        if (maleExistsOfAge && rabbit->getSymbol() == 'F') {  // checks how many female can reproduce
            born(rabbit);
        } else if (rabbit->getInfected()) {
            listOfNewInfected.push_back(infect(rabbit));
        }
    }

    for (const auto& infected : listOfNewInfected) {
        if (infected != nullptr) {
            auto it = std::find(listOfBunnies.begin(), listOfBunnies.end(), infected);
            if (it != listOfBunnies.end()) {
                listOfBunnies.erase(it);
            }
            gridOfBunnies[infected->getLocation().first][infected->getLocation().second]->setInfected(true);
            gridOfBunnies[infected->getLocation().first][infected->getLocation().second]->setSymbol('X');
            listOfBunnies.push_back(gridOfBunnies[infected->getLocation().first][infected->getLocation().second]);
        }
    }

    if (listOfBunnies.size() > 1000) {
        halfPopulation();
    }

    if (!listOfBunnies.empty()) {
        listOfBunnies.sort(sortList);  // sorts list
        printList();
        displayGrid();
        std::cout << noOfBunnies << " bunnies are alive." << std::endl;
        return true;
    } else {
        return false;
    }
}

void BunnyManager::halfPopulation() {
    std::vector<std::shared_ptr<Bunny>> vectorOfBunny(listOfBunnies.size());
    int i = 0;
    for (const auto& rabbit : listOfBunnies) {
        vectorOfBunny[i] = rabbit;
        i++;
    }
    std::random_shuffle(vectorOfBunny.begin(), vectorOfBunny.end());
    for (int j = noOfBunnies / 2; j < noOfBunnies; j++) {
        vectorOfBunny[i]->dead();
        gridOfBunnies[vectorOfBunny[i]->getLocation().first][vectorOfBunny[i]->getLocation().second] = nullptr;
    }
    vectorOfBunny.resize(int(noOfBunnies / 2));
    listOfBunnies.clear();
    noOfBunnies = vectorOfBunny.size();
    for (const auto& rabbit : vectorOfBunny) {
        listOfBunnies.push_back(rabbit);
    }
}

bool BunnyManager::sortList(const std::shared_ptr<Bunny>& a, const std::shared_ptr<Bunny>& b) {
    return a->getAge() < b->getAge();
}

std::vector<std::pair<int, int>> BunnyManager::checkSpace(std::pair<int, int> location, bool clear) {
    std::vector<std::pair<int, int>> coords;
    for (int x = -1; x < 2 && x + location.first >= 0 && x + location.first < gridSize; x++) {
        for (int y = -1; y < 2 && y + location.second >= 0 && y + location.second < gridSize; y++) {
            std::pair<int, int> newLocation = {x + location.first, y + location.second};
            if (!(x == 0 && y == 0) &&
                ((gridOfBunnies[newLocation.first][newLocation.second] == nullptr && clear) ||
                 (gridOfBunnies[newLocation.first][newLocation.second] != nullptr && !gridOfBunnies[newLocation.first][newLocation.second]->getInfected() && !clear))) {
                coords.push_back(newLocation);
            }
        }
    }
    return coords;
}

void BunnyManager::displayGrid() {
    for (int i = 0; i <= gridSize; i++) {
        for (int j = 0; j < gridSize && i != gridSize; j++) {
            if (gridOfBunnies[i][j] != nullptr) {
                std::cout << gridOfBunnies[i][j]->getSymbol();
            } else {
                std::cout << ".";
            }
            std::cout << " ";
            if (i == gridSize - 1) {
                // std::cout << j;
            }
        }
        // std::cout << i;
        std::cout << std::endl;
    }
}

void BunnyManager::born(const std::shared_ptr<Bunny>& mother) {
    std::vector<std::pair<int, int>> spacesFree = checkSpace(mother->getLocation(), true);
    try {
        if (spacesFree.empty()) {
            throw std::exception();
        }
        int random = rand() % spacesFree.size();
        gridOfBunnies[spacesFree[random].first][spacesFree[random].second] = std::make_shared<Bunny>(spacesFree[random], mother->getColour());
        listOfBunnies.push_back(gridOfBunnies[spacesFree[random].first][spacesFree[random].second]);
        noOfBunnies++;
    } catch (const std::exception& e) {
    }
}

std::shared_ptr<Bunny> BunnyManager::infect(const std::shared_ptr<Bunny>& infected) {
    std::vector<std::pair<int, int>> spacesConvert = checkSpace(infected->getLocation(), false);
    try {
        if (spacesConvert.empty()) {
            throw std::exception();
        }
        int random = rand() % spacesConvert.size();
        return gridOfBunnies[spacesConvert[random].first][spacesConvert[random].second];
    } catch (const std::exception& e) {
        return nullptr;
    }
}

void BunnyManager::createList() {
    listOfBunnies.clear();
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridSize; j++) {
            if (gridOfBunnies[i][j] != nullptr) {
                listOfBunnies.push_back(gridOfBunnies[i][j]);
            }
        }
    }
}

void BunnyManager::createGrid() {
    gridOfBunnies.clear();
    gridOfBunnies.resize(gridSize, std::vector<std::shared_ptr<Bunny>>(gridSize));
    for (const auto& rabbit : listOfBunnies) {
        gridOfBunnies[rabbit->getLocation().first][rabbit->getLocation().second] = rabbit;
    }
}

std::pair<int, int> BunnyManager::movement(const std::shared_ptr<Bunny>& rabbit) {
    std::vector<std::pair<int, int>> spacesFree = checkSpace(rabbit->getLocation(), true);
    try {
        if (spacesFree.empty()) {
            throw std::exception();
        }
        int random = rand() % spacesFree.size();
        gridOfBunnies[spacesFree[random].first][spacesFree[random].second] = rabbit;
        gridOfBunnies[rabbit->getLocation().first][rabbit->getLocation().second] = nullptr;
        gridOfBunnies[spacesFree[random].first][spacesFree[random].second]->setLocation(spacesFree[random]);
        return spacesFree[random];
    } catch (const std::exception& e) {
        return rabbit->getLocation();
    }
}

void BunnyManager::printList() {
    for (const auto& rabbit : listOfBunnies) {
        rabbit->printInfo();
    }
}