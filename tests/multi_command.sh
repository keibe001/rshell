#!/bin/sh
echo A || echo B
echo A; echo B
ls -i && echo A
ls -i || echo A
ls -i; echo A
ls -i && echo A || echo B
echo A || echo B || echo C
echo A || echo B && echo C
echo A && echo B && echo C  # print A, B, C