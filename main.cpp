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
// #include "Command.h"                         //add in back later





/*
1.  add error checks for consecutive connectors (;; should be fine?)
2.  || only works when the first fials
3.  fix the & and || so that they only execute the second command depending on the outcome of the first
4.  make v a vector of strings that pass them into the command in the second for loop  
5.  syntax ERROR: "bash: syntax error near unexpected token `||'"
*/



int main()
{
    string input = "";
    // bool flag = true;
    while(true)                                     //each newline
    {
        string com = "";                          //each command
        cout << " $ ";
        // cin >> input;
        getline (cin,input);
        // if (input == !cin.eof())
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
                //Command* A = new normalCommand(com);
                // v.push_back(A);
                // Command* B = new semiColonConnector();
                // v.push_back(B);
                v.push_back(com);
                v.push_back(";");
                com = "";
            }
            else
            {
                if(i < input.size()-1 && input.at(i) == '&' && input.at(i+1)=='&')  //&&
                {
                    i++;
                    // Command* A = new normalCommand(com);
                    // v.push_back(A);
                    // Command* B = new andConnector();
                    // v.push_back(B);
                    v.push_back(com);
                    v.push_back("&&");
                    com = "";
                }
                else if(i < input.size()-1 && input.at(i) == '|' && input.at(i+1)=='|')     //||
                {
                    i++;
                    // Command* A = new normalCommand(com);
                    // v.push_back(A);
                    // Command* B = new orConnector();
                    // v.push_back(B);
                    v.push_back(com);
                    v.push_back("||");
                    com = "";
                }
                else
                    com += input.at(i);               //adds to the string to be read
            }
        }
        v.push_back(com);
        // Command* left = v.at(0);
        // vector <Command*> C; 
        cout<<"Size: " <<v.size()<<endl;
        for(int i = 0; i< v.size(); i++)                         //read through v 
        {
            // cout<<"Inside for loop"<<endl;
            if(v.at(i) == ";")
            {
                //do nothing or pass into C
                cout<<v.at(i)<<endl;
            }
            else if(v.at(i) == "&&")
            {
                // Command* B = new andConnector();
                // C.push_back(B);
                /*
                check validity of the statement before, only execute if the first one works
                */
                cout<<v.at(i)<<endl;
            }
            else if(v.at(i) == "||")
            {
                // Command* B = new orConnector();
                // v.push_back(B);
                /*
                checks validity of the statement before, only executes if the first one fails
                */
                cout<<v.at(i)<<endl;
            }
            else
            {
                //Command* A = new normalCommand(com);
                // v.push_back(A);
                /*
                remove whitespace?
                */
                if(v.at(i) == "exit")
                {
                    cout<<"exited"<<endl;
                    return 0;
                }
                cout<<v.at(i)<<endl;
            }
            // cout<<"Outside for loop"<<endl;
        }
        // flag = false;
    }
    return 0;
}

















            // if(v.at(i)->type() == 2 || v.at(i)->type() == 3)    //v.at(i) is a connector
            // {
            //     //add error checks later
            //     v.at(i)->set(left,v.at(i+1));
            //     left = v.at(i);             //this is now the left most operator
            // }
            // if(v.at(i)->type() == 4)    //v.at(i) is a semi-colon;
            // {
            //     if(i < v.size() -1)
            //     {
            //         left = v.at(i+1);
            //     }
            // }