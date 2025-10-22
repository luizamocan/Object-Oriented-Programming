
#include "HTMLSaver.h"
void HTMLSaver::save(const std::vector<Dog>&dogs,const std::string& fileName) {
    std::ofstream file(fileName);
    if (!file.is_open()) {
        std::cerr << "File " << fileName << " could not be opened." << std::endl;
        return;
    }
    file << "<!DOCTYPE html>\n<html>\n<head>\n<title>Dog List</title>\n</head>\n<body>\n<table border=\"1\">\n";
    file << "    <tr>\n        <td>Name</td>\n        <td>Breed</td>\n        <td>Age</td>\n        <td>Photo Link</td>\n    </tr>\n";

    for (const auto& dog : dogs) {
        file << "    <tr>\n";
        file << "        <td>" << dog.getName() << "</td>\n";
        file << "        <td>" << dog.getBreed() << "</td>\n";
        file << "        <td>" << dog.getAge() << "</td>\n";
        file << "        <td><a href=\"" << dog.getLinkToPhoto() << "\">Link</a></td>\n";
        file << "    </tr>\n";
    }
    file << "</table>\n</body>\n</html>";
    file.close();
}
