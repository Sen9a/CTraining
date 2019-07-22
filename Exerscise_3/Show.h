#pragma once

#include "ICommand.h"
#include "IRecord.h"
#include <string>
#include <vector>
#include <memory>

class Show: public ICommand {
public:
    std::vector<std::pair<std::string, std::vector<std::pair<int, std::unique_ptr<IRecord>>>>>  &show_container;
public:
    Show(std::vector<std::pair<std::string, std::vector<std::pair<int, std::unique_ptr<IRecord>>>>>  &container);
    void execute() override ;
};