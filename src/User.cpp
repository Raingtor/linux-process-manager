#include "../include/User.h"

User::User() {

};

User::User(std::string name_, UserPrivilege userPrivilege_) {
    name = name_;
    userPrivilege = userPrivilege_;
}

std::string User::getName() {
    return name;
}

UserPrivilege User::getUserPrivilege() {
    return userPrivilege;
}