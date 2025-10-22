/*
#include <QApplication>
#include <QPushButton>
#include "GUI.h"
int main(int argc, char* argv[]) {
    QApplication app(argc,argv);
   GUI gui;
    //gui.showTable();
    gui.show();
    return app.exec();

}
*/
#include <QApplication>
#include "MainGUI.h"
#include "Controller.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    Controller controller;

    MainGUI mainGui(controller);
    mainGui.show();

    return a.exec();
}



