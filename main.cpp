#include <iostream>
#include <ctime>
#include <cstdlib>
#include <clocale>

#include <locale>


#include "Cafe.h"
#include "ConcreteDishes.h"
#include "VisitorFactory.h"
#include "Order.h"

int generateVisitorsCount(int hour) {
    if (hour >= 8 && hour < 12) return rand() % 3;
    if (hour >= 12 && hour < 16) return 1 + rand() % 4;
    if (hour >= 16 && hour < 22) return rand() % 3;
    return 0;
}

int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");

    srand(static_cast<unsigned>(time(nullptr)));

    Cafe cafe(900.0);

    cafe.getMenu().addDish(new Omelet());
    cafe.getMenu().addDish(new Porridge());
    cafe.getMenu().addDish(new Tea());
    cafe.getMenu().addDish(new Coffee());
    cafe.getMenu().addDish(new Soup());
    cafe.getMenu().addDish(new CutletWithPuree());
    cafe.getMenu().addDish(new Steak());
    cafe.getMenu().addDish(new Cocktail());

    cafe.addIngredientToStock("Яйцо", 20, 15);
    cafe.addIngredientToStock("Молоко", 5, 80);
    cafe.addIngredientToStock("Масло", 3, 250);
    cafe.addIngredientToStock("Крупа", 4, 120);
    cafe.addIngredientToStock("Сахар", 3, 60);
    cafe.addIngredientToStock("Чай", 1, 500);
    cafe.addIngredientToStock("Кофе", 1, 1200);
    cafe.addIngredientToStock("Бульон", 3, 140);
    cafe.addIngredientToStock("Овощи", 5, 100);
    cafe.addIngredientToStock("Мясо", 5, 450);
    cafe.addIngredientToStock("Картофель", 6, 50);
    cafe.addIngredientToStock("Сироп", 2, 180);
    cafe.addIngredientToStock("Сок", 4, 90);
    cafe.addIngredientToStock("Лед", 5, 20);

    cafe.getMenu().print();

    int visitorId = 1;

    for (int currentTime = 8 * 60; currentTime < 22 * 60; currentTime += 30) {
        int hour = currentTime / 60;
        int visitorsNow = generateVisitorsCount(hour);

        std::cout << "=== Временной слот " << formatTime(currentTime) << " ===\n";
        std::cout << "Новых посетителей: " << visitorsNow << "\n\n";

        for (int i = 0; i < visitorsNow; ++i) {
            int arrival = currentTime + rand() % 30;

            Visitor* visitor = VisitorFactory::createVisitor(visitorId++, arrival);

            std::cout << "Стратегия клиента: "
                      << visitor->getStrategyName()
                      << ", терпение: "
                      << visitor->getPatienceMinutes()
                      << " мин\n";

            std::vector<Dish*> dishes = visitor->makeOrder(cafe.getMenu());

            Order* order = new Order(
                visitor->getId(),
                dishes,
                visitor->getArrivalTime(),
                visitor->getPatienceMinutes()
            );

            cafe.processOrder(order);

            delete order;
            delete visitor;
        }
    }

    cafe.printStock();
    cafe.printReport();

    return 0;
}
