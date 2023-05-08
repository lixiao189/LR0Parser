cmake_minimum_required(VERSION 3.0.0)
project(LR0 VERSION 0.1.0)

# C++ 17 support
set(CMAKE_CXX_STANDARD 17)

include(CTest)
enable_testing()

add_executable(
    LR0 

    # Source code list
    src/main.cpp 
    src/data.cpp 
    src/item.cpp 
    src/production.cpp
    src/LRParser.cpp
    src/Automaton.cpp
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
