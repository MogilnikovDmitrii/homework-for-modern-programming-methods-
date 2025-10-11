
#include <fstream>
#include <iostream>
#include "books.hpp"


vector <Book> library;
int nextId = 0;

void loadLibrary() {
    ifstream file("resources/books.txt");
    if(!file.is_open()) ofstream file("resources/books.txt");;

    string line;
    while (getline(file,line))
    {
        size_t pos1 = line.find('|');
        size_t pos2 = line.rfind('|');
        if (pos1 == string::npos || pos2 == pos1) continue;
        int id = stoi(line.substr(0,pos1));
        string title = line.substr(pos1 + 1, pos2 - pos1 - 1);
        string author = line.substr(pos2 + 1);

        library.push_back({id,title,author});
        if (id >= nextId) nextId = id + 1;
    }
    file.close();
}

void saveBook(const Book& book) {
    ofstream file("resources/books.txt", ios::app);
    if (!file.is_open()) {
        ofstream file("resources/books.txt");
    }
    file << book.id << "|" << book.title << "|" << book.author << "\n";
    file.close();
}