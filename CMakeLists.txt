cmake_minimum_required(VERSION 3.10)
project(SBUS_Reader)

set(CMAKE_CXX_STANDARD 17)

add_executable(SBUS_Reader main.cpp sbus_serial.cpp)

target_link_libraries(SBUS_Reader -pthread)