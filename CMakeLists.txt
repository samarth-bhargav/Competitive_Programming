cmake_minimum_required(VERSION 3.21)
project(Competitive_Programming)

set(CMAKE_CXX_STANDARD 20)

add_definitions(-DLOCAL)

set_target_properties(PROPERTIES LINK_FLAGS -Wl,--stack,10000000)
add_executable(Competitive_Programming Codeforces/template.cpp)
add_executable(extra Codeforces/Problems/2055E.cpp)

add_executable(Informatics
        USACO/Feb24Plat2.cpp)
add_executable(MHC MHC/A.cpp)
add_executable(fun CodeSprint.cpp)
add_executable(Template Codeforces/Templates/FFT.cpp)
add_executable(InHouse In-House/InHouseD.cpp)

#For Stress Testing
add_executable(testing test.cpp)
add_executable(stress_tester stress/stress-tester.cpp)
add_executable(brute stress/brute.cpp)
add_executable(real stress/a.cpp)
add_executable(generator stress/generator.cpp)

add_custom_target(stress_test)
add_dependencies(stress_test
        brute
        real
        stress_tester
)

add_custom_target(generate)
add_dependencies(generate
        real
        generator
)