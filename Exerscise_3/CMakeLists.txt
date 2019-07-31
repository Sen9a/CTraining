cmake_minimum_required(VERSION 3.14)
project(Exerscise_3)

set(CMAKE_CXX_STANDARD 17)

add_executable(Exerscise_3
        main.cpp Course.cpp Course.h IRecord.h IPerson.h Student.h Student.cpp
        Teacher.cpp Teacher.h Exam.cpp Exam.h ICommand.h Show.h Show.cpp CommandParser.cpp CommandParser.h)
target_compile_options(Exerscise_3 PRIVATE -Wall -Wextra -Werror)