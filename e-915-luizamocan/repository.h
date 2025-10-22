
#ifndef REPOSITORY_H
#define REPOSITORY_H
#include <vector>

#include "domain.h"

class Repository {
private:
    std::vector<Event> events;
    std::vector<Person> persons;
    std::string eventFile;
    std::string personFile;
    public:
    Repository(std::string eventFile, std::string personFile);
    void loadEvents();
    void saveEvents();
    void loadPersons();
    void savePersons();
    std::vector<Event> getEvents();
    std::vector<Person> getPersons();
    void addEvent(const Event& event);



};
#endif //REPOSITORY_H
