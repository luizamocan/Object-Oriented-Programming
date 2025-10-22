

#include "MainGUI.h"
MainGUI::MainGUI(Controller &controller, QWidget *parent) :QWidget(parent),controller(controller){
    init_gui();
    connect_signals();
    this->setWindowTitle("Select Mode");
    this->resize(250,100);
}
void MainGUI::init_gui() {
    auto* layout=new QVBoxLayout(this);
    admin_button=new QPushButton("Admin Mode");
    user_button=new QPushButton("User Mode");
    layout->addWidget(admin_button);
    layout->addWidget(user_button);
}

void MainGUI::connect_signals() {
    connect(admin_button,&QPushButton::clicked,[this]() {
        auto* admin_gui=new AdminGUI(controller);
        admin_gui->show();
        this->close();
    });
    connect(user_button,&QPushButton::clicked,[this]() {
        auto* user_gui=new UserGUI(controller);
        user_gui->show();
        this->close();
    });
}


