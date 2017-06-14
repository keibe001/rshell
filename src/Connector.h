#ifndef CONNECTOR_H  
#define CONNECTOR_H

#include "Base.h"

class Connector : public Base {
    protected:
        Base* left;
        Base* right;
    
    public:
        Connector();
        Connector(Base* left, Base* right);
        virtual bool run() = 0;
};

class andConnector : public Connector {
    protected:
        Base* left;
        Base* right;
        
    public:
        andConnector(Base* left, Base* right);
        bool run();
};

class SemiConnector : public Connector {
    protected:
        Base* left;
        Base* right;
        bool hasRight;
        
    public:
        SemiConnector(Base* left);
        SemiConnector(Base* left, Base* right);
        bool run();

};

class orConnector : public Connector {
    protected:
        Base* left;
        Base* right;
        
    public:
        orConnector(Base* left, Base* right);
        bool run();
};

class PipeConnector : public Connector {
    protected:
        Base* left;
        Base* right;
        
    public:
        PipeConnector(Base* left, Command* right);
        bool run();
};


#endif