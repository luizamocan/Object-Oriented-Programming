//
// Created by Mocan Luiza on 5/26/2025.
//

#ifndef DOMAIN_H
#define DOMAIN_H
#include <iostream>
class Interval {
private:
    int start_hour,end_hour;
    int temperature,probability;
    std::string description;

    public:
    Interval(int start_hour, int end_hour, int temperature, int propability, std::string description);
    int getStartHour()const{return start_hour;}
    int getEndHour()const{return end_hour;}
    int getTemperature()const{return temperature;}
    int getProbability()const{return probability;}
    std::string getDescription()const{return description;}
    std::string toString() const;
};
#endif //DOMAIN_H
