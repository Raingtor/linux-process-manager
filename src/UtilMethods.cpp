#include "../include/UtilMethods.h"

std::vector<User> UtilMethods::initUsers() {
    std::vector<User> users;
    users.push_back(User("Kate", Admin_));
    users.push_back(User("Maria", User_));
    users.push_back(User("Alex", User_));
    return users;
}

std::vector<Program> UtilMethods::initPrograms() {
    std::vector<Program> programs;
    programs.push_back(Program("SystemConfig", Admin_));
    programs.push_back(Program("Chrome", User_));
    programs.push_back(Program("Adobe Reader", User_));
    programs.push_back(Program("Zoom", User_));
    programs.push_back(Program("Notepad++", User_));
    return programs;
}