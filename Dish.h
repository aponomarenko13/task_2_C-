#ifndef DISH_H
#define DISH_H

#include <string>
#include <vector>
#include <iostream>
#include "Ingredient.h"

class Dish {
protected:
    std::string name;
    std::string type;
    int cookMinutes;
    double sellPrice;
    std::vector<IngredientPortion> ingredients;

public:
    Dish(const std::string& name,
         const std::string& type,
         int cookMinutes,
         double sellPrice,
         const std::vector<IngredientPortion>& ingredients)
        : name(name), type(type), cookMinutes(cookMinutes),
          sellPrice(sellPrice), ingredients(ingredients) {}

    virtual ~Dish() {}

    virtual Dish* clone() const = 0;
    virtual std::string getCategoryName() const = 0;

    std::string getName() const { return name; }
    std::string getType() const { return type; }
    int getCookMinutes() const { return cookMinutes; }
    double getSellPrice() const { return sellPrice; }

    const std::vector<IngredientPortion>& getIngredients() const {
        return ingredients;
    }

    virtual void print() const {
        std::cout << "[" << getCategoryName() << "] "
                  << name
                  << ", тип: " << type
                  << ", время: " << cookMinutes
                  << " мин, цена: " << sellPrice << "\n";
    }
};

class BreakfastDish : public Dish {
public:
    BreakfastDish(const std::string& name,
                  int cookMinutes,
                  double sellPrice,
                  const std::vector<IngredientPortion>& ingredients)
        : Dish(name, "Завтрак", cookMinutes, sellPrice, ingredients) {}

    std::string getCategoryName() const override {
        return "BreakfastDish";
    }
};

class FirstCourse : public Dish {
public:
    FirstCourse(const std::string& name,
                int cookMinutes,
                double sellPrice,
                const std::vector<IngredientPortion>& ingredients)
        : Dish(name, "Первое", cookMinutes, sellPrice, ingredients) {}

    std::string getCategoryName() const override {
        return "FirstCourse";
    }
};

class SecondCourse : public Dish {
public:
    SecondCourse(const std::string& name,
                 int cookMinutes,
                 double sellPrice,
                 const std::vector<IngredientPortion>& ingredients)
        : Dish(name, "Второе", cookMinutes, sellPrice, ingredients) {}

    std::string getCategoryName() const override {
        return "SecondCourse";
    }
};

class Drink : public Dish {
public:
    Drink(const std::string& name,
          int cookMinutes,
          double sellPrice,
          const std::vector<IngredientPortion>& ingredients)
        : Dish(name, "Напиток", cookMinutes, sellPrice, ingredients) {}

    std::string getCategoryName() const override {
        return "Drink";
    }
};

#endif
