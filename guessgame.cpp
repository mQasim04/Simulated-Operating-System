#include <iostream>
#include <cstdlib>
#include <string>
#include <unistd.h>
#include <cstring>
#include <ctime>
#include <sys/shm.h>
#include <iomanip>

using namespace std;

// ANSI colors
#define RESET   "\033[0m"
#define CYAN    "\033[36m"
#define GREEN   "\033[32m"
#define RED     "\033[31m"
#define YELLOW  "\033[33m"
#define MAGENTA "\033[35m"
#define BOLD    "\033[1m"

void printBoxedMessage(const string& msg, const string& color = RESET) {
    cout << color;
    cout << "╔════════════════════════════════════════════════════╗" << endl;
    cout << "║ " << setw(50) << left << msg << " ║" << endl;
    cout << "╚════════════════════════════════════════════════════╝" << RESET << endl;
}

void *guess_game() {
    int num, guess, tries = 0;
    srand(time(0));
    num = rand() % 10 + 1;

    system("clear");
    printBoxedMessage(" Guess the Number (1 to 10)", CYAN);

    do {
        cout << YELLOW << " Enter your guess: " << RESET;
        cin >> guess;
        tries++;

        if (guess > num)
            cout << RED << " Too high!\n\n" << RESET;
        else if (guess < num)
            cout << RED << "Too low!\n\n" << RESET;
        else {
            cout << GREEN << "Correct! You got it in " << tries << " guesses! \n" << RESET;
            printBoxedMessage(" Well done!", GREEN);
        }

    } while (guess != num);

    sleep(3);
    system("clear");
    return nullptr;
}

void decrementSharedMemory() {
    int *shared_memory;
    int shmid = shmget((key_t)1122, sizeof(int), 0666);
    shared_memory = (int*)shmat(shmid, NULL, 0);
    *shared_memory -= 2;
    shmdt(shared_memory);
}

void incrementSharedMemory() {
    int *shared_memory;
    int shmid = shmget((key_t)1122, sizeof(int), 0666);
    shared_memory = (int*)shmat(shmid, NULL, 0);
    *shared_memory += 2;
    shmdt(shared_memory);
}

int main() {
    system("clear");
    printBoxedMessage("WELCOME TO THE GUESS GAME WORLD!", MAGENTA);

    decrementSharedMemory();

    int choice;

    do {
        cout << CYAN << "\n MENU:\n" << RESET;
        cout << BOLD << "1. Start Game\n0. Exit\n" << RESET;
        cout << YELLOW << "Enter your choice: " << RESET;
        cin >> choice;

        if (choice == 1) {
            guess_game();
        } else {
            incrementSharedMemory();
            printBoxedMessage("Game closed. See you next time!", GREEN);
            break;
        }

    } while (choice == 1);

    return 0;
}
