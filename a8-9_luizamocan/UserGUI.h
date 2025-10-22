
#ifndef GUI_USER_H
#define GUI_USER_H
#pragma once
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QFormLayout>
#include <QMessageBox>
#include <QLabel>
#include <vector>
#include "Controller.h"
#include "Dog.h"

class UserGUI : public QWidget {
    Q_OBJECT

    private:
    Controller& controller;
    std::string file_format;
    std::string file_name;

    std::vector<Dog> filteredDogs;
    int current_index=0;

    QLabel* name_label;
    QLabel* breed_label;
    QLabel* age_label;
    QLabel* image_label;

    QLineEdit* breed_filter_line;
    QLineEdit* age_filter_line;

    QPushButton* next_button;
    QPushButton* adopt_button;
    QPushButton* filter_button;
    QPushButton* view_adoptions_button;
    QPushButton* open_file_button;
    QPushButton* save_adoptions_button;
    QVBoxLayout* main_layout;
    QString ask_file_format();

    QPushButton* go_to_admin;
    void init_gui();
    void connect_signals();
    void show_current_dog();
    void update_labels(const Dog& dog);

    public:
    explicit UserGUI(Controller& controller,QWidget *parent = nullptr);
    void closeEvent(QCloseEvent* event) override;

    private slots:
    void next_dog();
    void adopt_dog();
    void filter_dogs();
    void view_adoption_dogs();
    void save_adoption_list();
    void open_file();
    void goToAdmin();
};

#endif //GUI_USER_H
