#ifndef COMMAND_H
#define COMMAND_H

#include <iostream>
#include <string>
using namespace std;

class Command {
    
    private:
        string input;
        bool validity; 
        int status; 
    public:
        Command(string command);
        void launch();
        bool isValid();
        int getStatus();
        
};

#endif 