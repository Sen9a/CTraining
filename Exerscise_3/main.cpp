#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>
#include "Course.h"
#include "Exam.h"
#include "Teacher.h"
#include "Student.h"
#include <memory>



template<class T>
void fill_up_container(std::istringstream &iss, std::vector<std::pair<int, std::shared_ptr<IRecord>>> &container){
    std::shared_ptr<IRecord> inst = std::make_shared<T>(iss);
    container.emplace_back(inst->getId(),inst);
}

void make_containers(std::ifstream &file,
                     std::vector<std::pair<int, std::shared_ptr<IRecord>>> &cource_vector,
                     std::vector<std::pair<int, std::shared_ptr<IRecord>>> &exam_vector,
                     std::vector<std::pair<int, std::shared_ptr<IRecord>>> &teacher_vector,
                     std::vector<std::pair<int, std::shared_ptr<IRecord>>> &student_vector){
    std::string row;
    char separator = ' ';
    while(std::getline(file, row)){
        std::string substr;
        std::replace(row.begin(),row.end(),',',separator);
        std::istringstream iss(row);
        std::getline(iss, substr, separator);
        if (substr == "C"){
            fill_up_container<Course>(iss, cource_vector);
        }
        if (substr == "E"){
            fill_up_container<Exam>(iss, exam_vector);
        }
        if(substr == "T"){
            fill_up_container<Teacher>(iss,teacher_vector);
        }
        if(substr == "S"){
            fill_up_container<Student>(iss,student_vector);
        }
    }
}


int write_data_to_file(const std::string &file, std::vector<std::pair<int, std::shared_ptr<IRecord>>>  &container){
    std::ofstream open_file(file);
    if(!open_file){
        std::cout << "Can`t create file" << std::endl;
        return EXIT_FAILURE;
    }
    sort(container.begin(), container.end());
    try {
        for(auto &iter : container){
            open_file<<iter.second->getFormatted()<<std::endl;
        }
    }catch (std::bad_alloc& ba){
        std::cerr << "bad_alloc caught: " << ba.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

std::ifstream read_from_file(const std::string &file) {
    std::ifstream open_file(file);
    return open_file;
}


int main(int args, char **argv){
    if(args==2) {
        std::vector<std::pair<int, std::shared_ptr<IRecord>>> cource_vector;
        std::vector<std::pair<int, std::shared_ptr<IRecord>>> exam_vector;
        std::vector<std::pair<int, std::shared_ptr<IRecord>>> teacher_vector;
        std::vector<std::pair<int, std::shared_ptr<IRecord>>> student_vector;
        std::ifstream file = read_from_file(argv[1]);
        if (!file) {
            std::cout << "File do not exists" << std::endl;
            return EXIT_FAILURE;
        }
        try {
            make_containers(file, cource_vector, exam_vector, teacher_vector, student_vector);
        } catch (std::invalid_argument &ia) {
            std::cerr << ia.what() << std::endl;
            return EXIT_FAILURE;
        }
        if (write_data_to_file("../Exam.txt", exam_vector)) {
            return EXIT_FAILURE;
        }
        if (write_data_to_file("../Cource.txt", cource_vector)) {
            return EXIT_FAILURE;
        }
        if (write_data_to_file("../Student.txt", student_vector)) {
            return EXIT_FAILURE;
        }
        if (write_data_to_file("../Teacher.txt", teacher_vector)) {
            return EXIT_FAILURE;
        }
        return EXIT_SUCCESS;
    }
    std::cout << "Please give path to the file as 1 parameter"<<std::endl;
    return EXIT_FAILURE;
}
