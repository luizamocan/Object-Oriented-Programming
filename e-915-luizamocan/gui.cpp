
#include "gui.h"
#include <QString>
#include <QVBoxLayout>
#include <QCheckBox>
#include <cmath>
#include <QFormLayout>
#include <QLineEdit>
#include <QMessageBox>
PersonWindow::PersonWindow(Service &service, Person person, QWidget *parent)
    : QMainWindow(parent), service(service), person(person) {
    service.addObserver(this);
    this->setWindowTitle(QString::fromStdString(person.getName()));

    QWidget* centralWidget = new QWidget{this};
    QVBoxLayout* layout = new QVBoxLayout(centralWidget);


    filterCheckBox = new QCheckBox("Show  events ");
    layout->addWidget(filterCheckBox);
    layout->addWidget(new QLabel("Latitude: "+QString::fromStdString(person.getLatitude())));
    layout->addWidget(new QLabel("Longitude"+QString::fromStdString(person.getLongitude())));

    eventsTable = new QTableWidget(this);
    eventsTable->setColumnCount(5);
    eventsTable->setHorizontalHeaderLabels({"Organiser", "Name", "Latitude", "Longitude", "Date"});
    layout->addWidget(eventsTable);
    if (person.getOrganiserStatus()=="true") {
        QFormLayout* formLayout = new QFormLayout();
        nameEdit=new QLineEdit{};
        descriptionEdit=new QLineEdit{};
        latEdit=new QLineEdit{};
        longEdit=new QLineEdit{};
        descriptionEdit=new QLineEdit{};
        dateEdit=new QLineEdit{};
        addButton=new QPushButton{"Add"};
        updateButton=new QPushButton{"Update"};

        formLayout->addRow("Name:", nameEdit);
        formLayout->addRow("Description:", descriptionEdit);
        formLayout->addRow("Latitude:", latEdit);
        formLayout->addRow("Longitude:", longEdit);
        formLayout->addRow("Date:", dateEdit);
        formLayout->addWidget(addButton);

        layout->addLayout(formLayout);

        QObject::connect(addButton, &QPushButton::clicked, this, &PersonWindow::addEvent);
        QObject::connect(updateButton,&QPushButton::clicked,this,&PersonWindow::update);
    }else {
        descEditBox = new QTextEdit();
        descEditBox->setReadOnly(true);
        layout->addWidget(new QLabel("Description:"));
        layout->addWidget(descEditBox);

        goingButton = new QPushButton("Going");
        layout->addWidget(goingButton);

    }

    this->setCentralWidget(centralWidget);
    QObject::connect(filterCheckBox, &QCheckBox::stateChanged, this, &PersonWindow::loadEvents);
    loadEvents();
}

void PersonWindow::loadEvents() {
    auto events = service.getSortedByDate();
    eventsTable->setRowCount(0);

    bool filter = filterCheckBox->isChecked();
    double personLat = std::stod(person.getLatitude());
    double personLong = std::stod(person.getLongitude());

    for (const auto& event : events) {
        double eventLat = std::stod(event.getLatitude());
        double eventLong = std::stod(event.getLongitude());

        double dx = eventLat - personLat;
        double dy = eventLong - personLong;
        double distance = std::sqrt(dx * dx + dy * dy);


        if (filter && distance > 5.0)
            continue;

        int row = eventsTable->rowCount();
        eventsTable->insertRow(row);

        eventsTable->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(event.getOrganiser())));
        eventsTable->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(event.getName())));
        eventsTable->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(event.getLatitude())));
        eventsTable->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(event.getLongitude())));
        eventsTable->setItem(row, 4, new QTableWidgetItem(QString::fromStdString(event.getDate())));

        if (event.getOrganiser() == person.getName()) {
            for (int col = 0; col < eventsTable->columnCount(); col++) {
                eventsTable->item(row, col)->setBackground(Qt::green);
            }
        }
    }
}
void PersonWindow::addEvent() {
    std::string name = nameEdit->text().toStdString();
    std::string desc = descriptionEdit->text().toStdString();
    std::string lat = latEdit->text().toStdString();
    std::string lon = longEdit->text().toStdString();
    std::string date = dateEdit->text().toStdString();


    for (const auto& ev : service.getSortedByDate()) {
        if (ev.getName() == name && ev.getLatitude() == lat && ev.getLongitude() == lon) {
            QMessageBox::warning(this,"Same Event", "Same event exists!");
            return;
        }
    }


    service.addEvent(person.getName(), name,desc,lat,lon,date);
    loadEvents();
    service.saveToFile();

    nameEdit->clear();
    descriptionEdit->clear();
    latEdit->clear();
    longEdit->clear();
    dateEdit->clear();
}

PersonWindow::~PersonWindow() {
    service.removeObserver(this);
}
void PersonWindow::update() {
    loadEvents();
}


