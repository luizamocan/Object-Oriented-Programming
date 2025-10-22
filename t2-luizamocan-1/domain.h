//
// Created by Mocan Luiza on 5/7/2025.
//

#ifndef DOMAIN_H
#define DOMAIN_H
#include <iostream>
class  HospitalDepartment {
protected:
    std::string hospitalName;
    int numberOfDoctors;
public:
    virtual bool isEfficient()=0;
    virtual std::string toString()=0;
    std::string getHospitalName();
    int getNumberOfDoctors();
    virtual ~HospitalDepartment()=default;
};

class Surgery:public HospitalDepartment {
private:
    int numberOfPatients;
public:
    Surgery(std::string hospitalName, int numberOfDoctors,int numberOfPatients);
    bool isEfficient() override;
    std::string toString() override;
    ~Surgery()override=default;
};

class NeonatalUnit:public HospitalDepartment {
private:
    double averageGrade;
public:
    NeonatalUnit(std::string hospitalName,int numberOfDoctors,double averageGrade);
    bool isEfficient() override;
    std::string toString() override;
    ~NeonatalUnit()override=default;
};
#endif //DOMAIN_H
