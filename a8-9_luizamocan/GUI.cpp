
#include "GUI.h"
#include <QMessageBox>
GUI::GUI(QWidget *parent) :QWidget(parent){
    this->init_gui();
    //this->populate_dogs();
    this->connectRelations();
}

void GUI::init_gui() {
    this->start=new QHBoxLayout(this);

    this->dogs_list=new QListWidget{};
    this->start->addWidget(dogs_list);

    auto* form_layout=new QFormLayout;
    this->name_line=new QLineEdit;
    this->breed_line=new QLineEdit;
    this->age_line=new QLineEdit;
    this->link_to_photo_line=new QLineEdit;

    form_layout->addRow("Name:",this->name_line);
    form_layout->addRow("Breed:",this->breed_line);
    form_layout->addRow("Age:",this->age_line);
    form_layout->addRow("Link:",this->link_to_photo_line);

    this->add=new QPushButton("Add");
    this->del=new QPushButton("Delete");
    this->update=new QPushButton("Update");
    this->show_table=new QPushButton("Show Table");

    auto* buttons_layout= new QHBoxLayout;
    buttons_layout->addWidget(this->add);
    buttons_layout->addWidget(this->del);
    buttons_layout->addWidget(this->update);
    buttons_layout->addWidget(this->show_table);

    auto *right_side=new QHBoxLayout;
    right_side->addLayout(form_layout);
    right_side->addLayout(buttons_layout);

    this->start->addLayout(right_side);

}
void GUI::populate_dogs() {
    this->dogs_list->clear();
    for (const Dog& dog:this->controller.getAdminRepository().getDogs())
        this->dogs_list->addItem(QString::fromStdString(dog.to_str()));
}
void GUI::connectRelations() {
    QObject::connect(this->add,&QPushButton::clicked,this,&GUI::_add);
    QObject::connect(this->del,&QPushButton::clicked,this,&GUI::_del);
    QObject::connect(this->update,&QPushButton::clicked,this,&GUI::_update);
    QObject::connect(this->show_table,&QPushButton::clicked,this,&GUI::showTable);
}
void GUI::_add() {
    try {
        Dog dog(this->name_line->text().toStdString(),
            this->breed_line->text().toStdString(),
            this->link_to_photo_line->text().toStdString(),
            std::stoi(this->age_line->text().toStdString()));

        ValidateDog::validate_add(this->controller.getAdminRepository(),dog);
        if (this->controller.addAdmin(dog)) {
            this->populate_dogs();
            //this->showTable();
        }

        else
            QMessageBox::warning(this, "Add error", "Dog already exists.");
    }catch (const ValidationException &ex) {
        QMessageBox::critical(this, "Validation failed", QString::fromStdString(ex.get_message()));
    } catch (...) {
        QMessageBox::critical(this, "Error", "Invalid input.");
    }
}

void GUI::_del() {
    QString name = name_line->text();
    if (name.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Please enter the name of the dog to delete.");
        return;
    }


    Dog dummyDog{name.toStdString(), "", "", 0};

    try {
        if (controller.removeAdmin(dummyDog)) {
            QMessageBox::information(this, "Success", "Dog deleted successfully.");
        } else {
            QMessageBox::warning(this, "Error", "Dog not found.");
        }
    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Exception", e.what());
    }

    name_line->clear();
    breed_line->clear();
    age_line->clear();
    link_to_photo_line->clear();
}

void GUI::_update() {
    QString name = name_line->text();
    QString breed = breed_line->text();
    QString ageStr = age_line->text();
    QString link = link_to_photo_line->text();

    if (name.isEmpty() || breed.isEmpty() || ageStr.isEmpty() || link.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Please complete all fields to update the dog.");
        return;
    }

    try {
        int age = std::stoi(ageStr.toStdString());

        Dog oldDog{name.toStdString(), "", "", 0};
        Dog newDog{name.toStdString(), breed.toStdString(), link.toStdString(), age};

        if (controller.updateAdmin(oldDog, newDog)) {
            QMessageBox::information(this, "Success", "Dog updated successfully.");
        } else {
            QMessageBox::warning(this, "Error", "Dog not found for update.");
        }
    } catch (const std::invalid_argument& e) {
        QMessageBox::critical(this, "Error", "Invalid age format. Please enter a number.");
    }

    name_line->clear();
    breed_line->clear();
    age_line->clear();
    link_to_photo_line->clear();
}

void GUI::showTable() {
    if (tableView!=nullptr) {
        delete tableView;
        start->removeWidget(tableView);
        tableView=nullptr;
    }
    std::vector<Dog> dogs = this->controller.getAdminRepository().getDogs();
    ModelGUI* model = new ModelGUI(dogs, this);

    tableView = new QTableView(this);
    tableView->setModel(model);

    start->addWidget(tableView);
    tableView->show();
}

void GUI::closeEvent(QCloseEvent *event) {
    event->accept();
}
