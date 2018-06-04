cmake_minimum_required(VERSION 3.8)
project(A_Start)
find_package(GTest REQUIRED)
INCLUDE_DIRECTORIES(include config)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        src/main.cpp include/Map.hpp include/Vec2.hpp
        include/Node.hpp src/GTest/Vec2iTest.cpp
        src/GTest/NodeTest.cpp config/config.hpp
        src/Map.cpp src/GTest/MapTest.cpp
        include/Generator.hpp src/Generator.cpp
        include/PathAlgorithm.hpp src/PathAlgorithm.cpp)
add_executable(A_Start ${SOURCE_FILES})
target_link_libraries(A_Start GTest::GTest)