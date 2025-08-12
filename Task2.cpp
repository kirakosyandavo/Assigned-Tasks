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
    virtual void monthEnd()=0;
    virtual void withdraw(double amount)=0; 

};

class SavingsAccount : public BankAccount {
    double interest;

public:
    SavingsAccount(const string& name,double inter, double sum)
        : interest{inter}, BankAccount(name, sum) {}

    void monthEnd() {
        double interAmount = interest * balance;
        balance += interAmount;
        logs.push_back(new Transaction("interest", interAmount, balance));
    }
    void withdraw(double amount){}
};

class CheckingAccount : public BankAccount {
    double overdraft;

public:
    CheckingAccount(const string& name, double sum, double od)
        : BankAccount(name, sum), overdraft{od} {}

 void withdraw(double amount) override {
        if (amount > balance + overdraft) {
            throw invalid_argument("you have not such money");
        }
        balance -= amount;
        logs.push_back(new Transaction("withdrawal", amount, balance));
    }
    void monthEnd(){}
};
int main() {
    SavingsAccount sa("Alice", 1000, 0.02);
    sa.deposit(200);
    sa.withdraw(50);
    sa.monthEnd();
   

    cout << "---\n";

    CheckingAccount ca("Bob", 500, 200);
    ca.withdraw(600);
    ca.deposit(100);
}