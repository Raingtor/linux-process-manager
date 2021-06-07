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

    std::string logFilePath;

public:
    Terminal();

    Terminal(size_t id_, TerminalState terminalState_);

    void start();

    void stop();

    size_t getId();

    void getTerminalState();

    bool getActive();

    void getUsers();

    void getPrograms();

    std::string getLogFilePath();

    void installProgram(std::string name);

    void updateProgram(std::string name);

    void reinstallProgram(std::string name);

    void addUser(std::string name);

    void removeUser(std::string name);

    void setTerminalState(TerminalState state);

    void writeToPipe(Data data);

    static void* readFromPipe(void *arg);

    ~Terminal();
};

#endif