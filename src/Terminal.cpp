#include "../include/Terminal.h"

Terminal::Terminal() {

}

Terminal::Terminal(size_t id_, TerminalState terminalState_) {
    id = id_;
    terminalState = terminalState_;
    adminPipePath = "./admin";
    terminalPipePath = "./terminal" + std::to_string(id);
    logFilePath = "./logTerminal" + std::to_string(id);
}

void Terminal::start() {
    pthread_create(&thread, nullptr, Terminal::readFromPipe, this);
    std::ofstream logFile(logFilePath.c_str(), std::ofstream::app);
    logFile << "Начата работа с терминалом." << std::endl;
    logFile.close();
    active = true;
}

size_t Terminal::getId() {
    return id;
}

void Terminal::getTerminalState() {
    Data data;
    memset(&data, 0, sizeof(data));
    std::string message = std::to_string(getId()) + " " + Utils::terminalStateToString(terminalState);
    strcpy(data.buffer, message.c_str());
    writeToPipe(data);
}

bool Terminal::getActive() {
    return active;
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
        message += programs[i].getName() + " " + Utils::userPrivilegeToString(programs[i].getUserPrivilege()) + "\n";
    }
    Data data;
    memset(&data, 0, sizeof(data));
    strcpy(data.buffer, message.c_str());
    writeToPipe(data);
}

std::string Terminal::getLogFilePath() {
    return logFilePath;
}

void Terminal::installProgram(std::string name) {
    Data data;
    memset(&data, 0, sizeof(data));
    std::string message;
    if (UtilMethods::inVector(programs, name)) {
        message = "Программа уже установлена.\n";
    } else {
        programs.push_back(UtilMethods::findProgramByName(UtilMethods::initPrograms(), name));
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
        users.push_back(UtilMethods::findUserByName(UtilMethods::initUsers(), name));
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

void *Terminal::readFromPipe(void *arg) {
    Terminal *terminal = reinterpret_cast<Terminal *>(arg);
    int file = open(terminal->terminalPipePath.c_str(), O_RDONLY);
    while (terminal->active) {
        Data data;
        pthread_mutex_lock(&Utils::terminalMutex);
        ssize_t size = read(file, &data, sizeof(data));
        if (size != sizeof(Data)) {
            pthread_mutex_unlock(&Utils::terminalMutex);
            continue;
        } else if (data.command == StopTerminal) {
            close(file);
            pthread_mutex_unlock(&Utils::terminalMutex);
            terminal->stop();
        } else {
            std::string message;
            switch (data.command) {
                case GetTerminalState:
                    message = "Запрос на получение состояния терминала.";
                    terminal->getTerminalState();
                    break;
                case GetPrograms:
                    message = "Запрос на получение списка ПО.";
                    terminal->getPrograms();
                    break;
                case InstallProgram:
                    message = "Запрос на добавление ПО " + std::string(data.buffer) + ".";
                    terminal->installProgram(data.buffer);
                    break;
                case UpdateProgram:
                    message = "Запрос на обновление ПО " + std::string(data.buffer) + ".";
                    terminal->updateProgram(data.buffer);
                    break;
                case ReinstallProgram:
                    message = "Запрос на удаление ПО " + std::string(data.buffer) + ".";
                    terminal->reinstallProgram(data.buffer);
                    break;
                case GetUsers:
                    message = "Запрос на получение списка пользователей.";
                    terminal->getUsers();
                    break;
                case AddUser:
                    message = "Запрос на добавление пользователя " + std::string(data.buffer) + ".";
                    terminal->addUser(data.buffer);
                    break;
                case RemoveUser:
                    message = "Запрос на удаление пользователя " + std::string(data.buffer) + ".";
                    terminal->removeUser(data.buffer);
                    break;
                case SetTerminalState:
                    message = "Запрос на изменение состояния терминала на " + std::string(data.buffer) + ".";
                    terminal->setTerminalState(Utils::stringToTerminalState(data.buffer));
                    break;
                default:
                    continue;
            }
            std::ofstream logFile(terminal->logFilePath.c_str(), std::ofstream::app);
            logFile << message << std::endl;
            logFile.close();
            pthread_mutex_unlock(&Utils::terminalMutex);
        }
    }
}

void Terminal::stop() {
    std::ofstream logFile(logFilePath.c_str(), std::ofstream::app);
    logFile << "Завершена работа с терминалом." << std::endl;
    logFile.close();
    active = false;
    pthread_cancel(thread);
}

Terminal::~Terminal() {

}
