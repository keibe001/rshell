#ifndef TESTCOMMAND_H
#define TESTCOMMAND_H

#include "Command.h"
#include <sys/stat.h>

class TestCommand : public Command {
    protected:
        string command;
        vector<char*> user_flags;
        
    public:
        TestCommand(string command);
        bool run();
};

#endif