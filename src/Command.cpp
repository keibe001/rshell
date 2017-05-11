#include "Command.h"
#include <iostream>
#include <string>
#include <cstring>
#include <stdio.h>
#include<stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

Command::Command(string command) {
    input = command;
}

void Command::launch() { 

    if (input == "exit") {
        abort(); 
    }
    
    char** command_arr = new char*[1000];
    string command_copy = input.substr(0,input.find(" "));
    
    char *command_copy_2 = new char[input.length()]; 
    char *command_copy_3 = new char[input.length()];
    strcpy(command_copy_2,command_copy.c_str());
    
    int x = 0; 
    while (input.find(" ") < 1000) { // while no whitespace found
        if(x == 0) {
            command_arr[x] = command_copy_2;
            x++;
        }
        
        else {
        command_copy = input.substr(0, input.find(" ")); 
            strcpy(command_copy_3, command_copy.c_str());
            command_arr[x] = command_copy_3; 
            x++;
        }
        
        input.erase(0,input.find(" ") + 1);
    }
    
    if(!input.empty()) {
        command_copy = input;
        char *cmd = new char[input.length()];
        strcpy(cmd,command_copy.c_str());
        command_arr[x] = cmd;
        delete[] cmd;
    }
    
    command_arr[x+1] = 0; 
    pid_t pid = fork(); 
    int pidnum = 1; 
    
    //checks if processes output correctly 
    if (pid == -1) {
        perror("Fork failed");
        pidnum = -1; 
        status = pidnum;
    }
    
    else if (pid == 0 && execvp(command_copy_2, command_arr)) {
        perror("Execute failed");
        pidnum = -1; 
        status = pidnum;
        return;
    }
    
    else if (pid > 0) {
        if (wait(0) == -1) {
            perror("Wait failed"); 
            pidnum = -1;
            status = pidnum;
        }
    }
    
    delete[] command_arr;
    delete[] command_copy_2;
    delete[] command_copy_3;
    status = pidnum;
    return; 
}

bool Command::isValid() {
    if(getStatus() == 1) {
        validity = true; 
        return validity;
    }
    
    validity = false;
    return validity;
}

int Command::getStatus() {
    return status;
}