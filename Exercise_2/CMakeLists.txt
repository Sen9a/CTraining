cmake_minimum_required(VERSION 3.14)
project(CTraining)
set(CMAKE_CXX_STANDARD 17)

add_executable(CTraining main.cpp)
target_compile_options(CTraining PRIVATE -Wall -Wextra -Werror)