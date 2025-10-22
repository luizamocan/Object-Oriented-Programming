//
// Created by Mocan Luiza on 5/7/2025.
//

#include "UI.h"
UI::UI() {

}
void UI::menu() {
    std::cout<<"Menu"<<std::endl;
    std::cout<<"1. Add Department"<<std::endl;
    std::cout<<"2. View Departments"<<std::endl;
    std::cout<<"3. View All Efficient Departments"<<std::endl;
    std::cout<<"4. Write to file"<<std::endl;
    std::cout<<"0. Exit"<<std::endl;
}
void UI::addDepartment() {
    std::string type,hospitalName;
    std::cout<<"Enter type of department (surgery/neonatalUnit)"<<std::endl;
    std::cin>>type;
    if (type=="surgery") {
        std::cout<<"Enter hospital name"<<std::endl;
        std::cin>>hospitalName;
        int numberOfDoctors,numberOfPatients;
        std::cout<<"Enter number of doctors"<<std::endl;
        std::cin>>numberOfDoctors;
        std::cout<<"Enter number of patients"<<std::endl;
        std::cin>>numberOfPatients;

        Surgery* s=new Surgery( hospitalName,numberOfDoctors,numberOfPatients);
        this->controller.addDepartment(s);
    }
    else if (type=="neonatalUnit") {
        std::cout<<"Enter hospital name"<<std::endl;
        std::cin>>hospitalName;
        int numberOfDoctors;
        double averageGrade;
        std::cout<<"Enter number of doctors"<<std::endl;
        std::cin>>numberOfDoctors;
        std::cout<<"Enter average grade"<<std::endl;
        std::cin>>averageGrade;

        NeonatalUnit* n=new NeonatalUnit(hospitalName,numberOfDoctors,averageGrade);
        this->controller.addDepartment(n);
    }
    else
        std::cout<<"Invalid Input"<<std::endl;
}
void UI::getDepartment() {
    for (int i=0;i<this->controller.getDepartments().size();i++)
        std::cout<<this->controller.getDepartments()[i]->toString()<<std::endl;
}
void UI::getEfficientDepartment() {
    std::vector<HospitalDepartment*> hospitalDepartments=this->controller.getEfficientDepartments();
    for (int i=0;i<hospitalDepartments.size();i++)
        std::cout<<hospitalDepartments[i]->toString()<<std::endl;
}
void UI::writeToFile() {
    std::string fileName;
    std::cout<<"Enter file name"<<std::endl;
    std::cin>>fileName;

    this->controller.sortDepartments();
    this->controller.writeToFile(fileName);
}
void UI::run() {
    Surgery* u=new Surgery("Urgenta",5,8);
    this->controller.addDepartment(u);
    Surgery* s=new Surgery("Recuperare",8,16);
    this->controller.addDepartment(s);
    NeonatalUnit* n=new NeonatalUnit("Stanca",10,8.6);
    this->controller.addDepartment(n);

    while (true) {
        this->menu();
        int option;
        std::cout<<"Enter your option: "<<std::endl;
        std::cin>>option;
        if (option==1)
            this->addDepartment();
        else if (option==2)
            this->getDepartment();
        else if (option==3)
            this->getEfficientDepartment();
        else if (option==4)
            this->writeToFile();
        else if (option==0)
            break;
        else
            std::cout<<"Invalid Input"<<std::endl;
    }
}






