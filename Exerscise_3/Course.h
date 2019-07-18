#pragma once
#include "IRecord.h"
#include <string>

class Course : public IRecord {
private:
    int m_id;
    std::string m_name;
    int m_teacher_id;

public:
    Course(std::istringstream &m_string);
    int getId() const override ;
    std::string getFormatted() const override ;
};




