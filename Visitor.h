#ifndef VISITOR_H
#define VISITOR_H

#include "CustomerStrategy.h"

class Visitor {
private:
    int id;
    CustomerStrategy* strategy;
    int patienceMinutes;
    int arrivalTime;

public:
    Visitor(int id, CustomerStrategy* strategy, int patienceMinutes, int arrivalTime)
        : id(id), strategy(strategy), patienceMinutes(patienceMinutes), arrivalTime(arrivalTime) {}

    ~Visitor() {
        delete strategy;
    }

    int getId() const { return id; }
    int getPatienceMinutes() const { return patienceMinutes; }
    int getArrivalTime() const { return arrivalTime; }

    std::string getStrategyName() const {
        return strategy->getStrategyName();
    }

    std::vector<Dish*> makeOrder(const Menu& menu) const {
        return strategy->chooseDishes(menu);
    }
};

#endif
