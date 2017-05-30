#ifndef COMMAND_H   
#define COMMAND_H

#include "Base.h" 

class Command : public Base {
    protected: 
        string command;
        vector<char*> user_flags;
    
    public:
        Command();
        Command(string command);
        bool run();
};

#endif