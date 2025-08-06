#include <iostream>
#include <memory>
using namespace std;

class Behaviour {
public:
    virtual void execute() = 0;
    virtual ~Behaviour() = default;
};

class FlightMechanics : public Behaviour {
public:
    void execute() override {
        cout << "your transport fly" << endl;
    }
};

class Driving : public Behaviour {
public:
    void execute() override {
        cout << "your transport drive" << endl;
    }
};

class Transport {
public:
    virtual void move() = 0;
    virtual ~Transport() = default;
};

class Car : public Transport {
    unique_ptr<Behaviour> ptr;
public:
    Car() {
        ptr = make_unique<Driving>();
    }

    void move() override {
        ptr->execute();
    }
};

class Bike : public Transport {
    unique_ptr<Behaviour> ptr;
public:
    Bike() {
        ptr = make_unique<Driving>();
    }

    void move() override {
        ptr->execute();
    }
};

class Plane : public Transport {
    unique_ptr<Behaviour> ptr;
public:
    Plane() {
        ptr = make_unique<FlightMechanics>();
    }

    void move() override {
        ptr->execute();
    }
};
