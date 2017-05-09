// <<<<<<< HEAD
using namespace std;

#include <iostream>
#include <string>
#include <vector>
//need these?
#include <unistd.h>     // getpid(), getcwd()
#include <sys/types.h>  // type definitions, e.g., pid_t
#include <sys/wait.h>   // wait()
#include <signal.h>     // signal name constants and kill()
#include <boost/algorithm/string.hpp>   // boost::trim_left(string s);

//Here goes the #include "files"
#include "Command.h"                      
#include "Connector.h"
#include "Connector.cpp"
// #include "Command.cpp"   



/*
#include "command.h"                        //jose's main.cpp

int main() {
    
    string s = "";
    
    cout << "$: "; 
    getline(cin, s);
    
    Command input(s);
    input.launch();
    
    return 0;
}
*/



/*
1.  add error checks for consecutive connectors (;; should be fine?)

5.  syntax ERROR: "bash: syntax error near unexpected token `||'"

ls; lsf && echo a; echo a; && lsf; lfs || echo a && echo b; echo a || lsf && echo b
*/



int main()
{
    
    while(true)                                     //each newline
    {
        string input = "";
        string com = "";                          //each command
        cout << "$ ";
        getline (cin,input);
        vector <string> v;                        //vector of inputs: normal, &&, ||, ;
        for(int i = 0; i < input.size(); i++)       //reads input
        {
            if(input.at(i) == '#')                  //comments out the rest
            {
                break;                  //need to double check if it still 
                                        //works if you type \# or somehting
            }
            if(input.at(i) == ';')
            {
                v.push_back(com);
                v.push_back(";");
                com = "";
            }
            else
            {
                if(i < input.size()-1 && input.at(i) == '&' && input.at(i+1)=='&')  //&&
                {
                    i++;
                    v.push_back(com);
                    v.push_back("&&");
                    com = "";
                }
                else if(i < input.size()-1 && input.at(i) == '|' && input.at(i+1)=='|')     //||
                {
                    i++;
                    v.push_back(com);
                    v.push_back("||");
                    com = "";
                }
                else
                    com += input.at(i);               //adds to the string to be read
            }
        }
        v.push_back(com);
        bool checker = false;
        
        // //remove this
        // cout<<"input # size: " << v.size()<<endl;
        // if(v.size() == 1)
        // {
        //     cout<<"["<<v.at(0)<<"]"<<endl;
        // }
        
        for(int i = 0; i< v.size(); i++)                         //read through v 
        {
            if(v.at(i) == "exit")
            {
                return 0;
            }
            if(v.at(i) == ";")
            {
                //  cout<<"SEMI"<<endl;
            }
            else if(v.at(i) == "&&")
            {
                boost::trim_left(v.at(i+1));
                // cout<<"&&: ["<< v.at(i+1)<<"]"<<endl;
                andConnector* a = new andConnector(checker, v.at(i+1));
                i++;
                checker = a->getValidity();              //truth value of &&
                // cout<<v.at(i)<<endl;
            }
            else if(v.at(i) == "||")
            {
                boost::trim_left(v.at(i+1));
                // cout<<"||: ["<< v.at(i+1)<<"]"<<endl;
                orConnector* o = new orConnector(checker, v.at(i+1));
                i++;
                checker = o->getValidity();
            }
            else
            {
                
                boost::trim_left(v.at(i));
                
                if(v.at(i) == "exit")
                {
                    // cout<<"exited"<<endl;
                    return 0;
                }
                
                // cout<<"Whats entering: " << v.at(i)<<endl;
                Command c(v.at(i));
                c.launch();
                checker = c.isValid();
                // cout<<v.at(i)<<endl;
            }

        }
    }
    return 0;
}










