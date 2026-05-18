#pragma once

#include "Library.h"
#include "Storage.h"

class Menu {
public:
    Menu(Library& library, Storage& storage);
    void run();

private:
    void showMainMenu() const;
    void listBooks() const;
    void listMembers() const;
    void listActiveLoans() const;
    void addBook();
    void addMember();
    void borrowBook();
    void returnBook();
    void searchBooks() const;
    void saveData() const;

    Library& library;
    Storage& storage;
};
