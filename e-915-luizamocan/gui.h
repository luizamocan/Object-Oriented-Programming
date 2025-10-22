//
// Created by Mocan Luiza on 6/25/2025.
//

#ifndef GUI_H
#define GUI_H
#include <QListWidget>
#include <QLabel>
#include <QPushButton>
#include <QMainWindow>
#include <QTableWidget>
#include "service.h"
#include <QCheckBox>
#include <QTextEdit>
class PersonWindow : public QMainWindow ,public Observer{
    Q_OBJECT
private:
    Service& service;
    Person person;
    QTableWidget* eventsTable;
    QCheckBox* filterCheckBox;


    QLineEdit* nameEdit;
    QLineEdit* descriptionEdit;
    QLineEdit* latEdit;
    QLineEdit* longEdit;
    QLineEdit* dateEdit;
    QLineEdit* filterEdit;
    QPushButton* addButton;

    QTextEdit* descEditBox;
    QPushButton* goingButton;
    QPushButton* updateButton;
    QLineEdit* dateEditBox;
    QListWidget* attendeesList;



    public:
    void loadEvents();
    void addEvent();
    explicit PersonWindow(Service& service,Person person,QWidget *parent = 0);
    ~PersonWindow() override;
    void update() override;


};
#endif //GUI_H
