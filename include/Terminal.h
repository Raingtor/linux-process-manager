#ifndef PROCESSMANAGER_TERMINAL_H
#define PROCESSMANAGER_TERMINAL_H

#include "stdafx.h"
#include "User.h"
#include "Program.h"
#include "Utils.h"

class Terminal {
private:
    size_t id;

    TerminalState terminalState;

    std::vector<User> users;

    std::vector<Program> programs;

    std::string adminPipePath;

    std::string terminalPipePath;

public:
    Terminal();

    Terminal(size_t id_, TerminalState terminalState_);

    TerminalState getTerminalState();

    std::vector<User> getUsers();

    std::vector<Program> getPrograms();
};

#endif