#include <iostream>
#include <string>
#include <cstring>
#include <iomanip>
#include <sys/shm.h>
#include <unistd.h>
using namespace std;

#define RESET   "\033[0m"
#define CYAN    "\033[36m"
#define GREEN   "\033[32m"
#define RED     "\033[31m"
#define YELLOW  "\033[93m"
#define BOLD    "\033[1m"

const int MAX_USERS = 10;
const int MAX_MESSAGES = 10;

struct Message {
    string sender;
    string content;
};

struct User {
    string name;
    Message messages[MAX_MESSAGES];
    int message_count;
};

User users[MAX_USERS];
int user_count = 0;

void toLowerCase(string& str) {
    for (int i = 0; i < str.length(); i++) {
        str[i] = tolower(str[i]);
    }
}

void waitForKey() {
    cout << YELLOW << "\nPress Enter to continue..." << RESET;
    cin.ignore();
    cin.get();
    system("clear");
}

void addUser(const string& name) {
    if (user_count < MAX_USERS) {
        users[user_count].name = name;
        toLowerCase(users[user_count].name);
        users[user_count].message_count = 0;
        user_count++;
    }
}

int findUser(string name) {
    toLowerCase(name);
    for (int i = 0; i < user_count; i++) {
        if (users[i].name == name) {
            return i;
        }
    }
    return -1;
}

void sendMessage(const string& sender, const string& receiver, const string& message) {
    int senderIndex = findUser(sender);
    int receiverIndex = findUser(receiver);

    if (senderIndex == -1 || receiverIndex == -1) {
        cout << RED << "User not found.\n" << RESET;
        waitForKey();
        return;
    }

    if (users[receiverIndex].message_count < MAX_MESSAGES) {
        users[receiverIndex].messages[users[receiverIndex].message_count].sender = sender;
        users[receiverIndex].messages[users[receiverIndex].message_count].content = message;
        users[receiverIndex].message_count++;
        cout << GREEN << "Message sent!\n" << RESET;
    } else {
        cout << RED << "Receiver's inbox is full!\n" << RESET;
    }

    waitForKey();
}

void readMessages(const string& user) {
    int userIndex = findUser(user);
    if (userIndex == -1) {
        cout << RED << "User not found.\n" << RESET;
        waitForKey();
        return;
    }

    if (users[userIndex].message_count == 0) {
        cout << YELLOW << "No new messages.\n" << RESET;
    } else {
        cout << CYAN << "\nYour Messages:\n" << RESET;
        for (int i = 0; i < users[userIndex].message_count; i++) {
            cout << GREEN << users[userIndex].messages[i].sender << ": " << RESET
                 << users[userIndex].messages[i].content << endl;
        }
        users[userIndex].message_count = 0;
    }

    waitForKey();
}

void printBoxedMessage(const string& msg, const string& color = RESET) {
    cout << color;
    cout << "╔════════════════════════════════════════════════════╗" << endl;
    cout << "║ " << setw(50) << left << msg << " ║" << endl;
    cout << "╚════════════════════════════════════════════════════╝" << RESET << endl;
}

int main() {
    system("clear");

    int* shared_memory;
    int shmid = shmget((key_t)1122, sizeof(int), 0666);
    shared_memory = (int*)shmat(shmid, NULL, 0);
    *shared_memory -= 30;
    shmdt(shared_memory);

    addUser("Bilal");
    addUser("Qasim");
    addUser("Tahir");

    printBoxedMessage("PRIVATE MESSAGING SYSTEM", GREEN);

    string command;
    while (true) {
        cout << YELLOW << "You have Bilal, Qasim, Tahir in your contact list.\n" << RESET;
        cout << BOLD << "Enter command (send, read, exit): " << RESET;
        cin >> command;

        if (command == "send") {
            string sender, receiver, message;
            cout << "Enter sender: ";
            cin >> sender;
            cout << "Enter receiver: ";
            cin >> receiver;
            cin.ignore(); // Important to flush newline
            cout << "Enter message: ";
            getline(cin, message);
            sendMessage(sender, receiver, message);
        } else if (command == "read") {
            string user;
            cout << "Enter user: ";
            cin >> user;
            readMessages(user);
        } else if (command == "exit") {
            shared_memory = (int*)shmat(shmid, NULL, 0);
            *shared_memory += 30;
            shmdt(shared_memory);
            cout << GREEN << "\nExiting messenger. Goodbye!\n" << RESET;
            break;
        } else {
            cout << RED << "Invalid command.\n" << RESET;
            waitForKey();
        }
    }

    return 0;
}
    