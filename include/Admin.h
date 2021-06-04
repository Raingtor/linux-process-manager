#ifndef PROCESSMANAGER_ADMIN_H
#define PROCESSMANAGER_ADMIN_H

#include "stdafx.h"
#include "User.h"
#include "Program.h"
#include "Terminal.h"
#include "UtilMethods.h"

class Admin {
private:
    std::vector<User> users;

    std::vector<Program> programs;

    std::vector<Terminal> terminals;

    size_t currentTerminal;

    std::string adminPipePath;

    std::string terminalPipePath;
public:
    Admin();

    std::vector<User> getUsers();

    std::vector<Program> getPrograms();

    std::vector<Terminal> getTerminals();

    void setCurrentTerminal(size_t currentTerminal_);

    void getTerminalState();

    void getTerminalsState();

    void getTerminalPrograms();

    void installProgram(std::string name);

    void updateProgram(std::string name);

    void reinstallProgram(std::string name);

    void getTerminalUsers();

    void addUser(std::string name);

    void removeUser(std::string name);

    void setTerminalState(TerminalState state);
};

#endif