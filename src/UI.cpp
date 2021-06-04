#include "../include/UI.h"

void UI::start() {
    admin = Admin();
    startMenu();
}

void UI::startMenu() {
    std::cout << "1. Посмотреть состояние всех терминалов в сети." << std::endl;
    std::cout << "2. Выбрать терминал для работы." << std::endl;
    std::cout << "3. Выход" << std::endl;
    int choice = input();
    switch (choice) {
        case 1:
            admin.getTerminalsState();
        case 2:
            chooseTerminal();
        case 3:
            exit();
        default:
            std::cout << "Нераспознанная команда." << std::endl;
            startMenu();
    }
}

void UI::exit() {
    ::exit(0);
}

void UI::chooseTerminal() {
    showTerminals();
    int choice = input();
    admin.setCurrentTerminal(admin.getTerminals()[choice].getId());
    workWithTerminal();
}

void UI::workWithTerminal() {
    std::cout << "1. Посмотреть состояние терминала." << std::endl;
    std::cout << "2. Работа с ПО." << std::endl;
    std::cout << "3. Работа с терминалом." << std::endl;
    std::cout << "4. Вернуться в меню." << std::endl;
    std::cout << "5. Выход." << std::endl;
    int choice = input();
    switch (choice) {
        case 1:
            admin.getTerminalState();
        case 2:
            editPrograms();
        case 3:
            editTerminal();
        case 4:
            startMenu();
        case 5:
            exit();
        default:
            std::cout << "Нераспознанная команда." << std::endl;
            workWithTerminal();
    }
}

void UI::editPrograms() {
    std::cout << "1. Просмотреть установленное ПО." << std::endl;
    std::cout << "2. Установить ПО." << std::endl;
    std::cout << "3. Обновить ПО." << std::endl;
    std::cout << "4. Удалить ПО." << std::endl;
    std::cout << "5. Вернуться в меню." << std::endl;
    std::cout << "6. Выход." << std::endl;
    int choice = input();
    switch (choice) {
        case 1:
            admin.getTerminalPrograms();
        case 2:
            installProgram();
        case 3:
            updateProgram();
        case 4:
            reinstallProgram();
        case 5:
            startMenu();
        case 6:
            exit();
        default:
            std::cout << "Нераспознанная команда." << std::endl;
            workWithTerminal();
    }
}

void UI::installProgram() {
    showPrograms();
    int programChoice = input();
    admin.installProgram(admin.getPrograms()[programChoice].getName());
}

void UI::updateProgram() {
    showPrograms();
    int programChoice = input();
    admin.updateProgram(admin.getPrograms()[programChoice].getName());
}

void UI::reinstallProgram() {
    showPrograms();
    int programChoice = input();
    admin.reinstallProgram(admin.getPrograms()[programChoice].getName());
}

void UI::editTerminal() {
    std::cout << "1. Просмотреть список пользователей." << std::endl;
    std::cout << "2. Добавить пользователя." << std::endl;
    std::cout << "3. Удалить пользователя." << std::endl;
    std::cout << "4. Изменить состояние терминала." << std::endl;
    std::cout << "4. Выбрать другой терминал." << std::endl;
    std::cout << "5. Вернуться в меню." << std::endl;
    std::cout << "6. Выход." << std::endl;
    int choice = input();
    switch (choice) {
        case 1:
            admin.getTerminalUsers();
        case 2:
            addUser();
        case 3:
            removeUser();
        case 4:
            chooseTerminal();
        case 5:
            startMenu();
        case 6:
            exit();
        default:
            std::cout << "Нераспознанная команда." << std::endl;
            workWithTerminal();
    }
}

void UI::addUser() {
    showUsers();
    int programChoice = input();
    admin.addUser(admin.getUsers()[programChoice].getName());
}

void UI::removeUser() {
    showUsers();
    int programChoice = input();
    admin.removeUser(admin.getUsers()[programChoice].getName());
}

void UI::setTerminalState() {
    std::cout << "1. Включить." << std::endl;
    std::cout << "2. Выключить." << std::endl;
    int programChoice = input();
    TerminalState state;
    switch (programChoice) {
        case 1:
            state = Online;
        case 2:
            state = Offline;
        default:
            std::cout << "Нераспознанная команда." << std::endl;
            setTerminalState();
    }
    admin.setTerminalState(state);
}

void UI::showUsers() {
    std::vector<User> users = admin.getUsers();
    for (int i = 0; i < users.size(); i++) {
        std::cout << i << ". " << users[i].getName() << std::endl;
    }
}

void UI::showPrograms() {
    std::vector<Program> programs = admin.getPrograms();
    for (int i = 0; i < programs.size(); i++) {
        std::cout << i << ". " << programs[i].getName() << std::endl;
    }
}

void UI::showTerminals() {
    std::vector<Terminal> terminals = admin.getTerminals();
    for (int i = 0; i < terminals.size(); i++) {
        std::cout << i << ". " << terminals[i].getId() << std::endl;
    }
}

int UI::input() {
    std::cout << ">> ";
    int index;
    std::cin >> index;
}