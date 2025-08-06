#include <iostream>
#include <vector>
using namespace std;

struct Transaction {
    string type;
    double amount;
    double postBalance;

    Transaction(const string& typ, double sum, double balance)
        : type{typ}, amount{sum}, postBalance{balance} {}
};

class BankAccount {
protected:
    double balance;
    string name;
    vector<Transaction*> logs;

public:
    virtual void deposit(double amount) {
        balance += amount;
        logs.push_back(new Transaction("deposit", amount, balance));
    }

    virtual bool withdraw(double amount) {
        if (amount > balance) {
            return false;
        }
        balance -= amount;
        logs.push_back(new Transaction("withdrawal", amount, balance));
        return true;
    }

    virtual double balanceAmount() const {
        return balance;
    }

    BankAccount(const string& anun, double sum) : name{anun}, balance{sum} {}

    BankAccount(const BankAccount& other) {
        balance = other.balance;
        name = other.name;
        for (int i = 0; i < other.logs.size(); i++) {
            logs.push_back(new Transaction(*other.logs[i]));
        }
    }

    BankAccount& operator=(const BankAccount& other) {
        if (this == &other) {
            return *this;
        }
        for (int i = 0; i < logs.size(); i++) {
            delete logs[i];
        }
        logs.clear();
        for (int i = 0; i < other.logs.size(); i++) {
            logs.push_back(new Transaction(*other.logs[i]));
        }
        balance = other.balance;
        name = other.name;
        return *this;
    }

    BankAccount(BankAccount&& other) noexcept {
        balance = other.balance;
        name = move(other.name);
        logs = move(other.logs);
        other.logs.clear();
    }

    BankAccount& operator=(BankAccount&& other) noexcept {
        if (this == &other) {
            return *this;
        }
        balance = other.balance;
        name = move(other.name);
        for (int i = 0; i < logs.size(); i++) {
            delete logs[i];
        }
        logs.clear();
        logs = move(other.logs);
        other.logs.clear();
        return *this;
    }

    virtual ~BankAccount() {
        for (int i = 0; i < logs.size(); i++) {
            delete logs[i];
        }
        logs.clear();
    }
};

class SasvingsAccount : public BankAccount {
    double interest;

public:
    SasvingsAccount(double inter, string name, double sum)
        : interest{inter}, BankAccount(name, sum) {}

    void addinterest() {
        double interAmount = interest * balance;
        balance += interAmount;
        logs.push_back(new Transaction("interest", interAmount, balance));
    }
};

class CheckingAccount : public BankAccount {
    double overdraft;

public:
    CheckingAccount(const string& name, double sum, double od)
        : BankAccount(name, sum), overdraft{od} {}

    bool withdraw(double amount) override {
        if (amount > balance + overdraft) {
            return false;
        }
        balance -= amount;
        logs.push_back(new Transaction("withdrawal", amount, balance));
        return true;
    }
};
