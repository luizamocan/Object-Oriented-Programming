
#include "service.h"
#include <algorithm>
void Service::addEvent(std::string organiser, std::string name, std::string description, std::string latitude, std::string longitude, std::string status) {
    repository.addEvent(Event(organiser, name, description, latitude, longitude, status));
    notifyObservers();
}
std::vector<Event> Service::getSortedByDate() {
    auto events = repository.getEvents();
    std::sort(events.begin(), events.end(),[](const Event &e1, const Event &e2) {
        return e1.getDate() < e2.getDate();
    });
    return events;
}
void Service::addObserver(Observer *observer) {
    observers.push_back(observer);
}
void Service::removeObserver(Observer *observer) {
    observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());

}
void Service::notifyObservers() {
    for (auto observer : observers)
        observer->update();
}






