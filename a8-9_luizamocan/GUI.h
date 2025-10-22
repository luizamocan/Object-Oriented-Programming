

#ifndef GUI_H
#define GUI_H
#include "qwidget.h"
#include "qboxlayout.h"
#include "qformlayout.h"
#include "qpushbutton.h"
#include "qlabel.h"
#include "qtabwidget.h"
#include "qlineedit.h"
#include "qlistwidget.h"
#include "Controller.h"
#include "Dog.h"
#include "QErrorMessage"
#include "ValidateDog.h"
#include "QCloseEvent"
#include "QTableView"
#include "ModelGUI.h"
#include <sstream>

class GUI:public QWidget {
    Q_OBJECT
    Controller controller;

    QHBoxLayout* start;
    QPushButton* csv;
    QPushButton* html;

    QListWidget* dogs_list;
    QListWidget* filteredDogs;
    QLineEdit* filterBox;

    QLineEdit* name_line;
    QLineEdit* breed_line;
    QLineEdit* link_to_photo_line;
    QLineEdit* age_line;

    QPushButton* add;
    QPushButton* del;
    QPushButton* update;


    QTableView* tableView=nullptr;

    QListWidget* adoption_dogs;
    QPushButton* browser;
    QPushButton* show_table;

    QLineEdit* filter_breed;
    QPushButton* filter;
    QLineEdit* current_dog;
    std::vector<Dog> filtered_list;
    int index;

    QPushButton* next;
    QPushButton* add_to_adoption_list;
    QPushButton* stop;

    QLineEdit* adoption_list_name_line;
    void closeEvent(QCloseEvent *event) override;

    public:
    GUI(QWidget *parent = nullptr);

    void choose_repo();
    void init_csv();
    void init_html();

    void init_gui();
    void populate_gui();
    void connectRelations();

    void filterFunction();
    public slots:
    void _add();
    void _del();
    void _update();
public :
    void populate_dogs();
    void open_in_browser();
    void filterByName();
    void _addToAdoptionList();
    void _next();
    void _stop();

    void showTable();
};

#endif //GUI_H
