#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include <cstring>
#include <sys/shm.h>
using namespace std;
int n1, n2, n3 = 0;

int main() {
    // NSI color codes
    const string RESET = "\033[0m";
    const string RED = "\033[31m";
    const string GREEN = "\033[32m";
    const string YELLOW = "\033[33m";
    const string CYAN = "\033[36m";
    cout << "             " << YELLOW << "CALCULATOR PROCESS" << CYAN << "\n";

    int *shared_memory;
    int shmid;
    shmid = shmget((key_t)1122, sizeof(int), 0666);

    shared_memory = (int*)shmat(shmid, NULL, 0);
    int new_data = *shared_memory - 10;
    *shared_memory = new_data;

    if (shmdt(shared_memory) == -1) {
        perror("shmdt error");
        exit(1);
    }

    int choice, chi;
    do {
        cout << CYAN << "============================================================\n";
        cout << "|                                                          |\n";
        cout << "|             " << YELLOW << "CALCULATOR OPTIONS" << CYAN << "                           |\n";
        cout << "|                                                          |\n";
        cout << "|----------------------------------------------------------|\n";
        cout << "|  " << GREEN << "1)Perform Calculations" << CYAN << "                                  |\n";
        cout << "|  " << GREEN << "0)Exit" << CYAN << "                                                  |\n";
        cout << "|----------------------------------------------------------|\n";
        cout << "|                                                          |\n";
        cout << "============================================================\n" << RESET;
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
        	system("clear");
cout << CYAN << "============================================================\n";
cout << "|                                                          |\n";
cout << "|                    " << YELLOW << "CALCULATOR ACTIONS" << CYAN << "                    |\n";
cout << "|                                                          |\n";
cout << "|----------------------------------------------------------|\n";
cout << "|  " << GREEN << "Press 1 to add" << CYAN << "                                          |\n";
cout << "|  " << GREEN << "Press 2 to subtract" << CYAN << "                                     |\n";
cout << "|  " << GREEN << "Press 3 to multiplication" << CYAN << "                               |\n";
cout << "|  " << GREEN << "Press 4 to division" << CYAN << "                                     |\n";
cout << "|----------------------------------------------------------|\n";
cout << "|                                                          |\n";
cout << "============================================================\n" << RESET;

            cout << "Enter choice: ";
            cin >> chi;
            cout << "Enter first number: ";
            cin >> n1;
            cout << "Enter second number: ";
            cin >> n2;

            if (chi == 1) {
            system("clear");
                n3 = n1 + n2;
                cout << CYAN << "============================================================\n";
                cout << "|                                                          |\n";
                cout << "|             " << YELLOW << "CALCULATION RESULT" << CYAN << "                           |\n";
                cout << "|                                                          |\n";
                cout << "|----------------------------------------------------------|\n";
                cout << "|  " << GREEN << "Addition of " << n1 << " and " << n2 << " = " << n3 << CYAN << "         \n";
                cout << "|----------------------------------------------------------|\n";
                cout << "|                                                          |\n";
                cout << "============================================================\n" << RESET;
                cout << "Press any key to clear the screen: ";
                cin.ignore();
                cin.get();
                system("clear");
            } else if (chi == 2) {
            system("clear");
                n3 = n1 - n2;
                cout << CYAN << "============================================================\n";
                cout << "|                                                          |\n";
                cout << "|             " << YELLOW << "CALCULATION RESULT" << CYAN << "                           |\n";
                cout << "|                                                          |\n";
                cout << "|----------------------------------------------------------|\n";
                cout << "|  " << GREEN << "Subtraction of " << n1 << " and " << n2 << " = " << n3 << CYAN << "     \n";
                cout << "|----------------------------------------------------------|\n";
                cout << "|                                                          |\n";
                cout << "============================================================\n" << RESET;
                cout << "Press any key to clear the screen: ";
                cin.ignore();
                cin.get();
                system("clear");
            } else if (chi == 3) {
            system("clear");
                n3 = n1 * n2;
                cout << CYAN << "============================================================\n";
                cout << "|                                                          |\n";
                cout << "|             " << YELLOW << "CALCULATION RESULT" << CYAN << "                           |\n";
                cout << "|                                                          |\n";
                cout << "|----------------------------------------------------------|\n";
                cout << "|  " << GREEN << "Multiplication of " << n1 << " and " << n2 << " = " << n3 << CYAN << "   \n";
                cout << "|----------------------------------------------------------|\n";
                cout << "|                                                          |\n";
                cout << "============================================================\n" << RESET;
                cout << "Press any key to clear the screen: ";
                cin.ignore();
                cin.get();
                system("clear");
            } else if (chi == 4) {
            system("clear");
                if (n2 == 0) {
                    cout << CYAN << "============================================================\n";
                    cout << "|                                                          |\n";
                    cout << "|             " << YELLOW << "CALCULATION ERROR" << CYAN << "                            |\n";
                    cout << "|                                                          |\n";
                    cout << "|----------------------------------------------------------|\n";
                    cout << "|  " << RED << "Error: Division by zero is not allowed!" << CYAN << "                 |\n";
                    cout << "|----------------------------------------------------------|\n";
                    cout << "|                                                          |\n";
                    cout << "============================================================\n" << RESET;
                    choice = 0; // Exit the loop, consistent with invalid chi handling
                    cout << "Press any key to clear the screen: ";
                    cin.ignore();
                    cin.get();
                    system("clear");
                } else {
                system("clear");
                    n3 = n1 / n2;
                    cout << CYAN << "============================================================\n";
                    cout << "|                                                          |\n";
                cout << "|             " << YELLOW << "CALCULATION RESULT" << CYAN << "                           |\n";
                    cout << "|                                                          |\n";
                    cout << "|----------------------------------------------------------|\n";
                    cout << "|  " << GREEN << "Division of " << n1 << " and " << n2 << " = " << n3 << CYAN << "         \n";
                    cout << "|----------------------------------------------------------|\n";
                    cout << "|                                                          |\n";
                    cout << "============================================================\n" << RESET;
                    cout << "Press any key to clear the screen: ";
                    cin.ignore();
                    cin.get();
                    system("clear");
                }
            } else {
                choice = 0;
            }
        }
        if (choice != 0 && choice != 1) {
            choice = 0;
        }
    } while (choice == 1);

    {
        int *shared_memory;
        int shmid;
        shmid = shmget((key_t)1122, sizeof(int), 0666);
        shared_memory = (int*)shmat(shmid, NULL, 0);
        int new_data = *shared_memory + 10;
        *shared_memory = new_data;
        if (shmdt(shared_memory) == -1) {
            perror("shmdt error");
            exit(1);
        }
        return 0;
    }
    return 0;
}