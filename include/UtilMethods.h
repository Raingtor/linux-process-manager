#ifndef PROCESSMANAGER_UTILMETHODS_H
#define PROCESSMANAGER_UTILMETHODS_H

#include "stdafx.h"
#include "User.h"
#include "Program.h"

class UtilMethods {
public:
    static std::vector<User> initUsers();

    static std::vector<Program> initPrograms();

    static bool inVector(std::vector<User> users, std::string name);

    static bool inVector(std::vector<Program> programs, std::string name);

    static User findUserByName(std::vector<User> users, std::string name);

    static Program findProgramByName(std::vector<Program> programs, std::string name);

    static int findUserIndex(std::vector<User> users, std::string name);

    static int findProgramIndex(std::vector<Program> programs, std::string name);
};

#endif