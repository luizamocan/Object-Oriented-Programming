//
// Created by Mocan Luiza on 5/7/2025.
//

#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <vector>

#include "domain.h"
class Controller {
private:
    std::vector<HospitalDepartment*> hospitalDepartments;
public:
    Controller();
    ~Controller();
    void addDepartment(HospitalDepartment *department);
    std::vector<HospitalDepartment *> getDepartments();
    std::vector<HospitalDepartment *> getEfficientDepartments();
    void writeToFile(std::string fileName);
    void sortDepartments();
};
#endif //CONTROLLER_H
