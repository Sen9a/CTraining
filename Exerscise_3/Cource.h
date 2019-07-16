#pragma once
#include "IRecord.h"
#include <iostream>

class Cource : public IRecord {
private:
    int m_id;
    std::string m_name;
    int m_teacher_id;

public:
    Cource(std::istringstream &m_string);
    int getId() const override ;
    std::string getFormatted() const override ;
    int getTeacher() const;
};




