#pragma once

#include <string>
#include <vector>

struct Book {
    const int id;
    std::string title;
    std::string author;
};

extern std::vector <Book> library;
extern int nextId;

void loadLibrary();
void saveBook(const Book& book);