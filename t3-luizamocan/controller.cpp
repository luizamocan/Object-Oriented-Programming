//
// Created by Mocan Luiza on 5/26/2025.
//

#include "controller.h"
#include <sstream>
#include <fstream>
#include <algorithm>
Controller::Controller() {

}
std::vector<Interval> Controller::getIntervals() {
    std::vector<Interval> sorted = this->intervals;
    std::sort(sorted.begin(), sorted.end(), [](const Interval& a, const Interval& b) {
        return a.getStartHour() < b.getStartHour();
    });
    return sorted;
}

std::vector<std::string> parce(std::string line,char del) {
    std::vector<std::string> result;
    std::stringstream ss(line);
    std::string token;
    while (std::getline(ss, token, del)) {
        result.push_back(token);
    }
    return result;
}

void Controller::readFromFile() {
    std::ifstream file("input.txt");
    std::string line;
    while (std::getline(file,line)) {
        std::vector<std::string> items = parce(line,';');
        if (items.size() == 5)
            this->intervals.push_back(Interval(std::stoi(items[0]),std::stoi(items[1]),std::stoi(items[2]),std::stoi(items[3]),items[4]));
    }
}


