using namespace std;

#include <iostream>
#include <string>
#include <vector>
//need these?
#include <unistd.h>     // getpid(), getcwd()
#include <sys/types.h>  // type definitions, e.g., pid_t
#include <sys/wait.h>   // wait()
#include <signal.h>     // signal name constants and kill()


//Here goes the #include "files"
#include "Command.h"





/*
1.  add error checks for consecutive connectors (;; should be fine?)
2.  
*/



int main()
{
    string input = "";
    while(true)                                     //each newline
    {
        string com = "";                          //each command
        cout << " $ ";
        cin >> input;
        vector <Command*> v;                        //vector of inputs: normal, &&, ||, ;
        for(int i = 0; i < input.size(); i++)       //reads input
        {
            if(input.at(i) == '#')                  //comments out the rest
            {
                break;                  //need to double check if it still 
                                        //works if you type \# or somehting
            }
            if(input.at(i) == ';')
            {
                Command* A = new normalCommand(com);
                v.push_back(A);
                Command* B = new semiColonConnector();
                v.push_back(B);
                com = "";
            }
            else
            {
                if(i < input.size()-1 && input.at(i) == '&' && input.at(i+1)=='&')  //&&
                {
                    i++;
                    Command* A = new normalCommand(com);
                    v.push_back(A);
                    Command* B = new andConnector();
                    v.push_back(B);
                    com = "";
                }
                else if(i < input.size()-1 && input.at(i) == '|' && input.at(i+1)=='|')     //||
                {
                    i++;
                    Command* A = new normalCommand(com);
                    v.push_back(A);
                    Command* B = new orConnector();
                    v.push_back(B);
                    com = "";
                }
                else
                    com += input.at(i);               //adds to the string to be read
            }
        }
        Command* left = v.at(0);
        for(int i = 0; i< v.size(); i++)                            //read through v 
        {
            if(v.at(i)->type() == 2 || v.at(i)->type() == 3)    //v.at(i) is a connector
            {
                //add error checks later
                v.at(i)->set(left,v.at(i+1));
                left = v.at(i);             //this is now the left most operator
            }
            if(v.at(i)->type() == 4)    //v.at(i) is a semi-colon;
            {
                if(i < v.size() -1)
                {
                    left = v.at(i+1);
                }
            }
        }
    }
}