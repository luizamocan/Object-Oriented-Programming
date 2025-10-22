
#include <iostream>
#include <QApplication>

#include "gui.h"
#include "repository.h"
#include "service.h"

int main(int argc,char* argv[]) {

    QApplication app(argc,argv);
    Repository repository("events.txt","person.txt");
    Service service(repository);

    for (const auto& participant:repository.getPersons()) {
        auto* personWindow=new PersonWindow(service,participant);
        personWindow->show();

    }
    return app.exec();
}
