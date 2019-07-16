#include "Cource.h"
#include <sstream>


int Cource::getId() const {
    return this->m_id;
}

std::string Cource::getFormatted() const {
    std::string formated_string = std::to_string(this->m_id) + ",";
    formated_string += this->m_name+ ",";
    formated_string += std::to_string(this->m_teacher_id);
    return formated_string;
}

Cource::Cource(std::istringstream &m_string) {
    m_string>>this->m_id>>this->m_name>>this->m_teacher_id;
    if(m_string.fail()){
        throw std::invalid_argument("Bad DB");
    }
}

int Cource::getTeacher() const {
    return this->m_teacher_id;
}
