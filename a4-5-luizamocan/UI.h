
#ifndef UI_H
#define UI_H
#include "Controller.h"
class UI {
private:
    Controller controller;
public:
    static bool isNumber(const string& str);
    static string login_option();
    static void admin_menu();
    static void user_menu();
    static string admin_input();
    static string user_input();
    void addAdmin();
    void removeAdmin();
    void updateAdmin();
    void displayAdmin();
    void start();
    static string get_breed_input();
    static string get_response_input();
    void adopt_dogs();
    void display_user();
    void filter_and_adopt_dogs();
};
#endif //UI_H
