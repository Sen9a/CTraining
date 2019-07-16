#pragma once

#include "IPersone.h"
#include "IRecord.h"


class Student : public IPerson,IRecord{
private:
    int m_id;
    std::string m_name;

public:
    Student(std::istringstream &m_string);
    std::string getName() const override ;
    std::string getFormatted() const override ;
    int getId() const override ;
};




