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

TerminalState Terminal::getTerminalState() {
    return terminalState;
}

std::vector<User> Terminal::getUsers() {
    return users;
}

std::vector<Program> Terminal::getPrograms() {
    return programs;
}