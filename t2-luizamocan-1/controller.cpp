//
// Created by Mocan Luiza on 5/7/2025.
//

#include "controller.h"
#include <iostream>
#include <fstream>
Controller::Controller() {

}
Controller::~Controller() {
    for (HospitalDepartment* h:hospitalDepartments)
        delete h;
}
std::vector<HospitalDepartment *> Controller::getDepartments() {
    return this->hospitalDepartments;
}
void Controller::addDepartment(HospitalDepartment *department) {
    hospitalDepartments.push_back(department);
}
std::vector<HospitalDepartment *> Controller::getEfficientDepartments() {
    std::vector<HospitalDepartment *> result;
    for (HospitalDepartment* h:this->hospitalDepartments) {
        if (h->isEfficient())
            result.push_back(h);
    }
    return result;
}
void Controller::writeToFile(std::string fileName) {
    std::ofstream f(fileName);
    for (int i=0;i<hospitalDepartments.size();i++){
        f<<hospitalDepartments[i]->toString()<<std::endl;
        if (hospitalDepartments[i]->isEfficient())
            f<<"efficient"<<std::endl;
        else
            f<<"inefficient"<<std::endl;
    }
}

void Controller::sortDepartments() {
    for (int i=0;i<hospitalDepartments.size();i++)
        for (int j=i;j<hospitalDepartments.size();j++)
            if (hospitalDepartments[i]->getHospitalName()>hospitalDepartments[j]->getHospitalName())
                std::swap(hospitalDepartments[i], hospitalDepartments[j]);
}




