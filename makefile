CC=g++
CC_FLAGS=-Wall -Werror -ansi -pedantic
EXEC=test.out
SOURCES=$(wildcard *.cpp)
OBJECTS=$(SOURCES:.cpp=.o)

all: $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXEC)

rshell: 
	$(CC) $(CC_FLAGS) /.src/rshell.cpp 

clean:
	rm -f $(EXEC) $(OBJECTS)