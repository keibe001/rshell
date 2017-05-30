#!/bin/sh
(echo A && echo B)||(echo C || echo D)
(echo "True1")
(echo "True2" && echo "True3") 
(echo "True4" || echo "False") 
(echo "True5" && (echo "True6"))
(echo "True7" || (echo "False"))
(echo "True8" && (echo "True9" && (echo "True10"))) # 10 T 
([ -e /src/Base.h ]) && (echo "True11?") #question
(echo "True12" || echo "False") && echo "True13"
(echo "True14" && echo "True15") && (echo "True16" && echo "True17")
(echo "True18" && echo "True19") || (echo "False" && echo "False")
