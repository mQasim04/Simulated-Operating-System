#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <sys/shm.h>
#include <cctype>
using namespace std;

//ANSI Color Codes
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
const int MAX_WRONG = 8; //maximum number of incorrect guesses allowed
vector<string> words;
string current_word;
string so_far;
int wrong;

//initialize the collection of possible words
void init_words() {
    words = {"BILAL", "WORLD", "HANGMAN", "COMPUTER", "SCIENCE", "PROGRAMMING", "PAKISTAN"};
}

//play one round of hangman
void play() {
    current_word = words[rand() % words.size()];
    so_far = string(current_word.length(), '-');
    wrong = 0;

    while (wrong < MAX_WRONG && so_far != current_word) {
        cout << YELLOW << "\n──────────────────────────────────────\n" << RESET;
        cout << CYAN << "You have " << (MAX_WRONG - wrong) << " incorrect guesses left.\n" << RESET;
        cout << GREEN << "Word so far: " << BOLD << so_far << RESET << endl;

        char guess;
        cout << CYAN << "\nEnter your guess: " << RESET;
        cin >> guess;
        guess = toupper(guess);

        if (current_word.find(guess) != string::npos) {
            cout << GREEN << " Good! '" << guess << "' is in the word.\n" << RESET;
            for (int i = 0; i < current_word.length(); ++i) {
                if (current_word[i] == guess) {
                    so_far[i] = guess;
                }
            }
        } else {
            cout << RED << " Sorry, '" << guess << "' is not in the word.\n" << RESET;
            ++wrong;
        }
    }

    cout << YELLOW << "──────────────────────────────────────\n" << RESET;

    if (so_far == current_word) {
        cout << GREEN << BOLD << "\n Congratulations! You guessed the word: " << current_word << RESET << endl;
    } else {
        cout << RED << BOLD << "\n Out of guesses. The word was: " << current_word << RESET << endl;
    }

    waitForKey();
}

int main() {

    cout << CYAN << "\n\t═══════════════════════════════════════════════\n" << RESET;
    cout << BOLD << "\t        WELCOME TO THE HANGMAN GAME WORLD\n" << RESET;
    cout << CYAN << "\t═══════════════════════════════════════════════\n" << RESET;

    //shared memory setup (decrease usage count)
    int* shared_memory;
    int shmid = shmget((key_t)1122, sizeof(int), 0666);
    shared_memory = (int*)shmat(shmid, NULL, 0);
    *shared_memory -= 15;
    if (shmdt(shared_memory) == -1) {
        perror(RED "shmdt error" RESET);
        exit(1);
    }

    // Game loop
    srand(static_cast<unsigned int>(time(0)));
    init_words();
    char play_again = 'y';
    while (play_again == 'y' || play_again == 'Y') {
        play();
        cout << CYAN << "\nDo you want to play again? (y/n): " << RESET;
        cin >> play_again;
        cin.ignore(); //clean buffer for next input
    }

    //shared memory cleanup (restore usage count)
    shared_memory = (int*)shmat(shmid, NULL, 0);
    *shared_memory += 15;
    if (shmdt(shared_memory) == -1) {
        perror(RED "shmdt error" RESET);
        exit(1);
    }

    cout << GREEN << "\nThanks for playing Hangman! Press Enter to exit." << RESET;
    cin.get();
    return 0;
}
