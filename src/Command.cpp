#include "Command.h"

Command::Command() {}

Command::Command(string command) {
    string tempCmd;
    size_t x = command.find(" ");
    char* tempCmdCStr = new char[500]; 
    
    if (x == string::npos) {
        this->command = command;
    }
    else {
        tempCmd = command; 
        
        this->command = tempCmd.substr(0, x);
        tempCmd.erase(0, x + 1);
        strcpy(tempCmdCStr, tempCmd.c_str());
        char* temp= strtok(tempCmdCStr, " ");
        
        while (temp != NULL) {
            user_flags.push_back(temp);
            temp = strtok(NULL, " ");
        }
    }
}

bool Command::run() {
    if (command == "exit") {
        exit(EXIT_SUCCESS);
    }
    
    int status;
    bool ran = true;
    char* x[500];
    char* temp = new char[100];
    
    
    strcpy(temp, command.c_str());
    x[0] = temp;
    
    if (user_flags.size() != 0) {
		for (unsigned i = 1; i <= user_flags.size(); ++i) {
			x[i] = user_flags[i - 1];
		}
    }
    
    x[user_flags.size() + 1] = NULL; 
    pid_t pid = fork();
    
    if (pid == -1) {
        ran = false;
        perror("fork() has failed");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0) {
        if (execvp(command.c_str(), x) == -1) {
            ran = false;
            perror("execvp() has failed");
            exit(EXIT_FAILURE);
        }
    }
    else if (pid > 0) {
        if (waitpid(pid, &status, 0) == -1) {
            perror("wait() has failed");
        }
        
        if (WIFEXITED(status) == 1) {
            if (WEXITSTATUS(status) != 0) {
                ran = false;
            }
        }
    }
    
    return ran;
}
