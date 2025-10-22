
#include "CSVViewer.h"
#include <cstdlib>

void CSVViewer::view(const std::string &fileName) {
    std::string command = "start notepad \"" + fileName + "\"";
    system(command.c_str());
}
