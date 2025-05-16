#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <iomanip>
#include <sys/shm.h>

using namespace std;

// ANSI color codes
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define BLUE    "\033[34m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define CYAN    "\033[36m"
#define BOLD    "\033[1m"

// Game board (1 to 9)
char B[9] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};

//Check for win (0 = win, -1 = draw, 1 = continue)
int check() {
    //Rows
    if (B[0] == B[1] && B[1] == B[2]) return 0;
    if (B[3] == B[4] && B[4] == B[5]) return 0;
    if (B[6] == B[7] && B[7] == B[8]) return 0;
    //Columns
    if (B[0] == B[3] && B[3] == B[6]) return 0;
    if (B[1] == B[4] && B[4] == B[7]) return 0;
    if (B[2] == B[5] && B[5] == B[8]) return 0;
    //Diagonals
    if (B[0] == B[4] && B[4] == B[8]) return 0;
    if (B[2] == B[4] && B[4] == B[6]) return 0;
    // Draw
    for (int i = 0; i < 9; i++)
        if (B[i] == '1' + i) return 1; //Still has empty cells
    return -1; //Draw
}


void Board(int playerWins, int computerWins, int draws, const string& name) {
    system("clear"); 
    cout << CYAN << "┌────────────────────────────────────────────┐" << endl;
    cout << "│" << BOLD << "            TIC TAC TOE GAME                " << RESET << CYAN << "│" << endl;
    cout << "└────────────────────────────────────────────┘" << RESET << endl;
    cout << YELLOW << "  " << name << " (X) vs Computer (O)" << RESET << endl;
    cout << endl;

    // Board table
    cout << "  ┌─────┬─────┬─────┐" << endl;
    cout << "  │ " << (B[0] == 'X' ? RED : B[0] == 'O' ? BLUE : YELLOW) << " " << B[0] << " " << RESET 
         << " │ " << (B[1] == 'X' ? RED : B[1] == 'O' ? BLUE : YELLOW) << " " << B[1] << " " << RESET 
         << " │ " << (B[2] == 'X' ? RED : B[2] == 'O' ? BLUE : YELLOW) << " " << B[2] << " " << RESET << " │" << endl;
    cout << "  ├─────┼─────┼─────┤" << endl;
    cout << "  │ " << (B[3] == 'X' ? RED : B[3] == 'O' ? BLUE : YELLOW) << " " << B[3] << " " << RESET 
         << " │ " << (B[4] == 'X' ? RED : B[4] == 'O' ? BLUE : YELLOW) << " " << B[4] << " " << RESET 
         << " │ " << (B[5] == 'X' ? RED : B[5] == 'O' ? BLUE : YELLOW) << " " << B[5] << " " << RESET << " │" << endl;
    cout << "  ├─────┼─────┼─────┤" << endl;
    cout << "  │ " << (B[6] == 'X' ? RED : B[6] == 'O' ? BLUE : YELLOW) << " " << B[6] << " " << RESET 
         << " │ " << (B[7] == 'X' ? RED : B[7] == 'O' ? BLUE : YELLOW) << " " << B[7] << " " << RESET 
         << " │ " << (B[8] == 'X' ? RED : B[8] == 'O' ? BLUE : YELLOW) << " " << B[8] << " " << RESET << " │" << endl;
    cout << "  └─────┴─────┴─────┘" << endl;

    //scoreboard
    cout << endl << GREEN << "  Scoreboard" << RESET << endl;
    cout << "  ┌──────────────────┬──────────────────┬──────────────────┐" << endl;
    cout << "  │ " << left << setw(16) << (name + " Wins") << " │ " << setw(16) << "Computer Wins" 
         << " │ " << setw(16) << "Draws" << " │" << endl;
    cout << "  ├──────────────────┼──────────────────┼──────────────────┤" << endl;
    cout << "  │ " << left << setw(16) << playerWins << " │ " << setw(16) << computerWins 
         << " │ " << setw(16) << draws << " │" << endl;
    cout << "  └──────────────────┴──────────────────┴──────────────────┘" << endl;
}

//computer's move: win, block, center, or random
char computerMove() {
    // Check for winning move (O)
    for (int i = 0; i < 9; i++) {
        if (B[i] == '1' + i) {
            B[i] = 'O';
            if (check() == 0) {
                B[i] = '1' + i; //Undo
                return '1' + i;
            }
            B[i] = '1' + i; //Undo
        }
    }
    //Block player's winning move (X)
    for (int i = 0; i < 9; i++) {
        if (B[i] == '1' + i) {
            B[i] = 'X';
            if (check() == 0) {
                B[i] = '1' + i; //Undo
                return '1' + i;
            }
            B[i] = '1' + i; //Undo
        }
    }
    //take center if available
    if (B[4] == '5') return '5';
    //random move
    int available[9], count = 0;
    for (int i = 0; i < 9; i++)
        if (B[i] == '1' + i) available[count++] = i;
    if (count == 0) return '0'; //shouldn't happen
    return '1' + (available[rand() % count]);
}

//toss to decide who goes first (1 = player, 2 = computer)
int toss() {
    return (rand() % 2) + 1;
}

int main() {
    srand(time(0));

    //shared memory setup
    int shmid = shmget((key_t)1122, sizeof(int), 0666);
    if (shmid == -1) {
        perror("shmget error");
        exit(1);
    }
    int *shared_memory = (int*)shmat(shmid, NULL, 0);
    if (shared_memory == (int*)-1) {
        perror("shmat error");
        exit(1);
    }
    *shared_memory -= 30; //deduct 30 MB RAM

    string name;
    cout << CYAN << "\t\t┌────────────────────────────────────────────┐" << endl;
    cout << "\t\t│" << BOLD << "        WELCOME TO TIC TAC TOE!             " << RESET << CYAN << "│" << endl;
    cout << "\t\t└────────────────────────────────────────────┘" << RESET << endl;
    cout << YELLOW << "\t\tEnter your name: " << RESET;
    cin >> name;

    int playerWins = 0, computerWins = 0, draws = 0;
    bool playAgain = true;

    while (playAgain){
        for (int i = 0; i < 9; i++) B[i] = '1' + i;

        int turn = toss();
        Board(playerWins, computerWins, draws, name);
        cout << (turn == 1 ? GREEN : YELLOW) << "  " 
             << (turn == 1 ? name : "Computer") << " won the toss and will go first!" 
             << RESET << endl;

        int gameState = 1;
        while (gameState == 1) {
            char move;
            if (turn == 1) { // Player's turn
                cout << GREEN << "  " << name << ", enter a number (1-9): " << RESET;
                cin >> move;
                if (move < '1' || move > '9' || B[move - '1'] != move) {
                    cout << RED << "  Invalid move! Try again." << RESET << endl;
                    continue;
                }
                B[move - '1'] = 'X';
            } else { //computer's turn
                move = computerMove();
                if (move == '0') break;
                B[move - '1'] = 'O';
                cout << YELLOW << "  Computer chose position " << move << RESET << endl;
            }

            Board(playerWins, computerWins, draws, name);
            gameState = check();

            if (gameState == 0) {
                if (turn == 1) {
                    cout << GREEN << "  " << name << " wins!" << RESET << endl;
                    playerWins++;
                } else {
                    cout << YELLOW << "  Computer wins!" << RESET << endl;
                    computerWins++;
                }
            } else if (gameState == -1) {
                cout << CYAN << "  Game is a draw!" << RESET << endl;
                draws++;
            }

            turn = (turn == 1) ? 2 : 1;
        }

        char choice;
        cout << GREEN << "  Play again? (Y/N): " << RESET;
        cin >> choice;
        playAgain = (choice == 'Y' || choice == 'y');
    }

    //cleanup shared memory
    *shared_memory += 30; //restore 30 MB RAM
    if (shmdt(shared_memory) == -1) {
        perror("shmdt error");
        exit(1);
    }

    cout << CYAN << "\t\tThanks for playing, " << name << "!" << RESET << endl;
    cout << YELLOW << "\t\tPress Enter to exit..." << RESET;
    cin.ignore();
    cin.get();
    return 0;
}