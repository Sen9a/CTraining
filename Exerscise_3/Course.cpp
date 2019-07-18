#include "Course.h"
#include <sstream>

int Course::getId() const {
    return m_id;
}

std::string Course::getFormatted() const {
    std::string formated_string = std::to_string(this->m_id) + ",";
    formated_string += this->m_name+ ",";
    formated_string += std::to_string(this->m_teacher_id);
    return formated_string;
}

Course::Course(std::istringstream &m_string) {
    m_string>>this->m_id>>this->m_name>>this->m_teacher_id;
    if(m_string.fail()){
        throw std::invalid_argument("Bad DB");
    }
}

