#include "commands.hpp"
#include "database.hpp"

#include <cstdlib>
#include <fstream>
#include <iostream>



void  Commands(std::map<std::string, std::function<void()>>& commands) {
    commands["help"] = []() {
    std::ifstream file("resources/help.txt");  
    if (!file.is_open()) {
        std::cerr << "Невозможно открыть help.txt\n";
        return;
    }
    std::string line;
    while (std::getline(file, line)) {
        std::cout << line << std::endl;
    }
    };

    commands["exit"] = []() {
        std::cout << "Выход...\n";
        exit(0);
    };

    commands["add"] = []() {
        std::string author,title;
        std::cout << "Введите автора: ";
        getline(std::cin, author);
        std::cout << "Введите название: ";
        getline(std::cin, title);
        nextId += 1;
        Book newBook{nextId, title, author};
        library.push_back(newBook);
        saveBook(newBook);

        std::cout << "Книга добавлена! ID = " << newBook.id << ", Название = " << newBook.title<< ", Автор = " << newBook.author << std::endl;

    }; 
    
    commands["list"] = []() {
        std::ifstream file2("resources/books.txt");  
        if (!file2.is_open()) {
            std::ofstream file2("resources/books.txt");
        }
        std::cout << "All books: \n";
        std::string line2;
        while (getline(file2, line2)) {
            std::cout << line2 << std::endl;
        }
    };
}