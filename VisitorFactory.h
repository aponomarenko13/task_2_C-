#ifndef VISITOR_FACTORY_H
#define VISITOR_FACTORY_H

#include <cstdlib>
#include "Visitor.h"

class VisitorFactory {
public:
    static CustomerStrategy* createStrategyByHour(int hour) {
        int r = rand() % 100;

        if (hour >= 8 && hour < 12) {
            if (r < 65) return new MorningStrategy();
            if (r < 85) return new HungryStrategy();
            return new LunchStrategy();
        }

        if (hour >= 12 && hour < 17) {
            if (r < 70) return new LunchStrategy();
            if (r < 85) return new HungryStrategy();
            return new MorningStrategy();
        }

        if (hour >= 17 && hour < 22) {
            if (r < 65) return new EveningStrategy();
            if (r < 85) return new HungryStrategy();
            return new LunchStrategy();
        }

        return new LunchStrategy();
    }

    static int generatePatience(const CustomerStrategy* strategy) {
        std::string type = strategy->getStrategyName();

        if (type == "Утренняя стратегия")
            return 18 + rand() % 18;

        if (type == "Обеденная стратегия")
            return 25 + rand() % 21;

        if (type == "Вечерняя стратегия")
            return 20 + rand() % 26;

        return 10 + rand() % 14;
    }

    static Visitor* createVisitor(int id, int currentTime) {
        int hour = currentTime / 60;
        CustomerStrategy* strategy = createStrategyByHour(hour);
        int patience = generatePatience(strategy);

        return new Visitor(id, strategy, patience, currentTime);
    }
};

#endif
