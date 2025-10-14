#pragma once
#include <vector>
#include <string>
using namespace std;

struct Book {
    int id;
    string title;
    string author;
};
extern vector <Book> library;
extern int nextId;

void loadLibrary();
void saveBook(const Book& book);