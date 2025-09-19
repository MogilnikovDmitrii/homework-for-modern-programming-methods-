#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <functional>
using namespace std;

int main() {
    ifstream help("hepl.txt");
    if (!help.is_open()) {
        cout << "Fatal! help didn't open \n";
        return 1;
    }

    cout << "Welcome! waiting for the command:";
    map<string, function<void()>> commands;

    
    string line;
    commands["help"] = [&help, &line](){
        help.clear();
        help.seekg(0);
        while (getline(help, line)) { 
        cout << line << endl;      
        }
    };
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