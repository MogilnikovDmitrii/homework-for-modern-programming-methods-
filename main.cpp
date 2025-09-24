#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <functional>
#include "./commands/commands.h"
using namespace std;


int main() {
    cout << "Welcome!! waiting for the command:";
    string line;
    map<string, function<void()>> commands;
    Commands(commands);
    string command;
    while (true)
    {
        cout << "> ";
        getline(cin, command);
        if (commands.count(command)) {
            commands[command]();
        } else {
            cout << "Unexpected command!\n";
        }
    }
    

}