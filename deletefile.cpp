#include<iostream>
#include<cstring>
#include<fstream>
#include<stdio.h>
#include<unistd.h>
#include<sys/shm.h>
using namespace std;

#define RESET   "\033[0m"
#define GREEN   "\033[32m"
#define CYAN    "\033[36m"
#define YELLOW  "\033[93m"
#define RED     "\033[31m"
#define BOLD    "\033[1m"

int main()
{
    cout << CYAN << "\t\t───────────────────────────────────────" << RESET << endl;
    cout << BOLD << "\t\tWELCOME TO FILE DELETION PROCESS!" << RESET << endl;
    cout << CYAN << "\t\t───────────────────────────────────────" << RESET << endl;

    int choice;
    int *shared_memory;
    int shmid = shmget((key_t)1122, sizeof(int), 0666);
    shared_memory = (int*)shmat(shmid, NULL, 0);
    *shared_memory -= 3;
    shmdt(shared_memory);

    char fn[35];
    do {
        cout << YELLOW << "Press 1 to delete file" << RESET << endl;
        cout << YELLOW << "Press 0 to exit" << RESET << endl;
        cin >> choice;

        if (choice == 1) {
            cout << "Enter File Name: ";
            cin >> fn;

            FILE* file = fopen(fn, "r");  // Check if file exists
            if (!file) {
                cout << RED << "Error: File not found!" << RESET << endl;
            } else {
                fclose(file);
                remove(fn);
                cout << GREEN << "File \"" << fn << "\" is successfully deleted!" << RESET << endl;
            }
        }

        if (choice != 0 && choice != 1) {
            choice = 0;
        }
    } while (choice == 1);

    sleep(2);

    if ((choice == 0) || (choice != 0 && choice != 1)) {
        shmid = shmget((key_t)1122, sizeof(int), 0666);
        shared_memory = (int*)shmat(shmid, NULL, 0);
        *shared_memory += 3;
        shmdt(shared_memory);
        return 0;
    }

    return 0;
}
