cmake_minimum_required(VERSION 3.10)
add_library (constexprArduino constexprMapArduino.cpp)
add_executable (constexprArduino_exc main.cpp)
target_link_libraries (constexprArduino_exc constexprArduino)
