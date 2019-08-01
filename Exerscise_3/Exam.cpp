#include "Exam.h"
#include <sstream>

Exam::Exam(std::istringstream &m_string) {
    m_string>>this->m_id>>this->m_cource_id>>this->m_student_id>>this->result;
    if(m_string.fail()){
        throw std::invalid_argument("Bad DB");
    }
}

int Exam::getId() const {
    return m_id;
}

std::string Exam::getFormatted() const {
    std::string open_file;
    open_file += std::to_string(this->m_id) + "," + std::to_string(this->m_cource_id) + ",";
    open_file += std::to_string(this->m_student_id) + "," + std::to_string(this->result);
    return open_file;
}

std::string Exam::getPrettyPrinted() const {
    std::string output = std::string("ID: ")+std::to_string(this->m_id);
    output += ", CourseID: "+std::to_string(this->m_cource_id) + ", StudentID: " + std::to_string(this->m_student_id);
    output += ", Result: "+std::to_string(this->result);
    return output;
}