#pragma once
#include "FileSaver.h"
#include <fstream>
#include <iostream>

class HTMLSaver : public FileSaver {
public:
    void save(const std::vector<Dog>&dogs,const std::string& fileName) override;
};