#!/bin/bash

clear
g++ -std=c++0x lexer.cpp -o lexer
lexer input.txt
g++ -std=c++0x engine.cpp -o engine
engine
g++ -std=c++0x syntactic.cpp -o syntactic
syntactic
