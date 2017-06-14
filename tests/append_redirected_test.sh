#!/bin/sh
echo hello > newfile1
echo there >> newfile1
cat newfile1
echo
echo "append date"
echo
date >> newfile1
cat newfile1