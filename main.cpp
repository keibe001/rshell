using namespace std;

#include <iostream>
#include <string>

//Here goes the #include "files"

int main()
{
    string input = "";
    while(true)                                     //each newline
    {
        string parse = "";                          //each command
        cout << " $ ";
        cin >> input;
        for(int i = 0; i < input.size(); i++)       //reads input
        {
            if(input.at(i) == '#')                  //comments out the rest
            {
                break;
            }
            if(input.at(i) == ';')
            {
                //pass parse into Command
                    //Command* A = new Command(parse)
                parse = "";
            }
            else
            {
                //read for && or || ??????????????
                /*
                    when you get to a connector pass the left one into the Command
                    if(&) -> if(Left == true): then pass right
                */
                parse += input.at(i);               //adds to the string to be read
            }
        }
    }
}