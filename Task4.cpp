#include <iostream>
#include <vector>
#include<memory>
using namespace std;

class Expression {
public:
    virtual double evaluate() = 0;
    virtual void print() = 0;
    virtual unique_ptr<Expression> clone() const = 0;
    virtual ~Expression() = default; 
};

class Number : public Expression {
    int number;
public:
    Number(int num) : number{num} {}

    double evaluate() override {
        return number;
    }

    void print() override {
        cout << number;
    }
     unique_ptr<Expression> clone() const override {
        return make_unique<Number>(*this);
    }
};

class Multiplication : public Expression {
    unique_ptr<Expression> left;
    unique_ptr<Expression> right;
public:
    Multiplication(unique_ptr<Expression>lef,unique_ptr<Expression>rig):left(move(lef)),right{move(rig)} {}
    double evaluate() override {
        return left->evaluate() * right->evaluate();
    }

    void print() override {
        cout << evaluate() << endl;
    }
    unique_ptr<Expression> clone() const override {
        return make_unique<Multiplication>(*this);
    }
};
class Addition: public Expression {
    unique_ptr<Expression> left;
    unique_ptr<Expression> right;
public:
    Addition(unique_ptr<Expression>lef,unique_ptr<Expression>rig):left(move(lef)),right{move(rig)} {}
    double evaluate() override {
        return left->evaluate() + right->evaluate();
    }

    void print() override {
        cout << evaluate() << endl;
    }
    unique_ptr<Expression> clone() const override {
        return make_unique<Addition>(*this);
    }
};
class Substriction: public Expression {
    unique_ptr<Expression> left;
    unique_ptr<Expression> right;
public:
    Substriction(unique_ptr<Expression>lef,unique_ptr<Expression>rig):left(move(lef)),right{move(rig)} {}
    double evaluate() override {
        return left->evaluate() -right->evaluate();
    }

    void print() override {
        cout << evaluate() << endl;
    }
    unique_ptr<Expression> clone() const override {
        return make_unique<Substriction>(*this);
    }
};
