#include "TestCommand.h"

TestCommand::TestCommand(string command) {
    string tempCmd = ""; 
    size_t x = command.find(" ");
    char* tempCmdCstr = new char[500];
    
    if (x == string::npos) {
        this->command = command;
    }
    else {
        tempCmd = command;
        
        this->command = tempCmd.substr(0, x);
        tempCmd.erase(0, x + 1);
        strcpy(tempCmdCstr, tempCmd.c_str());
        char* temp = strtok(tempCmdCstr, " ");
        
        while (temp != NULL) {
            user_flags.push_back(temp);
            temp = strtok(NULL, " ");
        }
    }
}


bool TestCommand::run() {
    string f = "";
    bool ran;
    struct stat sb;
    char* z;
    
    if (user_flags.size() == 1) {
        f = "-e";
        z = user_flags[0];
    }
    else if (user_flags.size() == 2) {
        f.assign(user_flags[0], 2);
        z = user_flags[1];
    }
    else {
        perror("Error: Invalid input");
        exit(EXIT_FAILURE);
    }

    if (stat(z, &sb) == 0) {
        if (f == "-e"){
            ran = true;
        }
        else if (f == "-f") {
            ran = S_ISREG(sb.st_mode);
        }
        else if (f == "-d") {
            ran = S_ISDIR(sb.st_mode);
        }
        else {
            cout << "Error: Invalid input" << endl;
            exit(EXIT_FAILURE);
        }
    }
    else {
        ran = false;
    }
    
    if (ran) {
        cout << "(True)" << endl;
    }
    else {
        cout << "(False)" << endl;
    }
    
    return ran;
} 