#include "Command.h"

Command::Command() {}

Command::Command(string command) {
    string tempCmd;
    size_t x = command.find(" ");
    char* tempCmdCStr = new char[500]; 
    
    if (x == string::npos) //npos is a static member constant value with the greatest 
    {                           // possible value for an element of type size_t.
        this->command = command;
    }
    else 
    {
        tempCmd = command; 
        
        this->command = tempCmd.substr(0, x);
        tempCmd.erase(0, x + 1);
        strcpy(tempCmdCStr, tempCmd.c_str());
        char* temp= strtok(tempCmdCStr, " ");
        
        while (temp != NULL) 
        {
            user_flags.push_back(temp);
            temp = strtok(NULL, " ");
        }
    }
    /*
        command = the string upto the first space
        user_flags = vector of char* that is composed of everything after the initial command
    */
}

bool Command::run() {
    if (command == "exit") {
        exit(EXIT_SUCCESS);
    }
    
    int status;
    bool ran = true;
    char* x[500];
    char* temp = new char[100];
    
    
    strcpy(temp, command.c_str());  //copies command.c_str() onto temp with a NULL at the end
    x[0] = temp;
    
    if (user_flags.size() != 0) 
    {
		for (unsigned i = 1; i <= user_flags.size(); ++i) 
		{
			x[i] = user_flags[i - 1];
		}
    }
    
    x[user_flags.size() + 1] = NULL; 
    pid_t pid = fork();
    /*
    Description: fork creates a child process that differs from the parent process only in its PID and
    PPID, and in the fact that resource utilizations are set to 0. File locks and pending signals
    are not inherited.
    
    Returns: On success, the PID of the child process is returned in the parent’s thread of execution,
    and a 0 is returned in the child’s thread of execution.

    */
    
    if (pid == -1) //fork failed
    {
        ran = false;
        perror("fork() has failed");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0)  //This is done by the child process.
    {  
        // char const* fileName = "output.txt";
        // int fd = open(fileName, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
        // dup2(fd, 1);   // make stdout go to file
        int blue = execvp(command.c_str(), x);
        // close(fd);
        if (blue == -1)   ///* If execvp returns, it must have failed. */
        {
            ran = false;
            perror("execvp() has failed");
            exit(EXIT_FAILURE);
        }
    }
    else if (pid > 0)       /* This is run by the parent.  Wait for the child to terminate. */
    {
        if (waitpid(pid, &status, 0) == -1) //waiting for the child
        {
            perror("wait() has failed");
        }
        
        if (WIFEXITED(status) == 1) //returns a nonzero value if the child process terminated normally with exit or _exit.
        {
            if (WEXITSTATUS(status) != 0) //WEXITSTATUS returns the child's exit status.
            {
                ran = false;
            }
        }
    }
    
    return ran;
}
