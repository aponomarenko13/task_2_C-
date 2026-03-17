#ifndef CONCRETE_DISHES_H
#define CONCRETE_DISHES_H

#include "Dish.h"

class Omelet : public BreakfastDish {
public:
    Omelet()
        : BreakfastDish("Омлет", 10, 220.0,
                        {{"Яйцо", 3}, {"Молоко", 0.2}, {"Масло", 0.05}}) {}

    Dish* clone() const override {
        return new Omelet(*this);
    }
};

class Porridge : public BreakfastDish {
public:
    Porridge()
        : BreakfastDish("Каша", 8, 180.0,
                        {{"Крупа", 0.15}, {"Молоко", 0.3}, {"Сахар", 0.03}}) {}

    Dish* clone() const override {
        return new Porridge(*this);
    }
};

class Tea : public Drink {
public:
    Tea()
        : Drink("Чай", 3, 90.0,
                {{"Чай", 0.02}, {"Сахар", 0.02}}) {}

    Dish* clone() const override {
        return new Tea(*this);
    }
};

class Coffee : public Drink {
public:
    Coffee()
        : Drink("Кофе", 4, 120.0,
                {{"Кофе", 0.02}, {"Молоко", 0.1}, {"Сахар", 0.02}}) {}

    Dish* clone() const override {
        return new Coffee(*this);
    }
};

class Soup : public FirstCourse {
public:
    Soup()
        : FirstCourse("Суп", 18, 260.0,
                      {{"Бульон", 0.4}, {"Овощи", 0.25}, {"Мясо", 0.15}}) {}

    Dish* clone() const override {
        return new Soup(*this);
    }
};

class CutletWithPuree : public SecondCourse {
public:
    CutletWithPuree()
        : SecondCourse("Котлета с пюре", 22, 380.0,
                       {{"Мясо", 0.2}, {"Картофель", 0.3}, {"Масло", 0.05}}) {}

    Dish* clone() const override {
        return new CutletWithPuree(*this);
    }
};

class Steak : public SecondCourse {
public:
    Steak()
        : SecondCourse("Стейк", 28, 520.0,
                       {{"Мясо", 0.3}, {"Масло", 0.04}, {"Овощи", 0.15}}) {}

    Dish* clone() const override {
        return new Steak(*this);
    }
};

class Cocktail : public Drink {
public:
    Cocktail()
        : Drink("Коктейль", 6, 240.0,
                {{"Сироп", 0.05}, {"Сок", 0.25}, {"Лед", 0.2}}) {}

    Dish* clone() const override {
        return new Cocktail(*this);
    }
};

#endif
