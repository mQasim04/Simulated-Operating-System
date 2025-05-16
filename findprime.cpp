#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <sys/shm.h>
using namespace std;

// ANSI Color Codes
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define CYAN    "\033[36m"
#define YELLOW  "\033[33m"
#define BOLD    "\033[1m"
void waitForKey() {
    cout << YELLOW << "\nPress any key to continue..." << RESET;
    cin.ignore();
    cin.get();
    system("clear");
}
void* findprime() {
    int i, n;
    bool isPrime = true;

    cout << CYAN << "\nEnter a positive integer: " << RESET;
    cin >> n;

    // 0 and 1 are not prime numbers
    if (n == 0 || n == 1) {
        isPrime = false;
    } else {
        for (i = 2; i <= n / 2; ++i) {
            if (n % i == 0) {
                isPrime = false;
                break;
            }
        }
    }

    cout << YELLOW << "\n━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n" << RESET;
    if (isPrime)
        cout << GREEN << BOLD << n << " is a PRIME number!" << RESET << endl;
    else
        cout << RED << BOLD << n << " is NOT a prime number." << RESET << endl;
    cout << YELLOW << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n" << RESET;

    waitForKey();
    return NULL;
}

int main() {
  
    

    //shared memory setup
    int* shared_memory;
    int shmid = shmget((key_t)1122, sizeof(int), 0666);
    shared_memory = (int*)shmat(shmid, NULL, 0);
    *shared_memory -= 20;
    if (shmdt(shared_memory) == -1) {
        perror(RED "shmdt error" RESET);
        exit(1);
    }

    int choice;
    do {
    	cout << CYAN << "\n\t═══════════════════════════════════════════════\n" << RESET;
    	cout << BOLD << "\t    WELCOME TO PRIME NUMBER CHECKER SYSTEM\n" << RESET;
    	cout << CYAN << "\t═══════════════════════════════════════════════\n" << RESET;
        cout << "\n" << YELLOW << "[1] Check for Prime\n[0] Exit\nChoose an option: " << RESET;
        cin >> choice;

        if (choice == 1) {
            cin.ignore(); // Clean buffer
            findprime();
        } else if (choice != 0) {
            cout << RED << "Invalid input. Exiting..." << RESET << endl;
            break;
        }

    } while (choice == 1);

    sleep(2);

    // Shared memory restore
    shared_memory = (int*)shmat(shmid, NULL, 0);
    *shared_memory += 20;
    if (shmdt(shared_memory) == -1) {
        perror(RED "shmdt error" RESET);
        exit(1);
    }

    cout << GREEN << "\nThank you for using the Prime Checker. Press Enter to exit..." << RESET;
    cin.get();
    return 0;
}
