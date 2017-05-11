#ifndef CONNECTOR_CPP
#define CONNECTOR_CPP

#include "Command.h"
#include "Connector.h"

using namespace std;
#include <iostream>
#include <vector>
#include <list>

//   VectorContainer(Sort* function):Container(function){};


class andConnector: public Connector
{
    private:
    
    public:

        andConnector(bool l, string s) : Connector(l,s)
        {
            // left = l;
            // right = s;
            self = false;
            if(l)
            {
                Command input(s);
                input.launch();
                self = (l && input.isValid() );
            }

            //input.getValidity()
            
        };
        
        bool getValidity()
        {
            return self;
        }
};


class orConnector: public Connector
{
    private:
    
    public:

        orConnector(bool l, string s) : Connector(l,s)
        {
            // left = l;
            // right = s;
            self = l;
            if(!l)
            {
                Command input(s);
                input.launch();
                self = (l || input.isValid() );
            }
            //input.getValidity()
            
        };
        
        bool getValidity()
        {
            return self;
        }
};










#endif 