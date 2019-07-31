#pragma once


#include "ICommand.h"
#include "Show.h"
#include <vector>

class CommandParser
{
public:
    TableContainer container;
    Table &student, &course, &exam, &teacher;
public:
    CommandParser(Table &student, Table &course, Table &exam, Table &teacher);
    std::unique_ptr<ICommand> parse(std::vector<std::string> arguments);
    void show(std::vector<std::string> &arguments);
};




