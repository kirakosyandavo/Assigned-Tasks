#include <iostream>
#include <vector>
using namespace std;

class Expression {
public:
    virtual double evaluate() = 0;
    virtual void print() = 0;
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
};

class Multiplication : public Expression {
    vector<Expression*> vecs;
public:
    Multiplication(Expression* first, Expression* second) {
        vecs.push_back(first);
        vecs.push_back(second);
    }

    double evaluate() override {
        return vecs[0]->evaluate() * vecs[1]->evaluate();
    }

    void print() override {
        cout << evaluate() << endl;
    }
};

class Addition : public Expression {
    vector<Expression*> vecs;
public:
    Addition(Expression* first, Expression* second) {
        vecs.push_back(first);
        vecs.push_back(second);
    }

    double evaluate() override {
        return vecs[0]->evaluate() + vecs[1]->evaluate();
    }

    void print() override {
        cout << evaluate() << endl;
    }
};

class Subtraction : public Expression { 
    vector<Expression*> vecs;
public:
    Subtraction(Expression* first, Expression* second) {
        vecs.push_back(first);
        vecs.push_back(second);
    }

    double evaluate() override {
        return vecs[0]->evaluate() - vecs[1]->evaluate();
    }

    void print() override {
        cout << evaluate() << endl;
    }
};
