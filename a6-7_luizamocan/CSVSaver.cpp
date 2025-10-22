
#include "CSVSaver.h"
void CSVSaver::save(const std::vector<Dog> &dogs, const std::string &fileName) {
    std::ofstream file(fileName);
    if (!file.is_open()) {
        std::cerr << "File could not be opened." << std::endl;
        return;
    }
    file<<"Name,Breed,Age,Link"<<std::endl;
    for (const auto& dog : dogs) {
        file<<dog.getName()<<","<<dog.getBreed()<<","<<dog.getAge()<<","<<dog.getLinkToPhoto()<<std::endl;
    }
    file.close();
}
