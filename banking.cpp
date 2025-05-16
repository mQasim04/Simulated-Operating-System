#include <iostream>
#include <string>
#include <iomanip>
#include <sys/shm.h>
using namespace std;

// ANSI colors
#define RESET   "\033[0m"
#define CYAN    "\033[36m"
#define GREEN   "\033[32m"
#define RED     "\033[31m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[32m"
#define MAGENTA "\033[35m"

const int MAX_TRANSACTIONS = 100;

struct Transaction {
    string type;
    double amount;
};

struct Account {
    string name;
    double balance;
    int transaction_count;
    Transaction transactions[MAX_TRANSACTIONS];
};

void printBoxedMessage(const string& msg, const string& color = RESET) {
    cout << color;
    cout << "==================================================" << endl;
    cout << "| " << setw(46) << left << msg << " |" << endl;
    cout << "==================================================" << RESET << endl;
}

void displayMenu() {
    cout << CYAN;
    cout << "+-------------------- MENU ---------------------+" << endl;
    cout << "| 1. Check balance                             |" << endl;
    cout << "| 2. Deposit                                   |" << endl;
    cout << "| 3. Withdraw                                  |" << endl;
    cout << "| 4. Send money                                |" << endl;
    cout << "| 5. Transaction history                       |" << endl;
    cout << "| 6. Exit                                      |" << endl;
    cout << "+----------------------------------------------+" << endl;
    cout << YELLOW << "Enter your choice: " << RESET;
}

double deposit(Account &account, double amount) {
    account.balance += amount;
    account.transactions[account.transaction_count++] = {"Deposit", amount};
    printBoxedMessage("Deposited successfully!", GREEN);
    return account.balance;
}

double withdraw(Account &account, double amount) {
    if (account.balance >= amount) {
        account.balance -= amount;
        account.transactions[account.transaction_count++] = {"Withdraw", amount};
        printBoxedMessage("Withdrawal successful!", GREEN);
    } else {
        printBoxedMessage("Insufficient balance!", RED);
    }
    return account.balance;
}

void sendMoney(Account &sender, Account &receiver, double amount) {
    if (sender.balance >= amount) {
        sender.balance -= amount;
        receiver.balance += amount;
        sender.transactions[sender.transaction_count++] = {"Send", amount};
        receiver.transactions[receiver.transaction_count++] = {"Receive", amount};
        printBoxedMessage("Money sent successfully!", GREEN);
    } else {
        printBoxedMessage("Insufficient balance!", RED);
    }
}

void printTransactionHistory(Account &account) {
    printBoxedMessage("Transaction history for " + account.name, MAGENTA);
    cout << CYAN << left << setw(15) << "Type" << setw(10) << "Amount" << RESET << endl;
    for (int i = 0; i < account.transaction_count; i++) {
        cout << left << setw(15) << account.transactions[i].type
             << "$" << fixed << setprecision(2) << account.transactions[i].amount << endl;
    }
}
void pressAnyKey() {
    cout << endl << YELLOW << "Press Enter to continue..." << RESET;
    cin.ignore();
    cin.get();
    system("clear");
}

int main() {
    printBoxedMessage("WELCOME TO BANKING SYSTEM PROCESS", BLUE);

    // Shared memory access
    int *shared_memory;
    int shmid = shmget((key_t)1122, sizeof(int), 0666);
    shared_memory = (int*)shmat(shmid, NULL, 0);
    *shared_memory -= 2;
    shmdt(shared_memory);
    Account bilal = {"bilal", 1000, 0};
    Account qasim = {"qasim", 500, 0};

    int choice;
    double amount;

    do {
        displayMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                printBoxedMessage("Current balance: $" + to_string(bilal.balance), YELLOW);
                    pressAnyKey();
                break;
            case 2:
                cout << "Enter deposit amount: ";
                cin >> amount;
                deposit(bilal, amount);
                    pressAnyKey();
                break;
            case 3:
                cout << "Enter withdrawal amount: ";
                cin >> amount;
                withdraw(bilal, amount);
                    pressAnyKey();
                break;
            case 4:
                cout << "Enter amount to send to qasim: ";
                cin >> amount;
                sendMoney(bilal, qasim, amount);
                    pressAnyKey();
                break;
            case 5:
                printTransactionHistory(bilal);
                    pressAnyKey();
                break;
            case 6:
                //restore shared memory
                shmid = shmget((key_t)1122, sizeof(int), 0666);
                shared_memory = (int*)shmat(shmid, NULL, 0);
                *shared_memory += 2;
                shmdt(shared_memory);

                printBoxedMessage("Thank you! Goodbye!", GREEN);
                break;
            default:
                printBoxedMessage("Invalid choice!", RED);
        }
    } while (choice != 6);

    return 0;
}
