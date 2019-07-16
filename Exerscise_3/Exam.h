#pragma once
#include "IRecord.h"
#include "Student.h"
#include "Cource.h"
#include <map>

class Exam : public IRecord{
private:
    int m_id;
    int m_cource_id;
    int m_student_id;
    int result;
public:
    Exam(std::istringstream &m_string);
    int getId() const override ;
    std::string getFormatted() const override ;
    std::string getFormatted(std::map<int, Student> &student, std::map<int, Cource> &cource);
};




