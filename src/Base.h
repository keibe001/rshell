#ifndef BASE_H
#define BASE_H

#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <string>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <iostream>
#include <vector>
using namespace std;

class Base {
    public:
        virtual bool run() = 0;
};

#endif