
#ifndef MAINGUI_H
#define MAINGUI_H
#pragma once
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include "Controller.h"
#include "AdminGUI.h"
#include "UserGUI.h"

class MainGUI : public QWidget {
    Q_OBJECT
    private:
    Controller& controller;
    QPushButton* admin_button;
    QPushButton* user_button;

    void init_gui();
    void connect_signals();

    public:
    explicit MainGUI(Controller& controller,QWidget *parent = nullptr);
};
#endif //MAINGUI_H
