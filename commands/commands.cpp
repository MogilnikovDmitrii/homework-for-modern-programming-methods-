#include "commands.h"
#include <iostream>
#include <fstream>
using namespace std;

void  setupCommands(map<string, function<void()>>& commands) {
    commands["help"] = []() {
    ifstream file("help.txt");  // локальный поток
    if (!file.is_open()) {
        cout << "Cannot open help.txt\n";
        return;
    }
    string line;
    while (getline(file, line)) {
        cout << line << endl;
    }
};

}