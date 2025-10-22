//
// Created by Mocan Luiza on 5/7/2025.
//

#ifndef UI_H
#define UI_H
#include "controller.h"

class UI {
private:
    Controller controller;
public:
    void addDepartment();
    void getDepartment();
    void getEfficientDepartment();
    void writeToFile();

    void run();
    void menu();
    UI();
    ~UI()=default;
};
#endif //UI_H
