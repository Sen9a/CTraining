#include "Teacher.h"
#include <sstream>

Teacher::Teacher(std::istringstream &m_string) {
    m_string>>this->m_id>>this->m_name;
    if(m_string.fail()){
        throw std::invalid_argument("Bad DB");
    }
}

int Teacher::getId() const {
    return m_id;
}

std::string Teacher::getName() const {
    return m_name;
}

std::string Teacher::getFormatted() const {
    std::string formated_string = std::to_string(this->m_id) + ",";
    formated_string += this->m_name;
    return formated_string;
}

std::string Teacher::getPrettyPrinted() const {
    std::string output = std::string("ID: ") + std::to_string(this->m_id) + ", Name: " + this->m_name;
    return output;
}