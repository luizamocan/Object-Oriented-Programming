#include <QApplication>
#include "controller.h"
#include "gui.h"
int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    Controller controller;
    GUI gui(controller);
    gui.show();
    return app.exec();
}