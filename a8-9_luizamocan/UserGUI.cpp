
#include "UserGUI.h"
#include <QDesktopServices>
#include <QUrl>
#include <QCloseEvent>
#include "FileViewer.h"
#include "FileSaver.h"
#include "CSVSaver.h"
#include "HTMLSaver.h"
#include "AdminGUI.h"
#include "AdoptionListWindow.h"
UserGUI::UserGUI(Controller& controller, QWidget* parent) : controller(controller), QWidget(parent) {
    QString format = ask_file_format();
    if (format.isEmpty()) {
        QMessageBox::warning(this, "Error", "You must select a file format to continue.");
        close();
        return;
    }

    this->file_format = format.toStdString();
    this->file_name = "adoptions";

    controller.getUserRepository().setFileFormat(file_format);
    controller.getUserRepository().setFileName(file_name);

    this->init_gui();
    this->connect_signals();
    //this->populate_list();
}

void UserGUI::init_gui() {
    main_layout=new QVBoxLayout(this);

    name_label=new QLabel("Name:");
    breed_label=new QLabel("Breed:");
    age_label=new QLabel("Age:");
    image_label=new QLabel();
    image_label->setFixedSize(200,200);
    image_label->setScaledContents(true);

    auto* info_layout=new QVBoxLayout();
    info_layout->addWidget(name_label);
    info_layout->addWidget(breed_label);
    info_layout->addWidget(age_label);
    info_layout->addWidget(image_label);

    next_button=new QPushButton("Next");
    adopt_button=new QPushButton("Adopt");

    auto* navigate_layout=new QHBoxLayout;
    navigate_layout->addWidget(next_button);
    navigate_layout->addWidget(adopt_button);

    breed_filter_line=new QLineEdit;
    age_filter_line=new QLineEdit;
    filter_button=new QPushButton("Filter:");

    auto* filter_form = new QFormLayout;
    filter_form->addRow("Breed:", breed_filter_line);
    filter_form->addRow("Max Age:", age_filter_line);

    auto* filter_layout = new QVBoxLayout;
    filter_layout->addLayout(filter_form);
    filter_layout->addWidget(filter_button);

    view_adoptions_button = new QPushButton("View Adoption List");
    open_file_button = new QPushButton("Open File");
    save_adoptions_button = new QPushButton("Save Adoption List");
    this->go_to_admin=new QPushButton("Go to Admin");

    main_layout->addLayout(info_layout);
    main_layout->addLayout(navigate_layout);
    main_layout->addLayout(filter_layout);
    main_layout->addWidget(view_adoptions_button);
    main_layout->addWidget(open_file_button);
    main_layout->addWidget(save_adoptions_button);
    main_layout->addWidget(go_to_admin);
}

void UserGUI::connect_signals() {
    connect(next_button, &QPushButton::clicked, this, &UserGUI::next_dog);
    connect(adopt_button, &QPushButton::clicked, this, &UserGUI::adopt_dog);
    connect(filter_button, &QPushButton::clicked, this, &UserGUI::filter_dogs);
    connect(view_adoptions_button, &QPushButton::clicked, this, &UserGUI::view_adoption_dogs);
    connect(open_file_button, &QPushButton::clicked, this, &UserGUI::open_file);
    connect(save_adoptions_button, &QPushButton::clicked, this, &UserGUI::save_adoption_list);
    connect(go_to_admin, &QPushButton::clicked, this, &UserGUI::goToAdmin);
}
void UserGUI::show_current_dog() {
    if (filteredDogs.empty()) {
        QMessageBox::information(this,"Info","No dogs available.");
        return;
    }
    current_index %= filteredDogs.size();
    const Dog& current_dog = filteredDogs[current_index];
    update_labels(current_dog);


    QDesktopServices::openUrl(QUrl(QString::fromStdString(current_dog.getLinkToPhoto())));
}

void UserGUI::update_labels(const Dog& dog) {
    name_label->setText(QString::fromStdString("Name: "+dog.getName()));
    breed_label->setText(QString::fromStdString("Breed: "+dog.getBreed()));
    age_label->setText(QString::fromStdString("Age: " + std::to_string(dog.getAge())));
    image_label->setPixmap(QPixmap(QString::fromStdString(dog.getLinkToPhoto())));
}

void UserGUI::next_dog() {
    if (!filteredDogs.empty()) {
        current_index=(current_index+1)%filteredDogs.size();
        show_current_dog();
    }
}


void UserGUI::adopt_dog() {
    if (filteredDogs.empty()) return;
    controller.add_user(filteredDogs[current_index]);
    QMessageBox::information(this,"Info","Added new dog to adoption list.");
}
void UserGUI::filter_dogs() {
    std::string breed=breed_filter_line->text().toStdString();
    std::string age_str=age_filter_line->text().toStdString();
    int max_age=0;

    try {
        if (!age_str.empty())
            max_age=std::stoi(age_str);
    }catch (...) {
        QMessageBox::warning(this,"Error","Invalid age.");
        return;
    }
    filteredDogs.clear();
    for (const auto&dog:controller.getAdminRepository().getDogs()) {
        if ((breed.empty() || dog.getBreed()==breed)&& (age_str.empty() || dog.getAge()<=max_age)) {
            filteredDogs.push_back(dog);
        }
    }

    current_index=0;
    if (!filteredDogs.empty()) {
        show_current_dog();
    }
    else
        QMessageBox::information(this, "No dogs", "No dogs match the criteria.");

}
void UserGUI::view_adoption_dogs() {
    const auto& dogs = controller.getUserRepository().getAdoption_dogs();

    if (dogs.empty()) {
        QMessageBox::information(this, "Info", "There are no dogs in the adoption list.");
        return;
    }

    auto* window = new AdoptionListWindow(dogs);
    window->setAttribute(Qt::WA_DeleteOnClose);
    window->show();
}
void UserGUI::open_file() {
    std::string filename = file_name + "." + file_format;
    QString qfilename = QString::fromStdString(filename);

    bool opened = QDesktopServices::openUrl(QUrl::fromLocalFile(qfilename));
    if (!opened) {
        QMessageBox::warning(this, "Error", "Could not open the file: " + qfilename);
    }
}

void UserGUI::closeEvent(QCloseEvent *event) {
    event->accept();
}

QString UserGUI::ask_file_format() {
    QDialog dialog(this);
    dialog.setWindowTitle("Select File Format");

    QPushButton* csv_button = new QPushButton("CSV");
    QPushButton* html_button = new QPushButton("HTML");

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(new QLabel("Choose file format:"));
    layout->addWidget(csv_button);
    layout->addWidget(html_button);
    dialog.setLayout(layout);

    QString selected_format;

    connect(csv_button, &QPushButton::clicked, [&]() {
        selected_format = "csv";
        dialog.accept();
    });
    connect(html_button, &QPushButton::clicked, [&]() {
        selected_format = "html";
        dialog.accept();
    });

    dialog.exec();
    return selected_format;
}

void UserGUI::save_adoption_list() {
    const auto& adopted_dogs = controller.getUserRepository().getAdoption_dogs();
    if (adopted_dogs.empty()) {
        QMessageBox::information(this, "Info", "There are no dogs in the adoption list.");
        return;
    }

    FileSaver* saver = nullptr;
    std::string filename = file_name + "." + file_format;

    if (file_format == "csv") {
        saver = new  CSVSaver();
    } else if (file_format == "html") {
        saver = new HTMLSaver();
    } else {
        QMessageBox::warning(this, "Error", "Unsupported file format.");
        return;
    }

    saver->save(adopted_dogs, filename);
    QMessageBox::information(this, "Saved", QString::fromStdString("Adoption list saved to " + filename));
    delete saver;
}
void UserGUI::goToAdmin() {
    auto *adminGUI=new AdminGUI(this->controller);
    adminGUI->show();
    this->close();
}
