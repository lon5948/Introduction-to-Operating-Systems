#include <iostream>
#include <unistd.h>
using namespace std;

int main(){
    cout << "Main Process ID : " << getpid();
    if(!fork()){ //child process
        cout << "Fork 1. I'm the child " << getpid() << ", my parent is " << getppid() << ".";
        if(fork()>0){
            wait(NULL);
        }
        else{
            cout << "Fork 2. I'm the child " << getpid() << ", my parent is " << getppid() << ".";
            if(fork()>0){
                wait(NULL);
            }
            else{
                cout << "Fork 3. I'm the child " << getpid() << ", my parent is " << getppid() << ".";
            } 
        } 
    }
    else{ //parent process
        wait(NULL);
        if(fork()>0){
            wait(NULL);
        }
        else{
            cout << "Fork 4. I'm the child " << getpid() << ", my parent is " << getppid() << ".";
        } 
    }
}