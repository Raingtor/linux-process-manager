#ifndef PROCESSMANAGER_UI_H
#define PROCESSMANAGER_UI_H

#include "stdafx.h"
#include "User.h"
#include "Program.h"
#include "Admin.h"
#include "Terminal.h"

class UI {
private:
    Admin admin;

public:
    void start();

    void exit();

    void startMenu();

    void chooseTerminal();

    void workWithTerminal();

    void editPrograms();

    void installProgram();

    void updateProgram();

    void reinstallProgram();

    void editTerminal();

    void addUser();

    void removeUser();

    void setTerminalState();

    void showUsers();

    void showPrograms();

    void showTerminals();

    int input();
};

#endif