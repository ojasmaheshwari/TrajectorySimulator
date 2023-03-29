cmake_minimum_required(VERSION 3.25.2)

set(CMAKE_CXX_STANDARD 17)

project(trajectory VERSION 0.0.1)

set (SOURCES src/main.cpp)

set(CMAKE_BUILD_TYPE Debug)

# find_package(ImGui-SFML CONFIG REQUIRED)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-system) 
