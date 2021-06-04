#ifndef PROCESSMANAGER_UTILMETHODS_H
#define PROCESSMANAGER_UTILMETHODS_H

#include "stdafx.h"
#include "User.h"
#include "Program.h"

class UtilMethods {
public:
    std::vector<User> initUsers();

    std::vector<Program> initPrograms();
};

#endif