#include <iostream>
#include <chrono>
#include <thread>
#include <atomic>
#include <unistd.h>
#include <future>
#include <sys/shm.h>
using namespace std;

//aNSI Color Codes
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define CYAN    "\033[36m"
#define YELLOW  "\033[33m"
#define BOLD    "\033[1m"

class Stopwatch {
public:
    Stopwatch() : start_time(chrono::high_resolution_clock::now()) {}

    void reset() {
        start_time = chrono::high_resolution_clock::now();
    }

    double elapsed_seconds() {
        auto now = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(now - start_time).count();
        return duration / 1e6;
    }

private:
    chrono::high_resolution_clock::time_point start_time;
};

void display_elapsed_time(atomic<bool>& running, Stopwatch& stopwatch) {
    while (running.load()) {
        cout << CYAN << " Elapsed time: " << stopwatch.elapsed_seconds() << " seconds" << RESET << endl;
        this_thread::sleep_for(chrono::seconds(1));
    }
}

int main() {

    cout << CYAN << "\n\t═══════════════════════════════════════════════\n" << RESET;
    cout << BOLD << "\t\tWELCOME TO THE STOPWATCH PROCESS\n" << RESET;
    cout << CYAN << "\t═══════════════════════════════════════════════\n" << RESET;

    //shared Memory - Decrease Value
    int *shared_memory;
    int shmid = shmget((key_t)1122, sizeof(int), 0666);
    shared_memory = (int*)shmat(shmid, NULL, 0);
    *shared_memory -= 11;
    if (shmdt(shared_memory) == -1) {
        perror(RED "shmdt error" RESET);
        exit(1);
    }

    //start Stopwatch
    Stopwatch stopwatch;
    atomic<bool> running(true);

    cout << YELLOW << "\nStopwatch started. Press Enter to stop it..." << RESET << endl;

    //start time display thread
    thread display_thread(display_elapsed_time, ref(running), ref(stopwatch));

    cin.get(); // Wait for Enter
    running.store(false);
    display_thread.join();

    cout << GREEN << "\n Stopwatch stopped." << RESET;
    cout << BOLD << "\n Final elapsed time: " << stopwatch.elapsed_seconds() << " seconds" << RESET << endl;

    //restore Shared Memory
    shared_memory = (int*)shmat(shmid, NULL, 0);
    *shared_memory += 11;
    if (shmdt(shared_memory) == -1) {
        perror(RED "shmdt error" RESET);
        exit(1);
    }

    cout << CYAN << "\nPress Enter to exit..." << RESET;
    cin.get();
    return 0;
}
