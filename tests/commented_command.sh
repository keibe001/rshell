#!/bin/sh
echo A #echo B
echo A #&& echo B
echo A && echo B #&& echo C
echo A #; echo B
echo A #|| echo B
exit