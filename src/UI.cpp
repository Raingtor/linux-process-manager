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
            sleep(1);
            startMenu();
            break;
        case 2:
            chooseTerminal();
            break;
        case 3:
            exit(0);
        default:
            std::cout << "Нераспознанная команда." << std::endl;
            startMenu();
    }
}

void UI::chooseTerminal() {
    showTerminals();
    int choice = input();
    admin.getTerminals()[admin.getCurrentTerminal()].setActive(false);
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
            sleep(1);
            workWithTerminal();
            break;
        case 2:
            editPrograms();
            break;
        case 3:
            editTerminal();
            break;
        case 4:
            sleep(1);
            startMenu();
            break;
        case 5:
            exit(0);
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
            sleep(1);
            editPrograms();
            break;
        case 2:
            installProgram();
            sleep(1);
            editPrograms();
            break;
        case 3:
            updateProgram();
            sleep(1);
            editPrograms();
            break;
        case 4:
            reinstallProgram();
            sleep(1);
            editPrograms();
            break;
        case 5:
            sleep(1);
            startMenu();
            break;
        case 6:
            exit(0);
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
    std::cout << "5. Выбрать другой терминал." << std::endl;
    std::cout << "6. Вернуться в меню." << std::endl;
    std::cout << "7. Выход." << std::endl;
    int choice = input();
    switch (choice) {
        case 1:
            admin.getTerminalUsers();
            sleep(1);
            editTerminal();
            break;
        case 2:
            addUser();
            sleep(1);
            editTerminal();
            break;
        case 3:
            removeUser();
            sleep(1);
            editTerminal();
            break;
        case 4:
            setTerminalState();
            sleep(1);
            editTerminal();
            break;
        case 5:
            chooseTerminal();
            sleep(1);
            editTerminal();
            break;
        case 6:
            sleep(1);
            startMenu();
            break;
        case 7:
            exit(0);
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
            break;
        case 2:
            state = Offline;
            break;
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
    return index;
}