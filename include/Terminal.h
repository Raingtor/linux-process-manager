#ifndef PROCESSMANAGER_TERMINAL_H
#define PROCESSMANAGER_TERMINAL_H

#include "stdafx.h"
#include "User.h"
#include "Program.h"
#include "Utils.h"
#include "UtilMethods.h"

class Terminal {
private:
    size_t id;

    TerminalState terminalState;

    bool active = false;

    std::vector<User> users;

    std::vector<Program> programs;

    std::string adminPipePath;

    std::string terminalPipePath;

    pthread_t thread;

public:
    Terminal();

    Terminal(size_t id_, TerminalState terminalState_);

    void start();

    size_t getId();

    void getTerminalState();

    void setActive(bool active_);

    void getUsers();

    void getPrograms();

    void installProgram(std::string name);

    void updateProgram(std::string name);

    void reinstallProgram(std::string name);

    void addUser(std::string name);

    void removeUser(std::string name);

    void setTerminalState(TerminalState state);

    void writeToPipe(Data data);

    static void* readFromPipe(void *arg);
};

#endif