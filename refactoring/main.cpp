#include "commands.hpp"

#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include <string>

int main() {
    std::cout << "Добро пожаловать!! Ожидание команды:";
    std::map<std::string, std::function<void()>> commands;
    initializeCommands(commands);

    std::string command;
    
    while (true){
        std::cout << "> ";
        std::getline(std::cin, command);
        if (commands.count(command)) {
            commands[command]();
        } else {
            std::cerr << "Неизвестная команда!\n" 
            << "Введите 'help' чтобы увидеть список команд";
        }
    }
}