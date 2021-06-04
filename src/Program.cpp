#include "../include/Program.h"

Program::Program() {

};

Program::Program(std::string name_, UserPrivilege userPrivilege_) {
    name = name_;
    userPrivilege = userPrivilege_;
}

std::string Program::getName() {
    return name;
}

UserPrivilege Program::getUserPrivilege() {
    return userPrivilege;
}