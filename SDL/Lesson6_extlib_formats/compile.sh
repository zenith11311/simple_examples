#!/bin/bash

g++ -o $1 $1.c -I$DEV_HOME/tools/include -lSDL2 -lSDL2_image
