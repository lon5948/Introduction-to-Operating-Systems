#include <iostream>
#include <sys/wait.h>
#include <unistd.h>
using namespace std;

int main(){
    cout << "Main Process ID : " << getpid() << endl;
    if(!fork()){ //fork 1
        cout << "Fork 1. I'm the child " << getpid() << ", my parent is " << getppid() << "." << endl;
        if(!fork()){ // fork 2
            cout << "Fork 2. I'm the child " << getpid() << ", my parent is " << getppid() << "." << endl;
            if(!fork()){ // fork 3
                cout << "Fork 3. I'm the child " << getpid() << ", my parent is " << getppid() << "." << endl;
            }
            else{
                wait(NULL);
            } 
        }
        else{
            wait(NULL);
        } 
    }
    else{ 
        wait(NULL);
        if(!fork()){ // fork 4
            cout << "Fork 4. I'm the child " << getpid() << ", my parent is " << getppid() << "." << endl;
        }
        else{
            wait(NULL);
            if(!fork()){ // fork 6
                cout << "Fork 6. I'm the child " << getpid() << ", my parent is " << getppid() << "." << endl;
            }
            else{
                wait(NULL);
            } 
        } 
        if(!fork()){ // fork 5
        cout << "Fork 5. I'm the child " << getpid() << ", my parent is " << getppid() << "." << endl;
	}
    }
}
