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
add_executable(Wet1 wet1util.h Key.h main_ut.cpp AVLNode.h Ranktree.h StreamingDBa1.cpp StreamingDBa1.h MoviesRankingKey.h MoviesRankingKey.cpp Data.h)
add_executable(Wet2 rankTreetester.cpp run_test.sh AVLNode.h RankTree.h)
add_executable(Wet3 main_ut.cpp AVLNode.h RankTree.h)
#rankTreetester.cpp run_test.sh
#main_ut.cpp