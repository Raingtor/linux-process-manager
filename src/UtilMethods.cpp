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

bool UtilMethods::inVector(std::vector<User> users, std::string name) {
    for (int i = 0; i < users.size(); i++) {
        if (users[i].getName() == name) {
            return true;
        }
    }
    return false;
}

bool UtilMethods::inVector(std::vector<Program> programs, std::string name) {
    for (int i = 0; i < programs.size(); i++) {
        if (programs[i].getName() == name) {
            return true;
        }
    }
    return false;
}

User UtilMethods::findUserByName(std::vector<User> users, std::string name) {
    for (int i = 0; i < users.size(); i++) {
        if (users[i].getName() == name) {
            return users[i];
        }
    }
}

Program UtilMethods::findProgramByName(std::vector<Program> programs, std::string name) {
    for (int i = 0; i < programs.size(); i++) {
        if (programs[i].getName() == name) {
            return programs[i];
        }
    }
}

int UtilMethods::findUserIndex(std::vector<User> users, std::string name) {
    for (int i = 0; i < users.size(); i++) {
        if (users[i].getName() == name) {
            return i;
        }
    }
}

int UtilMethods::findProgramIndex(std::vector<Program> programs, std::string name) {
    for (int i = 0; i < programs.size(); i++) {
        if (programs[i].getName() == name) {
            return i;
        }
    }
}
