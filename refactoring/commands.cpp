#include "commands.hpp"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include "database.hpp"
using namespace std;

void  Commands(map<string, function<void()>>& commands) {
    commands["help"] = []() {
    ifstream file("resources/help.txt");  
    if (!file.is_open()) {
        cerr << "Cannot open help.txt\n";
        return;
    }
    string line;
    while (getline(file, line)) {
        cout << line << endl;
    }
    };
    commands["exit"] = []() {
        cout << "Exiting...\n";
        exit(0);
    };
    commands["add"] = []() {
        string author,title;
        cout << "Enter author: ";
        getline(cin, author);
        cout << "Enter title: ";
        getline(cin, title);
        nextId += 1;
        Book newBook{nextId, title, author};
        library.push_back(newBook);
        saveBook(newBook);

        cout << "Book added! ID = " << newBook.id << ", Title = " << newBook.title<< ", Author = " << newBook.author << endl;

    }; // kakashki
    commands["list"] = []() {
        ifstream file2("resources/books.txt");  
        if (!file2.is_open()) {
            ofstream file2("resources/books.txt");
        }
        cout << "All books: \n";
        string line2;
        while (getline(file2, line2)) {
            cout << line2 << endl;
        }
    };
}