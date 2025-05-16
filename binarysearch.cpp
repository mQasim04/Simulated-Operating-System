#include <iostream>
#include <cstdlib>
#include <sys/shm.h>
#include <limits>
#include <unistd.h> 

using namespace std;


#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[94m"
#define CYAN    "\033[36m"

// Binary Search Function
int binarySearch(int arr[], int left, int right, int x) {
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == x)
            return mid;
        else if (arr[mid] < x)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return -1;
}


void updateSharedMemory(int delta) {
    int* shared_memory;
    int shmid = shmget((key_t)1122, sizeof(int), 0666);
    if (shmid == -1) {
        perror("shmget failed");
        exit(1);
    }

    shared_memory = (int*)shmat(shmid, nullptr, 0);
    if (shared_memory == (void*)-1) {
        perror("shmat failed");
        exit(1);
    }

    *shared_memory += delta;

    if (shmdt(shared_memory) == -1) {
        perror("shmdt failed");
        exit(1);
    }
}
void waitForKey() {
    cout << YELLOW << "\nPress any key to continue..." << RESET;
    cin.ignore();
    cin.get();
    system("clear");
}
int main() {

    cout << CYAN << "\n\t\t===============================================" << endl;
    cout << "\t\t\tWELCOME TO THE BINARY SEARCH PROCESS!" << endl;
    cout << "\t\t===============================================" << RESET << endl;

    updateSharedMemory(-40);


    int n;
    cout << YELLOW << "\nEnter the number of elements in the array: " << RESET;
    cin >> n;
    int arr[n];

    cout << YELLOW << "Enter the elements of the array (in sorted order): \n" << RESET;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    int x, choice = 0;
    while (true) {

        cout << BLUE << "\n===============================================" << endl;
        cout << "[1] Find a number in the array" << endl;
        cout << "[0] Exit" << endl;
        cout << "Enter your choice: " << RESET;
        cin >> choice;

        if (choice == 1) {
            cout << YELLOW << "\nEnter the number to search for: " << RESET;
            cin >> x;

            int result = binarySearch(arr, 0, n - 1, x);
            if (result == -1)
                cout << RED << "Element not found" << RESET << endl;
            else
                cout << GREEN << "Element found at index " << result << RESET << endl;
        } 
        else if (choice == 0) {
            cout << CYAN << "Exiting the process..." << RESET << endl;
            break;
        } 
        else {
            cout << RED << "Invalid input! Please try again." << RESET << endl;
            continue;
        }
        waitForKey();
    }

    updateSharedMemory(40);

    cout << GREEN << "\nPress Enter to exit..." << RESET;
    cin.ignore();
    cin.get();

    return 0;
}
