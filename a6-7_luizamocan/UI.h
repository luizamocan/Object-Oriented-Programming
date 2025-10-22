
#ifndef UI_H
#define UI_H
#include "Controller.h"
#include "FileSaver.h"
class UI {
private:
    Controller controller;
    string file_format;
    string file_name;
public:
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

    void choose_file_format();
    void save_adoption_list(const std::string& format);

    void view_adoption_list();
};
#endif //UI_H
