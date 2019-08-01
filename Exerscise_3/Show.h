#pragma once

#include "ICommand.h"
#include "IRecord.h"
#include <string>
#include "map"
#include "memory"

using Table = std::map<int, std::unique_ptr<IRecord>>;
using TableContainer = std::map<std::string, std::reference_wrapper<const Table>>;


class Show: public ICommand {
private:
    TableContainer show_container;
public:
    Show(TableContainer tables);
    void execute() override;
};