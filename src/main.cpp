#include "Base.h"
#include "Command.cpp"
#include "ReCommand.cpp"
#include "Connector.cpp"
#include "r_shell.cpp"
#include "TestCommand.cpp"

Base* launch(const vector<string>& cmd) {
    string x = "";
    string tempcmd = "";
    vector<string> seperate;
    vector<string> comm; 
    r_shell rshell;
    Base* root;
    bool right = false;
    

    for (unsigned i = 0; i < cmd.size(); ++i) {
        if (right) {
            right = false;
        }
        else if (cmd.at(i) == "&&") {
            if (cmd.at(i + 1).at(0) == '(') {
                x = cmd.at(i + 1);
                x = x.substr(1, x.size() - 2);
                rshell.parse(x, seperate);
                rshell.compareCommands(seperate, comm);
                andConnector* a = new andConnector(root,launch(comm));
                root = a;
                seperate.clear();
                comm.clear();
                right = true;
            }
            else {   
                if (cmd.at(i + 1).find("test") == 0) {
                    TestCommand* t = new TestCommand(cmd.at(i + 1));
                    andConnector* a2 = new andConnector(root, t);
                    root = a2;
                }
                else if (cmd.at(i + 1).at(0) == '[') {
                    tempcmd = "test";
                
                    for (unsigned j = 1; cmd.at(i + 1).at(j) != ']'; ++j) {
                        tempcmd =tempcmd + cmd.at(i + 1).at(j);
                    }

                    TestCommand* t = new TestCommand(tempcmd);
                    andConnector* a2 = new andConnector(root, t);
                    root = a2;
                }
                else {
                    Command* c1 = new Command(cmd.at(i + 1));
                    andConnector* a2 = new andConnector(root, c1);
                    root = a2;
                }
                right = true;
            }
        }
        else if (cmd.at(i) == ";") {
            if (i == cmd.size() - 1) {
                SemiConnector* s = new SemiConnector(root);
                root = s;
            }
            else if (cmd.at(i + 1).at(0) == '(') {
                x = cmd.at(i + 1);
                x = x.substr(1, x.size() - 2);
                rshell.parse(x, seperate);
                rshell.compareCommands(seperate, comm);
                SemiConnector* s1 = new SemiConnector(root,launch(comm));
                root = s1;
                seperate.clear();
                comm.clear();
                right = true;
            }
            else {
                if (cmd.at(i + 1).find("test") == 0) {
                    TestCommand* t = new TestCommand(cmd.at(i + 1));
                    SemiConnector* s2 = new SemiConnector(root, t);
                    root = s2;
                }
                else if (cmd.at(i + 1).at(0) == '[') {
                    tempcmd = "test";
                
                    for (unsigned j = 1; cmd.at(i + 1).at(j) != ']'; ++j) {
                        tempcmd =tempcmd + cmd.at(i + 1).at(j);
                    }

                    TestCommand* t = new TestCommand(tempcmd);
                    SemiConnector* s2 = new SemiConnector(root, t);
                    root = s2;
                }
                else {
                    Command* c1 = new Command(cmd.at(i + 1));
                    SemiConnector* s2 = new SemiConnector(root, c1);
                    root = s2;
                }
                right = true;
            }
        }
        else if (cmd.at(i) == "||") {
            if (cmd.at(i + 1).at(0) == '(') {
                x = cmd.at(i + 1);
                x = x.substr(1, x.size() - 2);
                rshell.parse(x, seperate);
                rshell.compareCommands(seperate, comm);
                orConnector* o2 = new orConnector(root,launch(comm));
                root = o2;
                seperate.clear();
                comm.clear();
                right = true;
            }
            else {
                if (cmd.at(i + 1).find("test") == 0) {
                    TestCommand* t = new TestCommand(cmd.at(i + 1));
                    orConnector* o = new orConnector(root, t);
                    root = o;
                }
                else if (cmd.at(i + 1).at(0) == '[') {
                    tempcmd = "test";
                
                    for (unsigned j = 1; cmd.at(i + 1).at(j) != ']'; ++j) {
                        tempcmd = tempcmd + cmd.at(i + 1).at(j);
                    }

                    TestCommand* t = new TestCommand(tempcmd);
                    orConnector* o = new orConnector(root, t);
                    root = o;
                }
                else {
                    Command* c1 = new Command(cmd.at(i + 1));
                    orConnector* o = new orConnector(root, c1);
                    
                    root = o;
                }
                
                right = true;
            }
        }
        else if (cmd.at(i).at(0) == '(') {
            x = cmd.at(i);
            x = x.substr(1, x.size() - 2);
            
            rshell.parse(x, seperate);
            rshell.compareCommands(seperate, comm);
            root = launch(comm);
            seperate.clear();
            comm.clear();
        }
        
            
        else {    
            if (cmd.at(i).find("test") == 0) {
                TestCommand* c = new TestCommand(cmd.at(i));
                root = c;
            }
            else if (cmd.at(i).at(0) == '[') 
            {
                tempcmd = "test";
                
                for (unsigned j = 1; cmd.at(i).at(j) != ']'; ++j) {
                    tempcmd =tempcmd + cmd.at(i).at(j);
                }

                TestCommand* c = new TestCommand(tempcmd);
                root = c;
            }
            else if((i + 2 < cmd.size() ) && (cmd.at(i+1) == ">" || cmd.at(i+1) == ">>" || cmd.at(i+1) == "<" ) )   //redirection
            {
                if(cmd.at(i+1) == "<")                                                                              //input redirection
                {
                    if(i+4 < cmd.size())
                    {
                        if(i<cmd.size()-4 && cmd.at(i+3) == ">>")   //type 5
                        {
                            /*
                            cmd.at(i)       = command
                            cmd.at(i+1)     = '<'
                            cmd.at(i+2)     = command2
                            cmd.at(i+3)     = ">>"
                            cmd.at(i+4)     = fileName
                            */
                            ReCommand* c5 = new ReCommand(cmd.at(i), cmd.at(i+2),cmd.at(i+4).c_str(),5);
                            root = c5;
                            i +=4;
                        }
                        else if(i<cmd.size()-4 && cmd.at(i+3) == ">")   //type 4
                        {
                            ReCommand* c4 = new ReCommand(cmd.at(i), cmd.at(i+2),cmd.at(i+4).c_str(),4);
                            root = c4;
                            i +=4;
                        }
                        else       //type 1
                        {
                            /*
                                cmd.at(i)       = command
                                cmd.at(i+1)     = '<' 
                                cmd.at(i+2)     = fileName
                            */
                            ReCommand* c1 = new ReCommand(cmd.at(i),cmd.at(i+2).c_str(),1);
                            root = c1;
                            i+=2;
                        }
                    }
                    else       //type 1
                    {
                        /*
                            cmd.at(i)       = command
                            cmd.at(i+1)     = '<' 
                            cmd.at(i+2)     = fileName
                        */
                        ReCommand* c1 = new ReCommand(cmd.at(i),cmd.at(i+2).c_str(),1);
                        root = c1;
                        i+=2;
                    }
                }
                /*
                    cmd.at(i)       = command
                    cmd.at(i+1)     = '>' or ">>"
                    cmd.at(i+2)     = fileName
                */
                else if(cmd.at(i+1) == ">")         //type 2
                {
                    ReCommand* c2 = new ReCommand(cmd.at(i),cmd.at(i+2).c_str(),2);
                    root = c2;
                    i+=2;
                }
                else if(cmd.at(i+1) == ">>")        //type 3
                {
                    ReCommand* c3 = new ReCommand(cmd.at(i),cmd.at(i+2).c_str(),3);
                    root = c3;
                    i+=2;
                }
            }
            else {
                Command* c = new Command(cmd.at(i));
                root = c;
            }
            
        }
    }
    
    return root;
}

int main() {	
	r_shell rshell;         
	string input ="";
	vector<string> v;
	vector<string> cmd;
    

    
	while(true) {
	    
        cout << "$ ";
        getline(cin, input); 
        
        while(input == "") {
            cout << "$ ";
            getline(cin, input);
        }
        rshell.delete_comments(input);
        rshell.parse(input, v);
        rshell.compareCommands(v, cmd);
        // for(unsigned i = 0; i <  cmd.size(); i ++)
        // {
        //     cout<<"\""<<cmd.at(i)<<"\""<<endl;
        // }

        Base* t1 = launch(cmd);
        t1->run();

        v.clear();
        cmd.clear();
    }

	return 0;
}


/*
cat < input.txt | tr A-Z a-z | tee newOutputFile1 | tr a-z A-Z > newOutputFile2
*/



