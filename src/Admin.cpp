#include "../include/Admin.h"

Admin::Admin() {
    users = UtilMethods::initUsers();
    programs = UtilMethods::initPrograms();
    terminals.push_back(Terminal(0, Online));
    terminals.push_back(Terminal(1, Offline));
    for (int i = 0; i < terminals.size(); i++) {
        std::ofstream logFile(terminals[i].getLogFilePath(), std::ios::trunc);
        logFile.close();
    }
    adminPipePath = "./admin";
    unlink(adminPipePath.c_str());
    mkfifo(adminPipePath.c_str(), 0666);
    pthread_mutex_init(&Utils::adminMutex, nullptr);
    pthread_mutex_init(&Utils::terminalMutex, nullptr);
}

void Admin::start() {
    pthread_create(&thread, nullptr, Admin::readFromPipe, this);
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

size_t Admin::getCurrentTerminal() {
    return currentTerminal;
}

void Admin::setCurrentTerminal(size_t currentTerminal_) {
    currentTerminal = currentTerminal_;
    terminalPipePath = "./terminal" + std::to_string(currentTerminal);
    unlink(terminalPipePath.c_str());
    mkfifo(terminalPipePath.c_str(), 0666);
    terminals[currentTerminal].setActive(true);
    terminals[currentTerminal].start();
}

void Admin::getTerminalState() {
    Data data;
    memset(&data, 0, sizeof(data));
    data.command = GetTerminalState;
    writeToPipe(data);
}

void Admin::getTerminalsState() {
    for (int i = 0; i < terminals.size(); i++) {
        setCurrentTerminal(terminals[i].getId());
        getTerminalState();
    }
}

void Admin::getTerminalPrograms() {
    Data data;
    memset(&data, 0, sizeof(data));
    data.command = GetPrograms;
    writeToPipe(data);
}

void Admin::installProgram(std::string name) {
    Data data;
    memset(&data, 0, sizeof(data));
    data.command = InstallProgram;
    strcpy(data.buffer, name.c_str());
    writeToPipe(data);
}

void Admin::updateProgram(std::string name) {
    Data data;
    memset(&data, 0, sizeof(data));
    data.command = UpdateProgram;
    strcpy(data.buffer, name.c_str());
    writeToPipe(data);
}

void Admin::reinstallProgram(std::string name) {
    Data data;
    memset(&data, 0, sizeof(data));
    data.command = ReinstallProgram;
    strcpy(data.buffer, name.c_str());
    writeToPipe(data);
}

void Admin::getTerminalUsers() {
    Data data;
    memset(&data, 0, sizeof(data));
    data.command = GetUsers;
    writeToPipe(data);
}

void Admin::addUser(std::string name) {
    Data data;
    memset(&data, 0, sizeof(data));
    data.command = AddUser;
    strcpy(data.buffer, name.c_str());
    writeToPipe(data);
}

void Admin::removeUser(std::string name) {
    Data data;
    memset(&data, 0, sizeof(data));
    data.command = RemoveUser;
    strcpy(data.buffer, name.c_str());
    writeToPipe(data);
}

void Admin::setTerminalState(TerminalState state) {
    Data data;
    memset(&data, 0, sizeof(data));
    data.command = SetTerminalState;
    strcpy(data.buffer, Utils::terminalStateToString(state).c_str());
    writeToPipe(data);
}

void Admin::writeToPipe(Data data) {
    pthread_mutex_lock(&Utils::terminalMutex);
    int file = open(terminalPipePath.c_str(), O_WRONLY);
    write(file, &data, sizeof(data));
    close(file);
    pthread_mutex_unlock(&Utils::terminalMutex);
}

void* Admin::readFromPipe(void *arg) {
    Admin *admin = reinterpret_cast<Admin *>(arg);
    int file = open(admin->adminPipePath.c_str(), O_RDONLY);
    while (true) {
        Data data;
        pthread_mutex_lock(&Utils::adminMutex);
        ssize_t size = read(file, &data, sizeof(data));
        if (size != sizeof(Data)) {
            pthread_mutex_unlock(&Utils::adminMutex);
            continue;
        }
        std::cout << data.buffer << std::endl;
        pthread_mutex_unlock(&Utils::adminMutex);
    }
    close(file);
}