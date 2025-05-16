#include <iostream>
#include <iomanip>
#include <ctime>
#include <sys/shm.h>
using namespace std;

#define RESET   "\033[0m"
#define GREEN   "\033[32m"
#define CYAN    "\033[36m"
#define YELLOW  "\033[93m"
#define RED     "\033[31m"
#define BOLD    "\033[1m"
void waitForKey() {
    cout << YELLOW << "\nPress any key to continue..." << RESET;
    cin.ignore();
    cin.get();
    system("clear");
}
int main()
{
    cout << CYAN << "\t\t───────────────────────────────────────" << RESET << endl;
    cout << BOLD << "\t\t\tWELCOME TO CALENDAR PROCESS!" << RESET << endl;
    cout << CYAN << "\t\t───────────────────────────────────────" << RESET << endl;

    int *shared_memory;
    int shmid;
    shmid = shmget((key_t)1122, sizeof(int), 0666);
    shared_memory = (int*)shmat(shmid, NULL, 0);
    *shared_memory -= 10;
    shmdt(shared_memory);

    //get current year and month
    time_t now = time(0);
    tm *ltm = localtime(&now);
    int year = 1900 + ltm->tm_year;
    int month = 1 + ltm->tm_mon;

    //input year and month if desired
    int choice = 1;
    while (choice == 1)
    {
        cout << GREEN << "Enter year (0 to use current year): " << RESET;
        cin >> year;
        if (year == 0)
        {
            year = 1900 + ltm->tm_year;
        }
        cout << GREEN << "Enter month (1-12, 0 to use current month): " << RESET;
        cin >> month;
        if (month == 0)
        {
            month = 1 + ltm->tm_mon;
        }

        // determine number of days in month and starting day of week
        int daysInMonth, startDay;
        if (month == 2) // February
        {
            if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) // Leap year
            {
                daysInMonth = 29;
            }
            else
            {
                daysInMonth = 28;
            }
        }
        else if (month == 4 || month == 6 || month == 9 || month == 11)
        {
            daysInMonth = 30;
        }
        else
        {
            daysInMonth = 31;
        }

        //january 1st of input year
        tm jan1st = {0, 0, 0, 1, 0, year - 1900};
        time_t jan1stTime = mktime(&jan1st);

        //starting day of input month
        tm start = *localtime(&jan1stTime);
        start.tm_mon = month - 1;
        mktime(&start);
        startDay = start.tm_wday;
        cout << endl << CYAN << setw(17) << " " << month << "/" << year << RESET << endl;
        cout << YELLOW << "Sun Mon Tue Wed Thu Fri Sat" << RESET << endl;

        for (int i = 0; i < startDay; i++)
        {
            cout << "    ";
        }

        for (int i = 1; i <= daysInMonth; i++)
        {
            cout << setw(3) << i << " ";

            if ((i + startDay) % 7 == 0)
            {
                cout << endl;
            }
        }

        cout << endl;
        cout << GREEN << "Enter 1 to continue and 0 to exit: " << RESET;
        cin >> choice;
        if (choice != 1 && choice != 0)
        {
            choice = 0;
        }
         waitForKey();

    }

    return 0;
}
