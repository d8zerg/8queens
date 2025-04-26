cmake_minimum_required(VERSION 3.20)

project(CMakeSFMLProject LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

find_package(SFML COMPONENTS graphics window system REQUIRED)

add_executable(8queens 
    src/main.cpp
    src/chessvisualizer.h
    src/config.h
    src/queenssolver.h 
    src/solutions.h)


target_link_libraries(8queens pthread sfml-graphics sfml-window sfml-system)