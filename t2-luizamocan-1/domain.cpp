//
// Created by Mocan Luiza on 5/7/2025.
//

#include "domain.h"
std::string HospitalDepartment::getHospitalName() {
    return hospitalName;
}
int HospitalDepartment::getNumberOfDoctors() {
    return numberOfDoctors;
}

Surgery::Surgery(std::string hospitalName, int numberOfDoctors, int numberOfPatients) {
    this->hospitalName = hospitalName;
    this->numberOfDoctors = numberOfDoctors;
    this->numberOfPatients = numberOfPatients;
}
bool Surgery::isEfficient() {
    return this->numberOfPatients/this->numberOfDoctors >=2;
}

std::string Surgery::toString() {
    return "Surgery|| Hospital name: " + this->hospitalName +" | nr of doctors: "+std::to_string(numberOfDoctors)+" | nr of patients: "+std::to_string(numberOfPatients);

}
NeonatalUnit::NeonatalUnit(std::string hospitalName, int numberOfDoctors, double averageGrade) {
    this->hospitalName = hospitalName;
    this->numberOfDoctors = numberOfDoctors;
    this->averageGrade = averageGrade;
}

bool NeonatalUnit::isEfficient() {
    return this->averageGrade >8.5;
}
std::string NeonatalUnit::toString() {
    return "Neonatal Unit|| Hospital name: "+this->hospitalName+"   nr of doctors: "+std::to_string(numberOfDoctors)+" | average grade: "+std::to_string(averageGrade);

}







