#include <string>
#include <cmath>
using namespace std;
#ifndef ACCOUNT_H
#define ACCOUNT_H
class Account {
private:
    string userId, password;
    double balance;
public:
    // Constructor for if there's an initial balance or not
    Account(string userId, string password, double balance = 0) {
        this->userId = userId;
        this->password = password;
        this->balance = balance;
    }

    // Setters and getters, balance returns to 2 decimal places
    string getUserId() {
        return userId;
    }

    string setUserId(string userId) {
        this->userId = userId;
    }

    string getPassword() {
        return password;
    }

    string setPassword(string password) {
        this->password = password;
    }

    double getBalance() {
        return round(balance * 100.0) / 100.0;
    }

    void setBalance(double balance) {
        this->balance = balance;
    }

    void deposit(double amount) {
        this->balance += amount;
    }

    // Uses can withdraw function for more modularity, this also returns true or false so whatever uses this function can use the true/false to let the user know if it worked or not
    bool withdraw(double amount) {
        if (canWithdraw(amount)) {
            balance -= amount;
            return true;
        }
        return false;
    }

    bool canWithdraw(double amount) {
        if (amount > balance) {
            return false;
        }
        return true;
    }
};
#endif //ACCOUNT_H
