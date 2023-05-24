cmake_minimum_required(VERSION 3.21.1)
project(Wet1)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_EXE_LINKER_FLAGS "-static")
include_directories(.)

#add_executable(Wet1
#        AVLNode.h
#        maina1.cpp
#        StreamingDBa1.cpp
#        StreamingDBa1.h
#        wet1util.h AVLTree.h
#        Key.h)
add_executable(Wet1 wet1util.h Key.h AVLNode.h maina1.cpp Ranktree.h StreamingDBa1.cpp StreamingDBa1.h MovieData.cpp MovieData.h MoviesRankingKey.h MoviesRankingKey.cpp Data.h UserData.cpp UserData.h GroupData.cpp GroupData.h)
add_executable(Wet2 rankTreetester.cpp run_test.sh AVLNode.h RankTree.h)
add_executable(Wet3 main_ut.cpp AVLNode.h RankTree.h)
#rankTreetester.cpp run_test.sh
#main_ut.cpp
#add_executable(Wet1 AVLNode.h Ranktree.h run_test.sh rankTreeTester.cpp)
