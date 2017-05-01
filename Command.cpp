
using namespace std;

#include "Command.h"


/*
1.  should probably move validity back to Command.h as a private variable
    shouldn't matter though
2.  probably don't need the semi-colon class
3.  find out if connectors work like they should, or how it's written
*/

class normalCommand: public Command
{
    private:
        bool validity;
    public:
        normalCommand(string s)
        {
            //use syscall to execute (DO NOT USE SYSTEM)
            //also "exit"
            //set validity (true if it executes properly, false otherwise)
        };
        bool valid()
        {
            return validity;
        };
        int type();
        {
            return 1;
        };
};

class andConnector: public Command                          // &&
{
    private:
        bool validity;
        Command* l;
        Command* r;
    public:
        andConnector()      //Command* l, Command* r
        {
            
        };
        bool valid()
        {
            return validity;
        };
        int type();
        {
            return 2;
        };
        void set(Command* left, Command* right)
        {
            l = left;
            r = right;
            if(l->valid() && r->valid())
            {
                validity = true;
            }
            else
            {
                 validity = false;
            }
        }
};

class orConnector: public Command                           // ||
{
    private:
        bool validity;
        Command* l;
        Command* r;
    public:
        orConnector()       //Command* l, Command* r
        {
            
        };
        bool valid()
        {
            return validity;
        };
        int type();
        {
            return 3;
        };
        void set(Command* left, Command* right)
        {
            l = left;
            r = right;
            if(!l->valid() && !r->valid())
            {
                 validity = false;
            }
            else
            {
                 validity = true;
            }
        }
};


class semiColonConnector: public Command                    // ;
{
    // private:
    //     bool validity;
    public:
        semiColonConnector()
        {
            
        };
        bool valid()
        {
            return false;                                   // this is an error
        };
        int type();
        {
            return 4;
        };
};

































