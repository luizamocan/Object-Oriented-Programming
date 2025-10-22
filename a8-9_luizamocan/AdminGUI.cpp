#include "AdminGUI.h"
#include <QMessageBox>
#include "UserGUI.h"
#include <QShortcut>
AdminGUI::AdminGUI(Controller& ctrl, QWidget *parent) : QWidget(parent), controller(ctrl) {
    //this->setAttribute(Qt::WA_DeleteOnClose);
    this->init_gui();
    this->connectRelations();
    this->populate_dogs();
}

void AdminGUI::init_gui() {
    this->start = new QHBoxLayout(this);

    this->dogs_list = new QListWidget{};
    this->start->addWidget(dogs_list);

    auto* form_layout = new QFormLayout;
    this->name_line = new QLineEdit;
    this->breed_line = new QLineEdit;
    this->age_line = new QLineEdit;
    this->link_to_photo_line = new QLineEdit;

    form_layout->addRow("Name:", this->name_line);
    form_layout->addRow("Breed:", this->breed_line);
    form_layout->addRow("Age:", this->age_line);
    form_layout->addRow("Link:", this->link_to_photo_line);

    this->add = new QPushButton("Add");
    this->del = new QPushButton("Delete");
    this->update = new QPushButton("Update");
    this->show_table = new QPushButton("Show Table");
    this->go_to_user = new QPushButton("Go to User");

    this->undo_button=new QPushButton("Undo");
    this->redo_button=new QPushButton("Redo");


    auto* buttons_layout = new QHBoxLayout;
    buttons_layout->addWidget(this->add);
    buttons_layout->addWidget(this->del);
    buttons_layout->addWidget(this->update);
    buttons_layout->addWidget(this->show_table);
    buttons_layout->addWidget(this->go_to_user);
    buttons_layout->addWidget(this->undo_button);
    buttons_layout->addWidget(this->redo_button);

    auto* right_side = new QHBoxLayout;
    right_side->addLayout(form_layout);
    right_side->addLayout(buttons_layout);

    this->start->addLayout(right_side);
}

void AdminGUI::populate_dogs() {
    this->dogs_list->clear();
    for (const Dog& dog : this->controller.getAdminRepository().getDogs())
        this->dogs_list->addItem(QString::fromStdString(dog.to_str()));
}

void AdminGUI::connectRelations() {
    QObject::connect(this->add, &QPushButton::clicked, this, &AdminGUI::_add);
    QObject::connect(this->del, &QPushButton::clicked, this, &AdminGUI::_del);
    QObject::connect(this->update, &QPushButton::clicked, this, &AdminGUI::_update);
    QObject::connect(this->show_table, &QPushButton::clicked, this, &AdminGUI::showTable);
    QObject::connect(this->go_to_user, &QPushButton::clicked, this, &AdminGUI::openUserGUI);
    connect(undo_button, &QPushButton::clicked, this, [=]() {
    if (!undo_stack.empty()) {
        undo_stack.back()->undo();
        redo_stack.push_back(std::move(undo_stack.back()));
        undo_stack.pop_back();

        this->populate_dogs();
    }
});

    connect(redo_button, &QPushButton::clicked, this, [=]() {
        if (!redo_stack.empty()) {
            redo_stack.back()->redo();
            undo_stack.push_back(std::move(redo_stack.back()));
            redo_stack.pop_back();

            this->populate_dogs();
        }
    });

    // Keyboard shortcuts
    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Z), this, [=]() {
        undo_button->click();
    });
    new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Y), this, [=]() {
        redo_button->click();
    });

}

void AdminGUI::_add() {
    try {
        Dog dog(
            this->name_line->text().toStdString(),
            this->breed_line->text().toStdString(),
            this->link_to_photo_line->text().toStdString(),
            std::stoi(this->age_line->text().toStdString())
        );

        ValidateDog::validate_add(this->controller.getAdminRepository(), dog);
        if (this->controller.addAdmin(dog)) {
            undo_stack.push_back(std::make_unique<UndoAdd>(controller, dog));
            redo_stack.clear();
            this->populate_dogs();
        } else {
            QMessageBox::warning(this, "Add error", "Dog already exists.");
        }
    } catch (const ValidationException &ex) {
        QMessageBox::critical(this, "Validation failed", QString::fromStdString(ex.get_message()));
    } catch (...) {
        QMessageBox::critical(this, "Error", "Invalid input.");
    }
}

void AdminGUI::_del() {
    QString name = name_line->text();
    if (name.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Please enter the name of the dog to delete.");
        return;
    }

    Dog dummyDog{name.toStdString(), "", "", 0};

    try {
        const Dog& actualDog = controller.getAdminRepository().find(dummyDog);
        if (controller.removeAdmin(dummyDog)) {
            QMessageBox::information(this, "Success", "Dog deleted successfully.");
            undo_stack.push_back(std::make_unique<UndoRemove>(controller, actualDog));
            redo_stack.clear();
            this->populate_dogs();
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

void AdminGUI::_update() {
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
        std::string nameStr = name.toStdString();


        Dog actualOldDog = controller.getAdminRepository().findByName(nameStr);


        Dog newDog{nameStr, breed.toStdString(), link.toStdString(), age};

        if (controller.updateAdmin(actualOldDog, newDog)) {
            undo_stack.push_back(std::make_unique<UndoUpdate>(controller, actualOldDog, newDog));
            redo_stack.clear();
            QMessageBox::information(this, "Success", "Dog updated successfully.");
            this->populate_dogs();
        } else {
            QMessageBox::warning(this, "Error", "Dog not found for update.");
        }
    } catch (const std::invalid_argument& e) {
        QMessageBox::critical(this, "Error", "Invalid age format. Please enter a number.");
    } catch (const ValidationException& e) {
        QMessageBox::critical(this, "Validation error", QString::fromStdString(e.get_message()));
    } catch (const std::runtime_error& e) {
        QMessageBox::critical(this, "Error", e.what());
    }

    name_line->clear();
    breed_line->clear();
    age_line->clear();
    link_to_photo_line->clear();
}



void AdminGUI::showTable() {
    if (tableView != nullptr) {
        delete tableView;
        start->removeWidget(tableView);
        tableView = nullptr;
    }

    std::vector<Dog> dogs = this->controller.getAdminRepository().getDogs();
    ModelGUI* model = new ModelGUI(dogs, this);

    tableView = new QTableView(this);
    tableView->setModel(model);

    start->addWidget(tableView);
    tableView->show();
}

void AdminGUI::closeEvent(QCloseEvent *event) {
    event->accept();
}
void AdminGUI::openUserGUI() {
    auto* userGUI=new UserGUI(this->controller);
    userGUI->show();
    this->close();
}
