#pragma once
#include <string>

class FileViewer {
public:
    virtual void view(const std::string& fileName)=0;
    virtual ~FileViewer()=default;
};