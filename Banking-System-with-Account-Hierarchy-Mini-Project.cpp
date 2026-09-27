#include <iostream>
#include <string>
#include <vector>
#include <memory>
using namespace std;

class Account {
protected:
    int accountNumber;
    string holderName;
    double balance;

public:
    Account(int number, string name, double bal)
        : accountNumber(number),
          holderName(name),
          balance(bal) {}

    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            cout << "Deposited: Rs. " << amount << endl;
        }
    }

    virtual void withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            cout << "Withdrawn: Rs. " << amount << endl;
        } else {
            cout << "Invalid withdrawal!" << endl;
        }
    }

    virtual double calculateInterest() const = 0;

    virtual void display() const {
        cout << "Account No: " << accountNumber << endl;
        cout << "Holder Name: " << holderName << endl;
        cout << "Balance: Rs. " << balance << endl;
    }

    virtual ~Account() = default;
};

class SavingsAccount : public Account {
public:
    SavingsAccount(int number, string name, double bal)
        : Account(number, name, bal) {}

    double calculateInterest() const override {
        return balance * 0.04;
    }

    void display() const override {
        cout << "\n--- Savings Account ---" << endl;
        Account::display();

        cout << "Interest: Rs. "
             << calculateInterest() << endl;
    }
};

class CurrentAccount : public Account {
public:
    CurrentAccount(int number, string name, double bal)
        : Account(number, name, bal) {}

    double calculateInterest() const override {
        return 0.0;
    }

    void display() const override {
        cout << "\n--- Current Account ---" << endl;
        Account::display();

        cout << "Interest: Rs. "
             << calculateInterest() << endl;
    }
};

class FixedDepositAccount : public Account {
private:
    int years;

public:
    FixedDepositAccount(int number, string name,
                        double bal, int y)
        : Account(number, name, bal), years(y) {}

    double calculateInterest() const override {
        return balance * 0.07 * years;
    }

    void display() const override {
        cout << "\n--- Fixed Deposit Account ---" << endl;
        Account::display();

        cout << "Duration: "
             << years << " years" << endl;

        cout << "Interest: Rs. "
             << calculateInterest() << endl;
    }
};

int main() {

    SavingsAccount savings(
        1001, "Rahul", 50000
    );

    CurrentAccount current(
        1002, "Priya", 75000
    );

    FixedDepositAccount fixed(
        1003, "Amit", 100000, 3
    );

    cout << "=== Banking System ===" << endl;

    savings.deposit(5000);
    savings.withdraw(2000);

    current.deposit(10000);
    current.withdraw(5000);

    fixed.deposit(10000);

    savings.display();
    current.display();
    fixed.display();

    return 0;
}
