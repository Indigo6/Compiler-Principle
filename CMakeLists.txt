cmake_minimum_required(VERSION 2.8)
project(pl0)

set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g2 -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")

add_subdirectory(lex)
add_subdirectory(common)
add_subdirectory(syntax)
<<<<<<< HEAD
add_subdirectory(error)

add_executable(PL0 PL0.c)
target_link_libraries(PL0 lex common tax error)
=======

add_executable(test test.c)
target_link_libraries(test lex common tax)
>>>>>>> 67062ac6f51b3d07f818def67dca73fa2b86ceca
