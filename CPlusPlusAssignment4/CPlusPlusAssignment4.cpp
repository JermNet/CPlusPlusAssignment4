#include <iostream>
#include "accountmanager.h"
using namespace std;

void start();
void login();
void createAccount();
void printMainMenu();
void printIntroMenu();

// Declaring here makes variables global
// Create the account manager
AccountManager accountManager;
// Int used to decide what the user wants to do
int action;
// Strings for id passwords before they're saved
string userId, password;
// Double for amount
double amount;

int main() {
    // Call the start function to go through the menus
    start();
    return 0;
}

// Simply adds an extra piece of text prompting the user to enter one of the options and then call the printIntroMenu function
void start() {
    cout << "Please select from from one of the options: " << endl;
    printIntroMenu();
}

// Prints the menu for letting the user login, create an account, and exit. The first two call their respective functions, the third returns to start(),
// which has nothing left to do, so returns to main, which then returns 0, ending the program
void printIntroMenu() {
    while (true) {
        cout << "What would you like to do?" << endl << "[1] Login" << endl << "[2] Create Account" << endl << "[3] Exit" << endl;
        // Check and ignore wrong data type inputs
        while (!(cin >> action)) {
            cout << "Invalid input. Please enter a number." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        if (action == 1) {
            login();
        }
        else if (action == 2) {
            createAccount();
        }
        else if (action == 3) {
            return;
        }
        else {
            cout << "That is not a valid option." << endl;
        }
    }
}

// Asks the user to log in, if the account doesn't exist, text is printed letting the user know, and then ends the function, going back to printIntroMenu()
// If the account does exits, the printMainMenu function is called.
void login() {
    cout << "Please enter your user id: " << endl;
    cin >> userId;
    cout << "Please enter your password: " << endl;
    cin >> password;
    if (accountManager.findAccountByIdAndPassword(userId, password) == nullptr) {
        cout << "That account does not exist, please make an account." << endl;
    }
    else {
        printMainMenu();
    }
}

// If an account exists, the function exits, and it's back to the printIntroMenu() function.
// If an account doesn't exist, it's created, and then it's back to the printIntroMenu() by calling it to make sure the account exists in the current instance
void createAccount() {
    cout << "Please enter a user id: " << endl;
    cin >> userId;
    cout << "Please enter a password: " << endl;
    cin >> password;
    if (!accountManager.addAccount(userId, password)) {
        cout << "That account already exists, please change your username to a unique one." << endl;
    }
    else {
        cout << "Account added successfully!" << endl;
        printIntroMenu();
    }
}

// Prints the main menu, asking the user what they want to do now that they're logged in
void printMainMenu() {
    cout << "You have been logged in!" << endl;
    while (true) {
        cout << "What would you like to do?" << endl << "[1] Deposit" << endl << "[2] Withdraw" << endl << "[3] Request Balance" << endl << "[4] Logout" << endl;
        // Check and ignore wrong data type inputs
        while (!(cin >> action)) {
            cout << "Invalid input. Please enter a number." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        if (action == 1) {
            cout << "How much to deposit?" << endl;
            cin >> amount;
            accountManager.deposit(userId, amount);
            cout << "Your account has been deposited $" << amount << "!" << endl;
        }
        else if (action == 2) {
            cout << "How much to withdraw?" << endl;
            cin >> amount;
            if (accountManager.withdraw(userId, amount)) {
                cout << "Your account has been withdrawn $" << amount << "!" << endl;
            }
            else {
                cout << "Your account does not have enough money to withdraw $" << amount << "!" << endl;
            }
        }
        else if (action == 3) {
            cout << "You have $" << accountManager.getBalance(userId) << "!" << endl;
        }
        else if (action == 4) {
            cout << "You have been logged out!" << endl;
            break;
        }
        else {
            cout << "That is not a valid option." << endl;
        }
    }
}