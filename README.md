



# rshell
CS 100 assignment

## Summary

Write a command shell called rshell that prints out a command prompt ($)  that will either be a cmd (executable [ argumentList ] [ connector cmd ]) or a connector (|| or && or ;). Anything after a ‘#’ will be a comment and there is an exit command which exits your shell.

### BUGS
1. echo a sentence has the last two words in the correct place, but has the second to last word replacing all the previous words. <br /> ex) "$ echo there once was a man from nantucket" prints out "from from from from from from nantucket"
2. The code will get stuck on previous commands and you will have to type the exit command repeatly until it eventualy exits. <br /> ex) "ls; lsf && echo a; echo a && lsf; lfs || echo a && echo b; echo a || lsf && echo b"
will result in having to use the exit command approximately 8 times. Typing in new commands will still execute correctly, but it won't exit without multiple exit commands.
3. There are no syntax checkers, so it reads a single connector (| or &) has a word  <br /> ex) "$ echo a | echo b" gives you "echo echo echo b" 
4. Having three connectors (&&&) also creates an error, and it will execute the first one but not the following because it would pass the final '&' along to Command::launch()
5. Having two semi-colon's together also creates an error because it pushes an empty string onto the vector of strings that are passed into the Command::launch().
6. Just typeing enter on the command line gives you "Execute failed: No such file or directory"
7. The exit.sh doesn't exit the program
8. The multi_command.sh causes a Segmentation Fault frequently.
