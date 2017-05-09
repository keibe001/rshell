


# rshell
CS 100 assignment

## Summary

Write a command shell called rshell that prints out a command prompt ($)  that will either be a cmd (executable [ argumentList ] [ connector cmd ]) or a connector (|| or && or ;). Anything after a ‘#’ will be a comment and there is an exit command which exits your shell.

### BUGS
1. echo a sentence has the last two words in the correct place, but has the second to last word replacing all the previous words. <br /> ex) "$ echo there once was a man from nantucket" prints out "from from from from from from nantucket"
2. The code will get stuck on previous commands and you will have to type the exit command repeatly until it eventualy exits. <br /> ex) "ls; lsf && echo a; echo a && lsf; lfs || echo a && echo b; echo a || lsf && echo b"
will result in having to use the exit command approximately 8 times. Typing in new commands will still execute correctly, but it won't exit without multiple exit commands.
