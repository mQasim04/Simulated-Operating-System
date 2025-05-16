#include<iostream>
#include<cstring>
#include<fstream>
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
    cout << BOLD << "\t\tWELCOME TO FILE CREATION PROCESS!" << RESET << endl;
    cout << CYAN << "\t\t───────────────────────────────────────" << RESET << endl;

    int *shared_memory;
    int shmid;
    shmid = shmget((key_t)1122, sizeof(int), 0666);
    shared_memory = (int*)shmat(shmid, NULL, 0);
    int new_data = *shared_memory - 6;
    *shared_memory = new_data;

    if (shmdt(shared_memory) == -1) {
        perror("shmdt error");
        exit(1);
    }

    ofstream File;
    int choice;
    do {
        cout << YELLOW << "Press 1 to create file" << RESET << endl;
        cout << YELLOW << "Press 0 to exit" << RESET << endl;
        cin >> choice;

        if (choice == 1) {
            string filename;
            cout << "Enter Filename: ";
            cin >> filename;
            File.open(filename);
            cout << GREEN << "File is successfully created!!" << RESET << endl;
            File.close();
        }

        if (choice != 0 && choice != 1) {
            choice = 0;
        }
    } while (choice == 1);

    sleep(2);

    if ((choice == 0) || (choice != 0 && choice != 1)) {
        int *shared_memory;
        int shmid;
        shmid = shmget((key_t)1122, sizeof(int), 0666);
        shared_memory = (int*)shmat(shmid, NULL, 0);
        int new_data = *shared_memory - 6;
        *shared_memory = new_data;

        if (shmdt(shared_memory) == -1) {
            perror("shmdt error");
            exit(1);
        }
        return 0;
    }

    return 0;
}
