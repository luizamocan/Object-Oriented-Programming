#pragma once
#include <QWidget>
#include <QPushButton>
#include <QListWidget>
#include <QLineEdit>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QTableView>
#include "Controller.h"
#include <QCloseEvent>
#include "Dog.h"
#include "ModelGUI.h"
#include "UndoAction.h"
#include "ValidateDog.h"
#include <memory>
class AdminGUI : public QWidget {
    Q_OBJECT

private:
    Controller& controller;

    // Layouts
    QHBoxLayout* start;
    QTableView* tableView = nullptr;

    // Widgets
    QListWidget* dogs_list;
    QLineEdit *name_line, *breed_line, *age_line, *link_to_photo_line;
    QPushButton *add, *del, *update, *show_table;
    QPushButton *go_to_user;


    //undo/redo operations
    std::vector<std::unique_ptr<UndoAction>> undo_stack;
    std::vector<std::unique_ptr<UndoAction>> redo_stack;
    QPushButton* undo_button,*redo_button;

    void init_gui();
    void connectRelations();
    void populate_dogs();

    void _add();
    void _del();
    void _update();
    void showTable();
    void openUserGUI();

protected:
    void closeEvent(QCloseEvent *event) override;

public:
    AdminGUI(Controller& ctrl, QWidget* parent = nullptr);
};
