#ifndef PROCESSMANAGER_PROGRAM_H
#define PROCESSMANAGER_PROGRAM_H

#include "stdafx.h"
#include "Utils.h"

class Program {
private:
    std::string name;

    UserPrivilege userPrivilege;

public:
    Program();

    Program(std::string name_, UserPrivilege userPrivilege_);

    std::string getName();

    UserPrivilege getUserPrivilege();
};

#endif