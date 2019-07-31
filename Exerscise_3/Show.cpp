#include "Show.h"
#include <iostream>


Show::Show(TableContainer tables):
show_container(tables){}

void Show::execute() {
    for (const auto &i:this->show_container){
        std::cout<<i.first<<std::endl;
        for (const auto &j: i.second.get()){
            std::cout<<j.second->getPrettyPrinted()<<std::endl;
        }
        std::cout << std::endl;
    }
}