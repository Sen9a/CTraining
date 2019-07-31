#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>
#include "Course.h"
#include "Exam.h"
#include "Teacher.h"
#include "Student.h"
#include "Show.h"
#include "CommandParser.h"
#include <memory>
#include <map>


template<class T>
void fill_up_container(std::istringstream &iss, std::map<int, std::unique_ptr<IRecord>> &container){
    std::unique_ptr<IRecord> inst = std::make_unique<T>(iss);
    container.insert(std::pair<int, std::unique_ptr<IRecord>>(inst->getId(),std::move(inst)));
}

void make_containers(std::ifstream &file,
                     std::map<int, std::unique_ptr<IRecord>> &cource_vector,
                     std::map<int, std::unique_ptr<IRecord>> &exam_vector,
                     std::map<int, std::unique_ptr<IRecord>> &teacher_vector,
                     std::map<int, std::unique_ptr<IRecord>> &student_vector){
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


int write_data_to_file(const std::string &file, std::map<int, std::unique_ptr<IRecord>>  &container){
    std::ofstream open_file(file);
    if(!open_file){
        std::cout << "Can`t create file" << std::endl;
        return EXIT_FAILURE;
    }
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
    std::vector<std::string> arguments(argv + 1, argv + args);
    if(arguments.size()>=1) {
        std::map<int, std::unique_ptr<IRecord>> cource_vector;
        std::map<int, std::unique_ptr<IRecord>> exam_vector;
        std::map<int, std::unique_ptr<IRecord>> teacher_vector;
        std::map<int, std::unique_ptr<IRecord>> student_vector;
        std::ifstream file = read_from_file(arguments[0]);
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
        if (arguments.size() == 1) {
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
        } else if (arguments.size() > 1) {
            CommandParser command(student_vector,cource_vector,exam_vector,teacher_vector);
            try{
                command.parse(arguments)->execute();
            }catch (std::bad_alloc& ba){
                std::cerr << "bad_alloc caught: " << ba.what() << std::endl;
                return EXIT_FAILURE;
             }
            return EXIT_SUCCESS;
        }else{
            std::cout<<"Bad command"<<std::endl;
            return EXIT_FAILURE;
        }
    }
    std::cout << "Please give path to the file as 1 parameter"<<std::endl;
    return EXIT_FAILURE;
}
