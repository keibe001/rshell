


#include "Command.h"


/*
    should probably move validity back to Command.h as a private variable
    shouldn't matter though
*/

class normalCommand: public Command
{
    private:
        bool validity;
    public:
        normalCommand(string s)
        {
            //use syscall to execute
            //set validity (true if it executes properly, false otherwise)
        };
        bool valid()
        {
            return validity;
        };
};

class andConnector: public Command
{
    private:
        bool validity;
    public:
        andConnector(Command* l, Command* r)
        {
            
        };
        bool valid()
        {
            return validity;
        };
};

class orConnector: public Command
{
    private:
        bool validity;
    public:
        orConnector(Command* l, Command* r)
        {
            
        };
        bool valid()
        {
            return validity;
        };
};