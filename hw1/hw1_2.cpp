#include <iostream>
#include <sys/wait.h>
#include <unistd.h>
using namespace std;

int main(){
    cout << "Main Process ID : " << getpid();
    if(!fork()){ //child process
        cout << "Fork 1. I'm the child " << getpid() << ", my parent is " << getppid() << "." << endl;
        if(fork()>0){
            wait(NULL);
        }
        else{
            cout << "Fork 2. I'm the child " << getpid() << ", my parent is " << getppid() << "." << endl;
            if(fork()>0){
                wait(NULL);
            }
            else{
                cout << "Fork 3. I'm the child " << getpid() << ", my parent is " << getppid() << "." << endl;
            } 
        } 
    }
    else{ //parent process
        wait(NULL);
        if(fork()>0){
            wait(NULL);
            if(fork()>0){
                wait(NULL);
            }
            else{
                cout << "Fork 6. I'm the child " << getpid() << ", my parent is " << getppid() << "." << endl;
            } 
        }
        else{
            cout << "Fork 4. I'm the child " << getpid() << ", my parent is " << getppid() << "." << endl;
        } 
        cout << "Fork 5. I'm the child " << getpid() << ", my parent is " << getppid() << "." << endl;
    }
}
