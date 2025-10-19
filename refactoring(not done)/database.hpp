#pragma once

#include <vector>
#include <string>

struct Book {
    int id;
    std::string title;
    std::string author;
};
extern std::vector <Book> library;
extern int nextId;

void loadLibrary();
void saveBook(const Book& book);