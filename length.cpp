#include<iostream>
#include<unistd.h>
#include<cstdlib>
#include<cstring>
#include<ctime>
#include<sys/shm.h>
using namespace std;

// ANSI color codes
#define RESET   "\033[0m"
#define CYAN    "\033[36m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define RED     "\033[31m"
#define BOLD    "\033[1m"

void* nofalphabets() {
    char* array_point;
    char c1;
    int count = 0, alp = 0, digt = 0, spcchr = 0, oth = 0;
    char string_array[100];
    string str1;

    cout << CYAN << "\nEnter a string: " << RESET;
    cin.ignore(); // Clear leftover input
    getline(cin, str1);

    strcpy(string_array, str1.c_str());

    for (array_point = string_array; *array_point != '\0'; array_point++) {
        c1 = *array_point;
        count++;
        if (isalpha(c1)) {
            alp++;
        } else if (isdigit(c1)) {
            digt++;
        } else if (isspace(c1)) {
            spcchr++;
        } else {
            oth++;
        }
    }

    cout << GREEN << "\n━━━━━━━━━━ Character Count Report ━━━━━━━━━━" << RESET << endl;
    cout << YELLOW << "• Alphabets: " << RESET << alp << endl;
    cout << YELLOW << "• Digits:    " << RESET << digt << endl;
    cout << YELLOW << "• Spaces:    " << RESET << spcchr << endl;
    cout << YELLOW << "• Symbols:   " << RESET << oth << endl << endl;
    return NULL;
}

int main() {
    cout << CYAN << "\n\t═════════════════════════════════════════════════\n" << RESET;
    cout << BOLD << "\t   WELCOME TO STRING CHARACTER ANALYSIS TOOL\n" << RESET;
    cout << CYAN << "\t═════════════════════════════════════════════════\n" << RESET;

    int choice;
    int* shared_memory;
    int shmid = shmget((key_t)1122, sizeof(int), 0666);
    shared_memory = (int*)shmat(shmid, NULL, 0);
    *shared_memory -= 11;
    if (shmdt(shared_memory) == -1) {
        perror(RED "shmdt error" RESET);
        exit(1);
    }

    do {
        cout << YELLOW << "[1] Start Analysis\n[0] Exit\nChoose an option: " << RESET;
        cin >> choice;
        if (choice == 1) {
            nofalphabets();
        }
        if (choice != 0 && choice != 1) {
            cout << RED << "Invalid input. Exiting..." << RESET << endl;
            choice = 0;
        }
    } while (choice == 1);

    //releasing shared memory
    {
        int* shared_memory;
        int shmid = shmget((key_t)1122, sizeof(int), 0666);
        shared_memory = (int*)shmat(shmid, NULL, 0);
        *shared_memory += 11;
        if (shmdt(shared_memory) == -1) {
            perror(RED "shmdt error" RESET);
            exit(1);
        }
    }

    cout << GREEN << "\nThank you for using the tool. Exiting...\n" << RESET;
    return 0;
}
