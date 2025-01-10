#include "account.h"
#ifndef ACCOUNTMANAGER_H
#define ACCOUNTMANAGER_H
class AccountManager {
private:
    // This is a pointer to the dynamically allocated array
    Account** accounts;
    // The capacity of the array
    int size;
    // The number of accounts in use in the array
    int numberOfAccounts;
public:
    // A constructor, the default size of the array is 5
    AccountManager(int size = 5) {
        this->size = size;
        // Start with no accounts
        numberOfAccounts = 0;
        // Allocate the array dynamically
        accounts = new Account * [size];
    }

    // A function to resize the array, everytime it's full, it increases size to make room for a new account, sets the old accounts to the new accounts,
    // frees the old array, and then points to the new, bigger array
    void resize() {
        size *= 2;
        Account** newAccounts = new Account * [size];
        for (int i = 0; i < numberOfAccounts; i++) {
            newAccounts[i] = accounts[i];
        }
        delete[] accounts;
        accounts = newAccounts;
    }

    // This is a "destructor", used an instance of this class is deleted. In this case, it deletes the accounts and array to avoid memory issues
    ~AccountManager() {
        for (int i = 0; i < numberOfAccounts; i++) {
            delete accounts[i];
        }
        delete[] accounts;
    }

    // An account can only be added if the username doesn't already exist, it's a bool instead of void so that can be used to let the user know
    bool addAccount(string userId, string password, double balance = 0) {
        // If findAccountById returns doesn't return a nullptr, that means the account exists, and so it is not added.
        if (findAccountById(userId) != nullptr) {
            return false;
        }

        // If not returning false, the account can be added, but first we have to check if there's room and resize if there isn't
        if (numberOfAccounts == size) {
            resize();
        }
        // Add the account and increase the numberOfAccounts variable
        accounts[numberOfAccounts] = new Account(userId, password, balance);
        numberOfAccounts++;
        return true;
    }

    // Find an account by its userId
    Account* findAccountById(string userId) {
        for (int i = 0; i < numberOfAccounts; i++) {
            if (accounts[i]->getUserId() == userId) {
                return accounts[i];
            }
        }
        // Reutrn a null pointer if there is no such account
        return nullptr;
    }

    // Find an account by userId AND password
    Account* findAccountByIdAndPassword(string userId, string password) {
        for (int i = 0; i < numberOfAccounts; i++) {
            if (accounts[i]->getUserId() == userId && accounts[i]->getPassword() == password) {
                return accounts[i];
            }
        }
        return nullptr;
    }

    // Deposit in an account (userIds are unique, so we can find just by that)
    bool deposit(string userId, double amount) {
        if (findAccountById(userId) != nullptr) {
            findAccountById(userId)->deposit(amount);
            return true;
        }
        return false;
    }

    // Withdraw from an account
    bool withdraw(string userId, double amount) {
        if (findAccountById(userId) != nullptr && findAccountById(userId)->withdraw(amount)) {
            return true;
        }
        return false;
    }

    // Get the balance from an account
    double getBalance(string userId) {
        if (findAccountById(userId) != nullptr) {
            return findAccountById(userId)->getBalance();
        }
        return 0;
    }
};
#endif //ACCOUNTMANAGER_H
