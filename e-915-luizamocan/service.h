

#ifndef SERVICE_H
#define SERVICE_H
#include "repository.h"
#include <algorithm>

class Observer {
    public:
    virtual void update() = 0;
    virtual ~Observer()=default;
};

class Service {
private:
    Repository& repository;
    std::vector<Observer*> observers;
    public:
    Service(Repository& repo) : repository(repo) {}

    void addEvent(std::string organiser,std::string name,std::string description,std::string latitude,std::string longitude,std::string status);
    std::vector<Event> getSortedByDate();


    void saveToFile(){repository.saveEvents();}
    void addObserver(Observer* observer);
    void removeObserver(Observer* observer);
    void notifyObservers();





};
#endif //SERVICE_H
