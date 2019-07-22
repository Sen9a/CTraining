#include "Show.h"
#include <iostream>

Show::Show(std::vector<std::pair<std::string, std::vector<std::pair<int, std::unique_ptr<IRecord>>>>>  &container):
show_container(container){}

void Show::execute() {
    for (auto &i:this->show_container){
        std::cout<<i.first<<std::endl;
        for (auto &j: i.second){
            std::cout<<j.second->getPrettyPrinted()<<std::endl;
        }
        std::cout << std::endl;
    }
}