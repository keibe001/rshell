#!/bin/sh
#cases when it should be true
test src/Base.h
test -e src/Base.h
test -f Base.h
test -d src
#cases when it should be false
test src/Base.cpp
test -e src/Base.cpp
test -f src
test -d src/Base.h
#cases where parens, test and connectors are combined, should be true 
(test src/Base.h && echo "A")
(test -e src/Base.h || echo "B")
(test -f Base.h ; echo "C")
(test -d src && (echo "D" || (echo "A" || echo "B")))
#cases where parens, test and connectors are combined, should be false
test src/Base.cpp
test -e src/Base.cpp
test -f src
test -d src/Base.h
#cases where [] are used, should be true
([ src/Base.h ] && echo "A") || echo "B"
[ -e src/Base.h ]
[ -f Base.h ]
[ -d src ]
#cases where [] are used, should be false
[ src/Base.cpp ] 
[ -e src/Base.cpp ]
[ -f src ]
[ -d src/Base.h ]