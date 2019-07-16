#include "Student.h"
#include <sstream>

Student::Student(std::istringstream &m_string) {
    m_string>>this->m_id>>this->m_name;
    if(m_string.fail()){
        throw std::invalid_argument("Bad DB");
    }
}

std::string Student::getName() const {
    return this->m_name;
}

int Student::getId() const {
    return this->m_id;
}

std::string Student::getFormatted() const {
    std::string formated_string = std::to_string(this->m_id) + ",";
    formated_string += this->m_name;
    return formated_string;
}