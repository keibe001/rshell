CC=g++
CC_FLAGS=-Wall -Werror -ansi -pendantic

all: rshell

rshell: main.cpp Command.cpp Connector.cpp
	gcc -o rshell main.cpp Command.cpp Connector.cpp
	
clean: rm all main.cpp Command.cpp Connector.cpp