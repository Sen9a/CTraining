#pragma once

#include "IPerson.h"
#include "IRecord.h"
#include <string>

class Teacher : public IPerson, public IRecord{
private:
    int m_id;
    std::string m_name;
    std::string m_t_name;
public:
    Teacher(std::istringstream &m_string) ;
    std::string getName() const override ;
    std::string getFormatted() const override ;
    std::string getPrettyPrinted() const override ;
    int getId() const override ;
};




