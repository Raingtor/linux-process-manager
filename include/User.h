#ifndef PROCESSMANAGER_USER_H
#define PROCESSMANAGER_USER_H

#include "stdafx.h"
#include "Utils.h"

class User {
private:
    std::string name;

    UserPrivilege userPrivilege;

public:
    User();

    User(std::string name_, UserPrivilege userPrivilege_);

    std::string getName();

    UserPrivilege getUserPrivilege();
};

#endif