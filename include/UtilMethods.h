#ifndef PROCESSMANAGER_UTILMETHODS_H
#define PROCESSMANAGER_UTILMETHODS_H

#include "stdafx.h"
#include "User.h"
#include "Program.h"

class UtilMethods {
public:
    static std::vector<User> initUsers();

    static std::vector<Program> initPrograms();
};

#endif