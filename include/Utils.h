#ifndef PROCESSMANAGER_UTILS_H
#define PROCESSMANAGER_UTILS_H

#include "stdafx.h"

enum UserPrivilege {
    Admin_,
    User_
};

enum TerminalState {
    Online,
    Offline
};

class Utils {
private:
    inline static pthread_mutex_t adminMutex;

    inline static pthread_mutex_t terminalMutex;

public:
    static pthread_mutex_t getAdminMutex();

    static pthread_mutex_t getTerminalMutex();

    static std::string userPrivilegeToString(UserPrivilege userPrivilege);

    static std::string terminalStateToString(TerminalState terminalState);
};

#endif