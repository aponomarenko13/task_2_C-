#ifndef ORDER_H
#define ORDER_H

#include <vector>
#include <string>
#include <sstream>
#include "Dish.h"

class Order {
private:
    int customerId;
    std::vector<Dish*> dishes;
    int arrivalTime;
    int patienceMinutes;

public:
    Order(int customerId,
          const std::vector<Dish*>& dishes,
          int arrivalTime,
          int patienceMinutes)
        : customerId(customerId),
          dishes(dishes),
          arrivalTime(arrivalTime),
          patienceMinutes(patienceMinutes) {}

    ~Order() {
        for (size_t i = 0; i < dishes.size(); ++i) {
            delete dishes[i];
        }
        dishes.clear();
    }

    int getCustomerId() const { return customerId; }
    int getArrivalTime() const { return arrivalTime; }
    int getPatienceMinutes() const { return patienceMinutes; }

    const std::vector<Dish*>& getDishes() const {
        return dishes;
    }

    int getTotalCookTime() const {
        int total = 0;
        for (size_t i = 0; i < dishes.size(); ++i) {
            total += dishes[i]->getCookMinutes();
        }
        return total;
    }

    double getTotalSellPrice() const {
        double total = 0.0;
        for (size_t i = 0; i < dishes.size(); ++i) {
            total += dishes[i]->getSellPrice();
        }
        return total;
    }

    std::string getOrderText() const {
        std::ostringstream out;
        for (size_t i = 0; i < dishes.size(); ++i) {
            out << dishes[i]->getName();
            if (i + 1 < dishes.size()) {
                out << ", ";
            }
        }
        return out.str();
    }
};

#endif
