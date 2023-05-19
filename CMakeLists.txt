cmake_minimum_required(VERSION 3.21.1)
project(Wet1)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

#add_executable(Wet1
#        AVLNode.h
#        maina1.cpp
#        StreamingDBa1.cpp
#        StreamingDBa1.h
#        wet1util.h AVLTree.h
#        Key.h)
add_executable(RankTree.h rankTreeTester.cpp run_test.sh AVLNode.h)

