#include "r_shell.h"

void r_shell::delete_comments(string &input) {
    size_t octothorpe = input.find_first_of("#");
    
    if(octothorpe != string::npos) {
        input.erase(octothorpe + input.begin(), input.end());
    }
}

void r_shell::parse(const string& input, vector<string>& holdParsedInput) {
    unsigned i = 0;
    char* inputCstr = new char[input.size() + 1];
    string temp;
    
    strcpy(inputCstr, input.c_str());
    char* AlreadyParsedInput = strtok(inputCstr, " ");
    
    while (AlreadyParsedInput != NULL) { 
        temp = AlreadyParsedInput;
        holdParsedInput.push_back(temp);
        AlreadyParsedInput = strtok(NULL, " ");
        i++;
    }
}

void r_shell::compareCommands(const vector<string>& seperatedInput, vector<string>& v) {             
    string mod;
    for (unsigned i = 0; i < seperatedInput.size(); ++i) {

        if (seperatedInput.at(i).compare("&&") == 0) {
            if(!mod.empty()) {
                v.push_back(mod);
                mod.clear();
            }
            v.push_back("&&");
        }
        
        else if (seperatedInput.at(i).compare("||") == 0) {
            if(!mod.empty()) {
                v.push_back(mod);
                mod.clear();
            }
            v.push_back("||");
        }
        
        else if (seperatedInput.at(i).compare("|") == 0) {
            if(!mod.empty()) {
                v.push_back(mod);
                mod.clear();
            }
            v.push_back("|");
        }
        
        else if (seperatedInput.at(i).compare(seperatedInput.at(i).size() - 1, 1, ";") == 0) {
            if (!mod.empty()) {
                mod = mod + seperatedInput.at(i);
                mod.erase(mod.size() - 1, 1);
                v.push_back(mod);
                mod.clear();
            }
            v.push_back(";");
        }
        
        else if (seperatedInput.at(i).compare(0, 1,  "(") == 0) {
            bool p_end = false;
            bool semiEnd = false;
            while (!semiEnd && !p_end) {
                if (seperatedInput.at(i).compare(seperatedInput.at(i).size() - 1, 1,  ")") == 0) {
                    p_end = true;
                }
                if (seperatedInput.at(i).compare(seperatedInput.at(i).size() - 1, 1, ";") == 0) {
                    semiEnd = true;
                }
                if (!semiEnd && !p_end) {
                    mod = mod + seperatedInput.at(i);
                    mod = mod + " ";
                    i++;
                }
            }
            if (p_end) {
                mod = mod + seperatedInput.at(i);
                v.push_back(mod);
                mod.clear();
            }
            else if(semiEnd) {
                mod = mod + seperatedInput.at(i);
                mod.erase(mod.size() - 1, 1);
                v.push_back(mod);
                v.push_back(";");
                mod.clear();
            }
        }
        
        //ReCommand < , > , >>
        else if(seperatedInput.at(i) ==  "<" || seperatedInput.at(i) ==  ">" || seperatedInput.at(i) ==  ">>")
        {
            if(seperatedInput.at(i) ==  "<")
            {
                unsigned j = i+1;
                
                if(!mod.empty()) 
                {
                    v.push_back(mod);       //command cat, sort, etc
                    mod.clear();
                }
                string pipes = "";
                v.push_back("<");
                while(j < seperatedInput.size() )                     //search for mirror >
                {
                    if(seperatedInput.at(j) == ">" || seperatedInput.at(j) == ">>" 
                    || seperatedInput.at(j) == "&&" || seperatedInput.at(j) == "||" || seperatedInput.at(j) == ";" )
                    {
                        v.push_back(pipes);
                        v.push_back(seperatedInput.at(j));
                        i = j;
                        break;
                    }
                    pipes += seperatedInput.at(j);
                    j++;
                }
            }
            else
            {
                if(!mod.empty()) 
                {
                    v.push_back(mod);
                    mod.clear();
                }
                v.push_back(seperatedInput.at(i));
            }
        }
        
        else if (seperatedInput.at(i) ==  "[") {
            bool p = false;
            unsigned q;
            
            for (unsigned k = i; k < seperatedInput.size(); ++k) {
                if (seperatedInput.at(k) ==  "]") {
                    p = true;
                    q = k;
                } 
            }
            if (!p) {
                cout << "Error: Input right bracket or put spaces between brackets" << endl;
                
                v.pop_back();
                
                break;
            }
            
            for (unsigned j = i; j <= q; ++j) {   
                mod = mod + seperatedInput.at(j);
                mod = mod + " ";
            }
            v.push_back(mod);
            mod.clear();
            i = i + q - i;
        }
        
        else if (i == seperatedInput.size() - 1) {
            mod = mod + seperatedInput.at(i);
            v.push_back(mod);
            mod.clear();
        }

        else {
            mod = mod + seperatedInput.at(i);
            mod = mod + " ";
        }
    }
}