#pragma once
#include "FileViewer.h"
#include <string>

class CSVViewer : public FileViewer {
    public:
    void view(const std::string& fileName) override;
    ~CSVViewer() override=default;
};