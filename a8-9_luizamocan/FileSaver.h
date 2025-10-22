#pragma once
#include "Dog.h"
#include <vector>
#include <string>

class FileSaver {
public:
    virtual void save(const std::vector<Dog>&dogs,const std::string& fileName)=0;
    virtual ~FileSaver() {};
};