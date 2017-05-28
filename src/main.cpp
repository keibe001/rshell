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
#include "Command.cpp"




/*


ls; lsf && echo a; echo a && lsf; lfs || echo a && echo b; echo a || lsf && echo b
*/



int main()
{
    bool terminate = false;
    cout<<"START"<<endl;
    while(!terminate)                                     //each newline
    {
        string input = "";
        string com = "";                          //each command
        cout << "$ ";
        getline (cin,input);
        vector <string> v;                        //vector of inputs: normal, &&, ||, ;
        if(terminate)
        {
            break;
        }
        for(unsigned i = 0; i < input.size() && !terminate; i++)       //reads input
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
        cout<<"Input Size: "<<input.size()<<endl;
        v.push_back(com);
        com = "";
        bool checker = false;                           //last command's truth value

        for(unsigned i = 0; i< v.size() && !terminate; i++)                         //read through v 
        {
            cout<<">>>>>>>> "<< v.at(i)<<" <<<<<<<<<"<<endl;
            if(v.at(i) == "exit" || terminate)
            {
                cout<<"EXIT"<<endl;
                terminate = true;
                return 0;
            }
            else if(v.at(i) == ";")
            {
                
            }
            else if(v.at(i) == "&&" && !terminate)
            {
                boost::trim_left(v.at(i+1));
                andConnector* a = new andConnector(checker, v.at(i+1));
                i++;                                   //skips v.at(i+1)
                checker = a->getValidity();              //truth value of &&
            }
            else if(v.at(i) == "||" && !terminate)
            {
                boost::trim_left(v.at(i+1));
                orConnector* o = new orConnector(checker, v.at(i+1));
                i++;                                    //skips v.at(i+1)
                checker = o->getValidity();             //truth value of ||
            }
            else if(!terminate)
            {
                boost::trim_left(v.at(i));
                if(v.at(i) == "exit")
                {
                    terminate = true;
                    return 0;
                }
                Command c(v.at(i));
                c.launch();
                checker = c.isValid();
            }
            else
            {
                cout<<"TERMINATE"<<endl;
                return 0;
            }
        }
        if(terminate)
        {
            break;
        }
    }
    return 0;
}










