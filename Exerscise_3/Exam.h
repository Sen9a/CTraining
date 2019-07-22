#pragma once
#include "IRecord.h"
#include "ICommand.h"
#include <string>

class Exam : public IRecord{
private:
    int m_id;
    int m_cource_id;
    int m_student_id;
    int result;
public:
    Exam(std::istringstream &m_string);
    int getId() const override ;
    virtual std::string getPrettyPrinted() const override ;
    std::string getFormatted() const override ;
};




