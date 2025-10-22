
#include "HTMLViewer.h"
#include <cstdlib>
#include <windows.h>

void HTMLViewer::view(const std::string &fileName) {
    char fullPath[MAX_PATH];
    GetFullPathNameA(fileName.c_str(), MAX_PATH, fullPath, nullptr);
    std::string command = "start chrome \"file:///" + std::string(fullPath) + "\"";
    system(command.c_str());
}