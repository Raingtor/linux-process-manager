#include "../include/Admin.h"

Admin::Admin() {
    users = UtilMethods::initUsers();
    programs = UtilMethods::initPrograms();
    terminals.push_back(Terminal(0, Online));
    terminals.push_back(Terminal(1, Offline));
    adminPipePath = "./admin";
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
}

void Admin::getTerminalState() {

}

void Admin::getTerminalsState() {

}

void Admin::getTerminalPrograms() {

}

void Admin::installProgram(std::string name) {

}

void Admin::updateProgram(std::string name) {

}

void Admin::reinstallProgram(std::string name) {

}

void Admin::getTerminalUsers() {

}

void Admin::addUser(std::string name) {

}

void Admin::removeUser(std::string name) {

}

void Admin::setTerminalState(TerminalState state) {

}