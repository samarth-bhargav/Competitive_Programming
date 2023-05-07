cmake_minimum_required(VERSION 3.21)
project(Competitive_Programming)

set(CMAKE_CXX_STANDARD 14)

set_target_properties(PROPERTIES LINK_FLAGS -Wl,--stack,10000000)
add_executable(Competitive_Programming Codeforces/Problems/E/1750E.cpp)

#For Stress Testing
add_executable(testing test.cpp)
add_executable(stress_tester stress/stress-tester.cpp)
add_executable(brute stress/brute.cpp)
add_executable(real stress/a.cpp)
