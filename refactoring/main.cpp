#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <functional>
#include "commands.hpp"

int main() {
    std::cout << "Welcome!! waiting for the command:";
    std::string line;
    std::map<std::string, std::function<void()>> commands;
    Commands(commands);
    std::string command;
    while (true){
        std::cout << "> ";
        std::getline(std::cin, command);
        if (commands.count(command)) {
            commands[command]();
        } else {
            std::cerr << "Unexpected command!\n" << "Enter 'help' to see commands";
        }
    }
    

}