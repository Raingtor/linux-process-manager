#include "../include/Terminal.h"

Terminal::Terminal() {

}

Terminal::Terminal(size_t id_, TerminalState terminalState_) {
    id = id_;
    terminalState = terminalState_;
    adminPipePath = "./admin";
    terminalPipePath = "./terminal" + std::to_string(id);
}

void Terminal::start() {
    pthread_create(&thread, nullptr, Terminal::readFromPipe, this);
}

size_t Terminal::getId() {
    return id;
}

void Terminal::getTerminalState() {
    Data data;
    memset(&data, 0, sizeof(data));
    strcpy(data.buffer, Utils::terminalStateToString(terminalState).c_str());
    writeToPipe(data);
}

void Terminal::setActive(bool active_) {
    active = active_;
}

void Terminal::getUsers() {
    std::string message;
    for (int i = 0; i < users.size(); i++) {
        message += users[i].getName() + " " + Utils::userPrivilegeToString(users[i].getUserPrivilege()) + "\n";
    }
    Data data;
    memset(&data, 0, sizeof(data));
    strcpy(data.buffer, message.c_str());
    writeToPipe(data);
}

void Terminal::getPrograms() {
    std::string message;
    for (int i = 0; i < programs.size(); i++) {
        message += programs[i].getName() + " " + Utils::userPrivilegeToString(users[i].getUserPrivilege()) + "\n";
    }
    Data data;
    memset(&data, 0, sizeof(data));
    strcpy(data.buffer, message.c_str());
    writeToPipe(data);
}

void Terminal::installProgram(std::string name) {
    Data data;
    memset(&data, 0, sizeof(data));
    std::string message;
    if (UtilMethods::inVector(programs, name)) {
        message = "Программа уже установлена.\n";
    } else {
        programs.push_back(UtilMethods::findProgramByName(programs, name));
        message = "Программа установлена.\n";
    }
    strcpy(data.buffer, message.c_str());
    writeToPipe(data);
}

void Terminal::updateProgram(std::string name) {
    Data data;
    memset(&data, 0, sizeof(data));
    std::string message;
    if (UtilMethods::inVector(programs, name)) {
        message = "Программа обновлена.\n";
    } else {
        message = "Программа еще не установлена.\n";
    }
    strcpy(data.buffer, message.c_str());
    writeToPipe(data);
}

void Terminal::reinstallProgram(std::string name) {
    Data data;
    memset(&data, 0, sizeof(data));
    std::string message;
    if (UtilMethods::inVector(programs, name)) {
        message = "Программа удалена.\n";
        programs.erase(programs.begin() + UtilMethods::findProgramIndex(programs, name));
    } else {
        message = "Программа еще не установлена.\n";
    }
    strcpy(data.buffer, message.c_str());
    writeToPipe(data);
}

void Terminal::addUser(std::string name) {
    Data data;
    memset(&data, 0, sizeof(data));
    std::string message;
    if (UtilMethods::inVector(users, name)) {
        message = "Пользователь уже есть в списке.\n";
    } else {
        users.push_back(UtilMethods::findUserByName(users, name));
        message = "Пользователь добавлен в список.\n";
    }
    strcpy(data.buffer, message.c_str());
    writeToPipe(data);
}

void Terminal::removeUser(std::string name) {
    Data data;
    memset(&data, 0, sizeof(data));
    std::string message;
    if (UtilMethods::inVector(users, name)) {
        message = "Пользователь удален.\n";
        users.erase(users.begin() + UtilMethods::findUserIndex(users, name));
    } else {
        message = "Пользователя еще нет в списке.\n";
    }
    strcpy(data.buffer, message.c_str());
    writeToPipe(data);
}

void Terminal::setTerminalState(TerminalState state) {
    std::string message;
    if (state == Online) {
        message = "включен.";
    } else {
        message = "выключен.";
    }
    Data data;
    memset(&data, 0, sizeof(data));
    std::string finalMessage;
    if (state != terminalState) {
        finalMessage = "Терминал " + message;
        terminalState = state;
    } else {
        finalMessage = "Терминал уже " + message;
    }
    strcpy(data.buffer, finalMessage.c_str());
    writeToPipe(data);
}

void Terminal::writeToPipe(Data data) {
    pthread_mutex_lock(&Utils::adminMutex);
    int file = open(adminPipePath.c_str(), O_WRONLY);
    write(file, &data, sizeof(data));
    close(file);
    pthread_mutex_unlock(&Utils::adminMutex);
}

void* Terminal::readFromPipe(void *arg) {
    Terminal *terminal = reinterpret_cast<Terminal *>(arg);
    int file = open(terminal->terminalPipePath.c_str(), O_RDONLY);
    while (terminal->active) {
        Data data;
        pthread_mutex_lock(&Utils::terminalMutex);
        ssize_t size = read(file, &data, sizeof(data));
        if (size != sizeof(Data)) {
            pthread_mutex_unlock(&Utils::terminalMutex);
            continue;
        } else {
            switch (data.command) {
                case GetTerminalState:
                    terminal->getTerminalState();
                    break;
                case GetPrograms:
                    terminal->getPrograms();
                    break;
                case InstallProgram:
                    terminal->installProgram(data.buffer);
                    break;
                case UpdateProgram:
                    terminal->updateProgram(data.buffer);
                    break;
                case ReinstallProgram:
                    terminal->reinstallProgram(data.buffer);
                    break;
                case GetUsers:
                    terminal->getUsers();
                    break;
                case AddUser:
                    terminal->addUser(data.buffer);
                    break;
                case RemoveUser:
                    terminal->removeUser(data.buffer);
                    break;
                case SetTerminalState:
                    terminal->setTerminalState(Utils::stringToTerminalState(data.buffer));
                    break;
                default:
                    continue;
            }
            pthread_mutex_unlock(&Utils::terminalMutex);
        }
    }
    close(file);
}