#ifndef CONNECTOR_H
#define CONNECTOR_H

// #include "command.h"

#include <iostream>
#include <string>
using namespace std;

class Connector {
    
    private:
        bool left;
        string right;
        
    protected:
        bool self;
        
    public:
        Connector(bool l, string s )
        {
            left = l;
            right = s;
        }
        virtual bool getValidity() = 0;

};

#endif 