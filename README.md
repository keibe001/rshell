



# rshell
CS 100 assignment

## Summary

Write a command shell called rshell that prints out a command prompt ($)  that will either be a cmd (executable [ argumentList ] [ connector cmd ]) or a connector (|| or && or ;). Anything after a ‘#’ will be a comment and there is an exit command which exits your shell.
rshell also has the test command built into it. It takes the form of test input/file or [ input/file ]. The -e, -f, -d flags are also included. 
Parenthesis make commands execute based on where the commands are relative to the parenthesis. Allows precedence of commands. 

### BUGS
1. Any attempts to exit within .sh files do not execute, but when typing exit in the terminal, it exits immediately
2. Entering the [] test command without a space before the ] causes a segmentation fault.
3. The output (True)/(False) of the test commands do not output in the .sh files, but when the command is entered individually, the output appears
4. Uneven amount of parenthesis throws out of range error