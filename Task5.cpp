#include <iostream>
#include <memory>
using namespace std;

class IMovable {
public:
    virtual void travelTime(double km) = 0;
    virtual ~IMovable()=default;
};

class IRoadVehicle:public IMovable{
public:
    void travelTime(double km) override {
        cout << "your transport drive" << endl;
    }
};

class IAircraft: public IMovable {
public:
    void travelTime(double km) override {
        cout << "your transport fly" << endl;
    }
};
class IRailVehicle: public IMovable {
public:
    void travelTime(double km) override {
        cout << "your transport rail" << endl;
    }
};
class Transport {
public:
    virtual void move(double km) = 0;
    virtual ~Transport() = default;
};

class Car : public Transport {
    unique_ptr<IMovable> ptr;
public:
    Car() {
        ptr = make_unique<IRoadVehicle>();
    }

    void move(double km) override {
        ptr->travelTime(km);
    }
};

class TRain : public Transport {
    unique_ptr<IMovable> ptr;
public:
    TRain() {
        ptr = make_unique<IRailVehicle>();
    }

    void move(double km) override {
        ptr->travelTime(km);
    }
};

class Plane : public Transport {
    unique_ptr<IMovable> ptr;
public:
    Plane() {
        ptr = make_unique<IAircraft>();
    }

    void move(double km) override {
        ptr->travelTime(km);
    }
};
