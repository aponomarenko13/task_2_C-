#ifndef CAFE_H
#define CAFE_H

#include <map>
#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <algorithm>
#include "Menu.h"
#include "Ingredient.h"
#include "Order.h"

inline std::string formatTime(int minutesFromStartOfDay) {
    int h = minutesFromStartOfDay / 60;
    int m = minutesFromStartOfDay % 60;

    std::ostringstream out;
    out << std::setfill('0') << std::setw(2) << h
        << ":" << std::setw(2) << m;
    return out.str();
}

class Cafe {
private:
    Menu menu;
    std::map<std::string, StockItem> stock;

    double chefHourCost;
    int kitchenFreeAt;

    double ingredientExpenses;
    double laborExpenses;
    double revenue;
    int servedOrders;
    int canceledOrders;
    int utilizedDishes;

    void ensureIngredient(const std::string& ingredientName, double neededAmount) {
        if (stock.find(ingredientName) == stock.end()) {
            stock[ingredientName] = {0.0, 100.0};
        }

        double current = stock[ingredientName].amount;
        if (current < neededAmount) {
            double toBuy = neededAmount - current + 2.0;
            ingredientExpenses += toBuy * stock[ingredientName].purchasePricePerUnit;
            stock[ingredientName].amount += toBuy;
        }
    }

    void spendIngredientsForDish(const Dish* dish) {
        const std::vector<IngredientPortion>& ing = dish->getIngredients();

        for (size_t i = 0; i < ing.size(); ++i) {
            ensureIngredient(ing[i].name, ing[i].amount);
            stock[ing[i].name].amount -= ing[i].amount;
        }
    }

public:
    Cafe(double chefHourCost)
        : chefHourCost(chefHourCost),
          kitchenFreeAt(8 * 60),
          ingredientExpenses(0.0),
          laborExpenses(0.0),
          revenue(0.0),
          servedOrders(0),
          canceledOrders(0),
          utilizedDishes(0) {}

    Menu& getMenu() {
        return menu;
    }

    void addIngredientToStock(const std::string& name, double amount, double pricePerUnit) {
        stock[name] = {amount, pricePerUnit};
    }

    void printStock() const {
        std::cout << "\n------ СКЛАД ------\n";
        for (std::map<std::string, StockItem>::const_iterator it = stock.begin(); it != stock.end(); ++it) {
            std::cout << it->first
                      << ": остаток=" << it->second.amount
                      << ", закупка/ед=" << it->second.purchasePricePerUnit << "\n";
        }
        std::cout << "-------------------\n";
    }

    void processOrder(Order* order) {
        std::cout << "Клиент #" << order->getCustomerId()
                  << " пришел в " << formatTime(order->getArrivalTime())
                  << " и заказал: " << order->getOrderText() << "\n";

        const std::vector<Dish*>& dishes = order->getDishes();
        for (size_t i = 0; i < dishes.size(); ++i) {
            spendIngredientsForDish(dishes[i]);
            laborExpenses += (dishes[i]->getCookMinutes() / 60.0) * chefHourCost;
        }

        int startCook = std::max(kitchenFreeAt, order->getArrivalTime());
        int finishCook = startCook + order->getTotalCookTime();
        kitchenFreeAt = finishCook;

        int waitingTime = finishCook - order->getArrivalTime();

        std::cout << "  Начало готовки: " << formatTime(startCook) << "\n";
        std::cout << "  Готово будет:   " << formatTime(finishCook) << "\n";
        std::cout << "  Клиент готов ждать: " << order->getPatienceMinutes() << " мин\n";
        std::cout << "  Реальное ожидание:  " << waitingTime << " мин\n";

        if (waitingTime > order->getPatienceMinutes()) {
            std::cout << "  ИНЦИДЕНТ: клиент не дождался заказа. Блюда утилизированы.\n\n";
            canceledOrders++;
            utilizedDishes += static_cast<int>(dishes.size());
        } else {
            std::cout << "  Заказ выдан клиенту.\n\n";
            servedOrders++;
            revenue += order->getTotalSellPrice();
        }
    }

    void printReport() const {
        std::cout << "\n=========== ИТОГИ ДНЯ ===========\n";
        std::cout << "Выручка:              " << revenue << "\n";
        std::cout << "Расходы на ингредиенты: " << ingredientExpenses << "\n";
        std::cout << "Расходы на повара:      " << laborExpenses << "\n";
        std::cout << "Прибыль:              " << (revenue - ingredientExpenses - laborExpenses) << "\n";
        std::cout << "Обслужено заказов:    " << servedOrders << "\n";
        std::cout << "Отменено заказов:     " << canceledOrders << "\n";
        std::cout << "Утилизировано блюд:   " << utilizedDishes << "\n";
        std::cout << "=================================\n";
    }
};

#endif
