#include <istream>
#include "Cource.h"
#include "Exam.h"
#include "Teacher.h"
#include "Student.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <algorithm>

template<class T>
void fill_up_container(std::istringstream &iss, std::map<int, T> &container){
    T inst(iss);
    container.insert(std::pair<int, T>(inst.getId(),inst));
}

void make_containers(std::ifstream &file,
                     std::map <int, Cource> &cource_map,
                     std::map <int, Exam> &exam_map,
                     std::map <int, Teacher> &teacher_map,
                     std::map <int, Student> &student_map){
    std::string row;
    char separator = ' ';
    while(std::getline(file, row)){
        std::string substr;
        std::replace(row.begin(),row.end(),',',separator);
        std::istringstream iss(row);
        std::getline(iss, substr, separator);
        if (substr == "C"){
            fill_up_container<Cource>(iss, cource_map);
        }
        if (substr == "E"){
            fill_up_container<Exam>(iss, exam_map);
        }
        if(substr == "T"){
            fill_up_container<Teacher>(iss,teacher_map);
        }
        if(substr == "S"){
            fill_up_container<Student>(iss,student_map);
        }
    }
}

template <class T>
int write_data_to_file(const std::string &file, std::map<int, T> &container){
    std::ofstream open_file(file);
    if(!open_file){
        std::cout << "Can`t create file" << std::endl;
        return EXIT_FAILURE;
    }
    for(auto &iter : container){
        open_file<<iter.second.getFormatted()<<std::endl;
    }
    return EXIT_SUCCESS;
}

std::ifstream read_from_file(const std::string &file) {
    std::ifstream open_file(file);
    return open_file;
}




int main(int args, char **argv){
    if(args==2) {
        std::map<int, Cource> cource_map;
        std::map<int, Exam> exam_map;
        std::map<int, Teacher> teacher_map;
        std::map<int, Student> student_map;
        std::ifstream file = read_from_file(argv[1]);
        if (!file) {
            std::cout << "File do not exists" << std::endl;
            return EXIT_FAILURE;
        }
        try {
            make_containers(file, cource_map, exam_map, teacher_map, student_map);
        } catch (std::invalid_argument &ia) {
            std::cerr << ia.what() << std::endl;
            return EXIT_FAILURE;
        }
        if (write_data_to_file("../Exam.txt", exam_map)) {
            return EXIT_FAILURE;
        }
        if (write_data_to_file("../Cource.txt", cource_map)) {
            return EXIT_FAILURE;
        }
        if (write_data_to_file("../Student.txt", student_map)) {
            return EXIT_FAILURE;
        }
        if (write_data_to_file("../Teacher.txt", teacher_map)) {
            return EXIT_FAILURE;
        }
        return EXIT_SUCCESS;
    }
    std::cout << "Please give path to the file as 1 parameter"<<std::endl;
    return EXIT_FAILURE;
}
