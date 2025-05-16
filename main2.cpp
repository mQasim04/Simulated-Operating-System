#include<iostream> 
#include<string> 
#include<unistd.h> 
#include<stdlib.h>
#include<pthread.h>
#include <bits/stdc++.h>
#include<algorithm>
#include<string.h>
#include<sys/shm.h>
#include<stdio.h>
#include<queue>
#include <vector>

#include <mutex> //for process synchronization

using namespace std;
queue<int> wqueue;
queue<int> rqueue;
void showq(queue<int> wqueue)
{
    queue<int> g = wqueue;
    while (!g.empty()) {
        cout << '\t' << g.front();
        g.pop();
    }
    cout << '\n';
}
bool flag=true;
int i;
pthread_t thrTask[15];///thread pool for our 2o tasks
int n=15;//to keep the value up to which our loops have to operate
int *currentIDArr = new int [15];///creating ids for each process
//array for setting the priority for each process
int *currentPriorityArr = new int[15];
int IDPosition = 0;//process index track
int positionPriority = 0;//priority array index track
int RAM;//variable in which we store the ram that we will store the ram given by the user
int *shared_memory;
struct Task
{//struct for kepping the values that are to identify and stored each process 
  int id;
  string name;
  int ramUse; //in MBs
  int priority; //Higher the number ,higher the  priority
};
Task t[15];

//the scheduling algorithm that we will be using for the process
void priorityScheduling(){
     for(int i=1;i<n;i++)
     {
      for(int j=1;j<n;j++)
       {
        if(t[i].priority > t[j].priority)//higher priority comes first
        {
         swap(t[i].id,t[j].id);
         swap(t[i].name,t[j].name); 
         swap(t[i].ramUse,t[j].ramUse);
         swap(t[i].priority,t[j].priority);
        }
      }
     }
  }
  
  ///function for showing each process with all its properties
void showAll(){
	for(int i=0;i<n;i++) {
    	cout<<t[i].id<<"\t"<<t[i].name<<"\t\t"<<t[i].ramUse<<"\t"<<t[i].priority<<endl; 
    }
}

//function that we will use if a process is stoped and the next is choosen 
//this is simply for contexting switching
int ContextSwitch(int ID, Task t[]){
	int pri;
///this checks basiclly if the process choosen by the user has a higher or lower priority than the process that is before it in the array.
	for(int i = 0;i<n;i++){
		if(ID == t[i].id){
			pri = t[i].priority;
			break;
		}
	}
	return pri;
}

//ANSI color codes
#define RESET   "\033[0m"
#define BLACK   "\033[30m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[94m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"
#define LIGHT_BLUE "\033[94m"
#define BOLD "\033[1m"
void board(int RAM, int CORES, int DISK) {
    system("clear");

    // First loading screen
    cout << BLUE;
    cout << "\n\t ┌────────────────────────────────────────────────────────────┐" << endl;
    cout << "\t │                                                            │" << endl;
    cout << "\t │                     " << YELLOW << "Falcon OS Bootloader" << BLUE << "                   │" << endl;
    cout << "\t │                                                            │" << endl;
    cout << "\t ├────────────────────────────────────────────────────────────┤" << endl;
    cout << "\t │                     " << GREEN << "Loading Falcon OS..." << BLUE << "                   │" << endl;
    cout << "\t ├────────────────────────────────────────────────────────────┤" << endl;
    cout << "\t │                                                            │" << endl;
    cout << "\t └────────────────────────────────────────────────────────────┘" << RESET << endl;

    sleep(3);
    system("clear");

    // Welcome screen
    cout << CYAN;
    cout << "\n\t ┌────────────────────────────────────────────────────────────┐" << endl;
    cout << "\t │                                                            │" << endl;
    cout << "\t │                       " << YELLOW << "Falcon OS" << CYAN << "                            │" << endl;
    cout << "\t │                                                            │" << endl;
    cout << "\t ├────────────────────────────────────────────────────────────┤" << endl;
    cout << "\t │                " << GREEN << "All set. Let’s go!" << CYAN << "                          │" << endl;

    stringstream info;
    info << "RAM: " << RAM << "MB   Cores: " << CORES << "   Disk: " << DISK << "MB";
    string infoLine = info.str();
    int padding = (60 - infoLine.length()) / 2;
    cout << "\t |" << string(padding, ' ') << RED << infoLine << CYAN << string(60 - padding - infoLine.length(), ' ') << "│" << endl;

    cout << "\t ├────────────────────────────────────────────────────────────┤" << endl;
    cout << "\t │                                                            │" << endl;
    cout << "\t └────────────────────────────────────────────────────────────┘" << RESET << endl;

    sleep(3);
}

//=====================Calculator Process========================
void *calculator(void *args)
{
sleep(4);
system("gnome-terminal -e  'sh -c \"g++ calculator.cpp && ./a.out\"'");
return  NULL;
}
//=====================TicTacToe Process========================
void *tictactoe(void *args){
sleep(4);
 system("gnome-terminal -e  'sh -c \"g++ tictactoe.cpp && ./a.out\"'");
 return NULL;
}
//=====================Binary Seach Process========================
void *binar_search(void *args){
sleep(4);
system("gnome-terminal -e  'sh -c \"g++ binarysearch.cpp && ./a.out\"'");
 return NULL;
}
//=====================Banking System Process========================
void *banking(void *args){

sleep(4);
system("gnome-terminal -e  'sh -c \"g++ banking.cpp && ./a.out\"'");

 return NULL;
}
//=====================Guessing Game Process========================
void *Guessing_game(void *args){
sleep(4);
system("gnome-terminal -e  'sh -c \"g++ guessgame.cpp && ./a.out\"'");

 return NULL;
}
//=====================Message box Process========================
void *message(void *args){
sleep(4);
system("gnome-terminal -e  'sh -c \"g++ messagebox.cpp && ./a.out\"'");
 return NULL;
}
//=====================Create FIle Process========================
void *createfile(void *args){
sleep(4);
system("gnome-terminal -e  'sh -c \"g++ createfile.cpp && ./a.out\"'");

return  NULL;
}
//=====================Delete file Process========================
void *delete_file(void *args){
 sleep(4);
system("gnome-terminal -e  'sh -c \"g++ deletefile.cpp && ./a.out\"'");
 return NULL;
}
//=====================Calendar Process========================
void *calender(void *args){
sleep(4);
system("gnome-terminal -e  'sh -c \"g++ calender.cpp && ./a.out\"'");
return  NULL;
}

//=====================Factorial Process========================
void *factorial(void *args){
sleep(4);
system("gnome-terminal -e  'sh -c \"g++ factorial.cpp && ./a.out\"'");
 return NULL;
}
//=====================Time Process========================
void *time(void *args){
sleep(4);
system("gnome-terminal -e  'sh -c \"g++ time.cpp && ./a.out\"'");
 return NULL;
}
//=====================Stop Watch Process========================
void *stopwatch(void *args){
sleep(4);
system("gnome-terminal -e  'sh -c \"g++ stopwatch.cpp && ./a.out\"'");
 return NULL;
}
//=====================Length of String Process========================
void *length(void *args){
sleep(4);
system("gnome-terminal -e  'sh -c \"g++ stringlen.cpp && ./a.out\"'");
return NULL;
}
//=====================Prime number Process========================
void *prime(void *args){
sleep(4);
system("gnome-terminal -e  'sh -c \"g++ findprime.cpp && ./a.out\"'");
return NULL;
}
//=====================Hangman Game Process========================
void *hangman_game(void *args){
sleep(4);
system("gnome-terminal -e  'sh -c \"g++ hangman.cpp && ./a.out\"'");
return NULL;
}

//this funtion tells wich prosses or task is runing, along with its priorty and ram ussage
void *TaskManager(void *args){
cout << "ID\tName\t\tRam"<<endl;
	int ID;
	for(int i = 0; i< IDPosition-1;i++){
		ID = currentIDArr[i];
		cout << ID << "\t" << t[ID].name << "\t" << t[ID].ramUse<<endl;
	}
sleep(8);
 return NULL;
}
void userFunc()
{
	bool cond1=1;
	int ch1,pri;
	while (cond1) {
        system("clear");
        cout << CYAN << "============================================================\n";
        cout << "|                                                          |\n";
        cout << "|                      " << YELLOW << "Falcon OS" << CYAN << "                           |\n";
        cout << "|                                                          |\n";
        cout << "|----------------------------------------------------------|\n";
        cout << "|                " << RED << "Total RAM: " << *shared_memory << "MB" << CYAN << "                         |\n";
        cout << "|                " << GREEN << "MAIN MENU" << CYAN << "                                 |\n";
        cout << "|----------------------------------------------------------|\n";
        cout << "|  1. Calculator         2. Tic Tac Toe                    |\n";
        cout << "|  3. Binary Search      4. Banking System                 |\n";
        cout << "|  5. Guessing Game      6. Message Box                    |\n";
        cout << "|  7. Create File        8. Delete File                    |\n";
        cout << "|  9. Calender          10. Time Task                      |\n";
        cout << "| 11. Find Factorial    12. String Length                  |\n";
        cout << "| 13. Find Prime        14. Hangman Task                   |\n";
        cout << "| 15. Stop Watch        16. Show Running Tasks             |\n";
        cout << "| 17. Shutdown                                             |\n";
        cout << "|----------------------------------------------------------|\n";
        cout << "|                                                          |\n";
        cout << "============================================================\n" << RESET;
        cout << "Enter choice: ";
		cin>>ch1;
		if(t[ch1-1].ramUse>*shared_memory)
		{
		wqueue.push(t[ch1-1].id);
		}
		if( !wqueue.empty())
		{
		 int tempid=wqueue.front();
		 wqueue.pop(); 
		   for(i=0;i<15&&flag!=false;i++)
		    {
		       if(t[i].id==tempid)
		       {
		          flag=false;
		      }
		
		    }
		    if(t[i].ramUse>=*shared_memory)
		    {
		        rqueue.push(tempid);
		
		currentIDArr[IDPosition] = t[ch1-1].id;
		IDPosition++;
	    if(RAM>t[ch1-1].ramUse)
	      {
		    RAM = RAM - t[ch1-1].ramUse;
		    //add currnet position in arr
		    currentPriorityArr[positionPriority] = t[ch1-1].priority;
		    pri = ContextSwitch(ch1, t);
		    if(pri > currentPriorityArr[positionPriority] )
		    {
		       RAM = RAM + 2;
		    }
		    positionPriority++;
		cout<<"================================================"<<endl;		    
		if( !rqueue.empty())
		{
		    int tempid=rqueue.front();
		    rqueue.pop();
		    for(i=0;i<15&&flag!=false;i++)
		    {
		       if(t[i].id==tempid)
		       {
		          flag=false;
		      }
		
		    }
		    flag=true;
		    if(t[i].name=="Calculator")
		    {
		      cout<<"Opening the calculator"<<endl;
		      pthread_create(&thrTask[0],NULL,&calculator,NULL); 
     		      pthread_join(thrTask[0],NULL);
     		      RAM = RAM + t[i].ramUse;
     		      sleep(2);  
		    }
		    else if(t[i].name=="TIC TAC TOE")
		    {    
		      cout<<"Opening the TIC TAC TOE"<<endl;
		      pthread_create(&thrTask[1],NULL,&tictactoe,NULL); 
     		      pthread_join(thrTask[1],NULL);
     		      RAM = RAM + t[i].ramUse;
     		      sleep(2);  
		    }
		     else if(t[i].name=="Binary Search")
		    {    
		      cout<<"Opening the binary search"<<endl;
		      pthread_create(&thrTask[2],NULL,&binar_search,NULL); 
     		      pthread_join(thrTask[2],NULL);
     		      RAM = RAM + t[i].ramUse;
     		      sleep(2);  
		    }
		     else if(t[i].name=="Banking System")
		    {    
		      cout<<"Opening the banking "<<endl;
		      pthread_create(&thrTask[3],NULL,&banking,NULL); 
     		      pthread_join(thrTask[3],NULL);
     		      RAM = RAM + t[i].ramUse;
     		      sleep(2);  
		    }
		     else if(t[i].name=="Guessing Game")
		    {    
		         cout<<"Opening the guessing game"<<endl;
		          pthread_create(&thrTask[4],NULL,&Guessing_game,NULL); 
     		          pthread_join(thrTask[4],NULL);
     		          RAM = RAM + t[i].ramUse;
     		          sleep(2);  
		    }
		     else if(t[i].name=="Message Box")
		    {    
		         cout<<"Opening the message box"<<endl;
		          pthread_create(&thrTask[5],NULL,&message,NULL); 
     		          pthread_join(thrTask[5],NULL);
     		          RAM = RAM + t[i].ramUse;
     		          sleep(2);  
		    }
		     else if(t[i].name=="Create File")
		    {    
		         cout<<"Opening the create file"<<endl;
		          pthread_create(&thrTask[6],NULL,&createfile,NULL); 
     		          pthread_join(thrTask[6],NULL);
     		          RAM = RAM + t[i].ramUse;
     		          sleep(2);  
		    }
		     else if(t[i].name=="Delete File")
		    {    
		         cout<<"Opening the delete file"<<endl;
		          pthread_create(&thrTask[7],NULL,&delete_file,NULL); 
     		          pthread_join(thrTask[7],NULL);
     		          RAM = RAM + t[i].ramUse;
     		          sleep(2);  
		    }
		     else if(t[i].name=="Calender")
		    {    
		         cout<<"Opening the calender"<<endl;
		          pthread_create(&thrTask[8],NULL,&calender,NULL); 
     		          pthread_join(thrTask[8],NULL);                           
     		          RAM = RAM + t[i].ramUse;
     		          sleep(2);  
		    }
		      else if(t[i].name=="Time Task")
		    {    
		         cout<<"Opening the clock"<<endl;
		          pthread_create(&thrTask[9],NULL,&time,NULL); 
     		          pthread_join(thrTask[9],NULL);
     		          RAM = RAM + t[i].ramUse;
     		          sleep(2);  
		    }
		     else if(t[i].name=="Find Factorial")
		    {    
		         cout<<"Opening the find factorial proccess"<<endl;
		          pthread_create(&thrTask[10],NULL,&factorial,NULL); 
     		          pthread_join(thrTask[10],NULL);
     		          RAM = RAM + t[i].ramUse;
     		          sleep(2);  
		    }
		      else if(t[i].name=="String Length")
		    {    
		         cout<<"Opening the string length proccess"<<endl;
		          pthread_create(&thrTask[11],NULL,&length,NULL); 
     		          pthread_join(thrTask[11],NULL);
     		          RAM = RAM + t[i].ramUse;
     		          sleep(2);  
		    }
		      else if(t[i].name=="Find prime")
		    {    
		         cout<<"Opening the find prime proccess"<<endl;
		          pthread_create(&thrTask[12],NULL,&prime,NULL); 
     		          pthread_join(thrTask[12],NULL);
     		          RAM = RAM + t[i].ramUse;
     		          sleep(2);  
		    }
		     else if(t[i].name=="Hangman Task")
		    {    
		         cout<<"Opening the hangman game"<<endl;
		          pthread_create(&thrTask[13],NULL,&hangman_game,NULL); 
     		          pthread_join(thrTask[13],NULL);
     		          RAM = RAM + t[i].ramUse;
     		          sleep(2);  
		    }
		     else if(t[i].name=="Stop Watch")
		    {    
		         cout<<"Opening the stop watch"<<endl;
		          pthread_create(&thrTask[14],NULL,&stopwatch,NULL); 
     		          pthread_join(thrTask[14],NULL);
     		          RAM = RAM + t[i].ramUse;
     		          sleep(2);  
		    }
		}
		}
		    
	      }
	      }
	      else
	      {
		      if(ch1==1)
		       {
		          cout<<"Opening the calculator"<<endl;
		          pthread_create(&thrTask[0],NULL,&calculator,NULL); 
     		          pthread_join(thrTask[0],NULL);
     		          RAM = RAM + t[ch1-1].ramUse;
     		          sleep(2);
	               }
		    else if(ch1==2)
		      {
		        cout<<"Opening TIC TAC TOE "<<endl;
		        pthread_create(&thrTask[1],NULL,&tictactoe,NULL); 
		        pthread_join(thrTask[1],NULL);
		        RAM = RAM + t[ch1-1].ramUse;
     		        sleep(2);
     		      }
		  else if(ch1==3)
		    {
		       cout<<"Proccess for binary search is opening"<<endl;
		       pthread_create(&thrTask[2],NULL,&binar_search,NULL); 
		       pthread_join(thrTask[2],NULL);
		       RAM = RAM + t[ch1-1].ramUse;
     		       sleep(2);
     		    }
		else if(ch1==4)
		   {
		      cout<<"opening banking system "<<endl;
		      pthread_create(&thrTask[3],NULL,&banking,NULL); 
		      pthread_join(thrTask[3],NULL);
		      RAM = RAM + t[ch1-1].ramUse;
     		      sleep(2);
		   }
		else if(ch1==5)
		   {
		      cout<<"Opening guessing game "<<endl;
		      pthread_create(&thrTask[4],NULL,&Guessing_game,NULL); 
		      pthread_join(thrTask[4],NULL);
		      RAM = RAM + t[ch1-1].ramUse;
     		      sleep(2);		
		   }
		else if(ch1==6)
		   {
		      cout<<"Opening Message Box"<<endl;
		      pthread_create(&thrTask[5],NULL,&message,NULL); 
		      pthread_join(thrTask[5],NULL);
		      RAM = RAM + t[ch1-1].ramUse;
     		      sleep(2);
		  }
		else if(ch1==7)
		  {
		      cout<<"Opening create file"<<endl;
		      pthread_create(&thrTask[6],NULL,&createfile,NULL); 
		      pthread_join(thrTask[6],NULL);
		      RAM = RAM + t[ch1-1].ramUse;
     		      sleep(2);
			
		  }
		else if(ch1==8)
		  {
		      cout<<"Opening Delete file process"<<endl;
		      pthread_create(&thrTask[7],NULL,&delete_file,NULL); 
		      pthread_join(thrTask[7],NULL);
		      RAM = RAM + t[ch1-1].ramUse;
     		      sleep(2);
		  }
		else if(ch1==9)
		  {
		      cout<<"Opening calender process"<<endl;
		      pthread_create(&thrTask[8],NULL,&calender,NULL); 
		      pthread_join(thrTask[8],NULL);
		      RAM = RAM + t[ch1-1].ramUse;
     		      sleep(2);	
		  }
		   else if(ch1==10)
		  {
		      cout<<"Clock opening..."<<endl;
		      pthread_create(&thrTask[9],NULL,&time,NULL); 
		      pthread_join(thrTask[9],NULL);
		      RAM = RAM + t[ch1-1].ramUse;
     		      sleep(2);
		  }
	       else if(ch1==11)
		  {
		      cout<<"Factorial Proccess opening..."<<endl;
		      pthread_create(&thrTask[10],NULL,&factorial,NULL); 
		      pthread_join(thrTask[10],NULL);
		      RAM = RAM + t[ch1-1].ramUse;
     		      sleep(2);
		  }
		   else if(ch1==12)
		  {
		     cout<<"Length of string proccess opening..."<<endl;
		     pthread_create(&thrTask[11],NULL,&length,NULL); 
		     pthread_join(thrTask[11],NULL);
		     RAM = RAM + t[ch1-1].ramUse;
     		     sleep(2);
		  }
		   else if(ch1==13)
		  {
		      cout<<"Find Prime Proccess opening..."<<endl;
		      pthread_create(&thrTask[12],NULL,&prime,NULL); 
		      pthread_join(thrTask[12],NULL);
		      RAM = RAM + t[ch1-1].ramUse;
     		      sleep(2);
		  }
		    else if(ch1==14)
		 {
		     cout<<"Hangman game opening..."<<endl;
		     pthread_create(&thrTask[13],NULL,&hangman_game,NULL); 
		     pthread_join(thrTask[13],NULL);
		     RAM = RAM + t[ch1-1].ramUse;
     		     sleep(2);
		 }
	       else if(ch1==15)
		  {
		      cout<<"Stop watch opening..."<<endl;
		      pthread_create(&thrTask[14],NULL,&stopwatch,NULL); 
		      pthread_join(thrTask[14],NULL);
		      RAM = RAM + t[ch1-1].ramUse;
     		      sleep(2);	
		  }
	      
	      else if(ch1==16)
	      {
	            cout<<"SHUTTING DOWN"<<endl;
	            sleep(5);
	            system("clear");
	            return;
	      }
	      else
		 {
		     cout<<"Please choose valid task number"<<endl;
		 }
	}
	    }
	}

void *initialize(void *args){	//assigning each process a name and ID
   t[0].id=1; t[0].name="Calculator";    
   t[0].ramUse=10;t[0].priority=1;
   
   t[1].id=2; t[1].name="TIC TAC TOE";   
   t[1].ramUse=30;t[1].priority=2;
   
   t[2].id=3; t[2].name="Binary Search"; 
   t[2].ramUse=40;t[2].priority=4;
   
   t[3].id=4; t[3].name="Banking System";     
   t[3].ramUse=2; t[3].priority=3;
   
   t[4].id=5; t[4].name="Guessing Game";     
   t[4].ramUse=2; t[4].priority=3;
   
   t[5].id=6; t[5].name="Message Box";
   t[5].ramUse=30;t[5].priority=6;
   
   t[6].id=7; t[6].name="Create File";    
   t[6].ramUse=6; t[6].priority=8;
   
   t[7].id=8; t[7].name="Delete File"; 
   t[7].ramUse=3; t[7].priority=7;
   
   t[8].id=9; t[8].name="Calender";    
   t[8].ramUse=10;t[8].priority=9;
   
   t[9].id=10;t[9].name="Time Task";  
   t[9].ramUse=30;t[9].priority=10;
   
   t[10].id=11;t[10].name="Find Factorial";  
   t[10].ramUse=11;t[10].priority=11;
   
   t[11].id=12;t[11].name="String Length";  
   t[11].ramUse=11;t[11].priority=12;
   
   t[12].id=13;t[12].name="Find prime";  
   t[12].ramUse=20;t[12].priority=9;
   
   t[13].id=14;t[13].name="Hangman Task";  
   t[13].ramUse=15;t[13].priority=19;
   
   t[14].id=15;t[14].name="Stop Watch";  
   t[14].ramUse=11;t[14].priority=15;
   
    pthread_exit(NULL);
}


mutex mtx; //mutex for process synchronization

//function for process duplication
void duplicateProcess() {
    int pid = fork();
    if (pid == 0) {
        //child process
        cout << "Child process created!" << endl;
        exit(0);
    } else if (pid > 0){
        //parent process
        cout << "Parent process continues..." << endl;
    } else {
        cerr << "Failed to create child process!" << endl;
    }
}

//function for process synchronization
void* synchronizedFunction(void* args){
    mtx.lock(); //lock mutex to synchronize access
    //critical section
    cout << "Synchronized function executing..." << endl;
    mtx.unlock(); //unlock mutex
    return NULL;
}


struct Process{
    int id;
    int priority;
};

class ComparePriority{
public:
    bool operator()(const Process& p1, const Process& p2) {
        return p1.priority < p2.priority; //higher priority goes first
    }
};

void priorityScheduling1(){
    vector<priority_queue<Process, vector<Process>, ComparePriority>> priorityQueues(5);//5 prioity levels
    vector<Process> processes ={
        {1, 2}, //example processes
        {2, 3},
    };

//distribute processes into priority queues based on their priority
for (int i = 0; i < processes.size(); ++i) {
    Process& process = processes[i];
    int priority = process.priority;
    if (priority >= 0 && priority < priorityQueues.size()) {
        priorityQueues[priority].push(process);
    } else {
        cout << "Invalid priority for process " << process.id << endl;
    }
}

// Execute processes based on priority
for (int i = 0; i < priorityQueues.size(); ++i) {
    while (!priorityQueues[i].empty()) {
        Process p = priorityQueues[i].top();
        priorityQueues[i].pop();
        cout << "Executing process: " << p.id << " with priority: " << p.priority << endl;
    }
}
}
void login(){
	cout << CYAN;
    cout << "\t\t┌──────────────────────────────────────────┐" << endl;
    cout << "\t\t│              LOGIN PAGE                  │" << endl;
    cout << "\t\t└──────────────────────────────────────────┘" << endl;
    
    cout << GREEN;
    cout << "\n\t\t\t  Welcome to Falcon OS!" << endl;
    cout << RESET;
    cout << LIGHT_BLUE;
    cout << "\n\t\t┌──────────────────────────────────────────┐" << endl;
    cout << "\t\t│    How do you want to log in?            │" << endl;
    cout << "\t\t│  Please select from the following options|" << endl;
    cout << "\t\t│    1. User.                              │" << endl;
    cout << "\t\t│    2. Kernel.                            │" << endl;
    cout << "\t\t└──────────────────────────────────────────┘" << endl;
    cout << RESET;
    cout << YELLOW;
    cout << "\n\t\tWHO ARE YOU?: ";
}
void kernel_choice(){
		        	
					cout << CYAN;
		    cout << "\n\t\t┌────────────────────────────────────────┐" << endl;
		    cout << "\t\t│        " << BOLD << "KERNEL MENU            " << RESET << CYAN << "         │" << endl;
		    cout << "\t\t├────────────────────────────────────────┤" << endl;
		    cout << "\t\t│   " << GREEN << "1." << RESET << CYAN << " Add Task                          │" << endl;
		    cout << "\t\t│   " << GREEN << "2." << RESET << CYAN << " Delete Task                       │" << endl;
		    cout << "\t\t│   " << GREEN << "3." << RESET << CYAN << " Shutdown System                   │" << endl;
		    cout << "\t\t└────────────────────────────────────────┘" << endl;
		    cout << RESET;
		    cout << YELLOW << "\t\t     Enter your choice: " << RESET;
}					
int main(int argc, char** num)
{
	string r = string(num[1]);
	RAM = stoi(r);
	string c = string(num[2]);
	int Cores = stoi(c);
	string d = string(num[3]);
	int Disk = stoi(d);
	bool cond1=1;
	int ch1;
	pthread_t thr; 
 	pthread_create(&thr,NULL,&initialize,NULL);  //loading tasks
 	pthread_join(thr,NULL);
  	      	
    //process Duplication example
    duplicateProcess();
    
    //process Synchronization example
    pthread_t syncThread;
    pthread_create(&syncThread, NULL, synchronizedFunction, NULL);
    pthread_join(syncThread, NULL);
    
    //multilevel queue scheduling example
    priorityScheduling1();
	string pass;
	string kernalpass="admin";
	system("clear");
int shmid;
shmid=shmget((key_t)1122,sizeof(int),0666|IPC_CREAT);
shared_memory=(int*)shmat(shmid,NULL,0);
int data=RAM;

*shared_memory=data;
board(RAM, Cores, Disk);
	//auto turn on apps(as required)
	system("gnome-terminal -e  'sh -c \"g++ calender.cpp && ./a.out\"'");
	system("gnome-terminal -e  'sh -c \"g++ time.cpp && ./a.out\"'");
	system("clear");

    login();
    cin >> ch1;
    cout << RESET;
	system("clear");
	switch(ch1)
	{
		case 1:
		userFunc();
		break;
		case 2:
		   Task t1[50];
		   for(int i=0;i<24;++i)
		   {
		    t1[i].name=t[i].name;
		    t1[i].priority=t[i].priority;
		    t1[i].ramUse=t[i].ramUse;
		   }
		        
		   t[50];
		   for(int i=0;i<50;++i)
		   {
		     t[i].name="123";
		   }
		        
		   for(int i=0;i<15;++i)
		   {
		     t[i].name=t1[i].name;
		     t[i].priority=t1[i].priority;
		     t[i].ramUse=t1[i].ramUse;
		   }    
		           
		   int count=15;
		   cout << CYAN;
    		   cout << "\n\t\t┌──────────────────────────────────────────────┐" << endl;
    		   cout << "\t\t│         " << BOLD << "     ENTER PASSWORD TO LOGIN" << RESET << CYAN << "         │" << endl;
    		   cout << "\t\t└──────────────────────────────────────────────┘" << endl;
    
    		   cout << YELLOW << "\n\t\tEnter password for Kernel: " << RESET;
    		   cin >> pass;
		   if(pass==kernalpass)
		   {
        	   cout << GREEN << "\n\t\tPassword correct! Welcome, Kernel" << RESET << endl;
         	   }
		   while(pass!=kernalpass)
		   {
		    cout<< RED <<"Try again OR press 0 to shutdown"<<RESET<<endl;
		     cin>>pass;
		     if(pass=="0")
		       break;
		      } 
		      int kChoice;
		      system("clear");
			do
			{
			kernel_choice();
			cin>>kChoice;
			if(kChoice == 1)
			{
			system("clear");
			    cout << CYAN 				   << 			"\n\t\t===============================================" << endl;
			    cout << "\t\t              TASK ADDITION PAGE" << endl;
			    cout << "\t\t===============================================\n" << RESET;
			    for(int i = 0; i < 50; i++)
			    {
				if(t[count].name != "")
				{
				    cout << "Enter the name of Task: ";
				    cin >> t[count].name;
				    cout << "Enter the Priority of Task: ";
				    cin >> t[count].priority;
				    cout << "Enter the Ram usage of Task: ";
				    cin >> t[count].ramUse;
				    count++;
				    break;
				}
			    }
			    cout << "\nTOTAL TASKS\n";
			    cout << left << setw(20) << "Name" << setw(15) << "Priority" << setw(10) << "RAM" << endl;
			    cout << string(45, '-') << endl;
			    for(int i = 0; i < count; ++i)
			    {
				if(t[i].name != "")
				{
				    cout << left << setw(20) << t[i].name 
					 << setw(15) << t[i].priority 
					 << setw(10) << t[i].ramUse << endl;
				}
			    }

			    sleep(5);
			    system("clear");
			}
			else if(kChoice == 2)
			{
			system("clear");
			 string inp;
			 cout << CYAN << "\n\t\t===============================================" << endl;
			 cout << "\t\t             TASK DELETION PAGE" << endl;
			 cout << "\t\t===============================================\n" << RESET;
	         	 cout << "Please enter the name of task you want to delete: ";
			 cin >> inp;

			 for(int i = 0; i < 50; i++)
			 {
			  if(inp == t[i].name)
			   {
			    t[i].name = "";
			    t[i].id = 0;
			    t[i].priority = 0;
			    t[i].ramUse = 0;
			    cout << "Task deleted successfully.\n";
			    break;
			   }
			  }
			    cout << "\nTOTAL TASKS\n";
			    cout << left << setw(20) << "Name" << setw(15) << "Priority" << setw(10) << "RAM" << endl;
			    cout << string(45, '-') << endl;

			    for(int i = 0; i < count; ++i)
			    {
				if(t[i].name != "")
				{
				    cout << left << setw(20) << t[i].name 
					 << setw(15) << t[i].priority 
					 << setw(10) << t[i].ramUse << endl;
				}
			    }
				system("clear");
			    sleep(5);
			}
	
			}while((kChoice==1)||(kChoice==2));
			system("clear");
			break;//case 2 ends
	}
	return 0;
}
