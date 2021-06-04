#include "../include/Admin.h"

Admin::Admin() {
    users = UtilMethods::initUsers();
    programs = UtilMethods::initPrograms();
    terminals.push_back(Terminal(0, Online));
    terminals.push_back(Terminal(1, Offline));
    adminPipePath = "./admin";
    pthread_mutex_init(&Utils::adminMutex, nullptr);
    pthread_mutex_init(&Utils::terminalMutex, nullptr);
    mkfifo(adminPipePath.c_str(), 0666);
}

std::vector<User> Admin::getUsers() {
    return users;
}

std::vector<Program> Admin::getPrograms() {
    return programs;
}

std::vector<Terminal> Admin::getTerminals() {
    return terminals;
}

void Admin::setCurrentTerminal(size_t currentTerminal_) {
    currentTerminal = currentTerminal_;
    terminalPipePath = "./terminal" + std::to_string(currentTerminal);
    mkfifo(terminalPipePath.c_str(), 0666);
    terminals[currentTerminal].start();
}

void Admin::getTerminalState() {
    Data data;
    data.command = GetTerminalState;
    data.info = "";
    writeToPipe(data);
    readFromPipe();
}

void Admin::getTerminalsState() {
    for (int i = 0; i < terminals.size(); i++) {
        currentTerminal = terminals[i].getId();
        getTerminalState();
    }
}

void Admin::getTerminalPrograms() {
    Data data;
    data.command = GetPrograms;
    data.info = "";
    writeToPipe(data);
    readFromPipe();
}

void Admin::installProgram(std::string name) {
    Data data;
    data.command = InstallProgram;
    data.info = name;
    writeToPipe(data);
    readFromPipe();
}

void Admin::updateProgram(std::string name) {
    Data data;
    data.command = UpdateProgram;
    data.info = name;
    writeToPipe(data);
    readFromPipe();
}

void Admin::reinstallProgram(std::string name) {
    Data data;
    data.command = ReinstallProgram;
    data.info = name;
    writeToPipe(data);
    readFromPipe();
}

void Admin::getTerminalUsers() {
    Data data;
    data.command = GetUsers;
    data.info = "";
    writeToPipe(data);
    readFromPipe();
}

void Admin::addUser(std::string name) {
    Data data;
    data.command = AddUser;
    data.info = name;
    writeToPipe(data);
    readFromPipe();
}

void Admin::removeUser(std::string name) {
    Data data;
    data.command = RemoveUser;
    data.info = name;
    writeToPipe(data);
    readFromPipe();
}

void Admin::setTerminalState(TerminalState state) {
    Data data;
    data.command = SetTerminalState;
    data.info = Utils::terminalStateToString(state);
    writeToPipe(data);
    readFromPipe();
}

void Admin::writeToPipe(Data data) {
    pthread_mutex_lock(&Utils::terminalMutex);
    int file = open(terminalPipePath.c_str(), O_WRONLY);
    write(file, &data, sizeof(data));
    close(file);
    pthread_mutex_unlock(&Utils::terminalMutex);
}

void Admin::readFromPipe() {
    while (true) {
        Data data;
        pthread_mutex_lock(&Utils::adminMutex);
        int file = open(adminPipePath.c_str(), O_RDONLY);
        ssize_t size = read(file, &data, sizeof(data));
        if (size != sizeof(Data)) {
            pthread_mutex_unlock(&Utils::adminMutex);
            continue;
        }
        std::cout << data.info << std::endl;
    }
}