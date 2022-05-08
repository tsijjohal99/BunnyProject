#pragma once
#include <bunny.h>

#include <list>
#include <memory>

class BunnyManager {
   private:
    std::list<std::shared_ptr<Bunny>> listOfBunnys;

   public:
    BunnyManager();

    bool turnComplete();
    void halfPopulation();
    bool sortList(const std::shared_ptr<Bunny>& a, const std::shared_ptr<Bunny>& b);
};