#ifndef CUSTOMER_STRATEGY_H
#define CUSTOMER_STRATEGY_H

#include <vector>
#include <string>
#include <cstdlib>
#include "Menu.h"

class CustomerStrategy {
public:
    virtual ~CustomerStrategy() {}

    virtual std::vector<Dish*> chooseDishes(const Menu& menu) const = 0;
    virtual std::string getStrategyName() const = 0;
};

class MorningStrategy : public CustomerStrategy {
public:
    std::vector<Dish*> chooseDishes(const Menu& menu) const override {
        std::vector<Dish*> order;

        Dish* mainDish = nullptr;
        if (rand() % 2 == 0)
            mainDish = menu.createDishByName("Омлет");
        else
            mainDish = menu.createDishByName("Каша");

        Dish* drink = nullptr;
        if (rand() % 2 == 0)
            drink = menu.createDishByName("Чай");
        else
            drink = menu.createDishByName("Кофе");

        if (mainDish) order.push_back(mainDish);
        if (drink) order.push_back(drink);

        return order;
    }

    std::string getStrategyName() const override {
        return "Утренняя стратегия";
    }
};

class LunchStrategy : public CustomerStrategy {
public:
    std::vector<Dish*> chooseDishes(const Menu& menu) const override {
        std::vector<Dish*> order;

        Dish* d1 = menu.createDishByName("Суп");
        Dish* d2 = menu.createDishByName("Котлета с пюре");
        Dish* d3 = nullptr;

        if (rand() % 2 == 0)
            d3 = menu.createDishByName("Чай");
        else
            d3 = menu.createDishByName("Кофе");

        if (d1) order.push_back(d1);
        if (d2) order.push_back(d2);
        if (d3) order.push_back(d3);

        return order;
    }

    std::string getStrategyName() const override {
        return "Обеденная стратегия";
    }
};

class EveningStrategy : public CustomerStrategy {
public:
    std::vector<Dish*> chooseDishes(const Menu& menu) const override {
        std::vector<Dish*> order;

        Dish* d1 = menu.createDishByName("Стейк");
        Dish* d2 = menu.createDishByName("Коктейль");

        if (d1) order.push_back(d1);
        if (d2) order.push_back(d2);

        return order;
    }

    std::string getStrategyName() const override {
        return "Вечерняя стратегия";
    }
};

class HungryStrategy : public CustomerStrategy {
public:
    std::vector<Dish*> chooseDishes(const Menu& menu) const override {
        std::vector<Dish*> order;

        Dish* d1 = menu.createDishByName("Суп");
        Dish* d2 = menu.createDishByName("Стейк");
        Dish* d3 = menu.createDishByName("Кофе");

        if (d1) order.push_back(d1);
        if (d2) order.push_back(d2);
        if (d3) order.push_back(d3);

        return order;
    }

    std::string getStrategyName() const override {
        return "Голодный клиент";
    }
};

#endif
