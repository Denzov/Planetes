cmake_minimum_required(VERSION 3.16)
project(Planetes)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
find_package(raylib 5.5 REQUIRED)

file(GLOB SOURCES src/*.cpp include/*.h)

add_executable(Planetes ${SOURCES})
# Setting parameters for raylib
target_link_libraries(Planetes PRIVATE raylib)