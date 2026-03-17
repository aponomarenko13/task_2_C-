#ifndef INGREDIENT_H
#define INGREDIENT_H

#include <string>

struct IngredientPortion {
    std::string name;
    double amount;
};

struct StockItem {
    double amount;
    double purchasePricePerUnit;
};

#endif
