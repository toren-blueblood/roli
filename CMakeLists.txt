cmake_minimum_required(VERSION 3.15)
project(Roli)

set(CMAKE_CXX_STANDARD 17)

find_package(SDL2 REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})
add_executable(${PROJECT_NAME} server.cpp)
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})
