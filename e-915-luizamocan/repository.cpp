
#include "repository.h"
#include <fstream>
#include <sstream>
Repository::Repository(std::string eventFile, std::string personFile):eventFile(eventFile),personFile(personFile) {
        loadEvents();
        loadPersons();
}
std::vector<Event> Repository::getEvents() {
        return  events;
}
std::vector<Person> Repository::getPersons() {
        return  persons;
}
void Repository::loadEvents() {
        events.clear();
        std::ifstream file(eventFile);
        std::string line;
        while (std::getline(file, line)) {
                std::string organiser, name, description, latitude, longitude, date;
                std::stringstream ss(line);
                std::getline(ss, organiser, ',');
                std::getline(ss, name, ',');
                std::getline(ss, description, ',');
                std::getline(ss, latitude, ',');
                std::getline(ss, longitude, ',');
                std::getline(ss, date, ',');

                events.emplace_back(organiser, name, description, latitude, longitude, date);
        }
}

void Repository::saveEvents() {
        std::ofstream file(eventFile);
        for (const auto& event : events) {
                file << event.toString() << "\n";
        }
}

void Repository::loadPersons() {
        std::ifstream file(personFile);
        std::string line;
        while (std::getline(file, line)) {
                std::string name,latitude,longitude,organiser_status;
                std::stringstream ss(line);
                std::getline(ss, name, ',');
                std::getline(ss, latitude, ',');
                std::getline(ss, longitude, ',');
                std::getline(ss, organiser_status, ',');
                persons.emplace_back(name, latitude, longitude, organiser_status);
        }

}
void Repository::savePersons() {
        std::ofstream file(personFile);
        for (const auto& person : persons) {
                file<<person.toString()<<"\n";
        }
}

void Repository::addEvent(const Event &event) {
        events.push_back(event);
}



