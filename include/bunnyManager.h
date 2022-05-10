#pragma once
#include <bunny.h>

#include <list>
#include <memory>
#include <vector>

class BunnyManager {
   private:
    std::list<std::shared_ptr<Bunny>> listOfBunnies;
    int gridSize = 60;
    std::vector<std::vector<std::shared_ptr<Bunny>>> gridOfBunnies;
    int noOfBunnies = 0;

   public:
    BunnyManager();

    bool turnComplete();
    void halfPopulation();
    static bool sortList(const std::shared_ptr<Bunny>& a, const std::shared_ptr<Bunny>& b);
    std::vector<std::pair<int, int>> checkSpace(std::pair<int, int> location, bool clear);
    void displayGrid();
    void born(const std::shared_ptr<Bunny>& mother);
    std::shared_ptr<Bunny> infect(const std::shared_ptr<Bunny>& infected);
    void createList();
    void createGrid();
    std::pair<int, int> movement(const std::shared_ptr<Bunny>& rabbit);
    void printList();
};