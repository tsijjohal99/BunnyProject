#pragma once
#include <bunny.h>

#include <list>
#include <memory>
#include <vector>

class BunnyManager {
   private:
    std::list<std::shared_ptr<Bunny>> listOfBunnys;
    int gridSize = 80;
    std::vector<std::vector<std::shared_ptr<Bunny>>> gridOfBunnys;
    int noOfBunnys = 0;
    std::list<std::pair<int, int>> locationOfMothers;
    std::list<std::pair<int, int>> locationOfInfected;

   public:
    BunnyManager();

    bool turnComplete();
    void halfPopulation();
    static bool sortList(const std::shared_ptr<Bunny>& a, const std::shared_ptr<Bunny>& b);
    std::vector<std::pair<int, int>> checkSpace(std::pair<int, int> location, bool clear);
    void displayGrid();
    void born();
    void infect();
    void createList();
    std::shared_ptr<Bunny> movement(int i, int j);
};