#include <algorithm>
#include <iostream>
#include <string>
#include <map>
#include <tuple>
#include <memory>
#include <vector>

using namespace std;

constexpr auto SIZE = 16;

// Абстрактный класс транспорта
class Transport {
protected:
    int speed;
    int volume;
    double price;
    int distance;
public:
    virtual double sumCost(int mass, int distance) = 0;
    virtual double sumTime(int distance) = 0;
    virtual int getDistance() const = 0;
    virtual ~Transport() = default;
};

class Car : public Transport {
public:
    Car(const tuple<int, int, double>& params, int distance) {
        speed = get<1>(params);
        volume = get<2>(params);
        price = get<0>(params);
        this->distance = distance;
    }
    double sumCost(int mass, int distance) override {
        return (mass / volume) * sumTime(distance) * price;
    }
    double sumTime(int distance) override {
        return distance / speed;
    }
    int getDistance() const override {
        return distance;
    }
};

class Train : public Transport {
public:
    Train(const tuple<int, int, double>& params, int distance) {
        speed = get<1>(params);
        volume = get<2>(params);
        price = get<0>(params);
        this->distance = distance;
    }
    double sumCost(int mass, int distance) override {
        return (mass / volume) * sumTime(distance) * price;
    }
    double sumTime(int distance) override {
        return distance / speed;
    }
    int getDistance() const override {
        return distance;
    }
};

class Plane : public Transport {
public:
    Plane(const tuple<int, int, double>& params, int distance) {
        speed = get<1>(params);
        volume = get<2>(params);
        price = get<0>(params);
        this->distance = distance;
    }
    double sumCost(int mass, int distance) override {
        return (mass / volume) * sumTime(distance) * price;
    }
    double sumTime(int distance) override {
        return distance / speed;
    }
    int getDistance() const override {
        return distance;
    }
};

// Абстрактная фабрика для создания транспорта
class TransportFactory {
public:
    virtual unique_ptr<Transport> createTransport(const tuple<int, int, double>& params, int distance) = 0;
    virtual ~TransportFactory() = default;
};

// Фабрика для создания автомобилей
class CarFactory : public TransportFactory {
public:
    unique_ptr<Transport> createTransport(const tuple<int, int, double>& params, int distance) override {
        return make_unique<Car>(params, distance);
    }
};

// Фабрика для создания поездов
class TrainFactory : public TransportFactory {
public:
    unique_ptr<Transport> createTransport(const tuple<int, int, double>& params, int distance) override {
        return make_unique<Train>(params, distance);
    }
};

// Фабрика для создания самолетов
class PlaneFactory : public TransportFactory {
public:
    unique_ptr<Transport> createTransport(const tuple<int, int, double>& params, int distance) override {
        return make_unique<Plane>(params, distance);
    }
};

// Стратегия расчета стоимости и времени грузоперевозок
class CostStrategy {
public:
    virtual double calculateCost(int mass, int distance) = 0;
    virtual double calculateTime(int distance) = 0;
    virtual ~CostStrategy() = default;
};

class CarCostStrategy : public CostStrategy {
public:
    double calculateCost(int mass, int distance) override {
        return (mass / 50) * (distance / 120) * 100;
    }
    double calculateTime(int distance) override {
        return distance / 120.0;
    }
};

class TrainCostStrategy : public CostStrategy {
public:
    double calculateCost(int mass, int distance) override {
        return (mass / 500) * (distance / 120) * 500;
    }
    double calculateTime(int distance) override {
        return distance / 120.0;
    }
};

class PlaneCostStrategy : public CostStrategy {
public:
    double calculateCost(int mass, int distance) override {
        return (mass / 100) * (distance / 600) * 1100;
    }
    double calculateTime(int distance) override {
        return distance / 680.0;
    }
};

// Компоновщик для маршрутов
class RouteComponent {
public:
    virtual double getTotalCost(int mass) const = 0;
    virtual double getTotalTime() const = 0;
    virtual void add(shared_ptr<RouteComponent> component) {}
    virtual ~RouteComponent() = default;
};

class LeafRoute : public RouteComponent {
private:
    unique_ptr<Transport> transport;
    int distance;
public:
    LeafRoute(unique_ptr<Transport> transport, int distance)
        : transport(move(transport)), distance(distance) {}

    double getTotalCost(int mass) const override {
        return transport->sumCost(mass, distance);
    }

    double getTotalTime() const override {
        return transport->sumTime(distance);
    }
};

class CompositeRoute : public RouteComponent {
private:
    vector<shared_ptr<RouteComponent>> children;
public:
    void add(shared_ptr<RouteComponent> component) override {
        children.push_back(component);
    }

    double getTotalCost(int mass) const override {
        double totalCost = 0;
        for (const auto& child : children) {
            totalCost += child->getTotalCost(mass);
        }
        return totalCost;
    }

    double getTotalTime() const override {
        double totalTime = 0;
        for (const auto& child : children) {
            totalTime += child->getTotalTime();
        }
        return totalTime;
    }
};

int main() {
    // Пример использования фабрик и стратегий
    CarFactory carFactory;
    TrainFactory trainFactory;
    PlaneFactory planeFactory;

    // Пример создания маршрута
    auto car = carFactory.createTransport(make_tuple(100, 60, 50), 100);
    auto train = trainFactory.createTransport(make_tuple(200, 100, 500), 500);
    auto plane = planeFactory.createTransport(make_tuple(500, 300, 100), 1000);

    auto route = make_shared<CompositeRoute>();
    route->add(make_shared<LeafRoute>(move(car), 100));
    route->add(make_shared<LeafRoute>(move(train), 500));
    route->add(make_shared<LeafRoute>(move(plane), 1000));

    // Выбор города
    map<string, int> towns = {
        {"Moscow", 0},
        {"Mozhaisk", 100},
        {"Zvenigorod", 50},
        {"Nizhniy Novgorod", 400},
        {"Dzerzhinsk", 450},
        {"Volgograd", 900},
        {"Kamishin", 1000}
    };

    cout << "Select town:" << endl;
    for (const auto& town : towns) {
        cout << town.first << endl;
    }

    string selectedTown;
    cin >> selectedTown;

    int distance = towns[selectedTown];

    CarCostStrategy carCostStrategy;
    TrainCostStrategy trainCostStrategy;
    PlaneCostStrategy planeCostStrategy;

    cout << "Car Cost: " << carCostStrategy.calculateCost(1000, distance) << endl;
    cout << "Car Time: " << carCostStrategy.calculateTime(distance) << "h" << endl;
    cout << endl;
    cout << "Train Cost: " << trainCostStrategy.calculateCost(1000, distance) << endl;
    cout << "Train Time: " << trainCostStrategy.calculateTime(distance) << "h" << endl;
    cout << endl;
    cout << "Plane Cost: " << planeCostStrategy.calculateCost(1000, distance) << endl;
    cout << "Plane Time: " << planeCostStrategy.calculateTime(distance) << "h" << endl;

    return 0;
}


