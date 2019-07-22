#include "Student.h"
#include <sstream>
#include <iostream>

Student::Student(std::istringstream &m_string) {
    m_string>>this->m_id>>this->m_name;
    if(m_string.fail()){
        throw std::invalid_argument("Bad DB");
    }
}

std::string Student::getName() const {
    return m_name;
}

int Student::getId() const {
    return m_id;
}

std::string Student::getFormatted() const {
    std::string formated_string = std::to_string(this->m_id) + ",";
    formated_string += this->m_name;
    return formated_string;
}

std::string Student::getPrettyPrinted() const {
    std::string output = std::string("ID: ")+std::to_string(this->m_id)+", Name: "+this->m_name;
    return output;
}
