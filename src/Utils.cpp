#include "../include/Utils.h"

std::string Utils::userPrivilegeToString(UserPrivilege userPrivilege) {
    switch (userPrivilege) {
        case Admin_:
            return "Admin";
        case User_:
            return "User";
        default:
            return "";
    }
}

std::string Utils::terminalStateToString(TerminalState terminalState) {
    switch (terminalState) {
        case Online:
            return "Online";
        case Offline:
            return "Offline";
        default:
            return "";
    }
}

TerminalState Utils::stringToTerminalState(std::string state) {
    if (state == "Online") {
        return Online;
    } else {
        return Offline;
    }
}
