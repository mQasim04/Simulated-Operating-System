#include <iostream>
#include <unistd.h>
#include <sys/shm.h>
using namespace std;

// Color codes
#define RESET   "\033[0m"
#define CYAN    "\033[36m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define RED     "\033[31m"
#define BOLD    "\033[1m"

int factorial(int n) {
    if (n == 0 || n == 1)
        return 1;
    return n * factorial(n - 1);
}
void waitForKey() {
    cout << YELLOW << "\nPress any key to continue..." << RESET;
    cin.ignore();
    cin.get();
    system("clear");
}
int main() {


    int choice;
    int *shared_memory;
    int shmid = shmget((key_t)1122, sizeof(int), 0666);
    shared_memory = (int*)shmat(shmid, NULL, 0);
    *shared_memory -= 11;

    if (shmdt(shared_memory) == -1) {
        perror(RED "shmdt error" RESET);
        exit(1);
    }

    do {
        cout << CYAN << "\n\t\t═════════════════════════════════════════════════════\n" << RESET;
    cout << BOLD << "\t\t   WELCOME TO FACTORIAL FINDING PROCESS\n" << RESET;
    cout << CYAN << "\t\t═════════════════════════════════════════════════════\n" << RESET;
        cout << YELLOW << "\n[1] Start Process\n[0] Exit\nChoose an option: " << RESET;
        cin >> choice;

        if (choice == 1) {
            int n;
            cout << CYAN << "Enter a positive integer: " << RESET;
            cin >> n;

            if (n < 0) {
                cout << RED << "Error: Negative numbers don't have factorials.\n" << RESET;
            } else {
                cout << GREEN << "Factorial of " << n << " is: " << factorial(n) << RESET << endl;
            }
        }

        if (choice != 0 && choice != 1) {
            cout << RED << "Invalid option. Exiting...\n" << RESET;
            choice = 0;
        }
	waitForKey();

    } while (choice == 1);

    sleep(3);

    {
        int *shared_memory;
        int shmid = shmget((key_t)1122, sizeof(int), 0666);
        shared_memory = (int*)shmat(shmid, NULL, 0);
        *shared_memory += 11;

        if (shmdt(shared_memory) == -1) {
            perror(RED "shmdt error" RESET);
            exit(1);
        }
    }

    cout << YELLOW << "\nProcess complete. Exiting..." << RESET << endl;
    return 0;
}
