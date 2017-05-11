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
#include "Connector.cpp"        //and / or




/*


ls; lsf && echo a; echo a && lsf; lfs || echo a && echo b; echo a || lsf && echo b
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
                break;                  
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
        cin.clear();
        v.push_back(com);
        bool checker = false;                           //last command's truth value

        for(int i = 0; i< v.size(); i++)                         //read through v 
        {
            if(v.at(i) == "exit" )
            {
                return 0;
            }
            if(v.at(i) == ";")
            {
                
            }
            else if(v.at(i) == "&&" )
            {
                boost::trim_left(v.at(i+1));
                andConnector* a = new andConnector(checker, v.at(i+1));
                i++;                                   //skips v.at(i+1)
                checker = a->getValidity();              //truth value of &&
            }
            else if(v.at(i) == "||" )
            {
                boost::trim_left(v.at(i+1));
                orConnector* o = new orConnector(checker, v.at(i+1));
                i++;                                    //skips v.at(i+1)
                checker = o->getValidity();             //truth value of ||
            }
            else
            {
                boost::trim_left(v.at(i));
                if(v.at(i) == "exit")
                {
                    return 0;
                }
                Command c(v.at(i));
                c.launch();
                checker = c.isValid();
            }

        }
    }
    return 0;
}










