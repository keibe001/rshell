#ifndef COMMAND_H
#define COMMAND_H

#include <string>

class Command
{
    public:
        Command();
        virtual bool valid() = 0;
        virtual bool type() = 0;
    private:
        
};












#endif