#!/bin/bash
if [ "$#" -lt 2 ];
	then
		echo "Params[Diretorio][Nome arquivo de teste]"
	else
		g++ $1/$2.cpp /usr/lib/libgtest.a -o test.bin -fPIC -g -Wall -lpthread -std=c++11
		./test.bin

		rm test.bin
fi
