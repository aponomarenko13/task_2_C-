#ifndef MENU_H
#define MENU_H

#include <vector>
#include <string>
#include <iostream>
#include "Dish.h"

class Menu {
private:
    std::vector<Dish*> dishes;

public:
    ~Menu() {
        for (size_t i = 0; i < dishes.size(); ++i) {
            delete dishes[i];
        }
        dishes.clear();
    }

    void addDish(Dish* dish) {
        dishes.push_back(dish);
    }

    Dish* createDishByName(const std::string& name) const {
        for (size_t i = 0; i < dishes.size(); ++i) {
            if (dishes[i]->getName() == name) {
                return dishes[i]->clone();
            }
        }
        return nullptr;
    }

    void print() const {
        std::cout << "------ МЕНЮ ------\n";
        for (size_t i = 0; i < dishes.size(); ++i) {
            dishes[i]->print();
        }
        std::cout << "------------------\n\n";
    }
};

#endif
