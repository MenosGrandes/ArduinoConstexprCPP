cmake_minimum_required(VERSION 3.10)
add_library (constexprArduino constexprMapArduino.cpp)
add_executable (demo main.cpp)
target_link_libraries (demo constexprArduino)
