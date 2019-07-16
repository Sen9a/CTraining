#pragma once

#include <iostream>

class IRecord {
    public:
        virtual int getId() const  = 0;
        virtual std::string getFormatted() const = 0;
        virtual ~IRecord() = default;
};




