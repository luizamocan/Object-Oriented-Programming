#pragma once
#include "FileViewer.h"
#include <string>

class HTMLViewer : public FileViewer {
public:
    void view(const std::string &fileName) override;
    ~HTMLViewer() override=default;
};