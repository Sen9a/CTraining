cmake_minimum_required(VERSION 3.14)
project(Exerscise_3)

set(CMAKE_CXX_STANDARD 17)

add_executable(Exerscise_3
        main.cpp Cource.cpp Cource.h IRecord.h IPersone.h Student.h Student.cpp
        Teacher.cpp Teacher.h Exam.cpp Exam.h)
target_compile_options(Exerscise_3 PRIVATE -Wall -Wextra -Werror)