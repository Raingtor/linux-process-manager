#include "../include/Terminal.h"

Terminal::Terminal() {

}

Terminal::Terminal(size_t id_, TerminalState terminalState_) {
    id = id_;
    terminalState = terminalState_;
    adminPipePath = "./admin";
    terminalPipePath = "./terminal" + std::to_string(id);
}

size_t Terminal::getId() {
    return id;
}

void Terminal::getTerminalState() {
    Data data;
    data.info = Utils::terminalStateToString(terminalState);
    writeToPipe(data);
    readFromPipe();
}

void Terminal::getUsers() {
    std::string message;
    for (int i = 0; i < users.size(); i++) {
        message += users[i].getName() + " " + Utils::userPrivilegeToString(users[i].getUserPrivilege()) + "\n";
    }
    Data data;
    data.info = message;
    writeToPipe(data);
    readFromPipe();
}

void Terminal::getPrograms() {
    std::string message;
    for (int i = 0; i < programs.size(); i++) {
        message += programs[i].getName() + " " + Utils::userPrivilegeToString(users[i].getUserPrivilege()) + "\n";
    }
    Data data;
    data.info = message;
    writeToPipe(data);
    readFromPipe();
}

void Terminal::installProgram(std::string name) {
    Data data;
    if (UtilMethods::inVector(programs, name)) {
        data.info = "Программа уже установлена.\n";
    } else {
        programs.push_back(UtilMethods::findProgramByName(programs, name));
        data.info = "Программа установлена.\n";
    }
    writeToPipe(data);
    readFromPipe();
}

void Terminal::updateProgram(std::string name) {
    Data data;
    if (UtilMethods::inVector(programs, name)) {
        data.info = "Программа обновлена.\n";
    } else {
        data.info = "Программа еще не установлена.\n";
    }
    writeToPipe(data);
    readFromPipe();
}

void Terminal::reinstallProgram(std::string name) {
    Data data;
    if (UtilMethods::inVector(programs, name)) {
        data.info = "Программа удалена.\n";
        programs.erase(programs.begin() + UtilMethods::findProgramIndex(programs, name));
    } else {
        data.info = "Программа еще не установлена.\n";
    }
    writeToPipe(data);
    readFromPipe();
}

void Terminal::addUser(std::string name) {
    Data data;
    if (UtilMethods::inVector(users, name)) {
        data.info = "Пользователь уже есть в списке.\n";
    } else {
        users.push_back(UtilMethods::findUserByName(users, name));
        data.info = "Пользователь добавлен в список.\n";
    }
    writeToPipe(data);
    readFromPipe();
}

void Terminal::removeUser(std::string name) {
    Data data;
    if (UtilMethods::inVector(users, name)) {
        data.info = "Пользователь удален.\n";
        users.erase(users.begin() + UtilMethods::findUserIndex(users, name));
    } else {
        data.info = "Пользователя еще нет в списке.\n";
    }
    writeToPipe(data);
    readFromPipe();
}

void Terminal::setTerminalState(TerminalState state) {
    std::string message;
    if (state == Online) {
        message = "включен.";
    } else {
        message = "выключен.";
    }
    Data data;
    if (state != terminalState) {
        data.info = "Терминал " + message;
        terminalState = state;
    } else {
        data.info = "Терминал уже " + message;
    }
    writeToPipe(data);
    readFromPipe();
}

void Terminal::writeToPipe(Data data) {
    int file = open(adminPipePath.c_str(), O_WRONLY);
    write(file, &data, sizeof(data));
    close(file);
}

void Terminal::readFromPipe() {
    while (terminalState == Online) {
        Data data;
        int file = open(adminPipePath.c_str(), O_RDONLY);
        ssize_t size = read(file, &data, sizeof(data));
        if (size != sizeof(Data)) {
            continue;
        } else {
            switch (data.command) {
                case GetTerminalState:
                    getTerminalState();
                case GetPrograms:
                    getPrograms();
                case InstallProgram:
                    installProgram(data.info);
                case UpdateProgram:
                    updateProgram(data.info);
                case ReinstallProgram:
                    reinstallProgram(data.info);
                case GetUsers:
                    getUsers();
                case AddUser:
                    addUser(data.info);
                case RemoveUser:
                    removeUser(data.info);
                case SetTerminalState:
                    setTerminalState(Utils::stringToTerminalState(data.info));
                default:
                    continue;
            }
        }
    }
}