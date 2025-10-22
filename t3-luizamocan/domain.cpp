//
// Created by Mocan Luiza on 5/26/2025.
//

#include "domain.h"
Interval::Interval(int start_hour, int end_hour, int temperature, int probability, std::string description) {
    this->start_hour = start_hour;
    this->end_hour = end_hour;
    this->temperature = temperature;
    this->probability = probability;
    this->description = description;
}
std::string Interval::toString() const{
    return std::to_string(this->start_hour)+";"+std::to_string(this->end_hour)+";"+std::to_string(this->temperature)+";"+std::to_string(this->probability)+";"+this->description;
}
