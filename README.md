


# rshell
CS 100 assignment

## Summary

Write a command shell called rshell that prints out a command prompt ($) <br /> that will either be a cmd (executable [ argumentList ] [ connector cmd ]) or a connector (|| or && or ;). Anything after a ‘#’ will be a comment and there is an exit command which exits your shell.

### BUGS
1. echo a sentence like "$ echo there once was a man from nantucket " <br /> 
prints out "from from from from from from nantucket"
2. The code will get stuck on previous commands and you will have to type the exit command repeatly until it eventualy exits.
ex) ls; lsf && echo a; echo a; && lsf; lfs || echo a && echo b; echo a || lsf && echo b
will result in having to use the exit command around 12 times
