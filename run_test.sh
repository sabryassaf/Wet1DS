#!/bin/bash
g++ -std=c++11 rankTreeTester.cpp wet1util.h AVLNode.h RankTree.h -o exe_test
chmod +x exe_test
./exe_test
