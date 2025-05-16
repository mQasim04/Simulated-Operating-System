#include <iostream>
#include <ctime>
#include <cstdlib>
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
int main()
{
    int *shared_memory;
    int shmid;
    shmid = shmget((key_t)1122, sizeof(int), 0666);

    shared_memory = (int*)shmat(shmid, NULL, 0);
    int new_data = *shared_memory - 30;
    *shared_memory = new_data;

    if (shmdt(shared_memory) == -1) {
        perror("shmdt error");
        exit(1);
    }

    int sec_prev = 0;
    while (true)
    {
        int seconds, minutes, hours;
        string str;

        //storing total seconds
        time_t total_seconds = time(0);

        //getting values of seconds, minutes, and hours
        struct tm* ct = localtime(&total_seconds);

        seconds = ct->tm_sec;
        minutes = ct->tm_min;
        hours = ct->tm_hour;

        // Converting to 12-hour format
        if (hours >= 12)
            str = "PM";
        else
            str = "AM";
        hours = hours > 12 ? hours - 12 : hours;

        // Printing the result
        if (seconds == sec_prev + 1 || (sec_prev == 59 && seconds == 0))
        {
            system("clear");
            cout << CYAN << "\t\t───────────────────────────────────────" << RESET << endl;
            cout << CYAN << "\t\t\tWELCOME TO DIGITAL CLOCK SYSTEM!" << RESET << endl;
            cout << CYAN << "\t\t───────────────────────────────────────" << RESET << endl;
            cout << GREEN << "\t\t\t\t" << (hours < 10 ? "0" : "") << hours << ":" 
                 << (minutes < 10 ? "0" : "") << minutes << ":" 
                 << (seconds < 10 ? "0" : "") << seconds << " " 
                 << str << RESET << endl;
        }

        sec_prev = seconds;
        sleep(1);
    }
    return 0;
}
