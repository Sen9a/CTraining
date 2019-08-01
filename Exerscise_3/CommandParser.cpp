#include "CommandParser.h"
#include <iostream>

CommandParser::CommandParser(Table &student, Table &course, Table &exam, Table &teacher):
student(student), course(course), exam(exam), teacher(teacher){}


void CommandParser::show(std::vector<std::string> &arguments) {
    if (arguments.size() == 2 || arguments[2] == std::string("STUDENTS")) {
        this->container.insert_or_assign("Table Students:", std::cref(this->student));
    }
    if (arguments.size() == 2 || arguments[2] == std::string("TEACHERS")) {
        this->container.insert_or_assign("Table Teachers:", std::cref(this->teacher));
    }
    if (arguments.size() == 2 || arguments[2] == std::string("COURSES")) {
        this->container.insert_or_assign("Table Courses:", std::cref(this->course));
    }
    if (arguments.size() == 2 || arguments[2] == std::string("EXAMS")) {
        this->container.insert_or_assign("Table Exams:", std::cref(this->exam));
    }
    if (this->container.empty()) {
        std::cout << "Can`t show table with " << arguments[2] << " as parameter" << std::endl;
    }
}

std::unique_ptr<ICommand> CommandParser::parse(std::vector<std::string> arguments) {
    if (arguments[1]==std::string("SHOW"))
    {
        this->show(arguments);
    }
    std::unique_ptr<ICommand> show_ptr = std::make_unique<Show>(this->container);
    return show_ptr;
}