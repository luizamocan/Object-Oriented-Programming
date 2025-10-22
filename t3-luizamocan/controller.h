//
// Created by Mocan Luiza on 5/26/2025.
//

#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <vector>

#include "domain.h"

class Controller {
    private:
    std::vector<Interval> intervals;
    public:
    Controller();
    std::vector<Interval> getIntervals();
    void readFromFile();
};
#endif //CONTROLLER_H
