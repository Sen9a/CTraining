#include "Exam.h"
#include <sstream>
#include <fstream>

Exam::Exam(std::istringstream &m_string) {
    m_string>>this->m_id>>this->m_cource_id>>this->m_student_id>>this->result;
    if(m_string.fail()){
        throw std::invalid_argument("Bad DB");
    }
}

int Exam::getId() const {
    return this->m_id;
}

std::string Exam::getFormatted() const {
    std::string open_file;
    open_file += std::to_string(this->m_id) + "," + std::to_string(this->m_cource_id) + ",";
    open_file += std::to_string(this->m_student_id) + "," + std::to_string(this->result);
    return open_file;
}

std::string Exam::getFormatted(std::map<int, Student> &student, std::map<int, Cource> &cource) {
    std::string result_string = "Cource :" + cource.find(this->m_cource_id)->second.getFormatted() + ",";
    result_string += "Student :" + student.find(this->m_student_id)->second.getName() + ",";
    result_string += "Result :" + std::to_string(this->result) + ",";
    return result_string;
}
