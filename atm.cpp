#include <iostream>
#include <iomanip>
#include <string>
#include <limits> // Include for numeric_limits
#include <ctime>
#include <termios.h>
#include <unistd.h>
using namespace std;
const int VALID_ACCOUNT = 221215;
const string VALID_PIN = "221215";

void clearScreen() {
    cout << "\033[2J\033[1;1H"; // ANSI escape sequence to clear screen
}

void showLogo() {
    cout << "\n\t\t\t + ************** WELCOME TO *************** + "
         << "\n\t\t\t _____________________________________________"
         << "\n\t\t\t|                                             |"
         << "\n\t\t\t|              ATM SIMULATION                 |"
         << "\n\t\t\t|_____________________________________________|";
}

void showMenu() {
    clearScreen();
    showLogo();
    cout << "\n\n\t\t\t  MAIN MENU";
    cout << "\n\t\t\t  [1] Withdrawal";
    cout << "\n\t\t\t  [2] Deposit";
    cout << "\n\t\t\t  [3] Balance Check";
    cout << "\n\t\t\t  [4] Funds Transfer";
    cout << "\n\t\t\t  [5] Exit";
    cout << "\n\t\t\t  Enter your choice: ";
}

void welcomeScreen() {
    cout << "\n\t\t\t _____________________________________________"
         << "\n\t\t\t|                                             |"
         << "\n\t\t\t|              WELCOME TO ATM                 |"
         << "\n\t\t\t|_____________________________________________|";
    cin.ignore(); // Ignore any pending newline characters
    cin.get(); // Wait for user to press Enter
}

void receipt(double amount, double balance, const string &transactionType) {
    cout << "\n\t\t\t|TRANSACTION:         " << transactionType
         << "\n\t\t\t|AMOUNT:              " << amount
         << "\n\t\t\t|CURRENT BAL:         " << balance
         << "\n\t\t\t|AVAILABLE BAL:       " << balance
         << "\n\t\t\t|DO NOT DISCLOSE YOUR PIN TO OTHERS           |"
         << "\n\t\t\t|_____________________________________________|";
}

void waiting(unsigned int mseconds) {
    clock_t goal = mseconds + clock();
    while (goal > clock());
}

void handleWithdrawal(double &checkingBalance, double &savingsBalance) {
    int choice;
    double amount;
 clearScreen();
    showLogo();
    cout << "\n\n\t\t\t  WITHDRAWAL TRANSACTION";
    cout << "\n\t\t\t  [1] From Checking";
    cout << "\n\t\t\t  [2] From Savings";
    cout << "\n\t\t\t  [3] Quick Cash (Php 500)";
    cout << "\n\t\t\t  [4] Back to Main Menu";
    cout << "\n\t\t\t  Enter your choice: ";
    cin >> choice;

    switch(choice) {
        case 1:
            cout << "\n\t\t\tEnter the amount: Php ";
            cin >> amount;
            if (amount <= checkingBalance) {
                checkingBalance -= amount;
                receipt(amount, checkingBalance, "Checking Withdrawal");
            } else {
                cout << "\n\t\t\tInsufficient funds!";
            }
            break;
        case 2:
            cout << "\n\t\t\tEnter the amount: Php ";
            cin >> amount;
            if (amount <= savingsBalance) {
                savingsBalance -= amount;
                receipt(amount, savingsBalance, "Savings Withdrawal");
            } else {
                cout << "\n\t\t\tInsufficient funds!";
            }
            break;
        case 3:
            amount = 500;
            if (amount <= checkingBalance) {
                checkingBalance -= amount;
                receipt(amount, checkingBalance, "Quick Cash");
            } else {
                cout << "\n\t\t\tInsufficient funds!";
            }
            break;
        case 4:
            return;
        default:
            cout << "\n\t\t\tInvalid choice!";
            break;
    }
    waiting(3000);
}
void handleDeposit(double &checkingBalance, double &savingsBalance) {
    int choice;
    double amount;

    clearScreen();
    showLogo();
    cout << "\n\n\t\t\t  DEPOSIT TRANSACTION";
    cout << "\n\t\t\t  [1] To Checking";
    cout << "\n\t\t\t  [2] To Savings";
    cout << "\n\t\t\t  [3] Back to Main Menu";
    cout << "\n\t\t\t  Enter your choice: ";
    cin >> choice;

    switch(choice) {
        case 1:
            cout << "\n\t\t\tEnter the deposit amount: Php ";
            cin >> amount;
            checkingBalance += amount;
            receipt(amount, checkingBalance, "Checking Deposit");
            break;
        case 2:
            cout << "\n\t\t\tEnter the deposit amount: Php ";
            cin >> amount;
            savingsBalance += amount;
            receipt(amount, savingsBalance, "Savings Deposit");
            break;
        case 3:
            return;
        default:
            cout << "\n\t\t\tInvalid choice!";
            break;
    }
    waiting(3000);
}

void handleBalanceCheck(double checkingBalance, double savingsBalance) {
    int choice;

    clearScreen();
    showLogo();
    cout << "\n\n\t\t\t  BALANCE CHECK";
    cout << "\n\t\t\t  [1] From Checking";
    cout << "\n\t\t\t  [2] From Savings";
    cout << "\n\t\t\t  [3] Back to Main Menu";
    cout << "\n\t\t\t  Enter your choice: ";
    cin >> choice;

    switch(choice) {
        case 1:
            cout << "\n\t\t\tAvailable Balance in Checking: Php " << checkingBalance;
            break;
        case 2:
            cout << "\n\t\t\tAvailable Balance in Savings: Php " << savingsBalance;
            break;
        case 3:
            return;
        default:
            cout << "\n\t\t\tInvalid choice!";
            break;
    }
    waiting(3000);
}

void handleFundsTransfer(double &checkingBalance, double &savingsBalance) {
    int choice;
    double amount;

    clearScreen();
    showLogo();
    cout << "\n\n\t\t\t  FUNDS TRANSFER";
    cout << "\n\t\t\t  [1] From Checking to Savings";
    cout << "\n\t\t\t  [2] From Savings to Checking";
    cout << "\n\t\t\t  [3] Back to Main Menu";
    cout << "\n\t\t\t  Enter your choice: ";
    cin >> choice;

    switch(choice) {
        case 1:
            cout << "\n\t\t\tEnter the amount to transfer: Php ";
            cin >> amount;
            if (amount <= checkingBalance) {
                checkingBalance -= amount;
                savingsBalance += amount;
                receipt(amount, checkingBalance, "Transfer to Savings");
            } else {
                cout << "\n\t\t\tInsufficient funds!";
            }
            break;
        case 2:
            cout << "\n\t\t\tEnter the amount to transfer: Php ";
            cin >> amount;
            if (amount <= savingsBalance) {
                savingsBalance -= amount;
                checkingBalance += amount;
                receipt(amount, savingsBalance, "Transfer to Checking");
            } else {
                cout << "\n\t\t\tInsufficient funds!";
            }
            break;
        case 3:
            return;
        default:
            cout << "\n\t\t\tInvalid choice!";
            break;
    }
    waiting(3000);
}
int main() {
    int account;
    string pin;
    char ch;
    double checkingBalance = 20000.0;
    double savingsBalance = 10000.0;

    cout << fixed << showpoint << setprecision(2);

    welcomeScreen();
    clearScreen();

    showLogo();
    cout << "\n\n\t\t\t  Please type your Bank Account Number: ";
    cin >> account;
    cout << "\n\t\t\t  Please type Personal Identification Number (PIN): ";

    struct termios old, current;
    tcgetattr(STDIN_FILENO, &old);
    current = old;
    current.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &current);

    while((ch = getchar()) != '\n') {
        pin.push_back(ch);
        cout << '*';
    }

    tcsetattr(STDIN_FILENO, TCSANOW, &old); // Restore terminal settings

    if (account != VALID_ACCOUNT || pin != VALID_PIN) {
        cout << "\n\t\t\tInvalid Bank Account and PIN. Please try again!" << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
        cin.get(); // Wait for user to press Enter
        return 1;
    }

    int choice;
    do {
        showMenu();
        cin >> choice;
        switch(choice) {
            case 1:
                handleWithdrawal(checkingBalance, savingsBalance);
                break;
            case 2:
                handleDeposit(checkingBalance, savingsBalance);
                break;
            case 3:
                handleBalanceCheck(checkingBalance, savingsBalance);
                break;
            case 4:
                handleFundsTransfer(checkingBalance, savingsBalance);
                break;
            case 5:
                cout << " \n\t\t\t Brought To You By code-projects.org" << endl << endl;
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
                cin.get(); // Wait for user to press Enter
                break;
            default:
                cout << "\n\t\t\tInvalid choice!";
                break;
        }
    } while(choice != 5);

    return 0;
}
